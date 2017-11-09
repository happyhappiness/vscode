static void
internal_function
init_word_char (re_dfa_t *dfa)
{
  int i, j, ch;
  dfa->word_ops_used = 1;
  for (i = 0, ch = 0; i < BITSET_WORDS; ++i)
    for (j = 0; j < BITSET_WORD_BITS; ++j, ++ch)
      if (isalnum (ch) || ch == '_')
	dfa->word_char[i] |= (bitset_word_t) 1 << j;
}