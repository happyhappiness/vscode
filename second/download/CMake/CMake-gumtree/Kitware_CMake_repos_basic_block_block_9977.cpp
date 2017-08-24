(t->stack != NULL) {
		/* If there's an open dir, get the next entry from there. */
		if (t->d != INVALID_HANDLE_VALUE) {
			r = tree_dir_next_windows(t, NULL);
			if (r == 0)
				continue;
			return (r);
		}

		if (t->stack->flags & needsFirstVisit) {
			wchar_t *d = t->stack->name.s;
			t->stack->flags &= ~needsFirstVisit;
			if (!(d[0] == L'/' && d[1] == L'/' &&
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
			/* Top stack item needs a regular visit. */
			t->current = t->stack;
			tree_append(t, t->stack->name.s,
			    archive_strlen(&(t->stack->name)));
			//t->dirname_length = t->path_length;
			//tree_pop(t);
			t->stack->flags &= ~needsFirstVisit;
			return (t->visit_type = TREE_REGULAR);
		} else if (t->stack->flags & needsDescent) {
			/* Top stack item is dir to descend into. */
			t->current = t->stack;
			tree_append(t, t->stack->name.s,
			    archive_strlen(&(t->stack->name)));
			t->stack->flags &= ~needsDescent;
			r = tree_descent(t);
			if (r != 0) {
				tree_pop(t);
				t->visit_type = r;
			} else
				t->visit_type = TREE_POSTDESCENT;
			return (t->visit_type);
		} else if (t->stack->flags & needsOpen) {
			t->stack->flags &= ~needsOpen;
			r = tree_dir_next_windows(t, L"*");
			if (r == 0)
				continue;
			return (r);
		} else if (t->stack->flags & needsAscent) {
		        /* Top stack item is dir and we're done with it. */
			r = tree_ascend(t);
			tree_pop(t);
			t->visit_type = r != 0 ? r : TREE_POSTASCENT;
			return (t->visit_type);
		} else {
			/* Top item on stack is dead. */
			tree_pop(t);
			t->flags &= ~hasLstat;
			t->flags &= ~hasStat;
		}
	}