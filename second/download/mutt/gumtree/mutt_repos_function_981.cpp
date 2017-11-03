void mutt_attach_forward (FILE * fp, HEADER * hdr, 
			  ATTACHPTR ** idx, short idxlen, BODY * cur)
{
  short nattach;
  

  if (check_all_msg (idx, idxlen, cur, 0) == 0)
    attach_forward_msgs (fp, hdr, idx, idxlen, cur);
  else
  {
    nattach = count_tagged (idx, idxlen);
    attach_forward_bodies (fp, hdr, idx, idxlen, cur, nattach);
  }
}