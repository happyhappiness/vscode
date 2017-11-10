size_t fwrite_null(char *ptr, size_t eltsize, size_t nmemb, void *strbuf)
{
	return eltsize * nmemb;
}