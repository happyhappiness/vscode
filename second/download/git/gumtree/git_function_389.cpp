static int run_status(FILE *fp, const char *index_file, const char *prefix, int nowarn,
		      struct wt_status *s)
{
	unsigned char sha1[20];

	if (s->relative_paths)
		s->prefix = prefix;

	if (amend) {
		s->amend = 1;
		s->reference = "HEAD^1";
	}
	s->verbose = verbose;
	s->index_file = index_file;
	s->fp = fp;
	s->nowarn = nowarn;
	s->is_initial = get_sha1(s->reference, sha1) ? 1 : 0;

	wt_status_collect(s);

	switch (status_format) {
	case STATUS_FORMAT_SHORT:
		wt_shortstatus_print(s);
		break;
	case STATUS_FORMAT_PORCELAIN:
		wt_porcelain_print(s);
		break;
	case STATUS_FORMAT_UNSPECIFIED:
		die("BUG: finalize_deferred_config() should have been called");
		break;
	case STATUS_FORMAT_NONE:
	case STATUS_FORMAT_LONG:
		wt_status_print(s);
		break;
	}

	return s->commitable;
}