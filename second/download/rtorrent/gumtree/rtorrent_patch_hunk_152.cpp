 
   static bool         m_isInitialized;
 
   WINDOW*             m_window;
 };
 
-// Undefines 'timeout' that ncurses defines which screws up the global
-// namespace. Idiots; Especially you, ESR.
-#undef timeout
+inline void
+Canvas::print(unsigned int x, unsigned int y, const char* str, ...) {
+  va_list arglist;
+
+  va_start(arglist, str);
+  wmove(m_window, y, x);
+  vw_printw(m_window, const_cast<char*>(str), arglist);
+  va_end(arglist);
+}
 
 }
 
 #endif
