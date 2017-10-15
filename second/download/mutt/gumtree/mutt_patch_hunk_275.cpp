 	last = env->userhdrs = mutt_new_list ();
       last->data = safe_strdup (uh->data);
     }
   }
 }
 
-LIST *mutt_copy_list (LIST *p)
-{
-  LIST *t, *r=NULL, *l=NULL;
-
-  for (; p; p = p->next)
-  {
-    t = (LIST *) safe_malloc (sizeof (LIST));
-    t->data = safe_strdup (p->data);
-    t->next = NULL;
-    if (l)
-    {
-      r->next = t;
-      r = r->next;
-    }
-    else
-      l = r = t;
-  }
-  return (l);
-}
-
 void mutt_forward_intro (FILE *fp, HEADER *cur)
 {
   char buffer[STRING];
   
   fputs ("----- Forwarded message from ", fp);
   buffer[0] = 0;
