
XGBOOST_REGISTER_METRIC(Error, "error")
.describe("Binary classification error.")
.set_body([](const char* param) { return new EvalError(); });

XGBOOST_REGISTER_METRIC(PossionNegLoglik, "poisson-nloglik")
.describe("Negative loglikelihood for poisson regression.")
