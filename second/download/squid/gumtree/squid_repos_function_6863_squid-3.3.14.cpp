int SMB_Get_Protocol(SMB_Handle_Type Con_Handle)

{
    if (Con_Handle != NULL) {
        return(Con_Handle -> protocol);
    } else {
        return(0xFFFF);  /* Invalid protocol */
    }

}