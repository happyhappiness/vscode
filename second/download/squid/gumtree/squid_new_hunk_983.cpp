        if (head->flags.ignore_reload)
            storeAppendPrintf(entry, " ignore-reload");

        if (head->flags.ignore_no_store)
            storeAppendPrintf(entry, " ignore-no-store");

        if (head->flags.ignore_private)
            storeAppendPrintf(entry, " ignore-private");
#endif

        storeAppendPrintf(entry, "\n");

        head = head->next;
    }
