static void init_service(service *pservice)
{
	memset((char *)pservice,0,sizeof(service));
	copy_service(pservice,&sDefault);
}