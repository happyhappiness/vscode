int ap_expr_yylex_destroy  (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

    /* Pop the buffer stack, destroying each element. */
	while(YY_CURRENT_BUFFER){
		ap_expr_yy_delete_buffer(YY_CURRENT_BUFFER ,yyscanner );
		YY_CURRENT_BUFFER_LVALUE = NULL;
		ap_expr_yypop_buffer_state(yyscanner);
	}

	/* Destroy the stack itself. */
	ap_expr_yyfree(yyg->yy_buffer_stack ,yyscanner);
	yyg->yy_buffer_stack = NULL;

    /* Destroy the start condition stack. */
        ap_expr_yyfree(yyg->yy_start_stack ,yyscanner );
        yyg->yy_start_stack = NULL;

    /* Reset the globals. This is important in a non-reentrant scanner so the next time
     * ap_expr_yylex() is called, initialization will occur. */
    yy_init_globals( yyscanner);

    /* Destroy the main struct (reentrant only). */
    ap_expr_yyfree ( yyscanner , yyscanner );
    yyscanner = NULL;
    return 0;
}