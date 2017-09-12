    case REDIS_REPLY_ARRAY:
        return processMultiBulkItem(r);
    default:
        assert(NULL);
        return -1;
    }
}
