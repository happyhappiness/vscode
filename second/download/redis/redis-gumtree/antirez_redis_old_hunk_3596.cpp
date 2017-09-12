        }
    break;
    case REDIS_REPLY_NIL:
        out = sdscat(out,prefix);
        out = sdscat(out,"(nil)\n");
    break;
    case REDIS_REPLY_ARRAY:
        if (r->elements == 0) {
            out = sdscat(out,prefix);
            out = sdscat(out,"(empty list or set)\n");
        } else {
            unsigned int i;
            sds tmp;

            for (i = 0; i < r->elements; i++) {
                tmp = cliFormatReply(r->element[i],prefix);
                out = sdscat(out,prefix);
                out = sdscatlen(out,tmp,sdslen(tmp));
                sdsfree(tmp);
            }
        }
    break;
    default:
