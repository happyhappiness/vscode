static ATTRIBUTE_ID *
getAttributeId(XML_Parser parser, const ENCODING *enc,
               const char *start, const char *end)
{
  DTD * const dtd = _dtd;  /* save one level of indirection */
  ATTRIBUTE_ID *id;
  const XML_Char *name;
  if (!poolAppendChar(&dtd->pool, XML_T('\0')))
    return NULL;
  name = poolStoreString(&dtd->pool, enc, start, end);
  if (!name)
    return NULL;
  /* skip quotation mark - its storage will be re-used (like in name[-1]) */
  ++name;
  id = (ATTRIBUTE_ID *)lookup(&dtd->attributeIds, name, sizeof(ATTRIBUTE_ID));
  if (!id)
    return NULL;
  if (id->name != name)
    poolDiscard(&dtd->pool);
  else {
    poolFinish(&dtd->pool);
    if (!ns)
      ;
    else if (name[0] == XML_T('x')
        && name[1] == XML_T('m')
        && name[2] == XML_T('l')
        && name[3] == XML_T('n')
        && name[4] == XML_T('s')
        && (name[5] == XML_T('\0') || name[5] == XML_T(':'))) {
      if (name[5] == XML_T('\0'))
        id->prefix = &dtd->defaultPrefix;
      else
        id->prefix = (PREFIX *)lookup(&dtd->prefixes, name + 6, sizeof(PREFIX));
      id->xmlns = XML_TRUE;
    }
    else {
      int i;
      for (i = 0; name[i]; i++) {
        /* attributes without prefix are *not* in the default namespace */
        if (name[i] == XML_T(':')) {
          int j;
          for (j = 0; j < i; j++) {
            if (!poolAppendChar(&dtd->pool, name[j]))
              return NULL;
          }
          if (!poolAppendChar(&dtd->pool, XML_T('\0')))
            return NULL;
          id->prefix = (PREFIX *)lookup(&dtd->prefixes, poolStart(&dtd->pool),
                                        sizeof(PREFIX));
          if (id->prefix->name == poolStart(&dtd->pool))
            poolFinish(&dtd->pool);
          else
            poolDiscard(&dtd->pool);
          break;
        }
      }
    }
  }
  return id;
}