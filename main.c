//  ! blue

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


void info(); 
void help();
void greet(char *name); 
void picture();
void file();


int main (int argc, char * argv[])
{
    if( argc == 1 )
    {
        info();
        printf("1 Param passed %s\r\n", argv [ 0 ] ); // first param is name of program e.g. blue 
    }

    if( argc == 2 )
    {
        if (strcmp( argv[ 1 ], "-h") == 0)
        {
            help();
        }
    }

    if(argc == 3)
    {
        if (strcmp(argv [ 1 ], "-n") == 0)
        {
        greet( argv [ 2 ]); 
        }
    }
        if( argc == 3 && strcmp(argv[1], "-p") == 0)
    {
        picture( argv [ 2 ] );
    }
        if(argc == 3 && strcmp(argv[1], "-t") == 0)
        {
            file(argv [ 2 ]); 
        }
}


void info ()
{
    printf("blue util. Type blue -h for more information. \r\n");
}

void help()
{
    printf("Type: blue -n {name} for a proper greeting. \r\nType: blue -p {picture} to display a picture, either jpg, png or gif. Other Types are not supported right now. \r\n");
}

void greet( char *name)
{
    if ( strlen (name) > 16) // Name 16 Zeichen oder länger --> Name zu lang
    {
        fprintf(stderr, "WARNING: The name is too long! Pick a shorter one \r\n", name);
    }
    
    else if( strlen( name ) <= 3 ) // Name 3 Zeichen oder länger --> name ist zu kurz
    {
        fprintf(stderr, "WARNING: The name '%s' is too short! \r\n", name);
    }
    
    else// name 4 oder länger --> name ist ok man wird gegrüßt 
    {
        printf("Well, hello there %s\r\n", name);
    }
    

}


const char *get_filename_ext(const char *filename) 
{
    const char *dot = strrchr(filename, '.'); 
    if (!dot || dot == filename) return ""; 
    return dot + 1; 
}

void picture(const char *filename)
{
    const char *ext = get_filename_ext(filename); 
    
    if(strcmp(ext, "jpg") == 0 || strcmp(ext, "png") == 0 || strcmp(ext, "gif") == 0)
    {
        // wenn dateiformat .png .jpg --> Bild anzeigen
        printf("Displaying picture: %s\n", filename);  
        // construct the command to open the picture viewer
        char command[256];
        snprintf(command, sizeof(command), "gwenview %s 2> /dev/null", filename);

        // use the system function to execute the command
        int result = system(command); 

        //Check the result of the system call
        if( result == -1 )
        {
            fprintf(stderr , "Error opening picture viewer \r\n");
        }
        
    } // dateiformat nicht .png .jpg --> 
    else
    {
        fprintf(stderr, "WARNING: This file format is not supported by 'blue' \r\n");   
    }
}

void file(const char *filename)
{
    const char *ext = get_filename_ext(filename);
    if ( strcmp(ext, "txt") == 0 || strcmp(ext, "py") == 0 || strcmp(ext, "cpp") == 0 )
    {
        printf("Displaying file %s\n", filename);
        char command[256];
        snprintf(command, sizeof(command), "kate %s 2> /dev/null", filename );
        int result = system(command);

        if ( result == -1 )
        {
            fprintf(stderr, "Error opening file viewer \r\n");
        }
    }
    
    else
    {
        fprintf(stderr, "WARNING: This file format is not supported by 'blue' \r\n ");
    }
}

