static value_t csnmp_value_list_to_value (struct variable_list *vl, int type,
    double scale, double shift)
{
  value_t ret;
  uint64_t tmp_unsigned = 0;
  int64_t tmp_signed = 0;
  int defined = 1;

  if ((vl->type == ASN_INTEGER)
      || (vl->type == ASN_UINTEGER)
      || (vl->type == ASN_COUNTER)
#ifdef ASN_TIMETICKS
      || (vl->type == ASN_TIMETICKS)
#endif
      || (vl->type == ASN_GAUGE))
  {
    tmp_unsigned = (uint32_t) *vl->val.integer;
    tmp_signed = (int32_t) *vl->val.integer;
    DEBUG ("snmp plugin: Parsed int32 value is %"PRIi64".", tmp_signed);
  }
  else if (vl->type == ASN_COUNTER64)
  {
    tmp_unsigned = (uint32_t) vl->val.counter64->high;
    tmp_unsigned = tmp_unsigned << 32;
    tmp_unsigned += (uint32_t) vl->val.counter64->low;
    tmp_signed = (int64_t) tmp_unsigned;
    DEBUG ("snmp plugin: Parsed int64 value is %"PRIu64".", tmp_unsigned);
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
    int status = -1;

    if (vl->val.string != NULL)
    {
      char string[64];
      size_t string_length;

      string_length = sizeof (string) - 1;
      if (vl->val_len < string_length)
	string_length = vl->val_len;

      /* The strings we get from the Net-SNMP library may not be null
       * terminated. That is why we're using `memcpy' here and not `strcpy'.
       * `string_length' is set to `vl->val_len' which holds the length of the
       * string.  -octo */
      memcpy (string, vl->val.string, string_length);
      string[string_length] = 0;

      status = parse_value (string, &ret, type);
      if (status != 0)
      {
	ERROR ("snmp plugin: csnmp_value_list_to_value: Parsing string as %s failed: %s",
	    DS_TYPE_TO_STRING (type), string);
      }
    }

    if (status != 0)
    {
      switch (type)
      {
	case DS_TYPE_COUNTER:
	case DS_TYPE_DERIVE:
	case DS_TYPE_ABSOLUTE:
	  memset (&ret, 0, sizeof (ret));
	  break;

	case DS_TYPE_GAUGE:
	  ret.gauge = NAN;
	  break;

	default:
	  ERROR ("snmp plugin: csnmp_value_list_to_value: Unknown "
	      "data source type: %i.", type);
	  ret.gauge = NAN;
      }
    }
  } /* if (vl->type == ASN_OCTET_STR) */
  else if (type == DS_TYPE_COUNTER)
  {
    ret.counter = tmp_unsigned;
  }
  else if (type == DS_TYPE_GAUGE)
  {
    ret.gauge = NAN;
    if (defined != 0)
      ret.gauge = (scale * tmp_signed) + shift;
  }
  else if (type == DS_TYPE_DERIVE)
    ret.derive = (derive_t) tmp_signed;
  else if (type == DS_TYPE_ABSOLUTE)
    ret.absolute = (absolute_t) tmp_unsigned;
  else
  {
    ERROR ("snmp plugin: csnmp_value_list_to_value: Unknown data source "
	"type: %i.", type);
    ret.gauge = NAN;
  }

  return (ret);
}