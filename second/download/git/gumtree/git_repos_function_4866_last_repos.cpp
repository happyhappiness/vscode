static int is_cr_needed(xdfenv_t *xe1, xdfenv_t *xe2, xdmerge_t *m)
{
	int needs_cr;

	/* Match post-images' preceding, or first, lines' end-of-line style */
	needs_cr = is_eol_crlf(&xe1->xdf2, m->i1 ? m->i1 - 1 : 0);
	if (needs_cr)
		needs_cr = is_eol_crlf(&xe2->xdf2, m->i2 ? m->i2 - 1 : 0);
	/* Look at pre-image's first line, unless we already settled on LF */
	if (needs_cr)
		needs_cr = is_eol_crlf(&xe1->xdf1, 0);
	/* If still undecided, use LF-only */
	return needs_cr < 0 ? 0 : needs_cr;
}