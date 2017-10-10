		return -1;
	}

	return 0;
}

/*
 * Try to read the location of the git directory from the .git file,
 * return path to git directory if found.
 *
 * On failure, if return_error_code is not NULL, return_error_code
 * will be set to an error code and NULL will be returned. If
