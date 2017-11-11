int
mutt_pattern_exec (struct pattern_t *pat, pattern_exec_flag flags, CONTEXT *ctx, HEADER *h)
{
  switch (pat->op)
  {
    case M_AND:
      return (pat->not ^ (perform_and (pat->child, flags, ctx, h) > 0));
    case M_OR:
      return (pat->not ^ (perform_or (pat->child, flags, ctx, h) > 0));
    case M_THREAD:
      return (pat->not ^ match_threadcomplete(pat->child, flags, ctx, h->thread, 1, 1, 1, 1));
    case M_ALL:
      return (!pat->not);
    case M_EXPIRED:
      return (pat->not ^ h->expired);
    case M_SUPERSEDED:
      return (pat->not ^ h->superseded);
    case M_FLAG:
      return (pat->not ^ h->flagged);
    case M_TAG:
      return (pat->not ^ h->tagged);
    case M_NEW:
      return (pat->not ? h->old || h->read : !(h->old || h->read));
    case M_UNREAD:
      return (pat->not ? h->read : !h->read);
    case M_REPLIED:
      return (pat->not ^ h->replied);
    case M_OLD:
      return (pat->not ? (!h->old || h->read) : (h->old && !h->read));
    case M_READ:
      return (pat->not ^ h->read);
    case M_DELETED:
      return (pat->not ^ h->deleted);
    case M_MESSAGE:
      return (pat->not ^ (h->msgno >= pat->min - 1 && (pat->max == M_MAXRANGE ||
						   h->msgno <= pat->max - 1)));
    case M_DATE:
      return (pat->not ^ (h->date_sent >= pat->min && h->date_sent <= pat->max));
    case M_DATE_RECEIVED:
      return (pat->not ^ (h->received >= pat->min && h->received <= pat->max));
    case M_BODY:
    case M_HEADER:
    case M_WHOLE_MSG:
      /*
       * ctx can be NULL in certain cases, such as when replying to a message from the attachment menu and
       * the user has a reply-hook using "~h" (bug #2190).
       */
      if (!ctx)
	      return 0;
#ifdef USE_IMAP
      /* IMAP search sets h->matched at search compile time */
      if (ctx->magic == M_IMAP && pat->stringmatch)
	return (h->matched);
#endif
      return (pat->not ^ msg_search (ctx, pat, h->msgno));
    case M_SENDER:
      return (pat->not ^ match_adrlist (pat, flags & M_MATCH_FULL_ADDRESS, 1,
                                        h->env->sender));
    case M_FROM:
      return (pat->not ^ match_adrlist (pat, flags & M_MATCH_FULL_ADDRESS, 1,
                                        h->env->from));
    case M_TO:
      return (pat->not ^ match_adrlist (pat, flags & M_MATCH_FULL_ADDRESS, 1,
                                        h->env->to));
    case M_CC:
      return (pat->not ^ match_adrlist (pat, flags & M_MATCH_FULL_ADDRESS, 1,
                                        h->env->cc));
    case M_SUBJECT:
      return (pat->not ^ (h->env->subject && patmatch (pat, h->env->subject) == 0));
    case M_ID:
      return (pat->not ^ (h->env->message_id && patmatch (pat, h->env->message_id) == 0));
    case M_SCORE:
      return (pat->not ^ (h->score >= pat->min && (pat->max == M_MAXRANGE ||
						   h->score <= pat->max)));
    case M_SIZE:
      return (pat->not ^ (h->content->length >= pat->min && (pat->max == M_MAXRANGE || h->content->length <= pat->max)));
    case M_REFERENCE:
      return (pat->not ^ (match_reference (pat, h->env->references) ||
			  match_reference (pat, h->env->in_reply_to)));
    case M_ADDRESS:
      return (pat->not ^ match_adrlist (pat, flags & M_MATCH_FULL_ADDRESS, 4,
                                        h->env->from, h->env->sender,
                                        h->env->to, h->env->cc));
    case M_RECIPIENT:
           return (pat->not ^ match_adrlist (pat, flags & M_MATCH_FULL_ADDRESS,
                                             2, h->env->to, h->env->cc));
    case M_LIST:	/* known list, subscribed or not */
      return (pat->not ^ mutt_is_list_cc (pat->alladdr, h->env->to, h->env->cc));
    case M_SUBSCRIBED_LIST:
      return (pat->not ^ mutt_is_list_recipient (pat->alladdr, h->env->to, h->env->cc));
    case M_PERSONAL_RECIP:
      return (pat->not ^ match_user (pat->alladdr, h->env->to, h->env->cc));
    case M_PERSONAL_FROM:
      return (pat->not ^ match_user (pat->alladdr, h->env->from, NULL));
    case M_COLLAPSED:
      return (pat->not ^ (h->collapsed && h->num_hidden > 1));
   case M_CRYPT_SIGN:
     if (!WithCrypto)
       break;
     return (pat->not ^ ((h->security & SIGN) ? 1 : 0));
   case M_CRYPT_VERIFIED:
     if (!WithCrypto)
       break;
     return (pat->not ^ ((h->security & GOODSIGN) ? 1 : 0));
   case M_CRYPT_ENCRYPT:
     if (!WithCrypto)
       break;
     return (pat->not ^ ((h->security & ENCRYPT) ? 1 : 0));
   case M_PGP_KEY:
     if (!(WithCrypto & APPLICATION_PGP))
       break;
     return (pat->not ^ ((h->security & APPLICATION_PGP) && (h->security & PGPKEY)));
    case M_XLABEL:
      return (pat->not ^ (h->env->x_label && patmatch (pat, h->env->x_label) == 0));
    case M_HORMEL:
      return (pat->not ^ (h->env->spam && h->env->spam->data && patmatch (pat, h->env->spam->data) == 0));
    case M_DUPLICATED:
      return (pat->not ^ (h->thread && h->thread->duplicate_thread));
    case M_MIMEATTACH:
      {
      int count = mutt_count_body_parts (ctx, h);
      return (pat->not ^ (count >= pat->min && (pat->max == M_MAXRANGE ||
                                                count <= pat->max)));
      }
    case M_UNREFERENCED:
      return (pat->not ^ (h->thread && !h->thread->child));
  }
  mutt_error (_("error: unknown op %d (report this error)."), pat->op);
  return (-1);
}