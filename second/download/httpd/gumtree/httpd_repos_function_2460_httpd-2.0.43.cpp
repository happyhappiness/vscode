static
int addBinding(XML_Parser parser, PREFIX *prefix, const ATTRIBUTE_ID *attId, const XML_Char *uri, BINDING **bindingsPtr)
{
  BINDING *b;
  int len;
  for (len = 0; uri[len]; len++)
    ;
  if (namespaceSeparator)
    len++;
  if (freeBindingList) {
    b = freeBindingList;
    if (len > b->uriAlloc) {
      b->uri = REALLOC(b->uri, sizeof(XML_Char) * (len + EXPAND_SPARE));
      if (!b->uri)
	return 0;
      b->uriAlloc = len + EXPAND_SPARE;
    }
    freeBindingList = b->nextTagBinding;
  }
  else {
    b = MALLOC(sizeof(BINDING));
    if (!b)
      return 0;
    b->uri = MALLOC(sizeof(XML_Char) * (len + EXPAND_SPARE));
    if (!b->uri) {
      FREE(b);
      return 0;
    }
    b->uriAlloc = len + EXPAND_SPARE;
  }
  b->uriLen = len;
  memcpy(b->uri, uri, len * sizeof(XML_Char));
  if (namespaceSeparator)
    b->uri[len - 1] = namespaceSeparator;
  b->prefix = prefix;
  b->attId = attId;
  b->prevPrefixBinding = prefix->binding;
  if (*uri == XML_T('\0') && prefix == &dtd.defaultPrefix)
    prefix->binding = 0;
  else
    prefix->binding = b;
  b->nextTagBinding = *bindingsPtr;
  *bindingsPtr = b;
  if (startNamespaceDeclHandler)
    startNamespaceDeclHandler(handlerArg, prefix->name,
			      prefix->binding ? uri : 0);
  return 1;
}