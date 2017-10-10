}

static void insert_one_record(struct shortlog *log,
			      const char *author,
			      const char *oneline)
{
	struct string_list_item *item;
	const char *mailbuf, *namebuf;
	size_t namelen, maillen;
	struct strbuf namemailbuf = STRBUF_INIT;
	struct ident_split ident;

	if (split_ident_line(&ident, author, strlen(author)))
		return;

