static enum XML_Error
prologProcessor(XML_Parser parser,
		const char *s,
		const char *end,
		const char **nextPtr)
{
  const char *next;
  int tok = XmlPrologTok(encoding, s, end, &next);
  return doProlog(parser, encoding, s, end, tok, next, nextPtr);
}