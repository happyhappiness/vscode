#define ondisk_cache_entry_size(len) align_flex_name(ondisk_cache_entry,len)
#define ondisk_cache_entry_extended_size(len) align_flex_name(ondisk_cache_entry_extended,len)
#define ondisk_ce_size(ce) (((ce)->ce_flags & CE_EXTENDED) ? \
			    ondisk_cache_entry_extended_size(ce_namelen(ce)) : \
			    ondisk_cache_entry_size(ce_namelen(ce)))

static int verify_hdr(struct cache_header *hdr, unsigned long size)
{
	git_SHA_CTX c;
	unsigned char sha1[20];
	int hdr_version;

	if (hdr->hdr_signature != htonl(CACHE_SIGNATURE))
		return error("bad signature");
	hdr_version = ntohl(hdr->hdr_version);
	if (hdr_version < INDEX_FORMAT_LB || INDEX_FORMAT_UB < hdr_version)
		return error("bad index version %d", hdr_version);
	git_SHA1_Init(&c);
	git_SHA1_Update(&c, hdr, size - 20);
	git_SHA1_Final(sha1, &c);
	if (hashcmp(sha1, (unsigned char *)hdr + size - 20))
		return error("bad index file sha1 signature");
	return 0;
