int
RFCNB_Hangup(struct RFCNB_Con *con_Handle)
{

    if (con_Handle != NULL) {
        RFCNB_Close(con_Handle->fd);	/* Could this fail? */
        free(con_Handle);
    }
    return 0;


}