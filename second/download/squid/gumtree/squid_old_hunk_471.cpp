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
