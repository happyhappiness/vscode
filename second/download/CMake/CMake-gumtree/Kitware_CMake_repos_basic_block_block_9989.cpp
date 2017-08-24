{
			struct archive_wstring pt;

			archive_string_init(&pt);
			archive_wstring_ensure(&pt,
			    archive_strlen(&(t->full_path))
			      + 2 + wcslen(pattern));
			archive_wstring_copy(&pt, &(t->full_path));
			archive_wstrappend_wchar(&pt, L'\\');
			archive_wstrcat(&pt, pattern);
			t->d = FindFirstFileW(pt.s, &t->_findData);
			archive_wstring_free(&pt);
			if (t->d == INVALID_HANDLE_VALUE) {
				la_dosmaperr(GetLastError());
				t->tree_errno = errno;
				r = tree_ascend(t); /* Undo "chdir" */
				tree_pop(t);
				t->visit_type = r != 0 ? r : TREE_ERROR_DIR;
				return (t->visit_type);
			}
			t->findData = &t->_findData;
			pattern = NULL;
		}