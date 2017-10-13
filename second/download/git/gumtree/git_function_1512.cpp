static int show_blob_object(const unsigned char *sha1, struct rev_info *rev, const char *obj_name)
{
	unsigned char sha1c[20];
	struct object_context obj_context;
	char *buf;
	unsigned long size;

	fflush(stdout);
	if (!DIFF_OPT_TOUCHED(&rev->diffopt, ALLOW_TEXTCONV) ||
	    !DIFF_OPT_TST(&rev->diffopt, ALLOW_TEXTCONV))
		return stream_blob_to_fd(1, sha1, NULL, 0);

	if (get_sha1_with_context(obj_name, 0, sha1c, &obj_context))
		die("Not a valid object name %s", obj_name);
	if (!obj_context.path[0] ||
	    !textconv_object(obj_context.path, obj_context.mode, sha1c, 1, &buf, &size))
		return stream_blob_to_fd(1, sha1, NULL, 0);

	if (!buf)
		die("git show %s: bad file", obj_name);

	write_or_die(1, buf, size);
	return 0;
}