static int sideband_demux(int in, int out, void *data)
{
	int *fd = data, ret;
#ifdef NO_PTHREADS
	close(fd[1]);
#endif
	ret = recv_sideband("send-pack", fd[0], out);
	close(out);
	return ret;
}