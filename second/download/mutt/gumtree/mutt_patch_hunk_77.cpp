 	if (hdr->env->return_path)
 	  p = hdr->env->return_path;
 	else if (hdr->env->sender)
 	  p = hdr->env->sender;
 	else
 	  p = hdr->env->from;
-
-	if (!hdr->received)
-	  hdr->received = time (NULL);
-	t = hdr->received;
       }
-      else
-	t = time (NULL);
 
-      fprintf (msg->fp, "From %s %s", p ? p->mailbox : NONULL(Username), ctime (&t));
+      fprintf (msg->fp, "From %s %s", p ? p->mailbox : NONULL(Username), ctime (&msg->received));
     }
   }
   else
-    safe_free ((void **) &msg);
+    FREE (&msg);
 
   return msg;
 }
 
 /* check for new mail */
 int mx_check_mailbox (CONTEXT *ctx, int *index_hint, int lock)
