int main(int argc, char *argv[])
{
#ifdef SIGPIPE
    signal(SIGPIPE, SIG_IGN);
#endif

    /* Gee whiz this is goofy logic but I wanna drive sendfile right now, 
     * not dork around with the command line!
     */
    if (argc >= 3 && !strcmp(argv[1], "client")) {
        char *host = 0;
        if (argv[3]) {
            host = argv[3];
        }	
        if (!strcmp(argv[2], "blocking")) {
            return client(BLK, host);
        }
        else if (!strcmp(argv[2], "timeout")) {
            return client(TIMEOUT, host);
        }
        else if (!strcmp(argv[2], "nonblocking")) {
            return client(NONBLK, host);
        }
    }
    else if (argc == 2 && !strcmp(argv[1], "server")) {
        return server();
    }

    fprintf(stderr, 
            "Usage: %s client {blocking|nonblocking|timeout}\n"
            "       %s server\n",
            argv[0], argv[0]);
    return -1;
}