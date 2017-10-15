 static void draw_envelope_addr (int line, ADDRESS *addr)
 {
   char buf[LONG_STRING];
 
   buf[0] = 0;
   rfc822_write_address (buf, sizeof (buf), addr, 1);
-  mvprintw (line, 0, TITLE_FMT, Prompts[line - 1]);
+  mutt_window_mvprintw (MuttIndexWindow, line, 0, TITLE_FMT, Prompts[line]);
   mutt_paddstr (W, buf);
 }
 
 static void draw_envelope (HEADER *msg, char *fcc)
 {
   draw_envelope_addr (HDR_FROM, msg->env->from);
   draw_envelope_addr (HDR_TO, msg->env->to);
   draw_envelope_addr (HDR_CC, msg->env->cc);
   draw_envelope_addr (HDR_BCC, msg->env->bcc);
-  mvprintw (HDR_SUBJECT, 0, TITLE_FMT, Prompts[HDR_SUBJECT - 1]);
+  mutt_window_mvprintw (MuttIndexWindow, HDR_SUBJECT, 0, TITLE_FMT, Prompts[HDR_SUBJECT]);
   mutt_paddstr (W, NONULL (msg->env->subject));
   draw_envelope_addr (HDR_REPLYTO, msg->env->reply_to);
-  mvprintw (HDR_FCC, 0, TITLE_FMT, Prompts[HDR_FCC - 1]);
+  mutt_window_mvprintw (MuttIndexWindow, HDR_FCC, 0, TITLE_FMT, Prompts[HDR_FCC]);
   mutt_paddstr (W, fcc);
 
   if (WithCrypto)
     redraw_crypt_lines (msg);
 
 #ifdef MIXMASTER
   redraw_mix_line (msg->chain);
 #endif
 
   SETCOLOR (MT_COLOR_STATUS);
-  mvaddstr (HDR_ATTACH - 1, 0, _("-- Attachments"));
-  clrtoeol ();
+  mutt_window_mvaddstr (MuttIndexWindow, HDR_ATTACH - 1, 0, _("-- Attachments"));
+  mutt_window_clrtoeol (MuttIndexWindow);
 
   NORMAL_COLOR;
 }
 
 static int edit_address_list (int line, ADDRESS **addr)
 {
   char buf[HUGE_STRING] = ""; /* needs to be large for alias expansion */
   char *err = NULL;
   
   mutt_addrlist_to_local (*addr);
   rfc822_write_address (buf, sizeof (buf), *addr, 0);
-  if (mutt_get_field (Prompts[line - 1], buf, sizeof (buf), M_ALIAS) == 0)
+  if (mutt_get_field (Prompts[line], buf, sizeof (buf), MUTT_ALIAS) == 0)
   {
     rfc822_free_address (addr);
     *addr = mutt_parse_adrlist (*addr, buf);
     *addr = mutt_expand_aliases (*addr);
   }
 
