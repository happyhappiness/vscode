static int detect_patch_format(const char **paths)
{
	enum patch_format ret = PATCH_FORMAT_UNKNOWN;
	struct strbuf l1 = STRBUF_INIT;
	struct strbuf l2 = STRBUF_INIT;
	struct strbuf l3 = STRBUF_INIT;
	FILE *fp;

	/*
	 * We default to mbox format if input is from stdin and for directories
	 */
	if (!*paths || !strcmp(*paths, "-") || is_directory(*paths))
		return PATCH_FORMAT_MBOX;

	/*
	 * Otherwise, check the first few lines of the first patch, starting
	 * from the first non-blank line, to try to detect its format.
	 */

	fp = xfopen(*paths, "r");

	while (!strbuf_getline(&l1, fp)) {
		if (l1.len)
			break;
	}

	if (starts_with(l1.buf, "From ") || starts_with(l1.buf, "From: ")) {
		ret = PATCH_FORMAT_MBOX;
		goto done;
	}

	if (starts_with(l1.buf, "# This series applies on GIT commit")) {
		ret = PATCH_FORMAT_STGIT_SERIES;
		goto done;
	}

	if (!strcmp(l1.buf, "# HG changeset patch")) {
		ret = PATCH_FORMAT_HG;
		goto done;
	}

	strbuf_reset(&l2);
	strbuf_getline(&l2, fp);
	strbuf_reset(&l3);
	strbuf_getline(&l3, fp);

	/*
	 * If the second line is empty and the third is a From, Author or Date
	 * entry, this is likely an StGit patch.
	 */
	if (l1.len && !l2.len &&
		(starts_with(l3.buf, "From:") ||
		 starts_with(l3.buf, "Author:") ||
		 starts_with(l3.buf, "Date:"))) {
		ret = PATCH_FORMAT_STGIT;
		goto done;
	}

	if (l1.len && is_mail(fp)) {
		ret = PATCH_FORMAT_MBOX;
		goto done;
	}

done:
	fclose(fp);
	strbuf_release(&l1);
	return ret;
}