static void describe_detached_head(const char *msg, struct commit *commit)
{
	struct strbuf sb = STRBUF_INIT;
	if (!parse_commit(commit))
		pp_commit_easy(CMIT_FMT_ONELINE, commit, &sb);
	fprintf(stderr, "%s %s... %s\n", msg,
		find_unique_abbrev(commit->object.oid.hash, DEFAULT_ABBREV), sb.buf);
	strbuf_release(&sb);
}