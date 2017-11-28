static void
sig_handle(int)
{
    fflush(stdout);
    close(2);
    close(1);
    close(0);
    exit(0);
}