static void err(char *s)
{
    fprintf(stderr, "%s\n", s);
    if (done)
        printf("Total of %ld requests completed\n" , done);
    exit(1);
}