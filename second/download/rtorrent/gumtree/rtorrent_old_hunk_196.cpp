  // the caller must write a '\0' to terminate the c string. The
  // attributes must contain at least one attribute.
  virtual char*       print(char* first, char* last, Canvas::attributes_list* attributes, void* object) = 0;

  virtual extent_type max_length() = 0;

private:
  TextElement(const TextElement&);
  void operator = (const TextElement&);
};

}
