int
main( int argc, char* argv[] )
{
    // setup variables
    REList* list = 0;
    char* conffile = xstrdup( DEFAULT_SQUID_CONF );
    serverPort = htons(DEFAULTPORT);
    if ( convertHostname(DEFAULTHOST,serverHost) == -1 ) {
        fprintf( stderr, "unable to resolve host %s!\n", DEFAULTHOST );
        return 1;
    }

    // setup line buffer
    ::linebuffer = new char[ ::buffersize ];
    assert( ::linebuffer != 0 );

    // parse commandline
    puts( "### Use at your own risk! No guarantees whatsoever. You were warned. ###");
    parseCommandline( argc, argv, list, conffile, ::copydir,
                      serverHost, serverPort );

    // prepare execution
    if ( atexit( exiter ) != 0 ||
            Signal( SIGTERM, handler, true ) == SIG_ERR ||
            Signal( SIGINT, handler, true ) == SIG_ERR ||
            Signal( SIGHUP, handler, true ) == SIG_ERR ) {
        perror( "unable to install signal/exit function" );
        return 1;
    }

    // try to read squid.conf file to determine all cache_dir locations
    CacheDirVector cdv(0);
    if ( readConfigFile( cdv, conffile, debugFlag ? stderr : 0 ) > 0 ) {
        // there are some valid cache_dir entries.
        // unless forking was forbidden by cmdline option,
        // for a process for each cache_dir entry to remove files.

        if ( ::no_fork || cdv.size() == 1 ) {
            // linear mode, one cache_dir after the next
            for ( CacheDirVector::iterator i = cdv.begin(); i != cdv.end(); ++i ) {
                // execute OR complain
                if ( ! dirlevel(i->base,list) )
                    fprintf( stderr, "program terminated due to error: %s",
                             strerror(errno) );
                xfree((void*) i->base);
            }
        } else {
            // parallel mode, all cache_dir in parallel
            pid_t* child = new pid_t[ cdv.size() ];

            // make stdout/stderr line bufferd
            makelinebuffered( stdout, "stdout" );
            makelinebuffered( stderr, "stderr" );

            // make parent process group leader for easier killings
            if ( setpgid(getpid(), getpid()) != 0 ) {
                perror( "unable to set process group leader" );
                return 1;
            }

            // -a is mutually exclusive with fork mode
            if ( ::iamalive ) {
                puts( "# i-am-alive flag incompatible with fork mode, resetting" );
                ::iamalive = false;
            }

            for ( size_t i=0; i < cdv.size(); ++i ) {
                if ( getpid() == getpgrp() ) {
                    // only parent == group leader may fork off new processes
                    if ( (child[i]=fork()) < 0 ) {
                        // fork error, this is bad!
                        perror( "unable to fork" );
                        kill( -getpgrp(), SIGTERM );
                        return 1;
                    } else if ( child[i] == 0 ) {
                        // child mode
                        // execute OR complain
                        if ( ! dirlevel(cdv[i].base,list) )
                            fprintf( stderr, "program terminated due to error: %s\n",
                                     strerror(errno) );
                        xfree((void*) cdv[i].base);
                        return 0;
                    } else {
                        // parent mode
                        if ( ::debugFlag ) printf( "forked child %d\n", (int) child[i] );
                    }
                }
            }

            // collect the garbase
            pid_t temp;
            int status;
            for ( size_t i=0; i < cdv.size(); ++i ) {
                while ( (temp=waitpid( (pid_t)-1, &status, 0 )) == -1 )
                    if ( errno == EINTR ) continue;
                if ( ::debugFlag ) printf( "collected child %d\n", (int) temp );
            }
            delete[] child;
        }
    } else {
        fprintf( stderr, "no cache_dir or error accessing \"%s\"\n", conffile );
    }

    // clean up
    if ( copydir ) xfree( (void*) copydir );
    xfree((void*) conffile);
    delete list;
    return 0;
}