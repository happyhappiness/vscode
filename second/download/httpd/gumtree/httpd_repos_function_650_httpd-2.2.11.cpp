static void yy_flex_strncpy( char *s1, yyconst char *s2, int n )
#else
static void yy_flex_strncpy( s1, s2, n )
char *s1;
yyconst char *s2;
int n;
#endif
        {
        register int i;
        for ( i = 0; i < n; ++i )
                s1[i] = s2[i];
        }