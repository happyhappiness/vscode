char *
SMB_AtrToStr(int attribs, BOOL verbose)
{
    static char SMB_Attrib_Temp[128];

    SMB_Attrib_Temp[0] = 0;

    if (attribs & SMB_FA_ROF)
        strcat(SMB_Attrib_Temp, (verbose ? "Read Only " : "R"));

    if (attribs & SMB_FA_HID)
        strcat(SMB_Attrib_Temp, (verbose ? "Hidden " : "H"));

    if (attribs & SMB_FA_SYS)
        strcat(SMB_Attrib_Temp, (verbose ? "System " : "S"));

    if (attribs & SMB_FA_VOL)
        strcat(SMB_Attrib_Temp, (verbose ? "Volume " : "V"));

    if (attribs & SMB_FA_DIR)
        strcat(SMB_Attrib_Temp, (verbose ? "Directory " : "D"));

    if (attribs & SMB_FA_ARC)
        strcat(SMB_Attrib_Temp, (verbose ? "Archive " : "A"));

    return (SMB_Attrib_Temp);

}