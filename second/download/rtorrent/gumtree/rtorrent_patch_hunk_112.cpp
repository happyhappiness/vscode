                	            A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)  { mvwprintw(m_window, y, x, str, a1, a2, a3, a4, a5, a6, a7); }
 
   template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
   void                print(int x, int y, char* str,
                	            A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) { mvwprintw(m_window, y, x, str, a1, a2, a3, a4, a5, a6, a7, a8); }
 
+  void                print_char(const chtype ch) { waddch(m_window, ch); }
+
+  void                print_char(int x, int y, const chtype ch) { mvwaddch(m_window, y, x, ch); }
+
   void                set_attr(int x, int y, int n, int attr, int color)      { mvwchgat(m_window, y, x, n, attr, color, NULL); }
 
   // Initialize stdscr.
   static void         initialize();
   static void         cleanup();
 
