        releaseInstanceLink(ri->link,NULL);
        ri->link = match->link;
        match->link->refcount++;
        return REDIS_OK;
    }
    dictReleaseIterator(di);
