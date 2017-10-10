			s->should_free = 1;
		}
	}
	else {
		enum object_type type;
		if (size_only || (flags & CHECK_BINARY)) {
			type = sha1_object_info(s->sha1, &s->size);
			if (type < 0)
				die("unable to read %s", sha1_to_hex(s->sha1));
			if (size_only)
				return 0;
			if (s->size > big_file_threshold && s->is_binary == -1) {
				s->is_binary = 1;
				return 0;
			}
		}
		s->data = read_sha1_file(s->sha1, &type, &s->size);
		if (!s->data)
			die("unable to read %s", sha1_to_hex(s->sha1));
		s->should_free = 1;
	}
	return 0;
}

void diff_free_filespec_blob(struct diff_filespec *s)
