void
NTLM_Disconnect(void *handle)
{
    SMB_Handle_Type con = handle;
    SMB_Discon(con, 0);
}