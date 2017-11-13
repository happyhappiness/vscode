static void show_ce_entry(const char *tag, const struct cache_entry *ce)
{
	int len = max_prefix_len;

	if (len >= ce_namelen(ce))
		die("git ls-files: internal error - cache entry not superset of prefix");

	if (!match_pathspec(&pathspec, ce->name, ce_namelen(ce),
			    len, ps_matched,
			    S_ISDIR(ce->ce_mode) || S_ISGITLINK(ce->ce_mode)))
		return;

	if (tag && *tag && show_valid_bit &&
	    (ce->ce_flags & CE_VALID)) {
		static char alttag[4];
		memcpy(alttag, tag, 3);
		if (isalpha(tag[0]))
			alttag[0] = tolower(tag[0]);
		else if (tag[0] == '?')
			alttag[0] = '!';
		else {
			alttag[0] = 'v';
			alttag[1] = tag[0];
			alttag[2] = ' ';
			alttag[3] = 0;
		}
		tag = alttag;
	}

	if (!show_stage) {
		fputs(tag, stdout);
	} else {
		printf("%s%06o %s %d\t",
		       tag,
		       ce->ce_mode,
		       find_unique_abbrev(ce->sha1,abbrev),
		       ce_stage(ce));
	}
	write_eolinfo(ce, ce->name);
	write_name(ce->name);
	if (debug_mode) {
		const struct stat_data *sd = &ce->ce_stat_data;

		printf("  ctime: %d:%d\n", sd->sd_ctime.sec, sd->sd_ctime.nsec);
		printf("  mtime: %d:%d\n", sd->sd_mtime.sec, sd->sd_mtime.nsec);
		printf("  dev: %d\tino: %d\n", sd->sd_dev, sd->sd_ino);
		printf("  uid: %d\tgid: %d\n", sd->sd_uid, sd->sd_gid);
		printf("  size: %d\tflags: %x\n", sd->sd_size, ce->ce_flags);
	}
}