
  uint32_t            interval() const         { return m_interval; }
  void                set_interval(uint32_t i) { m_interval = i; }

  void                push_back(TextElement* element);

  // Set an error handler if targets pointing to NULL elements should
  // be handled separately to avoid throwing errors.
  void                set_error_handler(TextElement* element) { m_errorHandler = element; }

  virtual void        redraw();

private:
  rpc::target_type    m_target;
  TextElement*        m_errorHandler;

  extent_type         m_margin;
  uint32_t            m_interval;
};

}
