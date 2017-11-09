static int add_graft_decoration(const struct commit_graft *graft, void *cb_data)
{
	struct commit *commit = lookup_commit(&graft->oid);
	if (!commit)
		return 0;
	add_name_decoration(DECORATION_GRAFTED, "grafted", &commit->object);
	return 0;
}