void yyfree (void * ptr )
{
	free( (char *) ptr );	/* see yyrealloc() for (char *) cast */
}