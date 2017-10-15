  ** Controls whether 8-bit data is converted to 7-bit using either Quoted-
  ** Printable or Base64 encoding when sending mail.
  */
  { "allow_ansi",      DT_BOOL, R_NONE, OPTALLOWANSI, 0 },
  /*
  ** .pp
  ** Controls whether ANSI color codes in messages (and color tags in
  ** rich text messages) are to be interpreted.
  ** Messages containing these codes are rare, but if this option is \fIset\fP,
  ** their text will be colored accordingly. Note that this may override
  ** your color choices, and even present a security problem, since a
  ** message could include a line like
  ** .ts
  ** [-- PGP output follows ...
  ** .te
  ** .pp
  ** and give it the same color as your attachment color (see also
  ** $$crypt_timestamp).
  */
  { "arrow_cursor",	DT_BOOL, R_BOTH, OPTARROWCURSOR, 0 },
  /*
  ** .pp
  ** When \fIset\fP, an arrow (``->'') will be used to indicate the current entry
  ** in menus instead of highlighting the whole line.  On slow network or modem
  ** links this will make response faster because there is less that has to
  ** be redrawn on the screen when moving to the next or previous entries
  ** in the menu.
  */
  { "ascii_chars",	DT_BOOL, R_BOTH, OPTASCIICHARS, 0 },
  /*
  ** .pp
  ** If \fIset\fP, Mutt will use plain ASCII characters when displaying thread
  ** and attachment trees, instead of the default \fIACS\fP characters.
  */
  { "askbcc",		DT_BOOL, R_NONE, OPTASKBCC, 0 },
  /*
  ** .pp
  ** If \fIset\fP, Mutt will prompt you for blind-carbon-copy (Bcc) recipients
  ** before editing an outgoing message.
  */
  { "askcc",		DT_BOOL, R_NONE, OPTASKCC, 0 },
  /*
  ** .pp
  ** If \fIset\fP, Mutt will prompt you for carbon-copy (Cc) recipients before
  ** editing the body of an outgoing message.
  */
  { "assumed_charset", DT_STR, R_NONE, UL &AssumedCharset, UL 0},
  /*
  ** .pp
  ** This variable is a colon-separated list of character encoding
  ** schemes for messages without character encoding indication.
  ** Header field values and message body content without character encoding
  ** indication would be assumed that they are written in one of this list.
  ** By default, all the header fields and message body without any charset
  ** indication are assumed to be in ``us-ascii''.
  ** .pp
  ** For example, Japanese users might prefer this:
  ** .ts
  ** set assumed_charset="iso-2022-jp:euc-jp:shift_jis:utf-8"
  ** .te
  ** .pp
  ** However, only the first content is valid for the message body.
  */
  { "attach_charset",    DT_STR,  R_NONE, UL &AttachCharset, UL 0 },
  /*
  ** .pp
  ** This variable is a colon-separated list of character encoding
  ** schemes for text file attachments. Mutt uses this setting to guess
  ** which encoding files being attached are encoded in to convert them to
  ** a proper character set given in $$send_charset.
  ** .pp
  ** If \fIunset\fP, the value of $$charset will be used instead.
  ** For example, the following configuration would work for Japanese
  ** text handling:
  ** .ts
  ** set attach_charset="iso-2022-jp:euc-jp:shift_jis:utf-8"
  ** .te
  ** .pp
  ** Note: for Japanese users, ``iso-2022-*'' must be put at the head
  ** of the value as shown above if included.
  */
  { "attach_format",	DT_STR,  R_NONE, UL &AttachFormat, UL "%u%D%I %t%4n %T%.40d%> [%.7m/%.10M, %.6e%?C?, %C?, %s] " },
  /*
  ** .pp
  ** This variable describes the format of the ``attachment'' menu.  The
  ** following \fCprintf(3)\fP-style sequences are understood:
  ** .dl
  ** .dt %C  .dd charset
  ** .dt %c  .dd requires charset conversion (``n'' or ``c'')
  ** .dt %D  .dd deleted flag
  ** .dt %d  .dd description
  ** .dt %e  .dd MIME content-transfer-encoding
  ** .dt %f  .dd filename
  ** .dt %I  .dd disposition (``I'' for inline, ``A'' for attachment)
  ** .dt %m  .dd major MIME type
  ** .dt %M  .dd MIME subtype
  ** .dt %n  .dd attachment number
  ** .dt %Q  .dd ``Q'', if MIME part qualifies for attachment counting
  ** .dt %s  .dd size
  ** .dt %t  .dd tagged flag
  ** .dt %T  .dd graphic tree characters
  ** .dt %u  .dd unlink (=to delete) flag
  ** .dt %X  .dd number of qualifying MIME parts in this part and its children
  **             (please see the ``$attachments'' section for possible speed effects)
  ** .dt %>X .dd right justify the rest of the string and pad with character ``X''
  ** .dt %|X .dd pad to the end of the line with character ``X''
  ** .dt %*X .dd soft-fill with character ``X'' as pad
  ** .de
  ** .pp
  ** For an explanation of ``soft-fill'', see the $$index_format documentation.
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
  ** If this variable is \fIunset\fP, when operating (saving, printing, piping,
  ** etc) on a list of tagged attachments, Mutt will concatenate the
  ** attachments and will operate on them as a single attachment. The
  ** $$attach_sep separator is added after each attachment. When \fIset\fP,
  ** Mutt will operate on the attachments one by one.
  */
  { "attribution",	DT_STR,	 R_NONE, UL &Attribution, UL "On %d, %n wrote:" },
  /*
  ** .pp
  ** This is the string that will precede a message which has been included
  ** in a reply.  For a full listing of defined \fCprintf(3)\fP-like sequences see
  ** the section on $$index_format.
  */
  { "auto_tag",		DT_BOOL, R_NONE, OPTAUTOTAG, 0 },
  /*
  ** .pp
  ** When \fIset\fP, functions in the \fIindex\fP menu which affect a message
  ** will be applied to all tagged messages (if there are any).  When
  ** unset, you must first use the \fC<tag-prefix>\fP function (bound to ``;''
  ** by default) to make the next function apply to all tagged messages.
  */
  { "autoedit",		DT_BOOL, R_NONE, OPTAUTOEDIT, 0 },
  /*
  ** .pp
  ** When \fIset\fP along with $$edit_headers, Mutt will skip the initial
  ** send-menu (prompting for subject and recipients) and allow you to
  ** immediately begin editing the body of your
  ** message.  The send-menu may still be accessed once you have finished
  ** editing the body of your message.
  ** .pp
  ** .pp
  ** \fBNote:\fP when this option is \fIset\fP, you cannot use send-hooks that depend
  ** on the recipients when composing a new (non-reply) message, as the initial
  ** list of recipients is empty.
  ** .pp
  ** Also see $$fast_reply.
  */
  { "beep",		DT_BOOL, R_NONE, OPTBEEP, 1 },
  /*
  ** .pp
  ** When this variable is \fIset\fP, mutt will beep when an error occurs.
  */
  { "beep_new",		DT_BOOL, R_NONE, OPTBEEPNEW, 0 },
  /*
  ** .pp
  ** When this variable is \fIset\fP, mutt will beep whenever it prints a message
  ** notifying you of new mail.  This is independent of the setting of the
  ** $$beep variable.
  */
  { "bounce",	DT_QUAD, R_NONE, OPT_BOUNCE, M_ASKYES },
  /*
  ** .pp
  ** Controls whether you will be asked to confirm bouncing messages.
  ** If set to \fIyes\fP you don't get asked if you want to bounce a
  ** message. Setting this variable to \fIno\fP is not generally useful,
  ** and thus not recommended, because you are unable to bounce messages.
  */
  { "bounce_delivered", DT_BOOL, R_NONE, OPTBOUNCEDELIVERED, 1 },
  /*
  ** .pp
  ** When this variable is \fIset\fP, mutt will include Delivered-To headers when
  ** bouncing messages.  Postfix users may wish to \fIunset\fP this variable.
  */
  { "braille_friendly", DT_BOOL, R_NONE, OPTBRAILLEFRIENDLY, 0 },
  /*
  ** .pp
  ** When this variable is \fIset\fP, mutt will place the cursor at the beginning
  ** of the current line in menus, even when the $$arrow_cursor variable
  ** is \fIunset\fP, making it easier for blind persons using Braille displays to
  ** follow these menus.  The option is \fIunset\fP by default because many
  ** visual terminals don't permit making the cursor invisible.
  */
#if defined(USE_SSL)
  { "certificate_file",	DT_PATH, R_NONE, UL &SslCertFile, UL "~/.mutt_certificates" },
  /*
  ** .pp
  ** This variable specifies the file where the certificates you trust
  ** are saved. When an unknown certificate is encountered, you are asked
  ** if you accept it or not. If you accept it, the certificate can also
  ** be saved in this file and further connections are automatically
  ** accepted.
  ** .pp
  ** You can also manually add CA certificates in this file. Any server
  ** certificate that is signed with one of these CA certificates is
  ** also automatically accepted.
  ** .pp
  ** Example:
  ** .ts
  ** set certificate_file=~/.mutt/certificates
  ** .te
  **
  */
#endif
  { "charset",		DT_STR,	 R_NONE, UL &Charset, UL 0 },
  /*
  ** .pp
  ** Character set your terminal uses to display and enter textual data.
  ** It is also the fallback for $$send_charset.
  ** .pp
  ** Upon startup Mutt tries to derive this value from environment variables
  ** such as \fC$$$LC_CTYPE\fP or \fC$$$LANG\fP.
  ** .pp
  ** \fBNote:\fP It should only be set in case Mutt isn't able to determine the
  ** character set used correctly.
  */
  { "check_mbox_size",	DT_BOOL, R_NONE, OPTCHECKMBOXSIZE, 0 },
  /*
  ** .pp
  ** When this variable is \fIset\fP, mutt will use file size attribute instead of
  ** access time when checking for new mail in mbox and mmdf folders.
  ** .pp
  ** This variable is \fIunset\fP by default and should only be enabled when
  ** new mail detection for these folder types is unreliable or doesn't work.
  ** .pp
  ** Note that enabling this variable should happen before any ``$mailboxes''
  ** directives occur in configuration files regarding mbox or mmdf folders
  ** because mutt needs to determine the initial new mail status of such a
  ** mailbox by performing a fast mailbox scan when it is defined.
  ** Afterwards the new mail status is tracked by file size changes.
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
  ** this variable is \fIunset\fP, no check for new mail is performed
  ** while the mailbox is open.
  */
  { "collapse_unread",	DT_BOOL, R_NONE, OPTCOLLAPSEUNREAD, 1 },
  /*
  ** .pp
  ** When \fIunset\fP, Mutt will not collapse a thread if it contains any
  ** unread messages.
  */
  { "compose_format",	DT_STR,	 R_BOTH, UL &ComposeFormat, UL "-- Mutt: Compose  [Approx. msg size: %l   Atts: %a]%>-" },
  /*
  ** .pp
  ** Controls the format of the status line displayed in the ``compose''
  ** menu.  This string is similar to $$status_format, but has its own
  ** set of \fCprintf(3)\fP-like sequences:
  ** .dl
  ** .dt %a .dd total number of attachments
  ** .dt %h .dd local hostname
  ** .dt %l .dd approximate size (in bytes) of the current message
  ** .dt %v .dd Mutt version string
  ** .de
  ** .pp
  ** See the text describing the $$status_format option for more
  ** information on how to set $$compose_format.
  */
  { "config_charset",	DT_STR,  R_NONE, UL &ConfigCharset, UL 0 },
  /*
  ** .pp
  ** When defined, Mutt will recode commands in rc files from this
  ** encoding to the current character set as specified by $$charset
  ** and aliases written to $$alias_file from the current character set.
  ** .pp
  ** Please note that if setting $$charset it must be done before
  ** setting $$config_charset.
  ** .pp
  ** Recoding should be avoided as it may render unconvertable
  ** characters as question marks which can lead to undesired
  ** side effects (for example in regular expressions).
  */
  { "confirmappend",	DT_BOOL, R_NONE, OPTCONFIRMAPPEND, 1 },
  /*
  ** .pp
  ** When \fIset\fP, Mutt will prompt for confirmation when appending messages to
  ** an existing mailbox.
  */
  { "confirmcreate",	DT_BOOL, R_NONE, OPTCONFIRMCREATE, 1 },
  /*
  ** .pp
  ** When \fIset\fP, Mutt will prompt for confirmation when saving messages to a
  ** mailbox which does not yet exist before creating it.
  */
  { "connect_timeout",	DT_NUM,	R_NONE, UL &ConnectTimeout, 30 },
  /*
  ** .pp
  ** Causes Mutt to timeout a network connection (for IMAP, POP or SMTP) after this
  ** many seconds if the connection is not able to be established.  A negative
  ** value causes Mutt to wait indefinitely for the connection attempt to succeed.
  */
  { "content_type",	DT_STR, R_NONE, UL &ContentType, UL "text/plain" },
  /*
  ** .pp
  ** Sets the default Content-Type for the body of newly composed messages.
  */
  { "copy",		DT_QUAD, R_NONE, OPT_COPY, M_YES },
  /*
  ** .pp
  ** This variable controls whether or not copies of your outgoing messages
  ** will be saved for later references.  Also see $$record,
  ** $$save_name, $$force_name and ``$fcc-hook''.
  */
  { "pgp_autoencrypt",		DT_SYN,  R_NONE, UL "crypt_autoencrypt", 0 },
  { "crypt_autoencrypt",	DT_BOOL, R_NONE, OPTCRYPTAUTOENCRYPT, 0 },
  /*
  ** .pp
  ** Setting this variable will cause Mutt to always attempt to PGP
  ** encrypt outgoing messages.  This is probably only useful in
  ** connection to the ``$send-hook'' command.  It can be overridden
  ** by use of the pgp menu, when encryption is not required or
  ** signing is requested as well.  If $$smime_is_default is \fIset\fP,
  ** then OpenSSL is used instead to create S/MIME messages and
  ** settings can be overridden by use of the smime menu instead.
  ** (Crypto only)
  */
  { "crypt_autopgp",	DT_BOOL, R_NONE, OPTCRYPTAUTOPGP, 1 },
  /*
  ** .pp
  ** This variable controls whether or not mutt may automatically enable
  ** PGP encryption/signing for messages.  See also $$crypt_autoencrypt,
  ** $$crypt_replyencrypt,
  ** $$crypt_autosign, $$crypt_replysign and $$smime_is_default.
  */
  { "pgp_autosign", 	DT_SYN,  R_NONE, UL "crypt_autosign", 0 },
  { "crypt_autosign",	DT_BOOL, R_NONE, OPTCRYPTAUTOSIGN, 0 },
  /*
  ** .pp
  ** Setting this variable will cause Mutt to always attempt to
  ** cryptographically sign outgoing messages.  This can be overridden
  ** by use of the pgp menu, when signing is not required or
  ** encryption is requested as well. If $$smime_is_default is \fIset\fP,
  ** then OpenSSL is used instead to create S/MIME messages and settings can
  ** be overridden by use of the smime menu instead of the pgp menu.
  ** (Crypto only)
  */
  { "crypt_autosmime",	DT_BOOL, R_NONE, OPTCRYPTAUTOSMIME, 1 },
  /*
  ** .pp
  ** This variable controls whether or not mutt may automatically enable
  ** S/MIME encryption/signing for messages. See also $$crypt_autoencrypt,
  ** $$crypt_replyencrypt,
  ** $$crypt_autosign, $$crypt_replysign and $$smime_is_default.
  */
  { "pgp_replyencrypt",		DT_SYN,  R_NONE, UL "crypt_replyencrypt", 1  },
  { "crypt_replyencrypt",	DT_BOOL, R_NONE, OPTCRYPTREPLYENCRYPT, 1 },
  /*
  ** .pp
  ** If \fIset\fP, automatically PGP or OpenSSL encrypt replies to messages which are
  ** encrypted.
  ** (Crypto only)
  */
  { "pgp_replysign",	DT_SYN, R_NONE, UL "crypt_replysign", 0 },
  { "crypt_replysign",	DT_BOOL, R_NONE, OPTCRYPTREPLYSIGN, 0 },
  /*
  ** .pp
  ** If \fIset\fP, automatically PGP or OpenSSL sign replies to messages which are
  ** signed.
  ** .pp
  ** \fBNote:\fP this does not work on messages that are encrypted
  ** \fIand\fP signed!
  ** (Crypto only)
  */
  { "pgp_replysignencrypted",   DT_SYN,  R_NONE, UL "crypt_replysignencrypted", 0},
  { "crypt_replysignencrypted", DT_BOOL, R_NONE, OPTCRYPTREPLYSIGNENCRYPTED, 0 },
  /*
  ** .pp
  ** If \fIset\fP, automatically PGP or OpenSSL sign replies to messages
  ** which are encrypted. This makes sense in combination with
  ** $$crypt_replyencrypt, because it allows you to sign all
  ** messages which are automatically encrypted.  This works around
  ** the problem noted in $$crypt_replysign, that mutt is not able
  ** to find out whether an encrypted message is also signed.
  ** (Crypto only)
  */
  { "crypt_timestamp", DT_BOOL, R_NONE, OPTCRYPTTIMESTAMP, 1 },
  /*
  ** .pp
  ** If \fIset\fP, mutt will include a time stamp in the lines surrounding
  ** PGP or S/MIME output, so spoofing such lines is more difficult.
  ** If you are using colors to mark these lines, and rely on these,
  ** you may \fIunset\fP this setting.
  ** (Crypto only)
  */
  { "crypt_use_gpgme",  DT_BOOL, R_NONE, OPTCRYPTUSEGPGME, 0 },
  /*
  ** .pp
  ** This variable controls the use of the GPGME-enabled crypto backends.
  ** If it is \fIset\fP and Mutt was built with gpgme support, the gpgme code for
  ** S/MIME and PGP will be used instead of the classic code.  Note that
  ** you need to set this option in .muttrc; it won't have any effect when
  ** used interactively.
  */
  { "crypt_use_pka", DT_BOOL, R_NONE, OPTCRYPTUSEPKA, 0 },
  /*
  ** .pp
  ** Controls whether mutt uses PKA
  ** (see http://www.g10code.de/docs/pka-intro.de.pdf) during signature
  ** verification (only supported by the GPGME backend).
  */
  { "pgp_verify_sig",   DT_SYN,  R_NONE, UL "crypt_verify_sig", 0},
  { "crypt_verify_sig",	DT_QUAD, R_NONE, OPT_VERIFYSIG, M_YES },
  /*
  ** .pp
  ** If \fI``yes''\fP, always attempt to verify PGP or S/MIME signatures.
  ** If \fI``ask-*''\fP, ask whether or not to verify the signature.
  ** If \fI``no''\fP, never attempt to verify cryptographic signatures.
  ** (Crypto only)
  */
  { "date_format",	DT_STR,	 R_BOTH, UL &DateFmt, UL "!%a, %b %d, %Y at %I:%M:%S%p %Z" },
  /*
  ** .pp
  ** This variable controls the format of the date printed by the ``%d''
  ** sequence in $$index_format.  This is passed to the \fCstrftime(3)\fP
  ** function to process the date, see the man page for the proper syntax.
  ** .pp
  ** Unless the first character in the string is a bang (``!''), the month
  ** and week day names are expanded according to the locale specified in
  ** the variable $$locale. If the first character in the string is a
  ** bang, the bang is discarded, and the month and week day names in the
  ** rest of the string are expanded in the \fIC\fP locale (that is in US
  ** English).
  */
  { "default_hook",	DT_STR,	 R_NONE, UL &DefaultHook, UL "~f %s !~P | (~P ~C %s)" },
  /*
  ** .pp
  ** This variable controls how ``$message-hook'', ``$reply-hook'', ``$send-hook'',
  ** ``$send2-hook'', ``$save-hook'', and ``$fcc-hook'' will
  ** be interpreted if they are specified with only a simple regexp,
  ** instead of a matching pattern.  The hooks are expanded when they are
  ** declared, so a hook will be interpreted according to the value of this
  ** variable at the time the hook is declared.
  ** .pp
  ** The default value matches
  ** if the message is either from a user matching the regular expression
  ** given, or if it is from you (if the from address matches
  ** ``$alternates'') and is to or cc'ed to a user matching the given
  ** regular expression.
  */
  { "delete",		DT_QUAD, R_NONE, OPT_DELETE, M_ASKYES },
  /*
  ** .pp
  ** Controls whether or not messages are really deleted when closing or
