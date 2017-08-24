{
			wchar_t *full;
			full = __la_win_permissive_name_w(path);
			h = FindFirstFileW(full, &findData);
			free(full);
		}