int SMB_Get_Max_Buf_Siz(SMB_Handle_Type Con_Handle)

{
    if (Con_Handle != NULL) {
        return(Con_Handle -> max_xmit);
    } else {
        return(SMBlibE_BAD);
    }

}