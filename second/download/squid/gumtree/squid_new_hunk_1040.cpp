
    ikey = (getpid() << 10) + (instanceID << 2);
    ikey &= 0x7fffffff;
    smsgid = msgget((key_t) ikey, 0700 | IPC_CREAT);

    if (smsgid < 0) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, MYNAME << "msgget: " << xstrerr(xerrno));
        fatal("msgget failed");
    }

    rmsgid = msgget((key_t) (ikey + 1), 0700 | IPC_CREAT);

    if (rmsgid < 0) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, MYNAME << "msgget: " << xstrerr(xerrno));
        fatal("msgget failed");
    }

    shm.init(ikey, magic2);
    snprintf(skey1, 32, "%d", ikey);
    snprintf(skey2, 32, "%d", ikey + 1);
