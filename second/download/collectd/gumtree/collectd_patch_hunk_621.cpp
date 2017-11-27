  *
  * PARAMETERS
  *   `level'  The log level passed to `plugin_log'.
  *   `c'      Identifier for the complaint.
  *   `format' Message format - see the documentation of printf(3).
  */
-__attribute__ ((format(printf,3,4)))
-void c_complain (int level, c_complain_t *c, const char *format, ...);
+__attribute__((format(printf, 3, 4))) void
+c_complain(int level, c_complain_t *c, const char *format, ...);
 
 /*
  * NAME
  *   c_complain_once
  *
  * DESCRIPTION
