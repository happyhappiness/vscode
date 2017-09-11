      if (save_period != 0 && (i + 1) % save_period == 0) {
        this->SaveModel(i);
      }
      utils::Assert(rabit::VersionNumber() == i, "incorrect version number");
      // checkpoint the model
      rabit::CheckPoint(&learner);
      elapsed = (unsigned long)(time(NULL) - start);
    }
    // always save final round
