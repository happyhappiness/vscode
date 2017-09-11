                        // linear boost automatically set do reboost
                        if (booster_type == 1) do_reboost = 1;
                    }
                    if (!strcmp("num_pbuffer", name))      num_pbuffer = atoi(val);
                    if (!strcmp("do_reboost", name))       do_reboost = atoi(val);
                    if (!strcmp("bst:num_roots", name))    num_roots = atoi(val);
                    if (!strcmp("bst:num_feature", name))  num_feature = atoi(val);
                }
            };
            /*! \brief training parameters */
