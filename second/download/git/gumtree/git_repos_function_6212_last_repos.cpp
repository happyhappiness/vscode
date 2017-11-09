static void merge_name(const char *remote, struct strbuf *msg)
{
	struct commit *remote_head;
	struct object_id branch_head;
	struct strbuf buf = STRBUF_INIT;
	struct strbuf bname = STRBUF_INIT;
	const char *ptr;
	char *found_ref;
	int len, early;

	strbuf_branchname(&bname, remote, 0);
	remote = bname.buf;

	oidclr(&branch_head);
	remote_head = get_merge_parent(remote);
	if (!remote_head)
		die(_("'%s' does not point to a commit"), remote);

	if (dwim_ref(remote, strlen(remote), branch_head.hash, &found_ref) > 0) {
		if (starts_with(found_ref, "refs/heads/")) {
			strbuf_addf(msg, "%s\t\tbranch '%s' of .\n",
				    oid_to_hex(&branch_head), remote);
			goto cleanup;
		}
		if (starts_with(found_ref, "refs/tags/")) {
			strbuf_addf(msg, "%s\t\ttag '%s' of .\n",
				    oid_to_hex(&branch_head), remote);
			goto cleanup;
		}
		if (starts_with(found_ref, "refs/remotes/")) {
			strbuf_addf(msg, "%s\t\tremote-tracking branch '%s' of .\n",
				    oid_to_hex(&branch_head), remote);
			goto cleanup;
		}
	}

	/* See if remote matches <name>^^^.. or <name>~<number> */
	for (len = 0, ptr = remote + strlen(remote);
	     remote < ptr && ptr[-1] == '^';
	     ptr--)
		len++;
	if (len)
		early = 1;
	else {
		early = 0;
		ptr = strrchr(remote, '~');
		if (ptr) {
			int seen_nonzero = 0;

			len++; /* count ~ */
			while (*++ptr && isdigit(*ptr)) {
				seen_nonzero |= (*ptr != '0');
				len++;
			}
			if (*ptr)
				len = 0; /* not ...~<number> */
			else if (seen_nonzero)
				early = 1;
			else if (len == 1)
				early = 1; /* "name~" is "name~1"! */
		}
	}
	if (len) {
		struct strbuf truname = STRBUF_INIT;
		strbuf_addf(&truname, "refs/heads/%s", remote);
		strbuf_setlen(&truname, truname.len - len);
		if (ref_exists(truname.buf)) {
			strbuf_addf(msg,
				    "%s\t\tbranch '%s'%s of .\n",
				    oid_to_hex(&remote_head->object.oid),
				    truname.buf + 11,
				    (early ? " (early part)" : ""));
			strbuf_release(&truname);
			goto cleanup;
		}
		strbuf_release(&truname);
	}

	if (remote_head->util) {
		struct merge_remote_desc *desc;
		desc = merge_remote_util(remote_head);
		if (desc && desc->obj && desc->obj->type == OBJ_TAG) {
			strbuf_addf(msg, "%s\t\t%s '%s'\n",
				    oid_to_hex(&desc->obj->oid),
				    typename(desc->obj->type),
				    remote);
			goto cleanup;
		}
	}

	strbuf_addf(msg, "%s\t\tcommit '%s'\n",
		oid_to_hex(&remote_head->object.oid), remote);
cleanup:
	strbuf_release(&buf);
	strbuf_release(&bname);
}