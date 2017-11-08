int write_file(int f,char *buf,size_t len)
{
	int ret = 0;

	while (len>0) {
		int r1;
		if (sparse_files) {
			int len1 = MIN(len, SPARSE_WRITE_SIZE);
			r1 = write_sparse(f, buf, len1);
		} else {
			r1 = write(f, buf, len);
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