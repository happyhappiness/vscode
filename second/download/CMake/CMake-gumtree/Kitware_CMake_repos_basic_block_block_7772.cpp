(len > b->uriAlloc) {
      XML_Char *temp = (XML_Char *)REALLOC(b->uri,
                          sizeof(XML_Char) * (len + EXPAND_SPARE));
      if (temp == NULL)
        return XML_ERROR_NO_MEMORY;
      b->uri = temp;
      b->uriAlloc = len + EXPAND_SPARE;
    }