static bool field_enabled (curl_stats_t *s, size_t offset)
{
	return *(bool *)((char *)s + offset);
}