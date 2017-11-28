void *
slist_unbox (SList *item)
{
  void *userdata = 0;

  if (item)
    {
      /* Strip the const, because responsibility for this memory
	 passes to the caller on return.  */
      userdata = (void *) item->userdata;
      free (item);
    }

  return userdata;
}