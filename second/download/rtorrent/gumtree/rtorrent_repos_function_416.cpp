virtual bool operator () (Download* d1) const {
    return (rpc::call_command_d_value(m_name, d1) == m_value) != m_inverse;
  }