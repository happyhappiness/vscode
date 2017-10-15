                          int flags = TextElementStringBase::flag_normal,
                          int attributes = Attributes::a_invalid,
                          TextElement::extent_type length = TextElement::extent_full) {
   return new TextElementStringSlot<slot_type>(slot, flags, attributes, length);
 }
 
+//
+// New TE's for calling commands directly. Move to a better place.
+//
+
+class TextElementCommand : public TextElement {
+public:
+  static const int flag_normal      = 0;
+  static const int flag_escape_hex  = (1 << 0);
+  static const int flag_escape_html = (1 << 1);
+
+  static const int flag_fixed_width = (1 << 8);
+
+  TextElementCommand(const char* command, int flags, int attributes, extent_type length) :
+    m_flags(flags),
+    m_attributes(attributes),
+    m_length(length),
+    m_command(command),
+    m_commandEnd(command + std::strlen(command)) {}
+
+  int                 flags() const                 { return m_flags; }
+  void                set_flags(int flags)          { m_flags = flags; }
+
+  int                 attributes() const            { return m_attributes; }
+  void                set_attributes(int a)         { m_attributes = a; }
+
+  virtual char*       print(char* first, char* last, Canvas::attributes_list* attributes, rpc::target_type target);
+
+  virtual extent_type max_length()                  { return m_length; }
+
+protected:
+  int                 m_flags;
+  int                 m_attributes;
+  extent_type         m_length;
+
+  const char*         m_command;
+  const char*         m_commandEnd;
+};
+
 }
 
 #endif
