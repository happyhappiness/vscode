void cmDependsFortran_yyset_lineno (int  line_number , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

        /* lineno is only valid if an input buffer exists. */
        if (! YY_CURRENT_BUFFER )
           yy_fatal_error( "cmDependsFortran_yyset_lineno called with no buffer" ); 
    
    yylineno = line_number;
}