int flush_write_file(int f)
{
	int ret = 0;
	char *bp = wf_writeBuf;

	while (wf_writeBufCnt > 0) {
		if ((ret = write(f, bp, wf_writeBufCnt)) < 0) {
			if (errno == EINTR)
				continue;
			return ret;
		}
		wf_writeBufCnt -= ret;
		bp += ret;
	}
	return ret;
}