#if DEBUG

	{

		char buff[1024];

		if (len > sizeof(buff)-1)

			len = sizeof(buff)-1;

		memcpy(buff, s, len);

		buff[len] = 0;

		fprintf(stderr, "\tlen=%d:\"%s\"\n", len, buff);

	}
