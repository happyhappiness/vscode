{
	struct pax *pax;

	pax = (struct pax *)a->format_data;
	if (pax == NULL)
		return (ARCHIVE_OK);

	archive_string_free(&pax->pax_header);
	archive_string_free(&pax->sparse_map);
	archive_string_free(&pax->l_url_encoded_name);
	sparse_list_clear(pax);
	free(pax);
	a->format_data = NULL;
	return (ARCHIVE_OK);
}