		|| (pack_size + 60 + len) < pack_size)
		cycle_packfile();

	sha1file_checkpoint(pack_file, &checkpoint);
	offset = checkpoint.offset;

	hdrlen = xsnprintf((char *)out_buf, out_sz, "blob %" PRIuMAX, len) + 1;

	git_SHA1_Init(&c);
	git_SHA1_Update(&c, out_buf, hdrlen);

	crc32_begin(pack_file);

	git_deflate_init(&s, pack_compression_level);

	hdrlen = encode_in_pack_object_header(out_buf, out_sz, OBJ_BLOB, len);

	s.next_out = out_buf + hdrlen;
	s.avail_out = out_sz - hdrlen;

	while (status != Z_STREAM_END) {
		if (0 < len && !s.avail_in) {
