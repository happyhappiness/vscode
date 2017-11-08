static int add_a_service(service *pservice, char *name)
{
  int i;
  service tservice;
  int num_to_alloc = iNumServices+1;

  tservice = *pservice;

  /* it might already exist */
  if (name) 
    {
      i = getservicebyname(name,NULL);
      if (i >= 0)
	return(i);
    }

  i = iNumServices;

  ServicePtrs = (service **)Realloc(ServicePtrs,sizeof(service *)*num_to_alloc);
  if (ServicePtrs)
	  pSERVICE(iNumServices) = (service *)malloc(sizeof(service));

  if (!ServicePtrs || !pSERVICE(iNumServices))
	  return(-1);

  iNumServices++;

  init_service(pSERVICE(i));
  copy_service(pSERVICE(i),&tservice);
  if (name)
    string_set(&iSERVICE(i).name,name);  

  return(i);
}