const lt_dlvtable *
lt_dlloader_get	(lt_dlloader loader)
{
  return (const lt_dlvtable *) (loader ? ((SList *) loader)->userdata : NULL);
}