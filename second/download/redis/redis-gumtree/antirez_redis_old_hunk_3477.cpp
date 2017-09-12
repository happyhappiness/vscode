    case REDIS_REPLY_ARRAY:
        return processMultiBulkItem(r);
    default:
        redisSetReplyReaderError(r,sdscatprintf(sdsempty(),
            "unknown item type '%d'", cur->type));
        return -1;
    }
}
