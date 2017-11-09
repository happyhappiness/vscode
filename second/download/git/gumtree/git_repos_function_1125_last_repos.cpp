static void wt_status_get_detached_from(struct wt_status_state *state)
{
	struct grab_1st_switch_cbdata cb;
	struct commit *commit;
	struct object_id oid;
	char *ref = NULL;

	strbuf_init(&cb.buf, 0);
	if (for_each_reflog_ent_reverse("HEAD", grab_1st_switch, &cb) <= 0) {
		strbuf_release(&cb.buf);
		return;
	}

	if (dwim_ref(cb.buf.buf, cb.buf.len, oid.hash, &ref) == 1 &&
	    /* sha1 is a commit? match without further lookup */
	    (!oidcmp(&cb.noid, &oid) ||
	     /* perhaps sha1 is a tag, try to dereference to a commit */
	     ((commit = lookup_commit_reference_gently(&oid, 1)) != NULL &&
	      !oidcmp(&cb.noid, &commit->object.oid)))) {
		const char *from = ref;
		if (!skip_prefix(from, "refs/tags/", &from))
			skip_prefix(from, "refs/remotes/", &from);
		state->detached_from = xstrdup(from);
	} else
		state->detached_from =
			xstrdup(find_unique_abbrev(cb.noid.hash, DEFAULT_ABBREV));
	hashcpy(state->detached_sha1, cb.noid.hash);
	state->detached_at = !get_oid("HEAD", &oid) &&
			     !hashcmp(oid.hash, state->detached_sha1);

	free(ref);
	strbuf_release(&cb.buf);
}