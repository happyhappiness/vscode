int
lt_dlloader_add (place, dlloader, loader_name)
     lt_dlloader *place;
     const struct lt_user_dlloader *dlloader;
     const char *loader_name;
{
  int errors = 0;
  lt_dlloader *node = 0, *ptr = 0;

  if ((dlloader == 0)	/* diagnose null parameters */
      || (dlloader->module_open == 0)
      || (dlloader->module_close == 0)
      || (dlloader->find_sym == 0))
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (INVALID_LOADER));
      return 1;
    }

  /* Create a new dlloader node with copies of the user callbacks.  */
  node = LT_EMALLOC (lt_dlloader, 1);
  if (!node)
    return 1;

  node->next		= 0;
  node->loader_name	= loader_name;
  node->sym_prefix	= dlloader->sym_prefix;
  node->dlloader_exit	= dlloader->dlloader_exit;
  node->module_open	= dlloader->module_open;
  node->module_close	= dlloader->module_close;
  node->find_sym	= dlloader->find_sym;
  node->dlloader_data	= dlloader->dlloader_data;

  LT_DLMUTEX_LOCK ();
  if (!loaders)
    {
      /* If there are no loaders, NODE becomes the list! */
      loaders = node;
    }
  else if (!place)
    {
      /* If PLACE is not set, add NODE to the end of the
	 LOADERS list. */
      for (ptr = loaders; ptr->next; ptr = ptr->next)
	{
	  /*NOWORK*/;
	}

      ptr->next = node;
    }
  else if (loaders == place)
    {
      /* If PLACE is the first loader, NODE goes first. */
      node->next = place;
      loaders = node;
    }
  else
    {
      /* Find the node immediately preceding PLACE. */
      for (ptr = loaders; ptr->next != place; ptr = ptr->next)
	{
	  /*NOWORK*/;
	}

      if (ptr->next != place)
	{
	  LT_DLMUTEX_SETERROR (LT_DLSTRERROR (INVALID_LOADER));
	  ++errors;
	}
      else
	{
	  /* Insert NODE between PTR and PLACE. */
	  node->next = place;
	  ptr->next  = node;
	}
    }

  LT_DLMUTEX_UNLOCK ();

  return errors;
}