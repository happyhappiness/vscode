extent_type max_length() {
    return std::max(m_branch1 != NULL ? m_branch1->max_length() : 0,
                    std::max(m_branch2 != NULL ? m_branch2->max_length() : 0,
                             m_branch3 != NULL ? m_branch3->max_length() : 0));
  }