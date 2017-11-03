static void replace_part (ENTER_STATE *state, size_t from, char *buf)
{
  /* Save the suffix */
  size_t savelen = state->lastchar - state->curpos;
  wchar_t *savebuf = NULL;

  if (savelen)
  {
    savebuf = safe_calloc (savelen, sizeof (wchar_t));
    memcpy (savebuf, state->wbuf + state->curpos, savelen * sizeof (wchar_t));
  }

  /* Convert to wide characters */
  state->curpos = my_mbstowcs (&state->wbuf, &state->wbuflen, from, buf);

  if (savelen)
  {
    /* Make space for suffix */
    if (state->curpos + savelen > state->wbuflen)
    {
      state->wbuflen = state->curpos + savelen;
      safe_realloc (&state->wbuf, state->wbuflen * sizeof (wchar_t));
    }

    /* Restore suffix */
    memcpy (state->wbuf + state->curpos, savebuf, savelen * sizeof (wchar_t));
    FREE (&savebuf);
  }

  state->lastchar = state->curpos + savelen;
}