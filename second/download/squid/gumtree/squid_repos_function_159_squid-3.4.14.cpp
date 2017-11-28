void
sig_intr(int sig)
{
    fd_close(0);
    nfds++;
    printf("\rWaiting for open connections to finish...\n");
    signal(sig, SIG_DFL);
}