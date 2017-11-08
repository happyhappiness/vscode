static void unpack_all(void)
{
	int i;
	struct progress *progress = NULL;
	struct pack_header *hdr = fill(sizeof(struct pack_header));

	nr_objects = ntohl(hdr->hdr_entries);

	if (ntohl(hdr->hdr_signature) != PACK_SIGNATURE)
		die("bad pack file");
	if (!pack_version_ok(hdr->hdr_version))
		die("unknown pack file version %"PRIu32,
			ntohl(hdr->hdr_version));
	use(sizeof(struct pack_header));

	if (!quiet)
		progress = start_progress(_("Unpacking objects"), nr_objects);
	obj_list = xcalloc(nr_objects, sizeof(*obj_list));
	for (i = 0; i < nr_objects; i++) {
		unpack_one(i);
		display_progress(progress, i + 1);
	}
	stop_progress(&progress);

	if (delta_list)
		die("unresolved deltas left after unpacking");
}