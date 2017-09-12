            addReply(c,shared.wrongtypeerr);
        } else {
            zs = o->ptr;
            addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",zs->zsl->length));
        }
    }
}
