    if (header == "bs64") {
      io::Base64InStream bsin(fi);
      bsin.InitPosition();
      model.Load(bsin);
    } else if (header == "binf") {
      model.Load(*fi);
    } else {
      utils::Error("invalid model file");
    }
