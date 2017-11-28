char *SMB_DOSTimToStr(int DOS_time)

{
    static char SMB_Time_Temp[48];
    int DOS_sec, DOS_min, DOS_hour, DOS_day, DOS_month, DOS_year;

    SMB_Time_Temp[0] = 0;

    DOS_sec   = (DOS_time & 0x001F) * 2;
    DOS_min   = (DOS_time & 0x07E0) >> 5;
    DOS_hour  = ((DOS_time & 0xF800) >> 11);

    DOS_day   = (DOS_time & 0x001F0000) >> 16;
    DOS_month = (DOS_time & 0x01E00000) >> 21;
    DOS_year  = ((DOS_time & 0xFE000000) >> 25) + 80;

    snprintf(SMB_Time_Temp, 48, "%2d/%02d/%2d %2d:%02d:%02d", DOS_day, DOS_month,
             DOS_year, DOS_hour, DOS_min, DOS_sec);

    return(SMB_Time_Temp);

}