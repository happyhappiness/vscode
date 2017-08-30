#define YY_EXIT_FAILURE 2

#endif



static void yy_fatal_error (yyconst char* msg , yyscan_t)

{

        (void) fprintf( stderr, "%s\n", msg );

        exit( YY_EXIT_FAILURE );

