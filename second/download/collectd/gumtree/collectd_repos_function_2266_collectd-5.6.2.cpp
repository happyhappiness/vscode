int lcc_network_buffer_finalize(lcc_network_buffer_t *nb) /* {{{ */
{
  if (nb == NULL)
    return (EINVAL);

#if HAVE_LIBGCRYPT
  if (nb->seclevel == SIGN)
    return nb_add_signature(nb);
  else if (nb->seclevel == ENCRYPT)
    return nb_add_encryption(nb);
#endif

  return (0);
}