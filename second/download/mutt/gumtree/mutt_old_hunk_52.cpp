
static void mutt_usage (void)
{
  puts (mutt_make_version ());

  puts _(
"usage: mutt [ -nRyzZ ] [ -e <cmd> ] [ -F <file> ] [ -m <type> ] [ -f <file> ]\n\
       mutt [ -nx ] [ -e <cmd> ] [ -a <file> ] [ -F <file> ] [ -H <file> ] [ -i <file> ] [ -s <subj> ] [ -b <addr> ] [ -c <addr> ] <addr> [ ... ]\n\
       mutt [ -n ] [ -e <cmd> ] [ -F <file> ] -p\n\
       mutt -v[v]\n\
\n\
options:\n\
  -a <file>\tattach a file to the message\n\
  -b <address>\tspecify a blind carbon-copy (BCC) address\n\
  -c <address>\tspecify a carbon-copy (CC) address\n\
  -e <command>\tspecify a command to be executed after initialization\n\
  -f <file>\tspecify which mailbox to read\n\
  -F <file>\tspecify an alternate muttrc file\n\
  -H <file>\tspecify a draft file to read header from\n\
  -i <file>\tspecify a file which Mutt should include in the reply\n\
  -m <type>\tspecify a default mailbox type\n\
  -n\t\tcauses Mutt not to read the system Muttrc\n\
  -p\t\trecall a postponed message\n\
  -R\t\topen mailbox in read-only mode\n\
  -s <subj>\tspecify a subject (must be in quotes if it has spaces)\n\
  -v\t\tshow version and compile-time definitions\n\
  -x\t\tsimulate the mailx send mode\n\
  -y\t\tselect a mailbox specified in your `mailboxes' list\n\
  -z\t\texit immediately if there are no messages in the mailbox\n\
  -Z\t\topen the first folder with new message, exit immediately if none\n\
  -h\t\tthis help message");

  exit (0);
}

static void show_version (void)
{
  struct utsname uts;

  puts (mutt_make_version());
  puts (_(Notice));
