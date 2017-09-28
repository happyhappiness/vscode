            server.aof_fsync,aof_fsync_enum);
    config_get_enum_field("syslog-facility",
            server.syslog_facility,syslog_facility_enum);

    /* Everything we can't handle with macros follows. */

    if (stringmatch(pattern,"appendonly",0)) {
        addReplyBulkCString(c,"appendonly");
        addReplyBulkCString(c,server.aof_state == AOF_OFF ? "no" : "yes");
        matches++;
    }
    if (stringmatch(pattern,"dir",0)) {
        char buf[1024];

        if (getcwd(buf,sizeof(buf)) == NULL)
            buf[0] = '\0';

        addReplyBulkCString(c,"dir");
        addReplyBulkCString(c,buf);
        matches++;
    }
    if (stringmatch(pattern,"save",0)) {
        sds buf = sdsempty();
        int j;

        for (j = 0; j < server.saveparamslen; j++) {
            buf = sdscatprintf(buf,"%jd %d",
                    (intmax_t)server.saveparams[j].seconds,
