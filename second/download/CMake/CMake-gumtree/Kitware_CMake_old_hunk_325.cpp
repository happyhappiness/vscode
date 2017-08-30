void cmExpr_yypop_buffer_state (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
  if (!YY_CURRENT_BUFFER)
    return;

  cmExpr_yy_delete_buffer(YY_CURRENT_BUFFER ,yyscanner);
  YY_CURRENT_BUFFER_LVALUE = NULL;
  if (yyg->yy_buffer_stack_top > 0)
    --yyg->yy_buffer_stack_top;

  if (YY_CURRENT_BUFFER) {
    cmExpr_yy_load_buffer_state(yyscanner );
    yyg->yy_did_buffer_switch_on_eof = 1;
  }
}

/* Allocates the stack if it does not exist.
 *  Guarantees space for at least one push.
 */
static void cmExpr_yyensure_buffer_stack (yyscan_t yyscanner)
{
  int nuto_alloc;
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

  if (!yyg->yy_buffer_stack) {

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

  if (yyg->yy_buffer_stack_top >= (yyg->yy_buffer_stack_max) - 1){

    /* Increase the buffer to prepare for a possible push. */
    int grow_size = 8 /* arbitrary grow size */;

    nuto_alloc = yyg->yy_buffer_stack_max + grow_size;
    yyg->yy_buffer_stack = (struct yy_buffer_state**)cmExpr_yyrealloc
                (yyg->yy_buffer_stack,
                nuto_alloc * sizeof(struct yy_buffer_state*)
                , yyscanner);

    /* zero only the new slots.*/
    memset(yyg->yy_buffer_stack + yyg->yy_buffer_stack_max, 0, grow_size * sizeof(struct yy_buffer_state*));
    yyg->yy_buffer_stack_max = nuto_alloc;
  }
}

/** Setup the input buffer state to scan directly from a user-specified character buffer.
