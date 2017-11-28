void
DiskdFile::completed(diomsg *M)
{
    assert (M->newstyle);

    switch (M->mtype) {

    case _MQD_OPEN:
        openDone(M);
        break;

    case _MQD_CREATE:
        createDone(M);
        break;

    case _MQD_CLOSE:
        closeDone(M);
        break;

    case _MQD_READ:
        readDone(M);
        break;

    case _MQD_WRITE:
        writeDone(M);
        break;

    case _MQD_UNLINK:
        assert (0);
        break;

    default:
        assert(0);
        break;
    }
}