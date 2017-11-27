static int nfs_submit_fields (int nfs_version, const char *instance,
		char **fields, size_t fields_num,
		const char **proc_names, size_t proc_names_num)
{
	char plugin_instance[DATA_MAX_NAME_LEN];
	value_t values[fields_num];
	size_t i;

	if (fields_num != proc_names_num)
	{
		WARNING ("nfs plugin: Wrong number of fields for "
				"NFSv%i %s statistics. Expected %zu, got %zu.",
				nfs_version, instance,
				proc_names_num, fields_num);
		return (EINVAL);
	}

	ssnprintf (plugin_instance, sizeof (plugin_instance), "v%i%s",
			nfs_version, instance);

	for (i = 0; i < proc_names_num; i++)
		(void) parse_value (fields[i], &values[i], DS_TYPE_DERIVE);

	nfs_procedures_submit (plugin_instance, proc_names, values,
			proc_names_num);

	return (0);
}