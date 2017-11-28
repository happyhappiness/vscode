void
parseCommandline( int argc, char* argv[], REList*& head,
                  char*& conffile, char*& copydir,
                  struct in_addr& serverHost, unsigned short& serverPort )
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
                if ( copydir ) xfree( (void*) copydir );
                copydir = xstrdup(optarg);
                assert(copydir);
            }
            break;
        case 'c':
            if ( optarg && *optarg ) {
                if ( *conffile ) xfree((void*) conffile);
                conffile = xstrdup(optarg);
                assert(conffile);
            }
            break;

        case 'd':
            ::debugFlag = strtoul( optarg, 0, 0 );
            break;

        case 'E':
        case 'e':
            if ( head == 0 ) tail = head = new REList( optarg, option=='E' );
            else {
                tail->next = new REList( optarg, option=='E' );
                tail = tail->next;
            }
            break;

        case 'f':
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
            colon = strchr( optarg, ':' );
            if ( colon == 0 ) {
                // no colon, only look at host

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