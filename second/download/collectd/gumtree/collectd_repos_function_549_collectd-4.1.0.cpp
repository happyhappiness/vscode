static int parse_part_values (void **ret_buffer, int *ret_buffer_len,
		value_t **ret_values, int *ret_num_values)
{
	char *buffer = *ret_buffer;
	int   buffer_len = *ret_buffer_len;
	part_values_t pv;
	int   i;

	uint16_t h_length;
	uint16_t h_type;
	uint16_t h_num;

	if (buffer_len < (15))
	{
		DEBUG ("network plugin: packet is too short: buffer_len = %i",
				buffer_len);
		return (-1);
	}

	pv.head = (part_header_t *) buffer;
	h_length = ntohs (pv.head->length);
	h_type = ntohs (pv.head->type);

	assert (h_type == TYPE_VALUES);

	pv.num_values = (uint16_t *) (pv.head + 1);
	h_num = ntohs (*pv.num_values);

	if (h_num != ((h_length - 6) / 9))
	{
		DEBUG ("`length' and `num of values' don't match");
		return (-1);
	}

	pv.values_types = (uint8_t *) (pv.num_values + 1);
	pv.values = (value_t *) (pv.values_types + h_num);

	for (i = 0; i < h_num; i++)
		if (pv.values_types[i] == DS_TYPE_COUNTER)
			pv.values[i].counter = ntohll (pv.values[i].counter);

	*ret_buffer     = (void *) (pv.values + h_num);
	*ret_buffer_len = buffer_len - h_length;
	*ret_num_values = h_num;
	*ret_values     = pv.values;

	return (0);
}