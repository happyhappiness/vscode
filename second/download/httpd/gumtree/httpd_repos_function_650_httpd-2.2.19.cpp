static void yy_push_state( int new_state )
#else
static void yy_push_state( new_state )
int new_state;
#endif
        {
        if ( yy_start_stack_ptr >= yy_start_stack_depth )
                {
                yy_size_t new_size;

                yy_start_stack_depth += YY_START_STACK_INCR;
                new_size = yy_start_stack_depth * sizeof( int );

                if ( ! yy_start_stack )
                        yy_start_stack = (int *) yy_flex_alloc( new_size );

                else
                        yy_start_stack = (int *) yy_flex_realloc(
                                        (void *) yy_start_stack, new_size );

                if ( ! yy_start_stack )
                        YY_FATAL_ERROR(
                        "out of memory expanding start-condition stack" );
                }

        yy_start_stack[yy_start_stack_ptr++] = YY_START;

        BEGIN(new_state);
        }