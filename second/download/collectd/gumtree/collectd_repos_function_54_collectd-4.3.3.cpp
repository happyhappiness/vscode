int
lt_dlexit ()
{
  /* shut down libltdl */
  lt_dlloader *loader;
  int	       errors   = 0;

  LT_DLMUTEX_LOCK ();
  loader = loaders;

  if (!initialized)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (SHUTDOWN));
      ++errors;
      goto done;
    }

  /* shut down only at last call. */
  if (--initialized == 0)
    {
      int	level;

      while (handles && LT_DLIS_RESIDENT (handles))
	{
	  handles = handles->next;
	}

      /* close all modules */
      for (level = 1; handles; ++level)
	{
	  lt_dlhandle cur = handles;
	  int saw_nonresident = 0;

	  while (cur)
	    {
	      lt_dlhandle tmp = cur;
	      cur = cur->next;
	      if (!LT_DLIS_RESIDENT (tmp))
		saw_nonresident = 1;
	      if (!LT_DLIS_RESIDENT (tmp) && tmp->info.ref_count <= level)
		{
		  if (lt_dlclose (tmp))
		    {
		      ++errors;
		    }
		  /* Make sure that the handle pointed to by 'cur' still exists.
		     lt_dlclose recursively closes dependent libraries which removes
		     them from the linked list.  One of these might be the one
		     pointed to by 'cur'.  */
		  if (cur)
		    {
		      for (tmp = handles; tmp; tmp = tmp->next)
			if (tmp == cur)
			  break;
		      if (! tmp)
			cur = handles;
		    }
		}
	    }
	  /* done if only resident modules are left */
	  if (!saw_nonresident)
	    break;
	}

      /* close all loaders */
      while (loader)
	{
	  lt_dlloader *next = loader->next;
	  lt_user_data data = loader->dlloader_data;
	  if (loader->dlloader_exit && loader->dlloader_exit (data))
	    {
	      ++errors;
	    }

	  LT_DLMEM_REASSIGN (loader, next);
	}
      loaders = 0;
    }

 done:
  LT_DLMUTEX_UNLOCK ();
  return errors;
}