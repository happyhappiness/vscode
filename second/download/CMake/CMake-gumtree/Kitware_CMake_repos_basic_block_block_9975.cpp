((base[0] == L'/' && base[1] == L'/' &&
	     base[2] == L'?' && base[3] == L'/' &&
	     (wcschr(base+4, L'*') || wcschr(base+4, L'?'))) ||
	    (!(base[0] == L'/' && base[1] == L'/' &&
	       base[2] == L'?' && base[3] == L'/') &&
	       (wcschr(base, L'*') || wcschr(base, L'?')))) {
		// It has a wildcard in it...
		// Separate the last element.
		p = wcsrchr(base, L'/');
		if (p != NULL) {
			*p = L'\0';
			tree_append(t, base, p - base);
			t->dirname_length = archive_strlen(&t->path);
			base = p + 1;
		}
		p = wcsrchr(t->full_path.s, L'\\');
		if (p != NULL) {
			*p = L'\0';
			t->full_path.length = wcslen(t->full_path.s);
			t->full_path_dir_length = archive_strlen(&t->full_path);
		}
	}