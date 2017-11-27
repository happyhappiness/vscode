static int mic_init(void) {
  U32 ret;
  U32 mic_count;

  if (mic_handle)
    return 0;

  mic_count = (U32)STATIC_ARRAY_SIZE(mics);
  ret = MicInitAPI(&mic_handle, eTARGET_SCIF_DRIVER, mics, &mic_count);
  if (ret != MIC_ACCESS_API_SUCCESS) {
    ERROR("mic plugin: Problem initializing MicAccessAPI: %s",
          MicGetErrorString(ret));
  }
  DEBUG("mic plugin: found: %" PRIu32 " MIC(s)", mic_count);

  if (mic_count < 0 || mic_count >= MAX_MICS) {
    ERROR("mic plugin: No Intel MICs in system");
    return 1;
  } else {
    num_mics = mic_count;
    return 0;
  }
}