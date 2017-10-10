 #define raise mingw_raise
 
 /*
  * ANSI emulation wrappers
  */
 
-int winansi_fputs(const char *str, FILE *stream);
-int winansi_printf(const char *format, ...) __attribute__((format (printf, 1, 2)));
-int winansi_fprintf(FILE *stream, const char *format, ...) __attribute__((format (printf, 2, 3)));
-#define fputs winansi_fputs
-#define printf(...) winansi_printf(__VA_ARGS__)
-#define fprintf(...) winansi_fprintf(__VA_ARGS__)
+void winansi_init(void);
+HANDLE winansi_get_osfhandle(int fd);
 
 /*
  * git specific compatibility
  */
 
 #define has_dos_drive_prefix(path) (isalpha(*(path)) && (path)[1] == ':')
