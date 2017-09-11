            snprintf(buf,sizeof(buf),"value:%lu",j);
            val = createStringObject(buf,strlen(buf));
            dbAdd(c->db,key,val);
            signalModifiedKey(c->db,key);
            decrRefCount(key);
        }
        addReply(c,shared.ok);
