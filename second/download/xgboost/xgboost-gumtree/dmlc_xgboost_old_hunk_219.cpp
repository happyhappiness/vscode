  if (!strcmp("multi:softprob", name)) return new SoftmaxMultiClassObj(1);
  if (!strcmp("rank:pairwise", name )) return new PairwiseRankObj();
  if (!strcmp("rank:ndcg", name)) return new LambdaRankObjNDCG();
  if (!strcmp("rank:map", name)) return new LambdaRankObjMAP();  
  utils::Error("unknown objective function type: %s", name);
  return NULL;
}
