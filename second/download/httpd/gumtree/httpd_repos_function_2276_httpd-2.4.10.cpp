static int fcomp(sed_commands_t *commands, apr_file_t *fin)
{
    char *p, *op, *tp;
    sed_reptr_t *pt, *pt1;
    int i, ii;
    sed_label_t *lpt;
    char fnamebuf[APR_PATH_MAX];
    apr_status_t status;
    sed_comp_args compargs;

    op = commands->lastre;
    if (!commands->linebuf) {
        commands->linebuf = apr_pcalloc(commands->pool, LBSIZE + 1);
    }

    if (rline(commands, fin, commands->linebuf,
              (commands->linebuf + LBSIZE + 1)) < 0)
        return 0;
    if (*commands->linebuf == '#') {
        if (commands->linebuf[1] == 'n')
            commands->nflag = 1;
    }
    else {
        commands->cp = commands->linebuf;
        goto comploop;
    }

    for (;;) {
        if (rline(commands, fin, commands->linebuf,
                  (commands->linebuf + LBSIZE + 1)) < 0)
            break;

        commands->cp = commands->linebuf;

comploop:
        while (*commands->cp == ' ' || *commands->cp == '\t')
            commands->cp++;
        if (*commands->cp == '\0' || *commands->cp == '#')
            continue;
        if (*commands->cp == ';') {
            commands->cp++;
            goto comploop;
        }

        p = address(commands, commands->rep->ad1, &status);
        if (status != APR_SUCCESS) {
            command_errf(commands, SEDERR_CGMES, commands->linebuf);
            return -1;
        }

        if (p == commands->rep->ad1) {
            if (op)
                commands->rep->ad1 = op;
            else {
                command_errf(commands, SEDERR_NRMES);
                return -1;
            }
        } else if (p == 0) {
            p = commands->rep->ad1;
            commands->rep->ad1 = 0;
        } else {
            op = commands->rep->ad1;
            if (*commands->cp == ',' || *commands->cp == ';') {
                commands->cp++;
                commands->rep->ad2 = p;
                p = address(commands, commands->rep->ad2, &status);
                if ((status != APR_SUCCESS) || (p == 0)) {
                    command_errf(commands, SEDERR_CGMES, commands->linebuf);
                    return -1;
                }
                if (p == commands->rep->ad2)
                    commands->rep->ad2 = op;
                else
                    op = commands->rep->ad2;
            } else
                commands->rep->ad2 = 0;
        }

        if(p > &commands->respace[RESIZE-1]) {
            command_errf(commands, SEDERR_TMMES, commands->linebuf);
            return -1;
        }

        while (*commands->cp == ' ' || *commands->cp == '\t')
            commands->cp++;

swit:
        switch(*commands->cp++) {
        default:
            command_errf(commands, SEDERR_UCMES, commands->linebuf);
            return -1;

        case '!':
            commands->rep->negfl = 1;
            goto swit;

        case '{':
            commands->rep->command = BCOM;
            commands->rep->negfl = !(commands->rep->negfl);
            commands->cmpend[commands->depth++] = &commands->rep->lb1;
            commands->rep = alloc_reptr(commands);
            commands->rep->ad1 = p;
            if (*commands->cp == '\0')
                continue;
            goto comploop;

        case '}':
            if (commands->rep->ad1) {
                command_errf(commands, SEDERR_AD0MES, commands->linebuf);
                return -1;
            }

            if (--commands->depth < 0) {
                command_errf(commands, SEDERR_TMCMES);
                return -1;
            }
            *commands->cmpend[commands->depth] = commands->rep;

            commands->rep->ad1 = p;
            continue;

        case '=':
            commands->rep->command = EQCOM;
            if (commands->rep->ad2) {
                command_errf(commands, SEDERR_AD1MES, commands->linebuf);
                return -1;
            }
            break;

        case ':':
            if (commands->rep->ad1) {
                command_errf(commands, SEDERR_AD0MES, commands->linebuf);
                return -1;
            }

            while (*commands->cp++ == ' ');
            commands->cp--;

            tp = commands->lab->asc;
            while ((*tp++ = *commands->cp++)) {
                if (tp >= &(commands->lab->asc[8])) {
                    command_errf(commands, SEDERR_LTLMES, commands->linebuf);
                    return -1;
                }
            }
            *--tp = '\0';

            if ((lpt = search(commands)) != NULL) {
                if (lpt->address) {
                    command_errf(commands, SEDERR_DLMES, commands->linebuf);
                    return -1;
                }
                dechain(lpt, commands->rep);
            } else {
                commands->lab->chain = 0;
                lpt = commands->lab;
                if (++commands->lab >= commands->labend) {
                    command_errf(commands, SEDERR_TMLMES, commands->linebuf);
                    return -1;
                }
            }
            lpt->address = commands->rep;
            commands->rep->ad1 = p;

            continue;

        case 'a':
            commands->rep->command = ACOM;
            if (commands->rep->ad2) {
                command_errf(commands, SEDERR_AD1MES, commands->linebuf);
                return -1;
            }
            if (*commands->cp == '\\')
                commands->cp++;
            if (*commands->cp++ != '\n') {
                command_errf(commands, SEDERR_CGMES, commands->linebuf);
                return -1;
            }
            commands->rep->re1 = p;
            p = text(commands, commands->rep->re1, commands->reend);
            if (p == NULL)
                return -1;
            break;

        case 'c':
            commands->rep->command = CCOM;
            if (*commands->cp == '\\') commands->cp++;
            if (*commands->cp++ != ('\n')) {
                command_errf(commands, SEDERR_CGMES, commands->linebuf);
                return -1;
            }
            commands->rep->re1 = p;
            p = text(commands, commands->rep->re1, commands->reend);
            if (p == NULL)
                return -1;
            break;

        case 'i':
            commands->rep->command = ICOM;
            if (commands->rep->ad2) {
                command_errf(commands, SEDERR_AD1MES, commands->linebuf);
                return -1;
            }
            if (*commands->cp == '\\') commands->cp++;
            if (*commands->cp++ != ('\n')) {
                command_errf(commands, SEDERR_CGMES, commands->linebuf);
                return -1;
            }
            commands->rep->re1 = p;
            p = text(commands, commands->rep->re1, commands->reend);
            if (p == NULL)
                return -1;
            break;

        case 'g':
            commands->rep->command = GCOM;
            break;

        case 'G':
            commands->rep->command = CGCOM;
            break;

        case 'h':
            commands->rep->command = HCOM;
            break;

        case 'H':
            commands->rep->command = CHCOM;
            break;

        case 't':
            commands->rep->command = TCOM;
            goto jtcommon;

        case 'b':
            commands->rep->command = BCOM;
jtcommon:
            while (*commands->cp++ == ' ');
            commands->cp--;

            if (*commands->cp == '\0') {
                if ((pt = commands->labtab->chain) != NULL) {
                    while ((pt1 = pt->lb1) != NULL)
                        pt = pt1;
                    pt->lb1 = commands->rep;
                } else
                    commands->labtab->chain = commands->rep;
                break;
            }
            tp = commands->lab->asc;
            while ((*tp++ = *commands->cp++))
                if (tp >= &(commands->lab->asc[8])) {
                    command_errf(commands, SEDERR_LTLMES, commands->linebuf);
                    return -1;
                }
            commands->cp--;
            *--tp = '\0';

            if ((lpt = search(commands)) != NULL) {
                if (lpt->address) {
                    commands->rep->lb1 = lpt->address;
                } else {
                    pt = lpt->chain;
                    while ((pt1 = pt->lb1) != NULL)
                        pt = pt1;
                    pt->lb1 = commands->rep;
                }
            } else {
                commands->lab->chain = commands->rep;
                commands->lab->address = 0;
                if (++commands->lab >= commands->labend) {
                    command_errf(commands, SEDERR_TMLMES, commands->linebuf);
                    return -1;
                }
            }
            break;

        case 'n':
            commands->rep->command = NCOM;
            break;

        case 'N':
            commands->rep->command = CNCOM;
            break;

        case 'p':
            commands->rep->command = PCOM;
            break;

        case 'P':
            commands->rep->command = CPCOM;
            break;

        case 'r':
            commands->rep->command = RCOM;
            if (commands->rep->ad2) {
                command_errf(commands, SEDERR_AD1MES, commands->linebuf);
                return -1;
            }
            if (*commands->cp++ != ' ') {
                command_errf(commands, SEDERR_CGMES, commands->linebuf);
                return -1;
            }
            commands->rep->re1 = p;
            p = text(commands, commands->rep->re1, commands->reend);
            if (p == NULL)
                return -1;
            break;

        case 'd':
            commands->rep->command = DCOM;
            break;

        case 'D':
            commands->rep->command = CDCOM;
            commands->rep->lb1 = commands->ptrspace;
            break;

        case 'q':
            commands->rep->command = QCOM;
            if (commands->rep->ad2) {
                command_errf(commands, SEDERR_AD1MES, commands->linebuf);
                return -1;
            }
            break;

        case 'l':
            commands->rep->command = LCOM;
            break;

        case 's':
            commands->rep->command = SCOM;
            commands->sseof = *commands->cp++;
            commands->rep->re1 = p;
            p = comple(commands, &compargs, (char *) 0, commands->rep->re1,
                       commands->reend, commands->sseof);
            if (p == NULL)
                return -1;
            if (p == commands->rep->re1) {
                if (op)
                    commands->rep->re1 = op;
                else {
                    command_errf(commands, SEDERR_NRMES);
                    return -1;
                }
            } else
                op = commands->rep->re1;
            commands->rep->rhs = p;

            p = compsub(commands, &compargs, commands->rep->rhs);
            if ((p) == NULL)
                return -1;

            if (*commands->cp == 'g') {
                commands->cp++;
                commands->rep->gfl = 999;
            } else if (commands->gflag)
                commands->rep->gfl = 999;

            if (*commands->cp >= '1' && *commands->cp <= '9') {
                i = *commands->cp - '0';
                commands->cp++;
                while (1) {
                    ii = *commands->cp;
                    if (ii < '0' || ii > '9')
                        break;
                    i = i*10 + ii - '0';
                    if (i > 512) {
                        command_errf(commands, SEDERR_TOOBIG, commands->linebuf);
                        return -1;
                    }
                    commands->cp++;
                }
                commands->rep->gfl = i;
            }

            if (*commands->cp == 'p') {
                commands->cp++;
                commands->rep->pfl = 1;
            }

            if (*commands->cp == 'P') {
                commands->cp++;
                commands->rep->pfl = 2;
            }

            if (*commands->cp == 'w') {
                commands->cp++;
                if (*commands->cp++ !=  ' ') {
                    command_errf(commands, SEDERR_SMMES, commands->linebuf);
                    return -1;
                }
                if (text(commands, fnamebuf, &fnamebuf[APR_PATH_MAX]) == NULL) {
                    command_errf(commands, SEDERR_FNTL, commands->linebuf);
                    return -1;
                }
                for (i = commands->nfiles - 1; i >= 0; i--)
                    if (strcmp(fnamebuf,commands->fname[i]) == 0) {
                        commands->rep->findex = i;
                        goto done;
                    }
                if (commands->nfiles >= NWFILES) {
                    command_errf(commands, SEDERR_TMWFMES);
                    return -1;
                }
                commands->fname[commands->nfiles] =
                            apr_pstrdup(commands->pool, fnamebuf);
                if (commands->fname[commands->nfiles] == NULL) {
                    command_errf(commands, SEDERR_OOMMES);
                    return -1;
                }
                commands->rep->findex = commands->nfiles++;
            }
            break;

        case 'w':
            commands->rep->command = WCOM;
            if (*commands->cp++ != ' ') {
                command_errf(commands, SEDERR_SMMES, commands->linebuf);
                return -1;
            }
            if (text(commands, fnamebuf, &fnamebuf[APR_PATH_MAX]) == NULL) {
                command_errf(commands, SEDERR_FNTL, commands->linebuf);
                return -1;
            }
            for (i = commands->nfiles - 1; i >= 0; i--)
                if (strcmp(fnamebuf, commands->fname[i]) == 0) {
                    commands->rep->findex = i;
                    goto done;
                }
            if (commands->nfiles >= NWFILES) {
                command_errf(commands, SEDERR_TMWFMES);
                return -1;
            }
            if ((commands->fname[commands->nfiles] =
                        apr_pstrdup(commands->pool, fnamebuf)) == NULL) {
                command_errf(commands, SEDERR_OOMMES);
                return -1;
            }

            commands->rep->findex = commands->nfiles++;
            break;

        case 'x':
            commands->rep->command = XCOM;
            break;

        case 'y':
            commands->rep->command = YCOM;
            commands->sseof = *commands->cp++;
            commands->rep->re1 = p;
            p = ycomp(commands, commands->rep->re1);
            if (p == NULL)
                return -1;
            break;
        }
done:
        commands->rep = alloc_reptr(commands);

        commands->rep->ad1 = p;

        if (*commands->cp++ != '\0') {
            if (commands->cp[-1] == ';')
                goto comploop;
            command_errf(commands, SEDERR_CGMES, commands->linebuf);
            return -1;
        }
    }
    commands->rep->command = 0;
    commands->lastre = op;

    return 0;
}