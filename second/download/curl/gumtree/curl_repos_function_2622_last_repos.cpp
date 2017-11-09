static void nss_destroy_object(void *user, void *ptr)
{
  struct ptr_list_wrap *wrap = (struct ptr_list_wrap *) ptr;
  PK11GenericObject *obj = (PK11GenericObject *) wrap->ptr;
  (void) user;
  PK11_DestroyGenericObject(obj);
  free(wrap);
}