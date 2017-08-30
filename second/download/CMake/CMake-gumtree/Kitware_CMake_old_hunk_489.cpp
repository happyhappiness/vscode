}

/** Set the current line number.
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

/** Set the current column.
 * @param line_number
 * @param yyscanner The scanner object.
 */
void cmListFileLexer_yyset_column (int  column_no , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

        /* column is only valid if an input buffer exists. */
        if (! YY_CURRENT_BUFFER )
           yy_fatal_error( "cmListFileLexer_yyset_column called with no buffer" , yyscanner);

    yycolumn = column_no;
}

/** Set the input stream. This does not discard the current
 * input buffer.
 * @param in_str A readable stream.
 * @param yyscanner The scanner object.
 * @see cmListFileLexer_yy_switch_to_buffer
 */
void cmListFileLexer_yyset_in (FILE *  in_str , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
    yyin = in_str ;
}

void cmListFileLexer_yyset_out (FILE *  out_str , yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
    yyout = out_str ;
}

int cmListFileLexer_yyget_debug  (yyscan_t yyscanner)
