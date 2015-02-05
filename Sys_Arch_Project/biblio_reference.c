/**CFile***********************************************************************
 
 FileName    [biblio_reference.c]
 
 Synopsis    [Program that stores Bibliography References in hash table.]
 
 Description [Given data about a bibliographic reference the application stores information in an 'ultraefficient' way (in a hash table).]
 
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
#include "biblio_reference.h"
#include "data_read.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*---------------------------------------------------------------------------*/
/* Definition of functions                                                   */
/*---------------------------------------------------------------------------*/

  
 /*
  * display_menu()
  *
  * Display the main menu with its options   
  */

void display_menu()
{
    printf("\n\n\t\t=HASH-BIBMANAGER (Efficient Ed.)=\n");
    printf("\n");
    printf("[1]\t\tExit\n");
    printf("[2]\t\tInsert\n");
    printf("[3]\t\tDisplay All\n");
    printf("[4]\t\tDisplay a Publication\n");
    printf("[5]\t\tModify a Publication\n");
    printf("[6]\t\tDelete a Publication\n");
    printf("[7]\t\tExport to File\n");
    printf("[8]\t\tImport from File\n");
    printf("[9]\t\tDisplay Sorted Publications (by year)\n\n");
    printf("\t\t\tEnter an option: ");
}

/*
 * display_pub()
 *
 Given the unique identifier of a element and a hash table containing the 
 * element this function prints out the element's information.
 * A publication's doi is searched for in the table using the get_entry()
 * function and is printed if found.
*/
 
void display_pub(entry_t **hash_table, const char *doi)
{
    publication_t *current;
    
    current = get_entry(hash_table, doi);
    
    if (current != NULL)
    {
        printf("\tDOI:\t%-s\n", current->doi);
        
        if (current->is_journal == 0)
        {
            printf("\tConference Venue:\t%-s\n", current->conference.venue);
        }
        else
        {
            printf("\tJournal Volume, Article Number:\t%-i, %i\n", current->journal.volume, current->journal.article);
        }
        
        printf("\tTitle:\t%-s\n", current->title);
        printf("\tYear:\t%-d\n", current->year);
        printf("\tISBN:\t%-s\n", current->isbn);
        printf("\tSource:\t%-s\n", current->source);
        printf("\tAuthors:\t%-s\n", current->authors);
        printf("\tImpact:\t%-f\n", current->impact);
        
    }
    else
    {
        printf("Could not find matching Publication to display.\n");
    }
}

/*
 * display_pub_summary()
 *
 * Prints out the DOI, Title, and Year of a publication when passed a pointer to 
 * a publication.
 */
void display_pub_summary(publication_t *publication)
{
    printf("\t\tDOI:\t%s\n", publication->doi);
    printf("\t\tTitle:\t%s\n", publication->title);
    printf("\t\tYear:\t%d\n", publication->year);
    printf("\n");
}

/*
 * display_pubs()
 *
 * Given a hash table of entries the function loops through and prints out the
 * data pointed to in each entry (publications).
 */

void display_pubs(entry_t **hash_table)
{
    int i;
    for ( i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] != NULL) {
            entry_t *current;
            for(current = hash_table[i]; current != NULL; current=current->next){
                display_pub_summary(current->publication);
                
            }
        }
    }
}

/* new_pub()
 *
 * Prompts user for input corresponding to data of a new publication. Allocates 
 * memory to a pointer for the publication, which is then assigned the values 
 * given by the user.
 * Returns a pointer to the new publication data.
 */
publication_t *new_pub()
{
    publication_t new_pub;
    publication_t *pubP = malloc(sizeof(publication_t));
    
    printf("\tDOI:\t");
    new_pub.doi = read_text();
    pubP->doi = strdup(new_pub.doi);
    
    printf("\tChoose Publication Type:\n\t(1) Conference\n\t(2) Journal\n");
    int pub_type = atoi(read_text());
    
    if (pub_type == 1)
    {
        pubP->is_journal = 0;
        printf("\tConference Venue:\t");
        new_pub.conference.venue = read_text();
        pubP->conference.venue = strdup(new_pub.conference.venue);
        
    }
    
    if (pub_type == 2)
    {
        pubP->is_journal = 1;
        printf("\tJournal Volume:\t");
        new_pub.journal.volume = atoi(read_text());
        pubP->journal.volume = new_pub.journal.volume;
        
        printf("\tArticle Number:\t");
        new_pub.journal.article = atoi(read_text());
        pubP->journal.article = new_pub.journal.article;
    }
    
    printf("\tTitle:\t");
    new_pub.title = read_text();
    pubP->title = strdup(new_pub.title);
    
    printf("\tISBN:\t");
    new_pub.isbn=read_text();
    pubP->isbn = strdup(new_pub.isbn);
    
    printf("\tSource:\t");
    new_pub.source = read_text();
    pubP->source = strdup(new_pub.source);
    
    printf("\tAuthors:\t");
    new_pub.authors = read_text();
    pubP->authors = strdup(new_pub.authors);
   
    //TODO handle string inputs 
    printf("\tYear:\t");
    new_pub.year = atoi(read_text());
    if (0 < new_pub.year && new_pub.year < 2015)
    {
        pubP->year = new_pub.year;
    }
    else
    {
        printf("Please enter year between 0 and 2015\n");
        printf("\tYear:\t");
        new_pub.year = atoi(read_text());
        
    }
    
    
    printf("\tImpact:\t");
    new_pub.impact = atof(read_text());
    pubP->impact = new_pub.impact;
    
    return pubP;
}

/*
 * modify_pub()
 *
 * Given a hash table and a publication DOI function allows user to
 * modify field of a publication and frees the previously allocated memory
 * of the old value.
 */
void modify_pub(entry_t **hash_table, const char *doi)
{
    char *new;
    int input;
    publication_t *pub = get_entry(hash_table, doi);
    display_pub_summary(pub);
    
    printf("What would you like to modify?\n");
    printf("\t(1) Title\n\t(2) ISBN\n\t(3) Source\n\t(4) Authors\n\t(5) Year\n\t(6) Impact\n");
    input = atoi(read_text());
    
    switch (input)
    {
        case 1:
            printf("\tNew Title: ");
            new = read_text();
            free(pub->title);
            pub->title = strdup(new);
            
            break;
            
        case 2:
            printf("\tNew ISBN: ");
            new = read_text();
            free(pub->isbn);
            pub->isbn = strdup(new);
            
            break;
            
        case 3:
            printf("\tNew Source: ");
            new = read_text();
            free(pub->source);
            pub->source = strdup(new);
            
            break;
            
        case 4:
            printf("\tNew Author: ");
            new = read_text();
            free(pub->authors);
            pub->authors = strdup(new);
            
            break;
            
        case 5:
            printf("\tNew Year: ");
            new = read_text();
            pub->year = atoi(new);
            
            break;
            
        case 6:
            printf("\tNew Impact: ");
            new = read_text();
            pub->impact= atoi(new);
            
            break;
            
        default:
            break;
    }    
}

/*
 * delete_pub()
 *
 * Given a hash table and a publication DOI function allows user to
 * choose a publication to remove by freeing the allocated memory
 * for each element of the publication's structure and then freeing the structure itself
 */
void delete_pub(entry_t **hash_table, const char *doi)
{
    publication_t *current;
    current = get_entry(hash_table, doi);
    printf("removing publication: %p\n", current);
    
    if (current != NULL)
    {
         
        if (current->is_journal == 0)
        {
            free(current->conference.venue);
        }
        
        free(current->doi);
        
        free(current->title);
        
        free(current->isbn);
        
        free(current->source);
        
        free(current->authors);
        
        free(current);
    }
    else
    {
        printf("Could not find matching Publication to remove.\n");
    }
}



/*
 * publication_cleanup
 *
 * frees all the memory used by publication type 
 */

void publication_cleanup(publication_t *pub)
{
    // free members
    free(pub->doi);
    free(pub->title);
    free(pub->isbn);
    free(pub->source);
    free(pub->authors);
    
    // free the struct
    free(pub);
}


