      if (save_period != 0 && (i + 1) % save_period == 0) {
        this->SaveModel(i);
      }
      if (allow_lazy) {
        rabit::LazyCheckPoint(&learner);
      } else {
        rabit::CheckPoint(&learner);
      }
      version += 1;
      utils::Assert(version == rabit::VersionNumber(), "consistent check");
      elapsed = (unsigned long)(time(NULL) - start);
    }
    // always save final round
