static LPTIME_ZONE_INFORMATION GetLocalTimeZone()
{
    static int init = 0;
    static TIME_ZONE_INFORMATION tz;

    if (!init) {
        GetTimeZoneInformation(&tz);
        init = 1;
    }
    return &tz;
}