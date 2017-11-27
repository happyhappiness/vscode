static int mic_read_temps(int mic) {
  size_t num_therms = STATIC_ARRAY_SIZE(therm_ids);

  for (size_t j = 0; j < num_therms; j++) {
    U32 status;
    U32 temp_buffer;
    U32 buffer_size = (U32)sizeof(temp_buffer);
    char const *name = therm_names[j];

    if (ignorelist_match(temp_ignore, name) != 0)
      continue;

    status =
        MicGetTemperature(mic_handle, therm_ids[j], &temp_buffer, &buffer_size);
    if (status != MIC_ACCESS_API_SUCCESS) {
      ERROR("mic plugin: Error reading temperature \"%s\": "
            "%s",
            name, MicGetErrorString(status));
      return 1;
    }
    mic_submit_temp(mic, name, temp_buffer);
  }
  return 0;
}