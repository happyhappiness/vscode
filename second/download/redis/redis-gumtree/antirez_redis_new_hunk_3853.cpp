            char *strenc;

            strenc = strEncoding(val->encoding);
            addReplyStatusFormat(c,
                "Value at:%p refcount:%d "
                "encoding:%s serializedlength:%lld",
                (void*)val, val->refcount,
                strenc, (long long) rdbSavedObjectLen(val,NULL));
        } else {
            vmpointer *vp = (vmpointer*) val;
            addReplyStatusFormat(c,
                "Value swapped at: page %llu "
                "using %llu pages",
                (unsigned long long) vp->page,
                (unsigned long long) vp->usedpages);
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"swapin") && c->argc == 3) {
        lookupKeyRead(c->db,c->argv[2]);
