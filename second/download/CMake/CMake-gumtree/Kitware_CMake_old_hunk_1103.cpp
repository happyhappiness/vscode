                /* Increase the buffer to prepare for a possible push. */
                int grow_size = 8 /* arbitrary grow size */;

                nuto_alloc = yyg->yy_buffer_stack_max + grow_size;
                yyg->yy_buffer_stack = (struct yy_buffer_state**)cmDependsFortran_yyrealloc
                                                                (yyg->yy_buffer_stack,
                                                                nuto_alloc * sizeof(struct yy_buffer_state*)
                                                                , yyscanner);

                /* zero only the new slots.*/
                memset(yyg->yy_buffer_stack + yyg->yy_buffer_stack_max, 0, grow_size * sizeof(struct yy_buffer_state*));
                yyg->yy_buffer_stack_max = nuto_alloc;
        }
}

/** Setup the input buffer state to scan directly from a user-specified character buffer.
 * @param base the character buffer
 * @param size the size in bytes of the character buffer
 * @param yyscanner The scanner object.
 * @return the newly allocated buffer state object.
 */
YY_BUFFER_STATE cmDependsFortran_yy_scan_buffer  (char * base, yy_size_t  size , yyscan_t yyscanner)
{
        YY_BUFFER_STATE b;

        if ( size < 2 ||
             base[size-2] != YY_END_OF_BUFFER_CHAR ||
             base[size-1] != YY_END_OF_BUFFER_CHAR )
                /* They forgot to leave room for the EOB's. */
                return 0;

        b = (YY_BUFFER_STATE) cmDependsFortran_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
        if ( ! b )
                YY_FATAL_ERROR( "out of dynamic memory in cmDependsFortran_yy_scan_buffer()" );

