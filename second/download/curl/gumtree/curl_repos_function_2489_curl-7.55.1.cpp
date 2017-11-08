static void nss_destroy_crl_item(void *user, void *ptr)
{
  struct ptr_list_wrap *wrap = (struct ptr_list_wrap *) ptr;
  SECItem *crl_der = (SECItem *) wrap->ptr;
  (void) user;
  SECITEM_FreeItem(crl_der, PR_TRUE);
  free(wrap);
}