{
  size_t i;

  if(!ludp)
    return;

  free(ludp->lud_dn);
  free(ludp->lud_filter);

  if(ludp->lud_attrs) {
    for(i = 0; i < ludp->lud_attrs_dups; i++)
      free(ludp->lud_attrs[i]);
    free(ludp->lud_attrs);
  }

  free(ludp);
}