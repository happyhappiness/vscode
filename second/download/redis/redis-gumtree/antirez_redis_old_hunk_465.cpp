    }

    for (j = 0; j < elements; j++) {
        score = scores[j];

        ele = c->argv[scoreidx+1+j*2]->ptr;
        if (zobj->encoding == OBJ_ENCODING_ZIPLIST) {
            unsigned char *eptr;

            if ((eptr = zzlFind(zobj->ptr,ele,&curscore)) != NULL) {
                if (nx) continue;
                if (incr) {
                    score += curscore;
                    if (isnan(score)) {
                        addReplyError(c,nanerr);
                        goto cleanup;
                    }
                }

                /* Remove and re-insert when score changed. */
                if (score != curscore) {
                    zobj->ptr = zzlDelete(zobj->ptr,eptr);
                    zobj->ptr = zzlInsert(zobj->ptr,ele,score);
                    server.dirty++;
                    updated++;
                }
                processed++;
            } else if (!xx) {
                /* Optimize: check if the element is too large or the list
                 * becomes too long *before* executing zzlInsert. */
                zobj->ptr = zzlInsert(zobj->ptr,ele,score);
                if (zzlLength(zobj->ptr) > server.zset_max_ziplist_entries)
                    zsetConvert(zobj,OBJ_ENCODING_SKIPLIST);
                if (sdslen(ele) > server.zset_max_ziplist_value)
                    zsetConvert(zobj,OBJ_ENCODING_SKIPLIST);
                server.dirty++;
                added++;
                processed++;
            }
        } else if (zobj->encoding == OBJ_ENCODING_SKIPLIST) {
            zset *zs = zobj->ptr;
            zskiplistNode *znode;
            dictEntry *de;

            de = dictFind(zs->dict,ele);
            if (de != NULL) {
                if (nx) continue;
                curscore = *(double*)dictGetVal(de);

                if (incr) {
                    score += curscore;
                    if (isnan(score)) {
                        addReplyError(c,nanerr);
                        /* Don't need to check if the sorted set is empty
                         * because we know it has at least one element. */
                        goto cleanup;
                    }
                }

                /* Remove and re-insert when score changes. */
                if (score != curscore) {
                    zskiplistNode *node;
                    serverAssert(zslDelete(zs->zsl,curscore,ele,&node));
                    znode = zslInsert(zs->zsl,score,node->ele);
                    /* We reused the node->ele SDS string, free the node now
                     * since zslInsert created a new one. */
                    node->ele = NULL;
                    zslFreeNode(node);
                    /* Note that we did not removed the original element from
                     * the hash table representing the sorted set, so we just
                     * update the score. */
                    dictGetVal(de) = &znode->score; /* Update score ptr. */
                    server.dirty++;
                    updated++;
                }
                processed++;
            } else if (!xx) {
                ele = sdsdup(ele);
                znode = zslInsert(zs->zsl,score,ele);
                serverAssert(dictAdd(zs->dict,ele,&znode->score) == DICT_OK);
                server.dirty++;
                added++;
                processed++;
            }
        } else {
            serverPanic("Unknown sorted set encoding");
        }
    }

reply_to_client:
    if (incr) { /* ZINCRBY or INCR option. */
