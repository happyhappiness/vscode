        switch ( option ) {
        case 'a':
            ::iamalive = ! ::iamalive;
            break;
        case 'C':
            if ( optarg && *optarg ) {
                if ( copyDirPath ) xfree( (void*) copyDirPath );
                copyDirPath = xstrdup(optarg);
                assert(copyDirPath);
            }
            break;
        case 'c':
            if ( !optarg || !*optarg ) {
                fprintf( stderr, "%c requires a regex pattern argument!\n", option );
                exit(1);
