            dictReleaseIterator(sdi);
        }
        dictReleaseIterator(di);
        if (masters_local != sentinel.masters) dictRelease(masters_local);
    } else {
        addReplyErrorFormat(c,"Unknown sentinel subcommand '%s'",
                               (char*)c->argv[1]->ptr);
