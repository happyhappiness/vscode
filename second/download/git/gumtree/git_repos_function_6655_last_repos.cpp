static void winansi_exit(void)
{
	/* flush all streams */
	_flushall();

	/* signal console thread to exit */
	FlushFileBuffers(hwrite);
	DisconnectNamedPipe(hwrite);

	/* wait for console thread to copy remaining data */
	WaitForSingleObject(hthread, INFINITE);

	/* cleanup handles... */
	CloseHandle(hwrite);
	CloseHandle(hthread);
}