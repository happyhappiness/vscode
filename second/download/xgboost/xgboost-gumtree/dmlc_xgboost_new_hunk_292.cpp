        // load in local model
        utils::MemoryFixSizeBuffer fs(BeginPtr(local_chkpt[local_chkpt_version]),
                                      local_rptr[local_chkpt_version][1]);
        local_model->Load(&fs);
      } else {
        utils::Assert(nlocal == 0, "[%d] local model inconsistent, nlocal=%d", rank, nlocal);
      }
