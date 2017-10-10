			s->size = size;
			s->should_free = 1;
		}
	}
	else {
		enum object_type type;
		if (size_only) {
			type = sha1_object_info(s->sha1, &s->size);
			if (type < 0)
				die("unable to read %s", sha1_to_hex(s->sha1));
		} else {
			s->data = read_sha1_file(s->sha1, &type, &s->size);
			if (!s->data)
				die("unable to read %s", sha1_to_hex(s->sha1));
			s->should_free = 1;
		}
	}
	return 0;
}

void diff_free_filespec_blob(struct diff_filespec *s)
{
