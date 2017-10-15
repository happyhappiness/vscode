 
   void                clear();
 
   void                set_column(unsigned int column)      { m_column = column; }
   void                set_column_width(extent_type* width) { m_columnWidth = width; }
 
-  virtual char*       print(char* first, char* last, Canvas::attributes_list* attributes, void* object);
+  virtual char*       print(char* first, char* last, Canvas::attributes_list* attributes, rpc::target_type target);
 
   virtual extent_type max_length();
 
 private:
   unsigned int        m_column;
   extent_type*        m_columnWidth;
