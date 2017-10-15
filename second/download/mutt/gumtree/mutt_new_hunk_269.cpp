    /* manual page */
    case F_MAN:
    {
      fprintf (out, "\n.TP\n.B %s\n", varname);
      fputs (".nf\n", out);
      fprintf (out, "Type: %s\n", type2human (type));
      if (type == DT_STR || type == DT_RX || type == DT_ADDR || type == DT_PATH ||
          type == DT_MBCHARTBL)
      {
	fputs ("Default: \\(lq", out);
	man_print_strval (val, out);
	fputs ("\\(rq\n", out);
      }
      else {
