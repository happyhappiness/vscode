
#ifdef WIN32
#include <conio.h>
#define unlink _unlink
#endif

#define APHTP_NEWFILE        1
#define APHTP_NOFILE         2
#define APHTP_DELUSER        4

apr_file_t *ftemp = NULL;

static int mkrecord(struct passwd_ctx *ctx, char *user)
{
    char hash_str[MAX_STRING_LEN];
    int ret;
    ctx->out = hash_str;
    ctx->out_len = sizeof(hash_str);

    ret = mkhash(ctx);
    if (ret)
        return ret;

    ctx->out = apr_pstrcat(ctx->pool, user, ":", hash_str, NL, NULL);
    if (strlen(ctx->out) >= MAX_STRING_LEN) {
        ctx->errstr = "resultant record too long";
        return ERR_OVERFLOW;
    }
    return 0;
}

static void usage(void)
{
    apr_file_printf(errfile, "Usage:" NL
        "\thtpasswd [-cimBdpsD] [-C cost] passwordfile username" NL
        "\thtpasswd -b[cmBdpsD] [-C cost] passwordfile username password" NL
        NL
        "\thtpasswd -n[imBdps] [-C cost] username" NL
        "\thtpasswd -nb[mBdps] [-C cost] username password" NL
        " -c  Create a new file." NL
        " -n  Don't update file; display results on stdout." NL
        " -b  Use the password from the command line rather than prompting "
            "for it." NL
        " -i  Read password from stdin without verification (for script usage)." NL
        " -m  Force MD5 encryption of the password (default)." NL
        " -B  Force bcrypt encryption of the password (very secure)." NL
        " -C  Set the computing time used for the bcrypt algorithm" NL
        "     (higher is more secure but slower, default: %d, valid: 4 to 31)." NL
        " -d  Force CRYPT encryption of the password (8 chars max, insecure)." NL
        " -s  Force SHA encryption of the password (insecure)." NL
        " -p  Do not encrypt the password (plaintext, insecure)." NL
        " -D  Delete the specified user." NL
        "On other systems than Windows and NetWare the '-p' flag will "
            "probably not work." NL
        "The SHA algorithm does not use a salt and is less secure than the "
            "MD5 algorithm." NL,
        BCRYPT_DEFAULT_COST
    );
    exit(ERR_SYNTAX);
}

/*
 * Check to see if the specified file can be opened for the given
 * access.
