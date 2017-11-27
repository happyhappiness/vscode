static int cna_setup_disk (cfg_disk_t *cd) /* {{{ */
{
	na_elem_t *e;

	if (cd == NULL)
		return (EINVAL);

	if (cd->query != NULL)
		return (0);

	cd->query = na_elem_new ("perf-object-get-instances");
	if (cd->query == NULL)
	{
		ERROR ("netapp plugin: na_elem_new failed.");
		return (-1);
	}
	na_child_add_string (cd->query, "objectname", "disk");

	e = na_elem_new("counters");
	if (e == NULL)
	{
		na_elem_free (cd->query);
		cd->query = NULL;
		ERROR ("netapp plugin: na_elem_new failed.");
		return (-1);
	}
	na_child_add_string(e, "counter", "disk_busy");
	na_child_add_string(e, "counter", "base_for_disk_busy");
	na_child_add(cd->query, e);

	return (0);
}