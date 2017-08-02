
        /* lineno is only valid if an input buffer exists. */
        if (! YY_CURRENT_BUFFER )
           YY_FATAL_ERROR( "cmFortran_yyset_lineno called with no buffer" );

    yylineno = line_number;
}

/** Set the current column.
 * @param line_number
 * @param yyscanner The scanner object.
 */
void cmFortran_yyset_column (int  column_no , yyscan_t yyscanner)
