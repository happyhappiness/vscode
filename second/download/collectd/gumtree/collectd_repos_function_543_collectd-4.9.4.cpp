int parse_values (char *buffer, value_list_t *vl, const data_set_t *ds)
{
	int i;
	char *dummy;
	char *ptr;
	char *saveptr;

	i = -1;
	dummy = buffer;
	saveptr = NULL;
	while ((ptr = strtok_r (dummy, ":", &saveptr)) != NULL)
	{
		dummy = NULL;

		if (i >= vl->values_len)
		{
			/* Make sure i is invalid. */
			i = vl->values_len + 1;
			break;
		}

		if (i == -1)
		{
			if (strcmp ("N", ptr) == 0)
				vl->time = time (NULL);
			else
				vl->time = (time_t) atoi (ptr);
		}
		else
		{
			if ((strcmp ("U", ptr) == 0) && (ds->ds[i].type == DS_TYPE_GAUGE))
				vl->values[i].gauge = NAN;
			else if (0 != parse_value (ptr, &vl->values[i], ds->ds[i].type))
				return -1;
		}

		i++;
	} /* while (strtok_r) */

	if ((ptr != NULL) || (i != vl->values_len))
		return (-1);
	return (0);
}