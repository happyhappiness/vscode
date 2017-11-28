void
IdleConnList::findAndClose(const Comm::ConnectionPointer &conn)
{
    const int index = findIndexOf(conn);
    if (index >= 0) {
        if (parent_)
            parent_->notifyManager("idle conn closure");
        clearHandlers(conn);
        /* might delete this */
        removeAt(index);
        conn->close();
    }
}