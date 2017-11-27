static int thermal_init (void)
{
	int ret = -1;

	if (!force_procfs && access (dirname_sysfs, R_OK | X_OK) == 0) {
		ret = plugin_register_read ("thermal", thermal_sysfs_read);
	} else if (access (dirname_procfs, R_OK | X_OK) == 0) {
		ret = plugin_register_read ("thermal", thermal_procfs_read);
	}

	if (!ret) {
		vl_temp_template.values_len = 1;
		vl_temp_template.interval = interval_g;
		sstrncpy (vl_temp_template.host, hostname_g,
			sizeof(vl_temp_template.host));
		sstrncpy (vl_temp_template.plugin, "thermal",
			sizeof(vl_temp_template.plugin));
		sstrncpy (vl_temp_template.type_instance, "temperature",
			sizeof(vl_temp_template.type_instance));

		vl_state_template = vl_temp_template;
		sstrncpy (vl_state_template.type_instance, "cooling_state",
			sizeof(vl_state_template.type_instance));
	}

	return ret;
}