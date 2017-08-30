

/** Setup the input buffer state to scan a string. The next call to cmListFileLexer_yylex() will

 * scan from a @e copy of @a str.

 * @param yystr a NUL-terminated string to scan

 * @param yyscanner The scanner object.

 * @return the newly allocated buffer state object.

 * @note If you want to scan bytes that may contain NUL values, then use

 *       cmListFileLexer_yy_scan_bytes() instead.

 */

YY_BUFFER_STATE cmListFileLexer_yy_scan_string (yyconst char * yystr , yyscan_t yyscanner)

{



        return cmListFileLexer_yy_scan_bytes(yystr,strlen(yystr) ,yyscanner);

}



/** Setup the input buffer state to scan the given bytes. The next call to cmListFileLexer_yylex() will

 * scan from a @e copy of @a bytes.

 * @param yybytes the byte buffer to scan

 * @param _yybytes_len the number of bytes in the buffer pointed to by @a bytes.

 * @param yyscanner The scanner object.

 * @return the newly allocated buffer state object.

 */

YY_BUFFER_STATE cmListFileLexer_yy_scan_bytes  (yyconst char * yybytes, int  _yybytes_len , yyscan_t yyscanner)

{

        YY_BUFFER_STATE b;

        char *buf;

        yy_size_t n;

        int i;



        /* Get memory for full buffer, including space for trailing EOB's. */

        n = _yybytes_len + 2;

        buf = (char *) cmListFileLexer_yyalloc(n ,yyscanner );

        if ( ! buf )

                YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yy_scan_bytes()" );



        for ( i = 0; i < _yybytes_len; ++i )

                buf[i] = yybytes[i];



        buf[_yybytes_len] = buf[_yybytes_len+1] = YY_END_OF_BUFFER_CHAR;



        b = cmListFileLexer_yy_scan_buffer(buf,n ,yyscanner);

        if ( ! b )

