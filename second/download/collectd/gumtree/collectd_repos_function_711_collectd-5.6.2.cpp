static int mic_read(void) {
  U32 ret;
  int error;

  error = 0;
  for (int i = 0; i < num_mics; i++) {
    ret = MicInitAdapter(&mic_handle, &mics[i]);
    if (ret != MIC_ACCESS_API_SUCCESS) {
      ERROR("mic plugin: Problem initializing MicAdapter: %s",
            MicGetErrorString(ret));
      error = 1;
    }

    if (error == 0 && show_memory)
      error = mic_read_memory(i);

    if (error == 0 && show_temps)
      error = mic_read_temps(i);

    if (error == 0 && (show_cpu || show_cpu_cores))
      error = mic_read_cpu(i);

    if (error == 0 && (show_power))
      error = mic_read_power(i);

    ret = MicCloseAdapter(mic_handle);
    if (ret != MIC_ACCESS_API_SUCCESS) {
      ERROR("mic plugin: Problem closing MicAdapter: %s",
            MicGetErrorString(ret));
      error = 2;
      break;
    }
  }
  if (num_mics == 0)
    error = 3;
  return error;
}