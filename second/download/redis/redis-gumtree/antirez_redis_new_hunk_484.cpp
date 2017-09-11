                    return;
                }
                i++;
            } else if (!strcasecmp(arg, "store") && (i+1) < remaining) {
                storekey = c->argv[base_args+i+1];
                storedist = 0;
                i++;
            } else if (!strcasecmp(arg, "storedist") && (i+1) < remaining) {
                storekey = c->argv[base_args+i+1];
                storedist = 1;
                i++;
            } else {
                addReply(c, shared.syntaxerr);
                return;
            }
        }
    }

    /* Trap options not compatible with STORE and STOREDIST. */
    if (storekey && (withdist || withhash || withcoords)) {
        addReplyError(c,
            "STORE option in GEORADIUS is not compatible with "
            "WITHDIST, WITHHASH and WITHCOORDS options");
        return;
    }

    /* COUNT without ordering does not make much sense, force ASC
     * ordering if COUNT was specified but no sorting was requested. */
    if (count != 0 && sort == SORT_NONE) sort = SORT_ASC;
