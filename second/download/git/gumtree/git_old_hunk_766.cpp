	default:
		die("BUG: trailer.c: unhandled type %d", type);
	}
	return 0;
}

static const char *token_from_item(struct arg_item *item, char *tok)
{
	if (item->conf.key)
		return item->conf.key;
	if (tok)
		return tok;
