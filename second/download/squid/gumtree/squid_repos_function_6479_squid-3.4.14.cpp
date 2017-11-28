void
Ipc::Mem::PageStack::push(PageId &page)
{
    if (!page)
        return;

    Must(pageIdIsValid(page));
    // find a Writable slot, starting with theFirstWritable and going right
    while (theSize < theCapacity) {
        const Offset idx = theFirstWritable;
        const bool pushed = theItems[idx].swap_if(Writable, page.number);
        // theItems[idx] is probably not Writable [any more];

        // Whether we pushed the page number or not, we should try going right
        // to maintain the index (and make progress).
        // We may fail if others already updated the index, but that is OK.
        theFirstWritable.swap_if(idx, next(idx)); // may fail or lie

        if (pushed) {
            // the enqueued value may already by gone, but that is OK
            theLastReadable = idx; // may lie
            ++theSize;
            page = PageId();
            return;
        }
        // TODO: report suspiciously long loops
    }
    Must(false); // the number of pages cannot exceed theCapacity
}