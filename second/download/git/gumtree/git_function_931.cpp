static int receive_status(int in, struct ref *refs)
{
	struct ref *hint;
	int ret = 0;
	char *line = packet_read_line(in, NULL);
	if (!starts_with(line, "unpack "))
		return error("did not receive remote status");
	if (strcmp(line, "unpack ok")) {
		error("unpack failed: %s", line + 7);
		ret = -1;
	}
	hint = NULL;
	while (1) {
		char *refname;
		char *msg;
		line = packet_read_line(in, NULL);
		if (!line)
			break;
		if (!starts_with(line, "ok ") && !starts_with(line, "ng ")) {
			error("invalid ref status from remote: %s", line);
			ret = -1;
			break;
		}

		refname = line + 3;
		msg = strchr(refname, ' ');
		if (msg)
			*msg++ = '\0';

		/* first try searching at our hint, falling back to all refs */
		if (hint)
			hint = find_ref_by_name(hint, refname);
		if (!hint)
			hint = find_ref_by_name(refs, refname);
		if (!hint) {
			warning("remote reported status on unknown ref: %s",
					refname);
			continue;
		}
		if (hint->status != REF_STATUS_EXPECTING_REPORT) {
			warning("remote reported status on unexpected ref: %s",
					refname);
			continue;
		}

		if (line[0] == 'o' && line[1] == 'k')
			hint->status = REF_STATUS_OK;
		else {
			hint->status = REF_STATUS_REMOTE_REJECT;
			ret = -1;
		}
		hint->remote_status = xstrdup_or_null(msg);
		/* start our next search from the next ref */
		hint = hint->next;
	}
	return ret;
}