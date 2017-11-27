static int cna_setup_wafl (cfg_wafl_t *cw) /* {{{ */
{
	na_elem_t *e;

	if (cw == NULL)
		return (EINVAL);

	if (cw->query != NULL)
		return (0);

	cw->query = na_elem_new("perf-object-get-instances");
	if (cw->query == NULL)
	{
		ERROR ("netapp plugin: na_elem_new failed.");
		return (-1);
	}
	na_child_add_string (cw->query, "objectname", "wafl");

	e = na_elem_new("counters");
	if (e == NULL)
	{
		na_elem_free (cw->query);
		cw->query = NULL;
		ERROR ("netapp plugin: na_elem_new failed.");
		return (-1);
	}
	na_child_add_string(e, "counter", "name_cache_hit");
	na_child_add_string(e, "counter", "name_cache_miss");
	na_child_add_string(e, "counter", "find_dir_hit");
	na_child_add_string(e, "counter", "find_dir_miss");
	na_child_add_string(e, "counter", "buf_hash_hit");
	na_child_add_string(e, "counter", "buf_hash_miss");
	na_child_add_string(e, "counter", "inode_cache_hit");
	na_child_add_string(e, "counter", "inode_cache_miss");

	na_child_add(cw->query, e);

	return (0);
}