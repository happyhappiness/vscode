(*p == kMainStreamsInfo) {
		if (read_StreamsInfo(a, &(zip->si)) < 0)
			return (-1);
		if ((p = header_bytes(a, 1)) == NULL)
			return (-1);
	}