{
		char c = header->checksum[i];
		if (c != ' ' && c != '\0' && (c < '0' || c > '7'))
			return 0;
	}