bool
isxstring( const char* s, size_t testlen )
// purpose: test a string for conforming to xdigit
// paramtr: s (IN): string to test
//          testlen (IN): length the string must have
// returns: true, iff strlen(s)==testlen && all_x_chars(s), false otherwise
{
    if ( strlen(s) != testlen ) return false;

    size_t i=0;
    while ( i<testlen && isxdigit(s[i]) )
        ++i;
    return (i==testlen);
}