		return NULL;
	if (hide && !access(filename, F_OK) && set_hidden_flag(wfilename, 0)) {
		error("could not unhide %s", filename);
		return NULL;
	}
	file = _wfopen(wfilename, wotype);
	if (file && hide && set_hidden_flag(wfilename, 1))
		warning("could not mark '%s' as hidden.", filename);
	return file;
}

FILE *mingw_freopen (const char *filename, const char *otype, FILE *stream)
