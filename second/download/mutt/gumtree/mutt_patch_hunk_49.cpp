   /*
   ** .pp
   ** This variable controls the number of lines of context that are given
   ** when displaying the next or previous page in the internal pager.  By
   ** default, Mutt will display the line after the last one on the screen
   ** at the top of the next page (0 lines of context).
+  ** .pp
+  ** This variable also specifies the amount of context given for search
+  ** results. If positive, this many lines will be given before a match,
+  ** if 0, the match will be top-aligned.
   */
-  { "pager_format",	DT_STR,	 R_PAGER, UL &PagerFmt, UL "-%Z- %C/%m: %-20.20n   %s" },
+  { "pager_format",	DT_STR,	 R_PAGER, UL &PagerFmt, UL "-%Z- %C/%m: %-20.20n   %s%*  -- (%P)" },
   /*
   ** .pp
   ** This variable controls the format of the one-line message ``status''
   ** displayed before each message in either the internal or an external
-  ** pager.  The valid sequences are listed in the ``$$index_format''
+  ** pager.  The valid sequences are listed in the $$index_format
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
-  ** for the status bar from the index, so a \fIpager_index_lines\fP of 6
+  ** for the status bar from the index, so a setting of 6
   ** will only show 5 lines of the actual index.  A value of 0 results in
   ** no index being shown.  If the number of messages in the current folder
-  ** is less than \fIpager_index_lines\fP, then the index will only use as
+  ** is less than $$pager_index_lines, then the index will only use as
   ** many lines as it needs.
   */
   { "pager_stop",	DT_BOOL, R_NONE, OPTPAGERSTOP, 0 },
   /*
   ** .pp
-  ** When set, the internal-pager will \fBnot\fP move to the next message
-  ** when you are at the end of a message and invoke the \fInext-page\fP
+  ** When \fIset\fP, the internal-pager will \fBnot\fP move to the next message
+  ** when you are at the end of a message and invoke the \fC<next-page>\fP
   ** function.
   */
-  
-
-#ifdef HAVE_PGP
-
-  { "pgp_autosign",	DT_BOOL, R_NONE, OPTPGPAUTOSIGN, 0 },
+  { "pgp_auto_decode", DT_BOOL, R_NONE, OPTPGPAUTODEC, 0 },
   /*
   ** .pp
-  ** Setting this variable will cause Mutt to always attempt to PGP/MIME
-  ** sign outgoing messages.  This can be overridden by use of the \fIpgp-
-  ** menu\fP, when signing is not required or encryption is requested as
-  ** well.
+  ** If \fIset\fP, mutt will automatically attempt to decrypt traditional PGP
+  ** messages whenever the user performs an operation which ordinarily would
+  ** result in the contents of the message being operated on.  For example,
+  ** if the user displays a pgp-traditional message which has not been manually
+  ** checked with the \fC$<check-traditional-pgp>\fP function, mutt will automatically
+  ** check the message for traditional pgp.
   */
-  { "pgp_autoencrypt",	DT_BOOL, R_NONE, OPTPGPAUTOENCRYPT, 0 },
+  { "pgp_create_traditional",	DT_SYN, R_NONE, UL "pgp_autoinline", 0 },
+  { "pgp_autoinline",		DT_BOOL, R_NONE, OPTPGPAUTOINLINE, 0 },
   /*
   ** .pp
-  ** Setting this variable will cause Mutt to always attempt to PGP/MIME
-  ** encrypt outgoing messages.  This is probably only useful in connection
-  ** to the \fIsend-hook\fP command.  It can be overridden by use of the
-  ** \fIpgp-menu\fP, when encryption is not required or signing is
-  ** requested as well.
-  */
-  { "pgp_ignore_subkeys", DT_BOOL, R_NONE, OPTPGPIGNORESUB, 1},
-  /*
+  ** This option controls whether Mutt generates old-style inline
+  ** (traditional) PGP encrypted or signed messages under certain
+  ** circumstances.  This can be overridden by use of the pgp menu,
+  ** when inline is not required.
   ** .pp
-  ** Setting this variable will cause Mutt to ignore OpenPGP subkeys. Instead,
-  ** the principal key will inherit the subkeys' capabilities.  Unset this
-  ** if you want to play interesting key selection games.
+  ** Note that Mutt might automatically use PGP/MIME for messages
+  ** which consist of more than a single MIME part.  Mutt can be
+  ** configured to ask before sending PGP/MIME messages when inline
+  ** (traditional) would not work.
+  ** .pp
+  ** Also see the $$pgp_mime_auto variable.
+  ** .pp
+  ** Also note that using the old-style PGP message format is \fBstrongly\fP
+  ** \fBdeprecated\fP.
+  ** (PGP only)
+  */
+  { "pgp_check_exit",	DT_BOOL, R_NONE, OPTPGPCHECKEXIT, 1 },
+  /*
+  ** .pp
+  ** If \fIset\fP, mutt will check the exit code of the PGP subprocess when
+  ** signing or encrypting.  A non-zero exit code means that the
+  ** subprocess failed.
+  ** (PGP only)
+  */
+  { "pgp_clearsign_command",	DT_STR,	R_NONE, UL &PgpClearSignCommand, 0 },
+  /*
+  ** .pp
+  ** This format is used to create an old-style ``clearsigned'' PGP
+  ** message.  Note that the use of this format is \fBstrongly\fP
+  ** \fBdeprecated\fP.
+  ** .pp
+  ** This is a format string, see the $$pgp_decode_command command for
+  ** possible \fCprintf(3)\fP-like sequences.
+  ** (PGP only)
+  */
+  { "pgp_decode_command",       DT_STR, R_NONE, UL &PgpDecodeCommand, 0},
+  /*
+  ** .pp
+  ** This format strings specifies a command which is used to decode
+  ** application/pgp attachments.
+  ** .pp
+  ** The PGP command formats have their own set of \fCprintf(3)\fP-like sequences:
+  ** .dl
+  ** .dt %p .dd Expands to PGPPASSFD=0 when a pass phrase is needed, to an empty
+  **            string otherwise. Note: This may be used with a %? construct.
+  ** .dt %f .dd Expands to the name of a file containing a message.
+  ** .dt %s .dd Expands to the name of a file containing the signature part
+  ** .          of a \fCmultipart/signed\fP attachment when verifying it.
+  ** .dt %a .dd The value of $$pgp_sign_as.
+  ** .dt %r .dd One or more key IDs.
+  ** .de
+  ** .pp
+  ** For examples on how to configure these formats for the various versions
+  ** of PGP which are floating around, see the pgp and gpg sample configuration files in
+  ** the \fCsamples/\fP subdirectory which has been installed on your system
+  ** alongside the documentation.
+  ** (PGP only)
+  */
+  { "pgp_decrypt_command", 	DT_STR, R_NONE, UL &PgpDecryptCommand, 0},
+  /*
+  ** .pp
+  ** This command is used to decrypt a PGP encrypted message.
+  ** .pp
+  ** This is a format string, see the $$pgp_decode_command command for
+  ** possible \fCprintf(3)\fP-like sequences.
+  ** (PGP only)
+  */
+  { "pgp_encrypt_only_command", DT_STR, R_NONE, UL &PgpEncryptOnlyCommand, 0},
+  /*
+  ** .pp
+  ** This command is used to encrypt a body part without signing it.
+  ** .pp
+  ** This is a format string, see the $$pgp_decode_command command for
+  ** possible \fCprintf(3)\fP-like sequences.
+  ** (PGP only)
+  */
+  { "pgp_encrypt_sign_command",	DT_STR, R_NONE, UL &PgpEncryptSignCommand, 0},
+  /*
+  ** .pp
+  ** This command is used to both sign and encrypt a body part.
+  ** .pp
+  ** This is a format string, see the $$pgp_decode_command command for
+  ** possible \fCprintf(3)\fP-like sequences.
+  ** (PGP only)
   */
   { "pgp_entry_format", DT_STR,  R_NONE, UL &PgpEntryFormat, UL "%4n %t%f %4l/0x%k %-4a %2c %u" },
   /*
   ** .pp
   ** This variable allows you to customize the PGP key selection menu to
-  ** your personal taste. This string is similar to ``$$index_format'', but
-  ** has its own set of printf()-like sequences:
-  ** .pp
+  ** your personal taste. This string is similar to $$index_format, but
+  ** has its own set of \fCprintf(3)\fP-like sequences:
   ** .dl
   ** .dt %n     .dd number
   ** .dt %k     .dd key id
   ** .dt %u     .dd user id
   ** .dt %a     .dd algorithm
   ** .dt %l     .dd key length
   ** .dt %f     .dd flags
   ** .dt %c     .dd capabilities
   ** .dt %t     .dd trust/validity of the key-uid association
-  ** .dt %[<s>] .dd date of the key where <s> is an strftime(3) expression
+  ** .dt %[<s>] .dd date of the key where <s> is an \fCstrftime(3)\fP expression
   ** .de
+  ** .pp
+  ** (PGP only)
+  */
+  { "pgp_export_command", 	DT_STR, R_NONE, UL &PgpExportCommand, 0},
+  /*
+  ** .pp
+  ** This command is used to export a public key from the user's
+  ** key ring.
+  ** .pp
+  ** This is a format string, see the $$pgp_decode_command command for
+  ** possible \fCprintf(3)\fP-like sequences.
+  ** (PGP only)
+  */
+  { "pgp_getkeys_command",	DT_STR, R_NONE, UL &PgpGetkeysCommand, 0},
+  /*
+  ** .pp
+  ** This command is invoked whenever Mutt needs to fetch the public key associated with
+  ** an email address.  Of the sequences supported by $$pgp_decode_command, %r is
+  ** the only \fCprintf(3)\fP-like sequence used with this format.  Note that
+  ** in this case, %r expands to the email address, not the public key ID (the key ID is
+  ** unknown, which is why Mutt is invoking this command).
+  ** (PGP only)
   */
   { "pgp_good_sign",	DT_RX,  R_NONE, UL &PgpGoodSign, 0 },
   /*
   ** .pp
   ** If you assign a text to this variable, then a PGP signature is only
   ** considered verified if the output from $$pgp_verify_command contains
   ** the text. Use this variable if the exit code from the command is 0
   ** even for bad signatures.
-  */ 
-  { "pgp_long_ids",	DT_BOOL, R_NONE, OPTPGPLONGIDS, 0 },
+  ** (PGP only)
+  */
+  { "pgp_ignore_subkeys", DT_BOOL, R_NONE, OPTPGPIGNORESUB, 1},
   /*
   ** .pp
-  ** If set, use 64 bit PGP key IDs. Unset uses the normal 32 bit Key IDs.
+  ** Setting this variable will cause Mutt to ignore OpenPGP subkeys. Instead,
+  ** the principal key will inherit the subkeys' capabilities.  \fIUnset\fP this
+  ** if you want to play interesting key selection games.
+  ** (PGP only)
   */
-  { "pgp_replyencrypt",	DT_BOOL, R_NONE, OPTPGPREPLYENCRYPT, 1 },
+  { "pgp_import_command",	DT_STR, R_NONE, UL &PgpImportCommand, 0},
   /*
   ** .pp
-  ** If set, automatically PGP encrypt replies to messages which are
-  ** encrypted.
+  ** This command is used to import a key from a message into
+  ** the user's public key ring.
+  ** .pp
+  ** This is a format string, see the $$pgp_decode_command command for
+  ** possible \fCprintf(3)\fP-like sequences.
+  ** (PGP only)
   */
-  { "pgp_replysign",	DT_BOOL, R_NONE, OPTPGPREPLYSIGN, 0 },
+  { "pgp_list_pubring_command", DT_STR, R_NONE, UL &PgpListPubringCommand, 0},
   /*
   ** .pp
-  ** If set, automatically PGP sign replies to messages which are signed.
+  ** This command is used to list the public key ring's contents.  The
+  ** output format must be analogous to the one used by
+  ** .ts
+  ** gpg --list-keys --with-colons.
+  ** .te
   ** .pp
-  ** \fBNote:\fP this does not work on messages that are encrypted
-  ** \fBand\fP signed!
+  ** This format is also generated by the \fCpgpring\fP utility which comes
+  ** with mutt.
+  ** .pp
+  ** This is a format string, see the $$pgp_decode_command command for
+  ** possible \fCprintf(3)\fP-like sequences.
+  ** (PGP only)
+  */
+  { "pgp_list_secring_command",	DT_STR, R_NONE, UL &PgpListSecringCommand, 0},
+  /*
+  ** .pp
+  ** This command is used to list the secret key ring's contents.  The
+  ** output format must be analogous to the one used by:
+  ** .ts
+  ** gpg --list-keys --with-colons.
+  ** .te
+  ** .pp
+  ** This format is also generated by the \fCpgpring\fP utility which comes
+  ** with mutt.
+  ** .pp
+  ** This is a format string, see the $$pgp_decode_command command for
+  ** possible \fCprintf(3)\fP-like sequences.
+  ** (PGP only)
+  */
+  { "pgp_long_ids",	DT_BOOL, R_NONE, OPTPGPLONGIDS, 0 },
+  /*
+  ** .pp
+  ** If \fIset\fP, use 64 bit PGP key IDs, if \fIunset\fP use the normal 32 bit key IDs.
+  ** (PGP only)
+  */
+  { "pgp_mime_auto", DT_QUAD, R_NONE, OPT_PGPMIMEAUTO, M_ASKYES },
+  /*
+  ** .pp
+  ** This option controls whether Mutt will prompt you for
+  ** automatically sending a (signed/encrypted) message using
+  ** PGP/MIME when inline (traditional) fails (for any reason).
+  ** .pp
+  ** Also note that using the old-style PGP message format is \fBstrongly\fP
+  ** \fBdeprecated\fP.
+  ** (PGP only)
   */
-  { "pgp_replysignencrypted", DT_BOOL, R_NONE, OPTPGPREPLYSIGNENCRYPTED, 0 },
+  { "pgp_auto_traditional",	DT_SYN, R_NONE, UL "pgp_replyinline", 0 },
+  { "pgp_replyinline",		DT_BOOL, R_NONE, OPTPGPREPLYINLINE, 0 },
   /*
   ** .pp
-  ** If set, automatically PGP sign replies to messages which are
-  ** encrypted. This makes sense in combination with
-  ** ``$$pgp_replyencrypt'', because it allows you to sign all messages
-  ** which are automatically encrypted.  This works around the problem
-  ** noted in ``$$pgp_replysign'', that mutt is not able to find out
-  ** whether an encrypted message is also signed.
+  ** Setting this variable will cause Mutt to always attempt to
+  ** create an inline (traditional) message when replying to a
+  ** message which is PGP encrypted/signed inline.  This can be
+  ** overridden by use of the pgp menu, when inline is not
+  ** required.  This option does not automatically detect if the
+  ** (replied-to) message is inline; instead it relies on Mutt
+  ** internals for previously checked/flagged messages.
+  ** .pp
+  ** Note that Mutt might automatically use PGP/MIME for messages
+  ** which consist of more than a single MIME part.  Mutt can be
+  ** configured to ask before sending PGP/MIME messages when inline
+  ** (traditional) would not work.
+  ** .pp
+  ** Also see the $$pgp_mime_auto variable.
+  ** .pp
+  ** Also note that using the old-style PGP message format is \fBstrongly\fP
+  ** \fBdeprecated\fP.
+  ** (PGP only)
+  **
   */
   { "pgp_retainable_sigs", DT_BOOL, R_NONE, OPTPGPRETAINABLESIG, 0 },
   /*
   ** .pp
-  ** If set, signed and encrypted messages will consist of nested
-  ** multipart/signed and multipart/encrypted body parts.
+  ** If \fIset\fP, signed and encrypted messages will consist of nested
+  ** \fCmultipart/signed\fP and \fCmultipart/encrypted\fP body parts.
   ** .pp
   ** This is useful for applications like encrypted and signed mailing
-  ** lists, where the outer layer (multipart/encrypted) can be easily
-  ** removed, while the inner multipart/signed part is retained.
+  ** lists, where the outer layer (\fCmultipart/encrypted\fP) can be easily
+  ** removed, while the inner \fCmultipart/signed\fP part is retained.
+  ** (PGP only)
   */
   { "pgp_show_unusable", DT_BOOL, R_NONE, OPTPGPSHOWUNUSABLE, 1 },
   /*
   ** .pp
-  ** If set, mutt will display non-usable keys on the PGP key selection
+  ** If \fIset\fP, mutt will display non-usable keys on the PGP key selection
   ** menu.  This includes keys which have been revoked, have expired, or
   ** have been marked as ``disabled'' by the user.
+  ** (PGP only)
   */
   { "pgp_sign_as",	DT_STR,	 R_NONE, UL &PgpSignAs, 0 },
   /*
   ** .pp
   ** If you have more than one key pair, this option allows you to specify
   ** which of your private keys to use.  It is recommended that you use the
-  ** keyid form to specify your key (e.g., ``0x00112233'').
+  ** keyid form to specify your key (e.g. \fC0x00112233\fP).
+  ** (PGP only)
   */
-  { "pgp_strict_enc",	DT_BOOL, R_NONE, OPTPGPSTRICTENC, 1 },
-  /*
-  ** .pp
-  ** If set, Mutt will automatically encode PGP/MIME signed messages as
-  ** \fIquoted-printable\fP.  Please note that unsetting this variable may
-  ** lead to problems with non-verifyable PGP signatures, so only change
-  ** this if you know what you are doing.
-  */
-  { "pgp_timeout",	DT_NUM,	 R_NONE, UL &PgpTimeout, 300 },
+  { "pgp_sign_command",		DT_STR, R_NONE, UL &PgpSignCommand, 0},
   /*
   ** .pp
-  ** The number of seconds after which a cached passphrase will expire if
-  ** not used.
-  */
-  { "pgp_verify_sig",	DT_QUAD, R_NONE, OPT_VERIFYSIG, M_YES },
-  /*
+  ** This command is used to create the detached PGP signature for a
+  ** \fCmultipart/signed\fP PGP/MIME body part.
   ** .pp
-  ** If ``yes'', always attempt to verify PGP/MIME signatures.  If ``ask-yes''
-  ** or ``ask-no'',
-  ** ask whether or not to verify the signature.  If ``no'', never attempt
-  ** to verify PGP/MIME signatures.
+  ** This is a format string, see the $$pgp_decode_command command for
+  ** possible \fCprintf(3)\fP-like sequences.
+  ** (PGP only)
   */
   { "pgp_sort_keys",	DT_SORT|DT_SORT_KEYS, R_NONE, UL &PgpSortKeys, SORT_ADDRESS },
   /*
   ** .pp
-  ** Specifies how the entries in the `pgp keys' menu are sorted. The
+  ** Specifies how the entries in the pgp menu are sorted. The
   ** following are legal values:
-  ** .pp
   ** .dl
   ** .dt address .dd sort alphabetically by user id
   ** .dt keyid   .dd sort alphabetically by key id
   ** .dt date    .dd sort by key creation date
   ** .dt trust   .dd sort by the trust of the key
   ** .de
   ** .pp
   ** If you prefer reverse order of the above values, prefix it with
-  ** `reverse-'.
+  ** ``reverse-''.
+  ** (PGP only)
   */
-  { "pgp_create_traditional", DT_QUAD, R_NONE, OPT_PGPTRADITIONAL, M_NO },
+  { "pgp_strict_enc",	DT_BOOL, R_NONE, OPTPGPSTRICTENC, 1 },
   /*
   ** .pp
-  ** This option controls whether Mutt generates old-style PGP encrypted
-  ** or signed messages under certain circumstances.
-  ** .pp
-  ** Note that PGP/MIME will be used automatically for messages which have
-  ** a character set different from us-ascii, or which consist of more than
-  ** a single MIME part.
-  ** .pp
-  ** Also note that using the old-style PGP message format is \fBstrongly\fP
-  ** \fBdeprecated\fP.
+  ** If \fIset\fP, Mutt will automatically encode PGP/MIME signed messages as
+  ** quoted-printable.  Please note that unsetting this variable may
+  ** lead to problems with non-verifyable PGP signatures, so only change
+  ** this if you know what you are doing.
+  ** (PGP only)
   */
-
-  /* XXX Default values! */
-  
-  { "pgp_decode_command", 	DT_STR, R_NONE, UL &PgpDecodeCommand, 0},
+  { "pgp_timeout",	DT_NUM,	 R_NONE, UL &PgpTimeout, 300 },
   /*
   ** .pp
-  ** This format strings specifies a command which is used to decode 
-  ** application/pgp attachments.
-  ** .pp
-  ** The PGP command formats have their own set of printf-like sequences:
-  ** .pp
-  ** .dl
-  ** .dt %p .dd Expands to PGPPASSFD=0 when a pass phrase is needed, to an empty
-  **            string otherwise. Note: This may be used with a %? construct.
-  ** .dt %f .dd Expands to the name of a file containing a message.
-  ** .dt %s .dd Expands to the name of a file containing the signature part
-  ** .          of a multipart/signed attachment when verifying it.
-  ** .dt %a .dd The value of $$pgp_sign_as.
-  ** .dt %r .dd One or more key IDs.
-  ** .de
-  ** .pp
-  ** For examples on how to configure these formats for the various versions
-  ** of PGP which are floating around, see the pgp*.rc and gpg.rc files in
-  ** the samples/ subdirectory which has been installed on your system
-  ** alongside the documentation.
+  ** The number of seconds after which a cached passphrase will expire if
+  ** not used.
+  ** (PGP only)
   */
-  { "pgp_getkeys_command",	DT_STR, R_NONE, UL &PgpGetkeysCommand, 0},
+  { "pgp_use_gpg_agent", DT_BOOL, R_NONE, OPTUSEGPGAGENT, 0},
   /*
   ** .pp
-  ** This command is invoked whenever mutt will need public key information.
-  ** %r is the only printf-like sequence used with this format.
+  ** If \fIset\fP, mutt will use a possibly-running \fCgpg-agent(1)\fP process.
+  ** (PGP only)
   */
   { "pgp_verify_command", 	DT_STR, R_NONE, UL &PgpVerifyCommand, 0},
   /*
   ** .pp
-  ** This command is used to verify PGP/MIME signatures.
-  */
-  { "pgp_decrypt_command", 	DT_STR, R_NONE, UL &PgpDecryptCommand, 0},
-  /*
+  ** This command is used to verify PGP signatures.
   ** .pp
-  ** This command is used to decrypt a PGP/MIME encrypted message.
-  */  
-  { "pgp_clearsign_command",	DT_STR,	R_NONE, UL &PgpClearSignCommand, 0 },
-  /*
-  ** .pp
-  ** This format is used to create a "clearsigned" old-style PGP attachment.
-  ** Note that the use of this format is \fBstrongly\fP \fBdeprecated\fP.
+  ** This is a format string, see the $$pgp_decode_command command for
+  ** possible \fCprintf(3)\fP-like sequences.
+  ** (PGP only)
   */
-  { "pgp_sign_command",		DT_STR, R_NONE, UL &PgpSignCommand, 0},
-  /*
-  ** .pp
-  ** This command is used to create the detached PGP signature for a 
-  ** multipart/signed PGP/MIME body part.
-  */  
-  { "pgp_encrypt_sign_command",	DT_STR, R_NONE, UL &PgpEncryptSignCommand, 0},
-  /*
-  ** .pp
-  ** This command is used to combinedly sign/encrypt a body part.
-  */  
-  { "pgp_encrypt_only_command", DT_STR, R_NONE, UL &PgpEncryptOnlyCommand, 0},
-  /*
-  ** .pp
-  ** This command is used to encrypt a body part without signing it.
-  */  
-  { "pgp_import_command",	DT_STR, R_NONE, UL &PgpImportCommand, 0},
-  /*
-  ** .pp
-  ** This command is used to import a key from a message into 
-  ** the user's public key ring.
-  */  
-  { "pgp_export_command", 	DT_STR, R_NONE, UL &PgpExportCommand, 0},
-  /*
-  ** .pp
-  ** This command is used to export a public key from the user's
-  ** key ring.
-  */  
   { "pgp_verify_key_command",	DT_STR, R_NONE, UL &PgpVerifyKeyCommand, 0},
   /*
   ** .pp
   ** This command is used to verify key information from the key selection
   ** menu.
-  */  
-  { "pgp_list_secring_command",	DT_STR, R_NONE, UL &PgpListSecringCommand, 0},
-  /*
-  ** .pp
-  ** This command is used to list the secret key ring's contents.  The
-  ** output format must be analogous to the one used by 
-  ** gpg --list-keys --with-colons.
-  ** .pp
-  ** This format is also generated by the pgpring utility which comes 
-  ** with mutt.
-  */  
-  { "pgp_list_pubring_command", DT_STR, R_NONE, UL &PgpListPubringCommand, 0},
-  /*
-  ** .pp
-  ** This command is used to list the public key ring's contents.  The
-  ** output format must be analogous to the one used by 
-  ** gpg --list-keys --with-colons.
-  ** .pp
-  ** This format is also generated by the pgpring utility which comes 
-  ** with mutt.
-  */  
-  { "forward_decrypt",	DT_BOOL, R_NONE, OPTFORWDECRYPT, 1 },
-  /*
-  ** .pp
-  ** Controls the handling of encrypted messages when forwarding a message.
-  ** When set, the outer layer of encryption is stripped off.  This
-  ** variable is only used if ``$$mime_forward'' is \fIset\fP and
-  ** ``$$mime_forward_decode'' is \fIunset\fP.
-  */
-  { "forw_decrypt",	DT_SYN,  R_NONE, UL "forward_decrypt", 0 },
-  /*
-  */
-#endif /* HAVE_PGP */
-  
-#if defined(USE_SSL)||defined(USE_NSS)
-# ifndef USE_NSS  
-  { "ssl_starttls", DT_QUAD, R_NONE, OPT_SSLSTARTTLS, M_YES },
-  /*
-  ** .pp
-  ** If set (the default), mutt will attempt to use STARTTLS on servers
-  ** advertising the capability. When unset, mutt will not attempt to
-  ** use STARTTLS regardless of the server's capabilities.
-  */
-# endif  
-  { "certificate_file",	DT_PATH, R_NONE, UL &SslCertFile, 0 },
-  /*
-  ** .pp
-  ** This variable specifies the file where the certificates you trust
-  ** are saved. When an unknown certificate is encountered, you are asked
-  ** if you accept it or not. If you accept it, the certificate can also 
-  ** be saved in this file and further connections are automatically 
-  ** accepted.
-  ** .pp
-  ** You can also manually add CA certificates in this file. Any server
-  ** certificate that is signed with one of these CA certificates are 
-  ** also automatically accepted.
-  ** .pp
-  ** Example: set certificate_file=~/.mutt/certificates
-  */
-  { "ssl_usesystemcerts", DT_BOOL, R_NONE, OPTSSLSYSTEMCERTS, 1 },
-  /*
   ** .pp
-  ** If set to \fIyes\fP, mutt will use CA certificates in the
-  ** system-wide certificate store when checking if server certificate 
-  ** is signed by a trusted CA.
+  ** This is a format string, see the $$pgp_decode_command command for
+  ** possible \fCprintf(3)\fP-like sequences.
+  ** (PGP only)
   */
-  { "entropy_file",	DT_PATH, R_NONE, UL &SslEntropyFile, 0 },
-  /*
-  ** .pp
-  ** The file which includes random data that is used to initalize SSL
-  ** library functions.
-   */
-  { "ssl_use_sslv2", DT_BOOL, R_NONE, OPTSSLV2, 1 },
-  /*
-  ** .pp
-  ** This variables specifies whether to attempt to use SSLv2 in the
-  ** SSL authentication process.
-  */
-  { "ssl_use_sslv3", DT_BOOL, R_NONE, OPTSSLV3, 1 },
+  { "pipe_decode",	DT_BOOL, R_NONE, OPTPIPEDECODE, 0 },
   /*
   ** .pp
-  ** This variables specifies whether to attempt to use SSLv3 in the
-  ** SSL authentication process.
+  ** Used in connection with the \fC<pipe-message>\fP command.  When \fIunset\fP,
+  ** Mutt will pipe the messages without any preprocessing. When \fIset\fP, Mutt
+  ** will weed headers and will attempt to decode the messages
+  ** first.
   */
-  { "ssl_use_tlsv1", DT_BOOL, R_NONE, OPTTLSV1, 1 },
+  { "pipe_sep",		DT_STR,	 R_NONE, UL &PipeSep, UL "\n" },
   /*
   ** .pp
-  ** This variables specifies whether to attempt to use TLSv1 in the
-  ** SSL authentication process.
+  ** The separator to add between messages when piping a list of tagged
+  ** messages to an external Unix command.
   */
-#endif
-
   { "pipe_split",	DT_BOOL, R_NONE, OPTPIPESPLIT, 0 },
   /*
   ** .pp
-  ** Used in connection with the \fIpipe-message\fP command and the ``tag-
-  ** prefix'' operator.  If this variable is unset, when piping a list of
+  ** Used in connection with the \fC<pipe-message>\fP function following
+  ** \fC<tag-prefix>\fP.  If this variable is \fIunset\fP, when piping a list of
   ** tagged messages Mutt will concatenate the messages and will pipe them
-  ** as a single folder.  When set, Mutt will pipe the messages one by one.
+  ** all concatenated.  When \fIset\fP, Mutt will pipe the messages one by one.
   ** In both cases the messages are piped in the current sorted order,
-  ** and the ``$$pipe_sep'' separator is added after each message.
-  */
-  { "pipe_decode",	DT_BOOL, R_NONE, OPTPIPEDECODE, 0 },
-  /*
-  ** .pp
-  ** Used in connection with the \fIpipe-message\fP command.  When unset,
-  ** Mutt will pipe the messages without any preprocessing. When set, Mutt
-  ** will weed headers and will attempt to PGP/MIME decode the messages
-  ** first.
+  ** and the $$pipe_sep separator is added after each message.
   */
-  { "pipe_sep",		DT_STR,	 R_NONE, UL &PipeSep, UL "\n" },
+#ifdef USE_POP
+  { "pop_auth_try_all",	DT_BOOL, R_NONE, OPTPOPAUTHTRYALL, 1 },
   /*
   ** .pp
-  ** The separator to add between messages when piping a list of tagged
-  ** messages to an external Unix command.
+  ** If \fIset\fP, Mutt will try all available authentication methods.
+  ** When \fIunset\fP, Mutt will only fall back to other authentication
+  ** methods if the previous methods are unavailable. If a method is
+  ** available but authentication fails, Mutt will not connect to the POP server.
   */
-#ifdef USE_POP
   { "pop_authenticators", DT_STR, R_NONE, UL &PopAuthenticators, UL 0 },
   /*
   ** .pp
   ** This is a colon-delimited list of authentication methods mutt may
   ** attempt to use to log in to an POP server, in the order mutt should
-  ** try them.  Authentication methods are either 'user', 'apop' or any
-  ** SASL mechanism, eg 'digest-md5', 'gssapi' or 'cram-md5'.
-  ** This parameter is case-insensitive. If this parameter is unset
+  ** try them.  Authentication methods are either ``user'', ``apop'' or any
+  ** SASL mechanism, e.g. ``digest-md5'', ``gssapi'' or ``cram-md5''.
+  ** This option is case-insensitive. If this option is \fIunset\fP
   ** (the default) mutt will try all available methods, in order from
   ** most-secure to least-secure.
   ** .pp
-  ** Example: set pop_authenticators="digest-md5:apop:user"
-  */
-  { "pop_auth_try_all",	DT_BOOL, R_NONE, OPTPOPAUTHTRYALL, 1 },
-  /*
-  ** .pp
-  ** If set, Mutt will try all available methods. When unset, Mutt will
-  ** only fall back to other authentication methods if the previous
-  ** methods are unavailable. If a method is available but authentication
-  ** fails, Mutt will not connect to the POP server.
+  ** Example:
+  ** .ts
+  ** set pop_authenticators="digest-md5:apop:user"
+  ** .te
   */
   { "pop_checkinterval", DT_NUM, R_NONE, UL &PopCheckTimeout, 60 },
   /*
   ** .pp
-  ** This variable configures how often (in seconds) POP should look for
-  ** new mail.
+  ** This variable configures how often (in seconds) mutt should look for
+  ** new mail in the currently selected mailbox if it is a POP mailbox.
   */
   { "pop_delete",	DT_QUAD, R_NONE, OPT_POPDELETE, M_ASKNO },
   /*
   ** .pp
-  ** If set, Mutt will delete successfully downloaded messages from the POP
-  ** server when using the fetch-mail function.  When unset, Mutt will
+  ** If \fIset\fP, Mutt will delete successfully downloaded messages from the POP
+  ** server when using the \fC$<fetch-mail>\fP function.  When \fIunset\fP, Mutt will
   ** download messages but also leave them on the POP server.
   */
   { "pop_host",		DT_STR,	 R_NONE, UL &PopHost, UL "" },
   /*
   ** .pp
-  ** The name of your POP server for the fetch-mail function.  You
-  ** can also specify an alternative port, username and password, ie:
-  ** .pp
+  ** The name of your POP server for the \fC$<fetch-mail>\fP function.  You
+  ** can also specify an alternative port, username and password, i.e.:
+  ** .ts
   ** [pop[s]://][username[:password]@]popserver[:port]
+  ** .te
+  ** .pp
+  ** where ``[...]'' denotes an optional part.
   */
   { "pop_last",		DT_BOOL, R_NONE, OPTPOPLAST, 0 },
   /*
   ** .pp
-  ** If this variable is set, mutt will try to use the "LAST" POP command
+  ** If this variable is \fIset\fP, mutt will try to use the ``\fCLAST\fP'' POP command
   ** for retrieving only unread messages from the POP server when using
-  ** the fetch-mail function.
+  ** the \fC$<fetch-mail>\fP function.
+  */
+  { "pop_pass",		DT_STR,	 R_NONE, UL &PopPass, UL "" },
+  /*
+  ** .pp
+  ** Specifies the password for your POP account.  If \fIunset\fP, Mutt will
+  ** prompt you for your password when you open a POP mailbox.
+  ** .pp
+  ** \fBWarning\fP: you should only use this option when you are on a
+  ** fairly secure machine, because the superuser can read your muttrc
+  ** even if you are the only one who can read the file.
   */
   { "pop_reconnect",	DT_QUAD, R_NONE, OPT_POPRECONNECT, M_ASKYES },
   /*
   ** .pp
-  ** Controls whether or not Mutt will try to reconnect to POP server when
-  ** connection lost.
+  ** Controls whether or not Mutt will try to reconnect to the POP server if
+  ** the connection is lost.
   */
   { "pop_user",		DT_STR,	 R_NONE, UL &PopUser, 0 },
   /*
   ** .pp
   ** Your login name on the POP server.
   ** .pp
   ** This variable defaults to your user name on the local machine.
   */
-  { "pop_pass",		DT_STR,	 R_NONE, UL &PopPass, UL "" },
-  /*
-  ** .pp
-  ** Specifies the password for your POP account.  If unset, Mutt will
-  ** prompt you for your password when you open POP mailbox.
-  ** \fBWarning\fP: you should only use this option when you are on a
-  ** fairly secure machine, because the superuser can read your muttrc
-  ** even if you are the only one who can read the file.
-  */
 #endif /* USE_POP */
   { "post_indent_string",DT_STR, R_NONE, UL &PostIndentString, UL "" },
   /*
   ** .pp
-  ** Similar to the ``$$attribution'' variable, Mutt will append this
+  ** Similar to the $$attribution variable, Mutt will append this
   ** string after the inclusion of a message which is being replied to.
   */
   { "post_indent_str",  DT_SYN,  R_NONE, UL "post_indent_string", 0 },
   /*
   */
   { "postpone",		DT_QUAD, R_NONE, OPT_POSTPONE, M_ASKYES },
   /*
   ** .pp
-  ** Controls whether or not messages are saved in the ``$$postponed''
+  ** Controls whether or not messages are saved in the $$postponed
   ** mailbox when you elect not to send immediately.
+  ** .pp
+  ** Also see the $$recall variable.
   */
-  { "postponed",	DT_PATH, R_NONE, UL &Postponed, UL "~/postponed" },
+  { "postponed",	DT_PATH, R_INDEX, UL &Postponed, UL "~/postponed" },
   /*
   ** .pp
   ** Mutt allows you to indefinitely ``$postpone sending a message'' which
   ** you are editing.  When you choose to postpone a message, Mutt saves it
-  ** in the mailbox specified by this variable.  Also see the ``$$postpone''
-  ** variable.
+  ** in the mailbox specified by this variable.
+  ** .pp
+  ** Also see the $$postpone variable.
   */
 #ifdef USE_SOCKET
   { "preconnect",	DT_STR, R_NONE, UL &Preconnect, UL 0},
   /*
   ** .pp
-  ** If set, a shell command to be executed if mutt fails to establish
+  ** If \fIset\fP, a shell command to be executed if mutt fails to establish
   ** a connection to the server. This is useful for setting up secure
-  ** connections, e.g. with ssh(1). If the command returns a  nonzero
+  ** connections, e.g. with \fCssh(1)\fP. If the command returns a  nonzero
   ** status, mutt gives up opening the server. Example:
+  ** .ts
+  ** set preconnect="ssh -f -q -L 1234:mailhost.net:143 mailhost.net \(rs
+  ** sleep 20 < /dev/null > /dev/null"
+  ** .te
   ** .pp
-  ** preconnect="ssh -f -q -L 1234:mailhost.net:143 mailhost.net
-  **                   sleep 20 < /dev/null > /dev/null"
-  ** .pp
-  ** Mailbox 'foo' on mailhost.net can now be reached
-  ** as '{localhost:1234}foo'.
+  ** Mailbox ``foo'' on ``mailhost.net'' can now be reached
+  ** as ``{localhost:1234}foo''.
   ** .pp
-  ** NOTE: For this example to work, you must be able to log in to the
+  ** Note: For this example to work, you must be able to log in to the
   ** remote machine without having to enter a password.
   */
 #endif /* USE_SOCKET */
   { "print",		DT_QUAD, R_NONE, OPT_PRINT, M_ASKNO },
   /*
   ** .pp
-  ** Controls whether or not Mutt asks for confirmation before printing.
-  ** This is useful for people (like me) who accidentally hit ``p'' often.
+  ** Controls whether or not Mutt really prints messages.
+  ** This is set to ``ask-no'' by default, because some people
+  ** accidentally hit ``p'' often.
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
-  ** Used in connection with the print-message command.  If this
-  ** option is set, the message is decoded before it is passed to the
+  ** Used in connection with the \fC<print-message>\fP command.  If this
+  ** option is \fIset\fP, the message is decoded before it is passed to the
   ** external command specified by $$print_command.  If this option
-  ** is unset, no processing will be applied to the message when
+  ** is \fIunset\fP, no processing will be applied to the message when
   ** printing it.  The latter setting may be useful if you are using
   ** some advanced printer filter which is able to properly format
   ** e-mail messages for printing.
   */
   { "print_split",	DT_BOOL, R_NONE, OPTPRINTSPLIT,  0 },
   /*
   ** .pp
-  ** Used in connection with the print-message command.  If this option
-  ** is set, the command sepcified by $$print_command is executed once for
-  ** each message which is to be printed.  If this option is unset, 
+  ** Used in connection with the \fC<print-message>\fP command.  If this option
+  ** is \fIset\fP, the command specified by $$print_command is executed once for
+  ** each message which is to be printed.  If this option is \fIunset\fP,
   ** the command specified by $$print_command is executed only once, and
   ** all the messages are concatenated, with a form feed as the message
   ** separator.
   ** .pp
-  ** Those who use the \fBenscript\fP(1) program's mail-printing mode will
-  ** most likely want to set this option.
+  ** Those who use the \fCenscript\fP(1) program's mail-printing mode will
+  ** most likely want to \fIset\fP this option.
   */
   { "prompt_after",	DT_BOOL, R_NONE, OPTPROMPTAFTER, 1 },
   /*
   ** .pp
-  ** If you use an \fIexternal\fP ``$$pager'', setting this variable will
+  ** If you use an \fIexternal\fP $$pager, setting this variable will
   ** cause Mutt to prompt you for a command when the pager exits rather
-  ** than returning to the index menu.  If unset, Mutt will return to the
+  ** than returning to the index menu.  If \fIunset\fP, Mutt will return to the
   ** index menu when the external pager exits.
   */
   { "query_command",	DT_PATH, R_NONE, UL &QueryCmd, UL "" },
   /*
   ** .pp
-  ** This specifies the command that mutt will use to make external address
-  ** queries.  The string should contain a %s, which will be substituted
-  ** with the query string the user types.  See ``$query'' for more
-  ** information.
+  ** This specifies the command Mutt will use to make external address
+  ** queries.  The string may contain a ``%s'', which will be substituted
+  ** with the query string the user types.  Mutt will add quotes around the
+  ** string substituted for ``%s'' automatically according to shell quoting
+  ** rules, so you should avoid adding your own.  If no ``%s'' is found in
+  ** the string, Mutt will append the user's query to the end of the string.
+  ** See ``$query'' for more information.
+  */
+  { "query_format",	DT_STR, R_NONE, UL &QueryFormat, UL "%4c %t %-25.25a %-25.25n %?e?(%e)?" },
+  /*
+  ** .pp
+  ** This variable describes the format of the ``query'' menu. The
+  ** following \fCprintf(3)\fP-style sequences are understood:
+  ** .dl
+  ** .dt %a  .dd destination address
+  ** .dt %c  .dd current entry number
+  ** .dt %e  .dd extra information *
+  ** .dt %n  .dd destination name
+  ** .dt %t  .dd ``*'' if current entry is tagged, a space otherwise
+  ** .dt %>X .dd right justify the rest of the string and pad with ``X''
+  ** .dt %|X .dd pad to the end of the line with ``X''
+  ** .dt %*X .dd soft-fill with character ``X'' as pad
+  ** .de
+  ** .pp
+  ** For an explanation of ``soft-fill'', see the $$index_format documentation.
+  ** .pp
+  ** * = can be optionally printed if nonzero, see the $$status_format documentation.
   */
   { "quit",		DT_QUAD, R_NONE, OPT_QUIT, M_YES },
   /*
   ** .pp
   ** This variable controls whether ``quit'' and ``exit'' actually quit
-  ** from mutt.  If it set to yes, they do quit, if it is set to no, they
-  ** have no effect, and if it is set to ask-yes or ask-no, you are
+  ** from mutt.  If this option is \fIset\fP, they do quit, if it is \fIunset\fP, they
+  ** have no effect, and if it is set to \fIask-yes\fP or \fIask-no\fP, you are
   ** prompted for confirmation when you try to quit.
   */
   { "quote_regexp",	DT_RX,	 R_PAGER, UL &QuoteRegexp, UL "^([ \t]*[|>:}#])+" },
   /*
   ** .pp
-  ** A regular expression used in the internal-pager to determine quoted
-  ** sections of text in the body of a message.
+  ** A regular expression used in the internal pager to determine quoted
+  ** sections of text in the body of a message. Quoted text may be filtered
+  ** out using the \fC<toggle-quoted>\fP command, or colored according to the
+  ** ``color quoted'' family of directives.
+  ** .pp
+  ** Higher levels of quoting may be colored differently (``color quoted1'',
+  ** ``color quoted2'', etc.). The quoting level is determined by removing
+  ** the last character from the matched text and recursively reapplying
+  ** the regular expression until it fails to produce a match.
   ** .pp
-  ** \fBNote:\fP In order to use the \fIquoted\fP\fBx\fP patterns in the
-  ** internal pager, you need to set this to a regular expression that
-  ** matches \fIexactly\fP the quote characters at the beginning of quoted
-  ** lines.
+  ** Match detection may be overridden by the $$smileys regular expression.
   */
   { "read_inc",		DT_NUM,	 R_NONE, UL &ReadInc, 10 },
   /*
   ** .pp
   ** If set to a value greater than 0, Mutt will display which message it
-  ** is currently on when reading a mailbox.  The message is printed after
-  ** \fIread_inc\fP messages have been read (e.g., if set to 25, Mutt will
-  ** print a message when it reads message 25, and then again when it gets
+  ** is currently on when reading a mailbox or when performing search actions
+  ** such as search and limit. The message is printed after
+  ** this many messages have been read or searched (e.g., if set to 25, Mutt will
+  ** print a message when it is at message 25, and then again when it gets
   ** to message 50).  This variable is meant to indicate progress when
-  ** reading large mailboxes which may take some time.
+  ** reading or searching large mailboxes which may take some time.
   ** When set to 0, only a single message will appear before the reading
   ** the mailbox.
   ** .pp
-  ** Also see the ``$$write_inc'' variable.
+  ** Also see the $$write_inc, $$net_inc and $$time_inc variables and the
+  ** ``$tuning'' section of the manual for performance considerations.
   */
   { "read_only",	DT_BOOL, R_NONE, OPTREADONLY, 0 },
   /*
   ** .pp
-  ** If set, all folders are opened in read-only mode.
+  ** If \fIset\fP, all folders are opened in read-only mode.
   */
   { "realname",		DT_STR,	 R_BOTH, UL &Realname, 0 },
   /*
   ** .pp
-  ** This variable specifies what "real" or "personal" name should be used
+  ** This variable specifies what ``real'' or ``personal'' name should be used
   ** when sending messages.
   ** .pp
-  ** By default, this is the GCOS field from /etc/passwd.  Note that this
+  ** By default, this is the GECOS field from \fC/etc/passwd\fP.  Note that this
   ** variable will \fInot\fP be used when the user has set a real name
   ** in the $$from variable.
   */
   { "recall",		DT_QUAD, R_NONE, OPT_RECALL, M_ASKYES },
   /*
   ** .pp
-  ** Controls whether or not you are prompted to recall postponed messages
-  ** when composing a new message.  Also see ``$$postponed''.
+  ** Controls whether or not Mutt recalls postponed messages
+  ** when composing a new message.
   ** .pp
-  ** Setting this variable to ``yes'' is not generally useful, and thus not
+  ** \fISetting\fP this variable to is not generally useful, and thus not
   ** recommended.
+  ** .pp
+  ** Also see $$postponed variable.
   */
-  { "record",		DT_PATH, R_NONE, UL &Outbox, UL "" },
+  { "record",		DT_PATH, R_NONE, UL &Outbox, UL "~/sent" },
   /*
   ** .pp
   ** This specifies the file into which your outgoing messages should be
   ** appended.  (This is meant as the primary method for saving a copy of
   ** your messages, but another way to do this is using the ``$my_hdr''
-  ** command to create a \fIBcc:\fP field with your email address in it.)
+  ** command to create a ``Bcc:'' field with your email address in it.)
+  ** .pp
+  ** The value of \fI$$record\fP is overridden by the $$force_name and
+  ** $$save_name variables, and the ``$fcc-hook'' command.
+  */
+  { "reflow_text",	DT_BOOL, R_NONE, OPTREFLOWTEXT, 1 },
+  /*
+  ** .pp
+  ** When \fIset\fP, Mutt will reformat paragraphs in text/plain
+  ** parts marked format=flowed.  If \fIunset\fP, Mutt will display paragraphs
+  ** unaltered from how they appear in the message body.  See RFC3676 for
+  ** details on the \fIformat=flowed\fP format.
+  ** .pp
+  ** Also see $$reflow_wrap, and $$wrap.
+  */
+  { "reflow_wrap",	DT_NUM,	R_NONE, UL &ReflowWrap, 78 },
+  /*
+  ** .pp
+  ** This variable controls the maximum paragraph width when reformatting text/plain
+  ** parts when $$reflow_text is \fIset\fP.  When the value is 0, paragraphs will
+  ** be wrapped at the terminal's right margin.  A positive value sets the
+  ** paragraph width relative to the left margin.  A negative value set the
+  ** paragraph width relative to the right margin.
   ** .pp
-  ** The value of \fI$$record\fP is overridden by the ``$$force_name'' and
-  ** ``$$save_name'' variables, and the ``$fcc-hook'' command.
+  ** Also see $$wrap.
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
-  ** If unset and you are replying to a message sent by you, Mutt will
+  ** If \fIunset\fP and you are replying to a message sent by you, Mutt will
   ** assume that you want to reply to the recipients of that message rather
   ** than to yourself.
+  ** .pp
+  ** Also see the ``$alternates'' command.
   */
   { "reply_to",		DT_QUAD, R_NONE, OPT_REPLYTO, M_ASKYES },
   /*
   ** .pp
-  ** If set, Mutt will ask you if you want to use the address listed in the
-  ** Reply-To: header field when replying to a message.  If you answer no,
+  ** If \fIset\fP, when replying to a message, Mutt will use the address listed
+  ** in the Reply-to: header as the recipient of the reply.  If \fIunset\fP,
   ** it will use the address in the From: header field instead.  This
   ** option is useful for reading a mailing list that sets the Reply-To:
   ** header field to the list address and you want to send a private
   ** message to the author of a message.
   */
   { "resolve",		DT_BOOL, R_NONE, OPTRESOLVE, 1 },
   /*
   ** .pp
-  ** When set, the cursor will be automatically advanced to the next
+  ** When \fIset\fP, the cursor will be automatically advanced to the next
   ** (possibly undeleted) message whenever a command that modifies the
   ** current message is executed.
   */
   { "reverse_alias",	DT_BOOL, R_BOTH, OPTREVALIAS, 0 },
   /*
   ** .pp
-  ** This variable controls whether or not Mutt will display the "personal"
+  ** This variable controls whether or not Mutt will display the ``personal''
   ** name from your aliases in the index menu if it finds an alias that
   ** matches the message's sender.  For example, if you have the following
   ** alias:
-  ** .pp
   ** .ts
-  **  alias juser abd30425@somewhere.net (Joe User)
+  ** alias juser abd30425@somewhere.net (Joe User)
   ** .te
   ** .pp
   ** and then you receive mail which contains the following header:
-  ** .pp
   ** .ts
-  **  From: abd30425@somewhere.net
+  ** From: abd30425@somewhere.net
   ** .te
   ** .pp
   ** It would be displayed in the index menu as ``Joe User'' instead of
   ** ``abd30425@somewhere.net.''  This is useful when the person's e-mail
-  ** address is not human friendly (like CompuServe addresses).
+  ** address is not human friendly.
   */
   { "reverse_name",	DT_BOOL, R_BOTH, OPTREVNAME, 0 },
   /*
   ** .pp
   ** It may sometimes arrive that you receive mail to a certain machine,
   ** move the messages to another machine, and reply to some the messages
-  ** from there.  If this variable is set, the default \fIFrom:\fP line of
+  ** from there.  If this variable is \fIset\fP, the default \fIFrom:\fP line of
   ** the reply messages is built using the address where you received the
-  ** messages you are replying to.  If the variable is unset, the
-  ** \fIFrom:\fP line will use your address on the current machine.
+  ** messages you are replying to \fBif\fP that address matches your
+  ** ``$alternates''.  If the variable is \fIunset\fP, or the address that would be
+  ** used doesn't match your ``$alternates'', the \fIFrom:\fP line will use
+  ** your address on the current machine.
+  ** .pp
+  ** Also see the ``$alternates'' command.
   */
   { "reverse_realname",	DT_BOOL, R_BOTH, OPTREVREAL, 1 },
   /*
   ** .pp
-  ** This variable fine-tunes the behaviour of the $reverse_name feature.
-  ** When it is set, mutt will use the address from incoming messages as-is,
-  ** possibly including eventual real names.  When it is unset, mutt will
-  ** override any such realnames with the setting of the $realname variable.
+  ** This variable fine-tunes the behavior of the $$reverse_name feature.
+  ** When it is \fIset\fP, mutt will use the address from incoming messages as-is,
+  ** possibly including eventual real names.  When it is \fIunset\fP, mutt will
+  ** override any such real names with the setting of the $$realname variable.
   */
   { "rfc2047_parameters", DT_BOOL, R_NONE, OPTRFC2047PARAMS, 0 },
   /*
   ** .pp
-  ** When this variable is set, Mutt will decode RFC-2047-encoded MIME 
+  ** When this variable is \fIset\fP, Mutt will decode RFC2047-encoded MIME
   ** parameters. You want to set this variable when mutt suggests you
-  ** to save attachments to files named like this: 
+  ** to save attachments to files named like:
+  ** .ts
   ** =?iso-8859-1?Q?file=5F=E4=5F991116=2Ezip?=
+  ** .te
   ** .pp
-  ** When this variable is set interactively, the change doesn't have
-  ** the desired effect before you have changed folders.
+  ** When this variable is \fIset\fP interactively, the change won't be
+  ** active until you change folders.
   ** .pp
-  ** Note that this use of RFC 2047's encoding is explicitly,
+  ** Note that this use of RFC2047's encoding is explicitly
   ** prohibited by the standard, but nevertheless encountered in the
   ** wild.
-  ** Also note that setting this parameter will \fInot\fP have the effect 
+  ** .pp
+  ** Also note that setting this parameter will \fInot\fP have the effect
   ** that mutt \fIgenerates\fP this kind of encoding.  Instead, mutt will
-  ** unconditionally use the encoding specified in RFC 2231.
+  ** unconditionally use the encoding specified in RFC2231.
   */
   { "save_address",	DT_BOOL, R_NONE, OPTSAVEADDRESS, 0 },
   /*
   ** .pp
-  ** If set, mutt will take the sender's full address when choosing a
-  ** default folder for saving a mail. If ``$$save_name'' or ``$$force_name''
-  ** is set too, the selection of the fcc folder will be changed as well.
+  ** If \fIset\fP, mutt will take the sender's full address when choosing a
+  ** default folder for saving a mail. If $$save_name or $$force_name
+  ** is \fIset\fP too, the selection of the Fcc folder will be changed as well.
   */
   { "save_empty",	DT_BOOL, R_NONE, OPTSAVEEMPTY, 1 },
   /*
   ** .pp
-  ** When unset, mailboxes which contain no saved messages will be removed
-  ** when closed (the exception is ``$$spoolfile'' which is never removed).
-  ** If set, mailboxes are never removed.
+  ** When \fIunset\fP, mailboxes which contain no saved messages will be removed
+  ** when closed (the exception is $$spoolfile which is never removed).
+  ** If \fIset\fP, mailboxes are never removed.
   ** .pp
   ** \fBNote:\fP This only applies to mbox and MMDF folders, Mutt does not
   ** delete MH and Maildir directories.
   */
+  { "save_history",     DT_NUM,  R_NONE, UL &SaveHist, 0 },
+  /*
+  ** .pp
+  ** This variable controls the size of the history (per category) saved in the
+  ** $$history_file file.
+  */
   { "save_name",	DT_BOOL, R_NONE, OPTSAVENAME, 0 },
   /*
   ** .pp
   ** This variable controls how copies of outgoing messages are saved.
-  ** When set, a check is made to see if a mailbox specified by the
+  ** When \fIset\fP, a check is made to see if a mailbox specified by the
   ** recipient address exists (this is done by searching for a mailbox in
-  ** the ``$$folder'' directory with the \fIusername\fP part of the
+  ** the $$folder directory with the \fIusername\fP part of the
   ** recipient address).  If the mailbox exists, the outgoing message will
   ** be saved to that mailbox, otherwise the message is saved to the
-  ** ``$$record'' mailbox.
+  ** $$record mailbox.
   ** .pp
-  ** Also see the ``$$force_name'' variable.
+  ** Also see the $$force_name variable.
   */
   { "score", 		DT_BOOL, R_NONE, OPTSCORE, 1 },
   /*
   ** .pp
   ** When this variable is \fIunset\fP, scoring is turned off.  This can
   ** be useful to selectively disable scoring for certain folders when the
-  ** ``$$score_threshold_delete'' variable and friends are used.
+  ** $$score_threshold_delete variable and related are used.
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
-  /* 
+  /*
   ** .pp
-  ** Messages wich have been assigned a score greater than or equal to this 
+  ** Messages which have been assigned a score greater than or equal to this
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
+  { "search_context",	DT_NUM,  R_NONE, UL &SearchContext, UL 0 },
+  /*
+  ** .pp
+  ** For the pager, this variable specifies the number of lines shown
+  ** before search results. By default, search results will be top-aligned.
+  */
   { "send_charset",	DT_STR,  R_NONE, UL &SendCharset, UL "us-ascii:iso-8859-1:utf-8" },
   /*
   ** .pp
-  ** A list of character sets for outgoing messages. Mutt will use the
+  ** A colon-delimited list of character sets for outgoing messages. Mutt will use the
   ** first character set into which the text can be converted exactly.
-  ** If your ``$$charset'' is not iso-8859-1 and recipients may not
-  ** understand UTF-8, it is advisable to include in the list an
+  ** If your $$charset is not ``iso-8859-1'' and recipients may not
+  ** understand ``UTF-8'', it is advisable to include in the list an
   ** appropriate widely used standard character set (such as
-  ** iso-8859-2, koi8-r or iso-2022-jp) either instead of or after
-  ** "iso-8859-1".
+  ** ``iso-8859-2'', ``koi8-r'' or ``iso-2022-jp'') either instead of or after
+  ** ``iso-8859-1''.
+  ** .pp
+  ** In case the text cannot be converted into one of these exactly,
+  ** mutt uses $$charset as a fallback.
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
-  ** Specifies the number of seconds to wait for the ``$$sendmail'' process
+  ** Specifies the number of seconds to wait for the $$sendmail process
   ** to finish before giving up and putting delivery in the background.
   ** .pp
   ** Mutt interprets the value of this variable as follows:
   ** .dl
   ** .dt >0 .dd number of seconds to wait for sendmail to finish before continuing
   ** .dt 0  .dd wait forever for sendmail to finish
