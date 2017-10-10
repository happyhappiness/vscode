			unsigned long size;
			char *buf = gfi_unpack_entry(oe, &size);
			parse_from_commit(b, buf, size);
			free(buf);
		} else
			parse_from_existing(b);
	} else if (!get_sha1(from, b->sha1)) {
		parse_from_existing(b);
		if (is_null_sha1(b->sha1))
			b->delete = 1;
	}
	else
		die("Invalid ref name or SHA1 expression: %s", from);

	read_next_command();
	return 1;
}
