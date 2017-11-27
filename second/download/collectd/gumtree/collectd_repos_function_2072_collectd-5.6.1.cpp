static void enable_field (curl_stats_t *s, size_t offset)
{
	*(bool *)((char *)s + offset) = true;
}