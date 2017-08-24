{
    model = uv__strndup(inferred_model, strlen(inferred_model));
    if (model == NULL)
      return -ENOMEM;
    ci[model_idx++].model = model;
  }