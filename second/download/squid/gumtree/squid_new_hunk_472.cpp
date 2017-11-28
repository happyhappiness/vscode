            ::envelope = ! ::envelope;
            break;
        case 'n':
            ::no_fork = ! ::no_fork;
            break;
        case 'p':
            if ( !optarg || !*optarg ) {
                fprintf( stderr, "%c requires a port argument!\n", option );
                exit(1);
            }
            colon = strchr( optarg, ':' );
            if ( colon == 0 ) {
                // no colon, only look at host

                // fix: see if somebody just put in there a port (no periods)
                // give port number precedence over host names
