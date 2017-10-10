
static int similarity_index(struct diff_filepair *p)
{
	return p->score * 100 / MAX_SCORE;
}

static void fill_metainfo(struct strbuf *msg,
			  const char *name,
			  const char *other,
			  struct diff_filespec *one,
			  struct diff_filespec *two,
			  struct diff_options *o,
