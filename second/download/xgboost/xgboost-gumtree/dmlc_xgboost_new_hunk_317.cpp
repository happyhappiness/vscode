      train_path = s_tmp;
      load_part = 1;
    }
    bool loadsplit = data_split == "row";
    if (name_fmap != "NULL") fmap.LoadText(name_fmap.c_str());
    if (task == "dump") return;
    if (task == "pred") {
      data = io::LoadDataMatrix(test_path.c_str(), silent != 0, use_buffer != 0, loadsplit);
    } else {
      // training
      data = io::LoadDataMatrix(train_path.c_str(),
                                silent != 0 && load_part == 0,
                                use_buffer != 0, loadsplit);
      utils::Assert(eval_data_names.size() == eval_data_paths.size(), "BUG");
      for (size_t i = 0; i < eval_data_names.size(); ++i) {
        deval.push_back(io::LoadDataMatrix(eval_data_paths[i].c_str(),
                                           silent != 0,
                                           use_buffer != 0,
                                           loadsplit));
        devalall.push_back(deval.back());
      }
            
