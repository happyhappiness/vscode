{
    va_list var_args;
    va_start(var_args, format);
    vfprintf(stream, format, var_args);
    va_end(var_args);
  }