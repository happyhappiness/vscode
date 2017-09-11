    } else {
      // training
      data = io::LoadDataMatrix(train_path.c_str(), silent != 0, use_buffer != 0);
      utils::Assert(eval_data_names.size() == eval_data_paths.size(), "BUG");
      for (size_t i = 0; i < eval_data_names.size(); ++i) {
        deval.push_back(io::LoadDataMatrix(eval_data_paths[i].c_str(), silent != 0, use_buffer != 0));
