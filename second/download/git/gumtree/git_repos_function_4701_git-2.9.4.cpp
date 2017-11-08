static void prefix_patch(struct patch *p)
{
	if (!prefix || p->is_toplevel_relative)
		return;
	prefix_one(&p->new_name);
	prefix_one(&p->old_name);
}