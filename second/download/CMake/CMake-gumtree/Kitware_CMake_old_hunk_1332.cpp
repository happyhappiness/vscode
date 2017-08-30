                                                                (yyg->yy_buffer_stack,

                                                                num_to_alloc * sizeof(struct yy_buffer_state*)

                                                                , yyscanner);



                /* zero only the new slots.*/

                memset(yyg->yy_buffer_stack + yyg->yy_buffer_stack_max, 0, grow_size * sizeof(struct yy_buffer_state*));

