          ctx->hdrs[idx]->changed = h.data->changed;
          /*  ctx->hdrs[msgno]->received is restored from mutt_hcache_restore */
          ctx->hdrs[idx]->data = (void *) (h.data);

          ctx->msgcount++;
          ctx->size += ctx->hdrs[idx]->content->length;

          h.data = NULL;
          idx++;
        }
      }
      while (mfhrc == -1);

      imap_free_header_data (&h.data);

      if ((mfhrc < -1) || ((rc != IMAP_CMD_CONTINUE) && (rc != IMAP_CMD_OK)))
      {
        imap_hcache_close (idata);
	goto error_out_1;
      }
    }

    /* Look for the first empty MSN and start there */
    while (msn_begin <= msn_end)
    {
      if (!idata->msn_index[msn_begin -1])
        break;
      msn_begin++;
    }
  }
#endif /* USE_HCACHE */

  mutt_progress_init (&progress, _("Fetching message headers..."),
		      MUTT_PROGRESS_MSG, ReadInc, msn_end);

  while (msn_begin <= msn_end && fetch_msn_end < msn_end)
  {
    char *cmd;
    BUFFER *b;

    b = mutt_buffer_new ();
    if (evalhc)
    {
      /* In case there are holes in the header cache. */
      evalhc = 0;
      imap_generate_seqset (b, idata, msn_begin, msn_end);
    }
    else
      mutt_buffer_printf (b, "%u:%u", msn_begin, msn_end);

    fetch_msn_end = msn_end;
    safe_asprintf (&cmd, "FETCH %s (UID FLAGS INTERNALDATE RFC822.SIZE %s)",
                   b->data, hdrreq);
    imap_cmd_start (idata, cmd);
    FREE (&cmd);
    mutt_buffer_free (&b);

    rc = IMAP_CMD_CONTINUE;
    for (msgno = msn_begin; rc == IMAP_CMD_CONTINUE; msgno++)
    {
      mutt_progress_update (&progress, msgno, -1);

      rewind (fp);
      memset (&h, 0, sizeof (h));
      h.data = safe_calloc (1, sizeof (IMAP_HEADER_DATA));

      /* this DO loop does two things:
       * 1. handles untagged messages, so we can try again on the same msg
       * 2. fetches the tagged response at the end of the last message.
       */
      do
      {
        rc = imap_cmd_step (idata);
        if (rc != IMAP_CMD_CONTINUE)
          break;

        if ((mfhrc = msg_fetch_header (ctx, &h, idata->buf, fp)) < 0)
          continue;

        if (!ftello (fp))
        {
          dprint (2, (debugfile, "msg_fetch_header: ignoring fetch response with no body\n"));
          continue;
        }

        /* make sure we don't get remnants from older larger message headers */
        fputs ("\n\n", fp);

        if (h.data->msn < 1 || h.data->msn > fetch_msn_end)
        {
          dprint (1, (debugfile, "imap_read_headers: skipping FETCH response for "
                      "unknown message number %d\n", h.data->msn));
          continue;
        }

        /* May receive FLAGS updates in a separate untagged response (#2935) */
        if (idata->msn_index[h.data->msn - 1])
        {
          dprint (2, (debugfile, "imap_read_headers: skipping FETCH response for "
                      "duplicate message %d\n", h.data->msn));
          continue;
        }

        ctx->hdrs[idx] = mutt_new_header ();

        idata->max_msn = MAX (idata->max_msn, h.data->msn);
        idata->msn_index[h.data->msn - 1] = ctx->hdrs[idx];

        ctx->hdrs[idx]->index = idx;
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

        h.data = NULL;
        idx++;
      }
      while (mfhrc == -1);

      imap_free_header_data (&h.data);

      if ((mfhrc < -1) || ((rc != IMAP_CMD_CONTINUE) && (rc != IMAP_CMD_OK)))
      {
#if USE_HCACHE
        imap_hcache_close (idata);
#endif
        goto error_out_1;
      }
    }

    /* In case we get new mail while fetching the headers.
     *
     * Note: The RFC says we shouldn't get any EXPUNGE responses in the
     * middle of a FETCH.  But just to be cautious, use the current state
     * of max_msn, not fetch_msn_end to set the next start range.
     */
    if (idata->reopen & IMAP_NEWMAIL_PENDING)
    {
      /* update to the last value we actually pulled down */
      fetch_msn_end = idata->max_msn;
      msn_begin = idata->max_msn + 1;
      msn_end = idata->newMailCount;
      while (msn_end > ctx->hdrmax)
	mx_alloc_memory (ctx);
      imap_alloc_msn_index (idata, msn_end);
      idata->reopen &= ~IMAP_NEWMAIL_PENDING;
      idata->newMailCount = 0;
    }
  }

  if (maxuid && (status = imap_mboxcache_get (idata, idata->mailbox, 0)) &&
