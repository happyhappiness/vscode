((critical_flags != 0)  &&  (set & critical_flags)) {
			le = current_fixup(a, a->name);
			if (le == NULL)
				return (ARCHIVE_FATAL);
			le->fixup |= TODO_FFLAGS;
			le->fflags_set = set;
			/* Store the mode if it's not already there. */
			if ((le->fixup & TODO_MODE) == 0)
				le->mode = mode;
		} else {
			r = set_fflags_platform(a, a->fd,
			    a->name, mode, set, clear);
			if (r != ARCHIVE_OK)
				return (r);
		}