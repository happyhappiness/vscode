static int write_part_values (char **ret_buffer, int *ret_buffer_len,
		const data_set_t *ds, const value_list_t *vl)
{
	part_values_t pv;
	int i;

	i = 6 + (9 * vl->values_len);
	if (*ret_buffer_len < i)
		return (-1);
	*ret_buffer_len -= i;

	pv.head = (part_header_t *) *ret_buffer;
	pv.num_values = (uint16_t *) (pv.head + 1);
	pv.values_types = (uint8_t *) (pv.num_values + 1);
	pv.values = (value_t *) (pv.values_types + vl->values_len);
	*ret_buffer = (void *) (pv.values + vl->values_len);

	pv.head->type = htons (TYPE_VALUES);
	pv.head->length = htons (6 + (9 * vl->values_len));
	*pv.num_values = htons ((uint16_t) vl->values_len);
	
	for (i = 0; i < vl->values_len; i++)
	{
		if (ds->ds[i].type == DS_TYPE_COUNTER)
		{
			pv.values_types[i] = DS_TYPE_COUNTER;
			pv.values[i].counter = htonll (vl->values[i].counter);
		}
		else
		{
			pv.values_types[i] = DS_TYPE_GAUGE;
			pv.values[i].gauge = vl->values[i].gauge;
		}
	} /* for (values) */

	return (0);
}