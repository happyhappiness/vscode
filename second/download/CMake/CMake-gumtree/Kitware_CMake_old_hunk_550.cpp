

        /* lineno is only valid if an input buffer exists. */

        if (! YY_CURRENT_BUFFER )

           yy_fatal_error( "cmFortran_yyset_lineno called with no buffer" , yyscanner);



    yylineno = line_number;

}



/** Set the current column.

 * @param column_no The column number to set.

 * @param yyscanner The scanner object.

 */

void cmFortran_yyset_column (int  column_no , yyscan_t yyscanner)

