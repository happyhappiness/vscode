static void usage(void)
{
    fprintf(stderr, "Usage: htdigest [-c] passwordfile realm username\n");
    fprintf(stderr, "The -c flag creates a new file.\n");
    exit(1);
}