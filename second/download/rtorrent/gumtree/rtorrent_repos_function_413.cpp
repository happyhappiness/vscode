virtual bool operator () (Download* d1, Download* d2) const {
    return
      rpc::call_command_d_string(m_name, d1) == m_value &&
      rpc::call_command_d_string(m_name, d2) != m_value;
  }