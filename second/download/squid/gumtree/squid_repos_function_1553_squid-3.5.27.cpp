static bool
doPages(StoreEntry *anEntry)
{
    MemObject *mem = anEntry->mem_obj;

    do {
        // find the page containing the first byte we have not swapped out yet
        mem_node *page =
            mem->data_hdr.getBlockContainingLocation(mem->swapout.queue_offset);

        if (!page)
            break; // wait for more data to become available

        // memNodeWriteComplete() and absence of buffer offset math below
        // imply that we always write from the very beginning of the page
        assert(page->start() == mem->swapout.queue_offset);

        /*
         * Get the length of this buffer. We are assuming(!) that the buffer
         * length won't change on this buffer, or things are going to be very
         * strange. I think that after the copy to a buffer is done, the buffer
         * size should stay fixed regardless so that this code isn't confused,
         * but we can look at this at a later date or whenever the code results
         * in bad swapouts, whichever happens first. :-)
         */
        ssize_t swap_buf_len = page->nodeBuffer.length;

        debugs(20, 3, "storeSwapOut: swap_buf_len = " << swap_buf_len);

        assert(swap_buf_len > 0);

        debugs(20, 3, "storeSwapOut: swapping out " << swap_buf_len << " bytes from " << mem->swapout.queue_offset);

        mem->swapout.queue_offset += swap_buf_len;

        // Quit if write() fails. Sio is going to call our callback, and that
        // will cleanup, but, depending on the fs, that call may be async.
        const bool ok = mem->swapout.sio->write(
                            mem->data_hdr.NodeGet(page),
                            swap_buf_len,
                            -1,
                            memNodeWriteComplete);

        if (!ok || anEntry->swap_status != SWAPOUT_WRITING)
            return false;

        int64_t swapout_size = mem->endOffset() - mem->swapout.queue_offset;

        if (anEntry->store_status == STORE_PENDING)
            if (swapout_size < SM_PAGE_SIZE)
                break;

        if (swapout_size <= 0)
            break;
    } while (true);

    // either wait for more data or call swapOutFileClose()
    return true;
}