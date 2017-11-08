static void push_header_arg(struct argv_array *args, struct pack_header *hdr)
{
	argv_array_pushf(args, "--pack_header=%"PRIu32",%"PRIu32,
			ntohl(hdr->hdr_version), ntohl(hdr->hdr_entries));
}