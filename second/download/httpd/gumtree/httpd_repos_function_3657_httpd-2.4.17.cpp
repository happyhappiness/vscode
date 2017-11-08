void ap_expr_yyfree (void * ptr , yyscan_t yyscanner)
{
	free( (char *) ptr );	/* see ap_expr_yyrealloc() for (char *) cast */
}