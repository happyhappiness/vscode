{
#endif
			t->entry_fd = open_on_current_dir(t,
			    tree_current_access_path(t), flags);
			__archive_ensure_cloexec_flag(t->entry_fd);
#if defined(O_NOATIME)
			/*
			 * When we did open the file with O_NOATIME flag,
			 * if successful, set 1 to t->restore_time.noatime
			 * not to restore an atime of the file later.
			 * if failed by EPERM, retry it without O_NOATIME flag.
			 */
			if (flags & O_NOATIME) {
				if (t->entry_fd >= 0)
					t->restore_time.noatime = 1;
				else if (errno == EPERM) {
					flags &= ~O_NOATIME;
					continue;
				}
			}
		}