        break;
    case REDIS_REPLY_STATUS:
    case REDIS_REPLY_STRING:
        if (r->type == REDIS_REPLY_STATUS && config.eval_ldb) {
            /* The Lua debugger replies with arrays of simple (status)
             * strings. We colorize the output for more fun if this
             * is a debugging session. */
            out = sdsCatColorizedLdbReply(out,r->str,r->len);
        } else {
            out = sdscatlen(out,r->str,r->len);
        }
        break;
    case REDIS_REPLY_INTEGER:
        out = sdscatprintf(out,"%lld",r->integer);
