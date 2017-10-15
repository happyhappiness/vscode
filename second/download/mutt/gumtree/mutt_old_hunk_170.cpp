	}
	t = t->next;
      }
      mutt_free_list (&attach);
    }

    rv = ci_send_message (sendflags, msg, tempfile, NULL, NULL);

    if (!option (OPTNOCURSES))
      mutt_endwin (NULL);

    if (rv)
      exit(1);
