}

void Adaptation::Icap::Xaction::scheduleRead()
{
    Must(haveConnection());
    Must(!reader);
    Must(readBuf.length() < SQUID_TCP_SO_RCVBUF); // will expand later if needed

    typedef CommCbMemFunT<Adaptation::Icap::Xaction, CommIoCbParams> Dialer;
    reader = JobCallback(93, 3, Dialer, this, Adaptation::Icap::Xaction::noteCommRead);
    Comm::Read(connection, reader);
    updateTimeout();
}

// comm module read a portion of the ICAP response for us
void Adaptation::Icap::Xaction::noteCommRead(const CommIoCbParams &io)
{
    Must(reader != NULL);
    reader = NULL;

    Must(io.flag == Comm::OK);

    // TODO: tune this better to expected message sizes
    readBuf.reserveCapacity(SQUID_TCP_SO_RCVBUF);
    // we are not asked to grow beyond the allowed maximum
    Must(readBuf.length() < SQUID_TCP_SO_RCVBUF);
    // now we can ensure that there is space to read new data,
    // even if readBuf.spaceSize() currently returns zero.
    readBuf.rawSpace(1);

    CommIoCbParams rd(this); // will be expanded with ReadNow results
    rd.conn = io.conn;

    switch (Comm::ReadNow(rd, readBuf)) {
    case Comm::INPROGRESS:
        if (readBuf.isEmpty())
            debugs(33, 2, io.conn << ": no data to process, " << xstrerr(rd.xerrno));
        scheduleRead();
        return;

    case Comm::OK:
        al.icap.bytesRead += rd.size;

        updateTimeout();

        debugs(93, 3, "read " << rd.size << " bytes");

        disableRetries(); // because pconn did not fail

        /* Continue to process previously read data */
        break;

    case Comm::ENDFILE: // close detected by 0-byte read
        commEof = true;
        reuseConnection = false;

        // detect a pconn race condition: eof on the first pconn read
        if (!al.icap.bytesRead && retriable()) {
            setOutcome(xoRace);
            mustStop("pconn race");
            return;
        }

        break;

    // case Comm::COMM_ERROR:
    default: // no other flags should ever occur
        debugs(11, 2, io.conn << ": read failure: " << xstrerr(rd.xerrno));
        mustStop("unknown ICAP I/O read error");
        return;
    }

    handleCommRead(io.size);
}

void Adaptation::Icap::Xaction::cancelRead()
