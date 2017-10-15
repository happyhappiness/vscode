       case OP_COMPOSE_WRITE_MESSAGE:
 
        fname[0] = '\0';
        if (Context)
        {
 	 strfcpy (fname, NONULL (Context->path), sizeof (fname));
-	 mutt_pretty_mailbox (fname);
+	 mutt_pretty_mailbox (fname, sizeof (fname));
        }
        if (idxlen)
          msg->content = idx[0]->content;
        if (mutt_enter_fname (_("Write message to mailbox"), fname, sizeof (fname),
                              &menu->redraw, 1) != -1 && fname[0])
        {
          mutt_message (_("Writing message to %s ..."), fname);
          mutt_expand_path (fname, sizeof (fname));
 
          if (msg->content->next)
            msg->content = mutt_make_multipart (msg->content);
 
-         if (mutt_write_fcc (NONULL (fname), msg, NULL, 1, NULL) < 0)
+         if (mutt_write_fcc (fname, msg, NULL, 0, NULL) < 0)
            msg->content = mutt_remove_multipart (msg->content);
          else
            mutt_message _("Message written.");
        }
        break;
 
 
 
-#ifdef HAVE_PGP
       case OP_COMPOSE_PGP_MENU:
-
-	msg->pgp = pgp_send_menu (msg->pgp, &menu->redraw);
+        if (!(WithCrypto & APPLICATION_PGP))
+          break;
+	if ((WithCrypto & APPLICATION_SMIME)
+            && (msg->security & APPLICATION_SMIME))
+	{
+	  if (mutt_yesorno (_("S/MIME already selected. Clear & continue ? "),
+			     M_YES) != M_YES)
+	  {
+	    mutt_clear_error ();
+	    break;
+	  }
+	  msg->security = 0;
+	}
+	msg->security = crypt_pgp_send_menu (msg, &menu->redraw);
+	redraw_crypt_lines (msg);
+        mutt_message_hook (NULL, msg, M_SEND2HOOK);
 	break;
 
-      case OP_FORGET_PASSPHRASE:
 
-	mutt_forget_passphrase ();
+      case OP_FORGET_PASSPHRASE:
+	crypt_forget_passphrase ();
 	break;
 
-#endif /* HAVE_PGP */
+
+      case OP_COMPOSE_SMIME_MENU:
+        if (!(WithCrypto & APPLICATION_SMIME))
+          break;
+
+	if ((WithCrypto & APPLICATION_PGP)
+            && (msg->security & APPLICATION_PGP))
+	{
+	  if (mutt_yesorno (_("PGP already selected. Clear & continue ? "),
+			      M_YES) != M_YES)
+	  {
+	     mutt_clear_error ();
+	     break;
+	  }
+	  msg->security = 0;
+	}
+	msg->security = crypt_smime_send_menu(msg, &menu->redraw);
+	redraw_crypt_lines (msg);
+        mutt_message_hook (NULL, msg, M_SEND2HOOK);
+        break;
 
 
 #ifdef MIXMASTER
       case OP_COMPOSE_MIX:
       
       	mix_make_chain (&msg->chain, &menu->redraw);
+        mutt_message_hook (NULL, msg, M_SEND2HOOK);
         break;
 #endif
 
     }
 
-    /* Draw formated compose status line */
+    /* Draw formatted compose status line */
     if (menu->redraw & REDRAW_STATUS) 
     {
-       	compose_status_line (buf, sizeof (buf), menu, NONULL(ComposeFormat));
-	CLEARLINE (option (OPTSTATUSONTOP) ? 0 : LINES-2);
+	compose_status_line (buf, sizeof (buf), 0, menu, NONULL(ComposeFormat));
+	move(option (OPTSTATUSONTOP) ? 0 : LINES-2, 0);
 	SETCOLOR (MT_COLOR_STATUS);
-	printw ("%-*.*s", COLS, COLS, buf);
-	SETCOLOR (MT_COLOR_NORMAL);
+	mutt_paddstr (COLS, buf);
+	NORMAL_COLOR;
 	menu->redraw &= ~REDRAW_STATUS;
     }
   }
 
   mutt_menuDestroy (&menu);
 
   if (idxlen)
   {
     msg->content = idx[0]->content;
     for (i = 0; i < idxlen; i++)
-      safe_free ((void **) &idx[i]);
+    {
+      idx[i]->content->aptr = NULL;
+      FREE (&idx[i]);
+    }
   }
   else
     msg->content = NULL;
 
-  safe_free ((void **) &idx);
+  FREE (&idx);
 
   return (r);
 }
+
