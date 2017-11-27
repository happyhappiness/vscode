static int mic_read_memory(int mic) {
  U32 ret;
  U32 mem_total, mem_free, mem_bufs;

  ret = MicGetMemoryUtilization(mic_handle, &mem_total, &mem_free, &mem_bufs);
  if (ret != MIC_ACCESS_API_SUCCESS) {
    ERROR("mic plugin: Problem getting Memory Utilization: %s",
          MicGetErrorString(ret));
    return (1);
  }
  mic_submit_memory_use(mic, "free", mem_free);
  mic_submit_memory_use(mic, "used", mem_total - mem_free - mem_bufs);
  mic_submit_memory_use(mic, "buffered", mem_bufs);
  DEBUG("mic plugin: Memory Read: %u %u %u", mem_total, mem_free, mem_bufs);
  return (0);
}