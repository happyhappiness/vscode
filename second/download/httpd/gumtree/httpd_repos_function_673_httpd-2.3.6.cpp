YY_BUFFER_STATE yy_scan_string( yyconst char *yy_str )
#else
YY_BUFFER_STATE yy_scan_string( yy_str )
yyconst char *yy_str;
#endif
        {
        int len;
        for ( len = 0; yy_str[len]; ++len )
                ;

        return yy_scan_bytes( yy_str, len );
        }