cmd_error(CMD_OK, &err, "Success: %i %s been dispatched.",
              (int)cmd.cmd.putval.vl_num,
              (cmd.cmd.putval.vl_num == 1) ? "value has" : "values have");