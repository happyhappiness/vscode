static void copy_section(local_vars *psectionDest, local_vars *psectionSource)
{
	int count = LOCAL_STRING_COUNT();
	char **strings = (char**)psectionDest;

	memcpy(psectionDest, psectionSource, sizeof psectionDest[0]);
	while (count--) {
		if (strings[count] && !(strings[count] = strdup(strings[count])))
			out_of_memory("copy_section");
	}
}