void XmlPrologStateInit(PROLOG_STATE *state)
{
  state->handler = prolog0;
#ifdef XML_DTD
  state->documentEntity = 1;
  state->includeLevel = 0;
#endif /* XML_DTD */
}