	}
	s->verbose = verbose;
	s->index_file = index_file;
	s->fp = fp;
	s->nowarn = nowarn;
	s->is_initial = get_sha1(s->reference, sha1) ? 1 : 0;
	if (!s->is_initial)
		hashcpy(s->sha1_commit, sha1);
	s->status_format = status_format;
	s->ignore_submodule_arg = ignore_submodule_arg;

	wt_status_collect(s);
	wt_status_print(s);

	return s->commitable;
}

static int is_a_merge(const struct commit *current_head)
{
