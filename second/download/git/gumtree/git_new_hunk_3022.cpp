
	if (has_loose_object(sha1))
		return 0;
	buf = read_packed_sha1(sha1, &type, &len);
	if (!buf)
		return error("cannot read sha1_file for %s", sha1_to_hex(sha1));
	hdrlen = xsnprintf(hdr, sizeof(hdr), "%s %lu", typename(type), len) + 1;
	ret = write_loose_object(sha1, hdr, hdrlen, buf, len, mtime);
	free(buf);

	return ret;
}

