int
RFCNB_Close(int socket)
{

    close(socket);

    /* If we want to do error recovery, here is where we put it */

    return 0;
}