static int parse_part_string (void **ret_buffer, int *ret_buffer_len,
		char *output, int output_len)
{
	char *buffer = *ret_buffer;
	int   buffer_len = *ret_buffer_len;
	part_string_t ps;

	uint16_t h_length;
	uint16_t h_type;

	DEBUG ("network plugin: parse_part_string: ret_buffer = %p;"
			" ret_buffer_len = %i; output = %p; output_len = %i;",
			*ret_buffer, *ret_buffer_len,
			(void *) output, output_len);

	ps.head = (part_header_t *) buffer;

	h_length = ntohs (ps.head->length);
	h_type = ntohs (ps.head->type);

	DEBUG ("network plugin: parse_part_string: length = %hu; type = %hu;",
			h_length, h_type);

	if (buffer_len < h_length)
	{
		DEBUG ("packet is too short");
		return (-1);
	}
	assert ((h_type == TYPE_HOST)
			|| (h_type == TYPE_PLUGIN)
			|| (h_type == TYPE_PLUGIN_INSTANCE)
			|| (h_type == TYPE_TYPE)
			|| (h_type == TYPE_TYPE_INSTANCE)
			|| (h_type == TYPE_MESSAGE));

	ps.value = buffer + 4;
	if (ps.value[h_length - 5] != '\0')
	{
		DEBUG ("String does not end with a nullbyte");
		return (-1);
	}

	if (output_len < (h_length - 4))
	{
		DEBUG ("output buffer is too small");
		return (-1);
	}
	strcpy (output, ps.value);

	DEBUG ("network plugin: parse_part_string: output = %s", output);

	*ret_buffer = (void *) (buffer + h_length);
	*ret_buffer_len = buffer_len - h_length;

	return (0);
}