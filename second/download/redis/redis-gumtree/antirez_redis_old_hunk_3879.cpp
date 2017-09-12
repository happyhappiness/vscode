    int j, busykeys = 0;

    if ((c->argc % 2) == 0) {
        addReplySds(c,sdsnew("-ERR wrong number of arguments for MSET\r\n"));
        return;
    }
    /* Handle the NX flag. The MSETNX semantic is to return zero and don't
