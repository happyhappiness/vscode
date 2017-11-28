inline
int
log_output( const char* fn, int code, long size, const char* url )
{
    return printf( "%s %3d %8ld %s\n", fn, code, size, url );
}