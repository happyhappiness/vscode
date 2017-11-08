void clean_getout(struct OperationConfig *config)
{
  struct getout *next;
  struct getout *node = config->url_list;

  while(node) {
    next = node->next;
    Curl_safefree(node->url);
    Curl_safefree(node->outfile);
    Curl_safefree(node->infile);
    Curl_safefree(node);
    node = next;
  }
  config->url_list = NULL;
}