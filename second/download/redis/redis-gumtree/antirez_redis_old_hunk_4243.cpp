    time_t uptime = time(NULL)-server.stat_starttime;
    int j;
    char hmem[64];
  
    bytesToHuman(hmem,zmalloc_used_memory());
    info = sdscatprintf(sdsempty(),
