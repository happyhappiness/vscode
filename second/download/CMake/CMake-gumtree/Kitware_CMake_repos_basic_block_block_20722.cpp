{
    /* Clean up child stdio handles. */
    uv__stdio_destroy(process->child_stdio_buffer);
    process->child_stdio_buffer = NULL;
  }