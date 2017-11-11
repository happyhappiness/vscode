static int
defineAttribute(ELEMENT_TYPE *type, ATTRIBUTE_ID *attId, int isCdata,
		int isId, const XML_Char *value, XML_Parser parser)
{
  DEFAULT_ATTRIBUTE *att;
  if (value || isId) {
    /* The handling of default attributes gets messed up if we have
       a default which duplicates a non-default. */
    int i;
    for (i = 0; i < type->nDefaultAtts; i++)
      if (attId == type->defaultAtts[i].id)
	return 1;
    if (isId && !type->idAtt && !attId->xmlns)
      type->idAtt = attId;
  }
  if (type->nDefaultAtts == type->allocDefaultAtts) {
    if (type->allocDefaultAtts == 0) {
      type->allocDefaultAtts = 8;
      type->defaultAtts = MALLOC(type->allocDefaultAtts*sizeof(DEFAULT_ATTRIBUTE));
    }
    else {
      type->allocDefaultAtts *= 2;
      type->defaultAtts = REALLOC(type->defaultAtts,
				  type->allocDefaultAtts*sizeof(DEFAULT_ATTRIBUTE));
    }
    if (!type->defaultAtts)
      return 0;
  }
  att = type->defaultAtts + type->nDefaultAtts;
  att->id = attId;
  att->value = value;
  att->isCdata = isCdata;
  if (!isCdata)
    attId->maybeTokenized = 1;
  type->nDefaultAtts += 1;
  return 1;
}