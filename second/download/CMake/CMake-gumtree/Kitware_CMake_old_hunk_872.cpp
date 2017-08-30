                yyg->yy_buffer_stack = (struct yy_buffer_state**)cmListFileLexer_yyalloc
                                                                (num_to_alloc * sizeof(struct yy_buffer_state*)
                                                                , yyscanner);

                memset(yyg->yy_buffer_stack, 0, num_to_alloc * sizeof(struct yy_buffer_state*));

