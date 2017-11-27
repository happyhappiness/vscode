int yyerror (const char *s)
{
	fprintf (stderr, "Error in line %i near `%s': %s\n", yylineno, yytext, s);
	return (-1);
}