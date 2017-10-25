void cookie_cleanup(struct CookieInfo *c)
{
   struct Cookie *co;
   struct Cookie *next;
   if(c) {
      if(c->filename)
	 free(c->filename);
      co = c->cookies;

      while(co) {
	 if(co->name)
	    free(co->name);
	 if(co->value)
	    free(co->value);
	 if(co->domain)
	    free(co->domain);
	 if(co->path)
	    free(co->path);
	 if(co->expirestr)
	    free(co->expirestr);

	 if(co->version)
	    free(co->version);
	 if(co->maxage)
	    free(co->maxage);

	 next = co->next;
	 free(co);
	 co = next;
      }
   }
}