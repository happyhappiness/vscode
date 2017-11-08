void accept_mutex_off()
{
    if (usunsetlock(uslock) == -1) {
        perror("usunsetlock");
        exit(-1);
    }
}