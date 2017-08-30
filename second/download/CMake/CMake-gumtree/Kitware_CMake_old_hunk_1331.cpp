                yyg->yy_buffer_stack = (struct yy_buffer_state**)cmDependsFortran_yyalloc
                                                                (num_to_alloc * sizeof(struct yy_buffer_state*)
                                                                , yyscanner);
                
                memset(yyg->yy_buffer_stack, 0, num_to_alloc * sizeof(struct yy_buffer_state*));
                                
                yyg->yy_buffer_stack_max = num_to_alloc;
                yyg->yy_buffer_stack_top = 0;
                return;
