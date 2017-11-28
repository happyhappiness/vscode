    }
}

void Adaptation::Icap::Xaction::fillDoneStatus(MemBuf &buf) const
{
    if (haveConnection() && commEof)
        buf.Printf("Comm(%d)", connection->fd);

    if (stopReason != NULL)
        buf.Printf("Stopped");
}

bool Adaptation::Icap::Xaction::fillVirginHttpHeader(MemBuf &buf) const
{
    return false;
}

