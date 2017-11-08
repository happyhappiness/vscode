struct branch *branch_get(const char *name)
{
	struct branch *ret;

	read_config();
	if (!name || !*name || !strcmp(name, "HEAD"))
		ret = current_branch;
	else
		ret = make_branch(name, 0);
	if (ret && ret->remote_name) {
		ret->remote = remote_get(ret->remote_name);
		if (ret->merge_nr) {
			int i;
			ret->merge = xcalloc(ret->merge_nr, sizeof(*ret->merge));
			for (i = 0; i < ret->merge_nr; i++) {
				ret->merge[i] = xcalloc(1, sizeof(**ret->merge));
				ret->merge[i]->src = xstrdup(ret->merge_name[i]);
				if (remote_find_tracking(ret->remote, ret->merge[i])
				    && !strcmp(ret->remote_name, "."))
					ret->merge[i]->dst = xstrdup(ret->merge_name[i]);
			}
		}
	}
	return ret;
}