{
		fullname = __la_win_permissive_name_w(path);
		r = _wrmdir(fullname);
		free(fullname);
	}