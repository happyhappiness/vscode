static void parse_pack_header(void)
{
	struct pack_header *hdr = fill(sizeof(struct pack_header));

	/* Header consistency check */
	if (hdr->hdr_signature != htonl(PACK_SIGNATURE))
		die(_("pack signature mismatch"));
	if (!pack_version_ok(hdr->hdr_version))
		die(_("pack version %"PRIu32" unsupported"),
			ntohl(hdr->hdr_version));

	nr_objects = ntohl(hdr->hdr_entries);
	use(sizeof(struct pack_header));
}