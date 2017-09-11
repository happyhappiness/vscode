  if (!strcmp(name, "rabit_task_id")) task_id = val;
  if (!strcmp(name, "rabit_world_size")) world_size = atoi(val);
  if (!strcmp(name, "rabit_hadoop_mode")) hadoop_mode = atoi(val);
  if (!strcmp(name, "rabit_reduce_ring_mincount")) {
    reduce_ring_mincount = ParseUnit(name, val);
  }
  if (!strcmp(name, "rabit_reduce_buffer")) {
    reduce_buffer_size = (ParseUnit(name, val) + 7) >> 3;
  }
}
/*!
