static UCHAR randbyte_sysinfo()
{
    UCHAR byte = 0;
    UCHAR SysVars[100];
    int b;

    DosQuerySysInfo(1, QSV_FOREGROUND_PROCESS, SysVars, sizeof(SysVars));

    for (b = 0; b < 100; b++) {
        byte ^= SysVars[b];
    }

    return byte;
}