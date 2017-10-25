static void negotiate(struct UrlData *data)
{
   int i;
   
   for(i = 0;i < NTELOPTS;i++)
   {
      if(us_preferred[i] == YES)
	 set_local_option(data, i, YES);
      
      if(him_preferred[i] == YES)
	 set_remote_option(data, i, YES);
   }
}