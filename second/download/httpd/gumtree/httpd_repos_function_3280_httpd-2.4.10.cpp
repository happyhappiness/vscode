static void yy_push_state (int  new_state , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
	if ( yyg->yy_start_stack_ptr >= yyg->yy_start_stack_depth )
		{
		yy_size_t new_size;

		yyg->yy_start_stack_depth += YY_START_STACK_INCR;
		new_size = yyg->yy_start_stack_depth * sizeof( int );

		if ( ! yyg->yy_start_stack )
			yyg->yy_start_stack = (int *) ap_expr_yyalloc(new_size ,yyscanner );

		else
			yyg->yy_start_stack = (int *) ap_expr_yyrealloc((void *) yyg->yy_start_stack,new_size ,yyscanner );

		if ( ! yyg->yy_start_stack )
			YY_FATAL_ERROR( "out of memory expanding start-condition stack" );
		}

	yyg->yy_start_stack[yyg->yy_start_stack_ptr++] = YY_START;

	BEGIN(new_state);
}