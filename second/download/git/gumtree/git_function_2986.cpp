int index_path(unsigned char *sha1, const char *path, struct stat *st, unsigned flags)
{
	int fd;
	struct strbuf sb = STRBUF_INIT;

	switch (st->st_mode & S_IFMT) {
	case S_IFREG:
		fd = open(path, O_RDONLY);
		if (fd < 0)
			return error("open(\"%s\"): %s", path,
				     strerror(errno));
		if (index_fd(sha1, fd, st, OBJ_BLOB, path, flags) < 0)
			return error("%s: failed to insert into database",
				     path);
		break;
	case S_IFLNK:
		if (strbuf_readlink(&sb, path, st->st_size)) {
			char *errstr = strerror(errno);
			return error("readlink(\"%s\"): %s", path,
			             errstr);
		}
		if (!(flags & HASH_WRITE_OBJECT))
			hash_sha1_file(sb.buf, sb.len, blob_type, sha1);
		else if (write_sha1_file(sb.buf, sb.len, blob_type, sha1))
			return error("%s: failed to insert into database",
				     path);
		strbuf_release(&sb);
		break;
	case S_IFDIR:
		return resolve_gitlink_ref(path, "HEAD", sha1);
	default:
		return error("%s: unsupported file type", path);
	}
	return 0;
}