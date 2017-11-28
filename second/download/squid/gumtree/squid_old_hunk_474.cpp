    // make sure that the copy out directory is there and accessible
    if ( copydir && *copydir )
        if ( assert_copydir( copydir ) != 0 ) exit(1);

    // show results
    if ( showme ) {
        printf( "#\n# Currently active values for %s:\n# %s\n",
                ::programname, ::RCS_ID );
        printf( "# Debug level       : " );
        if ( ::debugFlag ) printf( "%#6.4x", ::debugFlag );
        else printf( "production level" ); // printf omits 0x prefix for 0!
        printf( " + %s mode", ::no_fork ? "linear" : "parallel" );
        puts( ::verbose ? " + extra verbosity" : "" );

