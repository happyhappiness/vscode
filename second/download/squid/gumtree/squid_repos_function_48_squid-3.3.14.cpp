void
pipe_handler(int sig)
{
    fprintf(stderr, "SIGPIPE received.\n");
}