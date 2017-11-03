static void crypt_fetch_signatures (BODY ***signatures, BODY *a, int *n)
{
  if (!WithCrypto)
    return;

  for (; a; a = a->next)
  {
    if (a->type == TYPEMULTIPART)
      crypt_fetch_signatures (signatures, a->parts, n);
    else
    {
      if((*n % 5) == 0)
	safe_realloc (signatures, (*n + 6) * sizeof (BODY **));

      (*signatures)[(*n)++] = a;
    }
  }
}