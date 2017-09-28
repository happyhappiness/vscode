        key = dictGetKey(de);

        if (val->type != OBJ_STRING || !sdsEncodedObject(val)) {
            addReplyError(c,"Not an sds encoded string.");
        } else {
            addReplyStatusFormat(c,
                "key_sds_len:%lld, key_sds_avail:%lld, "
                "val_sds_len:%lld, val_sds_avail:%lld",
                (long long) sdslen(key),
                (long long) sdsavail(key),
                (long long) sdslen(val->ptr),
                (long long) sdsavail(val->ptr));
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"populate") &&
               (c->argc == 3 || c->argc == 4)) {
        long keys, j;
        robj *key, *val;
        char buf[128];

        if (getLongFromObjectOrReply(c, c->argv[2], &keys, NULL) != C_OK)
            return;
        dictExpand(c->db->dict,keys);
        for (j = 0; j < keys; j++) {
            snprintf(buf,sizeof(buf),"%s:%lu",
                (c->argc == 3) ? "key" : (char*)c->argv[3]->ptr, j);
            key = createStringObject(buf,strlen(buf));
            if (lookupKeyWrite(c->db,key) != NULL) {
                decrRefCount(key);
                continue;
            }
            snprintf(buf,sizeof(buf),"value:%lu",j);
            val = createStringObject(buf,strlen(buf));
            dbAdd(c->db,key,val);
            signalModifiedKey(c->db,key);
            decrRefCount(key);
        }
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"digest") && c->argc == 2) {
