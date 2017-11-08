static void add_name_vhost_config(apr_pool_t *p, server_rec *main_s,
                                 server_rec *s, server_addr_rec *sar,
                                 ipaddr_chain *ic)
{

   name_chain *nc = new_name_chain(p, s, sar);
   nc->next = ic->names;

   /* iterating backwards, so each one we see becomes the current default server */
   ic->server = s;

   if (ic->names == NULL) {
       if (ic->initialnames == NULL) {
           /* first pass, set these names aside in case we see another VH.
            * Until then, this looks like an IP-based VH to runtime.
            */
           ic->initialnames = nc;
       }
       else {
           /* second pass through this chain -- this really is an NVH, and we
            * have two sets of names to link in.
            */
           nc->next = ic->initialnames;
           ic->names = nc;
           ic->initialnames = NULL;
       }
   }
   else {
       /* 3rd or more -- just keep stacking the names */
       ic->names = nc;
   }
}