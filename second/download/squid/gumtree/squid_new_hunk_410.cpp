                      "Type",
                      "Tout",
                      "Nread",
                      "Nwrite",
                      "Remote Address",
                      "Description");
#if _SQUID_WINDOWS_
    storeAppendPrintf(dumpEntry, "---- ---------- ------ ---- -------- -------- --------------------- ------------------------------\n");
#else
    storeAppendPrintf(dumpEntry, "---- ------ ---- -------- -------- --------------------- ------------------------------\n");
#endif

    for (i = 0; i < Squid_MaxFD; ++i) {
