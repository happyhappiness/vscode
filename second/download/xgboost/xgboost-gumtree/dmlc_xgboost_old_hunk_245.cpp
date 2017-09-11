      }
      version += 1;
      utils::Assert(version == rabit::VersionNumber(), "consistent check");
      elapsed = (unsigned long)(time(NULL) - start);
    }
    // always save final round
    if ((save_period == 0 || num_round % save_period != 0) && model_out != "NONE") {
      if (model_out == "NULL"){
        this->SaveModel(num_round - 1);
      } else {
        this->SaveModel(model_out.c_str());
      }
    }
    if (!silent){
      printf("\nupdating end, %lu sec in all\n", elapsed);
    }
  }
  inline void TaskEval(void) {
    learner.EvalOneIter(0, devalall, eval_data_names);
  }
  inline void TaskDump(void){
    FILE *fo = utils::FopenCheck(name_dump.c_str(), "w");
    std::vector<std::string> dump = learner.DumpModel(fmap, dump_model_stats != 0);
    for (size_t i = 0; i < dump.size(); ++ i) {
      fprintf(fo,"booster[%lu]:\n", i);
      fprintf(fo,"%s", dump[i].c_str()); 
    }
    fclose(fo);
  }
