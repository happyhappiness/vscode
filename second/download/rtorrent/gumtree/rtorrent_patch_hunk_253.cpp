                                   text_element_wrapper entry5);
 
   void                push_column(text_element_wrapper entry1, text_element_wrapper entry2,
                                   text_element_wrapper entry3, text_element_wrapper entry4,
                                   text_element_wrapper entry5, text_element_wrapper entry6);
 
-  void                set_column(unsigned int column)     { m_column = column; }
+  void                set_column(unsigned int column)            { m_column = column; }
+  void                set_error_handler(display::TextElement* t) { m_window->set_error_handler(t); }
 
-  extent_type         column_width() const                { return m_columnWidth; }
-  void                set_column_width(extent_type width) { m_columnWidth = width; }
+  extent_type         column_width() const                       { return m_columnWidth; }
+  void                set_column_width(extent_type width)        { m_columnWidth = width; }
 
 private:
   WindowText*         m_window;
 
   unsigned int        m_column;
   extent_type         m_columnWidth;
