int lp_number(char *name)
{
   int iService;

   for (iService = iNumServices - 1; iService >= 0; iService--)
      if (strcmp(lp_name(iService), name) == 0)
         break;

   return (iService);
}