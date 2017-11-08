int write_file(int f,char *buf,size_t len)
{
	int ret = 0;

	if (!sparse_files) {
		return write(f,buf,len);
	}

	while (len>0) {
		int len1 = MIN(len, SPARSE_WRITE_SIZE);
		int r1 = write_sparse(f, buf, len1);
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