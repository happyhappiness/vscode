static int store_updated_refs(const char *raw_url, const char *remote_name,
		struct ref *ref_map)
{
	FILE *fp;
	struct commit *commit;
	int url_len, i, rc = 0;
	struct strbuf note = STRBUF_INIT;
	const char *what, *kind;
	struct ref *rm;
	char *url;
	const char *filename = dry_run ? "/dev/null" : git_path_fetch_head();
	int want_status;

	fp = fopen(filename, "a");
	if (!fp)
		return error(_("cannot open %s: %s\n"), filename, strerror(errno));

	if (raw_url)
		url = transport_anonymize_url(raw_url);
	else
		url = xstrdup("foreign");

	rm = ref_map;
	if (check_everything_connected(iterate_ref_map, 0, &rm)) {
		rc = error(_("%s did not send all necessary objects\n"), url);
		goto abort;
	}

	/*
	 * We do a pass for each fetch_head_status type in their enum order, so
	 * merged entries are written before not-for-merge. That lets readers
	 * use FETCH_HEAD as a refname to refer to the ref to be merged.
	 */
	for (want_status = FETCH_HEAD_MERGE;
	     want_status <= FETCH_HEAD_IGNORE;
	     want_status++) {
		for (rm = ref_map; rm; rm = rm->next) {
			struct ref *ref = NULL;
			const char *merge_status_marker = "";

			if (rm->status == REF_STATUS_REJECT_SHALLOW) {
				if (want_status == FETCH_HEAD_MERGE)
					warning(_("reject %s because shallow roots are not allowed to be updated"),
						rm->peer_ref ? rm->peer_ref->name : rm->name);
				continue;
			}

			commit = lookup_commit_reference_gently(rm->old_oid.hash, 1);
			if (!commit)
				rm->fetch_head_status = FETCH_HEAD_NOT_FOR_MERGE;

			if (rm->fetch_head_status != want_status)
				continue;

			if (rm->peer_ref) {
				ref = alloc_ref(rm->peer_ref->name);
				oidcpy(&ref->old_oid, &rm->peer_ref->old_oid);
				oidcpy(&ref->new_oid, &rm->old_oid);
				ref->force = rm->peer_ref->force;
			}


			if (!strcmp(rm->name, "HEAD")) {
				kind = "";
				what = "";
			}
			else if (starts_with(rm->name, "refs/heads/")) {
				kind = "branch";
				what = rm->name + 11;
			}
			else if (starts_with(rm->name, "refs/tags/")) {
				kind = "tag";
				what = rm->name + 10;
			}
			else if (starts_with(rm->name, "refs/remotes/")) {
				kind = "remote-tracking branch";
				what = rm->name + 13;
			}
			else {
				kind = "";
				what = rm->name;
			}

			url_len = strlen(url);
			for (i = url_len - 1; url[i] == '/' && 0 <= i; i--)
				;
			url_len = i + 1;
			if (4 < i && !strncmp(".git", url + i - 3, 4))
				url_len = i - 3;

			strbuf_reset(&note);
			if (*what) {
				if (*kind)
					strbuf_addf(&note, "%s ", kind);
				strbuf_addf(&note, "'%s' of ", what);
			}
			switch (rm->fetch_head_status) {
			case FETCH_HEAD_NOT_FOR_MERGE:
				merge_status_marker = "not-for-merge";
				/* fall-through */
			case FETCH_HEAD_MERGE:
				fprintf(fp, "%s\t%s\t%s",
					oid_to_hex(&rm->old_oid),
					merge_status_marker,
					note.buf);
				for (i = 0; i < url_len; ++i)
					if ('\n' == url[i])
						fputs("\\n", fp);
					else
						fputc(url[i], fp);
				fputc('\n', fp);
				break;
			default:
				/* do not write anything to FETCH_HEAD */
				break;
			}

			strbuf_reset(&note);
			if (ref) {
				rc |= update_local_ref(ref, what, rm, &note);
				free(ref);
			} else
				strbuf_addf(&note, "* %-*s %-*s -> FETCH_HEAD",
					    TRANSPORT_SUMMARY_WIDTH,
					    *kind ? kind : "branch",
					    REFCOL_WIDTH,
					    *what ? what : "HEAD");
			if (note.len) {
				if (verbosity >= 0 && !shown_url) {
					fprintf(stderr, _("From %.*s\n"),
							url_len, url);
					shown_url = 1;
				}
				if (verbosity >= 0)
					fprintf(stderr, " %s\n", note.buf);
			}
		}
	}

	if (rc & STORE_REF_ERROR_DF_CONFLICT)
		error(_("some local refs could not be updated; try running\n"
		      " 'git remote prune %s' to remove any old, conflicting "
		      "branches"), remote_name);

 abort:
	strbuf_release(&note);
	free(url);
	fclose(fp);
	return rc;
}