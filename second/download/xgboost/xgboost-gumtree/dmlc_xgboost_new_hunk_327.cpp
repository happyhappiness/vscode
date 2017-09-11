    printf("Finishing writing to %s\n", name_pred.c_str());
  }
  inline void LoadModel(const char *fname) {
    IStream *fi = io::CreateStream(fname, "r");
    std::string header; header.resize(4);
    // check header for different binary encode
    // can be base64 or binary
    utils::Check(fi->Read(&header[0], 4) != 0, "invalid model");
    // base64 format
    if (header == "bs64") {
      io::Base64InStream bsin(fi);
      bsin.InitPosition();
      model.Load(bsin);
    } else if (header == "binf") {
      model.Load(*fi);
    } else {
      utils::Error("invalid model file");
    }
    delete fi;
  }
  inline void SaveModel(const char *fname,
                        const float *wptr,
                        bool save_base64 = false) {
    IStream *fo = io::CreateStream(fname, "w");
    if (save_base64 != 0 || !strcmp(fname, "stdout")) {
      fo->Write("bs64\t", 5);
      io::Base64OutStream bout(fo);
      model.Save(bout, wptr);
      bout.Finish('\n');
    } else {
      fo->Write("binf", 4);
      model.Save(*fo, wptr);
    }
    delete fo;
  }
  inline void LoadData(const char *fname) {
    dtrain.Load(fname);
