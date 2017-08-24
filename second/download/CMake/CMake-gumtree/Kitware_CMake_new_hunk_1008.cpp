    YY_BUFFER_STATE cmCommandArgument_yy_create_buffer  (FILE * file, int  size , yyscan_t yyscanner)
{
        YY_BUFFER_STATE b;

        b = (YY_BUFFER_STATE) cmCommandArgument_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
        if ( ! b )
                YY_FATAL_ERROR( "out of dynamic memory in cmCommandArgument_yy_create_buffer()" );
