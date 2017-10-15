  ** Controls whether 8-bit data is converted to 7-bit using either Quoted-
  ** Printable or Base64 encoding when sending mail.
  */
  { "allow_ansi",      DT_BOOL, R_NONE, OPTALLOWANSI, 0 },
  /*
  ** .pp
  ** Controls whether ANSI color codes in messages (and color tags in 
  ** rich text messages) are to be interpreted.
  ** Messages containing these codes are rare, but if this option is set,
  ** their text will be colored accordingly. Note that this may override
  ** your color choices, and even present a security problem, since a
  ** message could include a line like "[-- PGP output follows ..." and
  ** give it the same color as your attachment color.
  */
  { "alternates",	DT_RX,	 R_BOTH, UL &Alternates, 0 },
  /*
  ** .pp
  ** A regexp that allows you to specify \fIalternate\fP addresses where
  ** you receive mail.  This affects Mutt's idea about messages from you
  ** and addressed to you.
  */
  { "arrow_cursor",	DT_BOOL, R_BOTH, OPTARROWCURSOR, 0 },
  /*
  ** .pp
  ** When set, an arrow (``->'') will be used to indicate the current entry
  ** in menus instead of hiliting the whole line.  On slow network or modem
  ** links this will make response faster because there is less that has to
  ** be redrawn on the screen when moving to the next or previous entries
  ** in the menu.
  */
  { "ascii_chars",	DT_BOOL, R_BOTH, OPTASCIICHARS, 0 },
  /*
  ** .pp
  ** If set, Mutt will use plain ASCII characters when displaying thread
  ** and attachment trees, instead of the default \fIACS\fP characters.
  */
  { "askbcc",		DT_BOOL, R_NONE, OPTASKBCC, 0 },
  /*
  ** .pp
  ** If set, Mutt will prompt you for blind-carbon-copy (Bcc) recipients
  ** before editing an outgoing message.
  */
  { "askcc",		DT_BOOL, R_NONE, OPTASKCC, 0 },
  /*
  ** .pp
  ** If set, Mutt will prompt you for carbon-copy (Cc) recipients before
  ** editing the body of an outgoing message.
  */  
  { "attach_format",	DT_STR,  R_NONE, UL &AttachFormat, UL "%u%D%I %t%4n %T%.40d%> [%.7m/%.10M, %.6e%?C?, %C?, %s] " },
  /*
  ** .pp
  ** This variable describes the format of the `attachment' menu.  The
  ** following printf-style sequences are understood:
  ** .pp
  ** .dl
  ** .dt %D  .dd deleted flag
  ** .dt %d  .dd description
  ** .dt %e  .dd MIME content-transfer-encoding
  ** .dt %f  .dd filename
  ** .dt %I  .dd disposition (I=inline, A=attachment)
  ** .dt %m  .dd major MIME type
  ** .dt %M  .dd MIME subtype
  ** .dt %n  .dd attachment number
  ** .dt %s  .dd size
  ** .dt %t  .dd tagged flag
  ** .dt %u  .dd unlink (=to delete) flag
  ** .dt %>X .dd right justify the rest of the string and pad with character "X"
  ** .dt %|X .dd pad to the end of the line with character "X"
  ** .de
  */
  { "attach_sep",	DT_STR,	 R_NONE, UL &AttachSep, UL "\n" },
  /*
  ** .pp
  ** The separator to add between attachments when operating (saving,
  ** printing, piping, etc) on a list of tagged attachments.
  */
  { "attach_split",	DT_BOOL, R_NONE, OPTATTACHSPLIT, 1 },
  /*
  ** .pp
  ** If this variable is unset, when operating (saving, printing, piping,
  ** etc) on a list of tagged attachments, Mutt will concatenate the
  ** attachments and will operate on them as a single attachment. The
  ** ``$$attach_sep'' separator is added after each attachment. When set,
  ** Mutt will operate on the attachments one by one.
  */
  { "attribution",	DT_STR,	 R_NONE, UL &Attribution, UL "On %d, %n wrote:" },
  /*
  ** .pp
  ** This is the string that will precede a message which has been included
  ** in a reply.  For a full listing of defined printf()-like sequences see
  ** the section on ``$$index_format''.
  */
  { "autoedit",		DT_BOOL, R_NONE, OPTAUTOEDIT, 0 },
  /*
  ** .pp
  ** When set along with ``$$edit_headers'', Mutt will skip the initial
  ** send-menu and allow you to immediately begin editing the body of your
  ** message.  The send-menu may still be accessed once you have finished
  ** editing the body of your message.
  ** .pp
  ** Also see ``$$fast_reply''.
  */
  { "auto_tag",		DT_BOOL, R_NONE, OPTAUTOTAG, 0 },
  /*
  ** .pp
  ** When set, functions in the \fIindex\fP menu which affect a message
  ** will be applied to all tagged messages (if there are any).  When
  ** unset, you must first use the tag-prefix function (default: ";") to
  ** make the next function apply to all tagged messages.
  */
  { "beep",		DT_BOOL, R_NONE, OPTBEEP, 1 },
  /*
  ** .pp
  ** When this variable is set, mutt will beep when an error occurs.
  */
  { "beep_new",		DT_BOOL, R_NONE, OPTBEEPNEW, 0 },
  /*
  ** .pp
  ** When this variable is set, mutt will beep whenever it prints a message
  ** notifying you of new mail.  This is independent of the setting of the
  ** ``$$beep'' variable.
  */
  { "bounce_delivered", DT_BOOL, R_NONE, OPTBOUNCEDELIVERED, 1 },
  /*
  ** .pp
  ** When this variable is set, mutt will include Delivered-To headers when
  ** bouncing messages.  Postfix users may wish to unset this variable.
  */
  { "charset",		DT_STR,	 R_NONE, UL &Charset, UL 0 },
  /*
  ** .pp
  ** Character set your terminal uses to display and enter textual data.
  */
  { "check_new",	DT_BOOL, R_NONE, OPTCHECKNEW, 1 },
  /*
  ** .pp
  ** \fBNote:\fP this option only affects \fImaildir\fP and \fIMH\fP style
  ** mailboxes.
  ** .pp
  ** When \fIset\fP, Mutt will check for new mail delivered while the
  ** mailbox is open.  Especially with MH mailboxes, this operation can
  ** take quite some time since it involves scanning the directory and
  ** checking each file to see if it has already been looked at.  If
  ** \fIcheck_new\fP is \fIunset\fP, no check for new mail is performed
  ** while the mailbox is open.
  */
  { "collapse_unread",	DT_BOOL, R_NONE, OPTCOLLAPSEUNREAD, 1 },
  /*
  ** .pp
  ** When \fIunset\fP, Mutt will not collapse a thread if it contains any
  ** unread messages.
  */
  { "uncollapse_jump", 	DT_BOOL, R_NONE, OPTUNCOLLAPSEJUMP, 0 },
  /*
  ** .pp
  ** When \fIset\fP, Mutt will jump to the next unread message, if any,
  ** when the current thread is \fIun\fPcollapsed.
  */
  { "compose_format",	DT_STR,	 R_BOTH, UL &ComposeFormat, UL "-- Mutt: Compose  [Approx. msg size: %l   Atts: %a]%>-" },
  /*
  ** .pp
  ** Controls the format of the status line displayed in the \fCompose\fP
  ** menu.  This string is similar to ``$$status_format'', but has its own
  ** set of printf()-like sequences:
  ** .pp
  ** .dl
  ** .dt %a .dd total number of attachments 
  ** .dt %h .dd local hostname
  ** .dt %l .dd approximate size (in bytes) of the current message
  ** .dt %v .dd Mutt version string
  ** .de
  ** .pp
  ** See the text describing the ``$$status_format'' option for more 
  ** information on how to set ``$$compose_format''.
  */
  { "confirmappend",	DT_BOOL, R_NONE, OPTCONFIRMAPPEND, 1 },
  /*
  ** .pp
  ** When set, Mutt will prompt for confirmation when appending messages to
  ** an existing mailbox.
  */
  { "confirmcreate",	DT_BOOL, R_NONE, OPTCONFIRMCREATE, 1 },
  /*
  ** .pp
  ** When set, Mutt will prompt for confirmation when saving messages to a
  ** mailbox which does not yet exist before creating it.
  */
  { "connect_timeout",	DT_NUM,	R_NONE, UL &ConnectTimeout, 30 },
  /*
  ** .pp
  ** Causes Mutt to timeout a network connection (for IMAP or POP) after this
  ** many seconds if the connection is not able to be established.  A negative
  ** value causes Mutt to wait indefinitely for the connection to succeed.
  */
  { "copy",		DT_QUAD, R_NONE, OPT_COPY, M_YES },
  /*
  ** .pp
  ** This variable controls whether or not copies of your outgoing messages
  ** will be saved for later references.  Also see ``$$record'',
  ** ``$$save_name'', ``$$force_name'' and ``$fcc-hook''.
  */
  { "date_format",	DT_STR,	 R_BOTH, UL &DateFmt, UL "!%a, %b %d, %Y at %I:%M:%S%p %Z" },
  /*
  ** .pp
  ** This variable controls the format of the date printed by the ``%d''
  ** sequence in ``$$index_format''.  This is passed to the \fIstrftime\fP
  ** call to process the date. See the man page for \fIstrftime(3)\fP for
  ** the proper syntax.
  ** .pp
  ** Unless the first character in the string is a bang (``!''), the month
  ** and week day names are expanded according to the locale specified in
  ** the variable ``$$locale''. If the first character in the string is a
  ** bang, the bang is discarded, and the month and week day names in the
  ** rest of the string are expanded in the \fIC\fP locale (that is in US
  ** English).
  */  
  { "default_hook",	DT_STR,	 R_NONE, UL &DefaultHook, UL "~f %s !~P | (~P ~C %s)" },
  /*
  ** .pp
  ** This variable controls how send-hooks, message-hooks, save-hooks,
  ** and fcc-hooks will
  ** be interpreted if they are specified with only a simple regexp,
  ** instead of a matching pattern.  The hooks are expanded when they are
  ** declared, so a hook will be interpreted according to the value of this
  ** variable at the time the hook is declared.  The default value matches
  ** if the message is either from a user matching the regular expression
  ** given, or if it is from you (if the from address matches
  ** ``$$alternates'') and is to or cc'ed to a user matching the given
  ** regular expression.
  */
  { "delete",		DT_QUAD, R_NONE, OPT_DELETE, M_ASKYES },
  /*
  ** .pp
  ** Controls whether or not messages are really deleted when closing or
