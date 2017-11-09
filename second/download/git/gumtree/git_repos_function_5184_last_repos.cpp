static void describe_one_orphan(struct strbuf *sb, struct commit *commit)
{
	strbuf_addstr(sb, "  ");
	strbuf_add_unique_abbrev(sb, commit->object.oid.hash, DEFAULT_ABBREV);
	strbuf_addch(sb, ' ');
	if (!parse_commit(commit))
		pp_commit_easy(CMIT_FMT_ONELINE, commit, sb);
	strbuf_addch(sb, '\n');
}