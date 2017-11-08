static int fetch_finish(int retvalue, struct strbuf *err,
			void *cb, void *task_cb)
{
	struct submodule_parallel_fetch *spf = cb;

	if (retvalue)
		spf->result = 1;

	return 0;
}