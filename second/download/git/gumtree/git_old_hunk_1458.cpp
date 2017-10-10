		}
		/*
		 * FALL THROUGH
		 * If the identifier is non-NULL (in the submodule case) it
		 * will be a SHA1 that needs to be copied.
		 */
	case GREP_SOURCE_SHA1:
		gs->identifier = xmalloc(20);
		hashcpy(gs->identifier, identifier);
		break;
	case GREP_SOURCE_BUF:
		gs->identifier = NULL;
		break;
	}
}

void grep_source_clear(struct grep_source *gs)
{
	free(gs->name);
	gs->name = NULL;
	free(gs->path);
	gs->path = NULL;
	free(gs->identifier);
	gs->identifier = NULL;
	grep_source_clear_data(gs);
}

void grep_source_clear_data(struct grep_source *gs)
{
	switch (gs->type) {
	case GREP_SOURCE_FILE:
	case GREP_SOURCE_SHA1:
	case GREP_SOURCE_SUBMODULE:
		free(gs->buf);
		gs->buf = NULL;
		gs->size = 0;
		break;
	case GREP_SOURCE_BUF:
		/* leave user-provided buf intact */
		break;
	}
}

static int grep_source_load_sha1(struct grep_source *gs)
{
	enum object_type type;

	grep_read_lock();
	gs->buf = read_sha1_file(gs->identifier, &type, &gs->size);
	grep_read_unlock();

	if (!gs->buf)
		return error(_("'%s': unable to read %s"),
			     gs->name,
			     sha1_to_hex(gs->identifier));
	return 0;
}

static int grep_source_load_file(struct grep_source *gs)
{
	const char *filename = gs->identifier;
