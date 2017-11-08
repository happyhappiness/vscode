void add_cvs_excludes(void)
{
	char fname[MAXPATHLEN];
	char *p;

	add_exclude(&exclude_list, default_cvsignore,
		    XFLG_WORD_SPLIT | XFLG_WORDS_ONLY);

	if ((p = getenv("HOME"))
	    && pathjoin(fname, sizeof fname, p, ".cvsignore") < sizeof fname) {
		add_exclude_file(&exclude_list, fname,
				 XFLG_WORD_SPLIT | XFLG_WORDS_ONLY);
	}

	add_exclude(&exclude_list, getenv("CVSIGNORE"),
		    XFLG_WORD_SPLIT | XFLG_WORDS_ONLY);
}