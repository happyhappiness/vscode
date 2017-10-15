      else
	offset = Context->hdrs[n]->content->offset;
      buf = be_snarf_data (Context->fp, buf, bufmax, buflen, offset, bytes,
			   pfx);

      if (*bufmax == *buflen)
	safe_realloc ((void **)&buf, sizeof (char *) * (*bufmax += 25));
      buf[(*buflen)++] = safe_strdup ("\n");
    }
    else
      printw (_("%d: invalid message number.\n"), n);
    msg = NULL;
  }
