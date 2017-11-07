int print_stat_summary(FILE *fp, int files, int insertions, int deletions)
{
	struct strbuf sb = STRBUF_INIT;
	int ret;

	if (!files) {
		assert(insertions == 0 && deletions == 0);
		return fprintf(fp, "%s\n", " 0 files changed");
	}

	strbuf_addf(&sb,
		    (files == 1) ? " %d file changed" : " %d files changed",
		    files);

	/*
	 * For binary diff, the caller may want to print "x files
	 * changed" with insertions == 0 && deletions == 0.
	 *
	 * Not omitting "0 insertions(+), 0 deletions(-)" in this case
	 * is probably less confusing (i.e skip over "2 files changed
	 * but nothing about added/removed lines? Is this a bug in Git?").
	 */
	if (insertions || deletions == 0) {
		strbuf_addf(&sb,
			    (insertions == 1) ? ", %d insertion(+)" : ", %d insertions(+)",
			    insertions);
	}

	if (deletions || insertions == 0) {
		strbuf_addf(&sb,
			    (deletions == 1) ? ", %d deletion(-)" : ", %d deletions(-)",
			    deletions);
	}
	strbuf_addch(&sb, '\n');
	ret = fputs(sb.buf, fp);
	strbuf_release(&sb);
	return ret;
}