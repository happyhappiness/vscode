            updated++;
            break;
        case -1:
            addReplyError(c,invalid_hll_err);
            return;
        }
    }
