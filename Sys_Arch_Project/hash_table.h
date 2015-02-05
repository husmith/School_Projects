/**CHeaderFile*****************************************************************
 
 FileName    [hash_table.h]
 
 Synopsis    [Header file for hash table implementation]
 
 Description [Creates hash table and allows user interaction and manipulation of entries.]
 
 SeeAlso     [optional]
 
 Author      [Aaron Stromberg, Hannah Smith, Julia, Nick Tangletti]
 
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
#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include "biblio_reference.h"

/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/
struct _entry {
    const char *key;
    publication_t *publication;
    struct _entry *next;
};


/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

void insert_entry(entry_t **hash_table, publication_t *pubP);
publication_t * get_entry(entry_t **hash_table, const char *key);
void delete_entry(entry_t **hash_table, const char *key);
void free_table(entry_t **hash_table);
void sort_table(entry_t **hash_table, int start_date);
#endif /*_HASH_TABLE_H_*/
