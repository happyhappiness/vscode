static char *make_perchild_socket(const char *fullsockname, int sd[2])
{
    socketpair(PF_UNIX, SOCK_STREAM, 0, sd);
    return NULL;
}