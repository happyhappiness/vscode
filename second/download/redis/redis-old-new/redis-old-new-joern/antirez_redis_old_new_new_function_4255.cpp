static int vmFindContiguousPages(off_t *first, int n) {
    off_t base, offset = 0, since_jump = 0, numfree = 0;

    if (server.vm_near_pages == REDIS_VM_MAX_NEAR_PAGES) {
        server.vm_near_pages = 0;
        server.vm_next_page = 0;
    }
    server.vm_near_pages++; /* Yet another try for pages near to the old ones */
    base = server.vm_next_page;

    while(offset < server.vm_pages) {
        off_t this = base+offset;

        redisLog(REDIS_DEBUG, "THIS: %lld (%c)\n", (long long) this, vmFreePage(this) ? 'F' : 'X');
        /* If we overflow, restart from page zero */
        if (this >= server.vm_pages) {
            this -= server.vm_pages;
            if (this == 0) {
                /* Just overflowed, what we found on tail is no longer
                 * interesting, as it's no longer contiguous. */
                numfree = 0;
            }
        }
        if (vmFreePage(this)) {
            /* This is a free page */
            numfree++;
            /* Already got N free pages? Return to the caller, with success */
            if (numfree == n) {
                *first = this-(n-1);
                server.vm_next_page = this+1;
                return REDIS_OK;
            }
        } else {
            /* The current one is not a free page */
            numfree = 0;
        }

        /* Fast-forward if the current page is not free and we already
         * searched enough near this place. */
        since_jump++;
        if (!numfree && since_jump >= REDIS_VM_MAX_RANDOM_JUMP/4) {
            offset += random() % REDIS_VM_MAX_RANDOM_JUMP;
            since_jump = 0;
            /* Note that even if we rewind after the jump, we are don't need
             * to make sure numfree is set to zero as we only jump *if* it
             * is set to zero. */
        } else {
            /* Otherwise just check the next page */
            offset++;
        }
    }
    return REDIS_ERR;
}