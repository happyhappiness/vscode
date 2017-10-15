 
 static void mutt_usage (void)
 {
   puts (mutt_make_version ());
 
   puts _(
-"usage: mutt [ -nRyzZ ] [ -e <cmd> ] [ -F <file> ] [ -m <type> ] [ -f <file> ]\n\
-       mutt [ -nx ] [ -e <cmd> ] [ -a <file> ] [ -F <file> ] [ -H <file> ] [ -i <file> ] [ -s <subj> ] [ -b <addr> ] [ -c <addr> ] <addr> [ ... ]\n\
-       mutt [ -n ] [ -e <cmd> ] [ -F <file> ] -p\n\
-       mutt -v[v]\n\
-\n\
+"usage: mutt [<options>] [-z] [-f <file> | -yZ]\n\
+       mutt [<options>] [-x] [-Hi <file>] [-s <subj>] [-bc <addr>] [-a <file> [...] --] <addr> [...]\n\
+       mutt [<options>] [-x] [-s <subj>] [-bc <addr>] [-a <file> [...] --] <addr> [...] < message\n\
+       mutt [<options>] -p\n\
+       mutt [<options>] -A <alias> [...]\n\
+       mutt [<options>] -Q <query> [...]\n\
+       mutt [<options>] -D\n\
+       mutt -v[v]\n");
+
+  puts _("\
 options:\n\
-  -a <file>\tattach a file to the message\n\
+  -A <alias>\texpand the given alias\n\
+  -a <file> [...] --\tattach file(s) to the message\n\
+\t\tthe list of files must be terminated with the \"--\" sequence\n\
   -b <address>\tspecify a blind carbon-copy (BCC) address\n\
   -c <address>\tspecify a carbon-copy (CC) address\n\
-  -e <command>\tspecify a command to be executed after initialization\n\
+  -D\t\tprint the value of all variables to stdout");
+#if DEBUG
+  puts _("  -d <level>\tlog debugging output to ~/.muttdebug0");
+#endif
+  puts _(
+"  -e <command>\tspecify a command to be executed after initialization\n\
   -f <file>\tspecify which mailbox to read\n\
   -F <file>\tspecify an alternate muttrc file\n\
-  -H <file>\tspecify a draft file to read header from\n\
-  -i <file>\tspecify a file which Mutt should include in the reply\n\
+  -H <file>\tspecify a draft file to read header and body from\n\
+  -i <file>\tspecify a file which Mutt should include in the body\n\
   -m <type>\tspecify a default mailbox type\n\
   -n\t\tcauses Mutt not to read the system Muttrc\n\
-  -p\t\trecall a postponed message\n\
+  -p\t\trecall a postponed message");
+  
+  puts _("\
+  -Q <variable>\tquery a configuration variable\n\
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
 
+extern const char cc_version[];
+extern const char cc_cflags[];
+extern const char configure_options[];
+
+static char *
+rstrip_in_place(char *s)
+{
+  char *p;
+
+  p = &s[strlen(s)];
+  if (p == s)
+    return s;
+  p--;
+  while (p >= s && (*p == '\n' || *p == '\r'))
+    *p-- = '\0';
+  return s;
+}
+
 static void show_version (void)
 {
   struct utsname uts;
 
   puts (mutt_make_version());
   puts (_(Notice));
