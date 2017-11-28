inline
unsigned
xlate( char ch )
{
    if ( ch == '\r' ) return 0u;
    else if ( ch == '\n' ) return 1u;
    else return 2u;
}