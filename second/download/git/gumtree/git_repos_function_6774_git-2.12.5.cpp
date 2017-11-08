static void
internal_function
re_string_construct_common (const char *str, int len, re_string_t *pstr,
			    RE_TRANSLATE_TYPE trans, int icase,
			    const re_dfa_t *dfa)
{
  pstr->raw_mbs = (const unsigned char *) str;
  pstr->len = len;
  pstr->raw_len = len;
  pstr->trans = trans;
  pstr->icase = icase ? 1 : 0;
  pstr->mbs_allocated = (trans != NULL || icase);
  pstr->mb_cur_max = dfa->mb_cur_max;
  pstr->is_utf8 = dfa->is_utf8;
  pstr->map_notascii = dfa->map_notascii;
  pstr->stop = pstr->len;
  pstr->raw_stop = pstr->stop;
}