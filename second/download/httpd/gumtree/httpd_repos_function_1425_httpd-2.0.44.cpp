unsigned long util_ald_hash_string(int nstr, ...)
{
    int i;
    va_list args;
    unsigned long h=0, g;
    char *str, *p;
  
    va_start(args, nstr);
    for (i=0; i < nstr; ++i) {
        str = va_arg(args, char *);
        for (p = str; *p; ++p) {
            h = ( h << 4 ) + *p;
            if ( ( g = h & 0xf0000000 ) ) {
	        h = h ^ (g >> 24);
	        h = h ^ g;
            }
        }
    }
    va_end(args);

    return h;
}