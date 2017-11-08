static int in_commit_list(const struct commit_list *want, struct commit *c)
{
	for (; want; want = want->next)
		if (!oidcmp(&want->item->object.oid, &c->object.oid))
			return 1;
	return 0;
}