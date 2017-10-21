	}
	free(dont);
	free(fname);
}

/* non-compressing recv token */
static int32 simple_recv_token(int f, char **data)
{
	static int32 residue;
	static char *buf;
	int32 n;

	if (!buf) {
		buf = new_array(char, CHUNK_SIZE);
		if (!buf)
			out_of_memory("simple_recv_token");
	}

	if (residue == 0) {
		int32 i = read_int(f);
		if (i <= 0)
			return i;
		residue = i;
	}

	*data = buf;
