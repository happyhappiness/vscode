            ::envelope = ! ::envelope;
            break;
        case 'n':
            ::no_fork = ! ::no_fork;
            break;
        case 'p':
            colon = strchr( optarg, ':' );
            if ( colon == 0 ) {
                // no colon, only look at host

                // fix: see if somebody just put in there a port (no periods)
                // give port number precedence over host names
