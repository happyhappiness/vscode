{
    port_dissociate(handle->loop->fs_fd,
                    PORT_SOURCE_FILE,
                    (uintptr_t) &handle->fo);
  }