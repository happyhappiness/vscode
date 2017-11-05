static void print_commit(char sign, struct commit *commit, int verbose,
			 int abbrev)
{
	if (!verbose) {
		printf("%c %s\n", sign,
		       find_unique_abbrev(commit->object.sha1, abbrev));
	} else {
		struct strbuf buf = STRBUF_INIT;
		pp_commit_easy(CMIT_FMT_ONELINE, commit, &buf);
		printf("%c %s %s\n", sign,
		       find_unique_abbrev(commit->object.sha1, abbrev),
		       buf.buf);
		strbuf_release(&buf);
	}
}