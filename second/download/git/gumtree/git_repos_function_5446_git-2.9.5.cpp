static int update_clone_get_next_task(struct child_process *child,
				      struct strbuf *err,
				      void *suc_cb,
				      void **void_task_cb)
{
	struct submodule_update_clone *suc = suc_cb;

	for (; suc->current < suc->list.nr; suc->current++) {
		const struct cache_entry *ce = suc->list.entries[suc->current];
		if (prepare_to_clone_next_submodule(ce, child, suc, err)) {
			suc->current++;
			return 1;
		}
	}
	return 0;
}