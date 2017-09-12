    while(offset < server.vm_pages) {
        off_t this = base+offset;

        /* If we overflow, restart from page zero */
        if (this >= server.vm_pages) {
            this -= server.vm_pages;
