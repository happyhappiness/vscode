static void agg_instance_destroy (agg_instance_t *inst) /* {{{ */
{
  if (inst == NULL)
    return;

  /* Remove this instance from the global list of instances. */
  pthread_mutex_lock (&agg_instance_list_lock);
  if (agg_instance_list_head == inst)
    agg_instance_list_head = inst->next;
  else if (agg_instance_list_head != NULL)
  {
    agg_instance_t *prev = agg_instance_list_head;
    while ((prev != NULL) && (prev->next != inst))
      prev = prev->next;
    if (prev != NULL)
      prev->next = inst->next;
  }
  pthread_mutex_unlock (&agg_instance_list_lock);

  sfree (inst->state_num);
  sfree (inst->state_sum);
  sfree (inst->state_average);
  sfree (inst->state_min);
  sfree (inst->state_max);
  sfree (inst->state_stddev);

  memset (inst, 0, sizeof (*inst));
  inst->ds_type = -1;
  inst->min = NAN;
  inst->max = NAN;
}