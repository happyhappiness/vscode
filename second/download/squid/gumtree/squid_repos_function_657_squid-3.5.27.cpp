int
lt_dlloader_add (const lt_dlvtable *vtable)
{
  SList *item;

  if ((vtable == 0)	/* diagnose invalid vtable fields */
      || (vtable->module_open == 0)
      || (vtable->module_close == 0)
      || (vtable->find_sym == 0)
      || ((vtable->priority != LT_DLLOADER_PREPEND) &&
	  (vtable->priority != LT_DLLOADER_APPEND)))
    {
      LT__SETERROR (INVALID_LOADER);
      return RETURN_FAILURE;
    }

  item = slist_box (vtable);
  if (!item)
    {
      (*lt__alloc_die) ();

      /* Let the caller know something went wrong if lt__alloc_die
	 doesn't abort.  */
      return RETURN_FAILURE;
    }

  if (vtable->priority == LT_DLLOADER_PREPEND)
    {
      loaders = slist_cons (item, loaders);
    }
  else
    {
      assert (vtable->priority == LT_DLLOADER_APPEND);
      loaders = slist_concat (loaders, item);
    }

  return RETURN_SUCCESS;
}