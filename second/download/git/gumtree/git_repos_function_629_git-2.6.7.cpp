static int write_tar_entry(struct archiver_args *args,
			   const unsigned char *sha1,
			   const char *path, size_t pathlen,
			   unsigned int mode)
{
	struct ustar_header header;
	struct strbuf ext_header = STRBUF_INIT;
	unsigned int old_mode = mode;
	unsigned long size;
	void *buffer;
	int err = 0;

	memset(&header, 0, sizeof(header));

	if (S_ISDIR(mode) || S_ISGITLINK(mode)) {
		*header.typeflag = TYPEFLAG_DIR;
		mode = (mode | 0777) & ~tar_umask;
	} else if (S_ISLNK(mode)) {
		*header.typeflag = TYPEFLAG_LNK;
		mode |= 0777;
	} else if (S_ISREG(mode)) {
		*header.typeflag = TYPEFLAG_REG;
		mode = (mode | ((mode & 0100) ? 0777 : 0666)) & ~tar_umask;
	} else {
		return error("unsupported file mode: 0%o (SHA1: %s)",
			     mode, sha1_to_hex(sha1));
	}
	if (pathlen > sizeof(header.name)) {
		size_t plen = get_path_prefix(path, pathlen,
					      sizeof(header.prefix));
		size_t rest = pathlen - plen - 1;
		if (plen > 0 && rest <= sizeof(header.name)) {
			memcpy(header.prefix, path, plen);
				memcpy(header.name, path + plen + 1, rest);
		} else {
			sprintf(header.name, "%s.data",
				sha1_to_hex(sha1));
			strbuf_append_ext_header(&ext_header, "path",
						 path, pathlen);
		}
	} else
		memcpy(header.name, path, pathlen);

	if (S_ISREG(mode) && !args->convert &&
	    sha1_object_info(sha1, &size) == OBJ_BLOB &&
	    size > big_file_threshold)
		buffer = NULL;
	else if (S_ISLNK(mode) || S_ISREG(mode)) {
		enum object_type type;
		buffer = sha1_file_to_archive(args, path, sha1, old_mode, &type, &size);
		if (!buffer)
			return error("cannot read %s", sha1_to_hex(sha1));
	} else {
		buffer = NULL;
		size = 0;
	}

	if (S_ISLNK(mode)) {
		if (size > sizeof(header.linkname)) {
			sprintf(header.linkname, "see %s.paxheader",
			        sha1_to_hex(sha1));
			strbuf_append_ext_header(&ext_header, "linkpath",
			                         buffer, size);
		} else
			memcpy(header.linkname, buffer, size);
	}

	prepare_header(args, &header, mode, size);

	if (ext_header.len > 0) {
		err = write_extended_header(args, sha1, ext_header.buf,
					    ext_header.len);
		if (err) {
			free(buffer);
			return err;
		}
	}
	strbuf_release(&ext_header);
	write_blocked(&header, sizeof(header));
	if (S_ISREG(mode) && size > 0) {
		if (buffer)
			write_blocked(buffer, size);
		else
			err = stream_blocked(sha1);
	}
	free(buffer);
	return err;
}