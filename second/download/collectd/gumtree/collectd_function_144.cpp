int yyerror (const char *s)
{
	char *text;

	if (*yytext == '\n')
		text = "<newline>";
	else
		text = yytext;

	fprintf (stderr, "Parse error in file `%s', line %i near `%s': %s\n",
		c_file, yylineno, text, s);
	return (-1);
}