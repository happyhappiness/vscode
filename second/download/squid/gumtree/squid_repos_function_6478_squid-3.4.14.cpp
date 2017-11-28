bool
Ipc::Mem::PageStack::pop(PageId &page)
{
    Must(!page);

    // we may fail to dequeue, but be conservative to prevent long searches
    --theSize;

    // find a Readable slot, starting with theLastReadable and going left
    while (theSize >= 0) {
        const Offset idx = theLastReadable;
        // mark the slot at ids Writable while extracting its current value
        const Value value = theItems[idx].fetchAndAnd(0); // works if Writable is 0
        const bool popped = value != Writable;
        // theItems[idx] is probably not Readable [any more]

        // Whether we popped a Readable value or not, we should try going left
        // to maintain the index (and make progress).
        // We may fail if others already updated the index, but that is OK.
        theLastReadable.swap_if(idx, prev(idx)); // may fail or lie

        if (popped) {
            // the slot we emptied may already be filled, but that is OK
            theFirstWritable = idx; // may lie
            page.pool = thePoolId;
            page.number = value;
            return true;
        }
        // TODO: report suspiciously long loops
    }

    ++theSize;
    return false;
}