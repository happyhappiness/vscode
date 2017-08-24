 * @param yyscanner The scanner object.
 * @return the newly allocated buffer state object.
 */
YY_BUFFER_STATE cmDependsFortran_yy_scan_bytes  (yyconst char * bytes, int  len , yyscan_t yyscanner)
{
        YY_BUFFER_STATE b;
        char *buf;
        yy_size_t n;
        int i;

        /* Get memory for full buffer, including space for trailing EOB's. */
        n = len + 2;
        buf = (char *) cmDependsFortran_yyalloc(n ,yyscanner );
        if ( ! buf )
                YY_FATAL_ERROR( "out of dynamic memory in cmDependsFortran_yy_scan_bytes()" );

        for ( i = 0; i < len; ++i )
                buf[i] = bytes[i];

        buf[len] = buf[len+1] = YY_END_OF_BUFFER_CHAR;

        b = cmDependsFortran_yy_scan_buffer(buf,n ,yyscanner);
        if ( ! b )
