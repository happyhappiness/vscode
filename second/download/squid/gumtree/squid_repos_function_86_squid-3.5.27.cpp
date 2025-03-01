bool
copy_out( size_t filesize, size_t metasize, unsigned debug,
          const char* fn, const char* url, const char* copydir,
          bool copyHdr )
// purpose: copy content from squid disk file into separate file
// paramtr: metasize (IN): size of metadata to skip
//          fn (IN): current filename of squid disk file
//          url (IN): currently looked at URL to generate separate file
//          copydir (IN): base directory where to generate the file
//          copyHdr (IN): copy HTTP header, too, if set to true.
// returns: true, if successful, false otherwise.
{
    static const char* index = "index.html";

    // find hostname part after the scheme (okok, not counting port, etc.)
    const char* ptr = strstr( url, "://" );
    if ( ptr == 0 || strlen(ptr) < 4 ) return false;

    // create filename to store contents into
    // NP: magic extra 5 bytes for the component delimiter and termination octets
    char *filename = new char[ strlen(ptr) + strlen(copydir) + strlen(index) +5 ];
    assert( filename != 0 );
    strcpy( filename, copydir );
    strcat( filename, "/" );
    char* here = filename + strlen(filename);
    strcat( filename, ptr+3 );

    // handle server root (e.g. "http://www.focus.de" )
    if ( strchr( ptr+3, '/' ) == 0 ) strcat( filename, "/" );

    // handle directories (e.g. "http://www.focus.de/A/" )
    if ( filename[strlen(filename)-1] == '/' ) strcat( filename, index );

    // create subdirectory structure
    for ( char* t = strchr(here,'/'); t; t = strchr(t,'/') ) {
        *t = 0;
        if ( mkdir( filename, 0775 ) == -1 && errno != EEXIST ) {
            fprintf( stderr, "mkdir(%s): %s\n", filename, strerror(errno) );
            delete[] filename;
            return false;
        } else if ( debug & 0x02 ) {
            fprintf( stderr, "# creating %s\n", filename );
        }
        *t = '/';
        ++t;
    }

    // create file
    int out = open( filename, O_CREAT | O_RDWR | O_TRUNC, 0664 );
    if ( out == -1 ) {
        fprintf( stderr, "open(%s,RDWR): %s\n", filename, strerror(errno) );
        delete[] filename;
        return false;
    } else if ( debug & 0x02 ) {
        fprintf( stderr, "# creating %s\n", filename );
    }

    // (re)open cache file
    int input = open( fn, O_RDONLY );
    if ( input == -1 ) {
        fprintf( stderr, "open(%s,RDONLY): %s\n", fn, strerror(errno) );
        delete[] filename;
        close(out);
        return false;
    }

    // find double CRLF sequence (actually, look at the FSM below)
    // FIXME: this only looks at the already known buffer read previously,
    // which is globally passed (yuck)! As a limitation, the content data
    // *must* begin within the buffer size (that is: 16k)!
    if ( ! copyHdr ) {
        extern char*  linebuffer; // import from purge.cc
        extern size_t buffersize; // import from purge.cc

        unsigned state = 0;
        char* s = linebuffer + metasize;
        while ( s < linebuffer + buffersize && state < 4 ) {
            // state transition machine
            static unsigned table[4][3] = { {3,2,0}, {0,4,0}, {1,4,0}, {4,2,0} };
            //  old || \r | \n |else|
            // =====++====+====+====+
            //    0 ||  3 |  2 |  0 |
            //    1 ||  0 |  4 |  0 |
            //    2 ||  1 |  4 |  0 |
            //    3 ||  4 |  2 |  0 |
            state = table[ state ][ xlate(*s) ];
            ++s;
        }

        if ( state < 4 )
            // complain bitterly, if the HTTP header was too large ( > 16k ).
            fprintf( stderr, "WARNING: %s will contain partial HTTP header data!\n",
                     filename );

        // adjust to different seek size
        metasize = s - linebuffer;
    }

    // no need to copy zero content files
    if ( filesize - metasize <= 0 ) {
        BAUTZ( filesize-metasize == 0 );
    }

#ifdef USE_REGULAR_COPY
    // position input at start of server answer (contains HTTP headers)
    if ( lseek( input, metasize, SEEK_SET ) == -1 ) {
        fprintf( stderr, "lseek(%s,%lu): %s\n", fn, metasize, strerror(errno) );
        BAUTZ(false);
    }

    // file copy input into output via buffer (regular io)
    char buffer[32768];
    int rsize, wsize;
    while ( (rsize=read(input,buffer,sizeof(buffer))) > 0 ) {
        if ( (wsize=write(out,buffer,rsize)) <= 0 ) break;
    }
    if ( rsize < 0 || wsize < 0 ) perror( "while copying" );
#else // use mmap copy (compare: Stevens APUE 12.9)
    // precondition: filesize-metasize > 0
    // seek end of output file ...
    off_t position = lseek( out, filesize-metasize-1, SEEK_SET );
    if ( position == -1 ) {
        fprintf( stderr, "lseek(%s,%lu): %s\n", filename,
                 (unsigned long)filesize-metasize,
                 strerror(errno) );
        BAUTZ(false);
    } else if ( debug & 0x02 ) {
        fprintf( stderr, "# filesize=%lu, metasize=%lu, filepos=%ld\n",
                 (unsigned long)filesize, (unsigned long)metasize,
                 (long)position );
    }

    // ...and write 1 byte there (create a file that length)
    if ( write( out, "", 1 ) != 1 ) {
        perror( "write to output" );
        BAUTZ(false);
    }

    // create source mmap to copy from (mmap complete file)
    caddr_t src = (caddr_t) mmap( 0, filesize, PROT_READ,
                                  MAP_FILE | MAP_SHARED, input, 0 );
    if ( src == (caddr_t) -1 ) {
        perror( "mmap input" );
        BAUTZ(false);
    }

    // create destination mmap to copy into (mmap data portion)
    caddr_t dst = (caddr_t) mmap( 0, filesize-metasize, PROT_READ | PROT_WRITE,
                                  MAP_FILE | MAP_SHARED, out, 0 );
    if ( dst == (caddr_t) -1 ) {
        perror( "mmap output" );
        munmap( src, filesize );
        BAUTZ(false);
    }

    // copy file (beware of offset into wanted data, skip meta data)
    memcpy( dst, src+metasize, filesize-metasize );

    // clean up
    munmap( dst, filesize-metasize );
    munmap( src, filesize );
#endif // USE_REGULAR_COPY

    BAUTZ(true);
}