static void terminate(void)
{
    while (modList)
	dlclose(modList);
}