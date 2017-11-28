void
fatal(const char *message)
{
    fprintf(stderr, "FATAL: %s\n", message);
    exit(1);
}