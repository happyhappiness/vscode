double tvdiff (struct timeval t1, struct timeval t2)
{
 return (double)(t1.tv_sec - t2.tv_sec) + ((t1.tv_usec-t2.tv_usec)/1000000.0);
}