void
Ipc::Mem::PageStack::push(PageId &page)
{
    debugs(54, 9, page);

    if (!page)
        return;

    Must(pageIdIsValid(page));
    // find a Writable slot, starting with theFirstWritable and going right
    while (theSize < theCapacity) {
        Offset idx = theFirstWritable;
        auto isWritable = Writable;
        const bool pushed = theItems[idx].compare_exchange_strong(isWritable, page.number);
        // theItems[idx] is probably not Writable [any more];

        // Whether we pushed the page number or not, we should try going right
        // to maintain the index (and make progress).
        // We may fail if others already updated the index, but that is OK.
        theFirstWritable.compare_exchange_weak(idx, next(idx)); // may fail or lie

        if (pushed) {
            // the enqueued value may already by gone, but that is OK
            theLastReadable = idx; // may lie
            ++theSize;
            debugs(54, 9, page << " at " << idx << " size: " << theSize);
            page = PageId();
            return;
        }
        // TODO: report suspiciously long loops
    }
    Must(false); // the number of pages cannot exceed theCapacity
}