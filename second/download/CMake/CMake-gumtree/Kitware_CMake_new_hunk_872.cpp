                yyg->yy_buffer_stack = (struct yy_buffer_state**)cmListFileLexer_yyalloc
                                                                (num_to_alloc * sizeof(struct yy_buffer_state*)
                                                                , yyscanner);
                if ( ! yyg->yy_buffer_stack )
                        YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yyensure_buffer_stack()" );

                memset(yyg->yy_buffer_stack, 0, num_to_alloc * sizeof(struct yy_buffer_state*));

