void grep_source_clear_data(struct grep_source *gs)
{
	switch (gs->type) {
	case GREP_SOURCE_FILE:
	case GREP_SOURCE_OID:
	case GREP_SOURCE_SUBMODULE:
		FREE_AND_NULL(gs->buf);
		gs->size = 0;
		break;
	case GREP_SOURCE_BUF:
		/* leave user-provided buf intact */
		break;
	}
}