static const char *
hdr_format_str (char *dest,
		size_t destlen,
		size_t col,
		char op,
		const char *src,
		const char *prefix,
		const char *ifstring,
		const char *elsestring,
		unsigned long data,
		format_flag flags)
{
  struct hdr_format_info *hfi = (struct hdr_format_info *) data;
  HEADER *hdr, *htmp;
  CONTEXT *ctx;
  char fmt[SHORT_STRING], buf2[LONG_STRING], ch, *p;
  int do_locales, i;
  int optional = (flags & M_FORMAT_OPTIONAL);
  int threads = ((Sort & SORT_MASK) == SORT_THREADS);
  int is_index = (flags & M_FORMAT_INDEX);
#define THREAD_NEW (threads && hdr->collapsed && hdr->num_hidden > 1 && mutt_thread_contains_unread (ctx, hdr) == 1)
#define THREAD_OLD (threads && hdr->collapsed && hdr->num_hidden > 1 && mutt_thread_contains_unread (ctx, hdr) == 2)
  size_t len;

  hdr = hfi->hdr;
  ctx = hfi->ctx;

  dest[0] = 0;
  switch (op)
  {
    case 'A':
      if(hdr->env->reply_to && hdr->env->reply_to->mailbox)
      {
	mutt_format_s (dest, destlen, prefix, mutt_addr_for_display (hdr->env->reply_to));
	break;
      }
      /* fall through if 'A' returns nothing */

    case 'a':
      if(hdr->env->from && hdr->env->from->mailbox)
      {
	mutt_format_s (dest, destlen, prefix, mutt_addr_for_display (hdr->env->from));
      }
      else
        dest[0] = '\0';
      break;

    case 'B':
      if (!first_mailing_list (dest, destlen, hdr->env->to) &&
	  !first_mailing_list (dest, destlen, hdr->env->cc))
	dest[0] = 0;
      if (dest[0])
      {
	strfcpy (buf2, dest, sizeof(buf2));
	mutt_format_s (dest, destlen, prefix, buf2);
	break;
      }
      /* fall through if 'B' returns nothing */

    case 'b':
      if(ctx)
      {
	if ((p = strrchr (ctx->path, '/')))
	  strfcpy (dest, p + 1, destlen);
	else
	  strfcpy (dest, ctx->path, destlen);
      }
      else 
	strfcpy(dest, "(null)", destlen);
      strfcpy (buf2, dest, sizeof(buf2));
      mutt_format_s (dest, destlen, prefix, buf2);
      break;
    
    case 'c':
      mutt_pretty_size (buf2, sizeof (buf2), (long) hdr->content->length);
      mutt_format_s (dest, destlen, prefix, buf2);
      break;

    case 'C':
      snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
      snprintf (dest, destlen, fmt, hdr->msgno + 1);
      break;

    case 'd':
    case 'D':
    case '{':
    case '[':
    case '(':
    case '<':

      /* preprocess $date_format to handle %Z */
      {
	const char *cp;
	struct tm *tm; 
	time_t T;

	p = dest;

	cp = (op == 'd' || op == 'D') ? (NONULL (DateFmt)) : src;
	if (*cp == '!')
	{
	  do_locales = 0;
	  cp++;
	}
	else
	  do_locales = 1;

	len = destlen - 1;
	while (len > 0 && (((op == 'd' || op == 'D') && *cp) ||
			   (op == '{' && *cp != '}') || 
			   (op == '[' && *cp != ']') ||
			   (op == '(' && *cp != ')') ||
			   (op == '<' && *cp != '>')))
	{
	  if (*cp == '%')
	  {
	    cp++;
	    if ((*cp == 'Z' || *cp == 'z') && (op == 'd' || op == '{'))
	    {
	      if (len >= 5)
	      {
		sprintf (p, "%c%02u%02u", hdr->zoccident ? '-' : '+',
			 hdr->zhours, hdr->zminutes);
		p += 5;
		len -= 5;
	      }
	      else
		break; /* not enough space left */
	    }
	    else
	    {
	      if (len >= 2)
	      {
		*p++ = '%';
		*p++ = *cp;
		len -= 2;
	      }
	      else
		break; /* not enough space */
	    }
	    cp++;
	  }
	  else
	  {
	    *p++ = *cp++;
	    len--;
	  }
	}
	*p = 0;

	if (do_locales && Locale)
	  setlocale (LC_TIME, Locale);

	if (op == '[' || op == 'D')
	  tm = localtime (&hdr->date_sent);
	else if (op == '(')
	  tm = localtime (&hdr->received);
	else if (op == '<')
	{
	  T = time (NULL);
	  tm = localtime (&T);
	}
	else
	{
	  /* restore sender's time zone */
	  T = hdr->date_sent;
	  if (hdr->zoccident)
	    T -= (hdr->zhours * 3600 + hdr->zminutes * 60);
	  else
	    T += (hdr->zhours * 3600 + hdr->zminutes * 60);
	  tm = gmtime (&T);
	}

	strftime (buf2, sizeof (buf2), dest, tm);

	if (do_locales)
	  setlocale (LC_TIME, "C");

	mutt_format_s (dest, destlen, prefix, buf2);
	if (len > 0 && op != 'd' && op != 'D') /* Skip ending op */
	  src = cp + 1;
      }
      break;

    case 'e':
      snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
      snprintf (dest, destlen, fmt, mutt_messages_in_thread(ctx, hdr, 1));
      break;

    case 'E':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
	snprintf (dest, destlen, fmt, mutt_messages_in_thread(ctx, hdr, 0));
      }
      else if (mutt_messages_in_thread(ctx, hdr, 0) <= 1)
	optional = 0;
      break;

    case 'f':
      buf2[0] = 0;
      rfc822_write_address (buf2, sizeof (buf2), hdr->env->from, 1);
      mutt_format_s (dest, destlen, prefix, buf2);
      break;

    case 'F':
      if (!optional)
      {
        make_from (hdr->env, buf2, sizeof (buf2), 0);
	mutt_format_s (dest, destlen, prefix, buf2);
      }
      else if (mutt_addr_is_user (hdr->env->from))
        optional = 0;
      break;

    case 'H':
      /* (Hormel) spam score */
      if (optional)
	optional = hdr->env->spam ? 1 : 0;

       if (hdr->env->spam)
         mutt_format_s (dest, destlen, prefix, NONULL (hdr->env->spam->data));
       else
         mutt_format_s (dest, destlen, prefix, "");

      break;

    case 'i':
      mutt_format_s (dest, destlen, prefix, hdr->env->message_id ? hdr->env->message_id : "<no.id>");
      break;

    case 'l':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
	snprintf (dest, destlen, fmt, (int) hdr->lines);
      }
      else if (hdr->lines <= 0)
        optional = 0;
      break;

    case 'L':
      if (!optional)
      {
	make_from (hdr->env, buf2, sizeof (buf2), 1);
	mutt_format_s (dest, destlen, prefix, buf2);
      }
      else if (!check_for_mailing_list (hdr->env->to, NULL, NULL, 0) &&
	       !check_for_mailing_list (hdr->env->cc, NULL, NULL, 0))
      {
	optional = 0;
      }
      break;

    case 'm':
      if(ctx)
      {
	snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
	snprintf (dest, destlen, fmt, ctx->msgcount);
      }
      else
	strfcpy(dest, "(null)", destlen);
      break;

    case 'n':
      mutt_format_s (dest, destlen, prefix, mutt_get_name (hdr->env->from));
      break;

    case 'N':
      if (!optional)
      {
	snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
	snprintf (dest, destlen, fmt, hdr->score);
      }
      else
      {
	if (hdr->score == 0)
	  optional = 0;
      }
      break;

    case 'O':
      if (!optional)
      {
	make_from_addr (hdr->env, buf2, sizeof (buf2), 1);
	if (!option (OPTSAVEADDRESS) && (p = strpbrk (buf2, "%@")))
	  *p = 0;
	mutt_format_s (dest, destlen, prefix, buf2);
      }
      else if (!check_for_mailing_list_addr (hdr->env->to, NULL, 0) &&
	       !check_for_mailing_list_addr (hdr->env->cc, NULL, 0))
      {
	optional = 0;
      }
      break;

    case 'M':
      snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
      if (!optional)
      {
	if (threads && is_index && hdr->collapsed && hdr->num_hidden > 1)
	  snprintf (dest, destlen, fmt, hdr->num_hidden);
	else if (is_index && threads)
	  mutt_format_s (dest, destlen, prefix, " ");
	else
	  *dest = '\0';
      }
      else
      {
	if (!(threads && is_index && hdr->collapsed && hdr->num_hidden > 1))
	  optional = 0;
      }
      break;

    case 'P':
      strfcpy(dest, NONULL(hfi->pager_progress), destlen);
      break;

    case 'r':
      buf2[0] = 0;
      rfc822_write_address(buf2, sizeof(buf2), hdr->env->to, 1);
      if (optional && buf2[0] == '\0')
        optional = 0;
      mutt_format_s (dest, destlen, prefix, buf2);
      break;

    case 'R':
      buf2[0] = 0;
      rfc822_write_address(buf2, sizeof(buf2), hdr->env->cc, 1);
      if (optional && buf2[0] == '\0')
        optional = 0;
      mutt_format_s (dest, destlen, prefix, buf2);
      break;

    case 's':
      
      if (flags & M_FORMAT_TREE && !hdr->collapsed)
      {
	if (flags & M_FORMAT_FORCESUBJ)
	{
	  mutt_format_s (dest, destlen, "", NONULL (hdr->env->subject));
	  snprintf (buf2, sizeof (buf2), "%s%s", hdr->tree, dest);
	  mutt_format_s_tree (dest, destlen, prefix, buf2);
	}
	else
	  mutt_format_s_tree (dest, destlen, prefix, hdr->tree);
      }
      else
	mutt_format_s (dest, destlen, prefix, NONULL (hdr->env->subject));
      break;

    case 'S':
      if (hdr->deleted)
	ch = 'D';
      else if (hdr->attach_del)
	ch = 'd';
      else if (hdr->tagged)
	ch = '*';
      else if (hdr->flagged)
	ch = '!';
      else if (hdr->replied)
	ch = 'r';
      else if (hdr->read && (ctx && ctx->msgnotreadyet != hdr->msgno))
	ch = '-';
      else if (hdr->old)
	ch = 'O';
      else
	ch = 'N';

      /* FOO - this is probably unsafe, but we are not likely to have such
	 a short string passed into this routine */
      *dest = ch;
      *(dest + 1) = 0;
      break;

    case 't':
      buf2[0] = 0;
      if (!check_for_mailing_list (hdr->env->to, "To ", buf2, sizeof (buf2)) &&
	  !check_for_mailing_list (hdr->env->cc, "Cc ", buf2, sizeof (buf2)))
      {
	if (hdr->env->to)
	  snprintf (buf2, sizeof (buf2), "To %s", mutt_get_name (hdr->env->to));
	else if (hdr->env->cc)
	  snprintf (buf2, sizeof (buf2), "Cc %s", mutt_get_name (hdr->env->cc));
      }
      mutt_format_s (dest, destlen, prefix, buf2);
      break;

    case 'T':
      snprintf (fmt, sizeof (fmt), "%%%sc", prefix);
      snprintf (dest, destlen, fmt,
		(Tochars && ((i = mutt_user_is_recipient (hdr))) < mutt_strlen (Tochars)) ? Tochars[i] : ' ');
      break;

    case 'u':
      if (hdr->env->from && hdr->env->from->mailbox)
      {
	strfcpy (buf2, mutt_addr_for_display (hdr->env->from), sizeof (buf2));
	if ((p = strpbrk (buf2, "%@")))
	  *p = 0;
      }
      else
	buf2[0] = 0;
      mutt_format_s (dest, destlen, prefix, buf2);
      break;

    case 'v':
      if (mutt_addr_is_user (hdr->env->from)) 
      {
	if (hdr->env->to)
	  mutt_format_s (buf2, sizeof (buf2), prefix, mutt_get_name (hdr->env->to));
	else if (hdr->env->cc)
	  mutt_format_s (buf2, sizeof (buf2), prefix, mutt_get_name (hdr->env->cc));
	else
	  *buf2 = 0;
      }
      else
	mutt_format_s (buf2, sizeof (buf2), prefix, mutt_get_name (hdr->env->from));
      if ((p = strpbrk (buf2, " %@")))
	*p = 0;
      mutt_format_s (dest, destlen, prefix, buf2);
      break;

    case 'Z':
    
      ch = ' ';

      if (WithCrypto && hdr->security & GOODSIGN)
        ch = 'S';
      else if (WithCrypto && hdr->security & ENCRYPT)
      	ch = 'P';
      else if (WithCrypto && hdr->security & SIGN)
        ch = 's';
      else if ((WithCrypto & APPLICATION_PGP) && hdr->security & PGPKEY)
        ch = 'K';

      snprintf (buf2, sizeof (buf2),
		"%c%c%c", (THREAD_NEW ? 'n' : (THREAD_OLD ? 'o' : 
		((hdr->read && (ctx && ctx->msgnotreadyet != hdr->msgno))
		? (hdr->replied ? 'r' : ' ') : (hdr->old ? 'O' : 'N')))),
		hdr->deleted ? 'D' : (hdr->attach_del ? 'd' : ch),
		hdr->tagged ? '*' :
		(hdr->flagged ? '!' :
		 (Tochars && ((i = mutt_user_is_recipient (hdr)) < mutt_strlen (Tochars)) ? Tochars[i] : ' ')));
      mutt_format_s (dest, destlen, prefix, buf2);
      break;

    case 'X':
      {
	int count = mutt_count_body_parts (ctx, hdr);

	/* The recursion allows messages without depth to return 0. */
	if (optional)
          optional = count != 0;

        snprintf (fmt, sizeof (fmt), "%%%sd", prefix);
        snprintf (dest, destlen, fmt, count);
      }
      break;

     case 'y':
       if (optional)
	 optional = hdr->env->x_label ? 1 : 0;

       mutt_format_s (dest, destlen, prefix, NONULL (hdr->env->x_label));
       break;
 
    case 'Y':
      if (hdr->env->x_label)
      {
	i = 1;	/* reduce reuse recycle */
	htmp = NULL;
	if (flags & M_FORMAT_TREE
	    && (hdr->thread->prev && hdr->thread->prev->message
		&& hdr->thread->prev->message->env->x_label))
	  htmp = hdr->thread->prev->message;
	else if (flags & M_FORMAT_TREE
		 && (hdr->thread->parent && hdr->thread->parent->message
		     && hdr->thread->parent->message->env->x_label))
	  htmp = hdr->thread->parent->message;
	if (htmp && mutt_strcasecmp (hdr->env->x_label,
				     htmp->env->x_label) == 0)
	  i = 0;
      }
      else
	i = 0;

      if (optional)
	optional = i;

      if (i)
        mutt_format_s (dest, destlen, prefix, NONULL (hdr->env->x_label));
      else
        mutt_format_s (dest, destlen, prefix, "");

      break;

    default:
      snprintf (dest, destlen, "%%%s%c", prefix, op);
      break;
  }

  if (optional)
    mutt_FormatString (dest, destlen, col, ifstring, hdr_format_str, (unsigned long) hfi, flags);
  else if (flags & M_FORMAT_OPTIONAL)
    mutt_FormatString (dest, destlen, col, elsestring, hdr_format_str, (unsigned long) hfi, flags);

  return (src);
#undef THREAD_NEW
#undef THREAD_OLD
}