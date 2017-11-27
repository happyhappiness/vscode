static void nfs2_read_kstat (kstat_t *ksp, char *inst)
{
	unsigned long long values[18];

	values[0] = get_kstat_value (ksp, "null");
	values[1] = get_kstat_value (ksp, "getattr");
	values[2] = get_kstat_value (ksp, "setattr");
	values[3] = get_kstat_value (ksp, "root");
	values[4] = get_kstat_value (ksp, "lookup");
	values[5] = get_kstat_value (ksp, "readlink");
	values[6] = get_kstat_value (ksp, "read");
	values[7] = get_kstat_value (ksp, "wrcache");
	values[8] = get_kstat_value (ksp, "write");
	values[9] = get_kstat_value (ksp, "create");
	values[10] = get_kstat_value (ksp, "remove");
	values[11] = get_kstat_value (ksp, "rename");
	values[12] = get_kstat_value (ksp, "link");
	values[13] = get_kstat_value (ksp, "symlink");
	values[14] = get_kstat_value (ksp, "mkdir");
	values[15] = get_kstat_value (ksp, "rmdir");
	values[16] = get_kstat_value (ksp, "readdir");
	values[17] = get_kstat_value (ksp, "statfs");

	nfs2_procedures_submit (values, inst);
}