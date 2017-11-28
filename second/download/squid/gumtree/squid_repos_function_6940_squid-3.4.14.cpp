int SMB_Get_Protocol_IDX(SMB_Handle_Type Con_Handle)

{
    if (Con_Handle != NULL) {
        return(Con_Handle -> prot_IDX);
    } else {
        return(0xFFFF);  /* Invalid protocol */
    }

}