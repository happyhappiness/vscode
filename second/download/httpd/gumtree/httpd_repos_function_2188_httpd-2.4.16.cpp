static int _advance(char *lp, char *ep, step_vars_storage *vars)
{
    char *curlp;
    int c;
    char *bbeg;
    char neg;
    int ct;
    int epint; /* int value of *ep */

    while (1) {
        neg = 0;
        switch (*ep++) {

        case CCHR:
            if (*ep++ == *lp++)
                continue;
            return (0);

        case CDOT:
            if (*lp++)
                continue;
            return (0);

        case CDOL:
            if (*lp == 0)
                continue;
            return (0);

        case CCEOF:
            vars->loc2 = lp;
            return (1);

        case CXCL:
            c = (unsigned char)*lp++;
            if (ISTHERE(c)) {
                ep += 32;
                continue;
            }
            return (0);

        case NCCL:
            neg = 1;

        case CCL:
            c = *lp++;
            if (((c & 0200) == 0 && ISTHERE(c)) ^ neg) {
                ep += 16;
                continue;
            }
            return (0);

        case CBRA:
            epint = (int) *ep;
            vars->braslist[epint] = lp;
            ep++;
            continue;

        case CKET:
            epint = (int) *ep;
            vars->braelist[epint] = lp;
            ep++;
            continue;

        case CCHR | RNGE:
            c = *ep++;
            getrnge(ep, vars);
            while (vars->low--)
                if (*lp++ != c)
                    return (0);
            curlp = lp;
            while (vars->size--)
                if (*lp++ != c)
                    break;
            if (vars->size < 0)
                lp++;
            ep += 2;
            goto star;

        case CDOT | RNGE:
            getrnge(ep, vars);
            while (vars->low--)
                if (*lp++ == '\0')
                    return (0);
            curlp = lp;
            while (vars->size--)
                if (*lp++ == '\0')
                    break;
            if (vars->size < 0)
                lp++;
            ep += 2;
            goto star;

        case CXCL | RNGE:
            getrnge(ep + 32, vars);
            while (vars->low--) {
                c = (unsigned char)*lp++;
                if (!ISTHERE(c))
                    return (0);
            }
            curlp = lp;
            while (vars->size--) {
                c = (unsigned char)*lp++;
                if (!ISTHERE(c))
                    break;
            }
            if (vars->size < 0)
                lp++;
            ep += 34;        /* 32 + 2 */
            goto star;

        case NCCL | RNGE:
            neg = 1;

        case CCL | RNGE:
            getrnge(ep + 16, vars);
            while (vars->low--) {
                c = *lp++;
                if (((c & 0200) || !ISTHERE(c)) ^ neg)
                    return (0);
            }
            curlp = lp;
            while (vars->size--) {
                c = *lp++;
                if (((c & 0200) || !ISTHERE(c)) ^ neg)
                    break;
            }
            if (vars->size < 0)
                lp++;
            ep += 18;         /* 16 + 2 */
            goto star;

        case CBACK:
            epint = (int) *ep;
            bbeg = vars->braslist[epint];
            ct = vars->braelist[epint] - bbeg;
            ep++;

            if (ecmp(bbeg, lp, ct)) {
                lp += ct;
                continue;
            }
            return (0);

        case CBACK | STAR:
            epint = (int) *ep;
            bbeg = vars->braslist[epint];
            ct = vars->braelist[epint] - bbeg;
            ep++;
            curlp = lp;
            while (ecmp(bbeg, lp, ct))
                lp += ct;

            while (lp >= curlp) {
                if (_advance(lp, ep, vars))
                    return (1);
                lp -= ct;
            }
            return (0);


        case CDOT | STAR:
            curlp = lp;
            while (*lp++);
            goto star;

        case CCHR | STAR:
            curlp = lp;
            while (*lp++ == *ep);
            ep++;
            goto star;

        case CXCL | STAR:
   