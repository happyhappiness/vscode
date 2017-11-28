int
RFCNB_Close(int aSocket)
{

    close(aSocket);

    /* If we want to do error recovery, here is where we put it */

    return 0;

}