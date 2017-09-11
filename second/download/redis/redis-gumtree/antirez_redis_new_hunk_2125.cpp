            if (strchr(c->argv[j+1]->ptr,'*') == NULL) dontsort = 1;
            j++;
        } else if (!strcasecmp(c->argv[j]->ptr,"get") && leftargs >= 1) {
            if (server.cluster_enabled) {
                addReplyError(c,"GET option of SORT denied in Cluster mode.");
                syntax_error++;
                break;
            }
            listAddNodeTail(operations,createSortOperation(
                REDIS_SORT_GET,c->argv[j+1]));
            getop++;
            j++;
        } else {
            addReply(c,shared.syntaxerr);
            syntax_error++;
            break;
        }
        j++;
    }

    /* Handle syntax errors set during options parsing. */
    if (syntax_error) {
        decrRefCount(sortval);
        listRelease(operations);
        return;
    }

    /* For the STORE option, or when SORT is called from a Lua script,
     * we want to force a specific ordering even when no explicit ordering
     * was asked (SORT BY nosort). This guarantees that replication / AOF
