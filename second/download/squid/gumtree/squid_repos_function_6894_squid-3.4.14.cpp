int
RFCNB_Close(int fd)
{

    close(fd);

    /* If we want to do error recovery, here is where we put it */

    return 0;
}