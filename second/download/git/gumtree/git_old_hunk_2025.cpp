
		for (;;) {
			readlen = read_istream(stream, buf, sizeof(buf));
			if (readlen <= 0)
				break;
			crc = crc32(crc, buf, readlen);

			zstream.next_in = buf;
			zstream.avail_in = readlen;
			result = git_deflate(&zstream, 0);
			if (result != Z_OK)
				die("deflate error (%d)", result);
