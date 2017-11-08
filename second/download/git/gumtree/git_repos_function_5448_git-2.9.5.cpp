static int update_clone_task_finished(int result,
				      struct strbuf *err,
				      void *suc_cb,
				      void *void_task_cb)
{
	struct submodule_update_clone *suc = suc_cb;

	if (!result)
		return 0;

	suc->quickstop = 1;
	return 1;
}