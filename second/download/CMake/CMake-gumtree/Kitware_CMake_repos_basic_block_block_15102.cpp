{
				/* Now, match patterns such as
				 * "\\server-name\share-name\" */
				wn = _wcsdup(wnp);
				if (wn == NULL)
					return (-1);
				archive_wstring_ensure(&(a->_name_data),
					8 + wcslen(wn) + 1);
				a->name = a->_name_data.s;
				/* Prepend "\\?\UNC\" */
				archive_wstrncpy(&(a->_name_data),
					L"\\\\?\\UNC\\", 8);
				archive_wstrcat(&(a->_name_data), wn+2);
				free(wn);
				return (0);
			}