        char *buf;
        yy_size_t n;
        int i;
    
        /* Get memory for full buffer, including space for trailing EOB's. */
        n = len + 2;
        buf = (char *) cmDependsFortran_yyalloc(n  );
        if ( ! buf )
                YY_FATAL_ERROR( "out of dynamic memory in cmDependsFortran_yy_scan_bytes()" );

