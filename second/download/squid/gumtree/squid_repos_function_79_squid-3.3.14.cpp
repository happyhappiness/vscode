bool
match( const char* fn, const REList* list )
// purpose: do something with the given cache content filename
// paramtr: fn (IN): filename of cache file
// returns: true for successful action, false otherwise.
// warning: only return false, if you want the loop to terminate!
{
    static const size_t addon = sizeof(unsigned char) + sizeof(unsigned int);
    bool flag = true;

    if ( debugFlag & 0x01 ) fprintf( stderr, "# [3] %s\n", fn );
    int fd = open( fn, O_RDONLY );
    if ( fd != -1 ) {
        if ( read(fd,::linebuffer,::buffersize-1) > 60 ) {
            ::linebuffer[ ::buffersize-1 ] = '\0'; // force-terminate string

            // check the offset into the start of object data. The offset is
            // stored in a host endianess after the first byte.
            unsigned int datastart;
            memcpy( &datastart, ::linebuffer + 1, sizeof(unsigned int) );
            if ( datastart > ::buffersize - addon - 1 ) {
                // check offset into server reply header (start of cache data).
                fputs( "WARNING: Using a truncated URL string.\n", stderr );
                datastart = ::buffersize - addon - 1;
            }

            // NEW: Parse squid meta data, which is a kind of linked list
            // flattened out into a file byte stream. Somewhere within is
            // the URL as part of the list. First, gobble all meta data.
            unsigned int offset = addon;
            SquidMetaList meta;
            while ( offset + addon <= datastart ) {
                unsigned int size = 0;
                memcpy( &size, linebuffer+offset+sizeof(char), sizeof(unsigned int) );
                meta.append( SquidMetaType(*(linebuffer+offset)),
                             size, linebuffer+offset+addon );
                offset += ( addon + size );
            }

            // Now extract the key URL from the meta data.
            const SquidTLV* urlmeta = meta.search( STORE_META_URL );
            if ( urlmeta ) {
                // found URL in meta data. Try to process the URL
                if ( list == 0 )
                    flag = action( fd, datastart, fn, (char*) urlmeta->data, meta );
                else {
                    REList* head = (REList*) list; // YUCK!
                    while ( head != 0 ) {
                        if ( head->match( (char*) urlmeta->data ) ) break;
                        head = head->next;
                    }
                    if ( head != 0 )
                        flag = action( fd, datastart, fn, (char*) urlmeta->data, meta );
                    else flag = true;
                }
            }

            // "meta" will be deleted when exiting from this block
        } else {
            // weird file, FIXME: stat() it!
            struct stat st;
            long size = ( fstat(fd,&st) == -1 ? -1 : st.st_size );
            if ( ::verbose ) flag = ( log_extended( fn, -1, size, 0 ) >= 0 );
            else flag = ( log_output( fn, -1, size, "strange file" ) >= 0 );

            if ( (::purgeMode & 0x04) ) {
                reminder = true;
                if ( unlink(fn) == -1 )
                    // error while unlinking file, this may happen due to the cache
                    // unlinking a file while it is in the readdir() cache of purge.
                    fprintf( stderr, "WARNING: unable to unlink %s: %s\n",
                             fn, strerror(errno) );
            }
        }
        close(fd);
    } else {
        // error while opening file, this may happen due to the cache
        // unlinking a file while it is still in the readdir() cache of purge.
        fprintf( stderr, "WARNING: open \"%s\": %s\n", fn, strerror(errno) );
    }

    return flag;
}