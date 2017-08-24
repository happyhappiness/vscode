(a->mode & AE_IFMT) {
	default:
		/* POSIX requires that we fall through here. */
		/* FALLTHROUGH */
	case AE_IFREG:
		a->fd = open(a->name,
		    O_WRONLY | O_CREAT | O_EXCL | O_BINARY | O_CLOEXEC, mode);
		__archive_ensure_cloexec_flag(a->fd);
		r = (a->fd < 0);
		break;
	case AE_IFCHR:
#ifdef HAVE_MKNOD
		/* Note: we use AE_IFCHR for the case label, and
		 * S_IFCHR for the mknod() call.  This is correct.  */
		r = mknod(a->name, mode | S_IFCHR,
		    archive_entry_rdev(a->entry));
		break;
#else
		/* TODO: Find a better way to warn about our inability
		 * to restore a char device node. */
		return (EINVAL);
#endif /* HAVE_MKNOD */
	case AE_IFBLK:
#ifdef HAVE_MKNOD
		r = mknod(a->name, mode | S_IFBLK,
		    archive_entry_rdev(a->entry));
		break;
#else
		/* TODO: Find a better way to warn about our inability
		 * to restore a block device node. */
		return (EINVAL);
#endif /* HAVE_MKNOD */
	case AE_IFDIR:
		mode = (mode | MINIMUM_DIR_MODE) & MAXIMUM_DIR_MODE;
		r = mkdir(a->name, mode);
		if (r == 0) {
			/* Defer setting dir times. */
			a->deferred |= (a->todo & TODO_TIMES);
			a->todo &= ~TODO_TIMES;
			/* Never use an immediate chmod(). */
			/* We can't avoid the chmod() entirely if EXTRACT_PERM
			 * because of SysV SGID inheritance. */
			if ((mode != final_mode)
			    || (a->flags & ARCHIVE_EXTRACT_PERM))
				a->deferred |= (a->todo & TODO_MODE);
			a->todo &= ~TODO_MODE;
		}
		break;
	case AE_IFIFO:
#ifdef HAVE_MKFIFO
		r = mkfifo(a->name, mode);
		break;
#else
		/* TODO: Find a better way to warn about our inability
		 * to restore a fifo. */
		return (EINVAL);
#endif /* HAVE_MKFIFO */
	}