{

    /* First allocation is just for 2 elements, since we don't know if this
     * scanner will even need a stack. We use 2 instead of 1 to avoid an
     * immediate realloc on the next call.
         */
    nuto_alloc = 1;
    yyg->yy_buffer_stack = (struct yy_buffer_state**)cmExpr_yyalloc
                (nuto_alloc * sizeof(struct yy_buffer_state*)
                , yyscanner);

    memset(yyg->yy_buffer_stack, 0, nuto_alloc * sizeof(struct yy_buffer_state*));

    yyg->yy_buffer_stack_max = nuto_alloc;
    yyg->yy_buffer_stack_top = 0;
    return;
  }