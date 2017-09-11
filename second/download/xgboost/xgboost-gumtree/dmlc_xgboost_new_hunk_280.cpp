      this->SetParam("rabit_world_size", num_task);
    }
  }
  if (dmlc_role != "worker") {
    fprintf(stderr, "Rabit Module currently only work with dmlc worker, quit this program by exit 0\n");
    exit(0);
  }
  // clear the setting before start reconnection
  this->rank = -1;
  //---------------------
