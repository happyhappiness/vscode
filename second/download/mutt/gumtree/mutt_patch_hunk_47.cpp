   ** for deletion.  This applies when you either explicitly delete a message,
   ** or when you save it to another folder.
   */
   { "digest_collapse",	DT_BOOL, R_NONE, OPTDIGESTCOLLAPSE, 1},
   /*
   ** .pp
-  ** If this option is \fIset\fP, mutt's revattach menu will not show the subparts of
-  ** individual messages in a digest.  To see these subparts, press 'v' on that menu.
+  ** If this option is \fIset\fP, mutt's received-attachments menu will not show the subparts of
+  ** individual messages in a multipart/digest.  To see these subparts, press ``v'' on that menu.
   */
   { "display_filter",	DT_PATH, R_PAGER, UL &DisplayFilter, UL "" },
   /*
   ** .pp
   ** When set, specifies a command used to filter messages.  When a message
   ** is viewed it is passed as standard input to $$display_filter, and the
   ** filtered message is read from the standard output.
   */
 #if defined(DL_STANDALONE) && defined(USE_DOTLOCK)
   { "dotlock_program",  DT_PATH, R_NONE, UL &MuttDotlock, UL BINDIR "/mutt_dotlock" },
   /*
   ** .pp
-  ** Contains the path of the mutt_dotlock (8) binary to be used by
+  ** Contains the path of the \fCmutt_dotlock(8)\fP binary to be used by
   ** mutt.
   */
 #endif
   { "dsn_notify",	DT_STR,	 R_NONE, UL &DsnNotify, UL "" },
   /*
   ** .pp
-  ** \fBNote:\fP you should not enable this unless you are using Sendmail
-  ** 8.8.x or greater.
-  ** .pp
   ** This variable sets the request for when notification is returned.  The
   ** string consists of a comma separated list (no spaces!) of one or more
   ** of the following: \fInever\fP, to never request notification,
   ** \fIfailure\fP, to request notification on transmission failure,
   ** \fIdelay\fP, to be notified of message delays, \fIsuccess\fP, to be
   ** notified of successful transmission.
   ** .pp
-  ** Example: set dsn_notify="failure,delay"
+  ** Example:
+  ** .ts
+  ** set dsn_notify="failure,delay"
+  ** .te
+  ** .pp
+  ** \fBNote:\fP when using $$sendmail for delivery, you should not enable
+  ** this unless you are either using Sendmail 8.8.x or greater or a MTA
+  ** providing a \fCsendmail(1)\fP-compatible interface supporting the \fC-N\fP option
+  ** for DSN. For SMTP delivery, DSN support is auto-detected so that it
+  ** depends on the server whether DSN will be used or not.
   */
   { "dsn_return",	DT_STR,	 R_NONE, UL &DsnReturn, UL "" },
   /*
   ** .pp
-  ** \fBNote:\fP you should not enable this unless you are using Sendmail
-  ** 8.8.x or greater.
-  ** .pp
   ** This variable controls how much of your message is returned in DSN
   ** messages.  It may be set to either \fIhdrs\fP to return just the
   ** message header, or \fIfull\fP to return the full message.
   ** .pp
-  ** Example: set dsn_return=hdrs
+  ** Example:
+  ** .ts
+  ** set dsn_return=hdrs
+  ** .te
+  ** .pp
+  ** \fBNote:\fP when using $$sendmail for delivery, you should not enable
+  ** this unless you are either using Sendmail 8.8.x or greater or a MTA
+  ** providing a \fCsendmail(1)\fP-compatible interface supporting the \fC-R\fP option
+  ** for DSN. For SMTP delivery, DSN support is auto-detected so that it
+  ** depends on the server whether DSN will be used or not.
   */
   { "duplicate_threads",	DT_BOOL, R_RESORT|R_RESORT_INIT|R_INDEX, OPTDUPTHREADS, 1 },
   /*
   ** .pp
-  ** This variable controls whether mutt, when sorting by threads, threads
-  ** messages with the same message-id together.  If it is set, it will indicate
+  ** This variable controls whether mutt, when $$sort is set to \fIthreads\fP, threads
+  ** messages with the same Message-Id together.  If it is \fIset\fP, it will indicate
   ** that it thinks they are duplicates of each other with an equals sign
-  ** in the thread diagram.
+  ** in the thread tree.
   */
   { "edit_headers",	DT_BOOL, R_NONE, OPTEDITHDRS, 0 },
   /*
   ** .pp
   ** This option allows you to edit the header of your outgoing messages
   ** along with the body of your message.
+  ** .pp
+  ** \fBNote\fP that changes made to the References: and Date: headers are
+  ** ignored for interoperability reasons.
   */
   { "edit_hdrs",	DT_SYN,  R_NONE, UL "edit_headers", 0 },
   /*
-  */  
+  */
   { "editor",		DT_PATH, R_NONE, UL &Editor, 0 },
   /*
   ** .pp
   ** This variable specifies which editor is used by mutt.
-  ** It defaults to the value of the VISUAL, or EDITOR, environment
-  ** variable, or to the string "vi" if neither of those are set.
+  ** It defaults to the value of the \fC$$$VISUAL\fP, or \fC$$$EDITOR\fP, environment
+  ** variable, or to the string ``vi'' if neither of those are set.
+  ** .pp
+  ** The \fC$$editor\fP string may contain a \fI%s\fP escape, which will be replaced by the name
+  ** of the file to be edited.  If the \fI%s\fP escape does not appear in \fC$$editor\fP, a
+  ** space and the name to be edited are appended.
+  ** .pp
+  ** The resulting string is then executed by running
+  ** .ts
+  ** sh -c 'string'
+  ** .te
+  ** .pp
+  ** where \fIstring\fP is the expansion of \fC$$editor\fP described above.
   */
   { "encode_from",	DT_BOOL, R_NONE, OPTENCODEFROM, 0 },
   /*
   ** .pp
   ** When \fIset\fP, mutt will quoted-printable encode messages when
-  ** they contain the string "From " in the beginning of a line.
-  ** Useful to avoid the tampering certain mail delivery and transport
-  ** agents tend to do with messages.
-  */
-  { "envelope_from", 	DT_BOOL, R_NONE, OPTENVFROM, 0 },
+  ** they contain the string ``From '' (note the trailing space) in the beginning of a line.
+  ** This is useful to avoid the tampering certain mail delivery and transport
+  ** agents tend to do with messages (in order to prevent tools from
+  ** misinterpreting the line as a mbox message separator).
+  */
+#if defined(USE_SSL_OPENSSL)
+  { "entropy_file",	DT_PATH, R_NONE, UL &SslEntropyFile, 0 },
+  /*
+  ** .pp
+  ** The file which includes random data that is used to initialize SSL
+  ** library functions.
+  */
+#endif
+  { "envelope_from_address", DT_ADDR, R_NONE, UL &EnvFrom, 0 },
   /*
   ** .pp
-  ** When \fIset\fP, mutt will try to derive the message's \fIenvelope\fP
-  ** sender from the "From:" header.  Note that this information is passed 
-  ** to sendmail command using the "-f" command line switch, so don't set this
-  ** option if you are using that switch in $$sendmail yourself,
-  ** or if the sendmail on your machine doesn't support that command
-  ** line switch.
+  ** Manually sets the \fIenvelope\fP sender for outgoing messages.
+  ** This value is ignored if $$use_envelope_from is \fIunset\fP.
   */
   { "escape",		DT_STR,	 R_NONE, UL &EscChar, UL "~" },
   /*
   ** .pp
-  ** Escape character to use for functions in the builtin editor.
+  ** Escape character to use for functions in the built-in editor.
   */
   { "fast_reply",	DT_BOOL, R_NONE, OPTFASTREPLY, 0 },
   /*
   ** .pp
-  ** When set, the initial prompt for recipients and subject are skipped
+  ** When \fIset\fP, the initial prompt for recipients and subject are skipped
   ** when replying to messages, and the initial prompt for subject is
   ** skipped when forwarding messages.
   ** .pp
-  ** \fBNote:\fP this variable has no effect when the ``$$autoedit''
-  ** variable is set.
+  ** \fBNote:\fP this variable has no effect when the $$autoedit
+  ** variable is \fIset\fP.
   */
-  { "fcc_attach",	DT_BOOL, R_NONE, OPTFCCATTACH, 1 },
+  { "fcc_attach",	DT_QUAD, R_NONE, OPT_FCCATTACH, M_YES },
   /*
   ** .pp
   ** This variable controls whether or not attachments on outgoing messages
   ** are saved along with the main body of your message.
   */
-#ifdef HAVE_PGP
   { "fcc_clear",	DT_BOOL, R_NONE, OPTFCCCLEAR, 0 },
   /*
   ** .pp
   ** When this variable is \fIset\fP, FCCs will be stored unencrypted and
-  ** unsigned, even when the actual message is encrypted and/or signed.
+  ** unsigned, even when the actual message is encrypted and/or
+  ** signed.
+  ** (PGP only)
   */
-#endif
   { "folder",		DT_PATH, R_NONE, UL &Maildir, UL "~/Mail" },
   /*
   ** .pp
-  ** Specifies the default location of your mailboxes.  A `+' or `=' at the
+  ** Specifies the default location of your mailboxes.  A ``+'' or ``='' at the
   ** beginning of a pathname will be expanded to the value of this
-  ** variable.  Note that if you change this variable from the default
+  ** variable.  Note that if you change this variable (from the default)
   ** value you need to make sure that the assignment occurs \fIbefore\fP
-  ** you use `+' or `=' for any other variables since expansion takes place
-  ** during the `set' command.
+  ** you use ``+'' or ``='' for any other variables since expansion takes place
+  ** when handling the ``$mailboxes'' command.
   */
   { "folder_format",	DT_STR,	 R_INDEX, UL &FolderFormat, UL "%2C %t %N %F %2l %-8.8u %-8.8g %8s %d %f" },
   /*
   ** .pp
   ** This variable allows you to customize the file browser display to your
-  ** personal taste.  This string is similar to ``$$index_format'', but has
-  ** its own set of printf()-like sequences:
-  ** .pp
+  ** personal taste.  This string is similar to $$index_format, but has
+  ** its own set of \fCprintf(3)\fP-like sequences:
   ** .dl
   ** .dt %C  .dd current file number
   ** .dt %d  .dd date/time folder was last modified
-  ** .dt %f  .dd filename
+  ** .dt %D  .dd date/time folder was last modified using $$date_format.
+  ** .dt %f  .dd filename (``/'' is appended to directory names,
+  **             ``@'' to symbolic links and ``*'' to executable
+  **             files)
   ** .dt %F  .dd file permissions
   ** .dt %g  .dd group name (or numeric gid, if missing)
   ** .dt %l  .dd number of hard links
   ** .dt %N  .dd N if folder has new mail, blank otherwise
   ** .dt %s  .dd size in bytes
-  ** .dt %t  .dd * if the file is tagged, blank otherwise
+  ** .dt %t  .dd ``*'' if the file is tagged, blank otherwise
   ** .dt %u  .dd owner name (or numeric uid, if missing)
-  ** .dt %>X .dd right justify the rest of the string and pad with character "X"
-  ** .dt %|X .dd pad to the end of the line with character "X"
+  ** .dt %>X .dd right justify the rest of the string and pad with character ``X''
+  ** .dt %|X .dd pad to the end of the line with character ``X''
+  ** .dt %*X .dd soft-fill with character ``X'' as pad
   ** .de
+  ** .pp
+  ** For an explanation of ``soft-fill'', see the $$index_format documentation.
   */
   { "followup_to",	DT_BOOL, R_NONE, OPTFOLLOWUPTO, 1 },
   /*
   ** .pp
-  ** Controls whether or not the \fIMail-Followup-To\fP header field is
+  ** Controls whether or not the ``Mail-Followup-To:'' header field is
   ** generated when sending mail.  When \fIset\fP, Mutt will generate this
   ** field when you are replying to a known mailing list, specified with
-  ** the ``subscribe'' or ``$lists'' commands.
+  ** the ``$subscribe'' or ``$lists'' commands.
   ** .pp
-  ** This field has two purposes.  First, preventing you from receiving
-  ** duplicate copies of replies to messages which you send to mailing
-  ** lists.  Second, ensuring that you do get a reply separately for any
-  ** messages sent to known lists to which you are not subscribed.  The
-  ** header will contain only the list's address for subscribed lists,
-  ** and both the list address and your own email address for unsubscribed
-  ** lists.  Without this header, a group reply to your message sent to a
-  ** subscribed list will be sent to both the list and your address,
-  ** resulting in two copies of the same email for you.
+  ** This field has two purposes.  First, preventing you from
+  ** receiving duplicate copies of replies to messages which you send
+  ** to mailing lists, and second, ensuring that you do get a reply
+  ** separately for any messages sent to known lists to which you are
+  ** not subscribed.
+  ** .pp
+  ** The header will contain only the list's address
+  ** for subscribed lists, and both the list address and your own
+  ** email address for unsubscribed lists.  Without this header, a
+  ** group reply to your message sent to a subscribed list will be
+  ** sent to both the list and your address, resulting in two copies
+  ** of the same email for you.
   */
   { "force_name",	DT_BOOL, R_NONE, OPTFORCENAME, 0 },
   /*
   ** .pp
-  ** This variable is similar to ``$$save_name'', except that Mutt will
+  ** This variable is similar to $$save_name, except that Mutt will
   ** store a copy of your outgoing message by the username of the address
   ** you are sending to even if that mailbox does not exist.
   ** .pp
-  ** Also see the ``$$record'' variable.
+  ** Also see the $$record variable.
   */
   { "forward_decode",	DT_BOOL, R_NONE, OPTFORWDECODE, 1 },
   /*
   ** .pp
-  ** Controls the decoding of complex MIME messages into text/plain when
+  ** Controls the decoding of complex MIME messages into \fCtext/plain\fP when
   ** forwarding a message.  The message header is also RFC2047 decoded.
-  ** This variable is only used, if ``$$mime_forward'' is \fIunset\fP,
-  ** otherwise ``$$mime_forward_decode'' is used instead.
+  ** This variable is only used, if $$mime_forward is \fIunset\fP,
+  ** otherwise $$mime_forward_decode is used instead.
   */
   { "forw_decode",	DT_SYN,  R_NONE, UL "forward_decode", 0 },
   /*
   */
+  { "forward_decrypt",	DT_BOOL, R_NONE, OPTFORWDECRYPT, 1 },
+  /*
+  ** .pp
+  ** Controls the handling of encrypted messages when forwarding a message.
+  ** When \fIset\fP, the outer layer of encryption is stripped off.  This
+  ** variable is only used if $$mime_forward is \fIset\fP and
+  ** $$mime_forward_decode is \fIunset\fP.
+  ** (PGP only)
+  */
+  { "forw_decrypt",	DT_SYN,  R_NONE, UL "forward_decrypt", 0 },
+  /*
+  */
+  { "forward_edit",	DT_QUAD, R_NONE, OPT_FORWEDIT, M_YES },
+  /*
+  ** .pp
+  ** This quadoption controls whether or not the user is automatically
+  ** placed in the editor when forwarding messages.  For those who always want
+  ** to forward with no modification, use a setting of ``no''.
+  */
   { "forward_format",	DT_STR,	 R_NONE, UL &ForwFmt, UL "[%a: %s]" },
   /*
   ** .pp
   ** This variable controls the default subject when forwarding a message.
-  ** It uses the same format sequences as the ``$$index_format'' variable.
+  ** It uses the same format sequences as the $$index_format variable.
   */
-  { "forw_format",	DT_SYN,  R_NONE, UL "forward_format", 0 },  
+  { "forw_format",	DT_SYN,  R_NONE, UL "forward_format", 0 },
   /*
   */
   { "forward_quote",	DT_BOOL, R_NONE, OPTFORWQUOTE, 0 },
   /*
   ** .pp
-  ** When \fIset\fP forwarded messages included in the main body of the
-  ** message (when ``$$mime_forward'' is \fIunset\fP) will be quoted using
-  ** ``$$indent_string''.
+  ** When \fIset\fP, forwarded messages included in the main body of the
+  ** message (when $$mime_forward is \fIunset\fP) will be quoted using
+  ** $$indent_string.
   */
   { "forw_quote",	DT_SYN,  R_NONE, UL "forward_quote", 0 },
   /*
   */
   { "from",		DT_ADDR, R_NONE, UL &From, UL 0 },
   /*
   ** .pp
-  ** When set, this variable contains a default from address.  It
-  ** can be overridden using my_hdr (including from send-hooks) and
-  ** ``$$reverse_name''.
+  ** When \fIset\fP, this variable contains a default from address.  It
+  ** can be overridden using ``$my_hdr'' (including from a ``$send-hook'') and
+  ** $$reverse_name.  This variable is ignored if $$use_from is \fIunset\fP.
   ** .pp
-  ** Defaults to the EMAIL environment variable's content.
+  ** This setting defaults to the contents of the environment variable \fC$$$EMAIL\fP.
   */
   { "gecos_mask",	DT_RX,	 R_NONE, UL &GecosMask, UL "^[^,]*" },
   /*
   ** .pp
   ** A regular expression used by mutt to parse the GECOS field of a password
-  ** entry when expanding the alias.  By default the regular expression is set
-  ** to "^[^,]*" which will return the string up to the first "," encountered.
-  ** If the GECOS field contains a string like "lastname, firstname" then you
-  ** should set the gecos_mask=".*".
-  ** .pp
-  ** This can be useful if you see the following behavior: you address a e-mail
-  ** to user ID stevef whose full name is Steve Franklin.  If mutt expands 
-  ** stevef to "Franklin" stevef@foo.bar then you should set the gecos_mask to
+  ** entry when expanding the alias.  The default value
+  ** will return the string up to the first ``,'' encountered.
+  ** If the GECOS field contains a string like ``lastname, firstname'' then you
+  ** should set it to ``\fC.*\fP''.
+  ** .pp
+  ** This can be useful if you see the following behavior: you address an e-mail
+  ** to user ID ``stevef'' whose full name is ``Steve Franklin''.  If mutt expands
+  ** ``stevef'' to ``"Franklin" stevef@foo.bar'' then you should set the $$gecos_mask to
   ** a regular expression that will match the whole name so mutt will expand
-  ** "Franklin" to "Franklin, Steve".
+  ** ``Franklin'' to ``Franklin, Steve''.
   */
   { "hdr_format",	DT_SYN,  R_NONE, UL "index_format", 0 },
   /*
   */
   { "hdrs",		DT_BOOL, R_NONE, OPTHDRS, 1 },
   /*
   ** .pp
-  ** When unset, the header fields normally added by the ``$my_hdr''
+  ** When \fIunset\fP, the header fields normally added by the ``$my_hdr''
   ** command are not created.  This variable \fImust\fP be unset before
-  ** composing a new message or replying in order to take effect.  If set,
+  ** composing a new message or replying in order to take effect.  If \fIset\fP,
   ** the user defined header fields are added to every new message.
   */
   { "header",		DT_BOOL, R_NONE, OPTHEADER, 0 },
   /*
   ** .pp
-  ** When set, this variable causes Mutt to include the header
+  ** When \fIset\fP, this variable causes Mutt to include the header
   ** of the message you are replying to into the edit buffer.
-  ** The ``$$weed'' setting applies.
-  */  
+  ** The $$weed setting applies.
+  */
+#ifdef USE_HCACHE
+  { "header_cache", DT_PATH, R_NONE, UL &HeaderCache, 0 },
+  /*
+  ** .pp
+  ** This variable points to the header cache database.
+  ** If pointing to a directory Mutt will contain a header cache
+  ** database file per folder, if pointing to a file that file will
+  ** be a single global header cache. By default it is \fIunset\fP so no header
+  ** caching will be used.
+  ** .pp
+  ** Header caching can greatly improve speed when opening POP, IMAP
+  ** MH or Maildir folders, see ``$caching'' for details.
+  */
+#if defined(HAVE_QDBM) || defined(HAVE_TC)
+  { "header_cache_compress", DT_BOOL, R_NONE, OPTHCACHECOMPRESS, 1 },
+  /*
+  ** .pp
+  ** When mutt is compiled with qdbm or tokyocabinet as header cache backend,
+  ** this option determines whether the database will be compressed.
+  ** Compression results in database files roughly being one fifth
+  ** of the usual diskspace, but the decompression can result in a
+  ** slower opening of cached folder(s) which in general is still
+  ** much faster than opening non header cached folders.
+  */
+#endif /* HAVE_QDBM */
+#if defined(HAVE_GDBM) || defined(HAVE_DB4)
+  { "header_cache_pagesize", DT_STR, R_NONE, UL &HeaderCachePageSize, UL "16384" },
+  /*
+  ** .pp
+  ** When mutt is compiled with either gdbm or bdb4 as the header cache backend,
+  ** this option changes the database page size.  Too large or too small
+  ** values can waste space, memory, or CPU time. The default should be more
+  ** or less optimal for most use cases.
+  */
+#endif /* HAVE_GDBM || HAVE_DB4 */
+#endif /* USE_HCACHE */
   { "help",		DT_BOOL, R_BOTH, OPTHELP, 1 },
   /*
   ** .pp
-  ** When set, help lines describing the bindings for the major functions
+  ** When \fIset\fP, help lines describing the bindings for the major functions
   ** provided by each menu are displayed on the first line of the screen.
   ** .pp
   ** \fBNote:\fP The binding will not be displayed correctly if the
   ** function is bound to a sequence rather than a single keystroke.  Also,
   ** the help line may not be updated if a binding is changed while Mutt is
   ** running.  Since this variable is primarily aimed at new users, neither
   ** of these should present a major problem.
   */
   { "hidden_host",	DT_BOOL, R_NONE, OPTHIDDENHOST, 0 },
   /*
   ** .pp
-  ** When set, mutt will skip the host name part of ``$$hostname'' variable
+  ** When \fIset\fP, mutt will skip the host name part of $$hostname variable
   ** when adding the domain part to addresses.  This variable does not
-  ** affect the generation of Message-IDs, and it will not lead to the 
+  ** affect the generation of Message-IDs, and it will not lead to the
   ** cut-off of first-level domains.
   */
-  { "hide_limited",	DT_BOOL, R_RESORT|R_INDEX, OPTHIDELIMITED, 0 },
+  { "hide_limited",	DT_BOOL, R_TREE|R_INDEX, OPTHIDELIMITED, 0 },
+  /*
+  ** .pp
+  ** When \fIset\fP, mutt will not show the presence of messages that are hidden
+  ** by limiting, in the thread tree.
+  */
+  { "hide_missing",	DT_BOOL, R_TREE|R_INDEX, OPTHIDEMISSING, 1 },
   /*
   ** .pp
-  ** When set, mutt will not show the presence of missing messages in the
+  ** When \fIset\fP, mutt will not show the presence of missing messages in the
   ** thread tree.
   */
-  { "hide_missing",	DT_BOOL, R_RESORT|R_INDEX, OPTHIDEMISSING, 1 },
+  { "hide_thread_subject", DT_BOOL, R_TREE|R_INDEX, OPTHIDETHREADSUBJECT, 1 },
   /*
   ** .pp
-  ** When set, mutt will not show the presence of messages that are hidden
-  ** by limiting, in the thread tree.
+  ** When \fIset\fP, mutt will not show the subject of messages in the thread
+  ** tree that have the same subject as their parent or closest previously
+  ** displayed sibling.
   */
-  { "hide_top_limited",	DT_BOOL, R_RESORT|R_INDEX, OPTHIDETOPLIMITED, 0 },
+  { "hide_top_limited",	DT_BOOL, R_TREE|R_INDEX, OPTHIDETOPLIMITED, 0 },
   /*
   ** .pp
-  ** When set, mutt will not show the presence of missing messages at the
-  ** top of threads in the thread tree.  Note that when $$hide_limited is
-  ** set, this option will have no effect.
+  ** When \fIset\fP, mutt will not show the presence of messages that are hidden
+  ** by limiting, at the top of threads in the thread tree.  Note that when
+  ** $$hide_limited is \fIset\fP, this option will have no effect.
   */
-  { "hide_top_missing",	DT_BOOL, R_RESORT|R_INDEX, OPTHIDETOPMISSING, 1 },
+  { "hide_top_missing",	DT_BOOL, R_TREE|R_INDEX, OPTHIDETOPMISSING, 1 },
   /*
   ** .pp
-  ** When set, mutt will not show the presence of messages that are hidden
-  ** by limiting, at the top of threads in the thread tree.Note that when
-  ** $$hide_missing is set, this option will have no effect.
+  ** When \fIset\fP, mutt will not show the presence of missing messages at the
+  ** top of threads in the thread tree.  Note that when $$hide_missing is
+  ** \fIset\fP, this option will have no effect.
   */
   { "history",		DT_NUM,	 R_NONE, UL &HistSize, 10 },
   /*
   ** .pp
   ** This variable controls the size (in number of strings remembered) of
-  ** the string history buffer. The buffer is cleared each time the
+  ** the string history buffer per category. The buffer is cleared each time the
   ** variable is set.
   */
+  { "history_file",     DT_PATH, R_NONE, UL &HistFile, UL "~/.mutthistory" },
+  /*
+  ** .pp
+  ** The file in which Mutt will save its history.
+  */
+  { "honor_disposition", DT_BOOL, R_NONE, OPTHONORDISP, 0 },
+  /*
+  ** .pp
+  ** When \fIset\fP, Mutt will not display attachments with a
+  ** disposition of ``attachment'' inline even if it could
+  ** render the part to plain text. These MIME parts can only
+  ** be viewed from the attachment menu.
+  ** .pp
+  ** If \fIunset\fP, Mutt will render all MIME parts it can
+  ** properly transform to plain text.
+  */
   { "honor_followup_to", DT_QUAD, R_NONE, OPT_MFUPTO, M_YES },
   /*
   ** .pp
   ** This variable controls whether or not a Mail-Followup-To header is
   ** honored when group-replying to a message.
   */
   { "hostname",		DT_STR,	 R_NONE, UL &Fqdn, 0 },
   /*
   ** .pp
-  ** Specifies the hostname to use after the ``@'' in local e-mail
-  ** addresses.  This overrides the compile time definition obtained from
-  ** /etc/resolv.conf.
+  ** Specifies the fully-qualified hostname of the system mutt is running on
+  ** containing the host's name and the DNS domain it belongs to. It is used
+  ** as the domain part (after ``@'') for local email addresses as well as
+  ** Message-Id headers.
+  ** .pp
+  ** Its value is determined at startup as follows: If the node's name
+  ** as returned by the \fCuname(3)\fP function contains the hostname and the
+  ** domain, these are used to construct $$hostname. If there is no
+  ** domain part returned, Mutt will look for a ``domain'' or ``search''
+  ** line in \fC/etc/resolv.conf\fP to determine the domain. Optionally, Mutt
+  ** can be compiled with a fixed domain name in which case a detected
+  ** one is not used.
+  ** .pp
+  ** Also see $$use_domain and $$hidden_host.
+  */
+  { "ignore_linear_white_space",    DT_BOOL, R_NONE, OPTIGNORELWS, 0 },
+  /*
+  ** .pp
+  ** This option replaces linear-white-space between encoded-word
+  ** and text to a single space to prevent the display of MIME-encoded
+  ** ``Subject:'' field from being divided into multiple lines.
   */
   { "ignore_list_reply_to", DT_BOOL, R_NONE, OPTIGNORELISTREPLYTO, 0 },
   /*
   ** .pp
-  ** Affects the behaviour of the \fIreply\fP function when replying to
-  ** messages from mailing lists.  When set, if the ``Reply-To:'' field is
+  ** Affects the behavior of the \fC<reply>\fP function when replying to
+  ** messages from mailing lists (as defined by the ``$subscribe'' or
+  ** ``$lists'' commands).  When \fIset\fP, if the ``Reply-To:'' field is
   ** set to the same value as the ``To:'' field, Mutt assumes that the
   ** ``Reply-To:'' field was set by the mailing list to automate responses
   ** to the list, and will ignore this field.  To direct a response to the
-  ** mailing list when this option is set, use the \fIlist-reply\fP
-  ** function; \fIgroup-reply\fP will reply to both the sender and the
+  ** mailing list when this option is \fIset\fP, use the \fC$<list-reply>\fP
+  ** function; \fC<group-reply>\fP will reply to both the sender and the
   ** list.
   */
 #ifdef USE_IMAP
   { "imap_authenticators", DT_STR, R_NONE, UL &ImapAuthenticators, UL 0 },
   /*
   ** .pp
   ** This is a colon-delimited list of authentication methods mutt may
   ** attempt to use to log in to an IMAP server, in the order mutt should
-  ** try them.  Authentication methods are either 'login' or the right
-  ** side of an IMAP 'AUTH=xxx' capability string, eg 'digest-md5',
-  ** 'gssapi' or 'cram-md5'. This parameter is case-insensitive. If this
-  ** parameter is unset (the default) mutt will try all available methods,
+  ** try them.  Authentication methods are either ``login'' or the right
+  ** side of an IMAP ``AUTH=xxx'' capability string, e.g. ``digest-md5'', ``gssapi''
+  ** or ``cram-md5''. This option is case-insensitive. If it's
+  ** \fIunset\fP (the default) mutt will try all available methods,
   ** in order from most-secure to least-secure.
   ** .pp
-  ** Example: set imap_authenticators="gssapi:cram-md5:login"
+  ** Example:
+  ** .ts
+  ** set imap_authenticators="gssapi:cram-md5:login"
+  ** .te
   ** .pp
   ** \fBNote:\fP Mutt will only fall back to other authentication methods if
   ** the previous methods are unavailable. If a method is available but
   ** authentication fails, mutt will not connect to the IMAP server.
   */
+  { "imap_check_subscribed",  DT_BOOL, R_NONE, OPTIMAPCHECKSUBSCRIBED, 0 },
+  /*
+   ** .pp
+   ** When \fIset\fP, mutt will fetch the set of subscribed folders from
+   ** your server on connection, and add them to the set of mailboxes
+   ** it polls for new mail just as if you had issued individual ``$mailboxes''
+   ** commands.
+   */
   { "imap_delim_chars",		DT_STR, R_NONE, UL &ImapDelimChars, UL "/." },
   /*
   ** .pp
   ** This contains the list of characters which you would like to treat
   ** as folder separators for displaying IMAP paths. In particular it
-  ** helps in using the '=' shortcut for your \fIfolder\fP variable.
+  ** helps in using the ``='' shortcut for your \fIfolder\fP variable.
   */
-# ifdef USE_SSL
-  { "imap_force_ssl",		DT_BOOL, R_NONE, OPTIMAPFORCESSL, 0 },
+  { "imap_headers",	DT_STR, R_INDEX, UL &ImapHeaders, UL 0},
   /*
   ** .pp
-  ** If this variable is set, Mutt will always use SSL when
-  ** connecting to IMAP servers.
+  ** Mutt requests these header fields in addition to the default headers
+  ** (``Date:'', ``From:'', ``Subject:'', ``To:'', ``Cc:'', ``Message-Id:'',
+  ** ``References:'', ``Content-Type:'', ``Content-Description:'', ``In-Reply-To:'',
+  ** ``Reply-To:'', ``Lines:'', ``List-Post:'', ``X-Label:'') from IMAP
+  ** servers before displaying the index menu. You may want to add more
+  ** headers for spam detection.
+  ** .pp
+  ** \fBNote:\fP This is a space separated list, items should be uppercase
+  ** and not contain the colon, e.g. ``X-BOGOSITY X-SPAM-STATUS'' for the
+  ** ``X-Bogosity:'' and ``X-Spam-Status:'' header fields.
   */
-# endif
-  { "imap_home_namespace",	DT_STR, R_NONE, UL &ImapHomeNamespace, UL 0},
+  { "imap_idle",                DT_BOOL, R_NONE, OPTIMAPIDLE, 0 },
   /*
   ** .pp
-  ** You normally want to see your personal folders alongside
-  ** your INBOX in the IMAP browser. If you see something else, you may set
-  ** this variable to the IMAP path to your folders.
+  ** When \fIset\fP, mutt will attempt to use the IMAP IDLE extension
+  ** to check for new mail in the current mailbox. Some servers
+  ** (dovecot was the inspiration for this option) react badly
+  ** to mutt's implementation. If your connection seems to freeze
+  ** up periodically, try unsetting this.
   */
-  { "imap_keepalive",           DT_NUM,  R_NONE, UL &ImapKeepalive, 900 },
+  { "imap_keepalive",           DT_NUM,  R_NONE, UL &ImapKeepalive, 300 },
   /*
   ** .pp
   ** This variable specifies the maximum amount of time in seconds that mutt
   ** will wait before polling open IMAP connections, to prevent the server
   ** from closing them before mutt has finished with them. The default is
   ** well within the RFC-specified minimum amount of time (30 minutes) before
