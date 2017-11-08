void grep_source_init(struct grep_source *gs, enum grep_source_type type,
		      const char *name, const char *path,
		      const void *identifier)
{
	gs->type = type;
	gs->name = name ? xstrdup(name) : NULL;
	gs->path = path ? xstrdup(path) : NULL;
	gs->buf = NULL;
	gs->size = 0;
	gs->driver = NULL;

	switch (type) {
	case GREP_SOURCE_FILE:
		gs->identifier = xstrdup(identifier);
		break;
	case GREP_SOURCE_SHA1:
		gs->identifier = xmalloc(20);
		hashcpy(gs->identifier, identifier);
		break;
	case GREP_SOURCE_BUF:
		gs->identifier = NULL;
	}
}