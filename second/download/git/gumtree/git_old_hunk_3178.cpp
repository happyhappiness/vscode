}

static void insert_one_record(struct shortlog *log,
			      const char *author,
			      const char *oneline)
{
	const char *dot3 = log->common_repo_prefix;
	char *buffer, *p;
	struct string_list_item *item;
	const char *mailbuf, *namebuf;
	size_t namelen, maillen;
	const char *eol;
	struct strbuf subject = STRBUF_INIT;
	struct strbuf namemailbuf = STRBUF_INIT;
	struct ident_split ident;

	if (split_ident_line(&ident, author, strlen(author)))
		return;

