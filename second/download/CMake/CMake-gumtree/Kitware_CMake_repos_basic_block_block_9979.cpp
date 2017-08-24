(!(d[0] == L'/' && d[1] == L'/' &&
			      d[2] == L'?' && d[3] == L'/') &&
			    (wcschr(d, L'*') || wcschr(d, L'?'))) {
				r = tree_dir_next_windows(t, d);
				if (r == 0)
					continue;
				return (r);
			} else {
				HANDLE h = FindFirstFileW(d, &t->_findData);
				if (h == INVALID_HANDLE_VALUE) {
					la_dosmaperr(GetLastError());
					t->tree_errno = errno;
					t->visit_type = TREE_ERROR_DIR;
					return (t->visit_type);
				}
				t->findData = &t->_findData;
				FindClose(h);
			}