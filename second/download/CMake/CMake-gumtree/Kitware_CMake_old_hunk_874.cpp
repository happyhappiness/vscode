

/** Setup the input buffer state to scan a string. The next call to cmListFileLexer_yylex() will

 * scan from a @e copy of @a str.

 * @param str a NUL-terminated string to scan

 * @param yyscanner The scanner object.

 * @return the newly allocated buffer state object.

 * @note If you want to scan bytes that may contain NUL values, then use

 *       cmListFileLexer_yy_scan_bytes() instead.

 */

YY_BUFFER_STATE cmListFileLexer_yy_scan_string (yyconst char * yy_str , yyscan_t yyscanner)

{



        return cmListFileLexer_yy_scan_bytes(yy_str,strlen(yy_str) ,yyscanner);

}



/** Setup the input buffer state to scan the given bytes. The next call to cmListFileLexer_yylex() will

 * scan from a @e copy of @a bytes.

 * @param bytes the byte buffer to scan

 * @param len the number of bytes in the buffer pointed to by @a bytes.

 * @param yyscanner The scanner object.

 * @return the newly allocated buffer state object.

 */

YY_BUFFER_STATE cmListFileLexer_yy_scan_bytes  (yyconst char * bytes, int  len , yyscan_t yyscanner)

{

        YY_BUFFER_STATE b;

        char *buf;

        yy_size_t n;

        int i;



        /* Get memory for full buffer, including space for trailing EOB's. */

        n = len + 2;

        buf = (char *) cmListFileLexer_yyalloc(n ,yyscanner );

        if ( ! buf )

                YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yy_scan_bytes()" );



        for ( i = 0; i < len; ++i )

                buf[i] = bytes[i];



        buf[len] = buf[len+1] = YY_END_OF_BUFFER_CHAR;



        b = cmListFileLexer_yy_scan_buffer(buf,n ,yyscanner);

        if ( ! b )

