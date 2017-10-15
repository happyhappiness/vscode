
  uint32_t            interval() const         { return m_interval; }
  void                set_interval(uint32_t i) { m_interval = i; }

  void                push_back(TextElement* element);

  virtual void        redraw();

private:
  rpc::target_type    m_target;

  extent_type         m_margin;
  uint32_t            m_interval;
};

}
