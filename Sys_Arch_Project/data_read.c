/**CFile***********************************************************************
 
 FileName    data_read.c
 
 Synopsis    contains all functionality for ex/importing to/from a file

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
#include "data_read.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*---------------------------------------------------------------------------*/
/* Definition of functions                                                   */
/*---------------------------------------------------------------------------*/
/**Function********************************************************************

  Synopsis           get's an integer input from the user. Returns -1 on error

  Parameters         	int *theint: the integer that will store the input

******************************************************************************/
int get_int(unsigned int *theint)
{
    int data_read;
    size_t size_int = 10;    
    int returni=0;
    char *string;
 
    string = (char *)malloc(size_int);   
    data_read = getline(&string, &size_int, stdin);
    
    char* string2=NULL;
    
    if(data_read>0)
    {
        (*theint)=strtol(string,&string2,10);   
    }
   
    if(string==string2)   
    {
        returni= -1;   
    }
   
    free(string);
    
    return returni;
}

/**Function********************************************************************

  Synopsis      Both functions below use getline to read input from user and
                remove the return character from the end of the input string.
                get_doi() is used to read the doi from the user and read_text()
                is used for general input-reading purposes.
               
******************************************************************************/
const char * get_doi()
{
    size_t nbytes = 0;
    char *doi = NULL;
    
    puts("Enter DOI of publication:");
    getline(&doi, &nbytes, stdin);
    doi[strlen(doi)-1] = '\0';
    
    return doi;
}

char * read_text()
{
    size_t nbytes = 0;
    char *data = NULL;
    
    getline(&data, &nbytes, stdin);
    data[strlen(data)-1] = '\0';

    return data;
}
