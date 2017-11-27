static int averaging_create(averaging_t *avg, int size) {
  avg->ring_buffer = calloc((size_t)size, sizeof(*avg->ring_buffer));
  if (avg->ring_buffer == NULL) {
    ERROR("barometer: averaging_create - ring buffer allocation of size %d "
          "failed",
          size);
    return -1;
  }

  avg->ring_buffer_size = size;
  avg->ring_buffer_sum = 0L;
  avg->ring_buffer_head = 0;

  return 0;
}