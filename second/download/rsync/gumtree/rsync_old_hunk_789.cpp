	}
	free(dont);
	free(fname);
}

/* non-compressing recv token */
static int simple_recv_token(int f,char **data)
{
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
