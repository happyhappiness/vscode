static UCHAR randbyte_perf()
{
    UCHAR byte = 0;
    CPUUTIL util;
    int c;

    if (hDoscalls == 0) {
        char failed_module[20];
        ULONG rc;

        rc = DosLoadModule(failed_module, sizeof(failed_module), "DOSCALLS",
                           &hDoscalls);

        if (rc == 0) {
            rc = DosQueryProcAddr(hDoscalls, 976, NULL, (PFN *)&DosPerfSysCall);

            if (rc) {
                DosPerfSysCall = NULL;
            }
        }
    }

    if (DosPerfSysCall) {
        if (DosPerfSysCall(CMD_KI_RDCNT, (ULONG)&util, 0, 0) == 0) {
            for (c = 0; c < sizeof(util); c++) {
                byte ^= ((UCHAR *)&util)[c];
            }
        }
        else {
            DosPerfSysCall = NULL;
        }
    }

    return byte;
}