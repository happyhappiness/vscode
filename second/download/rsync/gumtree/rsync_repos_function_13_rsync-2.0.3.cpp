static void init_service(service *pservice)
{
	bzero((char *)pservice,sizeof(service));
	copy_service(pservice,&sDefault);
}