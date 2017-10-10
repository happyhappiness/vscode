
	git_SHA1_Init(&c);
	git_SHA1_Update(&c, out_buf, hdrlen);

	crc32_begin(pack_file);

	memset(&s, 0, sizeof(s));
	git_deflate_init(&s, pack_compression_level);

	hdrlen = encode_in_pack_object_header(OBJ_BLOB, len, out_buf);
	if (out_sz <= hdrlen)
		die("impossibly large object header");

