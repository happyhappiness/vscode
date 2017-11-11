static char *write_text(char *s, const apr_text *t)
{
    for (; t; t = t->next) {
	apr_size_t len = strlen(t->text);
	memcpy(s, t->text, len);
	s += len;
    }
    return s;
}