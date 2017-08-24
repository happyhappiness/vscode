{
    use_fd = pipes[fd][1];

    if (use_fd >= stdio_count)
      uv__close(use_fd);
  }