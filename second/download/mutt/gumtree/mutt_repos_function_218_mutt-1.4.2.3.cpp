int pgp_query (BODY *m)
{
  int t = 0;

  t |= mutt_is_application_pgp (m);

  if ((t & (PGPSIGN|PGPENCRYPT)) && m->goodsig)
    t |= PGPGOODSIGN|PGPSIGN;
  else if (m->type == TYPEMULTIPART)
  {
    if (mutt_is_multipart_signed(m))
      t |= PGPSIGN;
    else if (mutt_is_multipart_encrypted(m))
      t |= PGPENCRYPT;

    if (m->goodsig && 
	(mutt_is_multipart_signed (m) || mutt_is_multipart_encrypted (m)))
      t |= PGPGOODSIGN;
  }
  
  if (m->type == TYPEMULTIPART || m->type == TYPEMESSAGE)
  {
    BODY *p;
 
    for (p = m->parts; p; p = p->next)
      t |= pgp_query(p) & ~PGPGOODSIGN;
  }

  return t;
}