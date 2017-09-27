        /* first try to attach to existing slotmem */
        if (next) {
            for (;;) {
                if (strcmp(next->name, fname) == 0) {
                    /* we already have it */
                    *new = next;
                    return APR_SUCCESS;
                }
                if (!next->next) {
                     break;
                }
                next = next->next;
            }
        }
    }
    else {
        fbased = 0;
        fname = "none";
    }

