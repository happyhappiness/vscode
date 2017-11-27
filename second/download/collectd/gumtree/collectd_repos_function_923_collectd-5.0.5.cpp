static int cna_setup_volume_usage (cfg_volume_usage_t *cvu) /* {{{ */
{
	if (cvu == NULL)
		return (EINVAL);

	if (cvu->query != NULL)
		return (0);

	cvu->query = na_elem_new ("volume-list-info");
	if (cvu->query == NULL)
	{
		ERROR ("netapp plugin: na_elem_new failed.");
		return (-1);
	}

	return (0);
}