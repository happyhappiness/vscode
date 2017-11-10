static int snprintf( char *str, size_t n, const char *fmt, ... )
{
        va_list ap;
        int res;
 
        va_start( ap, fmt );
        res = vsnprintf( str, n, fmt, ap );
        va_end( ap );
        return res;
}