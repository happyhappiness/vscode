int
mutt_pattern_exec (struct pattern_t *pat, pattern_exec_flag flags, CONTEXT *ctx, HEADER *h)
{
  switch (pat->op)
  {
    case MUTT_AND:
      return (pat->not ^ (perform_and (pat->child, flags, ctx, h) > 0));
    case MUTT_OR:
      return (pat->not ^ (perform_or (pat->child, flags, ctx, h) > 0));
    case MUTT_THREAD:
      return (pat->not ^ match_threadcomplete(pat->child, flags, ctx, h->thread, 1, 1, 1, 1));
    case MUTT_ALL:
      return (!pat->not);
    case MUTT_EXPIRED:
      return (pat->not ^ h->expired);
    case MUTT_SUPERSEDED:
      return (pat->not ^ h->superseded);
    case MUTT_FLAG:
      return (pat->not ^ h->flagged);
    case MUTT_TAG:
      return (pat->not ^ h->tagged);
    case MUTT_NEW:
      return (pat->not ? h->old || h->read : !(h->old || h->read));
    case MUTT_UNREAD:
      return (pat->not ? h->read : !h->read);
    case MUTT_REPLIED:
      return (pat->not ^ h->replied);
    case MUTT_OLD:
      return (pat->not ? (!h->old || h->read) : (h->old && !h->read));
    case MUTT_READ:
      return (pat->not ^ h->read);
    case MUTT_DELETED:
      return (pat->not ^ h->deleted);
    case MUTT_MESSAGE:
      return (pat->not ^ (h->msgno >= pat->min - 1 && (pat->max == MUTT_MAXRANGE ||
						   h->msgno <= pat->max - 1)));
    case MUTT_DATE:
      return (pat->not ^ (h->date_sent >= pat->min && h->date_sent <= pat->max));
    case MUTT_DATE_RECEIVED:
      return (pat->not ^ (h->received >= pat->min && h->received <= pat->max));
    case MUTT_BODY:
    case MUTT_HEADER:
    case MUTT_WHOLE_MSG:
      /*
       * ctx can be NULL in certain cases, such as when replying to a message from the attachment menu and
       * the user has a reply-hook using "~h" (bug #2190).
       * This is also the case when message scoring.
       */
      if (!ctx)
	      return 0;
#ifdef USE_IMAP
      /* IMAP search sets h->matched at search compile time */
      if (ctx->magic == MUTT_IMAP && pat->stringmatch)
	return (h->matched);
#endif
      return (pat->not ^ msg_search (ctx, pat, h->msgno));
    case MUTT_SENDER:
      return (pat->not ^ match_adrlist (pat, flags & MUTT_MATCH_FULL_ADDRESS, 1,
                                        h->env->sender));
    case MUTT_FROM:
      return (pat->not ^ match_adrlist (pat, flags & MUTT_MATCH_FULL_ADDRESS, 1,
                                        h->env->from));
    case MUTT_TO:
      return (pat->not ^ match_adrlist (pat, flags & MUTT_MATCH_FULL_ADDRESS, 1,
                                        h->env->to));
    case MUTT_CC:
      return (pat->not ^ match_adrlist (pat, flags & MUTT_MATCH_FULL_ADDRESS, 1,
                                        h->env->cc));
    case MUTT_SUBJECT:
      return (pat->not ^ (h->env->subject && patmatch (pat, h->env->subject) == 0));
    case MUTT_ID:
      return (pat->not ^ (h->env->message_id && patmatch (pat, h->env->message_id) == 0));
    case MUTT_SCORE:
      return (pat->not ^ (h->score >= pat->min && (pat->max == MUTT_MAXRANGE ||
						   h->score <= pat->max)));
    case MUTT_SIZE:
      return (pat->not ^ (h->content->length >= pat->min && (pat->max == MUTT_MAXRANGE || h->content->length <= pat->max)));
    case MUTT_REFERENCE:
      return (pat->not ^ (match_reference (pat, h->env->references) ||
			  match_reference (pat, h->env->in_reply_to)));
    case MUTT_ADDRESS:
      return (pat->not ^ match_adrlist (pat, flags & MUTT_MATCH_FULL_ADDRESS, 4,
                                        h->env->from, h->env->sender,
                                        h->env->to, h->env->cc));
    case MUTT_RECIPIENT:
           return (pat->not ^ match_adrlist (pat, flags & MUTT_MATCH_FULL_ADDRESS,
                                             2, h->env->to, h->env->cc));
    case MUTT_LIST:	/* known list, subscribed or not */
      return (pat->not ^ mutt_is_list_cc (pat->alladdr, h->env->to, h->env->cc));
    case MUTT_SUBSCRIBED_LIST:
      return (pat->not ^ mutt_is_list_recipient (pat->alladdr, h->env->to, h->env->cc));
    case MUTT_PERSONAL_RECIP:
      return (pat->not ^ match_user (pat->alladdr, h->env->to, h->env->cc));
    case MUTT_PERSONAL_FROM:
      return (pat->not ^ match_user (pat->alladdr, h->env->from, NULL));
    case MUTT_COLLAPSED:
      return (pat->not ^ (h->collapsed && h->num_hidden > 1));
   case MUTT_CRYPT_SIGN:
     if (!WithCrypto)
       break;
     return (pat->not ^ ((h->security & SIGN) ? 1 : 0));
   case MUTT_CRYPT_VERIFIED:
     if (!WithCrypto)
       break;
     return (pat->not ^ ((h->security & GOODSIGN) ? 1 : 0));
   case MUTT_CRYPT_ENCRYPT:
     if (!WithCrypto)
       break;
     return (pat->not ^ ((h->security & ENCRYPT) ? 1 : 0));
   case MUTT_PGP_KEY:
     if (!(WithCrypto & APPLICATION_PGP))
       break;
     return (pat->not ^ ((h->security & APPLICATION_PGP) && (h->security & PGPKEY)));
    case MUTT_XLABEL:
      return (pat->not ^ (h->env->x_label && patmatch (pat, h->env->x_label) == 0));
    case MUTT_HORMEL:
      return (pat->not ^ (h->env->spam && h->env->spam->data && patmatch (pat, h->env->spam->data) == 0));
    case MUTT_DUPLICATED:
      return (pat->not ^ (h->thread && h->thread->duplicate_thread));
    case MUTT_MIMEATTACH:
      if (!ctx)
        return 0;
      {
      int count = mutt_count_body_parts (ctx, h);
      return (pat->not ^ (count >= pat->min && (pat->max == MUTT_MAXRANGE ||
                                                count <= pat->max)));
      }
    case MUTT_UNREFERENCED:
      return (pat->not ^ (h->thread && !h->thread->child));
  }
  mutt_error (_("error: unknown op %d (report this error)."), pat->op);
  return (-1);
}