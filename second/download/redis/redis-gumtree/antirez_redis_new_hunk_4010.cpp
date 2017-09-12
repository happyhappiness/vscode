                strenc = buf;
            }
            addReplySds(c,sdscatprintf(sdsempty(),
                "+Value at:%p refcount:%d "
                "encoding:%s serializedlength:%lld\r\n",
                (void*)val, val->refcount,
                strenc, (long long) rdbSavedObjectLen(val,NULL)));
        } else {
            vmpointer *vp = (vmpointer*) val;
            addReplySds(c,sdscatprintf(sdsempty(),
                "+Value swapped at: page %llu "
                "using %llu pages\r\n",
                (unsigned long long) vp->page,
                (unsigned long long) vp->usedpages));
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"swapin") && c->argc == 3) {
        lookupKeyRead(c->db,c->argv[2]);
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"swapout") && c->argc == 3) {
        dictEntry *de = dictFind(c->db->dict,c->argv[2]->ptr);
        robj *val;
        vmpointer *vp;

        if (!server.vm_enabled) {
            addReplySds(c,sdsnew("-ERR Virtual Memory is disabled\r\n"));
