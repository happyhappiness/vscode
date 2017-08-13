{
		char buff[1024];
		if (len > (int)(sizeof(buff)-1))
			len = (int)(sizeof(buff)-1);
		strncpy(buff, s, len);
		buff[len] = 0;
		fprintf(stderr, "\tlen=%d:\"%s\"\n", len, buff);
	}