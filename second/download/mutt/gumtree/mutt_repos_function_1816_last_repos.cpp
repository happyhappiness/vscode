int mutt_label_complete (char *buffer, size_t len, int numtabs)
{
  char *pt = buffer;
  int spaces; /* keep track of the number of leading spaces on the line */

  if (!Context || !Context->label_hash)
    return 0;

  SKIPWS (buffer);
  spaces = buffer - pt;

  /* first TAB. Collect all the matches */
  if (numtabs == 1)
  {
    struct hash_elem *entry;
    struct hash_walk_state state;

    Num_matched = 0;
    strfcpy (User_typed, buffer, sizeof (User_typed));
    memset (Matches, 0, Matches_listsize);
    memset (Completed, 0, sizeof (Completed));
    memset (&state, 0, sizeof(state));
    while ((entry = hash_walk(Context->label_hash, &state)))
      candidate (Completed, User_typed, entry->key.strkey, sizeof (Completed));
    matches_ensure_morespace (Num_matched);
    qsort(Matches, Num_matched, sizeof(char *), (sort_t *) mutt_strcasecmp);
    Matches[Num_matched++] = User_typed;

    /* All matches are stored. Longest non-ambiguous string is ""
     * i.e. dont change 'buffer'. Fake successful return this time */
    if (User_typed[0] == 0)
      return 1;
  }

  if (Completed[0] == 0 && User_typed[0])
    return 0;

   /* Num_matched will _always_ be atleast 1 since the initial
    * user-typed string is always stored */
  if (numtabs == 1 && Num_matched == 2)
    snprintf(Completed, sizeof(Completed), "%s", Matches[0]);
  else if (numtabs > 1 && Num_matched > 2)
    /* cycle thru all the matches */
    snprintf(Completed, sizeof(Completed), "%s", 
             Matches[(numtabs - 2) % Num_matched]);

  /* return the completed label */
  strncpy (buffer, Completed, len - spaces);

  return 1;
}