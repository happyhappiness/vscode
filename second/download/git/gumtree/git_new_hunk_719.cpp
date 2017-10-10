	case GREP_SOURCE_FILE:
		return grep_source_load_file(gs);
	case GREP_SOURCE_SHA1:
		return grep_source_load_sha1(gs);
	case GREP_SOURCE_BUF:
		return gs->buf ? 0 : -1;
	case GREP_SOURCE_SUBMODULE:
		break;
	}
	die("BUG: invalid grep_source type to load");
}

void grep_source_load_driver(struct grep_source *gs)
{
	if (gs->driver)
		return;
