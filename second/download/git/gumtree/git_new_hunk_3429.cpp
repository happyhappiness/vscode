
	fclose(io.input);
	if (io.io.wrerror)
		error("There were errors while writing %s (%s)",
		      path, strerror(io.io.wrerror));
	if (io.io.output && fclose(io.io.output))
		io.io.wrerror = error_errno("Failed to flush %s", path);

	if (hunk_no < 0) {
		if (output)
			unlink_or_warn(output);
		return error("Could not parse conflict hunks in %s", path);
	}
	if (io.io.wrerror)
		return -1;
	return hunk_no;
}

/*
 * Look at a cache entry at "i" and see if it is not conflicting,
 * conflicting and we are willing to handle, or conflicting and
 * we are unable to handle, and return the determination in *type.
 * Return the cache index to be looked at next, by skipping the
 * stages we have already looked at in this invocation of this
 * function.
