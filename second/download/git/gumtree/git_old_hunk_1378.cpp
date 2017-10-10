		/* We don't take any non-flag arguments now.. Maybe some day */
		usage(unpack_usage);
	}
	git_SHA1_Init(&ctx);
	unpack_all();
	git_SHA1_Update(&ctx, buffer, offset);
	git_SHA1_Final(sha1, &ctx);
	if (strict)
		write_rest();
	if (hashcmp(fill(20), sha1))
		die("final sha1 did not match");
	use(20);

	/* Write the last part of the buffer to stdout */
	while (len) {
		int ret = xwrite(1, buffer + offset, len);
		if (ret <= 0)
			break;
