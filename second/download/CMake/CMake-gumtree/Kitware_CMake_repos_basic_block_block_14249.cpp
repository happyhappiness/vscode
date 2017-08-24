{
		char *p;

		p = tp;
		archive_random(p, ep - p);
		while (p < ep) {
			int d = *((unsigned char *)p) % sizeof(num);
			*p++ = num[d];
		}
		fd = open(temp_name.s, O_CREAT | O_EXCL | O_RDWR | O_CLOEXEC,
			  0600);
	}