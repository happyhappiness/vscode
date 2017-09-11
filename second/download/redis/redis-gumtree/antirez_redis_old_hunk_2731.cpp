        return;
    }
    if ((aeWait(fd,AE_WRITABLE,timeout*1000) & AE_WRITABLE) == 0) {
        addReplyError(c,"Timeout connecting to the client");
        return;
    }

