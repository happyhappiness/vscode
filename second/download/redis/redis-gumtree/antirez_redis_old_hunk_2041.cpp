            updated++;
            break;
        case -1:
            addReplyError(c,"Invalid HyperLogLog representation");
            return;
        }
    }
