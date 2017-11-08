static void decc_init(void)
{
  int feat_index;
  int feat_value;
  int feat_value_max;
  int feat_value_min;
  int i;
  int sts;

  /* Set the global flag to indicate that LIB$INITIALIZE worked. */
  decc_init_done = 1;

  /* Loop through all items in the decc_feat_array[]. */
  for(i = 0; decc_feat_array[i].name != NULL; i++) {

    /* Get the feature index. */
    feat_index = decc$feature_get_index(decc_feat_array[i].name);

    if(feat_index >= 0) {
      /* Valid item.  Collect its properties. */
      feat_value = decc$feature_get_value(feat_index, 1);
      feat_value_min = decc$feature_get_value(feat_index, 2);
      feat_value_max = decc$feature_get_value(feat_index, 3);

      if((decc_feat_array[i].value >= feat_value_min) &&
         (decc_feat_array[i].value <= feat_value_max)) {
        /* Valid value.  Set it if necessary. */
        if(feat_value != decc_feat_array[i].value) {
          sts = decc$feature_set_value(feat_index, 1,
                                       decc_feat_array[i].value);
        }
      }
      else {
        /* Invalid DECC feature value. */
        printf(" INVALID DECC FEATURE VALUE, %d: %d <= %s <= %d.\n",
               feat_value,
               feat_value_min, decc_feat_array[i].name, feat_value_max);
      }
    }
    else {
      /* Invalid DECC feature name. */
      printf(" UNKNOWN DECC FEATURE: %s.\n", decc_feat_array[i].name);
    }

  }
}