{
    uri += i - 1;
    *uri = namespaceSeparator;  /* replace null terminator */
    memcpy(uri + 1, binding->prefix->name, prefixLen * sizeof(XML_Char));
  }