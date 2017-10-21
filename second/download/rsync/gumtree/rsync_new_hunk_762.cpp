	static int residue;
	static char *buf;
	int n;

	if (!buf) {
		buf = new_array(char, CHUNK_SIZE);
		if (!buf)
			out_of_memory("simple_recv_token");
	}

	if (residue == 0) {
		int i = read_int(f);
		if (i <= 0)
			return i;
		residue = i;
	}

	*data = buf;
	n = MIN(CHUNK_SIZE,residue);
	residue -= n;
