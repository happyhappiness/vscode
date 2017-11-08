static void yy_pop_state()
        {
        if ( --yy_start_stack_ptr < 0 )
                YY_FATAL_ERROR( "start-condition stack underflow" );

        BEGIN(yy_start_stack[yy_start_stack_ptr]);
        }