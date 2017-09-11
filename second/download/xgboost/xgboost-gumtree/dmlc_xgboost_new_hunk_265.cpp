  if (!strcmp(name, "merror")) return new EvalMatchError();
  if (!strcmp(name, "logloss")) return new EvalLogLoss();
  if (!strcmp(name, "mlogloss")) return new EvalMultiLogLoss();
  if (!strcmp(name, "poisson-nloglik")) return new EvalPoissionNegLogLik();
  if (!strcmp(name, "auc")) return new EvalAuc();
  if (!strncmp(name, "ams@", 4)) return new EvalAMS(name);
  if (!strncmp(name, "pre@", 4)) return new EvalPrecision(name);
