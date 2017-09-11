      if (!silent) printf("boosting round %d, %lu sec elapsed\n", i, elapsed);
      learner.UpdateOneIter(i, *data); 
      std::string res = learner.EvalOneIter(i, devalall, eval_data_names);
      if (silent < 1) {
        fprintf(stderr, "%s\n", res.c_str());
      }
      if (save_period != 0 && (i + 1) % save_period == 0) {
        this->SaveModel(i);
      }
