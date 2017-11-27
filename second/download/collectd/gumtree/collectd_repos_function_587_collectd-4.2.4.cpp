static int write_part_number (char **ret_buffer, int *ret_buffer_len,
		int type, uint64_t value)
{
	part_number_t pn;

	if (*ret_buffer_len < 12)
		return (-1);

	pn.head = (part_header_t *) *ret_buffer;
	pn.value = (uint64_t *) (pn.head + 1);

	pn.head->type = htons (type);
	pn.head->length = htons (12);
	*pn.value = htonll (value);

	*ret_buffer = (char *) (pn.value + 1);
	*ret_buffer_len -= 12;

	return (0);
}