    int j;
    char hmem[64];
  
    bytesToHuman(hmem,server.usedmemory);
    info = sdscatprintf(sdsempty(),
        "redis_version:%s\r\n"
        "arch_bits:%s\r\n"
