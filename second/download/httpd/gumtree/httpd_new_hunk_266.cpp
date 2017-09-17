     * where we would end up with LOTS of zombies.
     */
    sub_pool = ap_make_sub_pool(r->pool);

    if (!ap_bspawn_child(sub_pool, uncompress_child, &parm, kill_always,
			 &bin, &bout, NULL)) {
	ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
		    MODNAME ": couldn't spawn uncompress process: %s", r->uri);
	return -1;
    }

    if (ap_bwrite(bin, old, n) != n) {
	ap_destroy_pool(sub_pool);
	ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
		    MODNAME ": write failed.");
	return -1;
    }
    ap_bclose(bin);
    *newch = (unsigned char *) ap_palloc(r->pool, n);
    if ((n = ap_bread(bout, *newch, n)) <= 0) {
	ap_destroy_pool(sub_pool);
	ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
	    MODNAME ": read failed %s", r->filename);
	return -1;
    }
    ap_destroy_pool(sub_pool);
    return n;
}
