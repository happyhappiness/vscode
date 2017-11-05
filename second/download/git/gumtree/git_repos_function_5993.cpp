PREC_DIR *precompose_utf8_opendir(const char *dirname)
{
	PREC_DIR *prec_dir = xmalloc(sizeof(PREC_DIR));
	prec_dir->dirent_nfc = xmalloc(sizeof(dirent_prec_psx));
	prec_dir->dirent_nfc->max_name_len = sizeof(prec_dir->dirent_nfc->d_name);

	prec_dir->dirp = opendir(dirname);
	if (!prec_dir->dirp) {
		free(prec_dir->dirent_nfc);
		free(prec_dir);
		return NULL;
	} else {
		int ret_errno = errno;
		prec_dir->ic_precompose = iconv_open(repo_encoding, path_encoding);
		/* if iconv_open() fails, die() in readdir() if needed */
		errno = ret_errno;
	}

	return prec_dir;
}