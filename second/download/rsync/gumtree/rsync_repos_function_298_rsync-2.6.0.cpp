static char *string_area_strdup(struct string_area **ap, const char *src)
{
	char *dest = string_area_malloc(ap, strlen(src) + 1);
	return strcpy(dest, src);
}