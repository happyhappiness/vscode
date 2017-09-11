            updated++;
            break;
        case -1:
            addReplySds(c,sdsnew(invalid_hll_err));
            return;
        }
    }
