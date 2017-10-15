   TextElement() {}
   virtual ~TextElement() {}
 
   // The last element must point to a valid memory location into which
   // the caller must write a '\0' to terminate the c string. The
   // attributes must contain at least one attribute.
-  virtual char*       print(char* first, char* last, Canvas::attributes_list* attributes, void* object) = 0;
+  virtual char*       print(char* first, char* last, Canvas::attributes_list* attributes, rpc::target_type target) = 0;
 
   virtual extent_type max_length() = 0;
 
   static void         push_attribute(Canvas::attributes_list* attributes, Attributes value);
 
 private:
