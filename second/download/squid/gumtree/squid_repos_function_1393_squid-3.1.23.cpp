static void
doPages(StoreEntry *anEntry)
{
    MemObject *mem = anEntry->mem_obj;

    do {
        /*
         * Evil hack time.
         * We are paging out to disk in page size chunks. however, later on when
         * we update the queue position, we might not have a page (I *think*),
         * so we do the actual page update here.
         */

        if (mem->swapout.memnode == NULL) {
            /* We need to swap out the first page */
            mem->swapout.memnode = const_cast<mem_node *>(mem->data_hdr.start());
        } else {
            /* We need to swap out the next page */
            /* 20030636 RBC - we don't have ->next anymore.
             * But we do have the next location */
            mem->swapout.memnode = mem->data_hdr.getBlockContainingLocation (mem->swapout.memnode->end());
        }

        /*
         * Get the length of this buffer. We are assuming(!) that the buffer
         * length won't change on this buffer, or things are going to be very
         * strange. I think that after the copy to a buffer is done, the buffer
         * size should stay fixed regardless so that this code isn't confused,
         * but we can look at this at a later date or whenever the code results
         * in bad swapouts, whichever happens first. :-)
         */
        ssize_t swap_buf_len = mem->swapout.memnode->nodeBuffer.length;

        debugs(20, 3, "storeSwapOut: swap_buf_len = " << swap_buf_len);

        assert(swap_buf_len > 0);

        debugs(20, 3, "storeSwapOut: swapping out " << swap_buf_len << " bytes from " << mem->swapout.queue_offset);

        mem->swapout.queue_offset += swap_buf_len;

        storeIOWrite(mem->swapout.sio,
                     mem->data_hdr.NodeGet(mem->swapout.memnode),
                     swap_buf_len,
                     -1,
                     memNodeWriteComplete);

        /* the storeWrite() call might generate an error */
        if (anEntry->swap_status != SWAPOUT_WRITING)
            break;

        int64_t swapout_size = mem->endOffset() - mem->swapout.queue_offset;

        if (anEntry->store_status == STORE_PENDING)
            if (swapout_size < SM_PAGE_SIZE)
                break;

        if (swapout_size <= 0)
            return;
    } while (true);
}