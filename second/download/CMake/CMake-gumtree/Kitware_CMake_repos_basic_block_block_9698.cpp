(errno == EPERM) {
					flags &= ~O_NOATIME;
					continue;
				}