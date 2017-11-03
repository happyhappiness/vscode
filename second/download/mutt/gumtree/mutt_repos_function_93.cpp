void mutt_set_followup_to (ENVELOPE *e)
{
  ADDRESS *t = NULL;
  ADDRESS *from;

  /* 
   * Only generate the Mail-Followup-To if the user has requested it, and
   * it hasn't already been set
   */

  if (option (OPTFOLLOWUPTO) && !e->mail_followup_to)
  {
    if (mutt_is_list_cc (0, e->to, e->cc))
    {
      /* 
       * this message goes to known mailing lists, so create a proper
       * mail-followup-to header
       */

      t = rfc822_append (&e->mail_followup_to, e->to, 0);
      rfc822_append (&t, e->cc, 1);
    }

    /* remove ourselves from the mail-followup-to header */
    e->mail_followup_to = remove_user (e->mail_followup_to, 0);

    /*
     * If we are not subscribed to any of the lists in question,
     * re-add ourselves to the mail-followup-to header.  The 
     * mail-followup-to header generated is a no-op with group-reply,
     * but makes sure list-reply has the desired effect.
     */

    if (e->mail_followup_to && !mutt_is_list_recipient (0, e->to, e->cc))
    {
      if (e->reply_to)
	from = rfc822_cpy_adr (e->reply_to, 0);
      else if (e->from)
	from = rfc822_cpy_adr (e->from, 0);
      else
	from = mutt_default_from ();
      
      if (from)
      {
	/* Normally, this loop will not even be entered. */
	for (t = from; t && t->next; t = t->next)
	  ;
	
	t->next = e->mail_followup_to; 	/* t cannot be NULL at this point. */
	e->mail_followup_to = from;
      }
    }
    
    e->mail_followup_to = mutt_remove_duplicates (e->mail_followup_to);
    
  }
}