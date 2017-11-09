static void easysrc_free(void)
{
  slist_wc_free_all(easysrc_decl);
  easysrc_decl = NULL;
  slist_wc_free_all(easysrc_data);
  easysrc_data = NULL;
  slist_wc_free_all(easysrc_code);
  easysrc_code = NULL;
  slist_wc_free_all(easysrc_toohard);
  easysrc_toohard = NULL;
  slist_wc_free_all(easysrc_clean);
  easysrc_clean = NULL;
}