	}
	return fd;
}

static int warn_if_unremovable(const char *op, const char *file, int rc)
{
	if (rc < 0) {
		int err = errno;
		if (ENOENT != err) {
			warning("unable to %s %s: %s",
				op, file, strerror(errno));
			errno = err;
		}
	}
	return rc;
}

int unlink_or_warn(const char *file)
{
	return warn_if_unremovable("unlink", file, unlink(file));
}

int rmdir_or_warn(const char *file)
