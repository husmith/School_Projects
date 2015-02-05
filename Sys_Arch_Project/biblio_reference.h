/**CHeaderFile*****************************************************************
 
 FileName    [biblio_reference.h]
 
 Synopsis    [Header file for program that stores Bibliographic Database in a hash table.]
 
 Description [Creates hash table and allows user interaction and manipulation of entries.]
 
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
 OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF CARLOS III
 UNIVERSITY OF MADRID HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 CARLOS III UNIVERSITY OF MADRID SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN
 "AS IS" BASIS, AND CARLOS III UNIVERSITY OF MADRID HAS NO OBLIGATION TO
 PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.]
 
 ******************************************************************************/
#ifndef _BIBLIO_REFERENCE_H
#define _BIBLIO_REFERENCE_H

/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/
//enumeration which sets constant sizes for certain fields within structures below
enum {
    DOI_SIZE = 8,
    TABLE_SIZE = 10,
    ISBN_SIZE = 10,
    SOURCE_SIZE = 10,
    TITLE_SIZE = 30,
    AUTHOR_SIZE = 20
};

/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/
//Structure for entry into hash table
struct _entry;
typedef struct _entry entry_t;


//Structure for conference publication type, including pointer field for venue
typedef struct _conference {
    char *venue;
} conference_t;

//Structure for journal publication type, including volume and article fields
typedef struct _journal {
    int volume;
    int article;
} journal_t;

//Structure for general publication with pointer fields to doi, title, isbn, source, and authors
//as well as fields for year and impact
//Also included here is a union which allows for additional fields for publications
//that are a conference or a journal, linked to corresponding structs above
typedef struct _publication {
    char *doi;
    int is_journal; //1 if Journal
    union {
        conference_t conference;
        journal_t journal;
    };
    char *title;
    char *isbn;
    char *source;
    char *authors;
    int year;
    float impact;
} publication_t;



/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/
void display_menu();
void display_pub(entry_t **hash_table, const char *doi);
void display_pub_summary(publication_t *publication);
void display_pubs(entry_t **hash_table);
publication_t *new_pub();
void modify_pub(entry_t **hash_table, const char *doi);
void delete_pub(entry_t **hash_table, const char *doi);
void publication_cleanup(publication_t *pub);

#endif /*_BIBLIO_REFERENCE_H*/
