static BOOL lp_do_parameter(int snum, char *parmname, char *parmvalue)
{
   int parmnum, i;
   void *parm_ptr=NULL; /* where we are going to store the result */
   void *def_ptr=NULL;
   char *cp;

   parmnum = map_parameter(parmname);

   if (parmnum < 0)
     {
       rprintf(FLOG, "IGNORING unknown parameter \"%s\"\n", parmname);
       return(True);
     }

   def_ptr = parm_table[parmnum].ptr;

   /* we might point at a service, the default service or a global */
   if (snum < 0) {
     parm_ptr = def_ptr;
   } else {
       if (parm_table[parmnum].class == P_GLOBAL) {
	   rprintf(FLOG, "Global parameter %s found in service section!\n",parmname);
	   return(True);
	 }
       parm_ptr = ((char *)pSERVICE(snum)) + PTR_DIFF(def_ptr,&sDefault);
   }

   /* now switch on the type of variable it is */
   switch (parm_table[parmnum].type)
     {
     case P_BOOL:
       set_boolean(parm_ptr,parmvalue);
       break;

     case P_BOOLREV:
       set_boolean(parm_ptr,parmvalue);
       *(BOOL *)parm_ptr = ! *(BOOL *)parm_ptr;
       break;

     case P_INTEGER:
       *(int *)parm_ptr = atoi(parmvalue);
       break;

     case P_CHAR:
       *(char *)parm_ptr = *parmvalue;
       break;

     case P_OCTAL:
       sscanf(parmvalue,"%o",(int *)parm_ptr);
       break;

     case P_PATH:
       string_set(parm_ptr,parmvalue);
       if ((cp = *(char**)parm_ptr) != NULL) {
	   int len = strlen(cp);
	   while (len > 1 && cp[len-1] == '/') len--;
	   cp[len] = '\0';
       }
       break;

     case P_STRING:
       string_set(parm_ptr,parmvalue);
       break;

     case P_GSTRING:
       strlcpy((char *)parm_ptr,parmvalue,sizeof(pstring));
       break;

     case P_ENUM:
	     for (i=0;parm_table[parmnum].enum_list[i].name;i++) {
		     if (strequal(parmvalue, parm_table[parmnum].enum_list[i].name)) {
			     *(int *)parm_ptr = parm_table[parmnum].enum_list[i].value;
			     break;
		     }
	     }
	     if (!parm_table[parmnum].enum_list[i].name) {
		     if (atoi(parmvalue) > 0)
			     *(int *)parm_ptr = atoi(parmvalue);
	     }
	     break;
     case P_SEP:
	     break;
     }

   return(True);
}