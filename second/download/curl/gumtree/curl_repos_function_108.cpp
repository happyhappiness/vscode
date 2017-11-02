static void endElement(void *userData, const XML_Char *name)
{
  struct ParserStruct *state = (struct ParserStruct *) userData;
  state->depth--;

  printf("%5lu   %10lu   %s\n", state->depth, state->characters.size, name);
}