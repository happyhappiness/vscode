static
int
makelinebuffered( FILE* fp, const char* fn = 0 )
// purpose: make the given FILE line buffered
// paramtr: fp (IO): file pointer which to put into line buffer mode
//          fn (IN): name of file to print in case of error
// returns: 0 is ok, -1 to indicate an error
// warning: error messages will already be printed
{
    if ( setvbuf( fp, 0, _IOLBF, 0 ) == 0 ) {
        // ok
        return 0;
    } else {
        // error
        fprintf( stderr, "unable to make \"%s\" line buffered: %s\n",
                 fn ? fn : "", strerror(errno) );
        return -1;
    }
}