      }
      utils::Assert(version == rabit::VersionNumber(), "consistent check");
      std::string res = learner.EvalOneIter(i, devalall, eval_data_names);
      if (rabit::IsDistributed()) {
        if (rabit::GetRank() == 0) {
          rabit::TrackerPrintf("%s\n", res.c_str());
        }
