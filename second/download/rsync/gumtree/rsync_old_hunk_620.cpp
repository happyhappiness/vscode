	if (!users || !*users) return "";

	gen_challenge(addr, challenge);
	
	base64_encode(challenge, 16, b64_challenge);

	io_printf(fd,"%s%s\n", leader, b64_challenge);

	if (!read_line(fd, line, sizeof(line)-1)) {
		return NULL;
	}

	memset(user, 0, sizeof(user));
	memset(pass, 0, sizeof(pass));

