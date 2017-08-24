(t->entry_fd >= 0)
					t->restore_time.noatime = 1;
				else if (errno == EPERM) {
					flags &= ~O_NOATIME;
					continue;
				}