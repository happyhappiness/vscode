	}

	/* response: "<user> <digest in hex>" */
	response = xstrfmt("%s %s", user, hex);
	resp_len = strlen(response) + 1;

	response_64 = xmallocz(ENCODED_SIZE(resp_len));
	encoded_len = EVP_EncodeBlock((unsigned char *)response_64,
				      (unsigned char *)response, resp_len);
	if (encoded_len < 0)
		die("EVP_EncodeBlock error");
	return (char *)response_64;
}

#else

static char *cram(const char *challenge_64, const char *user, const char *pass)
