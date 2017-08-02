; ModuleID = '/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/commands.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.sockaddr_in = type { i16, i16, %struct.in_addr, [8 x i8] }
%struct.in_addr = type { i32 }
%struct.passwd = type { i8*, i8*, i32, i32, i8*, i8*, i8* }
%struct.command = type { i8*, i8*, void (i8*)*, i8, i8 }
%struct.__va_list_tag = type { i32, i32, i8*, i8* }
%struct.sockaddr = type { i16, [14 x i8] }
%union.__SOCKADDR_ARG = type { %struct.sockaddr* }
%union.__CONST_SOCKADDR_ARG = type { %struct.sockaddr* }
%struct.fd_set = type { [16 x i64] }
%struct.timeval = type { i64, i64 }
%union.__WAIT_STATUS = type { %union.wait* }
%union.wait = type { i32 }
%struct.rusage = type opaque
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }
%struct.tm = type { i32, i32, i32, i32, i32, i32, i32, i32, i32, i64, i8* }
%struct.md5_t = type { i32, i32, i32, i32, [2 x i32], i32, [128 x i8] }

@state = global i32 0, align 4
@pasv = global i8 0, align 1
@philename = global i8* null, align 8
@offset = global i64 0, align 8
@xfertype = global i16 1, align 2
@ratio_send = global i32 1, align 4
@ratio_recv = global i32 1, align 4
@bytes_sent = global double 0.000000e+00, align 8
@bytes_recvd = global double 0.000000e+00, align 8
@epsvall = global i32 0, align 4
@stderr = external global %struct._IO_FILE*, align 8
@.str = private unnamed_addr constant [5 x i8] c"%s\0D\0A\00", align 1
@.str.1 = private unnamed_addr constant [2 x i8] c"\0D\00", align 1
@.str.2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.3 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.4 = private unnamed_addr constant [6 x i8] c"UMASK\00", align 1
@.str.5 = private unnamed_addr constant [41 x i8] c"Error with umask value. Setting to 022.\0A\00", align 1
@pasvsock = common global i32 0, align 4
@sock = common global i32 0, align 4
@.str.6 = private unnamed_addr constant [47 x i8] c"425-Unable to accept data connection.\0D\0A425 %s.\00", align 1
@name = external global %struct.sockaddr_in, align 4
@.str.7 = private unnamed_addr constant [11 x i8] c"DATAPORT20\00", align 1
@.str.8 = private unnamed_addr constant [4 x i8] c"yes\00", align 1
@.str.9 = private unnamed_addr constant [41 x i8] c"425-Unable to bind data socket.\0D\0A425 %s.\00", align 1
@sa = common global %struct.sockaddr_in zeroinitializer, align 4
@.str.10 = private unnamed_addr constant [50 x i8] c"425-Unable to establish data connection.\0D\0A425 %s.\00", align 1
@.str.11 = private unnamed_addr constant [36 x i8] c"150 %s data connection established.\00", align 1
@.str.12 = private unnamed_addr constant [7 x i8] c"BINARY\00", align 1
@.str.13 = private unnamed_addr constant [6 x i8] c"ASCII\00", align 1
@user = common global [31 x i8] zeroinitializer, align 16
@userinfo = external global %struct.passwd, align 8
@userinfo_set = external global i8, align 1
@.str.14 = private unnamed_addr constant [28 x i8] c"503 Username already given.\00", align 1
@.str.15 = private unnamed_addr constant [6 x i8] c"ALIAS\00", align 1
@.str.16 = private unnamed_addr constant [15 x i8] c"ANONYMOUS_USER\00", align 1
@.str.17 = private unnamed_addr constant [21 x i8] c"331 Password please.\00", align 1
@.str.18 = private unnamed_addr constant [23 x i8] c"503 Already logged in.\00", align 1
@.str.19 = private unnamed_addr constant [28 x i8] c"Login as user '%s' failed.\0A\00", align 1
@.str.20 = private unnamed_addr constant [21 x i8] c"530 Login incorrect.\00", align 1
@.str.21 = private unnamed_addr constant [43 x i8] c"257 \22%s\22 is the current working directory.\00", align 1
@.str.22 = private unnamed_addr constant [35 x i8] c"200 Transfer type changed to ASCII\00", align 1
@.str.23 = private unnamed_addr constant [36 x i8] c"200 Transfer type changed to BINARY\00", align 1
@.str.24 = private unnamed_addr constant [29 x i8] c"500 Type '%c' not supported.\00", align 1
@.str.25 = private unnamed_addr constant [30 x i8] c"500 EPSV ALL has been called.\00", align 1
@.str.26 = private unnamed_addr constant [24 x i8] c"%lu,%lu,%lu,%lu,%lu,%lu\00", align 1
@remotename = external global %struct.sockaddr_in, align 4
@.str.27 = private unnamed_addr constant [10 x i8] c"ALLOW_FXP\00", align 1
@.str.28 = private unnamed_addr constant [36 x i8] c"500 The given address is not yours.\00", align 1
@.str.29 = private unnamed_addr constant [32 x i8] c"200 PORT %lu.%lu.%lu.%lu:%lu OK\00", align 1
@.str.30 = private unnamed_addr constant [18 x i8] c"500 Syntax error.\00", align 1
@.str.31 = private unnamed_addr constant [24 x i8] c"%c%%i%c%%50[^%c]%c%%i%c\00", align 1
@.str.32 = private unnamed_addr constant [34 x i8] c"522 Protocol unsupported, use (1)\00", align 1
@.str.33 = private unnamed_addr constant [18 x i8] c"200 EPRT %s:%i OK\00", align 1
@.str.34 = private unnamed_addr constant [14 x i8] c"PASSIVE_PORTS\00", align 1
@.str.35 = private unnamed_addr constant [47 x i8] c"425-Error: Unable to bind data socket.\0D\0A425 %s\00", align 1
@.str.36 = private unnamed_addr constant [39 x i8] c"425 Error: Unable to bind data socket.\00", align 1
@.str.37 = private unnamed_addr constant [49 x i8] c"425-Error: Unable to make socket listen.\0D\0A425 %s\00", align 1
@.str.38 = private unnamed_addr constant [12 x i8] c"OVERRIDE_IP\00", align 1
@.str.39 = private unnamed_addr constant [12 x i8] c"%i.%i.%i.%i\00", align 1
@.str.40 = private unnamed_addr constant [46 x i8] c"227 Entering Passive Mode (%i,%i,%i,%i,%i,%i)\00", align 1
@.str.41 = private unnamed_addr constant [4 x i8] c"ALL\00", align 1
@.str.42 = private unnamed_addr constant [3 x i8] c"%i\00", align 1
@.str.43 = private unnamed_addr constant [47 x i8] c"500-Error: Unable to bind data socket.\0D\0A425 %s\00", align 1
@.str.44 = private unnamed_addr constant [49 x i8] c"500-Error: Unable to make socket listen.\0D\0A425 %s\00", align 1
@.str.45 = private unnamed_addr constant [44 x i8] c"229 Entering extended passive mode (|||%i|)\00", align 1
@stdin = external global %struct._IO_FILE*, align 8
@.str.46 = private unnamed_addr constant [5 x i8] c"ABOR\00", align 1
@.str.47 = private unnamed_addr constant [22 x i8] c"426 Transfer aborted.\00", align 1
@.str.48 = private unnamed_addr constant [13 x i8] c"226 Aborted.\00", align 1
@.str.49 = private unnamed_addr constant [35 x i8] c"Client aborted file transmission.\0A\00", align 1
@control_timeout = external global i32, align 4
@.str.50 = private unnamed_addr constant [35 x i8] c"Error: Filename in '%s' too long.\0A\00", align 1
@pre_write_script = common global i8* null, align 8
@.str.51 = private unnamed_addr constant [11 x i8] c"XFER_DELAY\00", align 1
@.str.52 = private unnamed_addr constant [40 x i8] c"Error getting xfer_delay in do_stor().\0A\00", align 1
@.str.53 = private unnamed_addr constant [18 x i8] c"ALLOWCOMMAND_DELE\00", align 1
@.str.54 = private unnamed_addr constant [3 x i8] c"no\00", align 1
@.str.55 = private unnamed_addr constant [33 x i8] c"Not allowed to over-write '%s'.\0A\00", align 1
@.str.56 = private unnamed_addr constant [43 x i8] c"553 Error: Remote file is write protected.\00", align 1
@.str.57 = private unnamed_addr constant [46 x i8] c"Error: '%s' while trying to store file '%s'.\0A\00", align 1
@.str.58 = private unnamed_addr constant [15 x i8] c"553 Error: %s.\00", align 1
@post_write_script = common global i8* null, align 8
@.str.59 = private unnamed_addr constant [30 x i8] c"Client is storing file '%s'.\0A\00", align 1
@.str.60 = private unnamed_addr constant [15 x i8] c"CHANGE_BUFSIZE\00", align 1
@.str.61 = private unnamed_addr constant [2 x i8] c"*\00", align 1
@xfer_bufsize = common global i32 0, align 4
@.str.62 = private unnamed_addr constant [42 x i8] c"Unable to create buffer to receive file.\0A\00", align 1
@.str.63 = private unnamed_addr constant [51 x i8] c"553 Error: An unknown error occured on the server.\00", align 1
@data_timeout = external global i32, align 4
@.str.64 = private unnamed_addr constant [45 x i8] c"426 Kicked due to data transmission timeout.\00", align 1
@.str.65 = private unnamed_addr constant [42 x i8] c"Kicked due to data transmission timeout.\0A\00", align 1
@.str.66 = private unnamed_addr constant [34 x i8] c"226 File transmission successful.\00", align 1
@.str.67 = private unnamed_addr constant [31 x i8] c"File transmission successful.\0A\00", align 1
@.str.68 = private unnamed_addr constant [45 x i8] c"Error getting XFER_DELAY in command_retr().\0A\00", align 1
@.str.69 = private unnamed_addr constant [31 x i8] c"Memory error in sending file.\0A\00", align 1
@.str.70 = private unnamed_addr constant [44 x i8] c"553 An unknown error occured on the server.\00", align 1
@.str.71 = private unnamed_addr constant [48 x i8] c"Error: '%s' while trying to receive file '%s'.\0A\00", align 1
@.str.72 = private unnamed_addr constant [27 x i8] c"550 Error: Is a directory.\00", align 1
@.str.73 = private unnamed_addr constant [6 x i8] c"RATIO\00", align 1
@.str.74 = private unnamed_addr constant [5 x i8] c"none\00", align 1
@.str.75 = private unnamed_addr constant [66 x i8] c"Error: 'File too big (ratio)' while trying to receive file '%s'.\0A\00", align 1
@.str.76 = private unnamed_addr constant [49 x i8] c"553 File too big. Send at least %lf bytes first.\00", align 1
@.str.77 = private unnamed_addr constant [32 x i8] c"Client is receiving file '%s'.\0A\00", align 1
@.str.78 = private unnamed_addr constant [30 x i8] c"553 An unknown error occured.\00", align 1
@.str.79 = private unnamed_addr constant [40 x i8] c"Memory error while trying to send file.\00", align 1
@.str.80 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.81 = private unnamed_addr constant [3 x i8] c"\0D\0A\00", align 1
@.str.82 = private unnamed_addr constant [45 x i8] c"File transmission interrupted. Send failed.\0A\00", align 1
@.str.83 = private unnamed_addr constant [39 x i8] c"File transmission of '%s' successful.\0A\00", align 1
@.str.84 = private unnamed_addr constant [2 x i8] c"w\00", align 1
@.str.85 = private unnamed_addr constant [39 x i8] c"226 Directory list has been submitted.\00", align 1
@.str.86 = private unnamed_addr constant [18 x i8] c"215 UNIX Type: L8\00", align 1
@.str.87 = private unnamed_addr constant [29 x i8] c"213 %04i%02i%02i%02i%02i%02i\00", align 1
@.str.88 = private unnamed_addr constant [54 x i8] c"550 Error while determining the modification time: %s\00", align 1
@.str.89 = private unnamed_addr constant [47 x i8] c"Error: '%s' while changing directory to '%s'.\0A\00", align 1
@.str.90 = private unnamed_addr constant [15 x i8] c"451 Error: %s.\00", align 1
@.str.91 = private unnamed_addr constant [28 x i8] c"Changed directory to '%s'.\0A\00", align 1
@.str.92 = private unnamed_addr constant [7 x i8] c"250 OK\00", align 1
@.str.93 = private unnamed_addr constant [28 x i8] c"Changed directory to '..'.\0A\00", align 1
@.str.94 = private unnamed_addr constant [3 x i8] c"..\00", align 1
@.str.95 = private unnamed_addr constant [59 x i8] c"Error: '%s' while trying to delete folder '%s' with DELE.\0A\00", align 1
@.str.96 = private unnamed_addr constant [23 x i8] c"550 %s: Is a directory\00", align 1
@.str.97 = private unnamed_addr constant [47 x i8] c"Error: '%s' while trying to delete file '%s'.\0A\00", align 1
@.str.98 = private unnamed_addr constant [20 x i8] c"Deleted file '%s'.\0A\00", align 1
@.str.99 = private unnamed_addr constant [7 x i8] c"200 OK\00", align 1
@.str.100 = private unnamed_addr constant [52 x i8] c"Error: '%s' while trying to create directory '%s'.\0A\00", align 1
@.str.101 = private unnamed_addr constant [25 x i8] c"Created directory '%s'.\0A\00", align 1
@.str.102 = private unnamed_addr constant [27 x i8] c"257 \22%s\22 has been created.\00", align 1
@.str.103 = private unnamed_addr constant [63 x i8] c"Error: '%s' while trying to remove directory '%s': not empty.\0A\00", align 1
@.str.104 = private unnamed_addr constant [28 x i8] c"550 %s: Directory not empty\00", align 1
@.str.105 = private unnamed_addr constant [52 x i8] c"Error: '%s' while trying to remove directory '%s'.\0A\00", align 1
@.str.106 = private unnamed_addr constant [25 x i8] c"Removed directory '%s'.\0A\00", align 1
@.str.107 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@.str.108 = private unnamed_addr constant [44 x i8] c"350 File exists, ready for destination name\00", align 1
@.str.109 = private unnamed_addr constant [50 x i8] c"Error: '%s' while trying to rename '%s' to '%s'.\0A\00", align 1
@.str.110 = private unnamed_addr constant [36 x i8] c"Successfully renamed '%s' to '%s'.\0A\00", align 1
@.str.111 = private unnamed_addr constant [29 x i8] c"350 Restarting at offset %i.\00", align 1
@.str.112 = private unnamed_addr constant [7 x i8] c"213 %i\00", align 1
@.str.113 = private unnamed_addr constant [15 x i8] c"550 Error: %s.\00", align 1
@.str.114 = private unnamed_addr constant [7 x i8] c"221 %s\00", align 1
@.str.115 = private unnamed_addr constant [9 x i8] c"QUIT_MSG\00", align 1
@.str.116 = private unnamed_addr constant [18 x i8] c"213-Status of %s:\00", align 1
@.str.117 = private unnamed_addr constant [19 x i8] c"213 End of Status.\00", align 1
@.str.118 = private unnamed_addr constant [47 x i8] c"550 Usage: SITE CHMOD <permissions> <filename>\00", align 1
@.str.119 = private unnamed_addr constant [53 x i8] c"550: An error occured on the server trying to CHMOD.\00", align 1
@.str.120 = private unnamed_addr constant [3 x i8] c"%o\00", align 1
@.str.121 = private unnamed_addr constant [11 x i8] c"Error: %s.\00", align 1
@.str.122 = private unnamed_addr constant [38 x i8] c"Changed permissions of '%s' to '%o'.\0A\00", align 1
@.str.123 = private unnamed_addr constant [22 x i8] c"200 CHMOD successful.\00", align 1
@.str.124 = private unnamed_addr constant [51 x i8] c"550 Usage: SITE CHOWN <owner>[.<group>] <filename>\00", align 1
@.str.125 = private unnamed_addr constant [9 x i8] c"%[^ ] %s\00", align 1
@.str.126 = private unnamed_addr constant [9 x i8] c"%[^.].%s\00", align 1
@passwdfile = external global %struct._IO_FILE*, align 8
@.str.127 = private unnamed_addr constant [25 x i8] c"550 User '%s' not found.\00", align 1
@groupfile = external global %struct._IO_FILE*, align 8
@.str.128 = private unnamed_addr constant [26 x i8] c"550 Group '%s' not found.\00", align 1
@.str.129 = private unnamed_addr constant [41 x i8] c"Changed owner of '%s' to UID %i GID %i.\0A\00", align 1
@.str.130 = private unnamed_addr constant [22 x i8] c"200 CHOWN successful.\00", align 1
@.str.131 = private unnamed_addr constant [20 x i8] c"550 File not found.\00", align 1
@.str.132 = private unnamed_addr constant [30 x i8] c"550 Unable to open file `%s'.\00", align 1
@.str.133 = private unnamed_addr constant [26 x i8] c"200 MD5 finger print: %s.\00", align 1
@command_site.subcmds = internal constant [4 x %struct.command] [%struct.command { i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.134, i32 0, i32 0), i8* null, void (i8*)* @command_chmod, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.135, i32 0, i32 0), i8* null, void (i8*)* @command_chown, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.136, i32 0, i32 0), i8* null, void (i8*)* @command_md5, i8 2, i8 0 }, %struct.command zeroinitializer], align 16
@.str.134 = private unnamed_addr constant [7 x i8] c"chmod \00", align 1
@.str.135 = private unnamed_addr constant [7 x i8] c"chown \00", align 1
@.str.136 = private unnamed_addr constant [4 x i8] c"md5\00", align 1
@.str.137 = private unnamed_addr constant [12 x i8] c"ENABLE_SITE\00", align 1
@.str.138 = private unnamed_addr constant [32 x i8] c"550 SITE commands are disabled.\00", align 1
@.str.139 = private unnamed_addr constant [5 x i8] c"help\00", align 1
@.str.140 = private unnamed_addr constant [38 x i8] c"211-Possible usages for SITE command:\00", align 1
@.str.141 = private unnamed_addr constant [33 x i8] c"211-site chmod <mask> <filename>\00", align 1
@.str.142 = private unnamed_addr constant [34 x i8] c"211-site chown <owner> <filename>\00", align 1
@.str.143 = private unnamed_addr constant [24 x i8] c"211 site md5 <filename>\00", align 1
@.str.144 = private unnamed_addr constant [32 x i8] c"550 Unknown command: 'SITE %s'.\00", align 1
@.str.145 = private unnamed_addr constant [26 x i8] c"550 Not implemented yet\0D\0A\00", align 1
@.str.146 = private unnamed_addr constant [5 x i8] c"USER\00", align 1
@.str.147 = private unnamed_addr constant [14 x i8] c"<sp> username\00", align 1
@.str.148 = private unnamed_addr constant [5 x i8] c"PASS\00", align 1
@.str.149 = private unnamed_addr constant [14 x i8] c"<sp> password\00", align 1
@.str.150 = private unnamed_addr constant [5 x i8] c"XPWD\00", align 1
@.str.151 = private unnamed_addr constant [14 x i8] c"(returns cwd)\00", align 1
@.str.152 = private unnamed_addr constant [4 x i8] c"PWD\00", align 1
@.str.153 = private unnamed_addr constant [5 x i8] c"TYPE\00", align 1
@.str.154 = private unnamed_addr constant [24 x i8] c"<sp> type-code (A or I)\00", align 1
@.str.155 = private unnamed_addr constant [5 x i8] c"PORT\00", align 1
@.str.156 = private unnamed_addr constant [23 x i8] c"<sp> h1,h2,h3,h4,p1,p2\00", align 1
@.str.157 = private unnamed_addr constant [5 x i8] c"EPRT\00", align 1
@.str.158 = private unnamed_addr constant [39 x i8] c"<sp><d><net-prt><d><ip><d><tcp-prt><d>\00", align 1
@.str.159 = private unnamed_addr constant [5 x i8] c"PASV\00", align 1
@.str.160 = private unnamed_addr constant [23 x i8] c"(returns address/port)\00", align 1
@.str.161 = private unnamed_addr constant [5 x i8] c"EPSV\00", align 1
@.str.162 = private unnamed_addr constant [23 x i8] c"(returns address/post)\00", align 1
@.str.163 = private unnamed_addr constant [5 x i8] c"ALLO\00", align 1
@.str.164 = private unnamed_addr constant [10 x i8] c"<sp> size\00", align 1
@.str.165 = private unnamed_addr constant [5 x i8] c"STOR\00", align 1
@.str.166 = private unnamed_addr constant [14 x i8] c"<sp> pathname\00", align 1
@.str.167 = private unnamed_addr constant [5 x i8] c"APPE\00", align 1
@.str.168 = private unnamed_addr constant [5 x i8] c"RETR\00", align 1
@.str.169 = private unnamed_addr constant [5 x i8] c"LIST\00", align 1
@.str.170 = private unnamed_addr constant [16 x i8] c"[<sp> pathname]\00", align 1
@.str.171 = private unnamed_addr constant [5 x i8] c"NLST\00", align 1
@.str.172 = private unnamed_addr constant [5 x i8] c"SYST\00", align 1
@.str.173 = private unnamed_addr constant [22 x i8] c"(returns system type)\00", align 1
@.str.174 = private unnamed_addr constant [5 x i8] c"MDTM\00", align 1
@.str.175 = private unnamed_addr constant [5 x i8] c"XCWD\00", align 1
@.str.176 = private unnamed_addr constant [4 x i8] c"CWD\00", align 1
@.str.177 = private unnamed_addr constant [5 x i8] c"XCUP\00", align 1
@.str.178 = private unnamed_addr constant [19 x i8] c"(up one directory)\00", align 1
@.str.179 = private unnamed_addr constant [5 x i8] c"CDUP\00", align 1
@.str.180 = private unnamed_addr constant [5 x i8] c"DELE\00", align 1
@.str.181 = private unnamed_addr constant [5 x i8] c"XMKD\00", align 1
@.str.182 = private unnamed_addr constant [4 x i8] c"MKD\00", align 1
@.str.183 = private unnamed_addr constant [5 x i8] c"XRMD\00", align 1
@.str.184 = private unnamed_addr constant [4 x i8] c"RMD\00", align 1
@.str.185 = private unnamed_addr constant [5 x i8] c"NOOP\00", align 1
@.str.186 = private unnamed_addr constant [15 x i8] c"(no operation)\00", align 1
@.str.187 = private unnamed_addr constant [5 x i8] c"OPTS\00", align 1
@.str.188 = private unnamed_addr constant [21 x i8] c"<sp> string <sp> val\00", align 1
@.str.189 = private unnamed_addr constant [5 x i8] c"RNFR\00", align 1
@.str.190 = private unnamed_addr constant [5 x i8] c"RNTO\00", align 1
@.str.191 = private unnamed_addr constant [5 x i8] c"REST\00", align 1
@.str.192 = private unnamed_addr constant [16 x i8] c"<sp> byte-count\00", align 1
@.str.193 = private unnamed_addr constant [5 x i8] c"SIZE\00", align 1
@.str.194 = private unnamed_addr constant [5 x i8] c"QUIT\00", align 1
@.str.195 = private unnamed_addr constant [27 x i8] c"(close control connection)\00", align 1
@.str.196 = private unnamed_addr constant [5 x i8] c"HELP\00", align 1
@.str.197 = private unnamed_addr constant [15 x i8] c"[<sp> command]\00", align 1
@.str.198 = private unnamed_addr constant [5 x i8] c"STAT\00", align 1
@.str.199 = private unnamed_addr constant [5 x i8] c"SITE\00", align 1
@.str.200 = private unnamed_addr constant [12 x i8] c"<sp> string\00", align 1
@.str.201 = private unnamed_addr constant [5 x i8] c"FEAT\00", align 1
@.str.202 = private unnamed_addr constant [29 x i8] c"(returns list of extensions)\00", align 1
@.str.203 = private unnamed_addr constant [5 x i8] c"MGET\00", align 1
@.str.204 = private unnamed_addr constant [5 x i8] c"MPUT\00", align 1
@commands = constant [40 x %struct.command] [%struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.146, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.147, i32 0, i32 0), void (i8*)* @command_user, i8 0, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.148, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.149, i32 0, i32 0), void (i8*)* @command_pass, i8 1, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.150, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.151, i32 0, i32 0), void (i8*)* @command_pwd, i8 2, i8 1 }, %struct.command { i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.152, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.151, i32 0, i32 0), void (i8*)* @command_pwd, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.153, i32 0, i32 0), i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.154, i32 0, i32 0), void (i8*)* @command_type, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.155, i32 0, i32 0), i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.156, i32 0, i32 0), void (i8*)* @command_port, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.157, i32 0, i32 0), i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.158, i32 0, i32 0), void (i8*)* @command_eprt, i8 2, i8 1 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.159, i32 0, i32 0), i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.160, i32 0, i32 0), void (i8*)* @command_pasv, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.161, i32 0, i32 0), i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.162, i32 0, i32 0), void (i8*)* @command_epsv, i8 2, i8 1 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.163, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.164, i32 0, i32 0), void (i8*)* @command_allo, i8 2, i8 1 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.165, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.166, i32 0, i32 0), void (i8*)* @command_stor, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.167, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.166, i32 0, i32 0), void (i8*)* @command_appe, i8 2, i8 1 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.168, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.166, i32 0, i32 0), void (i8*)* @command_retr, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.169, i32 0, i32 0), i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.170, i32 0, i32 0), void (i8*)* @command_list, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.171, i32 0, i32 0), i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.170, i32 0, i32 0), void (i8*)* @command_nlst, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.172, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.173, i32 0, i32 0), void (i8*)* @command_syst, i8 0, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.174, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.166, i32 0, i32 0), void (i8*)* @command_mdtm, i8 2, i8 1 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.175, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.166, i32 0, i32 0), void (i8*)* @command_cwd, i8 2, i8 1 }, %struct.command { i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.176, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.166, i32 0, i32 0), void (i8*)* @command_cwd, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.177, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.178, i32 0, i32 0), void (i8*)* @command_cdup, i8 2, i8 1 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.179, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.178, i32 0, i32 0), void (i8*)* @command_cdup, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.180, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.166, i32 0, i32 0), void (i8*)* @command_dele, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.181, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.166, i32 0, i32 0), void (i8*)* @command_mkd, i8 2, i8 1 }, %struct.command { i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.182, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.166, i32 0, i32 0), void (i8*)* @command_mkd, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.183, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.166, i32 0, i32 0), void (i8*)* @command_rmd, i8 2, i8 1 }, %struct.command { i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.184, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.166, i32 0, i32 0), void (i8*)* @command_rmd, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.185, i32 0, i32 0), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.186, i32 0, i32 0), void (i8*)* @command_noop, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.187, i32 0, i32 0), i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.188, i32 0, i32 0), void (i8*)* @command_opts, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.189, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.166, i32 0, i32 0), void (i8*)* @command_rnfr, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.190, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.166, i32 0, i32 0), void (i8*)* @command_rnto, i8 3, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.191, i32 0, i32 0), i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.192, i32 0, i32 0), void (i8*)* @command_rest, i8 2, i8 1 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.193, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.166, i32 0, i32 0), void (i8*)* @command_size, i8 2, i8 1 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.194, i32 0, i32 0), i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.195, i32 0, i32 0), void (i8*)* @command_quit, i8 0, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.196, i32 0, i32 0), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.197, i32 0, i32 0), void (i8*)* @command_help, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.198, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.166, i32 0, i32 0), void (i8*)* @command_stat, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.199, i32 0, i32 0), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.200, i32 0, i32 0), void (i8*)* @command_site, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.201, i32 0, i32 0), i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.202, i32 0, i32 0), void (i8*)* @command_feat, i8 2, i8 1 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.203, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.166, i32 0, i32 0), void (i8*)* @command_mget, i8 2, i8 0 }, %struct.command { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.204, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.166, i32 0, i32 0), void (i8*)* @command_mput, i8 2, i8 0 }, %struct.command zeroinitializer], align 16
@.str.205 = private unnamed_addr constant [26 x i8] c"211-Extensions supported:\00", align 1
@.str.206 = private unnamed_addr constant [4 x i8] c" %s\00", align 1
@.str.207 = private unnamed_addr constant [6 x i8] c" UTF8\00", align 1
@.str.208 = private unnamed_addr constant [8 x i8] c"211 End\00", align 1
@.str.209 = private unnamed_addr constant [8 x i8] c"utf8 on\00", align 1
@.str.210 = private unnamed_addr constant [12 x i8] c"200 UTF8 ON\00", align 1
@.str.211 = private unnamed_addr constant [23 x i8] c"550 %s not implemented\00", align 1
@.str.212 = private unnamed_addr constant [43 x i8] c"214-The following commands are recognized.\00", align 1
@.str.213 = private unnamed_addr constant [7 x i8] c"214-%s\00", align 1
@.str.214 = private unnamed_addr constant [16 x i8] c"214 End of help\00", align 1
@.str.215 = private unnamed_addr constant [15 x i8] c"214 Syntax: %s\00", align 1
@.str.216 = private unnamed_addr constant [16 x i8] c"ALLOWCOMMAND_%s\00", align 1
@.str.217 = private unnamed_addr constant [34 x i8] c"550 The command '%s' is disabled.\00", align 1
@.str.218 = private unnamed_addr constant [19 x i8] c"503 USER expected.\00", align 1
@.str.219 = private unnamed_addr constant [19 x i8] c"503 PASS expected.\00", align 1
@.str.220 = private unnamed_addr constant [31 x i8] c"503 RNFR before RNTO expected.\00", align 1
@.str.221 = private unnamed_addr constant [26 x i8] c"500 Unknown command: \22%s\22\00", align 1
@.str.222 = private unnamed_addr constant [32 x i8] c"Error trying to run script: %s\0A\00", align 1
@configpath = common global i8* null, align 8
@daemonmode = common global i32 0, align 4

; Function Attrs: nounwind uwtable
define void @control_printf(i8 signext %success, i8* %format, ...) #0 !dbg !114 {
entry:
  %success.addr = alloca i8, align 1
  %format.addr = alloca i8*, align 8
  %buffer = alloca [512 x i8], align 16
  %val = alloca [1 x %struct.__va_list_tag], align 16
  store i8 %success, i8* %success.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %success.addr, metadata !245, metadata !246), !dbg !247
  store i8* %format, i8** %format.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %format.addr, metadata !248, metadata !246), !dbg !249
  call void @llvm.dbg.declare(metadata [512 x i8]* %buffer, metadata !250, metadata !246), !dbg !254
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %val, metadata !255, metadata !246), !dbg !270
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %val, i32 0, i32 0, !dbg !271
  %arraydecay1 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !271
  call void @llvm.va_start(i8* %arraydecay1), !dbg !271
  %arraydecay2 = getelementptr inbounds [512 x i8], [512 x i8]* %buffer, i32 0, i32 0, !dbg !272
  %0 = load i8*, i8** %format.addr, align 8, !dbg !273
  %arraydecay3 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %val, i32 0, i32 0, !dbg !274
  %call = call i32 @vsnprintf(i8* %arraydecay2, i64 512, i8* %0, %struct.__va_list_tag* %arraydecay3) #2, !dbg !275
  %arraydecay4 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %val, i32 0, i32 0, !dbg !276
  %arraydecay45 = bitcast %struct.__va_list_tag* %arraydecay4 to i8*, !dbg !276
  call void @llvm.va_end(i8* %arraydecay45), !dbg !276
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !277
  %arraydecay6 = getelementptr inbounds [512 x i8], [512 x i8]* %buffer, i32 0, i32 0, !dbg !278
  %call7 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %1, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i32 0, i32 0), i8* %arraydecay6), !dbg !279
  %arraydecay8 = getelementptr inbounds [512 x i8], [512 x i8]* %buffer, i32 0, i32 0, !dbg !280
  %call9 = call i32 @replace(i8* %arraydecay8, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.1, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.2, i32 0, i32 0), i32 512), !dbg !281
  %2 = load i8, i8* %success.addr, align 1, !dbg !282
  %arraydecay10 = getelementptr inbounds [512 x i8], [512 x i8]* %buffer, i32 0, i32 0, !dbg !283
  call void (i8, i8, i8*, ...) @bftpd_statuslog(i8 signext 3, i8 signext %2, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.3, i32 0, i32 0), i8* %arraydecay10), !dbg !284
  ret void, !dbg !285
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #2

; Function Attrs: nounwind
declare i32 @vsnprintf(i8*, i64, i8*, %struct.__va_list_tag*) #3

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #2

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #4

declare i32 @replace(i8*, i8*, i8*, i32) #4

declare void @bftpd_statuslog(i8 signext, i8 signext, i8*, ...) #4

; Function Attrs: nounwind uwtable
define void @new_umask() #0 !dbg !119 {
entry:
  %um = alloca i32, align 4
  %get_um = alloca i64, align 8
  %foo = alloca i8*, align 8
  call void @llvm.dbg.declare(metadata i32* %um, metadata !286, metadata !246), !dbg !287
  call void @llvm.dbg.declare(metadata i64* %get_um, metadata !288, metadata !246), !dbg !289
  call void @llvm.dbg.declare(metadata i8** %foo, metadata !290, metadata !246), !dbg !291
  %call = call i8* @config_getoption(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.4, i32 0, i32 0)), !dbg !292
  store i8* %call, i8** %foo, align 8, !dbg !291
  %0 = load i8*, i8** %foo, align 8, !dbg !293
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !293
  %1 = load i8, i8* %arrayidx, align 1, !dbg !293
  %tobool = icmp ne i8 %1, 0, !dbg !293
  br i1 %tobool, label %if.else, label %if.then, !dbg !295

if.then:                                          ; preds = %entry
  store i32 18, i32* %um, align 4, !dbg !296
  br label %if.end4, !dbg !297

if.else:                                          ; preds = %entry
  %2 = load i8*, i8** %foo, align 8, !dbg !298
  %call1 = call i64 @strtoul(i8* %2, i8** null, i32 8) #2, !dbg !300
  store i64 %call1, i64* %get_um, align 8, !dbg !301
  %3 = load i64, i64* %get_um, align 8, !dbg !302
  %cmp = icmp ule i64 %3, 2147483647, !dbg !304
  br i1 %cmp, label %if.then2, label %if.else3, !dbg !305

if.then2:                                         ; preds = %if.else
  %4 = load i64, i64* %get_um, align 8, !dbg !306
  %conv = trunc i64 %4 to i32, !dbg !306
  store i32 %conv, i32* %um, align 4, !dbg !307
  br label %if.end, !dbg !308

if.else3:                                         ; preds = %if.else
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.5, i32 0, i32 0), i32 0), !dbg !309
  store i32 18, i32* %um, align 4, !dbg !311
  br label %if.end

if.end:                                           ; preds = %if.else3, %if.then2
  br label %if.end4

if.end4:                                          ; preds = %if.end, %if.then
  %5 = load i32, i32* %um, align 4, !dbg !312
  %call5 = call i32 @umask(i32 %5) #2, !dbg !313
  ret void, !dbg !314
}

declare i8* @config_getoption(i8*) #4

; Function Attrs: nounwind
declare i64 @strtoul(i8*, i8**, i32) #3

declare void @bftpd_log(i8*, ...) #4

; Function Attrs: nounwind
declare i32 @umask(i32) #3

; Function Attrs: nounwind uwtable
define void @prepare_sock(i32 %sock) #0 !dbg !122 {
entry:
  %sock.addr = alloca i32, align 4
  %on = alloca i32, align 4
  store i32 %sock, i32* %sock.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sock.addr, metadata !315, metadata !246), !dbg !316
  call void @llvm.dbg.declare(metadata i32* %on, metadata !317, metadata !246), !dbg !318
  store i32 1, i32* %on, align 4, !dbg !318
  %0 = load i32, i32* %sock.addr, align 4, !dbg !319
  %1 = bitcast i32* %on to i8*, !dbg !320
  %call = call i32 @setsockopt(i32 %0, i32 1, i32 2, i8* %1, i32 4) #2, !dbg !321
  %2 = load i32, i32* %sock.addr, align 4, !dbg !322
  %3 = bitcast i32* %on to i8*, !dbg !323
  %call1 = call i32 @setsockopt(i32 %2, i32 1, i32 15, i8* %3, i32 4) #2, !dbg !324
  store i32 65536, i32* %on, align 4, !dbg !325
  %4 = load i32, i32* %sock.addr, align 4, !dbg !326
  %5 = bitcast i32* %on to i8*, !dbg !327
  %call2 = call i32 @setsockopt(i32 %4, i32 1, i32 7, i8* %5, i32 4) #2, !dbg !328
  ret void, !dbg !329
}

; Function Attrs: nounwind
declare i32 @setsockopt(i32, i32, i32, i8*, i32) #3

; Function Attrs: nounwind uwtable
define i32 @dataconn() #0 !dbg !123 {
entry:
  %retval = alloca i32, align 4
  %foo = alloca %struct.sockaddr, align 2
  %local = alloca %struct.sockaddr_in, align 4
  %namelen = alloca i32, align 4
  %curuid = alloca i32, align 4
  %agg.tmp = alloca %union.__SOCKADDR_ARG, align 8
  %agg.tmp14 = alloca %union.__CONST_SOCKADDR_ARG, align 8
  %agg.tmp29 = alloca %union.__CONST_SOCKADDR_ARG, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr* %foo, metadata !330, metadata !246), !dbg !331
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in* %local, metadata !332, metadata !246), !dbg !333
  call void @llvm.dbg.declare(metadata i32* %namelen, metadata !334, metadata !246), !dbg !335
  store i32 16, i32* %namelen, align 4, !dbg !335
  call void @llvm.dbg.declare(metadata i32* %curuid, metadata !336, metadata !246), !dbg !337
  %call = call i32 @geteuid() #2, !dbg !338
  store i32 %call, i32* %curuid, align 4, !dbg !337
  %0 = bitcast %struct.sockaddr* %foo to i8*, !dbg !339
  call void @llvm.memset.p0i8.i64(i8* %0, i8 0, i64 16, i32 2, i1 false), !dbg !339
  %1 = bitcast %struct.sockaddr_in* %local to i8*, !dbg !340
  call void @llvm.memset.p0i8.i64(i8* %1, i8 0, i64 16, i32 4, i1 false), !dbg !340
  %2 = load i8, i8* @pasv, align 1, !dbg !341
  %tobool = icmp ne i8 %2, 0, !dbg !341
  br i1 %tobool, label %if.then, label %if.else, !dbg !343

if.then:                                          ; preds = %entry
  %3 = load i32, i32* @pasvsock, align 4, !dbg !344
  %__sockaddr__ = bitcast %union.__SOCKADDR_ARG* %agg.tmp to %struct.sockaddr**, !dbg !346
  store %struct.sockaddr* %foo, %struct.sockaddr** %__sockaddr__, align 8, !dbg !346
  %coerce.dive = getelementptr inbounds %union.__SOCKADDR_ARG, %union.__SOCKADDR_ARG* %agg.tmp, i32 0, i32 0, !dbg !347
  %4 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive, align 8, !dbg !347
  %call1 = call i32 @accept(i32 %3, %struct.sockaddr* %4, i32* %namelen), !dbg !347
  store i32 %call1, i32* @sock, align 4, !dbg !348
  %5 = load i32, i32* @sock, align 4, !dbg !349
  %cmp = icmp eq i32 %5, -1, !dbg !351
  br i1 %cmp, label %if.then2, label %if.end, !dbg !352

if.then2:                                         ; preds = %if.then
  %call3 = call i32* @__errno_location() #1, !dbg !353
  %6 = load i32, i32* %call3, align 4, !dbg !353
  %call4 = call i8* @strerror(i32 %6) #2, !dbg !355
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.6, i32 0, i32 0), i8* %call4), !dbg !357
  store i32 1, i32* %retval, align 4, !dbg !358
  br label %return, !dbg !358

if.end:                                           ; preds = %if.then
  %7 = load i32, i32* @pasvsock, align 4, !dbg !359
  %call5 = call i32 @close(i32 %7), !dbg !360
  %8 = load i32, i32* @sock, align 4, !dbg !361
  call void @prepare_sock(i32 %8), !dbg !362
  br label %if.end38, !dbg !363

if.else:                                          ; preds = %entry
  %call6 = call i32 @socket(i32 2, i32 1, i32 0) #2, !dbg !364
  store i32 %call6, i32* @sock, align 4, !dbg !366
  %9 = load i32, i32* @sock, align 4, !dbg !367
  call void @prepare_sock(i32 %9), !dbg !368
  %10 = load i32, i32* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @name, i32 0, i32 2, i32 0), align 4, !dbg !369
  %sin_addr = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %local, i32 0, i32 2, !dbg !370
  %s_addr = getelementptr inbounds %struct.in_addr, %struct.in_addr* %sin_addr, i32 0, i32 0, !dbg !371
  store i32 %10, i32* %s_addr, align 4, !dbg !372
  %sin_family = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %local, i32 0, i32 0, !dbg !373
  store i16 2, i16* %sin_family, align 4, !dbg !374
  %call7 = call i8* @config_getoption(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.7, i32 0, i32 0)), !dbg !375
  %call8 = call i32 @strcasecmp(i8* %call7, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.8, i32 0, i32 0)) #9, !dbg !377
  %tobool9 = icmp ne i32 %call8, 0, !dbg !379
  br i1 %tobool9, label %if.end13, label %if.then10, !dbg !380

if.then10:                                        ; preds = %if.else
  %call11 = call i32 @seteuid(i32 0) #2, !dbg !381
  %call12 = call zeroext i16 @htons(i16 zeroext 20) #1, !dbg !383
  %sin_port = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %local, i32 0, i32 1, !dbg !384
  store i16 %call12, i16* %sin_port, align 2, !dbg !385
  br label %if.end13, !dbg !386

if.end13:                                         ; preds = %if.then10, %if.else
  %11 = load i32, i32* @sock, align 4, !dbg !387
  %__sockaddr__15 = bitcast %union.__CONST_SOCKADDR_ARG* %agg.tmp14 to %struct.sockaddr**, !dbg !389
  %12 = bitcast %struct.sockaddr_in* %local to %struct.sockaddr*, !dbg !389
  store %struct.sockaddr* %12, %struct.sockaddr** %__sockaddr__15, align 8, !dbg !389
  %coerce.dive16 = getelementptr inbounds %union.__CONST_SOCKADDR_ARG, %union.__CONST_SOCKADDR_ARG* %agg.tmp14, i32 0, i32 0, !dbg !390
  %13 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive16, align 8, !dbg !390
  %call17 = call i32 @bind(i32 %11, %struct.sockaddr* %13, i32 16) #2, !dbg !390
  %cmp18 = icmp slt i32 %call17, 0, !dbg !391
  br i1 %cmp18, label %if.then19, label %if.end22, !dbg !392

if.then19:                                        ; preds = %if.end13
  %call20 = call i32* @__errno_location() #1, !dbg !393
  %14 = load i32, i32* %call20, align 4, !dbg !393
  %call21 = call i8* @strerror(i32 %14) #2, !dbg !395
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.9, i32 0, i32 0), i8* %call21), !dbg !397
  store i32 1, i32* %retval, align 4, !dbg !398
  br label %return, !dbg !398

if.end22:                                         ; preds = %if.end13
  %call23 = call i8* @config_getoption(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.7, i32 0, i32 0)), !dbg !399
  %call24 = call i32 @strcasecmp(i8* %call23, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.8, i32 0, i32 0)) #9, !dbg !401
  %tobool25 = icmp ne i32 %call24, 0, !dbg !403
  br i1 %tobool25, label %if.end28, label %if.then26, !dbg !404

if.then26:                                        ; preds = %if.end22
  %15 = load i32, i32* %curuid, align 4, !dbg !405
  %call27 = call i32 @seteuid(i32 %15) #2, !dbg !406
  br label %if.end28, !dbg !406

if.end28:                                         ; preds = %if.then26, %if.end22
  store i16 2, i16* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @sa, i32 0, i32 0), align 4, !dbg !407
  %16 = load i32, i32* @sock, align 4, !dbg !408
  %__sockaddr__30 = bitcast %union.__CONST_SOCKADDR_ARG* %agg.tmp29 to %struct.sockaddr**, !dbg !410
  store %struct.sockaddr* bitcast (%struct.sockaddr_in* @sa to %struct.sockaddr*), %struct.sockaddr** %__sockaddr__30, align 8, !dbg !410
  %coerce.dive31 = getelementptr inbounds %union.__CONST_SOCKADDR_ARG, %union.__CONST_SOCKADDR_ARG* %agg.tmp29, i32 0, i32 0, !dbg !411
  %17 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive31, align 8, !dbg !411
  %call32 = call i32 @connect(i32 %16, %struct.sockaddr* %17, i32 16), !dbg !411
  %cmp33 = icmp eq i32 %call32, -1, !dbg !412
  br i1 %cmp33, label %if.then34, label %if.end37, !dbg !413

if.then34:                                        ; preds = %if.end28
  %call35 = call i32* @__errno_location() #1, !dbg !414
  %18 = load i32, i32* %call35, align 4, !dbg !414
  %call36 = call i8* @strerror(i32 %18) #2, !dbg !416
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.10, i32 0, i32 0), i8* %call36), !dbg !418
  store i32 1, i32* %retval, align 4, !dbg !419
  br label %return, !dbg !419

if.end37:                                         ; preds = %if.end28
  br label %if.end38

if.end38:                                         ; preds = %if.end37, %if.end
  %19 = load i16, i16* @xfertype, align 2, !dbg !420
  %conv = sext i16 %19 to i32, !dbg !420
  %cmp39 = icmp eq i32 %conv, 1, !dbg !421
  %cond = select i1 %cmp39, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.13, i32 0, i32 0), !dbg !420
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.11, i32 0, i32 0), i8* %cond), !dbg !422
  store i32 0, i32* %retval, align 4, !dbg !423
  br label %return, !dbg !423

return:                                           ; preds = %if.end38, %if.then34, %if.then19, %if.then2
  %20 = load i32, i32* %retval, align 4, !dbg !424
  ret i32 %20, !dbg !424
}

; Function Attrs: nounwind
declare i32 @geteuid() #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #5

declare i32 @accept(i32, %struct.sockaddr*, i32*) #4

; Function Attrs: nounwind
declare i8* @strerror(i32) #3

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #6

declare i32 @close(i32) #4

; Function Attrs: nounwind
declare i32 @socket(i32, i32, i32) #3

; Function Attrs: nounwind readonly
declare i32 @strcasecmp(i8*, i8*) #7

; Function Attrs: nounwind
declare i32 @seteuid(i32) #3

; Function Attrs: nounwind readnone
declare zeroext i16 @htons(i16 zeroext) #6

; Function Attrs: nounwind
declare i32 @bind(i32, %struct.sockaddr*, i32) #3

declare i32 @connect(i32, %struct.sockaddr*, i32) #4

; Function Attrs: nounwind uwtable
define void @init_userinfo() #0 !dbg !126 {
entry:
  %temp = alloca %struct.passwd*, align 8
  call void @llvm.dbg.declare(metadata %struct.passwd** %temp, metadata !425, metadata !246), !dbg !437
  %call = call %struct.passwd* @getpwnam(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0)), !dbg !438
  store %struct.passwd* %call, %struct.passwd** %temp, align 8, !dbg !437
  %0 = load %struct.passwd*, %struct.passwd** %temp, align 8, !dbg !439
  %tobool = icmp ne %struct.passwd* %0, null, !dbg !439
  br i1 %tobool, label %if.then, label %if.end, !dbg !441

if.then:                                          ; preds = %entry
  %1 = load %struct.passwd*, %struct.passwd** %temp, align 8, !dbg !442
  %pw_name = getelementptr inbounds %struct.passwd, %struct.passwd* %1, i32 0, i32 0, !dbg !444
  %2 = load i8*, i8** %pw_name, align 8, !dbg !444
  %call1 = call noalias i8* @strdup(i8* %2) #2, !dbg !445
  store i8* %call1, i8** getelementptr inbounds (%struct.passwd, %struct.passwd* @userinfo, i32 0, i32 0), align 8, !dbg !446
  %3 = load %struct.passwd*, %struct.passwd** %temp, align 8, !dbg !447
  %pw_passwd = getelementptr inbounds %struct.passwd, %struct.passwd* %3, i32 0, i32 1, !dbg !448
  %4 = load i8*, i8** %pw_passwd, align 8, !dbg !448
  %call2 = call noalias i8* @strdup(i8* %4) #2, !dbg !449
  store i8* %call2, i8** getelementptr inbounds (%struct.passwd, %struct.passwd* @userinfo, i32 0, i32 1), align 8, !dbg !450
  %5 = load %struct.passwd*, %struct.passwd** %temp, align 8, !dbg !451
  %pw_uid = getelementptr inbounds %struct.passwd, %struct.passwd* %5, i32 0, i32 2, !dbg !452
  %6 = load i32, i32* %pw_uid, align 8, !dbg !452
  store i32 %6, i32* getelementptr inbounds (%struct.passwd, %struct.passwd* @userinfo, i32 0, i32 2), align 8, !dbg !453
  %7 = load %struct.passwd*, %struct.passwd** %temp, align 8, !dbg !454
  %pw_gid = getelementptr inbounds %struct.passwd, %struct.passwd* %7, i32 0, i32 3, !dbg !455
  %8 = load i32, i32* %pw_gid, align 4, !dbg !455
  store i32 %8, i32* getelementptr inbounds (%struct.passwd, %struct.passwd* @userinfo, i32 0, i32 3), align 4, !dbg !456
  %9 = load %struct.passwd*, %struct.passwd** %temp, align 8, !dbg !457
  %pw_gecos = getelementptr inbounds %struct.passwd, %struct.passwd* %9, i32 0, i32 4, !dbg !458
  %10 = load i8*, i8** %pw_gecos, align 8, !dbg !458
  %call3 = call noalias i8* @strdup(i8* %10) #2, !dbg !459
  store i8* %call3, i8** getelementptr inbounds (%struct.passwd, %struct.passwd* @userinfo, i32 0, i32 4), align 8, !dbg !460
  %11 = load %struct.passwd*, %struct.passwd** %temp, align 8, !dbg !461
  %pw_dir = getelementptr inbounds %struct.passwd, %struct.passwd* %11, i32 0, i32 5, !dbg !462
  %12 = load i8*, i8** %pw_dir, align 8, !dbg !462
  %call4 = call noalias i8* @strdup(i8* %12) #2, !dbg !463
  store i8* %call4, i8** getelementptr inbounds (%struct.passwd, %struct.passwd* @userinfo, i32 0, i32 5), align 8, !dbg !464
  %13 = load %struct.passwd*, %struct.passwd** %temp, align 8, !dbg !465
  %pw_shell = getelementptr inbounds %struct.passwd, %struct.passwd* %13, i32 0, i32 6, !dbg !466
  %14 = load i8*, i8** %pw_shell, align 8, !dbg !466
  %call5 = call noalias i8* @strdup(i8* %14) #2, !dbg !467
  store i8* %call5, i8** getelementptr inbounds (%struct.passwd, %struct.passwd* @userinfo, i32 0, i32 6), align 8, !dbg !468
  store i8 1, i8* @userinfo_set, align 1, !dbg !469
  br label %if.end, !dbg !470

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !471
}

declare %struct.passwd* @getpwnam(i8*) #4

; Function Attrs: nounwind
declare noalias i8* @strdup(i8*) #3

; Function Attrs: nounwind uwtable
define void @command_user(i8* %username) #0 !dbg !127 {
entry:
  %username.addr = alloca i8*, align 8
  %alias = alloca i8*, align 8
  store i8* %username, i8** %username.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %username.addr, metadata !472, metadata !246), !dbg !473
  call void @llvm.dbg.declare(metadata i8** %alias, metadata !474, metadata !246), !dbg !475
  %0 = load i32, i32* @state, align 4, !dbg !476
  %tobool = icmp ne i32 %0, 0, !dbg !476
  br i1 %tobool, label %if.then, label %if.end, !dbg !478

if.then:                                          ; preds = %entry
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.14, i32 0, i32 0)), !dbg !479
  br label %if.end8, !dbg !481

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %username.addr, align 8, !dbg !482
  call void @mystrncpy(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0), i8* %1, i32 30), !dbg !483
  store i8 1, i8* @userinfo_set, align 1, !dbg !484
  %call = call i8* @config_getoption(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.15, i32 0, i32 0)), !dbg !485
  store i8* %call, i8** %alias, align 8, !dbg !486
  store i8 0, i8* @userinfo_set, align 1, !dbg !487
  %2 = load i8*, i8** %alias, align 8, !dbg !488
  %arrayidx = getelementptr inbounds i8, i8* %2, i64 0, !dbg !488
  %3 = load i8, i8* %arrayidx, align 1, !dbg !488
  %conv = sext i8 %3 to i32, !dbg !488
  %cmp = icmp ne i32 %conv, 0, !dbg !490
  br i1 %cmp, label %if.then2, label %if.end3, !dbg !491

if.then2:                                         ; preds = %if.end
  %4 = load i8*, i8** %alias, align 8, !dbg !492
  call void @mystrncpy(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0), i8* %4, i32 30), !dbg !493
  br label %if.end3, !dbg !493

if.end3:                                          ; preds = %if.then2, %if.end
  call void @init_userinfo(), !dbg !494
  store i8 1, i8* @userinfo_set, align 1, !dbg !495
  call void (...) @expand_groups(), !dbg !496
  %call4 = call i8* @config_getoption(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.16, i32 0, i32 0)), !dbg !497
  %call5 = call i32 @strcasecmp(i8* %call4, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.8, i32 0, i32 0)) #9, !dbg !499
  %tobool6 = icmp ne i32 %call5, 0, !dbg !501
  br i1 %tobool6, label %if.else, label %if.then7, !dbg !502

if.then7:                                         ; preds = %if.end3
  store i32 1, i32* @state, align 4, !dbg !503
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.17, i32 0, i32 0)), !dbg !505
  br label %if.end8, !dbg !506

if.else:                                          ; preds = %if.end3
  store i32 1, i32* @state, align 4, !dbg !507
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.17, i32 0, i32 0)), !dbg !509
  br label %if.end8

if.end8:                                          ; preds = %if.then, %if.else, %if.then7
  ret void, !dbg !510
}

declare void @mystrncpy(i8*, i8*, i32) #4

declare void @expand_groups(...) #4

; Function Attrs: nounwind uwtable
define void @command_pass(i8* %password) #0 !dbg !130 {
entry:
  %password.addr = alloca i8*, align 8
  store i8* %password, i8** %password.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %password.addr, metadata !511, metadata !246), !dbg !512
  %0 = load i32, i32* @state, align 4, !dbg !513
  %cmp = icmp sgt i32 %0, 1, !dbg !515
  br i1 %cmp, label %if.then, label %if.end, !dbg !516

if.then:                                          ; preds = %entry
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.18, i32 0, i32 0)), !dbg !517
  br label %if.end2, !dbg !519

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %password.addr, align 8, !dbg !520
  %call = call i32 @bftpd_login(i8* %1), !dbg !522
  %tobool = icmp ne i32 %call, 0, !dbg !522
  br i1 %tobool, label %if.then1, label %if.end2, !dbg !523

if.then1:                                         ; preds = %if.end
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.19, i32 0, i32 0), i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0)), !dbg !524
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.20, i32 0, i32 0)), !dbg !526
  store i32 0, i32* @state, align 4, !dbg !527
  br label %if.end2, !dbg !528

if.end2:                                          ; preds = %if.then, %if.then1, %if.end
  ret void, !dbg !529
}

declare i32 @bftpd_login(i8*) #4

; Function Attrs: nounwind uwtable
define void @command_pwd(i8* %params) #0 !dbg !131 {
entry:
  %params.addr = alloca i8*, align 8
  %my_cwd = alloca i8*, align 8
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !530, metadata !246), !dbg !531
  call void @llvm.dbg.declare(metadata i8** %my_cwd, metadata !532, metadata !246), !dbg !533
  store i8* null, i8** %my_cwd, align 8, !dbg !533
  %call = call i8* (...) @bftpd_cwd_getcwd(), !dbg !534
  store i8* %call, i8** %my_cwd, align 8, !dbg !535
  %0 = load i8*, i8** %my_cwd, align 8, !dbg !536
  %tobool = icmp ne i8* %0, null, !dbg !536
  br i1 %tobool, label %if.then, label %if.end, !dbg !538

if.then:                                          ; preds = %entry
  %1 = load i8*, i8** %my_cwd, align 8, !dbg !539
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.21, i32 0, i32 0), i8* %1), !dbg !541
  %2 = load i8*, i8** %my_cwd, align 8, !dbg !542
  call void @free(i8* %2) #2, !dbg !543
  br label %if.end, !dbg !544

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !545
}

declare i8* @bftpd_cwd_getcwd(...) #4

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind uwtable
define void @command_type(i8* %params) #0 !dbg !132 {
entry:
  %params.addr = alloca i8*, align 8
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !546, metadata !246), !dbg !547
  %0 = load i8*, i8** %params.addr, align 8, !dbg !548
  %1 = load i8, i8* %0, align 1, !dbg !550
  %conv = sext i8 %1 to i32, !dbg !550
  %cmp = icmp eq i32 %conv, 65, !dbg !551
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !552

lor.lhs.false:                                    ; preds = %entry
  %2 = load i8*, i8** %params.addr, align 8, !dbg !553
  %3 = load i8, i8* %2, align 1, !dbg !555
  %conv2 = sext i8 %3 to i32, !dbg !555
  %cmp3 = icmp eq i32 %conv2, 97, !dbg !556
  br i1 %cmp3, label %if.then, label %if.else, !dbg !557

if.then:                                          ; preds = %lor.lhs.false, %entry
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.22, i32 0, i32 0)), !dbg !558
  store i16 0, i16* @xfertype, align 2, !dbg !560
  br label %if.end15, !dbg !561

if.else:                                          ; preds = %lor.lhs.false
  %4 = load i8*, i8** %params.addr, align 8, !dbg !562
  %5 = load i8, i8* %4, align 1, !dbg !565
  %conv5 = sext i8 %5 to i32, !dbg !565
  %cmp6 = icmp eq i32 %conv5, 73, !dbg !566
  br i1 %cmp6, label %if.then12, label %lor.lhs.false8, !dbg !567

lor.lhs.false8:                                   ; preds = %if.else
  %6 = load i8*, i8** %params.addr, align 8, !dbg !568
  %7 = load i8, i8* %6, align 1, !dbg !570
  %conv9 = sext i8 %7 to i32, !dbg !570
  %cmp10 = icmp eq i32 %conv9, 105, !dbg !571
  br i1 %cmp10, label %if.then12, label %if.else13, !dbg !572

if.then12:                                        ; preds = %lor.lhs.false8, %if.else
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.23, i32 0, i32 0)), !dbg !573
  store i16 1, i16* @xfertype, align 2, !dbg !575
  br label %if.end, !dbg !576

if.else13:                                        ; preds = %lor.lhs.false8
  %8 = load i8*, i8** %params.addr, align 8, !dbg !577
  %9 = load i8, i8* %8, align 1, !dbg !578
  %conv14 = sext i8 %9 to i32, !dbg !578
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.24, i32 0, i32 0), i32 %conv14), !dbg !579
  br label %if.end

if.end:                                           ; preds = %if.else13, %if.then12
  br label %if.end15

if.end15:                                         ; preds = %if.end, %if.then
  ret void, !dbg !580
}

; Function Attrs: nounwind uwtable
define void @command_port(i8* %params) #0 !dbg !133 {
entry:
  %params.addr = alloca i8*, align 8
  %a0 = alloca i64, align 8
  %a1 = alloca i64, align 8
  %a2 = alloca i64, align 8
  %a3 = alloca i64, align 8
  %p0 = alloca i64, align 8
  %p1 = alloca i64, align 8
  %addr = alloca i64, align 8
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !581, metadata !246), !dbg !582
  call void @llvm.dbg.declare(metadata i64* %a0, metadata !583, metadata !246), !dbg !584
  call void @llvm.dbg.declare(metadata i64* %a1, metadata !585, metadata !246), !dbg !586
  call void @llvm.dbg.declare(metadata i64* %a2, metadata !587, metadata !246), !dbg !588
  call void @llvm.dbg.declare(metadata i64* %a3, metadata !589, metadata !246), !dbg !590
  call void @llvm.dbg.declare(metadata i64* %p0, metadata !591, metadata !246), !dbg !592
  call void @llvm.dbg.declare(metadata i64* %p1, metadata !593, metadata !246), !dbg !594
  call void @llvm.dbg.declare(metadata i64* %addr, metadata !595, metadata !246), !dbg !596
  %0 = load i32, i32* @epsvall, align 4, !dbg !597
  %tobool = icmp ne i32 %0, 0, !dbg !597
  br i1 %tobool, label %if.then, label %if.end, !dbg !599

if.then:                                          ; preds = %entry
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.25, i32 0, i32 0)), !dbg !600
  br label %return, !dbg !602

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %params.addr, align 8, !dbg !603
  %call = call i32 (i8*, i8*, ...) @__isoc99_sscanf(i8* %1, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.26, i32 0, i32 0), i64* %a0, i64* %a1, i64* %a2, i64* %a3, i64* %p0, i64* %p1) #2, !dbg !604
  %2 = load i64, i64* %a0, align 8, !dbg !605
  %shl = shl i64 %2, 24, !dbg !606
  %3 = load i64, i64* %a1, align 8, !dbg !607
  %shl1 = shl i64 %3, 16, !dbg !608
  %add = add i64 %shl, %shl1, !dbg !609
  %4 = load i64, i64* %a2, align 8, !dbg !610
  %shl2 = shl i64 %4, 8, !dbg !611
  %add3 = add i64 %add, %shl2, !dbg !612
  %5 = load i64, i64* %a3, align 8, !dbg !613
  %add4 = add i64 %add3, %5, !dbg !614
  %conv = trunc i64 %add4 to i32, !dbg !615
  %call5 = call i32 @htonl(i32 %conv) #1, !dbg !616
  %conv6 = zext i32 %call5 to i64, !dbg !616
  store i64 %conv6, i64* %addr, align 8, !dbg !617
  %6 = load i64, i64* %addr, align 8, !dbg !618
  %7 = load i32, i32* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @remotename, i32 0, i32 2, i32 0), align 4, !dbg !620
  %conv7 = zext i32 %7 to i64, !dbg !621
  %cmp = icmp ne i64 %6, %conv7, !dbg !622
  br i1 %cmp, label %land.lhs.true, label %if.end13, !dbg !623

land.lhs.true:                                    ; preds = %if.end
  %call9 = call i8* @config_getoption(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.27, i32 0, i32 0)), !dbg !624
  %call10 = call i32 @strncasecmp(i8* %call9, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.8, i32 0, i32 0), i64 3) #9, !dbg !626
  %tobool11 = icmp ne i32 %call10, 0, !dbg !628
  br i1 %tobool11, label %if.then12, label %if.end13, !dbg !629

if.then12:                                        ; preds = %land.lhs.true
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.28, i32 0, i32 0)), !dbg !630
  br label %return, !dbg !632

if.end13:                                         ; preds = %land.lhs.true, %if.end
  %8 = load i64, i64* %addr, align 8, !dbg !633
  %conv14 = trunc i64 %8 to i32, !dbg !633
  store i32 %conv14, i32* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @sa, i32 0, i32 2, i32 0), align 4, !dbg !634
  %9 = load i64, i64* %p0, align 8, !dbg !635
  %shl15 = shl i64 %9, 8, !dbg !636
  %10 = load i64, i64* %p1, align 8, !dbg !637
  %add16 = add i64 %shl15, %10, !dbg !638
  %conv17 = trunc i64 %add16 to i16, !dbg !639
  %call18 = call zeroext i16 @htons(i16 zeroext %conv17) #1, !dbg !640
  store i16 %call18, i16* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @sa, i32 0, i32 1), align 2, !dbg !641
  %11 = load i8, i8* @pasv, align 1, !dbg !642
  %tobool19 = icmp ne i8 %11, 0, !dbg !642
  br i1 %tobool19, label %if.then20, label %if.end22, !dbg !644

if.then20:                                        ; preds = %if.end13
  %12 = load i32, i32* @sock, align 4, !dbg !645
  %call21 = call i32 @close(i32 %12), !dbg !647
  store i8 0, i8* @pasv, align 1, !dbg !648
  br label %if.end22, !dbg !649

if.end22:                                         ; preds = %if.then20, %if.end13
  %13 = load i64, i64* %a0, align 8, !dbg !650
  %14 = load i64, i64* %a1, align 8, !dbg !651
  %15 = load i64, i64* %a2, align 8, !dbg !652
  %16 = load i64, i64* %a3, align 8, !dbg !653
  %17 = load i64, i64* %p0, align 8, !dbg !654
  %shl23 = shl i64 %17, 8, !dbg !655
  %18 = load i64, i64* %p1, align 8, !dbg !656
  %add24 = add i64 %shl23, %18, !dbg !657
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.29, i32 0, i32 0), i64 %13, i64 %14, i64 %15, i64 %16, i64 %add24), !dbg !658
  br label %return, !dbg !659

return:                                           ; preds = %if.end22, %if.then12, %if.then
  ret void, !dbg !660
}

; Function Attrs: nounwind
declare i32 @__isoc99_sscanf(i8*, i8*, ...) #3

; Function Attrs: nounwind readnone
declare i32 @htonl(i32) #6

; Function Attrs: nounwind readonly
declare i32 @strncasecmp(i8*, i8*, i64) #7

; Function Attrs: nounwind uwtable
define void @command_eprt(i8* %params) #0 !dbg !134 {
entry:
  %params.addr = alloca i8*, align 8
  %delim = alloca i8, align 1
  %af = alloca i32, align 4
  %addr = alloca [51 x i8], align 16
  %foo = alloca [20 x i8], align 16
  %port = alloca i32, align 4
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !662, metadata !246), !dbg !663
  call void @llvm.dbg.declare(metadata i8* %delim, metadata !664, metadata !246), !dbg !665
  call void @llvm.dbg.declare(metadata i32* %af, metadata !666, metadata !246), !dbg !667
  call void @llvm.dbg.declare(metadata [51 x i8]* %addr, metadata !668, metadata !246), !dbg !672
  call void @llvm.dbg.declare(metadata [20 x i8]* %foo, metadata !673, metadata !246), !dbg !677
  call void @llvm.dbg.declare(metadata i32* %port, metadata !678, metadata !246), !dbg !679
  %0 = load i32, i32* @epsvall, align 4, !dbg !680
  %tobool = icmp ne i32 %0, 0, !dbg !680
  br i1 %tobool, label %if.then, label %if.end, !dbg !682

if.then:                                          ; preds = %entry
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.25, i32 0, i32 0)), !dbg !683
  br label %return, !dbg !685

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %params.addr, align 8, !dbg !686
  %call = call i64 @strlen(i8* %1) #9, !dbg !688
  %cmp = icmp ult i64 %call, 5, !dbg !689
  br i1 %cmp, label %if.then1, label %if.end2, !dbg !690

if.then1:                                         ; preds = %if.end
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.30, i32 0, i32 0)), !dbg !691
  br label %return, !dbg !693

if.end2:                                          ; preds = %if.end
  %2 = load i8*, i8** %params.addr, align 8, !dbg !694
  %arrayidx = getelementptr inbounds i8, i8* %2, i64 0, !dbg !694
  %3 = load i8, i8* %arrayidx, align 1, !dbg !694
  store i8 %3, i8* %delim, align 1, !dbg !695
  %arraydecay = getelementptr inbounds [20 x i8], [20 x i8]* %foo, i32 0, i32 0, !dbg !696
  %4 = load i8, i8* %delim, align 1, !dbg !697
  %conv = sext i8 %4 to i32, !dbg !697
  %5 = load i8, i8* %delim, align 1, !dbg !698
  %conv3 = sext i8 %5 to i32, !dbg !698
  %6 = load i8, i8* %delim, align 1, !dbg !699
  %conv4 = sext i8 %6 to i32, !dbg !699
  %7 = load i8, i8* %delim, align 1, !dbg !700
  %conv5 = sext i8 %7 to i32, !dbg !700
  %8 = load i8, i8* %delim, align 1, !dbg !701
  %conv6 = sext i8 %8 to i32, !dbg !701
  %call7 = call i32 (i8*, i8*, ...) @sprintf(i8* %arraydecay, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.31, i32 0, i32 0), i32 %conv, i32 %conv3, i32 %conv4, i32 %conv5, i32 %conv6) #2, !dbg !702
  %9 = load i8*, i8** %params.addr, align 8, !dbg !703
  %arraydecay8 = getelementptr inbounds [20 x i8], [20 x i8]* %foo, i32 0, i32 0, !dbg !705
  %arraydecay9 = getelementptr inbounds [51 x i8], [51 x i8]* %addr, i32 0, i32 0, !dbg !706
  %call10 = call i32 (i8*, i8*, ...) @__isoc99_sscanf(i8* %9, i8* %arraydecay8, i32* %af, i8* %arraydecay9, i32* %port) #2, !dbg !707
  %cmp11 = icmp slt i32 %call10, 3, !dbg !708
  br i1 %cmp11, label %if.then13, label %if.end14, !dbg !709

if.then13:                                        ; preds = %if.end2
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.30, i32 0, i32 0)), !dbg !710
  br label %return, !dbg !712

if.end14:                                         ; preds = %if.end2
  %10 = load i32, i32* %af, align 4, !dbg !713
  %cmp15 = icmp ne i32 %10, 1, !dbg !715
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !716

if.then17:                                        ; preds = %if.end14
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.32, i32 0, i32 0)), !dbg !717
  br label %return, !dbg !719

if.end18:                                         ; preds = %if.end14
  %arraydecay19 = getelementptr inbounds [51 x i8], [51 x i8]* %addr, i32 0, i32 0, !dbg !720
  %call20 = call i32 @inet_addr(i8* %arraydecay19) #2, !dbg !721
  store i32 %call20, i32* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @sa, i32 0, i32 2, i32 0), align 4, !dbg !722
  %11 = load i32, i32* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @sa, i32 0, i32 2, i32 0), align 4, !dbg !723
  %12 = load i32, i32* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @remotename, i32 0, i32 2, i32 0), align 4, !dbg !725
  %cmp21 = icmp ne i32 %11, %12, !dbg !726
  br i1 %cmp21, label %land.lhs.true, label %if.end27, !dbg !727

land.lhs.true:                                    ; preds = %if.end18
  %call23 = call i8* @config_getoption(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.27, i32 0, i32 0)), !dbg !728
  %call24 = call i32 @strncasecmp(i8* %call23, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.8, i32 0, i32 0), i64 3) #9, !dbg !730
  %tobool25 = icmp ne i32 %call24, 0, !dbg !732
  br i1 %tobool25, label %if.then26, label %if.end27, !dbg !733

if.then26:                                        ; preds = %land.lhs.true
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.28, i32 0, i32 0)), !dbg !734
  br label %return, !dbg !736

if.end27:                                         ; preds = %land.lhs.true, %if.end18
  %13 = load i32, i32* %port, align 4, !dbg !737
  %conv28 = trunc i32 %13 to i16, !dbg !737
  %call29 = call zeroext i16 @htons(i16 zeroext %conv28) #1, !dbg !738
  store i16 %call29, i16* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @sa, i32 0, i32 1), align 2, !dbg !739
  %14 = load i8, i8* @pasv, align 1, !dbg !740
  %tobool30 = icmp ne i8 %14, 0, !dbg !740
  br i1 %tobool30, label %if.then31, label %if.end33, !dbg !742

if.then31:                                        ; preds = %if.end27
  %15 = load i32, i32* @sock, align 4, !dbg !743
  %call32 = call i32 @close(i32 %15), !dbg !745
  store i8 0, i8* @pasv, align 1, !dbg !746
  br label %if.end33, !dbg !747

if.end33:                                         ; preds = %if.then31, %if.end27
  %arraydecay34 = getelementptr inbounds [51 x i8], [51 x i8]* %addr, i32 0, i32 0, !dbg !748
  %16 = load i32, i32* %port, align 4, !dbg !749
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.33, i32 0, i32 0), i8* %arraydecay34, i32 %16), !dbg !750
  br label %return, !dbg !751

return:                                           ; preds = %if.end33, %if.then26, %if.then17, %if.then13, %if.then1, %if.then
  ret void, !dbg !752
}

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #7

; Function Attrs: nounwind
declare i32 @sprintf(i8*, i8*, ...) #3

; Function Attrs: nounwind
declare i32 @inet_addr(i8*) #3

; Function Attrs: nounwind uwtable
define void @command_pasv(i8* %foo) #0 !dbg !135 {
entry:
  %foo.addr = alloca i8*, align 8
  %a1 = alloca i32, align 4
  %a2 = alloca i32, align 4
  %a3 = alloca i32, align 4
  %a4 = alloca i32, align 4
  %namelen = alloca i32, align 4
  %localsock = alloca %struct.sockaddr_in, align 4
  %my_override_ip = alloca i8*, align 8
  %agg.tmp = alloca %union.__CONST_SOCKADDR_ARG, align 8
  %i = alloca i32, align 4
  %success = alloca i32, align 4
  %port = alloca i32, align 4
  %agg.tmp18 = alloca %union.__CONST_SOCKADDR_ARG, align 8
  %agg.tmp36 = alloca %union.__SOCKADDR_ARG, align 8
  store i8* %foo, i8** %foo.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %foo.addr, metadata !754, metadata !246), !dbg !755
  call void @llvm.dbg.declare(metadata i32* %a1, metadata !756, metadata !246), !dbg !757
  call void @llvm.dbg.declare(metadata i32* %a2, metadata !758, metadata !246), !dbg !759
  call void @llvm.dbg.declare(metadata i32* %a3, metadata !760, metadata !246), !dbg !761
  call void @llvm.dbg.declare(metadata i32* %a4, metadata !762, metadata !246), !dbg !763
  call void @llvm.dbg.declare(metadata i32* %namelen, metadata !764, metadata !246), !dbg !765
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in* %localsock, metadata !766, metadata !246), !dbg !767
  call void @llvm.dbg.declare(metadata i8** %my_override_ip, metadata !768, metadata !246), !dbg !769
  %0 = load i32, i32* @epsvall, align 4, !dbg !770
  %tobool = icmp ne i32 %0, 0, !dbg !770
  br i1 %tobool, label %if.then, label %if.end, !dbg !772

if.then:                                          ; preds = %entry
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.25, i32 0, i32 0)), !dbg !773
  br label %return, !dbg !775

if.end:                                           ; preds = %entry
  %call = call i32 @socket(i32 2, i32 1, i32 0) #2, !dbg !776
  store i32 %call, i32* @pasvsock, align 4, !dbg !777
  store i32 0, i32* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @sa, i32 0, i32 2, i32 0), align 4, !dbg !778
  store i16 2, i16* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @sa, i32 0, i32 0), align 4, !dbg !779
  %call1 = call i8* @config_getoption(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.34, i32 0, i32 0)), !dbg !780
  %tobool2 = icmp ne i8* %call1, null, !dbg !780
  br i1 %tobool2, label %lor.lhs.false, label %if.then6, !dbg !782

lor.lhs.false:                                    ; preds = %if.end
  %call3 = call i8* @config_getoption(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.34, i32 0, i32 0)), !dbg !783
  %call4 = call i64 @strlen(i8* %call3) #9, !dbg !785
  %tobool5 = icmp ne i64 %call4, 0, !dbg !787
  br i1 %tobool5, label %if.else, label %if.then6, !dbg !788

if.then6:                                         ; preds = %lor.lhs.false, %if.end
  store i16 0, i16* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @sa, i32 0, i32 1), align 2, !dbg !789
  %1 = load i32, i32* @pasvsock, align 4, !dbg !791
  %__sockaddr__ = bitcast %union.__CONST_SOCKADDR_ARG* %agg.tmp to %struct.sockaddr**, !dbg !793
  store %struct.sockaddr* bitcast (%struct.sockaddr_in* @sa to %struct.sockaddr*), %struct.sockaddr** %__sockaddr__, align 8, !dbg !793
  %coerce.dive = getelementptr inbounds %union.__CONST_SOCKADDR_ARG, %union.__CONST_SOCKADDR_ARG* %agg.tmp, i32 0, i32 0, !dbg !794
  %2 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive, align 8, !dbg !794
  %call7 = call i32 @bind(i32 %1, %struct.sockaddr* %2, i32 16) #2, !dbg !794
  %cmp = icmp eq i32 %call7, -1, !dbg !795
  br i1 %cmp, label %if.then8, label %if.end11, !dbg !796

if.then8:                                         ; preds = %if.then6
  %call9 = call i32* @__errno_location() #1, !dbg !797
  %3 = load i32, i32* %call9, align 4, !dbg !797
  %call10 = call i8* @strerror(i32 %3) #2, !dbg !799
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.35, i32 0, i32 0), i8* %call10), !dbg !801
  br label %return, !dbg !803

if.end11:                                         ; preds = %if.then6
  br label %if.end29, !dbg !804

if.else:                                          ; preds = %lor.lhs.false
  call void @llvm.dbg.declare(metadata i32* %i, metadata !805, metadata !246), !dbg !807
  store i32 0, i32* %i, align 4, !dbg !807
  call void @llvm.dbg.declare(metadata i32* %success, metadata !808, metadata !246), !dbg !809
  store i32 0, i32* %success, align 4, !dbg !809
  call void @llvm.dbg.declare(metadata i32* %port, metadata !810, metadata !246), !dbg !811
  br label %for.cond, !dbg !812

for.cond:                                         ; preds = %if.end25, %if.else
  %call12 = call i8* @config_getoption(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.34, i32 0, i32 0)), !dbg !813
  %4 = load i32, i32* %i, align 4, !dbg !817
  %inc = add nsw i32 %4, 1, !dbg !817
  store i32 %inc, i32* %i, align 4, !dbg !817
  %call13 = call i32 @int_from_list(i8* %call12, i32 %4), !dbg !818
  store i32 %call13, i32* %port, align 4, !dbg !820
  %5 = load i32, i32* %port, align 4, !dbg !821
  %cmp14 = icmp slt i32 %5, 0, !dbg !823
  br i1 %cmp14, label %if.then15, label %if.end16, !dbg !824

if.then15:                                        ; preds = %for.cond
  br label %for.end, !dbg !825

if.end16:                                         ; preds = %for.cond
  %6 = load i32, i32* %port, align 4, !dbg !826
  %conv = trunc i32 %6 to i16, !dbg !826
  %call17 = call zeroext i16 @htons(i16 zeroext %conv) #1, !dbg !827
  store i16 %call17, i16* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @sa, i32 0, i32 1), align 2, !dbg !828
  %7 = load i32, i32* @pasvsock, align 4, !dbg !829
  %__sockaddr__19 = bitcast %union.__CONST_SOCKADDR_ARG* %agg.tmp18 to %struct.sockaddr**, !dbg !831
  store %struct.sockaddr* bitcast (%struct.sockaddr_in* @sa to %struct.sockaddr*), %struct.sockaddr** %__sockaddr__19, align 8, !dbg !831
  %coerce.dive20 = getelementptr inbounds %union.__CONST_SOCKADDR_ARG, %union.__CONST_SOCKADDR_ARG* %agg.tmp18, i32 0, i32 0, !dbg !832
  %8 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive20, align 8, !dbg !832
  %call21 = call i32 @bind(i32 %7, %struct.sockaddr* %8, i32 16) #2, !dbg !832
  %cmp22 = icmp eq i32 %call21, 0, !dbg !833
  br i1 %cmp22, label %if.then24, label %if.end25, !dbg !834

if.then24:                                        ; preds = %if.end16
  store i32 1, i32* %success, align 4, !dbg !835
  br label %for.end, !dbg !837

if.end25:                                         ; preds = %if.end16
  br label %for.cond, !dbg !838

for.end:                                          ; preds = %if.then24, %if.then15
  %9 = load i32, i32* %success, align 4, !dbg !840
  %tobool26 = icmp ne i32 %9, 0, !dbg !840
  br i1 %tobool26, label %if.end28, label %if.then27, !dbg !842

if.then27:                                        ; preds = %for.end
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.36, i32 0, i32 0)), !dbg !843
  br label %return, !dbg !845

if.end28:                                         ; preds = %for.end
  %10 = load i32, i32* @pasvsock, align 4, !dbg !846
  call void @prepare_sock(i32 %10), !dbg !847
  br label %if.end29

if.end29:                                         ; preds = %if.end28, %if.end11
  %11 = load i32, i32* @pasvsock, align 4, !dbg !848
  %call30 = call i32 @listen(i32 %11, i32 1) #2, !dbg !850
  %tobool31 = icmp ne i32 %call30, 0, !dbg !850
  br i1 %tobool31, label %if.then32, label %if.end35, !dbg !851

if.then32:                                        ; preds = %if.end29
  %call33 = call i32* @__errno_location() #1, !dbg !852
  %12 = load i32, i32* %call33, align 4, !dbg !852
  %call34 = call i8* @strerror(i32 %12) #2, !dbg !854
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str.37, i32 0, i32 0), i8* %call34), !dbg !856
  br label %return, !dbg !857

if.end35:                                         ; preds = %if.end29
  store i32 16, i32* %namelen, align 4, !dbg !858
  %13 = load i32, i32* @pasvsock, align 4, !dbg !859
  %__sockaddr__37 = bitcast %union.__SOCKADDR_ARG* %agg.tmp36 to %struct.sockaddr**, !dbg !860
  %14 = bitcast %struct.sockaddr_in* %localsock to %struct.sockaddr*, !dbg !860
  store %struct.sockaddr* %14, %struct.sockaddr** %__sockaddr__37, align 8, !dbg !860
  %coerce.dive38 = getelementptr inbounds %union.__SOCKADDR_ARG, %union.__SOCKADDR_ARG* %agg.tmp36, i32 0, i32 0, !dbg !861
  %15 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive38, align 8, !dbg !861
  %call39 = call i32 @getsockname(i32 %13, %struct.sockaddr* %15, i32* %namelen) #2, !dbg !861
  %call40 = call i8* @config_getoption(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.38, i32 0, i32 0)), !dbg !862
  store i8* %call40, i8** %my_override_ip, align 8, !dbg !863
  %16 = load i8*, i8** %my_override_ip, align 8, !dbg !864
  %arrayidx = getelementptr inbounds i8, i8* %16, i64 0, !dbg !864
  %17 = load i8, i8* %arrayidx, align 1, !dbg !864
  %tobool41 = icmp ne i8 %17, 0, !dbg !864
  br i1 %tobool41, label %if.then42, label %if.else44, !dbg !866

if.then42:                                        ; preds = %if.end35
  %18 = load i8*, i8** %my_override_ip, align 8, !dbg !867
  %call43 = call i32 (i8*, i8*, ...) @__isoc99_sscanf(i8* %18, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.39, i32 0, i32 0), i32* %a1, i32* %a2, i32* %a3, i32* %a4) #2, !dbg !869
  br label %if.end47, !dbg !870

if.else44:                                        ; preds = %if.end35
  %19 = load i32, i32* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @name, i32 0, i32 2, i32 0), align 4, !dbg !871
  %call45 = call i8* @inet_ntoa(i32 %19) #2, !dbg !871
  %call46 = call i32 (i8*, i8*, ...) @__isoc99_sscanf(i8* %call45, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.39, i32 0, i32 0), i32* %a1, i32* %a2, i32* %a3, i32* %a4) #2, !dbg !873
  br label %if.end47

if.end47:                                         ; preds = %if.else44, %if.then42
  %20 = load i32, i32* %a1, align 4, !dbg !875
  %21 = load i32, i32* %a2, align 4, !dbg !876
  %22 = load i32, i32* %a3, align 4, !dbg !877
  %23 = load i32, i32* %a4, align 4, !dbg !878
  %sin_port = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %localsock, i32 0, i32 1, !dbg !879
  %24 = load i16, i16* %sin_port, align 2, !dbg !879
  %call48 = call zeroext i16 @ntohs(i16 zeroext %24) #1, !dbg !880
  %conv49 = zext i16 %call48 to i32, !dbg !880
  %shr = ashr i32 %conv49, 8, !dbg !881
  %sin_port50 = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %localsock, i32 0, i32 1, !dbg !882
  %25 = load i16, i16* %sin_port50, align 2, !dbg !882
  %call51 = call zeroext i16 @ntohs(i16 zeroext %25) #1, !dbg !883
  %conv52 = zext i16 %call51 to i32, !dbg !885
  %and = and i32 %conv52, 255, !dbg !886
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([46 x i8], [46 x i8]* @.str.40, i32 0, i32 0), i32 %20, i32 %21, i32 %22, i32 %23, i32 %shr, i32 %and), !dbg !887
  store i8 1, i8* @pasv, align 1, !dbg !888
  br label %return, !dbg !889

return:                                           ; preds = %if.end47, %if.then32, %if.then27, %if.then8, %if.then
  ret void, !dbg !890
}

declare i32 @int_from_list(i8*, i32) #4

; Function Attrs: nounwind
declare i32 @listen(i32, i32) #3

; Function Attrs: nounwind
declare i32 @getsockname(i32, %struct.sockaddr*, i32*) #3

; Function Attrs: nounwind
declare i8* @inet_ntoa(i32) #3

; Function Attrs: nounwind readnone
declare zeroext i16 @ntohs(i16 zeroext) #6

; Function Attrs: nounwind uwtable
define void @command_epsv(i8* %params) #0 !dbg !136 {
entry:
  %params.addr = alloca i8*, align 8
  %localsock = alloca %struct.sockaddr_in, align 4
  %namelen = alloca i32, align 4
  %af = alloca i32, align 4
  %agg.tmp = alloca %union.__CONST_SOCKADDR_ARG, align 8
  %agg.tmp24 = alloca %union.__SOCKADDR_ARG, align 8
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !891, metadata !246), !dbg !892
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in* %localsock, metadata !893, metadata !246), !dbg !894
  call void @llvm.dbg.declare(metadata i32* %namelen, metadata !895, metadata !246), !dbg !896
  call void @llvm.dbg.declare(metadata i32* %af, metadata !897, metadata !246), !dbg !898
  %0 = load i8*, i8** %params.addr, align 8, !dbg !899
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !899
  %1 = load i8, i8* %arrayidx, align 1, !dbg !899
  %tobool = icmp ne i8 %1, 0, !dbg !899
  br i1 %tobool, label %if.then, label %if.end10, !dbg !901

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** %params.addr, align 8, !dbg !902
  %call = call i32 @strncasecmp(i8* %2, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.41, i32 0, i32 0), i64 3) #9, !dbg !905
  %tobool1 = icmp ne i32 %call, 0, !dbg !905
  br i1 %tobool1, label %if.else, label %if.then2, !dbg !906

if.then2:                                         ; preds = %if.then
  store i32 1, i32* @epsvall, align 4, !dbg !907
  br label %if.end9, !dbg !908

if.else:                                          ; preds = %if.then
  %3 = load i8*, i8** %params.addr, align 8, !dbg !909
  %call3 = call i32 (i8*, i8*, ...) @__isoc99_sscanf(i8* %3, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.42, i32 0, i32 0), i32* %af) #2, !dbg !912
  %cmp = icmp slt i32 %call3, 1, !dbg !913
  br i1 %cmp, label %if.then4, label %if.else5, !dbg !914

if.then4:                                         ; preds = %if.else
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.30, i32 0, i32 0)), !dbg !915
  br label %return, !dbg !917

if.else5:                                         ; preds = %if.else
  %4 = load i32, i32* %af, align 4, !dbg !918
  %cmp6 = icmp ne i32 %4, 1, !dbg !921
  br i1 %cmp6, label %if.then7, label %if.end, !dbg !922

if.then7:                                         ; preds = %if.else5
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.32, i32 0, i32 0)), !dbg !923
  br label %return, !dbg !925

if.end:                                           ; preds = %if.else5
  br label %if.end8

if.end8:                                          ; preds = %if.end
  br label %if.end9

if.end9:                                          ; preds = %if.end8, %if.then2
  br label %if.end10, !dbg !926

if.end10:                                         ; preds = %if.end9, %entry
  %call11 = call i32 @socket(i32 2, i32 1, i32 0) #2, !dbg !927
  store i32 %call11, i32* @pasvsock, align 4, !dbg !928
  store i32 0, i32* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @sa, i32 0, i32 2, i32 0), align 4, !dbg !929
  store i16 0, i16* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @sa, i32 0, i32 1), align 2, !dbg !930
  store i16 2, i16* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @sa, i32 0, i32 0), align 4, !dbg !931
  %5 = load i32, i32* @pasvsock, align 4, !dbg !932
  %__sockaddr__ = bitcast %union.__CONST_SOCKADDR_ARG* %agg.tmp to %struct.sockaddr**, !dbg !934
  store %struct.sockaddr* bitcast (%struct.sockaddr_in* @sa to %struct.sockaddr*), %struct.sockaddr** %__sockaddr__, align 8, !dbg !934
  %coerce.dive = getelementptr inbounds %union.__CONST_SOCKADDR_ARG, %union.__CONST_SOCKADDR_ARG* %agg.tmp, i32 0, i32 0, !dbg !935
  %6 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive, align 8, !dbg !935
  %call12 = call i32 @bind(i32 %5, %struct.sockaddr* %6, i32 16) #2, !dbg !935
  %cmp13 = icmp eq i32 %call12, -1, !dbg !936
  br i1 %cmp13, label %if.then14, label %if.end17, !dbg !937

if.then14:                                        ; preds = %if.end10
  %call15 = call i32* @__errno_location() #1, !dbg !938
  %7 = load i32, i32* %call15, align 4, !dbg !938
  %call16 = call i8* @strerror(i32 %7) #2, !dbg !940
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.43, i32 0, i32 0), i8* %call16), !dbg !942
  br label %return, !dbg !943

if.end17:                                         ; preds = %if.end10
  %8 = load i32, i32* @pasvsock, align 4, !dbg !944
  %call18 = call i32 @listen(i32 %8, i32 1) #2, !dbg !946
  %tobool19 = icmp ne i32 %call18, 0, !dbg !946
  br i1 %tobool19, label %if.then20, label %if.end23, !dbg !947

if.then20:                                        ; preds = %if.end17
  %call21 = call i32* @__errno_location() #1, !dbg !948
  %9 = load i32, i32* %call21, align 4, !dbg !948
  %call22 = call i8* @strerror(i32 %9) #2, !dbg !950
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str.44, i32 0, i32 0), i8* %call22), !dbg !952
  br label %return, !dbg !953

if.end23:                                         ; preds = %if.end17
  store i32 16, i32* %namelen, align 4, !dbg !954
  %10 = load i32, i32* @pasvsock, align 4, !dbg !955
  %__sockaddr__25 = bitcast %union.__SOCKADDR_ARG* %agg.tmp24 to %struct.sockaddr**, !dbg !956
  %11 = bitcast %struct.sockaddr_in* %localsock to %struct.sockaddr*, !dbg !956
  store %struct.sockaddr* %11, %struct.sockaddr** %__sockaddr__25, align 8, !dbg !956
  %coerce.dive26 = getelementptr inbounds %union.__SOCKADDR_ARG, %union.__SOCKADDR_ARG* %agg.tmp24, i32 0, i32 0, !dbg !957
  %12 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive26, align 8, !dbg !957
  %call27 = call i32 @getsockname(i32 %10, %struct.sockaddr* %12, i32* %namelen) #2, !dbg !957
  %sin_port = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %localsock, i32 0, i32 1, !dbg !958
  %13 = load i16, i16* %sin_port, align 2, !dbg !958
  %call28 = call zeroext i16 @ntohs(i16 zeroext %13) #1, !dbg !959
  %conv = zext i16 %call28 to i32, !dbg !959
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.45, i32 0, i32 0), i32 %conv), !dbg !960
  store i8 1, i8* @pasv, align 1, !dbg !961
  br label %return, !dbg !962

return:                                           ; preds = %if.end23, %if.then20, %if.then14, %if.then7, %if.then4
  ret void, !dbg !963
}

; Function Attrs: nounwind uwtable
define signext i8 @test_abort(i8 signext %selectbefore, i32 %file, i32 %sock) #0 !dbg !137 {
entry:
  %retval = alloca i8, align 1
  %selectbefore.addr = alloca i8, align 1
  %file.addr = alloca i32, align 4
  %sock.addr = alloca i32, align 4
  %str = alloca [256 x i8], align 16
  %rfds = alloca %struct.fd_set, align 8
  %tv = alloca %struct.timeval, align 8
  %result = alloca i8*, align 8
  %__d0 = alloca i32, align 4
  %__d1 = alloca i32, align 4
  store i8 %selectbefore, i8* %selectbefore.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %selectbefore.addr, metadata !965, metadata !246), !dbg !966
  store i32 %file, i32* %file.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %file.addr, metadata !967, metadata !246), !dbg !968
  store i32 %sock, i32* %sock.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sock.addr, metadata !969, metadata !246), !dbg !970
  call void @llvm.dbg.declare(metadata [256 x i8]* %str, metadata !971, metadata !246), !dbg !975
  call void @llvm.dbg.declare(metadata %struct.fd_set* %rfds, metadata !976, metadata !246), !dbg !984
  call void @llvm.dbg.declare(metadata %struct.timeval* %tv, metadata !985, metadata !246), !dbg !992
  call void @llvm.dbg.declare(metadata i8** %result, metadata !993, metadata !246), !dbg !994
  %0 = load i8, i8* %selectbefore.addr, align 1, !dbg !995
  %tobool = icmp ne i8 %0, 0, !dbg !995
  br i1 %tobool, label %if.then, label %if.end9, !dbg !997

if.then:                                          ; preds = %entry
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %tv, i32 0, i32 0, !dbg !998
  store i64 0, i64* %tv_sec, align 8, !dbg !1000
  %tv_usec = getelementptr inbounds %struct.timeval, %struct.timeval* %tv, i32 0, i32 1, !dbg !1001
  store i64 0, i64* %tv_usec, align 8, !dbg !1002
  br label %do.body, !dbg !1003

do.body:                                          ; preds = %if.then
  call void @llvm.dbg.declare(metadata i32* %__d0, metadata !1004, metadata !246), !dbg !1006
  call void @llvm.dbg.declare(metadata i32* %__d1, metadata !1007, metadata !246), !dbg !1006
  %__fds_bits = getelementptr inbounds %struct.fd_set, %struct.fd_set* %rfds, i32 0, i32 0, !dbg !1008
  %arrayidx = getelementptr inbounds [16 x i64], [16 x i64]* %__fds_bits, i64 0, i64 0, !dbg !1008
  %1 = call { i64, i64* } asm sideeffect "cld; rep; stosq", "={cx},={di},{ax},0,1,~{memory},~{dirflag},~{fpsr},~{flags}"(i32 0, i64 16, i64* %arrayidx) #2, !dbg !1008, !srcloc !1010
  %asmresult = extractvalue { i64, i64* } %1, 0, !dbg !1008
  %asmresult1 = extractvalue { i64, i64* } %1, 1, !dbg !1008
  %2 = trunc i64 %asmresult to i32, !dbg !1008
  store i32 %2, i32* %__d0, align 4, !dbg !1008
  %3 = ptrtoint i64* %asmresult1 to i64, !dbg !1008
  %4 = trunc i64 %3 to i32, !dbg !1008
  store i32 %4, i32* %__d1, align 4, !dbg !1008
  br label %do.end, !dbg !1008

do.end:                                           ; preds = %do.body
  %5 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !1011
  %call = call i32 @fileno(%struct._IO_FILE* %5) #2, !dbg !1011
  %rem = srem i32 %call, 64, !dbg !1011
  %sh_prom = zext i32 %rem to i64, !dbg !1011
  %shl = shl i64 1, %sh_prom, !dbg !1011
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !1011
  %call2 = call i32 @fileno(%struct._IO_FILE* %6) #2, !dbg !1012
  %div = sdiv i32 %call2, 64, !dbg !1011
  %idxprom = sext i32 %div to i64, !dbg !1011
  %__fds_bits3 = getelementptr inbounds %struct.fd_set, %struct.fd_set* %rfds, i32 0, i32 0, !dbg !1011
  %arrayidx4 = getelementptr inbounds [16 x i64], [16 x i64]* %__fds_bits3, i64 0, i64 %idxprom, !dbg !1011
  %7 = load i64, i64* %arrayidx4, align 8, !dbg !1011
  %or = or i64 %7, %shl, !dbg !1011
  store i64 %or, i64* %arrayidx4, align 8, !dbg !1011
  %8 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !1014
  %call5 = call i32 @fileno(%struct._IO_FILE* %8) #2, !dbg !1016
  %add = add nsw i32 %call5, 1, !dbg !1017
  %call6 = call i32 @select(i32 %add, %struct.fd_set* %rfds, %struct.fd_set* null, %struct.fd_set* null, %struct.timeval* %tv), !dbg !1018
  %tobool7 = icmp ne i32 %call6, 0, !dbg !1020
  br i1 %tobool7, label %if.end, label %if.then8, !dbg !1021

if.then8:                                         ; preds = %do.end
  store i8 0, i8* %retval, align 1, !dbg !1022
  br label %return, !dbg !1022

if.end:                                           ; preds = %do.end
  br label %if.end9, !dbg !1023

if.end9:                                          ; preds = %if.end, %entry
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %str, i32 0, i32 0, !dbg !1024
  %9 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !1025
  %call10 = call i8* @fgets(i8* %arraydecay, i32 256, %struct._IO_FILE* %9), !dbg !1026
  store i8* %call10, i8** %result, align 8, !dbg !1027
  %10 = load i8*, i8** %result, align 8, !dbg !1028
  %tobool11 = icmp ne i8* %10, null, !dbg !1030
  br i1 %tobool11, label %land.lhs.true, label %if.end19, !dbg !1031

land.lhs.true:                                    ; preds = %if.end9
  %arraydecay12 = getelementptr inbounds [256 x i8], [256 x i8]* %str, i32 0, i32 0, !dbg !1032
  %call13 = call i8* @strstr(i8* %arraydecay12, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.46, i32 0, i32 0)) #9, !dbg !1034
  %tobool14 = icmp ne i8* %call13, null, !dbg !1034
  br i1 %tobool14, label %if.then15, label %if.end19, !dbg !1035

if.then15:                                        ; preds = %land.lhs.true
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.47, i32 0, i32 0)), !dbg !1036
  %11 = load i32, i32* %file.addr, align 4, !dbg !1038
  %call16 = call i32 @close(i32 %11), !dbg !1039
  %12 = load i32, i32* %sock.addr, align 4, !dbg !1040
  %call17 = call i32 @close(i32 %12), !dbg !1041
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.48, i32 0, i32 0)), !dbg !1042
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.49, i32 0, i32 0)), !dbg !1043
  %13 = load i32, i32* @control_timeout, align 4, !dbg !1044
  %call18 = call i32 @alarm(i32 %13) #2, !dbg !1045
  store i8 1, i8* %retval, align 1, !dbg !1046
  br label %return, !dbg !1046

if.end19:                                         ; preds = %land.lhs.true, %if.end9
  store i8 0, i8* %retval, align 1, !dbg !1047
  br label %return, !dbg !1047

return:                                           ; preds = %if.end19, %if.then15, %if.then8
  %14 = load i8, i8* %retval, align 1, !dbg !1048
  ret i8 %14, !dbg !1048
}

; Function Attrs: nounwind
declare i32 @fileno(%struct._IO_FILE*) #3

declare i32 @select(i32, %struct.fd_set*, %struct.fd_set*, %struct.fd_set*, %struct.timeval*) #4

declare i8* @fgets(i8*, i32, %struct._IO_FILE*) #4

; Function Attrs: nounwind readonly
declare i8* @strstr(i8*, i8*) #7

; Function Attrs: nounwind
declare i32 @alarm(i32) #3

; Function Attrs: nounwind uwtable
define void @command_allo(i8* %foo) #0 !dbg !140 {
entry:
  %foo.addr = alloca i8*, align 8
  store i8* %foo, i8** %foo.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %foo.addr, metadata !1049, metadata !246), !dbg !1050
  %0 = load i8*, i8** %foo.addr, align 8, !dbg !1051
  call void @command_noop(i8* %0), !dbg !1052
  ret void, !dbg !1053
}

; Function Attrs: nounwind uwtable
define void @command_noop(i8* %params) #0 !dbg !161 {
entry:
  %params.addr = alloca i8*, align 8
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !1054, metadata !246), !dbg !1055
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.99, i32 0, i32 0)), !dbg !1056
  ret void, !dbg !1057
}

; Function Attrs: nounwind uwtable
define void @command_mput(i8* %filenames) #0 !dbg !141 {
entry:
  %filenames.addr = alloca i8*, align 8
  %filename = alloca [255 x i8], align 16
  %from_index = alloca i32, align 4
  %to_index = alloca i32, align 4
  store i8* %filenames, i8** %filenames.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filenames.addr, metadata !1058, metadata !246), !dbg !1059
  call void @llvm.dbg.declare(metadata [255 x i8]* %filename, metadata !1060, metadata !246), !dbg !1064
  call void @llvm.dbg.declare(metadata i32* %from_index, metadata !1065, metadata !246), !dbg !1066
  call void @llvm.dbg.declare(metadata i32* %to_index, metadata !1067, metadata !246), !dbg !1068
  store i32 0, i32* %from_index, align 4, !dbg !1069
  %arraydecay = getelementptr inbounds [255 x i8], [255 x i8]* %filename, i32 0, i32 0, !dbg !1070
  call void @llvm.memset.p0i8.i64(i8* %arraydecay, i8 0, i64 255, i32 16, i1 false), !dbg !1070
  store i32 0, i32* %to_index, align 4, !dbg !1071
  br label %while.cond, !dbg !1072

while.cond:                                       ; preds = %if.end32, %entry
  %0 = load i32, i32* %from_index, align 4, !dbg !1073
  %idxprom = sext i32 %0 to i64, !dbg !1075
  %1 = load i8*, i8** %filenames.addr, align 8, !dbg !1075
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 %idxprom, !dbg !1075
  %2 = load i8, i8* %arrayidx, align 1, !dbg !1075
  %conv = sext i8 %2 to i32, !dbg !1075
  %cmp = icmp sgt i32 %conv, 0, !dbg !1076
  br i1 %cmp, label %while.body, label %while.end33, !dbg !1077

while.body:                                       ; preds = %while.cond
  %3 = load i32, i32* %from_index, align 4, !dbg !1078
  %idxprom2 = sext i32 %3 to i64, !dbg !1081
  %4 = load i8*, i8** %filenames.addr, align 8, !dbg !1081
  %arrayidx3 = getelementptr inbounds i8, i8* %4, i64 %idxprom2, !dbg !1081
  %5 = load i8, i8* %arrayidx3, align 1, !dbg !1081
  %conv4 = sext i8 %5 to i32, !dbg !1081
  %cmp5 = icmp eq i32 %conv4, 32, !dbg !1082
  br i1 %cmp5, label %if.then, label %if.else, !dbg !1083

if.then:                                          ; preds = %while.body
  %arraydecay7 = getelementptr inbounds [255 x i8], [255 x i8]* %filename, i32 0, i32 0, !dbg !1084
  call void @command_stor(i8* %arraydecay7), !dbg !1086
  store i32 0, i32* %to_index, align 4, !dbg !1087
  %arraydecay8 = getelementptr inbounds [255 x i8], [255 x i8]* %filename, i32 0, i32 0, !dbg !1088
  call void @llvm.memset.p0i8.i64(i8* %arraydecay8, i8 0, i64 255, i32 16, i1 false), !dbg !1088
  br label %while.cond9, !dbg !1089

while.cond9:                                      ; preds = %while.body15, %if.then
  %6 = load i32, i32* %from_index, align 4, !dbg !1090
  %idxprom10 = sext i32 %6 to i64, !dbg !1092
  %7 = load i8*, i8** %filenames.addr, align 8, !dbg !1092
  %arrayidx11 = getelementptr inbounds i8, i8* %7, i64 %idxprom10, !dbg !1092
  %8 = load i8, i8* %arrayidx11, align 1, !dbg !1092
  %conv12 = sext i8 %8 to i32, !dbg !1092
  %cmp13 = icmp eq i32 %conv12, 32, !dbg !1093
  br i1 %cmp13, label %while.body15, label %while.end, !dbg !1094

while.body15:                                     ; preds = %while.cond9
  %9 = load i32, i32* %from_index, align 4, !dbg !1095
  %inc = add nsw i32 %9, 1, !dbg !1095
  store i32 %inc, i32* %from_index, align 4, !dbg !1095
  br label %while.cond9, !dbg !1096

while.end:                                        ; preds = %while.cond9
  br label %if.end28, !dbg !1098

if.else:                                          ; preds = %while.body
  %10 = load i32, i32* %from_index, align 4, !dbg !1099
  %idxprom16 = sext i32 %10 to i64, !dbg !1101
  %11 = load i8*, i8** %filenames.addr, align 8, !dbg !1101
  %arrayidx17 = getelementptr inbounds i8, i8* %11, i64 %idxprom16, !dbg !1101
  %12 = load i8, i8* %arrayidx17, align 1, !dbg !1101
  %13 = load i32, i32* %to_index, align 4, !dbg !1102
  %idxprom18 = sext i32 %13 to i64, !dbg !1103
  %arrayidx19 = getelementptr inbounds [255 x i8], [255 x i8]* %filename, i64 0, i64 %idxprom18, !dbg !1103
  store i8 %12, i8* %arrayidx19, align 1, !dbg !1104
  %14 = load i32, i32* %to_index, align 4, !dbg !1105
  %inc20 = add nsw i32 %14, 1, !dbg !1105
  store i32 %inc20, i32* %to_index, align 4, !dbg !1105
  %15 = load i32, i32* %from_index, align 4, !dbg !1106
  %inc21 = add nsw i32 %15, 1, !dbg !1106
  store i32 %inc21, i32* %from_index, align 4, !dbg !1106
  %16 = load i32, i32* %from_index, align 4, !dbg !1107
  %idxprom22 = sext i32 %16 to i64, !dbg !1109
  %17 = load i8*, i8** %filenames.addr, align 8, !dbg !1109
  %arrayidx23 = getelementptr inbounds i8, i8* %17, i64 %idxprom22, !dbg !1109
  %18 = load i8, i8* %arrayidx23, align 1, !dbg !1109
  %tobool = icmp ne i8 %18, 0, !dbg !1109
  br i1 %tobool, label %if.end, label %if.then24, !dbg !1110

if.then24:                                        ; preds = %if.else
  %arraydecay25 = getelementptr inbounds [255 x i8], [255 x i8]* %filename, i32 0, i32 0, !dbg !1111
  call void @command_stor(i8* %arraydecay25), !dbg !1113
  store i32 0, i32* %to_index, align 4, !dbg !1114
  %arraydecay26 = getelementptr inbounds [255 x i8], [255 x i8]* %filename, i32 0, i32 0, !dbg !1115
  call void @llvm.memset.p0i8.i64(i8* %arraydecay26, i8 0, i64 255, i32 16, i1 false), !dbg !1115
  %19 = load i32, i32* %from_index, align 4, !dbg !1116
  %inc27 = add nsw i32 %19, 1, !dbg !1116
  store i32 %inc27, i32* %from_index, align 4, !dbg !1116
  br label %if.end, !dbg !1117

if.end:                                           ; preds = %if.then24, %if.else
  br label %if.end28

if.end28:                                         ; preds = %if.end, %while.end
  %20 = load i32, i32* %to_index, align 4, !dbg !1118
  %cmp29 = icmp sgt i32 %20, 253, !dbg !1120
  br i1 %cmp29, label %if.then31, label %if.end32, !dbg !1121

if.then31:                                        ; preds = %if.end28
  %21 = load i8*, i8** %filenames.addr, align 8, !dbg !1122
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.50, i32 0, i32 0), i8* %21), !dbg !1124
  br label %while.end33, !dbg !1125

if.end32:                                         ; preds = %if.end28
  br label %while.cond, !dbg !1126

while.end33:                                      ; preds = %if.then31, %while.cond
  ret void, !dbg !1128
}

; Function Attrs: nounwind uwtable
define void @command_stor(i8* %filename) #0 !dbg !145 {
entry:
  %filename.addr = alloca i8*, align 8
  store i8* %filename, i8** %filename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filename.addr, metadata !1129, metadata !246), !dbg !1130
  %0 = load i8*, i8** %filename.addr, align 8, !dbg !1131
  call void @do_stor(i8* %0, i32 577), !dbg !1132
  ret void, !dbg !1133
}

; Function Attrs: nounwind uwtable
define void @do_stor(i8* %filename, i32 %flags) #0 !dbg !142 {
entry:
  %filename.addr = alloca i8*, align 8
  %flags.addr = alloca i32, align 4
  %buffer = alloca i8*, align 8
  %fd = alloca i32, align 4
  %i = alloca i32, align 4
  %max = alloca i32, align 4
  %rfds = alloca %struct.fd_set, align 8
  %tv = alloca %struct.timeval, align 8
  %p = alloca i8*, align 8
  %pp = alloca i8*, align 8
  %mapped = alloca i8*, align 8
  %my_buffer_size = alloca i32, align 4
  %num_clients = alloca i32, align 4
  %new_num_clients = alloca i32, align 4
  %xfer_delay = alloca i32, align 4
  %attempt_gzip = alloca i32, align 4
  %get_value = alloca i64, align 8
  %change_buffer_size = alloca i32, align 4
  %stdin_fileno = alloca i32, align 4
  %write_result = alloca i32, align 4
  %__d0 = alloca i32, align 4
  %__d1 = alloca i32, align 4
  %wait_time = alloca %struct.timeval, align 8
  store i8* %filename, i8** %filename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filename.addr, metadata !1134, metadata !246), !dbg !1135
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !1136, metadata !246), !dbg !1137
  call void @llvm.dbg.declare(metadata i8** %buffer, metadata !1138, metadata !246), !dbg !1139
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !1140, metadata !246), !dbg !1141
  call void @llvm.dbg.declare(metadata i32* %i, metadata !1142, metadata !246), !dbg !1143
  call void @llvm.dbg.declare(metadata i32* %max, metadata !1144, metadata !246), !dbg !1145
  call void @llvm.dbg.declare(metadata %struct.fd_set* %rfds, metadata !1146, metadata !246), !dbg !1147
  call void @llvm.dbg.declare(metadata %struct.timeval* %tv, metadata !1148, metadata !246), !dbg !1149
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1150, metadata !246), !dbg !1151
  call void @llvm.dbg.declare(metadata i8** %pp, metadata !1152, metadata !246), !dbg !1153
  call void @llvm.dbg.declare(metadata i8** %mapped, metadata !1154, metadata !246), !dbg !1155
  %0 = load i8*, i8** %filename.addr, align 8, !dbg !1156
  %call = call i8* @bftpd_cwd_mappath(i8* %0), !dbg !1157
  store i8* %call, i8** %mapped, align 8, !dbg !1155
  call void @llvm.dbg.declare(metadata i32* %my_buffer_size, metadata !1158, metadata !246), !dbg !1159
  call void @llvm.dbg.declare(metadata i32* %num_clients, metadata !1160, metadata !246), !dbg !1161
  store i32 1, i32* %num_clients, align 4, !dbg !1161
  call void @llvm.dbg.declare(metadata i32* %new_num_clients, metadata !1162, metadata !246), !dbg !1163
  store i32 1, i32* %new_num_clients, align 4, !dbg !1163
  call void @llvm.dbg.declare(metadata i32* %xfer_delay, metadata !1164, metadata !246), !dbg !1165
  call void @llvm.dbg.declare(metadata i32* %attempt_gzip, metadata !1166, metadata !246), !dbg !1167
  store i32 0, i32* %attempt_gzip, align 4, !dbg !1167
  call void @llvm.dbg.declare(metadata i64* %get_value, metadata !1168, metadata !246), !dbg !1169
  call void @llvm.dbg.declare(metadata i32* %change_buffer_size, metadata !1170, metadata !246), !dbg !1171
  store i32 0, i32* %change_buffer_size, align 4, !dbg !1171
  call void @llvm.dbg.declare(metadata i32* %stdin_fileno, metadata !1172, metadata !246), !dbg !1173
  call void @llvm.dbg.declare(metadata i32* %write_result, metadata !1174, metadata !246), !dbg !1175
  %1 = load i8*, i8** @pre_write_script, align 8, !dbg !1176
  %tobool = icmp ne i8* %1, null, !dbg !1176
  br i1 %tobool, label %if.then, label %if.end, !dbg !1178

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** @pre_write_script, align 8, !dbg !1179
  %3 = load i8*, i8** %mapped, align 8, !dbg !1180
  %call1 = call i32 @run_script(i8* %2, i8* %3), !dbg !1181
  br label %if.end, !dbg !1181

if.end:                                           ; preds = %if.then, %entry
  %call2 = call i8* @config_getoption(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.51, i32 0, i32 0)), !dbg !1182
  %call3 = call i64 @strtoul(i8* %call2, i8** null, i32 0) #2, !dbg !1183
  store i64 %call3, i64* %get_value, align 8, !dbg !1185
  %4 = load i64, i64* %get_value, align 8, !dbg !1186
  %cmp = icmp ule i64 %4, 2147483647, !dbg !1188
  br i1 %cmp, label %if.then4, label %if.else, !dbg !1189

if.then4:                                         ; preds = %if.end
  %5 = load i64, i64* %get_value, align 8, !dbg !1190
  %conv = trunc i64 %5 to i32, !dbg !1190
  store i32 %conv, i32* %xfer_delay, align 4, !dbg !1191
  br label %if.end5, !dbg !1192

if.else:                                          ; preds = %if.end
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str.52, i32 0, i32 0), i32 0), !dbg !1193
  store i32 0, i32* %xfer_delay, align 4, !dbg !1195
  br label %if.end5

if.end5:                                          ; preds = %if.else, %if.then4
  %6 = load i8*, i8** %mapped, align 8, !dbg !1196
  %call6 = call i32 (i8*, i32, ...) @open64(i8* %6, i32 0), !dbg !1197
  store i32 %call6, i32* %fd, align 4, !dbg !1198
  %7 = load i32, i32* %fd, align 4, !dbg !1199
  %cmp7 = icmp sge i32 %7, 0, !dbg !1201
  br i1 %cmp7, label %if.then9, label %if.end17, !dbg !1202

if.then9:                                         ; preds = %if.end5
  %8 = load i32, i32* %fd, align 4, !dbg !1203
  %call10 = call i32 @close(i32 %8), !dbg !1205
  %call11 = call i8* @config_getoption(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.53, i32 0, i32 0)), !dbg !1206
  %call12 = call i32 @strcasecmp(i8* %call11, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.54, i32 0, i32 0)) #9, !dbg !1208
  %tobool13 = icmp ne i32 %call12, 0, !dbg !1210
  br i1 %tobool13, label %if.end16, label %if.then14, !dbg !1211

if.then14:                                        ; preds = %if.then9
  %9 = load i8*, i8** %filename.addr, align 8, !dbg !1212
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.55, i32 0, i32 0), i8* %9), !dbg !1214
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.56, i32 0, i32 0)), !dbg !1215
  %10 = load i8*, i8** %mapped, align 8, !dbg !1216
  call void @free(i8* %10) #2, !dbg !1217
  %11 = load i32, i32* @sock, align 4, !dbg !1218
  %call15 = call i32 @close(i32 %11), !dbg !1219
  br label %if.end178, !dbg !1220

if.end16:                                         ; preds = %if.then9
  br label %if.end17, !dbg !1221

if.end17:                                         ; preds = %if.end16, %if.end5
  %12 = load i32, i32* %attempt_gzip, align 4, !dbg !1222
  %tobool18 = icmp ne i32 %12, 0, !dbg !1222
  br i1 %tobool18, label %if.end34, label %if.then19, !dbg !1224

if.then19:                                        ; preds = %if.end17
  %13 = load i8*, i8** %mapped, align 8, !dbg !1225
  %14 = load i32, i32* %flags.addr, align 4, !dbg !1227
  %call20 = call i32 (i8*, i32, ...) @open64(i8* %13, i32 %14, i32 438), !dbg !1228
  store i32 %call20, i32* %fd, align 4, !dbg !1229
  %15 = load i32, i32* %fd, align 4, !dbg !1230
  %cmp21 = icmp eq i32 %15, -1, !dbg !1232
  br i1 %cmp21, label %if.then23, label %if.end33, !dbg !1233

if.then23:                                        ; preds = %if.then19
  %call24 = call i32* @__errno_location() #1, !dbg !1234
  %16 = load i32, i32* %call24, align 4, !dbg !1234
  %call25 = call i8* @strerror(i32 %16) #2, !dbg !1236
  %17 = load i8*, i8** %filename.addr, align 8, !dbg !1238
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([46 x i8], [46 x i8]* @.str.57, i32 0, i32 0), i8* %call25, i8* %17), !dbg !1239
  %call26 = call i32* @__errno_location() #1, !dbg !1240
  %18 = load i32, i32* %call26, align 4, !dbg !1240
  %call27 = call i8* @strerror(i32 %18) #2, !dbg !1241
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.58, i32 0, i32 0), i8* %call27), !dbg !1242
  %19 = load i32, i32* %fd, align 4, !dbg !1244
  %call28 = call i32 @close(i32 %19), !dbg !1245
  %20 = load i8*, i8** @post_write_script, align 8, !dbg !1246
  %tobool29 = icmp ne i8* %20, null, !dbg !1246
  br i1 %tobool29, label %if.then30, label %if.end32, !dbg !1248

if.then30:                                        ; preds = %if.then23
  %21 = load i8*, i8** @post_write_script, align 8, !dbg !1249
  %22 = load i8*, i8** %mapped, align 8, !dbg !1250
  %call31 = call i32 @run_script(i8* %21, i8* %22), !dbg !1251
  br label %if.end32, !dbg !1251

if.end32:                                         ; preds = %if.then30, %if.then23
  %23 = load i8*, i8** %mapped, align 8, !dbg !1252
  call void @free(i8* %23) #2, !dbg !1253
  br label %if.end178, !dbg !1254

if.end33:                                         ; preds = %if.then19
  br label %if.end34, !dbg !1255

if.end34:                                         ; preds = %if.end33, %if.end17
  %24 = load i8*, i8** %filename.addr, align 8, !dbg !1256
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.59, i32 0, i32 0), i8* %24), !dbg !1257
  %call35 = call i32 @dataconn(), !dbg !1258
  %tobool36 = icmp ne i32 %call35, 0, !dbg !1258
  br i1 %tobool36, label %if.then37, label %if.end46, !dbg !1260

if.then37:                                        ; preds = %if.end34
  %25 = load i32, i32* %fd, align 4, !dbg !1261
  %call38 = call i32 @close(i32 %25), !dbg !1263
  %26 = load i8*, i8** @post_write_script, align 8, !dbg !1264
  %tobool39 = icmp ne i8* %26, null, !dbg !1264
  br i1 %tobool39, label %if.then40, label %if.end42, !dbg !1266

if.then40:                                        ; preds = %if.then37
  %27 = load i8*, i8** @post_write_script, align 8, !dbg !1267
  %28 = load i8*, i8** %mapped, align 8, !dbg !1268
  %call41 = call i32 @run_script(i8* %27, i8* %28), !dbg !1269
  br label %if.end42, !dbg !1269

if.end42:                                         ; preds = %if.then40, %if.then37
  %29 = load i8*, i8** %mapped, align 8, !dbg !1270
  %tobool43 = icmp ne i8* %29, null, !dbg !1270
  br i1 %tobool43, label %if.then44, label %if.end45, !dbg !1272

if.then44:                                        ; preds = %if.end42
  %30 = load i8*, i8** %mapped, align 8, !dbg !1273
  call void @free(i8* %30) #2, !dbg !1274
  br label %if.end45, !dbg !1274

if.end45:                                         ; preds = %if.then44, %if.end42
  br label %if.end178, !dbg !1275

if.end46:                                         ; preds = %if.end34
  %call47 = call i8* @config_getoption(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.60, i32 0, i32 0)), !dbg !1276
  %call48 = call i32 @strcasecmp(i8* %call47, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.8, i32 0, i32 0)) #9, !dbg !1278
  %tobool49 = icmp ne i32 %call48, 0, !dbg !1280
  br i1 %tobool49, label %if.end51, label %if.then50, !dbg !1281

if.then50:                                        ; preds = %if.end46
  store i32 1, i32* %change_buffer_size, align 4, !dbg !1282
  br label %if.end51, !dbg !1283

if.end51:                                         ; preds = %if.then50, %if.end46
  %31 = load i32, i32* %change_buffer_size, align 4, !dbg !1284
  %tobool52 = icmp ne i32 %31, 0, !dbg !1284
  br i1 %tobool52, label %if.then53, label %if.else56, !dbg !1286

if.then53:                                        ; preds = %if.end51
  %call54 = call i32 @bftpdutmp_usercount(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.61, i32 0, i32 0)), !dbg !1287
  store i32 %call54, i32* %num_clients, align 4, !dbg !1289
  %32 = load i32, i32* %num_clients, align 4, !dbg !1290
  %call55 = call i32 @get_buffer_size(i32 %32), !dbg !1291
  store i32 %call55, i32* %my_buffer_size, align 4, !dbg !1292
  br label %if.end57, !dbg !1293

if.else56:                                        ; preds = %if.end51
  %33 = load i32, i32* @xfer_bufsize, align 4, !dbg !1294
  store i32 %33, i32* %my_buffer_size, align 4, !dbg !1295
  br label %if.end57

if.end57:                                         ; preds = %if.else56, %if.then53
  %call58 = call i32 @alarm(i32 0) #2, !dbg !1296
  %34 = load i32, i32* @xfer_bufsize, align 4, !dbg !1297
  %conv59 = sext i32 %34 to i64, !dbg !1297
  %call60 = call noalias i8* @malloc(i64 %conv59) #2, !dbg !1298
  store i8* %call60, i8** %buffer, align 8, !dbg !1299
  %35 = load i8*, i8** %buffer, align 8, !dbg !1300
  %tobool61 = icmp ne i8* %35, null, !dbg !1300
  br i1 %tobool61, label %if.end69, label %if.then62, !dbg !1302

if.then62:                                        ; preds = %if.end57
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.62, i32 0, i32 0), i32 0), !dbg !1303
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.63, i32 0, i32 0)), !dbg !1305
  %36 = load i32, i32* %fd, align 4, !dbg !1306
  %cmp63 = icmp sge i32 %36, 0, !dbg !1308
  br i1 %cmp63, label %if.then65, label %if.end67, !dbg !1309

if.then65:                                        ; preds = %if.then62
  %37 = load i32, i32* %fd, align 4, !dbg !1310
  %call66 = call i32 @close(i32 %37), !dbg !1311
  br label %if.end67, !dbg !1311

if.end67:                                         ; preds = %if.then65, %if.then62
  %38 = load i32, i32* @sock, align 4, !dbg !1312
  %call68 = call i32 @close(i32 %38), !dbg !1313
  br label %if.end178, !dbg !1314

if.end69:                                         ; preds = %if.end57
  %39 = load i32, i32* %fd, align 4, !dbg !1315
  %40 = load i64, i64* @offset, align 8, !dbg !1316
  %call70 = call i64 @lseek64(i32 %39, i64 %40, i32 0) #2, !dbg !1317
  store i64 0, i64* @offset, align 8, !dbg !1318
  %41 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !1319
  %call71 = call i32 @fileno(%struct._IO_FILE* %41) #2, !dbg !1320
  store i32 %call71, i32* %stdin_fileno, align 4, !dbg !1321
  %42 = load i32, i32* @sock, align 4, !dbg !1322
  %43 = load i32, i32* %stdin_fileno, align 4, !dbg !1323
  %cmp72 = icmp sgt i32 %42, %43, !dbg !1324
  br i1 %cmp72, label %cond.true, label %cond.false, !dbg !1322

cond.true:                                        ; preds = %if.end69
  %44 = load i32, i32* @sock, align 4, !dbg !1325
  br label %cond.end, !dbg !1326

cond.false:                                       ; preds = %if.end69
  %45 = load i32, i32* %stdin_fileno, align 4, !dbg !1327
  br label %cond.end, !dbg !1329

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %44, %cond.true ], [ %45, %cond.false ], !dbg !1330
  %add = add nsw i32 %cond, 1, !dbg !1332
  store i32 %add, i32* %max, align 4, !dbg !1333
  br label %for.cond, !dbg !1334

for.cond:                                         ; preds = %if.end168, %cond.end
  br label %do.body, !dbg !1335

do.body:                                          ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i32* %__d0, metadata !1339, metadata !246), !dbg !1341
  call void @llvm.dbg.declare(metadata i32* %__d1, metadata !1342, metadata !246), !dbg !1341
  %__fds_bits = getelementptr inbounds %struct.fd_set, %struct.fd_set* %rfds, i32 0, i32 0, !dbg !1343
  %arrayidx = getelementptr inbounds [16 x i64], [16 x i64]* %__fds_bits, i64 0, i64 0, !dbg !1343
  %46 = call { i64, i64* } asm sideeffect "cld; rep; stosq", "={cx},={di},{ax},0,1,~{memory},~{dirflag},~{fpsr},~{flags}"(i32 0, i64 16, i64* %arrayidx) #2, !dbg !1343, !srcloc !1345
  %asmresult = extractvalue { i64, i64* } %46, 0, !dbg !1343
  %asmresult74 = extractvalue { i64, i64* } %46, 1, !dbg !1343
  %47 = trunc i64 %asmresult to i32, !dbg !1343
  store i32 %47, i32* %__d0, align 4, !dbg !1343
  %48 = ptrtoint i64* %asmresult74 to i64, !dbg !1343
  %49 = trunc i64 %48 to i32, !dbg !1343
  store i32 %49, i32* %__d1, align 4, !dbg !1343
  br label %do.end, !dbg !1343

do.end:                                           ; preds = %do.body
  %50 = load i32, i32* @sock, align 4, !dbg !1346
  %rem = srem i32 %50, 64, !dbg !1346
  %sh_prom = zext i32 %rem to i64, !dbg !1346
  %shl = shl i64 1, %sh_prom, !dbg !1346
  %51 = load i32, i32* @sock, align 4, !dbg !1346
  %div = sdiv i32 %51, 64, !dbg !1346
  %idxprom = sext i32 %div to i64, !dbg !1346
  %__fds_bits75 = getelementptr inbounds %struct.fd_set, %struct.fd_set* %rfds, i32 0, i32 0, !dbg !1346
  %arrayidx76 = getelementptr inbounds [16 x i64], [16 x i64]* %__fds_bits75, i64 0, i64 %idxprom, !dbg !1346
  %52 = load i64, i64* %arrayidx76, align 8, !dbg !1346
  %or = or i64 %52, %shl, !dbg !1346
  store i64 %or, i64* %arrayidx76, align 8, !dbg !1346
  %53 = load i32, i32* %stdin_fileno, align 4, !dbg !1347
  %rem77 = srem i32 %53, 64, !dbg !1347
  %sh_prom78 = zext i32 %rem77 to i64, !dbg !1347
  %shl79 = shl i64 1, %sh_prom78, !dbg !1347
  %54 = load i32, i32* %stdin_fileno, align 4, !dbg !1347
  %div80 = sdiv i32 %54, 64, !dbg !1347
  %idxprom81 = sext i32 %div80 to i64, !dbg !1347
  %__fds_bits82 = getelementptr inbounds %struct.fd_set, %struct.fd_set* %rfds, i32 0, i32 0, !dbg !1347
  %arrayidx83 = getelementptr inbounds [16 x i64], [16 x i64]* %__fds_bits82, i64 0, i64 %idxprom81, !dbg !1347
  %55 = load i64, i64* %arrayidx83, align 8, !dbg !1347
  %or84 = or i64 %55, %shl79, !dbg !1347
  store i64 %or84, i64* %arrayidx83, align 8, !dbg !1347
  %56 = load i32, i32* @data_timeout, align 4, !dbg !1348
  %conv85 = sext i32 %56 to i64, !dbg !1348
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %tv, i32 0, i32 0, !dbg !1349
  store i64 %conv85, i64* %tv_sec, align 8, !dbg !1350
  %tv_usec = getelementptr inbounds %struct.timeval, %struct.timeval* %tv, i32 0, i32 1, !dbg !1351
  store i64 0, i64* %tv_usec, align 8, !dbg !1352
  %57 = load i32, i32* %max, align 4, !dbg !1353
  %call86 = call i32 @select(i32 %57, %struct.fd_set* %rfds, %struct.fd_set* null, %struct.fd_set* null, %struct.timeval* %tv), !dbg !1355
  %tobool87 = icmp ne i32 %call86, 0, !dbg !1355
  br i1 %tobool87, label %if.end95, label %if.then88, !dbg !1356

if.then88:                                        ; preds = %do.end
  %58 = load i32, i32* @sock, align 4, !dbg !1357
  %call89 = call i32 @close(i32 %58), !dbg !1359
  %59 = load i32, i32* %fd, align 4, !dbg !1360
  %call90 = call i32 @close(i32 %59), !dbg !1361
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.64, i32 0, i32 0)), !dbg !1362
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.65, i32 0, i32 0)), !dbg !1363
  %60 = load i8*, i8** @post_write_script, align 8, !dbg !1364
  %tobool91 = icmp ne i8* %60, null, !dbg !1364
  br i1 %tobool91, label %if.then92, label %if.end94, !dbg !1366

if.then92:                                        ; preds = %if.then88
  %61 = load i8*, i8** @post_write_script, align 8, !dbg !1367
  %62 = load i8*, i8** %mapped, align 8, !dbg !1368
  %call93 = call i32 @run_script(i8* %61, i8* %62), !dbg !1369
  br label %if.end94, !dbg !1369

if.end94:                                         ; preds = %if.then92, %if.then88
  call void (...) @bftpdutmp_end(), !dbg !1370
  call void @exit(i32 0) #10, !dbg !1371
  unreachable, !dbg !1371

if.end95:                                         ; preds = %do.end
  %63 = load i32, i32* %stdin_fileno, align 4, !dbg !1372
  %div96 = sdiv i32 %63, 64, !dbg !1372
  %idxprom97 = sext i32 %div96 to i64, !dbg !1372
  %__fds_bits98 = getelementptr inbounds %struct.fd_set, %struct.fd_set* %rfds, i32 0, i32 0, !dbg !1372
  %arrayidx99 = getelementptr inbounds [16 x i64], [16 x i64]* %__fds_bits98, i64 0, i64 %idxprom97, !dbg !1372
  %64 = load i64, i64* %arrayidx99, align 8, !dbg !1372
  %65 = load i32, i32* %stdin_fileno, align 4, !dbg !1372
  %rem100 = srem i32 %65, 64, !dbg !1372
  %sh_prom101 = zext i32 %rem100 to i64, !dbg !1372
  %shl102 = shl i64 1, %sh_prom101, !dbg !1372
  %and = and i64 %64, %shl102, !dbg !1372
  %cmp103 = icmp ne i64 %and, 0, !dbg !1372
  br i1 %cmp103, label %if.then105, label %if.end115, !dbg !1374

if.then105:                                       ; preds = %if.end95
  %66 = load i32, i32* %fd, align 4, !dbg !1375
  %67 = load i32, i32* @sock, align 4, !dbg !1377
  %call106 = call signext i8 @test_abort(i8 signext 0, i32 %66, i32 %67), !dbg !1378
  %68 = load i8*, i8** %buffer, align 8, !dbg !1379
  %tobool107 = icmp ne i8* %68, null, !dbg !1379
  br i1 %tobool107, label %if.then108, label %if.end109, !dbg !1381

if.then108:                                       ; preds = %if.then105
  %69 = load i8*, i8** %buffer, align 8, !dbg !1382
  call void @free(i8* %69) #2, !dbg !1383
  br label %if.end109, !dbg !1383

if.end109:                                        ; preds = %if.then108, %if.then105
  %70 = load i32, i32* %fd, align 4, !dbg !1384
  %call110 = call i32 @close(i32 %70), !dbg !1385
  %71 = load i8*, i8** @post_write_script, align 8, !dbg !1386
  %tobool111 = icmp ne i8* %71, null, !dbg !1386
  br i1 %tobool111, label %if.then112, label %if.end114, !dbg !1388

if.then112:                                       ; preds = %if.end109
  %72 = load i8*, i8** @post_write_script, align 8, !dbg !1389
  %73 = load i8*, i8** %mapped, align 8, !dbg !1390
  %call113 = call i32 @run_script(i8* %72, i8* %73), !dbg !1391
  br label %if.end114, !dbg !1391

if.end114:                                        ; preds = %if.then112, %if.end109
  %74 = load i8*, i8** %mapped, align 8, !dbg !1392
  call void @free(i8* %74) #2, !dbg !1393
  br label %if.end178, !dbg !1394

if.end115:                                        ; preds = %if.end95
  %75 = load i32, i32* @sock, align 4, !dbg !1395
  %76 = load i8*, i8** %buffer, align 8, !dbg !1397
  %77 = load i32, i32* %my_buffer_size, align 4, !dbg !1398
  %sub = sub nsw i32 %77, 1, !dbg !1399
  %conv116 = sext i32 %sub to i64, !dbg !1398
  %call117 = call i64 @recv(i32 %75, i8* %76, i64 %conv116, i32 0), !dbg !1400
  %conv118 = trunc i64 %call117 to i32, !dbg !1400
  store i32 %conv118, i32* %i, align 4, !dbg !1401
  %tobool119 = icmp ne i32 %conv118, 0, !dbg !1401
  br i1 %tobool119, label %if.end121, label %if.then120, !dbg !1402

if.then120:                                       ; preds = %if.end115
  br label %for.end, !dbg !1403

if.end121:                                        ; preds = %if.end115
  %78 = load i32, i32* %i, align 4, !dbg !1404
  %conv122 = sitofp i32 %78 to double, !dbg !1404
  %79 = load double, double* @bytes_recvd, align 8, !dbg !1405
  %add123 = fadd double %79, %conv122, !dbg !1405
  store double %add123, double* @bytes_recvd, align 8, !dbg !1405
  %80 = load i16, i16* @xfertype, align 2, !dbg !1406
  %conv124 = sext i16 %80 to i32, !dbg !1406
  %cmp125 = icmp eq i32 %conv124, 0, !dbg !1408
  br i1 %cmp125, label %if.then127, label %if.end142, !dbg !1409

if.then127:                                       ; preds = %if.end121
  %81 = load i32, i32* %i, align 4, !dbg !1410
  %idxprom128 = sext i32 %81 to i64, !dbg !1412
  %82 = load i8*, i8** %buffer, align 8, !dbg !1412
  %arrayidx129 = getelementptr inbounds i8, i8* %82, i64 %idxprom128, !dbg !1412
  store i8 0, i8* %arrayidx129, align 1, !dbg !1413
  %83 = load i8*, i8** %buffer, align 8, !dbg !1414
  store i8* %83, i8** %pp, align 8, !dbg !1415
  store i8* %83, i8** %p, align 8, !dbg !1416
  br label %while.cond, !dbg !1417

while.cond:                                       ; preds = %if.end138, %if.then127
  %84 = load i8*, i8** %p, align 8, !dbg !1418
  %85 = load i8, i8* %84, align 1, !dbg !1420
  %tobool130 = icmp ne i8 %85, 0, !dbg !1421
  br i1 %tobool130, label %while.body, label %while.end, !dbg !1421

while.body:                                       ; preds = %while.cond
  %86 = load i8*, i8** %p, align 8, !dbg !1422
  %87 = load i8, i8* %86, align 1, !dbg !1425
  %conv131 = zext i8 %87 to i32, !dbg !1426
  %cmp132 = icmp eq i32 %conv131, 13, !dbg !1427
  br i1 %cmp132, label %if.then134, label %if.else135, !dbg !1428

if.then134:                                       ; preds = %while.body
  %88 = load i8*, i8** %p, align 8, !dbg !1429
  %incdec.ptr = getelementptr inbounds i8, i8* %88, i32 1, !dbg !1429
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !1429
  br label %if.end138, !dbg !1430

if.else135:                                       ; preds = %while.body
  %89 = load i8*, i8** %p, align 8, !dbg !1431
  %incdec.ptr136 = getelementptr inbounds i8, i8* %89, i32 1, !dbg !1431
  store i8* %incdec.ptr136, i8** %p, align 8, !dbg !1431
  %90 = load i8, i8* %89, align 1, !dbg !1432
  %91 = load i8*, i8** %pp, align 8, !dbg !1433
  %incdec.ptr137 = getelementptr inbounds i8, i8* %91, i32 1, !dbg !1433
  store i8* %incdec.ptr137, i8** %pp, align 8, !dbg !1433
  store i8 %90, i8* %91, align 1, !dbg !1434
  br label %if.end138

if.end138:                                        ; preds = %if.else135, %if.then134
  br label %while.cond, !dbg !1435

while.end:                                        ; preds = %while.cond
  %92 = load i8*, i8** %pp, align 8, !dbg !1437
  %incdec.ptr139 = getelementptr inbounds i8, i8* %92, i32 1, !dbg !1437
  store i8* %incdec.ptr139, i8** %pp, align 8, !dbg !1437
  store i8 0, i8* %92, align 1, !dbg !1438
  %93 = load i8*, i8** %buffer, align 8, !dbg !1439
  %call140 = call i64 @strlen(i8* %93) #9, !dbg !1440
  %conv141 = trunc i64 %call140 to i32, !dbg !1440
  store i32 %conv141, i32* %i, align 4, !dbg !1441
  br label %if.end142, !dbg !1442

if.end142:                                        ; preds = %while.end, %if.end121
  %94 = load i32, i32* %attempt_gzip, align 4, !dbg !1443
  %tobool143 = icmp ne i32 %94, 0, !dbg !1443
  br i1 %tobool143, label %if.end152, label %if.then144, !dbg !1445

if.then144:                                       ; preds = %if.end142
  %95 = load i32, i32* %fd, align 4, !dbg !1446
  %96 = load i8*, i8** %buffer, align 8, !dbg !1448
  %97 = load i32, i32* %i, align 4, !dbg !1449
  %conv145 = sext i32 %97 to i64, !dbg !1449
  %call146 = call i64 @write(i32 %95, i8* %96, i64 %conv145), !dbg !1450
  %conv147 = trunc i64 %call146 to i32, !dbg !1450
  store i32 %conv147, i32* %write_result, align 4, !dbg !1451
  %98 = load i32, i32* %write_result, align 4, !dbg !1452
  %cmp148 = icmp eq i32 %98, -1, !dbg !1454
  br i1 %cmp148, label %if.then150, label %if.end151, !dbg !1455

if.then150:                                       ; preds = %if.then144
  br label %for.end, !dbg !1456

if.end151:                                        ; preds = %if.then144
  br label %if.end152, !dbg !1457

if.end152:                                        ; preds = %if.end151, %if.end142
  %99 = load i32, i32* %change_buffer_size, align 4, !dbg !1458
  %tobool153 = icmp ne i32 %99, 0, !dbg !1458
  br i1 %tobool153, label %if.then154, label %if.end161, !dbg !1460

if.then154:                                       ; preds = %if.end152
  %call155 = call i32 @bftpdutmp_usercount(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.61, i32 0, i32 0)), !dbg !1461
  store i32 %call155, i32* %new_num_clients, align 4, !dbg !1463
  %100 = load i32, i32* %new_num_clients, align 4, !dbg !1464
  %101 = load i32, i32* %num_clients, align 4, !dbg !1466
  %cmp156 = icmp ne i32 %100, %101, !dbg !1467
  br i1 %cmp156, label %if.then158, label %if.end160, !dbg !1468

if.then158:                                       ; preds = %if.then154
  %102 = load i32, i32* %new_num_clients, align 4, !dbg !1469
  store i32 %102, i32* %num_clients, align 4, !dbg !1471
  %103 = load i32, i32* %num_clients, align 4, !dbg !1472
  %call159 = call i32 @get_buffer_size(i32 %103), !dbg !1473
  store i32 %call159, i32* %my_buffer_size, align 4, !dbg !1474
  br label %if.end160, !dbg !1475

if.end160:                                        ; preds = %if.then158, %if.then154
  br label %if.end161, !dbg !1476

if.end161:                                        ; preds = %if.end160, %if.end152
  %104 = load i32, i32* %xfer_delay, align 4, !dbg !1477
  %tobool162 = icmp ne i32 %104, 0, !dbg !1477
  br i1 %tobool162, label %if.then163, label %if.end168, !dbg !1479

if.then163:                                       ; preds = %if.end161
  call void @llvm.dbg.declare(metadata %struct.timeval* %wait_time, metadata !1480, metadata !246), !dbg !1482
  %tv_sec164 = getelementptr inbounds %struct.timeval, %struct.timeval* %wait_time, i32 0, i32 0, !dbg !1483
  store i64 0, i64* %tv_sec164, align 8, !dbg !1484
  %105 = load i32, i32* %xfer_delay, align 4, !dbg !1485
  %conv165 = sext i32 %105 to i64, !dbg !1485
  %tv_usec166 = getelementptr inbounds %struct.timeval, %struct.timeval* %wait_time, i32 0, i32 1, !dbg !1486
  store i64 %conv165, i64* %tv_usec166, align 8, !dbg !1487
  %call167 = call i32 @select(i32 0, %struct.fd_set* null, %struct.fd_set* null, %struct.fd_set* null, %struct.timeval* %wait_time), !dbg !1488
  br label %if.end168, !dbg !1489

if.end168:                                        ; preds = %if.then163, %if.end161
  br label %for.cond, !dbg !1490

for.end:                                          ; preds = %if.then150, %if.then120
  %106 = load i8*, i8** %buffer, align 8, !dbg !1492
  call void @free(i8* %106) #2, !dbg !1493
  %107 = load i32, i32* %fd, align 4, !dbg !1494
  %call169 = call i32 @close(i32 %107), !dbg !1495
  %108 = load i32, i32* @sock, align 4, !dbg !1496
  %call170 = call i32 @close(i32 %108), !dbg !1497
  %109 = load i32, i32* @control_timeout, align 4, !dbg !1498
  %call171 = call i32 @alarm(i32 %109) #2, !dbg !1499
  store i64 0, i64* @offset, align 8, !dbg !1500
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.66, i32 0, i32 0)), !dbg !1501
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.67, i32 0, i32 0)), !dbg !1502
  %110 = load i8*, i8** @post_write_script, align 8, !dbg !1503
  %tobool172 = icmp ne i8* %110, null, !dbg !1503
  br i1 %tobool172, label %if.then173, label %if.end175, !dbg !1505

if.then173:                                       ; preds = %for.end
  %111 = load i8*, i8** @post_write_script, align 8, !dbg !1506
  %112 = load i8*, i8** %mapped, align 8, !dbg !1507
  %call174 = call i32 @run_script(i8* %111, i8* %112), !dbg !1508
  br label %if.end175, !dbg !1508

if.end175:                                        ; preds = %if.then173, %for.end
  %113 = load i8*, i8** %mapped, align 8, !dbg !1509
  %tobool176 = icmp ne i8* %113, null, !dbg !1509
  br i1 %tobool176, label %if.then177, label %if.end178, !dbg !1511

if.then177:                                       ; preds = %if.end175
  %114 = load i8*, i8** %mapped, align 8, !dbg !1512
  call void @free(i8* %114) #2, !dbg !1513
  br label %if.end178, !dbg !1513

if.end178:                                        ; preds = %if.then14, %if.end32, %if.end45, %if.end67, %if.end114, %if.then177, %if.end175
  ret void, !dbg !1514
}

declare i8* @bftpd_cwd_mappath(i8*) #4

; Function Attrs: nounwind uwtable
define i32 @run_script(i8* %script, i8* %path) #0 !dbg !182 {
entry:
  %retval = alloca i32, align 4
  %script.addr = alloca i8*, align 8
  %path.addr = alloca i8*, align 8
  %process_id = alloca i32, align 4
  %command_args = alloca [3 x i8*], align 16
  %save_quit = alloca void (i32)*, align 8
  %save_int = alloca void (i32)*, align 8
  %save_chld = alloca void (i32)*, align 8
  %agg.tmp = alloca %union.__WAIT_STATUS, align 8
  store i8* %script, i8** %script.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %script.addr, metadata !1515, metadata !246), !dbg !1516
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !1517, metadata !246), !dbg !1518
  call void @llvm.dbg.declare(metadata i32* %process_id, metadata !1519, metadata !246), !dbg !1523
  call void @llvm.dbg.declare(metadata [3 x i8*]* %command_args, metadata !1524, metadata !246), !dbg !1526
  %arrayinit.begin = getelementptr inbounds [3 x i8*], [3 x i8*]* %command_args, i64 0, i64 0, !dbg !1527
  %0 = load i8*, i8** %script.addr, align 8, !dbg !1528
  store i8* %0, i8** %arrayinit.begin, align 8, !dbg !1527
  %arrayinit.element = getelementptr inbounds i8*, i8** %arrayinit.begin, i64 1, !dbg !1527
  %1 = load i8*, i8** %path.addr, align 8, !dbg !1529
  store i8* %1, i8** %arrayinit.element, align 8, !dbg !1527
  %arrayinit.element1 = getelementptr inbounds i8*, i8** %arrayinit.element, i64 1, !dbg !1527
  store i8* null, i8** %arrayinit.element1, align 8, !dbg !1527
  call void @llvm.dbg.declare(metadata void (i32)** %save_quit, metadata !1530, metadata !246), !dbg !1532
  call void @llvm.dbg.declare(metadata void (i32)** %save_int, metadata !1533, metadata !246), !dbg !1534
  call void @llvm.dbg.declare(metadata void (i32)** %save_chld, metadata !1535, metadata !246), !dbg !1536
  %call = call void (i32)* @signal(i32 3, void (i32)* inttoptr (i64 1 to void (i32)*)) #2, !dbg !1537
  store void (i32)* %call, void (i32)** %save_quit, align 8, !dbg !1538
  %call2 = call void (i32)* @signal(i32 2, void (i32)* inttoptr (i64 1 to void (i32)*)) #2, !dbg !1539
  store void (i32)* %call2, void (i32)** %save_int, align 8, !dbg !1540
  %call3 = call void (i32)* @signal(i32 17, void (i32)* null) #2, !dbg !1541
  store void (i32)* %call3, void (i32)** %save_chld, align 8, !dbg !1542
  %call4 = call i32 @fork() #2, !dbg !1543
  store i32 %call4, i32* %process_id, align 4, !dbg !1544
  %2 = load i32, i32* %process_id, align 4, !dbg !1545
  %cmp = icmp slt i32 %2, 0, !dbg !1547
  br i1 %cmp, label %if.then, label %if.end, !dbg !1548

if.then:                                          ; preds = %entry
  %3 = load void (i32)*, void (i32)** %save_quit, align 8, !dbg !1549
  %call5 = call void (i32)* @signal(i32 3, void (i32)* %3) #2, !dbg !1551
  %4 = load void (i32)*, void (i32)** %save_int, align 8, !dbg !1552
  %call6 = call void (i32)* @signal(i32 2, void (i32)* %4) #2, !dbg !1553
  %5 = load void (i32)*, void (i32)** %save_chld, align 8, !dbg !1554
  %call7 = call void (i32)* @signal(i32 17, void (i32)* %5) #2, !dbg !1555
  store i32 0, i32* %retval, align 4, !dbg !1556
  br label %return, !dbg !1556

if.end:                                           ; preds = %entry
  %6 = load i32, i32* %process_id, align 4, !dbg !1557
  %cmp8 = icmp eq i32 %6, 0, !dbg !1559
  br i1 %cmp8, label %if.then9, label %if.end14, !dbg !1560

if.then9:                                         ; preds = %if.end
  %call10 = call void (i32)* @signal(i32 3, void (i32)* null) #2, !dbg !1561
  %call11 = call void (i32)* @signal(i32 2, void (i32)* null) #2, !dbg !1563
  %call12 = call void (i32)* @signal(i32 17, void (i32)* null) #2, !dbg !1564
  %7 = load i8*, i8** %script.addr, align 8, !dbg !1565
  %arraydecay = getelementptr inbounds [3 x i8*], [3 x i8*]* %command_args, i32 0, i32 0, !dbg !1566
  %call13 = call i32 @execv(i8* %7, i8** %arraydecay) #2, !dbg !1567
  %8 = load i8*, i8** %script.addr, align 8, !dbg !1568
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.222, i32 0, i32 0), i8* %8), !dbg !1569
  call void @exit(i32 127) #10, !dbg !1570
  unreachable, !dbg !1570

if.end14:                                         ; preds = %if.end
  br label %do.body, !dbg !1571

do.body:                                          ; preds = %land.end, %if.end14
  %9 = load i32, i32* %process_id, align 4, !dbg !1572
  %__uptr = bitcast %union.__WAIT_STATUS* %agg.tmp to %union.wait**, !dbg !1574
  store %union.wait* null, %union.wait** %__uptr, align 8, !dbg !1574
  %coerce.dive = getelementptr inbounds %union.__WAIT_STATUS, %union.__WAIT_STATUS* %agg.tmp, i32 0, i32 0, !dbg !1575
  %10 = load %union.wait*, %union.wait** %coerce.dive, align 8, !dbg !1575
  %call15 = call i32 @wait4(i32 %9, %union.wait* %10, i32 0, %struct.rusage* null) #2, !dbg !1575
  store i32 %call15, i32* %process_id, align 4, !dbg !1576
  br label %do.cond, !dbg !1577

do.cond:                                          ; preds = %do.body
  %11 = load i32, i32* %process_id, align 4, !dbg !1578
  %cmp16 = icmp eq i32 %11, -1, !dbg !1580
  br i1 %cmp16, label %land.rhs, label %land.end, !dbg !1581

land.rhs:                                         ; preds = %do.cond
  %call17 = call i32* @__errno_location() #1, !dbg !1582
  %12 = load i32, i32* %call17, align 4, !dbg !1582
  %cmp18 = icmp eq i32 %12, 4, !dbg !1584
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %13 = phi i1 [ false, %do.cond ], [ %cmp18, %land.rhs ]
  br i1 %13, label %do.body, label %do.end, !dbg !1585

do.end:                                           ; preds = %land.end
  %14 = load void (i32)*, void (i32)** %save_quit, align 8, !dbg !1587
  %call19 = call void (i32)* @signal(i32 3, void (i32)* %14) #2, !dbg !1588
  %15 = load void (i32)*, void (i32)** %save_int, align 8, !dbg !1589
  %call20 = call void (i32)* @signal(i32 2, void (i32)* %15) #2, !dbg !1590
  %16 = load void (i32)*, void (i32)** %save_chld, align 8, !dbg !1591
  %call21 = call void (i32)* @signal(i32 17, void (i32)* %16) #2, !dbg !1592
  store i32 1, i32* %retval, align 4, !dbg !1593
  br label %return, !dbg !1593

return:                                           ; preds = %do.end, %if.then
  %17 = load i32, i32* %retval, align 4, !dbg !1594
  ret i32 %17, !dbg !1594
}

declare i32 @open64(i8*, i32, ...) #4

declare i32 @bftpdutmp_usercount(i8*) #4

; Function Attrs: nounwind uwtable
define i32 @get_buffer_size(i32 %num_connections) #0 !dbg !179 {
entry:
  %num_connections.addr = alloca i32, align 4
  %buffer_size = alloca i32, align 4
  store i32 %num_connections, i32* %num_connections.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %num_connections.addr, metadata !1595, metadata !246), !dbg !1596
  call void @llvm.dbg.declare(metadata i32* %buffer_size, metadata !1597, metadata !246), !dbg !1598
  %0 = load i32, i32* %num_connections.addr, align 4, !dbg !1599
  %cmp = icmp slt i32 %0, 1, !dbg !1601
  br i1 %cmp, label %if.then, label %if.end, !dbg !1602

if.then:                                          ; preds = %entry
  store i32 1, i32* %num_connections.addr, align 4, !dbg !1603
  br label %if.end, !dbg !1604

if.end:                                           ; preds = %if.then, %entry
  %1 = load i32, i32* @xfer_bufsize, align 4, !dbg !1605
  %2 = load i32, i32* %num_connections.addr, align 4, !dbg !1606
  %div = sdiv i32 %1, %2, !dbg !1607
  store i32 %div, i32* %buffer_size, align 4, !dbg !1608
  %3 = load i32, i32* %buffer_size, align 4, !dbg !1609
  %cmp1 = icmp slt i32 %3, 2, !dbg !1611
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !1612

if.then2:                                         ; preds = %if.end
  store i32 2, i32* %buffer_size, align 4, !dbg !1613
  br label %if.end3, !dbg !1614

if.end3:                                          ; preds = %if.then2, %if.end
  %4 = load i32, i32* %buffer_size, align 4, !dbg !1615
  ret i32 %4, !dbg !1616
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: nounwind
declare i64 @lseek64(i32, i64, i32) #3

declare void @bftpdutmp_end(...) #4

; Function Attrs: noreturn nounwind
declare void @exit(i32) #8

declare i64 @recv(i32, i8*, i64, i32) #4

declare i64 @write(i32, i8*, i64) #4

; Function Attrs: nounwind uwtable
define void @command_appe(i8* %filename) #0 !dbg !146 {
entry:
  %filename.addr = alloca i8*, align 8
  store i8* %filename, i8** %filename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filename.addr, metadata !1617, metadata !246), !dbg !1618
  %0 = load i8*, i8** %filename.addr, align 8, !dbg !1619
  call void @do_stor(i8* %0, i32 1089), !dbg !1620
  ret void, !dbg !1621
}

; Function Attrs: nounwind uwtable
define void @command_mget(i8* %filenames) #0 !dbg !147 {
entry:
  %filenames.addr = alloca i8*, align 8
  %filename = alloca [255 x i8], align 16
  %from_index = alloca i32, align 4
  %to_index = alloca i32, align 4
  store i8* %filenames, i8** %filenames.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filenames.addr, metadata !1622, metadata !246), !dbg !1623
  call void @llvm.dbg.declare(metadata [255 x i8]* %filename, metadata !1624, metadata !246), !dbg !1625
  call void @llvm.dbg.declare(metadata i32* %from_index, metadata !1626, metadata !246), !dbg !1627
  call void @llvm.dbg.declare(metadata i32* %to_index, metadata !1628, metadata !246), !dbg !1629
  store i32 0, i32* %from_index, align 4, !dbg !1630
  %arraydecay = getelementptr inbounds [255 x i8], [255 x i8]* %filename, i32 0, i32 0, !dbg !1631
  call void @llvm.memset.p0i8.i64(i8* %arraydecay, i8 0, i64 255, i32 16, i1 false), !dbg !1631
  store i32 0, i32* %to_index, align 4, !dbg !1632
  br label %while.cond, !dbg !1633

while.cond:                                       ; preds = %if.end32, %entry
  %0 = load i32, i32* %from_index, align 4, !dbg !1634
  %idxprom = sext i32 %0 to i64, !dbg !1636
  %1 = load i8*, i8** %filenames.addr, align 8, !dbg !1636
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 %idxprom, !dbg !1636
  %2 = load i8, i8* %arrayidx, align 1, !dbg !1636
  %conv = sext i8 %2 to i32, !dbg !1636
  %cmp = icmp sgt i32 %conv, 0, !dbg !1637
  br i1 %cmp, label %while.body, label %while.end33, !dbg !1638

while.body:                                       ; preds = %while.cond
  %3 = load i32, i32* %from_index, align 4, !dbg !1639
  %idxprom2 = sext i32 %3 to i64, !dbg !1642
  %4 = load i8*, i8** %filenames.addr, align 8, !dbg !1642
  %arrayidx3 = getelementptr inbounds i8, i8* %4, i64 %idxprom2, !dbg !1642
  %5 = load i8, i8* %arrayidx3, align 1, !dbg !1642
  %conv4 = sext i8 %5 to i32, !dbg !1642
  %cmp5 = icmp eq i32 %conv4, 32, !dbg !1643
  br i1 %cmp5, label %if.then, label %if.else, !dbg !1644

if.then:                                          ; preds = %while.body
  %arraydecay7 = getelementptr inbounds [255 x i8], [255 x i8]* %filename, i32 0, i32 0, !dbg !1645
  call void @command_retr(i8* %arraydecay7), !dbg !1647
  store i32 0, i32* %to_index, align 4, !dbg !1648
  %arraydecay8 = getelementptr inbounds [255 x i8], [255 x i8]* %filename, i32 0, i32 0, !dbg !1649
  call void @llvm.memset.p0i8.i64(i8* %arraydecay8, i8 0, i64 255, i32 16, i1 false), !dbg !1649
  br label %while.cond9, !dbg !1650

while.cond9:                                      ; preds = %while.body15, %if.then
  %6 = load i32, i32* %from_index, align 4, !dbg !1651
  %idxprom10 = sext i32 %6 to i64, !dbg !1653
  %7 = load i8*, i8** %filenames.addr, align 8, !dbg !1653
  %arrayidx11 = getelementptr inbounds i8, i8* %7, i64 %idxprom10, !dbg !1653
  %8 = load i8, i8* %arrayidx11, align 1, !dbg !1653
  %conv12 = sext i8 %8 to i32, !dbg !1653
  %cmp13 = icmp eq i32 %conv12, 32, !dbg !1654
  br i1 %cmp13, label %while.body15, label %while.end, !dbg !1655

while.body15:                                     ; preds = %while.cond9
  %9 = load i32, i32* %from_index, align 4, !dbg !1656
  %inc = add nsw i32 %9, 1, !dbg !1656
  store i32 %inc, i32* %from_index, align 4, !dbg !1656
  br label %while.cond9, !dbg !1657

while.end:                                        ; preds = %while.cond9
  br label %if.end28, !dbg !1659

if.else:                                          ; preds = %while.body
  %10 = load i32, i32* %from_index, align 4, !dbg !1660
  %idxprom16 = sext i32 %10 to i64, !dbg !1662
  %11 = load i8*, i8** %filenames.addr, align 8, !dbg !1662
  %arrayidx17 = getelementptr inbounds i8, i8* %11, i64 %idxprom16, !dbg !1662
  %12 = load i8, i8* %arrayidx17, align 1, !dbg !1662
  %13 = load i32, i32* %to_index, align 4, !dbg !1663
  %idxprom18 = sext i32 %13 to i64, !dbg !1664
  %arrayidx19 = getelementptr inbounds [255 x i8], [255 x i8]* %filename, i64 0, i64 %idxprom18, !dbg !1664
  store i8 %12, i8* %arrayidx19, align 1, !dbg !1665
  %14 = load i32, i32* %to_index, align 4, !dbg !1666
  %inc20 = add nsw i32 %14, 1, !dbg !1666
  store i32 %inc20, i32* %to_index, align 4, !dbg !1666
  %15 = load i32, i32* %from_index, align 4, !dbg !1667
  %inc21 = add nsw i32 %15, 1, !dbg !1667
  store i32 %inc21, i32* %from_index, align 4, !dbg !1667
  %16 = load i32, i32* %from_index, align 4, !dbg !1668
  %idxprom22 = sext i32 %16 to i64, !dbg !1670
  %17 = load i8*, i8** %filenames.addr, align 8, !dbg !1670
  %arrayidx23 = getelementptr inbounds i8, i8* %17, i64 %idxprom22, !dbg !1670
  %18 = load i8, i8* %arrayidx23, align 1, !dbg !1670
  %tobool = icmp ne i8 %18, 0, !dbg !1670
  br i1 %tobool, label %if.end, label %if.then24, !dbg !1671

if.then24:                                        ; preds = %if.else
  %arraydecay25 = getelementptr inbounds [255 x i8], [255 x i8]* %filename, i32 0, i32 0, !dbg !1672
  call void @command_retr(i8* %arraydecay25), !dbg !1674
  store i32 0, i32* %to_index, align 4, !dbg !1675
  %arraydecay26 = getelementptr inbounds [255 x i8], [255 x i8]* %filename, i32 0, i32 0, !dbg !1676
  call void @llvm.memset.p0i8.i64(i8* %arraydecay26, i8 0, i64 255, i32 16, i1 false), !dbg !1676
  %19 = load i32, i32* %from_index, align 4, !dbg !1677
  %inc27 = add nsw i32 %19, 1, !dbg !1677
  store i32 %inc27, i32* %from_index, align 4, !dbg !1677
  br label %if.end, !dbg !1678

if.end:                                           ; preds = %if.then24, %if.else
  br label %if.end28

if.end28:                                         ; preds = %if.end, %while.end
  %20 = load i32, i32* %to_index, align 4, !dbg !1679
  %cmp29 = icmp sgt i32 %20, 253, !dbg !1681
  br i1 %cmp29, label %if.then31, label %if.end32, !dbg !1682

if.then31:                                        ; preds = %if.end28
  %21 = load i8*, i8** %filenames.addr, align 8, !dbg !1683
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.50, i32 0, i32 0), i8* %21), !dbg !1685
  br label %while.end33, !dbg !1686

if.end32:                                         ; preds = %if.end28
  br label %while.cond, !dbg !1687

while.end33:                                      ; preds = %if.then31, %while.cond
  ret void, !dbg !1689
}

; Function Attrs: nounwind uwtable
define void @command_retr(i8* %filename) #0 !dbg !148 {
entry:
  %filename.addr = alloca i8*, align 8
  %num_clients = alloca i32, align 4
  %new_num_clients = alloca i32, align 4
  %my_buffer_size = alloca i32, align 4
  %mapped = alloca i8*, align 8
  %buffer = alloca i8*, align 8
  %xfer_delay = alloca i32, align 4
  %wait_time = alloca %struct.timeval, align 8
  %get_value = alloca i64, align 8
  %send_status = alloca i64, align 8
  %change_buffer_size = alloca i32, align 4
  %phile = alloca i32, align 4
  %i = alloca i32, align 4
  %whattodo = alloca i32, align 4
  %statbuf = alloca %struct.stat, align 8
  store i8* %filename, i8** %filename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filename.addr, metadata !1690, metadata !246), !dbg !1691
  call void @llvm.dbg.declare(metadata i32* %num_clients, metadata !1692, metadata !246), !dbg !1693
  store i32 1, i32* %num_clients, align 4, !dbg !1693
  call void @llvm.dbg.declare(metadata i32* %new_num_clients, metadata !1694, metadata !246), !dbg !1695
  store i32 1, i32* %new_num_clients, align 4, !dbg !1695
  call void @llvm.dbg.declare(metadata i32* %my_buffer_size, metadata !1696, metadata !246), !dbg !1697
  call void @llvm.dbg.declare(metadata i8** %mapped, metadata !1698, metadata !246), !dbg !1699
  store i8* null, i8** %mapped, align 8, !dbg !1699
  call void @llvm.dbg.declare(metadata i8** %buffer, metadata !1700, metadata !246), !dbg !1701
  call void @llvm.dbg.declare(metadata i32* %xfer_delay, metadata !1702, metadata !246), !dbg !1703
  call void @llvm.dbg.declare(metadata %struct.timeval* %wait_time, metadata !1704, metadata !246), !dbg !1705
  call void @llvm.dbg.declare(metadata i64* %get_value, metadata !1706, metadata !246), !dbg !1707
  call void @llvm.dbg.declare(metadata i64* %send_status, metadata !1708, metadata !246), !dbg !1711
  call void @llvm.dbg.declare(metadata i32* %change_buffer_size, metadata !1712, metadata !246), !dbg !1713
  store i32 0, i32* %change_buffer_size, align 4, !dbg !1713
  call void @llvm.dbg.declare(metadata i32* %phile, metadata !1714, metadata !246), !dbg !1715
  call void @llvm.dbg.declare(metadata i32* %i, metadata !1716, metadata !246), !dbg !1717
  call void @llvm.dbg.declare(metadata i32* %whattodo, metadata !1718, metadata !246), !dbg !1719
  store i32 0, i32* %whattodo, align 4, !dbg !1719
  call void @llvm.dbg.declare(metadata %struct.stat* %statbuf, metadata !1720, metadata !246), !dbg !1721
  %call = call i8* @config_getoption(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.51, i32 0, i32 0)), !dbg !1722
  %call1 = call i64 @strtoul(i8* %call, i8** null, i32 0) #2, !dbg !1723
  store i64 %call1, i64* %get_value, align 8, !dbg !1725
  %0 = load i64, i64* %get_value, align 8, !dbg !1726
  %cmp = icmp ule i64 %0, 2147483647, !dbg !1728
  br i1 %cmp, label %if.then, label %if.else, !dbg !1729

if.then:                                          ; preds = %entry
  %1 = load i64, i64* %get_value, align 8, !dbg !1730
  %conv = trunc i64 %1 to i32, !dbg !1730
  store i32 %conv, i32* %xfer_delay, align 4, !dbg !1731
  br label %if.end, !dbg !1732

if.else:                                          ; preds = %entry
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.68, i32 0, i32 0), i32 0), !dbg !1733
  store i32 0, i32* %xfer_delay, align 4, !dbg !1735
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %2 = load i8*, i8** %filename.addr, align 8, !dbg !1736
  %call2 = call i8* @bftpd_cwd_mappath(i8* %2), !dbg !1737
  store i8* %call2, i8** %mapped, align 8, !dbg !1738
  %3 = load i8*, i8** %mapped, align 8, !dbg !1739
  %tobool = icmp ne i8* %3, null, !dbg !1739
  br i1 %tobool, label %if.end4, label %if.then3, !dbg !1741

if.then3:                                         ; preds = %if.end
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.69, i32 0, i32 0), i32 0), !dbg !1742
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.70, i32 0, i32 0), i32 9), !dbg !1744
  br label %if.end120, !dbg !1745

if.end4:                                          ; preds = %if.end
  %call5 = call i8* @config_getoption(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.60, i32 0, i32 0)), !dbg !1746
  %call6 = call i32 @strcasecmp(i8* %call5, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.8, i32 0, i32 0)) #9, !dbg !1748
  %tobool7 = icmp ne i32 %call6, 0, !dbg !1750
  br i1 %tobool7, label %if.end9, label %if.then8, !dbg !1751

if.then8:                                         ; preds = %if.end4
  store i32 1, i32* %change_buffer_size, align 4, !dbg !1752
  br label %if.end9, !dbg !1753

if.end9:                                          ; preds = %if.then8, %if.end4
  %4 = load i8*, i8** %mapped, align 8, !dbg !1754
  %call10 = call i32 (i8*, i32, ...) @open64(i8* %4, i32 0), !dbg !1755
  store i32 %call10, i32* %phile, align 4, !dbg !1756
  %5 = load i32, i32* %phile, align 4, !dbg !1757
  %cmp11 = icmp eq i32 %5, -1, !dbg !1759
  br i1 %cmp11, label %if.then13, label %if.end25, !dbg !1760

if.then13:                                        ; preds = %if.end9
  %6 = load i32, i32* %whattodo, align 4, !dbg !1761
  %cmp14 = icmp eq i32 %6, 0, !dbg !1764
  br i1 %cmp14, label %if.then16, label %if.end24, !dbg !1765

if.then16:                                        ; preds = %if.then13
  %call17 = call i32* @__errno_location() #1, !dbg !1766
  %7 = load i32, i32* %call17, align 4, !dbg !1766
  %call18 = call i8* @strerror(i32 %7) #2, !dbg !1768
  %8 = load i8*, i8** %filename.addr, align 8, !dbg !1770
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([48 x i8], [48 x i8]* @.str.71, i32 0, i32 0), i8* %call18, i8* %8), !dbg !1771
  %call19 = call i32* @__errno_location() #1, !dbg !1772
  %9 = load i32, i32* %call19, align 4, !dbg !1772
  %call20 = call i8* @strerror(i32 %9) #2, !dbg !1773
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.58, i32 0, i32 0), i8* %call20), !dbg !1774
  %10 = load i8*, i8** %mapped, align 8, !dbg !1776
  %tobool21 = icmp ne i8* %10, null, !dbg !1776
  br i1 %tobool21, label %if.then22, label %if.end23, !dbg !1778

if.then22:                                        ; preds = %if.then16
  %11 = load i8*, i8** %mapped, align 8, !dbg !1779
  call void @free(i8* %11) #2, !dbg !1780
  br label %if.end23, !dbg !1780

if.end23:                                         ; preds = %if.then22, %if.then16
  br label %if.end120, !dbg !1781

if.end24:                                         ; preds = %if.then13
  br label %if.end25, !dbg !1782

if.end25:                                         ; preds = %if.end24, %if.end9
  %12 = load i8*, i8** %mapped, align 8, !dbg !1783
  %call26 = call i32 @stat64(i8* %12, %struct.stat* %statbuf) #2, !dbg !1784
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 3, !dbg !1785
  %13 = load i32, i32* %st_mode, align 8, !dbg !1785
  %and = and i32 %13, 61440, !dbg !1785
  %cmp27 = icmp eq i32 %and, 16384, !dbg !1785
  br i1 %cmp27, label %if.then29, label %if.end33, !dbg !1787

if.then29:                                        ; preds = %if.end25
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.72, i32 0, i32 0)), !dbg !1788
  %14 = load i8*, i8** %mapped, align 8, !dbg !1790
  %tobool30 = icmp ne i8* %14, null, !dbg !1790
  br i1 %tobool30, label %if.then31, label %if.end32, !dbg !1792

if.then31:                                        ; preds = %if.then29
  %15 = load i8*, i8** %mapped, align 8, !dbg !1793
  call void @free(i8* %15) #2, !dbg !1794
  br label %if.end32, !dbg !1794

if.end32:                                         ; preds = %if.then31, %if.then29
  br label %if.end120, !dbg !1795

if.end33:                                         ; preds = %if.end25
  %st_size = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 8, !dbg !1796
  %16 = load i64, i64* %st_size, align 8, !dbg !1796
  %17 = load i64, i64* @offset, align 8, !dbg !1798
  %sub = sub i64 %16, %17, !dbg !1799
  %18 = load i32, i32* @ratio_send, align 4, !dbg !1800
  %conv34 = sext i32 %18 to i64, !dbg !1800
  %mul = mul i64 %sub, %conv34, !dbg !1801
  %19 = load i32, i32* @ratio_recv, align 4, !dbg !1802
  %conv35 = sext i32 %19 to i64, !dbg !1802
  %div = udiv i64 %mul, %conv35, !dbg !1803
  %conv36 = uitofp i64 %div to double, !dbg !1804
  %20 = load double, double* @bytes_recvd, align 8, !dbg !1805
  %21 = load double, double* @bytes_sent, align 8, !dbg !1806
  %sub37 = fsub double %20, %21, !dbg !1807
  %cmp38 = fcmp ogt double %conv36, %sub37, !dbg !1808
  br i1 %cmp38, label %land.lhs.true, label %if.end55, !dbg !1809

land.lhs.true:                                    ; preds = %if.end33
  %call40 = call i8* @config_getoption(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.73, i32 0, i32 0)), !dbg !1810
  %call41 = call i32 @strcmp(i8* %call40, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.74, i32 0, i32 0)) #9, !dbg !1812
  %tobool42 = icmp ne i32 %call41, 0, !dbg !1814
  br i1 %tobool42, label %if.then43, label %if.end55, !dbg !1815

if.then43:                                        ; preds = %land.lhs.true
  %22 = load i8*, i8** %filename.addr, align 8, !dbg !1816
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.75, i32 0, i32 0), i8* %22), !dbg !1818
  %st_size44 = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 8, !dbg !1819
  %23 = load i64, i64* %st_size44, align 8, !dbg !1819
  %24 = load i64, i64* @offset, align 8, !dbg !1820
  %sub45 = sub i64 %23, %24, !dbg !1821
  %25 = load i32, i32* @ratio_send, align 4, !dbg !1822
  %conv46 = sext i32 %25 to i64, !dbg !1822
  %mul47 = mul i64 %sub45, %conv46, !dbg !1823
  %26 = load i32, i32* @ratio_recv, align 4, !dbg !1824
  %conv48 = sext i32 %26 to i64, !dbg !1824
  %div49 = udiv i64 %mul47, %conv48, !dbg !1825
  %conv50 = uitofp i64 %div49 to double, !dbg !1826
  %27 = load double, double* @bytes_recvd, align 8, !dbg !1827
  %sub51 = fsub double %conv50, %27, !dbg !1828
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str.76, i32 0, i32 0), double %sub51), !dbg !1829
  %28 = load i8*, i8** %mapped, align 8, !dbg !1830
  %tobool52 = icmp ne i8* %28, null, !dbg !1830
  br i1 %tobool52, label %if.then53, label %if.end54, !dbg !1832

if.then53:                                        ; preds = %if.then43
  %29 = load i8*, i8** %mapped, align 8, !dbg !1833
  call void @free(i8* %29) #2, !dbg !1834
  br label %if.end54, !dbg !1834

if.end54:                                         ; preds = %if.then53, %if.then43
  br label %if.end120, !dbg !1835

if.end55:                                         ; preds = %land.lhs.true, %if.end33
  %30 = load i8*, i8** %filename.addr, align 8, !dbg !1836
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.77, i32 0, i32 0), i8* %30), !dbg !1837
  %31 = load i32, i32* %whattodo, align 4, !dbg !1838
  switch i32 %31, label %sw.epilog [
    i32 0, label %sw.bb
  ], !dbg !1839

sw.bb:                                            ; preds = %if.end55
  %32 = load i8*, i8** %mapped, align 8, !dbg !1840
  %tobool56 = icmp ne i8* %32, null, !dbg !1840
  br i1 %tobool56, label %if.then57, label %if.end58, !dbg !1843

if.then57:                                        ; preds = %sw.bb
  %33 = load i8*, i8** %mapped, align 8, !dbg !1844
  call void @free(i8* %33) #2, !dbg !1846
  store i8* null, i8** %mapped, align 8, !dbg !1847
  br label %if.end58, !dbg !1848

if.end58:                                         ; preds = %if.then57, %sw.bb
  %call59 = call i32 @dataconn(), !dbg !1849
  %tobool60 = icmp ne i32 %call59, 0, !dbg !1849
  br i1 %tobool60, label %if.then61, label %if.end62, !dbg !1851

if.then61:                                        ; preds = %if.end58
  br label %if.end120, !dbg !1852

if.end62:                                         ; preds = %if.end58
  %call63 = call i32 @alarm(i32 0) #2, !dbg !1853
  %34 = load i32, i32* %phile, align 4, !dbg !1854
  %35 = load i64, i64* @offset, align 8, !dbg !1855
  %call64 = call i64 @lseek64(i32 %34, i64 %35, i32 0) #2, !dbg !1856
  store i64 0, i64* @offset, align 8, !dbg !1857
  %36 = load i32, i32* @xfer_bufsize, align 4, !dbg !1858
  %mul65 = mul nsw i32 %36, 2, !dbg !1859
  %add = add nsw i32 %mul65, 1, !dbg !1860
  %conv66 = sext i32 %add to i64, !dbg !1858
  %call67 = call noalias i8* @malloc(i64 %conv66) #2, !dbg !1861
  store i8* %call67, i8** %buffer, align 8, !dbg !1862
  %37 = load i8*, i8** %buffer, align 8, !dbg !1863
  %tobool68 = icmp ne i8* %37, null, !dbg !1863
  br i1 %tobool68, label %if.end72, label %if.then69, !dbg !1865

if.then69:                                        ; preds = %if.end62
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.78, i32 0, i32 0)), !dbg !1866
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str.79, i32 0, i32 0), i32 0), !dbg !1868
  %38 = load i32, i32* @sock, align 4, !dbg !1869
  %call70 = call i32 @close(i32 %38), !dbg !1870
  %39 = load i32, i32* %phile, align 4, !dbg !1871
  %call71 = call i32 @close(i32 %39), !dbg !1872
  br label %if.end120, !dbg !1873

if.end72:                                         ; preds = %if.end62
  %40 = load i32, i32* %change_buffer_size, align 4, !dbg !1874
  %tobool73 = icmp ne i32 %40, 0, !dbg !1874
  br i1 %tobool73, label %if.then74, label %if.else77, !dbg !1876

if.then74:                                        ; preds = %if.end72
  %call75 = call i32 @bftpdutmp_usercount(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.61, i32 0, i32 0)), !dbg !1877
  store i32 %call75, i32* %num_clients, align 4, !dbg !1879
  %41 = load i32, i32* %num_clients, align 4, !dbg !1880
  %call76 = call i32 @get_buffer_size(i32 %41), !dbg !1881
  store i32 %call76, i32* %my_buffer_size, align 4, !dbg !1882
  br label %if.end78, !dbg !1883

if.else77:                                        ; preds = %if.end72
  %42 = load i32, i32* @xfer_bufsize, align 4, !dbg !1884
  store i32 %42, i32* %my_buffer_size, align 4, !dbg !1885
  br label %if.end78

if.end78:                                         ; preds = %if.else77, %if.then74
  br label %while.cond, !dbg !1886

while.cond:                                       ; preds = %if.end114, %if.end78
  %43 = load i32, i32* %phile, align 4, !dbg !1887
  %44 = load i8*, i8** %buffer, align 8, !dbg !1889
  %45 = load i32, i32* %my_buffer_size, align 4, !dbg !1890
  %conv79 = sext i32 %45 to i64, !dbg !1890
  %call80 = call i64 @read(i32 %43, i8* %44, i64 %conv79), !dbg !1891
  %conv81 = trunc i64 %call80 to i32, !dbg !1891
  store i32 %conv81, i32* %i, align 4, !dbg !1892
  %tobool82 = icmp ne i32 %conv81, 0, !dbg !1893
  br i1 %tobool82, label %while.body, label %while.end, !dbg !1893

while.body:                                       ; preds = %while.cond
  %46 = load i32, i32* %phile, align 4, !dbg !1894
  %47 = load i32, i32* @sock, align 4, !dbg !1897
  %call83 = call signext i8 @test_abort(i8 signext 1, i32 %46, i32 %47), !dbg !1898
  %tobool84 = icmp ne i8 %call83, 0, !dbg !1898
  br i1 %tobool84, label %if.then85, label %if.end86, !dbg !1899

if.then85:                                        ; preds = %while.body
  %48 = load i8*, i8** %buffer, align 8, !dbg !1900
  call void @free(i8* %48) #2, !dbg !1902
  br label %if.end120, !dbg !1903

if.end86:                                         ; preds = %while.body
  %49 = load i16, i16* @xfertype, align 2, !dbg !1904
  %conv87 = sext i16 %49 to i32, !dbg !1904
  %cmp88 = icmp eq i32 %conv87, 0, !dbg !1906
  br i1 %cmp88, label %if.then90, label %if.end93, !dbg !1907

if.then90:                                        ; preds = %if.end86
  %50 = load i32, i32* %i, align 4, !dbg !1908
  %idxprom = sext i32 %50 to i64, !dbg !1910
  %51 = load i8*, i8** %buffer, align 8, !dbg !1910
  %arrayidx = getelementptr inbounds i8, i8* %51, i64 %idxprom, !dbg !1910
  store i8 0, i8* %arrayidx, align 1, !dbg !1911
  %52 = load i8*, i8** %buffer, align 8, !dbg !1912
  %53 = load i32, i32* @xfer_bufsize, align 4, !dbg !1913
  %call91 = call i32 @replace(i8* %52, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.80, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.81, i32 0, i32 0), i32 %53), !dbg !1914
  %54 = load i32, i32* %i, align 4, !dbg !1915
  %add92 = add nsw i32 %54, %call91, !dbg !1915
  store i32 %add92, i32* %i, align 4, !dbg !1915
  br label %if.end93, !dbg !1916

if.end93:                                         ; preds = %if.then90, %if.end86
  %55 = load i32, i32* @sock, align 4, !dbg !1917
  %56 = load i8*, i8** %buffer, align 8, !dbg !1918
  %57 = load i32, i32* %i, align 4, !dbg !1919
  %conv94 = sext i32 %57 to i64, !dbg !1919
  %call95 = call i64 @send(i32 %55, i8* %56, i64 %conv94, i32 0), !dbg !1920
  store i64 %call95, i64* %send_status, align 8, !dbg !1921
  %58 = load i64, i64* %send_status, align 8, !dbg !1922
  %cmp96 = icmp slt i64 %58, 0, !dbg !1924
  br i1 %cmp96, label %if.then98, label %if.end102, !dbg !1925

if.then98:                                        ; preds = %if.end93
  %59 = load i8*, i8** %buffer, align 8, !dbg !1926
  call void @free(i8* %59) #2, !dbg !1928
  %60 = load i32, i32* %phile, align 4, !dbg !1929
  %call99 = call i32 @close(i32 %60), !dbg !1930
  %61 = load i32, i32* @sock, align 4, !dbg !1931
  %call100 = call i32 @close(i32 %61), !dbg !1932
  %62 = load i32, i32* @control_timeout, align 4, !dbg !1933
  %call101 = call i32 @alarm(i32 %62) #2, !dbg !1934
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.47, i32 0, i32 0)), !dbg !1935
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.48, i32 0, i32 0)), !dbg !1936
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.82, i32 0, i32 0)), !dbg !1937
  br label %if.end120, !dbg !1938

if.end102:                                        ; preds = %if.end93
  %63 = load i32, i32* %i, align 4, !dbg !1939
  %conv103 = sitofp i32 %63 to double, !dbg !1939
  %64 = load double, double* @bytes_sent, align 8, !dbg !1940
  %add104 = fadd double %64, %conv103, !dbg !1940
  store double %add104, double* @bytes_sent, align 8, !dbg !1940
  %65 = load i32, i32* %change_buffer_size, align 4, !dbg !1941
  %tobool105 = icmp ne i32 %65, 0, !dbg !1941
  br i1 %tobool105, label %if.then106, label %if.end109, !dbg !1943

if.then106:                                       ; preds = %if.end102
  %call107 = call i32 @bftpdutmp_usercount(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.61, i32 0, i32 0)), !dbg !1944
  store i32 %call107, i32* %new_num_clients, align 4, !dbg !1946
  %66 = load i32, i32* %num_clients, align 4, !dbg !1947
  %call108 = call i32 @get_buffer_size(i32 %66), !dbg !1948
  store i32 %call108, i32* %my_buffer_size, align 4, !dbg !1949
  br label %if.end109, !dbg !1950

if.end109:                                        ; preds = %if.then106, %if.end102
  %67 = load i32, i32* %xfer_delay, align 4, !dbg !1951
  %tobool110 = icmp ne i32 %67, 0, !dbg !1951
  br i1 %tobool110, label %if.then111, label %if.end114, !dbg !1953

if.then111:                                       ; preds = %if.end109
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %wait_time, i32 0, i32 0, !dbg !1954
  store i64 0, i64* %tv_sec, align 8, !dbg !1956
  %68 = load i32, i32* %xfer_delay, align 4, !dbg !1957
  %conv112 = sext i32 %68 to i64, !dbg !1957
  %tv_usec = getelementptr inbounds %struct.timeval, %struct.timeval* %wait_time, i32 0, i32 1, !dbg !1958
  store i64 %conv112, i64* %tv_usec, align 8, !dbg !1959
  %call113 = call i32 @select(i32 0, %struct.fd_set* null, %struct.fd_set* null, %struct.fd_set* null, %struct.timeval* %wait_time), !dbg !1960
  br label %if.end114, !dbg !1961

if.end114:                                        ; preds = %if.then111, %if.end109
  br label %while.cond, !dbg !1962

while.end:                                        ; preds = %while.cond
  %69 = load i8*, i8** %buffer, align 8, !dbg !1964
  call void @free(i8* %69) #2, !dbg !1965
  br label %sw.epilog, !dbg !1966

sw.epilog:                                        ; preds = %while.end, %if.end55
  %70 = load i32, i32* %phile, align 4, !dbg !1967
  %call115 = call i32 @close(i32 %70), !dbg !1968
  %71 = load i32, i32* @sock, align 4, !dbg !1969
  %call116 = call i32 @close(i32 %71), !dbg !1970
  store i64 0, i64* @offset, align 8, !dbg !1971
  %72 = load i32, i32* @control_timeout, align 4, !dbg !1972
  %call117 = call i32 @alarm(i32 %72) #2, !dbg !1973
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.66, i32 0, i32 0)), !dbg !1974
  %73 = load i8*, i8** %filename.addr, align 8, !dbg !1975
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.83, i32 0, i32 0), i8* %73), !dbg !1976
  %74 = load i8*, i8** %mapped, align 8, !dbg !1977
  %tobool118 = icmp ne i8* %74, null, !dbg !1977
  br i1 %tobool118, label %if.then119, label %if.end120, !dbg !1979

if.then119:                                       ; preds = %sw.epilog
  %75 = load i8*, i8** %mapped, align 8, !dbg !1980
  call void @free(i8* %75) #2, !dbg !1982
  br label %if.end120, !dbg !1982

if.end120:                                        ; preds = %if.then3, %if.end23, %if.end32, %if.end54, %if.then61, %if.then69, %if.then85, %if.then98, %if.then119, %sw.epilog
  ret void, !dbg !1983
}

; Function Attrs: nounwind
declare i32 @stat64(i8*, %struct.stat*) #3

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #7

declare i64 @read(i32, i8*, i64) #4

declare i64 @send(i32, i8*, i64, i32) #4

; Function Attrs: nounwind uwtable
define void @do_dirlist(i8* %dirname, i8 signext %verbose) #0 !dbg !149 {
entry:
  %dirname.addr = alloca i8*, align 8
  %verbose.addr = alloca i8, align 1
  %show_hidden = alloca i32, align 4
  %datastream = alloca %struct._IO_FILE*, align 8
  %mapped = alloca i8*, align 8
  store i8* %dirname, i8** %dirname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dirname.addr, metadata !1984, metadata !246), !dbg !1985
  store i8 %verbose, i8* %verbose.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %verbose.addr, metadata !1986, metadata !246), !dbg !1987
  call void @llvm.dbg.declare(metadata i32* %show_hidden, metadata !1988, metadata !246), !dbg !1989
  store i32 0, i32* %show_hidden, align 4, !dbg !1989
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %datastream, metadata !1990, metadata !246), !dbg !2039
  %0 = load i8*, i8** %dirname.addr, align 8, !dbg !2040
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !2040
  %1 = load i8, i8* %arrayidx, align 1, !dbg !2040
  %conv = sext i8 %1 to i32, !dbg !2040
  %cmp = icmp ne i32 %conv, 0, !dbg !2042
  br i1 %cmp, label %if.then, label %if.end53, !dbg !2043

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** %dirname.addr, align 8, !dbg !2044
  %arrayidx2 = getelementptr inbounds i8, i8* %2, i64 0, !dbg !2044
  %3 = load i8, i8* %arrayidx2, align 1, !dbg !2044
  %conv3 = sext i8 %3 to i32, !dbg !2044
  %cmp4 = icmp eq i32 %conv3, 45, !dbg !2047
  br i1 %cmp4, label %land.lhs.true, label %if.else, !dbg !2048

land.lhs.true:                                    ; preds = %if.then
  %4 = load i8*, i8** %dirname.addr, align 8, !dbg !2049
  %arrayidx6 = getelementptr inbounds i8, i8* %4, i64 1, !dbg !2049
  %5 = load i8, i8* %arrayidx6, align 1, !dbg !2049
  %conv7 = sext i8 %5 to i32, !dbg !2049
  %cmp8 = icmp eq i32 %conv7, 97, !dbg !2051
  br i1 %cmp8, label %if.then10, label %if.else, !dbg !2052

if.then10:                                        ; preds = %land.lhs.true
  store i32 1, i32* %show_hidden, align 4, !dbg !2053
  br label %while.cond, !dbg !2055

while.cond:                                       ; preds = %while.body, %if.then10
  %6 = load i8*, i8** %dirname.addr, align 8, !dbg !2056
  %arrayidx11 = getelementptr inbounds i8, i8* %6, i64 0, !dbg !2056
  %7 = load i8, i8* %arrayidx11, align 1, !dbg !2056
  %conv12 = sext i8 %7 to i32, !dbg !2056
  %cmp13 = icmp ne i32 %conv12, 32, !dbg !2058
  br i1 %cmp13, label %land.rhs, label %land.end, !dbg !2059

land.rhs:                                         ; preds = %while.cond
  %8 = load i8*, i8** %dirname.addr, align 8, !dbg !2060
  %arrayidx15 = getelementptr inbounds i8, i8* %8, i64 0, !dbg !2060
  %9 = load i8, i8* %arrayidx15, align 1, !dbg !2060
  %conv16 = sext i8 %9 to i32, !dbg !2060
  %cmp17 = icmp ne i32 %conv16, 0, !dbg !2062
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %10 = phi i1 [ false, %while.cond ], [ %cmp17, %land.rhs ]
  br i1 %10, label %while.body, label %while.end, !dbg !2063

while.body:                                       ; preds = %land.end
  %11 = load i8*, i8** %dirname.addr, align 8, !dbg !2065
  %incdec.ptr = getelementptr inbounds i8, i8* %11, i32 1, !dbg !2065
  store i8* %incdec.ptr, i8** %dirname.addr, align 8, !dbg !2065
  br label %while.cond, !dbg !2066

while.end:                                        ; preds = %land.end
  %12 = load i8*, i8** %dirname.addr, align 8, !dbg !2068
  %arrayidx19 = getelementptr inbounds i8, i8* %12, i64 0, !dbg !2068
  %13 = load i8, i8* %arrayidx19, align 1, !dbg !2068
  %conv20 = sext i8 %13 to i32, !dbg !2068
  %cmp21 = icmp ne i32 %conv20, 0, !dbg !2070
  br i1 %cmp21, label %if.then23, label %if.end, !dbg !2071

if.then23:                                        ; preds = %while.end
  %14 = load i8*, i8** %dirname.addr, align 8, !dbg !2072
  %incdec.ptr24 = getelementptr inbounds i8, i8* %14, i32 1, !dbg !2072
  store i8* %incdec.ptr24, i8** %dirname.addr, align 8, !dbg !2072
  br label %if.end, !dbg !2073

if.end:                                           ; preds = %if.then23, %while.end
  br label %if.end52, !dbg !2074

if.else:                                          ; preds = %land.lhs.true, %if.then
  %15 = load i8*, i8** %dirname.addr, align 8, !dbg !2075
  %arrayidx25 = getelementptr inbounds i8, i8* %15, i64 0, !dbg !2075
  %16 = load i8, i8* %arrayidx25, align 1, !dbg !2075
  %conv26 = sext i8 %16 to i32, !dbg !2075
  %cmp27 = icmp eq i32 %conv26, 45, !dbg !2077
  br i1 %cmp27, label %if.then29, label %if.end51, !dbg !2078

if.then29:                                        ; preds = %if.else
  br label %while.cond30, !dbg !2079

while.cond30:                                     ; preds = %while.body41, %if.then29
  %17 = load i8*, i8** %dirname.addr, align 8, !dbg !2081
  %arrayidx31 = getelementptr inbounds i8, i8* %17, i64 0, !dbg !2081
  %18 = load i8, i8* %arrayidx31, align 1, !dbg !2081
  %conv32 = sext i8 %18 to i32, !dbg !2081
  %cmp33 = icmp ne i32 %conv32, 32, !dbg !2083
  br i1 %cmp33, label %land.rhs35, label %land.end40, !dbg !2084

land.rhs35:                                       ; preds = %while.cond30
  %19 = load i8*, i8** %dirname.addr, align 8, !dbg !2085
  %arrayidx36 = getelementptr inbounds i8, i8* %19, i64 0, !dbg !2085
  %20 = load i8, i8* %arrayidx36, align 1, !dbg !2085
  %conv37 = sext i8 %20 to i32, !dbg !2085
  %cmp38 = icmp ne i32 %conv37, 0, !dbg !2087
  br label %land.end40

land.end40:                                       ; preds = %land.rhs35, %while.cond30
  %21 = phi i1 [ false, %while.cond30 ], [ %cmp38, %land.rhs35 ]
  br i1 %21, label %while.body41, label %while.end43, !dbg !2088

while.body41:                                     ; preds = %land.end40
  %22 = load i8*, i8** %dirname.addr, align 8, !dbg !2090
  %incdec.ptr42 = getelementptr inbounds i8, i8* %22, i32 1, !dbg !2090
  store i8* %incdec.ptr42, i8** %dirname.addr, align 8, !dbg !2090
  br label %while.cond30, !dbg !2091

while.end43:                                      ; preds = %land.end40
  %23 = load i8*, i8** %dirname.addr, align 8, !dbg !2093
  %arrayidx44 = getelementptr inbounds i8, i8* %23, i64 0, !dbg !2093
  %24 = load i8, i8* %arrayidx44, align 1, !dbg !2093
  %conv45 = sext i8 %24 to i32, !dbg !2093
  %cmp46 = icmp ne i32 %conv45, 0, !dbg !2095
  br i1 %cmp46, label %if.then48, label %if.end50, !dbg !2096

if.then48:                                        ; preds = %while.end43
  %25 = load i8*, i8** %dirname.addr, align 8, !dbg !2097
  %incdec.ptr49 = getelementptr inbounds i8, i8* %25, i32 1, !dbg !2097
  store i8* %incdec.ptr49, i8** %dirname.addr, align 8, !dbg !2097
  br label %if.end50, !dbg !2098

if.end50:                                         ; preds = %if.then48, %while.end43
  br label %if.end51, !dbg !2099

if.end51:                                         ; preds = %if.end50, %if.else
  br label %if.end52

if.end52:                                         ; preds = %if.end51, %if.end
  br label %if.end53, !dbg !2100

if.end53:                                         ; preds = %if.end52, %entry
  %call = call i32 @dataconn(), !dbg !2101
  %tobool = icmp ne i32 %call, 0, !dbg !2101
  br i1 %tobool, label %if.then54, label %if.end55, !dbg !2103

if.then54:                                        ; preds = %if.end53
  br label %return, !dbg !2104

if.end55:                                         ; preds = %if.end53
  %call56 = call i32 @alarm(i32 0) #2, !dbg !2105
  %26 = load i32, i32* @sock, align 4, !dbg !2106
  %call57 = call %struct._IO_FILE* @fdopen(i32 %26, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.84, i32 0, i32 0)) #2, !dbg !2107
  store %struct._IO_FILE* %call57, %struct._IO_FILE** %datastream, align 8, !dbg !2108
  %27 = load i8*, i8** %dirname.addr, align 8, !dbg !2109
  %arrayidx58 = getelementptr inbounds i8, i8* %27, i64 0, !dbg !2109
  %28 = load i8, i8* %arrayidx58, align 1, !dbg !2109
  %conv59 = sext i8 %28 to i32, !dbg !2109
  %cmp60 = icmp eq i32 %conv59, 0, !dbg !2111
  br i1 %cmp60, label %if.then62, label %if.else63, !dbg !2112

if.then62:                                        ; preds = %if.end55
  %29 = load %struct._IO_FILE*, %struct._IO_FILE** %datastream, align 8, !dbg !2113
  %30 = load i8, i8* %verbose.addr, align 1, !dbg !2114
  %31 = load i32, i32* %show_hidden, align 4, !dbg !2115
  call void @dirlist(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.61, i32 0, i32 0), %struct._IO_FILE* %29, i8 signext %30, i32 %31), !dbg !2116
  br label %if.end65, !dbg !2116

if.else63:                                        ; preds = %if.end55
  call void @llvm.dbg.declare(metadata i8** %mapped, metadata !2117, metadata !246), !dbg !2119
  %32 = load i8*, i8** %dirname.addr, align 8, !dbg !2120
  %call64 = call i8* @bftpd_cwd_mappath(i8* %32), !dbg !2121
  store i8* %call64, i8** %mapped, align 8, !dbg !2119
  %33 = load i8*, i8** %mapped, align 8, !dbg !2122
  %34 = load %struct._IO_FILE*, %struct._IO_FILE** %datastream, align 8, !dbg !2123
  %35 = load i8, i8* %verbose.addr, align 1, !dbg !2124
  %36 = load i32, i32* %show_hidden, align 4, !dbg !2125
  call void @dirlist(i8* %33, %struct._IO_FILE* %34, i8 signext %35, i32 %36), !dbg !2126
  %37 = load i8*, i8** %mapped, align 8, !dbg !2127
  call void @free(i8* %37) #2, !dbg !2128
  br label %if.end65

if.end65:                                         ; preds = %if.else63, %if.then62
  %38 = load %struct._IO_FILE*, %struct._IO_FILE** %datastream, align 8, !dbg !2129
  %call66 = call i32 @fclose(%struct._IO_FILE* %38), !dbg !2130
  %39 = load i32, i32* @control_timeout, align 4, !dbg !2131
  %call67 = call i32 @alarm(i32 %39) #2, !dbg !2132
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.85, i32 0, i32 0)), !dbg !2133
  br label %return, !dbg !2134

return:                                           ; preds = %if.end65, %if.then54
  ret void, !dbg !2135
}

; Function Attrs: nounwind
declare %struct._IO_FILE* @fdopen(i32, i8*) #3

declare void @dirlist(i8*, %struct._IO_FILE*, i8 signext, i32) #4

declare i32 @fclose(%struct._IO_FILE*) #4

; Function Attrs: nounwind uwtable
define void @command_list(i8* %dirname) #0 !dbg !152 {
entry:
  %dirname.addr = alloca i8*, align 8
  store i8* %dirname, i8** %dirname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dirname.addr, metadata !2137, metadata !246), !dbg !2138
  %0 = load i8*, i8** %dirname.addr, align 8, !dbg !2139
  call void @do_dirlist(i8* %0, i8 signext 1), !dbg !2140
  ret void, !dbg !2141
}

; Function Attrs: nounwind uwtable
define void @command_nlst(i8* %dirname) #0 !dbg !153 {
entry:
  %dirname.addr = alloca i8*, align 8
  store i8* %dirname, i8** %dirname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dirname.addr, metadata !2142, metadata !246), !dbg !2143
  %0 = load i8*, i8** %dirname.addr, align 8, !dbg !2144
  call void @do_dirlist(i8* %0, i8 signext 0), !dbg !2145
  ret void, !dbg !2146
}

; Function Attrs: nounwind uwtable
define void @command_syst(i8* %params) #0 !dbg !154 {
entry:
  %params.addr = alloca i8*, align 8
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !2147, metadata !246), !dbg !2148
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.86, i32 0, i32 0)), !dbg !2149
  ret void, !dbg !2150
}

; Function Attrs: nounwind uwtable
define void @command_mdtm(i8* %filename) #0 !dbg !155 {
entry:
  %filename.addr = alloca i8*, align 8
  %statbuf = alloca %struct.stat, align 8
  %filetime = alloca %struct.tm*, align 8
  %fullfilename = alloca i8*, align 8
  store i8* %filename, i8** %filename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filename.addr, metadata !2151, metadata !246), !dbg !2152
  call void @llvm.dbg.declare(metadata %struct.stat* %statbuf, metadata !2153, metadata !246), !dbg !2154
  call void @llvm.dbg.declare(metadata %struct.tm** %filetime, metadata !2155, metadata !246), !dbg !2172
  call void @llvm.dbg.declare(metadata i8** %fullfilename, metadata !2173, metadata !246), !dbg !2174
  %0 = load i8*, i8** %filename.addr, align 8, !dbg !2175
  %call = call i8* @bftpd_cwd_mappath(i8* %0), !dbg !2176
  store i8* %call, i8** %fullfilename, align 8, !dbg !2174
  %1 = load i8*, i8** %fullfilename, align 8, !dbg !2177
  %call1 = call i32 @stat64(i8* %1, %struct.stat* %statbuf) #2, !dbg !2179
  %tobool = icmp ne i32 %call1, 0, !dbg !2179
  br i1 %tobool, label %if.else, label %if.then, !dbg !2180

if.then:                                          ; preds = %entry
  %st_mtim = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 12, !dbg !2181
  %tv_sec = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim, i32 0, i32 0, !dbg !2181
  %call2 = call %struct.tm* @gmtime(i64* %tv_sec) #2, !dbg !2183
  store %struct.tm* %call2, %struct.tm** %filetime, align 8, !dbg !2184
  %2 = load %struct.tm*, %struct.tm** %filetime, align 8, !dbg !2185
  %tm_year = getelementptr inbounds %struct.tm, %struct.tm* %2, i32 0, i32 5, !dbg !2186
  %3 = load i32, i32* %tm_year, align 4, !dbg !2186
  %add = add nsw i32 %3, 1900, !dbg !2187
  %4 = load %struct.tm*, %struct.tm** %filetime, align 8, !dbg !2188
  %tm_mon = getelementptr inbounds %struct.tm, %struct.tm* %4, i32 0, i32 4, !dbg !2189
  %5 = load i32, i32* %tm_mon, align 8, !dbg !2189
  %add3 = add nsw i32 %5, 1, !dbg !2190
  %6 = load %struct.tm*, %struct.tm** %filetime, align 8, !dbg !2191
  %tm_mday = getelementptr inbounds %struct.tm, %struct.tm* %6, i32 0, i32 3, !dbg !2192
  %7 = load i32, i32* %tm_mday, align 4, !dbg !2192
  %8 = load %struct.tm*, %struct.tm** %filetime, align 8, !dbg !2193
  %tm_hour = getelementptr inbounds %struct.tm, %struct.tm* %8, i32 0, i32 2, !dbg !2194
  %9 = load i32, i32* %tm_hour, align 8, !dbg !2194
  %10 = load %struct.tm*, %struct.tm** %filetime, align 8, !dbg !2195
  %tm_min = getelementptr inbounds %struct.tm, %struct.tm* %10, i32 0, i32 1, !dbg !2196
  %11 = load i32, i32* %tm_min, align 4, !dbg !2196
  %12 = load %struct.tm*, %struct.tm** %filetime, align 8, !dbg !2197
  %tm_sec = getelementptr inbounds %struct.tm, %struct.tm* %12, i32 0, i32 0, !dbg !2198
  %13 = load i32, i32* %tm_sec, align 8, !dbg !2198
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.87, i32 0, i32 0), i32 %add, i32 %add3, i32 %7, i32 %9, i32 %11, i32 %13), !dbg !2199
  br label %if.end, !dbg !2200

if.else:                                          ; preds = %entry
  %call4 = call i32* @__errno_location() #1, !dbg !2201
  %14 = load i32, i32* %call4, align 4, !dbg !2201
  %call5 = call i8* @strerror(i32 %14) #2, !dbg !2203
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([54 x i8], [54 x i8]* @.str.88, i32 0, i32 0), i8* %call5), !dbg !2205
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %15 = load i8*, i8** %fullfilename, align 8, !dbg !2206
  call void @free(i8* %15) #2, !dbg !2207
  ret void, !dbg !2208
}

; Function Attrs: nounwind
declare %struct.tm* @gmtime(i64*) #3

; Function Attrs: nounwind uwtable
define void @command_cwd(i8* %dir) #0 !dbg !156 {
entry:
  %dir.addr = alloca i8*, align 8
  store i8* %dir, i8** %dir.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dir.addr, metadata !2209, metadata !246), !dbg !2210
  %0 = load i8*, i8** %dir.addr, align 8, !dbg !2211
  %call = call i32 @bftpd_cwd_chdir(i8* %0), !dbg !2213
  %tobool = icmp ne i32 %call, 0, !dbg !2213
  br i1 %tobool, label %if.then, label %if.else, !dbg !2214

if.then:                                          ; preds = %entry
  %call1 = call i32* @__errno_location() #1, !dbg !2215
  %1 = load i32, i32* %call1, align 4, !dbg !2215
  %call2 = call i8* @strerror(i32 %1) #2, !dbg !2217
  %2 = load i8*, i8** %dir.addr, align 8, !dbg !2219
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.89, i32 0, i32 0), i8* %call2, i8* %2), !dbg !2220
  %call3 = call i32* @__errno_location() #1, !dbg !2221
  %3 = load i32, i32* %call3, align 4, !dbg !2221
  %call4 = call i8* @strerror(i32 %3) #2, !dbg !2222
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.90, i32 0, i32 0), i8* %call4), !dbg !2223
  br label %if.end, !dbg !2225

if.else:                                          ; preds = %entry
  %4 = load i8*, i8** %dir.addr, align 8, !dbg !2226
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.91, i32 0, i32 0), i8* %4), !dbg !2228
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.92, i32 0, i32 0)), !dbg !2229
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !2230
}

declare i32 @bftpd_cwd_chdir(i8*) #4

; Function Attrs: nounwind uwtable
define void @command_cdup(i8* %params) #0 !dbg !157 {
entry:
  %params.addr = alloca i8*, align 8
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !2231, metadata !246), !dbg !2232
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.93, i32 0, i32 0)), !dbg !2233
  %call = call i32 @bftpd_cwd_chdir(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.94, i32 0, i32 0)), !dbg !2234
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.92, i32 0, i32 0)), !dbg !2235
  ret void, !dbg !2236
}

; Function Attrs: nounwind uwtable
define void @command_dele(i8* %filename) #0 !dbg !158 {
entry:
  %filename.addr = alloca i8*, align 8
  %sbuf = alloca %struct.stat, align 8
  %mapped = alloca i8*, align 8
  store i8* %filename, i8** %filename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filename.addr, metadata !2237, metadata !246), !dbg !2238
  call void @llvm.dbg.declare(metadata %struct.stat* %sbuf, metadata !2239, metadata !246), !dbg !2240
  call void @llvm.dbg.declare(metadata i8** %mapped, metadata !2241, metadata !246), !dbg !2242
  %0 = load i8*, i8** %filename.addr, align 8, !dbg !2243
  %call = call i8* @bftpd_cwd_mappath(i8* %0), !dbg !2244
  store i8* %call, i8** %mapped, align 8, !dbg !2242
  %1 = load i8*, i8** @pre_write_script, align 8, !dbg !2245
  %tobool = icmp ne i8* %1, null, !dbg !2245
  br i1 %tobool, label %if.then, label %if.end, !dbg !2247

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** @pre_write_script, align 8, !dbg !2248
  %3 = load i8*, i8** %mapped, align 8, !dbg !2249
  %call1 = call i32 @run_script(i8* %2, i8* %3), !dbg !2250
  br label %if.end, !dbg !2250

if.end:                                           ; preds = %if.then, %entry
  %4 = load i8*, i8** %mapped, align 8, !dbg !2251
  %call2 = call i32 @lstat64(i8* %4, %struct.stat* %sbuf) #2, !dbg !2253
  %cmp = icmp eq i32 %call2, -1, !dbg !2254
  br i1 %cmp, label %if.then3, label %if.else, !dbg !2255

if.then3:                                         ; preds = %if.end
  %call4 = call i32* @__errno_location() #1, !dbg !2256
  %5 = load i32, i32* %call4, align 4, !dbg !2256
  %call5 = call i8* @strerror(i32 %5) #2, !dbg !2258
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.90, i32 0, i32 0), i8* %call5), !dbg !2260
  br label %if.end21, !dbg !2262

if.else:                                          ; preds = %if.end
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %sbuf, i32 0, i32 3, !dbg !2263
  %6 = load i32, i32* %st_mode, align 8, !dbg !2263
  %and = and i32 %6, 61440, !dbg !2263
  %cmp6 = icmp eq i32 %and, 16384, !dbg !2263
  br i1 %cmp6, label %if.then7, label %if.else10, !dbg !2266

if.then7:                                         ; preds = %if.else
  %call8 = call i32* @__errno_location() #1, !dbg !2267
  %7 = load i32, i32* %call8, align 4, !dbg !2267
  %call9 = call i8* @strerror(i32 %7) #2, !dbg !2269
  %8 = load i8*, i8** %filename.addr, align 8, !dbg !2271
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([59 x i8], [59 x i8]* @.str.95, i32 0, i32 0), i8* %call9, i8* %8), !dbg !2272
  %9 = load i8*, i8** %filename.addr, align 8, !dbg !2274
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.96, i32 0, i32 0), i8* %9), !dbg !2275
  br label %if.end20, !dbg !2276

if.else10:                                        ; preds = %if.else
  %10 = load i8*, i8** %mapped, align 8, !dbg !2277
  %call11 = call i32 @unlink(i8* %10) #2, !dbg !2280
  %tobool12 = icmp ne i32 %call11, 0, !dbg !2280
  br i1 %tobool12, label %if.then13, label %if.else18, !dbg !2281

if.then13:                                        ; preds = %if.else10
  %call14 = call i32* @__errno_location() #1, !dbg !2282
  %11 = load i32, i32* %call14, align 4, !dbg !2282
  %call15 = call i8* @strerror(i32 %11) #2, !dbg !2284
  %12 = load i8*, i8** %filename.addr, align 8, !dbg !2286
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.97, i32 0, i32 0), i8* %call15, i8* %12), !dbg !2287
  %call16 = call i32* @__errno_location() #1, !dbg !2289
  %13 = load i32, i32* %call16, align 4, !dbg !2289
  %call17 = call i8* @strerror(i32 %13) #2, !dbg !2290
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.90, i32 0, i32 0), i8* %call17), !dbg !2291
  br label %if.end19, !dbg !2292

if.else18:                                        ; preds = %if.else10
  %14 = load i8*, i8** %filename.addr, align 8, !dbg !2293
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.98, i32 0, i32 0), i8* %14), !dbg !2295
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.99, i32 0, i32 0)), !dbg !2296
  br label %if.end19

if.end19:                                         ; preds = %if.else18, %if.then13
  br label %if.end20

if.end20:                                         ; preds = %if.end19, %if.then7
  br label %if.end21

if.end21:                                         ; preds = %if.end20, %if.then3
  %15 = load i8*, i8** @post_write_script, align 8, !dbg !2297
  %tobool22 = icmp ne i8* %15, null, !dbg !2297
  br i1 %tobool22, label %if.then23, label %if.end25, !dbg !2299

if.then23:                                        ; preds = %if.end21
  %16 = load i8*, i8** @post_write_script, align 8, !dbg !2300
  %17 = load i8*, i8** %mapped, align 8, !dbg !2301
  %call24 = call i32 @run_script(i8* %16, i8* %17), !dbg !2302
  br label %if.end25, !dbg !2302

if.end25:                                         ; preds = %if.then23, %if.end21
  %18 = load i8*, i8** %mapped, align 8, !dbg !2303
  call void @free(i8* %18) #2, !dbg !2304
  ret void, !dbg !2305
}

; Function Attrs: nounwind
declare i32 @lstat64(i8*, %struct.stat*) #3

; Function Attrs: nounwind
declare i32 @unlink(i8*) #3

; Function Attrs: nounwind uwtable
define void @command_mkd(i8* %dirname) #0 !dbg !159 {
entry:
  %dirname.addr = alloca i8*, align 8
  %mapped = alloca i8*, align 8
  store i8* %dirname, i8** %dirname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dirname.addr, metadata !2306, metadata !246), !dbg !2307
  call void @llvm.dbg.declare(metadata i8** %mapped, metadata !2308, metadata !246), !dbg !2309
  %0 = load i8*, i8** %dirname.addr, align 8, !dbg !2310
  %call = call i8* @bftpd_cwd_mappath(i8* %0), !dbg !2311
  store i8* %call, i8** %mapped, align 8, !dbg !2309
  %1 = load i8*, i8** @pre_write_script, align 8, !dbg !2312
  %tobool = icmp ne i8* %1, null, !dbg !2312
  br i1 %tobool, label %if.then, label %if.end, !dbg !2314

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** @pre_write_script, align 8, !dbg !2315
  %3 = load i8*, i8** %mapped, align 8, !dbg !2316
  %call1 = call i32 @run_script(i8* %2, i8* %3), !dbg !2317
  br label %if.end, !dbg !2317

if.end:                                           ; preds = %if.then, %entry
  %4 = load i8*, i8** %mapped, align 8, !dbg !2318
  %call2 = call i32 @mkdir(i8* %4, i32 511) #2, !dbg !2320
  %tobool3 = icmp ne i32 %call2, 0, !dbg !2320
  br i1 %tobool3, label %if.then4, label %if.else, !dbg !2321

if.then4:                                         ; preds = %if.end
  %call5 = call i32* @__errno_location() #1, !dbg !2322
  %5 = load i32, i32* %call5, align 4, !dbg !2322
  %call6 = call i8* @strerror(i32 %5) #2, !dbg !2324
  %6 = load i8*, i8** %dirname.addr, align 8, !dbg !2326
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([52 x i8], [52 x i8]* @.str.100, i32 0, i32 0), i8* %call6, i8* %6), !dbg !2327
  %call7 = call i32* @__errno_location() #1, !dbg !2328
  %7 = load i32, i32* %call7, align 4, !dbg !2328
  %call8 = call i8* @strerror(i32 %7) #2, !dbg !2329
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.90, i32 0, i32 0), i8* %call8), !dbg !2330
  br label %if.end9, !dbg !2332

if.else:                                          ; preds = %if.end
  %8 = load i8*, i8** %dirname.addr, align 8, !dbg !2333
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.101, i32 0, i32 0), i8* %8), !dbg !2335
  %9 = load i8*, i8** %dirname.addr, align 8, !dbg !2336
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.102, i32 0, i32 0), i8* %9), !dbg !2337
  br label %if.end9

if.end9:                                          ; preds = %if.else, %if.then4
  %10 = load i8*, i8** @post_write_script, align 8, !dbg !2338
  %tobool10 = icmp ne i8* %10, null, !dbg !2338
  br i1 %tobool10, label %if.then11, label %if.end13, !dbg !2340

if.then11:                                        ; preds = %if.end9
  %11 = load i8*, i8** @post_write_script, align 8, !dbg !2341
  %12 = load i8*, i8** %mapped, align 8, !dbg !2342
  %call12 = call i32 @run_script(i8* %11, i8* %12), !dbg !2343
  br label %if.end13, !dbg !2343

if.end13:                                         ; preds = %if.then11, %if.end9
  %13 = load i8*, i8** %mapped, align 8, !dbg !2344
  call void @free(i8* %13) #2, !dbg !2345
  ret void, !dbg !2346
}

; Function Attrs: nounwind
declare i32 @mkdir(i8*, i32) #3

; Function Attrs: nounwind uwtable
define void @command_rmd(i8* %dirname) #0 !dbg !160 {
entry:
  %dirname.addr = alloca i8*, align 8
  %mapped = alloca i8*, align 8
  store i8* %dirname, i8** %dirname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dirname.addr, metadata !2347, metadata !246), !dbg !2348
  call void @llvm.dbg.declare(metadata i8** %mapped, metadata !2349, metadata !246), !dbg !2350
  %0 = load i8*, i8** %dirname.addr, align 8, !dbg !2351
  %call = call i8* @bftpd_cwd_mappath(i8* %0), !dbg !2352
  store i8* %call, i8** %mapped, align 8, !dbg !2350
  %1 = load i8*, i8** @pre_write_script, align 8, !dbg !2353
  %tobool = icmp ne i8* %1, null, !dbg !2353
  br i1 %tobool, label %if.then, label %if.end, !dbg !2355

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** @pre_write_script, align 8, !dbg !2356
  %3 = load i8*, i8** %mapped, align 8, !dbg !2357
  %call1 = call i32 @run_script(i8* %2, i8* %3), !dbg !2358
  br label %if.end, !dbg !2358

if.end:                                           ; preds = %if.then, %entry
  %4 = load i8*, i8** %mapped, align 8, !dbg !2359
  %call2 = call i32 @rmdir(i8* %4) #2, !dbg !2361
  %tobool3 = icmp ne i32 %call2, 0, !dbg !2361
  br i1 %tobool3, label %if.then4, label %if.else14, !dbg !2362

if.then4:                                         ; preds = %if.end
  %call5 = call i32* @__errno_location() #1, !dbg !2363
  %5 = load i32, i32* %call5, align 4, !dbg !2363
  %cmp = icmp eq i32 %5, 39, !dbg !2366
  br i1 %cmp, label %if.then6, label %if.else, !dbg !2367

if.then6:                                         ; preds = %if.then4
  %call7 = call i32* @__errno_location() #1, !dbg !2368
  %6 = load i32, i32* %call7, align 4, !dbg !2368
  %call8 = call i8* @strerror(i32 %6) #2, !dbg !2370
  %7 = load i8*, i8** %dirname.addr, align 8, !dbg !2372
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([63 x i8], [63 x i8]* @.str.103, i32 0, i32 0), i8* %call8, i8* %7), !dbg !2373
  %8 = load i8*, i8** %dirname.addr, align 8, !dbg !2375
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.104, i32 0, i32 0), i8* %8), !dbg !2376
  br label %if.end13, !dbg !2377

if.else:                                          ; preds = %if.then4
  %call9 = call i32* @__errno_location() #1, !dbg !2378
  %9 = load i32, i32* %call9, align 4, !dbg !2378
  %call10 = call i8* @strerror(i32 %9) #2, !dbg !2380
  %10 = load i8*, i8** %dirname.addr, align 8, !dbg !2382
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([52 x i8], [52 x i8]* @.str.105, i32 0, i32 0), i8* %call10, i8* %10), !dbg !2383
  %call11 = call i32* @__errno_location() #1, !dbg !2385
  %11 = load i32, i32* %call11, align 4, !dbg !2385
  %call12 = call i8* @strerror(i32 %11) #2, !dbg !2386
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.90, i32 0, i32 0), i8* %call12), !dbg !2387
  br label %if.end13

if.end13:                                         ; preds = %if.else, %if.then6
  br label %if.end15, !dbg !2388

if.else14:                                        ; preds = %if.end
  %12 = load i8*, i8** %dirname.addr, align 8, !dbg !2389
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.106, i32 0, i32 0), i8* %12), !dbg !2391
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.92, i32 0, i32 0)), !dbg !2392
  br label %if.end15

if.end15:                                         ; preds = %if.else14, %if.end13
  %13 = load i8*, i8** @post_write_script, align 8, !dbg !2393
  %tobool16 = icmp ne i8* %13, null, !dbg !2393
  br i1 %tobool16, label %if.then17, label %if.end19, !dbg !2395

if.then17:                                        ; preds = %if.end15
  %14 = load i8*, i8** @post_write_script, align 8, !dbg !2396
  %15 = load i8*, i8** %mapped, align 8, !dbg !2397
  %call18 = call i32 @run_script(i8* %14, i8* %15), !dbg !2398
  br label %if.end19, !dbg !2398

if.end19:                                         ; preds = %if.then17, %if.end15
  %16 = load i8*, i8** %mapped, align 8, !dbg !2399
  call void @free(i8* %16) #2, !dbg !2400
  ret void, !dbg !2401
}

; Function Attrs: nounwind
declare i32 @rmdir(i8*) #3

; Function Attrs: nounwind uwtable
define void @command_rnfr(i8* %oldname) #0 !dbg !162 {
entry:
  %oldname.addr = alloca i8*, align 8
  %file = alloca %struct._IO_FILE*, align 8
  %mapped = alloca i8*, align 8
  store i8* %oldname, i8** %oldname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %oldname.addr, metadata !2402, metadata !246), !dbg !2403
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %file, metadata !2404, metadata !246), !dbg !2405
  call void @llvm.dbg.declare(metadata i8** %mapped, metadata !2406, metadata !246), !dbg !2407
  %0 = load i8*, i8** %oldname.addr, align 8, !dbg !2408
  %call = call i8* @bftpd_cwd_mappath(i8* %0), !dbg !2409
  store i8* %call, i8** %mapped, align 8, !dbg !2407
  %1 = load i8*, i8** %mapped, align 8, !dbg !2410
  %call1 = call %struct._IO_FILE* @fopen64(i8* %1, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.107, i32 0, i32 0)), !dbg !2412
  store %struct._IO_FILE* %call1, %struct._IO_FILE** %file, align 8, !dbg !2413
  %tobool = icmp ne %struct._IO_FILE* %call1, null, !dbg !2413
  br i1 %tobool, label %if.then, label %if.else, !dbg !2414

if.then:                                          ; preds = %entry
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** %file, align 8, !dbg !2415
  %call2 = call i32 @fclose(%struct._IO_FILE* %2), !dbg !2417
  %3 = load i8*, i8** @philename, align 8, !dbg !2418
  %tobool3 = icmp ne i8* %3, null, !dbg !2418
  br i1 %tobool3, label %if.then4, label %if.end, !dbg !2420

if.then4:                                         ; preds = %if.then
  %4 = load i8*, i8** @philename, align 8, !dbg !2421
  call void @free(i8* %4) #2, !dbg !2422
  br label %if.end, !dbg !2422

if.end:                                           ; preds = %if.then4, %if.then
  %5 = load i8*, i8** %mapped, align 8, !dbg !2423
  store i8* %5, i8** @philename, align 8, !dbg !2424
  store i32 3, i32* @state, align 4, !dbg !2425
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.108, i32 0, i32 0)), !dbg !2426
  br label %if.end7, !dbg !2427

if.else:                                          ; preds = %entry
  %6 = load i8*, i8** %mapped, align 8, !dbg !2428
  call void @free(i8* %6) #2, !dbg !2430
  %call5 = call i32* @__errno_location() #1, !dbg !2431
  %7 = load i32, i32* %call5, align 4, !dbg !2431
  %call6 = call i8* @strerror(i32 %7) #2, !dbg !2432
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.90, i32 0, i32 0), i8* %call6), !dbg !2434
  br label %if.end7

if.end7:                                          ; preds = %if.else, %if.end
  ret void, !dbg !2436
}

declare %struct._IO_FILE* @fopen64(i8*, i8*) #4

; Function Attrs: nounwind uwtable
define void @command_rnto(i8* %newname) #0 !dbg !163 {
entry:
  %newname.addr = alloca i8*, align 8
  %mapped = alloca i8*, align 8
  store i8* %newname, i8** %newname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %newname.addr, metadata !2437, metadata !246), !dbg !2438
  call void @llvm.dbg.declare(metadata i8** %mapped, metadata !2439, metadata !246), !dbg !2440
  %0 = load i8*, i8** %newname.addr, align 8, !dbg !2441
  %call = call i8* @bftpd_cwd_mappath(i8* %0), !dbg !2442
  store i8* %call, i8** %mapped, align 8, !dbg !2440
  %1 = load i8*, i8** @pre_write_script, align 8, !dbg !2443
  %tobool = icmp ne i8* %1, null, !dbg !2443
  br i1 %tobool, label %if.then, label %if.end, !dbg !2445

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** @pre_write_script, align 8, !dbg !2446
  %3 = load i8*, i8** %mapped, align 8, !dbg !2447
  %call1 = call i32 @run_script(i8* %2, i8* %3), !dbg !2448
  br label %if.end, !dbg !2448

if.end:                                           ; preds = %if.then, %entry
  %4 = load i8*, i8** @philename, align 8, !dbg !2449
  %5 = load i8*, i8** %mapped, align 8, !dbg !2451
  %call2 = call i32 @rename(i8* %4, i8* %5) #2, !dbg !2452
  %tobool3 = icmp ne i32 %call2, 0, !dbg !2452
  br i1 %tobool3, label %if.then4, label %if.else, !dbg !2453

if.then4:                                         ; preds = %if.end
  %call5 = call i32* @__errno_location() #1, !dbg !2454
  %6 = load i32, i32* %call5, align 4, !dbg !2454
  %call6 = call i8* @strerror(i32 %6) #2, !dbg !2456
  %7 = load i8*, i8** @philename, align 8, !dbg !2458
  %8 = load i8*, i8** %newname.addr, align 8, !dbg !2459
  %call7 = call i8* @bftpd_cwd_mappath(i8* %8), !dbg !2460
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.109, i32 0, i32 0), i8* %call6, i8* %7, i8* %call7), !dbg !2462
  %call8 = call i32* @__errno_location() #1, !dbg !2463
  %9 = load i32, i32* %call8, align 4, !dbg !2463
  %call9 = call i8* @strerror(i32 %9) #2, !dbg !2464
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.90, i32 0, i32 0), i8* %call9), !dbg !2465
  br label %if.end11, !dbg !2466

if.else:                                          ; preds = %if.end
  %10 = load i8*, i8** @philename, align 8, !dbg !2467
  %11 = load i8*, i8** %newname.addr, align 8, !dbg !2469
  %call10 = call i8* @bftpd_cwd_mappath(i8* %11), !dbg !2470
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.110, i32 0, i32 0), i8* %10, i8* %call10), !dbg !2471
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.92, i32 0, i32 0)), !dbg !2473
  store i32 2, i32* @state, align 4, !dbg !2474
  br label %if.end11

if.end11:                                         ; preds = %if.else, %if.then4
  %12 = load i8*, i8** @post_write_script, align 8, !dbg !2475
  %tobool12 = icmp ne i8* %12, null, !dbg !2475
  br i1 %tobool12, label %if.then13, label %if.end15, !dbg !2477

if.then13:                                        ; preds = %if.end11
  %13 = load i8*, i8** @post_write_script, align 8, !dbg !2478
  %14 = load i8*, i8** %mapped, align 8, !dbg !2479
  %call14 = call i32 @run_script(i8* %13, i8* %14), !dbg !2480
  br label %if.end15, !dbg !2480

if.end15:                                         ; preds = %if.then13, %if.end11
  %15 = load i8*, i8** @philename, align 8, !dbg !2481
  call void @free(i8* %15) #2, !dbg !2482
  %16 = load i8*, i8** %mapped, align 8, !dbg !2483
  call void @free(i8* %16) #2, !dbg !2484
  store i8* null, i8** @philename, align 8, !dbg !2485
  ret void, !dbg !2486
}

; Function Attrs: nounwind
declare i32 @rename(i8*, i8*) #3

; Function Attrs: nounwind uwtable
define void @command_rest(i8* %params) #0 !dbg !164 {
entry:
  %params.addr = alloca i8*, align 8
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !2487, metadata !246), !dbg !2488
  %0 = load i8*, i8** %params.addr, align 8, !dbg !2489
  %call = call i64 @strtoul(i8* %0, i8** null, i32 10) #2, !dbg !2490
  store i64 %call, i64* @offset, align 8, !dbg !2491
  %1 = load i64, i64* @offset, align 8, !dbg !2492
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.111, i32 0, i32 0), i64 %1), !dbg !2493
  ret void, !dbg !2494
}

; Function Attrs: nounwind uwtable
define void @command_size(i8* %filename) #0 !dbg !165 {
entry:
  %filename.addr = alloca i8*, align 8
  %statbuf = alloca %struct.stat, align 8
  %mapped = alloca i8*, align 8
  store i8* %filename, i8** %filename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filename.addr, metadata !2495, metadata !246), !dbg !2496
  call void @llvm.dbg.declare(metadata %struct.stat* %statbuf, metadata !2497, metadata !246), !dbg !2498
  call void @llvm.dbg.declare(metadata i8** %mapped, metadata !2499, metadata !246), !dbg !2500
  %0 = load i8*, i8** %filename.addr, align 8, !dbg !2501
  %call = call i8* @bftpd_cwd_mappath(i8* %0), !dbg !2502
  store i8* %call, i8** %mapped, align 8, !dbg !2500
  %1 = load i8*, i8** %mapped, align 8, !dbg !2503
  %call1 = call i32 @stat64(i8* %1, %struct.stat* %statbuf) #2, !dbg !2505
  %tobool = icmp ne i32 %call1, 0, !dbg !2505
  br i1 %tobool, label %if.else, label %if.then, !dbg !2506

if.then:                                          ; preds = %entry
  %st_size = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 8, !dbg !2507
  %2 = load i64, i64* %st_size, align 8, !dbg !2507
  %conv = trunc i64 %2 to i32, !dbg !2509
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.112, i32 0, i32 0), i32 %conv), !dbg !2510
  br label %if.end, !dbg !2511

if.else:                                          ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !2512
  %3 = load i32, i32* %call2, align 4, !dbg !2512
  %call3 = call i8* @strerror(i32 %3) #2, !dbg !2514
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.113, i32 0, i32 0), i8* %call3), !dbg !2516
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %4 = load i8*, i8** %mapped, align 8, !dbg !2518
  call void @free(i8* %4) #2, !dbg !2519
  ret void, !dbg !2520
}

; Function Attrs: nounwind uwtable
define void @command_quit(i8* %params) #0 !dbg !166 {
entry:
  %params.addr = alloca i8*, align 8
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !2521, metadata !246), !dbg !2522
  %call = call i8* @config_getoption(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.115, i32 0, i32 0)), !dbg !2523
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.114, i32 0, i32 0), i8* %call), !dbg !2524
  call void (...) @bftpdutmp_end(), !dbg !2526
  call void @exit(i32 0) #10, !dbg !2527
  unreachable, !dbg !2527

return:                                           ; No predecessors!
  ret void, !dbg !2528
}

; Function Attrs: nounwind uwtable
define void @command_stat(i8* %filename) #0 !dbg !167 {
entry:
  %filename.addr = alloca i8*, align 8
  %mapped = alloca i8*, align 8
  store i8* %filename, i8** %filename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filename.addr, metadata !2529, metadata !246), !dbg !2530
  call void @llvm.dbg.declare(metadata i8** %mapped, metadata !2531, metadata !246), !dbg !2532
  %0 = load i8*, i8** %filename.addr, align 8, !dbg !2533
  %call = call i8* @bftpd_cwd_mappath(i8* %0), !dbg !2534
  store i8* %call, i8** %mapped, align 8, !dbg !2532
  %1 = load i8*, i8** %filename.addr, align 8, !dbg !2535
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.116, i32 0, i32 0), i8* %1), !dbg !2536
  %2 = load i8*, i8** %mapped, align 8, !dbg !2537
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !2538
  call void @bftpd_stat(i8* %2, %struct._IO_FILE* %3), !dbg !2539
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.117, i32 0, i32 0)), !dbg !2540
  %4 = load i8*, i8** %mapped, align 8, !dbg !2541
  call void @free(i8* %4) #2, !dbg !2542
  ret void, !dbg !2543
}

declare void @bftpd_stat(i8*, %struct._IO_FILE*) #4

; Function Attrs: nounwind uwtable
define void @command_chmod(i8* %params) #0 !dbg !168 {
entry:
  %params.addr = alloca i8*, align 8
  %permissions = alloca i32, align 4
  %mapped = alloca i8*, align 8
  %my_string = alloca i8*, align 8
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !2544, metadata !246), !dbg !2545
  call void @llvm.dbg.declare(metadata i32* %permissions, metadata !2546, metadata !246), !dbg !2547
  call void @llvm.dbg.declare(metadata i8** %mapped, metadata !2548, metadata !246), !dbg !2549
  call void @llvm.dbg.declare(metadata i8** %my_string, metadata !2550, metadata !246), !dbg !2551
  %0 = load i8*, i8** %params.addr, align 8, !dbg !2552
  %call = call i8* @strchr(i8* %0, i32 32) #9, !dbg !2554
  %tobool = icmp ne i8* %call, null, !dbg !2554
  br i1 %tobool, label %if.end, label %if.then, !dbg !2555

if.then:                                          ; preds = %entry
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.118, i32 0, i32 0)), !dbg !2556
  br label %return, !dbg !2558

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %params.addr, align 8, !dbg !2559
  %call1 = call i8* @strchr(i8* %1, i32 32) #9, !dbg !2560
  %add.ptr = getelementptr inbounds i8, i8* %call1, i64 1, !dbg !2561
  %call2 = call noalias i8* @strdup(i8* %add.ptr) #2, !dbg !2562
  store i8* %call2, i8** %my_string, align 8, !dbg !2564
  %2 = load i8*, i8** %my_string, align 8, !dbg !2565
  %tobool3 = icmp ne i8* %2, null, !dbg !2565
  br i1 %tobool3, label %if.end5, label %if.then4, !dbg !2567

if.then4:                                         ; preds = %if.end
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([53 x i8], [53 x i8]* @.str.119, i32 0, i32 0)), !dbg !2568
  br label %return, !dbg !2570

if.end5:                                          ; preds = %if.end
  %3 = load i8*, i8** %my_string, align 8, !dbg !2571
  %call6 = call i8* @bftpd_cwd_mappath(i8* %3), !dbg !2572
  store i8* %call6, i8** %mapped, align 8, !dbg !2573
  %4 = load i8*, i8** %my_string, align 8, !dbg !2574
  call void @free(i8* %4) #2, !dbg !2575
  %5 = load i8*, i8** @pre_write_script, align 8, !dbg !2576
  %tobool7 = icmp ne i8* %5, null, !dbg !2576
  br i1 %tobool7, label %if.then8, label %if.end10, !dbg !2578

if.then8:                                         ; preds = %if.end5
  %6 = load i8*, i8** @pre_write_script, align 8, !dbg !2579
  %7 = load i8*, i8** %mapped, align 8, !dbg !2580
  %call9 = call i32 @run_script(i8* %6, i8* %7), !dbg !2581
  br label %if.end10, !dbg !2581

if.end10:                                         ; preds = %if.then8, %if.end5
  %8 = load i8*, i8** %params.addr, align 8, !dbg !2582
  %call11 = call i8* @strchr(i8* %8, i32 32) #9, !dbg !2583
  store i8 0, i8* %call11, align 1, !dbg !2584
  %9 = load i8*, i8** %params.addr, align 8, !dbg !2585
  %call12 = call i32 (i8*, i8*, ...) @__isoc99_sscanf(i8* %9, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.120, i32 0, i32 0), i32* %permissions) #2, !dbg !2586
  %10 = load i8*, i8** %mapped, align 8, !dbg !2587
  %11 = load i32, i32* %permissions, align 4, !dbg !2589
  %call13 = call i32 @chmod(i8* %10, i32 %11) #2, !dbg !2590
  %tobool14 = icmp ne i32 %call13, 0, !dbg !2590
  br i1 %tobool14, label %if.then15, label %if.else, !dbg !2591

if.then15:                                        ; preds = %if.end10
  %call16 = call i32* @__errno_location() #1, !dbg !2592
  %12 = load i32, i32* %call16, align 4, !dbg !2592
  %call17 = call i8* @strerror(i32 %12) #2, !dbg !2593
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.121, i32 0, i32 0), i8* %call17), !dbg !2595
  br label %if.end18, !dbg !2597

if.else:                                          ; preds = %if.end10
  %13 = load i8*, i8** %mapped, align 8, !dbg !2598
  %14 = load i32, i32* %permissions, align 4, !dbg !2600
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.122, i32 0, i32 0), i8* %13, i32 %14), !dbg !2601
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.123, i32 0, i32 0)), !dbg !2602
  br label %if.end18

if.end18:                                         ; preds = %if.else, %if.then15
  %15 = load i8*, i8** @post_write_script, align 8, !dbg !2603
  %tobool19 = icmp ne i8* %15, null, !dbg !2603
  br i1 %tobool19, label %if.then20, label %if.end22, !dbg !2605

if.then20:                                        ; preds = %if.end18
  %16 = load i8*, i8** @post_write_script, align 8, !dbg !2606
  %17 = load i8*, i8** %mapped, align 8, !dbg !2607
  %call21 = call i32 @run_script(i8* %16, i8* %17), !dbg !2608
  br label %if.end22, !dbg !2608

if.end22:                                         ; preds = %if.then20, %if.end18
  %18 = load i8*, i8** %mapped, align 8, !dbg !2609
  call void @free(i8* %18) #2, !dbg !2610
  br label %return, !dbg !2611

return:                                           ; preds = %if.end22, %if.then4, %if.then
  ret void, !dbg !2612
}

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #7

; Function Attrs: nounwind
declare i32 @chmod(i8*, i32) #3

; Function Attrs: nounwind uwtable
define void @command_chown(i8* %params) #0 !dbg !169 {
entry:
  %params.addr = alloca i8*, align 8
  %foo = alloca [256 x i8], align 16
  %owner = alloca [256 x i8], align 16
  %group = alloca [256 x i8], align 16
  %filename = alloca [256 x i8], align 16
  %mapped = alloca i8*, align 8
  %uid = alloca i32, align 4
  %gid = alloca i32, align 4
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !2613, metadata !246), !dbg !2614
  call void @llvm.dbg.declare(metadata [256 x i8]* %foo, metadata !2615, metadata !246), !dbg !2616
  call void @llvm.dbg.declare(metadata [256 x i8]* %owner, metadata !2617, metadata !246), !dbg !2618
  call void @llvm.dbg.declare(metadata [256 x i8]* %group, metadata !2619, metadata !246), !dbg !2620
  call void @llvm.dbg.declare(metadata [256 x i8]* %filename, metadata !2621, metadata !246), !dbg !2622
  call void @llvm.dbg.declare(metadata i8** %mapped, metadata !2623, metadata !246), !dbg !2624
  call void @llvm.dbg.declare(metadata i32* %uid, metadata !2625, metadata !246), !dbg !2626
  call void @llvm.dbg.declare(metadata i32* %gid, metadata !2627, metadata !246), !dbg !2628
  %0 = load i8*, i8** %params.addr, align 8, !dbg !2629
  %call = call i8* @strchr(i8* %0, i32 32) #9, !dbg !2631
  %tobool = icmp ne i8* %call, null, !dbg !2631
  br i1 %tobool, label %if.end, label %if.then, !dbg !2632

if.then:                                          ; preds = %entry
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.124, i32 0, i32 0)), !dbg !2633
  br label %return, !dbg !2635

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %params.addr, align 8, !dbg !2636
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !2637
  %arraydecay1 = getelementptr inbounds [256 x i8], [256 x i8]* %filename, i32 0, i32 0, !dbg !2638
  %call2 = call i32 (i8*, i8*, ...) @__isoc99_sscanf(i8* %1, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.125, i32 0, i32 0), i8* %arraydecay, i8* %arraydecay1) #2, !dbg !2639
  %arraydecay3 = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !2640
  %call4 = call i8* @strchr(i8* %arraydecay3, i32 46) #9, !dbg !2642
  %tobool5 = icmp ne i8* %call4, null, !dbg !2642
  br i1 %tobool5, label %if.then6, label %if.else, !dbg !2643

if.then6:                                         ; preds = %if.end
  %arraydecay7 = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !2644
  %arraydecay8 = getelementptr inbounds [256 x i8], [256 x i8]* %owner, i32 0, i32 0, !dbg !2645
  %arraydecay9 = getelementptr inbounds [256 x i8], [256 x i8]* %group, i32 0, i32 0, !dbg !2646
  %call10 = call i32 (i8*, i8*, ...) @__isoc99_sscanf(i8* %arraydecay7, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.126, i32 0, i32 0), i8* %arraydecay8, i8* %arraydecay9) #2, !dbg !2647
  br label %if.end14, !dbg !2647

if.else:                                          ; preds = %if.end
  %arraydecay11 = getelementptr inbounds [256 x i8], [256 x i8]* %owner, i32 0, i32 0, !dbg !2648
  %arraydecay12 = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !2650
  %call13 = call i8* @strcpy(i8* %arraydecay11, i8* %arraydecay12) #2, !dbg !2651
  %arrayidx = getelementptr inbounds [256 x i8], [256 x i8]* %group, i64 0, i64 0, !dbg !2652
  store i8 0, i8* %arrayidx, align 16, !dbg !2653
  br label %if.end14

if.end14:                                         ; preds = %if.else, %if.then6
  %arraydecay15 = getelementptr inbounds [256 x i8], [256 x i8]* %owner, i32 0, i32 0, !dbg !2654
  %call16 = call i32 (i8*, i8*, ...) @__isoc99_sscanf(i8* %arraydecay15, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.42, i32 0, i32 0), i32* %uid) #2, !dbg !2656
  %tobool17 = icmp ne i32 %call16, 0, !dbg !2656
  br i1 %tobool17, label %if.end24, label %if.then18, !dbg !2657

if.then18:                                        ; preds = %if.end14
  %arraydecay19 = getelementptr inbounds [256 x i8], [256 x i8]* %owner, i32 0, i32 0, !dbg !2658
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** @passwdfile, align 8, !dbg !2660
  %call20 = call i32 @mygetpwnam(i8* %arraydecay19, %struct._IO_FILE* %2), !dbg !2661
  store i32 %call20, i32* %uid, align 4, !dbg !2662
  %cmp = icmp slt i32 %call20, 0, !dbg !2663
  br i1 %cmp, label %if.then21, label %if.end23, !dbg !2664

if.then21:                                        ; preds = %if.then18
  %arraydecay22 = getelementptr inbounds [256 x i8], [256 x i8]* %owner, i32 0, i32 0, !dbg !2665
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.127, i32 0, i32 0), i8* %arraydecay22), !dbg !2667
  br label %return, !dbg !2668

if.end23:                                         ; preds = %if.then18
  br label %if.end24, !dbg !2669

if.end24:                                         ; preds = %if.end23, %if.end14
  %arraydecay25 = getelementptr inbounds [256 x i8], [256 x i8]* %group, i32 0, i32 0, !dbg !2671
  %call26 = call i32 (i8*, i8*, ...) @__isoc99_sscanf(i8* %arraydecay25, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.42, i32 0, i32 0), i32* %gid) #2, !dbg !2673
  %tobool27 = icmp ne i32 %call26, 0, !dbg !2673
  br i1 %tobool27, label %if.end35, label %if.then28, !dbg !2674

if.then28:                                        ; preds = %if.end24
  %arraydecay29 = getelementptr inbounds [256 x i8], [256 x i8]* %group, i32 0, i32 0, !dbg !2675
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** @groupfile, align 8, !dbg !2677
  %call30 = call i32 @mygetpwnam(i8* %arraydecay29, %struct._IO_FILE* %3), !dbg !2678
  store i32 %call30, i32* %gid, align 4, !dbg !2679
  %cmp31 = icmp slt i32 %call30, 0, !dbg !2680
  br i1 %cmp31, label %if.then32, label %if.end34, !dbg !2681

if.then32:                                        ; preds = %if.then28
  %arraydecay33 = getelementptr inbounds [256 x i8], [256 x i8]* %group, i32 0, i32 0, !dbg !2682
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.128, i32 0, i32 0), i8* %arraydecay33), !dbg !2684
  br label %return, !dbg !2685

if.end34:                                         ; preds = %if.then28
  br label %if.end35, !dbg !2686

if.end35:                                         ; preds = %if.end34, %if.end24
  %arraydecay36 = getelementptr inbounds [256 x i8], [256 x i8]* %filename, i32 0, i32 0, !dbg !2688
  %call37 = call i8* @bftpd_cwd_mappath(i8* %arraydecay36), !dbg !2689
  store i8* %call37, i8** %mapped, align 8, !dbg !2690
  %4 = load i8*, i8** @pre_write_script, align 8, !dbg !2691
  %tobool38 = icmp ne i8* %4, null, !dbg !2691
  br i1 %tobool38, label %if.then39, label %if.end41, !dbg !2693

if.then39:                                        ; preds = %if.end35
  %5 = load i8*, i8** @pre_write_script, align 8, !dbg !2694
  %6 = load i8*, i8** %mapped, align 8, !dbg !2695
  %call40 = call i32 @run_script(i8* %5, i8* %6), !dbg !2696
  br label %if.end41, !dbg !2696

if.end41:                                         ; preds = %if.then39, %if.end35
  %7 = load i8*, i8** %mapped, align 8, !dbg !2697
  %8 = load i32, i32* %uid, align 4, !dbg !2699
  %9 = load i32, i32* %gid, align 4, !dbg !2700
  %call42 = call i32 @chown(i8* %7, i32 %8, i32 %9) #2, !dbg !2701
  %tobool43 = icmp ne i32 %call42, 0, !dbg !2701
  br i1 %tobool43, label %if.then44, label %if.else47, !dbg !2702

if.then44:                                        ; preds = %if.end41
  %call45 = call i32* @__errno_location() #1, !dbg !2703
  %10 = load i32, i32* %call45, align 4, !dbg !2703
  %call46 = call i8* @strerror(i32 %10) #2, !dbg !2704
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.113, i32 0, i32 0), i8* %call46), !dbg !2706
  br label %if.end49, !dbg !2708

if.else47:                                        ; preds = %if.end41
  %arraydecay48 = getelementptr inbounds [256 x i8], [256 x i8]* %filename, i32 0, i32 0, !dbg !2709
  %11 = load i32, i32* %uid, align 4, !dbg !2711
  %12 = load i32, i32* %gid, align 4, !dbg !2712
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.129, i32 0, i32 0), i8* %arraydecay48, i32 %11, i32 %12), !dbg !2713
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.130, i32 0, i32 0)), !dbg !2714
  br label %if.end49

if.end49:                                         ; preds = %if.else47, %if.then44
  %13 = load i8*, i8** @post_write_script, align 8, !dbg !2715
  %tobool50 = icmp ne i8* %13, null, !dbg !2715
  br i1 %tobool50, label %if.then51, label %if.end53, !dbg !2717

if.then51:                                        ; preds = %if.end49
  %14 = load i8*, i8** @post_write_script, align 8, !dbg !2718
  %15 = load i8*, i8** %mapped, align 8, !dbg !2719
  %call52 = call i32 @run_script(i8* %14, i8* %15), !dbg !2720
  br label %if.end53, !dbg !2720

if.end53:                                         ; preds = %if.then51, %if.end49
  %16 = load i8*, i8** %mapped, align 8, !dbg !2721
  call void @free(i8* %16) #2, !dbg !2722
  br label %return, !dbg !2723

return:                                           ; preds = %if.end53, %if.then32, %if.then21, %if.then
  ret void, !dbg !2724
}

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #3

declare i32 @mygetpwnam(i8*, %struct._IO_FILE*) #4

; Function Attrs: nounwind
declare i32 @chown(i8*, i32, i32) #3

; Function Attrs: nounwind uwtable
define void @command_md5(i8* %philename) #0 !dbg !170 {
entry:
  %philename.addr = alloca i8*, align 8
  %myphile = alloca %struct._IO_FILE*, align 8
  %my_md5 = alloca %struct.md5_t, align 4
  %buffer = alloca [1024 x i8], align 16
  %bytes_read = alloca i32, align 4
  %md5_result = alloca [16 x i8], align 16
  %output_string = alloca [64 x i8], align 16
  store i8* %philename, i8** %philename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %philename.addr, metadata !2726, metadata !246), !dbg !2727
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %myphile, metadata !2728, metadata !246), !dbg !2729
  call void @llvm.dbg.declare(metadata %struct.md5_t* %my_md5, metadata !2730, metadata !246), !dbg !2749
  call void @llvm.dbg.declare(metadata [1024 x i8]* %buffer, metadata !2750, metadata !246), !dbg !2754
  call void @llvm.dbg.declare(metadata i32* %bytes_read, metadata !2755, metadata !246), !dbg !2756
  store i32 0, i32* %bytes_read, align 4, !dbg !2756
  call void @llvm.dbg.declare(metadata [16 x i8]* %md5_result, metadata !2757, metadata !246), !dbg !2759
  call void @llvm.dbg.declare(metadata [64 x i8]* %output_string, metadata !2760, metadata !246), !dbg !2764
  %0 = load i8*, i8** %philename.addr, align 8, !dbg !2765
  %tobool = icmp ne i8* %0, null, !dbg !2765
  br i1 %tobool, label %if.end, label %if.then, !dbg !2767

if.then:                                          ; preds = %entry
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.131, i32 0, i32 0)), !dbg !2768
  br label %return, !dbg !2770

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %philename.addr, align 8, !dbg !2771
  %incdec.ptr = getelementptr inbounds i8, i8* %1, i32 1, !dbg !2771
  store i8* %incdec.ptr, i8** %philename.addr, align 8, !dbg !2771
  %2 = load i8*, i8** %philename.addr, align 8, !dbg !2772
  %call = call %struct._IO_FILE* @fopen64(i8* %2, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.107, i32 0, i32 0)), !dbg !2773
  store %struct._IO_FILE* %call, %struct._IO_FILE** %myphile, align 8, !dbg !2774
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** %myphile, align 8, !dbg !2775
  %tobool1 = icmp ne %struct._IO_FILE* %3, null, !dbg !2775
  br i1 %tobool1, label %if.end3, label %if.then2, !dbg !2777

if.then2:                                         ; preds = %if.end
  %4 = load i8*, i8** %philename.addr, align 8, !dbg !2778
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.132, i32 0, i32 0), i8* %4), !dbg !2780
  br label %return, !dbg !2781

if.end3:                                          ; preds = %if.end
  call void @md5_init(%struct.md5_t* %my_md5), !dbg !2782
  %arraydecay = getelementptr inbounds [1024 x i8], [1024 x i8]* %buffer, i32 0, i32 0, !dbg !2783
  %5 = load %struct._IO_FILE*, %struct._IO_FILE** %myphile, align 8, !dbg !2784
  %call4 = call i64 @fread(i8* %arraydecay, i64 1, i64 1024, %struct._IO_FILE* %5), !dbg !2785
  %conv = trunc i64 %call4 to i32, !dbg !2785
  store i32 %conv, i32* %bytes_read, align 4, !dbg !2786
  br label %while.cond, !dbg !2787

while.cond:                                       ; preds = %while.body, %if.end3
  %6 = load i32, i32* %bytes_read, align 4, !dbg !2788
  %cmp = icmp sgt i32 %6, 0, !dbg !2790
  br i1 %cmp, label %while.body, label %while.end, !dbg !2791

while.body:                                       ; preds = %while.cond
  %arraydecay6 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buffer, i32 0, i32 0, !dbg !2792
  %7 = load i32, i32* %bytes_read, align 4, !dbg !2794
  call void @md5_process(%struct.md5_t* %my_md5, i8* %arraydecay6, i32 %7), !dbg !2795
  %arraydecay7 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buffer, i32 0, i32 0, !dbg !2796
  %8 = load %struct._IO_FILE*, %struct._IO_FILE** %myphile, align 8, !dbg !2797
  %call8 = call i64 @fread(i8* %arraydecay7, i64 1, i64 1024, %struct._IO_FILE* %8), !dbg !2798
  %conv9 = trunc i64 %call8 to i32, !dbg !2798
  store i32 %conv9, i32* %bytes_read, align 4, !dbg !2799
  br label %while.cond, !dbg !2800

while.end:                                        ; preds = %while.cond
  %arraydecay10 = getelementptr inbounds [16 x i8], [16 x i8]* %md5_result, i32 0, i32 0, !dbg !2802
  call void @md5_finish(%struct.md5_t* %my_md5, i8* %arraydecay10), !dbg !2803
  %arraydecay11 = getelementptr inbounds [16 x i8], [16 x i8]* %md5_result, i32 0, i32 0, !dbg !2804
  %arraydecay12 = getelementptr inbounds [64 x i8], [64 x i8]* %output_string, i32 0, i32 0, !dbg !2805
  call void @md5_sig_to_string(i8* %arraydecay11, i8* %arraydecay12, i32 64), !dbg !2806
  %arraydecay13 = getelementptr inbounds [64 x i8], [64 x i8]* %output_string, i32 0, i32 0, !dbg !2807
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.133, i32 0, i32 0), i8* %arraydecay13), !dbg !2808
  %9 = load %struct._IO_FILE*, %struct._IO_FILE** %myphile, align 8, !dbg !2809
  %call14 = call i32 @fclose(%struct._IO_FILE* %9), !dbg !2810
  br label %return, !dbg !2811

return:                                           ; preds = %while.end, %if.then2, %if.then
  ret void, !dbg !2812
}

declare void @md5_init(%struct.md5_t*) #4

declare i64 @fread(i8*, i64, i64, %struct._IO_FILE*) #4

declare void @md5_process(%struct.md5_t*, i8*, i32) #4

declare void @md5_finish(%struct.md5_t*, i8*) #4

declare void @md5_sig_to_string(i8*, i8*, i32) #4

; Function Attrs: nounwind uwtable
define void @command_site(i8* %str) #0 !dbg !171 {
entry:
  %str.addr = alloca i8*, align 8
  %i = alloca i32, align 4
  store i8* %str, i8** %str.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %str.addr, metadata !2813, metadata !246), !dbg !2814
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2815, metadata !246), !dbg !2816
  %call = call i8* @config_getoption(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.137, i32 0, i32 0)), !dbg !2817
  %call1 = call i32 @strcasecmp(i8* %call, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.54, i32 0, i32 0)) #9, !dbg !2819
  %tobool = icmp ne i32 %call1, 0, !dbg !2821
  br i1 %tobool, label %if.end, label %if.then, !dbg !2822

if.then:                                          ; preds = %entry
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.138, i32 0, i32 0)), !dbg !2823
  br label %return, !dbg !2825

if.end:                                           ; preds = %entry
  store i32 0, i32* %i, align 4, !dbg !2826
  br label %for.cond, !dbg !2828

for.cond:                                         ; preds = %for.inc, %if.end
  %0 = load i32, i32* %i, align 4, !dbg !2829
  %idxprom = sext i32 %0 to i64, !dbg !2832
  %arrayidx = getelementptr inbounds [4 x %struct.command], [4 x %struct.command]* @command_site.subcmds, i64 0, i64 %idxprom, !dbg !2832
  %name = getelementptr inbounds %struct.command, %struct.command* %arrayidx, i32 0, i32 0, !dbg !2833
  %1 = load i8*, i8** %name, align 16, !dbg !2833
  %tobool2 = icmp ne i8* %1, null, !dbg !2834
  br i1 %tobool2, label %for.body, label %for.end, !dbg !2834

for.body:                                         ; preds = %for.cond
  %2 = load i8*, i8** %str.addr, align 8, !dbg !2835
  %3 = load i32, i32* %i, align 4, !dbg !2838
  %idxprom3 = sext i32 %3 to i64, !dbg !2839
  %arrayidx4 = getelementptr inbounds [4 x %struct.command], [4 x %struct.command]* @command_site.subcmds, i64 0, i64 %idxprom3, !dbg !2839
  %name5 = getelementptr inbounds %struct.command, %struct.command* %arrayidx4, i32 0, i32 0, !dbg !2840
  %4 = load i8*, i8** %name5, align 16, !dbg !2840
  %5 = load i32, i32* %i, align 4, !dbg !2841
  %idxprom6 = sext i32 %5 to i64, !dbg !2842
  %arrayidx7 = getelementptr inbounds [4 x %struct.command], [4 x %struct.command]* @command_site.subcmds, i64 0, i64 %idxprom6, !dbg !2842
  %name8 = getelementptr inbounds %struct.command, %struct.command* %arrayidx7, i32 0, i32 0, !dbg !2843
  %6 = load i8*, i8** %name8, align 16, !dbg !2843
  %call9 = call i64 @strlen(i8* %6) #9, !dbg !2844
  %call10 = call i32 @strncasecmp(i8* %2, i8* %4, i64 %call9) #9, !dbg !2845
  %tobool11 = icmp ne i32 %call10, 0, !dbg !2847
  br i1 %tobool11, label %if.end19, label %if.then12, !dbg !2848

if.then12:                                        ; preds = %for.body
  %7 = load i8*, i8** %str.addr, align 8, !dbg !2849
  %8 = load i32, i32* %i, align 4, !dbg !2851
  %idxprom13 = sext i32 %8 to i64, !dbg !2852
  %arrayidx14 = getelementptr inbounds [4 x %struct.command], [4 x %struct.command]* @command_site.subcmds, i64 0, i64 %idxprom13, !dbg !2852
  %name15 = getelementptr inbounds %struct.command, %struct.command* %arrayidx14, i32 0, i32 0, !dbg !2853
  %9 = load i8*, i8** %name15, align 16, !dbg !2853
  %call16 = call i64 @strlen(i8* %9) #9, !dbg !2854
  %conv = trunc i64 %call16 to i32, !dbg !2854
  call void @cutto(i8* %7, i32 %conv), !dbg !2855
  %10 = load i32, i32* %i, align 4, !dbg !2857
  %idxprom17 = sext i32 %10 to i64, !dbg !2858
  %arrayidx18 = getelementptr inbounds [4 x %struct.command], [4 x %struct.command]* @command_site.subcmds, i64 0, i64 %idxprom17, !dbg !2858
  %function = getelementptr inbounds %struct.command, %struct.command* %arrayidx18, i32 0, i32 2, !dbg !2859
  %11 = load void (i8*)*, void (i8*)** %function, align 16, !dbg !2859
  %12 = load i8*, i8** %str.addr, align 8, !dbg !2860
  call void %11(i8* %12), !dbg !2858
  br label %return, !dbg !2861

if.end19:                                         ; preds = %for.body
  br label %for.inc, !dbg !2862

for.inc:                                          ; preds = %if.end19
  %13 = load i32, i32* %i, align 4, !dbg !2863
  %inc = add nsw i32 %13, 1, !dbg !2863
  store i32 %inc, i32* %i, align 4, !dbg !2863
  br label %for.cond, !dbg !2865

for.end:                                          ; preds = %for.cond
  %14 = load i8*, i8** %str.addr, align 8, !dbg !2866
  %call20 = call i32 @strcasecmp(i8* %14, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.139, i32 0, i32 0)) #9, !dbg !2868
  %tobool21 = icmp ne i32 %call20, 0, !dbg !2868
  br i1 %tobool21, label %if.end23, label %if.then22, !dbg !2869

if.then22:                                        ; preds = %for.end
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.140, i32 0, i32 0)), !dbg !2870
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.141, i32 0, i32 0)), !dbg !2872
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.142, i32 0, i32 0)), !dbg !2873
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.143, i32 0, i32 0)), !dbg !2874
  br label %return, !dbg !2875

if.end23:                                         ; preds = %for.end
  %15 = load i8*, i8** %str.addr, align 8, !dbg !2876
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.144, i32 0, i32 0), i8* %15), !dbg !2877
  br label %return, !dbg !2878

return:                                           ; preds = %if.end23, %if.then22, %if.then12, %if.then
  ret void, !dbg !2879
}

declare void @cutto(i8*, i32) #4

; Function Attrs: nounwind uwtable
define void @command_auth(i8* %type) #0 !dbg !172 {
entry:
  %type.addr = alloca i8*, align 8
  store i8* %type, i8** %type.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %type.addr, metadata !2881, metadata !246), !dbg !2882
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.145, i32 0, i32 0)), !dbg !2883
  ret void, !dbg !2884
}

; Function Attrs: nounwind uwtable
define void @command_opts(i8* %params) #0 !dbg !174 {
entry:
  %params.addr = alloca i8*, align 8
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !2885, metadata !246), !dbg !2886
  %0 = load i8*, i8** %params.addr, align 8, !dbg !2887
  %call = call i32 @strcasecmp(i8* %0, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.209, i32 0, i32 0)) #9, !dbg !2889
  %tobool = icmp ne i32 %call, 0, !dbg !2889
  br i1 %tobool, label %if.else, label %if.then, !dbg !2890

if.then:                                          ; preds = %entry
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.210, i32 0, i32 0)), !dbg !2891
  br label %if.end, !dbg !2891

if.else:                                          ; preds = %entry
  %1 = load i8*, i8** %params.addr, align 8, !dbg !2892
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.211, i32 0, i32 0), i8* %1), !dbg !2893
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !2894
}

; Function Attrs: nounwind uwtable
define void @command_help(i8* %params) #0 !dbg !175 {
entry:
  %params.addr = alloca i8*, align 8
  %i = alloca i32, align 4
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !2895, metadata !246), !dbg !2896
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2897, metadata !246), !dbg !2898
  %0 = load i8*, i8** %params.addr, align 8, !dbg !2899
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !2899
  %1 = load i8, i8* %arrayidx, align 1, !dbg !2899
  %conv = sext i8 %1 to i32, !dbg !2899
  %cmp = icmp eq i32 %conv, 0, !dbg !2901
  br i1 %cmp, label %if.then, label %if.else, !dbg !2902

if.then:                                          ; preds = %entry
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.212, i32 0, i32 0)), !dbg !2903
  store i32 0, i32* %i, align 4, !dbg !2905
  br label %for.cond, !dbg !2907

for.cond:                                         ; preds = %for.inc, %if.then
  %2 = load i32, i32* %i, align 4, !dbg !2908
  %idxprom = sext i32 %2 to i64, !dbg !2911
  %arrayidx2 = getelementptr inbounds [40 x %struct.command], [40 x %struct.command]* @commands, i64 0, i64 %idxprom, !dbg !2911
  %name = getelementptr inbounds %struct.command, %struct.command* %arrayidx2, i32 0, i32 0, !dbg !2912
  %3 = load i8*, i8** %name, align 16, !dbg !2912
  %tobool = icmp ne i8* %3, null, !dbg !2913
  br i1 %tobool, label %for.body, label %for.end, !dbg !2913

for.body:                                         ; preds = %for.cond
  %4 = load i32, i32* %i, align 4, !dbg !2914
  %idxprom3 = sext i32 %4 to i64, !dbg !2915
  %arrayidx4 = getelementptr inbounds [40 x %struct.command], [40 x %struct.command]* @commands, i64 0, i64 %idxprom3, !dbg !2915
  %name5 = getelementptr inbounds %struct.command, %struct.command* %arrayidx4, i32 0, i32 0, !dbg !2916
  %5 = load i8*, i8** %name5, align 16, !dbg !2916
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.213, i32 0, i32 0), i8* %5), !dbg !2917
  br label %for.inc, !dbg !2917

for.inc:                                          ; preds = %for.body
  %6 = load i32, i32* %i, align 4, !dbg !2918
  %inc = add nsw i32 %6, 1, !dbg !2918
  store i32 %inc, i32* %i, align 4, !dbg !2918
  br label %for.cond, !dbg !2920

for.end:                                          ; preds = %for.cond
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.214, i32 0, i32 0)), !dbg !2921
  br label %if.end22, !dbg !2922

if.else:                                          ; preds = %entry
  store i32 0, i32* %i, align 4, !dbg !2923
  br label %for.cond6, !dbg !2926

for.cond6:                                        ; preds = %for.inc19, %if.else
  %7 = load i32, i32* %i, align 4, !dbg !2927
  %idxprom7 = sext i32 %7 to i64, !dbg !2930
  %arrayidx8 = getelementptr inbounds [40 x %struct.command], [40 x %struct.command]* @commands, i64 0, i64 %idxprom7, !dbg !2930
  %name9 = getelementptr inbounds %struct.command, %struct.command* %arrayidx8, i32 0, i32 0, !dbg !2931
  %8 = load i8*, i8** %name9, align 16, !dbg !2931
  %tobool10 = icmp ne i8* %8, null, !dbg !2932
  br i1 %tobool10, label %for.body11, label %for.end21, !dbg !2932

for.body11:                                       ; preds = %for.cond6
  %9 = load i8*, i8** %params.addr, align 8, !dbg !2933
  %10 = load i32, i32* %i, align 4, !dbg !2935
  %idxprom12 = sext i32 %10 to i64, !dbg !2936
  %arrayidx13 = getelementptr inbounds [40 x %struct.command], [40 x %struct.command]* @commands, i64 0, i64 %idxprom12, !dbg !2936
  %name14 = getelementptr inbounds %struct.command, %struct.command* %arrayidx13, i32 0, i32 0, !dbg !2937
  %11 = load i8*, i8** %name14, align 16, !dbg !2937
  %call = call i32 @strcasecmp(i8* %9, i8* %11) #9, !dbg !2938
  %tobool15 = icmp ne i32 %call, 0, !dbg !2938
  br i1 %tobool15, label %if.end, label %if.then16, !dbg !2939

if.then16:                                        ; preds = %for.body11
  %12 = load i32, i32* %i, align 4, !dbg !2940
  %idxprom17 = sext i32 %12 to i64, !dbg !2941
  %arrayidx18 = getelementptr inbounds [40 x %struct.command], [40 x %struct.command]* @commands, i64 0, i64 %idxprom17, !dbg !2941
  %syntax = getelementptr inbounds %struct.command, %struct.command* %arrayidx18, i32 0, i32 1, !dbg !2942
  %13 = load i8*, i8** %syntax, align 8, !dbg !2942
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.215, i32 0, i32 0), i8* %13), !dbg !2943
  br label %if.end, !dbg !2943

if.end:                                           ; preds = %if.then16, %for.body11
  br label %for.inc19, !dbg !2944

for.inc19:                                        ; preds = %if.end
  %14 = load i32, i32* %i, align 4, !dbg !2946
  %inc20 = add nsw i32 %14, 1, !dbg !2946
  store i32 %inc20, i32* %i, align 4, !dbg !2946
  br label %for.cond6, !dbg !2948

for.end21:                                        ; preds = %for.cond6
  br label %if.end22

if.end22:                                         ; preds = %for.end21, %for.end
  ret void, !dbg !2949
}

; Function Attrs: nounwind uwtable
define void @command_feat(i8* %params) #0 !dbg !173 {
entry:
  %params.addr = alloca i8*, align 8
  %i = alloca i32, align 4
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !2950, metadata !246), !dbg !2951
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2952, metadata !246), !dbg !2953
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.205, i32 0, i32 0)), !dbg !2954
  store i32 0, i32* %i, align 4, !dbg !2955
  br label %for.cond, !dbg !2957

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !2958
  %idxprom = sext i32 %0 to i64, !dbg !2961
  %arrayidx = getelementptr inbounds [40 x %struct.command], [40 x %struct.command]* @commands, i64 0, i64 %idxprom, !dbg !2961
  %name = getelementptr inbounds %struct.command, %struct.command* %arrayidx, i32 0, i32 0, !dbg !2962
  %1 = load i8*, i8** %name, align 16, !dbg !2962
  %tobool = icmp ne i8* %1, null, !dbg !2963
  br i1 %tobool, label %for.body, label %for.end, !dbg !2963

for.body:                                         ; preds = %for.cond
  %2 = load i32, i32* %i, align 4, !dbg !2964
  %idxprom1 = sext i32 %2 to i64, !dbg !2966
  %arrayidx2 = getelementptr inbounds [40 x %struct.command], [40 x %struct.command]* @commands, i64 0, i64 %idxprom1, !dbg !2966
  %showinfeat = getelementptr inbounds %struct.command, %struct.command* %arrayidx2, i32 0, i32 4, !dbg !2967
  %3 = load i8, i8* %showinfeat, align 1, !dbg !2967
  %tobool3 = icmp ne i8 %3, 0, !dbg !2966
  br i1 %tobool3, label %if.then, label %if.end, !dbg !2968

if.then:                                          ; preds = %for.body
  %4 = load i32, i32* %i, align 4, !dbg !2969
  %idxprom4 = sext i32 %4 to i64, !dbg !2970
  %arrayidx5 = getelementptr inbounds [40 x %struct.command], [40 x %struct.command]* @commands, i64 0, i64 %idxprom4, !dbg !2970
  %name6 = getelementptr inbounds %struct.command, %struct.command* %arrayidx5, i32 0, i32 0, !dbg !2971
  %5 = load i8*, i8** %name6, align 16, !dbg !2971
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.206, i32 0, i32 0), i8* %5), !dbg !2972
  br label %if.end, !dbg !2972

if.end:                                           ; preds = %if.then, %for.body
  br label %for.inc, !dbg !2973

for.inc:                                          ; preds = %if.end
  %6 = load i32, i32* %i, align 4, !dbg !2975
  %inc = add nsw i32 %6, 1, !dbg !2975
  store i32 %inc, i32* %i, align 4, !dbg !2975
  br label %for.cond, !dbg !2977

for.end:                                          ; preds = %for.cond
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.207, i32 0, i32 0)), !dbg !2978
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.208, i32 0, i32 0)), !dbg !2979
  ret void, !dbg !2980
}

; Function Attrs: nounwind uwtable
define i32 @parsecmd(i8* %str) #0 !dbg !176 {
entry:
  %retval = alloca i32, align 4
  %str.addr = alloca i8*, align 8
  %i = alloca i32, align 4
  %p = alloca i8*, align 8
  %pp = alloca i8*, align 8
  %confstr = alloca [64 x i8], align 16
  store i8* %str, i8** %str.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %str.addr, metadata !2981, metadata !246), !dbg !2982
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2983, metadata !246), !dbg !2984
  call void @llvm.dbg.declare(metadata i8** %p, metadata !2985, metadata !246), !dbg !2986
  call void @llvm.dbg.declare(metadata i8** %pp, metadata !2987, metadata !246), !dbg !2988
  call void @llvm.dbg.declare(metadata [64 x i8]* %confstr, metadata !2989, metadata !246), !dbg !2990
  %0 = load i8*, i8** %str.addr, align 8, !dbg !2991
  store i8* %0, i8** %pp, align 8, !dbg !2992
  store i8* %0, i8** %p, align 8, !dbg !2993
  br label %while.cond, !dbg !2994

while.cond:                                       ; preds = %if.end, %entry
  %1 = load i8*, i8** %p, align 8, !dbg !2995
  %2 = load i8, i8* %1, align 1, !dbg !2997
  %tobool = icmp ne i8 %2, 0, !dbg !2998
  br i1 %tobool, label %while.body, label %while.end, !dbg !2998

while.body:                                       ; preds = %while.cond
  %3 = load i8*, i8** %p, align 8, !dbg !2999
  %4 = load i8, i8* %3, align 1, !dbg !3001
  %conv = zext i8 %4 to i32, !dbg !3002
  %cmp = icmp slt i32 %conv, 32, !dbg !3003
  br i1 %cmp, label %if.then, label %if.else, !dbg !3004

if.then:                                          ; preds = %while.body
  %5 = load i8*, i8** %p, align 8, !dbg !3005
  %incdec.ptr = getelementptr inbounds i8, i8* %5, i32 1, !dbg !3005
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !3005
  br label %if.end, !dbg !3006

if.else:                                          ; preds = %while.body
  %6 = load i8*, i8** %p, align 8, !dbg !3007
  %incdec.ptr2 = getelementptr inbounds i8, i8* %6, i32 1, !dbg !3007
  store i8* %incdec.ptr2, i8** %p, align 8, !dbg !3007
  %7 = load i8, i8* %6, align 1, !dbg !3008
  %8 = load i8*, i8** %pp, align 8, !dbg !3009
  %incdec.ptr3 = getelementptr inbounds i8, i8* %8, i32 1, !dbg !3009
  store i8* %incdec.ptr3, i8** %pp, align 8, !dbg !3009
  store i8 %7, i8* %8, align 1, !dbg !3010
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  br label %while.cond, !dbg !3011

while.end:                                        ; preds = %while.cond
  %9 = load i8*, i8** %pp, align 8, !dbg !3013
  %incdec.ptr4 = getelementptr inbounds i8, i8* %9, i32 1, !dbg !3013
  store i8* %incdec.ptr4, i8** %pp, align 8, !dbg !3013
  store i8 0, i8* %9, align 1, !dbg !3014
  store i32 0, i32* %i, align 4, !dbg !3015
  br label %for.cond, !dbg !3017

for.cond:                                         ; preds = %for.inc, %while.end
  %10 = load i32, i32* %i, align 4, !dbg !3018
  %idxprom = sext i32 %10 to i64, !dbg !3021
  %arrayidx = getelementptr inbounds [40 x %struct.command], [40 x %struct.command]* @commands, i64 0, i64 %idxprom, !dbg !3021
  %name = getelementptr inbounds %struct.command, %struct.command* %arrayidx, i32 0, i32 0, !dbg !3022
  %11 = load i8*, i8** %name, align 16, !dbg !3022
  %tobool5 = icmp ne i8* %11, null, !dbg !3023
  br i1 %tobool5, label %for.body, label %for.end, !dbg !3023

for.body:                                         ; preds = %for.cond
  %12 = load i8*, i8** %str.addr, align 8, !dbg !3024
  %13 = load i32, i32* %i, align 4, !dbg !3027
  %idxprom6 = sext i32 %13 to i64, !dbg !3028
  %arrayidx7 = getelementptr inbounds [40 x %struct.command], [40 x %struct.command]* @commands, i64 0, i64 %idxprom6, !dbg !3028
  %name8 = getelementptr inbounds %struct.command, %struct.command* %arrayidx7, i32 0, i32 0, !dbg !3029
  %14 = load i8*, i8** %name8, align 16, !dbg !3029
  %15 = load i32, i32* %i, align 4, !dbg !3030
  %idxprom9 = sext i32 %15 to i64, !dbg !3031
  %arrayidx10 = getelementptr inbounds [40 x %struct.command], [40 x %struct.command]* @commands, i64 0, i64 %idxprom9, !dbg !3031
  %name11 = getelementptr inbounds %struct.command, %struct.command* %arrayidx10, i32 0, i32 0, !dbg !3032
  %16 = load i8*, i8** %name11, align 16, !dbg !3032
  %call = call i64 @strlen(i8* %16) #9, !dbg !3033
  %call12 = call i32 @strncasecmp(i8* %12, i8* %14, i64 %call) #9, !dbg !3034
  %tobool13 = icmp ne i32 %call12, 0, !dbg !3036
  br i1 %tobool13, label %if.end58, label %if.then14, !dbg !3037

if.then14:                                        ; preds = %for.body
  %arraydecay = getelementptr inbounds [64 x i8], [64 x i8]* %confstr, i32 0, i32 0, !dbg !3038
  %17 = load i32, i32* %i, align 4, !dbg !3040
  %idxprom15 = sext i32 %17 to i64, !dbg !3041
  %arrayidx16 = getelementptr inbounds [40 x %struct.command], [40 x %struct.command]* @commands, i64 0, i64 %idxprom15, !dbg !3041
  %name17 = getelementptr inbounds %struct.command, %struct.command* %arrayidx16, i32 0, i32 0, !dbg !3042
  %18 = load i8*, i8** %name17, align 16, !dbg !3042
  %call18 = call i32 (i8*, i8*, ...) @sprintf(i8* %arraydecay, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.216, i32 0, i32 0), i8* %18) #2, !dbg !3043
  %arraydecay19 = getelementptr inbounds [64 x i8], [64 x i8]* %confstr, i32 0, i32 0, !dbg !3044
  %call20 = call i8* @config_getoption(i8* %arraydecay19), !dbg !3046
  %call21 = call i32 @strcasecmp(i8* %call20, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.54, i32 0, i32 0)) #9, !dbg !3047
  %tobool22 = icmp ne i32 %call21, 0, !dbg !3049
  br i1 %tobool22, label %if.end27, label %if.then23, !dbg !3050

if.then23:                                        ; preds = %if.then14
  %19 = load i32, i32* %i, align 4, !dbg !3051
  %idxprom24 = sext i32 %19 to i64, !dbg !3053
  %arrayidx25 = getelementptr inbounds [40 x %struct.command], [40 x %struct.command]* @commands, i64 0, i64 %idxprom24, !dbg !3053
  %name26 = getelementptr inbounds %struct.command, %struct.command* %arrayidx25, i32 0, i32 0, !dbg !3054
  %20 = load i8*, i8** %name26, align 16, !dbg !3054
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.217, i32 0, i32 0), i8* %20), !dbg !3055
  store i32 1, i32* %retval, align 4, !dbg !3056
  br label %return, !dbg !3056

if.end27:                                         ; preds = %if.then14
  %21 = load i8*, i8** %str.addr, align 8, !dbg !3057
  %22 = load i32, i32* %i, align 4, !dbg !3058
  %idxprom28 = sext i32 %22 to i64, !dbg !3059
  %arrayidx29 = getelementptr inbounds [40 x %struct.command], [40 x %struct.command]* @commands, i64 0, i64 %idxprom28, !dbg !3059
  %name30 = getelementptr inbounds %struct.command, %struct.command* %arrayidx29, i32 0, i32 0, !dbg !3060
  %23 = load i8*, i8** %name30, align 16, !dbg !3060
  %call31 = call i64 @strlen(i8* %23) #9, !dbg !3061
  %conv32 = trunc i64 %call31 to i32, !dbg !3061
  call void @cutto(i8* %21, i32 %conv32), !dbg !3062
  %24 = load i8*, i8** %str.addr, align 8, !dbg !3064
  store i8* %24, i8** %p, align 8, !dbg !3065
  br label %while.cond33, !dbg !3066

while.cond33:                                     ; preds = %while.body42, %if.end27
  %25 = load i8*, i8** %p, align 8, !dbg !3067
  %26 = load i8, i8* %25, align 1, !dbg !3068
  %conv34 = sext i8 %26 to i32, !dbg !3069
  %tobool35 = icmp ne i32 %conv34, 0, !dbg !3069
  br i1 %tobool35, label %land.rhs, label %land.end, !dbg !3070

land.rhs:                                         ; preds = %while.cond33
  %27 = load i8*, i8** %p, align 8, !dbg !3071
  %28 = load i8, i8* %27, align 1, !dbg !3073
  %conv36 = sext i8 %28 to i32, !dbg !3073
  %cmp37 = icmp eq i32 %conv36, 32, !dbg !3074
  br i1 %cmp37, label %lor.end, label %lor.rhs, !dbg !3075

lor.rhs:                                          ; preds = %land.rhs
  %29 = load i8*, i8** %p, align 8, !dbg !3076
  %30 = load i8, i8* %29, align 1, !dbg !3078
  %conv39 = sext i8 %30 to i32, !dbg !3078
  %cmp40 = icmp eq i32 %conv39, 9, !dbg !3079
  br label %lor.end, !dbg !3080

lor.end:                                          ; preds = %lor.rhs, %land.rhs
  %31 = phi i1 [ true, %land.rhs ], [ %cmp40, %lor.rhs ]
  br label %land.end

land.end:                                         ; preds = %lor.end, %while.cond33
  %32 = phi i1 [ false, %while.cond33 ], [ %31, %lor.end ]
  br i1 %32, label %while.body42, label %while.end44, !dbg !3081

while.body42:                                     ; preds = %land.end
  %33 = load i8*, i8** %p, align 8, !dbg !3083
  %incdec.ptr43 = getelementptr inbounds i8, i8* %33, i32 1, !dbg !3083
  store i8* %incdec.ptr43, i8** %p, align 8, !dbg !3083
  br label %while.cond33, !dbg !3084

while.end44:                                      ; preds = %land.end
  %34 = load i8*, i8** %str.addr, align 8, !dbg !3086
  %35 = load i8*, i8** %p, align 8, !dbg !3087
  %36 = load i8*, i8** %str.addr, align 8, !dbg !3088
  %call45 = call i64 @strlen(i8* %36) #9, !dbg !3089
  %37 = load i8*, i8** %p, align 8, !dbg !3090
  %38 = load i8*, i8** %str.addr, align 8, !dbg !3091
  %sub.ptr.lhs.cast = ptrtoint i8* %37 to i64, !dbg !3092
  %sub.ptr.rhs.cast = ptrtoint i8* %38 to i64, !dbg !3092
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !3092
  %sub = sub i64 %call45, %sub.ptr.sub, !dbg !3093
  %add = add i64 %sub, 1, !dbg !3094
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %34, i8* %35, i64 %add, i32 1, i1 false), !dbg !3095
  %39 = load i32, i32* @state, align 4, !dbg !3096
  %40 = load i32, i32* %i, align 4, !dbg !3098
  %idxprom46 = sext i32 %40 to i64, !dbg !3099
  %arrayidx47 = getelementptr inbounds [40 x %struct.command], [40 x %struct.command]* @commands, i64 0, i64 %idxprom46, !dbg !3099
  %state_needed = getelementptr inbounds %struct.command, %struct.command* %arrayidx47, i32 0, i32 3, !dbg !3100
  %41 = load i8, i8* %state_needed, align 8, !dbg !3100
  %conv48 = sext i8 %41 to i32, !dbg !3099
  %cmp49 = icmp sge i32 %39, %conv48, !dbg !3101
  br i1 %cmp49, label %if.then51, label %if.else54, !dbg !3102

if.then51:                                        ; preds = %while.end44
  %42 = load i32, i32* %i, align 4, !dbg !3103
  %idxprom52 = sext i32 %42 to i64, !dbg !3105
  %arrayidx53 = getelementptr inbounds [40 x %struct.command], [40 x %struct.command]* @commands, i64 0, i64 %idxprom52, !dbg !3105
  %function = getelementptr inbounds %struct.command, %struct.command* %arrayidx53, i32 0, i32 2, !dbg !3106
  %43 = load void (i8*)*, void (i8*)** %function, align 16, !dbg !3106
  %44 = load i8*, i8** %str.addr, align 8, !dbg !3107
  call void %43(i8* %44), !dbg !3105
  store i32 0, i32* %retval, align 4, !dbg !3108
  br label %return, !dbg !3108

if.else54:                                        ; preds = %while.end44
  %45 = load i32, i32* @state, align 4, !dbg !3109
  switch i32 %45, label %sw.epilog [
    i32 0, label %sw.bb
    i32 1, label %sw.bb55
    i32 2, label %sw.bb56
  ], !dbg !3111

sw.bb:                                            ; preds = %if.else54
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.218, i32 0, i32 0)), !dbg !3112
  store i32 1, i32* %retval, align 4, !dbg !3115
  br label %return, !dbg !3115

sw.bb55:                                          ; preds = %if.else54
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.219, i32 0, i32 0)), !dbg !3116
  store i32 1, i32* %retval, align 4, !dbg !3118
  br label %return, !dbg !3118

sw.bb56:                                          ; preds = %if.else54
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.220, i32 0, i32 0)), !dbg !3119
  store i32 1, i32* %retval, align 4, !dbg !3121
  br label %return, !dbg !3121

sw.epilog:                                        ; preds = %if.else54
  br label %if.end57

if.end57:                                         ; preds = %sw.epilog
  br label %if.end58, !dbg !3122

if.end58:                                         ; preds = %if.end57, %for.body
  br label %for.inc, !dbg !3123

for.inc:                                          ; preds = %if.end58
  %46 = load i32, i32* %i, align 4, !dbg !3124
  %inc = add nsw i32 %46, 1, !dbg !3124
  store i32 %inc, i32* %i, align 4, !dbg !3124
  br label %for.cond, !dbg !3126

for.end:                                          ; preds = %for.cond
  %47 = load i8*, i8** %str.addr, align 8, !dbg !3127
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.221, i32 0, i32 0), i8* %47), !dbg !3128
  store i32 0, i32* %retval, align 4, !dbg !3129
  br label %return, !dbg !3129

return:                                           ; preds = %for.end, %sw.bb56, %sw.bb55, %sw.bb, %if.then51, %if.then23
  %48 = load i32, i32* %retval, align 4, !dbg !3130
  ret i32 %48, !dbg !3130
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

; Function Attrs: nounwind
declare void (i32)* @signal(i32, void (i32)*) #3

; Function Attrs: nounwind
declare i32 @fork() #3

; Function Attrs: nounwind
declare i32 @execv(i8*, i8**) #3

; Function Attrs: nounwind
declare i32 @wait4(i32, %union.wait*, i32, %struct.rusage*) #3

; Function Attrs: nounwind uwtable
define void @Force_Update_Sent_Recv_Log() #0 !dbg !185 {
entry:
  %0 = load double, double* @bytes_sent, align 8, !dbg !3131
  %1 = load double, double* @bytes_recvd, align 8, !dbg !3132
  %call = call i32 @Update_Send_Recv(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0), double %0, double %1), !dbg !3133
  ret void, !dbg !3134
}

declare i32 @Update_Send_Recv(i8*, double, double) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #9 = { nounwind readonly }
attributes #10 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!242, !243}
!llvm.ident = !{!244}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !35, subprograms: !113, globals: !186)
!1 = !DIFile(filename: "commands.c", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!2 = !{!3, !15, !20, !27}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "__socket_type", file: !4, line: 24, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket_type.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14}
!6 = !DIEnumerator(name: "SOCK_STREAM", value: 1)
!7 = !DIEnumerator(name: "SOCK_DGRAM", value: 2)
!8 = !DIEnumerator(name: "SOCK_RAW", value: 3)
!9 = !DIEnumerator(name: "SOCK_RDM", value: 4)
!10 = !DIEnumerator(name: "SOCK_SEQPACKET", value: 5)
!11 = !DIEnumerator(name: "SOCK_DCCP", value: 6)
!12 = !DIEnumerator(name: "SOCK_PACKET", value: 10)
!13 = !DIEnumerator(name: "SOCK_CLOEXEC", value: 524288)
!14 = !DIEnumerator(name: "SOCK_NONBLOCK", value: 2048)
!15 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !16, line: 19, size: 32, align: 32, elements: !17)
!16 = !DIFile(filename: "./commands.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!17 = !{!18, !19}
!18 = !DIEnumerator(name: "TYPE_ASCII", value: 0)
!19 = !DIEnumerator(name: "TYPE_BINARY", value: 1)
!20 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !16, line: 15, size: 32, align: 32, elements: !21)
!21 = !{!22, !23, !24, !25, !26}
!22 = !DIEnumerator(name: "STATE_CONNECTED", value: 0)
!23 = !DIEnumerator(name: "STATE_USER", value: 1)
!24 = !DIEnumerator(name: "STATE_AUTHENTICATED", value: 2)
!25 = !DIEnumerator(name: "STATE_RENAME", value: 3)
!26 = !DIEnumerator(name: "STATE_ADMIN", value: 4)
!27 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "const_whattodo", file: !28, line: 4, size: 32, align: 32, elements: !29)
!28 = !DIFile(filename: "./targzip.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!29 = !{!30, !31, !32, !33, !34}
!30 = !DIEnumerator(name: "DO_NORMAL", value: 0)
!31 = !DIEnumerator(name: "DO_TARGZ", value: 1)
!32 = !DIEnumerator(name: "DO_TARONLY", value: 2)
!33 = !DIEnumerator(name: "DO_GZONLY", value: 3)
!34 = !DIEnumerator(name: "DO_GZUNZIP", value: 4)
!35 = !{!36, !37, !50, !56, !57, !61, !64, !65, !66, !105, !106, !108}
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!37 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !38, size: 64, align: 64)
!38 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !39, line: 149, size: 128, align: 16, elements: !40)
!39 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!40 = !{!41, !45}
!41 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !38, file: !39, line: 151, baseType: !42, size: 16, align: 16)
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !43, line: 28, baseType: !44)
!43 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!44 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !38, file: !39, line: 152, baseType: !46, size: 112, align: 8, offset: 16)
!46 = !DICompositeType(tag: DW_TAG_array_type, baseType: !47, size: 112, align: 8, elements: !48)
!47 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!48 = !{!49}
!49 = !DISubrange(count: 14)
!50 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !51, size: 64, align: 64)
!51 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !52, line: 274, baseType: !53)
!52 = !DIFile(filename: "/usr/include/unistd.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!53 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !54, line: 189, baseType: !55)
!54 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!55 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!56 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !47, size: 64, align: 64)
!57 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_addr_t", file: !58, line: 30, baseType: !59)
!58 = !DIFile(filename: "/usr/include/netinet/in.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!59 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !60, line: 51, baseType: !55)
!60 = !DIFile(filename: "/usr/include/stdint.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!61 = !DIDerivedType(tag: DW_TAG_typedef, name: "__fd_mask", file: !62, line: 54, baseType: !63)
!62 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/select.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!63 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!64 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!65 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !67, size: 64, align: 64)
!67 = !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !68, line: 46, size: 1152, align: 64, elements: !69)
!68 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stat.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!69 = !{!70, !73, !75, !77, !79, !81, !83, !84, !85, !87, !89, !91, !99, !100, !101}
!70 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !67, file: !68, line: 48, baseType: !71, size: 64, align: 64)
!71 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !54, line: 124, baseType: !72)
!72 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !67, file: !68, line: 53, baseType: !74, size: 64, align: 64, offset: 64)
!74 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino_t", file: !54, line: 127, baseType: !72)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !67, file: !68, line: 61, baseType: !76, size: 64, align: 64, offset: 128)
!76 = !DIDerivedType(tag: DW_TAG_typedef, name: "__nlink_t", file: !54, line: 130, baseType: !72)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !67, file: !68, line: 62, baseType: !78, size: 32, align: 32, offset: 192)
!78 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !54, line: 129, baseType: !55)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !67, file: !68, line: 64, baseType: !80, size: 32, align: 32, offset: 224)
!80 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !54, line: 125, baseType: !55)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !67, file: !68, line: 65, baseType: !82, size: 32, align: 32, offset: 256)
!82 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !54, line: 126, baseType: !55)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "__pad0", scope: !67, file: !68, line: 67, baseType: !64, size: 32, align: 32, offset: 288)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !67, file: !68, line: 69, baseType: !71, size: 64, align: 64, offset: 320)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !67, file: !68, line: 74, baseType: !86, size: 64, align: 64, offset: 384)
!86 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !54, line: 131, baseType: !63)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !67, file: !68, line: 78, baseType: !88, size: 64, align: 64, offset: 448)
!88 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blksize_t", file: !54, line: 153, baseType: !63)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !67, file: !68, line: 80, baseType: !90, size: 64, align: 64, offset: 512)
!90 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blkcnt_t", file: !54, line: 158, baseType: !63)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !67, file: !68, line: 91, baseType: !92, size: 128, align: 64, offset: 576)
!92 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !93, line: 120, size: 128, align: 64, elements: !94)
!93 = !DIFile(filename: "/usr/include/time.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!94 = !{!95, !97}
!95 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !92, file: !93, line: 122, baseType: !96, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !54, line: 139, baseType: !63)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !92, file: !93, line: 123, baseType: !98, size: 64, align: 64, offset: 64)
!98 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !54, line: 175, baseType: !63)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !67, file: !68, line: 92, baseType: !92, size: 128, align: 64, offset: 704)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !67, file: !68, line: 93, baseType: !92, size: 128, align: 64, offset: 832)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !67, file: !68, line: 106, baseType: !102, size: 192, align: 64, offset: 960)
!102 = !DICompositeType(tag: DW_TAG_array_type, baseType: !98, size: 192, align: 64, elements: !103)
!103 = !{!104}
!104 = !DISubrange(count: 3)
!105 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!106 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !107, size: 64, align: 64)
!107 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !93, line: 75, baseType: !96)
!108 = !DIDerivedType(tag: DW_TAG_typedef, name: "__sighandler_t", file: !109, line: 85, baseType: !110)
!109 = !DIFile(filename: "/usr/include/signal.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!110 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !111, size: 64, align: 64)
!111 = !DISubroutineType(types: !112)
!112 = !{null, !64}
!113 = !{!114, !119, !122, !123, !126, !127, !130, !131, !132, !133, !134, !135, !136, !137, !140, !141, !142, !145, !146, !147, !148, !149, !152, !153, !154, !155, !156, !157, !158, !159, !160, !161, !162, !163, !164, !165, !166, !167, !168, !169, !170, !171, !172, !173, !174, !175, !176, !179, !182, !185}
!114 = distinct !DISubprogram(name: "control_printf", scope: !115, file: !115, line: 80, type: !116, isLocal: false, isDefinition: true, scopeLine: 81, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!115 = !DIFile(filename: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/commands.c", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!116 = !DISubroutineType(types: !117)
!117 = !{null, !47, !56, null}
!118 = !{}
!119 = distinct !DISubprogram(name: "new_umask", scope: !115, file: !115, line: 92, type: !120, isLocal: false, isDefinition: true, scopeLine: 93, isOptimized: false, variables: !118)
!120 = !DISubroutineType(types: !121)
!121 = !{null}
!122 = distinct !DISubprogram(name: "prepare_sock", scope: !115, file: !115, line: 113, type: !111, isLocal: false, isDefinition: true, scopeLine: 114, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!123 = distinct !DISubprogram(name: "dataconn", scope: !115, file: !115, line: 134, type: !124, isLocal: false, isDefinition: true, scopeLine: 135, isOptimized: false, variables: !118)
!124 = !DISubroutineType(types: !125)
!125 = !{!64}
!126 = distinct !DISubprogram(name: "init_userinfo", scope: !115, file: !115, line: 181, type: !120, isLocal: false, isDefinition: true, scopeLine: 182, isOptimized: false, variables: !118)
!127 = distinct !DISubprogram(name: "command_user", scope: !115, file: !115, line: 198, type: !128, isLocal: false, isDefinition: true, scopeLine: 199, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!128 = !DISubroutineType(types: !129)
!129 = !{null, !56}
!130 = distinct !DISubprogram(name: "command_pass", scope: !115, file: !115, line: 229, type: !128, isLocal: false, isDefinition: true, scopeLine: 230, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!131 = distinct !DISubprogram(name: "command_pwd", scope: !115, file: !115, line: 244, type: !128, isLocal: false, isDefinition: true, scopeLine: 245, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!132 = distinct !DISubprogram(name: "command_type", scope: !115, file: !115, line: 257, type: !128, isLocal: false, isDefinition: true, scopeLine: 258, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!133 = distinct !DISubprogram(name: "command_port", scope: !115, file: !115, line: 269, type: !128, isLocal: false, isDefinition: true, scopeLine: 269, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!134 = distinct !DISubprogram(name: "command_eprt", scope: !115, file: !115, line: 291, type: !128, isLocal: false, isDefinition: true, scopeLine: 291, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!135 = distinct !DISubprogram(name: "command_pasv", scope: !115, file: !115, line: 328, type: !128, isLocal: false, isDefinition: true, scopeLine: 329, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!136 = distinct !DISubprogram(name: "command_epsv", scope: !115, file: !115, line: 401, type: !128, isLocal: false, isDefinition: true, scopeLine: 402, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!137 = distinct !DISubprogram(name: "test_abort", scope: !115, file: !115, line: 442, type: !138, isLocal: false, isDefinition: true, scopeLine: 443, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!138 = !DISubroutineType(types: !139)
!139 = !{!47, !47, !64, !64}
!140 = distinct !DISubprogram(name: "command_allo", scope: !115, file: !115, line: 471, type: !128, isLocal: false, isDefinition: true, scopeLine: 472, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!141 = distinct !DISubprogram(name: "command_mput", scope: !115, file: !115, line: 478, type: !128, isLocal: false, isDefinition: true, scopeLine: 479, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!142 = distinct !DISubprogram(name: "do_stor", scope: !115, file: !115, line: 532, type: !143, isLocal: false, isDefinition: true, scopeLine: 533, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!143 = !DISubroutineType(types: !144)
!144 = !{null, !56, !64}
!145 = distinct !DISubprogram(name: "command_stor", scope: !115, file: !115, line: 788, type: !128, isLocal: false, isDefinition: true, scopeLine: 789, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!146 = distinct !DISubprogram(name: "command_appe", scope: !115, file: !115, line: 793, type: !128, isLocal: false, isDefinition: true, scopeLine: 794, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!147 = distinct !DISubprogram(name: "command_mget", scope: !115, file: !115, line: 802, type: !128, isLocal: false, isDefinition: true, scopeLine: 803, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!148 = distinct !DISubprogram(name: "command_retr", scope: !115, file: !115, line: 854, type: !128, isLocal: false, isDefinition: true, scopeLine: 855, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!149 = distinct !DISubprogram(name: "do_dirlist", scope: !115, file: !115, line: 1281, type: !150, isLocal: false, isDefinition: true, scopeLine: 1282, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!150 = !DISubroutineType(types: !151)
!151 = !{null, !56, !47}
!152 = distinct !DISubprogram(name: "command_list", scope: !115, file: !115, line: 1320, type: !128, isLocal: false, isDefinition: true, scopeLine: 1321, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!153 = distinct !DISubprogram(name: "command_nlst", scope: !115, file: !115, line: 1325, type: !128, isLocal: false, isDefinition: true, scopeLine: 1326, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!154 = distinct !DISubprogram(name: "command_syst", scope: !115, file: !115, line: 1330, type: !128, isLocal: false, isDefinition: true, scopeLine: 1331, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!155 = distinct !DISubprogram(name: "command_mdtm", scope: !115, file: !115, line: 1335, type: !128, isLocal: false, isDefinition: true, scopeLine: 1336, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!156 = distinct !DISubprogram(name: "command_cwd", scope: !115, file: !115, line: 1353, type: !128, isLocal: false, isDefinition: true, scopeLine: 1354, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!157 = distinct !DISubprogram(name: "command_cdup", scope: !115, file: !115, line: 1365, type: !128, isLocal: false, isDefinition: true, scopeLine: 1366, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!158 = distinct !DISubprogram(name: "command_dele", scope: !115, file: !115, line: 1372, type: !128, isLocal: false, isDefinition: true, scopeLine: 1373, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!159 = distinct !DISubprogram(name: "command_mkd", scope: !115, file: !115, line: 1417, type: !128, isLocal: false, isDefinition: true, scopeLine: 1418, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!160 = distinct !DISubprogram(name: "command_rmd", scope: !115, file: !115, line: 1439, type: !128, isLocal: false, isDefinition: true, scopeLine: 1440, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!161 = distinct !DISubprogram(name: "command_noop", scope: !115, file: !115, line: 1471, type: !128, isLocal: false, isDefinition: true, scopeLine: 1472, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!162 = distinct !DISubprogram(name: "command_rnfr", scope: !115, file: !115, line: 1476, type: !128, isLocal: false, isDefinition: true, scopeLine: 1477, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!163 = distinct !DISubprogram(name: "command_rnto", scope: !115, file: !115, line: 1493, type: !128, isLocal: false, isDefinition: true, scopeLine: 1494, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!164 = distinct !DISubprogram(name: "command_rest", scope: !115, file: !115, line: 1518, type: !128, isLocal: false, isDefinition: true, scopeLine: 1519, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!165 = distinct !DISubprogram(name: "command_size", scope: !115, file: !115, line: 1524, type: !128, isLocal: false, isDefinition: true, scopeLine: 1525, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!166 = distinct !DISubprogram(name: "command_quit", scope: !115, file: !115, line: 1536, type: !128, isLocal: false, isDefinition: true, scopeLine: 1537, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!167 = distinct !DISubprogram(name: "command_stat", scope: !115, file: !115, line: 1545, type: !128, isLocal: false, isDefinition: true, scopeLine: 1546, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!168 = distinct !DISubprogram(name: "command_chmod", scope: !115, file: !115, line: 1556, type: !128, isLocal: false, isDefinition: true, scopeLine: 1557, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!169 = distinct !DISubprogram(name: "command_chown", scope: !115, file: !115, line: 1594, type: !128, isLocal: false, isDefinition: true, scopeLine: 1595, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!170 = distinct !DISubprogram(name: "command_md5", scope: !115, file: !115, line: 1643, type: !128, isLocal: false, isDefinition: true, scopeLine: 1644, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!171 = distinct !DISubprogram(name: "command_site", scope: !115, file: !115, line: 1682, type: !128, isLocal: false, isDefinition: true, scopeLine: 1683, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!172 = distinct !DISubprogram(name: "command_auth", scope: !115, file: !115, line: 1715, type: !128, isLocal: false, isDefinition: true, scopeLine: 1716, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!173 = distinct !DISubprogram(name: "command_feat", scope: !115, file: !115, line: 1767, type: !128, isLocal: false, isDefinition: true, scopeLine: 1768, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!174 = distinct !DISubprogram(name: "command_opts", scope: !115, file: !115, line: 1778, type: !128, isLocal: false, isDefinition: true, scopeLine: 1779, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!175 = distinct !DISubprogram(name: "command_help", scope: !115, file: !115, line: 1787, type: !128, isLocal: false, isDefinition: true, scopeLine: 1788, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!176 = distinct !DISubprogram(name: "parsecmd", scope: !115, file: !115, line: 1802, type: !177, isLocal: false, isDefinition: true, scopeLine: 1803, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!177 = !DISubroutineType(types: !178)
!178 = !{!64, !56}
!179 = distinct !DISubprogram(name: "get_buffer_size", scope: !115, file: !115, line: 1852, type: !180, isLocal: false, isDefinition: true, scopeLine: 1853, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!180 = !DISubroutineType(types: !181)
!181 = !{!64, !64}
!182 = distinct !DISubprogram(name: "run_script", scope: !115, file: !115, line: 1872, type: !183, isLocal: false, isDefinition: true, scopeLine: 1873, flags: DIFlagPrototyped, isOptimized: false, variables: !118)
!183 = !DISubroutineType(types: !184)
!184 = !{!64, !56, !56}
!185 = distinct !DISubprogram(name: "Force_Update_Sent_Recv_Log", scope: !115, file: !115, line: 1920, type: !120, isLocal: false, isDefinition: true, scopeLine: 1921, isOptimized: false, variables: !118)
!186 = !{!187, !188, !189, !190, !191, !193, !194, !195, !196, !197, !198, !211, !215, !217, !218, !219, !220, !224, !239, !240, !241}
!187 = !DIGlobalVariable(name: "state", scope: !0, file: !115, line: 64, type: !64, isLocal: false, isDefinition: true, variable: i32* @state)
!188 = !DIGlobalVariable(name: "pasv", scope: !0, file: !115, line: 67, type: !47, isLocal: false, isDefinition: true, variable: i8* @pasv)
!189 = !DIGlobalVariable(name: "philename", scope: !0, file: !115, line: 70, type: !56, isLocal: false, isDefinition: true, variable: i8** @philename)
!190 = !DIGlobalVariable(name: "offset", scope: !0, file: !115, line: 71, type: !72, isLocal: false, isDefinition: true, variable: i64* @offset)
!191 = !DIGlobalVariable(name: "xfertype", scope: !0, file: !115, line: 72, type: !192, isLocal: false, isDefinition: true, variable: i16* @xfertype)
!192 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!193 = !DIGlobalVariable(name: "ratio_send", scope: !0, file: !115, line: 73, type: !64, isLocal: false, isDefinition: true, variable: i32* @ratio_send)
!194 = !DIGlobalVariable(name: "ratio_recv", scope: !0, file: !115, line: 73, type: !64, isLocal: false, isDefinition: true, variable: i32* @ratio_recv)
!195 = !DIGlobalVariable(name: "bytes_sent", scope: !0, file: !115, line: 75, type: !105, isLocal: false, isDefinition: true, variable: double* @bytes_sent)
!196 = !DIGlobalVariable(name: "bytes_recvd", scope: !0, file: !115, line: 75, type: !105, isLocal: false, isDefinition: true, variable: double* @bytes_recvd)
!197 = !DIGlobalVariable(name: "epsvall", scope: !0, file: !115, line: 76, type: !64, isLocal: false, isDefinition: true, variable: i32* @epsvall)
!198 = !DIGlobalVariable(name: "subcmds", scope: !171, file: !115, line: 1684, type: !199, isLocal: true, isDefinition: true, variable: [4 x %struct.command]* @command_site.subcmds)
!199 = !DICompositeType(tag: DW_TAG_array_type, baseType: !200, size: 1024, align: 64, elements: !209)
!200 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !201)
!201 = !DICompositeType(tag: DW_TAG_structure_type, name: "command", file: !16, line: 73, size: 256, align: 64, elements: !202)
!202 = !{!203, !204, !205, !207, !208}
!203 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !201, file: !16, line: 74, baseType: !56, size: 64, align: 64)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "syntax", scope: !201, file: !16, line: 75, baseType: !56, size: 64, align: 64, offset: 64)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "function", scope: !201, file: !16, line: 76, baseType: !206, size: 64, align: 64, offset: 128)
!206 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !128, size: 64, align: 64)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "state_needed", scope: !201, file: !16, line: 77, baseType: !47, size: 8, align: 8, offset: 192)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "showinfeat", scope: !201, file: !16, line: 78, baseType: !47, size: 8, align: 8, offset: 200)
!209 = !{!210}
!210 = !DISubrange(count: 4)
!211 = !DIGlobalVariable(name: "commands", scope: !0, file: !115, line: 1722, type: !212, isLocal: false, isDefinition: true, variable: [40 x %struct.command]* @commands)
!212 = !DICompositeType(tag: DW_TAG_array_type, baseType: !200, size: 10240, align: 64, elements: !213)
!213 = !{!214}
!214 = !DISubrange(count: 40)
!215 = !DIGlobalVariable(name: "configpath", scope: !0, file: !216, line: 25, type: !56, isLocal: false, isDefinition: true, variable: i8** @configpath)
!216 = !DIFile(filename: "./main.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!217 = !DIGlobalVariable(name: "daemonmode", scope: !0, file: !216, line: 26, type: !64, isLocal: false, isDefinition: true, variable: i32* @daemonmode)
!218 = !DIGlobalVariable(name: "pre_write_script", scope: !0, file: !216, line: 29, type: !56, isLocal: false, isDefinition: true, variable: i8** @pre_write_script)
!219 = !DIGlobalVariable(name: "post_write_script", scope: !0, file: !216, line: 30, type: !56, isLocal: false, isDefinition: true, variable: i8** @post_write_script)
!220 = !DIGlobalVariable(name: "user", scope: !0, file: !115, line: 65, type: !221, isLocal: false, isDefinition: true, variable: [31 x i8]* @user)
!221 = !DICompositeType(tag: DW_TAG_array_type, baseType: !47, size: 248, align: 8, elements: !222)
!222 = !{!223}
!223 = !DISubrange(count: 31)
!224 = !DIGlobalVariable(name: "sa", scope: !0, file: !115, line: 66, type: !225, isLocal: false, isDefinition: true, variable: %struct.sockaddr_in* @sa)
!225 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_in", file: !58, line: 237, size: 128, align: 32, elements: !226)
!226 = !{!227, !228, !231, !235}
!227 = !DIDerivedType(tag: DW_TAG_member, name: "sin_family", scope: !225, file: !58, line: 239, baseType: !42, size: 16, align: 16)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "sin_port", scope: !225, file: !58, line: 240, baseType: !229, size: 16, align: 16, offset: 16)
!229 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_port_t", file: !58, line: 117, baseType: !230)
!230 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !60, line: 49, baseType: !44)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "sin_addr", scope: !225, file: !58, line: 241, baseType: !232, size: 32, align: 32, offset: 32)
!232 = !DICompositeType(tag: DW_TAG_structure_type, name: "in_addr", file: !58, line: 31, size: 32, align: 32, elements: !233)
!233 = !{!234}
!234 = !DIDerivedType(tag: DW_TAG_member, name: "s_addr", scope: !232, file: !58, line: 33, baseType: !57, size: 32, align: 32)
!235 = !DIDerivedType(tag: DW_TAG_member, name: "sin_zero", scope: !225, file: !58, line: 244, baseType: !236, size: 64, align: 8, offset: 64)
!236 = !DICompositeType(tag: DW_TAG_array_type, baseType: !65, size: 64, align: 8, elements: !237)
!237 = !{!238}
!238 = !DISubrange(count: 8)
!239 = !DIGlobalVariable(name: "sock", scope: !0, file: !115, line: 68, type: !64, isLocal: false, isDefinition: true, variable: i32* @sock)
!240 = !DIGlobalVariable(name: "pasvsock", scope: !0, file: !115, line: 69, type: !64, isLocal: false, isDefinition: true, variable: i32* @pasvsock)
!241 = !DIGlobalVariable(name: "xfer_bufsize", scope: !0, file: !115, line: 77, type: !64, isLocal: false, isDefinition: true, variable: i32* @xfer_bufsize)
!242 = !{i32 2, !"Dwarf Version", i32 4}
!243 = !{i32 2, !"Debug Info Version", i32 3}
!244 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!245 = !DILocalVariable(name: "success", arg: 1, scope: !114, file: !115, line: 80, type: !47)
!246 = !DIExpression()
!247 = !DILocation(line: 80, column: 26, scope: !114)
!248 = !DILocalVariable(name: "format", arg: 2, scope: !114, file: !115, line: 80, type: !56)
!249 = !DILocation(line: 80, column: 41, scope: !114)
!250 = !DILocalVariable(name: "buffer", scope: !114, file: !115, line: 82, type: !251)
!251 = !DICompositeType(tag: DW_TAG_array_type, baseType: !47, size: 4096, align: 8, elements: !252)
!252 = !{!253}
!253 = !DISubrange(count: 512)
!254 = !DILocation(line: 82, column: 10, scope: !114)
!255 = !DILocalVariable(name: "val", scope: !114, file: !115, line: 83, type: !256)
!256 = !DIDerivedType(tag: DW_TAG_typedef, name: "va_list", file: !257, line: 79, baseType: !258)
!257 = !DIFile(filename: "/usr/include/stdio.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!258 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gnuc_va_list", file: !259, line: 50, baseType: !260)
!259 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stdarg.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!260 = !DIDerivedType(tag: DW_TAG_typedef, name: "__builtin_va_list", file: !1, line: 83, baseType: !261)
!261 = !DICompositeType(tag: DW_TAG_array_type, baseType: !262, size: 192, align: 64, elements: !268)
!262 = !DICompositeType(tag: DW_TAG_structure_type, name: "__va_list_tag", file: !1, line: 83, size: 192, align: 64, elements: !263)
!263 = !{!264, !265, !266, !267}
!264 = !DIDerivedType(tag: DW_TAG_member, name: "gp_offset", scope: !262, file: !1, line: 83, baseType: !55, size: 32, align: 32)
!265 = !DIDerivedType(tag: DW_TAG_member, name: "fp_offset", scope: !262, file: !1, line: 83, baseType: !55, size: 32, align: 32, offset: 32)
!266 = !DIDerivedType(tag: DW_TAG_member, name: "overflow_arg_area", scope: !262, file: !1, line: 83, baseType: !36, size: 64, align: 64, offset: 64)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "reg_save_area", scope: !262, file: !1, line: 83, baseType: !36, size: 64, align: 64, offset: 128)
!268 = !{!269}
!269 = !DISubrange(count: 1)
!270 = !DILocation(line: 83, column: 13, scope: !114)
!271 = !DILocation(line: 84, column: 5, scope: !114)
!272 = !DILocation(line: 85, column: 15, scope: !114)
!273 = !DILocation(line: 85, column: 39, scope: !114)
!274 = !DILocation(line: 85, column: 47, scope: !114)
!275 = !DILocation(line: 85, column: 5, scope: !114)
!276 = !DILocation(line: 86, column: 5, scope: !114)
!277 = !DILocation(line: 87, column: 13, scope: !114)
!278 = !DILocation(line: 87, column: 31, scope: !114)
!279 = !DILocation(line: 87, column: 5, scope: !114)
!280 = !DILocation(line: 88, column: 13, scope: !114)
!281 = !DILocation(line: 88, column: 5, scope: !114)
!282 = !DILocation(line: 89, column: 24, scope: !114)
!283 = !DILocation(line: 89, column: 39, scope: !114)
!284 = !DILocation(line: 89, column: 5, scope: !114)
!285 = !DILocation(line: 90, column: 1, scope: !114)
!286 = !DILocalVariable(name: "um", scope: !119, file: !115, line: 94, type: !64)
!287 = !DILocation(line: 94, column: 9, scope: !119)
!288 = !DILocalVariable(name: "get_um", scope: !119, file: !115, line: 95, type: !72)
!289 = !DILocation(line: 95, column: 19, scope: !119)
!290 = !DILocalVariable(name: "foo", scope: !119, file: !115, line: 96, type: !56)
!291 = !DILocation(line: 96, column: 11, scope: !119)
!292 = !DILocation(line: 96, column: 17, scope: !119)
!293 = !DILocation(line: 97, column: 10, scope: !294)
!294 = distinct !DILexicalBlock(scope: !119, file: !115, line: 97, column: 9)
!295 = !DILocation(line: 97, column: 9, scope: !119)
!296 = !DILocation(line: 98, column: 12, scope: !294)
!297 = !DILocation(line: 98, column: 9, scope: !294)
!298 = !DILocation(line: 101, column: 26, scope: !299)
!299 = distinct !DILexicalBlock(scope: !294, file: !115, line: 100, column: 5)
!300 = !DILocation(line: 101, column: 18, scope: !299)
!301 = !DILocation(line: 101, column: 16, scope: !299)
!302 = !DILocation(line: 102, column: 13, scope: !303)
!303 = distinct !DILexicalBlock(scope: !299, file: !115, line: 102, column: 13)
!304 = !DILocation(line: 102, column: 20, scope: !303)
!305 = !DILocation(line: 102, column: 13, scope: !299)
!306 = !DILocation(line: 103, column: 17, scope: !303)
!307 = !DILocation(line: 103, column: 15, scope: !303)
!308 = !DILocation(line: 103, column: 12, scope: !303)
!309 = !DILocation(line: 106, column: 12, scope: !310)
!310 = distinct !DILexicalBlock(scope: !303, file: !115, line: 105, column: 9)
!311 = !DILocation(line: 107, column: 15, scope: !310)
!312 = !DILocation(line: 110, column: 11, scope: !119)
!313 = !DILocation(line: 110, column: 5, scope: !119)
!314 = !DILocation(line: 111, column: 1, scope: !119)
!315 = !DILocalVariable(name: "sock", arg: 1, scope: !122, file: !115, line: 113, type: !64)
!316 = !DILocation(line: 113, column: 23, scope: !122)
!317 = !DILocalVariable(name: "on", scope: !122, file: !115, line: 115, type: !64)
!318 = !DILocation(line: 115, column: 9, scope: !122)
!319 = !DILocation(line: 123, column: 13, scope: !122)
!320 = !DILocation(line: 123, column: 45, scope: !122)
!321 = !DILocation(line: 123, column: 2, scope: !122)
!322 = !DILocation(line: 126, column: 13, scope: !122)
!323 = !DILocation(line: 126, column: 45, scope: !122)
!324 = !DILocation(line: 126, column: 2, scope: !122)
!325 = !DILocation(line: 129, column: 5, scope: !122)
!326 = !DILocation(line: 130, column: 13, scope: !122)
!327 = !DILocation(line: 130, column: 42, scope: !122)
!328 = !DILocation(line: 130, column: 2, scope: !122)
!329 = !DILocation(line: 132, column: 1, scope: !122)
!330 = !DILocalVariable(name: "foo", scope: !123, file: !115, line: 136, type: !38)
!331 = !DILocation(line: 136, column: 18, scope: !123)
!332 = !DILocalVariable(name: "local", scope: !123, file: !115, line: 137, type: !225)
!333 = !DILocation(line: 137, column: 21, scope: !123)
!334 = !DILocalVariable(name: "namelen", scope: !123, file: !115, line: 138, type: !51)
!335 = !DILocation(line: 138, column: 12, scope: !123)
!336 = !DILocalVariable(name: "curuid", scope: !123, file: !115, line: 139, type: !64)
!337 = !DILocation(line: 139, column: 9, scope: !123)
!338 = !DILocation(line: 139, column: 18, scope: !123)
!339 = !DILocation(line: 141, column: 2, scope: !123)
!340 = !DILocation(line: 142, column: 2, scope: !123)
!341 = !DILocation(line: 144, column: 6, scope: !342)
!342 = distinct !DILexicalBlock(scope: !123, file: !115, line: 144, column: 6)
!343 = !DILocation(line: 144, column: 6, scope: !123)
!344 = !DILocation(line: 145, column: 17, scope: !345)
!345 = distinct !DILexicalBlock(scope: !342, file: !115, line: 144, column: 12)
!346 = !DILocation(line: 145, column: 27, scope: !345)
!347 = !DILocation(line: 145, column: 10, scope: !345)
!348 = !DILocation(line: 145, column: 8, scope: !345)
!349 = !DILocation(line: 146, column: 7, scope: !350)
!350 = distinct !DILexicalBlock(scope: !345, file: !115, line: 146, column: 7)
!351 = !DILocation(line: 146, column: 12, scope: !350)
!352 = !DILocation(line: 146, column: 7, scope: !345)
!353 = !DILocation(line: 148, column: 31, scope: !354)
!354 = distinct !DILexicalBlock(scope: !350, file: !115, line: 146, column: 19)
!355 = !DILocation(line: 148, column: 22, scope: !356)
!356 = !DILexicalBlockFile(scope: !354, file: !115, discriminator: 1)
!357 = !DILocation(line: 147, column: 13, scope: !354)
!358 = !DILocation(line: 149, column: 4, scope: !354)
!359 = !DILocation(line: 151, column: 15, scope: !345)
!360 = !DILocation(line: 151, column: 9, scope: !345)
!361 = !DILocation(line: 152, column: 22, scope: !345)
!362 = !DILocation(line: 152, column: 9, scope: !345)
!363 = !DILocation(line: 153, column: 2, scope: !345)
!364 = !DILocation(line: 154, column: 10, scope: !365)
!365 = distinct !DILexicalBlock(scope: !342, file: !115, line: 153, column: 9)
!366 = !DILocation(line: 154, column: 8, scope: !365)
!367 = !DILocation(line: 155, column: 22, scope: !365)
!368 = !DILocation(line: 155, column: 9, scope: !365)
!369 = !DILocation(line: 156, column: 41, scope: !365)
!370 = !DILocation(line: 156, column: 9, scope: !365)
!371 = !DILocation(line: 156, column: 18, scope: !365)
!372 = !DILocation(line: 156, column: 25, scope: !365)
!373 = !DILocation(line: 157, column: 9, scope: !365)
!374 = !DILocation(line: 157, column: 20, scope: !365)
!375 = !DILocation(line: 158, column: 25, scope: !376)
!376 = distinct !DILexicalBlock(scope: !365, file: !115, line: 158, column: 13)
!377 = !DILocation(line: 158, column: 14, scope: !378)
!378 = !DILexicalBlockFile(scope: !376, file: !115, discriminator: 1)
!379 = !DILocation(line: 158, column: 14, scope: !376)
!380 = !DILocation(line: 158, column: 13, scope: !365)
!381 = !DILocation(line: 159, column: 13, scope: !382)
!382 = distinct !DILexicalBlock(scope: !376, file: !115, line: 158, column: 65)
!383 = !DILocation(line: 160, column: 30, scope: !382)
!384 = !DILocation(line: 160, column: 19, scope: !382)
!385 = !DILocation(line: 160, column: 28, scope: !382)
!386 = !DILocation(line: 161, column: 9, scope: !382)
!387 = !DILocation(line: 162, column: 12, scope: !388)
!388 = distinct !DILexicalBlock(scope: !365, file: !115, line: 162, column: 7)
!389 = !DILocation(line: 162, column: 18, scope: !388)
!390 = !DILocation(line: 162, column: 7, scope: !388)
!391 = !DILocation(line: 162, column: 61, scope: !388)
!392 = !DILocation(line: 162, column: 7, scope: !365)
!393 = !DILocation(line: 164, column: 15, scope: !394)
!394 = distinct !DILexicalBlock(scope: !388, file: !115, line: 162, column: 66)
!395 = !DILocation(line: 164, column: 6, scope: !396)
!396 = !DILexicalBlockFile(scope: !394, file: !115, discriminator: 1)
!397 = !DILocation(line: 163, column: 4, scope: !394)
!398 = !DILocation(line: 165, column: 4, scope: !394)
!399 = !DILocation(line: 167, column: 25, scope: !400)
!400 = distinct !DILexicalBlock(scope: !365, file: !115, line: 167, column: 13)
!401 = !DILocation(line: 167, column: 14, scope: !402)
!402 = !DILexicalBlockFile(scope: !400, file: !115, discriminator: 1)
!403 = !DILocation(line: 167, column: 14, scope: !400)
!404 = !DILocation(line: 167, column: 13, scope: !365)
!405 = !DILocation(line: 168, column: 21, scope: !400)
!406 = !DILocation(line: 168, column: 13, scope: !400)
!407 = !DILocation(line: 169, column: 17, scope: !365)
!408 = !DILocation(line: 170, column: 15, scope: !409)
!409 = distinct !DILexicalBlock(scope: !365, file: !115, line: 170, column: 7)
!410 = !DILocation(line: 170, column: 21, scope: !409)
!411 = !DILocation(line: 170, column: 7, scope: !409)
!412 = !DILocation(line: 170, column: 58, scope: !409)
!413 = !DILocation(line: 170, column: 7, scope: !365)
!414 = !DILocation(line: 172, column: 41, scope: !415)
!415 = distinct !DILexicalBlock(scope: !409, file: !115, line: 170, column: 65)
!416 = !DILocation(line: 172, column: 32, scope: !417)
!417 = !DILexicalBlockFile(scope: !415, file: !115, discriminator: 1)
!418 = !DILocation(line: 171, column: 4, scope: !415)
!419 = !DILocation(line: 173, column: 4, scope: !415)
!420 = !DILocation(line: 177, column: 17, scope: !123)
!421 = !DILocation(line: 177, column: 26, scope: !123)
!422 = !DILocation(line: 176, column: 2, scope: !123)
!423 = !DILocation(line: 178, column: 2, scope: !123)
!424 = !DILocation(line: 179, column: 1, scope: !123)
!425 = !DILocalVariable(name: "temp", scope: !126, file: !115, line: 184, type: !426)
!426 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !427, size: 64, align: 64)
!427 = !DICompositeType(tag: DW_TAG_structure_type, name: "passwd", file: !428, line: 49, size: 384, align: 64, elements: !429)
!428 = !DIFile(filename: "/usr/include/pwd.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!429 = !{!430, !431, !432, !433, !434, !435, !436}
!430 = !DIDerivedType(tag: DW_TAG_member, name: "pw_name", scope: !427, file: !428, line: 51, baseType: !56, size: 64, align: 64)
!431 = !DIDerivedType(tag: DW_TAG_member, name: "pw_passwd", scope: !427, file: !428, line: 52, baseType: !56, size: 64, align: 64, offset: 64)
!432 = !DIDerivedType(tag: DW_TAG_member, name: "pw_uid", scope: !427, file: !428, line: 53, baseType: !80, size: 32, align: 32, offset: 128)
!433 = !DIDerivedType(tag: DW_TAG_member, name: "pw_gid", scope: !427, file: !428, line: 54, baseType: !82, size: 32, align: 32, offset: 160)
!434 = !DIDerivedType(tag: DW_TAG_member, name: "pw_gecos", scope: !427, file: !428, line: 55, baseType: !56, size: 64, align: 64, offset: 192)
!435 = !DIDerivedType(tag: DW_TAG_member, name: "pw_dir", scope: !427, file: !428, line: 56, baseType: !56, size: 64, align: 64, offset: 256)
!436 = !DIDerivedType(tag: DW_TAG_member, name: "pw_shell", scope: !427, file: !428, line: 57, baseType: !56, size: 64, align: 64, offset: 320)
!437 = !DILocation(line: 184, column: 20, scope: !126)
!438 = !DILocation(line: 184, column: 27, scope: !126)
!439 = !DILocation(line: 185, column: 9, scope: !440)
!440 = distinct !DILexicalBlock(scope: !126, file: !115, line: 185, column: 9)
!441 = !DILocation(line: 185, column: 9, scope: !126)
!442 = !DILocation(line: 186, column: 35, scope: !443)
!443 = distinct !DILexicalBlock(scope: !440, file: !115, line: 185, column: 15)
!444 = !DILocation(line: 186, column: 41, scope: !443)
!445 = !DILocation(line: 186, column: 28, scope: !443)
!446 = !DILocation(line: 186, column: 26, scope: !443)
!447 = !DILocation(line: 187, column: 37, scope: !443)
!448 = !DILocation(line: 187, column: 43, scope: !443)
!449 = !DILocation(line: 187, column: 30, scope: !443)
!450 = !DILocation(line: 187, column: 28, scope: !443)
!451 = !DILocation(line: 188, column: 27, scope: !443)
!452 = !DILocation(line: 188, column: 33, scope: !443)
!453 = !DILocation(line: 188, column: 25, scope: !443)
!454 = !DILocation(line: 189, column: 27, scope: !443)
!455 = !DILocation(line: 189, column: 33, scope: !443)
!456 = !DILocation(line: 189, column: 25, scope: !443)
!457 = !DILocation(line: 190, column: 36, scope: !443)
!458 = !DILocation(line: 190, column: 42, scope: !443)
!459 = !DILocation(line: 190, column: 29, scope: !443)
!460 = !DILocation(line: 190, column: 27, scope: !443)
!461 = !DILocation(line: 191, column: 34, scope: !443)
!462 = !DILocation(line: 191, column: 40, scope: !443)
!463 = !DILocation(line: 191, column: 27, scope: !443)
!464 = !DILocation(line: 191, column: 25, scope: !443)
!465 = !DILocation(line: 192, column: 36, scope: !443)
!466 = !DILocation(line: 192, column: 42, scope: !443)
!467 = !DILocation(line: 192, column: 29, scope: !443)
!468 = !DILocation(line: 192, column: 27, scope: !443)
!469 = !DILocation(line: 193, column: 22, scope: !443)
!470 = !DILocation(line: 194, column: 5, scope: !443)
!471 = !DILocation(line: 196, column: 1, scope: !126)
!472 = !DILocalVariable(name: "username", arg: 1, scope: !127, file: !115, line: 198, type: !56)
!473 = !DILocation(line: 198, column: 25, scope: !127)
!474 = !DILocalVariable(name: "alias", scope: !127, file: !115, line: 200, type: !56)
!475 = !DILocation(line: 200, column: 8, scope: !127)
!476 = !DILocation(line: 201, column: 6, scope: !477)
!477 = distinct !DILexicalBlock(scope: !127, file: !115, line: 201, column: 6)
!478 = !DILocation(line: 201, column: 6, scope: !127)
!479 = !DILocation(line: 202, column: 3, scope: !480)
!480 = distinct !DILexicalBlock(scope: !477, file: !115, line: 201, column: 13)
!481 = !DILocation(line: 203, column: 3, scope: !480)
!482 = !DILocation(line: 205, column: 18, scope: !127)
!483 = !DILocation(line: 205, column: 2, scope: !127)
!484 = !DILocation(line: 206, column: 22, scope: !127)
!485 = !DILocation(line: 207, column: 19, scope: !127)
!486 = !DILocation(line: 207, column: 8, scope: !127)
!487 = !DILocation(line: 208, column: 22, scope: !127)
!488 = !DILocation(line: 209, column: 6, scope: !489)
!489 = distinct !DILexicalBlock(scope: !127, file: !115, line: 209, column: 6)
!490 = !DILocation(line: 209, column: 15, scope: !489)
!491 = !DILocation(line: 209, column: 6, scope: !127)
!492 = !DILocation(line: 210, column: 19, scope: !489)
!493 = !DILocation(line: 210, column: 3, scope: !489)
!494 = !DILocation(line: 211, column: 9, scope: !127)
!495 = !DILocation(line: 212, column: 22, scope: !127)
!496 = !DILocation(line: 216, column: 5, scope: !127)
!497 = !DILocation(line: 217, column: 18, scope: !498)
!498 = distinct !DILexicalBlock(scope: !127, file: !115, line: 217, column: 6)
!499 = !DILocation(line: 217, column: 7, scope: !500)
!500 = !DILexicalBlockFile(scope: !498, file: !115, discriminator: 1)
!501 = !DILocation(line: 217, column: 7, scope: !498)
!502 = !DILocation(line: 217, column: 6, scope: !127)
!503 = !DILocation(line: 219, column: 23, scope: !504)
!504 = distinct !DILexicalBlock(scope: !498, file: !115, line: 218, column: 9)
!505 = !DILocation(line: 220, column: 17, scope: !504)
!506 = !DILocation(line: 222, column: 9, scope: !504)
!507 = !DILocation(line: 224, column: 9, scope: !508)
!508 = distinct !DILexicalBlock(scope: !498, file: !115, line: 223, column: 7)
!509 = !DILocation(line: 225, column: 3, scope: !508)
!510 = !DILocation(line: 227, column: 1, scope: !127)
!511 = !DILocalVariable(name: "password", arg: 1, scope: !130, file: !115, line: 229, type: !56)
!512 = !DILocation(line: 229, column: 25, scope: !130)
!513 = !DILocation(line: 231, column: 6, scope: !514)
!514 = distinct !DILexicalBlock(scope: !130, file: !115, line: 231, column: 6)
!515 = !DILocation(line: 231, column: 12, scope: !514)
!516 = !DILocation(line: 231, column: 6, scope: !130)
!517 = !DILocation(line: 232, column: 3, scope: !518)
!518 = distinct !DILexicalBlock(scope: !514, file: !115, line: 231, column: 26)
!519 = !DILocation(line: 233, column: 3, scope: !518)
!520 = !DILocation(line: 235, column: 18, scope: !521)
!521 = distinct !DILexicalBlock(scope: !130, file: !115, line: 235, column: 6)
!522 = !DILocation(line: 235, column: 6, scope: !521)
!523 = !DILocation(line: 235, column: 6, scope: !130)
!524 = !DILocation(line: 236, column: 3, scope: !525)
!525 = distinct !DILexicalBlock(scope: !521, file: !115, line: 235, column: 29)
!526 = !DILocation(line: 237, column: 3, scope: !525)
!527 = !DILocation(line: 239, column: 23, scope: !525)
!528 = !DILocation(line: 240, column: 17, scope: !525)
!529 = !DILocation(line: 242, column: 1, scope: !130)
!530 = !DILocalVariable(name: "params", arg: 1, scope: !131, file: !115, line: 244, type: !56)
!531 = !DILocation(line: 244, column: 24, scope: !131)
!532 = !DILocalVariable(name: "my_cwd", scope: !131, file: !115, line: 246, type: !56)
!533 = !DILocation(line: 246, column: 12, scope: !131)
!534 = !DILocation(line: 248, column: 15, scope: !131)
!535 = !DILocation(line: 248, column: 13, scope: !131)
!536 = !DILocation(line: 249, column: 10, scope: !537)
!537 = distinct !DILexicalBlock(scope: !131, file: !115, line: 249, column: 10)
!538 = !DILocation(line: 249, column: 10, scope: !131)
!539 = !DILocation(line: 251, column: 85, scope: !540)
!540 = distinct !DILexicalBlock(scope: !537, file: !115, line: 250, column: 6)
!541 = !DILocation(line: 251, column: 10, scope: !540)
!542 = !DILocation(line: 252, column: 15, scope: !540)
!543 = !DILocation(line: 252, column: 10, scope: !540)
!544 = !DILocation(line: 253, column: 6, scope: !540)
!545 = !DILocation(line: 254, column: 1, scope: !131)
!546 = !DILocalVariable(name: "params", arg: 1, scope: !132, file: !115, line: 257, type: !56)
!547 = !DILocation(line: 257, column: 25, scope: !132)
!548 = !DILocation(line: 259, column: 11, scope: !549)
!549 = distinct !DILexicalBlock(scope: !132, file: !115, line: 259, column: 9)
!550 = !DILocation(line: 259, column: 10, scope: !549)
!551 = !DILocation(line: 259, column: 18, scope: !549)
!552 = !DILocation(line: 259, column: 26, scope: !549)
!553 = !DILocation(line: 259, column: 31, scope: !554)
!554 = !DILexicalBlockFile(scope: !549, file: !115, discriminator: 1)
!555 = !DILocation(line: 259, column: 30, scope: !554)
!556 = !DILocation(line: 259, column: 38, scope: !554)
!557 = !DILocation(line: 259, column: 9, scope: !554)
!558 = !DILocation(line: 260, column: 9, scope: !559)
!559 = distinct !DILexicalBlock(scope: !549, file: !115, line: 259, column: 47)
!560 = !DILocation(line: 261, column: 18, scope: !559)
!561 = !DILocation(line: 262, column: 5, scope: !559)
!562 = !DILocation(line: 262, column: 18, scope: !563)
!563 = !DILexicalBlockFile(scope: !564, file: !115, discriminator: 1)
!564 = distinct !DILexicalBlock(scope: !549, file: !115, line: 262, column: 16)
!565 = !DILocation(line: 262, column: 17, scope: !563)
!566 = !DILocation(line: 262, column: 25, scope: !563)
!567 = !DILocation(line: 262, column: 33, scope: !563)
!568 = !DILocation(line: 262, column: 38, scope: !569)
!569 = !DILexicalBlockFile(scope: !564, file: !115, discriminator: 2)
!570 = !DILocation(line: 262, column: 37, scope: !569)
!571 = !DILocation(line: 262, column: 45, scope: !569)
!572 = !DILocation(line: 262, column: 16, scope: !569)
!573 = !DILocation(line: 263, column: 8, scope: !574)
!574 = distinct !DILexicalBlock(scope: !564, file: !115, line: 262, column: 54)
!575 = !DILocation(line: 264, column: 18, scope: !574)
!576 = !DILocation(line: 265, column: 5, scope: !574)
!577 = !DILocation(line: 266, column: 69, scope: !564)
!578 = !DILocation(line: 266, column: 68, scope: !564)
!579 = !DILocation(line: 266, column: 9, scope: !564)
!580 = !DILocation(line: 267, column: 1, scope: !132)
!581 = !DILocalVariable(name: "params", arg: 1, scope: !133, file: !115, line: 269, type: !56)
!582 = !DILocation(line: 269, column: 25, scope: !133)
!583 = !DILocalVariable(name: "a0", scope: !133, file: !115, line: 270, type: !72)
!584 = !DILocation(line: 270, column: 17, scope: !133)
!585 = !DILocalVariable(name: "a1", scope: !133, file: !115, line: 270, type: !72)
!586 = !DILocation(line: 270, column: 21, scope: !133)
!587 = !DILocalVariable(name: "a2", scope: !133, file: !115, line: 270, type: !72)
!588 = !DILocation(line: 270, column: 25, scope: !133)
!589 = !DILocalVariable(name: "a3", scope: !133, file: !115, line: 270, type: !72)
!590 = !DILocation(line: 270, column: 29, scope: !133)
!591 = !DILocalVariable(name: "p0", scope: !133, file: !115, line: 270, type: !72)
!592 = !DILocation(line: 270, column: 33, scope: !133)
!593 = !DILocalVariable(name: "p1", scope: !133, file: !115, line: 270, type: !72)
!594 = !DILocation(line: 270, column: 37, scope: !133)
!595 = !DILocalVariable(name: "addr", scope: !133, file: !115, line: 270, type: !72)
!596 = !DILocation(line: 270, column: 41, scope: !133)
!597 = !DILocation(line: 271, column: 7, scope: !598)
!598 = distinct !DILexicalBlock(scope: !133, file: !115, line: 271, column: 7)
!599 = !DILocation(line: 271, column: 7, scope: !133)
!600 = !DILocation(line: 272, column: 7, scope: !601)
!601 = distinct !DILexicalBlock(scope: !598, file: !115, line: 271, column: 16)
!602 = !DILocation(line: 273, column: 7, scope: !601)
!603 = !DILocation(line: 275, column: 10, scope: !133)
!604 = !DILocation(line: 275, column: 3, scope: !133)
!605 = !DILocation(line: 276, column: 17, scope: !133)
!606 = !DILocation(line: 276, column: 20, scope: !133)
!607 = !DILocation(line: 276, column: 30, scope: !133)
!608 = !DILocation(line: 276, column: 33, scope: !133)
!609 = !DILocation(line: 276, column: 27, scope: !133)
!610 = !DILocation(line: 276, column: 43, scope: !133)
!611 = !DILocation(line: 276, column: 46, scope: !133)
!612 = !DILocation(line: 276, column: 40, scope: !133)
!613 = !DILocation(line: 276, column: 54, scope: !133)
!614 = !DILocation(line: 276, column: 52, scope: !133)
!615 = !DILocation(line: 276, column: 16, scope: !133)
!616 = !DILocation(line: 276, column: 10, scope: !133)
!617 = !DILocation(line: 276, column: 8, scope: !133)
!618 = !DILocation(line: 277, column: 7, scope: !619)
!619 = distinct !DILexicalBlock(scope: !133, file: !115, line: 277, column: 6)
!620 = !DILocation(line: 277, column: 35, scope: !619)
!621 = !DILocation(line: 277, column: 15, scope: !619)
!622 = !DILocation(line: 277, column: 12, scope: !619)
!623 = !DILocation(line: 277, column: 43, scope: !619)
!624 = !DILocation(line: 277, column: 59, scope: !625)
!625 = !DILexicalBlockFile(scope: !619, file: !115, discriminator: 1)
!626 = !DILocation(line: 277, column: 47, scope: !627)
!627 = !DILexicalBlockFile(scope: !625, file: !115, discriminator: 2)
!628 = !DILocation(line: 277, column: 47, scope: !625)
!629 = !DILocation(line: 277, column: 6, scope: !625)
!630 = !DILocation(line: 278, column: 7, scope: !631)
!631 = distinct !DILexicalBlock(scope: !619, file: !115, line: 277, column: 102)
!632 = !DILocation(line: 279, column: 7, scope: !631)
!633 = !DILocation(line: 281, column: 24, scope: !133)
!634 = !DILocation(line: 281, column: 22, scope: !133)
!635 = !DILocation(line: 282, column: 24, scope: !133)
!636 = !DILocation(line: 282, column: 27, scope: !133)
!637 = !DILocation(line: 282, column: 35, scope: !133)
!638 = !DILocation(line: 282, column: 33, scope: !133)
!639 = !DILocation(line: 282, column: 23, scope: !133)
!640 = !DILocation(line: 282, column: 17, scope: !133)
!641 = !DILocation(line: 282, column: 15, scope: !133)
!642 = !DILocation(line: 283, column: 7, scope: !643)
!643 = distinct !DILexicalBlock(scope: !133, file: !115, line: 283, column: 7)
!644 = !DILocation(line: 283, column: 7, scope: !133)
!645 = !DILocation(line: 284, column: 11, scope: !646)
!646 = distinct !DILexicalBlock(scope: !643, file: !115, line: 283, column: 13)
!647 = !DILocation(line: 284, column: 5, scope: !646)
!648 = !DILocation(line: 285, column: 10, scope: !646)
!649 = !DILocation(line: 286, column: 3, scope: !646)
!650 = !DILocation(line: 288, column: 12, scope: !133)
!651 = !DILocation(line: 288, column: 16, scope: !133)
!652 = !DILocation(line: 288, column: 20, scope: !133)
!653 = !DILocation(line: 288, column: 24, scope: !133)
!654 = !DILocation(line: 288, column: 29, scope: !133)
!655 = !DILocation(line: 288, column: 32, scope: !133)
!656 = !DILocation(line: 288, column: 40, scope: !133)
!657 = !DILocation(line: 288, column: 38, scope: !133)
!658 = !DILocation(line: 287, column: 3, scope: !133)
!659 = !DILocation(line: 289, column: 1, scope: !133)
!660 = !DILocation(line: 289, column: 1, scope: !661)
!661 = !DILexicalBlockFile(scope: !133, file: !115, discriminator: 1)
!662 = !DILocalVariable(name: "params", arg: 1, scope: !134, file: !115, line: 291, type: !56)
!663 = !DILocation(line: 291, column: 25, scope: !134)
!664 = !DILocalVariable(name: "delim", scope: !134, file: !115, line: 292, type: !47)
!665 = !DILocation(line: 292, column: 10, scope: !134)
!666 = !DILocalVariable(name: "af", scope: !134, file: !115, line: 293, type: !64)
!667 = !DILocation(line: 293, column: 9, scope: !134)
!668 = !DILocalVariable(name: "addr", scope: !134, file: !115, line: 294, type: !669)
!669 = !DICompositeType(tag: DW_TAG_array_type, baseType: !47, size: 408, align: 8, elements: !670)
!670 = !{!671}
!671 = !DISubrange(count: 51)
!672 = !DILocation(line: 294, column: 10, scope: !134)
!673 = !DILocalVariable(name: "foo", scope: !134, file: !115, line: 295, type: !674)
!674 = !DICompositeType(tag: DW_TAG_array_type, baseType: !47, size: 160, align: 8, elements: !675)
!675 = !{!676}
!676 = !DISubrange(count: 20)
!677 = !DILocation(line: 295, column: 10, scope: !134)
!678 = !DILocalVariable(name: "port", scope: !134, file: !115, line: 296, type: !64)
!679 = !DILocation(line: 296, column: 9, scope: !134)
!680 = !DILocation(line: 297, column: 9, scope: !681)
!681 = distinct !DILexicalBlock(scope: !134, file: !115, line: 297, column: 9)
!682 = !DILocation(line: 297, column: 9, scope: !134)
!683 = !DILocation(line: 298, column: 9, scope: !684)
!684 = distinct !DILexicalBlock(scope: !681, file: !115, line: 297, column: 18)
!685 = !DILocation(line: 299, column: 9, scope: !684)
!686 = !DILocation(line: 301, column: 16, scope: !687)
!687 = distinct !DILexicalBlock(scope: !134, file: !115, line: 301, column: 9)
!688 = !DILocation(line: 301, column: 9, scope: !687)
!689 = !DILocation(line: 301, column: 24, scope: !687)
!690 = !DILocation(line: 301, column: 9, scope: !134)
!691 = !DILocation(line: 302, column: 9, scope: !692)
!692 = distinct !DILexicalBlock(scope: !687, file: !115, line: 301, column: 29)
!693 = !DILocation(line: 303, column: 9, scope: !692)
!694 = !DILocation(line: 305, column: 13, scope: !134)
!695 = !DILocation(line: 305, column: 11, scope: !134)
!696 = !DILocation(line: 306, column: 13, scope: !134)
!697 = !DILocation(line: 306, column: 45, scope: !134)
!698 = !DILocation(line: 306, column: 52, scope: !134)
!699 = !DILocation(line: 306, column: 59, scope: !134)
!700 = !DILocation(line: 306, column: 66, scope: !134)
!701 = !DILocation(line: 306, column: 73, scope: !134)
!702 = !DILocation(line: 306, column: 5, scope: !134)
!703 = !DILocation(line: 307, column: 16, scope: !704)
!704 = distinct !DILexicalBlock(scope: !134, file: !115, line: 307, column: 9)
!705 = !DILocation(line: 307, column: 24, scope: !704)
!706 = !DILocation(line: 307, column: 34, scope: !704)
!707 = !DILocation(line: 307, column: 9, scope: !704)
!708 = !DILocation(line: 307, column: 47, scope: !704)
!709 = !DILocation(line: 307, column: 9, scope: !134)
!710 = !DILocation(line: 308, column: 9, scope: !711)
!711 = distinct !DILexicalBlock(scope: !704, file: !115, line: 307, column: 52)
!712 = !DILocation(line: 309, column: 9, scope: !711)
!713 = !DILocation(line: 311, column: 9, scope: !714)
!714 = distinct !DILexicalBlock(scope: !134, file: !115, line: 311, column: 9)
!715 = !DILocation(line: 311, column: 12, scope: !714)
!716 = !DILocation(line: 311, column: 9, scope: !134)
!717 = !DILocation(line: 312, column: 9, scope: !718)
!718 = distinct !DILexicalBlock(scope: !714, file: !115, line: 311, column: 18)
!719 = !DILocation(line: 313, column: 9, scope: !718)
!720 = !DILocation(line: 315, column: 36, scope: !134)
!721 = !DILocation(line: 315, column: 26, scope: !134)
!722 = !DILocation(line: 315, column: 24, scope: !134)
!723 = !DILocation(line: 316, column: 22, scope: !724)
!724 = distinct !DILexicalBlock(scope: !134, file: !115, line: 316, column: 9)
!725 = !DILocation(line: 316, column: 52, scope: !724)
!726 = !DILocation(line: 316, column: 29, scope: !724)
!727 = !DILocation(line: 316, column: 60, scope: !724)
!728 = !DILocation(line: 316, column: 76, scope: !729)
!729 = !DILexicalBlockFile(scope: !724, file: !115, discriminator: 1)
!730 = !DILocation(line: 316, column: 64, scope: !731)
!731 = !DILexicalBlockFile(scope: !729, file: !115, discriminator: 2)
!732 = !DILocation(line: 316, column: 64, scope: !729)
!733 = !DILocation(line: 316, column: 9, scope: !729)
!734 = !DILocation(line: 317, column: 9, scope: !735)
!735 = distinct !DILexicalBlock(scope: !724, file: !115, line: 316, column: 119)
!736 = !DILocation(line: 318, column: 9, scope: !735)
!737 = !DILocation(line: 320, column: 25, scope: !134)
!738 = !DILocation(line: 320, column: 19, scope: !134)
!739 = !DILocation(line: 320, column: 17, scope: !134)
!740 = !DILocation(line: 321, column: 9, scope: !741)
!741 = distinct !DILexicalBlock(scope: !134, file: !115, line: 321, column: 9)
!742 = !DILocation(line: 321, column: 9, scope: !134)
!743 = !DILocation(line: 322, column: 15, scope: !744)
!744 = distinct !DILexicalBlock(scope: !741, file: !115, line: 321, column: 15)
!745 = !DILocation(line: 322, column: 9, scope: !744)
!746 = !DILocation(line: 323, column: 14, scope: !744)
!747 = !DILocation(line: 324, column: 5, scope: !744)
!748 = !DILocation(line: 325, column: 53, scope: !134)
!749 = !DILocation(line: 325, column: 59, scope: !134)
!750 = !DILocation(line: 325, column: 5, scope: !134)
!751 = !DILocation(line: 326, column: 1, scope: !134)
!752 = !DILocation(line: 326, column: 1, scope: !753)
!753 = !DILexicalBlockFile(scope: !134, file: !115, discriminator: 1)
!754 = !DILocalVariable(name: "foo", arg: 1, scope: !135, file: !115, line: 328, type: !56)
!755 = !DILocation(line: 328, column: 25, scope: !135)
!756 = !DILocalVariable(name: "a1", scope: !135, file: !115, line: 330, type: !64)
!757 = !DILocation(line: 330, column: 6, scope: !135)
!758 = !DILocalVariable(name: "a2", scope: !135, file: !115, line: 330, type: !64)
!759 = !DILocation(line: 330, column: 10, scope: !135)
!760 = !DILocalVariable(name: "a3", scope: !135, file: !115, line: 330, type: !64)
!761 = !DILocation(line: 330, column: 14, scope: !135)
!762 = !DILocalVariable(name: "a4", scope: !135, file: !115, line: 330, type: !64)
!763 = !DILocation(line: 330, column: 18, scope: !135)
!764 = !DILocalVariable(name: "namelen", scope: !135, file: !115, line: 331, type: !51)
!765 = !DILocation(line: 331, column: 19, scope: !135)
!766 = !DILocalVariable(name: "localsock", scope: !135, file: !115, line: 332, type: !225)
!767 = !DILocation(line: 332, column: 21, scope: !135)
!768 = !DILocalVariable(name: "my_override_ip", scope: !135, file: !115, line: 333, type: !56)
!769 = !DILocation(line: 333, column: 15, scope: !135)
!770 = !DILocation(line: 335, column: 9, scope: !771)
!771 = distinct !DILexicalBlock(scope: !135, file: !115, line: 335, column: 9)
!772 = !DILocation(line: 335, column: 9, scope: !135)
!773 = !DILocation(line: 336, column: 9, scope: !774)
!774 = distinct !DILexicalBlock(scope: !771, file: !115, line: 335, column: 18)
!775 = !DILocation(line: 337, column: 9, scope: !774)
!776 = !DILocation(line: 339, column: 13, scope: !135)
!777 = !DILocation(line: 339, column: 11, scope: !135)
!778 = !DILocation(line: 340, column: 21, scope: !135)
!779 = !DILocation(line: 341, column: 16, scope: !135)
!780 = !DILocation(line: 343, column: 10, scope: !781)
!781 = distinct !DILexicalBlock(scope: !135, file: !115, line: 343, column: 9)
!782 = !DILocation(line: 343, column: 44, scope: !781)
!783 = !DILocation(line: 343, column: 55, scope: !784)
!784 = !DILexicalBlockFile(scope: !781, file: !115, discriminator: 1)
!785 = !DILocation(line: 343, column: 48, scope: !786)
!786 = !DILexicalBlockFile(scope: !784, file: !115, discriminator: 2)
!787 = !DILocation(line: 343, column: 48, scope: !784)
!788 = !DILocation(line: 343, column: 9, scope: !784)
!789 = !DILocation(line: 345, column: 21, scope: !790)
!790 = distinct !DILexicalBlock(scope: !781, file: !115, line: 343, column: 91)
!791 = !DILocation(line: 346, column: 18, scope: !792)
!792 = distinct !DILexicalBlock(scope: !790, file: !115, line: 346, column: 13)
!793 = !DILocation(line: 346, column: 28, scope: !792)
!794 = !DILocation(line: 346, column: 13, scope: !792)
!795 = !DILocation(line: 346, column: 65, scope: !792)
!796 = !DILocation(line: 346, column: 13, scope: !790)
!797 = !DILocation(line: 348, column: 101, scope: !798)
!798 = distinct !DILexicalBlock(scope: !792, file: !115, line: 347, column: 9)
!799 = !DILocation(line: 348, column: 92, scope: !800)
!800 = !DILexicalBlockFile(scope: !798, file: !115, discriminator: 1)
!801 = !DILocation(line: 348, column: 13, scope: !802)
!802 = !DILexicalBlockFile(scope: !798, file: !115, discriminator: 2)
!803 = !DILocation(line: 349, column: 13, scope: !798)
!804 = !DILocation(line: 351, column: 5, scope: !790)
!805 = !DILocalVariable(name: "i", scope: !806, file: !115, line: 354, type: !64)
!806 = distinct !DILexicalBlock(scope: !781, file: !115, line: 353, column: 11)
!807 = !DILocation(line: 354, column: 13, scope: !806)
!808 = !DILocalVariable(name: "success", scope: !806, file: !115, line: 354, type: !64)
!809 = !DILocation(line: 354, column: 20, scope: !806)
!810 = !DILocalVariable(name: "port", scope: !806, file: !115, line: 354, type: !64)
!811 = !DILocation(line: 354, column: 33, scope: !806)
!812 = !DILocation(line: 355, column: 9, scope: !806)
!813 = !DILocation(line: 356, column: 34, scope: !814)
!814 = distinct !DILexicalBlock(scope: !815, file: !115, line: 355, column: 18)
!815 = distinct !DILexicalBlock(scope: !816, file: !115, line: 355, column: 9)
!816 = distinct !DILexicalBlock(scope: !806, file: !115, line: 355, column: 9)
!817 = !DILocation(line: 356, column: 70, scope: !814)
!818 = !DILocation(line: 356, column: 20, scope: !819)
!819 = !DILexicalBlockFile(scope: !814, file: !115, discriminator: 1)
!820 = !DILocation(line: 356, column: 18, scope: !814)
!821 = !DILocation(line: 357, column: 17, scope: !822)
!822 = distinct !DILexicalBlock(scope: !814, file: !115, line: 357, column: 17)
!823 = !DILocation(line: 357, column: 22, scope: !822)
!824 = !DILocation(line: 357, column: 17, scope: !814)
!825 = !DILocation(line: 358, column: 17, scope: !822)
!826 = !DILocation(line: 359, column: 33, scope: !814)
!827 = !DILocation(line: 359, column: 27, scope: !814)
!828 = !DILocation(line: 359, column: 25, scope: !814)
!829 = !DILocation(line: 360, column: 22, scope: !830)
!830 = distinct !DILexicalBlock(scope: !814, file: !115, line: 360, column: 17)
!831 = !DILocation(line: 360, column: 32, scope: !830)
!832 = !DILocation(line: 360, column: 17, scope: !830)
!833 = !DILocation(line: 360, column: 69, scope: !830)
!834 = !DILocation(line: 360, column: 17, scope: !814)
!835 = !DILocation(line: 361, column: 25, scope: !836)
!836 = distinct !DILexicalBlock(scope: !830, file: !115, line: 360, column: 75)
!837 = !DILocation(line: 365, column: 17, scope: !836)
!838 = !DILocation(line: 355, column: 9, scope: !839)
!839 = !DILexicalBlockFile(scope: !815, file: !115, discriminator: 1)
!840 = !DILocation(line: 368, column: 14, scope: !841)
!841 = distinct !DILexicalBlock(scope: !806, file: !115, line: 368, column: 13)
!842 = !DILocation(line: 368, column: 13, scope: !806)
!843 = !DILocation(line: 369, column: 13, scope: !844)
!844 = distinct !DILexicalBlock(scope: !841, file: !115, line: 368, column: 23)
!845 = !DILocation(line: 370, column: 13, scope: !844)
!846 = !DILocation(line: 372, column: 22, scope: !806)
!847 = !DILocation(line: 372, column: 9, scope: !806)
!848 = !DILocation(line: 375, column: 13, scope: !849)
!849 = distinct !DILexicalBlock(scope: !135, file: !115, line: 375, column: 6)
!850 = !DILocation(line: 375, column: 6, scope: !849)
!851 = !DILocation(line: 375, column: 6, scope: !135)
!852 = !DILocation(line: 377, column: 15, scope: !853)
!853 = distinct !DILexicalBlock(scope: !849, file: !115, line: 375, column: 27)
!854 = !DILocation(line: 377, column: 6, scope: !855)
!855 = !DILexicalBlockFile(scope: !853, file: !115, discriminator: 1)
!856 = !DILocation(line: 376, column: 3, scope: !853)
!857 = !DILocation(line: 378, column: 3, scope: !853)
!858 = !DILocation(line: 380, column: 10, scope: !135)
!859 = !DILocation(line: 381, column: 14, scope: !135)
!860 = !DILocation(line: 381, column: 24, scope: !135)
!861 = !DILocation(line: 381, column: 2, scope: !135)
!862 = !DILocation(line: 384, column: 26, scope: !135)
!863 = !DILocation(line: 384, column: 24, scope: !135)
!864 = !DILocation(line: 385, column: 13, scope: !865)
!865 = distinct !DILexicalBlock(scope: !135, file: !115, line: 385, column: 13)
!866 = !DILocation(line: 385, column: 13, scope: !135)
!867 = !DILocation(line: 387, column: 21, scope: !868)
!868 = distinct !DILexicalBlock(scope: !865, file: !115, line: 386, column: 9)
!869 = !DILocation(line: 387, column: 13, scope: !868)
!870 = !DILocation(line: 389, column: 9, scope: !868)
!871 = !DILocation(line: 392, column: 24, scope: !872)
!872 = distinct !DILexicalBlock(scope: !865, file: !115, line: 391, column: 9)
!873 = !DILocation(line: 392, column: 8, scope: !874)
!874 = !DILexicalBlockFile(scope: !872, file: !115, discriminator: 1)
!875 = !DILocation(line: 396, column: 78, scope: !135)
!876 = !DILocation(line: 396, column: 82, scope: !135)
!877 = !DILocation(line: 396, column: 86, scope: !135)
!878 = !DILocation(line: 396, column: 90, scope: !135)
!879 = !DILocation(line: 397, column: 21, scope: !135)
!880 = !DILocation(line: 397, column: 5, scope: !135)
!881 = !DILocation(line: 397, column: 31, scope: !135)
!882 = !DILocation(line: 397, column: 53, scope: !135)
!883 = !DILocation(line: 397, column: 37, scope: !884)
!884 = !DILexicalBlockFile(scope: !135, file: !115, discriminator: 1)
!885 = !DILocation(line: 397, column: 37, scope: !135)
!886 = !DILocation(line: 397, column: 63, scope: !135)
!887 = !DILocation(line: 396, column: 2, scope: !135)
!888 = !DILocation(line: 398, column: 7, scope: !135)
!889 = !DILocation(line: 399, column: 1, scope: !135)
!890 = !DILocation(line: 399, column: 1, scope: !884)
!891 = !DILocalVariable(name: "params", arg: 1, scope: !136, file: !115, line: 401, type: !56)
!892 = !DILocation(line: 401, column: 25, scope: !136)
!893 = !DILocalVariable(name: "localsock", scope: !136, file: !115, line: 403, type: !225)
!894 = !DILocation(line: 403, column: 24, scope: !136)
!895 = !DILocalVariable(name: "namelen", scope: !136, file: !115, line: 404, type: !51)
!896 = !DILocation(line: 404, column: 15, scope: !136)
!897 = !DILocalVariable(name: "af", scope: !136, file: !115, line: 405, type: !64)
!898 = !DILocation(line: 405, column: 9, scope: !136)
!899 = !DILocation(line: 406, column: 9, scope: !900)
!900 = distinct !DILexicalBlock(scope: !136, file: !115, line: 406, column: 9)
!901 = !DILocation(line: 406, column: 9, scope: !136)
!902 = !DILocation(line: 407, column: 26, scope: !903)
!903 = distinct !DILexicalBlock(scope: !904, file: !115, line: 407, column: 13)
!904 = distinct !DILexicalBlock(scope: !900, file: !115, line: 406, column: 20)
!905 = !DILocation(line: 407, column: 14, scope: !903)
!906 = !DILocation(line: 407, column: 13, scope: !904)
!907 = !DILocation(line: 408, column: 21, scope: !903)
!908 = !DILocation(line: 408, column: 13, scope: !903)
!909 = !DILocation(line: 410, column: 24, scope: !910)
!910 = distinct !DILexicalBlock(scope: !911, file: !115, line: 410, column: 17)
!911 = distinct !DILexicalBlock(scope: !903, file: !115, line: 409, column: 14)
!912 = !DILocation(line: 410, column: 17, scope: !910)
!913 = !DILocation(line: 410, column: 43, scope: !910)
!914 = !DILocation(line: 410, column: 17, scope: !911)
!915 = !DILocation(line: 411, column: 17, scope: !916)
!916 = distinct !DILexicalBlock(scope: !910, file: !115, line: 410, column: 48)
!917 = !DILocation(line: 412, column: 17, scope: !916)
!918 = !DILocation(line: 414, column: 21, scope: !919)
!919 = distinct !DILexicalBlock(scope: !920, file: !115, line: 414, column: 21)
!920 = distinct !DILexicalBlock(scope: !910, file: !115, line: 413, column: 20)
!921 = !DILocation(line: 414, column: 24, scope: !919)
!922 = !DILocation(line: 414, column: 21, scope: !920)
!923 = !DILocation(line: 415, column: 21, scope: !924)
!924 = distinct !DILexicalBlock(scope: !919, file: !115, line: 414, column: 30)
!925 = !DILocation(line: 416, column: 21, scope: !924)
!926 = !DILocation(line: 420, column: 5, scope: !904)
!927 = !DILocation(line: 421, column: 16, scope: !136)
!928 = !DILocation(line: 421, column: 14, scope: !136)
!929 = !DILocation(line: 422, column: 24, scope: !136)
!930 = !DILocation(line: 423, column: 17, scope: !136)
!931 = !DILocation(line: 424, column: 19, scope: !136)
!932 = !DILocation(line: 425, column: 14, scope: !933)
!933 = distinct !DILexicalBlock(scope: !136, file: !115, line: 425, column: 9)
!934 = !DILocation(line: 425, column: 24, scope: !933)
!935 = !DILocation(line: 425, column: 9, scope: !933)
!936 = !DILocation(line: 425, column: 61, scope: !933)
!937 = !DILocation(line: 425, column: 9, scope: !136)
!938 = !DILocation(line: 427, column: 15, scope: !939)
!939 = distinct !DILexicalBlock(scope: !933, file: !115, line: 425, column: 68)
!940 = !DILocation(line: 427, column: 6, scope: !941)
!941 = !DILexicalBlockFile(scope: !939, file: !115, discriminator: 1)
!942 = !DILocation(line: 426, column: 3, scope: !939)
!943 = !DILocation(line: 428, column: 3, scope: !939)
!944 = !DILocation(line: 430, column: 13, scope: !945)
!945 = distinct !DILexicalBlock(scope: !136, file: !115, line: 430, column: 6)
!946 = !DILocation(line: 430, column: 6, scope: !945)
!947 = !DILocation(line: 430, column: 6, scope: !136)
!948 = !DILocation(line: 432, column: 15, scope: !949)
!949 = distinct !DILexicalBlock(scope: !945, file: !115, line: 430, column: 27)
!950 = !DILocation(line: 432, column: 6, scope: !951)
!951 = !DILexicalBlockFile(scope: !949, file: !115, discriminator: 1)
!952 = !DILocation(line: 431, column: 3, scope: !949)
!953 = !DILocation(line: 433, column: 3, scope: !949)
!954 = !DILocation(line: 435, column: 10, scope: !136)
!955 = !DILocation(line: 436, column: 14, scope: !136)
!956 = !DILocation(line: 436, column: 24, scope: !136)
!957 = !DILocation(line: 436, column: 2, scope: !136)
!958 = !DILocation(line: 438, column: 30, scope: !136)
!959 = !DILocation(line: 438, column: 14, scope: !136)
!960 = !DILocation(line: 437, column: 5, scope: !136)
!961 = !DILocation(line: 439, column: 10, scope: !136)
!962 = !DILocation(line: 440, column: 1, scope: !136)
!963 = !DILocation(line: 440, column: 1, scope: !964)
!964 = !DILexicalBlockFile(scope: !136, file: !115, discriminator: 1)
!965 = !DILocalVariable(name: "selectbefore", arg: 1, scope: !137, file: !115, line: 442, type: !47)
!966 = !DILocation(line: 442, column: 22, scope: !137)
!967 = !DILocalVariable(name: "file", arg: 2, scope: !137, file: !115, line: 442, type: !64)
!968 = !DILocation(line: 442, column: 40, scope: !137)
!969 = !DILocalVariable(name: "sock", arg: 3, scope: !137, file: !115, line: 442, type: !64)
!970 = !DILocation(line: 442, column: 50, scope: !137)
!971 = !DILocalVariable(name: "str", scope: !137, file: !115, line: 444, type: !972)
!972 = !DICompositeType(tag: DW_TAG_array_type, baseType: !47, size: 2048, align: 8, elements: !973)
!973 = !{!974}
!974 = !DISubrange(count: 256)
!975 = !DILocation(line: 444, column: 10, scope: !137)
!976 = !DILocalVariable(name: "rfds", scope: !137, file: !115, line: 445, type: !977)
!977 = !DIDerivedType(tag: DW_TAG_typedef, name: "fd_set", file: !62, line: 75, baseType: !978)
!978 = !DICompositeType(tag: DW_TAG_structure_type, file: !62, line: 64, size: 1024, align: 64, elements: !979)
!979 = !{!980}
!980 = !DIDerivedType(tag: DW_TAG_member, name: "__fds_bits", scope: !978, file: !62, line: 72, baseType: !981, size: 1024, align: 64)
!981 = !DICompositeType(tag: DW_TAG_array_type, baseType: !61, size: 1024, align: 64, elements: !982)
!982 = !{!983}
!983 = !DISubrange(count: 16)
!984 = !DILocation(line: 445, column: 12, scope: !137)
!985 = !DILocalVariable(name: "tv", scope: !137, file: !115, line: 446, type: !986)
!986 = !DICompositeType(tag: DW_TAG_structure_type, name: "timeval", file: !987, line: 30, size: 128, align: 64, elements: !988)
!987 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/time.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!988 = !{!989, !990}
!989 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !986, file: !987, line: 32, baseType: !96, size: 64, align: 64)
!990 = !DIDerivedType(tag: DW_TAG_member, name: "tv_usec", scope: !986, file: !987, line: 33, baseType: !991, size: 64, align: 64, offset: 64)
!991 = !DIDerivedType(tag: DW_TAG_typedef, name: "__suseconds_t", file: !54, line: 141, baseType: !63)
!992 = !DILocation(line: 446, column: 20, scope: !137)
!993 = !DILocalVariable(name: "result", scope: !137, file: !115, line: 447, type: !56)
!994 = !DILocation(line: 447, column: 11, scope: !137)
!995 = !DILocation(line: 449, column: 9, scope: !996)
!996 = distinct !DILexicalBlock(scope: !137, file: !115, line: 449, column: 9)
!997 = !DILocation(line: 449, column: 9, scope: !137)
!998 = !DILocation(line: 450, column: 12, scope: !999)
!999 = distinct !DILexicalBlock(scope: !996, file: !115, line: 449, column: 23)
!1000 = !DILocation(line: 450, column: 19, scope: !999)
!1001 = !DILocation(line: 451, column: 12, scope: !999)
!1002 = !DILocation(line: 451, column: 20, scope: !999)
!1003 = !DILocation(line: 452, column: 9, scope: !999)
!1004 = !DILocalVariable(name: "__d0", scope: !1005, file: !115, line: 452, type: !64)
!1005 = distinct !DILexicalBlock(scope: !999, file: !115, line: 452, column: 9)
!1006 = !DILocation(line: 452, column: 9, scope: !1005)
!1007 = !DILocalVariable(name: "__d1", scope: !1005, file: !115, line: 452, type: !64)
!1008 = !DILocation(line: 452, column: 9, scope: !1009)
!1009 = !DILexicalBlockFile(scope: !1005, file: !115, discriminator: 1)
!1010 = !{i32 -2146571257}
!1011 = !DILocation(line: 453, column: 9, scope: !999)
!1012 = !DILocation(line: 453, column: 9, scope: !1013)
!1013 = !DILexicalBlockFile(scope: !999, file: !115, discriminator: 1)
!1014 = !DILocation(line: 454, column: 28, scope: !1015)
!1015 = distinct !DILexicalBlock(scope: !999, file: !115, line: 454, column: 13)
!1016 = !DILocation(line: 454, column: 21, scope: !1015)
!1017 = !DILocation(line: 454, column: 35, scope: !1015)
!1018 = !DILocation(line: 454, column: 14, scope: !1019)
!1019 = !DILexicalBlockFile(scope: !1015, file: !115, discriminator: 1)
!1020 = !DILocation(line: 454, column: 14, scope: !1015)
!1021 = !DILocation(line: 454, column: 13, scope: !999)
!1022 = !DILocation(line: 455, column: 13, scope: !1015)
!1023 = !DILocation(line: 456, column: 5, scope: !999)
!1024 = !DILocation(line: 458, column: 20, scope: !137)
!1025 = !DILocation(line: 458, column: 38, scope: !137)
!1026 = !DILocation(line: 458, column: 14, scope: !137)
!1027 = !DILocation(line: 458, column: 12, scope: !137)
!1028 = !DILocation(line: 459, column: 11, scope: !1029)
!1029 = distinct !DILexicalBlock(scope: !137, file: !115, line: 459, column: 10)
!1030 = !DILocation(line: 459, column: 10, scope: !1029)
!1031 = !DILocation(line: 459, column: 19, scope: !1029)
!1032 = !DILocation(line: 459, column: 31, scope: !1033)
!1033 = !DILexicalBlockFile(scope: !1029, file: !115, discriminator: 1)
!1034 = !DILocation(line: 459, column: 24, scope: !1033)
!1035 = !DILocation(line: 459, column: 10, scope: !1033)
!1036 = !DILocation(line: 460, column: 9, scope: !1037)
!1037 = distinct !DILexicalBlock(scope: !1029, file: !115, line: 459, column: 47)
!1038 = !DILocation(line: 461, column: 12, scope: !1037)
!1039 = !DILocation(line: 461, column: 6, scope: !1037)
!1040 = !DILocation(line: 462, column: 9, scope: !1037)
!1041 = !DILocation(line: 462, column: 3, scope: !1037)
!1042 = !DILocation(line: 463, column: 6, scope: !1037)
!1043 = !DILocation(line: 464, column: 3, scope: !1037)
!1044 = !DILocation(line: 465, column: 15, scope: !1037)
!1045 = !DILocation(line: 465, column: 9, scope: !1037)
!1046 = !DILocation(line: 466, column: 9, scope: !1037)
!1047 = !DILocation(line: 468, column: 5, scope: !137)
!1048 = !DILocation(line: 469, column: 1, scope: !137)
!1049 = !DILocalVariable(name: "foo", arg: 1, scope: !140, file: !115, line: 471, type: !56)
!1050 = !DILocation(line: 471, column: 25, scope: !140)
!1051 = !DILocation(line: 473, column: 18, scope: !140)
!1052 = !DILocation(line: 473, column: 5, scope: !140)
!1053 = !DILocation(line: 474, column: 1, scope: !140)
!1054 = !DILocalVariable(name: "params", arg: 1, scope: !161, file: !115, line: 1471, type: !56)
!1055 = !DILocation(line: 1471, column: 25, scope: !161)
!1056 = !DILocation(line: 1473, column: 2, scope: !161)
!1057 = !DILocation(line: 1474, column: 1, scope: !161)
!1058 = !DILocalVariable(name: "filenames", arg: 1, scope: !141, file: !115, line: 478, type: !56)
!1059 = !DILocation(line: 478, column: 25, scope: !141)
!1060 = !DILocalVariable(name: "filename", scope: !141, file: !115, line: 480, type: !1061)
!1061 = !DICompositeType(tag: DW_TAG_array_type, baseType: !47, size: 2040, align: 8, elements: !1062)
!1062 = !{!1063}
!1063 = !DISubrange(count: 255)
!1064 = !DILocation(line: 480, column: 9, scope: !141)
!1065 = !DILocalVariable(name: "from_index", scope: !141, file: !115, line: 481, type: !64)
!1066 = !DILocation(line: 481, column: 8, scope: !141)
!1067 = !DILocalVariable(name: "to_index", scope: !141, file: !115, line: 481, type: !64)
!1068 = !DILocation(line: 481, column: 20, scope: !141)
!1069 = !DILocation(line: 483, column: 15, scope: !141)
!1070 = !DILocation(line: 484, column: 4, scope: !141)
!1071 = !DILocation(line: 485, column: 13, scope: !141)
!1072 = !DILocation(line: 488, column: 4, scope: !141)
!1073 = !DILocation(line: 488, column: 22, scope: !1074)
!1074 = !DILexicalBlockFile(scope: !141, file: !115, discriminator: 1)
!1075 = !DILocation(line: 488, column: 12, scope: !1074)
!1076 = !DILocation(line: 488, column: 34, scope: !1074)
!1077 = !DILocation(line: 488, column: 4, scope: !1074)
!1078 = !DILocation(line: 491, column: 22, scope: !1079)
!1079 = distinct !DILexicalBlock(scope: !1080, file: !115, line: 491, column: 12)
!1080 = distinct !DILexicalBlock(scope: !141, file: !115, line: 489, column: 4)
!1081 = !DILocation(line: 491, column: 12, scope: !1079)
!1082 = !DILocation(line: 491, column: 34, scope: !1079)
!1083 = !DILocation(line: 491, column: 12, scope: !1080)
!1084 = !DILocation(line: 494, column: 24, scope: !1085)
!1085 = distinct !DILexicalBlock(scope: !1079, file: !115, line: 492, column: 8)
!1086 = !DILocation(line: 494, column: 11, scope: !1085)
!1087 = !DILocation(line: 496, column: 20, scope: !1085)
!1088 = !DILocation(line: 497, column: 11, scope: !1085)
!1089 = !DILocation(line: 499, column: 11, scope: !1085)
!1090 = !DILocation(line: 499, column: 28, scope: !1091)
!1091 = !DILexicalBlockFile(scope: !1085, file: !115, discriminator: 1)
!1092 = !DILocation(line: 499, column: 18, scope: !1091)
!1093 = !DILocation(line: 499, column: 40, scope: !1091)
!1094 = !DILocation(line: 499, column: 11, scope: !1091)
!1095 = !DILocation(line: 500, column: 23, scope: !1085)
!1096 = !DILocation(line: 499, column: 11, scope: !1097)
!1097 = !DILexicalBlockFile(scope: !1085, file: !115, discriminator: 2)
!1098 = !DILocation(line: 501, column: 8, scope: !1085)
!1099 = !DILocation(line: 506, column: 42, scope: !1100)
!1100 = distinct !DILexicalBlock(scope: !1079, file: !115, line: 505, column: 8)
!1101 = !DILocation(line: 506, column: 32, scope: !1100)
!1102 = !DILocation(line: 506, column: 20, scope: !1100)
!1103 = !DILocation(line: 506, column: 11, scope: !1100)
!1104 = !DILocation(line: 506, column: 30, scope: !1100)
!1105 = !DILocation(line: 507, column: 19, scope: !1100)
!1106 = !DILocation(line: 508, column: 21, scope: !1100)
!1107 = !DILocation(line: 510, column: 27, scope: !1108)
!1108 = distinct !DILexicalBlock(scope: !1100, file: !115, line: 510, column: 15)
!1109 = !DILocation(line: 510, column: 17, scope: !1108)
!1110 = !DILocation(line: 510, column: 15, scope: !1100)
!1111 = !DILocation(line: 512, column: 27, scope: !1112)
!1112 = distinct !DILexicalBlock(scope: !1108, file: !115, line: 511, column: 11)
!1113 = !DILocation(line: 512, column: 14, scope: !1112)
!1114 = !DILocation(line: 513, column: 23, scope: !1112)
!1115 = !DILocation(line: 514, column: 14, scope: !1112)
!1116 = !DILocation(line: 515, column: 24, scope: !1112)
!1117 = !DILocation(line: 516, column: 11, scope: !1112)
!1118 = !DILocation(line: 520, column: 12, scope: !1119)
!1119 = distinct !DILexicalBlock(scope: !1080, file: !115, line: 520, column: 12)
!1120 = !DILocation(line: 520, column: 21, scope: !1119)
!1121 = !DILocation(line: 520, column: 12, scope: !1080)
!1122 = !DILocation(line: 522, column: 60, scope: !1123)
!1123 = distinct !DILexicalBlock(scope: !1119, file: !115, line: 521, column: 8)
!1124 = !DILocation(line: 522, column: 11, scope: !1123)
!1125 = !DILocation(line: 523, column: 11, scope: !1123)
!1126 = !DILocation(line: 488, column: 4, scope: !1127)
!1127 = !DILexicalBlockFile(scope: !141, file: !115, discriminator: 2)
!1128 = !DILocation(line: 528, column: 1, scope: !141)
!1129 = !DILocalVariable(name: "filename", arg: 1, scope: !145, file: !115, line: 788, type: !56)
!1130 = !DILocation(line: 788, column: 25, scope: !145)
!1131 = !DILocation(line: 790, column: 13, scope: !145)
!1132 = !DILocation(line: 790, column: 5, scope: !145)
!1133 = !DILocation(line: 791, column: 1, scope: !145)
!1134 = !DILocalVariable(name: "filename", arg: 1, scope: !142, file: !115, line: 532, type: !56)
!1135 = !DILocation(line: 532, column: 20, scope: !142)
!1136 = !DILocalVariable(name: "flags", arg: 2, scope: !142, file: !115, line: 532, type: !64)
!1137 = !DILocation(line: 532, column: 34, scope: !142)
!1138 = !DILocalVariable(name: "buffer", scope: !142, file: !115, line: 534, type: !56)
!1139 = !DILocation(line: 534, column: 11, scope: !142)
!1140 = !DILocalVariable(name: "fd", scope: !142, file: !115, line: 535, type: !64)
!1141 = !DILocation(line: 535, column: 9, scope: !142)
!1142 = !DILocalVariable(name: "i", scope: !142, file: !115, line: 535, type: !64)
!1143 = !DILocation(line: 535, column: 13, scope: !142)
!1144 = !DILocalVariable(name: "max", scope: !142, file: !115, line: 535, type: !64)
!1145 = !DILocation(line: 535, column: 16, scope: !142)
!1146 = !DILocalVariable(name: "rfds", scope: !142, file: !115, line: 536, type: !977)
!1147 = !DILocation(line: 536, column: 12, scope: !142)
!1148 = !DILocalVariable(name: "tv", scope: !142, file: !115, line: 537, type: !986)
!1149 = !DILocation(line: 537, column: 20, scope: !142)
!1150 = !DILocalVariable(name: "p", scope: !142, file: !115, line: 538, type: !56)
!1151 = !DILocation(line: 538, column: 11, scope: !142)
!1152 = !DILocalVariable(name: "pp", scope: !142, file: !115, line: 538, type: !56)
!1153 = !DILocation(line: 538, column: 15, scope: !142)
!1154 = !DILocalVariable(name: "mapped", scope: !142, file: !115, line: 539, type: !56)
!1155 = !DILocation(line: 539, column: 11, scope: !142)
!1156 = !DILocation(line: 539, column: 38, scope: !142)
!1157 = !DILocation(line: 539, column: 20, scope: !142)
!1158 = !DILocalVariable(name: "my_buffer_size", scope: !142, file: !115, line: 541, type: !64)
!1159 = !DILocation(line: 541, column: 9, scope: !142)
!1160 = !DILocalVariable(name: "num_clients", scope: !142, file: !115, line: 542, type: !64)
!1161 = !DILocation(line: 542, column: 9, scope: !142)
!1162 = !DILocalVariable(name: "new_num_clients", scope: !142, file: !115, line: 543, type: !64)
!1163 = !DILocation(line: 543, column: 9, scope: !142)
!1164 = !DILocalVariable(name: "xfer_delay", scope: !142, file: !115, line: 544, type: !64)
!1165 = !DILocation(line: 544, column: 9, scope: !142)
!1166 = !DILocalVariable(name: "attempt_gzip", scope: !142, file: !115, line: 545, type: !64)
!1167 = !DILocation(line: 545, column: 9, scope: !142)
!1168 = !DILocalVariable(name: "get_value", scope: !142, file: !115, line: 546, type: !72)
!1169 = !DILocation(line: 546, column: 19, scope: !142)
!1170 = !DILocalVariable(name: "change_buffer_size", scope: !142, file: !115, line: 547, type: !64)
!1171 = !DILocation(line: 547, column: 9, scope: !142)
!1172 = !DILocalVariable(name: "stdin_fileno", scope: !142, file: !115, line: 548, type: !64)
!1173 = !DILocation(line: 548, column: 9, scope: !142)
!1174 = !DILocalVariable(name: "write_result", scope: !142, file: !115, line: 549, type: !64)
!1175 = !DILocation(line: 549, column: 9, scope: !142)
!1176 = !DILocation(line: 554, column: 9, scope: !1177)
!1177 = distinct !DILexicalBlock(scope: !142, file: !115, line: 554, column: 9)
!1178 = !DILocation(line: 554, column: 9, scope: !142)
!1179 = !DILocation(line: 555, column: 19, scope: !1177)
!1180 = !DILocation(line: 555, column: 37, scope: !1177)
!1181 = !DILocation(line: 555, column: 8, scope: !1177)
!1182 = !DILocation(line: 568, column: 30, scope: !142)
!1183 = !DILocation(line: 568, column: 21, scope: !1184)
!1184 = !DILexicalBlockFile(scope: !142, file: !115, discriminator: 1)
!1185 = !DILocation(line: 568, column: 19, scope: !142)
!1186 = !DILocation(line: 569, column: 13, scope: !1187)
!1187 = distinct !DILexicalBlock(scope: !142, file: !115, line: 569, column: 13)
!1188 = !DILocation(line: 569, column: 23, scope: !1187)
!1189 = !DILocation(line: 569, column: 13, scope: !142)
!1190 = !DILocation(line: 570, column: 25, scope: !1187)
!1191 = !DILocation(line: 570, column: 23, scope: !1187)
!1192 = !DILocation(line: 570, column: 12, scope: !1187)
!1193 = !DILocation(line: 573, column: 12, scope: !1194)
!1194 = distinct !DILexicalBlock(scope: !1187, file: !115, line: 572, column: 9)
!1195 = !DILocation(line: 574, column: 23, scope: !1194)
!1196 = !DILocation(line: 579, column: 19, scope: !142)
!1197 = !DILocation(line: 579, column: 14, scope: !142)
!1198 = !DILocation(line: 579, column: 12, scope: !142)
!1199 = !DILocation(line: 580, column: 13, scope: !1200)
!1200 = distinct !DILexicalBlock(scope: !142, file: !115, line: 580, column: 13)
!1201 = !DILocation(line: 580, column: 16, scope: !1200)
!1202 = !DILocation(line: 580, column: 13, scope: !142)
!1203 = !DILocation(line: 583, column: 18, scope: !1204)
!1204 = distinct !DILexicalBlock(scope: !1200, file: !115, line: 581, column: 9)
!1205 = !DILocation(line: 583, column: 12, scope: !1204)
!1206 = !DILocation(line: 585, column: 30, scope: !1207)
!1207 = distinct !DILexicalBlock(scope: !1204, file: !115, line: 585, column: 17)
!1208 = !DILocation(line: 585, column: 18, scope: !1209)
!1209 = !DILexicalBlockFile(scope: !1207, file: !115, discriminator: 1)
!1210 = !DILocation(line: 585, column: 18, scope: !1207)
!1211 = !DILocation(line: 585, column: 17, scope: !1204)
!1212 = !DILocation(line: 587, column: 62, scope: !1213)
!1213 = distinct !DILexicalBlock(scope: !1207, file: !115, line: 586, column: 12)
!1214 = !DILocation(line: 587, column: 15, scope: !1213)
!1215 = !DILocation(line: 588, column: 15, scope: !1213)
!1216 = !DILocation(line: 591, column: 20, scope: !1213)
!1217 = !DILocation(line: 591, column: 15, scope: !1213)
!1218 = !DILocation(line: 592, column: 21, scope: !1213)
!1219 = !DILocation(line: 592, column: 15, scope: !1213)
!1220 = !DILocation(line: 593, column: 15, scope: !1213)
!1221 = !DILocation(line: 595, column: 9, scope: !1204)
!1222 = !DILocation(line: 597, column: 15, scope: !1223)
!1223 = distinct !DILexicalBlock(scope: !142, file: !115, line: 597, column: 13)
!1224 = !DILocation(line: 597, column: 13, scope: !142)
!1225 = !DILocation(line: 599, column: 14, scope: !1226)
!1226 = distinct !DILexicalBlock(scope: !1223, file: !115, line: 598, column: 9)
!1227 = !DILocation(line: 599, column: 22, scope: !1226)
!1228 = !DILocation(line: 599, column: 9, scope: !1226)
!1229 = !DILocation(line: 599, column: 7, scope: !1226)
!1230 = !DILocation(line: 605, column: 8, scope: !1231)
!1231 = distinct !DILexicalBlock(scope: !1226, file: !115, line: 605, column: 8)
!1232 = !DILocation(line: 605, column: 11, scope: !1231)
!1233 = !DILocation(line: 605, column: 8, scope: !1226)
!1234 = !DILocation(line: 607, column: 16, scope: !1235)
!1235 = distinct !DILexicalBlock(scope: !1231, file: !115, line: 605, column: 18)
!1236 = !DILocation(line: 607, column: 7, scope: !1237)
!1237 = !DILexicalBlockFile(scope: !1235, file: !115, discriminator: 1)
!1238 = !DILocation(line: 607, column: 24, scope: !1235)
!1239 = !DILocation(line: 606, column: 3, scope: !1235)
!1240 = !DILocation(line: 608, column: 57, scope: !1235)
!1241 = !DILocation(line: 608, column: 48, scope: !1237)
!1242 = !DILocation(line: 608, column: 3, scope: !1243)
!1243 = !DILexicalBlockFile(scope: !1235, file: !115, discriminator: 2)
!1244 = !DILocation(line: 610, column: 23, scope: !1235)
!1245 = !DILocation(line: 610, column: 17, scope: !1235)
!1246 = !DILocation(line: 611, column: 21, scope: !1247)
!1247 = distinct !DILexicalBlock(scope: !1235, file: !115, line: 611, column: 21)
!1248 = !DILocation(line: 611, column: 21, scope: !1235)
!1249 = !DILocation(line: 612, column: 31, scope: !1247)
!1250 = !DILocation(line: 612, column: 50, scope: !1247)
!1251 = !DILocation(line: 612, column: 20, scope: !1247)
!1252 = !DILocation(line: 613, column: 22, scope: !1235)
!1253 = !DILocation(line: 613, column: 17, scope: !1235)
!1254 = !DILocation(line: 614, column: 3, scope: !1235)
!1255 = !DILocation(line: 616, column: 2, scope: !1226)
!1256 = !DILocation(line: 637, column: 46, scope: !142)
!1257 = !DILocation(line: 637, column: 2, scope: !142)
!1258 = !DILocation(line: 638, column: 6, scope: !1259)
!1259 = distinct !DILexicalBlock(scope: !142, file: !115, line: 638, column: 6)
!1260 = !DILocation(line: 638, column: 6, scope: !142)
!1261 = !DILocation(line: 640, column: 19, scope: !1262)
!1262 = distinct !DILexicalBlock(scope: !1259, file: !115, line: 639, column: 9)
!1263 = !DILocation(line: 640, column: 13, scope: !1262)
!1264 = !DILocation(line: 641, column: 17, scope: !1265)
!1265 = distinct !DILexicalBlock(scope: !1262, file: !115, line: 641, column: 17)
!1266 = !DILocation(line: 641, column: 17, scope: !1262)
!1267 = !DILocation(line: 642, column: 27, scope: !1265)
!1268 = !DILocation(line: 642, column: 46, scope: !1265)
!1269 = !DILocation(line: 642, column: 16, scope: !1265)
!1270 = !DILocation(line: 643, column: 17, scope: !1271)
!1271 = distinct !DILexicalBlock(scope: !1262, file: !115, line: 643, column: 17)
!1272 = !DILocation(line: 643, column: 17, scope: !1262)
!1273 = !DILocation(line: 644, column: 21, scope: !1271)
!1274 = !DILocation(line: 644, column: 16, scope: !1271)
!1275 = !DILocation(line: 645, column: 6, scope: !1262)
!1276 = !DILocation(line: 650, column: 23, scope: !1277)
!1277 = distinct !DILexicalBlock(scope: !142, file: !115, line: 650, column: 9)
!1278 = !DILocation(line: 650, column: 11, scope: !1279)
!1279 = !DILexicalBlockFile(scope: !1277, file: !115, discriminator: 1)
!1280 = !DILocation(line: 650, column: 11, scope: !1277)
!1281 = !DILocation(line: 650, column: 9, scope: !142)
!1282 = !DILocation(line: 651, column: 27, scope: !1277)
!1283 = !DILocation(line: 651, column: 8, scope: !1277)
!1284 = !DILocation(line: 657, column: 9, scope: !1285)
!1285 = distinct !DILexicalBlock(scope: !142, file: !115, line: 657, column: 9)
!1286 = !DILocation(line: 657, column: 9, scope: !142)
!1287 = !DILocation(line: 659, column: 22, scope: !1288)
!1288 = distinct !DILexicalBlock(scope: !1285, file: !115, line: 658, column: 5)
!1289 = !DILocation(line: 659, column: 20, scope: !1288)
!1290 = !DILocation(line: 660, column: 41, scope: !1288)
!1291 = !DILocation(line: 660, column: 25, scope: !1288)
!1292 = !DILocation(line: 660, column: 23, scope: !1288)
!1293 = !DILocation(line: 661, column: 5, scope: !1288)
!1294 = !DILocation(line: 663, column: 25, scope: !1285)
!1295 = !DILocation(line: 663, column: 23, scope: !1285)
!1296 = !DILocation(line: 665, column: 5, scope: !142)
!1297 = !DILocation(line: 666, column: 21, scope: !142)
!1298 = !DILocation(line: 666, column: 14, scope: !142)
!1299 = !DILocation(line: 666, column: 12, scope: !142)
!1300 = !DILocation(line: 668, column: 11, scope: !1301)
!1301 = distinct !DILexicalBlock(scope: !142, file: !115, line: 668, column: 9)
!1302 = !DILocation(line: 668, column: 9, scope: !142)
!1303 = !DILocation(line: 670, column: 8, scope: !1304)
!1304 = distinct !DILexicalBlock(scope: !1301, file: !115, line: 669, column: 5)
!1305 = !DILocation(line: 671, column: 8, scope: !1304)
!1306 = !DILocation(line: 672, column: 12, scope: !1307)
!1307 = distinct !DILexicalBlock(scope: !1304, file: !115, line: 672, column: 12)
!1308 = !DILocation(line: 672, column: 15, scope: !1307)
!1309 = !DILocation(line: 672, column: 12, scope: !1304)
!1310 = !DILocation(line: 673, column: 17, scope: !1307)
!1311 = !DILocation(line: 673, column: 11, scope: !1307)
!1312 = !DILocation(line: 674, column: 14, scope: !1304)
!1313 = !DILocation(line: 674, column: 8, scope: !1304)
!1314 = !DILocation(line: 675, column: 8, scope: !1304)
!1315 = !DILocation(line: 678, column: 8, scope: !142)
!1316 = !DILocation(line: 678, column: 12, scope: !142)
!1317 = !DILocation(line: 678, column: 2, scope: !142)
!1318 = !DILocation(line: 679, column: 9, scope: !142)
!1319 = !DILocation(line: 682, column: 27, scope: !142)
!1320 = !DILocation(line: 682, column: 20, scope: !142)
!1321 = !DILocation(line: 682, column: 18, scope: !142)
!1322 = !DILocation(line: 683, column: 12, scope: !142)
!1323 = !DILocation(line: 683, column: 19, scope: !142)
!1324 = !DILocation(line: 683, column: 17, scope: !142)
!1325 = !DILocation(line: 683, column: 34, scope: !1184)
!1326 = !DILocation(line: 683, column: 12, scope: !1184)
!1327 = !DILocation(line: 683, column: 41, scope: !1328)
!1328 = !DILexicalBlockFile(scope: !142, file: !115, discriminator: 2)
!1329 = !DILocation(line: 683, column: 12, scope: !1328)
!1330 = !DILocation(line: 683, column: 12, scope: !1331)
!1331 = !DILexicalBlockFile(scope: !142, file: !115, discriminator: 3)
!1332 = !DILocation(line: 683, column: 55, scope: !1331)
!1333 = !DILocation(line: 683, column: 9, scope: !1331)
!1334 = !DILocation(line: 684, column: 2, scope: !142)
!1335 = !DILocation(line: 686, column: 9, scope: !1336)
!1336 = distinct !DILexicalBlock(scope: !1337, file: !115, line: 685, column: 9)
!1337 = distinct !DILexicalBlock(scope: !1338, file: !115, line: 684, column: 2)
!1338 = distinct !DILexicalBlock(scope: !142, file: !115, line: 684, column: 2)
!1339 = !DILocalVariable(name: "__d0", scope: !1340, file: !115, line: 686, type: !64)
!1340 = distinct !DILexicalBlock(scope: !1336, file: !115, line: 686, column: 9)
!1341 = !DILocation(line: 686, column: 9, scope: !1340)
!1342 = !DILocalVariable(name: "__d1", scope: !1340, file: !115, line: 686, type: !64)
!1343 = !DILocation(line: 686, column: 9, scope: !1344)
!1344 = !DILexicalBlockFile(scope: !1340, file: !115, discriminator: 1)
!1345 = !{i32 -2146570375}
!1346 = !DILocation(line: 687, column: 9, scope: !1336)
!1347 = !DILocation(line: 688, column: 9, scope: !1336)
!1348 = !DILocation(line: 690, column: 21, scope: !1336)
!1349 = !DILocation(line: 690, column: 12, scope: !1336)
!1350 = !DILocation(line: 690, column: 19, scope: !1336)
!1351 = !DILocation(line: 691, column: 12, scope: !1336)
!1352 = !DILocation(line: 691, column: 20, scope: !1336)
!1353 = !DILocation(line: 692, column: 21, scope: !1354)
!1354 = distinct !DILexicalBlock(scope: !1336, file: !115, line: 692, column: 13)
!1355 = !DILocation(line: 692, column: 14, scope: !1354)
!1356 = !DILocation(line: 692, column: 13, scope: !1336)
!1357 = !DILocation(line: 693, column: 19, scope: !1358)
!1358 = distinct !DILexicalBlock(scope: !1354, file: !115, line: 692, column: 51)
!1359 = !DILocation(line: 693, column: 13, scope: !1358)
!1360 = !DILocation(line: 694, column: 19, scope: !1358)
!1361 = !DILocation(line: 694, column: 13, scope: !1358)
!1362 = !DILocation(line: 695, column: 13, scope: !1358)
!1363 = !DILocation(line: 696, column: 13, scope: !1358)
!1364 = !DILocation(line: 698, column: 17, scope: !1365)
!1365 = distinct !DILexicalBlock(scope: !1358, file: !115, line: 698, column: 17)
!1366 = !DILocation(line: 698, column: 17, scope: !1358)
!1367 = !DILocation(line: 699, column: 27, scope: !1365)
!1368 = !DILocation(line: 699, column: 46, scope: !1365)
!1369 = !DILocation(line: 699, column: 16, scope: !1365)
!1370 = !DILocation(line: 701, column: 13, scope: !1358)
!1371 = !DILocation(line: 703, column: 13, scope: !1358)
!1372 = !DILocation(line: 705, column: 13, scope: !1373)
!1373 = distinct !DILexicalBlock(scope: !1336, file: !115, line: 705, column: 13)
!1374 = !DILocation(line: 705, column: 13, scope: !1336)
!1375 = !DILocation(line: 706, column: 27, scope: !1376)
!1376 = distinct !DILexicalBlock(scope: !1373, file: !115, line: 705, column: 44)
!1377 = !DILocation(line: 706, column: 31, scope: !1376)
!1378 = !DILocation(line: 706, column: 13, scope: !1376)
!1379 = !DILocation(line: 707, column: 10, scope: !1380)
!1380 = distinct !DILexicalBlock(scope: !1376, file: !115, line: 707, column: 10)
!1381 = !DILocation(line: 707, column: 10, scope: !1376)
!1382 = !DILocation(line: 708, column: 8, scope: !1380)
!1383 = !DILocation(line: 708, column: 3, scope: !1380)
!1384 = !DILocation(line: 709, column: 19, scope: !1376)
!1385 = !DILocation(line: 709, column: 13, scope: !1376)
!1386 = !DILocation(line: 710, column: 17, scope: !1387)
!1387 = distinct !DILexicalBlock(scope: !1376, file: !115, line: 710, column: 17)
!1388 = !DILocation(line: 710, column: 17, scope: !1376)
!1389 = !DILocation(line: 711, column: 27, scope: !1387)
!1390 = !DILocation(line: 711, column: 46, scope: !1387)
!1391 = !DILocation(line: 711, column: 16, scope: !1387)
!1392 = !DILocation(line: 712, column: 18, scope: !1376)
!1393 = !DILocation(line: 712, column: 13, scope: !1376)
!1394 = !DILocation(line: 713, column: 13, scope: !1376)
!1395 = !DILocation(line: 716, column: 18, scope: !1396)
!1396 = distinct !DILexicalBlock(scope: !1336, file: !115, line: 716, column: 6)
!1397 = !DILocation(line: 716, column: 24, scope: !1396)
!1398 = !DILocation(line: 716, column: 32, scope: !1396)
!1399 = !DILocation(line: 716, column: 47, scope: !1396)
!1400 = !DILocation(line: 716, column: 13, scope: !1396)
!1401 = !DILocation(line: 716, column: 11, scope: !1396)
!1402 = !DILocation(line: 716, column: 6, scope: !1336)
!1403 = !DILocation(line: 717, column: 13, scope: !1396)
!1404 = !DILocation(line: 718, column: 24, scope: !1336)
!1405 = !DILocation(line: 718, column: 21, scope: !1336)
!1406 = !DILocation(line: 719, column: 13, scope: !1407)
!1407 = distinct !DILexicalBlock(scope: !1336, file: !115, line: 719, column: 13)
!1408 = !DILocation(line: 719, column: 22, scope: !1407)
!1409 = !DILocation(line: 719, column: 13, scope: !1336)
!1410 = !DILocation(line: 720, column: 20, scope: !1411)
!1411 = distinct !DILexicalBlock(scope: !1407, file: !115, line: 719, column: 37)
!1412 = !DILocation(line: 720, column: 13, scope: !1411)
!1413 = !DILocation(line: 720, column: 23, scope: !1411)
!1414 = !DILocation(line: 722, column: 22, scope: !1411)
!1415 = !DILocation(line: 722, column: 20, scope: !1411)
!1416 = !DILocation(line: 722, column: 15, scope: !1411)
!1417 = !DILocation(line: 723, column: 10, scope: !1411)
!1418 = !DILocation(line: 723, column: 18, scope: !1419)
!1419 = !DILexicalBlockFile(scope: !1411, file: !115, discriminator: 1)
!1420 = !DILocation(line: 723, column: 17, scope: !1419)
!1421 = !DILocation(line: 723, column: 10, scope: !1419)
!1422 = !DILocation(line: 724, column: 32, scope: !1423)
!1423 = distinct !DILexicalBlock(scope: !1424, file: !115, line: 724, column: 15)
!1424 = distinct !DILexicalBlock(scope: !1411, file: !115, line: 723, column: 21)
!1425 = !DILocation(line: 724, column: 31, scope: !1423)
!1426 = !DILocation(line: 724, column: 15, scope: !1423)
!1427 = !DILocation(line: 724, column: 34, scope: !1423)
!1428 = !DILocation(line: 724, column: 15, scope: !1424)
!1429 = !DILocation(line: 725, column: 13, scope: !1423)
!1430 = !DILocation(line: 725, column: 12, scope: !1423)
!1431 = !DILocation(line: 727, column: 22, scope: !1423)
!1432 = !DILocation(line: 727, column: 20, scope: !1423)
!1433 = !DILocation(line: 727, column: 15, scope: !1423)
!1434 = !DILocation(line: 727, column: 18, scope: !1423)
!1435 = !DILocation(line: 723, column: 10, scope: !1436)
!1436 = !DILexicalBlockFile(scope: !1411, file: !115, discriminator: 2)
!1437 = !DILocation(line: 729, column: 13, scope: !1411)
!1438 = !DILocation(line: 729, column: 16, scope: !1411)
!1439 = !DILocation(line: 730, column: 24, scope: !1411)
!1440 = !DILocation(line: 730, column: 17, scope: !1411)
!1441 = !DILocation(line: 730, column: 15, scope: !1411)
!1442 = !DILocation(line: 731, column: 9, scope: !1411)
!1443 = !DILocation(line: 737, column: 17, scope: !1444)
!1444 = distinct !DILexicalBlock(scope: !1336, file: !115, line: 737, column: 15)
!1445 = !DILocation(line: 737, column: 15, scope: !1336)
!1446 = !DILocation(line: 739, column: 36, scope: !1447)
!1447 = distinct !DILexicalBlock(scope: !1444, file: !115, line: 738, column: 12)
!1448 = !DILocation(line: 739, column: 40, scope: !1447)
!1449 = !DILocation(line: 739, column: 48, scope: !1447)
!1450 = !DILocation(line: 739, column: 30, scope: !1447)
!1451 = !DILocation(line: 739, column: 28, scope: !1447)
!1452 = !DILocation(line: 740, column: 19, scope: !1453)
!1453 = distinct !DILexicalBlock(scope: !1447, file: !115, line: 740, column: 19)
!1454 = !DILocation(line: 740, column: 32, scope: !1453)
!1455 = !DILocation(line: 740, column: 19, scope: !1447)
!1456 = !DILocation(line: 741, column: 19, scope: !1453)
!1457 = !DILocation(line: 742, column: 12, scope: !1447)
!1458 = !DILocation(line: 745, column: 13, scope: !1459)
!1459 = distinct !DILexicalBlock(scope: !1336, file: !115, line: 745, column: 13)
!1460 = !DILocation(line: 745, column: 13, scope: !1336)
!1461 = !DILocation(line: 747, column: 30, scope: !1462)
!1462 = distinct !DILexicalBlock(scope: !1459, file: !115, line: 746, column: 9)
!1463 = !DILocation(line: 747, column: 28, scope: !1462)
!1464 = !DILocation(line: 748, column: 16, scope: !1465)
!1465 = distinct !DILexicalBlock(scope: !1462, file: !115, line: 748, column: 16)
!1466 = !DILocation(line: 748, column: 35, scope: !1465)
!1467 = !DILocation(line: 748, column: 32, scope: !1465)
!1468 = !DILocation(line: 748, column: 16, scope: !1462)
!1469 = !DILocation(line: 750, column: 30, scope: !1470)
!1470 = distinct !DILexicalBlock(scope: !1465, file: !115, line: 749, column: 12)
!1471 = !DILocation(line: 750, column: 28, scope: !1470)
!1472 = !DILocation(line: 751, column: 49, scope: !1470)
!1473 = !DILocation(line: 751, column: 33, scope: !1470)
!1474 = !DILocation(line: 751, column: 31, scope: !1470)
!1475 = !DILocation(line: 752, column: 12, scope: !1470)
!1476 = !DILocation(line: 753, column: 9, scope: !1462)
!1477 = !DILocation(line: 756, column: 14, scope: !1478)
!1478 = distinct !DILexicalBlock(scope: !1336, file: !115, line: 756, column: 14)
!1479 = !DILocation(line: 756, column: 14, scope: !1336)
!1480 = !DILocalVariable(name: "wait_time", scope: !1481, file: !115, line: 758, type: !986)
!1481 = distinct !DILexicalBlock(scope: !1478, file: !115, line: 757, column: 9)
!1482 = !DILocation(line: 758, column: 28, scope: !1481)
!1483 = !DILocation(line: 760, column: 23, scope: !1481)
!1484 = !DILocation(line: 760, column: 30, scope: !1481)
!1485 = !DILocation(line: 761, column: 33, scope: !1481)
!1486 = !DILocation(line: 761, column: 23, scope: !1481)
!1487 = !DILocation(line: 761, column: 31, scope: !1481)
!1488 = !DILocation(line: 762, column: 13, scope: !1481)
!1489 = !DILocation(line: 763, column: 9, scope: !1481)
!1490 = !DILocation(line: 684, column: 2, scope: !1491)
!1491 = !DILexicalBlockFile(scope: !1337, file: !115, discriminator: 1)
!1492 = !DILocation(line: 768, column: 7, scope: !142)
!1493 = !DILocation(line: 768, column: 2, scope: !142)
!1494 = !DILocation(line: 772, column: 10, scope: !142)
!1495 = !DILocation(line: 772, column: 4, scope: !142)
!1496 = !DILocation(line: 775, column: 8, scope: !142)
!1497 = !DILocation(line: 775, column: 2, scope: !142)
!1498 = !DILocation(line: 776, column: 15, scope: !142)
!1499 = !DILocation(line: 776, column: 9, scope: !142)
!1500 = !DILocation(line: 777, column: 16, scope: !142)
!1501 = !DILocation(line: 778, column: 2, scope: !142)
!1502 = !DILocation(line: 779, column: 2, scope: !142)
!1503 = !DILocation(line: 780, column: 13, scope: !1504)
!1504 = distinct !DILexicalBlock(scope: !142, file: !115, line: 780, column: 13)
!1505 = !DILocation(line: 780, column: 13, scope: !142)
!1506 = !DILocation(line: 781, column: 22, scope: !1504)
!1507 = !DILocation(line: 781, column: 41, scope: !1504)
!1508 = !DILocation(line: 781, column: 11, scope: !1504)
!1509 = !DILocation(line: 783, column: 13, scope: !1510)
!1510 = distinct !DILexicalBlock(scope: !142, file: !115, line: 783, column: 13)
!1511 = !DILocation(line: 783, column: 13, scope: !142)
!1512 = !DILocation(line: 784, column: 17, scope: !1510)
!1513 = !DILocation(line: 784, column: 12, scope: !1510)
!1514 = !DILocation(line: 786, column: 1, scope: !142)
!1515 = !DILocalVariable(name: "script", arg: 1, scope: !182, file: !115, line: 1872, type: !56)
!1516 = !DILocation(line: 1872, column: 22, scope: !182)
!1517 = !DILocalVariable(name: "path", arg: 2, scope: !182, file: !115, line: 1872, type: !56)
!1518 = !DILocation(line: 1872, column: 36, scope: !182)
!1519 = !DILocalVariable(name: "process_id", scope: !182, file: !115, line: 1874, type: !1520)
!1520 = !DIDerivedType(tag: DW_TAG_typedef, name: "pid_t", file: !1521, line: 98, baseType: !1522)
!1521 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!1522 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pid_t", file: !54, line: 133, baseType: !64)
!1523 = !DILocation(line: 1874, column: 10, scope: !182)
!1524 = !DILocalVariable(name: "command_args", scope: !182, file: !115, line: 1875, type: !1525)
!1525 = !DICompositeType(tag: DW_TAG_array_type, baseType: !56, size: 192, align: 64, elements: !103)
!1526 = !DILocation(line: 1875, column: 10, scope: !182)
!1527 = !DILocation(line: 1875, column: 27, scope: !182)
!1528 = !DILocation(line: 1875, column: 29, scope: !182)
!1529 = !DILocation(line: 1875, column: 37, scope: !182)
!1530 = !DILocalVariable(name: "save_quit", scope: !182, file: !115, line: 1877, type: !1531)
!1531 = !DIDerivedType(tag: DW_TAG_typedef, name: "sig_t", file: !109, line: 209, baseType: !108)
!1532 = !DILocation(line: 1877, column: 10, scope: !182)
!1533 = !DILocalVariable(name: "save_int", scope: !182, file: !115, line: 1877, type: !1531)
!1534 = !DILocation(line: 1877, column: 21, scope: !182)
!1535 = !DILocalVariable(name: "save_chld", scope: !182, file: !115, line: 1877, type: !1531)
!1536 = !DILocation(line: 1877, column: 31, scope: !182)
!1537 = !DILocation(line: 1880, column: 16, scope: !182)
!1538 = !DILocation(line: 1880, column: 14, scope: !182)
!1539 = !DILocation(line: 1881, column: 15, scope: !182)
!1540 = !DILocation(line: 1881, column: 13, scope: !182)
!1541 = !DILocation(line: 1882, column: 16, scope: !182)
!1542 = !DILocation(line: 1882, column: 14, scope: !182)
!1543 = !DILocation(line: 1884, column: 17, scope: !182)
!1544 = !DILocation(line: 1884, column: 15, scope: !182)
!1545 = !DILocation(line: 1886, column: 8, scope: !1546)
!1546 = distinct !DILexicalBlock(scope: !182, file: !115, line: 1886, column: 8)
!1547 = !DILocation(line: 1886, column: 19, scope: !1546)
!1548 = !DILocation(line: 1886, column: 8, scope: !182)
!1549 = !DILocation(line: 1888, column: 23, scope: !1550)
!1550 = distinct !DILexicalBlock(scope: !1546, file: !115, line: 1887, column: 4)
!1551 = !DILocation(line: 1888, column: 7, scope: !1550)
!1552 = !DILocation(line: 1889, column: 22, scope: !1550)
!1553 = !DILocation(line: 1889, column: 7, scope: !1550)
!1554 = !DILocation(line: 1890, column: 23, scope: !1550)
!1555 = !DILocation(line: 1890, column: 7, scope: !1550)
!1556 = !DILocation(line: 1891, column: 7, scope: !1550)
!1557 = !DILocation(line: 1895, column: 8, scope: !1558)
!1558 = distinct !DILexicalBlock(scope: !182, file: !115, line: 1895, column: 8)
!1559 = !DILocation(line: 1895, column: 19, scope: !1558)
!1560 = !DILocation(line: 1895, column: 8, scope: !182)
!1561 = !DILocation(line: 1897, column: 7, scope: !1562)
!1562 = distinct !DILexicalBlock(scope: !1558, file: !115, line: 1896, column: 4)
!1563 = !DILocation(line: 1898, column: 7, scope: !1562)
!1564 = !DILocation(line: 1899, column: 7, scope: !1562)
!1565 = !DILocation(line: 1901, column: 13, scope: !1562)
!1566 = !DILocation(line: 1901, column: 21, scope: !1562)
!1567 = !DILocation(line: 1901, column: 7, scope: !1562)
!1568 = !DILocation(line: 1902, column: 53, scope: !1562)
!1569 = !DILocation(line: 1902, column: 7, scope: !1562)
!1570 = !DILocation(line: 1903, column: 7, scope: !1562)
!1571 = !DILocation(line: 1907, column: 4, scope: !182)
!1572 = !DILocation(line: 1909, column: 27, scope: !1573)
!1573 = distinct !DILexicalBlock(scope: !182, file: !115, line: 1908, column: 4)
!1574 = !DILocation(line: 1909, column: 39, scope: !1573)
!1575 = !DILocation(line: 1909, column: 21, scope: !1573)
!1576 = !DILocation(line: 1909, column: 19, scope: !1573)
!1577 = !DILocation(line: 1910, column: 4, scope: !1573)
!1578 = !DILocation(line: 1910, column: 15, scope: !1579)
!1579 = !DILexicalBlockFile(scope: !182, file: !115, discriminator: 1)
!1580 = !DILocation(line: 1910, column: 26, scope: !1579)
!1581 = !DILocation(line: 1910, column: 33, scope: !1579)
!1582 = !DILocation(line: 1910, column: 37, scope: !1583)
!1583 = !DILexicalBlockFile(scope: !182, file: !115, discriminator: 2)
!1584 = !DILocation(line: 1910, column: 43, scope: !1583)
!1585 = !DILocation(line: 1910, column: 4, scope: !1586)
!1586 = !DILexicalBlockFile(scope: !1573, file: !115, discriminator: 3)
!1587 = !DILocation(line: 1912, column: 20, scope: !182)
!1588 = !DILocation(line: 1912, column: 4, scope: !182)
!1589 = !DILocation(line: 1913, column: 19, scope: !182)
!1590 = !DILocation(line: 1913, column: 4, scope: !182)
!1591 = !DILocation(line: 1914, column: 20, scope: !182)
!1592 = !DILocation(line: 1914, column: 4, scope: !182)
!1593 = !DILocation(line: 1916, column: 4, scope: !182)
!1594 = !DILocation(line: 1917, column: 1, scope: !182)
!1595 = !DILocalVariable(name: "num_connections", arg: 1, scope: !179, file: !115, line: 1852, type: !64)
!1596 = !DILocation(line: 1852, column: 25, scope: !179)
!1597 = !DILocalVariable(name: "buffer_size", scope: !179, file: !115, line: 1854, type: !64)
!1598 = !DILocation(line: 1854, column: 8, scope: !179)
!1599 = !DILocation(line: 1856, column: 8, scope: !1600)
!1600 = distinct !DILexicalBlock(scope: !179, file: !115, line: 1856, column: 8)
!1601 = !DILocation(line: 1856, column: 24, scope: !1600)
!1602 = !DILocation(line: 1856, column: 8, scope: !179)
!1603 = !DILocation(line: 1857, column: 23, scope: !1600)
!1604 = !DILocation(line: 1857, column: 7, scope: !1600)
!1605 = !DILocation(line: 1859, column: 18, scope: !179)
!1606 = !DILocation(line: 1859, column: 33, scope: !179)
!1607 = !DILocation(line: 1859, column: 31, scope: !179)
!1608 = !DILocation(line: 1859, column: 16, scope: !179)
!1609 = !DILocation(line: 1860, column: 9, scope: !1610)
!1610 = distinct !DILexicalBlock(scope: !179, file: !115, line: 1860, column: 9)
!1611 = !DILocation(line: 1860, column: 21, scope: !1610)
!1612 = !DILocation(line: 1860, column: 9, scope: !179)
!1613 = !DILocation(line: 1861, column: 19, scope: !1610)
!1614 = !DILocation(line: 1861, column: 7, scope: !1610)
!1615 = !DILocation(line: 1863, column: 11, scope: !179)
!1616 = !DILocation(line: 1863, column: 4, scope: !179)
!1617 = !DILocalVariable(name: "filename", arg: 1, scope: !146, file: !115, line: 793, type: !56)
!1618 = !DILocation(line: 793, column: 25, scope: !146)
!1619 = !DILocation(line: 795, column: 13, scope: !146)
!1620 = !DILocation(line: 795, column: 5, scope: !146)
!1621 = !DILocation(line: 796, column: 1, scope: !146)
!1622 = !DILocalVariable(name: "filenames", arg: 1, scope: !147, file: !115, line: 802, type: !56)
!1623 = !DILocation(line: 802, column: 25, scope: !147)
!1624 = !DILocalVariable(name: "filename", scope: !147, file: !115, line: 804, type: !1061)
!1625 = !DILocation(line: 804, column: 9, scope: !147)
!1626 = !DILocalVariable(name: "from_index", scope: !147, file: !115, line: 805, type: !64)
!1627 = !DILocation(line: 805, column: 8, scope: !147)
!1628 = !DILocalVariable(name: "to_index", scope: !147, file: !115, line: 805, type: !64)
!1629 = !DILocation(line: 805, column: 20, scope: !147)
!1630 = !DILocation(line: 807, column: 15, scope: !147)
!1631 = !DILocation(line: 808, column: 4, scope: !147)
!1632 = !DILocation(line: 809, column: 13, scope: !147)
!1633 = !DILocation(line: 812, column: 4, scope: !147)
!1634 = !DILocation(line: 812, column: 22, scope: !1635)
!1635 = !DILexicalBlockFile(scope: !147, file: !115, discriminator: 1)
!1636 = !DILocation(line: 812, column: 12, scope: !1635)
!1637 = !DILocation(line: 812, column: 34, scope: !1635)
!1638 = !DILocation(line: 812, column: 4, scope: !1635)
!1639 = !DILocation(line: 815, column: 22, scope: !1640)
!1640 = distinct !DILexicalBlock(scope: !1641, file: !115, line: 815, column: 12)
!1641 = distinct !DILexicalBlock(scope: !147, file: !115, line: 813, column: 4)
!1642 = !DILocation(line: 815, column: 12, scope: !1640)
!1643 = !DILocation(line: 815, column: 34, scope: !1640)
!1644 = !DILocation(line: 815, column: 12, scope: !1641)
!1645 = !DILocation(line: 818, column: 24, scope: !1646)
!1646 = distinct !DILexicalBlock(scope: !1640, file: !115, line: 816, column: 8)
!1647 = !DILocation(line: 818, column: 11, scope: !1646)
!1648 = !DILocation(line: 820, column: 20, scope: !1646)
!1649 = !DILocation(line: 821, column: 11, scope: !1646)
!1650 = !DILocation(line: 823, column: 11, scope: !1646)
!1651 = !DILocation(line: 823, column: 28, scope: !1652)
!1652 = !DILexicalBlockFile(scope: !1646, file: !115, discriminator: 1)
!1653 = !DILocation(line: 823, column: 18, scope: !1652)
!1654 = !DILocation(line: 823, column: 40, scope: !1652)
!1655 = !DILocation(line: 823, column: 11, scope: !1652)
!1656 = !DILocation(line: 824, column: 23, scope: !1646)
!1657 = !DILocation(line: 823, column: 11, scope: !1658)
!1658 = !DILexicalBlockFile(scope: !1646, file: !115, discriminator: 2)
!1659 = !DILocation(line: 825, column: 8, scope: !1646)
!1660 = !DILocation(line: 830, column: 42, scope: !1661)
!1661 = distinct !DILexicalBlock(scope: !1640, file: !115, line: 829, column: 8)
!1662 = !DILocation(line: 830, column: 32, scope: !1661)
!1663 = !DILocation(line: 830, column: 20, scope: !1661)
!1664 = !DILocation(line: 830, column: 11, scope: !1661)
!1665 = !DILocation(line: 830, column: 30, scope: !1661)
!1666 = !DILocation(line: 831, column: 19, scope: !1661)
!1667 = !DILocation(line: 832, column: 21, scope: !1661)
!1668 = !DILocation(line: 834, column: 27, scope: !1669)
!1669 = distinct !DILexicalBlock(scope: !1661, file: !115, line: 834, column: 15)
!1670 = !DILocation(line: 834, column: 17, scope: !1669)
!1671 = !DILocation(line: 834, column: 15, scope: !1661)
!1672 = !DILocation(line: 836, column: 27, scope: !1673)
!1673 = distinct !DILexicalBlock(scope: !1669, file: !115, line: 835, column: 11)
!1674 = !DILocation(line: 836, column: 14, scope: !1673)
!1675 = !DILocation(line: 837, column: 23, scope: !1673)
!1676 = !DILocation(line: 838, column: 14, scope: !1673)
!1677 = !DILocation(line: 839, column: 24, scope: !1673)
!1678 = !DILocation(line: 840, column: 11, scope: !1673)
!1679 = !DILocation(line: 844, column: 12, scope: !1680)
!1680 = distinct !DILexicalBlock(scope: !1641, file: !115, line: 844, column: 12)
!1681 = !DILocation(line: 844, column: 21, scope: !1680)
!1682 = !DILocation(line: 844, column: 12, scope: !1641)
!1683 = !DILocation(line: 846, column: 53, scope: !1684)
!1684 = distinct !DILexicalBlock(scope: !1680, file: !115, line: 845, column: 8)
!1685 = !DILocation(line: 846, column: 4, scope: !1684)
!1686 = !DILocation(line: 847, column: 11, scope: !1684)
!1687 = !DILocation(line: 812, column: 4, scope: !1688)
!1688 = !DILexicalBlockFile(scope: !147, file: !115, discriminator: 2)
!1689 = !DILocation(line: 852, column: 1, scope: !147)
!1690 = !DILocalVariable(name: "filename", arg: 1, scope: !148, file: !115, line: 854, type: !56)
!1691 = !DILocation(line: 854, column: 25, scope: !148)
!1692 = !DILocalVariable(name: "num_clients", scope: !148, file: !115, line: 856, type: !64)
!1693 = !DILocation(line: 856, column: 13, scope: !148)
!1694 = !DILocalVariable(name: "new_num_clients", scope: !148, file: !115, line: 857, type: !64)
!1695 = !DILocation(line: 857, column: 13, scope: !148)
!1696 = !DILocalVariable(name: "my_buffer_size", scope: !148, file: !115, line: 858, type: !64)
!1697 = !DILocation(line: 858, column: 13, scope: !148)
!1698 = !DILocalVariable(name: "mapped", scope: !148, file: !115, line: 859, type: !56)
!1699 = !DILocation(line: 859, column: 8, scope: !148)
!1700 = !DILocalVariable(name: "buffer", scope: !148, file: !115, line: 860, type: !56)
!1701 = !DILocation(line: 860, column: 8, scope: !148)
!1702 = !DILocalVariable(name: "xfer_delay", scope: !148, file: !115, line: 861, type: !64)
!1703 = !DILocation(line: 861, column: 13, scope: !148)
!1704 = !DILocalVariable(name: "wait_time", scope: !148, file: !115, line: 862, type: !986)
!1705 = !DILocation(line: 862, column: 24, scope: !148)
!1706 = !DILocalVariable(name: "get_value", scope: !148, file: !115, line: 863, type: !72)
!1707 = !DILocation(line: 863, column: 23, scope: !148)
!1708 = !DILocalVariable(name: "send_status", scope: !148, file: !115, line: 864, type: !1709)
!1709 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !257, line: 102, baseType: !1710)
!1710 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !54, line: 172, baseType: !63)
!1711 = !DILocation(line: 864, column: 17, scope: !148)
!1712 = !DILocalVariable(name: "change_buffer_size", scope: !148, file: !115, line: 865, type: !64)
!1713 = !DILocation(line: 865, column: 13, scope: !148)
!1714 = !DILocalVariable(name: "phile", scope: !148, file: !115, line: 870, type: !64)
!1715 = !DILocation(line: 870, column: 6, scope: !148)
!1716 = !DILocalVariable(name: "i", scope: !148, file: !115, line: 871, type: !64)
!1717 = !DILocation(line: 871, column: 6, scope: !148)
!1718 = !DILocalVariable(name: "whattodo", scope: !148, file: !115, line: 871, type: !64)
!1719 = !DILocation(line: 871, column: 9, scope: !148)
!1720 = !DILocalVariable(name: "statbuf", scope: !148, file: !115, line: 872, type: !67)
!1721 = !DILocation(line: 872, column: 14, scope: !148)
!1722 = !DILocation(line: 883, column: 30, scope: !148)
!1723 = !DILocation(line: 883, column: 21, scope: !1724)
!1724 = !DILexicalBlockFile(scope: !148, file: !115, discriminator: 1)
!1725 = !DILocation(line: 883, column: 19, scope: !148)
!1726 = !DILocation(line: 884, column: 13, scope: !1727)
!1727 = distinct !DILexicalBlock(scope: !148, file: !115, line: 884, column: 13)
!1728 = !DILocation(line: 884, column: 23, scope: !1727)
!1729 = !DILocation(line: 884, column: 13, scope: !148)
!1730 = !DILocation(line: 885, column: 25, scope: !1727)
!1731 = !DILocation(line: 885, column: 23, scope: !1727)
!1732 = !DILocation(line: 885, column: 12, scope: !1727)
!1733 = !DILocation(line: 888, column: 12, scope: !1734)
!1734 = distinct !DILexicalBlock(scope: !1727, file: !115, line: 887, column: 9)
!1735 = !DILocation(line: 889, column: 23, scope: !1734)
!1736 = !DILocation(line: 892, column: 29, scope: !148)
!1737 = !DILocation(line: 892, column: 11, scope: !148)
!1738 = !DILocation(line: 892, column: 9, scope: !148)
!1739 = !DILocation(line: 893, column: 15, scope: !1740)
!1740 = distinct !DILexicalBlock(scope: !148, file: !115, line: 893, column: 13)
!1741 = !DILocation(line: 893, column: 13, scope: !148)
!1742 = !DILocation(line: 895, column: 12, scope: !1743)
!1743 = distinct !DILexicalBlock(scope: !1740, file: !115, line: 894, column: 9)
!1744 = !DILocation(line: 896, column: 12, scope: !1743)
!1745 = !DILocation(line: 897, column: 12, scope: !1743)
!1746 = !DILocation(line: 900, column: 27, scope: !1747)
!1747 = distinct !DILexicalBlock(scope: !148, file: !115, line: 900, column: 13)
!1748 = !DILocation(line: 900, column: 15, scope: !1749)
!1749 = !DILexicalBlockFile(scope: !1747, file: !115, discriminator: 1)
!1750 = !DILocation(line: 900, column: 15, scope: !1747)
!1751 = !DILocation(line: 900, column: 13, scope: !148)
!1752 = !DILocation(line: 901, column: 31, scope: !1747)
!1753 = !DILocation(line: 901, column: 12, scope: !1747)
!1754 = !DILocation(line: 903, column: 15, scope: !148)
!1755 = !DILocation(line: 903, column: 10, scope: !148)
!1756 = !DILocation(line: 903, column: 8, scope: !148)
!1757 = !DILocation(line: 904, column: 6, scope: !1758)
!1758 = distinct !DILexicalBlock(scope: !148, file: !115, line: 904, column: 6)
!1759 = !DILocation(line: 904, column: 12, scope: !1758)
!1760 = !DILocation(line: 904, column: 6, scope: !148)
!1761 = !DILocation(line: 926, column: 7, scope: !1762)
!1762 = distinct !DILexicalBlock(scope: !1763, file: !115, line: 926, column: 7)
!1763 = distinct !DILexicalBlock(scope: !1758, file: !115, line: 904, column: 19)
!1764 = !DILocation(line: 926, column: 16, scope: !1762)
!1765 = !DILocation(line: 926, column: 7, scope: !1763)
!1766 = !DILocation(line: 928, column: 17, scope: !1767)
!1767 = distinct !DILexicalBlock(scope: !1762, file: !115, line: 926, column: 30)
!1768 = !DILocation(line: 928, column: 8, scope: !1769)
!1769 = !DILexicalBlockFile(scope: !1767, file: !115, discriminator: 1)
!1770 = !DILocation(line: 928, column: 25, scope: !1767)
!1771 = !DILocation(line: 927, column: 4, scope: !1767)
!1772 = !DILocation(line: 929, column: 58, scope: !1767)
!1773 = !DILocation(line: 929, column: 49, scope: !1769)
!1774 = !DILocation(line: 929, column: 4, scope: !1775)
!1775 = !DILexicalBlockFile(scope: !1767, file: !115, discriminator: 2)
!1776 = !DILocation(line: 930, column: 8, scope: !1777)
!1777 = distinct !DILexicalBlock(scope: !1767, file: !115, line: 930, column: 8)
!1778 = !DILocation(line: 930, column: 8, scope: !1767)
!1779 = !DILocation(line: 931, column: 10, scope: !1777)
!1780 = !DILocation(line: 931, column: 5, scope: !1777)
!1781 = !DILocation(line: 932, column: 4, scope: !1767)
!1782 = !DILocation(line: 934, column: 2, scope: !1763)
!1783 = !DILocation(line: 952, column: 7, scope: !148)
!1784 = !DILocation(line: 952, column: 2, scope: !148)
!1785 = !DILocation(line: 953, column: 6, scope: !1786)
!1786 = distinct !DILexicalBlock(scope: !148, file: !115, line: 953, column: 6)
!1787 = !DILocation(line: 953, column: 6, scope: !148)
!1788 = !DILocation(line: 954, column: 3, scope: !1789)
!1789 = distinct !DILexicalBlock(scope: !1786, file: !115, line: 953, column: 32)
!1790 = !DILocation(line: 955, column: 7, scope: !1791)
!1791 = distinct !DILexicalBlock(scope: !1789, file: !115, line: 955, column: 7)
!1792 = !DILocation(line: 955, column: 7, scope: !1789)
!1793 = !DILocation(line: 956, column: 9, scope: !1791)
!1794 = !DILocation(line: 956, column: 4, scope: !1791)
!1795 = !DILocation(line: 957, column: 3, scope: !1789)
!1796 = !DILocation(line: 960, column: 17, scope: !1797)
!1797 = distinct !DILexicalBlock(scope: !148, file: !115, line: 960, column: 6)
!1798 = !DILocation(line: 960, column: 27, scope: !1797)
!1799 = !DILocation(line: 960, column: 25, scope: !1797)
!1800 = !DILocation(line: 960, column: 37, scope: !1797)
!1801 = !DILocation(line: 960, column: 35, scope: !1797)
!1802 = !DILocation(line: 960, column: 51, scope: !1797)
!1803 = !DILocation(line: 960, column: 49, scope: !1797)
!1804 = !DILocation(line: 960, column: 7, scope: !1797)
!1805 = !DILocation(line: 960, column: 64, scope: !1797)
!1806 = !DILocation(line: 961, column: 6, scope: !1797)
!1807 = !DILocation(line: 961, column: 4, scope: !1797)
!1808 = !DILocation(line: 960, column: 62, scope: !1797)
!1809 = !DILocation(line: 961, column: 18, scope: !1797)
!1810 = !DILocation(line: 961, column: 38, scope: !1811)
!1811 = !DILexicalBlockFile(scope: !1797, file: !115, discriminator: 1)
!1812 = !DILocation(line: 961, column: 22, scope: !1813)
!1813 = !DILexicalBlockFile(scope: !1811, file: !115, discriminator: 2)
!1814 = !DILocation(line: 961, column: 22, scope: !1811)
!1815 = !DILocation(line: 960, column: 6, scope: !1724)
!1816 = !DILocation(line: 963, column: 18, scope: !1817)
!1817 = distinct !DILexicalBlock(scope: !1797, file: !115, line: 961, column: 75)
!1818 = !DILocation(line: 962, column: 3, scope: !1817)
!1819 = !DILocation(line: 965, column: 25, scope: !1817)
!1820 = !DILocation(line: 965, column: 35, scope: !1817)
!1821 = !DILocation(line: 965, column: 33, scope: !1817)
!1822 = !DILocation(line: 965, column: 45, scope: !1817)
!1823 = !DILocation(line: 965, column: 43, scope: !1817)
!1824 = !DILocation(line: 965, column: 59, scope: !1817)
!1825 = !DILocation(line: 965, column: 57, scope: !1817)
!1826 = !DILocation(line: 965, column: 5, scope: !1817)
!1827 = !DILocation(line: 966, column: 7, scope: !1817)
!1828 = !DILocation(line: 966, column: 5, scope: !1817)
!1829 = !DILocation(line: 964, column: 3, scope: !1817)
!1830 = !DILocation(line: 967, column: 7, scope: !1831)
!1831 = distinct !DILexicalBlock(scope: !1817, file: !115, line: 967, column: 7)
!1832 = !DILocation(line: 967, column: 7, scope: !1817)
!1833 = !DILocation(line: 968, column: 9, scope: !1831)
!1834 = !DILocation(line: 968, column: 4, scope: !1831)
!1835 = !DILocation(line: 969, column: 3, scope: !1817)
!1836 = !DILocation(line: 971, column: 48, scope: !148)
!1837 = !DILocation(line: 971, column: 2, scope: !148)
!1838 = !DILocation(line: 972, column: 10, scope: !148)
!1839 = !DILocation(line: 972, column: 2, scope: !148)
!1840 = !DILocation(line: 1199, column: 8, scope: !1841)
!1841 = distinct !DILexicalBlock(scope: !1842, file: !115, line: 1199, column: 8)
!1842 = distinct !DILexicalBlock(scope: !148, file: !115, line: 972, column: 20)
!1843 = !DILocation(line: 1199, column: 8, scope: !1842)
!1844 = !DILocation(line: 1201, column: 10, scope: !1845)
!1845 = distinct !DILexicalBlock(scope: !1841, file: !115, line: 1200, column: 25)
!1846 = !DILocation(line: 1201, column: 5, scope: !1845)
!1847 = !DILocation(line: 1202, column: 40, scope: !1845)
!1848 = !DILocation(line: 1203, column: 25, scope: !1845)
!1849 = !DILocation(line: 1204, column: 8, scope: !1850)
!1850 = distinct !DILexicalBlock(scope: !1842, file: !115, line: 1204, column: 8)
!1851 = !DILocation(line: 1204, column: 8, scope: !1842)
!1852 = !DILocation(line: 1205, column: 5, scope: !1850)
!1853 = !DILocation(line: 1206, column: 25, scope: !1842)
!1854 = !DILocation(line: 1207, column: 10, scope: !1842)
!1855 = !DILocation(line: 1207, column: 17, scope: !1842)
!1856 = !DILocation(line: 1207, column: 4, scope: !1842)
!1857 = !DILocation(line: 1208, column: 11, scope: !1842)
!1858 = !DILocation(line: 1209, column: 20, scope: !1842)
!1859 = !DILocation(line: 1209, column: 33, scope: !1842)
!1860 = !DILocation(line: 1209, column: 37, scope: !1842)
!1861 = !DILocation(line: 1209, column: 13, scope: !1842)
!1862 = !DILocation(line: 1209, column: 11, scope: !1842)
!1863 = !DILocation(line: 1211, column: 31, scope: !1864)
!1864 = distinct !DILexicalBlock(scope: !1842, file: !115, line: 1211, column: 29)
!1865 = !DILocation(line: 1211, column: 29, scope: !1842)
!1866 = !DILocation(line: 1213, column: 29, scope: !1867)
!1867 = distinct !DILexicalBlock(scope: !1864, file: !115, line: 1212, column: 25)
!1868 = !DILocation(line: 1214, column: 29, scope: !1867)
!1869 = !DILocation(line: 1215, column: 35, scope: !1867)
!1870 = !DILocation(line: 1215, column: 29, scope: !1867)
!1871 = !DILocation(line: 1216, column: 35, scope: !1867)
!1872 = !DILocation(line: 1216, column: 29, scope: !1867)
!1873 = !DILocation(line: 1217, column: 29, scope: !1867)
!1874 = !DILocation(line: 1219, column: 29, scope: !1875)
!1875 = distinct !DILexicalBlock(scope: !1842, file: !115, line: 1219, column: 29)
!1876 = !DILocation(line: 1219, column: 29, scope: !1842)
!1877 = !DILocation(line: 1221, column: 41, scope: !1878)
!1878 = distinct !DILexicalBlock(scope: !1875, file: !115, line: 1220, column: 25)
!1879 = !DILocation(line: 1221, column: 39, scope: !1878)
!1880 = !DILocation(line: 1222, column: 60, scope: !1878)
!1881 = !DILocation(line: 1222, column: 44, scope: !1878)
!1882 = !DILocation(line: 1222, column: 42, scope: !1878)
!1883 = !DILocation(line: 1223, column: 25, scope: !1878)
!1884 = !DILocation(line: 1225, column: 46, scope: !1875)
!1885 = !DILocation(line: 1225, column: 44, scope: !1875)
!1886 = !DILocation(line: 1227, column: 4, scope: !1842)
!1887 = !DILocation(line: 1227, column: 21, scope: !1888)
!1888 = !DILexicalBlockFile(scope: !1842, file: !115, discriminator: 1)
!1889 = !DILocation(line: 1227, column: 28, scope: !1888)
!1890 = !DILocation(line: 1227, column: 36, scope: !1888)
!1891 = !DILocation(line: 1227, column: 16, scope: !1888)
!1892 = !DILocation(line: 1227, column: 14, scope: !1888)
!1893 = !DILocation(line: 1227, column: 4, scope: !1888)
!1894 = !DILocation(line: 1228, column: 23, scope: !1895)
!1895 = distinct !DILexicalBlock(scope: !1896, file: !115, line: 1228, column: 9)
!1896 = distinct !DILexicalBlock(scope: !1842, file: !115, line: 1227, column: 54)
!1897 = !DILocation(line: 1228, column: 30, scope: !1895)
!1898 = !DILocation(line: 1228, column: 9, scope: !1895)
!1899 = !DILocation(line: 1228, column: 9, scope: !1896)
!1900 = !DILocation(line: 1229, column: 11, scope: !1901)
!1901 = distinct !DILexicalBlock(scope: !1895, file: !115, line: 1228, column: 37)
!1902 = !DILocation(line: 1229, column: 6, scope: !1901)
!1903 = !DILocation(line: 1230, column: 6, scope: !1901)
!1904 = !DILocation(line: 1233, column: 21, scope: !1905)
!1905 = distinct !DILexicalBlock(scope: !1896, file: !115, line: 1233, column: 21)
!1906 = !DILocation(line: 1233, column: 30, scope: !1905)
!1907 = !DILocation(line: 1233, column: 21, scope: !1896)
!1908 = !DILocation(line: 1234, column: 28, scope: !1909)
!1909 = distinct !DILexicalBlock(scope: !1905, file: !115, line: 1233, column: 45)
!1910 = !DILocation(line: 1234, column: 21, scope: !1909)
!1911 = !DILocation(line: 1234, column: 31, scope: !1909)
!1912 = !DILocation(line: 1235, column: 34, scope: !1909)
!1913 = !DILocation(line: 1235, column: 56, scope: !1909)
!1914 = !DILocation(line: 1235, column: 26, scope: !1909)
!1915 = !DILocation(line: 1235, column: 23, scope: !1909)
!1916 = !DILocation(line: 1236, column: 17, scope: !1909)
!1917 = !DILocation(line: 1237, column: 24, scope: !1896)
!1918 = !DILocation(line: 1237, column: 30, scope: !1896)
!1919 = !DILocation(line: 1237, column: 38, scope: !1896)
!1920 = !DILocation(line: 1237, column: 19, scope: !1896)
!1921 = !DILocation(line: 1237, column: 17, scope: !1896)
!1922 = !DILocation(line: 1239, column: 37, scope: !1923)
!1923 = distinct !DILexicalBlock(scope: !1896, file: !115, line: 1239, column: 37)
!1924 = !DILocation(line: 1239, column: 49, scope: !1923)
!1925 = !DILocation(line: 1239, column: 37, scope: !1896)
!1926 = !DILocation(line: 1241, column: 41, scope: !1927)
!1927 = distinct !DILexicalBlock(scope: !1923, file: !115, line: 1240, column: 33)
!1928 = !DILocation(line: 1241, column: 36, scope: !1927)
!1929 = !DILocation(line: 1242, column: 42, scope: !1927)
!1930 = !DILocation(line: 1242, column: 36, scope: !1927)
!1931 = !DILocation(line: 1243, column: 42, scope: !1927)
!1932 = !DILocation(line: 1243, column: 36, scope: !1927)
!1933 = !DILocation(line: 1244, column: 42, scope: !1927)
!1934 = !DILocation(line: 1244, column: 36, scope: !1927)
!1935 = !DILocation(line: 1245, column: 36, scope: !1927)
!1936 = !DILocation(line: 1246, column: 36, scope: !1927)
!1937 = !DILocation(line: 1247, column: 36, scope: !1927)
!1938 = !DILocation(line: 1248, column: 36, scope: !1927)
!1939 = !DILocation(line: 1251, column: 19, scope: !1896)
!1940 = !DILocation(line: 1251, column: 16, scope: !1896)
!1941 = !DILocation(line: 1253, column: 37, scope: !1942)
!1942 = distinct !DILexicalBlock(scope: !1896, file: !115, line: 1253, column: 37)
!1943 = !DILocation(line: 1253, column: 37, scope: !1896)
!1944 = !DILocation(line: 1255, column: 53, scope: !1945)
!1945 = distinct !DILexicalBlock(scope: !1942, file: !115, line: 1254, column: 33)
!1946 = !DILocation(line: 1255, column: 51, scope: !1945)
!1947 = !DILocation(line: 1256, column: 68, scope: !1945)
!1948 = !DILocation(line: 1256, column: 52, scope: !1945)
!1949 = !DILocation(line: 1256, column: 50, scope: !1945)
!1950 = !DILocation(line: 1257, column: 33, scope: !1945)
!1951 = !DILocation(line: 1260, column: 37, scope: !1952)
!1952 = distinct !DILexicalBlock(scope: !1896, file: !115, line: 1260, column: 37)
!1953 = !DILocation(line: 1260, column: 37, scope: !1896)
!1954 = !DILocation(line: 1262, column: 46, scope: !1955)
!1955 = distinct !DILexicalBlock(scope: !1952, file: !115, line: 1261, column: 33)
!1956 = !DILocation(line: 1262, column: 53, scope: !1955)
!1957 = !DILocation(line: 1263, column: 56, scope: !1955)
!1958 = !DILocation(line: 1263, column: 46, scope: !1955)
!1959 = !DILocation(line: 1263, column: 54, scope: !1955)
!1960 = !DILocation(line: 1264, column: 36, scope: !1955)
!1961 = !DILocation(line: 1265, column: 33, scope: !1955)
!1962 = !DILocation(line: 1227, column: 4, scope: !1963)
!1963 = !DILexicalBlockFile(scope: !1842, file: !115, discriminator: 2)
!1964 = !DILocation(line: 1268, column: 18, scope: !1842)
!1965 = !DILocation(line: 1268, column: 13, scope: !1842)
!1966 = !DILocation(line: 1269, column: 13, scope: !1842)
!1967 = !DILocation(line: 1271, column: 8, scope: !148)
!1968 = !DILocation(line: 1271, column: 2, scope: !148)
!1969 = !DILocation(line: 1272, column: 8, scope: !148)
!1970 = !DILocation(line: 1272, column: 2, scope: !148)
!1971 = !DILocation(line: 1273, column: 16, scope: !148)
!1972 = !DILocation(line: 1274, column: 15, scope: !148)
!1973 = !DILocation(line: 1274, column: 9, scope: !148)
!1974 = !DILocation(line: 1275, column: 2, scope: !148)
!1975 = !DILocation(line: 1276, column: 55, scope: !148)
!1976 = !DILocation(line: 1276, column: 2, scope: !148)
!1977 = !DILocation(line: 1277, column: 13, scope: !1978)
!1978 = distinct !DILexicalBlock(scope: !148, file: !115, line: 1277, column: 13)
!1979 = !DILocation(line: 1277, column: 13, scope: !148)
!1980 = !DILocation(line: 1277, column: 26, scope: !1981)
!1981 = !DILexicalBlockFile(scope: !1978, file: !115, discriminator: 1)
!1982 = !DILocation(line: 1277, column: 21, scope: !1981)
!1983 = !DILocation(line: 1279, column: 1, scope: !148)
!1984 = !DILocalVariable(name: "dirname", arg: 1, scope: !149, file: !115, line: 1281, type: !56)
!1985 = !DILocation(line: 1281, column: 23, scope: !149)
!1986 = !DILocalVariable(name: "verbose", arg: 2, scope: !149, file: !115, line: 1281, type: !47)
!1987 = !DILocation(line: 1281, column: 37, scope: !149)
!1988 = !DILocalVariable(name: "show_hidden", scope: !149, file: !115, line: 1283, type: !64)
!1989 = !DILocation(line: 1283, column: 13, scope: !149)
!1990 = !DILocalVariable(name: "datastream", scope: !149, file: !115, line: 1284, type: !1991)
!1991 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1992, size: 64, align: 64)
!1992 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !257, line: 48, baseType: !1993)
!1993 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !1994, line: 245, size: 1728, align: 64, elements: !1995)
!1994 = !DIFile(filename: "/usr/include/libio.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!1995 = !{!1996, !1997, !1998, !1999, !2000, !2001, !2002, !2003, !2004, !2005, !2006, !2007, !2008, !2016, !2017, !2018, !2019, !2020, !2021, !2023, !2025, !2028, !2030, !2031, !2032, !2033, !2034, !2037, !2038}
!1996 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !1993, file: !1994, line: 246, baseType: !64, size: 32, align: 32)
!1997 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !1993, file: !1994, line: 251, baseType: !56, size: 64, align: 64, offset: 64)
!1998 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !1993, file: !1994, line: 252, baseType: !56, size: 64, align: 64, offset: 128)
!1999 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !1993, file: !1994, line: 253, baseType: !56, size: 64, align: 64, offset: 192)
!2000 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !1993, file: !1994, line: 254, baseType: !56, size: 64, align: 64, offset: 256)
!2001 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !1993, file: !1994, line: 255, baseType: !56, size: 64, align: 64, offset: 320)
!2002 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !1993, file: !1994, line: 256, baseType: !56, size: 64, align: 64, offset: 384)
!2003 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !1993, file: !1994, line: 257, baseType: !56, size: 64, align: 64, offset: 448)
!2004 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !1993, file: !1994, line: 258, baseType: !56, size: 64, align: 64, offset: 512)
!2005 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !1993, file: !1994, line: 260, baseType: !56, size: 64, align: 64, offset: 576)
!2006 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !1993, file: !1994, line: 261, baseType: !56, size: 64, align: 64, offset: 640)
!2007 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !1993, file: !1994, line: 262, baseType: !56, size: 64, align: 64, offset: 704)
!2008 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !1993, file: !1994, line: 264, baseType: !2009, size: 64, align: 64, offset: 768)
!2009 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !2010, size: 64, align: 64)
!2010 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !1994, line: 160, size: 192, align: 64, elements: !2011)
!2011 = !{!2012, !2013, !2015}
!2012 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !2010, file: !1994, line: 161, baseType: !2009, size: 64, align: 64)
!2013 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !2010, file: !1994, line: 162, baseType: !2014, size: 64, align: 64, offset: 64)
!2014 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1993, size: 64, align: 64)
!2015 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !2010, file: !1994, line: 166, baseType: !64, size: 32, align: 32, offset: 128)
!2016 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !1993, file: !1994, line: 266, baseType: !2014, size: 64, align: 64, offset: 832)
!2017 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !1993, file: !1994, line: 268, baseType: !64, size: 32, align: 32, offset: 896)
!2018 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !1993, file: !1994, line: 272, baseType: !64, size: 32, align: 32, offset: 928)
!2019 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !1993, file: !1994, line: 274, baseType: !86, size: 64, align: 64, offset: 960)
!2020 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !1993, file: !1994, line: 278, baseType: !44, size: 16, align: 16, offset: 1024)
!2021 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !1993, file: !1994, line: 279, baseType: !2022, size: 8, align: 8, offset: 1040)
!2022 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!2023 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !1993, file: !1994, line: 280, baseType: !2024, size: 8, align: 8, offset: 1048)
!2024 = !DICompositeType(tag: DW_TAG_array_type, baseType: !47, size: 8, align: 8, elements: !268)
!2025 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !1993, file: !1994, line: 284, baseType: !2026, size: 64, align: 64, offset: 1088)
!2026 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !2027, size: 64, align: 64)
!2027 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !1994, line: 154, baseType: null)
!2028 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !1993, file: !1994, line: 293, baseType: !2029, size: 64, align: 64, offset: 1152)
!2029 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !54, line: 132, baseType: !63)
!2030 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !1993, file: !1994, line: 302, baseType: !36, size: 64, align: 64, offset: 1216)
!2031 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !1993, file: !1994, line: 303, baseType: !36, size: 64, align: 64, offset: 1280)
!2032 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !1993, file: !1994, line: 304, baseType: !36, size: 64, align: 64, offset: 1344)
!2033 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !1993, file: !1994, line: 305, baseType: !36, size: 64, align: 64, offset: 1408)
!2034 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !1993, file: !1994, line: 306, baseType: !2035, size: 64, align: 64, offset: 1472)
!2035 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !2036, line: 62, baseType: !72)
!2036 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!2037 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !1993, file: !1994, line: 308, baseType: !64, size: 32, align: 32, offset: 1536)
!2038 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !1993, file: !1994, line: 310, baseType: !674, size: 160, align: 8, offset: 1568)
!2039 = !DILocation(line: 1284, column: 8, scope: !149)
!2040 = !DILocation(line: 1286, column: 6, scope: !2041)
!2041 = distinct !DILexicalBlock(scope: !149, file: !115, line: 1286, column: 6)
!2042 = !DILocation(line: 1286, column: 17, scope: !2041)
!2043 = !DILocation(line: 1286, column: 6, scope: !149)
!2044 = !DILocation(line: 1288, column: 23, scope: !2045)
!2045 = distinct !DILexicalBlock(scope: !2046, file: !115, line: 1288, column: 22)
!2046 = distinct !DILexicalBlock(scope: !2041, file: !115, line: 1286, column: 26)
!2047 = !DILocation(line: 1288, column: 34, scope: !2045)
!2048 = !DILocation(line: 1288, column: 43, scope: !2045)
!2049 = !DILocation(line: 1288, column: 47, scope: !2050)
!2050 = !DILexicalBlockFile(scope: !2045, file: !115, discriminator: 1)
!2051 = !DILocation(line: 1288, column: 58, scope: !2050)
!2052 = !DILocation(line: 1288, column: 22, scope: !2050)
!2053 = !DILocation(line: 1290, column: 32, scope: !2054)
!2054 = distinct !DILexicalBlock(scope: !2045, file: !115, line: 1289, column: 17)
!2055 = !DILocation(line: 1291, column: 20, scope: !2054)
!2056 = !DILocation(line: 1291, column: 28, scope: !2057)
!2057 = !DILexicalBlockFile(scope: !2054, file: !115, discriminator: 1)
!2058 = !DILocation(line: 1291, column: 39, scope: !2057)
!2059 = !DILocation(line: 1291, column: 47, scope: !2057)
!2060 = !DILocation(line: 1291, column: 51, scope: !2061)
!2061 = !DILexicalBlockFile(scope: !2054, file: !115, discriminator: 2)
!2062 = !DILocation(line: 1291, column: 62, scope: !2061)
!2063 = !DILocation(line: 1291, column: 20, scope: !2064)
!2064 = !DILexicalBlockFile(scope: !2054, file: !115, discriminator: 3)
!2065 = !DILocation(line: 1292, column: 40, scope: !2054)
!2066 = !DILocation(line: 1291, column: 20, scope: !2067)
!2067 = !DILexicalBlockFile(scope: !2054, file: !115, discriminator: 4)
!2068 = !DILocation(line: 1293, column: 24, scope: !2069)
!2069 = distinct !DILexicalBlock(scope: !2054, file: !115, line: 1293, column: 24)
!2070 = !DILocation(line: 1293, column: 35, scope: !2069)
!2071 = !DILocation(line: 1293, column: 24, scope: !2054)
!2072 = !DILocation(line: 1294, column: 34, scope: !2069)
!2073 = !DILocation(line: 1294, column: 27, scope: !2069)
!2074 = !DILocation(line: 1295, column: 17, scope: !2054)
!2075 = !DILocation(line: 1297, column: 12, scope: !2076)
!2076 = distinct !DILexicalBlock(scope: !2045, file: !115, line: 1297, column: 12)
!2077 = !DILocation(line: 1297, column: 23, scope: !2076)
!2078 = !DILocation(line: 1297, column: 12, scope: !2045)
!2079 = !DILocation(line: 1298, column: 4, scope: !2080)
!2080 = distinct !DILexicalBlock(scope: !2076, file: !115, line: 1297, column: 31)
!2081 = !DILocation(line: 1298, column: 12, scope: !2082)
!2082 = !DILexicalBlockFile(scope: !2080, file: !115, discriminator: 1)
!2083 = !DILocation(line: 1298, column: 23, scope: !2082)
!2084 = !DILocation(line: 1298, column: 31, scope: !2082)
!2085 = !DILocation(line: 1298, column: 35, scope: !2086)
!2086 = !DILexicalBlockFile(scope: !2080, file: !115, discriminator: 2)
!2087 = !DILocation(line: 1298, column: 46, scope: !2086)
!2088 = !DILocation(line: 1298, column: 4, scope: !2089)
!2089 = !DILexicalBlockFile(scope: !2080, file: !115, discriminator: 3)
!2090 = !DILocation(line: 1299, column: 12, scope: !2080)
!2091 = !DILocation(line: 1298, column: 4, scope: !2092)
!2092 = !DILexicalBlockFile(scope: !2080, file: !115, discriminator: 4)
!2093 = !DILocation(line: 1300, column: 8, scope: !2094)
!2094 = distinct !DILexicalBlock(scope: !2080, file: !115, line: 1300, column: 8)
!2095 = !DILocation(line: 1300, column: 19, scope: !2094)
!2096 = !DILocation(line: 1300, column: 8, scope: !2080)
!2097 = !DILocation(line: 1301, column: 12, scope: !2094)
!2098 = !DILocation(line: 1301, column: 5, scope: !2094)
!2099 = !DILocation(line: 1302, column: 3, scope: !2080)
!2100 = !DILocation(line: 1303, column: 2, scope: !2046)
!2101 = !DILocation(line: 1304, column: 6, scope: !2102)
!2102 = distinct !DILexicalBlock(scope: !149, file: !115, line: 1304, column: 6)
!2103 = !DILocation(line: 1304, column: 6, scope: !149)
!2104 = !DILocation(line: 1305, column: 3, scope: !2102)
!2105 = !DILocation(line: 1306, column: 9, scope: !149)
!2106 = !DILocation(line: 1307, column: 22, scope: !149)
!2107 = !DILocation(line: 1307, column: 15, scope: !149)
!2108 = !DILocation(line: 1307, column: 13, scope: !149)
!2109 = !DILocation(line: 1308, column: 6, scope: !2110)
!2110 = distinct !DILexicalBlock(scope: !149, file: !115, line: 1308, column: 6)
!2111 = !DILocation(line: 1308, column: 17, scope: !2110)
!2112 = !DILocation(line: 1308, column: 6, scope: !149)
!2113 = !DILocation(line: 1309, column: 16, scope: !2110)
!2114 = !DILocation(line: 1309, column: 28, scope: !2110)
!2115 = !DILocation(line: 1309, column: 37, scope: !2110)
!2116 = !DILocation(line: 1309, column: 3, scope: !2110)
!2117 = !DILocalVariable(name: "mapped", scope: !2118, file: !115, line: 1311, type: !56)
!2118 = distinct !DILexicalBlock(scope: !2110, file: !115, line: 1310, column: 7)
!2119 = !DILocation(line: 1311, column: 9, scope: !2118)
!2120 = !DILocation(line: 1311, column: 36, scope: !2118)
!2121 = !DILocation(line: 1311, column: 18, scope: !2118)
!2122 = !DILocation(line: 1312, column: 11, scope: !2118)
!2123 = !DILocation(line: 1312, column: 19, scope: !2118)
!2124 = !DILocation(line: 1312, column: 31, scope: !2118)
!2125 = !DILocation(line: 1312, column: 40, scope: !2118)
!2126 = !DILocation(line: 1312, column: 3, scope: !2118)
!2127 = !DILocation(line: 1313, column: 8, scope: !2118)
!2128 = !DILocation(line: 1313, column: 3, scope: !2118)
!2129 = !DILocation(line: 1315, column: 9, scope: !149)
!2130 = !DILocation(line: 1315, column: 2, scope: !149)
!2131 = !DILocation(line: 1316, column: 15, scope: !149)
!2132 = !DILocation(line: 1316, column: 9, scope: !149)
!2133 = !DILocation(line: 1317, column: 2, scope: !149)
!2134 = !DILocation(line: 1318, column: 1, scope: !149)
!2135 = !DILocation(line: 1318, column: 1, scope: !2136)
!2136 = !DILexicalBlockFile(scope: !149, file: !115, discriminator: 1)
!2137 = !DILocalVariable(name: "dirname", arg: 1, scope: !152, file: !115, line: 1320, type: !56)
!2138 = !DILocation(line: 1320, column: 25, scope: !152)
!2139 = !DILocation(line: 1322, column: 13, scope: !152)
!2140 = !DILocation(line: 1322, column: 2, scope: !152)
!2141 = !DILocation(line: 1323, column: 1, scope: !152)
!2142 = !DILocalVariable(name: "dirname", arg: 1, scope: !153, file: !115, line: 1325, type: !56)
!2143 = !DILocation(line: 1325, column: 25, scope: !153)
!2144 = !DILocation(line: 1327, column: 13, scope: !153)
!2145 = !DILocation(line: 1327, column: 2, scope: !153)
!2146 = !DILocation(line: 1328, column: 1, scope: !153)
!2147 = !DILocalVariable(name: "params", arg: 1, scope: !154, file: !115, line: 1330, type: !56)
!2148 = !DILocation(line: 1330, column: 25, scope: !154)
!2149 = !DILocation(line: 1332, column: 2, scope: !154)
!2150 = !DILocation(line: 1333, column: 1, scope: !154)
!2151 = !DILocalVariable(name: "filename", arg: 1, scope: !155, file: !115, line: 1335, type: !56)
!2152 = !DILocation(line: 1335, column: 25, scope: !155)
!2153 = !DILocalVariable(name: "statbuf", scope: !155, file: !115, line: 1337, type: !67)
!2154 = !DILocation(line: 1337, column: 14, scope: !155)
!2155 = !DILocalVariable(name: "filetime", scope: !155, file: !115, line: 1338, type: !2156)
!2156 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !2157, size: 64, align: 64)
!2157 = !DICompositeType(tag: DW_TAG_structure_type, name: "tm", file: !93, line: 133, size: 448, align: 64, elements: !2158)
!2158 = !{!2159, !2160, !2161, !2162, !2163, !2164, !2165, !2166, !2167, !2168, !2169}
!2159 = !DIDerivedType(tag: DW_TAG_member, name: "tm_sec", scope: !2157, file: !93, line: 135, baseType: !64, size: 32, align: 32)
!2160 = !DIDerivedType(tag: DW_TAG_member, name: "tm_min", scope: !2157, file: !93, line: 136, baseType: !64, size: 32, align: 32, offset: 32)
!2161 = !DIDerivedType(tag: DW_TAG_member, name: "tm_hour", scope: !2157, file: !93, line: 137, baseType: !64, size: 32, align: 32, offset: 64)
!2162 = !DIDerivedType(tag: DW_TAG_member, name: "tm_mday", scope: !2157, file: !93, line: 138, baseType: !64, size: 32, align: 32, offset: 96)
!2163 = !DIDerivedType(tag: DW_TAG_member, name: "tm_mon", scope: !2157, file: !93, line: 139, baseType: !64, size: 32, align: 32, offset: 128)
!2164 = !DIDerivedType(tag: DW_TAG_member, name: "tm_year", scope: !2157, file: !93, line: 140, baseType: !64, size: 32, align: 32, offset: 160)
!2165 = !DIDerivedType(tag: DW_TAG_member, name: "tm_wday", scope: !2157, file: !93, line: 141, baseType: !64, size: 32, align: 32, offset: 192)
!2166 = !DIDerivedType(tag: DW_TAG_member, name: "tm_yday", scope: !2157, file: !93, line: 142, baseType: !64, size: 32, align: 32, offset: 224)
!2167 = !DIDerivedType(tag: DW_TAG_member, name: "tm_isdst", scope: !2157, file: !93, line: 143, baseType: !64, size: 32, align: 32, offset: 256)
!2168 = !DIDerivedType(tag: DW_TAG_member, name: "tm_gmtoff", scope: !2157, file: !93, line: 146, baseType: !63, size: 64, align: 64, offset: 320)
!2169 = !DIDerivedType(tag: DW_TAG_member, name: "tm_zone", scope: !2157, file: !93, line: 147, baseType: !2170, size: 64, align: 64, offset: 384)
!2170 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !2171, size: 64, align: 64)
!2171 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !47)
!2172 = !DILocation(line: 1338, column: 13, scope: !155)
!2173 = !DILocalVariable(name: "fullfilename", scope: !155, file: !115, line: 1339, type: !56)
!2174 = !DILocation(line: 1339, column: 8, scope: !155)
!2175 = !DILocation(line: 1339, column: 41, scope: !155)
!2176 = !DILocation(line: 1339, column: 23, scope: !155)
!2177 = !DILocation(line: 1340, column: 12, scope: !2178)
!2178 = distinct !DILexicalBlock(scope: !155, file: !115, line: 1340, column: 6)
!2179 = !DILocation(line: 1340, column: 7, scope: !2178)
!2180 = !DILocation(line: 1340, column: 6, scope: !155)
!2181 = !DILocation(line: 1341, column: 42, scope: !2182)
!2182 = distinct !DILexicalBlock(scope: !2178, file: !115, line: 1340, column: 53)
!2183 = !DILocation(line: 1341, column: 14, scope: !2182)
!2184 = !DILocation(line: 1341, column: 12, scope: !2182)
!2185 = !DILocation(line: 1343, column: 5, scope: !2182)
!2186 = !DILocation(line: 1343, column: 15, scope: !2182)
!2187 = !DILocation(line: 1343, column: 23, scope: !2182)
!2188 = !DILocation(line: 1343, column: 31, scope: !2182)
!2189 = !DILocation(line: 1343, column: 41, scope: !2182)
!2190 = !DILocation(line: 1343, column: 48, scope: !2182)
!2191 = !DILocation(line: 1344, column: 5, scope: !2182)
!2192 = !DILocation(line: 1344, column: 15, scope: !2182)
!2193 = !DILocation(line: 1344, column: 24, scope: !2182)
!2194 = !DILocation(line: 1344, column: 34, scope: !2182)
!2195 = !DILocation(line: 1344, column: 43, scope: !2182)
!2196 = !DILocation(line: 1344, column: 53, scope: !2182)
!2197 = !DILocation(line: 1345, column: 5, scope: !2182)
!2198 = !DILocation(line: 1345, column: 15, scope: !2182)
!2199 = !DILocation(line: 1342, column: 3, scope: !2182)
!2200 = !DILocation(line: 1346, column: 2, scope: !2182)
!2201 = !DILocation(line: 1348, column: 14, scope: !2202)
!2202 = distinct !DILexicalBlock(scope: !2178, file: !115, line: 1346, column: 9)
!2203 = !DILocation(line: 1348, column: 5, scope: !2204)
!2204 = !DILexicalBlockFile(scope: !2202, file: !115, discriminator: 1)
!2205 = !DILocation(line: 1347, column: 3, scope: !2202)
!2206 = !DILocation(line: 1350, column: 7, scope: !155)
!2207 = !DILocation(line: 1350, column: 2, scope: !155)
!2208 = !DILocation(line: 1351, column: 1, scope: !155)
!2209 = !DILocalVariable(name: "dir", arg: 1, scope: !156, file: !115, line: 1353, type: !56)
!2210 = !DILocation(line: 1353, column: 24, scope: !156)
!2211 = !DILocation(line: 1355, column: 25, scope: !2212)
!2212 = distinct !DILexicalBlock(scope: !156, file: !115, line: 1355, column: 9)
!2213 = !DILocation(line: 1355, column: 9, scope: !2212)
!2214 = !DILocation(line: 1355, column: 9, scope: !156)
!2215 = !DILocation(line: 1357, column: 16, scope: !2216)
!2216 = distinct !DILexicalBlock(scope: !2212, file: !115, line: 1355, column: 31)
!2217 = !DILocation(line: 1357, column: 7, scope: !2218)
!2218 = !DILexicalBlockFile(scope: !2216, file: !115, discriminator: 1)
!2219 = !DILocation(line: 1357, column: 24, scope: !2216)
!2220 = !DILocation(line: 1356, column: 3, scope: !2216)
!2221 = !DILocation(line: 1358, column: 57, scope: !2216)
!2222 = !DILocation(line: 1358, column: 48, scope: !2218)
!2223 = !DILocation(line: 1358, column: 3, scope: !2224)
!2224 = !DILexicalBlockFile(scope: !2216, file: !115, discriminator: 2)
!2225 = !DILocation(line: 1359, column: 2, scope: !2216)
!2226 = !DILocation(line: 1360, column: 45, scope: !2227)
!2227 = distinct !DILexicalBlock(scope: !2212, file: !115, line: 1359, column: 9)
!2228 = !DILocation(line: 1360, column: 3, scope: !2227)
!2229 = !DILocation(line: 1361, column: 3, scope: !2227)
!2230 = !DILocation(line: 1363, column: 1, scope: !156)
!2231 = !DILocalVariable(name: "params", arg: 1, scope: !157, file: !115, line: 1365, type: !56)
!2232 = !DILocation(line: 1365, column: 25, scope: !157)
!2233 = !DILocation(line: 1367, column: 2, scope: !157)
!2234 = !DILocation(line: 1368, column: 2, scope: !157)
!2235 = !DILocation(line: 1369, column: 2, scope: !157)
!2236 = !DILocation(line: 1370, column: 1, scope: !157)
!2237 = !DILocalVariable(name: "filename", arg: 1, scope: !158, file: !115, line: 1372, type: !56)
!2238 = !DILocation(line: 1372, column: 25, scope: !158)
!2239 = !DILocalVariable(name: "sbuf", scope: !158, file: !115, line: 1374, type: !67)
!2240 = !DILocation(line: 1374, column: 21, scope: !158)
!2241 = !DILocalVariable(name: "mapped", scope: !158, file: !115, line: 1375, type: !56)
!2242 = !DILocation(line: 1375, column: 8, scope: !158)
!2243 = !DILocation(line: 1375, column: 35, scope: !158)
!2244 = !DILocation(line: 1375, column: 17, scope: !158)
!2245 = !DILocation(line: 1376, column: 13, scope: !2246)
!2246 = distinct !DILexicalBlock(scope: !158, file: !115, line: 1376, column: 13)
!2247 = !DILocation(line: 1376, column: 13, scope: !158)
!2248 = !DILocation(line: 1377, column: 23, scope: !2246)
!2249 = !DILocation(line: 1377, column: 41, scope: !2246)
!2250 = !DILocation(line: 1377, column: 12, scope: !2246)
!2251 = !DILocation(line: 1384, column: 20, scope: !2252)
!2252 = distinct !DILexicalBlock(scope: !158, file: !115, line: 1384, column: 14)
!2253 = !DILocation(line: 1384, column: 14, scope: !2252)
!2254 = !DILocation(line: 1384, column: 35, scope: !2252)
!2255 = !DILocation(line: 1384, column: 14, scope: !158)
!2256 = !DILocation(line: 1385, column: 57, scope: !2257)
!2257 = distinct !DILexicalBlock(scope: !2252, file: !115, line: 1384, column: 43)
!2258 = !DILocation(line: 1385, column: 48, scope: !2259)
!2259 = !DILexicalBlockFile(scope: !2257, file: !115, discriminator: 1)
!2260 = !DILocation(line: 1385, column: 3, scope: !2261)
!2261 = !DILexicalBlockFile(scope: !2257, file: !115, discriminator: 2)
!2262 = !DILocation(line: 1386, column: 2, scope: !2257)
!2263 = !DILocation(line: 1391, column: 21, scope: !2264)
!2264 = distinct !DILexicalBlock(scope: !2265, file: !115, line: 1391, column: 21)
!2265 = distinct !DILexicalBlock(scope: !2252, file: !115, line: 1386, column: 9)
!2266 = !DILocation(line: 1391, column: 21, scope: !2265)
!2267 = !DILocation(line: 1393, column: 105, scope: !2268)
!2268 = distinct !DILexicalBlock(scope: !2264, file: !115, line: 1392, column: 17)
!2269 = !DILocation(line: 1393, column: 96, scope: !2270)
!2270 = !DILexicalBlockFile(scope: !2268, file: !115, discriminator: 1)
!2271 = !DILocation(line: 1393, column: 113, scope: !2268)
!2272 = !DILocation(line: 1393, column: 23, scope: !2273)
!2273 = !DILexicalBlockFile(scope: !2268, file: !115, discriminator: 2)
!2274 = !DILocation(line: 1394, column: 75, scope: !2268)
!2275 = !DILocation(line: 1394, column: 22, scope: !2268)
!2276 = !DILocation(line: 1395, column: 17, scope: !2268)
!2277 = !DILocation(line: 1398, column: 31, scope: !2278)
!2278 = distinct !DILexicalBlock(scope: !2279, file: !115, line: 1398, column: 24)
!2279 = distinct !DILexicalBlock(scope: !2264, file: !115, line: 1397, column: 17)
!2280 = !DILocation(line: 1398, column: 24, scope: !2278)
!2281 = !DILocation(line: 1398, column: 24, scope: !2279)
!2282 = !DILocation(line: 1400, column: 95, scope: !2283)
!2283 = distinct !DILexicalBlock(scope: !2278, file: !115, line: 1399, column: 20)
!2284 = !DILocation(line: 1400, column: 86, scope: !2285)
!2285 = !DILexicalBlockFile(scope: !2283, file: !115, discriminator: 1)
!2286 = !DILocation(line: 1400, column: 103, scope: !2283)
!2287 = !DILocation(line: 1400, column: 25, scope: !2288)
!2288 = !DILexicalBlockFile(scope: !2283, file: !115, discriminator: 2)
!2289 = !DILocation(line: 1401, column: 79, scope: !2283)
!2290 = !DILocation(line: 1401, column: 70, scope: !2285)
!2291 = !DILocation(line: 1401, column: 25, scope: !2288)
!2292 = !DILocation(line: 1402, column: 20, scope: !2283)
!2293 = !DILocation(line: 1405, column: 59, scope: !2294)
!2294 = distinct !DILexicalBlock(scope: !2278, file: !115, line: 1404, column: 20)
!2295 = !DILocation(line: 1405, column: 25, scope: !2294)
!2296 = !DILocation(line: 1406, column: 25, scope: !2294)
!2297 = !DILocation(line: 1411, column: 13, scope: !2298)
!2298 = distinct !DILexicalBlock(scope: !158, file: !115, line: 1411, column: 13)
!2299 = !DILocation(line: 1411, column: 13, scope: !158)
!2300 = !DILocation(line: 1412, column: 23, scope: !2298)
!2301 = !DILocation(line: 1412, column: 42, scope: !2298)
!2302 = !DILocation(line: 1412, column: 12, scope: !2298)
!2303 = !DILocation(line: 1414, column: 7, scope: !158)
!2304 = !DILocation(line: 1414, column: 2, scope: !158)
!2305 = !DILocation(line: 1415, column: 1, scope: !158)
!2306 = !DILocalVariable(name: "dirname", arg: 1, scope: !159, file: !115, line: 1417, type: !56)
!2307 = !DILocation(line: 1417, column: 24, scope: !159)
!2308 = !DILocalVariable(name: "mapped", scope: !159, file: !115, line: 1419, type: !56)
!2309 = !DILocation(line: 1419, column: 8, scope: !159)
!2310 = !DILocation(line: 1419, column: 35, scope: !159)
!2311 = !DILocation(line: 1419, column: 17, scope: !159)
!2312 = !DILocation(line: 1421, column: 13, scope: !2313)
!2313 = distinct !DILexicalBlock(scope: !159, file: !115, line: 1421, column: 13)
!2314 = !DILocation(line: 1421, column: 13, scope: !159)
!2315 = !DILocation(line: 1422, column: 23, scope: !2313)
!2316 = !DILocation(line: 1422, column: 41, scope: !2313)
!2317 = !DILocation(line: 1422, column: 12, scope: !2313)
!2318 = !DILocation(line: 1424, column: 12, scope: !2319)
!2319 = distinct !DILexicalBlock(scope: !159, file: !115, line: 1424, column: 6)
!2320 = !DILocation(line: 1424, column: 6, scope: !2319)
!2321 = !DILocation(line: 1424, column: 6, scope: !159)
!2322 = !DILocation(line: 1426, column: 16, scope: !2323)
!2323 = distinct !DILexicalBlock(scope: !2319, file: !115, line: 1424, column: 27)
!2324 = !DILocation(line: 1426, column: 7, scope: !2325)
!2325 = !DILexicalBlockFile(scope: !2323, file: !115, discriminator: 1)
!2326 = !DILocation(line: 1426, column: 24, scope: !2323)
!2327 = !DILocation(line: 1425, column: 3, scope: !2323)
!2328 = !DILocation(line: 1427, column: 57, scope: !2323)
!2329 = !DILocation(line: 1427, column: 48, scope: !2325)
!2330 = !DILocation(line: 1427, column: 3, scope: !2331)
!2331 = !DILexicalBlockFile(scope: !2323, file: !115, discriminator: 2)
!2332 = !DILocation(line: 1428, column: 2, scope: !2323)
!2333 = !DILocation(line: 1429, column: 42, scope: !2334)
!2334 = distinct !DILexicalBlock(scope: !2319, file: !115, line: 1428, column: 9)
!2335 = !DILocation(line: 1429, column: 3, scope: !2334)
!2336 = !DILocation(line: 1430, column: 62, scope: !2334)
!2337 = !DILocation(line: 1430, column: 3, scope: !2334)
!2338 = !DILocation(line: 1433, column: 13, scope: !2339)
!2339 = distinct !DILexicalBlock(scope: !159, file: !115, line: 1433, column: 13)
!2340 = !DILocation(line: 1433, column: 13, scope: !159)
!2341 = !DILocation(line: 1434, column: 23, scope: !2339)
!2342 = !DILocation(line: 1434, column: 42, scope: !2339)
!2343 = !DILocation(line: 1434, column: 12, scope: !2339)
!2344 = !DILocation(line: 1436, column: 7, scope: !159)
!2345 = !DILocation(line: 1436, column: 2, scope: !159)
!2346 = !DILocation(line: 1437, column: 1, scope: !159)
!2347 = !DILocalVariable(name: "dirname", arg: 1, scope: !160, file: !115, line: 1439, type: !56)
!2348 = !DILocation(line: 1439, column: 24, scope: !160)
!2349 = !DILocalVariable(name: "mapped", scope: !160, file: !115, line: 1441, type: !56)
!2350 = !DILocation(line: 1441, column: 8, scope: !160)
!2351 = !DILocation(line: 1441, column: 35, scope: !160)
!2352 = !DILocation(line: 1441, column: 17, scope: !160)
!2353 = !DILocation(line: 1442, column: 13, scope: !2354)
!2354 = distinct !DILexicalBlock(scope: !160, file: !115, line: 1442, column: 13)
!2355 = !DILocation(line: 1442, column: 13, scope: !160)
!2356 = !DILocation(line: 1443, column: 23, scope: !2354)
!2357 = !DILocation(line: 1443, column: 41, scope: !2354)
!2358 = !DILocation(line: 1443, column: 12, scope: !2354)
!2359 = !DILocation(line: 1445, column: 12, scope: !2360)
!2360 = distinct !DILexicalBlock(scope: !160, file: !115, line: 1445, column: 6)
!2361 = !DILocation(line: 1445, column: 6, scope: !2360)
!2362 = !DILocation(line: 1445, column: 6, scope: !160)
!2363 = !DILocation(line: 1450, column: 20, scope: !2364)
!2364 = distinct !DILexicalBlock(scope: !2365, file: !115, line: 1450, column: 20)
!2365 = distinct !DILexicalBlock(scope: !2360, file: !115, line: 1445, column: 21)
!2366 = !DILocation(line: 1450, column: 26, scope: !2364)
!2367 = !DILocation(line: 1450, column: 20, scope: !2365)
!2368 = !DILocation(line: 1452, column: 106, scope: !2369)
!2369 = distinct !DILexicalBlock(scope: !2364, file: !115, line: 1451, column: 16)
!2370 = !DILocation(line: 1452, column: 97, scope: !2371)
!2371 = !DILexicalBlockFile(scope: !2369, file: !115, discriminator: 1)
!2372 = !DILocation(line: 1452, column: 114, scope: !2369)
!2373 = !DILocation(line: 1452, column: 20, scope: !2374)
!2374 = !DILexicalBlockFile(scope: !2369, file: !115, discriminator: 2)
!2375 = !DILocation(line: 1453, column: 78, scope: !2369)
!2376 = !DILocation(line: 1453, column: 20, scope: !2369)
!2377 = !DILocation(line: 1454, column: 16, scope: !2369)
!2378 = !DILocation(line: 1457, column: 95, scope: !2379)
!2379 = distinct !DILexicalBlock(scope: !2364, file: !115, line: 1456, column: 16)
!2380 = !DILocation(line: 1457, column: 86, scope: !2381)
!2381 = !DILexicalBlockFile(scope: !2379, file: !115, discriminator: 1)
!2382 = !DILocation(line: 1457, column: 103, scope: !2379)
!2383 = !DILocation(line: 1457, column: 20, scope: !2384)
!2384 = !DILexicalBlockFile(scope: !2379, file: !115, discriminator: 2)
!2385 = !DILocation(line: 1458, column: 73, scope: !2379)
!2386 = !DILocation(line: 1458, column: 64, scope: !2381)
!2387 = !DILocation(line: 1458, column: 19, scope: !2384)
!2388 = !DILocation(line: 1461, column: 2, scope: !2365)
!2389 = !DILocation(line: 1462, column: 42, scope: !2390)
!2390 = distinct !DILexicalBlock(scope: !2360, file: !115, line: 1461, column: 9)
!2391 = !DILocation(line: 1462, column: 3, scope: !2390)
!2392 = !DILocation(line: 1463, column: 3, scope: !2390)
!2393 = !DILocation(line: 1466, column: 13, scope: !2394)
!2394 = distinct !DILexicalBlock(scope: !160, file: !115, line: 1466, column: 13)
!2395 = !DILocation(line: 1466, column: 13, scope: !160)
!2396 = !DILocation(line: 1467, column: 23, scope: !2394)
!2397 = !DILocation(line: 1467, column: 42, scope: !2394)
!2398 = !DILocation(line: 1467, column: 12, scope: !2394)
!2399 = !DILocation(line: 1468, column: 7, scope: !160)
!2400 = !DILocation(line: 1468, column: 2, scope: !160)
!2401 = !DILocation(line: 1469, column: 1, scope: !160)
!2402 = !DILocalVariable(name: "oldname", arg: 1, scope: !162, file: !115, line: 1476, type: !56)
!2403 = !DILocation(line: 1476, column: 25, scope: !162)
!2404 = !DILocalVariable(name: "file", scope: !162, file: !115, line: 1478, type: !1991)
!2405 = !DILocation(line: 1478, column: 8, scope: !162)
!2406 = !DILocalVariable(name: "mapped", scope: !162, file: !115, line: 1479, type: !56)
!2407 = !DILocation(line: 1479, column: 8, scope: !162)
!2408 = !DILocation(line: 1479, column: 35, scope: !162)
!2409 = !DILocation(line: 1479, column: 17, scope: !162)
!2410 = !DILocation(line: 1480, column: 20, scope: !2411)
!2411 = distinct !DILexicalBlock(scope: !162, file: !115, line: 1480, column: 6)
!2412 = !DILocation(line: 1480, column: 14, scope: !2411)
!2413 = !DILocation(line: 1480, column: 12, scope: !2411)
!2414 = !DILocation(line: 1480, column: 6, scope: !162)
!2415 = !DILocation(line: 1481, column: 10, scope: !2416)
!2416 = distinct !DILexicalBlock(scope: !2411, file: !115, line: 1480, column: 35)
!2417 = !DILocation(line: 1481, column: 3, scope: !2416)
!2418 = !DILocation(line: 1482, column: 7, scope: !2419)
!2419 = distinct !DILexicalBlock(scope: !2416, file: !115, line: 1482, column: 7)
!2420 = !DILocation(line: 1482, column: 7, scope: !2416)
!2421 = !DILocation(line: 1483, column: 9, scope: !2419)
!2422 = !DILocation(line: 1483, column: 4, scope: !2419)
!2423 = !DILocation(line: 1484, column: 15, scope: !2416)
!2424 = !DILocation(line: 1484, column: 13, scope: !2416)
!2425 = !DILocation(line: 1485, column: 9, scope: !2416)
!2426 = !DILocation(line: 1486, column: 3, scope: !2416)
!2427 = !DILocation(line: 1487, column: 2, scope: !2416)
!2428 = !DILocation(line: 1488, column: 8, scope: !2429)
!2429 = distinct !DILexicalBlock(scope: !2411, file: !115, line: 1487, column: 9)
!2430 = !DILocation(line: 1488, column: 3, scope: !2429)
!2431 = !DILocation(line: 1489, column: 57, scope: !2429)
!2432 = !DILocation(line: 1489, column: 48, scope: !2433)
!2433 = !DILexicalBlockFile(scope: !2429, file: !115, discriminator: 1)
!2434 = !DILocation(line: 1489, column: 3, scope: !2435)
!2435 = !DILexicalBlockFile(scope: !2429, file: !115, discriminator: 2)
!2436 = !DILocation(line: 1491, column: 1, scope: !162)
!2437 = !DILocalVariable(name: "newname", arg: 1, scope: !163, file: !115, line: 1493, type: !56)
!2438 = !DILocation(line: 1493, column: 25, scope: !163)
!2439 = !DILocalVariable(name: "mapped", scope: !163, file: !115, line: 1495, type: !56)
!2440 = !DILocation(line: 1495, column: 8, scope: !163)
!2441 = !DILocation(line: 1495, column: 35, scope: !163)
!2442 = !DILocation(line: 1495, column: 17, scope: !163)
!2443 = !DILocation(line: 1497, column: 13, scope: !2444)
!2444 = distinct !DILexicalBlock(scope: !163, file: !115, line: 1497, column: 13)
!2445 = !DILocation(line: 1497, column: 13, scope: !163)
!2446 = !DILocation(line: 1498, column: 23, scope: !2444)
!2447 = !DILocation(line: 1498, column: 41, scope: !2444)
!2448 = !DILocation(line: 1498, column: 12, scope: !2444)
!2449 = !DILocation(line: 1500, column: 13, scope: !2450)
!2450 = distinct !DILexicalBlock(scope: !163, file: !115, line: 1500, column: 6)
!2451 = !DILocation(line: 1500, column: 24, scope: !2450)
!2452 = !DILocation(line: 1500, column: 6, scope: !2450)
!2453 = !DILocation(line: 1500, column: 6, scope: !163)
!2454 = !DILocation(line: 1502, column: 16, scope: !2455)
!2455 = distinct !DILexicalBlock(scope: !2450, file: !115, line: 1500, column: 33)
!2456 = !DILocation(line: 1502, column: 7, scope: !2457)
!2457 = !DILexicalBlockFile(scope: !2455, file: !115, discriminator: 1)
!2458 = !DILocation(line: 1502, column: 24, scope: !2455)
!2459 = !DILocation(line: 1502, column: 53, scope: !2455)
!2460 = !DILocation(line: 1502, column: 35, scope: !2461)
!2461 = !DILexicalBlockFile(scope: !2455, file: !115, discriminator: 2)
!2462 = !DILocation(line: 1501, column: 3, scope: !2455)
!2463 = !DILocation(line: 1503, column: 57, scope: !2455)
!2464 = !DILocation(line: 1503, column: 48, scope: !2457)
!2465 = !DILocation(line: 1503, column: 3, scope: !2461)
!2466 = !DILocation(line: 1504, column: 2, scope: !2455)
!2467 = !DILocation(line: 1505, column: 53, scope: !2468)
!2468 = distinct !DILexicalBlock(scope: !2450, file: !115, line: 1504, column: 9)
!2469 = !DILocation(line: 1505, column: 82, scope: !2468)
!2470 = !DILocation(line: 1505, column: 64, scope: !2468)
!2471 = !DILocation(line: 1505, column: 3, scope: !2472)
!2472 = !DILexicalBlockFile(scope: !2468, file: !115, discriminator: 1)
!2473 = !DILocation(line: 1506, column: 3, scope: !2468)
!2474 = !DILocation(line: 1507, column: 9, scope: !2468)
!2475 = !DILocation(line: 1510, column: 13, scope: !2476)
!2476 = distinct !DILexicalBlock(scope: !163, file: !115, line: 1510, column: 13)
!2477 = !DILocation(line: 1510, column: 13, scope: !163)
!2478 = !DILocation(line: 1511, column: 23, scope: !2476)
!2479 = !DILocation(line: 1511, column: 42, scope: !2476)
!2480 = !DILocation(line: 1511, column: 12, scope: !2476)
!2481 = !DILocation(line: 1513, column: 7, scope: !163)
!2482 = !DILocation(line: 1513, column: 2, scope: !163)
!2483 = !DILocation(line: 1514, column: 7, scope: !163)
!2484 = !DILocation(line: 1514, column: 2, scope: !163)
!2485 = !DILocation(line: 1515, column: 12, scope: !163)
!2486 = !DILocation(line: 1516, column: 1, scope: !163)
!2487 = !DILocalVariable(name: "params", arg: 1, scope: !164, file: !115, line: 1518, type: !56)
!2488 = !DILocation(line: 1518, column: 25, scope: !164)
!2489 = !DILocation(line: 1520, column: 22, scope: !164)
!2490 = !DILocation(line: 1520, column: 14, scope: !164)
!2491 = !DILocation(line: 1520, column: 12, scope: !164)
!2492 = !DILocation(line: 1521, column: 64, scope: !164)
!2493 = !DILocation(line: 1521, column: 5, scope: !164)
!2494 = !DILocation(line: 1522, column: 1, scope: !164)
!2495 = !DILocalVariable(name: "filename", arg: 1, scope: !165, file: !115, line: 1524, type: !56)
!2496 = !DILocation(line: 1524, column: 25, scope: !165)
!2497 = !DILocalVariable(name: "statbuf", scope: !165, file: !115, line: 1526, type: !67)
!2498 = !DILocation(line: 1526, column: 14, scope: !165)
!2499 = !DILocalVariable(name: "mapped", scope: !165, file: !115, line: 1527, type: !56)
!2500 = !DILocation(line: 1527, column: 8, scope: !165)
!2501 = !DILocation(line: 1527, column: 35, scope: !165)
!2502 = !DILocation(line: 1527, column: 17, scope: !165)
!2503 = !DILocation(line: 1528, column: 12, scope: !2504)
!2504 = distinct !DILexicalBlock(scope: !165, file: !115, line: 1528, column: 6)
!2505 = !DILocation(line: 1528, column: 7, scope: !2504)
!2506 = !DILocation(line: 1528, column: 6, scope: !165)
!2507 = !DILocation(line: 1529, column: 54, scope: !2508)
!2508 = distinct !DILexicalBlock(scope: !2504, file: !115, line: 1528, column: 31)
!2509 = !DILocation(line: 1529, column: 40, scope: !2508)
!2510 = !DILocation(line: 1529, column: 3, scope: !2508)
!2511 = !DILocation(line: 1530, column: 2, scope: !2508)
!2512 = !DILocation(line: 1531, column: 57, scope: !2513)
!2513 = distinct !DILexicalBlock(scope: !2504, file: !115, line: 1530, column: 9)
!2514 = !DILocation(line: 1531, column: 48, scope: !2515)
!2515 = !DILexicalBlockFile(scope: !2513, file: !115, discriminator: 1)
!2516 = !DILocation(line: 1531, column: 3, scope: !2517)
!2517 = !DILexicalBlockFile(scope: !2513, file: !115, discriminator: 2)
!2518 = !DILocation(line: 1533, column: 7, scope: !165)
!2519 = !DILocation(line: 1533, column: 2, scope: !165)
!2520 = !DILocation(line: 1534, column: 1, scope: !165)
!2521 = !DILocalVariable(name: "params", arg: 1, scope: !166, file: !115, line: 1536, type: !56)
!2522 = !DILocation(line: 1536, column: 25, scope: !166)
!2523 = !DILocation(line: 1538, column: 39, scope: !166)
!2524 = !DILocation(line: 1538, column: 2, scope: !2525)
!2525 = !DILexicalBlockFile(scope: !166, file: !115, discriminator: 1)
!2526 = !DILocation(line: 1540, column: 9, scope: !166)
!2527 = !DILocation(line: 1542, column: 2, scope: !166)
!2528 = !DILocation(line: 1543, column: 1, scope: !166)
!2529 = !DILocalVariable(name: "filename", arg: 1, scope: !167, file: !115, line: 1545, type: !56)
!2530 = !DILocation(line: 1545, column: 25, scope: !167)
!2531 = !DILocalVariable(name: "mapped", scope: !167, file: !115, line: 1547, type: !56)
!2532 = !DILocation(line: 1547, column: 8, scope: !167)
!2533 = !DILocation(line: 1547, column: 35, scope: !167)
!2534 = !DILocation(line: 1547, column: 17, scope: !167)
!2535 = !DILocation(line: 1548, column: 53, scope: !167)
!2536 = !DILocation(line: 1548, column: 5, scope: !167)
!2537 = !DILocation(line: 1549, column: 16, scope: !167)
!2538 = !DILocation(line: 1549, column: 24, scope: !167)
!2539 = !DILocation(line: 1549, column: 5, scope: !167)
!2540 = !DILocation(line: 1550, column: 5, scope: !167)
!2541 = !DILocation(line: 1551, column: 7, scope: !167)
!2542 = !DILocation(line: 1551, column: 2, scope: !167)
!2543 = !DILocation(line: 1552, column: 1, scope: !167)
!2544 = !DILocalVariable(name: "params", arg: 1, scope: !168, file: !115, line: 1556, type: !56)
!2545 = !DILocation(line: 1556, column: 26, scope: !168)
!2546 = !DILocalVariable(name: "permissions", scope: !168, file: !115, line: 1558, type: !64)
!2547 = !DILocation(line: 1558, column: 6, scope: !168)
!2548 = !DILocalVariable(name: "mapped", scope: !168, file: !115, line: 1559, type: !56)
!2549 = !DILocation(line: 1559, column: 8, scope: !168)
!2550 = !DILocalVariable(name: "my_string", scope: !168, file: !115, line: 1560, type: !56)
!2551 = !DILocation(line: 1560, column: 15, scope: !168)
!2552 = !DILocation(line: 1562, column: 14, scope: !2553)
!2553 = distinct !DILexicalBlock(scope: !168, file: !115, line: 1562, column: 6)
!2554 = !DILocation(line: 1562, column: 7, scope: !2553)
!2555 = !DILocation(line: 1562, column: 6, scope: !168)
!2556 = !DILocation(line: 1563, column: 3, scope: !2557)
!2557 = distinct !DILexicalBlock(scope: !2553, file: !115, line: 1562, column: 28)
!2558 = !DILocation(line: 1564, column: 3, scope: !2557)
!2559 = !DILocation(line: 1566, column: 35, scope: !168)
!2560 = !DILocation(line: 1566, column: 28, scope: !168)
!2561 = !DILocation(line: 1566, column: 48, scope: !168)
!2562 = !DILocation(line: 1566, column: 21, scope: !2563)
!2563 = !DILexicalBlockFile(scope: !168, file: !115, discriminator: 1)
!2564 = !DILocation(line: 1566, column: 19, scope: !168)
!2565 = !DILocation(line: 1567, column: 15, scope: !2566)
!2566 = distinct !DILexicalBlock(scope: !168, file: !115, line: 1567, column: 13)
!2567 = !DILocation(line: 1567, column: 13, scope: !168)
!2568 = !DILocation(line: 1569, column: 13, scope: !2569)
!2569 = distinct !DILexicalBlock(scope: !2566, file: !115, line: 1568, column: 9)
!2570 = !DILocation(line: 1570, column: 13, scope: !2569)
!2571 = !DILocation(line: 1573, column: 36, scope: !168)
!2572 = !DILocation(line: 1573, column: 18, scope: !168)
!2573 = !DILocation(line: 1573, column: 16, scope: !168)
!2574 = !DILocation(line: 1574, column: 14, scope: !168)
!2575 = !DILocation(line: 1574, column: 9, scope: !168)
!2576 = !DILocation(line: 1576, column: 13, scope: !2577)
!2577 = distinct !DILexicalBlock(scope: !168, file: !115, line: 1576, column: 13)
!2578 = !DILocation(line: 1576, column: 13, scope: !168)
!2579 = !DILocation(line: 1577, column: 23, scope: !2577)
!2580 = !DILocation(line: 1577, column: 41, scope: !2577)
!2581 = !DILocation(line: 1577, column: 12, scope: !2577)
!2582 = !DILocation(line: 1579, column: 10, scope: !168)
!2583 = !DILocation(line: 1579, column: 3, scope: !168)
!2584 = !DILocation(line: 1579, column: 23, scope: !168)
!2585 = !DILocation(line: 1580, column: 9, scope: !168)
!2586 = !DILocation(line: 1580, column: 2, scope: !168)
!2587 = !DILocation(line: 1581, column: 12, scope: !2588)
!2588 = distinct !DILexicalBlock(scope: !168, file: !115, line: 1581, column: 6)
!2589 = !DILocation(line: 1581, column: 20, scope: !2588)
!2590 = !DILocation(line: 1581, column: 6, scope: !2588)
!2591 = !DILocation(line: 1581, column: 6, scope: !168)
!2592 = !DILocation(line: 1582, column: 53, scope: !2588)
!2593 = !DILocation(line: 1582, column: 44, scope: !2594)
!2594 = !DILexicalBlockFile(scope: !2588, file: !115, discriminator: 1)
!2595 = !DILocation(line: 1582, column: 3, scope: !2596)
!2596 = !DILexicalBlockFile(scope: !2588, file: !115, discriminator: 2)
!2597 = !DILocation(line: 1582, column: 3, scope: !2588)
!2598 = !DILocation(line: 1584, column: 55, scope: !2599)
!2599 = distinct !DILexicalBlock(scope: !2588, file: !115, line: 1583, column: 7)
!2600 = !DILocation(line: 1585, column: 7, scope: !2599)
!2601 = !DILocation(line: 1584, column: 3, scope: !2599)
!2602 = !DILocation(line: 1586, column: 3, scope: !2599)
!2603 = !DILocation(line: 1588, column: 13, scope: !2604)
!2604 = distinct !DILexicalBlock(scope: !168, file: !115, line: 1588, column: 13)
!2605 = !DILocation(line: 1588, column: 13, scope: !168)
!2606 = !DILocation(line: 1589, column: 23, scope: !2604)
!2607 = !DILocation(line: 1589, column: 42, scope: !2604)
!2608 = !DILocation(line: 1589, column: 12, scope: !2604)
!2609 = !DILocation(line: 1591, column: 7, scope: !168)
!2610 = !DILocation(line: 1591, column: 2, scope: !168)
!2611 = !DILocation(line: 1592, column: 1, scope: !168)
!2612 = !DILocation(line: 1592, column: 1, scope: !2563)
!2613 = !DILocalVariable(name: "params", arg: 1, scope: !169, file: !115, line: 1594, type: !56)
!2614 = !DILocation(line: 1594, column: 26, scope: !169)
!2615 = !DILocalVariable(name: "foo", scope: !169, file: !115, line: 1596, type: !972)
!2616 = !DILocation(line: 1596, column: 7, scope: !169)
!2617 = !DILocalVariable(name: "owner", scope: !169, file: !115, line: 1596, type: !972)
!2618 = !DILocation(line: 1596, column: 24, scope: !169)
!2619 = !DILocalVariable(name: "group", scope: !169, file: !115, line: 1596, type: !972)
!2620 = !DILocation(line: 1596, column: 43, scope: !169)
!2621 = !DILocalVariable(name: "filename", scope: !169, file: !115, line: 1597, type: !972)
!2622 = !DILocation(line: 1597, column: 3, scope: !169)
!2623 = !DILocalVariable(name: "mapped", scope: !169, file: !115, line: 1597, type: !56)
!2624 = !DILocation(line: 1597, column: 26, scope: !169)
!2625 = !DILocalVariable(name: "uid", scope: !169, file: !115, line: 1598, type: !64)
!2626 = !DILocation(line: 1598, column: 6, scope: !169)
!2627 = !DILocalVariable(name: "gid", scope: !169, file: !115, line: 1598, type: !64)
!2628 = !DILocation(line: 1598, column: 11, scope: !169)
!2629 = !DILocation(line: 1599, column: 14, scope: !2630)
!2630 = distinct !DILexicalBlock(scope: !169, file: !115, line: 1599, column: 6)
!2631 = !DILocation(line: 1599, column: 7, scope: !2630)
!2632 = !DILocation(line: 1599, column: 6, scope: !169)
!2633 = !DILocation(line: 1600, column: 3, scope: !2634)
!2634 = distinct !DILexicalBlock(scope: !2630, file: !115, line: 1599, column: 28)
!2635 = !DILocation(line: 1601, column: 3, scope: !2634)
!2636 = !DILocation(line: 1603, column: 9, scope: !169)
!2637 = !DILocation(line: 1603, column: 29, scope: !169)
!2638 = !DILocation(line: 1603, column: 34, scope: !169)
!2639 = !DILocation(line: 1603, column: 2, scope: !169)
!2640 = !DILocation(line: 1604, column: 13, scope: !2641)
!2641 = distinct !DILexicalBlock(scope: !169, file: !115, line: 1604, column: 6)
!2642 = !DILocation(line: 1604, column: 6, scope: !2641)
!2643 = !DILocation(line: 1604, column: 6, scope: !169)
!2644 = !DILocation(line: 1605, column: 10, scope: !2641)
!2645 = !DILocation(line: 1605, column: 27, scope: !2641)
!2646 = !DILocation(line: 1605, column: 34, scope: !2641)
!2647 = !DILocation(line: 1605, column: 3, scope: !2641)
!2648 = !DILocation(line: 1607, column: 10, scope: !2649)
!2649 = distinct !DILexicalBlock(scope: !2641, file: !115, line: 1606, column: 7)
!2650 = !DILocation(line: 1607, column: 17, scope: !2649)
!2651 = !DILocation(line: 1607, column: 3, scope: !2649)
!2652 = !DILocation(line: 1608, column: 3, scope: !2649)
!2653 = !DILocation(line: 1608, column: 12, scope: !2649)
!2654 = !DILocation(line: 1610, column: 14, scope: !2655)
!2655 = distinct !DILexicalBlock(scope: !169, file: !115, line: 1610, column: 6)
!2656 = !DILocation(line: 1610, column: 7, scope: !2655)
!2657 = !DILocation(line: 1610, column: 6, scope: !169)
!2658 = !DILocation(line: 1611, column: 26, scope: !2659)
!2659 = distinct !DILexicalBlock(scope: !2655, file: !115, line: 1611, column: 7)
!2660 = !DILocation(line: 1611, column: 33, scope: !2659)
!2661 = !DILocation(line: 1611, column: 15, scope: !2659)
!2662 = !DILocation(line: 1611, column: 13, scope: !2659)
!2663 = !DILocation(line: 1611, column: 47, scope: !2659)
!2664 = !DILocation(line: 1611, column: 7, scope: !2655)
!2665 = !DILocation(line: 1612, column: 59, scope: !2666)
!2666 = distinct !DILexicalBlock(scope: !2659, file: !115, line: 1611, column: 52)
!2667 = !DILocation(line: 1612, column: 4, scope: !2666)
!2668 = !DILocation(line: 1613, column: 4, scope: !2666)
!2669 = !DILocation(line: 1611, column: 49, scope: !2670)
!2670 = !DILexicalBlockFile(scope: !2659, file: !115, discriminator: 1)
!2671 = !DILocation(line: 1615, column: 14, scope: !2672)
!2672 = distinct !DILexicalBlock(scope: !169, file: !115, line: 1615, column: 6)
!2673 = !DILocation(line: 1615, column: 7, scope: !2672)
!2674 = !DILocation(line: 1615, column: 6, scope: !169)
!2675 = !DILocation(line: 1616, column: 26, scope: !2676)
!2676 = distinct !DILexicalBlock(scope: !2672, file: !115, line: 1616, column: 7)
!2677 = !DILocation(line: 1616, column: 33, scope: !2676)
!2678 = !DILocation(line: 1616, column: 15, scope: !2676)
!2679 = !DILocation(line: 1616, column: 13, scope: !2676)
!2680 = !DILocation(line: 1616, column: 46, scope: !2676)
!2681 = !DILocation(line: 1616, column: 7, scope: !2672)
!2682 = !DILocation(line: 1617, column: 60, scope: !2683)
!2683 = distinct !DILexicalBlock(scope: !2676, file: !115, line: 1616, column: 51)
!2684 = !DILocation(line: 1617, column: 4, scope: !2683)
!2685 = !DILocation(line: 1618, column: 4, scope: !2683)
!2686 = !DILocation(line: 1616, column: 48, scope: !2687)
!2687 = !DILexicalBlockFile(scope: !2676, file: !115, discriminator: 1)
!2688 = !DILocation(line: 1620, column: 29, scope: !169)
!2689 = !DILocation(line: 1620, column: 11, scope: !169)
!2690 = !DILocation(line: 1620, column: 9, scope: !169)
!2691 = !DILocation(line: 1621, column: 13, scope: !2692)
!2692 = distinct !DILexicalBlock(scope: !169, file: !115, line: 1621, column: 13)
!2693 = !DILocation(line: 1621, column: 13, scope: !169)
!2694 = !DILocation(line: 1622, column: 23, scope: !2692)
!2695 = !DILocation(line: 1622, column: 41, scope: !2692)
!2696 = !DILocation(line: 1622, column: 12, scope: !2692)
!2697 = !DILocation(line: 1624, column: 12, scope: !2698)
!2698 = distinct !DILexicalBlock(scope: !169, file: !115, line: 1624, column: 6)
!2699 = !DILocation(line: 1624, column: 20, scope: !2698)
!2700 = !DILocation(line: 1624, column: 25, scope: !2698)
!2701 = !DILocation(line: 1624, column: 6, scope: !2698)
!2702 = !DILocation(line: 1624, column: 6, scope: !169)
!2703 = !DILocation(line: 1625, column: 57, scope: !2698)
!2704 = !DILocation(line: 1625, column: 48, scope: !2705)
!2705 = !DILexicalBlockFile(scope: !2698, file: !115, discriminator: 1)
!2706 = !DILocation(line: 1625, column: 3, scope: !2707)
!2707 = !DILexicalBlockFile(scope: !2698, file: !115, discriminator: 2)
!2708 = !DILocation(line: 1625, column: 3, scope: !2698)
!2709 = !DILocation(line: 1627, column: 58, scope: !2710)
!2710 = distinct !DILexicalBlock(scope: !2698, file: !115, line: 1626, column: 7)
!2711 = !DILocation(line: 1627, column: 68, scope: !2710)
!2712 = !DILocation(line: 1628, column: 7, scope: !2710)
!2713 = !DILocation(line: 1627, column: 3, scope: !2710)
!2714 = !DILocation(line: 1629, column: 3, scope: !2710)
!2715 = !DILocation(line: 1631, column: 13, scope: !2716)
!2716 = distinct !DILexicalBlock(scope: !169, file: !115, line: 1631, column: 13)
!2717 = !DILocation(line: 1631, column: 13, scope: !169)
!2718 = !DILocation(line: 1632, column: 23, scope: !2716)
!2719 = !DILocation(line: 1632, column: 42, scope: !2716)
!2720 = !DILocation(line: 1632, column: 12, scope: !2716)
!2721 = !DILocation(line: 1633, column: 7, scope: !169)
!2722 = !DILocation(line: 1633, column: 2, scope: !169)
!2723 = !DILocation(line: 1634, column: 1, scope: !169)
!2724 = !DILocation(line: 1634, column: 1, scope: !2725)
!2725 = !DILexicalBlockFile(scope: !169, file: !115, discriminator: 1)
!2726 = !DILocalVariable(name: "philename", arg: 1, scope: !170, file: !115, line: 1643, type: !56)
!2727 = !DILocation(line: 1643, column: 24, scope: !170)
!2728 = !DILocalVariable(name: "myphile", scope: !170, file: !115, line: 1645, type: !1991)
!2729 = !DILocation(line: 1645, column: 11, scope: !170)
!2730 = !DILocalVariable(name: "my_md5", scope: !170, file: !115, line: 1646, type: !2731)
!2731 = !DIDerivedType(tag: DW_TAG_typedef, name: "md5_t", file: !2732, line: 68, baseType: !2733)
!2732 = !DIFile(filename: "./md5.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!2733 = !DICompositeType(tag: DW_TAG_structure_type, file: !2732, line: 58, size: 1248, align: 32, elements: !2734)
!2734 = !{!2735, !2737, !2738, !2739, !2740, !2744, !2745}
!2735 = !DIDerivedType(tag: DW_TAG_member, name: "md_A", scope: !2733, file: !2732, line: 60, baseType: !2736, size: 32, align: 32)
!2736 = !DIDerivedType(tag: DW_TAG_typedef, name: "md5_uint32", file: !2732, line: 46, baseType: !55)
!2737 = !DIDerivedType(tag: DW_TAG_member, name: "md_B", scope: !2733, file: !2732, line: 61, baseType: !2736, size: 32, align: 32, offset: 32)
!2738 = !DIDerivedType(tag: DW_TAG_member, name: "md_C", scope: !2733, file: !2732, line: 62, baseType: !2736, size: 32, align: 32, offset: 64)
!2739 = !DIDerivedType(tag: DW_TAG_member, name: "md_D", scope: !2733, file: !2732, line: 63, baseType: !2736, size: 32, align: 32, offset: 96)
!2740 = !DIDerivedType(tag: DW_TAG_member, name: "md_total", scope: !2733, file: !2732, line: 65, baseType: !2741, size: 64, align: 32, offset: 128)
!2741 = !DICompositeType(tag: DW_TAG_array_type, baseType: !2736, size: 64, align: 32, elements: !2742)
!2742 = !{!2743}
!2743 = !DISubrange(count: 2)
!2744 = !DIDerivedType(tag: DW_TAG_member, name: "md_buf_len", scope: !2733, file: !2732, line: 66, baseType: !2736, size: 32, align: 32, offset: 192)
!2745 = !DIDerivedType(tag: DW_TAG_member, name: "md_buffer", scope: !2733, file: !2732, line: 67, baseType: !2746, size: 1024, align: 8, offset: 224)
!2746 = !DICompositeType(tag: DW_TAG_array_type, baseType: !47, size: 1024, align: 8, elements: !2747)
!2747 = !{!2748}
!2748 = !DISubrange(count: 128)
!2749 = !DILocation(line: 1646, column: 11, scope: !170)
!2750 = !DILocalVariable(name: "buffer", scope: !170, file: !115, line: 1647, type: !2751)
!2751 = !DICompositeType(tag: DW_TAG_array_type, baseType: !47, size: 8192, align: 8, elements: !2752)
!2752 = !{!2753}
!2753 = !DISubrange(count: 1024)
!2754 = !DILocation(line: 1647, column: 10, scope: !170)
!2755 = !DILocalVariable(name: "bytes_read", scope: !170, file: !115, line: 1648, type: !64)
!2756 = !DILocation(line: 1648, column: 9, scope: !170)
!2757 = !DILocalVariable(name: "md5_result", scope: !170, file: !115, line: 1649, type: !2758)
!2758 = !DICompositeType(tag: DW_TAG_array_type, baseType: !47, size: 128, align: 8, elements: !982)
!2759 = !DILocation(line: 1649, column: 10, scope: !170)
!2760 = !DILocalVariable(name: "output_string", scope: !170, file: !115, line: 1650, type: !2761)
!2761 = !DICompositeType(tag: DW_TAG_array_type, baseType: !47, size: 512, align: 8, elements: !2762)
!2762 = !{!2763}
!2763 = !DISubrange(count: 64)
!2764 = !DILocation(line: 1650, column: 10, scope: !170)
!2765 = !DILocation(line: 1652, column: 11, scope: !2766)
!2766 = distinct !DILexicalBlock(scope: !170, file: !115, line: 1652, column: 9)
!2767 = !DILocation(line: 1652, column: 9, scope: !170)
!2768 = !DILocation(line: 1654, column: 8, scope: !2769)
!2769 = distinct !DILexicalBlock(scope: !2766, file: !115, line: 1653, column: 5)
!2770 = !DILocation(line: 1655, column: 8, scope: !2769)
!2771 = !DILocation(line: 1658, column: 14, scope: !170)
!2772 = !DILocation(line: 1659, column: 21, scope: !170)
!2773 = !DILocation(line: 1659, column: 15, scope: !170)
!2774 = !DILocation(line: 1659, column: 13, scope: !170)
!2775 = !DILocation(line: 1660, column: 11, scope: !2776)
!2776 = distinct !DILexicalBlock(scope: !170, file: !115, line: 1660, column: 9)
!2777 = !DILocation(line: 1660, column: 9, scope: !170)
!2778 = !DILocation(line: 1662, column: 69, scope: !2779)
!2779 = distinct !DILexicalBlock(scope: !2776, file: !115, line: 1661, column: 5)
!2780 = !DILocation(line: 1662, column: 9, scope: !2779)
!2781 = !DILocation(line: 1663, column: 9, scope: !2779)
!2782 = !DILocation(line: 1666, column: 5, scope: !170)
!2783 = !DILocation(line: 1667, column: 24, scope: !170)
!2784 = !DILocation(line: 1667, column: 52, scope: !170)
!2785 = !DILocation(line: 1667, column: 18, scope: !170)
!2786 = !DILocation(line: 1667, column: 16, scope: !170)
!2787 = !DILocation(line: 1668, column: 5, scope: !170)
!2788 = !DILocation(line: 1668, column: 12, scope: !2789)
!2789 = !DILexicalBlockFile(scope: !170, file: !115, discriminator: 1)
!2790 = !DILocation(line: 1668, column: 23, scope: !2789)
!2791 = !DILocation(line: 1668, column: 5, scope: !2789)
!2792 = !DILocation(line: 1670, column: 30, scope: !2793)
!2793 = distinct !DILexicalBlock(scope: !170, file: !115, line: 1669, column: 5)
!2794 = !DILocation(line: 1670, column: 38, scope: !2793)
!2795 = !DILocation(line: 1670, column: 9, scope: !2793)
!2796 = !DILocation(line: 1671, column: 28, scope: !2793)
!2797 = !DILocation(line: 1671, column: 56, scope: !2793)
!2798 = !DILocation(line: 1671, column: 22, scope: !2793)
!2799 = !DILocation(line: 1671, column: 20, scope: !2793)
!2800 = !DILocation(line: 1668, column: 5, scope: !2801)
!2801 = !DILexicalBlockFile(scope: !170, file: !115, discriminator: 2)
!2802 = !DILocation(line: 1674, column: 25, scope: !170)
!2803 = !DILocation(line: 1674, column: 5, scope: !170)
!2804 = !DILocation(line: 1675, column: 23, scope: !170)
!2805 = !DILocation(line: 1675, column: 35, scope: !170)
!2806 = !DILocation(line: 1675, column: 5, scope: !170)
!2807 = !DILocation(line: 1676, column: 61, scope: !170)
!2808 = !DILocation(line: 1676, column: 5, scope: !170)
!2809 = !DILocation(line: 1677, column: 12, scope: !170)
!2810 = !DILocation(line: 1677, column: 5, scope: !170)
!2811 = !DILocation(line: 1678, column: 1, scope: !170)
!2812 = !DILocation(line: 1678, column: 1, scope: !2789)
!2813 = !DILocalVariable(name: "str", arg: 1, scope: !171, file: !115, line: 1682, type: !56)
!2814 = !DILocation(line: 1682, column: 25, scope: !171)
!2815 = !DILocalVariable(name: "i", scope: !171, file: !115, line: 1690, type: !64)
!2816 = !DILocation(line: 1690, column: 6, scope: !171)
!2817 = !DILocation(line: 1691, column: 18, scope: !2818)
!2818 = distinct !DILexicalBlock(scope: !171, file: !115, line: 1691, column: 6)
!2819 = !DILocation(line: 1691, column: 7, scope: !2820)
!2820 = !DILexicalBlockFile(scope: !2818, file: !115, discriminator: 1)
!2821 = !DILocation(line: 1691, column: 7, scope: !2818)
!2822 = !DILocation(line: 1691, column: 6, scope: !171)
!2823 = !DILocation(line: 1692, column: 3, scope: !2824)
!2824 = distinct !DILexicalBlock(scope: !2818, file: !115, line: 1691, column: 58)
!2825 = !DILocation(line: 1693, column: 3, scope: !2824)
!2826 = !DILocation(line: 1695, column: 9, scope: !2827)
!2827 = distinct !DILexicalBlock(scope: !171, file: !115, line: 1695, column: 2)
!2828 = !DILocation(line: 1695, column: 7, scope: !2827)
!2829 = !DILocation(line: 1695, column: 22, scope: !2830)
!2830 = !DILexicalBlockFile(scope: !2831, file: !115, discriminator: 1)
!2831 = distinct !DILexicalBlock(scope: !2827, file: !115, line: 1695, column: 2)
!2832 = !DILocation(line: 1695, column: 14, scope: !2830)
!2833 = !DILocation(line: 1695, column: 25, scope: !2830)
!2834 = !DILocation(line: 1695, column: 2, scope: !2830)
!2835 = !DILocation(line: 1696, column: 20, scope: !2836)
!2836 = distinct !DILexicalBlock(scope: !2837, file: !115, line: 1696, column: 7)
!2837 = distinct !DILexicalBlock(scope: !2831, file: !115, line: 1695, column: 36)
!2838 = !DILocation(line: 1696, column: 33, scope: !2836)
!2839 = !DILocation(line: 1696, column: 25, scope: !2836)
!2840 = !DILocation(line: 1696, column: 36, scope: !2836)
!2841 = !DILocation(line: 1696, column: 57, scope: !2836)
!2842 = !DILocation(line: 1696, column: 49, scope: !2836)
!2843 = !DILocation(line: 1696, column: 60, scope: !2836)
!2844 = !DILocation(line: 1696, column: 42, scope: !2836)
!2845 = !DILocation(line: 1696, column: 8, scope: !2846)
!2846 = !DILexicalBlockFile(scope: !2836, file: !115, discriminator: 1)
!2847 = !DILocation(line: 1696, column: 8, scope: !2836)
!2848 = !DILocation(line: 1696, column: 7, scope: !2837)
!2849 = !DILocation(line: 1697, column: 10, scope: !2850)
!2850 = distinct !DILexicalBlock(scope: !2836, file: !115, line: 1696, column: 68)
!2851 = !DILocation(line: 1697, column: 30, scope: !2850)
!2852 = !DILocation(line: 1697, column: 22, scope: !2850)
!2853 = !DILocation(line: 1697, column: 33, scope: !2850)
!2854 = !DILocation(line: 1697, column: 15, scope: !2850)
!2855 = !DILocation(line: 1697, column: 4, scope: !2856)
!2856 = !DILexicalBlockFile(scope: !2850, file: !115, discriminator: 1)
!2857 = !DILocation(line: 1698, column: 12, scope: !2850)
!2858 = !DILocation(line: 1698, column: 4, scope: !2850)
!2859 = !DILocation(line: 1698, column: 15, scope: !2850)
!2860 = !DILocation(line: 1698, column: 24, scope: !2850)
!2861 = !DILocation(line: 1699, column: 4, scope: !2850)
!2862 = !DILocation(line: 1701, column: 2, scope: !2837)
!2863 = !DILocation(line: 1695, column: 32, scope: !2864)
!2864 = !DILexicalBlockFile(scope: !2831, file: !115, discriminator: 2)
!2865 = !DILocation(line: 1695, column: 2, scope: !2864)
!2866 = !DILocation(line: 1704, column: 26, scope: !2867)
!2867 = distinct !DILexicalBlock(scope: !171, file: !115, line: 1704, column: 13)
!2868 = !DILocation(line: 1704, column: 15, scope: !2867)
!2869 = !DILocation(line: 1704, column: 13, scope: !171)
!2870 = !DILocation(line: 1706, column: 13, scope: !2871)
!2871 = distinct !DILexicalBlock(scope: !2867, file: !115, line: 1705, column: 9)
!2872 = !DILocation(line: 1707, column: 13, scope: !2871)
!2873 = !DILocation(line: 1708, column: 13, scope: !2871)
!2874 = !DILocation(line: 1709, column: 13, scope: !2871)
!2875 = !DILocation(line: 1710, column: 13, scope: !2871)
!2876 = !DILocation(line: 1712, column: 64, scope: !171)
!2877 = !DILocation(line: 1712, column: 2, scope: !171)
!2878 = !DILocation(line: 1713, column: 1, scope: !171)
!2879 = !DILocation(line: 1713, column: 1, scope: !2880)
!2880 = !DILexicalBlockFile(scope: !171, file: !115, discriminator: 1)
!2881 = !DILocalVariable(name: "type", arg: 1, scope: !172, file: !115, line: 1715, type: !56)
!2882 = !DILocation(line: 1715, column: 25, scope: !172)
!2883 = !DILocation(line: 1717, column: 5, scope: !172)
!2884 = !DILocation(line: 1718, column: 1, scope: !172)
!2885 = !DILocalVariable(name: "params", arg: 1, scope: !174, file: !115, line: 1778, type: !56)
!2886 = !DILocation(line: 1778, column: 25, scope: !174)
!2887 = !DILocation(line: 1780, column: 22, scope: !2888)
!2888 = distinct !DILexicalBlock(scope: !174, file: !115, line: 1780, column: 9)
!2889 = !DILocation(line: 1780, column: 11, scope: !2888)
!2890 = !DILocation(line: 1780, column: 9, scope: !174)
!2891 = !DILocation(line: 1781, column: 8, scope: !2888)
!2892 = !DILocation(line: 1783, column: 61, scope: !2888)
!2893 = !DILocation(line: 1783, column: 8, scope: !2888)
!2894 = !DILocation(line: 1784, column: 1, scope: !174)
!2895 = !DILocalVariable(name: "params", arg: 1, scope: !175, file: !115, line: 1787, type: !56)
!2896 = !DILocation(line: 1787, column: 25, scope: !175)
!2897 = !DILocalVariable(name: "i", scope: !175, file: !115, line: 1789, type: !64)
!2898 = !DILocation(line: 1789, column: 6, scope: !175)
!2899 = !DILocation(line: 1790, column: 6, scope: !2900)
!2900 = distinct !DILexicalBlock(scope: !175, file: !115, line: 1790, column: 6)
!2901 = !DILocation(line: 1790, column: 16, scope: !2900)
!2902 = !DILocation(line: 1790, column: 6, scope: !175)
!2903 = !DILocation(line: 1791, column: 3, scope: !2904)
!2904 = distinct !DILexicalBlock(scope: !2900, file: !115, line: 1790, column: 25)
!2905 = !DILocation(line: 1792, column: 10, scope: !2906)
!2906 = distinct !DILexicalBlock(scope: !2904, file: !115, line: 1792, column: 3)
!2907 = !DILocation(line: 1792, column: 8, scope: !2906)
!2908 = !DILocation(line: 1792, column: 24, scope: !2909)
!2909 = !DILexicalBlockFile(scope: !2910, file: !115, discriminator: 1)
!2910 = distinct !DILexicalBlock(scope: !2906, file: !115, line: 1792, column: 3)
!2911 = !DILocation(line: 1792, column: 15, scope: !2909)
!2912 = !DILocation(line: 1792, column: 27, scope: !2909)
!2913 = !DILocation(line: 1792, column: 3, scope: !2909)
!2914 = !DILocation(line: 1793, column: 50, scope: !2910)
!2915 = !DILocation(line: 1793, column: 41, scope: !2910)
!2916 = !DILocation(line: 1793, column: 53, scope: !2910)
!2917 = !DILocation(line: 1793, column: 4, scope: !2910)
!2918 = !DILocation(line: 1792, column: 34, scope: !2919)
!2919 = !DILexicalBlockFile(scope: !2910, file: !115, discriminator: 2)
!2920 = !DILocation(line: 1792, column: 3, scope: !2919)
!2921 = !DILocation(line: 1794, column: 9, scope: !2904)
!2922 = !DILocation(line: 1795, column: 2, scope: !2904)
!2923 = !DILocation(line: 1796, column: 10, scope: !2924)
!2924 = distinct !DILexicalBlock(scope: !2925, file: !115, line: 1796, column: 3)
!2925 = distinct !DILexicalBlock(scope: !2900, file: !115, line: 1795, column: 9)
!2926 = !DILocation(line: 1796, column: 8, scope: !2924)
!2927 = !DILocation(line: 1796, column: 24, scope: !2928)
!2928 = !DILexicalBlockFile(scope: !2929, file: !115, discriminator: 1)
!2929 = distinct !DILexicalBlock(scope: !2924, file: !115, line: 1796, column: 3)
!2930 = !DILocation(line: 1796, column: 15, scope: !2928)
!2931 = !DILocation(line: 1796, column: 27, scope: !2928)
!2932 = !DILocation(line: 1796, column: 3, scope: !2928)
!2933 = !DILocation(line: 1797, column: 20, scope: !2934)
!2934 = distinct !DILexicalBlock(scope: !2929, file: !115, line: 1797, column: 8)
!2935 = !DILocation(line: 1797, column: 37, scope: !2934)
!2936 = !DILocation(line: 1797, column: 28, scope: !2934)
!2937 = !DILocation(line: 1797, column: 40, scope: !2934)
!2938 = !DILocation(line: 1797, column: 9, scope: !2934)
!2939 = !DILocation(line: 1797, column: 8, scope: !2929)
!2940 = !DILocation(line: 1798, column: 59, scope: !2934)
!2941 = !DILocation(line: 1798, column: 50, scope: !2934)
!2942 = !DILocation(line: 1798, column: 62, scope: !2934)
!2943 = !DILocation(line: 1798, column: 5, scope: !2934)
!2944 = !DILocation(line: 1797, column: 44, scope: !2945)
!2945 = !DILexicalBlockFile(scope: !2934, file: !115, discriminator: 1)
!2946 = !DILocation(line: 1796, column: 34, scope: !2947)
!2947 = !DILexicalBlockFile(scope: !2929, file: !115, discriminator: 2)
!2948 = !DILocation(line: 1796, column: 3, scope: !2947)
!2949 = !DILocation(line: 1800, column: 1, scope: !175)
!2950 = !DILocalVariable(name: "params", arg: 1, scope: !173, file: !115, line: 1767, type: !56)
!2951 = !DILocation(line: 1767, column: 25, scope: !173)
!2952 = !DILocalVariable(name: "i", scope: !173, file: !115, line: 1769, type: !64)
!2953 = !DILocation(line: 1769, column: 9, scope: !173)
!2954 = !DILocation(line: 1770, column: 5, scope: !173)
!2955 = !DILocation(line: 1771, column: 12, scope: !2956)
!2956 = distinct !DILexicalBlock(scope: !173, file: !115, line: 1771, column: 5)
!2957 = !DILocation(line: 1771, column: 10, scope: !2956)
!2958 = !DILocation(line: 1771, column: 26, scope: !2959)
!2959 = !DILexicalBlockFile(scope: !2960, file: !115, discriminator: 1)
!2960 = distinct !DILexicalBlock(scope: !2956, file: !115, line: 1771, column: 5)
!2961 = !DILocation(line: 1771, column: 17, scope: !2959)
!2962 = !DILocation(line: 1771, column: 29, scope: !2959)
!2963 = !DILocation(line: 1771, column: 5, scope: !2959)
!2964 = !DILocation(line: 1772, column: 22, scope: !2965)
!2965 = distinct !DILexicalBlock(scope: !2960, file: !115, line: 1772, column: 13)
!2966 = !DILocation(line: 1772, column: 13, scope: !2965)
!2967 = !DILocation(line: 1772, column: 25, scope: !2965)
!2968 = !DILocation(line: 1772, column: 13, scope: !2960)
!2969 = !DILocation(line: 1773, column: 56, scope: !2965)
!2970 = !DILocation(line: 1773, column: 47, scope: !2965)
!2971 = !DILocation(line: 1773, column: 59, scope: !2965)
!2972 = !DILocation(line: 1773, column: 13, scope: !2965)
!2973 = !DILocation(line: 1772, column: 25, scope: !2974)
!2974 = !DILexicalBlockFile(scope: !2965, file: !115, discriminator: 1)
!2975 = !DILocation(line: 1771, column: 36, scope: !2976)
!2976 = !DILexicalBlockFile(scope: !2960, file: !115, discriminator: 2)
!2977 = !DILocation(line: 1771, column: 5, scope: !2976)
!2978 = !DILocation(line: 1774, column: 5, scope: !173)
!2979 = !DILocation(line: 1775, column: 5, scope: !173)
!2980 = !DILocation(line: 1776, column: 1, scope: !173)
!2981 = !DILocalVariable(name: "str", arg: 1, scope: !176, file: !115, line: 1802, type: !56)
!2982 = !DILocation(line: 1802, column: 20, scope: !176)
!2983 = !DILocalVariable(name: "i", scope: !176, file: !115, line: 1804, type: !64)
!2984 = !DILocation(line: 1804, column: 6, scope: !176)
!2985 = !DILocalVariable(name: "p", scope: !176, file: !115, line: 1805, type: !56)
!2986 = !DILocation(line: 1805, column: 8, scope: !176)
!2987 = !DILocalVariable(name: "pp", scope: !176, file: !115, line: 1805, type: !56)
!2988 = !DILocation(line: 1805, column: 12, scope: !176)
!2989 = !DILocalVariable(name: "confstr", scope: !176, file: !115, line: 1805, type: !2761)
!2990 = !DILocation(line: 1805, column: 16, scope: !176)
!2991 = !DILocation(line: 1806, column: 11, scope: !176)
!2992 = !DILocation(line: 1806, column: 9, scope: !176)
!2993 = !DILocation(line: 1806, column: 4, scope: !176)
!2994 = !DILocation(line: 1807, column: 2, scope: !176)
!2995 = !DILocation(line: 1807, column: 10, scope: !2996)
!2996 = !DILexicalBlockFile(scope: !176, file: !115, discriminator: 1)
!2997 = !DILocation(line: 1807, column: 9, scope: !2996)
!2998 = !DILocation(line: 1807, column: 2, scope: !2996)
!2999 = !DILocation(line: 1808, column: 24, scope: !3000)
!3000 = distinct !DILexicalBlock(scope: !176, file: !115, line: 1808, column: 7)
!3001 = !DILocation(line: 1808, column: 23, scope: !3000)
!3002 = !DILocation(line: 1808, column: 7, scope: !3000)
!3003 = !DILocation(line: 1808, column: 26, scope: !3000)
!3004 = !DILocation(line: 1808, column: 7, scope: !176)
!3005 = !DILocation(line: 1809, column: 5, scope: !3000)
!3006 = !DILocation(line: 1809, column: 4, scope: !3000)
!3007 = !DILocation(line: 1811, column: 14, scope: !3000)
!3008 = !DILocation(line: 1811, column: 12, scope: !3000)
!3009 = !DILocation(line: 1811, column: 7, scope: !3000)
!3010 = !DILocation(line: 1811, column: 10, scope: !3000)
!3011 = !DILocation(line: 1807, column: 2, scope: !3012)
!3012 = !DILexicalBlockFile(scope: !176, file: !115, discriminator: 2)
!3013 = !DILocation(line: 1812, column: 5, scope: !176)
!3014 = !DILocation(line: 1812, column: 8, scope: !176)
!3015 = !DILocation(line: 1813, column: 9, scope: !3016)
!3016 = distinct !DILexicalBlock(scope: !176, file: !115, line: 1813, column: 2)
!3017 = !DILocation(line: 1813, column: 7, scope: !3016)
!3018 = !DILocation(line: 1813, column: 23, scope: !3019)
!3019 = !DILexicalBlockFile(scope: !3020, file: !115, discriminator: 1)
!3020 = distinct !DILexicalBlock(scope: !3016, file: !115, line: 1813, column: 2)
!3021 = !DILocation(line: 1813, column: 14, scope: !3019)
!3022 = !DILocation(line: 1813, column: 26, scope: !3019)
!3023 = !DILocation(line: 1813, column: 2, scope: !3019)
!3024 = !DILocation(line: 1814, column: 20, scope: !3025)
!3025 = distinct !DILexicalBlock(scope: !3026, file: !115, line: 1814, column: 7)
!3026 = distinct !DILexicalBlock(scope: !3020, file: !115, line: 1813, column: 37)
!3027 = !DILocation(line: 1814, column: 34, scope: !3025)
!3028 = !DILocation(line: 1814, column: 25, scope: !3025)
!3029 = !DILocation(line: 1814, column: 37, scope: !3025)
!3030 = !DILocation(line: 1814, column: 59, scope: !3025)
!3031 = !DILocation(line: 1814, column: 50, scope: !3025)
!3032 = !DILocation(line: 1814, column: 62, scope: !3025)
!3033 = !DILocation(line: 1814, column: 43, scope: !3025)
!3034 = !DILocation(line: 1814, column: 8, scope: !3035)
!3035 = !DILexicalBlockFile(scope: !3025, file: !115, discriminator: 1)
!3036 = !DILocation(line: 1814, column: 8, scope: !3025)
!3037 = !DILocation(line: 1814, column: 7, scope: !3026)
!3038 = !DILocation(line: 1815, column: 21, scope: !3039)
!3039 = distinct !DILexicalBlock(scope: !3025, file: !115, line: 1814, column: 70)
!3040 = !DILocation(line: 1815, column: 58, scope: !3039)
!3041 = !DILocation(line: 1815, column: 49, scope: !3039)
!3042 = !DILocation(line: 1815, column: 61, scope: !3039)
!3043 = !DILocation(line: 1815, column: 13, scope: !3039)
!3044 = !DILocation(line: 1816, column: 46, scope: !3045)
!3045 = distinct !DILexicalBlock(scope: !3039, file: !115, line: 1816, column: 17)
!3046 = !DILocation(line: 1816, column: 29, scope: !3045)
!3047 = !DILocation(line: 1816, column: 18, scope: !3048)
!3048 = !DILexicalBlockFile(scope: !3045, file: !115, discriminator: 1)
!3049 = !DILocation(line: 1816, column: 18, scope: !3045)
!3050 = !DILocation(line: 1816, column: 17, scope: !3039)
!3051 = !DILocation(line: 1818, column: 34, scope: !3052)
!3052 = distinct !DILexicalBlock(scope: !3045, file: !115, line: 1816, column: 63)
!3053 = !DILocation(line: 1818, column: 25, scope: !3052)
!3054 = !DILocation(line: 1818, column: 37, scope: !3052)
!3055 = !DILocation(line: 1817, column: 17, scope: !3052)
!3056 = !DILocation(line: 1819, column: 17, scope: !3052)
!3057 = !DILocation(line: 1821, column: 10, scope: !3039)
!3058 = !DILocation(line: 1821, column: 31, scope: !3039)
!3059 = !DILocation(line: 1821, column: 22, scope: !3039)
!3060 = !DILocation(line: 1821, column: 34, scope: !3039)
!3061 = !DILocation(line: 1821, column: 15, scope: !3039)
!3062 = !DILocation(line: 1821, column: 4, scope: !3063)
!3063 = !DILexicalBlockFile(scope: !3039, file: !115, discriminator: 1)
!3064 = !DILocation(line: 1822, column: 8, scope: !3039)
!3065 = !DILocation(line: 1822, column: 6, scope: !3039)
!3066 = !DILocation(line: 1823, column: 4, scope: !3039)
!3067 = !DILocation(line: 1823, column: 13, scope: !3063)
!3068 = !DILocation(line: 1823, column: 12, scope: !3063)
!3069 = !DILocation(line: 1823, column: 11, scope: !3063)
!3070 = !DILocation(line: 1823, column: 16, scope: !3063)
!3071 = !DILocation(line: 1823, column: 22, scope: !3072)
!3072 = !DILexicalBlockFile(scope: !3039, file: !115, discriminator: 2)
!3073 = !DILocation(line: 1823, column: 21, scope: !3072)
!3074 = !DILocation(line: 1823, column: 24, scope: !3072)
!3075 = !DILocation(line: 1823, column: 32, scope: !3072)
!3076 = !DILocation(line: 1823, column: 37, scope: !3077)
!3077 = !DILexicalBlockFile(scope: !3039, file: !115, discriminator: 3)
!3078 = !DILocation(line: 1823, column: 36, scope: !3077)
!3079 = !DILocation(line: 1823, column: 39, scope: !3077)
!3080 = !DILocation(line: 1823, column: 32, scope: !3077)
!3081 = !DILocation(line: 1823, column: 4, scope: !3082)
!3082 = !DILexicalBlockFile(scope: !3039, file: !115, discriminator: 4)
!3083 = !DILocation(line: 1824, column: 6, scope: !3039)
!3084 = !DILocation(line: 1823, column: 4, scope: !3085)
!3085 = !DILexicalBlockFile(scope: !3039, file: !115, discriminator: 5)
!3086 = !DILocation(line: 1825, column: 12, scope: !3039)
!3087 = !DILocation(line: 1825, column: 17, scope: !3039)
!3088 = !DILocation(line: 1825, column: 27, scope: !3039)
!3089 = !DILocation(line: 1825, column: 20, scope: !3039)
!3090 = !DILocation(line: 1825, column: 35, scope: !3039)
!3091 = !DILocation(line: 1825, column: 39, scope: !3039)
!3092 = !DILocation(line: 1825, column: 37, scope: !3039)
!3093 = !DILocation(line: 1825, column: 32, scope: !3039)
!3094 = !DILocation(line: 1825, column: 44, scope: !3039)
!3095 = !DILocation(line: 1825, column: 4, scope: !3063)
!3096 = !DILocation(line: 1826, column: 8, scope: !3097)
!3097 = distinct !DILexicalBlock(scope: !3039, file: !115, line: 1826, column: 8)
!3098 = !DILocation(line: 1826, column: 26, scope: !3097)
!3099 = !DILocation(line: 1826, column: 17, scope: !3097)
!3100 = !DILocation(line: 1826, column: 29, scope: !3097)
!3101 = !DILocation(line: 1826, column: 14, scope: !3097)
!3102 = !DILocation(line: 1826, column: 8, scope: !3039)
!3103 = !DILocation(line: 1827, column: 14, scope: !3104)
!3104 = distinct !DILexicalBlock(scope: !3097, file: !115, line: 1826, column: 43)
!3105 = !DILocation(line: 1827, column: 5, scope: !3104)
!3106 = !DILocation(line: 1827, column: 17, scope: !3104)
!3107 = !DILocation(line: 1827, column: 26, scope: !3104)
!3108 = !DILocation(line: 1828, column: 5, scope: !3104)
!3109 = !DILocation(line: 1830, column: 13, scope: !3110)
!3110 = distinct !DILexicalBlock(scope: !3097, file: !115, line: 1829, column: 11)
!3111 = !DILocation(line: 1830, column: 5, scope: !3110)
!3112 = !DILocation(line: 1832, column: 7, scope: !3113)
!3113 = distinct !DILexicalBlock(scope: !3114, file: !115, line: 1831, column: 28)
!3114 = distinct !DILexicalBlock(scope: !3110, file: !115, line: 1830, column: 20)
!3115 = !DILocation(line: 1833, column: 7, scope: !3113)
!3116 = !DILocation(line: 1836, column: 7, scope: !3117)
!3117 = distinct !DILexicalBlock(scope: !3114, file: !115, line: 1835, column: 23)
!3118 = !DILocation(line: 1837, column: 7, scope: !3117)
!3119 = !DILocation(line: 1840, column: 7, scope: !3120)
!3120 = distinct !DILexicalBlock(scope: !3114, file: !115, line: 1839, column: 32)
!3121 = !DILocation(line: 1841, column: 7, scope: !3120)
!3122 = !DILocation(line: 1845, column: 3, scope: !3039)
!3123 = !DILocation(line: 1846, column: 2, scope: !3026)
!3124 = !DILocation(line: 1813, column: 33, scope: !3125)
!3125 = !DILexicalBlockFile(scope: !3020, file: !115, discriminator: 2)
!3126 = !DILocation(line: 1813, column: 2, scope: !3125)
!3127 = !DILocation(line: 1847, column: 60, scope: !176)
!3128 = !DILocation(line: 1847, column: 2, scope: !176)
!3129 = !DILocation(line: 1848, column: 2, scope: !176)
!3130 = !DILocation(line: 1849, column: 1, scope: !176)
!3131 = !DILocation(line: 1922, column: 27, scope: !185)
!3132 = !DILocation(line: 1922, column: 39, scope: !185)
!3133 = !DILocation(line: 1922, column: 4, scope: !185)
!3134 = !DILocation(line: 1923, column: 1, scope: !185)
