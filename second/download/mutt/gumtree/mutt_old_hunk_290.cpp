          ctx->hdrs[idx]->changed = h.data->changed;
          /*  ctx->hdrs[msgno]->received is restored from mutt_hcache_restore */
          ctx->hdrs[idx]->data = (void *) (h.data);

          ctx->msgcount++;
          ctx->size += ctx->hdrs[idx]->content->length;
        }
	else
        {
	  /* bad header in the cache, we'll have to refetch. */
          dprint (3, (debugfile, "bad cache entry at %d, giving up\n", h.sid - 1));
          imap_free_header_data(&h.data);
          evalhc = 0;
          idx--;
        }
      }
      while (rc != IMAP_CMD_OK && mfhrc == -1);
      if (rc == IMAP_CMD_OK)
        break;
      if ((mfhrc < -1) || ((rc != IMAP_CMD_CONTINUE) && (rc != IMAP_CMD_OK)))
      {
        imap_free_header_data (&h.data);
        imap_hcache_close (idata);
	goto error_out_1;
      }
    }
    /* could also look for first null header in case hcache is holey */
    msgbegin = ctx->msgcount;
  }
#endif /* USE_HCACHE */

  mutt_progress_init (&progress, _("Fetching message headers..."),
		      MUTT_PROGRESS_MSG, ReadInc, msgend + 1);

  for (msgno = msgbegin; msgno <= msgend ; msgno++)
  {
    mutt_progress_update (&progress, msgno + 1, -1);

    /* we may get notification of new mail while fetching headers */
    if (msgno + 1 > fetchlast)
    {
      char *cmd;

      fetchlast = msgend + 1;
      safe_asprintf (&cmd, "FETCH %d:%d (UID FLAGS INTERNALDATE RFC822.SIZE %s)",
                     msgno + 1, fetchlast, hdrreq);
      imap_cmd_start (idata, cmd);
      FREE (&cmd);
    }

    rewind (fp);
    memset (&h, 0, sizeof (h));
    h.data = safe_calloc (1, sizeof (IMAP_HEADER_DATA));

    /* this DO loop does two things:
     * 1. handles untagged messages, so we can try again on the same msg
     * 2. fetches the tagged response at the end of the last message.
     */
    do
    {
      mfhrc = 0;

      rc = imap_cmd_step (idata);
      if (rc != IMAP_CMD_CONTINUE)
	break;

      if ((mfhrc = msg_fetch_header (ctx, &h, idata->buf, fp)) == -1)
	continue;
      else if (mfhrc < 0)
	break;

      if (!ftello (fp))
      {
        dprint (2, (debugfile, "msg_fetch_header: ignoring fetch response with no body\n"));
        mfhrc = -1;
        msgend--;
        continue;
      }

      /* make sure we don't get remnants from older larger message headers */
      fputs ("\n\n", fp);

      idx++;
      if (idx > msgend)
      {
        dprint (1, (debugfile, "imap_read_headers: skipping FETCH response for "
                    "unknown message number %d\n", h.sid));
        mfhrc = -1;
        idx--;
        continue;
      }
      /* May receive FLAGS updates in a separate untagged response (#2935) */
      if (idx < ctx->msgcount)
      {
	dprint (2, (debugfile, "imap_read_headers: message %d is not new\n",
		    h.sid));
        idx--;
	continue;
      }

      ctx->hdrs[idx] = mutt_new_header ();

      ctx->hdrs[idx]->index = h.sid - 1;
      /* messages which have not been expunged are ACTIVE (borrowed from mh
       * folders) */
      ctx->hdrs[idx]->active = 1;
      ctx->hdrs[idx]->read = h.data->read;
      ctx->hdrs[idx]->old = h.data->old;
      ctx->hdrs[idx]->deleted = h.data->deleted;
      ctx->hdrs[idx]->flagged = h.data->flagged;
      ctx->hdrs[idx]->replied = h.data->replied;
      ctx->hdrs[idx]->changed = h.data->changed;
      ctx->hdrs[idx]->received = h.received;
      ctx->hdrs[idx]->data = (void *) (h.data);

      if (maxuid < h.data->uid)
        maxuid = h.data->uid;

      rewind (fp);
      /* NOTE: if Date: header is missing, mutt_read_rfc822_header depends
       *   on h.received being set */
      ctx->hdrs[idx]->env = mutt_read_rfc822_header (fp, ctx->hdrs[idx],
        0, 0);
      /* content built as a side-effect of mutt_read_rfc822_header */
      ctx->hdrs[idx]->content->length = h.content_length;
      ctx->size += h.content_length;

#if USE_HCACHE
      imap_hcache_put (idata, ctx->hdrs[idx]);
#endif /* USE_HCACHE */

      ctx->msgcount++;
    }
    while ((rc != IMAP_CMD_OK) && ((mfhrc == -1) ||
      ((msgno + 1) >= fetchlast)));

    if ((mfhrc < -1) || ((rc != IMAP_CMD_CONTINUE) && (rc != IMAP_CMD_OK)))
    {
      imap_free_header_data (&h.data);
#if USE_HCACHE
      imap_hcache_close (idata);
#endif
      goto error_out_1;
    }

    /* in case we get new mail while fetching the headers */
    if (idata->reopen & IMAP_NEWMAIL_PENDING)
    {
      msgend = idata->newMailCount - 1;
      while ((msgend) >= ctx->hdrmax)
	mx_alloc_memory (ctx);
      idata->reopen &= ~IMAP_NEWMAIL_PENDING;
      idata->newMailCount = 0;
    }
  }

  if (maxuid && (status = imap_mboxcache_get (idata, idata->mailbox, 0)) &&
