static int write_sparse(int f,char *buf,int len)
{
	int l1=0,l2=0;
	int ret;

	for (l1=0;l1<len && buf[l1]==0;l1++) ;
	for (l2=0;l2<(len-l1) && buf[len-(l2+1)]==0;l2++) ;

	last_byte = buf[len-1];

	if (l1 == len || l2 > 0)
		last_sparse=1;

	if (l1 > 0)
		lseek(f,l1,SEEK_CUR);  

	if (l1 == len) 
		return len;

	if ((ret=write(f,buf+l1,len-(l1+l2))) != len-(l1+l2)) {
		if (ret == -1 || ret == 0) return ret;
		return (l1+ret);
	}

	if (l2 > 0)
		lseek(f,l2,SEEK_CUR);
	
	return len;
}