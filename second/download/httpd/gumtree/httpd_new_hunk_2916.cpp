                if ((v = *b++ - *a++) != 0)
                    break;
        }
        break;
    default:
        /*  bogosity, pretend that it just wasn't a match */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01540)
                    MODNAME ": invalid type %d in mcheck().", m->type);
        return 0;
    }

    v = signextend(r->server, m, v) & m->mask;

    switch (m->reln) {
    case 'x':
#if MIME_MAGIC_DEBUG
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01541)
                    "%lu == *any* = 1", v);
#endif
        matched = 1;
        break;

    case '!':
        matched = v != l;
#if MIME_MAGIC_DEBUG
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01542)
                    "%lu != %lu = %d", v, l, matched);
#endif
        break;

    case '=':
        matched = v == l;
#if MIME_MAGIC_DEBUG
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01543)
                    "%lu == %lu = %d", v, l, matched);
#endif
        break;

    case '>':
        if (m->flag & UNSIGNED) {
            matched = v > l;
#if MIME_MAGIC_DEBUG
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01544)
                        "%lu > %lu = %d", v, l, matched);
#endif
        }
        else {
            matched = (long) v > (long) l;
#if MIME_MAGIC_DEBUG
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01545)
                        "%ld > %ld = %d", v, l, matched);
#endif
        }
        break;

    case '<':
        if (m->flag & UNSIGNED) {
            matched = v < l;
#if MIME_MAGIC_DEBUG
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01546)
                        "%lu < %lu = %d", v, l, matched);
#endif
        }
        else {
            matched = (long) v < (long) l;
#if MIME_MAGIC_DEBUG
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01547)
                        "%ld < %ld = %d", v, l, matched);
#endif
        }
        break;

    case '&':
        matched = (v & l) == l;
#if MIME_MAGIC_DEBUG
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01548)
                    "((%lx & %lx) == %lx) = %d", v, l, l, matched);
#endif
        break;

    case '^':
        matched = (v & l) != l;
#if MIME_MAGIC_DEBUG
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01549)
                    "((%lx & %lx) != %lx) = %d", v, l, l, matched);
#endif
        break;

    default:
        /* bogosity, pretend it didn't match */
        matched = 0;
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01550)
                    MODNAME ": mcheck: can't happen: invalid relation %d.",
                    m->reln);
        break;
    }

    return matched;
