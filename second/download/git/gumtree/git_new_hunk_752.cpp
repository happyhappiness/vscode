		return -1;
	}

	return 0;
}

void read_gitfile_error_die(int error_code, const char *path, const char *dir)
{
	switch (error_code) {
	case READ_GITFILE_ERR_STAT_FAILED:
	case READ_GITFILE_ERR_NOT_A_FILE:
		/* non-fatal; follow return path */
		break;
	case READ_GITFILE_ERR_OPEN_FAILED:
		die_errno("Error opening '%s'", path);
	case READ_GITFILE_ERR_TOO_LARGE:
		die("Too large to be a .git file: '%s'", path);
	case READ_GITFILE_ERR_READ_FAILED:
		die("Error reading %s", path);
	case READ_GITFILE_ERR_INVALID_FORMAT:
		die("Invalid gitfile format: %s", path);
	case READ_GITFILE_ERR_NO_PATH:
		die("No path in gitfile: %s", path);
	case READ_GITFILE_ERR_NOT_A_REPO:
		die("Not a git repository: %s", dir);
	default:
		die("BUG: unknown error code");
	}
}

/*
 * Try to read the location of the git directory from the .git file,
 * return path to git directory if found.
 *
 * On failure, if return_error_code is not NULL, return_error_code
 * will be set to an error code and NULL will be returned. If
