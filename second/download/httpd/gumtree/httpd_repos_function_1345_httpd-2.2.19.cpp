static apr_status_t close_unix_socket(void *thefd)
{
    int fd = (int)((long)thefd);

    return close(fd);
}