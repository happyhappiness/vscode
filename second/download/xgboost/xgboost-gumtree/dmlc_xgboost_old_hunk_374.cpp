    std::vector<float> preds;
    if (!silent) printf("start prediction...\n");
    learner.Predict(*data, pred_margin != 0, &preds, ntree_limit);
    if (!silent) printf("writing prediction to %s\n", name_pred.c_str());
    FILE *fo = utils::FopenCheck(name_pred.c_str(), "w");
    for (size_t i = 0; i < preds.size(); i++) {
      fprintf(fo, "%f\n", preds[i]);
    }
    fclose(fo);
  }
 private:
  /*! \brief whether silent */
