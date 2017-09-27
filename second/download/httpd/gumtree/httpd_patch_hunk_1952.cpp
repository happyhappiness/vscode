     fprintf(stderr, "Options:\n");
     fprintf(stderr, "   -b   Use the password from the command line rather "
                     "than prompting for it.\n");
     fprintf(stderr, "   -c   Create a new database.\n");
     fprintf(stderr, "   -n   Don't update database; display results on stdout.\n");
     fprintf(stderr, "   -m   Force MD5 encryption of the password (default).\n");
-#if (!(defined(WIN32) || defined(TPF) || defined(NETWARE)))
+#if (!(defined(WIN32) || defined(NETWARE)))
     fprintf(stderr, "   -d   Force CRYPT encryption of the password (now deprecated).\n");
 #endif
     fprintf(stderr, "   -p   Do not encrypt the password (plaintext).\n");
     fprintf(stderr, "   -s   Force SHA encryption of the password.\n");
     fprintf(stderr, "   -T   DBM Type (SDBM|GDBM|DB|default).\n");
     fprintf(stderr, "   -l   Display usernames from database on stdout.\n");
