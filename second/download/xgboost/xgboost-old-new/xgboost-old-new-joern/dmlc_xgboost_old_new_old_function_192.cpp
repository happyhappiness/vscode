void AllreduceBase::SetParam(const char *name, const char *val) {
  if (!strcmp(name, "rabit_tracker_uri")) tracker_uri = val;
  if (!strcmp(name, "rabit_tracker_port")) tracker_port = atoi(val);
  if (!strcmp(name, "rabit_task_id")) task_id = val;
  if (!strcmp(name, "rabit_world_size")) world_size = atoi(val);
  if (!strcmp(name, "rabit_hadoop_mode")) hadoop_mode = atoi(val);
  if (!strcmp(name, "rabit_reduce_buffer")) {
    char unit;
    uint64_t amount;
    if (sscanf(val, "%lu%c", &amount, &unit) == 2) {
      switch (unit) {
        case 'B': reduce_buffer_size = (amount + 7)/ 8; break;
        case 'K': reduce_buffer_size = amount << 7UL; break;
        case 'M': reduce_buffer_size = amount << 17UL; break;
        case 'G': reduce_buffer_size = amount << 27UL; break;
        default: utils::Error("invalid format for reduce buffer");
      }
    } else {
      utils::Error("invalid format for reduce_buffer,"\
                   "shhould be {integer}{unit}, unit can be {B, KB, MB, GB}");
    }
  }
}