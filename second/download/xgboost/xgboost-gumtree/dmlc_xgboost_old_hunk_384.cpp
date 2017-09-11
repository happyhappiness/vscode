      if (save_period != 0 && (i + 1) % save_period == 0) {
        this->SaveModel(i);
      }
      elapsed = (unsigned long)(time(NULL) - start);
    }
    // always save final round
