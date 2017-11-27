static int
get_threads_on_core(unsigned int cpu)
{
	char path[80];
	FILE *filep;
	int sib1, sib2;
	int matches;
	char character;

	ssnprintf(path, sizeof(path), "/sys/devices/system/cpu/cpu%d/topology/thread_siblings_list", cpu);
	filep = fopen(path, "r");
	if (!filep) {
		ERROR("turbostat plugin: Failed to open '%s'", path);
		return -1;
	}
	/*
	 * file format:
	 * if a pair of number with a character between: 2 siblings (eg. 1-2, or 1,4)
	 * otherwinse 1 sibling (self).
	 */
	matches = fscanf(filep, "%d%c%d\n", &sib1, &character, &sib2);

	fclose(filep);

	if (matches == 3)
		return 2;
	else
		return 1;
}