 			   rak::hexchar_to_value(id[1]), rak::hexchar_to_value(id[2]), rak::hexchar_to_value(id[3]));
     
   } else if (std::isalpha(id[0]) && id[2] == '-' && id[4] == '-' && id[6] == '-' &&
 	     std::isxdigit(id[1]) && std::isxdigit(id[3]) && std::isxdigit(id[5])) {
     // TYPE_THREE_SPARSE.
 
-    iterator itr = std::find_if(m_containers[TYPE_MAINLINE].begin(), m_containers[TYPE_MAINLINE].end(),
-				client_info_equal(id, sizeof_key(TYPE_MAINLINE)));
+    const_iterator itr = std::find_if(m_containers[TYPE_MAINLINE].begin(), m_containers[TYPE_MAINLINE].end(),
+                                      client_info_equal(id, sizeof_key(TYPE_MAINLINE)));
 
     if (itr != m_containers[TYPE_MAINLINE].end())
       first = print_buffer(first, last, "%s %hhu.%hhu.%hhu", itr->second,
 			   rak::hexchar_to_value(id[1]), rak::hexchar_to_value(id[3]), rak::hexchar_to_value(id[5]));
     
     else
