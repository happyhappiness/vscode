   static const uint32_t key_size = 3;
 
   typedef uint32_t                               size_type;
   typedef std::pair<char[key_size], const char*> value_type;
   typedef std::vector<value_type>                container_type;
   typedef container_type::iterator               iterator;
+  typedef container_type::const_iterator         const_iterator;
 
   typedef enum {
     TYPE_AZUREUS,
     TYPE_COMPACT,
     TYPE_MAINLINE,
     TYPE_MAXSIZE
   } Type;
 
   ClientInfo();
 
   void                insert(Type t, const char* key, const char* name);
 
-  char*               print(char* first, char* last, const char* id);
+  char*               print(char* first, char* last, const char* id) const;
 
-  size_type           sizeof_key(Type t) {
+  // Fix this...
+  std::string         str(const char* id) const;
+  std::string         str_str(const std::string& id) const { return str(id.c_str()); }
+
+  size_type           sizeof_key(Type t) const {
     switch (t) {
     case TYPE_AZUREUS:  return 2;
     case TYPE_COMPACT:  return 1;
     case TYPE_MAINLINE: return 1;
     default:
     case TYPE_MAXSIZE:  return 0;
