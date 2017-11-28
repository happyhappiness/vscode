void
RFCNB_Get_Error_Msg(int code, char *msg_buf, int len)
{

    strncpy(msg_buf, RFCNB_Error_Strings[abs(code)], len);

}