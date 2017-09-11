        break;
    case REDIS_REPLY_STATUS:
    case REDIS_REPLY_STRING:
        out = sdscatlen(out,r->str,r->len);
        break;
    case REDIS_REPLY_INTEGER:
        out = sdscatprintf(out,"%lld",r->integer);
