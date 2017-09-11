    printf("Finishing writing to %s\n", name_pred.c_str());
  }
  inline void LoadModel(const char *fname) {
    FILE *fp = utils::FopenCheck(fname, "rb");
    std::string header; header.resize(4);
    // check header for different binary encode
    // can be base64 or binary
    utils::FileStream fi(fp);
    utils::Check(fi.Read(&header[0], 4) != 0, "invalid model");
      // base64 format
    if (header == "bs64") {
      utils::Base64InStream bsin(fp);
      bsin.InitPosition();
      model.Load(bsin);
      fclose(fp);
      return;
    } else if (header == "binf") {
      model.Load(fi);
      fclose(fp);
      return;     
    } else {
      utils::Error("invalid model file");
    }
  }
  inline void SaveModel(const char *fname,
                        const float *wptr,
                        bool save_base64 = false) {
    FILE *fp;
    bool use_stdout = false;
    if (!strcmp(fname, "stdout")) {
      fp = stdout;
      use_stdout = true;
    } else {
      fp = utils::FopenCheck(fname, "wb");
   }
    utils::FileStream fo(fp);
    if (save_base64 != 0|| use_stdout) {
      fo.Write("bs64\t", 5);
      utils::Base64OutStream bout(fp);
      model.Save(bout, wptr);
      bout.Finish('\n');
    } else {
      fo.Write("binf", 4);
      model.Save(fo, wptr);
    }
    if (!use_stdout) {
      fclose(fp);
    }
  }
  inline void LoadData(const char *fname) {
    dtrain.Load(fname);
