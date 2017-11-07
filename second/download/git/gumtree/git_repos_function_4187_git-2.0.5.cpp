static void prefix_patches(struct patch *p)
{
	if (!prefix || p->is_toplevel_relative)
		return;
	for ( ; p; p = p->next) {
		prefix_one(&p->new_name);
		prefix_one(&p->old_name);
	}
}