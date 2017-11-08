static int getservicebyname(char *name, service *pserviceDest)
{
   int iService;

   for (iService = iNumServices - 1; iService >= 0; iService--)
      if (strwicmp(iSERVICE(iService).name, name) == 0)
      {
         if (pserviceDest != NULL)
	   copy_service(pserviceDest, pSERVICE(iService));
         break;
      }

   return (iService);
}