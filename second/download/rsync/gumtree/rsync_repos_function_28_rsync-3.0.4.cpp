static BOOL do_parameter(char *parmname, char *parmvalue)
{
   return lp_do_parameter(bInGlobalSection?-2:iServiceIndex, parmname, parmvalue);
}