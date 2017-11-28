void
DiskdIOStrategy::init()
{
    int pid;
    void * hIpc;
    int rfd;
    int ikey;
    const char *args[5];
    char skey1[32];
    char skey2[32];
    char skey3[32];
    Ip::Address localhost;

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
    snprintf(skey3, 32, "%d", ikey + 2);
    args[0] = "diskd";
    args[1] = skey1;
    args[2] = skey2;
    args[3] = skey3;
    args[4] = NULL;
    localhost.setLocalhost();
    pid = ipcCreate(IPC_STREAM,
                    Config.Program.diskd,
                    args,
                    "diskd",
                    localhost,
                    &rfd,
                    &wfd,
                    &hIpc);

    if (pid < 0)
        fatalf("execl: %s", Config.Program.diskd);

    if (rfd != wfd)
        comm_close(rfd);

    fd_note(wfd, "squid -> diskd");

    commUnsetFdTimeout(wfd);
    commSetNonBlocking(wfd);
    Comm::QuickPollRequired();
}