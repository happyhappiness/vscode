    static const size_t addon = sizeof(unsigned char) + sizeof(unsigned int);
    bool flag = true;

    if ( debugFlag & 0x01 ) fprintf( stderr, "# [3] %s\n", fn );
    int fd = open( fn, O_RDONLY );
    if ( fd != -1 ) {
        memset(::linebuffer, 0, ::buffersize);
        size_t readLen = read(fd,::linebuffer,::buffersize-1);
        if ( readLen > 60 ) {
            ::linebuffer[ ::buffersize-1 ] = '\0'; // force-terminate string

            // check the offset into the start of object data. The offset is
            // stored in a host endianess after the first byte.
            unsigned int datastart;
            memcpy( &datastart, ::linebuffer + 1, sizeof(unsigned int) );
