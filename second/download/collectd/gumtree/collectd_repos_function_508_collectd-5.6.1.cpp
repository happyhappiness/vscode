static void nfs_submit_fields (int nfs_version, const char *instance,
		char **fields, size_t fields_num, const char **proc_names)
{
	char plugin_instance[DATA_MAX_NAME_LEN];
	value_t values[fields_num];

	ssnprintf (plugin_instance, sizeof (plugin_instance), "v%i%s",
			nfs_version, instance);

	for (size_t i = 0; i < fields_num; i++)
		(void) parse_value (fields[i], &values[i], DS_TYPE_DERIVE);

	nfs_procedures_submit (plugin_instance, proc_names, values,
			fields_num);
}