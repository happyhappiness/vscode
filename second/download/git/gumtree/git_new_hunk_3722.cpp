		size = buf.len;
	}
	if (write_in_full(fd, blob, size) != size)
		die_errno("unable to write temp-file");
	close_tempfile(&temp->tempfile);
	temp->name = get_tempfile_path(&temp->tempfile);
	oid_to_hex_r(temp->hex, oid);
	xsnprintf(temp->mode, sizeof(temp->mode), "%06o", mode);
	strbuf_release(&buf);
	strbuf_release(&template);
	free(path_dup);
}

