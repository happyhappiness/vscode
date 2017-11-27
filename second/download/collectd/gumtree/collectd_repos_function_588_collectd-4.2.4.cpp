static int write_part_string (char **ret_buffer, int *ret_buffer_len,
		int type, const char *str, int str_len)
{
	part_string_t ps;
	int len;

	len = 4 + str_len + 1;
	if (*ret_buffer_len < len)
		return (-1);
	*ret_buffer_len -= len;

	ps.head = (part_header_t *) *ret_buffer;
	ps.value = (char *) (ps.head + 1);

	ps.head->type = htons ((uint16_t) type);
	ps.head->length = htons ((uint16_t) str_len + 5);
	if (str_len > 0)
		memcpy (ps.value, str, str_len);
	ps.value[str_len] = '\0';
	*ret_buffer = (void *) (ps.value + (str_len + 1));

	return (0);
}