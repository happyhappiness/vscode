	default:
		die("BUG: trailer.c: unhandled type %d", type);
	}
	return 0;
}

static void ensure_configured(void)
{
	if (configured)
		return;

	/* Default config must be setup first */
	git_config(git_trailer_default_config, NULL);
	git_config(git_trailer_config, NULL);
	configured = 1;
}

static const char *token_from_item(struct arg_item *item, char *tok)
{
	if (item->conf.key)
		return item->conf.key;
	if (tok)
		return tok;
