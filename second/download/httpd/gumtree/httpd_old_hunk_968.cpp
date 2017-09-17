	    return;
	}
	if (utime(filename, NULL) == -1)
	    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			 "proxy: utimes(%s)", filename);
    }
    files = ap_make_array(r->pool, 100, sizeof(struct gc_ent *));
    curblocks = 0;
    curbytes = 0;

    sub_garbage_coll(r, files, cachedir, "/");

    if (curblocks < cachesize || curblocks + curbytes <= cachesize) {
	ap_unblock_alarms();
	return;
    }

    qsort(files->elts, files->nelts, sizeof(struct gc_ent *), gcdiff);

    elts = (struct gc_ent **) files->elts;
    for (i = 0; i < files->nelts; i++) {
	fent = elts[i];
	sprintf(filename, "%s%s", cachedir, fent->file);
	Explain3("GC Unlinking %s (expiry %ld, garbage_now %ld)", filename, fent->expire, garbage_now);
#if TESTING
	fprintf(stderr, "Would unlink %s\n", filename);
#else
	if (unlink(filename) == -1) {
