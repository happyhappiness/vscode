static int count_loose(const unsigned char *sha1, const char *path, void *data)
{
	struct stat st;

	if (lstat(path, &st) || !S_ISREG(st.st_mode))
		loose_garbage(path);
	else {
		loose_size += on_disk_bytes(st);
		loose++;
		if (verbose && has_sha1_pack(sha1))
			packed_loose++;
	}
	return 0;
}