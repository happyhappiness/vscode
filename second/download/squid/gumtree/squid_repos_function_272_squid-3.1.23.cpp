void
RFCNB_Get_Error(char *buffer, int buf_len)
{

    if (RFCNB_saved_errno <= 0) {
        sprintf(buffer, "%s", RFCNB_Error_Strings[RFCNB_errno]);
    } else {
        sprintf(buffer, "%s\n\terrno:%s", RFCNB_Error_Strings[RFCNB_errno],
                strerror(RFCNB_saved_errno));
    }

}