static int show_blob_object(const struct object_id *oid, struct rev_info *rev, const char *obj_name)
{
	struct object_id oidc;
	struct object_context obj_context;
	char *buf;
	unsigned long size;

	fflush(rev->diffopt.file);
	if (!DIFF_OPT_TOUCHED(&rev->diffopt, ALLOW_TEXTCONV) ||
	    !DIFF_OPT_TST(&rev->diffopt, ALLOW_TEXTCONV))
		return stream_blob_to_fd(1, oid, NULL, 0);

	if (get_sha1_with_context(obj_name, GET_SHA1_RECORD_PATH,
				  oidc.hash, &obj_context))
		die(_("Not a valid object name %s"), obj_name);
	if (!obj_context.path ||
	    !textconv_object(obj_context.path, obj_context.mode, &oidc, 1, &buf, &size)) {
		free(obj_context.path);
		return stream_blob_to_fd(1, oid, NULL, 0);
	}

	if (!buf)
		die(_("git show %s: bad file"), obj_name);

	write_or_die(1, buf, size);
	free(obj_context.path);
	return 0;
}