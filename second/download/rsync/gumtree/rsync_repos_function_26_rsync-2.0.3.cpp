int lp_number(char *name)
{
   int iService;

   for (iService = iNumServices - 1; iService >= 0; iService--)
      if (strequal(lp_name(iService), name)) 
         break;

   return (iService);
}