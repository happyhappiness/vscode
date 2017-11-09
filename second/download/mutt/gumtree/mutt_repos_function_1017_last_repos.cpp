void mutt_attach_forward (FILE * fp, HEADER * hdr, 
			  ATTACH_CONTEXT *actx, BODY * cur)
{
  short nattach;
  

  if (check_all_msg (actx, cur, 0) == 0)
    attach_forward_msgs (fp, hdr, actx, cur);
  else
  {
    nattach = count_tagged (actx);
    attach_forward_bodies (fp, hdr, actx, cur, nattach);
  }
}