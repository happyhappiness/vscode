static void wt_status_get_detached_from(struct wt_status_state *state)
{
	struct grab_1st_switch_cbdata cb;
	struct commit *commit;
	unsigned char sha1[20];
	char *ref = NULL;

	strbuf_init(&cb.buf, 0);
	if (for_each_reflog_ent_reverse("HEAD", grab_1st_switch, &cb) <= 0) {
		strbuf_release(&cb.buf);
		return;
	}

	if (dwim_ref(cb.buf.buf, cb.buf.len, sha1, &ref) == 1 &&
	    /* sha1 is a commit? match without further lookup */
	    (!hashcmp(cb.nsha1, sha1) ||
	     /* perhaps sha1 is a tag, try to dereference to a commit */
	     ((commit = lookup_commit_reference_gently(sha1, 1)) != NULL &&
	      !hashcmp(cb.nsha1, commit->object.sha1)))) {
		int ofs;
		if (starts_with(ref, "refs/tags/"))
			ofs = strlen("refs/tags/");
		else if (starts_with(ref, "refs/remotes/"))
			ofs = strlen("refs/remotes/");
		else
			ofs = 0;
		state->detached_from = xstrdup(ref + ofs);
	} else
		state->detached_from =
			xstrdup(find_unique_abbrev(cb.nsha1, DEFAULT_ABBREV));
	hashcpy(state->detached_sha1, cb.nsha1);
	state->detached_at = !get_sha1("HEAD", sha1) &&
			     !hashcmp(sha1, state->detached_sha1);

	free(ref);
	strbuf_release(&cb.buf);
}