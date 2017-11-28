
#include "squid.h"
#include "base64.h"
#include "helpers/defines.h"
#include "ntlmauth/ntlmauth.h"
#include "ntlmauth/support_bits.cci"

#include <cctype>
#include <cstring>
#if HAVE_CRYPT_H
#include <crypt.h>
#endif
#if HAVE_PWD_H
#include <pwd.h>
#endif
#if HAVE_GETOPT_H
#include <getopt.h>
#endif

/* A couple of harmless helper macros */
#define SEND(X) {debug("sending '%s' to squid\n",X); printf(X "\n");}
#ifdef __GNUC__
#define SEND2(X,Y...) {debug("sending '" X "' to squid\n",Y); printf(X "\n",Y);}
#define SEND4(X,Y...) {debug("sending '" X "' to squid\n",Y); printf(X "\n",Y);}
