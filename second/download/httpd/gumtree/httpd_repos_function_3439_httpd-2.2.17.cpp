static int vsnprintf( char *str, size_t n, const char *fmt, va_list ap )
{
       int res;

       if (f == NULL)
               f = fopen("/dev/null","w");
       if (f == NULL)
               return -1;

       setvbuf( f, str, _IOFBF, n );

       res = vfprintf( f, fmt, ap );

       if ( res > 0 && res < n ) {
               res = vsprintf( str, fmt, ap );
       }
       return res;
}