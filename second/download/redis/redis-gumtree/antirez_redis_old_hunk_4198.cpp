        value += incr;
        sds svalue = sdscatprintf(sdsempty(),"%lld",value);
        zm = zipmapSet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr),
            (unsigned char*)svalue,sdslen(svalue),&update);
        sdsfree(svalue);
        o->ptr = zm;

        /* Check if the zipmap needs to be converted
         * if this was not an update. */
        if (!update && zipmapLen(zm) > server.hash_max_zipmap_entries)
            convertToRealHash(o);
    } else {
        robj *hval;
