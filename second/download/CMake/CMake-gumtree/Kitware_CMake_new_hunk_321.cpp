}



/** Set the current line number.

 * @param _line_number line number

 * @param yyscanner The scanner object.

 */

void cmCommandArgument_yyset_lineno (int  _line_number , yyscan_t yyscanner)

{

    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;



        /* lineno is only valid if an input buffer exists. */

        if (! YY_CURRENT_BUFFER )

           YY_FATAL_ERROR( "cmCommandArgument_yyset_lineno called with no buffer" );



    yylineno = _line_number;

}



/** Set the current column.

 * @param _column_no column number

 * @param yyscanner The scanner object.

 */

void cmCommandArgument_yyset_column (int  _column_no , yyscan_t yyscanner)

{

    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;



        /* column is only valid if an input buffer exists. */

        if (! YY_CURRENT_BUFFER )

           YY_FATAL_ERROR( "cmCommandArgument_yyset_column called with no buffer" );



    yycolumn = _column_no;

}



/** Set the input stream. This does not discard the current

 * input buffer.

 * @param _in_str A readable stream.

 * @param yyscanner The scanner object.

 * @see cmCommandArgument_yy_switch_to_buffer

 */

void cmCommandArgument_yyset_in (FILE *  _in_str , yyscan_t yyscanner)

{

    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

    yyin = _in_str ;

}



void cmCommandArgument_yyset_out (FILE *  _out_str , yyscan_t yyscanner)

{

    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

    yyout = _out_str ;

}



int cmCommandArgument_yyget_debug  (yyscan_t yyscanner)

