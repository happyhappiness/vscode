(fflags != NULL) {
		r = make_fflags_entry(a, writer, "flags", fflags);
		if (r < 0)
			return (r);
		r = make_fflags_entry(a, writer, "ext2", fflags);
		if (r < 0)
			return (r);
	}