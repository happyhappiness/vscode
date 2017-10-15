  ** This variable contains the path to the Mixmaster binary on your
  ** system.  It is used with various sets of parameters to gather the
  ** list of known remailers, and to finally send a message through the
  ** mixmaster chain.
  */
#endif


  { "move",		DT_QUAD, R_NONE, OPT_MOVE, M_ASKNO },
  /*
  ** .pp
  ** Controls whether you will be asked to confirm moving read messages
  ** from your spool mailbox to your ``$$mbox'' mailbox, or as a result of
  ** a ``$mbox-hook'' command.
  */
  { "message_format",	DT_STR,	 R_NONE, UL &MsgFmt, UL "%s" },
  /*
  ** .pp
  ** This is the string displayed in the ``attachment'' menu for
  ** attachments of type message/rfc822.  For a full listing of defined
  ** printf()-like sequences see the section on ``$$index_format''.
  */
  { "msg_format",	DT_SYN,  R_NONE, UL "message_format", 0 },
  /*
  */
  { "pager",		DT_PATH, R_NONE, UL &Pager, UL "builtin" },
  /*
  ** .pp
  ** This variable specifies which pager you would like to use to view
  ** messages.  builtin means to use the builtin pager, otherwise this
  ** variable should specify the pathname of the external pager you would
  ** like to use.
  ** .pp
  ** Using an external pager may have some disadvantages: Additional
  ** keystrokes are necessary because you can't call mutt functions
  ** directly from the pager, and screen resizes cause lines longer than
