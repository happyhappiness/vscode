void _mutt_select_file (char *f, size_t flen, int flags, char ***files, int *numfiles)
{
  char buf[_POSIX_PATH_MAX];
  char prefix[_POSIX_PATH_MAX] = "";
  char helpstr[LONG_STRING];
  char title[STRING];
  struct browser_state state;
  MUTTMENU *menu;
  struct stat st;
  int i, killPrefix = 0;
  int multiple = (flags & M_SEL_MULTI)  ? 1 : 0;
  int folder   = (flags & M_SEL_FOLDER) ? 1 : 0;
  int buffy    = (flags & M_SEL_BUFFY)  ? 1 : 0;

  buffy = buffy && folder;
  
  memset (&state, 0, sizeof (struct browser_state));

  if (!folder)
    strfcpy (LastDirBackup, LastDir, sizeof (LastDirBackup));

  if (*f)
  {
    mutt_expand_path (f, flen);
#ifdef USE_IMAP
    if (mx_is_imap (f))
    {
      init_state (&state, NULL);
      state.imap_browse = 1;
      if (!imap_browse (f, &state))
        strfcpy (LastDir, state.folder, sizeof (LastDir));
    }
    else
    {
#endif
    for (i = mutt_strlen (f) - 1; i > 0 && f[i] != '/' ; i--);
    if (i > 0)
    {
      if (f[0] == '/')
      {
	if (i > sizeof (LastDir) - 1) i = sizeof (LastDir) - 1;
	strncpy (LastDir, f, i);
	LastDir[i] = 0;
      }
      else
      {
	getcwd (LastDir, sizeof (LastDir));
	safe_strcat (LastDir, sizeof (LastDir), "/");
	safe_strncat (LastDir, sizeof (LastDir), f, i);
      }
    }
    else
    {
      if (f[0] == '/')
	strcpy (LastDir, "/");		/* __STRCPY_CHECKED__ */
      else
	getcwd (LastDir, sizeof (LastDir));
    }

    if (i <= 0 && f[0] != '/')
      strfcpy (prefix, f, sizeof (prefix));
    else
      strfcpy (prefix, f + i + 1, sizeof (prefix));
    killPrefix = 1;
#ifdef USE_IMAP
    }
#endif
  }
  else 
  {
    if (!folder)
      getcwd (LastDir, sizeof (LastDir));
    else if (!LastDir[0])
      strfcpy (LastDir, NONULL(Maildir), sizeof (LastDir));
    
#ifdef USE_IMAP
    if (!buffy && mx_is_imap (LastDir))
    {
      init_state (&state, NULL);
      state.imap_browse = 1;
      imap_browse (LastDir, &state);
      browser_sort (&state);
    }
    else
#endif
    {
      i = mutt_strlen (LastDir);
      while (i && LastDir[--i] == '/')
        LastDir[i] = '\0';
      if (!LastDir[0])
        getcwd (LastDir, sizeof (LastDir));
    }
  }

  *f = 0;

  if (buffy)
  {
    if (examine_mailboxes (NULL, &state) == -1)
      goto bail;
  }
  else
#ifdef USE_IMAP
  if (!state.imap_browse)
#endif
  if (examine_directory (NULL, &state, LastDir, prefix) == -1)
    goto bail;

  menu = mutt_new_menu (MENU_FOLDER);
  menu->make_entry = folder_entry;
  menu->search = select_file_search;
  menu->title = title;
  menu->data = state.entry;
  if (multiple)
    menu->tag = file_tag;

  menu->help = mutt_compile_help (helpstr, sizeof (helpstr), MENU_FOLDER,
    FolderHelp);

  init_menu (&state, menu, title, sizeof (title), buffy);

  FOREVER
  {
    switch (i = mutt_menuLoop (menu))
    {
      case OP_GENERIC_SELECT_ENTRY:

	if (!state.entrylen)
	{
	  mutt_error _("No files match the file mask");
	  break;
	}

        if (S_ISDIR (state.entry[menu->current].mode) ||
	    (S_ISLNK (state.entry[menu->current].mode) &&
	    link_is_dir (LastDir, state.entry[menu->current].name)) 
#ifdef USE_IMAP
	    || state.entry[menu->current].inferiors
#endif
	    )
	{
	  /* make sure this isn't a MH or maildir mailbox */
	  if (buffy)
	  {
	    strfcpy (buf, state.entry[menu->current].name, sizeof (buf));
	    mutt_expand_path (buf, sizeof (buf));
	  }
#ifdef USE_IMAP
	  else if (state.imap_browse)
	  {
            strfcpy (buf, state.entry[menu->current].name, sizeof (buf));
	  }
#endif
	  else
	    mutt_concat_path (buf, LastDir, state.entry[menu->current].name, sizeof (buf));

	  if ((mx_get_magic (buf) <= 0)
#ifdef USE_IMAP
	    || state.entry[menu->current].inferiors
#endif
	    )
	  {
	    char OldLastDir[_POSIX_PATH_MAX];

	    /* save the old directory */
	    strfcpy (OldLastDir, LastDir, sizeof (OldLastDir));

	    if (mutt_strcmp (state.entry[menu->current].name, "..") == 0)
	    {
	      if (mutt_strcmp ("..", LastDir + mutt_strlen (LastDir) - 2) == 0)
		strcat (LastDir, "/..");	/* __STRCAT_CHECKED__ */
	      else
	      {
		char *p = strrchr (LastDir + 1, '/');

		if (p)
		  *p = 0;
		else
		{
		  if (LastDir[0] == '/')
		    LastDir[1] = 0;
		  else
		    strcat (LastDir, "/..");	/* __STRCAT_CHECKED__ */
		}
	      }
	    }
	    else if (buffy)
	    {
	      strfcpy (LastDir, state.entry[menu->current].name, sizeof (LastDir));
	      mutt_expand_path (LastDir, sizeof (LastDir));
	    }
#ifdef USE_IMAP
	    else if (state.imap_browse)
	    {
	      int n;
	      ciss_url_t url;
	      
              strfcpy (LastDir, state.entry[menu->current].name,
                sizeof (LastDir));
	      /* tack on delimiter here */
	      n = strlen (LastDir)+1;
	      
	      /* special case "" needs no delimiter */
	      url_parse_ciss (&url, state.entry[menu->current].name);
	      if (url.path &&
		  (state.entry[menu->current].delim != '\0') &&
		  (n < sizeof (LastDir)))
	      {
		LastDir[n] = '\0';
		LastDir[n-1] = state.entry[menu->current].delim;
	      }
	    }
#endif
	    else
	    {
	      char tmp[_POSIX_PATH_MAX];
	      mutt_concat_path (tmp, LastDir, state.entry[menu->current].name, sizeof (tmp));
	      strfcpy (LastDir, tmp, sizeof (LastDir));
	    }

	    destroy_state (&state);
	    if (killPrefix)
	    {
	      prefix[0] = 0;
	      killPrefix = 0;
	    }
	    buffy = 0;
#ifdef USE_IMAP
	    if (state.imap_browse)
	    {
	      init_state (&state, NULL);
	      state.imap_browse = 1;
	      imap_browse (LastDir, &state);
	      browser_sort (&state);
	      menu->data = state.entry;
	    }
	    else
#endif
	    if (examine_directory (menu, &state, LastDir, prefix) == -1)
	    {
	      /* try to restore the old values */
	      strfcpy (LastDir, OldLastDir, sizeof (LastDir));
	      if (examine_directory (menu, &state, LastDir, prefix) == -1)
	      {
		strfcpy (LastDir, NONULL(Homedir), sizeof (LastDir));
		goto bail;
	      }
	    }
	    menu->current = 0; 
	    menu->top = 0; 
	    init_menu (&state, menu, title, sizeof (title), buffy);
	    break;
	  }
	}

	if (buffy)
	{
	  strfcpy (f, state.entry[menu->current].name, flen);
	  mutt_expand_path (f, flen);
	}
#ifdef USE_IMAP
	else if (state.imap_browse)
          strfcpy (f, state.entry[menu->current].name, flen);
#endif
	else
	  mutt_concat_path (f, LastDir, state.entry[menu->current].name, flen);

	/* Fall through to OP_EXIT */

      case OP_EXIT:

	if (multiple)
	{
	  char **tfiles;
	  int i, j;

	  if (menu->tagged)
	  {
	    *numfiles = menu->tagged;
	    tfiles = safe_calloc (*numfiles, sizeof (char *));
	    for (i = 0, j = 0; i < state.entrylen; i++)
	    {
	      struct folder_file ff = state.entry[i];
	      char full[_POSIX_PATH_MAX];
	      if (ff.tagged)
	      {
		mutt_concat_path (full, LastDir, ff.name, sizeof (full));
		mutt_expand_path (full, sizeof (full));
		tfiles[j++] = safe_strdup (full);
	      }
	    }
	    *files = tfiles;
	  }
	  else if (f[0]) /* no tagged entries. return selected entry */
	  {
	    *numfiles = 1;
	    tfiles = safe_calloc (*numfiles, sizeof (char *));
	    mutt_expand_path (f, flen);
	    tfiles[0] = safe_strdup (f);
	    *files = tfiles;
	  }
	}

	destroy_state (&state);
	mutt_menuDestroy (&menu);
	goto bail;

      case OP_BROWSER_TELL:
        if(state.entrylen)
	  mutt_message("%s", state.entry[menu->current].name);
        break;

#ifdef USE_IMAP
      case OP_BROWSER_SUBSCRIBE:
	imap_subscribe (state.entry[menu->current].name, 1);
	break;

      case OP_BROWSER_UNSUBSCRIBE:
	imap_subscribe (state.entry[menu->current].name, 0);
	break;

      case OP_BROWSER_TOGGLE_LSUB:
	if (option (OPTIMAPLSUB))
	  unset_option (OPTIMAPLSUB);
	else
	  set_option (OPTIMAPLSUB);

	mutt_unget_event (0, OP_CHECK_NEW);
	break;

      case OP_CREATE_MAILBOX:
	if (!state.imap_browse)
	{
	  mutt_error (_("Create is only supported for IMAP mailboxes"));
	  break;
	}

	if (!imap_mailbox_create (LastDir))
	{
	  /* TODO: find a way to detect if the new folder would appear in
	   *   this window, and insert it without starting over. */
	  destroy_state (&state);
	  init_state (&state, NULL);
	  state.imap_browse = 1;
	  imap_browse (LastDir, &state);
	  browser_sort (&state);
	  menu->data = state.entry;
	  menu->current = 0; 
	  menu->top = 0; 
	  init_menu (&state, menu, title, sizeof (title), buffy);
	  MAYBE_REDRAW (menu->redraw);
	}
	/* else leave error on screen */
	break;

      case OP_RENAME_MAILBOX:
	if (!state.entry[menu->current].imap)
	  mutt_error (_("Rename is only supported for IMAP mailboxes"));
	else
	{
	  int nentry = menu->current;

	  if (imap_mailbox_rename (state.entry[nentry].name) >= 0)
	  {
	    destroy_state (&state);
	    init_state (&state, NULL);
	    state.imap_browse = 1;
	    imap_browse (LastDir, &state);
	    browser_sort (&state);
	    menu->data = state.entry;
	    menu->current = 0;
	    menu->top = 0;
	    init_menu (&state, menu, title, sizeof (title), buffy);
	    MAYBE_REDRAW (menu->redraw);
	  }
	}
	break;

    case OP_DELETE_MAILBOX:
	if (!state.entry[menu->current].imap)
	  mutt_error (_("Delete is only supported for IMAP mailboxes"));
	else
        {
	  char msg[SHORT_STRING];
	  IMAP_MBOX mx;
	  int nentry = menu->current;

	  imap_parse_path (state.entry[nentry].name, &mx);
	  if (!mx.mbox)
	  {
	    mutt_error _("Cannot delete root folder");
	    break;
	  }
	  snprintf (msg, sizeof (msg), _("Really delete mailbox \"%s\"?"),
            mx.mbox);
	  if (mutt_yesorno (msg, M_NO) == M_YES)
          {
	    if (!imap_delete_mailbox (Context, mx))
            {
	      /* free the mailbox from the browser */
	      FREE (&((state.entry)[nentry].name));
	      FREE (&((state.entry)[nentry].desc));
	      /* and move all other entries up */
	      if (nentry+1 < state.entrylen)
		memmove (state.entry + nentry, state.entry + nentry + 1,
                  sizeof (struct folder_file) * (state.entrylen - (nentry+1)));
	      state.entrylen--;
	      mutt_message _("Mailbox deleted.");
	      init_menu (&state, menu, title, sizeof (title), buffy);
	      MAYBE_REDRAW (menu->redraw);
	    }
	  }
	  else
	    mutt_message _("Mailbox not deleted.");
	  FREE (&mx.mbox);
        }
        break;
#endif
      
      case OP_CHANGE_DIRECTORY:

	strfcpy (buf, LastDir, sizeof (buf));
#ifdef USE_IMAP
	if (!state.imap_browse)
#endif
	{
	  /* add '/' at the end of the directory name if not already there */
	  int len=mutt_strlen(LastDir);
	  if (len && LastDir[len-1] != '/' && sizeof (buf) > len)
	    buf[len]='/';
	}

	if (mutt_get_field (_("Chdir to: "), buf, sizeof (buf), M_FILE) == 0 &&
	    buf[0])
	{
	  buffy = 0;	  
	  mutt_expand_path (buf, sizeof (buf));
#ifdef USE_IMAP
	  if (mx_is_imap (buf))
	  {
	    strfcpy (LastDir, buf, sizeof (LastDir));
	    destroy_state (&state);
	    init_state (&state, NULL);
	    state.imap_browse = 1;
	    imap_browse (LastDir, &state);
	    browser_sort (&state);
	    menu->data = state.entry;
	    menu->current = 0; 
	    menu->top = 0; 
	    init_menu (&state, menu, title, sizeof (title), buffy);
	  }
	  else
#endif
	  {
	    if (*buf != '/')
	    {
	      /* in case dir is relative, make it relative to LastDir,
	       * not current working dir */
	      char tmp[_POSIX_PATH_MAX];
	      mutt_concat_path (tmp, LastDir, buf, sizeof (tmp));
	      strfcpy (buf, tmp, sizeof (buf));
	    }
	    if (stat (buf, &st) == 0)
	    {
	      if (S_ISDIR (st.st_mode))
	      {
		destroy_state (&state);
		if (examine_directory (menu, &state, buf, prefix) == 0)
		  strfcpy (LastDir, buf, sizeof (LastDir));
		else
		{
		  mutt_error _("Error scanning directory.");
		  if (examine_directory (menu, &state, LastDir, prefix) == -1)
		  {
		    mutt_menuDestroy (&menu);
		    goto bail;
		  }
		}
		menu->current = 0;
		menu->top = 0;
		init_menu (&state, menu, title, sizeof (title), buffy);
	      }
	      else
		mutt_error (_("%s is not a directory."), buf);
	    }
	    else
	      mutt_perror (buf);
	  }
	}
	MAYBE_REDRAW (menu->redraw);
	break;
	
      case OP_ENTER_MASK:

	strfcpy (buf, NONULL(Mask.pattern), sizeof (buf));
	if (mutt_get_field (_("File Mask: "), buf, sizeof (buf), 0) == 0)
	{
	  regex_t *rx = (regex_t *) safe_malloc (sizeof (regex_t));
	  char *s = buf;
	  int not = 0, err;

	  buffy = 0;
	  /* assume that the user wants to see everything */
	  if (!buf[0])
	    strfcpy (buf, ".", sizeof (buf));
	  SKIPWS (s);
	  if (*s == '!')
	  {
	    s++;
	    SKIPWS (s);
	    not = 1;
	  }

	  if ((err = REGCOMP (rx, s, REG_NOSUB)) != 0)
	  {
	    regerror (err, rx, buf, sizeof (buf));
	    FREE (&rx);
	    mutt_error ("%s", buf);
	  }
	  else
	  {
	    mutt_str_replace (&Mask.pattern, buf);
	    regfree (Mask.rx);
	    FREE (&Mask.rx);
	    Mask.rx = rx;
	    Mask.not = not;

	    destroy_state (&state);
#ifdef USE_IMAP
	    if (state.imap_browse)
	    {
	      init_state (&state, NULL);
	      state.imap_browse = 1;
	      imap_browse (LastDir, &state);
	      browser_sort (&state);
	      menu->data = state.entry;
	      init_menu (&state, menu, title, sizeof (title), buffy);
	    }
	    else
#endif
	    if (examine_directory (menu, &state, LastDir, NULL) == 0)
	      init_menu (&state, menu, title, sizeof (title), buffy);
	    else
	    {
	      mutt_error _("Error scanning directory.");
	      mutt_menuDestroy (&menu);
	      goto bail;
	    }
	    killPrefix = 0;
	    if (!state.entrylen)
	    {
	      mutt_error _("No files match the file mask");
	      break;
	    }
	  }
	}
	MAYBE_REDRAW (menu->redraw);
	break;

      case OP_SORT:
      case OP_SORT_REVERSE:

        {
	  int resort = 1;
	  int reverse = (i == OP_SORT_REVERSE);
	  
	  switch (mutt_multi_choice ((reverse) ?
	      _("Reverse sort by (d)ate, (a)lpha, si(z)e or do(n)'t sort? ") :
	      _("Sort by (d)ate, (a)lpha, si(z)e or do(n)'t sort? "),
	      _("dazn")))
	  {
	    case -1: /* abort */
	      resort = 0;
	      break;

            case 1: /* (d)ate */
	      BrowserSort = SORT_DATE;
	      break;

            case 2: /* (a)lpha */
	      BrowserSort = SORT_SUBJECT;
	      break;

            case 3: /* si(z)e */
	      BrowserSort = SORT_SIZE;
	      break;

            case 4: /* do(n)'t sort */
	      BrowserSort = SORT_ORDER;
	      resort = 0;
	      break;
	  }
	  if (resort)
	  {
	    BrowserSort |= reverse ? SORT_REVERSE : 0;
	    browser_sort (&state);
	    menu->redraw = REDRAW_FULL;
	  }
	  break;
	}

      case OP_TOGGLE_MAILBOXES:
	buffy = 1 - buffy;

      case OP_CHECK_NEW:
	destroy_state (&state);
	prefix[0] = 0;
	killPrefix = 0;

	if (buffy)
	{
	  if (examine_mailboxes (menu, &state) == -1)
	    goto bail;
	}
#ifdef USE_IMAP
	else if (mx_is_imap (LastDir))
	{
	  init_state (&state, NULL);
	  state.imap_browse = 1;
	  imap_browse (LastDir, &state);
	  browser_sort (&state);
	  menu->data = state.entry;
	}
#endif
	else if (examine_directory (menu, &state, LastDir, prefix) == -1)
	  goto bail;
	init_menu (&state, menu, title, sizeof (title), buffy);
	break;

      case OP_BUFFY_LIST:
	mutt_buffy_list ();
	break;

      case OP_BROWSER_NEW_FILE:

	snprintf (buf, sizeof (buf), "%s/", LastDir);
	if (mutt_get_field (_("New file name: "), buf, sizeof (buf), M_FILE) == 0)
	{
	  strfcpy (f, buf, flen);
	  destroy_state (&state);
	  mutt_menuDestroy (&menu);
	  goto bail;
	}
	MAYBE_REDRAW (menu->redraw);
	break;

      case OP_BROWSER_VIEW_FILE:
	if (!state.entrylen)
	{
	  mutt_error _("No files match the file mask");
	  break;
	}

#ifdef USE_IMAP
	if (state.entry[menu->current].selectable)
	{
	  strfcpy (f, state.entry[menu->current].name, flen);
	  destroy_state (&state);
	  mutt_menuDestroy (&menu);
	  goto bail;
	}
	else
#endif
        if (S_ISDIR (state.entry[menu->current].mode) ||
	    (S_ISLNK (state.entry[menu->current].mode) &&
	    link_is_dir (LastDir, state.entry[menu->current].name)))
	{
	  mutt_error _("Can't view a directory");
	  break;
	} 
	else
	{
	  BODY *b;
	  char buf[_POSIX_PATH_MAX];
	  
	  mutt_concat_path (buf, LastDir, state.entry[menu->current].name, sizeof (buf));
	  b = mutt_make_file_attach (buf);
	  if (b != NULL)
	  {
	    mutt_view_attachment (NULL, b, M_REGULAR, NULL, NULL, 0);
	    mutt_free_body (&b);
	    menu->redraw = REDRAW_FULL;
	  }
	  else
	    mutt_error _("Error trying to view file");
	}
    }
  }
  
  bail:
  
  if (!folder)
    strfcpy (LastDir, LastDirBackup, sizeof (LastDir));
  
}