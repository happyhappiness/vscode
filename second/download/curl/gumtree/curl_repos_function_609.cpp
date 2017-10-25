struct Cookie *Curl_cookie_getlist(struct CookieInfo *c,
                                   char *host, char *path, bool secure)
{
   struct Cookie *newco;
   struct Cookie *co;
   time_t now = time(NULL);
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
       if(!co->domain ||
          (co->tailmatch && tailmatch(co->domain, host)) ||
          (!co->tailmatch && strequal(host, co->domain)) ) {
         /* the right part of the host matches the domain stuff in the
            cookie data */

         /* now check the left part of the path with the cookies path
            requirement */
         if(!co->path ||
            checkprefix(co->path, path) ) {

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
           else {
              /* failure, clear up the allocated chain and return NULL */
             while(mainco) {
               co = mainco->next;
               free(mainco);
               mainco = co;
             }

             return NULL;
           }
         }
       }
     }
     co = co->next;
   }

   return mainco; /* return the new list */
}