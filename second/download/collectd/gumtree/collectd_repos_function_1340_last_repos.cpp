static int c_grpc_init(void) {
  server = new CollectdServer();
  if (!server) {
    ERROR("grpc: Failed to create server");
    return -1;
  }

  server->Start();
  return 0;
}