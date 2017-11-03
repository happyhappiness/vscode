bool
SCgi::receive_call(SCgiTask* task, const char* buffer, uint32_t length) {
  slot_write slotWrite;
  slotWrite.set(rak::mem_fn(task, &SCgiTask::receive_write));

  return m_slotProcess(buffer, length, slotWrite);
}