            dictReleaseIterator(sdi);
        }
        dictReleaseIterator(di);
        if (needs_cleanup) dictRelease(masters_local);
    } else {
        addReplyErrorFormat(c,"Unknown sentinel subcommand '%s'",
                               (char*)c->argv[1]->ptr);
