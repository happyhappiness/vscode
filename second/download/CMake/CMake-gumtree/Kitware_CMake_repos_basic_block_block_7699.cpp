{
    TAG *p;
    uri = (XML_Char *)MALLOC((n + EXPAND_SPARE) * sizeof(XML_Char));
    if (!uri)
      return XML_ERROR_NO_MEMORY;
    binding->uriAlloc = n + EXPAND_SPARE;
    memcpy(uri, binding->uri, binding->uriLen * sizeof(XML_Char));
    for (p = tagStack; p; p = p->parent)
      if (p->name.str == binding->uri)
        p->name.str = uri;
    FREE(binding->uri);
    binding->uri = uri;
  }