int SMB_Discon(SMB_Handle_Type Con_Handle, BOOL KeepHandle)

{

    /* We just disconnect the connection for now ... */

    RFCNB_Hangup(Con_Handle -> Trans_Connect);

    if (!KeepHandle)
        free(Con_Handle);

    return(0);

}