  /*
  ** .pp
  ** This variable controls the number of lines of context that are given
  ** when displaying the next or previous page in the internal pager.  By
  ** default, Mutt will display the line after the last one on the screen
  ** at the top of the next page (0 lines of context).
  */
  { "pager_format",	DT_STR,	 R_PAGER, UL &PagerFmt, UL "-%Z- %C/%m: %-20.20n   %s" },
  /*
  ** .pp
  ** This variable controls the format of the one-line message ``status''
  ** displayed before each message in either the internal or an external
  ** pager.  The valid sequences are listed in the ``$$index_format''
  ** section.
  */
  { "pager_index_lines",DT_NUM,	 R_PAGER, UL &PagerIndexLines, 0 },
  /*
  ** .pp
  ** Determines the number of lines of a mini-index which is shown when in
  ** the pager.  The current message, unless near the top or bottom of the
  ** folder, will be roughly one third of the way down this mini-index,
  ** giving the reader the context of a few messages before and after the
  ** message.  This is useful, for example, to determine how many messages
  ** remain to be read in the current thread.  One of the lines is reserved
  ** for the status bar from the index, so a \fIpager_index_lines\fP of 6
  ** will only show 5 lines of the actual index.  A value of 0 results in
  ** no index being shown.  If the number of messages in the current folder
  ** is less than \fIpager_index_lines\fP, then the index will only use as
  ** many lines as it needs.
  */
  { "pager_stop",	DT_BOOL, R_NONE, OPTPAGERSTOP, 0 },
  /*
  ** .pp
  ** When set, the internal-pager will \fBnot\fP move to the next message
  ** when you are at the end of a message and invoke the \fInext-page\fP
  ** function.
  */
  

#ifdef HAVE_PGP

  { "pgp_autosign",	DT_BOOL, R_NONE, OPTPGPAUTOSIGN, 0 },
  /*
  ** .pp
  ** Setting this variable will cause Mutt to always attempt to PGP/MIME
  ** sign outgoing messages.  This can be overridden by use of the \fIpgp-
  ** menu\fP, when signing is not required or encryption is requested as
  ** well.
  */
  { "pgp_autoencrypt",	DT_BOOL, R_NONE, OPTPGPAUTOENCRYPT, 0 },
  /*
  ** .pp
  ** Setting this variable will cause Mutt to always attempt to PGP/MIME
  ** encrypt outgoing messages.  This is probably only useful in connection
  ** to the \fIsend-hook\fP command.  It can be overridden by use of the
  ** \fIpgp-menu\fP, when encryption is not required or signing is
  ** requested as well.
  */
  { "pgp_ignore_subkeys", DT_BOOL, R_NONE, OPTPGPIGNORESUB, 1},
  /*
  ** .pp
  ** Setting this variable will cause Mutt to ignore OpenPGP subkeys. Instead,
  ** the principal key will inherit the subkeys' capabilities.  Unset this
  ** if you want to play interesting key selection games.
  */
  { "pgp_entry_format", DT_STR,  R_NONE, UL &PgpEntryFormat, UL "%4n %t%f %4l/0x%k %-4a %2c %u" },
  /*
  ** .pp
  ** This variable allows you to customize the PGP key selection menu to
  ** your personal taste. This string is similar to ``$$index_format'', but
  ** has its own set of printf()-like sequences:
  ** .pp
  ** .dl
  ** .dt %n     .dd number
  ** .dt %k     .dd key id
  ** .dt %u     .dd user id
  ** .dt %a     .dd algorithm
  ** .dt %l     .dd key length
  ** .dt %f     .dd flags
  ** .dt %c     .dd capabilities
  ** .dt %t     .dd trust/validity of the key-uid association
  ** .dt %[<s>] .dd date of the key where <s> is an strftime(3) expression
  ** .de
  */
  { "pgp_good_sign",	DT_RX,  R_NONE, UL &PgpGoodSign, 0 },
  /*
  ** .pp
  ** If you assign a text to this variable, then a PGP signature is only
  ** considered verified if the output from $$pgp_verify_command contains
  ** the text. Use this variable if the exit code from the command is 0
  ** even for bad signatures.
  */ 
  { "pgp_long_ids",	DT_BOOL, R_NONE, OPTPGPLONGIDS, 0 },
  /*
  ** .pp
  ** If set, use 64 bit PGP key IDs. Unset uses the normal 32 bit Key IDs.
  */
  { "pgp_replyencrypt",	DT_BOOL, R_NONE, OPTPGPREPLYENCRYPT, 1 },
  /*
  ** .pp
  ** If set, automatically PGP encrypt replies to messages which are
  ** encrypted.
  */
  { "pgp_replysign",	DT_BOOL, R_NONE, OPTPGPREPLYSIGN, 0 },
  /*
  ** .pp
  ** If set, automatically PGP sign replies to messages which are signed.
  ** .pp
  ** \fBNote:\fP this does not work on messages that are encrypted
  ** \fBand\fP signed!
  */
  { "pgp_replysignencrypted", DT_BOOL, R_NONE, OPTPGPREPLYSIGNENCRYPTED, 0 },
  /*
  ** .pp
  ** If set, automatically PGP sign replies to messages which are
  ** encrypted. This makes sense in combination with
  ** ``$$pgp_replyencrypt'', because it allows you to sign all messages
  ** which are automatically encrypted.  This works around the problem
  ** noted in ``$$pgp_replysign'', that mutt is not able to find out
  ** whether an encrypted message is also signed.
  */
  { "pgp_retainable_sigs", DT_BOOL, R_NONE, OPTPGPRETAINABLESIG, 0 },
  /*
  ** .pp
  ** If set, signed and encrypted messages will consist of nested
  ** multipart/signed and multipart/encrypted body parts.
  ** .pp
  ** This is useful for applications like encrypted and signed mailing
  ** lists, where the outer layer (multipart/encrypted) can be easily
  ** removed, while the inner multipart/signed part is retained.
  */
  { "pgp_show_unusable", DT_BOOL, R_NONE, OPTPGPSHOWUNUSABLE, 1 },
  /*
  ** .pp
  ** If set, mutt will display non-usable keys on the PGP key selection
  ** menu.  This includes keys which have been revoked, have expired, or
  ** have been marked as ``disabled'' by the user.
  */
  { "pgp_sign_as",	DT_STR,	 R_NONE, UL &PgpSignAs, 0 },
  /*
  ** .pp
  ** If you have more than one key pair, this option allows you to specify
  ** which of your private keys to use.  It is recommended that you use the
  ** keyid form to specify your key (e.g., ``0x00112233'').
  */
  { "pgp_strict_enc",	DT_BOOL, R_NONE, OPTPGPSTRICTENC, 1 },
  /*
  ** .pp
  ** If set, Mutt will automatically encode PGP/MIME signed messages as
  ** \fIquoted-printable\fP.  Please note that unsetting this variable may
  ** lead to problems with non-verifyable PGP signatures, so only change
  ** this if you know what you are doing.
  */
  { "pgp_timeout",	DT_NUM,	 R_NONE, UL &PgpTimeout, 300 },
  /*
  ** .pp
  ** The number of seconds after which a cached passphrase will expire if
  ** not used.
  */
  { "pgp_verify_sig",	DT_QUAD, R_NONE, OPT_VERIFYSIG, M_YES },
  /*
  ** .pp
  ** If ``yes'', always attempt to verify PGP/MIME signatures.  If ``ask-yes''
  ** or ``ask-no'',
  ** ask whether or not to verify the signature.  If ``no'', never attempt
  ** to verify PGP/MIME signatures.
  */
  { "pgp_sort_keys",	DT_SORT|DT_SORT_KEYS, R_NONE, UL &PgpSortKeys, SORT_ADDRESS },
  /*
  ** .pp
  ** Specifies how the entries in the `pgp keys' menu are sorted. The
  ** following are legal values:
  ** .pp
  ** .dl
  ** .dt address .dd sort alphabetically by user id
  ** .dt keyid   .dd sort alphabetically by key id
  ** .dt date    .dd sort by key creation date
  ** .dt trust   .dd sort by the trust of the key
  ** .de
  ** .pp
  ** If you prefer reverse order of the above values, prefix it with
  ** `reverse-'.
  */
  { "pgp_create_traditional", DT_QUAD, R_NONE, OPT_PGPTRADITIONAL, M_NO },
  /*
  ** .pp
  ** This option controls whether Mutt generates old-style PGP encrypted
  ** or signed messages under certain circumstances.
  ** .pp
  ** Note that PGP/MIME will be used automatically for messages which have
  ** a character set different from us-ascii, or which consist of more than
  ** a single MIME part.
  ** .pp
  ** Also note that using the old-style PGP message format is \fBstrongly\fP
  ** \fBdeprecated\fP.
  */

  /* XXX Default values! */
  
  { "pgp_decode_command", 	DT_STR, R_NONE, UL &PgpDecodeCommand, 0},
  /*
  ** .pp
  ** This format strings specifies a command which is used to decode 
  ** application/pgp attachments.
  ** .pp
  ** The PGP command formats have their own set of printf-like sequences:
  ** .pp
  ** .dl
  ** .dt %p .dd Expands to PGPPASSFD=0 when a pass phrase is needed, to an empty
  **            string otherwise. Note: This may be used with a %? construct.
  ** .dt %f .dd Expands to the name of a file containing a message.
  ** .dt %s .dd Expands to the name of a file containing the signature part
  ** .          of a multipart/signed attachment when verifying it.
  ** .dt %a .dd The value of $$pgp_sign_as.
  ** .dt %r .dd One or more key IDs.
  ** .de
  ** .pp
  ** For examples on how to configure these formats for the various versions
  ** of PGP which are floating around, see the pgp*.rc and gpg.rc files in
  ** the samples/ subdirectory which has been installed on your system
  ** alongside the documentation.
  */
  { "pgp_getkeys_command",	DT_STR, R_NONE, UL &PgpGetkeysCommand, 0},
  /*
  ** .pp
  ** This command is invoked whenever mutt will need public key information.
  ** %r is the only printf-like sequence used with this format.
  */
  { "pgp_verify_command", 	DT_STR, R_NONE, UL &PgpVerifyCommand, 0},
  /*
  ** .pp
  ** This command is used to verify PGP/MIME signatures.
  */
  { "pgp_decrypt_command", 	DT_STR, R_NONE, UL &PgpDecryptCommand, 0},
  /*
  ** .pp
  ** This command is used to decrypt a PGP/MIME encrypted message.
  */  
  { "pgp_clearsign_command",	DT_STR,	R_NONE, UL &PgpClearSignCommand, 0 },
  /*
  ** .pp
  ** This format is used to create a "clearsigned" old-style PGP attachment.
  ** Note that the use of this format is \fBstrongly\fP \fBdeprecated\fP.
  */
  { "pgp_sign_command",		DT_STR, R_NONE, UL &PgpSignCommand, 0},
  /*
  ** .pp
  ** This command is used to create the detached PGP signature for a 
  ** multipart/signed PGP/MIME body part.
  */  
  { "pgp_encrypt_sign_command",	DT_STR, R_NONE, UL &PgpEncryptSignCommand, 0},
  /*
  ** .pp
  ** This command is used to combinedly sign/encrypt a body part.
  */  
  { "pgp_encrypt_only_command", DT_STR, R_NONE, UL &PgpEncryptOnlyCommand, 0},
  /*
  ** .pp
  ** This command is used to encrypt a body part without signing it.
  */  
  { "pgp_import_command",	DT_STR, R_NONE, UL &PgpImportCommand, 0},
  /*
  ** .pp
  ** This command is used to import a key from a message into 
  ** the user's public key ring.
  */  
  { "pgp_export_command", 	DT_STR, R_NONE, UL &PgpExportCommand, 0},
  /*
  ** .pp
  ** This command is used to export a public key from the user's
  ** key ring.
  */  
  { "pgp_verify_key_command",	DT_STR, R_NONE, UL &PgpVerifyKeyCommand, 0},
  /*
  ** .pp
  ** This command is used to verify key information from the key selection
  ** menu.
  */  
  { "pgp_list_secring_command",	DT_STR, R_NONE, UL &PgpListSecringCommand, 0},
  /*
  ** .pp
  ** This command is used to list the secret key ring's contents.  The
  ** output format must be analogous to the one used by 
  ** gpg --list-keys --with-colons.
  ** .pp
  ** This format is also generated by the pgpring utility which comes 
  ** with mutt.
  */  
  { "pgp_list_pubring_command", DT_STR, R_NONE, UL &PgpListPubringCommand, 0},
  /*
  ** .pp
  ** This command is used to list the public key ring's contents.  The
  ** output format must be analogous to the one used by 
  ** gpg --list-keys --with-colons.
  ** .pp
  ** This format is also generated by the pgpring utility which comes 
  ** with mutt.
  */  
  { "forward_decrypt",	DT_BOOL, R_NONE, OPTFORWDECRYPT, 1 },
  /*
  ** .pp
  ** Controls the handling of encrypted messages when forwarding a message.
  ** When set, the outer layer of encryption is stripped off.  This
  ** variable is only used if ``$$mime_forward'' is \fIset\fP and
  ** ``$$mime_forward_decode'' is \fIunset\fP.
  */
  { "forw_decrypt",	DT_SYN,  R_NONE, UL "forward_decrypt", 0 },
  /*
  */
#endif /* HAVE_PGP */
  
#if defined(USE_SSL)||defined(USE_NSS)
# ifndef USE_NSS  
  { "ssl_starttls", DT_QUAD, R_NONE, OPT_SSLSTARTTLS, M_YES },
  /*
  ** .pp
  ** If set (the default), mutt will attempt to use STARTTLS on servers
  ** advertising the capability. When unset, mutt will not attempt to
  ** use STARTTLS regardless of the server's capabilities.
  */
# endif  
  { "certificate_file",	DT_PATH, R_NONE, UL &SslCertFile, 0 },
  /*
  ** .pp
  ** This variable specifies the file where the certificates you trust
  ** are saved. When an unknown certificate is encountered, you are asked
  ** if you accept it or not. If you accept it, the certificate can also 
  ** be saved in this file and further connections are automatically 
  ** accepted.
  ** .pp
  ** You can also manually add CA certificates in this file. Any server
  ** certificate that is signed with one of these CA certificates are 
  ** also automatically accepted.
  ** .pp
  ** Example: set certificate_file=~/.mutt/certificates
  */
  { "ssl_usesystemcerts", DT_BOOL, R_NONE, OPTSSLSYSTEMCERTS, 1 },
  /*
  ** .pp
  ** If set to \fIyes\fP, mutt will use CA certificates in the
  ** system-wide certificate store when checking if server certificate 
  ** is signed by a trusted CA.
  */
  { "entropy_file",	DT_PATH, R_NONE, UL &SslEntropyFile, 0 },
  /*
  ** .pp
  ** The file which includes random data that is used to initalize SSL
  ** library functions.
   */
  { "ssl_use_sslv2", DT_BOOL, R_NONE, OPTSSLV2, 1 },
  /*
  ** .pp
  ** This variables specifies whether to attempt to use SSLv2 in the
  ** SSL authentication process.
  */
  { "ssl_use_sslv3", DT_BOOL, R_NONE, OPTSSLV3, 1 },
  /*
  ** .pp
  ** This variables specifies whether to attempt to use SSLv3 in the
  ** SSL authentication process.
  */
  { "ssl_use_tlsv1", DT_BOOL, R_NONE, OPTTLSV1, 1 },
  /*
  ** .pp
  ** This variables specifies whether to attempt to use TLSv1 in the
  ** SSL authentication process.
  */
#endif

  { "pipe_split",	DT_BOOL, R_NONE, OPTPIPESPLIT, 0 },
  /*
  ** .pp
  ** Used in connection with the \fIpipe-message\fP command and the ``tag-
  ** prefix'' operator.  If this variable is unset, when piping a list of
  ** tagged messages Mutt will concatenate the messages and will pipe them
  ** as a single folder.  When set, Mutt will pipe the messages one by one.
  ** In both cases the messages are piped in the current sorted order,
  ** and the ``$$pipe_sep'' separator is added after each message.
  */
  { "pipe_decode",	DT_BOOL, R_NONE, OPTPIPEDECODE, 0 },
  /*
  ** .pp
  ** Used in connection with the \fIpipe-message\fP command.  When unset,
  ** Mutt will pipe the messages without any preprocessing. When set, Mutt
  ** will weed headers and will attempt to PGP/MIME decode the messages
  ** first.
  */
  { "pipe_sep",		DT_STR,	 R_NONE, UL &PipeSep, UL "\n" },
  /*
  ** .pp
  ** The separator to add between messages when piping a list of tagged
  ** messages to an external Unix command.
  */
#ifdef USE_POP
  { "pop_authenticators", DT_STR, R_NONE, UL &PopAuthenticators, UL 0 },
  /*
  ** .pp
  ** This is a colon-delimited list of authentication methods mutt may
  ** attempt to use to log in to an POP server, in the order mutt should
  ** try them.  Authentication methods are either 'user', 'apop' or any
  ** SASL mechanism, eg 'digest-md5', 'gssapi' or 'cram-md5'.
  ** This parameter is case-insensitive. If this parameter is unset
  ** (the default) mutt will try all available methods, in order from
  ** most-secure to least-secure.
  ** .pp
  ** Example: set pop_authenticators="digest-md5:apop:user"
  */
  { "pop_auth_try_all",	DT_BOOL, R_NONE, OPTPOPAUTHTRYALL, 1 },
  /*
  ** .pp
  ** If set, Mutt will try all available methods. When unset, Mutt will
  ** only fall back to other authentication methods if the previous
  ** methods are unavailable. If a method is available but authentication
  ** fails, Mutt will not connect to the POP server.
  */
  { "pop_checkinterval", DT_NUM, R_NONE, UL &PopCheckTimeout, 60 },
  /*
  ** .pp
  ** This variable configures how often (in seconds) POP should look for
  ** new mail.
  */
  { "pop_delete",	DT_QUAD, R_NONE, OPT_POPDELETE, M_ASKNO },
  /*
  ** .pp
  ** If set, Mutt will delete successfully downloaded messages from the POP
  ** server when using the fetch-mail function.  When unset, Mutt will
  ** download messages but also leave them on the POP server.
  */
  { "pop_host",		DT_STR,	 R_NONE, UL &PopHost, UL "" },
  /*
  ** .pp
  ** The name of your POP server for the fetch-mail function.  You
  ** can also specify an alternative port, username and password, ie:
  ** .pp
  ** [pop[s]://][username[:password]@]popserver[:port]
  */
  { "pop_last",		DT_BOOL, R_NONE, OPTPOPLAST, 0 },
  /*
  ** .pp
  ** If this variable is set, mutt will try to use the "LAST" POP command
  ** for retrieving only unread messages from the POP server when using
  ** the fetch-mail function.
  */
  { "pop_reconnect",	DT_QUAD, R_NONE, OPT_POPRECONNECT, M_ASKYES },
  /*
  ** .pp
  ** Controls whether or not Mutt will try to reconnect to POP server when
  ** connection lost.
  */
  { "pop_user",		DT_STR,	 R_NONE, UL &PopUser, 0 },
  /*
  ** .pp
  ** Your login name on the POP server.
  ** .pp
  ** This variable defaults to your user name on the local machine.
  */
  { "pop_pass",		DT_STR,	 R_NONE, UL &PopPass, UL "" },
  /*
  ** .pp
  ** Specifies the password for your POP account.  If unset, Mutt will
  ** prompt you for your password when you open POP mailbox.
  ** \fBWarning\fP: you should only use this option when you are on a
  ** fairly secure machine, because the superuser can read your muttrc
  ** even if you are the only one who can read the file.
  */
#endif /* USE_POP */
  { "post_indent_string",DT_STR, R_NONE, UL &PostIndentString, UL "" },
  /*
  ** .pp
  ** Similar to the ``$$attribution'' variable, Mutt will append this
  ** string after the inclusion of a message which is being replied to.
  */
  { "post_indent_str",  DT_SYN,  R_NONE, UL "post_indent_string", 0 },
  /*
  */
  { "postpone",		DT_QUAD, R_NONE, OPT_POSTPONE, M_ASKYES },
  /*
  ** .pp
  ** Controls whether or not messages are saved in the ``$$postponed''
  ** mailbox when you elect not to send immediately.
  */
  { "postponed",	DT_PATH, R_NONE, UL &Postponed, UL "~/postponed" },
  /*
  ** .pp
  ** Mutt allows you to indefinitely ``$postpone sending a message'' which
  ** you are editing.  When you choose to postpone a message, Mutt saves it
  ** in the mailbox specified by this variable.  Also see the ``$$postpone''
  ** variable.
  */
#ifdef USE_SOCKET
  { "preconnect",	DT_STR, R_NONE, UL &Preconnect, UL 0},
  /*
  ** .pp
  ** If set, a shell command to be executed if mutt fails to establish
  ** a connection to the server. This is useful for setting up secure
  ** connections, e.g. with ssh(1). If the command returns a  nonzero
  ** status, mutt gives up opening the server. Example:
  ** .pp
  ** preconnect="ssh -f -q -L 1234:mailhost.net:143 mailhost.net
  **                   sleep 20 < /dev/null > /dev/null"
  ** .pp
  ** Mailbox 'foo' on mailhost.net can now be reached
  ** as '{localhost:1234}foo'.
  ** .pp
  ** NOTE: For this example to work, you must be able to log in to the
  ** remote machine without having to enter a password.
  */
#endif /* USE_SOCKET */
  { "print",		DT_QUAD, R_NONE, OPT_PRINT, M_ASKNO },
  /*
  ** .pp
  ** Controls whether or not Mutt asks for confirmation before printing.
  ** This is useful for people (like me) who accidentally hit ``p'' often.
  */
  { "print_command",	DT_PATH, R_NONE, UL &PrintCmd, UL "lpr" },
  /*
  ** .pp
  ** This specifies the command pipe that should be used to print messages.
  */
  { "print_cmd",	DT_SYN,  R_NONE, UL "print_command", 0 },
  /*
  */
  { "print_decode",	DT_BOOL, R_NONE, OPTPRINTDECODE, 1 },
  /*
  ** .pp
  ** Used in connection with the print-message command.  If this
  ** option is set, the message is decoded before it is passed to the
  ** external command specified by $$print_command.  If this option
  ** is unset, no processing will be applied to the message when
  ** printing it.  The latter setting may be useful if you are using
  ** some advanced printer filter which is able to properly format
  ** e-mail messages for printing.
  */
  { "print_split",	DT_BOOL, R_NONE, OPTPRINTSPLIT,  0 },
  /*
  ** .pp
  ** Used in connection with the print-message command.  If this option
  ** is set, the command sepcified by $$print_command is executed once for
  ** each message which is to be printed.  If this option is unset, 
  ** the command specified by $$print_command is executed only once, and
  ** all the messages are concatenated, with a form feed as the message
  ** separator.
  ** .pp
  ** Those who use the \fBenscript\fP(1) program's mail-printing mode will
  ** most likely want to set this option.
  */
  { "prompt_after",	DT_BOOL, R_NONE, OPTPROMPTAFTER, 1 },
  /*
  ** .pp
  ** If you use an \fIexternal\fP ``$$pager'', setting this variable will
  ** cause Mutt to prompt you for a command when the pager exits rather
  ** than returning to the index menu.  If unset, Mutt will return to the
  ** index menu when the external pager exits.
  */
  { "query_command",	DT_PATH, R_NONE, UL &QueryCmd, UL "" },
  /*
  ** .pp
  ** This specifies the command that mutt will use to make external address
  ** queries.  The string should contain a %s, which will be substituted
  ** with the query string the user types.  See ``$query'' for more
  ** information.
  */
  { "quit",		DT_QUAD, R_NONE, OPT_QUIT, M_YES },
  /*
  ** .pp
  ** This variable controls whether ``quit'' and ``exit'' actually quit
  ** from mutt.  If it set to yes, they do quit, if it is set to no, they
  ** have no effect, and if it is set to ask-yes or ask-no, you are
  ** prompted for confirmation when you try to quit.
  */
  { "quote_regexp",	DT_RX,	 R_PAGER, UL &QuoteRegexp, UL "^([ \t]*[|>:}#])+" },
  /*
  ** .pp
  ** A regular expression used in the internal-pager to determine quoted
  ** sections of text in the body of a message.
  ** .pp
  ** \fBNote:\fP In order to use the \fIquoted\fP\fBx\fP patterns in the
  ** internal pager, you need to set this to a regular expression that
  ** matches \fIexactly\fP the quote characters at the beginning of quoted
  ** lines.
  */
  { "read_inc",		DT_NUM,	 R_NONE, UL &ReadInc, 10 },
  /*
  ** .pp
  ** If set to a value greater than 0, Mutt will display which message it
  ** is currently on when reading a mailbox.  The message is printed after
  ** \fIread_inc\fP messages have been read (e.g., if set to 25, Mutt will
  ** print a message when it reads message 25, and then again when it gets
  ** to message 50).  This variable is meant to indicate progress when
  ** reading large mailboxes which may take some time.
  ** When set to 0, only a single message will appear before the reading
  ** the mailbox.
  ** .pp
  ** Also see the ``$$write_inc'' variable.
  */
  { "read_only",	DT_BOOL, R_NONE, OPTREADONLY, 0 },
  /*
  ** .pp
  ** If set, all folders are opened in read-only mode.
  */
  { "realname",		DT_STR,	 R_BOTH, UL &Realname, 0 },
  /*
  ** .pp
  ** This variable specifies what "real" or "personal" name should be used
  ** when sending messages.
  ** .pp
  ** By default, this is the GCOS field from /etc/passwd.  Note that this
  ** variable will \fInot\fP be used when the user has set a real name
  ** in the $$from variable.
  */
  { "recall",		DT_QUAD, R_NONE, OPT_RECALL, M_ASKYES },
  /*
  ** .pp
  ** Controls whether or not you are prompted to recall postponed messages
  ** when composing a new message.  Also see ``$$postponed''.
  ** .pp
  ** Setting this variable to ``yes'' is not generally useful, and thus not
  ** recommended.
  */
  { "record",		DT_PATH, R_NONE, UL &Outbox, UL "" },
  /*
  ** .pp
  ** This specifies the file into which your outgoing messages should be
  ** appended.  (This is meant as the primary method for saving a copy of
  ** your messages, but another way to do this is using the ``$my_hdr''
  ** command to create a \fIBcc:\fP field with your email address in it.)
  ** .pp
  ** The value of \fI$$record\fP is overridden by the ``$$force_name'' and
  ** ``$$save_name'' variables, and the ``$fcc-hook'' command.
  */
  { "reply_regexp",	DT_RX,	 R_INDEX|R_RESORT, UL &ReplyRegexp, UL "^(re([\\[0-9\\]+])*|aw):[ \t]*" },
  /*
  ** .pp
  ** A regular expression used to recognize reply messages when threading
  ** and replying. The default value corresponds to the English "Re:" and
  ** the German "Aw:".
  */
  { "reply_self",	DT_BOOL, R_NONE, OPTREPLYSELF, 0 },
  /*
  ** .pp
  ** If unset and you are replying to a message sent by you, Mutt will
  ** assume that you want to reply to the recipients of that message rather
  ** than to yourself.
  */
  { "reply_to",		DT_QUAD, R_NONE, OPT_REPLYTO, M_ASKYES },
  /*
  ** .pp
  ** If set, Mutt will ask you if you want to use the address listed in the
  ** Reply-To: header field when replying to a message.  If you answer no,
  ** it will use the address in the From: header field instead.  This
  ** option is useful for reading a mailing list that sets the Reply-To:
  ** header field to the list address and you want to send a private
  ** message to the author of a message.
  */
  { "resolve",		DT_BOOL, R_NONE, OPTRESOLVE, 1 },
  /*
  ** .pp
  ** When set, the cursor will be automatically advanced to the next
  ** (possibly undeleted) message whenever a command that modifies the
  ** current message is executed.
  */
  { "reverse_alias",	DT_BOOL, R_BOTH, OPTREVALIAS, 0 },
  /*
  ** .pp
  ** This variable controls whether or not Mutt will display the "personal"
  ** name from your aliases in the index menu if it finds an alias that
  ** matches the message's sender.  For example, if you have the following
  ** alias:
  ** .pp
  ** .ts
  **  alias juser abd30425@somewhere.net (Joe User)
  ** .te
  ** .pp
  ** and then you receive mail which contains the following header:
  ** .pp
  ** .ts
  **  From: abd30425@somewhere.net
  ** .te
  ** .pp
  ** It would be displayed in the index menu as ``Joe User'' instead of
  ** ``abd30425@somewhere.net.''  This is useful when the person's e-mail
  ** address is not human friendly (like CompuServe addresses).
  */
  { "reverse_name",	DT_BOOL, R_BOTH, OPTREVNAME, 0 },
  /*
  ** .pp
  ** It may sometimes arrive that you receive mail to a certain machine,
  ** move the messages to another machine, and reply to some the messages
  ** from there.  If this variable is set, the default \fIFrom:\fP line of
  ** the reply messages is built using the address where you received the
  ** messages you are replying to.  If the variable is unset, the
  ** \fIFrom:\fP line will use your address on the current machine.
  */
  { "reverse_realname",	DT_BOOL, R_BOTH, OPTREVREAL, 1 },
  /*
  ** .pp
  ** This variable fine-tunes the behaviour of the $reverse_name feature.
  ** When it is set, mutt will use the address from incoming messages as-is,
  ** possibly including eventual real names.  When it is unset, mutt will
  ** override any such realnames with the setting of the $realname variable.
  */
  { "rfc2047_parameters", DT_BOOL, R_NONE, OPTRFC2047PARAMS, 0 },
  /*
  ** .pp
  ** When this variable is set, Mutt will decode RFC-2047-encoded MIME 
  ** parameters. You want to set this variable when mutt suggests you
  ** to save attachments to files named like this: 
  ** =?iso-8859-1?Q?file=5F=E4=5F991116=2Ezip?=
  ** .pp
  ** When this variable is set interactively, the change doesn't have
  ** the desired effect before you have changed folders.
  ** .pp
  ** Note that this use of RFC 2047's encoding is explicitly,
  ** prohibited by the standard, but nevertheless encountered in the
  ** wild.
  ** Also note that setting this parameter will \fInot\fP have the effect 
  ** that mutt \fIgenerates\fP this kind of encoding.  Instead, mutt will
  ** unconditionally use the encoding specified in RFC 2231.
  */
  { "save_address",	DT_BOOL, R_NONE, OPTSAVEADDRESS, 0 },
  /*
  ** .pp
  ** If set, mutt will take the sender's full address when choosing a
  ** default folder for saving a mail. If ``$$save_name'' or ``$$force_name''
  ** is set too, the selection of the fcc folder will be changed as well.
  */
  { "save_empty",	DT_BOOL, R_NONE, OPTSAVEEMPTY, 1 },
  /*
  ** .pp
  ** When unset, mailboxes which contain no saved messages will be removed
  ** when closed (the exception is ``$$spoolfile'' which is never removed).
  ** If set, mailboxes are never removed.
  ** .pp
  ** \fBNote:\fP This only applies to mbox and MMDF folders, Mutt does not
  ** delete MH and Maildir directories.
  */
  { "save_name",	DT_BOOL, R_NONE, OPTSAVENAME, 0 },
  /*
  ** .pp
  ** This variable controls how copies of outgoing messages are saved.
  ** When set, a check is made to see if a mailbox specified by the
  ** recipient address exists (this is done by searching for a mailbox in
  ** the ``$$folder'' directory with the \fIusername\fP part of the
  ** recipient address).  If the mailbox exists, the outgoing message will
  ** be saved to that mailbox, otherwise the message is saved to the
  ** ``$$record'' mailbox.
  ** .pp
  ** Also see the ``$$force_name'' variable.
  */
  { "score", 		DT_BOOL, R_NONE, OPTSCORE, 1 },
  /*
  ** .pp
  ** When this variable is \fIunset\fP, scoring is turned off.  This can
  ** be useful to selectively disable scoring for certain folders when the
  ** ``$$score_threshold_delete'' variable and friends are used.
  **
  */
  { "score_threshold_delete", DT_NUM, R_NONE, UL &ScoreThresholdDelete, UL -1 },
  /*
  ** .pp
  ** Messages which have been assigned a score equal to or lower than the value
  ** of this variable are automatically marked for deletion by mutt.  Since
  ** mutt scores are always greater than or equal to zero, the default setting
  ** of this variable will never mark a message for deletion.
  */
  { "score_threshold_flag", DT_NUM, R_NONE, UL &ScoreThresholdFlag, 9999 },
  /* 
  ** .pp
  ** Messages wich have been assigned a score greater than or equal to this 
  ** variable's value are automatically marked "flagged".
  */
  { "score_threshold_read", DT_NUM, R_NONE, UL &ScoreThresholdRead, UL -1 },
  /*
  ** .pp
  ** Messages which have been assigned a score equal to or lower than the value
  ** of this variable are automatically marked as read by mutt.  Since
  ** mutt scores are always greater than or equal to zero, the default setting
  ** of this variable will never mark a message read.
  */
  { "send_charset",	DT_STR,  R_NONE, UL &SendCharset, UL "us-ascii:iso-8859-1:utf-8" },
  /*
  ** .pp
  ** A list of character sets for outgoing messages. Mutt will use the
  ** first character set into which the text can be converted exactly.
  ** If your ``$$charset'' is not iso-8859-1 and recipients may not
  ** understand UTF-8, it is advisable to include in the list an
  ** appropriate widely used standard character set (such as
  ** iso-8859-2, koi8-r or iso-2022-jp) either instead of or after
  ** "iso-8859-1".
  */
  { "sendmail",		DT_PATH, R_NONE, UL &Sendmail, UL SENDMAIL " -oem -oi" },
  /*
  ** .pp
  ** Specifies the program and arguments used to deliver mail sent by Mutt.
  ** Mutt expects that the specified program interprets additional
  ** arguments as recipient addresses.
  */
  { "sendmail_wait",	DT_NUM,  R_NONE, UL &SendmailWait, 0 },
  /*
  ** .pp
  ** Specifies the number of seconds to wait for the ``$$sendmail'' process
  ** to finish before giving up and putting delivery in the background.
  ** .pp
  ** Mutt interprets the value of this variable as follows:
  ** .dl
  ** .dt >0 .dd number of seconds to wait for sendmail to finish before continuing
  ** .dt 0  .dd wait forever for sendmail to finish
