int
SMBlib_Set_Sock_NoDelay(SMB_Handle_Type Con_Handle, BOOL yn)
{
    if (RFCNB_Set_Sock_NoDelay(Con_Handle->Trans_Connect, yn) < 0) {
        fprintf(stderr, "Setting no-delay on TCP socket failed ...\n");
    }
    return (0);
}