            return;
        dictExpand(c->db->dict,keys);
        for (j = 0; j < keys; j++) {
            long valsize = 0;
            snprintf(buf,sizeof(buf),"%s:%lu",
                (c->argc == 3) ? "key" : (char*)c->argv[3]->ptr, j);
            key = createStringObject(buf,strlen(buf));
            if (c->argc == 5)
                if (getLongFromObjectOrReply(c, c->argv[4], &valsize, NULL) != C_OK)
                    return;
            if (lookupKeyWrite(c->db,key) != NULL) {
                decrRefCount(key);
                continue;
            }
            snprintf(buf,sizeof(buf),"value:%lu",j);
            if (valsize==0)
                val = createStringObject(buf,strlen(buf));
            else {
                val = createStringObject(NULL,valsize);
                memset(val->ptr, 0, valsize);
            }
            dbAdd(c->db,key,val);
            signalModifiedKey(c->db,key);
            decrRefCount(key);
