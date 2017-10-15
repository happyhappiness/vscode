  ** will be informed as to where to find the output.
  */
  { "shell",		DT_PATH, R_NONE, UL &Shell, 0 },
  /*
  ** .pp
  ** Command to use when spawning a subshell.  By default, the user's login
  ** shell from /etc/passwd is used.
  */
  { "sig_dashes",	DT_BOOL, R_NONE, OPTSIGDASHES, 1 },
  /*
  ** .pp
  ** If set, a line containing ``-- '' will be inserted before your
  ** ``$$signature''.  It is \fBstrongly\fP recommended that you not unset
  ** this variable unless your ``signature'' contains just your name.  The
  ** reason for this is because many software packages use ``-- \n'' to
  ** detect your signature.  For example, Mutt has the ability to highlight
  ** the signature in a different color in the builtin pager.
  */
  { "sig_on_top",	DT_BOOL, R_NONE, OPTSIGONTOP, 0},
  /*
  ** .pp
  ** If set, the signature will be included before any quoted or forwarded
  ** text.  It is \fBstrongly\fP recommended that you do not set this variable
  ** unless you really know what you are doing, and are prepared to take
  ** some heat from netiquette guardians.
  */
  { "signature",	DT_PATH, R_NONE, UL &Signature, UL "~/.signature" },
  /*
  ** .pp
  ** Specifies the filename of your signature, which is appended to all
  ** outgoing messages.   If the filename ends with a pipe (``|''), it is
  ** assumed that filename is a shell command and input should be read from
  ** its stdout.
  */
  { "simple_search",	DT_STR,	 R_NONE, UL &SimpleSearch, UL "~f %s | ~s %s" },
  /*
  ** .pp
  ** Specifies how Mutt should expand a simple search into a real search
  ** pattern.  A simple search is one that does not contain any of the ~
  ** operators.  See ``$patterns'' for more information on search patterns.
  ** .pp
  ** For example, if you simply type joe at a search or limit prompt, Mutt
  ** will automatically expand it to the value specified by this variable.
  ** For the default value it would be:
  ** .pp
  ** ~f joe | ~s joe
  */
  { "smart_wrap",	DT_BOOL, R_PAGER, OPTWRAP, 1 },
  /*
  ** .pp
  ** Controls the display of lines longer then the screen width in the
  ** internal pager. If set, long lines are wrapped at a word boundary.  If
  ** unset, lines are simply wrapped at the screen edge. Also see the
  ** ``$$markers'' variable.
  */
  { "smileys",		DT_RX,	 R_PAGER, UL &Smileys, UL "(>From )|(:[-^]?[][)(><}{|/DP])" },
  /*
  ** .pp
  ** The \fIpager\fP uses this variable to catch some common false
  ** positives of ``$$quote_regexp'', most notably smileys in the beginning
  ** of a line
  */
  { "sleep_time",	DT_NUM, R_NONE, UL &SleepTime, 1 },
  /*
  ** .pp
  ** Specifies time, in seconds, to pause while displaying certain informational
  ** messages, while moving from folder to folder and after expunging
  ** messages from the current folder.  The default is to pause one second, so 
  ** a value of zero for this option suppresses the pause.
  */
  { "sort",		DT_SORT, R_INDEX|R_RESORT, UL &Sort, SORT_DATE },
  /*
  ** .pp
  ** Specifies how to sort messages in the \fIindex\fP menu.  Valid values
  ** are:
  ** .pp
  ** .ts
  ** .  date or date-sent
  ** .  date-received
  ** .  from
  ** .  mailbox-order (unsorted)
  ** .  score
  ** .  size
  ** .  subject
  ** .  threads
  ** .  to
  ** .te
  ** .pp
  ** You may optionally use the reverse- prefix to specify reverse sorting
  ** order (example: set sort=reverse-date-sent).
  */
  { "sort_alias",	DT_SORT|DT_SORT_ALIAS,	R_NONE,	UL &SortAlias, SORT_ALIAS },
  /*
  ** .pp
  ** Specifies how the entries in the `alias' menu are sorted.  The
  ** following are legal values:
  ** .pp
  ** .ts
  ** .  address (sort alphabetically by email address)
  ** .  alias (sort alphabetically by alias name)
  ** .  unsorted (leave in order specified in .muttrc)
  ** .te
  */
  { "sort_aux",		DT_SORT|DT_SORT_AUX, R_INDEX|R_RESORT_BOTH, UL &SortAux, SORT_DATE },
  /*
  ** .pp
  ** When sorting by threads, this variable controls how threads are sorted
  ** in relation to other threads, and how the branches of the thread trees
  ** are sorted.  This can be set to any value that ``$$sort'' can, except
  ** threads (in that case, mutt will just use date-sent).  You can also
  ** specify the last- prefix in addition to the reverse- prefix, but last-
  ** must come after reverse-.  The last- prefix causes messages to be
  ** sorted against its siblings by which has the last descendant, using
  ** the rest of sort_aux as an ordering.  For instance, set sort_aux=last-
  ** date-received would mean that if a new message is received in a
  ** thread, that thread becomes the last one displayed (or the first, if
  ** you have set sort=reverse-threads.) Note: For reversed ``$$sort''
  ** order $$sort_aux is reversed again (which is not the right thing to do,
  ** but kept to not break any existing configuration setting).
  */
  { "sort_browser",	DT_SORT|DT_SORT_BROWSER, R_NONE, UL &BrowserSort, SORT_SUBJECT },
  /*
  ** .pp
  ** Specifies how to sort entries in the file browser.  By default, the
  ** entries are sorted alphabetically.  Valid values:
  ** .pp
  ** .ts
  ** .  alpha (alphabetically)
  ** .  date
  ** .  size
  ** .  unsorted
  ** .te
  ** .pp
  ** You may optionally use the reverse- prefix to specify reverse sorting
  ** order (example: set sort_browser=reverse-date).
  */
  { "sort_re",		DT_BOOL, R_INDEX|R_RESORT|R_RESORT_INIT, OPTSORTRE, 1 },
  /*
  ** .pp
  ** This variable is only useful when sorting by threads with
  ** ``$$strict_threads'' unset.  In that case, it changes the heuristic
  ** mutt uses to thread messages by subject.  With sort_re set, mutt will
  ** only attach a message as the child of another message by subject if
  ** the subject of the child message starts with a substring matching the
  ** setting of ``$$reply_regexp''.  With sort_re unset, mutt will attach
  ** the message whether or not this is the case, as long as the
  ** non-``$$reply_regexp'' parts of both messages are identical.
  */
  { "spoolfile",	DT_PATH, R_NONE, UL &Spoolfile, 0 },
  /*
  ** .pp
  ** If your spool mailbox is in a non-default place where Mutt cannot find
  ** it, you can specify its location with this variable.  Mutt will
  ** automatically set this variable to the value of the environment
  ** variable $$$MAIL if it is not set.
  */
  { "status_chars",	DT_STR,	 R_BOTH, UL &StChars, UL "-*%A" },
  /*
  ** .pp
  ** Controls the characters used by the "%r" indicator in
  ** ``$$status_format''. The first character is used when the mailbox is
  ** unchanged. The second is used when the mailbox has been changed, and
  ** it needs to be resynchronized. The third is used if the mailbox is in
  ** read-only mode, or if the mailbox will not be written when exiting
  ** that mailbox (You can toggle whether to write changes to a mailbox
  ** with the toggle-write operation, bound by default to "%"). The fourth
  ** is used to indicate that the current folder has been opened in attach-
  ** message mode (Certain operations like composing a new mail, replying,
  ** forwarding, etc. are not permitted in this mode).
  */
  { "status_format",	DT_STR,	 R_BOTH, UL &Status, UL "-%r-Mutt: %f [Msgs:%?M?%M/?%m%?n? New:%n?%?o? Old:%o?%?d? Del:%d?%?F? Flag:%F?%?t? Tag:%t?%?p? Post:%p?%?b? Inc:%b?%?l? %l?]---(%s/%S)-%>-(%P)---" },
  /*
  ** .pp
  ** Controls the format of the status line displayed in the \fIindex\fP
  ** menu.  This string is similar to ``$$index_format'', but has its own
  ** set of printf()-like sequences:
  ** .pp
  ** .dl
  ** .dt %b  .dd number of mailboxes with new mail *
  ** .dt %d  .dd number of deleted messages *
  ** .dt %h  .dd local hostname
  ** .dt %f  .dd the full pathname of the current mailbox
  ** .dt %F  .dd number of flagged messages *
  ** .dt %l  .dd size (in bytes) of the current mailbox *
  ** .dt %L  .dd size (in bytes) of the messages shown 
  **             (i.e., which match the current limit) *
  ** .dt %m  .dd the number of messages in the mailbox *
  ** .dt %M  .dd the number of messages shown (i.e., which match the current limit) *
  ** .dt %n  .dd number of new messages in the mailbox *
  ** .dt %o  .dd number of old unread messages
  ** .dt %p  .dd number of postponed messages *
  ** .dt %P  .dd percentage of the way through the index
  ** .dt %r  .dd modified/read-only/won't-write/attach-message indicator,
  **             according to $$status_chars
  ** .dt %s  .dd current sorting mode ($$sort)
  ** .dt %S  .dd current aux sorting method ($$sort_aux)
  ** .dt %t  .dd number of tagged messages *
  ** .dt %u  .dd number of unread messages *
  ** .dt %v  .dd Mutt version string
  ** .dt %V  .dd currently active limit pattern, if any *
  ** .dt %>X .dd right justify the rest of the string and pad with "X"
  ** .dt %|X .dd pad to the end of the line with "X"
  ** .de
  ** .pp
  ** * = can be optionally printed if nonzero
  ** .pp
  ** Some of the above sequences can be used to optionally print a string
  ** if their value is nonzero.  For example, you may only want to see the
  ** number of flagged messages if such messages exist, since zero is not
  ** particularly meaningful.  To optionally print a string based upon one
  ** of the above sequences, the following construct is used
  ** .pp
  **  %?<sequence_char>?<optional_string>?
  ** .pp
  ** where \fIsequence_char\fP is a character from the table above, and
  ** \fIoptional_string\fP is the string you would like printed if
  ** \fIstatus_char\fP is nonzero.  \fIoptional_string\fP \fBmay\fP contain
  ** other sequence as well as normal text, but you may \fBnot\fP nest
  ** optional strings.
  ** .pp
  ** Here is an example illustrating how to optionally print the number of
  ** new messages in a mailbox:
  ** %?n?%n new messages.?
  ** .pp
  ** Additionally you can switch between two strings, the first one, if a
  ** value is zero, the second one, if the value is nonzero, by using the
  ** following construct:
  ** %?<sequence_char>?<if_string>&<else_string>?
  ** .pp
  ** You can additionally force the result of any printf-like sequence to
  ** be lowercase by prefixing the sequence character with an underscore
  ** (_) sign.  For example, if you want to display the local hostname in
  ** lowercase, you would use:
  ** %_h
  */
  { "status_on_top",	DT_BOOL, R_BOTH, OPTSTATUSONTOP, 0 },
  /*
  ** .pp
  ** Setting this variable causes the ``status bar'' to be displayed on
  ** the first line of the screen rather than near the bottom.
  */
  { "strict_threads",	DT_BOOL, R_RESORT|R_RESORT_INIT|R_INDEX, OPTSTRICTTHREADS, 0 },
  /*
  ** .pp
  ** If set, threading will only make use of the ``In-Reply-To'' and
  ** ``References'' fields when you ``$$sort'' by message threads.  By
  ** default, messages with the same subject are grouped together in
  ** ``pseudo threads.''  This may not always be desirable, such as in a
  ** personal mailbox where you might have several unrelated messages with
  ** the subject ``hi'' which will get grouped together.
  */
  { "suspend",		DT_BOOL, R_NONE, OPTSUSPEND, 1 },
  /*
  ** .pp
  ** When \fIunset\fP, mutt won't stop when the user presses the terminal's
  ** \fIsusp\fP key, usually ``control-Z''. This is useful if you run mutt
  ** inside an xterm using a command like xterm -e mutt.
  */
  { "text_flowed", 	DT_BOOL, R_NONE, OPTTEXTFLOWED,  0 },
  /*
  ** .pp
  ** When set, mutt will generate text/plain; format=flowed attachments.
  ** This format is easier to handle for some mailing software, and generally
  ** just looks like ordinary text.  To actually make use of this format's 
  ** features, you'll need support in your editor.
  ** .pp
  ** Note that $$indent_string is ignored when this option is set.
  */
  { "thread_received",	DT_BOOL, R_RESORT|R_RESORT_INIT|R_INDEX, OPTTHREADRECEIVED, 0 },
  /*
  ** .pp
  ** When set, mutt uses the date received rather than the date sent
  ** to thread messages by subject.
  */
  { "thorough_search",	DT_BOOL, R_NONE, OPTTHOROUGHSRC, 0 },
  /*
  ** .pp
  ** Affects the \fI~b\fP and \fI~h\fP search operations described in
  ** section ``$patterns'' above.  If set, the headers and attachments of
  ** messages to be searched are decoded before searching.  If unset,
  ** messages are searched as they appear in the folder.
  */
  { "tilde",		DT_BOOL, R_PAGER, OPTTILDE, 0 },
  /*
  ** .pp
  ** When set, the internal-pager will pad blank lines to the bottom of the
  ** screen with a tilde (~).
  */
  { "timeout",		DT_NUM,	 R_NONE, UL &Timeout, 600 },
  /*
  ** .pp
  ** This variable controls the \fInumber of seconds\fP Mutt will wait for
  ** a key to be pressed in the main menu before timing out and checking
  ** for new mail.  A value of zero or less will cause Mutt not to ever
  ** time out.
  */
  { "tmpdir",		DT_PATH, R_NONE, UL &Tempdir, 0 },
  /*
  ** .pp
  ** This variable allows you to specify where Mutt will place its
  ** temporary files needed for displaying and composing messages.
  */
  { "to_chars",		DT_STR,	 R_BOTH, UL &Tochars, UL " +TCFL" },
  /*
  ** .pp
  ** Controls the character used to indicate mail addressed to you.  The
  ** first character is the one used when the mail is NOT addressed to your
  ** address (default: space).  The second is used when you are the only
  ** recipient of the message (default: +).  The third is when your address
  ** appears in the TO header field, but you are not the only recipient of
  ** the message (default: T).  The fourth character is used when your
  ** address is specified in the CC header field, but you are not the only
  ** recipient.  The fifth character is used to indicate mail that was sent
  ** by \fIyou\fP.  The sixth character is used to indicate when a mail
  ** was sent to a mailing-list you subscribe to (default: L).
  */
#ifdef USE_SOCKET
  { "tunnel",            DT_STR, R_NONE, UL &Tunnel, UL 0 },
  /*
  ** .pp
  ** Setting this variable will cause mutt to open a pipe to a command
  ** instead of a raw socket. You may be able to use this to set up
  ** preauthenticated connections to your IMAP/POP3 server. Example:
  ** .pp
  ** tunnel="ssh -q mailhost.net /usr/local/libexec/imapd"
  ** .pp
  ** NOTE: For this example to work you must be able to log in to the remote
  ** machine without having to enter a password.
  */
#endif
  { "use_8bitmime",	DT_BOOL, R_NONE, OPTUSE8BITMIME, 0 },
  /*
  ** .pp
  ** \fBWarning:\fP do not set this variable unless you are using a version
  ** of sendmail which supports the -B8BITMIME flag (such as sendmail
  ** 8.8.x) or you may not be able to send mail.
  ** .pp
  ** When \fIset\fP, Mutt will invoke ``$$sendmail'' with the -B8BITMIME
  ** flag when sending 8-bit messages to enable ESMTP negotiation.
  */
  { "use_domain",	DT_BOOL, R_NONE, OPTUSEDOMAIN, 1 },
  /*
  ** .pp
  ** When set, Mutt will qualify all local addresses (ones without the
  ** @host portion) with the value of ``$$hostname''.  If \fIunset\fP, no
  ** addresses will be qualified.
  */
  { "use_from",		DT_BOOL, R_NONE, OPTUSEFROM, 1 },
  /*
  ** .pp
  ** When \fIset\fP, Mutt will generate the `From:' header field when
  ** sending messages.  If \fIunset\fP, no `From:' header field will be
  ** generated unless the user explicitly sets one using the ``$my_hdr''
  ** command.
  */
#ifdef HAVE_GETADDRINFO
  { "use_ipv6",		DT_BOOL, R_NONE, OPTUSEIPV6, 1},
  /*
  ** .pp
  ** When \fIset\fP, Mutt will look for IPv6 addresses of hosts it tries to
  ** contact.  If this option is unset, Mutt will restrict itself to IPv4 addresses.
  ** Normally, the default should work.
  */
#endif /* HAVE_GETADDRINFO */
  { "user_agent",	DT_BOOL, R_NONE, OPTXMAILER, 1},
  /*
  ** .pp
  ** When \fIset\fP, mutt will add a "User-Agent" header to outgoing
  ** messages, indicating which version of mutt was used for composing
  ** them.
  */
  { "visual",		DT_PATH, R_NONE, UL &Visual, 0 },
  /*
  ** .pp
  ** Specifies the visual editor to invoke when the \fI~v\fP command is
  ** given in the builtin editor.
  */
  { "wait_key",		DT_BOOL, R_NONE, OPTWAITKEY, 1 },
  /*
  ** .pp
  ** Controls whether Mutt will ask you to press a key after \fIshell-
  ** escape\fP, \fIpipe-message\fP, \fIpipe-entry\fP, \fIprint-message\fP,
  ** and \fIprint-entry\fP commands.
  ** .pp
  ** It is also used when viewing attachments with ``$auto_view'', provided
  ** that the corresponding mailcap entry has a \fIneedsterminal\fP flag,
  ** and the external program is interactive.
  ** .pp
  ** When set, Mutt will always ask for a key. When unset, Mutt will wait
  ** for a key only if the external command returned a non-zero status.
  */
  { "weed",		DT_BOOL, R_NONE, OPTWEED, 1 },
  /*
  ** .pp
  ** When set, mutt will weed headers when when displaying, forwarding,
  ** printing, or replying to messages.
  */
  { "wrap_search",	DT_BOOL, R_NONE, OPTWRAPSEARCH, 1 },
  /*
  ** .pp
  ** Controls whether searches wrap around the end of the mailbox.
  ** .pp
  ** When set, searches will wrap around the first (or last) message. When
  ** unset, searches will not wrap.
  */
  { "wrapmargin",	DT_NUM,	 R_PAGER, UL &WrapMargin, 0 },
  /*
  ** .pp
  ** Controls the margin left at the right side of the terminal when mutt's
  ** pager does smart wrapping.
  */
  { "write_inc",	DT_NUM,	 R_NONE, UL &WriteInc, 10 },
  /*
  ** .pp
  ** When writing a mailbox, a message will be printed every
  ** \fIwrite_inc\fP messages to indicate progress.  If set to 0, only a
  ** single message will be displayed before writing a mailbox.
  ** .pp
  ** Also see the ``$$read_inc'' variable.
  */
  { "write_bcc",	DT_BOOL, R_NONE, OPTWRITEBCC, 1},
  /*
  ** .pp
  ** Controls whether mutt writes out the Bcc header when preparing
  ** messages to be sent.  Exim users may wish to use this.
  */
  /*--*/
  { NULL }
};

const struct mapping_t SortMethods[] = {
  { "date",		SORT_DATE },
  { "date-sent",	SORT_DATE },
  { "date-received",	SORT_RECEIVED },
