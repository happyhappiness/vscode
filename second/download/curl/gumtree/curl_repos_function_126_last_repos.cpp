static void startElement(void *userData, const XML_Char *name,
                         const XML_Char **atts)
{
  struct ParserStruct *state = (struct ParserStruct *) userData;
  state->tags++;
  state->depth++;

  /* Get a clean slate for reading in character data. */
  free(state->characters.memory);
  state->characters.memory = NULL;
  state->characters.size = 0;
}