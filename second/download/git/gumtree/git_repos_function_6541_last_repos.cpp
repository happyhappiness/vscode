void fast_export_note(const char *committish, const char *dataref)
{
	printf("N %s %s\n", dataref, committish);
}