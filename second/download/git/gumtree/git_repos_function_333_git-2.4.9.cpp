static void remove_temporary_sharedindex(void)
{
	if (temporary_sharedindex) {
		unlink_or_warn(temporary_sharedindex);
		free(temporary_sharedindex);
		temporary_sharedindex = NULL;
	}
}