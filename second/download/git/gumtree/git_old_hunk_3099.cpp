	} else {
		index += 8;
		return index + 20 * n;
	}
}

off_t nth_packed_object_offset(const struct packed_git *p, uint32_t n)
{
	const unsigned char *index = p->index_data;
	index += 4 * 256;
	if (p->index_version == 1) {
		return ntohl(*((uint32_t *)(index + 24 * n)));
