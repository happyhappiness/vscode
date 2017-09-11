            decrRefCount(kobj);
            listDelNode(keys, ln);
        }

        ln = ln_;
    }

    addReplyMultiBulkLen(c, 2);

    rv = snprintf(buf, sizeof(buf), "%lu", cursor);
    redisAssert(rv < sizeof(buf));
    addReplyBulkCBuffer(c, buf, rv);
