(cp_times == NULL) {
    uv__free(*cpu_infos);
    return -ENOMEM;
  }