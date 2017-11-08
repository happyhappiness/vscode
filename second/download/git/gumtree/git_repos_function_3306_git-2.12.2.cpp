static void scan_rerere_dir(struct rerere_dir *rr_dir)
{
	struct dirent *de;
	DIR *dir = opendir(git_path("rr-cache/%s", sha1_to_hex(rr_dir->sha1)));

	if (!dir)
		return;
	while ((de = readdir(dir)) != NULL) {
		int variant;

		if (is_rr_file(de->d_name, "postimage", &variant)) {
			fit_variant(rr_dir, variant);
			rr_dir->status[variant] |= RR_HAS_POSTIMAGE;
		} else if (is_rr_file(de->d_name, "preimage", &variant)) {
			fit_variant(rr_dir, variant);
			rr_dir->status[variant] |= RR_HAS_PREIMAGE;
		}
	}
	closedir(dir);
}