void cmDependsFortran_yyset_column (int  column_no , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

        /* column is only valid if an input buffer exists. */
        if (! YY_CURRENT_BUFFER )
           yy_fatal_error( "cmDependsFortran_yyset_column called with no buffer" ); 
    
    yycolumn = column_no;
}