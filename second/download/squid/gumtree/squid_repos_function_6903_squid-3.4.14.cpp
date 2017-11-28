void
RFCNB_Get_Error(char *buffer, int buf_len)
{

    if (RFCNB_saved_errno <= 0) {
        snprintf(buffer, (buf_len - 1), "%s", RFCNB_Error_Strings[RFCNB_errno]);
    } else {
        snprintf(buffer, (buf_len - 1), "%s\n\terrno:%s", RFCNB_Error_Strings[RFCNB_errno],
                 strerror(RFCNB_saved_errno));
    }
}