                                                                (yyg->yy_buffer_stack,

                                                                num_to_alloc * sizeof(struct yy_buffer_state*)

                                                                , yyscanner);

                if ( ! yyg->yy_buffer_stack )

                        YY_FATAL_ERROR( "out of dynamic memory in cmDependsFortran_yyensure_buffer_stack()" );



                /* zero only the new slots.*/

                memset(yyg->yy_buffer_stack + yyg->yy_buffer_stack_max, 0, grow_size * sizeof(struct yy_buffer_state*));

