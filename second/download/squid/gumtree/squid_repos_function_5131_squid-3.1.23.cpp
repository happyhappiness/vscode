int
main(int argc, char *argv[])
{
    int key;
    int rmsgid;
    int smsgid;
    int shmid;
    diomsg rmsg;
    diomsg smsg;
    int rlen;
    char rbuf[512];

    struct sigaction sa;
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    mypid = getpid();
    assert(4 == argc);
    key = atoi(argv[1]);
    rmsgid = msgget(key, 0600);

    if (rmsgid < 0) {
        perror("msgget");
        return 1;
    }

    key = atoi(argv[2]);
    smsgid = msgget(key, 0600);

    if (smsgid < 0) {
        perror("msgget");
        return 1;
    }

    key = atoi(argv[3]);
    shmid = shmget(key, 0, 0600);

    if (shmid < 0) {
        perror("shmget");
        return 1;
    }

    shmbuf = (char *)shmat(shmid, NULL, 0);

    if (shmbuf == (void *) -1) {
        perror("shmat");
        return 1;
    }

    hash = hash_create(fsCmp, 1 << 4, fsHash);
    assert(hash);
    fcntl(0, F_SETFL, SQUID_NONBLOCK);
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = alarm_handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &sa, NULL);

    for (;;) {
        alarm(1);
        memset(&rmsg, '\0', sizeof(rmsg));
        DEBUG(2)
        std::cerr << "msgrcv: " << rmsgid << ", "
                  << &rmsg << ", " << diomsg::msg_snd_rcv_sz
                  << ", " << 0 << ", " << 0 << std::endl;
        rlen = msgrcv(rmsgid, &rmsg, diomsg::msg_snd_rcv_sz, 0, 0);

        if (rlen < 0) {
            if (EINTR == errno) {
                if (read(0, rbuf, 512) <= 0) {
                    if (EWOULDBLOCK == errno)
                        (void) 0;
                    else if (EAGAIN == errno)
                        (void) 0;
                    else
                        break;
                }
            }

            if (EAGAIN == errno) {
                continue;
            }

            perror("msgrcv");
            break;
        }

        alarm(0);
        msg_handle(&rmsg, rlen, &smsg);

        if (msgsnd(smsgid, &smsg, diomsg::msg_snd_rcv_sz, 0) < 0) {
            perror("msgsnd");
            break;
        }
    }

    DEBUG(2)
    fprintf(stderr, "%d diskd exiting\n", (int) mypid);

    if (msgctl(rmsgid, IPC_RMID, 0) < 0)
        perror("msgctl IPC_RMID");

    if (msgctl(smsgid, IPC_RMID, 0) < 0)
        perror("msgctl IPC_RMID");

    if (shmdt(shmbuf) < 0)
        perror("shmdt");

    if (shmctl(shmid, IPC_RMID, 0) < 0)
        perror("shmctl IPC_RMID");

    return 0;
}