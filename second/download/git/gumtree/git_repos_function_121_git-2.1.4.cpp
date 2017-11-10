void pp_commit_easy(enum cmit_fmt fmt, const struct commit *commit,
		    struct strbuf *sb)
{
	struct pretty_print_context pp = {0};
	pp.fmt = fmt;
	pretty_print_commit(&pp, commit, sb);
}