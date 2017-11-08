int write_file(int f,char *buf,size_t len)
{
	int ret = 0;

	while (len > 0) {
		int r1;
		if (sparse_files) {
			int len1 = MIN(len, SPARSE_WRITE_SIZE);
			r1 = write_sparse(f, buf, len1);
		} else {
			if (!wf_writeBuf) {
				wf_writeBufSize = MAX_MAP_SIZE;
				wf_writeBufCnt  = 0;
				wf_writeBuf = new_array(char, MAX_MAP_SIZE);
				if (!wf_writeBuf)
					out_of_memory("write_file");
			}
			r1 = MIN(len, wf_writeBufSize - wf_writeBufCnt);
			if (r1) {
				memcpy(wf_writeBuf + wf_writeBufCnt, buf, r1);
				wf_writeBufCnt += r1;
			}
			if (wf_writeBufCnt == wf_writeBufSize) {
				if (flush_write_file(f) < 0)
					return -1;
				if (!r1 && len)
					continue;
			}
		}
		if (r1 <= 0) {
			if (ret > 0) return ret;
			return r1;
		}
		len -= r1;
		buf += r1;
		ret += r1;
	}
	return ret;
}