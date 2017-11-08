static int check_signal(int signum)
{
    switch (signum) {
    case SIGTERM:
    case SIGINT:
        just_die(signum);
        return 1;
    }
    return 0;
}