int fc_process_chain (const data_set_t *ds, value_list_t *vl, /* {{{ */
    fc_chain_t *chain)
{
  fc_rule_t *rule;
  fc_target_t *target;
  int status;

  if (chain == NULL)
    return (-1);

  DEBUG ("fc_process_chain (chain = %s);", chain->name);

  status = FC_TARGET_CONTINUE;
  for (rule = chain->rules; rule != NULL; rule = rule->next)
  {
    fc_match_t *match;

    if (rule->name[0] != 0)
    {
      DEBUG ("fc_process_chain (%s): Testing the `%s' rule.",
          chain->name, rule->name);
    }

    /* N. B.: rule->matches may be NULL. */
    for (match = rule->matches; match != NULL; match = match->next)
    {
      /* FIXME: Pass the meta-data to match targets here (when implemented). */
      status = (*match->proc.match) (ds, vl, /* meta = */ NULL,
          &match->user_data);
      if (status < 0)
      {
        WARNING ("fc_process_chain (%s): A match failed.", chain->name);
        break;
      }
      else if (status != FC_MATCH_MATCHES)
        break;
    }

    /* for-loop has been aborted: Either error or no match. */
    if (match != NULL)
    {
      status = FC_TARGET_CONTINUE;
      continue;
    }

    if (rule->name[0] != 0)
    {
      DEBUG ("fc_process_chain (%s): Rule `%s' matches.",
          chain->name, rule->name);
    }

    for (target = rule->targets; target != NULL; target = target->next)
    {
      /* If we get here, all matches have matched the value. Execute the
       * target. */
      /* FIXME: Pass the meta-data to match targets here (when implemented). */
      status = (*target->proc.invoke) (ds, vl, /* meta = */ NULL,
          &target->user_data);
      if (status < 0)
      {
        WARNING ("fc_process_chain (%s): A target failed.", chain->name);
        continue;
      }
      else if (status == FC_TARGET_CONTINUE)
        continue;
      else if (status == FC_TARGET_STOP)
        break;
      else if (status == FC_TARGET_RETURN)
        break;
      else
      {
        WARNING ("fc_process_chain (%s): Unknown return value "
            "from target `%s': %i",
            chain->name, target->name, status);
      }
    }

    if ((status == FC_TARGET_STOP)
        || (status == FC_TARGET_RETURN))
    {
      if (rule->name[0] != 0)
      {
        DEBUG ("fc_process_chain (%s): Rule `%s' signaled "
            "the %s condition.",
            chain->name, rule->name,
            (status == FC_TARGET_STOP) ? "stop" : "return");
      }
      break;
    }
    else
    {
      status = FC_TARGET_CONTINUE;
    }
  } /* for (rule) */

  if (status == FC_TARGET_STOP)
    return (FC_TARGET_STOP);
  else if (status == FC_TARGET_RETURN)
    return (FC_TARGET_CONTINUE);

  /* for-loop has been aborted: A target returned `FC_TARGET_STOP' */
  if (rule != NULL)
    return (FC_TARGET_CONTINUE);

  DEBUG ("fc_process_chain (%s): Executing the default targets.",
      chain->name);

  status = FC_TARGET_CONTINUE;
  for (target = chain->targets; target != NULL; target = target->next)
  {
    /* If we get here, all matches have matched the value. Execute the
     * target. */
    /* FIXME: Pass the meta-data to match targets here (when implemented). */
    status = (*target->proc.invoke) (ds, vl, /* meta = */ NULL,
        &target->user_data);
    if (status < 0)
    {
      WARNING ("fc_process_chain (%s): The default target failed.",
          chain->name);
    }
    else if (status == FC_TARGET_CONTINUE)
      continue;
    else if (status == FC_TARGET_STOP)
      break;
    else if (status == FC_TARGET_RETURN)
      break;
    else
    {
      WARNING ("fc_process_chain (%s): Unknown return value "
          "from target `%s': %i",
          chain->name, target->name, status);
    }
  }

  if ((status == FC_TARGET_STOP)
      || (status == FC_TARGET_RETURN))
  {
    assert (target != NULL);
    DEBUG ("fc_process_chain (%s): Default target `%s' signaled "
        "the %s condition.",
        chain->name, target->name,
        (status == FC_TARGET_STOP) ? "stop" : "return");
    if (status == FC_TARGET_STOP)
      return (FC_TARGET_STOP);
    else
      return (FC_TARGET_CONTINUE);
  }

  DEBUG ("fc_process_chain (%s): Signaling `continue' at end of chain.",
      chain->name);

  return (FC_TARGET_CONTINUE);
}