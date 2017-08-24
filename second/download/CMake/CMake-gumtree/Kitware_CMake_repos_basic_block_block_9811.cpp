{
				closedir(t->d);
				t->d = INVALID_DIR_HANDLE;
				(void)tree_ascend(t);
				tree_pop(t);
				t->tree_errno = ENOMEM;
				t->visit_type = TREE_ERROR_DIR;
				return (t->visit_type);
			}