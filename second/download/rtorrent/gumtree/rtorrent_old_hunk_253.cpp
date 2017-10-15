                                  text_element_wrapper entry5);

  void                push_column(text_element_wrapper entry1, text_element_wrapper entry2,
                                  text_element_wrapper entry3, text_element_wrapper entry4,
                                  text_element_wrapper entry5, text_element_wrapper entry6);

  void                set_column(unsigned int column)     { m_column = column; }

  extent_type         column_width() const                { return m_columnWidth; }
  void                set_column_width(extent_type width) { m_columnWidth = width; }

private:
  WindowText*         m_window;

  unsigned int        m_column;
  extent_type         m_columnWidth;
