void
SMB_Get_Error_Msg(int msg, char *msgbuf, int len)
{

    if (msg >= 0) {

        strncpy(msgbuf,
                SMBlib_Error_Messages[msg > SMBlibE_NoSuchMsg ? SMBlibE_NoSuchMsg : msg],
                len - 1);
        msgbuf[len - 1] = 0;	/* Make sure it is a string */
    } else {			/* Add the lower layer message ... */

        char prot_msg[1024];

        msg = -msg;		/* Make it positive */

        strncpy(msgbuf,
                SMBlib_Error_Messages[msg > SMBlibE_NoSuchMsg ? SMBlibE_NoSuchMsg : msg],
                len - 1);

        msgbuf[len - 1] = 0;	/* make sure it is a string */

        if (strlen(msgbuf) < len) {	/* If there is space, put rest in */

            strncat(msgbuf, "\n\t", len - strlen(msgbuf));

            RFCNB_Get_Error(prot_msg, sizeof(prot_msg) - 1);

            strncat(msgbuf, prot_msg, len - strlen(msgbuf));

        }
    }

}