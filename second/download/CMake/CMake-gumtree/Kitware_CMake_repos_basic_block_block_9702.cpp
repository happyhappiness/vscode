((t->flags & needsRestoreTimes) != 0 &&
		    t->restore_time.noatime == 0)
			flags |= O_NOATIME