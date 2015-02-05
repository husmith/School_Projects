#include "biblio_reference.h"
#include "data_read.h"
#include "file_ops.h"
#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>


/**Function********************************************************************

  Main function where the program starts. Executes the option that the
  user chooses.
  
******************************************************************************/
int main()
{
    
    
    unsigned int iSelection;   
    entry_t * hash_table[TABLE_SIZE] = {NULL};

    while (1)
    {       
        display_menu();        

        if(get_int(&iSelection)==-1)           
        {
            printf("ERROR");   
        }

        printf("%d", iSelection);
       
        if ( iSelection == 2 )           
        {
            publication_t *pub = new_pub();
            insert_entry(hash_table, pub);
            //printf("DEBUG: entry has been successfully added!");
        } 
        else if ( iSelection == 3 )
        {
            display_pubs(hash_table);
        }
        else if ( iSelection == 4 )   
        {
            const char *doi = get_doi();
            display_pub(hash_table, doi);
        }
        else if ( iSelection == 5 )
        {
             const char *doi = get_doi();
             modify_pub(hash_table, doi); 
        }
        
        else if ( iSelection == 6 )
        {
            const char *doi = get_doi();
            delete_pub(hash_table, doi);
        }
        else if ( iSelection == 7 )
        {
            export_to_file(hash_table);
        }
        else if ( iSelection == 8 )
        {
            import_from_file(hash_table);
        }
        else if ( iSelection == 9 )
        {
            printf("Enter starting year:\n");
            int start_year = atoi(read_text());
            sort_table(hash_table, start_year);      
        }
        else if ( iSelection == 1)   
            break;
    }
    
    // cleanup memory before exit    
    free_table(hash_table);
    
    return 1;
}

