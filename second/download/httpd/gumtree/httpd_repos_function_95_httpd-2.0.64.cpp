char *strdup (const char *str)
{
    char *dup;

    if (!(dup = (char *) malloc(strlen(str) + 1)))
	return NULL;
    dup = strcpy(dup, str);

    return dup;
}