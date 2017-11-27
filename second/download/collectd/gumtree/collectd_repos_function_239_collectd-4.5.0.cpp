static value_t csnmp_value_list_to_value (struct variable_list *vl, int type,
    double scale, double shift)
{
  value_t ret;
  uint64_t temp = 0;
  int defined = 1;

  if ((vl->type == ASN_INTEGER)
      || (vl->type == ASN_UINTEGER)
      || (vl->type == ASN_COUNTER)
#ifdef ASN_TIMETICKS
      || (vl->type == ASN_TIMETICKS)
#endif
      || (vl->type == ASN_GAUGE))
  {
    temp = (uint32_t) *vl->val.integer;
    DEBUG ("snmp plugin: Parsed int32 value is %"PRIu64".", temp);
  }
  else if (vl->type == ASN_COUNTER64)
  {
    temp = (uint32_t) vl->val.counter64->high;
    temp = temp << 32;
    temp += (uint32_t) vl->val.counter64->low;
    DEBUG ("snmp plugin: Parsed int64 value is %"PRIu64".", temp);
  }
  else if (vl->type == ASN_OCTET_STR)
  {
    /* We'll handle this later.. */
  }
  else
  {
    WARNING ("snmp plugin: I don't know the ASN type `%i'", (int) vl->type);
    defined = 0;
  }

  if (vl->type == ASN_OCTET_STR)
  {
    char *string;
    char *endptr;

    string = (char *) vl->val.string;
    endptr = NULL;

    if (string != NULL)
    {
      if (type == DS_TYPE_COUNTER)
	ret.counter = (counter_t) strtoll (string, &endptr, /* base = */ 0);
      else if (type == DS_TYPE_GAUGE)
	ret.gauge = (gauge_t) strtod (string, &endptr);
    }

    /* Check if an error occurred */
    if ((string == NULL) || (endptr == string))
    {
      if (type == DS_TYPE_COUNTER)
	ret.counter = 0;
      else if (type == DS_TYPE_GAUGE)
	ret.gauge = NAN;
    }
  }
  else if (type == DS_TYPE_COUNTER)
  {
    ret.counter = temp;
  }
  else if (type == DS_TYPE_GAUGE)
  {
    ret.gauge = NAN;
    if (defined != 0)
      ret.gauge = (scale * temp) + shift;
  }

  return (ret);
}