        if (head->flags.reload_into_ims)
            storeAppendPrintf(entry, " reload-into-ims");

        if (head->flags.ignore_reload)
            storeAppendPrintf(entry, " ignore-reload");

        if (head->flags.ignore_no_store)
            storeAppendPrintf(entry, " ignore-no-store");

        if (head->flags.ignore_must_revalidate)
            storeAppendPrintf(entry, " ignore-must-revalidate");

