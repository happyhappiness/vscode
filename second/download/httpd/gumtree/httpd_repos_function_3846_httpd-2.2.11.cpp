static DWORD get_local_timezone(TIME_ZONE_INFORMATION **tzresult)
{
    static TIME_ZONE_INFORMATION tz;
    static DWORD result;
    static int init = 0;

    if (!init) {
        result = GetTimeZoneInformation(&tz);
        init = 1;
    }

    *tzresult = &tz;
    return result;
}