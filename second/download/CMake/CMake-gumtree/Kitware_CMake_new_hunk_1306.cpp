 * @param line_number
 * @param yyscanner The scanner object.
 */
void cmListFileLexer_yyset_lineno (int  line_number , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

        /* lineno is only valid if an input buffer exists. */
        if (! YY_CURRENT_BUFFER )
           yy_fatal_error( "cmListFileLexer_yyset_lineno called with no buffer" , yyscanner); 
    
    yylineno = line_number;
}
