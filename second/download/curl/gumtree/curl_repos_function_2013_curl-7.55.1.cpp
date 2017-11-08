int curl_strequal(const char *first, const char *second)
{
  return Curl_strcasecompare(first, second);
}