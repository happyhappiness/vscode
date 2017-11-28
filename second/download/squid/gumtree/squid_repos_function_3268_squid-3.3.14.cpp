int
IdleConnList::findIndexOf(const Comm::ConnectionPointer &conn) const
{
    for (int index = size_ - 1; index >= 0; --index) {
        if (conn->fd == theList_[index]->fd) {
            debugs(48, 3, HERE << "found " << conn << " at index " << index);
            return index;
        }
    }

    debugs(48, 2, HERE << conn << " NOT FOUND!");
    return -1;
}