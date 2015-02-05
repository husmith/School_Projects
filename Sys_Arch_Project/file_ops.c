/**CFile***********************************************************************

  FileName    [file_ops.c]

  Synopsis    [contains all functionality for ex/importing to/from a file]

  Author      [Aaron Stromberg]

  Copyright   [Copyright (c) 2012 Carlos III University of Madrid
  All rights reserved.

  Permission is hereby granted, without written agreement and without license
  or royalty fees, to use, copy, modify, and distribute this software and its
  documentation for any purpose, provided that the above copyright notice and
  the following two paragraphs appear in all copies of this software.

  IN NO EVENT SHALL THE CARLOS III UNIVERSITY OF MADRID BE LIABLE TO ANY PARTY 
  FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING 
  OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE CARLOS III
  UNIVERSITY OF MADRID HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  THE CARLOS III UNIVERSITY OF MADRID SPECIFICALLY DISCLAIMS ANY WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
  FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN
  "AS IS" BASIS, AND CARLOS III UNIVERSITY OF MADRID HAS NO OBLIGATION TO 
  PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.]

******************************************************************************/
#include "file_ops.h"
#include "biblio_reference.h"
#include "hash_table.h"
#include "data_read.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*---------------------------------------------------------------------------*/
/* Static function prototypes                                                */
/*---------------------------------------------------------------------------*/
static int write_string_to_file(char *string, FILE *fp);
static int read_string_from_file(char **string, FILE *fp);
static int write_int_to_file(int *integer, FILE *fp);
static int read_int_from_file(int *integer, FILE *fp);
static int write_float_to_file(float *number, FILE *fp);
static int read_float_from_file(float *number, FILE *fp);
static int export_publication(FILE *fp, publication_t *publication);
static int import_publication(FILE *fp, publication_t *publication);

/*---------------------------------------------------------------------------*/
/* Definition of functions                                                   */
/*---------------------------------------------------------------------------*/
/**Function********************************************************************

  Synopsis           exports bibliography to a file. No return value

  Parameters         	char *file_name: 	name of file to write to
			entry_t **table: 	hash_table containing all the entries

  SideEffects        overwrites file if it already exists

******************************************************************************/
void export_to_file(entry_t **table)
{
	printf("\tPlease type in a file name:\n");
	char *file_name = read_text();
	FILE *file;
	file = fopen(file_name, "wb");
	int i;
	entry_t *current_entry;
	for (i = 0; i < TABLE_SIZE; i++)
	{
		current_entry = table[i];

		while (current_entry)
		{
			if (export_publication(file, current_entry->publication))
			{
				printf("Error while writing the file!\n");
				fclose(file);

				return;
			}
			current_entry = current_entry->next;
		}
	}
	fclose(file);
}

/**Function********************************************************************

  Synopsis           imports a bibliography from a file, adding entries to current hash table. No return value

  Parameters         	char *file_name: 	name of file to read from
			entry_t **table: 	hash_table containing all the entries

  SideEffects        could cause repeat entries if a file is imported multiple times or if the file contains publications that already exist

******************************************************************************/
void import_from_file(entry_t **table)
{
	printf("\tPlease type a filename to import from:\n");
	char *file_name = read_text();
	FILE *file;
	file = fopen(file_name, "rb");
	if (!file)
	{
		printf("\nCouldn't open that file! Did you spell it correctly?\n");
		return;
	}
	int c = fgetc(file);
	while (c != EOF)
	{
		ungetc(c, file);
		publication_t *current_pub = (publication_t*)malloc(sizeof(publication_t));

		if (import_publication(file, current_pub))
		{
			printf("Error while reading the file!\n");
			break;
		}

		insert_entry(table, current_pub);
		c = fgetc(file);
	}
	if (ferror(file))
		printf("An error occurred while reading the file.\n");

	fclose(file);

	return;
}


/**Function********************************************************************
 It returns the size of the table 

******************************************************************************/
size_t num_of_entries(entry_t **table)
{
	entry_t *current_entry;
	size_t count = 0;
	int i;

	for (i = 0; i < TABLE_SIZE; i++)
	{
		current_entry = table[i];

		while (current_entry)
		{
			count++;
			current_entry = current_entry->next;
		}
	}

	return count;
}

/**Function********************************************************************

  Synopsis           Converts entries to publications and puts them in an array

  Parameters         	char *file_name: 	name of file to read from
			entry_t **table: 	hash_table containing all the entries

  SideEffects        could cause repeat entries if a file is imported multiple times or if the file contains publications that already exist

******************************************************************************/
void table_to_array(publication_t **array, entry_t **table)
{
	entry_t *current_entry;
	int i;
	int entry_num = 0;
	for (i = 0; i < TABLE_SIZE; i++)
	{
		current_entry = table[i];
		while (current_entry)
		{
			array[entry_num] = current_entry->publication;
			entry_num++;
			current_entry = current_entry->next;
		}
	}
}

/*---------------------------------------------------------------------------*/
/* Definition of static functions                                            */
/*---------------------------------------------------------------------------*/
//TODO all these necessary? I don't think supports generics so maybe...THANKS C
/**Function********************************************************************

  Synopsis           writes the length of a string to a file, followed by the string itself. Returns 1 on failed writing

  Parameters		char *string: 	string to write
			FILE *fp: 	file to write too   

******************************************************************************/
static int write_string_to_file(char *string, FILE *fp)
{
	size_t size_of_string = strlen(string);
	if (fwrite(&(size_of_string), sizeof(size_t), 1, fp) != 1 || fwrite(string, sizeof(char), size_of_string, fp) != size_of_string)
	{
		printf("Red alert! Error saving string %s! Aborting!\n", string);
		return 1;
	}
	return 0;
}

/**Function********************************************************************

  Synopsis           reads a string from file and allocates memory for it, 
	assuming a size_t representing the size of the string was written just 
	before the string itself. Returns 1 on failure

  Parameters            char *string:	string to read into (will allocate new
					memory)
                        FILE *fp:	file to read from 

******************************************************************************/
static int read_string_from_file(char **string, FILE *fp)
{
	size_t size_of_string;

	if (feof(fp))
	{
		printf("Can't read the size of the string! You're at the end of the file!\n");

		return 1;
	}
	else if (fread(&(size_of_string), sizeof(size_t), 1, fp) != 1)
	{
		//do I need to check ferror here? or do we know ferror(fp) will be true since we already checked feof(fp), and that passed?
		printf("Error occured while trying to read in the size of the string, which should have been written right before the string itself.\n");

		return 1;
	}
	*string = (char*)malloc(size_of_string * sizeof(char) + 1);
	if (feof(fp))
	{
		printf("Can't read the string! You're at the end of the file!\n");

		return 1;
	}
	else if (fread(*string, sizeof(char), size_of_string, fp) != size_of_string)
	{
		printf("An error occurred while reading in the string!\n");

		return 1;
	}
	(*string)[size_of_string] = '\0';
	return 0;
}

/**Function********************************************************************

  Synopsis           writes an int to a file safely. Returns 1 on failure

  Parameters		int *integer: 	int to write
			FILE *fp: 	file to write too 

******************************************************************************/
static int write_int_to_file(int *integer, FILE *fp)
{
	if (fwrite(integer, sizeof(int), 1, fp) != 1)
	{
		printf("Red alert! Error saving integer %d! Aborting!\n", *integer);

		return 1;
	}

	return 0;
}

/**Function********************************************************************

  Synopsis           reads an int from a file safely. Returns 1 on failure

  Parameters            int *integer:	int to read into
                        FILE fp:        file to read from

******************************************************************************/
static int read_int_from_file(int *integer, FILE *fp)
{
	if (feof(fp))
	{
		printf("Can't read! You're at the end of the file!\n");

		return 1;
	}
	else if (fread(integer, sizeof(int), 1, fp) != 1)
	{
		//do I need to check ferror here? or do we know ferror(fp) will be true since we already checked feof(fp), and that passed?
		printf("Error occured while reading int from file.\n");

		return 1;
	}

	return 0;
}
/**Function********************************************************************

  Synopsis           writes a float to a file safely. Returns 1 on failure

  Parameters		float *number: 	floats to write
			FILE *fp: 	file to read from 

******************************************************************************/
static int write_float_to_file (float *number, FILE *fp)
{
	if (fwrite(number, sizeof(float), 1, fp) != 1)
	{
		printf("Red alert! Error saving float %f! Aborting!\n", *number);

		return 1;
	}
	//fwrite(comma, sizeof(char), 1, fp); //TODO check for errors

	return 0;
}

/**Function********************************************************************

  Synopsis           reads a float from a file safely. Returns 1 on error

  Parameters            float *number:  float to write
                        FILE fp:        file to write too   

******************************************************************************/
static int read_float_from_file(float *number, FILE *fp)
{
	if (feof(fp))
	{
		printf("Can't read! You're at the end of the file!\n");

		return 1;
	}
	else if (fread(number, sizeof(float), 1, fp) != 1)
	{
		//do I need to check ferror here? or do we know ferror(fp) will be true since we already checked feof(fp), and that passed?
		printf("Error occured while reading float from file.\n");

		return 1;
	}

	return 0;
}


/**Function********************************************************************

  Synopsis           writes a publication to a file. The order of writing is as follows:
	Write number of characters in DOI ----| Remember that these are included in a single write_string_to_file() call
	Write DOI ----------------------------|
	Write number of characters in title
	Write title
	Write number of characters in ISBN
	Write isbn
	Write number of characters in source
	Write source
	Write number of characters in authors
	Write authors
	Write the integer year
	Write the float impact 
	Write int which should be 1 if it's a journal, and 0 if it's a conference 
	If conference:
		Write the number of elements in the venue string
		Write the venue
	Else:
		Write the integer volume
		Write the integer article

	returns a 1 on failure

  Parameters         	FILE *fp:	the file we want to export to. Should already be opened
			publication_t *publication: the publication we are trying to write	

******************************************************************************/
//TODO could probably save code with function pointers, consider if you have time
static int export_publication(FILE *fp, publication_t *publication)
{
	//TODO DELETE consider stdbool.h if we have time for type
	//write information common to all publications first
	/*size_t sizeOfDOI = strlen(publication->doi);
	size_t sizeOfTitle = strlen(publication->title);
	size_t sizeOfISBN = strlen(publication->isbn);
	size_t sizeOfSource = strlen(publi*/
	if (write_string_to_file(publication->doi, fp) ||
		write_string_to_file(publication->title, fp) ||
		write_string_to_file(publication->isbn, fp) ||
		write_string_to_file(publication->source, fp) ||
		write_string_to_file(publication->authors, fp) ||
		write_int_to_file(&(publication->year), fp) ||
		write_float_to_file(&(publication->impact), fp) ||
		write_int_to_file(&(publication->is_journal), fp))
	{
		printf("ERROR! Writing failed when trying to write the general publication information!\n");

		return 1;
	}
	else if(publication->is_journal)
	{
		if (write_int_to_file(&(publication->journal.volume), fp) ||
			write_int_to_file(&(publication->journal.article), fp))
		{
			printf("ERROR! Writing failed when trying to write journal information!\n");

			return 1;
		}
	}
	else
	{
		if (write_string_to_file(publication->conference.venue, fp))
		{
			printf("ERROR! Writing failed when trying to write conference information!\n");

			return 1;
		}
	}

	return 0;
}

/**Function********************************************************************

  Synopsis           imports a publication from a file. The order of writing should have been as follows:
	Write number of characters in DOI ----| Remember that these are included in a single write_string_to_file() call
	Write DOI ----------------------------|
	Write number of characters in title
	Write title
	Write number of characters in ISBN
	Write isbn
	Write number of characters in source
	Write source
	Write number of characters in authors
	Write authors
	Write the integer year
	Write the float impact 
	Write int which should be 1 if it's a journal, and 0 if it's a conference 
	If conference:
		Write the number of elements in the venue string
		Write the venue
	Else:
		Write the integer volume
		Write the integer article

	IT WILL ALLOCATE MEMORY FOR THESE FIELDS AS NECESSARY. returns a 1 on failure

  Parameters         	FILE *fp:	the file we want to export to. Should already be opened
			publication_t *publication: the publication we are trying to write	

******************************************************************************/
static int import_publication(FILE *fp, publication_t *publication)
{
	if (read_string_from_file(&(publication->doi), fp) ||
		read_string_from_file(&(publication->title), fp) ||
		read_string_from_file(&(publication->isbn), fp) ||
		read_string_from_file(&(publication->source), fp) ||
		read_string_from_file(&(publication->authors), fp) ||
		read_int_from_file(&(publication->year), fp) ||
		read_float_from_file(&(publication->impact), fp) ||
		read_int_from_file(&(publication->is_journal), fp))
	{
		printf("ERROR! Reading failed when trying to read the general publication information!\n");

		return 1;
	}
	else if (publication->is_journal)
	{
		if (read_int_from_file(&(publication->journal.volume), fp) ||
			read_int_from_file(&(publication->journal.article), fp))
		{
			printf("ERROR! Writing failed when trying to read journal information!\n");

			return 1;
		}
	}
	else
	{
		if (read_string_from_file(&(publication->conference.venue), fp))
		{
			printf("ERROR! Writing failed when trying to read conference information!\n");

			return 1;
		}
	}

	//printf("\nDEBUG: feof(fp) = '%d'\n", feof(fp));
	//printf("\nDEBUG: fgetc(fp) = '%d'\n", fgetc(fp));
	//printf("\nDEBUG: last character of doi = '%x'", (publication->doi)[strlen(publication->doi)]);
	return 0;
}

