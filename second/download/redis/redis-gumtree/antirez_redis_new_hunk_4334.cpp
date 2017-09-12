    while(offset < server.vm_pages) {
        off_t this = base+offset;

        printf("THIS: %lld (%c)\n", (long long) this, vmFreePage(this) ? 'F' : 'X');
        /* If we overflow, restart from page zero */
        if (this >= server.vm_pages) {
            this -= server.vm_pages;
