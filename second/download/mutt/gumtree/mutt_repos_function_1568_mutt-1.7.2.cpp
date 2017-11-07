int crypt_query (BODY *m)
{
  int t = 0;

  if (!WithCrypto)
    return 0;
  
  if (!m)
    return 0;

  if (m->type == TYPEAPPLICATION)
  {
    if ((WithCrypto & APPLICATION_PGP))
      t |= mutt_is_application_pgp(m);

    if ((WithCrypto & APPLICATION_SMIME))
    {
      t |= mutt_is_application_smime(m);
      if (t && m->goodsig) t |= GOODSIGN;
      if (t && m->badsig) t |= BADSIGN;
    }
  }
  else if ((WithCrypto & APPLICATION_PGP) && m->type == TYPETEXT)
  {
    t |= mutt_is_application_pgp (m);
    if (t && m->goodsig)
      t |= GOODSIGN;
  }
  
  if (m->type == TYPEMULTIPART)
  {
    t |= mutt_is_multipart_encrypted(m);
    t |= mutt_is_multipart_signed (m);
    t |= mutt_is_malformed_multipart_pgp_encrypted (m);

    if (t && m->goodsig) 
      t |= GOODSIGN;
  }

  if (m->type == TYPEMULTIPART || m->type == TYPEMESSAGE)
  {
    BODY *p;
    int u, v, w;
    
    u = m->parts ? 0xffffffff : 0;	/* Bits set in all parts */
    w = 0;				/* Bits set in any part  */
 
    for (p = m->parts; p; p = p->next)
    {
      v  = crypt_query (p);
      u &= v; w |= v;
    }
    t |= u | (w & ~GOODSIGN);
    
    if ((w & GOODSIGN) && !(u & GOODSIGN))
      t |= PARTSIGN;
  }

  return t;
}