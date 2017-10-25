char *curl_unescape(char *string, int length)
{
   int alloc = (length?length:strlen(string))+1;
   char *ns = malloc(alloc);
   unsigned char in;
   int index=0;
   int hex;
  
   while(--alloc) {
      in = *string;
      if('+' == in)
	 in = ' ';
      else if('%' == in) {
	 /* encoded part */
	 if(sscanf(string+1, "%02X", &hex)) {
	    in = hex;
	    string+=2;
	 }
      }

      ns[index++] = in;
      string++;
   }
   ns[index]=0; /* terminate it */
   return ns;
  
}