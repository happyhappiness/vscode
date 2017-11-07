static void pgp_fetch_signatures (BODY ***signatures, BODY *a, int *n)
{
  for (; a; a = a->next)
  {
    if(a->type == TYPEMULTIPART)
      pgp_fetch_signatures (signatures, a->parts, n);
    else
    {
      if((*n % 5) == 0)
	safe_realloc((void **) signatures, (*n + 6) * sizeof(BODY **));

      (*signatures)[(*n)++] = a;
    }
  }
}