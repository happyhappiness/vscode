            ele = c->argv[3+j*2];
            if ((eptr = zzlFind(zobj->ptr,ele,&curscore)) != NULL) {
                if (incr) {
                    score += curscore;
                    if (isnan(score)) {
                        addReplyError(c,nanerr);
                        /* Don't need to check if the sorted set is empty
                         * because we know it has at least one element. */
                        zfree(scores);
                        return;
                    }
                }

                /* Remove and re-insert when score changed. */
                if (score != curscore) {
                    zobj->ptr = zzlDelete(zobj->ptr,eptr);
                    zobj->ptr = zzlInsert(zobj->ptr,ele,score);

                    signalModifiedKey(c->db,key);
                    server.dirty++;
                }
            } else {
                /* Optimize: check if the element is too large or the list
                 * becomes too long *before* executing zzlInsert. */
                zobj->ptr = zzlInsert(zobj->ptr,ele,score);
                if (zzlLength(zobj->ptr) > server.zset_max_ziplist_entries)
                    zsetConvert(zobj,REDIS_ENCODING_SKIPLIST);
                if (sdslen(ele->ptr) > server.zset_max_ziplist_value)
                    zsetConvert(zobj,REDIS_ENCODING_SKIPLIST);

                signalModifiedKey(c->db,key);
                server.dirty++;
                if (!incr) added++;
            }
        } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
            zset *zs = zobj->ptr;
            zskiplistNode *znode;
            dictEntry *de;

