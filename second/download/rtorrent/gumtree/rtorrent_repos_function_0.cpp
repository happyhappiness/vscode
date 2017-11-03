virtual extent_type max_length() {
    return std::max(m_branch1 != NULL ? m_branch1->max_length() : 0,
                    m_branch2 != NULL ? m_branch2->max_length() : 0);
  }