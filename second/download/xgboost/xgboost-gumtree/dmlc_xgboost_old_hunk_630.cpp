  if (!strcmp(name, "merror")) return new EvalMatchError();
  if (!strcmp(name, "logloss")) return new EvalLogLoss();
  if (!strcmp(name, "auc")) return new EvalAuc();
  if (!strncmp(name, "ams@",4)) return new EvalAMS(name);
  if (!strncmp(name, "pre@", 4)) return new EvalPrecision(name);
  if (!strncmp(name, "map", 3)) return new EvalMAP(name);
  if (!strncmp(name, "ndcg", 3)) return new EvalNDCG(name);
