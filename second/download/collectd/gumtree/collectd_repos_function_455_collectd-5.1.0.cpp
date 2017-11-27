static int nfs_read_kstat (kstat_t *ksp, int nfs_version, char *inst,
		const char **proc_names, size_t proc_names_num)
{
	char plugin_instance[DATA_MAX_NAME_LEN];
	value_t values[proc_names_num];
	size_t i;

	if (ksp == NULL)
		return (EINVAL);

	ssnprintf (plugin_instance, sizeof (plugin_instance), "v%i%s",
			nfs_version, inst);

	kstat_read(kc, ksp, NULL);
	for (i = 0; i < proc_names_num; i++)
		values[i].counter = (derive_t) get_kstat_value (ksp, proc_names[i]);

	nfs_procedures_submit (plugin_instance, proc_names, values,
			proc_names_num);
}