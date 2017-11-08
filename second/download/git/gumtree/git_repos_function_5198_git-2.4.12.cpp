static int add_known_remote(struct remote *remote, void *cb_data)
{
	struct known_remotes *all = cb_data;
	struct known_remote *r;

	if (!strcmp(all->to_delete->name, remote->name))
		return 0;

	r = xmalloc(sizeof(*r));
	r->remote = remote;
	r->next = all->list;
	all->list = r;
	return 0;
}