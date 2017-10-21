{
	static int residue;
	static char *buf;
	int n;

	if (!buf) {
		buf = (char *)malloc(CHUNK_SIZE);
		if (!buf) out_of_memory("simple_recv_token");
	}

	if (residue == 0) {
		int i = read_int(f);
		if (i <= 0) return i;
