void
SCgi::event_read() {
  rak::socket_address sa;
  utils::SocketFd fd;

  while ((fd = get_fd().accept(&sa)).is_valid()) {
    SCgiTask* task = std::find_if(m_task, m_task + max_tasks, std::mem_fun_ref(&SCgiTask::is_available));

    if (task == task + max_tasks) {
      // Ergh... just closing for now.
      fd.close();
      continue;
    }
    
    task->open(this, fd.get_fd());
  }
}