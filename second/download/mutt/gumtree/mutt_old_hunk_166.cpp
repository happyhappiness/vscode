static void mutt_usage (void)
{
  puts (mutt_make_version ());

  puts _(
"usage: mutt [<options>] [-z] [-f <file> | -yZ]\n\
       mutt [<options>] [-x] [-Hi <file>] [-s <subj>] [-bc <addr>] [-a <file> [...] --] <addr> [...]\n\
       mutt [<options>] [-x] [-s <subj>] [-bc <addr>] [-a <file> [...] --] <addr> [...] < message\n\
       mutt [<options>] -p\n\
       mutt [<options>] -A <alias> [...]\n\
       mutt [<options>] -Q <query> [...]\n\
       mutt [<options>] -D\n\
       mutt -v[v]\n");
