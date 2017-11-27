static void c_grpc_destroy_write_callback (void *ptr) {
		delete (CollectdClient *) ptr;
	}