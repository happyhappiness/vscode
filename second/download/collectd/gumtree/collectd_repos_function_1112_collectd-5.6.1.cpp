static void cna_handle_volume_sis_saved (const host_config_t *host, /* {{{ */
		data_volume_usage_t *v, na_elem_t *sis)
{
	uint64_t saved;

	if (na_elem_child(sis, "sis-info"))
		sis = na_elem_child(sis, "sis-info");

	saved = na_child_get_uint64(sis, "compress-saved", UINT64_MAX);
	if (saved != UINT64_MAX) {
		v->compress_saved = saved;
		v->flags |= HAVE_VOLUME_USAGE_COMPRESS_SAVED;
	}

	saved = na_child_get_uint64(sis, "dedup-saved", UINT64_MAX);
	if (saved != UINT64_MAX) {
		v->dedup_saved = saved;
		v->flags |= HAVE_VOLUME_USAGE_DEDUP_SAVED;
	}
}