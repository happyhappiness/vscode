virtual void Broadcast(void *sendrecvbuf_, size_t total_size, int root) {
    if (world_size == 1) return;
    utils::Assert(TryBroadcast(sendrecvbuf_, total_size, root) == kSuccess,
                  "Broadcast failed");
  }