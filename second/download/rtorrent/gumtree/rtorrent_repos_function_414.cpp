virtual bool operator () (Download* d1, Download* d2) const {
    if (m_reverse)
      return rpc::call_command_d_value(m_name, d2) < rpc::call_command_d_value(m_name, d1);
    else
      return rpc::call_command_d_value(m_name, d1) < rpc::call_command_d_value(m_name, d2);
  }