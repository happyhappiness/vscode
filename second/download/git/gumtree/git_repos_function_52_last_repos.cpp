off_t write_pack_header(struct sha1file *f, uint32_t nr_entries)
{
	struct pack_header hdr;

	hdr.hdr_signature = htonl(PACK_SIGNATURE);
	hdr.hdr_version = htonl(PACK_VERSION);
	hdr.hdr_entries = htonl(nr_entries);
	sha1write(f, &hdr, sizeof(hdr));
	return sizeof(hdr);
}