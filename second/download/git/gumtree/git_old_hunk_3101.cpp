	} else {
		unsigned off64_nr = 0;
		struct {
			unsigned char sha1[20];
			uint32_t crc;
			uint32_t off;
		} *entries = xmalloc(nr * sizeof(entries[0]));
		for (i = 0; i < nr; i++)
			if (fread(entries[i].sha1, 20, 1, stdin) != 1)
				die("unable to read sha1 %u/%u", i, nr);
		for (i = 0; i < nr; i++)
			if (fread(&entries[i].crc, 4, 1, stdin) != 1)
				die("unable to read crc %u/%u", i, nr);
