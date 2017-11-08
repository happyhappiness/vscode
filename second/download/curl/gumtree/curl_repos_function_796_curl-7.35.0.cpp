static void easysrc_free(void)
{
  curl_slist_free_all(easysrc_decl);
  easysrc_decl = NULL;
  curl_slist_free_all(easysrc_data);
  easysrc_data = NULL;
  curl_slist_free_all(easysrc_code);
  easysrc_code = NULL;
  curl_slist_free_all(easysrc_toohard);
  easysrc_toohard = NULL;
  curl_slist_free_all(easysrc_clean);
  easysrc_clean = NULL;
}