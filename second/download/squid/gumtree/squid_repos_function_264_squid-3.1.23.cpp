int
NTLM_Auth(void *handle, char *username, char *password, int flag)
{
    SMB_Handle_Type con = handle;

    if (SMB_Logon_Server(con, username, password, NULL, flag) < 0) {
        return (NTV_LOGON_ERROR);
    }
    return (NTV_NO_ERROR);
}