/**CFile***********************************************************************
 
 FileName    [hash_table.c]
 
 Synopsis    [Hash table implementation.]
 
 Description [Program contains basic structures used by hash table, and has
 fundamental functions to update, insert, and clear a hash table.]
 
 SeeAlso     [optional]
 
 Author      [Aaron Stromberg, Hannah Smith, Julia Vidal Piñeiro, Nick Taglianetti]
 
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
#include "hash_table.h"
#include "file_ops.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Static function prototypes                                                */

/*---------------------------------------------------------------------------*/

static int hash_function(const char * key);

static int date_cmp(const void *a, const void *b);

static size_t num_of_entries(entry_t **table);

static void table_to_array(publication_t **array, entry_t **table);

/*---------------------------------------------------------------------------*/
/* Definition of functions                                                   */
/*---------------------------------------------------------------------------*/


/* insert_entry()
 *
 * Given the hash table, this function allocates memory for a new entry,
 * makes the key of the entry the doi of the new corresponding publication,
 * and gives the entry an index in the hash table. It also checks to see if the new
 * entry is already in the hash table and returns an error message if it is.
 */
void insert_entry(entry_t **hash_table, publication_t *pubP)
{
    int index;
    
    if (get_entry(hash_table, pubP->doi) != NULL)
    {
        printf("Publication already exists!\n");
    }
    else
    {
        entry_t *entryP = malloc(sizeof(entry_t));
        
        entryP->key = strdup(pubP->doi);
        entryP->publication = pubP;
        
        index = hash_function(pubP->doi);
        
        entryP->next = hash_table[index];
        hash_table[index] = entryP;
    }
}


/*
 * publication_t *get_entry()
 *
 * Given the hash table and the unique identifier, searches the
 * hash table for a publication matching the doi provided
 * and returns a pointer to corresponding publication if found.
 * If the publication is not found, an error message is printed.
 */
publication_t *get_entry(entry_t **hash_table, const char *doi)
{
    int index = hash_function(doi);
    entry_t *current =hash_table[index];
    while(current != NULL && strcmp(doi, current->key) != 0)
    {
        current = current->next;
    }
    
    if (current == NULL || strcmp(doi, current->key) != 0) {
        //printf("DOI does not exist!\n");
        return NULL;
    }
    else
    {
        return current->publication;
    }
}


/*
 * free_table()
 *
 * Given the hash table, this function walks through the
 * array of pointers to entries and frees the entries one by one.
 * When it reaches the end of the array of pointers, the
 * function frees the hash table itself.
 */
void free_table(entry_t **hash_table)
{
    int i;
    entry_t *current, *temp;
    
    if (hash_table == NULL) return;
    
    for (i=0; i<TABLE_SIZE;i++)
    {
        current =hash_table[i];
        
        while (current!=NULL)
        {
            temp = current;
            current = current->next;
            free(temp->publication);
            free(temp);
        }
    }
    
    //free(hash_table);
}


/*
 * sort_table()
 *
 * Given the hash table, this function uses the num_elements()
 * function then makes an array of pointers to publications
 * of size NUM_PUBS. qsort() is then used to sort the publications
 * by year with date_cmp() below. The sorted array is then displayed.
 */
void sort_table(entry_t **hash_table, int start_date)
{
    size_t NUM_PUBS = num_of_entries(hash_table);
    publication_t * sorted[NUM_PUBS];
    int k;
    
    table_to_array(sorted, hash_table);
    
    qsort(sorted, NUM_PUBS, sizeof(publication_t *), date_cmp);
    
    for (k=0; k < NUM_PUBS; k++)
    {
        if (sorted[k]->year >= start_date)
        {
            display_pub_summary(sorted[k]);
        }
    }
    
}




/*---------------------------------------------------------------------------*/
/* Definition of static functions                                            */
/*---------------------------------------------------------------------------*/

/*
 * hash_function()
 *
 * Given a unique identifier key, this function
 * assigns an entry an index in the hash table by modifing
 * that key and returning an integer index.
 *
 */
static int hash_function(const char * key)
{
    unsigned int hash = 0;
    int i;
    for (i = 0; i < strlen(key); i++)
    {
        hash = 31*hash + key[i];
    }
    
    return hash % TABLE_SIZE;
}

/*
 * date_cmp()
 *
 * This fuction is used in sort_table() to compare two publication
 * years within qsort(). It does this by returning -1
 * if one variable (ie. year) is greater than another,
 * 0 if the years are equal, and 1 otherwise.
 */
static int date_cmp(const void *a, const void *b)
{
    publication_t *one = *(publication_t **)a;
    publication_t *two = *(publication_t **)b;
    
    if (one->year > two->year) return -1;
    if (one->year == two->year) return 0;
    
    return 1;
}


/*
 * num_of_entries()
 *
 * Given the hash table, this function walks through the
 * array of pointers to entries and increases the counter
 * num_pubs for each publication found. When it reaches
 * the end of the array, the total num_pubs is returned.
 */
static size_t num_of_entries(entry_t **table)
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


//converts entries to publications and sticks em in an array
static void table_to_array(publication_t **array, entry_t **table)
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




