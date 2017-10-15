   typedef typename slot_type::result_type   result_type;
   
   TextElementBranch3(const slot_type& slot1, TextElement* branch1, const slot_type& slot2, TextElement* branch2, TextElement* branch3) :
     m_slot1(slot1), m_slot2(slot2), m_branch1(branch1), m_branch2(branch2), m_branch3(branch3) {}
   ~TextElementBranch3() { delete m_branch1; delete m_branch2; delete m_branch3; }
 
-  virtual char* print(char* first, char* last, Canvas::attributes_list* attributes, void* object) {
-    if (object == NULL)
+  virtual char* print(char* first, char* last, Canvas::attributes_list* attributes, rpc::target_type target) {
+    if (target.second == NULL)
       return first;
 
-    if (m_slot1(reinterpret_cast<arg1_type>(object)))
-      return m_branch1 != NULL ? m_branch1->print(first, last, attributes, object) : first;
-    else if (m_slot2(reinterpret_cast<arg1_type>(object)))
-      return m_branch2 != NULL ? m_branch2->print(first, last, attributes, object) : first;
+    if (m_slot1(reinterpret_cast<arg1_type>(target.second)))
+      return m_branch1 != NULL ? m_branch1->print(first, last, attributes, target) : first;
+    else if (m_slot2(reinterpret_cast<arg1_type>(target.second)))
+      return m_branch2 != NULL ? m_branch2->print(first, last, attributes, target) : first;
     else
-      return m_branch3 != NULL ? m_branch3->print(first, last, attributes, object) : first;
+      return m_branch3 != NULL ? m_branch3->print(first, last, attributes, target) : first;
   }
 
   virtual extent_type max_length() {
     return std::max(m_branch1 != NULL ? m_branch1->max_length() : 0,
                     std::max(m_branch2 != NULL ? m_branch2->max_length() : 0,
                              m_branch3 != NULL ? m_branch3->max_length() : 0));
