static void cmc_web_match_free(web_match_t *wm) /* {{{ */
{
  if (wm == NULL)
    return;

  sfree(wm->regex);
  sfree(wm->type);
  sfree(wm->instance);
  match_destroy(wm->match);
  cmc_web_match_free(wm->next);
  sfree(wm);
}