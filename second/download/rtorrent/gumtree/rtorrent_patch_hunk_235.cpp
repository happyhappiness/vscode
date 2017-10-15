   typedef typename slot_type::result_type   result_type;
   
   TextElementBranchVoid(const slot_type& slot, TextElement* branch1, TextElement* branch2) :
     m_slot(slot), m_branch1(branch1), m_branch2(branch2) {}
   ~TextElementBranchVoid() { delete m_branch1; delete m_branch2; }
 
-  virtual char* print(char* first, char* last, Canvas::attributes_list* attributes, void* object) {
+  virtual char* print(char* first, char* last, Canvas::attributes_list* attributes, rpc::target_type target) {
     if (m_slot())
-      return m_branch1 != NULL ? m_branch1->print(first, last, attributes, object) : first;
+      return m_branch1 != NULL ? m_branch1->print(first, last, attributes, target) : first;
     else
-      return m_branch2 != NULL ? m_branch2->print(first, last, attributes, object) : first;
+      return m_branch2 != NULL ? m_branch2->print(first, last, attributes, target) : first;
   }
 
   virtual extent_type max_length() {
     return std::max(m_branch1 != NULL ? m_branch1->max_length() : 0,
                     m_branch2 != NULL ? m_branch2->max_length() : 0);
   }
