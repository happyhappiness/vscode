                return;
            }
        } else
            writeReplyBody();
    }

    // storing/sending methods like earlier adaptOrFinalizeReply() or
    // above writeReplyBody() may release/abort the store entry.
    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        // TODO: In some cases (e.g., 304), we should keep persistent conn open.
        // Detect end-of-reply (and, hence, pool our idle pconn) earlier (ASAP).
        abortTransaction("store entry aborted while storing reply");
        return;
    } else
        switch (persistentConnStatus()) {
        case INCOMPLETE_MSG: {
            debugs(11, 5, "processReplyBody: INCOMPLETE_MSG from " << serverConnection);
