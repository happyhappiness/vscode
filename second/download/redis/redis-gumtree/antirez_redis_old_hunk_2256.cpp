        }
    }

    do {
        cursor = dictScan(c->db->dict, cursor, scanCallback, keys);
    } while (cursor && listLength(keys) < count);

    /* Filter keys */
    node = listFirst(keys);
    while (node) {
        robj *kobj = listNodeValue(node);
        nextnode = listNextNode(node);

        /* Keep key iff pattern matches and it hasn't expired */
        if ((patnoop ||
             stringmatchlen(pat, patlen, kobj->ptr, sdslen(kobj->ptr), 0)) &&
            (expireIfNeeded(c->db, kobj) == 0))
        {
            /* Keep */
        } else {
            decrRefCount(kobj);
            listDelNode(keys, node);
        }
        node = nextnode;
    }

    addReplyMultiBulkLen(c, 2);
    rv = snprintf(buf, sizeof(buf), "%lu", cursor);
    redisAssert(rv < sizeof(buf));
