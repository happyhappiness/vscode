void
SCgiTask::close() {
  if (!get_fd().is_valid())
    return;

  control->poll()->remove_read(this);
  control->poll()->remove_write(this);
  control->poll()->remove_error(this);
  control->poll()->close(this);

  get_fd().close();
  get_fd().clear();

  delete [] m_buffer;
  m_buffer = NULL;

  // Test
//   char buffer[512];
//   sprintf(buffer, "SCgi system call processed: %i", (int)(rak::timer::current() - scgiTimer).usec());
//   control->core()->push_log(std::string(buffer));
}