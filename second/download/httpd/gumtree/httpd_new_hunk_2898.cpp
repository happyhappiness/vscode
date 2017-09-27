        case LELONG:
            v = (long) v;
            break;
        case STRING:
            break;
        default:
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01520)
                        MODNAME ": can't happen: m->type=%d", m->type);
            return -1;
        }
    return v;
}

