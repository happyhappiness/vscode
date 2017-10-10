	if (gs->buf)
		return 0;

	switch (gs->type) {
	case GREP_SOURCE_FILE:
		return grep_source_load_file(gs);
	case GREP_SOURCE_OID:
		return grep_source_load_oid(gs);
	case GREP_SOURCE_BUF:
		return gs->buf ? 0 : -1;
	case GREP_SOURCE_SUBMODULE:
		break;
	}
	die("BUG: invalid grep_source type to load");
