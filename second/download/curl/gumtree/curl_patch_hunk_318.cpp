   char *libcurl; /* output libcurl code to this file name */
   bool raw;
   bool post301;
   bool nokeepalive; /* for keepalive needs */
   long alivetime;
 
+  int default_node_flags; /* default flags to seach for each 'node', which is
+                             basically each given URL to transfer */
   struct OutStruct *outs;
 };
 
 #define WARN_PREFIX "Warning: "
 #define WARN_TEXTWIDTH (79 - (int)strlen(WARN_PREFIX))
 /* produce this text message to the user unless mute was selected */
 static void warnf(struct Configurable *config, const char *fmt, ...)
 {
-  if(!(config->conf & CONF_MUTE)) {
+  if(!config->mute) {
     va_list ap;
     int len;
     char *ptr;
     char print_buffer[256];
 
     va_start(ap, fmt);
