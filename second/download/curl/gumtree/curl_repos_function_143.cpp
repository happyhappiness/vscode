void cookie_freelist(struct Cookie *co)
{
   struct Cookie *next;
   if(co) {
      while(co) {
	 next = co->next;
	 free(co); /* we only free the struct since the "members" are all
		      just copied! */
	 co = next;
      }
   }
}