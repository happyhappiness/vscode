            if (server.cluster_enabled) {
                addReplyError(c,"GET option of SORT denied in Cluster mode.");
                syntax_error++;
                break;
            }
            listAddNodeTail(operations,createSortOperation(
                SORT_OP_GET,c->argv[j+1]));
            getop++;
            j++;
        } else {
            addReply(c,shared.syntaxerr);
            syntax_error++;
            break;
