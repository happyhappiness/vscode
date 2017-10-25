struct Cookie *cookie_getlist(struct CookieInfo *c,
			      char *host, char *path, bool secure)
{
   struct Cookie *newco;
   struct Cookie *co;
   time_t now = time(NULL);
   int hostlen=strlen(host);
   int domlen;

   struct Cookie *mainco=NULL;

   if(!c || !c->cookies)
      return NULL; /* no cookie struct or no cookies in the struct */

   co = c->cookies;

   while(co) {
      /* only process this cookie if it is not expired or had no expire
	 date AND that if the cookie requires we're secure we must only
	 continue if we are! */
     if( (co->expires<=0 || (co->expires> now)) &&
         (co->secure?secure:TRUE) ) {

	 /* now check if the domain is correct */
	 domlen=co->domain?strlen(co->domain):0;
	 if(!co->domain ||
	    ((domlen<hostlen) &&
	     strequal(host+(hostlen-domlen), co->domain)) ) {
	    /* the right part of the host matches the domain stuff in the
	       cookie data */

	    /* now check the left part of the path with the cookies path
	       requirement */
	    if(!co->path ||
	       strnequal(path, co->path, strlen(co->path))) {

	       /* and now, we know this is a match and we should create an
		  entry for the return-linked-list */

	       newco = (struct Cookie *)malloc(sizeof(struct Cookie));
	       if(newco) {
		  /* first, copy the whole source cookie: */
		  memcpy(newco, co, sizeof(struct Cookie));

		  /* then modify our next */
		  newco->next = mainco;

		  /* point the main to us */
		  mainco = newco;
	       }
	    }
	 }
      }
      co = co->next;
   }

   return mainco; /* return the new list */
}