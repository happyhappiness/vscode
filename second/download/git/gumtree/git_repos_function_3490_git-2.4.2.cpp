static void set_merge(struct branch *ret)
{
	char *ref;
	unsigned char sha1[20];
	int i;

	ret->merge = xcalloc(ret->merge_nr, sizeof(*ret->merge));
	for (i = 0; i < ret->merge_nr; i++) {
		ret->merge[i] = xcalloc(1, sizeof(**ret->merge));
		ret->merge[i]->src = xstrdup(ret->merge_name[i]);
		if (!remote_find_tracking(ret->remote, ret->merge[i]) ||
		    strcmp(ret->remote_name, "."))
			continue;
		if (dwim_ref(ret->merge_name[i], strlen(ret->merge_name[i]),
			     sha1, &ref) == 1)
			ret->merge[i]->dst = ref;
		else
			ret->merge[i]->dst = xstrdup(ret->merge_name[i]);
	}
}