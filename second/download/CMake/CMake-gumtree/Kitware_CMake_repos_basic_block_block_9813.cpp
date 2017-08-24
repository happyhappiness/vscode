{
#if defined(USE_READDIR_R)
		size_t dirent_size;
#endif

#if defined(HAVE_FDOPENDIR)
		t->d = fdopendir(tree_dup(t->working_dir_fd));
#else /* HAVE_FDOPENDIR */
		if (tree_enter_working_dir(t) == 0) {
			t->d = opendir(".");
#if HAVE_DIRFD || defined(dirfd)
			__archive_ensure_cloexec_flag(dirfd(t->d));
#endif
		}
#endif /* HAVE_FDOPENDIR */
		if (t->d == NULL) {
			r = tree_ascend(t); /* Undo "chdir" */
			tree_pop(t);
			t->tree_errno = errno;
			t->visit_type = r != 0 ? r : TREE_ERROR_DIR;
			return (t->visit_type);
		}
#if defined(USE_READDIR_R)
		dirent_size = offsetof(struct dirent, d_name) +
		  t->filesystem_table[t->current->filesystem_id].name_max + 1;
		if (t->dirent == NULL || t->dirent_allocated < dirent_size) {
			free(t->dirent);
			t->dirent = malloc(dirent_size);
			if (t->dirent == NULL) {
				closedir(t->d);
				t->d = INVALID_DIR_HANDLE;
				(void)tree_ascend(t);
				tree_pop(t);
				t->tree_errno = ENOMEM;
				t->visit_type = TREE_ERROR_DIR;
				return (t->visit_type);
			}
			t->dirent_allocated = dirent_size;
		}
#endif /* USE_READDIR_R */
	}