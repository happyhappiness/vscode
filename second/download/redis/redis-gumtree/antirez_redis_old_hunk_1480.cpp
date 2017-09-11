        switch (zr->type) {
        case ZR_LONG:
            addReplyBulkLongLong(c, zr->val.v);
            if (withgeo && !noproperties)
                gp[i].member = sdscatprintf(sdsempty(), "%llu", zr->val.v);
            break;
        case ZR_STRING:
            addReplyBulkCBuffer(c, zr->val.s, sdslen(zr->val.s));
            if (withgeo && !noproperties)
                gp[i].member = sdsdup(zr->val.s);
            break;
        }

        if (withdist)
            addReplyDoubleNicer(c, gp[i].dist);

        if (withhash)
            addReplyLongLong(c, zr->score);
