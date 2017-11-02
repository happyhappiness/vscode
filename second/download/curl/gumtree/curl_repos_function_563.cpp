static CURLcode create_node(void)
{
  data_key = aprintf("%s:%d", "dummy", 0);
  if (!data_key)
    return CURLE_OUT_OF_MEMORY;

  data_node = calloc(1, sizeof(struct Curl_dns_entry));
  if (!data_node)
    return CURLE_OUT_OF_MEMORY;

  data_node->addr = fake_ai();
  if (!data_node->addr)
    return CURLE_OUT_OF_MEMORY;

  return CURLE_OK;
}