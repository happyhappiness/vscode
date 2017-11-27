#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 192 "parser.y"

static int yyerror (const char *s)
{
	fprintf (stderr, "Error in line %i near `%s': %s\n", yylineno, yytext, s);
	return (-1);
} /* int yyerror */

static char *unquote (const char *orig)
{
	char *ret = strdup (orig);
