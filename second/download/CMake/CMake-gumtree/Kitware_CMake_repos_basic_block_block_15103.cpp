{
		wn = _wcsdup(wnp);
		if (wn == NULL)
			return (-1);
		archive_wstring_ensure(&(a->_name_data), 4 + wcslen(wn) + 1);
		a->name = a->_name_data.s;
		/* Prepend "\\?\" */
		archive_wstrncpy(&(a->_name_data), L"\\\\?\\", 4);
		archive_wstrcat(&(a->_name_data), wn);
		free(wn);
		return (0);
	}