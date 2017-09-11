    std::vector<float> preds;
    if (!silent) printf("start prediction...\n");
    learner.Predict(*data, pred_margin != 0, &preds, ntree_limit);
    if (!silent) printf("writing prediction to %s\n", name_pred.c_str());    
    FILE *fo;
    if (name_pred != "stdout") {
      fo = utils::FopenCheck(name_pred.c_str(), "w");
    } else {
      fo = stdout;
    }
    for (size_t i = 0; i < preds.size(); ++i) {
      fprintf(fo, "%g\n", preds[i]);
    }
    if (fo != stdout) fclose(fo);
  }
 private:
  /*! \brief whether silent */
