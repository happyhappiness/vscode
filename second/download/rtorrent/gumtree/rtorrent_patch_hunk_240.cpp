 //           3185 Skoppum, NORWAY
 
 #include "config.h"
 
 #include <rak/string_manip.h>
 
+#include "rpc/parse_commands.h"
 #include "text_element_string.h"
 
 namespace display {
 
 char*
-TextElementStringBase::print(char* first, char* last, Canvas::attributes_list* attributes, void* object) {
+TextElementStringBase::print(char* first, char* last, Canvas::attributes_list* attributes, rpc::target_type target) {
   Attributes baseAttribute = attributes->back();
   push_attribute(attributes, Attributes(first, m_attributes, Attributes::color_invalid));
 
   if (first == last)
     return first;
 
   if (m_flags & flag_escape_hex) {
     char buffer[last - first];
-    char* bufferLast = copy_string(buffer, buffer + (last - first), object);
+    char* bufferLast = copy_string(buffer, buffer + (last - first), target);
 
     first = rak::transform_hex(buffer, bufferLast, first, last);
 
   } else if (m_flags & flag_escape_html) {
     char buffer[last - first];
-    char* bufferLast = copy_string(buffer, buffer + (last - first), object);
+    char* bufferLast = copy_string(buffer, buffer + (last - first), target);
 
     first = rak::copy_escape_html(buffer, bufferLast, first, last);
 
   } else {
-    first = copy_string(first, last, object);
+    first = copy_string(first, last, target);
   }  
 
   push_attribute(attributes, Attributes(first, baseAttribute));
 
   return first;
 }
 
 char*
-TextElementString::copy_string(char* first, char* last, void* object) {
+TextElementString::copy_string(char* first, char* last, rpc::target_type target) {
   extent_type length = std::min<extent_type>(last - first, m_string.size());
   
   std::memcpy(first, m_string.c_str(), length);
 
   return first + length;
 }
 
 char*
-TextElementCString::copy_string(char* first, char* last, void* object) {
+TextElementCString::copy_string(char* first, char* last, rpc::target_type target) {
   extent_type length = std::min<extent_type>(last - first, m_length);
 
   std::memcpy(first, m_string, length);
 
   return first + length;
 }
 
+char*
+TextElementCommand::print(char* first, char* last, Canvas::attributes_list* attributes, rpc::target_type target) {
+  Attributes baseAttribute = attributes->back();
+  push_attribute(attributes, Attributes(first, m_attributes, Attributes::color_invalid));
+
+  torrent::Object result = rpc::parse_command(target, m_command, m_commandEnd).first;
+
+  if (first == last)
+    return first;
+
+  switch (result.type()) {
+  case torrent::Object::TYPE_STRING:
+  {
+    const std::string& str = result.as_string();
+
+    if (m_flags & flag_escape_hex) {
+      first = rak::transform_hex(str.c_str(), str.c_str() + str.size(), first, last);
+
+    } else if (m_flags & flag_escape_html) {
+      first = rak::copy_escape_html(str.c_str(), str.c_str() + str.size(), first, last);
+
+    } else {
+      size_t length = std::min<size_t>(str.size(), std::distance(first, last));
+
+      std::memcpy(first, str.c_str(), length);
+      first += std::min<size_t>(str.size(), length);
+    }  
+
+    break;
+  }
+  case torrent::Object::TYPE_VALUE:
+  { 
+    first += std::max(snprintf(first, last - first + 1, "%lld", result.as_value()), 0);
+    break;
+  }
+  default:
+    return first;
+  }
+
+  push_attribute(attributes, Attributes(first, baseAttribute));
+  return first;
+}
+
 }
