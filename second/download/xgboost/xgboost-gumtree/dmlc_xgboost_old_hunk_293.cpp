    } else {
      utils::Assert(fs.Read(&version_number, sizeof(version_number)) != 0,
                    "read in version number");
      global_model->Load(fs);
      utils::Assert(local_model == NULL || nlocal == num_local_replica + 1,
                    "local model inconsistent, nlocal=%d", nlocal);
    }
