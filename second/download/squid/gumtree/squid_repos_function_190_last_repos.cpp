int
main ()
{
    char const *expressions[] = {
        "!(1==1)", "!(1!=1)", "1!=1", "!1==1", "1==1",
        "1 <=1","2<=1", "1 < 1", "1 < 2", "-1 < 1","!-1<1",
        "1>2","2>1","2>=2", "2>3", "1==1&1==1","1==1&1==0",
        "!('a'<='c')",
        "(1==1)|('abc'=='def')",
        "(4!=5)&(4==5)",
        "(1==1)|(2==3)&(3==4)", /* should be true because of precedence */
        "(1 & 4)",
        "(\"abc\" | \"edf\")", "1==1==1",
        "!('')",
        /* End of array */""
    };

    int results[] = {0, 1, 0, 0, 1,
                     1, 0, 0, 1, 1,
                     0, 0, 1, 1, 0,
                     1, 0, 0, 1, 0,
                     1, 0, 0, 0, 0,
                     1, 0
                    };

    int i = 0;

    while (strlen (expressions[i])) {
        int result = ESIExpression::Evaluate (expressions[i]);
#if VERBOSEDEBUG

        printf("Expr '%s' = '%s' (expected %s)\n", expressions[i],
               result ? "true" : "false",
               results[i] ? "true" : "false");
#endif

        if (result != results[i])
            return 1;

        ++i;
    }

    return 0;
}