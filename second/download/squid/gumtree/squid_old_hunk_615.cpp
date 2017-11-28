//          ::serverHost (IN): cache host address
//          ::serverPort (IN): cache port number
{
    static const char* schablone = "PURGE %s HTTP/1.0\r\nAccept: */*\r\n\r\n";
    struct stat st;
    long size = ( fstat(fd,&st) == -1 ? -1 : long(st.st_size - metasize) );
    int status = 0;

    // if we want to copy out the file, do that first of all.
    if ( ::copydir && *copydir && size > 0 )
        copy_out( st.st_size, metasize, ::debugFlag,
                  fn, url, ::copydir, ::envelope );

    // do we need to PURGE the file, yes, if purgemode bit#0 was set.
    if ( ::purgeMode & 0x01 ) {
        unsigned long bufsize = strlen(url) + strlen(schablone) + 4;
        char* buffer = new char[bufsize];

        snprintf( buffer, bufsize, schablone, url );
        int sockfd = connectTo( serverHost, serverPort, true );
        if ( sockfd == -1 ) {
            fprintf( stderr, "unable to connect to server: %s\n", strerror(errno) );
            delete[] buffer;
            return false;
        }

        int size = strlen(buffer);
        if ( write( sockfd, buffer, size ) != size ) {
            // error while talking to squid
            fprintf( stderr, "unable to talk to server: %s\n", strerror(errno) );
            close(sockfd);
            delete[] buffer;
            return false;
        }
        memset( buffer+8, 0, 4 );
        if ( read( sockfd, buffer, bufsize ) < 1 ) {
            // error while reading squid's answer
            fprintf( stderr, "unable to read answer: %s\n", strerror(errno) );
            close(sockfd);
            delete[] buffer;
            return false;
        }
        close(sockfd);
        status = strtol(buffer+8,0,10);
        delete[] buffer;
    }

    // log the output of our operation
    bool flag = true;
    if ( ::verbose ) flag = ( log_extended( fn, status, size, &meta ) >= 0 );
