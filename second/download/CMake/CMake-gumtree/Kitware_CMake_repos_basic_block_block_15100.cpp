(wnp[0] == L'\\') {
		wn = _wcsdup(wnp);
		if (wn == NULL)
			return (-1);
		archive_wstring_ensure(&(a->_name_data),
			4 + 2 + wcslen(wn) + 1);
		a->name = a->_name_data.s;
		/* Prepend "\\?\" and drive name. */
		archive_wstrncpy(&(a->_name_data), L"\\\\?\\", 4);
		archive_wstrncat(&(a->_name_data), wsp, 2);
		archive_wstrcat(&(a->_name_data), wn);
		free(wsp);
		free(wn);
		return (0);
	}