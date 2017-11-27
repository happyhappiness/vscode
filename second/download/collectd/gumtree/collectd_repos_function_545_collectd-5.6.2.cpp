static double averaging_add_sample(averaging_t *avg, long int sample) {
  double result;

  avg->ring_buffer_sum += sample - avg->ring_buffer[avg->ring_buffer_head];
  avg->ring_buffer[avg->ring_buffer_head] = sample;
  avg->ring_buffer_head = (avg->ring_buffer_head + 1) % avg->ring_buffer_size;
  result = (double)(avg->ring_buffer_sum) / (double)(avg->ring_buffer_size);

  DEBUG("barometer: averaging_add_sample - added %ld, result = %lf", sample,
        result);

  return result;
}