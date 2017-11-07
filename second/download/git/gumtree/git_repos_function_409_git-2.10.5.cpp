static int notes_cache_match_validity(const char *ref, const char *validity)
{
	unsigned char sha1[20];
	struct commit *commit;
	struct pretty_print_context pretty_ctx;
	struct strbuf msg = STRBUF_INIT;
	int ret;

	if (read_ref(ref, sha1) < 0)
		return 0;

	commit = lookup_commit_reference_gently(sha1, 1);
	if (!commit)
		return 0;

	memset(&pretty_ctx, 0, sizeof(pretty_ctx));
	format_commit_message(commit, "%s", &msg, &pretty_ctx);
	strbuf_trim(&msg);

	ret = !strcmp(msg.buf, validity);
	strbuf_release(&msg);

	return ret;
}