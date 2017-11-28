    }

    // postcondition: head != 0
    assert( head != 0 );

    // make sure that the copy out directory is there and accessible
    if ( copydir && *copydir )
        if ( assert_copydir( copydir ) != 0 ) exit(1);

    // show results
    if ( showme ) {
        printf( "#\n# Currently active values for %s:\n",
                ::programname);
        printf( "# Debug level       : " );
        if ( ::debugFlag ) printf( "%#6.4x", ::debugFlag );
        else printf( "production level" ); // printf omits 0x prefix for 0!
        printf( " + %s mode", ::no_fork ? "linear" : "parallel" );
        puts( ::verbose ? " + extra verbosity" : "" );

        printf( "# Copy-out directory: %s ",
                copydir ? copydir : "copy-out mode disabled" );
        if ( copydir )
            printf( "(%s HTTP header)\n", ::envelope ? "prepend" : "no" );
        else
            puts("");

        printf( "# Squid config file : %s\n", conffile );
        printf( "# Cacheserveraddress: %s:%u\n",
                inet_ntoa( serverHost ), ntohs( serverPort ) );
        printf( "# purge mode        : 0x%02x\n", ::purgeMode );
        printf( "# Regular expression: " );

        unsigned count(0);
        for ( tail = head; tail != NULL; tail = tail->next ) {
            if ( count++ )
