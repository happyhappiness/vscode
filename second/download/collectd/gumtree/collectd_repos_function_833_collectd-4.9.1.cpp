static void free_cfg_volume_perf (cfg_volume_perf_t *cvp) /* {{{ */
{
	data_volume_perf_t *data;

	if (cvp == NULL)
		return;

	/* Free the ignorelists */
	ignorelist_free (cvp->il_octets);
	ignorelist_free (cvp->il_operations);
	ignorelist_free (cvp->il_latency);

	/* Free the linked list of volumes */
	data = cvp->volumes;
	while (data != NULL)
	{
		data_volume_perf_t *next = data->next;
		sfree (data->name);
		sfree (data);
		data = next;
	}

	if (cvp->query != NULL)
		na_elem_free (cvp->query);

	sfree (cvp);
}