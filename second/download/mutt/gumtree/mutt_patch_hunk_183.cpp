 	return 1;
       }
       for (i = 0; i < Context->vcount; i++)
       {
         if (Context->hdrs[Context->v2r[i]]->tagged)
         {
-	  mutt_message_hook (Context, Context->hdrs[Context->v2r[i]], M_MESSAGEHOOK);
+	  mutt_message_hook (Context, Context->hdrs[Context->v2r[i]], MUTT_MESSAGEHOOK);
           pipe_msg (Context->hdrs[Context->v2r[i]], fpout, decode, print);
           /* add the message separator */
           if (sep) fputs (sep, fpout);
         }
       }
       safe_fclose (&fpout);
