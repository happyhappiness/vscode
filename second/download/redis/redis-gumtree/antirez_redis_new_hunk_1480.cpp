        switch (zr->type) {
        case ZR_LONG:
            addReplyBulkLongLong(c, zr->val.v);
            break;
        case ZR_STRING:
            addReplyBulkCBuffer(c, zr->val.s, sdslen(zr->val.s));
            break;
        }

        if (withdist)
            addReplyDoubleMeters(c, gp[i].dist);

        if (withhash)
            addReplyLongLong(c, zr->score);
