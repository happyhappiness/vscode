int
main()
{
    char *t;
    int n = 0;
    while ((t = tempnam(NULL, NULL))) {
        printf("%s\n", t);
        if (++n == 1000)
            break;
    }
    return 1;
}