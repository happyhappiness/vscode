static int
fdIsHttp(int fd)
{
    int j;

    for (j = 0; j < NHttpSockets; j++) {
        if (fd == HttpSockets[j])
            return 1;
    }

    return 0;
}