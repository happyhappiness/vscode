	for (i = 0; i < 16; i++) {
		hex[2 * i] = hexchar((hash[i] >> 4) & 0xf);
		hex[2 * i + 1] = hexchar(hash[i] & 0xf);
	}

	/* response: "<user> <digest in hex>" */
	resp_len = strlen(user) + 1 + strlen(hex) + 1;
	response = xmalloc(resp_len);
	sprintf(response, "%s %s", user, hex);

	response_64 = xmalloc(ENCODED_SIZE(resp_len) + 1);
	encoded_len = EVP_EncodeBlock((unsigned char *)response_64,
				      (unsigned char *)response, resp_len);
	if (encoded_len < 0)
		die("EVP_EncodeBlock error");
