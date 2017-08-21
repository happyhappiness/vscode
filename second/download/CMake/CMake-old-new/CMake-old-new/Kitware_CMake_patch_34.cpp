@@ -9,7 +9,6 @@
 #include "Terminal.h.in"
 #endif
 
-/*--------------------------------------------------------------------------*/
 /* Configure support for this platform.  */
 #if defined(_WIN32) || defined(__CYGWIN__)
 #define KWSYS_TERMINAL_SUPPORT_CONSOLE
@@ -18,7 +17,6 @@
 #define KWSYS_TERMINAL_ISATTY_WORKS
 #endif
 
-/*--------------------------------------------------------------------------*/
 /* Include needed system APIs.  */
 
 #include <stdarg.h> /* va_list */
@@ -36,7 +34,6 @@
 #include <sys/stat.h> /* fstat */
 #endif
 
-/*--------------------------------------------------------------------------*/
 static int kwsysTerminalStreamIsVT100(FILE* stream, int default_vt100,
                                       int default_tty);
 static void kwsysTerminalSetVT100Color(FILE* stream, int color);
@@ -47,7 +44,6 @@ static void kwsysTerminalSetConsoleColor(HANDLE hOut,
                                          FILE* stream, int color);
 #endif
 
-/*--------------------------------------------------------------------------*/
 void kwsysTerminal_cfprintf(int color, FILE* stream, const char* format, ...)
 {
   /* Setup the stream with the given color if possible.  */
@@ -89,7 +85,6 @@ void kwsysTerminal_cfprintf(int color, FILE* stream, const char* format, ...)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 /* Detect cases when a stream is definitely not interactive.  */
 #if !defined(KWSYS_TERMINAL_ISATTY_WORKS)
 static int kwsysTerminalStreamIsNotInteractive(FILE* stream)
@@ -106,7 +101,6 @@ static int kwsysTerminalStreamIsNotInteractive(FILE* stream)
 }
 #endif
 
-/*--------------------------------------------------------------------------*/
 /* List of terminal names known to support VT100 color escape sequences.  */
 static const char* kwsysTerminalVT100Names[] = { "Eterm",
                                                  "ansi",
@@ -162,7 +156,6 @@ static const char* kwsysTerminalVT100Names[] = { "Eterm",
                                                  "xterm-termite",
                                                  0 };
 
-/*--------------------------------------------------------------------------*/
 /* Detect whether a stream is displayed in a VT100-compatible terminal.  */
 static int kwsysTerminalStreamIsVT100(FILE* stream, int default_vt100,
                                       int default_tty)
@@ -214,7 +207,6 @@ static int kwsysTerminalStreamIsVT100(FILE* stream, int default_vt100,
 #endif
 }
 
-/*--------------------------------------------------------------------------*/
 /* VT100 escape sequence strings.  */
 #define KWSYS_TERMINAL_VT100_NORMAL "\33[0m"
 #define KWSYS_TERMINAL_VT100_BOLD "\33[1m"
@@ -238,7 +230,6 @@ static int kwsysTerminalStreamIsVT100(FILE* stream, int default_vt100,
 #define KWSYS_TERMINAL_VT100_BACKGROUND_CYAN "\33[46m"
 #define KWSYS_TERMINAL_VT100_BACKGROUND_WHITE "\33[47m"
 
-/*--------------------------------------------------------------------------*/
 /* Write VT100 escape sequences to the stream for the given color.  */
 static void kwsysTerminalSetVT100Color(FILE* stream, int color)
 {
@@ -307,7 +298,6 @@ static void kwsysTerminalSetVT100Color(FILE* stream, int color)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 #if defined(KWSYS_TERMINAL_SUPPORT_CONSOLE)
 
 #define KWSYS_TERMINAL_MASK_FOREGROUND                                        \