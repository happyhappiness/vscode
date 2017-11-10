static int push_update_ref_status(struct strbuf *buf,
				   struct ref **ref,
				   struct ref *remote_refs)
{
	char *refname, *msg;
	int status, forced = 0;

	if (starts_with(buf->buf, "ok ")) {
		status = REF_STATUS_OK;
		refname = buf->buf + 3;
	} else if (starts_with(buf->buf, "error ")) {
		status = REF_STATUS_REMOTE_REJECT;
		refname = buf->buf + 6;
	} else
		die("expected ok/error, helper said '%s'", buf->buf);

	msg = strchr(refname, ' ');
	if (msg) {
		struct strbuf msg_buf = STRBUF_INIT;
		const char *end;

		*msg++ = '\0';
		if (!unquote_c_style(&msg_buf, msg, &end))
			msg = strbuf_detach(&msg_buf, NULL);
		else
			msg = xstrdup(msg);
		strbuf_release(&msg_buf);

		if (!strcmp(msg, "no match")) {
			status = REF_STATUS_NONE;
			free(msg);
			msg = NULL;
		}
		else if (!strcmp(msg, "up to date")) {
			status = REF_STATUS_UPTODATE;
			free(msg);
			msg = NULL;
		}
		else if (!strcmp(msg, "non-fast forward")) {
			status = REF_STATUS_REJECT_NONFASTFORWARD;
			free(msg);
			msg = NULL;
		}
		else if (!strcmp(msg, "already exists")) {
			status = REF_STATUS_REJECT_ALREADY_EXISTS;
			free(msg);
			msg = NULL;
		}
		else if (!strcmp(msg, "fetch first")) {
			status = REF_STATUS_REJECT_FETCH_FIRST;
			free(msg);
			msg = NULL;
		}
		else if (!strcmp(msg, "needs force")) {
			status = REF_STATUS_REJECT_NEEDS_FORCE;
			free(msg);
			msg = NULL;
		}
		else if (!strcmp(msg, "stale info")) {
			status = REF_STATUS_REJECT_STALE;
			free(msg);
			msg = NULL;
		}
		else if (!strcmp(msg, "forced update")) {
			forced = 1;
			free(msg);
			msg = NULL;
		}
	}

	if (*ref)
		*ref = find_ref_by_name(*ref, refname);
	if (!*ref)
		*ref = find_ref_by_name(remote_refs, refname);
	if (!*ref) {
		warning("helper reported unexpected status of %s", refname);
		return 1;
	}

	if ((*ref)->status != REF_STATUS_NONE) {
		/*
		 * Earlier, the ref was marked not to be pushed, so ignore the ref
		 * status reported by the remote helper if the latter is 'no match'.
		 */
		if (status == REF_STATUS_NONE)
			return 1;
	}

	(*ref)->status = status;
	(*ref)->forced_update |= forced;
	(*ref)->remote_status = msg;
	return !(status == REF_STATUS_OK);
}