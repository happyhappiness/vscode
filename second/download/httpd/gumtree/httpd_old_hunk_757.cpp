	    m = m->next;
	}
#if MIME_MAGIC_DEBUG
	ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
		    MODNAME ": matched after %d rules", rule_counter);
#endif
	return 1;		/* all through */
    }
#if MIME_MAGIC_DEBUG
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
		MODNAME ": failed after %d rules", rule_counter);
#endif
    return 0;			/* no match at all */
}

static void mprint(request_rec *r, union VALUETYPE *p, struct magic *m)
{
    char *pp;
    unsigned long v;
