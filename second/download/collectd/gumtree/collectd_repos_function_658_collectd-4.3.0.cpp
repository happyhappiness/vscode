static int parse_part_number (void **ret_buffer, int *ret_buffer_len,
		uint64_t *value)
{
	part_number_t pn;
	uint16_t len;

	pn.head = (part_header_t *) *ret_buffer;
	pn.value = (uint64_t *) (pn.head + 1);

	len = ntohs (pn.head->length);
	if (len != 12)
		return (-1);
	if (len > *ret_buffer_len)
		return (-1);
	*value = ntohll (*pn.value);

	*ret_buffer = (void *) (pn.value + 1);
	*ret_buffer_len -= len;

	return (0);
}