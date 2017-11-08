static BOOL do_section(char *sectionname)
{
   BOOL bRetval;
   BOOL isglobal = (strwicmp(sectionname, GLOBAL_NAME) == 0);
   bRetval = False;

   /* if we were in a global section then do the local inits */
   if (bInGlobalSection && !isglobal)
     init_locals();

   /* if we've just struck a global section, note the fact. */
   bInGlobalSection = isglobal;

   /* check for multiple global sections */
   if (bInGlobalSection)
   {
     return(True);
   }

   /* if we have a current service, tidy it up before moving on */
   bRetval = True;

   if (iServiceIndex >= 0)
     bRetval = True;

   /* if all is still well, move to the next record in the services array */
   if (bRetval)
     {
       /* We put this here to avoid an odd message order if messages are */
       /* issued by the post-processing of a previous section. */

       if ((iServiceIndex=add_a_service(&sDefault,sectionname)) < 0)
	 {
	   rprintf(FERROR,"Failed to add a new service\n");
	   return(False);
	 }
     }

   return (bRetval);
}