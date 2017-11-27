    else
      num_okay++;
  }

  if ((num_critical == 0) && (num_warning == 0) && (num_okay == 0)) {
    printf("WARNING: No defined values found\n");
    return RET_WARNING;
  } else if ((num_critical == 0) && (num_warning == 0)) {
    status_str = "OKAY";
    status_code = RET_OKAY;
  } else if (num_critical == 0) {
    status_str = "WARNING";
    status_code = RET_WARNING;
