(elementType->prefix) {
    binding = elementType->prefix->binding;
    if (!binding)
      return XML_ERROR_UNBOUND_PREFIX;
    localPart = tagNamePtr->str;
    while (*localPart++ != XML_T(ASCII_COLON))
      ;
  }
  else if (dtd->defaultPrefix.binding) {
    binding = dtd->defaultPrefix.binding;
    localPart = tagNamePtr->str;
  }
  else
    return XML_ERROR_NONE;