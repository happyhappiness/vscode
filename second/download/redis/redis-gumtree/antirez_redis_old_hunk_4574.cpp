        uptime,
        uptime/(3600*24)
    );
    addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",sdslen(info)));
    addReplySds(c,info);
    addReply(c,shared.crlf);
}
