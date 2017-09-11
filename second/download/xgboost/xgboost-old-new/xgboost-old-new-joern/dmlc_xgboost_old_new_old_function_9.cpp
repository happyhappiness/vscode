inline void LoadModel(utils::IStream &fi) { // NOLINT(*)
      utils::Assert(fi.Read(&param, sizeof(Param)) != 0, "Load LinearBooster");
      fi.Read(&weight)