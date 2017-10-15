 	  {
 	    mutt_error _("Cannot delete root folder");
 	    break;
 	  }
 	  snprintf (msg, sizeof (msg), _("Really delete mailbox \"%s\"?"),
             mx.mbox);
-	  if (mutt_yesorno (msg, M_NO) == M_YES)
+	  if (mutt_yesorno (msg, MUTT_NO) == MUTT_YES)
           {
 	    if (!imap_delete_mailbox (Context, mx))
             {
 	      /* free the mailbox from the browser */
 	      FREE (&((state.entry)[nentry].name));
 	      FREE (&((state.entry)[nentry].desc));
 	      /* and move all other entries up */
 	      if (nentry+1 < state.entrylen)
 		memmove (state.entry + nentry, state.entry + nentry + 1,
                   sizeof (struct folder_file) * (state.entrylen - (nentry+1)));
+              memset (&state.entry[state.entrylen - 1], 0,
+                      sizeof (struct folder_file));
 	      state.entrylen--;
 	      mutt_message _("Mailbox deleted.");
 	      init_menu (&state, menu, title, sizeof (title), buffy);
 	      MAYBE_REDRAW (menu->redraw);
 	    }
 	  }
