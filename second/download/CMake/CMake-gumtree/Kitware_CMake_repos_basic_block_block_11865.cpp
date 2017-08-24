{
		if (build_pathname_utf16be(p, max, len, file->parent) != 0)
			return (-1);
		p[*len] = 0;
		p[*len + 1] = '/';
		*len += 2;
	}