  ** check only happens after the \fIfirst\fP edit of the file).  When set
  ** to \fIno\fP, composition will never be aborted.
  */
  { "alias_file",	DT_PATH, R_NONE, UL &AliasFile, UL "~/.muttrc" },
  /*
  ** .pp
  ** The default file in which to save aliases created by the
  ** \fC$<create-alias>\fP function. Entries added to this file are
  ** encoded in the character set specified by $$config_charset if it
  ** is \fIset\fP or the current character set otherwise.
  ** .pp
  ** \fBNote:\fP Mutt will not automatically source this file; you must
  ** explicitly use the ``$source'' command for it to be executed in case
  ** this option points to a dedicated alias file.
  ** .pp
  ** The default for this option is the currently used muttrc file, or
  ** ``~/.muttrc'' if no user muttrc was found.
  */
  { "alias_format",	DT_STR,  R_NONE, UL &AliasFmt, UL "%4n %2f %t %-10a   %r" },
  /*
  ** .pp
  ** Specifies the format of the data displayed for the ``$alias'' menu.  The
  ** following \fCprintf(3)\fP-style sequences are available:
  ** .dl
  ** .dt %a .dd alias name
  ** .dt %f .dd flags - currently, a ``d'' for an alias marked for deletion
  ** .dt %n .dd index number
  ** .dt %r .dd address which alias expands to
  ** .dt %t .dd character which indicates if the alias is tagged for inclusion
  ** .de
  */
  { "allow_8bit",	DT_BOOL, R_NONE, OPTALLOW8BIT, 1 },
