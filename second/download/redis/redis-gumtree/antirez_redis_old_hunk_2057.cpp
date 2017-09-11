        o = dbUnshareStringValue(c->db,c->argv[1],o);
    }
    /* Perform the low level ADD operation for every element. */
    hdr = o->ptr;
    for (j = 2; j < c->argc; j++) {
        if (hllDenseAdd(hdr->registers, (unsigned char*)c->argv[j]->ptr,
                        sdslen(c->argv[j]->ptr)))
        {
            updated++;
        }
    }
    if (updated) {
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
