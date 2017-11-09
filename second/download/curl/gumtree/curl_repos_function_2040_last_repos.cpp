int curl_strnequal(const char *first, const char *second, size_t max)
{
  return Curl_strncasecompare(first, second, max);
}