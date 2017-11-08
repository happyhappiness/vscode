static const curl_OID * searchOID(const char * oid)
{
  const curl_OID * op;

  /* Search the null terminated OID or OID identifier in local table.
     Return the table entry pointer or NULL if not found. */

  for(op = OIDtable; op->numoid; op++)
    if(!strcmp(op->numoid, oid) || curl_strequal(op->textoid, oid))
      return op;

  return (const curl_OID *) NULL;
}