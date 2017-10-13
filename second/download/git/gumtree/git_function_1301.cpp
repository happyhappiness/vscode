static void get_merge_heads(struct oid_array *merge_heads)
{
	const char *filename = git_path_fetch_head();
	FILE *fp;
	struct strbuf sb = STRBUF_INIT;
	struct object_id oid;

	if (!(fp = fopen(filename, "r")))
		die_errno(_("could not open '%s' for reading"), filename);
	while (strbuf_getline_lf(&sb, fp) != EOF) {
		if (get_oid_hex(sb.buf, &oid))
			continue;  /* invalid line: does not start with SHA1 */
		if (starts_with(sb.buf + GIT_SHA1_HEXSZ, "\tnot-for-merge\t"))
			continue;  /* ref is not-for-merge */
		oid_array_append(merge_heads, &oid);
	}
	fclose(fp);
	strbuf_release(&sb);
}