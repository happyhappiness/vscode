	encoded_len = strlen(challenge_64);
	challenge = xmalloc(encoded_len);
	decoded_len = EVP_DecodeBlock((unsigned char *)challenge,
				      (unsigned char *)challenge_64, encoded_len);
	if (decoded_len < 0)
		die("invalid challenge %s", challenge_64);
	if (!HMAC(EVP_md5(), pass, strlen(pass), (unsigned char *)challenge, decoded_len, hash, NULL))
		die("HMAC error");

	hex[32] = 0;
	for (i = 0; i < 16; i++) {
		hex[2 * i] = hexchar((hash[i] >> 4) & 0xf);
		hex[2 * i + 1] = hexchar(hash[i] & 0xf);
	}

	/* response: "<user> <digest in hex>" */
	response = xstrfmt("%s %s", user, hex);
	resp_len = strlen(response);

	response_64 = xmallocz(ENCODED_SIZE(resp_len));
	encoded_len = EVP_EncodeBlock((unsigned char *)response_64,
				      (unsigned char *)response, resp_len);
	if (encoded_len < 0)
		die("EVP_EncodeBlock error");
