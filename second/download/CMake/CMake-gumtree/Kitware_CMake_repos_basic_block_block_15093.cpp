{
		wchar_t *full;
		full = __la_win_permissive_name_w(path);
		h = CreateFileW(full, 0, 0, NULL,
		    OPEN_EXISTING, flag, NULL);
		free(full);
	}