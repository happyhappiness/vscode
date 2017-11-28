
                // fix: see if somebody just put in there a port (no periods)
                // give port number precedence over host names
                port = checkForPortOnly( optarg );
                if ( port == -1 ) {
                    // assume that main() did set the default port
                    if ( convertHostname(optarg,serverHost) == -1 ) {
                        fprintf( stderr, "unable to resolve host %s!\n", optarg );
                        exit(1);
                    }
                } else {
                    // assume that main() did set the default host
                    serverPort = port;
                }
            } else {
                // colon used, port is extra
                *colon = 0;
                ++colon;
                if ( convertHostname(optarg,serverHost) == -1 ) {
                    fprintf( stderr, "unable to resolve host %s!\n", optarg );
                    exit(1);
                }
                if ( convertPortname(colon,serverPort) == -1 ) {
                    fprintf( stderr, "unable to resolve port %s!\n", colon );
                    exit(1);
                }
            }
            break;
        case 'P':
