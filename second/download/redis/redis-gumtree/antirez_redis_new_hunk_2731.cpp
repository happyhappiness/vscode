        return;
    }
    if ((aeWait(fd,AE_WRITABLE,timeout*1000) & AE_WRITABLE) == 0) {
        addReplySds(c,sdsnew("-IOERR error or timeout connecting to the client\r\n"));
        return;
    }

