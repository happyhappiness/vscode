static void adjust_refcol_width(const struct ref *ref)
{
	int max, rlen, llen, len;

	/* uptodate lines are only shown on high verbosity level */
	if (!verbosity && !oidcmp(&ref->peer_ref->old_oid, &ref->old_oid))
		return;

	max    = term_columns();
	rlen   = utf8_strwidth(prettify_refname(ref->name));

	llen   = utf8_strwidth(prettify_refname(ref->peer_ref->name));

	/*
	 * rough estimation to see if the output line is too long and
	 * should not be counted (we can't do precise calculation
	 * anyway because we don't know if the error explanation part
	 * will be printed in update_local_ref)
	 */
	if (compact_format) {
		llen = 0;
		max = max * 2 / 3;
	}
	len = 21 /* flag and summary */ + rlen + 4 /* -> */ + llen;
	if (len >= max)
		return;

	/*
	 * Not precise calculation for compact mode because '*' can
	 * appear on the left hand side of '->' and shrink the column
	 * back.
	 */
	if (refcol_width < rlen)
		refcol_width = rlen;
}