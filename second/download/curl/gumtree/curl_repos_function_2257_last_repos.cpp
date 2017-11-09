CURLcode curl_global_init(long flags)
{
  return global_init(flags, TRUE);
}