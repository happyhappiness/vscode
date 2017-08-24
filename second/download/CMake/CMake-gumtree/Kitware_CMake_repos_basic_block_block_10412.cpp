{
		/* "begin-base64 " */
		while (len-nl > 0) {
			if (!base64[*b++])
				return (0);
			--len;
		}
		b += nl;

		if (avail >= 5 && memcmp(b, "====\n", 5) == 0)
			return (firstline+40);
		if (avail >= 6 && memcmp(b, "====\r\n", 6) == 0)
			return (firstline+40);
		if (avail > 0 && base64[*b])
			return (firstline+30);
	}