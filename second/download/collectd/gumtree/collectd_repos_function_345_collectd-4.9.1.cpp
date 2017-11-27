static int csnmp_strvbcopy (char *dst, /* {{{ */
    const struct variable_list *vb, size_t dst_size)
{
  char *src;
  size_t num_chars;
  size_t i;

  if (vb->type == ASN_OCTET_STR)
    src = (char *) vb->val.string;
  else if (vb->type == ASN_BIT_STR)
    src = (char *) vb->val.bitstring;
  else
  {
    dst[0] = 0;
    return (EINVAL);
  }

  num_chars = dst_size - 1;
  if (num_chars > vb->val_len)
    num_chars = vb->val_len;

  for (i = 0; i < num_chars; i++)
  {
    /* Check for control characters. */
    if ((src[i] >= 0) && (src[i] < 32))
      return (csnmp_strvbcopy_hexstring (dst, vb, dst_size));
    dst[i] = src[i];
  }
  dst[num_chars] = 0;

  return ((int) vb->val_len);
}