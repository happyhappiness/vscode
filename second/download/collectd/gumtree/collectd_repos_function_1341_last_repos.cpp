static int c_grpc_shutdown(void) {
  if (!server)
    return 0;

  server->Shutdown();

  delete server;
  server = nullptr;

  return 0;
}