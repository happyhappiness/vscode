        // TODO: cancel the pending timeout callback and allow re-use of the conn.
        if (fd_table[theList_[i]->fd].timeoutHandler == NULL)
            continue;

        // finally, a match. pop and return it.
        Comm::ConnectionPointer result = theList_[i];
        /* may delete this */
        removeAt(i);
        clearHandlers(result);
        return result;
    }

    return Comm::ConnectionPointer();
}

/* might delete list */
void
IdleConnList::findAndClose(const Comm::ConnectionPointer &conn)
{
    const int index = findIndexOf(conn);
    if (index >= 0) {
        /* might delete this */
        removeAt(index);
        clearHandlers(conn);
        conn->close();
    }
}

void
IdleConnList::Read(const Comm::ConnectionPointer &conn, char *buf, size_t len, comm_err_t flag, int xerrno, void *data)
{
    debugs(48, 3, HERE << len << " bytes from " << conn);

    if (flag == COMM_ERR_CLOSING) {
        debugs(48, 3, HERE << "COMM_ERR_CLOSING from " << conn);
        /* Bail out on COMM_ERR_CLOSING - may happen when shutdown aborts our idle FD */
        return;
    }

    IdleConnList *list = (IdleConnList *) data;
    /* may delete list/data */
    list->findAndClose(conn);
