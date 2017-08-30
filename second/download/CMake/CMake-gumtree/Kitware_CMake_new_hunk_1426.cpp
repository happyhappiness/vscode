

static void yy_fatal_error (yyconst char* msg , yyscan_t)

{

        (void) fprintf( stderr, "%s\n", msg );

        exit( YY_EXIT_FAILURE );

}



/* Redefine yyless() so it works in section 3 code. */



#undef yyless

#define yyless(n) \

        do \

                { \

                /* Undo effects of setting up yytext. */ \

        int yyless_macro_arg = (n); \

        YY_LESS_LINENO(yyless_macro_arg);\

                yytext[yyleng] = yyg->yy_hold_char; \

                yyg->yy_c_buf_p = yytext + yyless_macro_arg; \

                yyg->yy_hold_char = *yyg->yy_c_buf_p; \

                *yyg->yy_c_buf_p = '\0'; \

                yyleng = yyless_macro_arg; \

                } \

        while ( 0 )



/* Accessor  methods (get/set functions) to struct members. */



