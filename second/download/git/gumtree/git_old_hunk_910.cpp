
	/*
	 * Capture output to output buffer and check the return code from the
	 * child process.  A '0' indicates a hit, a '1' indicates no hit and
	 * anything else is an error.
	 */
	status = capture_command(&cp, &w->out, 0);
	if (status && (status != 1)) {
		/* flush the buffer */
		write_or_die(1, w->out.buf, w->out.len);
		die("process for submodule '%s' failed with exit code: %d",
		    gs->name, status);
	}

	/* invert the return code to make a hit equal to 1 */
	return !status;
}

/*
 * Prep grep structures for a submodule grep
