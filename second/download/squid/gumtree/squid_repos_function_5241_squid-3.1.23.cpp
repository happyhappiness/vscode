int
AIODiskIOStrategy::callback()
{
    return 0;
    int i;
    int completed = 0;
    int retval, reterr;
    FREE *freefunc;
    void *cbdata;
    int callback_valid;
    void *buf;
    async_queue_entry_t *aqe;
    async_queue_entry_type_t type;

    assert(aq.aq_state == AQ_STATE_SETUP);

    /* Loop through all slots */

    for (i = 0; i < MAX_ASYNCOP; i++) {
        if (aq.aq_queue[i].aq_e_state == AQ_ENTRY_USED) {
            aqe = &aq.aq_queue[i];
            /* Active, get status */
            reterr = aio_error(&aqe->aq_e_aiocb);

            if (reterr < 0) {
                fatal("aio_error returned an error!\n");
            }

            if (reterr != EINPROGRESS) {
                /* Get the return code */
                retval = aio_return(&aqe->aq_e_aiocb);

                /* Get the callback parameters */
                freefunc = aqe->aq_e_free;
                buf = aqe->aq_e_buf;
                type = aqe->aq_e_type;
                callback_valid = cbdataReferenceValidDone(aqe->aq_e_callback_data, &cbdata);
                AIODiskFile * theFile = NULL;
                void *theFileVoid = NULL;
                void *theTmpFile = aqe->theFile;
                bool fileOk = cbdataReferenceValidDone(theTmpFile, &theFileVoid);

                if (fileOk) {
                    theFile = static_cast<AIODiskFile *>(theFileVoid);
                }

                /* Free slot */
                memset(aqe, 0, sizeof(async_queue_entry_t));

                aqe->aq_e_state = AQ_ENTRY_FREE;

                --aq.aq_numpending;

                /* Callback */

                if (callback_valid) {
                    assert (fileOk);

                    if (type == AQ_ENTRY_READ)
                        theFile->ioRequestor->readCompleted((const char *)buf, retval, reterr, static_cast<ReadRequest *>(cbdata));

                    if (type == AQ_ENTRY_WRITE)
                        theFile->ioRequestor->writeCompleted(reterr,retval, static_cast<WriteRequest *>(cbdata));
                }

                if (type == AQ_ENTRY_WRITE && freefunc)
                    freefunc(buf);
            }
        }
    }

    return completed;
}