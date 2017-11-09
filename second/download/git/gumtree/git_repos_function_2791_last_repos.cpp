static inline const char *strintern(const char *string)
{
	return memintern(string, strlen(string));
}