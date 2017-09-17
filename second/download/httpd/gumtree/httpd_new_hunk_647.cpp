	    return;
	}
	if (utime(filename, NULL) == -1)
	    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			 "proxy: utimes(%s)", filename);
    }
    files = ap_make_array(r->pool, 100, sizeof(struct gc_ent));
    curbytes.upper = curbytes.lower = 0L;

    sub_garbage_coll(r, files, cachedir, "/");

    if (cmp_long61(&curbytes, &cachesize) < 0L) {
	ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, r->server,
			 "proxy GC: Cache is %ld%% full (nothing deleted)",
			 (long)(((curbytes.upper<<20)|(curbytes.lower>>10))*100/conf->space));
	ap_unblock_alarms();
	return;
    }

    /* sort the files we found by expiration date */
    qsort(files->elts, files->nelts, sizeof(struct gc_ent), gcdiff);

    for (i = 0; i < files->nelts; i++) {
	fent = &((struct gc_ent *) files->elts)[i];
	sprintf(filename, "%s%s", cachedir, fent->file);
	Explain3("GC Unlinking %s (expiry %ld, garbage_now %ld)", filename, fent->expire, garbage_now);
#if TESTING
	fprintf(stderr, "Would unlink %s\n", filename);
#else
	if (unlink(filename) == -1) {
