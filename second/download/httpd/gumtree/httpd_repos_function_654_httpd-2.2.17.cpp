static int yy_flex_strlen( yyconst char *s )
#else
static int yy_flex_strlen( s )
yyconst char *s;
#endif
        {
        register int n;
        for ( n = 0; s[n]; ++n )
                ;

        return n;
        }