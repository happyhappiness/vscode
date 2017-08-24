{
			r = errno;
#endif
			closedir(t->d);
			t->d = INVALID_DIR_HANDLE;
			if (r != 0) {
				t->tree_errno = r;
				t->visit_type = TREE_ERROR_DIR;
				return (t->visit_type);
			} else
				return (0);
		}