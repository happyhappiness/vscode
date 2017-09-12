            addReply(c,shared.wrongtypeerr);
        } else {
            zs = o->ptr;
            addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",zs->zsl->length));
        }
    }
}
