 #endif
 
 #ifdef HAVE_SYS_RESOURCE_H
 # include <sys/resource.h>
 #endif
 
-#ifdef HAVE_PGP
+#ifdef CRYPT_BACKEND_CLASSIC_PGP
 
+#include "mutt_crypt.h"
+#include "mutt_menu.h"
 
-char PgpPass[STRING];
-static time_t PgpExptime = 0; /* when does the cached passphrase expire? */
+
+char PgpPass[LONG_STRING];
+time_t PgpExptime = 0; /* when does the cached passphrase expire? */
 
 void pgp_void_passphrase (void)
 {
   memset (PgpPass, 0, sizeof (PgpPass));
   PgpExptime = 0;
 }
 
-# if defined(HAVE_SETRLIMIT) && (!defined(DEBUG))
-
-static void disable_coredumps (void)
-{
-  struct rlimit rl = {0, 0};
-  static short done = 0;
-
-  if (!done)
-  {
-    setrlimit (RLIMIT_CORE, &rl);
-    done = 1;
-  }
-}
-
-# endif /* HAVE_SETRLIMIT */
-
 int pgp_valid_passphrase (void)
 {
   time_t now = time (NULL);
 
-# if defined(HAVE_SETRLIMIT) && (!defined(DEBUG))
-  disable_coredumps ();
-# endif
+  if (pgp_use_gpg_agent())
+    {
+      *PgpPass = 0;
+      return 1; /* handled by gpg-agent */
+    }
 
-  if (now < PgpExptime) return 1; /* just use the cached copy. */
+  if (now < PgpExptime)
+    /* Use cached copy.  */
+    return 1;
+  
   pgp_void_passphrase ();
 
   if (mutt_get_password (_("Enter PGP passphrase:"), PgpPass, sizeof (PgpPass)) == 0)
-  {
-    PgpExptime = time (NULL) + PgpTimeout;
-    return (1);
-  }
+    {
+      PgpExptime = time (NULL) + PgpTimeout;
+      return (1);
+    }
   else
-  {
     PgpExptime = 0;
-    return (0);
-  }
-  /* not reached */
+
+  return 0;
 }
 
-void mutt_forget_passphrase (void)
+void pgp_forget_passphrase (void)
 {
   pgp_void_passphrase ();
   mutt_message _("PGP passphrase forgotten.");
 }
 
+int pgp_use_gpg_agent (void)
+{
+  char *tty;
+
+  if (!option (OPTUSEGPGAGENT) || !getenv ("GPG_AGENT_INFO"))
+    return 0;
 
-char *pgp_keyid(pgp_key_t *k)
+  if ((tty = ttyname(0)))
+    setenv("GPG_TTY", tty, 0);
+
+  return 1;
+}
+
+char *pgp_keyid(pgp_key_t k)
 {
-  if((k->flags & KEYFLAG_SUBKEY) && k->parent)
+  if((k->flags & KEYFLAG_SUBKEY) && k->parent && option(OPTPGPIGNORESUB))
     k = k->parent;
 
   return _pgp_keyid(k);
 }
 
-char *_pgp_keyid(pgp_key_t *k)
+char *_pgp_keyid(pgp_key_t k)
 {
   if(option(OPTPGPLONGIDS))
     return k->keyid;
   else
     return (k->keyid + 8);
 }
 
 /* ----------------------------------------------------------------------------
  * Routines for handing PGP input.
  */
 
-/* print the current time to avoid spoofing of the signature output */
-static void pgp_current_time (STATE *s)
-{
-  time_t t;
-  char p[STRING];
-
-  t = time (NULL);
-  setlocale (LC_TIME, "");
-  strftime (p, sizeof (p),
-	    _("[-- PGP output follows (current time: %c) --]\n"),
-	    localtime (&t));
-  setlocale (LC_TIME, "C");
-  state_attach_puts (p, s);
-}
 
 
 /* Copy PGP output messages and look for signs of a good signature */
 
 static int pgp_copy_checksig (FILE *fpin, FILE *fpout)
 {
