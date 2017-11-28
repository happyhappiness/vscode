}

void Adaptation::Icap::Xaction::scheduleRead()
{
    Must(haveConnection());
    Must(!reader);
    Must(readBuf.hasSpace());

    /*
     * See comments in Adaptation::Icap::Xaction.h about why we use commBuf
     * here instead of reading directly into readBuf.buf.
     */
    typedef CommCbMemFunT<Adaptation::Icap::Xaction, CommIoCbParams> Dialer;
    reader = JobCallback(93, 3,
                         Dialer, this, Adaptation::Icap::Xaction::noteCommRead);

    comm_read(connection, commBuf, readBuf.spaceSize(), reader);
    updateTimeout();
}

// comm module read a portion of the ICAP response for us
void Adaptation::Icap::Xaction::noteCommRead(const CommIoCbParams &io)
{
    Must(reader != NULL);
    reader = NULL;

    Must(io.flag == Comm::OK);

    if (!io.size) {
        commEof = true;
        reuseConnection = false;

        // detect a pconn race condition: eof on the first pconn read
        if (!al.icap.bytesRead && retriable()) {
            setOutcome(xoRace);
            mustStop("pconn race");
            return;
        }
    } else {

        al.icap.bytesRead+=io.size;

        updateTimeout();

        debugs(93, 3, HERE << "read " << io.size << " bytes");

        /*
         * See comments in Adaptation::Icap::Xaction.h about why we use commBuf
         * here instead of reading directly into readBuf.buf.
         */

        readBuf.append(commBuf, io.size);
        disableRetries(); // because pconn did not fail
    }

    handleCommRead(io.size);
}

void Adaptation::Icap::Xaction::cancelRead()
