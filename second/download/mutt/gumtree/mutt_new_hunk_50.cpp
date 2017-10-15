  ** will be informed as to where to find the output.
  */
  { "shell",		DT_PATH, R_NONE, UL &Shell, 0 },
  /*
  ** .pp
  ** Command to use when spawning a subshell.  By default, the user's login
  ** shell from \fC/etc/passwd\fP is used.
  */
  { "sig_dashes",	DT_BOOL, R_NONE, OPTSIGDASHES, 1 },
  /*
  ** .pp
  ** If \fIset\fP, a line containing ``-- '' (note the trailing space) will be inserted before your
  ** $$signature.  It is \fBstrongly\fP recommended that you not \fIunset\fP
  ** this variable unless your signature contains just your name.  The
  ** reason for this is because many software packages use ``-- \n'' to
  ** detect your signature.  For example, Mutt has the ability to highlight
  ** the signature in a different color in the built-in pager.
  */
  { "sig_on_top",	DT_BOOL, R_NONE, OPTSIGONTOP, 0},
  /*
  ** .pp
  ** If \fIset\fP, the signature will be included before any quoted or forwarded
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
  ** its standard output.
  */
  { "simple_search",	DT_STR,	 R_NONE, UL &SimpleSearch, UL "~f %s | ~s %s" },
  /*
  ** .pp
  ** Specifies how Mutt should expand a simple search into a real search
  ** pattern.  A simple search is one that does not contain any of the ``~'' pattern
  ** operators.  See ``$patterns'' for more information on search patterns.
  ** .pp
  ** For example, if you simply type ``joe'' at a search or limit prompt, Mutt
  ** will automatically expand it to the value specified by this variable by
  ** replacing ``%s'' with the supplied string.
  ** For the default value, ``joe'' would be expanded to: ``~f joe | ~s joe''.
  */
  { "sleep_time",	DT_NUM, R_NONE, UL &SleepTime, 1 },
  /*
  ** .pp
  ** Specifies time, in seconds, to pause while displaying certain informational
  ** messages, while moving from folder to folder and after expunging
  ** messages from the current folder.  The default is to pause one second, so
  ** a value of zero for this option suppresses the pause.
  */
  { "smart_wrap",	DT_BOOL, R_PAGER, OPTWRAP, 1 },
  /*
  ** .pp
  ** Controls the display of lines longer than the screen width in the
  ** internal pager. If \fIset\fP, long lines are wrapped at a word boundary.  If
  ** \fIunset\fP, lines are simply wrapped at the screen edge. Also see the
  ** $$markers variable.
  */
  { "smileys",		DT_RX,	 R_PAGER, UL &Smileys, UL "(>From )|(:[-^]?[][)(><}{|/DP])" },
  /*
  ** .pp
  ** The \fIpager\fP uses this variable to catch some common false
  ** positives of $$quote_regexp, most notably smileys and not consider
  ** a line quoted text if it also matches $$smileys. This mostly
  ** happens at the beginning of a line.
  */



  { "smime_ask_cert_label",	DT_BOOL, R_NONE, OPTASKCERTLABEL, 1 },
  /*
  ** .pp
  ** This flag controls whether you want to be asked to enter a label
  ** for a certificate about to be added to the database or not. It is
  ** \fIset\fP by default.
  ** (S/MIME only)
  */
  { "smime_ca_location",	DT_PATH, R_NONE, UL &SmimeCALocation, 0 },
  /*
  ** .pp
  ** This variable contains the name of either a directory, or a file which
  ** contains trusted certificates for use with OpenSSL.
  ** (S/MIME only)
  */
  { "smime_certificates",	DT_PATH, R_NONE, UL &SmimeCertificates, 0 },
  /*
  ** .pp
  ** Since for S/MIME there is no pubring/secring as with PGP, mutt has to handle
  ** storage and retrieval of keys by itself. This is very basic right
  ** now, and keys and certificates are stored in two different
  ** directories, both named as the hash-value retrieved from
  ** OpenSSL. There is an index file which contains mailbox-address
  ** keyid pairs, and which can be manually edited. This option points to
  ** the location of the certificates.
  ** (S/MIME only)
  */
  { "smime_decrypt_command", 	DT_STR, R_NONE, UL &SmimeDecryptCommand, 0},
  /*
  ** .pp
  ** This format string specifies a command which is used to decrypt
  ** \fCapplication/x-pkcs7-mime\fP attachments.
  ** .pp
  ** The OpenSSL command formats have their own set of \fCprintf(3)\fP-like sequences
  ** similar to PGP's:
  ** .dl
  ** .dt %f .dd Expands to the name of a file containing a message.
  ** .dt %s .dd Expands to the name of a file containing the signature part
  ** .          of a \fCmultipart/signed\fP attachment when verifying it.
  ** .dt %k .dd The key-pair specified with $$smime_default_key
  ** .dt %c .dd One or more certificate IDs.
  ** .dt %a .dd The algorithm used for encryption.
  ** .dt %C .dd CA location:  Depending on whether $$smime_ca_location
  ** .          points to a directory or file, this expands to
  ** .          ``-CApath $$smime_ca_location'' or ``-CAfile $$smime_ca_location''.
  ** .de
  ** .pp
  ** For examples on how to configure these formats, see the \fCsmime.rc\fP in
  ** the \fCsamples/\fP subdirectory which has been installed on your system
  ** alongside the documentation.
  ** (S/MIME only)
  */
  { "smime_decrypt_use_default_key",	DT_BOOL, R_NONE, OPTSDEFAULTDECRYPTKEY, 1 },
  /*
  ** .pp
  ** If \fIset\fP (default) this tells mutt to use the default key for decryption. Otherwise,
  ** if managing multiple certificate-key-pairs, mutt will try to use the mailbox-address
  ** to determine the key to use. It will ask you to supply a key, if it can't find one.
  ** (S/MIME only)
  */
  { "smime_sign_as",			DT_SYN,  R_NONE, UL "smime_default_key", 0 },
  { "smime_default_key",		DT_STR,	 R_NONE, UL &SmimeDefaultKey, 0 },
  /*
  ** .pp
  ** This is the default key-pair to use for signing. This must be set to the
  ** keyid (the hash-value that OpenSSL generates) to work properly
  ** (S/MIME only)
  */
  { "smime_encrypt_command", 	DT_STR, R_NONE, UL &SmimeEncryptCommand, 0},
  /*
  ** .pp
  ** This command is used to create encrypted S/MIME messages.
  ** .pp
  ** This is a format string, see the $$smime_decrypt_command command for
  ** possible \fCprintf(3)\fP-like sequences.
  ** (S/MIME only)
  */
  { "smime_encrypt_with",	DT_STR,	 R_NONE, UL &SmimeCryptAlg, 0 },
  /*
  ** .pp
  ** This sets the algorithm that should be used for encryption.
  ** Valid choices are ``des'', ``des3'', ``rc2-40'', ``rc2-64'', ``rc2-128''.
  ** If \fIunset\fP, ``3des'' (TripleDES) is used.
  ** (S/MIME only)
  */
  { "smime_get_cert_command", 	DT_STR, R_NONE, UL &SmimeGetCertCommand, 0},
  /*
  ** .pp
  ** This command is used to extract X509 certificates from a PKCS7 structure.
  ** .pp
  ** This is a format string, see the $$smime_decrypt_command command for
  ** possible \fCprintf(3)\fP-like sequences.
  ** (S/MIME only)
  */
  { "smime_get_cert_email_command", 	DT_STR, R_NONE, UL &SmimeGetCertEmailCommand, 0},
  /*
  ** .pp
  ** This command is used to extract the mail address(es) used for storing
  ** X509 certificates, and for verification purposes (to check whether the
  ** certificate was issued for the sender's mailbox).
  ** .pp
  ** This is a format string, see the $$smime_decrypt_command command for
  ** possible \fCprintf(3)\fP-like sequences.
  ** (S/MIME only)
  */
  { "smime_get_signer_cert_command", 	DT_STR, R_NONE, UL &SmimeGetSignerCertCommand, 0},
  /*
  ** .pp
  ** This command is used to extract only the signers X509 certificate from a S/MIME
  ** signature, so that the certificate's owner may get compared to the
  ** email's ``From:'' field.
  ** .pp
  ** This is a format string, see the $$smime_decrypt_command command for
  ** possible \fCprintf(3)\fP-like sequences.
  ** (S/MIME only)
  */
  { "smime_import_cert_command", 	DT_STR, R_NONE, UL &SmimeImportCertCommand, 0},
  /*
  ** .pp
  ** This command is used to import a certificate via smime_keys.
  ** .pp
  ** This is a format string, see the $$smime_decrypt_command command for
  ** possible \fCprintf(3)\fP-like sequences.
  ** (S/MIME only)
  */
  { "smime_is_default", DT_BOOL,  R_NONE, OPTSMIMEISDEFAULT, 0},
  /*
  ** .pp
  ** The default behavior of mutt is to use PGP on all auto-sign/encryption
  ** operations. To override and to use OpenSSL instead this must be \fIset\fP.
  ** However, this has no effect while replying, since mutt will automatically
  ** select the same application that was used to sign/encrypt the original
  ** message.  (Note that this variable can be overridden by unsetting $$crypt_autosmime.)
  ** (S/MIME only)
  */
  { "smime_keys",		DT_PATH, R_NONE, UL &SmimeKeys, 0 },
  /*
  ** .pp
  ** Since for S/MIME there is no pubring/secring as with PGP, mutt has to handle
  ** storage and retrieval of keys/certs by itself. This is very basic right now,
  ** and stores keys and certificates in two different directories, both
  ** named as the hash-value retrieved from OpenSSL. There is an index file
  ** which contains mailbox-address keyid pair, and which can be manually
  ** edited. This option points to the location of the private keys.
  ** (S/MIME only)
  */
  { "smime_pk7out_command", 	DT_STR, R_NONE, UL &SmimePk7outCommand, 0},
  /*
  ** .pp
  ** This command is used to extract PKCS7 structures of S/MIME signatures,
  ** in order to extract the public X509 certificate(s).
  ** .pp
  ** This is a format string, see the $$smime_decrypt_command command for
  ** possible \fCprintf(3)\fP-like sequences.
  ** (S/MIME only)
  */
  { "smime_sign_command", 	DT_STR, R_NONE, UL &SmimeSignCommand, 0},
  /*
  ** .pp
  ** This command is used to created S/MIME signatures of type
  ** \fCmultipart/signed\fP, which can be read by all mail clients.
  ** .pp
  ** This is a format string, see the $$smime_decrypt_command command for
  ** possible \fCprintf(3)\fP-like sequences.
  ** (S/MIME only)
  */
  { "smime_sign_opaque_command", 	DT_STR, R_NONE, UL &SmimeSignOpaqueCommand, 0},
  /*
  ** .pp
  ** This command is used to created S/MIME signatures of type
  ** \fCapplication/x-pkcs7-signature\fP, which can only be handled by mail
  ** clients supporting the S/MIME extension.
  ** .pp
  ** This is a format string, see the $$smime_decrypt_command command for
  ** possible \fCprintf(3)\fP-like sequences.
  ** (S/MIME only)
  */
  { "smime_timeout",		DT_NUM,	 R_NONE, UL &SmimeTimeout, 300 },
  /*
  ** .pp
  ** The number of seconds after which a cached passphrase will expire if
  ** not used.
  ** (S/MIME only)
  */
  { "smime_verify_command", 	DT_STR, R_NONE, UL &SmimeVerifyCommand, 0},
  /*
  ** .pp
  ** This command is used to verify S/MIME signatures of type \fCmultipart/signed\fP.
  ** .pp
  ** This is a format string, see the $$smime_decrypt_command command for
  ** possible \fCprintf(3)\fP-like sequences.
  ** (S/MIME only)
  */
  { "smime_verify_opaque_command", 	DT_STR, R_NONE, UL &SmimeVerifyOpaqueCommand, 0},
  /*
  ** .pp
  ** This command is used to verify S/MIME signatures of type
  ** \fCapplication/x-pkcs7-mime\fP.
  ** .pp
  ** This is a format string, see the $$smime_decrypt_command command for
  ** possible \fCprintf(3)\fP-like sequences.
  ** (S/MIME only)
  */
#ifdef USE_SMTP
# ifdef USE_SASL
  { "smtp_authenticators", DT_STR, R_NONE, UL &SmtpAuthenticators, UL 0 },
  /*
  ** .pp
  ** This is a colon-delimited list of authentication methods mutt may
  ** attempt to use to log in to an SMTP server, in the order mutt should
  ** try them.  Authentication methods are any SASL mechanism, e.g.
  ** ``digest-md5'', ``gssapi'' or ``cram-md5''.
  ** This option is case-insensitive. If it is ``unset''
  ** (the default) mutt will try all available methods, in order from
  ** most-secure to least-secure.
  ** .pp
  ** Example:
  ** .ts
  ** set smtp_authenticators="digest-md5:cram-md5"
  ** .te
  */
# endif /* USE_SASL */
  { "smtp_pass", 	DT_STR,  R_NONE, UL &SmtpPass, UL 0 },
  /*
  ** .pp
  ** Specifies the password for your SMTP account.  If \fIunset\fP, Mutt will
  ** prompt you for your password when you first send mail via SMTP.
  ** See $$smtp_url to configure mutt to send mail via SMTP.
  ** .pp
  ** \fBWarning\fP: you should only use this option when you are on a
  ** fairly secure machine, because the superuser can read your muttrc even
  ** if you are the only one who can read the file.
  */
  { "smtp_url",		DT_STR, R_NONE, UL &SmtpUrl, UL 0 },
  /*
  ** .pp
  ** Defines the SMTP smarthost where sent messages should relayed for
  ** delivery. This should take the form of an SMTP URL, e.g.:
  ** .ts
  ** smtp[s]://[user[:pass]@]host[:port]
  ** .te
  ** .pp
  ** where ``[...]'' denotes an optional part.
  ** Setting this variable overrides the value of the $$sendmail
  ** variable.
  */
#endif /* USE_SMTP */
  { "sort",		DT_SORT, R_INDEX|R_RESORT, UL &Sort, SORT_DATE },
  /*
  ** .pp
  ** Specifies how to sort messages in the ``index'' menu.  Valid values
  ** are:
  ** .il
  ** .dd date or date-sent
  ** .dd date-received
  ** .dd from
  ** .dd mailbox-order (unsorted)
  ** .dd score
  ** .dd size
  ** .dd spam
  ** .dd subject
  ** .dd threads
  ** .dd to
  ** .ie
  ** .pp
  ** You may optionally use the ``reverse-'' prefix to specify reverse sorting
  ** order (example: ``\fCset sort=reverse-date-sent\fP'').
  */
  { "sort_alias",	DT_SORT|DT_SORT_ALIAS,	R_NONE,	UL &SortAlias, SORT_ALIAS },
  /*
  ** .pp
  ** Specifies how the entries in the ``alias'' menu are sorted.  The
  ** following are legal values:
  ** .il
  ** .dd address (sort alphabetically by email address)
  ** .dd alias (sort alphabetically by alias name)
  ** .dd unsorted (leave in order specified in .muttrc)
  ** .ie
  */
  { "sort_aux",		DT_SORT|DT_SORT_AUX, R_INDEX|R_RESORT_BOTH, UL &SortAux, SORT_DATE },
  /*
  ** .pp
  ** When sorting by threads, this variable controls how threads are sorted
  ** in relation to other threads, and how the branches of the thread trees
  ** are sorted.  This can be set to any value that $$sort can, except
  ** ``threads'' (in that case, mutt will just use ``date-sent'').  You can also
  ** specify the ``last-'' prefix in addition to the ``reverse-'' prefix, but ``last-''
  ** must come after ``reverse-''.  The ``last-'' prefix causes messages to be
  ** sorted against its siblings by which has the last descendant, using
  ** the rest of $$sort_aux as an ordering.  For instance,
  ** .ts
  ** set sort_aux=last-date-received
  ** .te
  ** .pp
  ** would mean that if a new message is received in a
  ** thread, that thread becomes the last one displayed (or the first, if
  ** you have ``\fCset sort=reverse-threads\fP''.)
  ** .pp
  ** Note: For reversed $$sort
  ** order $$sort_aux is reversed again (which is not the right thing to do,
  ** but kept to not break any existing configuration setting).
  */
  { "sort_browser",	DT_SORT|DT_SORT_BROWSER, R_NONE, UL &BrowserSort, SORT_ALPHA },
  /*
  ** .pp
  ** Specifies how to sort entries in the file browser.  By default, the
  ** entries are sorted alphabetically.  Valid values:
  ** .il
  ** .dd alpha (alphabetically)
  ** .dd date
  ** .dd size
  ** .dd unsorted
  ** .ie
  ** .pp
  ** You may optionally use the ``reverse-'' prefix to specify reverse sorting
  ** order (example: ``\fCset sort_browser=reverse-date\fP'').
  */
  { "sort_re",		DT_BOOL, R_INDEX|R_RESORT|R_RESORT_INIT, OPTSORTRE, 1 },
  /*
  ** .pp
  ** This variable is only useful when sorting by threads with
  ** $$strict_threads \fIunset\fP.  In that case, it changes the heuristic
  ** mutt uses to thread messages by subject.  With $$sort_re \fIset\fP, mutt will
  ** only attach a message as the child of another message by subject if
  ** the subject of the child message starts with a substring matching the
  ** setting of $$reply_regexp.  With $$sort_re \fIunset\fP, mutt will attach
  ** the message whether or not this is the case, as long as the
  ** non-$$reply_regexp parts of both messages are identical.
  */
  { "spam_separator",   DT_STR, R_NONE, UL &SpamSep, UL "," },
  /*
  ** .pp
  ** This variable controls what happens when multiple spam headers
  ** are matched: if \fIunset\fP, each successive header will overwrite any
  ** previous matches value for the spam label. If \fIset\fP, each successive
  ** match will append to the previous, using this variable's value as a
  ** separator.
  */
  { "spoolfile",	DT_PATH, R_NONE, UL &Spoolfile, 0 },
  /*
  ** .pp
  ** If your spool mailbox is in a non-default place where Mutt cannot find
  ** it, you can specify its location with this variable.  Mutt will
  ** initially set this variable to the value of the environment
  ** variable \fC$$$MAIL\fP or \fC$$$MAILDIR\fP if either is defined.
  */
#if defined(USE_SSL)
#ifdef USE_SSL_GNUTLS
  { "ssl_ca_certificates_file", DT_PATH, R_NONE, UL &SslCACertFile, 0 },
  /*
  ** .pp
  ** This variable specifies a file containing trusted CA certificates.
  ** Any server certificate that is signed with one of these CA
  ** certificates is also automatically accepted.
  ** .pp
  ** Example:
  ** .ts
  ** set ssl_ca_certificates_file=/etc/ssl/certs/ca-certificates.crt
  ** .te
  */
#endif /* USE_SSL_GNUTLS */
  { "ssl_client_cert", DT_PATH, R_NONE, UL &SslClientCert, 0 },
  /*
  ** .pp
  ** The file containing a client certificate and its associated private
  ** key.
  */
  { "ssl_force_tls",		DT_BOOL, R_NONE, OPTSSLFORCETLS, 0 },
  /*
   ** .pp
   ** If this variable is \fIset\fP, Mutt will require that all connections
   ** to remote servers be encrypted. Furthermore it will attempt to
   ** negotiate TLS even if the server does not advertise the capability,
   ** since it would otherwise have to abort the connection anyway. This
   ** option supersedes $$ssl_starttls.
   */
# ifdef USE_SSL_GNUTLS
  { "ssl_min_dh_prime_bits", DT_NUM, R_NONE, UL &SslDHPrimeBits, 0 },
  /*
  ** .pp
  ** This variable specifies the minimum acceptable prime size (in bits)
  ** for use in any Diffie-Hellman key exchange. A value of 0 will use
  ** the default from the GNUTLS library.
  */
# endif /* USE_SSL_GNUTLS */
  { "ssl_starttls", DT_QUAD, R_NONE, OPT_SSLSTARTTLS, M_YES },
  /*
  ** .pp
  ** If \fIset\fP (the default), mutt will attempt to use \fCSTARTTLS\fP on servers
  ** advertising the capability. When \fIunset\fP, mutt will not attempt to
  ** use \fCSTARTTLS\fP regardless of the server's capabilities.
  */
# ifdef USE_SSL_OPENSSL
  { "ssl_use_sslv2", DT_BOOL, R_NONE, OPTSSLV2, 0 },
  /*
  ** .pp
  ** This variable specifies whether to attempt to use SSLv2 in the
  ** SSL authentication process.
  */
# endif /* defined USE_SSL_OPENSSL */
  { "ssl_use_sslv3", DT_BOOL, R_NONE, OPTSSLV3, 1 },
  /*
  ** .pp
  ** This variable specifies whether to attempt to use SSLv3 in the
  ** SSL authentication process.
  */
  { "ssl_use_tlsv1", DT_BOOL, R_NONE, OPTTLSV1, 1 },
  /*
  ** .pp
  ** This variable specifies whether to attempt to use TLSv1.0 in the
  ** SSL authentication process.
  */
  { "ssl_use_tlsv1_1", DT_BOOL, R_NONE, OPTTLSV1_1, 1 },
  /*
  ** .pp
  ** This variable specifies whether to attempt to use TLSv1.1 in the
  ** SSL authentication process.
  */
  { "ssl_use_tlsv1_2", DT_BOOL, R_NONE, OPTTLSV1_2, 1 },
  /*
  ** .pp
  ** This variable specifies whether to attempt to use TLSv1.2 in the
  ** SSL authentication process.
  */
#ifdef USE_SSL_OPENSSL
  { "ssl_usesystemcerts", DT_BOOL, R_NONE, OPTSSLSYSTEMCERTS, 1 },
  /*
  ** .pp
  ** If set to \fIyes\fP, mutt will use CA certificates in the
  ** system-wide certificate store when checking if a server certificate
  ** is signed by a trusted CA.
  */
#endif
  { "ssl_verify_dates", DT_BOOL, R_NONE, OPTSSLVERIFYDATES, 1 },
  /*
  ** .pp
  ** If \fIset\fP (the default), mutt will not automatically accept a server
  ** certificate that is either not yet valid or already expired. You should
  ** only unset this for particular known hosts, using the
  ** \fC$<account-hook>\fP function.
  */
  { "ssl_verify_host", DT_BOOL, R_NONE, OPTSSLVERIFYHOST, 1 },
  /*
  ** .pp
  ** If \fIset\fP (the default), mutt will not automatically accept a server
  ** certificate whose host name does not match the host used in your folder
  ** URL. You should only unset this for particular known hosts, using
  ** the \fC$<account-hook>\fP function.
  */
#endif /* defined(USE_SSL) */
  { "status_chars",	DT_STR,	 R_BOTH, UL &StChars, UL "-*%A" },
  /*
  ** .pp
  ** Controls the characters used by the ``%r'' indicator in
  ** $$status_format. The first character is used when the mailbox is
  ** unchanged. The second is used when the mailbox has been changed, and
  ** it needs to be resynchronized. The third is used if the mailbox is in
  ** read-only mode, or if the mailbox will not be written when exiting
  ** that mailbox (You can toggle whether to write changes to a mailbox
  ** with the \fC<toggle-write>\fP operation, bound by default to ``%''). The fourth
  ** is used to indicate that the current folder has been opened in attach-
  ** message mode (Certain operations like composing a new mail, replying,
  ** forwarding, etc. are not permitted in this mode).
  */
  { "status_format",	DT_STR,	 R_BOTH, UL &Status, UL "-%r-Mutt: %f [Msgs:%?M?%M/?%m%?n? New:%n?%?o? Old:%o?%?d? Del:%d?%?F? Flag:%F?%?t? Tag:%t?%?p? Post:%p?%?b? Inc:%b?%?l? %l?]---(%s/%S)-%>-(%P)---" },
  /*
  ** .pp
  ** Controls the format of the status line displayed in the ``index''
  ** menu.  This string is similar to $$index_format, but has its own
  ** set of \fCprintf(3)\fP-like sequences:
  ** .dl
  ** .dt %b  .dd number of mailboxes with new mail *
  ** .dt %d  .dd number of deleted messages *
  ** .dt %f  .dd the full pathname of the current mailbox
  ** .dt %F  .dd number of flagged messages *
  ** .dt %h  .dd local hostname
  ** .dt %l  .dd size (in bytes) of the current mailbox *
  ** .dt %L  .dd size (in bytes) of the messages shown
  **             (i.e., which match the current limit) *
  ** .dt %m  .dd the number of messages in the mailbox *
  ** .dt %M  .dd the number of messages shown (i.e., which match the current limit) *
  ** .dt %n  .dd number of new messages in the mailbox *
  ** .dt %o  .dd number of old unread messages *
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
  ** .dt %>X .dd right justify the rest of the string and pad with ``X''
  ** .dt %|X .dd pad to the end of the line with ``X''
  ** .dt %*X .dd soft-fill with character ``X'' as pad
  ** .de
  ** .pp
  ** For an explanation of ``soft-fill'', see the $$index_format documentation.
  ** .pp
  ** * = can be optionally printed if nonzero
  ** .pp
  ** Some of the above sequences can be used to optionally print a string
  ** if their value is nonzero.  For example, you may only want to see the
  ** number of flagged messages if such messages exist, since zero is not
  ** particularly meaningful.  To optionally print a string based upon one
  ** of the above sequences, the following construct is used:
  ** .pp
  **  \fC%?<sequence_char>?<optional_string>?\fP
  ** .pp
  ** where \fIsequence_char\fP is a character from the table above, and
  ** \fIoptional_string\fP is the string you would like printed if
  ** \fIsequence_char\fP is nonzero.  \fIoptional_string\fP \fBmay\fP contain
  ** other sequences as well as normal text, but you may \fBnot\fP nest
  ** optional strings.
  ** .pp
  ** Here is an example illustrating how to optionally print the number of
  ** new messages in a mailbox:
  ** .pp
  ** \fC%?n?%n new messages.?\fP
  ** .pp
  ** You can also switch between two strings using the following construct:
  ** .pp
  ** \fC%?<sequence_char>?<if_string>&<else_string>?\fP
  ** .pp
  ** If the value of \fIsequence_char\fP is non-zero, \fIif_string\fP will
  ** be expanded, otherwise \fIelse_string\fP will be expanded.
  ** .pp
  ** You can force the result of any \fCprintf(3)\fP-like sequence to be lowercase
  ** by prefixing the sequence character with an underscore (``_'') sign.
  ** For example, if you want to display the local hostname in lowercase,
  ** you would use: ``\fC%_h\fP''.
  ** .pp
  ** If you prefix the sequence character with a colon (``:'') character, mutt
  ** will replace any dots in the expansion by underscores. This might be helpful
  ** with IMAP folders that don't like dots in folder names.
  */
  { "status_on_top",	DT_BOOL, R_BOTH, OPTSTATUSONTOP, 0 },
  /*
  ** .pp
  ** Setting this variable causes the ``status bar'' to be displayed on
  ** the first line of the screen rather than near the bottom. If $$help
  ** is \fIset\fP, too it'll be placed at the bottom.
  */
  { "strict_threads",	DT_BOOL, R_RESORT|R_RESORT_INIT|R_INDEX, OPTSTRICTTHREADS, 0 },
  /*
  ** .pp
  ** If \fIset\fP, threading will only make use of the ``In-Reply-To'' and
  ** ``References:'' fields when you $$sort by message threads.  By
  ** default, messages with the same subject are grouped together in
  ** ``pseudo threads.''. This may not always be desirable, such as in a
  ** personal mailbox where you might have several unrelated messages with
  ** the subjects like ``hi'' which will get grouped together. See also
  ** $$sort_re for a less drastic way of controlling this
  ** behavior.
  */
  { "suspend",		DT_BOOL, R_NONE, OPTSUSPEND, 1 },
  /*
  ** .pp
  ** When \fIunset\fP, mutt won't stop when the user presses the terminal's
  ** \fIsusp\fP key, usually ``^Z''. This is useful if you run mutt
  ** inside an xterm using a command like ``\fCxterm -e mutt\fP''.
  */
  { "text_flowed", 	DT_BOOL, R_NONE, OPTTEXTFLOWED,  0 },
  /*
  ** .pp
  ** When \fIset\fP, mutt will generate ``format=flowed'' bodies with a content type
  ** of ``\fCtext/plain; format=flowed\fP''.
  ** This format is easier to handle for some mailing software, and generally
  ** just looks like ordinary text.  To actually make use of this format's
  ** features, you'll need support in your editor.
  ** .pp
  ** Note that $$indent_string is ignored when this option is \fIset\fP.
  */
  { "thorough_search",	DT_BOOL, R_NONE, OPTTHOROUGHSRC, 1 },
  /*
  ** .pp
  ** Affects the \fC~b\fP and \fC~h\fP search operations described in
  ** section ``$patterns''.  If \fIset\fP, the headers and body/attachments of
  ** messages to be searched are decoded before searching. If \fIunset\fP,
  ** messages are searched as they appear in the folder.
  ** .pp
  ** Users searching attachments or for non-ASCII characters should \fIset\fP
  ** this value because decoding also includes MIME parsing/decoding and possible
  ** character set conversions. Otherwise mutt will attempt to match against the
  ** raw message received (for example quoted-printable encoded or with encoded
  ** headers) which may lead to incorrect search results.
  */
  { "thread_received",	DT_BOOL, R_RESORT|R_RESORT_INIT|R_INDEX, OPTTHREADRECEIVED, 0 },
  /*
  ** .pp
  ** When \fIset\fP, mutt uses the date received rather than the date sent
  ** to thread messages by subject.
  */
  { "tilde",		DT_BOOL, R_PAGER, OPTTILDE, 0 },
  /*
  ** .pp
  ** When \fIset\fP, the internal-pager will pad blank lines to the bottom of the
  ** screen with a tilde (``~'').
  */
  { "time_inc",		DT_NUM,	 R_NONE, UL &TimeInc, 0 },
  /*
  ** .pp
  ** Along with $$read_inc, $$write_inc, and $$net_inc, this
  ** variable controls the frequency with which progress updates are
  ** displayed. It suppresses updates less than $$time_inc milliseconds
  ** apart. This can improve throughput on systems with slow terminals,
  ** or when running mutt on a remote system.
  ** .pp
  ** Also see the ``$tuning'' section of the manual for performance considerations.
  */
  { "timeout",		DT_NUM,	 R_NONE, UL &Timeout, 600 },
  /*
  ** .pp
  ** When Mutt is waiting for user input either idling in menus or
  ** in an interactive prompt, Mutt would block until input is
  ** present. Depending on the context, this would prevent certain
  ** operations from working, like checking for new mail or keeping
  ** an IMAP connection alive.
  ** .pp
  ** This variable controls how many seconds Mutt will at most wait
  ** until it aborts waiting for input, performs these operations and
  ** continues to wait for input.
  ** .pp
  ** A value of zero or less will cause Mutt to never time out.
  */
  { "tmpdir",		DT_PATH, R_NONE, UL &Tempdir, 0 },
  /*
  ** .pp
  ** This variable allows you to specify where Mutt will place its
  ** temporary files needed for displaying and composing messages.  If
  ** this variable is not set, the environment variable \fC$$$TMPDIR\fP is
  ** used.  If \fC$$$TMPDIR\fP is not set then ``\fC/tmp\fP'' is used.
  */
  { "to_chars",		DT_STR,	 R_BOTH, UL &Tochars, UL " +TCFL" },
  /*
  ** .pp
  ** Controls the character used to indicate mail addressed to you.  The
  ** first character is the one used when the mail is \fInot\fP addressed to your
  ** address.  The second is used when you are the only
  ** recipient of the message.  The third is when your address
  ** appears in the ``To:'' header field, but you are not the only recipient of
  ** the message.  The fourth character is used when your
  ** address is specified in the ``Cc:'' header field, but you are not the only
  ** recipient.  The fifth character is used to indicate mail that was sent
  ** by \fIyou\fP.  The sixth character is used to indicate when a mail
  ** was sent to a mailing-list you subscribe to.
  */
#ifdef USE_SOCKET
  { "tunnel",            DT_STR, R_NONE, UL &Tunnel, UL 0 },
  /*
  ** .pp
  ** Setting this variable will cause mutt to open a pipe to a command
  ** instead of a raw socket. You may be able to use this to set up
  ** preauthenticated connections to your IMAP/POP3/SMTP server. Example:
  ** .ts
  ** set tunnel="ssh -q mailhost.net /usr/local/libexec/imapd"
  ** .te
  ** .pp
  ** Note: For this example to work you must be able to log in to the remote
  ** machine without having to enter a password.
  ** .pp
  ** When set, Mutt uses the tunnel for all remote connections.
  ** Please see ``$account-hook'' in the manual for how to use different
  ** tunnel commands per connection.
  */
#endif
  { "uncollapse_jump", 	DT_BOOL, R_NONE, OPTUNCOLLAPSEJUMP, 0 },
  /*
  ** .pp
  ** When \fIset\fP, Mutt will jump to the next unread message, if any,
  ** when the current thread is \fIun\fPcollapsed.
  */
  { "use_8bitmime",	DT_BOOL, R_NONE, OPTUSE8BITMIME, 0 },
  /*
  ** .pp
  ** \fBWarning:\fP do not set this variable unless you are using a version
  ** of sendmail which supports the \fC-B8BITMIME\fP flag (such as sendmail
  ** 8.8.x) or you may not be able to send mail.
  ** .pp
  ** When \fIset\fP, Mutt will invoke $$sendmail with the \fC-B8BITMIME\fP
  ** flag when sending 8-bit messages to enable ESMTP negotiation.
  */
  { "use_domain",	DT_BOOL, R_NONE, OPTUSEDOMAIN, 1 },
  /*
  ** .pp
  ** When \fIset\fP, Mutt will qualify all local addresses (ones without the
  ** ``@host'' portion) with the value of $$hostname.  If \fIunset\fP, no
  ** addresses will be qualified.
  */
  { "use_envelope_from", 	DT_BOOL, R_NONE, OPTENVFROM, 0 },
  /*
   ** .pp
   ** When \fIset\fP, mutt will set the \fIenvelope\fP sender of the message.
   ** If $$envelope_from_address is \fIset\fP, it will be used as the sender
   ** address. If \fIunset\fP, mutt will attempt to derive the sender from the
   ** ``From:'' header.
   ** .pp
   ** Note that this information is passed to sendmail command using the
   ** \fC-f\fP command line switch. Therefore setting this option is not useful
   ** if the $$sendmail variable already contains \fC-f\fP or if the
   ** executable pointed to by $$sendmail doesn't support the \fC-f\fP switch.
   */
  { "envelope_from",	DT_SYN,  R_NONE, UL "use_envelope_from", 0 },
  /*
  */
  { "use_from",		DT_BOOL, R_NONE, OPTUSEFROM, 1 },
  /*
  ** .pp
  ** When \fIset\fP, Mutt will generate the ``From:'' header field when
  ** sending messages.  If \fIunset\fP, no ``From:'' header field will be
  ** generated unless the user explicitly sets one using the ``$my_hdr''
  ** command.
  */
#ifdef HAVE_LIBIDN
  { "use_idn",		DT_BOOL, R_BOTH, OPTUSEIDN, 1},
  /*
  ** .pp
  ** When \fIset\fP, Mutt will show you international domain names decoded.
  ** Note: You can use IDNs for addresses even if this is \fIunset\fP.
  ** This variable only affects decoding.
  */
#endif /* HAVE_LIBIDN */
#ifdef HAVE_GETADDRINFO
  { "use_ipv6",		DT_BOOL, R_NONE, OPTUSEIPV6, 1},
  /*
  ** .pp
  ** When \fIset\fP, Mutt will look for IPv6 addresses of hosts it tries to
  ** contact.  If this option is \fIunset\fP, Mutt will restrict itself to IPv4 addresses.
  ** Normally, the default should work.
  */
#endif /* HAVE_GETADDRINFO */
  { "user_agent",	DT_BOOL, R_NONE, OPTXMAILER, 1},
  /*
  ** .pp
  ** When \fIset\fP, mutt will add a ``User-Agent:'' header to outgoing
  ** messages, indicating which version of mutt was used for composing
  ** them.
  */
  { "visual",		DT_PATH, R_NONE, UL &Visual, 0 },
  /*
  ** .pp
  ** Specifies the visual editor to invoke when the ``\fC~v\fP'' command is
  ** given in the built-in editor.
  */
  { "wait_key",		DT_BOOL, R_NONE, OPTWAITKEY, 1 },
  /*
  ** .pp
  ** Controls whether Mutt will ask you to press a key after an external command
  ** has been invoked by these functions: \fC<shell-escape>\fP,
  ** \fC<pipe-message>\fP, \fC<pipe-entry>\fP, \fC<print-message>\fP,
  ** and \fC<print-entry>\fP commands.
  ** .pp
  ** It is also used when viewing attachments with ``$auto_view'', provided
  ** that the corresponding mailcap entry has a \fIneedsterminal\fP flag,
  ** and the external program is interactive.
  ** .pp
  ** When \fIset\fP, Mutt will always ask for a key. When \fIunset\fP, Mutt will wait
  ** for a key only if the external command returned a non-zero status.
  */
  { "weed",		DT_BOOL, R_NONE, OPTWEED, 1 },
  /*
  ** .pp
  ** When \fIset\fP, mutt will weed headers when displaying, forwarding,
  ** printing, or replying to messages.
  */
  { "wrap",             DT_NUM,  R_PAGER, UL &Wrap, 0 },
  /*
  ** .pp
  ** When set to a positive value, mutt will wrap text at $$wrap characters.
  ** When set to a negative value, mutt will wrap text so that there are $$wrap
  ** characters of empty space on the right side of the terminal. Setting it
  ** to zero makes mutt wrap at the terminal width.
  ** .pp
  ** Also see $$reflow_wrap.
  */
  { "wrap_headers",     DT_NUM,  R_PAGER, UL &WrapHeaders, 78 },
  /*
  ** .pp
  ** This option specifies the number of characters to use for wrapping
  ** an outgoing message's headers. Allowed values are between 78 and 998
  ** inclusive.
  ** .pp
  ** \fBNote:\fP This option usually shouldn't be changed. RFC5233
  ** recommends a line length of 78 (the default), so \fBplease only change
  ** this setting when you know what you're doing\fP.
  */
  { "wrap_search",	DT_BOOL, R_NONE, OPTWRAPSEARCH, 1 },
  /*
  ** .pp
  ** Controls whether searches wrap around the end.
  ** .pp
  ** When \fIset\fP, searches will wrap around the first (or last) item. When
  ** \fIunset\fP, incremental searches will not wrap.
  */
  { "wrapmargin",	DT_NUM,	 R_PAGER, UL &Wrap, 0 },
  /*
  ** .pp
  ** (DEPRECATED) Equivalent to setting $$wrap with a negative value.
  */
  { "write_bcc",	DT_BOOL, R_NONE, OPTWRITEBCC, 1},
  /*
  ** .pp
  ** Controls whether mutt writes out the ``Bcc:'' header when preparing
  ** messages to be sent.  Exim users may wish to unset this. If mutt
  ** is set to deliver directly via SMTP (see $$smtp_url), this
  ** option does nothing: mutt will never write out the ``Bcc:'' header
  ** in this case.
  */
  { "write_inc",	DT_NUM,	 R_NONE, UL &WriteInc, 10 },
  /*
  ** .pp
  ** When writing a mailbox, a message will be printed every
  ** $$write_inc messages to indicate progress.  If set to 0, only a
  ** single message will be displayed before writing a mailbox.
  ** .pp
  ** Also see the $$read_inc, $$net_inc and $$time_inc variables and the
  ** ``$tuning'' section of the manual for performance considerations.
  */
  /*--*/
  { NULL, 0, 0, 0, 0 }
};

const struct mapping_t SortMethods[] = {
  { "date",		SORT_DATE },
  { "date-sent",	SORT_DATE },
  { "date-received",	SORT_RECEIVED },
