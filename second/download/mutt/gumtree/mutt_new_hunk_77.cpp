	if (hdr->env->return_path)
	  p = hdr->env->return_path;
	else if (hdr->env->sender)
	  p = hdr->env->sender;
	else
	  p = hdr->env->from;
      }

      fprintf (msg->fp, "From %s %s", p ? p->mailbox : NONULL(Username), ctime (&msg->received));
    }
  }
  else
    FREE (&msg);

  return msg;
}

/* check for new mail */
int mx_check_mailbox (CONTEXT *ctx, int *index_hint, int lock)
