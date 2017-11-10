static ATTRIBUTE_ID *
getAttributeId(XML_Parser parser, const ENCODING *enc, const char *start, const char *end)
{
  ATTRIBUTE_ID *id;
  const XML_Char *name;
  if (!poolAppendChar(&dtd.pool, XML_T('\0')))
    return 0;
  name = poolStoreString(&dtd.pool, enc, start, end);
  if (!name)
    return 0;
  ++name;
  id = (ATTRIBUTE_ID *)lookup(&dtd.attributeIds, name, sizeof(ATTRIBUTE_ID));
  if (!id)
    return 0;
  if (id->name != name)
    poolDiscard(&dtd.pool);
  else {
    poolFinish(&dtd.pool);
    if (!ns)
      ;
    else if (name[0] == 'x'
	&& name[1] == 'm'
	&& name[2] == 'l'
	&& name[3] == 'n'
	&& name[4] == 's'
	&& (name[5] == XML_T('\0') || name[5] == XML_T(':'))) {
      if (name[5] == '\0')
	id->prefix = &dtd.defaultPrefix;
      else
	id->prefix = (PREFIX *)lookup(&dtd.prefixes, name + 6, sizeof(PREFIX));
      id->xmlns = 1;
    }
    else {
      int i;
      for (i = 0; name[i]; i++) {
	if (name[i] == XML_T(':')) {
	  int j;
	  for (j = 0; j < i; j++) {
	    if (!poolAppendChar(&dtd.pool, name[j]))
	      return 0;
	  }
	  if (!poolAppendChar(&dtd.pool, XML_T('\0')))
	    return 0;
	  id->prefix = (PREFIX *)lookup(&dtd.prefixes, poolStart(&dtd.pool), sizeof(PREFIX));
	  if (id->prefix->name == poolStart(&dtd.pool))
	    poolFinish(&dtd.pool);
	  else
	    poolDiscard(&dtd.pool);
	  break;
	}
      }
    }
  }
  return id;
}