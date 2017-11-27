static void format_protobuf(ProtobufCBuffer *buffer) {
  pthread_mutex_lock(&metrics_lock);

  char *unused_name;
  Io__Prometheus__Client__MetricFamily *fam;
  c_avl_iterator_t *iter = c_avl_get_iterator(metrics);
  while (c_avl_iterator_next(iter, (void *)&unused_name, (void *)&fam) == 0) {
    /* Prometheus uses a message length prefix to determine where one
     * MetricFamily ends and the next begins. This delimiter is encoded as a
     * "varint", which is common in Protobufs. */
    uint8_t delim[VARINT_UINT32_BYTES] = {0};
    size_t delim_len = varint(
        delim,
        (uint32_t)io__prometheus__client__metric_family__get_packed_size(fam));
    buffer->append(buffer, delim_len, delim);

    io__prometheus__client__metric_family__pack_to_buffer(fam, buffer);
  }
  c_avl_iterator_destroy(iter);

  pthread_mutex_unlock(&metrics_lock);
}