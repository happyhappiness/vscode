+/*************************************************
+*           PCRE DEMONSTRATION PROGRAM           *
+*************************************************/
+
+/* This is a demonstration program to illustrate the most straightforward ways
+of calling the PCRE regular expression library from a C program. See the
+pcresample documentation for a short discussion.
+
+Compile thuswise:
+  gcc -Wall pcredemo.c -I/usr/local/include -L/usr/local/lib \
+    -R/usr/local/lib -lpcre
+
+Replace "/usr/local/include" and "/usr/local/lib" with wherever the include and
+library files for PCRE are installed on your system. Only some operating
+systems (e.g. Solaris) use the -R option.
+*/
+
+
 #include <stdio.h>
 #include <string.h>
 #include <pcre.h>
 
-/* Compile thuswise:
-  gcc -Wall pcredemo.c -I/opt/local/include -L/opt/local/lib \
-    -R/opt/local/lib -lpcre
-*/
-
 #define OVECCOUNT 30    /* should be a multiple of 3 */
 
+
 int main(int argc, char **argv)
 {
 pcre *re;
 const char *error;
+char *pattern;
+char *subject;
+unsigned char *name_table;
 int erroffset;
+int find_all;
+int namecount;
+int name_entry_size;
 int ovector[OVECCOUNT];
+int subject_length;
 int rc, i;
 
-if (argc != 3)
+
+/**************************************************************************
+* First, sort out the command line. There is only one possible option at  *
+* the moment, "-g" to request repeated matching to find all occurrences,  *
+* like Perl's /g option. We set the variable find_all to a non-zero value *
+* if the -g option is present. Apart from that, there must be exactly two *
+* arguments.                                                              *
+**************************************************************************/
+
+find_all = 0;
+for (i = 1; i < argc; i++)
+  {
+  if (strcmp(argv[i], "-g") == 0) find_all = 1;
+    else break;
+  }
+
+/* After the options, we require exactly two arguments, which are the pattern,
+and the subject string. */
+
+if (argc - i != 2)
   {
   printf("Two arguments required: a regex and a subject string\n");
   return 1;
   }
 
-/* Compile the regular expression in the first argument */
+pattern = argv[i];
+subject = argv[i+1];
+subject_length = (int)strlen(subject);
+
+
+/*************************************************************************
+* Now we are going to compile the regular expression pattern, and handle *
+* and errors that are detected.                                          *
+*************************************************************************/
 
 re = pcre_compile(
-  argv[1],              /* the pattern */
+  pattern,              /* the pattern */
   0,                    /* default options */
   &error,               /* for error message */
   &erroffset,           /* for error offset */
   NULL);                /* use default character tables */
 
 /* Compilation failed: print the error message and exit */
