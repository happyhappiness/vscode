 * The per-object header is a pretty dense thing, which is
 *  - first byte: low four bits are "size", then three bits of "type",
 *    and the high bit is "size continues".
 *  - each byte afterwards: low seven bits are size continuation,
 *    with the high bit being "size continues"
 */
int encode_in_pack_object_header(unsigned char *hdr, int hdr_len,
				 enum object_type type, uintmax_t size)
{
	int n = 1;
	unsigned char c;

	if (type < OBJ_COMMIT || type > OBJ_REF_DELTA)
		die("bad type %d", type);

	c = (type << 4) | (size & 15);
	size >>= 4;
	while (size) {
		if (n == hdr_len)
			die("object size is too enormous to format");
		*hdr++ = c | 0x80;
		c = size & 0x7f;
		size >>= 7;
		n++;
	}
	*hdr = c;
	return n;
}

struct sha1file *create_tmp_packfile(char **pack_tmp_name)
{
	struct strbuf tmpname = STRBUF_INIT;
	int fd;

	fd = odb_mkstemp(&tmpname, "pack/tmp_pack_XXXXXX");
	*pack_tmp_name = strbuf_detach(&tmpname, NULL);
	return sha1fd(fd, *pack_tmp_name);
}

void finish_tmp_packfile(struct strbuf *name_buffer,
			 const char *pack_tmp_name,
			 struct pack_idx_entry **written_list,
