static int mic_shutdown (void)
{
	if (mic_handle)
		MicCloseAPI(&mic_handle);
	mic_handle = NULL;

	return (0);
}