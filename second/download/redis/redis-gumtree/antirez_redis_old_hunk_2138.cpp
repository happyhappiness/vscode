    if (allsections || defsections || !strcasecmp(section,"memory")) {
        char hmem[64];
        char peak_hmem[64];

        bytesToHuman(hmem,zmalloc_used_memory());
        bytesToHuman(peak_hmem,server.stat_peak_memory);
        if (sections++) info = sdscat(info,"\r\n");
        info = sdscatprintf(info,
