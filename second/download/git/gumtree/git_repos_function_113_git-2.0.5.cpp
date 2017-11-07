static size_t userformat_want_item(struct strbuf *sb, const char *placeholder,
				   void *context)
{
	struct userformat_want *w = context;

	if (*placeholder == '+' || *placeholder == '-' || *placeholder == ' ')
		placeholder++;

	switch (*placeholder) {
	case 'N':
		w->notes = 1;
		break;
	}
	return 0;
}