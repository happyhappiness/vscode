static int patmatch (const pattern_t* pat, const char* buf)
{
  if (pat->stringmatch)
    return pat->ign_case ? !strcasestr (buf, pat->p.str) :
			   !strstr (buf, pat->p.str);
  else if (pat->groupmatch)
    return !mutt_group_match (pat->p.g, buf);
  else
    return regexec (pat->p.rx, buf, 0, NULL, 0);
}