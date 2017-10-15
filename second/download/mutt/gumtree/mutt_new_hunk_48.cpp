  ** This variable contains the path to the Mixmaster binary on your
  ** system.  It is used with various sets of parameters to gather the
  ** list of known remailers, and to finally send a message through the
  ** mixmaster chain.
  */
#endif
  { "move",		DT_QUAD, R_NONE, OPT_MOVE, M_NO },
  /*
  ** .pp
  ** Controls whether or not Mutt will move read messages
  ** from your spool mailbox to your $$mbox mailbox, or as a result of
  ** a ``$mbox-hook'' command.
  */
  { "narrow_tree",	DT_BOOL, R_TREE|R_INDEX, OPTNARROWTREE, 0 },
  /*
  ** .pp
  ** This variable, when \fIset\fP, makes the thread tree narrower, allowing
  ** deeper threads to fit on the screen.
  */
#ifdef USE_SOCKET
  { "net_inc",	DT_NUM,	 R_NONE, UL &NetInc, 10 },
  /*
   ** .pp
   ** Operations that expect to transfer a large amount of data over the
   ** network will update their progress every $$net_inc kilobytes.
   ** If set to 0, no progress messages will be displayed.
   ** .pp
   ** See also $$read_inc, $$write_inc and $$net_inc.
   */
#endif
  { "pager",		DT_PATH, R_NONE, UL &Pager, UL "builtin" },
  /*
  ** .pp
  ** This variable specifies which pager you would like to use to view
  ** messages. The value ``builtin'' means to use the built-in pager, otherwise this
  ** variable should specify the pathname of the external pager you would
  ** like to use.
  ** .pp
  ** Using an external pager may have some disadvantages: Additional
  ** keystrokes are necessary because you can't call mutt functions
  ** directly from the pager, and screen resizes cause lines longer than
