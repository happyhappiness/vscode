static void mimesetstate(mime_state *state, enum mimestate tok, void *ptr)
{
  state->state = tok;
  state->ptr = ptr;
  state->offset = 0;
}