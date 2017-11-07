static int strict_cmp_envelopes (const ENVELOPE *e1, const ENVELOPE *e2)
{
  if (e1 && e2)
  {
    if (mutt_strcmp (e1->message_id, e2->message_id) ||
	mutt_strcmp (e1->subject, e2->subject) ||
	!strict_cmp_lists (e1->references, e2->references) ||
	!strict_addrcmp (e1->from, e2->from) ||
	!strict_addrcmp (e1->sender, e2->sender) ||
	!strict_addrcmp (e1->reply_to, e2->reply_to) ||
	!strict_addrcmp (e1->to, e2->to) ||
	!strict_addrcmp (e1->cc, e2->cc) ||
	!strict_addrcmp (e1->return_path, e2->return_path))
      return (0);
    else
      return (1);
  }
  else
  {
    if (e1 == NULL && e2 == NULL)
      return (1);
    else
      return (0);
  }
}