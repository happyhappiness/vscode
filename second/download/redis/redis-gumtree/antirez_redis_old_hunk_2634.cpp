    }
    
    /* Connect */
    fd = anetTcpNonBlockConnect(server.neterr,c->argv[1]->ptr,
                atoi(c->argv[2]->ptr));
    if (fd == -1) {
        addReplyErrorFormat(c,"Can't connect to target node: %s",
            server.neterr);
        return;
    }
    if ((aeWait(fd,AE_WRITABLE,timeout*1000) & AE_WRITABLE) == 0) {
        addReplySds(c,sdsnew("-IOERR error or timeout connecting to the client\r\n"));
        return;
    }

    /* Create RESTORE payload and generate the protocol to call the command. */
    rioInitWithBuffer(&cmd,sdsempty());
