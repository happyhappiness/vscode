int
turbostat_init(void)
{
	struct stat sb;
	int ret;

	if (stat("/dev/cpu/0/msr", &sb)) {
		ERROR("turbostat plugin: Initialization failed: /dev/cpu/0/msr "
		      "does not exist while the CPU supports MSR. You may be "
		      "missing the corresponding kernel module, please try '# "
		      "modprobe msr'");
		return -1;
	}

	DO_OR_GOTO_ERR(check_permissions());

	DO_OR_GOTO_ERR(probe_cpu());

	DO_OR_GOTO_ERR(setup_all_buffers());

	plugin_register_read(PLUGIN_NAME, turbostat_read);

	return 0;
err:
	free_all_buffers();
	return ret;
}