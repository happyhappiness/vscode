static int read_acpi(void) /* {{{ */
{
  int status;
  int battery_counter = 0;

  if (access(PROC_ACPI_PATH, R_OK) != 0)
    return ENOENT;

  status = walk_directory(PROC_ACPI_PATH, read_acpi_callback,
                          /* user_data = */ &battery_counter,
                          /* include hidden */ 0);
  return status;
}