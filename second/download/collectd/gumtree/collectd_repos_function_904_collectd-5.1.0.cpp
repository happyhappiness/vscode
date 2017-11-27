static void free_cfg_disk (cfg_disk_t *cfg_disk) /* {{{ */
{
	if (cfg_disk == NULL)
		return;

	if (cfg_disk->query != NULL)
		na_elem_free (cfg_disk->query);

	free_disk (cfg_disk->disks);
	sfree (cfg_disk);
}