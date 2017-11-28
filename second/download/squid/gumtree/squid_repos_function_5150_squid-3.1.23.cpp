void
DiskdIOStrategy::handle(diomsg * M)
{
    if (!cbdataReferenceValid (M->callback_data)) {
        /* I.e. already closed file
         * - say when we have a error opening after
         *   a read was already queued
         */
        debugs(79, 3, "storeDiskdHandle: Invalid callback_data " << M->callback_data);
        cbdataReferenceDone (M->callback_data);
        return;
    }


    /* set errno passed from diskd.  makes debugging more meaningful */
    if (M->status < 0)
        errno = -M->status;

    if (M->newstyle) {
        DiskdFile *theFile = (DiskdFile *)M->callback_data;
        theFile->RefCountDereference();
        theFile->completed (M);
    } else
        switch (M->mtype) {

        case _MQD_OPEN:

        case _MQD_CREATE:

        case _MQD_CLOSE:

        case _MQD_READ:

        case _MQD_WRITE:
            assert (0);
            break;

        case _MQD_UNLINK:
            unlinkDone(M);
            break;

        default:
            assert(0);
            break;
        }

    cbdataReferenceDone (M->callback_data);
}