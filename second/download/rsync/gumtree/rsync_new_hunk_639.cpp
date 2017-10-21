		}
	}
	rprintf(FINFO, "\n");
}


void out_of_memory(char *str)
{
  rprintf(FERROR,"ERROR: out of memory in %s\n",str);
  exit_cleanup(RERR_MALLOC);
}

