static void aquaero_submit_array (const char *type,
		const char *type_instance_prefix, double *value_array, int len)
{
	char type_instance[DATA_MAX_NAME_LEN];
	int i;

	for (i = 0; i < len; i++)
	{
		if (value_array[i] == AQ5_FLOAT_UNDEF)
			continue;

		snprintf (type_instance, sizeof (type_instance), "%s%d",
				type_instance_prefix, i + 1);
		aquaero_submit (type, type_instance, value_array[i]);
	}
}