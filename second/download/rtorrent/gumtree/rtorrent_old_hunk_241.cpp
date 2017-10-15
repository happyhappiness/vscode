  int                 flags() const                 { return m_flags; }
  void                set_flags(int flags)          { m_flags = flags; }

  int                 attributes() const            { return m_attributes; }
  void                set_attributes(int a)         { m_attributes = a; }

  virtual char*       print(char* first, char* last, Canvas::attributes_list* attributes, void* object);

protected:
  virtual char*       copy_string(char* first, char* last, void* object) = 0;

  int                 m_flags;
  int                 m_attributes;
};

class TextElementString : public TextElementStringBase {
