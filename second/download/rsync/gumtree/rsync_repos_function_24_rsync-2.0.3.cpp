BOOL lp_load(char *pszFname)
{
  pstring n2;
  BOOL bRetval;
 
  bRetval = False;

  bInGlobalSection = True;
  
  init_globals();

  pstrcpy(n2,pszFname);

  /* We get sections first, so have to start 'behind' to make up */
  iServiceIndex = -1;
  bRetval = pm_process(n2, do_section, do_parameter);
  
  bLoaded = True;

  return (bRetval);
}