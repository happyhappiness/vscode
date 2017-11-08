static int sideband_demux(int in, int out, void *data)
{
	int *xd = data;
	int ret;

	sigchain_push(SIGPIPE, SIG_IGN);
	ret = recv_sideband("fetch-pack", xd[0], out);
	close(out);
	sigchain_pop(SIGPIPE);
	return ret;
}