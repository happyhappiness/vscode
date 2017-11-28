void
parseCommandline( int argc, char* argv[], REList*& head,
                  char*& conffile, char*& copyDirPath,
                  struct in_addr& serverHostIp, unsigned short& serverHostPort )
// paramtr: argc: see ::main().
//          argv: see ::main().
// returns: Does terminate the program on errors!
// purpose: suck in any commandline options, and set the global vars.
{
    int option, port, showme = 0;
    char* ptr, *colon;
    FILE* rfile;

    // program basename
    if ( (ptr = strrchr(argv[0],'/')) == NULL )
        ptr=argv[0];
    else
        ++ptr;
    ::programname = ptr;

    // extract commandline parameters
    REList* tail = head = 0;
    opterr = 0;
    while ( (option = getopt( argc, argv, "ac:C:d:E:e:F:f:Hnp:P:sv" )) != -1 ) {
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
            }
            if ( *conffile ) xfree((void*) conffile);
            conffile = xstrdup(optarg);
            assert(conffile);
            break;

        case 'd':
            if ( !optarg || !*optarg ) {
                fprintf( stderr, "%c expects a mask parameter. Debug disabled.\n", option );
                ::debugFlag = 0;
            } else
                ::debugFlag = (strtoul(optarg, NULL, 0) & 0xFFFFFFFF);
            break;

        case 'E':
        case 'e':
            if ( !optarg || !*optarg ) {
                fprintf( stderr, "%c requires a regex pattern argument!\n", option );
                exit(1);
            }
            if ( head == 0 )
                tail = head = new REList( optarg, option=='E' );
            else {
                tail->next = new REList( optarg, option=='E' );
                tail = tail->next;
            }
            break;

        case 'f':
            if ( !optarg || !*optarg ) {
                fprintf( stderr, "%c requires a filename argument!\n", option );
                exit(1);
            }
            if ( (rfile = fopen( optarg, "r" )) != NULL ) {
                unsigned long lineno = 0;
#define LINESIZE 512
                char line[LINESIZE];
                while ( fgets( line, LINESIZE, rfile ) != NULL ) {
                    ++lineno;
                    int len = strlen(line)-1;
                    if ( len+2 >= LINESIZE ) {
                        fprintf( stderr, "%s:%lu: line too long, sorry.\n",
                                 optarg, lineno );
                        exit(1);
                    }

                    // remove trailing line breaks
                    while ( len > 0 && ( line[len] == '\n' || line[len] == '\r' ) ) {
                        line[len] = '\0';
                        --len;
                    }

                    // insert into list of expressions
                    if ( head == 0 ) tail = head = new REList(line,option=='F');
                    else {
                        tail->next = new REList(line,option=='F');
                        tail = tail->next;
                    }
                }
                fclose(rfile);
            } else
                fprintf( stderr, "unable to open %s: %s\n", optarg, strerror(errno));
            break;

        case 'H':
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
                port = checkForPortOnly( optarg );
                if ( port == -1 ) {
                    // assume that main() did set the default port
                    if ( convertHostname(optarg,serverHostIp) == -1 ) {
                        fprintf( stderr, "unable to resolve host %s!\n", optarg );
                        exit(1);
                    }
                } else {
                    // assume that main() did set the default host
                    serverHostPort = port;
                }
            } else {
                // colon used, port is extra
                *colon = 0;
                ++colon;
                if ( convertHostname(optarg,serverHostIp) == -1 ) {
                    fprintf( stderr, "unable to resolve host %s!\n", optarg );
                    exit(1);
                }
                if ( convertPortname(colon,serverHostPort) == -1 ) {
                    fprintf( stderr, "unable to resolve port %s!\n", colon );
                    exit(1);
                }
            }
            break;
        case 'P':
            if ( !optarg || !*optarg ) {
                fprintf( stderr, "%c requires a mode argument!\n", option );
                exit(1);
            }
            ::purgeMode = ( strtol( optarg, 0, 0 ) & 0x07 );
            break;
        case 's':
            showme=1;
            break;
        case 'v':
            ::verbose = ! ::verbose;
            break;
        case '?':
        default:
            helpMe();
            exit(1);
        }
    }

    // adjust
    if ( ! isatty(fileno(stdout)) || (::debugFlag & 0x01) ) ::iamalive = false;
    if ( head == 0 ) {
        fputs( "There was no regular expression defined. If you intend\n", stderr );
        fputs( "to match all possible URLs, use \"-e .\" instead.\n", stderr );
        exit(1);
    }

    // postcondition: head != 0
    assert( head != 0 );

    // make sure that the copy out directory is there and accessible
    if ( copyDirPath && *copyDirPath )
        if ( assert_copydir( copyDirPath ) != 0 ) exit(1);

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
                copyDirPath ? copyDirPath : "copy-out mode disabled" );
        if ( copyDirPath )
            printf( "(%s HTTP header)\n", ::envelope ? "prepend" : "no" );
        else
            puts("");

        printf( "# Squid config file : %s\n", conffile );
        printf( "# Cacheserveraddress: %s:%u\n",
                inet_ntoa( serverHostIp ), ntohs( serverHostPort ) );
        printf( "# purge mode        : 0x%02x\n", ::purgeMode );
        printf( "# Regular expression: " );

        unsigned count(0);
        for ( tail = head; tail != NULL; tail = tail->next ) {
            if ( count++ )
                printf( "#%22u", count );
#if defined(LINUX) && putc==_IO_putc
            // I HATE BROKEN LINUX HEADERS!
            // purge.o(.text+0x1040): undefined reference to `_IO_putc'
            // If your compilation breaks here, remove the undefinition
#undef putc
#endif
            else putchar('1');
            printf( " \"%s\"\n", tail->data );
        }
        puts( "#" );
    }
    fflush( stdout );
}