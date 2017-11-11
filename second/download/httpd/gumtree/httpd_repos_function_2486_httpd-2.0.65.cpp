static apr_size_t text_size(const apr_text *t)
{
    apr_size_t size = 0;

    for (; t; t = t->next)
	size += strlen(t->text);
    return size;
}