#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 512
#define ERR_MESG "skill issue"
#define BTR_SHEL "# You're not using a posix-compliant shell. Fix that."
#define EXP_SHEL "/sh"

void *foo( void * );
_Bool shelll( void * );

void *foo ( bar )
	void *bar;
{	
	void *baz;
	
	char *buffer;
	if ( NULL == ( buffer = calloc ( 1, MAX_SIZE * sizeof ( char ) ) ) )
		fprintf ( stderr, "%s\n", ERR_MESG );

	snprintf ( buffer, 3, "#!" );

	strncat ( buffer, ( char * ) bar, MAX_SIZE - 4 );

	baz = ( void* ) buffer;

	return baz;
}

_Bool is_using_correct_shell ( thethingtocompare )
	void * thethingtocompare;
{
	char * buffer;
	if ( NULL == ( buffer = calloc ( 1, MAX_SIZE * sizeof ( char ) ) ) )
		fprintf ( stderr, "%s\n", ERR_MESG );

	if ( strlen ( buffer ) )
		return false;

	strncpy	( buffer, &thethingtocompare [ strlen ( thethingtocompare ) - 4 ], 3 );

	if ( 0 == strcmp ( buffer, EXP_SHEL ) )
		return true;

	return false;
}

void *get_current_shell ()
{
	FILE *filepointer;
	int filedescriptor;
	
	char *buffer;
	if ( NULL == ( buffer = calloc ( 1, MAX_SIZE * sizeof ( char ) ) ) )
		fprintf ( stderr, "%s\n", ERR_MESG );

	filepointer = popen ( "echo $SHELL", "r" );
	filedescriptor = fileno ( filepointer );

	read ( filedescriptor, buffer, MAX_SIZE - 1 );
	pclose ( filepointer );

	return ( void * ) buffer;
}

void *get_correct_shell ()
{
	FILE *filepointer;
	int filedescriptor;
	
	char *buffer;
	if ( NULL == ( buffer = calloc ( 1, MAX_SIZE * sizeof ( char ) ) ) )
		fprintf ( stderr, "%s\n", ERR_MESG );

	filepointer = popen ( "which sh", "r" );
	filedescriptor = fileno ( filepointer );

	read ( filedescriptor, buffer, MAX_SIZE - 1 );
	pclose ( filepointer );

	buffer = foo ( ( void * ) buffer );

	return ( void * ) buffer;
}


void main ()
{
	void *buffer;
	void *shell;

	shell = get_correct_shell ();

	buffer = get_current_shell ();
	
	if ( true == is_using_correct_shell ( foo ( buffer ) ) )
		printf ( "%s", foo (buffer) );
	else
		printf ( "%s\n# Your shell: %s#\n%s", BTR_SHEL, get_current_shell (), shell );

	printf ( "%s\n%s\n", "# it works on my system", "# ( btw i use arch )" );
}
