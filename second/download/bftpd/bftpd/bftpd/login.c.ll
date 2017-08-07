; ModuleID = '/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/login.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.passwd = type { i8*, i8*, i32, i32, i8*, i8*, i8* }
%struct.utmp = type { i16, i32, [32 x i8], [4 x i8], [32 x i8], [256 x i8], %struct.exit_status, i32, %struct.anon, [4 x i32], [20 x i8] }
%struct.exit_status = type { i16, i16 }
%struct.anon = type { i32, i32 }
%struct.spwd = type { i8*, i8*, i64, i64, i64, i64, i64, i64, i64 }

@userinfo_set = global i8 0, align 1
@.str = private unnamed_addr constant [13 x i8] c"%255s%*[^\0A]\0A\00", align 1
@.str.1 = private unnamed_addr constant [3 x i8] c"%i\00", align 1
@.str.2 = private unnamed_addr constant [9 x i8] c"LOG_WTMP\00", align 1
@.str.3 = private unnamed_addr constant [3 x i8] c"no\00", align 1
@.str.4 = private unnamed_addr constant [14 x i8] c"/var/log/wtmp\00", align 1
@.str.5 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@wtmp = common global %struct._IO_FILE* null, align 8
@.str.6 = private unnamed_addr constant [29 x i8] c"Warning: Unable to open %s.\0A\00", align 1
@.str.7 = private unnamed_addr constant [6 x i8] c"ftp%i\00", align 1
@user = external global [31 x i8], align 16
@remotehostname = external global i8*, align 8
@state = external global i32, align 4
@.str.8 = private unnamed_addr constant [15 x i8] c"INITIAL_CHROOT\00", align 1
@.str.9 = private unnamed_addr constant [30 x i8] c"421 Initial chroot failed.\0D\0A.\00", align 1
@.str.10 = private unnamed_addr constant [11 x i8] c"DATAPORT20\00", align 1
@.str.11 = private unnamed_addr constant [4 x i8] c"yes\00", align 1
@.str.12 = private unnamed_addr constant [10 x i8] c"FILE_AUTH\00", align 1
@.str.13 = private unnamed_addr constant [15 x i8] c"ANONYMOUS_USER\00", align 1
@.str.14 = private unnamed_addr constant [2 x i8] c"/\00", align 1
@.str.15 = private unnamed_addr constant [21 x i8] c"530 Login incorrect.\00", align 1
@.str.16 = private unnamed_addr constant [32 x i8] c"530 Anonymous user not allowed.\00", align 1
@.str.17 = private unnamed_addr constant [11 x i8] c"DENY_LOGIN\00", align 1
@.str.18 = private unnamed_addr constant [37 x i8] c"530-Server disabled.\0D\0A421 Reason: %s\00", align 1
@.str.19 = private unnamed_addr constant [45 x i8] c"Login as user '%s' failed: Server disabled.\0A\00", align 1
@.str.20 = private unnamed_addr constant [17 x i8] c"USERLIMIT_GLOBAL\00", align 1
@.str.21 = private unnamed_addr constant [52 x i8] c"Error getting max users for GLOBAL in bftpd_login.\0A\00", align 1
@.str.22 = private unnamed_addr constant [2 x i8] c"*\00", align 1
@.str.23 = private unnamed_addr constant [42 x i8] c"421 There are already %i users logged in.\00", align 1
@.str.24 = private unnamed_addr constant [54 x i8] c"Login as user '%s' failed. Too many users on server.\0A\00", align 1
@.str.25 = private unnamed_addr constant [21 x i8] c"USERLIMIT_SINGLEUSER\00", align 1
@.str.26 = private unnamed_addr constant [55 x i8] c"error getting max users (SINGLE USER) in bftpd_login.\0A\00", align 1
@.str.27 = private unnamed_addr constant [43 x i8] c"421 User %s is already logged in %i times.\00", align 1
@.str.28 = private unnamed_addr constant [55 x i8] c"Login as user '%s' failed. Already logged in %d times.\00", align 1
@.str.29 = private unnamed_addr constant [15 x i8] c"USERLIMIT_HOST\00", align 1
@.str.30 = private unnamed_addr constant [50 x i8] c"Error getting max users per HOST in bftpd_login.\0A\00", align 1
@.str.31 = private unnamed_addr constant [47 x i8] c"421 Too many connections from your IP address.\00", align 1
@.str.32 = private unnamed_addr constant [60 x i8] c"Login as user '%s' failed. Already %d connections from %s.\0A\00", align 1
@.str.33 = private unnamed_addr constant [6 x i8] c"RATIO\00", align 1
@.str.34 = private unnamed_addr constant [5 x i8] c"none\00", align 1
@.str.35 = private unnamed_addr constant [6 x i8] c"%i/%i\00", align 1
@ratio_send = external global i32, align 4
@ratio_recv = external global i32, align 4
@.str.36 = private unnamed_addr constant [8 x i8] c"ROOTDIR\00", align 1
@.str.37 = private unnamed_addr constant [3 x i8] c"%h\00", align 1
@.str.38 = private unnamed_addr constant [3 x i8] c"%u\00", align 1
@userinfo = common global %struct.passwd zeroinitializer, align 8
@.str.39 = private unnamed_addr constant [13 x i8] c"RESOLVE_UIDS\00", align 1
@.str.40 = private unnamed_addr constant [12 x i8] c"/etc/passwd\00", align 1
@.str.41 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@passwdfile = external global %struct._IO_FILE*, align 8
@.str.42 = private unnamed_addr constant [11 x i8] c"/etc/group\00", align 1
@groupfile = external global %struct._IO_FILE*, align 8
@.str.43 = private unnamed_addr constant [10 x i8] c"DO_CHROOT\00", align 1
@.str.44 = private unnamed_addr constant [42 x i8] c"421 Unable to change root directory.\0D\0A%s.\00", align 1
@.str.45 = private unnamed_addr constant [28 x i8] c"421 Unable to change uid.\0D\0A\00", align 1
@.str.46 = private unnamed_addr constant [45 x i8] c"421 Unable to change working directory.\0D\0A%s.\00", align 1
@.str.47 = private unnamed_addr constant [39 x i8] c"230 Couldn't change cwd to '%s': %s.\0D\0A\00", align 1
@.str.48 = private unnamed_addr constant [39 x i8] c"421 Unable to change root directory.\0D\0A\00", align 1
@.str.49 = private unnamed_addr constant [42 x i8] c"421 Unable to change working directory.\0D\0A\00", align 1
@.str.50 = private unnamed_addr constant [10 x i8] c"MOTD_USER\00", align 1
@.str.51 = private unnamed_addr constant [20 x i8] c"230 User logged in.\00", align 1
@.str.52 = private unnamed_addr constant [38 x i8] c"Successfully logged in as user '%s'.\0A\00", align 1
@.str.53 = private unnamed_addr constant [11 x i8] c"AUTO_CHDIR\00", align 1
@.str.54 = private unnamed_addr constant [14 x i8] c"PATH_FTPUSERS\00", align 1
@.str.55 = private unnamed_addr constant [15 x i8] c"AUTH_ETCSHELLS\00", align 1
@.str.56 = private unnamed_addr constant [20 x i8] c"%32s %32s %32s %32s\00", align 1
@configpath = common global i8* null, align 8
@daemonmode = common global i32 0, align 4
@pre_write_script = common global i8* null, align 8
@post_write_script = common global i8* null, align 8

; Function Attrs: nounwind uwtable
define i8* @mygetpwuid(i32 %uid, %struct._IO_FILE* %file, i8* %name) #0 !dbg !17 {
entry:
  %retval = alloca i8*, align 8
  %uid.addr = alloca i32, align 4
  %file.addr = alloca %struct._IO_FILE*, align 8
  %name.addr = alloca i8*, align 8
  %_uid = alloca i32, align 4
  %foo = alloca [256 x i8], align 16
  %i = alloca i32, align 4
  store i32 %uid, i32* %uid.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %uid.addr, metadata !134, metadata !135), !dbg !136
  store %struct._IO_FILE* %file, %struct._IO_FILE** %file.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %file.addr, metadata !137, metadata !135), !dbg !138
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !139, metadata !135), !dbg !140
  call void @llvm.dbg.declare(metadata i32* %_uid, metadata !141, metadata !135), !dbg !142
  call void @llvm.dbg.declare(metadata [256 x i8]* %foo, metadata !143, metadata !135), !dbg !147
  call void @llvm.dbg.declare(metadata i32* %i, metadata !148, metadata !135), !dbg !149
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** %file.addr, align 8, !dbg !150
  %tobool = icmp ne %struct._IO_FILE* %0, null, !dbg !150
  br i1 %tobool, label %if.then, label %if.end38, !dbg !152

if.then:                                          ; preds = %entry
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** %file.addr, align 8, !dbg !153
  call void @rewind(%struct._IO_FILE* %1), !dbg !155
  br label %while.cond, !dbg !156

while.cond:                                       ; preds = %if.end37, %if.then13, %if.then
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** %file.addr, align 8, !dbg !157
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !159
  %call = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %2, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str, i32 0, i32 0), i8* %arraydecay), !dbg !160
  %cmp = icmp ne i32 %call, -1, !dbg !161
  br i1 %cmp, label %while.body, label %while.end, !dbg !162

while.body:                                       ; preds = %while.cond
  %arrayidx = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i64 0, i64 0, !dbg !163
  %3 = load i8, i8* %arrayidx, align 16, !dbg !163
  %conv = sext i8 %3 to i32, !dbg !163
  %cmp1 = icmp eq i32 %conv, 35, !dbg !166
  br i1 %cmp1, label %if.then13, label %lor.lhs.false, !dbg !167

lor.lhs.false:                                    ; preds = %while.body
  %arraydecay3 = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !168
  %call4 = call i8* @strchr(i8* %arraydecay3, i32 58) #8, !dbg !170
  %tobool5 = icmp ne i8* %call4, null, !dbg !170
  br i1 %tobool5, label %lor.lhs.false6, label %if.then13, !dbg !171

lor.lhs.false6:                                   ; preds = %lor.lhs.false
  %arraydecay7 = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !172
  %call8 = call i8* @strchr(i8* %arraydecay7, i32 58) #8, !dbg !174
  %arraydecay9 = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !175
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay9, i64 30, !dbg !176
  %add.ptr10 = getelementptr inbounds i8, i8* %add.ptr, i64 -1, !dbg !177
  %cmp11 = icmp ugt i8* %call8, %add.ptr10, !dbg !178
  br i1 %cmp11, label %if.then13, label %if.end, !dbg !179

if.then13:                                        ; preds = %lor.lhs.false6, %lor.lhs.false, %while.body
  br label %while.cond, !dbg !180

if.end:                                           ; preds = %lor.lhs.false6
  %arraydecay14 = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !181
  %call15 = call i8* @strchr(i8* %arraydecay14, i32 58) #8, !dbg !182
  %arraydecay16 = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !183
  %sub.ptr.lhs.cast = ptrtoint i8* %call15 to i64, !dbg !184
  %sub.ptr.rhs.cast = ptrtoint i8* %arraydecay16 to i64, !dbg !184
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !184
  %conv17 = trunc i64 %sub.ptr.sub to i32, !dbg !182
  store i32 %conv17, i32* %i, align 4, !dbg !185
  %4 = load i8*, i8** %name.addr, align 8, !dbg !186
  %arraydecay18 = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !187
  %5 = load i32, i32* %i, align 4, !dbg !188
  %conv19 = sext i32 %5 to i64, !dbg !188
  %call20 = call i8* @strncpy(i8* %4, i8* %arraydecay18, i64 %conv19) #9, !dbg !189
  %6 = load i32, i32* %i, align 4, !dbg !190
  %idxprom = sext i32 %6 to i64, !dbg !191
  %7 = load i8*, i8** %name.addr, align 8, !dbg !191
  %arrayidx21 = getelementptr inbounds i8, i8* %7, i64 %idxprom, !dbg !191
  store i8 0, i8* %arrayidx21, align 1, !dbg !192
  %arraydecay22 = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !193
  %8 = load i32, i32* %i, align 4, !dbg !194
  %idx.ext = sext i32 %8 to i64, !dbg !195
  %add.ptr23 = getelementptr inbounds i8, i8* %arraydecay22, i64 %idx.ext, !dbg !195
  %add.ptr24 = getelementptr inbounds i8, i8* %add.ptr23, i64 1, !dbg !196
  %call25 = call i8* @strchr(i8* %add.ptr24, i32 58) #8, !dbg !197
  %add.ptr26 = getelementptr inbounds i8, i8* %call25, i64 1, !dbg !198
  %call27 = call i32 (i8*, i8*, ...) @__isoc99_sscanf(i8* %add.ptr26, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i32 0, i32 0), i32* %_uid) #9, !dbg !199
  %9 = load i32, i32* %_uid, align 4, !dbg !201
  %10 = load i32, i32* %uid.addr, align 4, !dbg !203
  %cmp28 = icmp eq i32 %9, %10, !dbg !204
  br i1 %cmp28, label %if.then30, label %if.end37, !dbg !205

if.then30:                                        ; preds = %if.end
  %11 = load i8*, i8** %name.addr, align 8, !dbg !206
  %arrayidx31 = getelementptr inbounds i8, i8* %11, i64 0, !dbg !206
  %12 = load i8, i8* %arrayidx31, align 1, !dbg !206
  %conv32 = sext i8 %12 to i32, !dbg !206
  %cmp33 = icmp eq i32 %conv32, 10, !dbg !209
  br i1 %cmp33, label %if.then35, label %if.end36, !dbg !210

if.then35:                                        ; preds = %if.then30
  %13 = load i8*, i8** %name.addr, align 8, !dbg !211
  call void @cutto(i8* %13, i32 1), !dbg !212
  br label %if.end36, !dbg !212

if.end36:                                         ; preds = %if.then35, %if.then30
  %14 = load i8*, i8** %name.addr, align 8, !dbg !213
  store i8* %14, i8** %retval, align 8, !dbg !214
  br label %return, !dbg !214

if.end37:                                         ; preds = %if.end
  br label %while.cond, !dbg !215

while.end:                                        ; preds = %while.cond
  br label %if.end38, !dbg !217

if.end38:                                         ; preds = %while.end, %entry
  %15 = load i8*, i8** %name.addr, align 8, !dbg !218
  %16 = load i32, i32* %uid.addr, align 4, !dbg !219
  %call39 = call i32 (i8*, i8*, ...) @sprintf(i8* %15, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i32 0, i32 0), i32 %16) #9, !dbg !220
  %17 = load i8*, i8** %name.addr, align 8, !dbg !221
  store i8* %17, i8** %retval, align 8, !dbg !222
  br label %return, !dbg !222

return:                                           ; preds = %if.end38, %if.end36
  %18 = load i8*, i8** %retval, align 8, !dbg !223
  ret i8* %18, !dbg !223
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @rewind(%struct._IO_FILE*) #2

declare i32 @__isoc99_fscanf(%struct._IO_FILE*, i8*, ...) #2

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #3

; Function Attrs: nounwind
declare i8* @strncpy(i8*, i8*, i64) #4

; Function Attrs: nounwind
declare i32 @__isoc99_sscanf(i8*, i8*, ...) #4

declare void @cutto(i8*, i32) #2

; Function Attrs: nounwind
declare i32 @sprintf(i8*, i8*, ...) #4

; Function Attrs: nounwind uwtable
define i32 @mygetpwnam(i8* %name, %struct._IO_FILE* %file) #0 !dbg !81 {
entry:
  %retval = alloca i32, align 4
  %name.addr = alloca i8*, align 8
  %file.addr = alloca %struct._IO_FILE*, align 8
  %_name = alloca [31 x i8], align 16
  %foo = alloca [256 x i8], align 16
  %uid = alloca i32, align 4
  %i = alloca i32, align 4
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !224, metadata !135), !dbg !225
  store %struct._IO_FILE* %file, %struct._IO_FILE** %file.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %file.addr, metadata !226, metadata !135), !dbg !227
  call void @llvm.dbg.declare(metadata [31 x i8]* %_name, metadata !228, metadata !135), !dbg !232
  call void @llvm.dbg.declare(metadata [256 x i8]* %foo, metadata !233, metadata !135), !dbg !234
  call void @llvm.dbg.declare(metadata i32* %uid, metadata !235, metadata !135), !dbg !236
  call void @llvm.dbg.declare(metadata i32* %i, metadata !237, metadata !135), !dbg !238
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** %file.addr, align 8, !dbg !239
  %tobool = icmp ne %struct._IO_FILE* %0, null, !dbg !239
  br i1 %tobool, label %if.then, label %if.end41, !dbg !241

if.then:                                          ; preds = %entry
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** %file.addr, align 8, !dbg !242
  call void @rewind(%struct._IO_FILE* %1), !dbg !244
  br label %while.cond, !dbg !245

while.cond:                                       ; preds = %if.end40, %if.then13, %if.then
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** %file.addr, align 8, !dbg !246
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !248
  %call = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %2, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str, i32 0, i32 0), i8* %arraydecay), !dbg !249
  %cmp = icmp ne i32 %call, -1, !dbg !250
  br i1 %cmp, label %while.body, label %while.end, !dbg !251

while.body:                                       ; preds = %while.cond
  %arrayidx = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i64 0, i64 0, !dbg !252
  %3 = load i8, i8* %arrayidx, align 16, !dbg !252
  %conv = sext i8 %3 to i32, !dbg !252
  %cmp1 = icmp eq i32 %conv, 35, !dbg !255
  br i1 %cmp1, label %if.then13, label %lor.lhs.false, !dbg !256

lor.lhs.false:                                    ; preds = %while.body
  %arraydecay3 = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !257
  %call4 = call i8* @strchr(i8* %arraydecay3, i32 58) #8, !dbg !259
  %tobool5 = icmp ne i8* %call4, null, !dbg !259
  br i1 %tobool5, label %lor.lhs.false6, label %if.then13, !dbg !260

lor.lhs.false6:                                   ; preds = %lor.lhs.false
  %arraydecay7 = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !261
  %call8 = call i8* @strchr(i8* %arraydecay7, i32 58) #8, !dbg !263
  %arraydecay9 = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !264
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay9, i64 30, !dbg !265
  %add.ptr10 = getelementptr inbounds i8, i8* %add.ptr, i64 -1, !dbg !266
  %cmp11 = icmp ugt i8* %call8, %add.ptr10, !dbg !267
  br i1 %cmp11, label %if.then13, label %if.end, !dbg !268

if.then13:                                        ; preds = %lor.lhs.false6, %lor.lhs.false, %while.body
  br label %while.cond, !dbg !269

if.end:                                           ; preds = %lor.lhs.false6
  %arraydecay14 = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !270
  %call15 = call i8* @strchr(i8* %arraydecay14, i32 58) #8, !dbg !271
  %arraydecay16 = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !272
  %sub.ptr.lhs.cast = ptrtoint i8* %call15 to i64, !dbg !273
  %sub.ptr.rhs.cast = ptrtoint i8* %arraydecay16 to i64, !dbg !273
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !273
  %conv17 = trunc i64 %sub.ptr.sub to i32, !dbg !271
  store i32 %conv17, i32* %i, align 4, !dbg !274
  %arraydecay18 = getelementptr inbounds [31 x i8], [31 x i8]* %_name, i32 0, i32 0, !dbg !275
  %arraydecay19 = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !276
  %4 = load i32, i32* %i, align 4, !dbg !277
  %conv20 = sext i32 %4 to i64, !dbg !277
  %call21 = call i8* @strncpy(i8* %arraydecay18, i8* %arraydecay19, i64 %conv20) #9, !dbg !278
  %5 = load i32, i32* %i, align 4, !dbg !279
  %idxprom = sext i32 %5 to i64, !dbg !280
  %arrayidx22 = getelementptr inbounds [31 x i8], [31 x i8]* %_name, i64 0, i64 %idxprom, !dbg !280
  store i8 0, i8* %arrayidx22, align 1, !dbg !281
  %arraydecay23 = getelementptr inbounds [256 x i8], [256 x i8]* %foo, i32 0, i32 0, !dbg !282
  %6 = load i32, i32* %i, align 4, !dbg !283
  %idx.ext = sext i32 %6 to i64, !dbg !284
  %add.ptr24 = getelementptr inbounds i8, i8* %arraydecay23, i64 %idx.ext, !dbg !284
  %add.ptr25 = getelementptr inbounds i8, i8* %add.ptr24, i64 1, !dbg !285
  %call26 = call i8* @strchr(i8* %add.ptr25, i32 58) #8, !dbg !286
  %add.ptr27 = getelementptr inbounds i8, i8* %call26, i64 1, !dbg !287
  %call28 = call i32 (i8*, i8*, ...) @__isoc99_sscanf(i8* %add.ptr27, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i32 0, i32 0), i32* %uid) #9, !dbg !288
  %arrayidx29 = getelementptr inbounds [31 x i8], [31 x i8]* %_name, i64 0, i64 0, !dbg !290
  %7 = load i8, i8* %arrayidx29, align 16, !dbg !290
  %conv30 = sext i8 %7 to i32, !dbg !290
  %cmp31 = icmp eq i32 %conv30, 10, !dbg !292
  br i1 %cmp31, label %if.then33, label %if.end35, !dbg !293

if.then33:                                        ; preds = %if.end
  %arraydecay34 = getelementptr inbounds [31 x i8], [31 x i8]* %_name, i32 0, i32 0, !dbg !294
  call void @cutto(i8* %arraydecay34, i32 1), !dbg !295
  br label %if.end35, !dbg !295

if.end35:                                         ; preds = %if.then33, %if.end
  %8 = load i8*, i8** %name.addr, align 8, !dbg !296
  %arraydecay36 = getelementptr inbounds [31 x i8], [31 x i8]* %_name, i32 0, i32 0, !dbg !298
  %call37 = call i32 @strcmp(i8* %8, i8* %arraydecay36) #8, !dbg !299
  %tobool38 = icmp ne i32 %call37, 0, !dbg !299
  br i1 %tobool38, label %if.end40, label %if.then39, !dbg !300

if.then39:                                        ; preds = %if.end35
  %9 = load i32, i32* %uid, align 4, !dbg !301
  store i32 %9, i32* %retval, align 4, !dbg !302
  br label %return, !dbg !302

if.end40:                                         ; preds = %if.end35
  br label %while.cond, !dbg !303

while.end:                                        ; preds = %while.cond
  br label %if.end41, !dbg !305

if.end41:                                         ; preds = %while.end, %entry
  store i32 -1, i32* %retval, align 4, !dbg !306
  br label %return, !dbg !306

return:                                           ; preds = %if.end41, %if.then39
  %10 = load i32, i32* %retval, align 4, !dbg !307
  ret i32 %10, !dbg !307
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #3

; Function Attrs: nounwind uwtable
define void @wtmp_init() #0 !dbg !84 {
entry:
  %call = call i8* @config_getoption(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.2, i32 0, i32 0)), !dbg !308
  %call1 = call i32 @strcasecmp(i8* %call, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.3, i32 0, i32 0)) #8, !dbg !310
  %tobool = icmp ne i32 %call1, 0, !dbg !312
  br i1 %tobool, label %if.then, label %if.end5, !dbg !313

if.then:                                          ; preds = %entry
  %call2 = call %struct._IO_FILE* @fopen64(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.5, i32 0, i32 0)), !dbg !314
  store %struct._IO_FILE* %call2, %struct._IO_FILE** @wtmp, align 8, !dbg !317
  %tobool3 = icmp ne %struct._IO_FILE* %call2, null, !dbg !317
  br i1 %tobool3, label %if.end, label %if.then4, !dbg !318

if.then4:                                         ; preds = %if.then
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.4, i32 0, i32 0)), !dbg !319
  br label %if.end, !dbg !319

if.end:                                           ; preds = %if.then4, %if.then
  br label %if.end5, !dbg !320

if.end5:                                          ; preds = %if.end, %entry
  ret void, !dbg !321
}

; Function Attrs: nounwind readonly
declare i32 @strcasecmp(i8*, i8*) #3

declare i8* @config_getoption(i8*) #2

declare %struct._IO_FILE* @fopen64(i8*, i8*) #2

declare void @bftpd_log(i8*, ...) #2

; Function Attrs: nounwind uwtable
define void @bftpd_logwtmp(i8 signext %type) #0 !dbg !87 {
entry:
  %type.addr = alloca i8, align 1
  %ut = alloca %struct.utmp, align 4
  store i8 %type, i8* %type.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %type.addr, metadata !322, metadata !135), !dbg !323
  call void @llvm.dbg.declare(metadata %struct.utmp* %ut, metadata !324, metadata !135), !dbg !359
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @wtmp, align 8, !dbg !360
  %tobool = icmp ne %struct._IO_FILE* %0, null, !dbg !360
  br i1 %tobool, label %if.end, label %if.then, !dbg !362

if.then:                                          ; preds = %entry
  br label %return, !dbg !363

if.end:                                           ; preds = %entry
  %1 = bitcast %struct.utmp* %ut to i8*, !dbg !364
  call void @llvm.memset.p0i8.i64(i8* %1, i8 0, i64 384, i32 4, i1 false), !dbg !364
  %call = call i32 @getpid() #9, !dbg !365
  %ut_pid = getelementptr inbounds %struct.utmp, %struct.utmp* %ut, i32 0, i32 1, !dbg !366
  store i32 %call, i32* %ut_pid, align 4, !dbg !367
  %ut_line = getelementptr inbounds %struct.utmp, %struct.utmp* %ut, i32 0, i32 2, !dbg !368
  %arraydecay = getelementptr inbounds [32 x i8], [32 x i8]* %ut_line, i32 0, i32 0, !dbg !369
  %call1 = call i32 @getpid() #9, !dbg !370
  %call2 = call i32 (i8*, i8*, ...) @sprintf(i8* %arraydecay, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.7, i32 0, i32 0), i32 %call1) #9, !dbg !371
  %2 = load i8, i8* %type.addr, align 1, !dbg !373
  %tobool3 = icmp ne i8 %2, 0, !dbg !373
  br i1 %tobool3, label %if.then4, label %if.else, !dbg !375

if.then4:                                         ; preds = %if.end
  %ut_type = getelementptr inbounds %struct.utmp, %struct.utmp* %ut, i32 0, i32 0, !dbg !376
  store i16 7, i16* %ut_type, align 4, !dbg !378
  %ut_user = getelementptr inbounds %struct.utmp, %struct.utmp* %ut, i32 0, i32 4, !dbg !379
  %arraydecay5 = getelementptr inbounds [32 x i8], [32 x i8]* %ut_user, i32 0, i32 0, !dbg !380
  %call6 = call i8* @strncpy(i8* %arraydecay5, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0), i64 32) #9, !dbg !381
  %ut_host = getelementptr inbounds %struct.utmp, %struct.utmp* %ut, i32 0, i32 5, !dbg !382
  %arraydecay7 = getelementptr inbounds [256 x i8], [256 x i8]* %ut_host, i32 0, i32 0, !dbg !383
  %3 = load i8*, i8** @remotehostname, align 8, !dbg !384
  %call8 = call i8* @strncpy(i8* %arraydecay7, i8* %3, i64 256) #9, !dbg !385
  br label %if.end10, !dbg !386

if.else:                                          ; preds = %if.end
  %ut_type9 = getelementptr inbounds %struct.utmp, %struct.utmp* %ut, i32 0, i32 0, !dbg !387
  store i16 8, i16* %ut_type9, align 4, !dbg !389
  br label %if.end10

if.end10:                                         ; preds = %if.else, %if.then4
  %ut_tv = getelementptr inbounds %struct.utmp, %struct.utmp* %ut, i32 0, i32 8, !dbg !390
  %tv_sec = getelementptr inbounds %struct.anon, %struct.anon* %ut_tv, i32 0, i32 0, !dbg !390
  %4 = bitcast i32* %tv_sec to i64*, !dbg !391
  %call11 = call i64 @time(i64* %4) #9, !dbg !392
  %5 = load %struct._IO_FILE*, %struct._IO_FILE** @wtmp, align 8, !dbg !393
  %call12 = call i32 @fseek(%struct._IO_FILE* %5, i64 0, i32 2), !dbg !394
  %6 = bitcast %struct.utmp* %ut to i8*, !dbg !395
  %7 = load %struct._IO_FILE*, %struct._IO_FILE** @wtmp, align 8, !dbg !396
  %call13 = call i64 @fwrite(i8* %6, i64 384, i64 1, %struct._IO_FILE* %7), !dbg !397
  %8 = load %struct._IO_FILE*, %struct._IO_FILE** @wtmp, align 8, !dbg !398
  %call14 = call i32 @fflush(%struct._IO_FILE* %8), !dbg !399
  br label %return, !dbg !400

return:                                           ; preds = %if.end10, %if.then
  ret void, !dbg !401
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #5

; Function Attrs: nounwind
declare i32 @getpid() #4

; Function Attrs: nounwind
declare i64 @time(i64*) #4

declare i32 @fseek(%struct._IO_FILE*, i64, i32) #2

declare i64 @fwrite(i8*, i64, i64, %struct._IO_FILE*) #2

declare i32 @fflush(%struct._IO_FILE*) #2

; Function Attrs: nounwind uwtable
define void @wtmp_end() #0 !dbg !90 {
entry:
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @wtmp, align 8, !dbg !402
  %tobool = icmp ne %struct._IO_FILE* %0, null, !dbg !402
  br i1 %tobool, label %if.then, label %if.end2, !dbg !404

if.then:                                          ; preds = %entry
  %1 = load i32, i32* @state, align 4, !dbg !405
  %cmp = icmp sge i32 %1, 2, !dbg !408
  br i1 %cmp, label %if.then1, label %if.end, !dbg !409

if.then1:                                         ; preds = %if.then
  call void @bftpd_logwtmp(i8 signext 0), !dbg !410
  br label %if.end, !dbg !410

if.end:                                           ; preds = %if.then1, %if.then
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** @wtmp, align 8, !dbg !411
  %call = call i32 @fclose(%struct._IO_FILE* %2), !dbg !412
  br label %if.end2, !dbg !413

if.end2:                                          ; preds = %if.end, %entry
  ret void, !dbg !414
}

declare i32 @fclose(%struct._IO_FILE*) #2

; Function Attrs: nounwind uwtable
define void @login_init() #0 !dbg !91 {
entry:
  %foo = alloca i8*, align 8
  call void @llvm.dbg.declare(metadata i8** %foo, metadata !415, metadata !135), !dbg !416
  %call = call i8* @config_getoption(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.8, i32 0, i32 0)), !dbg !417
  store i8* %call, i8** %foo, align 8, !dbg !416
  call void @wtmp_init(), !dbg !418
  %0 = load i8*, i8** %foo, align 8, !dbg !419
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !419
  %1 = load i8, i8* %arrayidx, align 1, !dbg !419
  %tobool = icmp ne i8 %1, 0, !dbg !419
  br i1 %tobool, label %if.then, label %if.end3, !dbg !421

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** %foo, align 8, !dbg !422
  %call1 = call i32 @chroot(i8* %2) #9, !dbg !425
  %cmp = icmp eq i32 %call1, -1, !dbg !426
  br i1 %cmp, label %if.then2, label %if.end, !dbg !427

if.then2:                                         ; preds = %if.then
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.9, i32 0, i32 0)), !dbg !428
  call void @exit(i32 1) #10, !dbg !430
  unreachable, !dbg !430

if.end:                                           ; preds = %if.then
  br label %if.end3, !dbg !431

if.end3:                                          ; preds = %if.end, %entry
  ret void, !dbg !432
}

; Function Attrs: nounwind
declare i32 @chroot(i8*) #4

declare void @control_printf(i8 signext, i8*, ...) #2

; Function Attrs: noreturn nounwind
declare void @exit(i32) #6

; Function Attrs: nounwind uwtable
define i32 @bftpd_setuid(i32 %uid) #0 !dbg !92 {
entry:
  %retval = alloca i32, align 4
  %uid.addr = alloca i32, align 4
  store i32 %uid, i32* %uid.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %uid.addr, metadata !433, metadata !135), !dbg !434
  %call = call i8* @config_getoption(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.10, i32 0, i32 0)), !dbg !435
  %call1 = call i32 @strcasecmp(i8* %call, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.11, i32 0, i32 0)) #8, !dbg !437
  %tobool = icmp ne i32 %call1, 0, !dbg !439
  br i1 %tobool, label %if.else, label %if.then, !dbg !440

if.then:                                          ; preds = %entry
  %0 = load i32, i32* %uid.addr, align 4, !dbg !441
  %call2 = call i32 @seteuid(i32 %0) #9, !dbg !442
  store i32 %call2, i32* %retval, align 4, !dbg !443
  br label %return, !dbg !443

if.else:                                          ; preds = %entry
  %1 = load i32, i32* %uid.addr, align 4, !dbg !444
  %call3 = call i32 @setuid(i32 %1) #9, !dbg !445
  store i32 %call3, i32* %retval, align 4, !dbg !446
  br label %return, !dbg !446

return:                                           ; preds = %if.else, %if.then
  %2 = load i32, i32* %retval, align 4, !dbg !447
  ret i32 %2, !dbg !447
}

; Function Attrs: nounwind
declare i32 @seteuid(i32) #4

; Function Attrs: nounwind
declare i32 @setuid(i32) #4

; Function Attrs: nounwind uwtable
define i32 @bftpd_login(i8* %password) #0 !dbg !99 {
entry:
  %retval = alloca i32, align 4
  %password.addr = alloca i8*, align 8
  %str = alloca [513 x i8], align 16
  %foo = alloca i8*, align 8
  %maxusers = alloca i32, align 4
  %file_auth = alloca i8*, align 8
  %home_directory = alloca i8*, align 8
  %anonymous = alloca i8*, align 8
  %get_maxusers = alloca i64, align 8
  %anon_ok = alloca i32, align 4
  store i8* %password, i8** %password.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %password.addr, metadata !448, metadata !135), !dbg !449
  call void @llvm.dbg.declare(metadata [513 x i8]* %str, metadata !450, metadata !135), !dbg !454
  call void @llvm.dbg.declare(metadata i8** %foo, metadata !455, metadata !135), !dbg !456
  call void @llvm.dbg.declare(metadata i32* %maxusers, metadata !457, metadata !135), !dbg !458
  call void @llvm.dbg.declare(metadata i8** %file_auth, metadata !459, metadata !135), !dbg !460
  call void @llvm.dbg.declare(metadata i8** %home_directory, metadata !461, metadata !135), !dbg !462
  store i8* null, i8** %home_directory, align 8, !dbg !462
  call void @llvm.dbg.declare(metadata i8** %anonymous, metadata !463, metadata !135), !dbg !464
  store i8* null, i8** %anonymous, align 8, !dbg !464
  call void @llvm.dbg.declare(metadata i64* %get_maxusers, metadata !465, metadata !135), !dbg !466
  call void @llvm.dbg.declare(metadata i32* %anon_ok, metadata !467, metadata !135), !dbg !468
  store i32 0, i32* %anon_ok, align 4, !dbg !468
  %arrayidx = getelementptr inbounds [513 x i8], [513 x i8]* %str, i64 0, i64 0, !dbg !469
  store i8 0, i8* %arrayidx, align 16, !dbg !470
  %call = call i8* @config_getoption(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.12, i32 0, i32 0)), !dbg !471
  store i8* %call, i8** %file_auth, align 8, !dbg !472
  %0 = load i8*, i8** %file_auth, align 8, !dbg !473
  %arrayidx1 = getelementptr inbounds i8, i8* %0, i64 0, !dbg !473
  %1 = load i8, i8* %arrayidx1, align 1, !dbg !473
  %tobool = icmp ne i8 %1, 0, !dbg !473
  br i1 %tobool, label %if.else10, label %if.then, !dbg !475

if.then:                                          ; preds = %entry
  %call2 = call i8* @config_getoption(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.13, i32 0, i32 0)), !dbg !476
  store i8* %call2, i8** %anonymous, align 8, !dbg !478
  %2 = load i8*, i8** %anonymous, align 8, !dbg !479
  %call3 = call i32 @strcasecmp(i8* %2, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.11, i32 0, i32 0)) #8, !dbg !481
  %tobool4 = icmp ne i32 %call3, 0, !dbg !481
  br i1 %tobool4, label %if.else, label %if.then5, !dbg !482

if.then5:                                         ; preds = %if.then
  store i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.14, i32 0, i32 0), i8** %home_directory, align 8, !dbg !483
  store i32 1, i32* %anon_ok, align 4, !dbg !485
  br label %if.end9, !dbg !486

if.else:                                          ; preds = %if.then
  %call6 = call %struct.passwd* @getpwnam(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0)), !dbg !487
  %tobool7 = icmp ne %struct.passwd* %call6, null, !dbg !487
  br i1 %tobool7, label %if.end, label %if.then8, !dbg !489

if.then8:                                         ; preds = %if.else
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.15, i32 0, i32 0)), !dbg !490
  store i32 -1, i32* %retval, align 4, !dbg !492
  br label %return, !dbg !492

if.end:                                           ; preds = %if.else
  br label %if.end9

if.end9:                                          ; preds = %if.end, %if.then5
  br label %if.end21, !dbg !493

if.else10:                                        ; preds = %entry
  %3 = load i8*, i8** %file_auth, align 8, !dbg !494
  %4 = load i8*, i8** %password.addr, align 8, !dbg !496
  %call11 = call i8* @check_file_password(i8* %3, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0), i8* %4), !dbg !497
  store i8* %call11, i8** %home_directory, align 8, !dbg !498
  %call12 = call i8* @config_getoption(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.13, i32 0, i32 0)), !dbg !499
  store i8* %call12, i8** %anonymous, align 8, !dbg !500
  %5 = load i8*, i8** %home_directory, align 8, !dbg !501
  %tobool13 = icmp ne i8* %5, null, !dbg !501
  br i1 %tobool13, label %if.end20, label %if.then14, !dbg !503

if.then14:                                        ; preds = %if.else10
  %6 = load i8*, i8** %anonymous, align 8, !dbg !504
  %call15 = call i32 @strcasecmp(i8* %6, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.11, i32 0, i32 0)) #8, !dbg !507
  %tobool16 = icmp ne i32 %call15, 0, !dbg !507
  br i1 %tobool16, label %if.else18, label %if.then17, !dbg !508

if.then17:                                        ; preds = %if.then14
  store i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.14, i32 0, i32 0), i8** %home_directory, align 8, !dbg !509
  br label %if.end19, !dbg !510

if.else18:                                        ; preds = %if.then14
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.16, i32 0, i32 0)), !dbg !511
  store i32 -1, i32* %retval, align 4, !dbg !513
  br label %return, !dbg !513

if.end19:                                         ; preds = %if.then17
  br label %if.end20, !dbg !514

if.end20:                                         ; preds = %if.end19, %if.else10
  br label %if.end21

if.end21:                                         ; preds = %if.end20, %if.end9
  %call22 = call i8* @config_getoption(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.17, i32 0, i32 0)), !dbg !515
  store i8* %call22, i8** %foo, align 8, !dbg !517
  %call23 = call i32 @strncasecmp(i8* %call22, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.3, i32 0, i32 0), i64 2) #8, !dbg !518
  %tobool24 = icmp ne i32 %call23, 0, !dbg !520
  br i1 %tobool24, label %if.then25, label %if.end35, !dbg !521

if.then25:                                        ; preds = %if.end21
  %7 = load i8*, i8** %foo, align 8, !dbg !522
  %arrayidx26 = getelementptr inbounds i8, i8* %7, i64 0, !dbg !522
  %8 = load i8, i8* %arrayidx26, align 1, !dbg !522
  %conv = sext i8 %8 to i32, !dbg !522
  %cmp = icmp ne i32 %conv, 0, !dbg !525
  br i1 %cmp, label %if.then28, label %if.end34, !dbg !526

if.then28:                                        ; preds = %if.then25
  %9 = load i8*, i8** %foo, align 8, !dbg !527
  %call29 = call i32 @strncasecmp(i8* %9, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.11, i32 0, i32 0), i64 3) #8, !dbg !530
  %tobool30 = icmp ne i32 %call29, 0, !dbg !530
  br i1 %tobool30, label %if.then31, label %if.else32, !dbg !531

if.then31:                                        ; preds = %if.then28
  %10 = load i8*, i8** %foo, align 8, !dbg !532
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.18, i32 0, i32 0), i8* %10), !dbg !533
  br label %if.end33, !dbg !533

if.else32:                                        ; preds = %if.then28
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.15, i32 0, i32 0)), !dbg !534
  br label %if.end33

if.end33:                                         ; preds = %if.else32, %if.then31
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.19, i32 0, i32 0), i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0)), !dbg !535
  call void @exit(i32 0) #10, !dbg !536
  unreachable, !dbg !536

if.end34:                                         ; preds = %if.then25
  br label %if.end35, !dbg !537

if.end35:                                         ; preds = %if.end34, %if.end21
  %call36 = call i8* @config_getoption(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.20, i32 0, i32 0)), !dbg !538
  %call37 = call i64 @strtoul(i8* %call36, i8** null, i32 10) #9, !dbg !539
  store i64 %call37, i64* %get_maxusers, align 8, !dbg !541
  %11 = load i64, i64* %get_maxusers, align 8, !dbg !542
  %cmp38 = icmp ule i64 %11, 2147483647, !dbg !544
  br i1 %cmp38, label %if.then40, label %if.else42, !dbg !545

if.then40:                                        ; preds = %if.end35
  %12 = load i64, i64* %get_maxusers, align 8, !dbg !546
  %conv41 = trunc i64 %12 to i32, !dbg !546
  store i32 %conv41, i32* %maxusers, align 4, !dbg !547
  br label %if.end43, !dbg !548

if.else42:                                        ; preds = %if.end35
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([52 x i8], [52 x i8]* @.str.21, i32 0, i32 0), i32 0), !dbg !549
  store i32 0, i32* %maxusers, align 4, !dbg !551
  br label %if.end43

if.end43:                                         ; preds = %if.else42, %if.then40
  %13 = load i32, i32* %maxusers, align 4, !dbg !552
  %tobool44 = icmp ne i32 %13, 0, !dbg !554
  br i1 %tobool44, label %land.lhs.true, label %if.end49, !dbg !555

land.lhs.true:                                    ; preds = %if.end43
  %14 = load i32, i32* %maxusers, align 4, !dbg !556
  %call45 = call i32 @bftpdutmp_usercount(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.22, i32 0, i32 0)), !dbg !558
  %cmp46 = icmp eq i32 %14, %call45, !dbg !559
  br i1 %cmp46, label %if.then48, label %if.end49, !dbg !560

if.then48:                                        ; preds = %land.lhs.true
  %15 = load i32, i32* %maxusers, align 4, !dbg !561
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.23, i32 0, i32 0), i32 %15), !dbg !563
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([54 x i8], [54 x i8]* @.str.24, i32 0, i32 0), i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0)), !dbg !564
  call void @exit(i32 0) #10, !dbg !565
  unreachable, !dbg !565

if.end49:                                         ; preds = %land.lhs.true, %if.end43
  %call50 = call i8* @config_getoption(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.25, i32 0, i32 0)), !dbg !566
  %call51 = call i64 @strtoul(i8* %call50, i8** null, i32 10) #9, !dbg !567
  store i64 %call51, i64* %get_maxusers, align 8, !dbg !568
  %16 = load i64, i64* %get_maxusers, align 8, !dbg !569
  %cmp52 = icmp ule i64 %16, 2147483647, !dbg !571
  br i1 %cmp52, label %if.then54, label %if.else56, !dbg !572

if.then54:                                        ; preds = %if.end49
  %17 = load i64, i64* %get_maxusers, align 8, !dbg !573
  %conv55 = trunc i64 %17 to i32, !dbg !573
  store i32 %conv55, i32* %maxusers, align 4, !dbg !574
  br label %if.end57, !dbg !575

if.else56:                                        ; preds = %if.end49
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([55 x i8], [55 x i8]* @.str.26, i32 0, i32 0), i32 0), !dbg !576
  store i32 0, i32* %maxusers, align 4, !dbg !578
  br label %if.end57

if.end57:                                         ; preds = %if.else56, %if.then54
  %18 = load i32, i32* %maxusers, align 4, !dbg !579
  %tobool58 = icmp ne i32 %18, 0, !dbg !581
  br i1 %tobool58, label %land.lhs.true59, label %if.end64, !dbg !582

land.lhs.true59:                                  ; preds = %if.end57
  %19 = load i32, i32* %maxusers, align 4, !dbg !583
  %call60 = call i32 @bftpdutmp_usercount(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0)), !dbg !585
  %cmp61 = icmp eq i32 %19, %call60, !dbg !586
  br i1 %cmp61, label %if.then63, label %if.end64, !dbg !587

if.then63:                                        ; preds = %land.lhs.true59
  %20 = load i32, i32* %maxusers, align 4, !dbg !588
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.27, i32 0, i32 0), i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0), i32 %20), !dbg !590
  %21 = load i32, i32* %maxusers, align 4, !dbg !591
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([55 x i8], [55 x i8]* @.str.28, i32 0, i32 0), i32 %21), !dbg !592
  call void @exit(i32 0) #10, !dbg !593
  unreachable, !dbg !593

if.end64:                                         ; preds = %land.lhs.true59, %if.end57
  %call65 = call i8* @config_getoption(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.29, i32 0, i32 0)), !dbg !594
  %call66 = call i64 @strtoul(i8* %call65, i8** null, i32 10) #9, !dbg !595
  store i64 %call66, i64* %get_maxusers, align 8, !dbg !596
  %22 = load i64, i64* %get_maxusers, align 8, !dbg !597
  %cmp67 = icmp ule i64 %22, 2147483647, !dbg !599
  br i1 %cmp67, label %if.then69, label %if.else71, !dbg !600

if.then69:                                        ; preds = %if.end64
  %23 = load i64, i64* %get_maxusers, align 8, !dbg !601
  %conv70 = trunc i64 %23 to i32, !dbg !601
  store i32 %conv70, i32* %maxusers, align 4, !dbg !602
  br label %if.end72, !dbg !603

if.else71:                                        ; preds = %if.end64
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.30, i32 0, i32 0), i32 0), !dbg !604
  store i32 0, i32* %maxusers, align 4, !dbg !606
  br label %if.end72

if.end72:                                         ; preds = %if.else71, %if.then69
  %24 = load i32, i32* %maxusers, align 4, !dbg !607
  %tobool73 = icmp ne i32 %24, 0, !dbg !609
  br i1 %tobool73, label %land.lhs.true74, label %if.end79, !dbg !610

land.lhs.true74:                                  ; preds = %if.end72
  %25 = load i32, i32* %maxusers, align 4, !dbg !611
  %26 = load i8*, i8** @remotehostname, align 8, !dbg !613
  %call75 = call i32 @bftpdutmp_dup_ip_count(i8* %26), !dbg !614
  %cmp76 = icmp eq i32 %25, %call75, !dbg !615
  br i1 %cmp76, label %if.then78, label %if.end79, !dbg !616

if.then78:                                        ; preds = %land.lhs.true74
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.31, i32 0, i32 0)), !dbg !617
  %27 = load i32, i32* %maxusers, align 4, !dbg !619
  %28 = load i8*, i8** @remotehostname, align 8, !dbg !620
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([60 x i8], [60 x i8]* @.str.32, i32 0, i32 0), i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0), i32 %27, i8* %28), !dbg !621
  call void @exit(i32 0) #10, !dbg !622
  unreachable, !dbg !622

if.end79:                                         ; preds = %land.lhs.true74, %if.end72
  %29 = load i8*, i8** %file_auth, align 8, !dbg !623
  %arrayidx80 = getelementptr inbounds i8, i8* %29, i64 0, !dbg !623
  %30 = load i8, i8* %arrayidx80, align 1, !dbg !623
  %tobool81 = icmp ne i8 %30, 0, !dbg !623
  br i1 %tobool81, label %if.end91, label %land.lhs.true82, !dbg !625

land.lhs.true82:                                  ; preds = %if.end79
  %31 = load i32, i32* %anon_ok, align 4, !dbg !626
  %tobool83 = icmp ne i32 %31, 0, !dbg !626
  br i1 %tobool83, label %if.end91, label %if.then84, !dbg !628

if.then84:                                        ; preds = %land.lhs.true82
  %call85 = call i32 @checkuser(), !dbg !629
  %tobool86 = icmp ne i32 %call85, 0, !dbg !629
  br i1 %tobool86, label %if.then89, label %lor.lhs.false, !dbg !632

lor.lhs.false:                                    ; preds = %if.then84
  %call87 = call i32 @checkshell(), !dbg !633
  %tobool88 = icmp ne i32 %call87, 0, !dbg !633
  br i1 %tobool88, label %if.then89, label %if.end90, !dbg !635

if.then89:                                        ; preds = %lor.lhs.false, %if.then84
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.15, i32 0, i32 0)), !dbg !636
  store i32 -1, i32* %retval, align 4, !dbg !638
  br label %return, !dbg !638

if.end90:                                         ; preds = %lor.lhs.false
  br label %if.end91, !dbg !639

if.end91:                                         ; preds = %if.end90, %land.lhs.true82, %if.end79
  %32 = load i8*, i8** %file_auth, align 8, !dbg !640
  %arrayidx92 = getelementptr inbounds i8, i8* %32, i64 0, !dbg !640
  %33 = load i8, i8* %arrayidx92, align 1, !dbg !640
  %tobool93 = icmp ne i8 %33, 0, !dbg !640
  br i1 %tobool93, label %if.end101, label %land.lhs.true94, !dbg !642

land.lhs.true94:                                  ; preds = %if.end91
  %34 = load i32, i32* %anon_ok, align 4, !dbg !643
  %tobool95 = icmp ne i32 %34, 0, !dbg !643
  br i1 %tobool95, label %if.end101, label %if.then96, !dbg !645

if.then96:                                        ; preds = %land.lhs.true94
  %35 = load i8*, i8** %password.addr, align 8, !dbg !646
  %call97 = call i32 @checkpass(i8* %35), !dbg !649
  %tobool98 = icmp ne i32 %call97, 0, !dbg !649
  br i1 %tobool98, label %if.then99, label %if.end100, !dbg !650

if.then99:                                        ; preds = %if.then96
  store i32 1, i32* %retval, align 4, !dbg !651
  br label %return, !dbg !651

if.end100:                                        ; preds = %if.then96
  br label %if.end101, !dbg !652

if.end101:                                        ; preds = %if.end100, %land.lhs.true94, %if.end91
  %call102 = call i8* @config_getoption(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.33, i32 0, i32 0)), !dbg !653
  %call103 = call i32 @strcasecmp(i8* %call102, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.34, i32 0, i32 0)) #8, !dbg !655
  %tobool104 = icmp ne i32 %call103, 0, !dbg !657
  br i1 %tobool104, label %if.then105, label %if.end108, !dbg !658

if.then105:                                       ; preds = %if.end101
  %call106 = call i8* @config_getoption(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.33, i32 0, i32 0)), !dbg !659
  %call107 = call i32 (i8*, i8*, ...) @__isoc99_sscanf(i8* %call106, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.35, i32 0, i32 0), i32* @ratio_send, i32* @ratio_recv) #9, !dbg !661
  br label %if.end108, !dbg !663

if.end108:                                        ; preds = %if.then105, %if.end101
  %36 = load i8*, i8** %file_auth, align 8, !dbg !664
  %arrayidx109 = getelementptr inbounds i8, i8* %36, i64 0, !dbg !664
  %37 = load i8, i8* %arrayidx109, align 1, !dbg !664
  %tobool110 = icmp ne i8 %37, 0, !dbg !664
  br i1 %tobool110, label %if.else171, label %land.lhs.true111, !dbg !666

land.lhs.true111:                                 ; preds = %if.end108
  %38 = load i32, i32* %anon_ok, align 4, !dbg !667
  %tobool112 = icmp ne i32 %38, 0, !dbg !667
  br i1 %tobool112, label %if.else171, label %if.then113, !dbg !669

if.then113:                                       ; preds = %land.lhs.true111
  %arraydecay = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !670
  %call114 = call i8* @config_getoption(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.36, i32 0, i32 0)), !dbg !672
  %call115 = call i8* @strcpy(i8* %arraydecay, i8* %call114) #9, !dbg !673
  %arrayidx116 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i64 0, i64 0, !dbg !675
  %39 = load i8, i8* %arrayidx116, align 16, !dbg !675
  %tobool117 = icmp ne i8 %39, 0, !dbg !675
  br i1 %tobool117, label %if.end121, label %if.then118, !dbg !677

if.then118:                                       ; preds = %if.then113
  %arraydecay119 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !678
  %call120 = call i8* @strcpy(i8* %arraydecay119, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.37, i32 0, i32 0)) #9, !dbg !679
  br label %if.end121, !dbg !679

if.end121:                                        ; preds = %if.then118, %if.then113
  %arraydecay122 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !680
  %40 = load i8*, i8** getelementptr inbounds (%struct.passwd, %struct.passwd* @userinfo, i32 0, i32 0), align 8, !dbg !681
  %call123 = call i32 @replace(i8* %arraydecay122, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.38, i32 0, i32 0), i8* %40, i32 512), !dbg !682
  %arraydecay124 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !683
  %41 = load i8*, i8** getelementptr inbounds (%struct.passwd, %struct.passwd* @userinfo, i32 0, i32 5), align 8, !dbg !684
  %call125 = call i32 @replace(i8* %arraydecay124, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.37, i32 0, i32 0), i8* %41, i32 512), !dbg !685
  %call126 = call i8* @config_getoption(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.39, i32 0, i32 0)), !dbg !686
  %call127 = call i32 @strcasecmp(i8* %call126, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.11, i32 0, i32 0)) #8, !dbg !688
  %tobool128 = icmp ne i32 %call127, 0, !dbg !690
  br i1 %tobool128, label %if.end132, label %if.then129, !dbg !691

if.then129:                                       ; preds = %if.end121
  %call130 = call %struct._IO_FILE* @fopen64(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.40, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.41, i32 0, i32 0)), !dbg !692
  store %struct._IO_FILE* %call130, %struct._IO_FILE** @passwdfile, align 8, !dbg !694
  %call131 = call %struct._IO_FILE* @fopen64(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.42, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.41, i32 0, i32 0)), !dbg !695
  store %struct._IO_FILE* %call131, %struct._IO_FILE** @groupfile, align 8, !dbg !696
  br label %if.end132, !dbg !697

if.end132:                                        ; preds = %if.then129, %if.end121
  %42 = load i32, i32* getelementptr inbounds (%struct.passwd, %struct.passwd* @userinfo, i32 0, i32 3), align 4, !dbg !698
  %call133 = call i32 @setgid(i32 %42) #9, !dbg !699
  %43 = load i8*, i8** getelementptr inbounds (%struct.passwd, %struct.passwd* @userinfo, i32 0, i32 0), align 8, !dbg !700
  %44 = load i32, i32* getelementptr inbounds (%struct.passwd, %struct.passwd* @userinfo, i32 0, i32 3), align 4, !dbg !701
  %call134 = call i32 @initgroups(i8* %43, i32 %44), !dbg !702
  %call135 = call i8* @config_getoption(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.43, i32 0, i32 0)), !dbg !703
  %call136 = call i32 @strcasecmp(i8* %call135, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.3, i32 0, i32 0)) #8, !dbg !705
  %tobool137 = icmp ne i32 %call136, 0, !dbg !707
  br i1 %tobool137, label %if.then138, label %if.else156, !dbg !708

if.then138:                                       ; preds = %if.end132
  %arraydecay139 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !709
  %call140 = call i32 @chroot(i8* %arraydecay139) #9, !dbg !712
  %tobool141 = icmp ne i32 %call140, 0, !dbg !712
  br i1 %tobool141, label %if.then142, label %if.end145, !dbg !713

if.then142:                                       ; preds = %if.then138
  %call143 = call i32* @__errno_location() #1, !dbg !714
  %45 = load i32, i32* %call143, align 4, !dbg !714
  %call144 = call i8* @strerror(i32 %45) #9, !dbg !716
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.44, i32 0, i32 0), i8* %call144), !dbg !718
  call void @exit(i32 0) #10, !dbg !719
  unreachable, !dbg !719

if.end145:                                        ; preds = %if.then138
  %46 = load i32, i32* getelementptr inbounds (%struct.passwd, %struct.passwd* @userinfo, i32 0, i32 2), align 8, !dbg !720
  %call146 = call i32 @bftpd_setuid(i32 %46), !dbg !722
  %tobool147 = icmp ne i32 %call146, 0, !dbg !722
  br i1 %tobool147, label %if.then148, label %if.end149, !dbg !723

if.then148:                                       ; preds = %if.end145
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.45, i32 0, i32 0)), !dbg !724
  call void @exit(i32 0) #10, !dbg !726
  unreachable, !dbg !726

if.end149:                                        ; preds = %if.end145
  %call150 = call i32 @chdir(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.14, i32 0, i32 0)) #9, !dbg !727
  %tobool151 = icmp ne i32 %call150, 0, !dbg !727
  br i1 %tobool151, label %if.then152, label %if.end155, !dbg !729

if.then152:                                       ; preds = %if.end149
  %call153 = call i32* @__errno_location() #1, !dbg !730
  %47 = load i32, i32* %call153, align 4, !dbg !730
  %call154 = call i8* @strerror(i32 %47) #9, !dbg !732
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.46, i32 0, i32 0), i8* %call154), !dbg !734
  call void @exit(i32 0) #10, !dbg !735
  unreachable, !dbg !735

if.end155:                                        ; preds = %if.end149
  br label %if.end170, !dbg !736

if.else156:                                       ; preds = %if.end132
  %48 = load i32, i32* getelementptr inbounds (%struct.passwd, %struct.passwd* @userinfo, i32 0, i32 2), align 8, !dbg !737
  %call157 = call i32 @bftpd_setuid(i32 %48), !dbg !740
  %tobool158 = icmp ne i32 %call157, 0, !dbg !740
  br i1 %tobool158, label %if.then159, label %if.end160, !dbg !741

if.then159:                                       ; preds = %if.else156
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.45, i32 0, i32 0)), !dbg !742
  call void @exit(i32 0) #10, !dbg !744
  unreachable, !dbg !744

if.end160:                                        ; preds = %if.else156
  %arraydecay161 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !745
  %call162 = call i32 @chdir(i8* %arraydecay161) #9, !dbg !747
  %tobool163 = icmp ne i32 %call162, 0, !dbg !747
  br i1 %tobool163, label %if.then164, label %if.end169, !dbg !748

if.then164:                                       ; preds = %if.end160
  %arraydecay165 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !749
  %call166 = call i32* @__errno_location() #1, !dbg !751
  %49 = load i32, i32* %call166, align 4, !dbg !751
  %call167 = call i8* @strerror(i32 %49) #9, !dbg !752
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.47, i32 0, i32 0), i8* %arraydecay165, i8* %call167), !dbg !754
  %call168 = call i32 @chdir(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.14, i32 0, i32 0)) #9, !dbg !755
  br label %if.end169, !dbg !756

if.end169:                                        ; preds = %if.then164, %if.end160
  br label %if.end170

if.end170:                                        ; preds = %if.end169, %if.end155
  br label %if.end231, !dbg !757

if.else171:                                       ; preds = %land.lhs.true111, %if.end108
  %50 = load i8*, i8** %file_auth, align 8, !dbg !758
  %arrayidx172 = getelementptr inbounds i8, i8* %50, i64 0, !dbg !758
  %51 = load i8, i8* %arrayidx172, align 1, !dbg !758
  %tobool173 = icmp ne i8 %51, 0, !dbg !758
  br i1 %tobool173, label %if.else203, label %land.lhs.true174, !dbg !760

land.lhs.true174:                                 ; preds = %if.else171
  %52 = load i32, i32* %anon_ok, align 4, !dbg !761
  %tobool175 = icmp ne i32 %52, 0, !dbg !763
  br i1 %tobool175, label %if.then176, label %if.else203, !dbg !764

if.then176:                                       ; preds = %land.lhs.true174
  %arraydecay177 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !765
  %call178 = call i8* @config_getoption(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.36, i32 0, i32 0)), !dbg !767
  %call179 = call i8* @strcpy(i8* %arraydecay177, i8* %call178) #9, !dbg !768
  %arrayidx180 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i64 0, i64 0, !dbg !770
  %53 = load i8, i8* %arrayidx180, align 16, !dbg !770
  %tobool181 = icmp ne i8 %53, 0, !dbg !770
  br i1 %tobool181, label %if.end184, label %if.then182, !dbg !772

if.then182:                                       ; preds = %if.then176
  %arrayidx183 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i64 0, i64 0, !dbg !773
  store i8 47, i8* %arrayidx183, align 16, !dbg !774
  br label %if.end184, !dbg !773

if.end184:                                        ; preds = %if.then182, %if.then176
  %arraydecay185 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !775
  %54 = load i8*, i8** %home_directory, align 8, !dbg !776
  %call186 = call i32 @replace(i8* %arraydecay185, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.37, i32 0, i32 0), i8* %54, i32 512), !dbg !777
  %arraydecay187 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !778
  %call188 = call i32 @replace(i8* %arraydecay187, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.38, i32 0, i32 0), i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0), i32 512), !dbg !779
  %call189 = call i8* @config_getoption(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.43, i32 0, i32 0)), !dbg !780
  %call190 = call i32 @strcasecmp(i8* %call189, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.11, i32 0, i32 0)) #8, !dbg !782
  %tobool191 = icmp ne i32 %call190, 0, !dbg !784
  br i1 %tobool191, label %if.end202, label %if.then192, !dbg !785

if.then192:                                       ; preds = %if.end184
  %arraydecay193 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !786
  %call194 = call i32 @chroot(i8* %arraydecay193) #9, !dbg !789
  %tobool195 = icmp ne i32 %call194, 0, !dbg !789
  br i1 %tobool195, label %if.then196, label %if.end197, !dbg !790

if.then196:                                       ; preds = %if.then192
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.48, i32 0, i32 0)), !dbg !791
  call void @exit(i32 0) #10, !dbg !793
  unreachable, !dbg !793

if.end197:                                        ; preds = %if.then192
  %call198 = call i32 @chdir(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.14, i32 0, i32 0)) #9, !dbg !794
  %tobool199 = icmp ne i32 %call198, 0, !dbg !794
  br i1 %tobool199, label %if.then200, label %if.end201, !dbg !796

if.then200:                                       ; preds = %if.end197
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.49, i32 0, i32 0)), !dbg !797
  call void @exit(i32 0) #10, !dbg !799
  unreachable, !dbg !799

if.end201:                                        ; preds = %if.end197
  br label %if.end202, !dbg !800

if.end202:                                        ; preds = %if.end201, %if.end184
  br label %if.end230, !dbg !801

if.else203:                                       ; preds = %land.lhs.true174, %if.else171
  %arraydecay204 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !802
  %call205 = call i8* @config_getoption(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.36, i32 0, i32 0)), !dbg !804
  %call206 = call i8* @strcpy(i8* %arraydecay204, i8* %call205) #9, !dbg !805
  %arrayidx207 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i64 0, i64 0, !dbg !807
  %55 = load i8, i8* %arrayidx207, align 16, !dbg !807
  %tobool208 = icmp ne i8 %55, 0, !dbg !807
  br i1 %tobool208, label %if.end212, label %if.then209, !dbg !809

if.then209:                                       ; preds = %if.else203
  %arraydecay210 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !810
  %call211 = call i8* @strcpy(i8* %arraydecay210, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.37, i32 0, i32 0)) #9, !dbg !811
  br label %if.end212, !dbg !811

if.end212:                                        ; preds = %if.then209, %if.else203
  %arraydecay213 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !812
  %56 = load i8*, i8** %home_directory, align 8, !dbg !813
  %call214 = call i32 @replace(i8* %arraydecay213, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.37, i32 0, i32 0), i8* %56, i32 512), !dbg !814
  %arraydecay215 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !815
  %call216 = call i32 @replace(i8* %arraydecay215, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.38, i32 0, i32 0), i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0), i32 512), !dbg !816
  %call217 = call i8* @config_getoption(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.43, i32 0, i32 0)), !dbg !817
  %call218 = call i32 @strcasecmp(i8* %call217, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.11, i32 0, i32 0)) #8, !dbg !819
  %tobool219 = icmp ne i32 %call218, 0, !dbg !821
  br i1 %tobool219, label %if.end229, label %if.then220, !dbg !822

if.then220:                                       ; preds = %if.end212
  %57 = load i8*, i8** %home_directory, align 8, !dbg !823
  %call221 = call i32 @chroot(i8* %57) #9, !dbg !826
  %tobool222 = icmp ne i32 %call221, 0, !dbg !826
  br i1 %tobool222, label %if.then223, label %if.end224, !dbg !827

if.then223:                                       ; preds = %if.then220
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.48, i32 0, i32 0)), !dbg !828
  call void @exit(i32 0) #10, !dbg !830
  unreachable, !dbg !830

if.end224:                                        ; preds = %if.then220
  %call225 = call i32 @chdir(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.14, i32 0, i32 0)) #9, !dbg !831
  %tobool226 = icmp ne i32 %call225, 0, !dbg !831
  br i1 %tobool226, label %if.then227, label %if.end228, !dbg !833

if.then227:                                       ; preds = %if.end224
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.49, i32 0, i32 0)), !dbg !834
  call void @exit(i32 0) #10, !dbg !836
  unreachable, !dbg !836

if.end228:                                        ; preds = %if.end224
  br label %if.end229, !dbg !837

if.end229:                                        ; preds = %if.end228, %if.end212
  br label %if.end230

if.end230:                                        ; preds = %if.end229, %if.end202
  br label %if.end231

if.end231:                                        ; preds = %if.end230, %if.end170
  call void (...) @new_umask(), !dbg !838
  %arraydecay232 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !839
  %call233 = call i8* @config_getoption(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.50, i32 0, i32 0)), !dbg !840
  %call234 = call i8* @strcpy(i8* %arraydecay232, i8* %call233) #9, !dbg !841
  %arraydecay235 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !842
  %58 = load i8*, i8** %home_directory, align 8, !dbg !843
  %call236 = call i32 @replace(i8* %arraydecay235, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.37, i32 0, i32 0), i8* %58, i32 512), !dbg !844
  %arraydecay237 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !845
  %call238 = call i32 @replace(i8* %arraydecay237, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.38, i32 0, i32 0), i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0), i32 512), !dbg !846
  %arraydecay239 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !847
  call void @print_file(i32 230, i8* %arraydecay239), !dbg !848
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.51, i32 0, i32 0)), !dbg !849
  call void @bftpd_logwtmp(i8 signext 1), !dbg !850
  call void @bftpdutmp_log(i8 signext 1), !dbg !851
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.52, i32 0, i32 0), i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0)), !dbg !852
  %call240 = call i8* @config_getoption(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.53, i32 0, i32 0)), !dbg !853
  %arrayidx241 = getelementptr inbounds i8, i8* %call240, i64 0, !dbg !853
  %59 = load i8, i8* %arrayidx241, align 1, !dbg !853
  %tobool242 = icmp ne i8 %59, 0, !dbg !853
  br i1 %tobool242, label %if.then243, label %if.end246, !dbg !855

if.then243:                                       ; preds = %if.end231
  %call244 = call i8* @config_getoption(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.53, i32 0, i32 0)), !dbg !856
  %call245 = call i32 @chdir(i8* %call244) #9, !dbg !857
  br label %if.end246, !dbg !859

if.end246:                                        ; preds = %if.then243, %if.end231
  store i32 2, i32* @state, align 4, !dbg !860
  call void (...) @bftpd_cwd_init(), !dbg !861
  %60 = load i8*, i8** %home_directory, align 8, !dbg !862
  %tobool247 = icmp ne i8* %60, null, !dbg !864
  br i1 %tobool247, label %land.lhs.true248, label %if.end252, !dbg !865

land.lhs.true248:                                 ; preds = %if.end246
  %61 = load i8*, i8** %home_directory, align 8, !dbg !866
  %call249 = call i32 @strcmp(i8* %61, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.14, i32 0, i32 0)) #8, !dbg !868
  %tobool250 = icmp ne i32 %call249, 0, !dbg !868
  br i1 %tobool250, label %if.then251, label %if.end252, !dbg !869

if.then251:                                       ; preds = %land.lhs.true248
  %62 = load i8*, i8** %home_directory, align 8, !dbg !870
  call void @free(i8* %62) #9, !dbg !871
  br label %if.end252, !dbg !871

if.end252:                                        ; preds = %if.then251, %land.lhs.true248, %if.end246
  store i32 0, i32* %retval, align 4, !dbg !872
  br label %return, !dbg !872

return:                                           ; preds = %if.end252, %if.then99, %if.then89, %if.else18, %if.then8
  %63 = load i32, i32* %retval, align 4, !dbg !873
  ret i32 %63, !dbg !873
}

declare %struct.passwd* @getpwnam(i8*) #2

; Function Attrs: nounwind uwtable
define i8* @check_file_password(i8* %my_filename, i8* %my_username, i8* %my_password) #0 !dbg !109 {
entry:
  %retval = alloca i8*, align 8
  %my_filename.addr = alloca i8*, align 8
  %my_username.addr = alloca i8*, align 8
  %my_password.addr = alloca i8*, align 8
  %my_file = alloca %struct._IO_FILE*, align 8
  %found_user = alloca i32, align 4
  %user = alloca [33 x i8], align 16
  %password = alloca [33 x i8], align 16
  %group = alloca [33 x i8], align 16
  %home_dir = alloca [33 x i8], align 16
  %my_home_dir = alloca i8*, align 8
  %return_value = alloca i32, align 4
  store i8* %my_filename, i8** %my_filename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %my_filename.addr, metadata !874, metadata !135), !dbg !875
  store i8* %my_username, i8** %my_username.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %my_username.addr, metadata !876, metadata !135), !dbg !877
  store i8* %my_password, i8** %my_password.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %my_password.addr, metadata !878, metadata !135), !dbg !879
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %my_file, metadata !880, metadata !135), !dbg !881
  call void @llvm.dbg.declare(metadata i32* %found_user, metadata !882, metadata !135), !dbg !883
  store i32 0, i32* %found_user, align 4, !dbg !883
  call void @llvm.dbg.declare(metadata [33 x i8]* %user, metadata !884, metadata !135), !dbg !888
  call void @llvm.dbg.declare(metadata [33 x i8]* %password, metadata !889, metadata !135), !dbg !890
  call void @llvm.dbg.declare(metadata [33 x i8]* %group, metadata !891, metadata !135), !dbg !892
  call void @llvm.dbg.declare(metadata [33 x i8]* %home_dir, metadata !893, metadata !135), !dbg !894
  call void @llvm.dbg.declare(metadata i8** %my_home_dir, metadata !895, metadata !135), !dbg !896
  store i8* null, i8** %my_home_dir, align 8, !dbg !896
  call void @llvm.dbg.declare(metadata i32* %return_value, metadata !897, metadata !135), !dbg !898
  %0 = load i8*, i8** %my_filename.addr, align 8, !dbg !899
  %call = call %struct._IO_FILE* @fopen64(i8* %0, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.41, i32 0, i32 0)), !dbg !900
  store %struct._IO_FILE* %call, %struct._IO_FILE** %my_file, align 8, !dbg !901
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** %my_file, align 8, !dbg !902
  %tobool = icmp ne %struct._IO_FILE* %1, null, !dbg !902
  br i1 %tobool, label %if.end, label %if.then, !dbg !904

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !905
  br label %return, !dbg !905

if.end:                                           ; preds = %entry
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** %my_file, align 8, !dbg !906
  %arraydecay = getelementptr inbounds [33 x i8], [33 x i8]* %user, i32 0, i32 0, !dbg !907
  %arraydecay1 = getelementptr inbounds [33 x i8], [33 x i8]* %password, i32 0, i32 0, !dbg !908
  %arraydecay2 = getelementptr inbounds [33 x i8], [33 x i8]* %group, i32 0, i32 0, !dbg !909
  %arraydecay3 = getelementptr inbounds [33 x i8], [33 x i8]* %home_dir, i32 0, i32 0, !dbg !910
  %call4 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %2, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.56, i32 0, i32 0), i8* %arraydecay, i8* %arraydecay1, i8* %arraydecay2, i8* %arraydecay3), !dbg !911
  store i32 %call4, i32* %return_value, align 4, !dbg !912
  %arraydecay5 = getelementptr inbounds [33 x i8], [33 x i8]* %user, i32 0, i32 0, !dbg !913
  %3 = load i8*, i8** %my_username.addr, align 8, !dbg !915
  %call6 = call i32 @strcmp(i8* %arraydecay5, i8* %3) #8, !dbg !916
  %tobool7 = icmp ne i32 %call6, 0, !dbg !916
  br i1 %tobool7, label %if.end9, label %if.then8, !dbg !917

if.then8:                                         ; preds = %if.end
  store i32 1, i32* %found_user, align 4, !dbg !918
  br label %if.end9, !dbg !919

if.end9:                                          ; preds = %if.then8, %if.end
  br label %while.cond, !dbg !920

while.cond:                                       ; preds = %if.end20, %if.end9
  %4 = load i32, i32* %found_user, align 4, !dbg !921
  %tobool10 = icmp ne i32 %4, 0, !dbg !921
  br i1 %tobool10, label %land.end, label %land.rhs, !dbg !923

land.rhs:                                         ; preds = %while.cond
  %5 = load i32, i32* %return_value, align 4, !dbg !924
  %cmp = icmp ne i32 %5, -1, !dbg !926
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %6 = phi i1 [ false, %while.cond ], [ %cmp, %land.rhs ]
  br i1 %6, label %while.body, label %while.end, !dbg !927

while.body:                                       ; preds = %land.end
  %7 = load %struct._IO_FILE*, %struct._IO_FILE** %my_file, align 8, !dbg !929
  %arraydecay11 = getelementptr inbounds [33 x i8], [33 x i8]* %user, i32 0, i32 0, !dbg !931
  %arraydecay12 = getelementptr inbounds [33 x i8], [33 x i8]* %password, i32 0, i32 0, !dbg !932
  %arraydecay13 = getelementptr inbounds [33 x i8], [33 x i8]* %group, i32 0, i32 0, !dbg !933
  %arraydecay14 = getelementptr inbounds [33 x i8], [33 x i8]* %home_dir, i32 0, i32 0, !dbg !934
  %call15 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %7, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.56, i32 0, i32 0), i8* %arraydecay11, i8* %arraydecay12, i8* %arraydecay13, i8* %arraydecay14), !dbg !935
  store i32 %call15, i32* %return_value, align 4, !dbg !936
  %arraydecay16 = getelementptr inbounds [33 x i8], [33 x i8]* %user, i32 0, i32 0, !dbg !937
  %8 = load i8*, i8** %my_username.addr, align 8, !dbg !939
  %call17 = call i32 @strcmp(i8* %arraydecay16, i8* %8) #8, !dbg !940
  %tobool18 = icmp ne i32 %call17, 0, !dbg !940
  br i1 %tobool18, label %if.end20, label %if.then19, !dbg !941

if.then19:                                        ; preds = %while.body
  store i32 1, i32* %found_user, align 4, !dbg !942
  br label %if.end20, !dbg !943

if.end20:                                         ; preds = %if.then19, %while.body
  br label %while.cond, !dbg !944

while.end:                                        ; preds = %land.end
  %9 = load %struct._IO_FILE*, %struct._IO_FILE** %my_file, align 8, !dbg !946
  %call21 = call i32 @fclose(%struct._IO_FILE* %9), !dbg !947
  %10 = load i32, i32* %found_user, align 4, !dbg !948
  %tobool22 = icmp ne i32 %10, 0, !dbg !948
  br i1 %tobool22, label %if.then23, label %if.end42, !dbg !950

if.then23:                                        ; preds = %while.end
  %arraydecay24 = getelementptr inbounds [33 x i8], [33 x i8]* %password, i32 0, i32 0, !dbg !951
  %call25 = call i32 @strcmp(i8* %arraydecay24, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.22, i32 0, i32 0)) #8, !dbg !954
  %tobool26 = icmp ne i32 %call25, 0, !dbg !954
  br i1 %tobool26, label %if.else, label %if.then27, !dbg !955

if.then27:                                        ; preds = %if.then23
  br label %if.end33, !dbg !956

if.else:                                          ; preds = %if.then23
  %arraydecay28 = getelementptr inbounds [33 x i8], [33 x i8]* %password, i32 0, i32 0, !dbg !958
  %11 = load i8*, i8** %my_password.addr, align 8, !dbg !960
  %call29 = call i32 @strcmp(i8* %arraydecay28, i8* %11) #8, !dbg !961
  %tobool30 = icmp ne i32 %call29, 0, !dbg !961
  br i1 %tobool30, label %if.then31, label %if.end32, !dbg !962

if.then31:                                        ; preds = %if.else
  store i8* null, i8** %retval, align 8, !dbg !963
  br label %return, !dbg !963

if.end32:                                         ; preds = %if.else
  br label %if.end33

if.end33:                                         ; preds = %if.end32, %if.then27
  %arraydecay34 = getelementptr inbounds [33 x i8], [33 x i8]* %home_dir, i32 0, i32 0, !dbg !964
  %call35 = call i64 @strlen(i8* %arraydecay34) #8, !dbg !965
  %add = add i64 %call35, 1, !dbg !966
  %call36 = call noalias i8* @calloc(i64 %add, i64 1) #9, !dbg !967
  store i8* %call36, i8** %my_home_dir, align 8, !dbg !969
  %12 = load i8*, i8** %my_home_dir, align 8, !dbg !970
  %tobool37 = icmp ne i8* %12, null, !dbg !970
  br i1 %tobool37, label %if.end39, label %if.then38, !dbg !972

if.then38:                                        ; preds = %if.end33
  store i8* null, i8** %retval, align 8, !dbg !973
  br label %return, !dbg !973

if.end39:                                         ; preds = %if.end33
  %13 = load i8*, i8** %my_home_dir, align 8, !dbg !974
  %arraydecay40 = getelementptr inbounds [33 x i8], [33 x i8]* %home_dir, i32 0, i32 0, !dbg !975
  %call41 = call i8* @strcpy(i8* %13, i8* %arraydecay40) #9, !dbg !976
  br label %if.end42, !dbg !977

if.end42:                                         ; preds = %if.end39, %while.end
  %14 = load i8*, i8** %my_home_dir, align 8, !dbg !978
  store i8* %14, i8** %retval, align 8, !dbg !979
  br label %return, !dbg !979

return:                                           ; preds = %if.end42, %if.then38, %if.then31, %if.then
  %15 = load i8*, i8** %retval, align 8, !dbg !980
  ret i8* %15, !dbg !980
}

; Function Attrs: nounwind readonly
declare i32 @strncasecmp(i8*, i8*, i64) #3

; Function Attrs: nounwind
declare i64 @strtoul(i8*, i8**, i32) #4

declare i32 @bftpdutmp_usercount(i8*) #2

declare i32 @bftpdutmp_dup_ip_count(i8*) #2

; Function Attrs: nounwind uwtable
define i32 @checkpass(i8* %password) #0 !dbg !102 {
entry:
  %retval = alloca i32, align 4
  %password.addr = alloca i8*, align 8
  store i8* %password, i8** %password.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %password.addr, metadata !981, metadata !135), !dbg !982
  %call = call %struct.passwd* @getpwnam(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0)), !dbg !983
  %tobool = icmp ne %struct.passwd* %call, null, !dbg !983
  br i1 %tobool, label %if.end, label %if.then, !dbg !985

if.then:                                          ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !986
  br label %return, !dbg !986

if.end:                                           ; preds = %entry
  %call1 = call i8* @config_getoption(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.13, i32 0, i32 0)), !dbg !987
  %call2 = call i32 @strcasecmp(i8* %call1, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.11, i32 0, i32 0)) #8, !dbg !989
  %tobool3 = icmp ne i32 %call2, 0, !dbg !991
  br i1 %tobool3, label %if.end5, label %if.then4, !dbg !992

if.then4:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !993
  br label %return, !dbg !993

if.end5:                                          ; preds = %if.end
  %0 = load i8*, i8** %password.addr, align 8, !dbg !994
  %call6 = call i32 @checkpass_pwd(i8* %0), !dbg !995
  store i32 %call6, i32* %retval, align 4, !dbg !996
  br label %return, !dbg !996

return:                                           ; preds = %if.end5, %if.then4, %if.then
  %1 = load i32, i32* %retval, align 4, !dbg !997
  ret i32 %1, !dbg !997
}

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #4

declare i32 @replace(i8*, i8*, i8*, i32) #2

; Function Attrs: nounwind
declare i32 @setgid(i32) #4

declare i32 @initgroups(i8*, i32) #2

; Function Attrs: nounwind
declare i8* @strerror(i32) #4

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #7

; Function Attrs: nounwind
declare i32 @chdir(i8*) #4

declare void @new_umask(...) #2

declare void @print_file(i32, i8*) #2

declare void @bftpdutmp_log(i8 signext) #2

declare void @bftpd_cwd_init(...) #2

; Function Attrs: nounwind
declare void @free(i8*) #4

; Function Attrs: nounwind uwtable
define i32 @checkpass_pwd(i8* %password) #0 !dbg !104 {
entry:
  %retval = alloca i32, align 4
  %password.addr = alloca i8*, align 8
  %shd = alloca %struct.spwd*, align 8
  store i8* %password, i8** %password.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %password.addr, metadata !998, metadata !135), !dbg !999
  call void @llvm.dbg.declare(metadata %struct.spwd** %shd, metadata !1000, metadata !135), !dbg !1014
  %0 = load i8*, i8** getelementptr inbounds (%struct.passwd, %struct.passwd* @userinfo, i32 0, i32 1), align 8, !dbg !1015
  %1 = load i8*, i8** %password.addr, align 8, !dbg !1017
  %2 = load i8*, i8** getelementptr inbounds (%struct.passwd, %struct.passwd* @userinfo, i32 0, i32 1), align 8, !dbg !1018
  %call = call i8* @crypt(i8* %1, i8* %2) #9, !dbg !1019
  %call1 = call i32 @strcmp(i8* %0, i8* %call) #8, !dbg !1020
  %tobool = icmp ne i32 %call1, 0, !dbg !1022
  br i1 %tobool, label %if.then, label %if.end11, !dbg !1023

if.then:                                          ; preds = %entry
  %call2 = call %struct.spwd* @getspnam(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0)), !dbg !1024
  store %struct.spwd* %call2, %struct.spwd** %shd, align 8, !dbg !1027
  %tobool3 = icmp ne %struct.spwd* %call2, null, !dbg !1027
  br i1 %tobool3, label %if.end, label %if.then4, !dbg !1028

if.then4:                                         ; preds = %if.then
  store i32 1, i32* %retval, align 4, !dbg !1029
  br label %return, !dbg !1029

if.end:                                           ; preds = %if.then
  %3 = load %struct.spwd*, %struct.spwd** %shd, align 8, !dbg !1030
  %sp_pwdp = getelementptr inbounds %struct.spwd, %struct.spwd* %3, i32 0, i32 1, !dbg !1032
  %4 = load i8*, i8** %sp_pwdp, align 8, !dbg !1032
  %5 = load i8*, i8** %password.addr, align 8, !dbg !1033
  %6 = load %struct.spwd*, %struct.spwd** %shd, align 8, !dbg !1034
  %sp_pwdp5 = getelementptr inbounds %struct.spwd, %struct.spwd* %6, i32 0, i32 1, !dbg !1035
  %7 = load i8*, i8** %sp_pwdp5, align 8, !dbg !1035
  %call6 = call i8* @crypt(i8* %5, i8* %7) #9, !dbg !1036
  %call7 = call i32 @strcmp(i8* %4, i8* %call6) #8, !dbg !1037
  %tobool8 = icmp ne i32 %call7, 0, !dbg !1039
  br i1 %tobool8, label %if.then9, label %if.end10, !dbg !1040

if.then9:                                         ; preds = %if.end
  store i32 1, i32* %retval, align 4, !dbg !1041
  br label %return, !dbg !1041

if.end10:                                         ; preds = %if.end
  br label %if.end11, !dbg !1042

if.end11:                                         ; preds = %if.end10, %entry
  store i32 0, i32* %retval, align 4, !dbg !1043
  br label %return, !dbg !1043

return:                                           ; preds = %if.end11, %if.then9, %if.then4
  %8 = load i32, i32* %retval, align 4, !dbg !1044
  ret i32 %8, !dbg !1044
}

; Function Attrs: nounwind uwtable
define void @login_end() #0 !dbg !103 {
entry:
  call void @wtmp_end(), !dbg !1045
  ret void, !dbg !1046
}

; Function Attrs: nounwind
declare i8* @crypt(i8*, i8*) #4

declare %struct.spwd* @getspnam(i8*) #2

; Function Attrs: nounwind uwtable
define i32 @checkuser() #0 !dbg !105 {
entry:
  %retval = alloca i32, align 4
  %fd = alloca %struct._IO_FILE*, align 8
  %p = alloca i8*, align 8
  %line = alloca [256 x i8], align 16
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %fd, metadata !1047, metadata !135), !dbg !1048
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1049, metadata !135), !dbg !1050
  call void @llvm.dbg.declare(metadata [256 x i8]* %line, metadata !1051, metadata !135), !dbg !1052
  %call = call i8* @config_getoption(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.54, i32 0, i32 0)), !dbg !1053
  %call1 = call %struct._IO_FILE* @fopen64(i8* %call, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.41, i32 0, i32 0)), !dbg !1055
  store %struct._IO_FILE* %call1, %struct._IO_FILE** %fd, align 8, !dbg !1057
  %tobool = icmp ne %struct._IO_FILE* %call1, null, !dbg !1057
  br i1 %tobool, label %if.then, label %if.end18, !dbg !1058

if.then:                                          ; preds = %entry
  br label %while.cond, !dbg !1059

while.cond:                                       ; preds = %if.end16, %if.then9, %if.then
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %line, i32 0, i32 0, !dbg !1061
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** %fd, align 8, !dbg !1063
  %call2 = call i8* @fgets(i8* %arraydecay, i32 256, %struct._IO_FILE* %0), !dbg !1064
  %tobool3 = icmp ne i8* %call2, null, !dbg !1065
  br i1 %tobool3, label %while.body, label %while.end, !dbg !1065

while.body:                                       ; preds = %while.cond
  %arraydecay4 = getelementptr inbounds [256 x i8], [256 x i8]* %line, i32 0, i32 0, !dbg !1066
  %call5 = call i8* @strchr(i8* %arraydecay4, i32 10) #8, !dbg !1068
  store i8* %call5, i8** %p, align 8, !dbg !1069
  %tobool6 = icmp ne i8* %call5, null, !dbg !1069
  br i1 %tobool6, label %if.then7, label %if.end16, !dbg !1070

if.then7:                                         ; preds = %while.body
  %1 = load i8*, i8** %p, align 8, !dbg !1071
  store i8 0, i8* %1, align 1, !dbg !1073
  %arrayidx = getelementptr inbounds [256 x i8], [256 x i8]* %line, i64 0, i64 0, !dbg !1074
  %2 = load i8, i8* %arrayidx, align 16, !dbg !1074
  %conv = sext i8 %2 to i32, !dbg !1074
  %cmp = icmp eq i32 %conv, 35, !dbg !1076
  br i1 %cmp, label %if.then9, label %if.end, !dbg !1077

if.then9:                                         ; preds = %if.then7
  br label %while.cond, !dbg !1078

if.end:                                           ; preds = %if.then7
  %arraydecay10 = getelementptr inbounds [256 x i8], [256 x i8]* %line, i32 0, i32 0, !dbg !1079
  %call11 = call i32 @strcasecmp(i8* %arraydecay10, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0)) #8, !dbg !1081
  %tobool12 = icmp ne i32 %call11, 0, !dbg !1081
  br i1 %tobool12, label %if.end15, label %if.then13, !dbg !1082

if.then13:                                        ; preds = %if.end
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** %fd, align 8, !dbg !1083
  %call14 = call i32 @fclose(%struct._IO_FILE* %3), !dbg !1085
  store i32 1, i32* %retval, align 4, !dbg !1086
  br label %return, !dbg !1086

if.end15:                                         ; preds = %if.end
  br label %if.end16, !dbg !1087

if.end16:                                         ; preds = %if.end15, %while.body
  br label %while.cond, !dbg !1088

while.end:                                        ; preds = %while.cond
  %4 = load %struct._IO_FILE*, %struct._IO_FILE** %fd, align 8, !dbg !1090
  %call17 = call i32 @fclose(%struct._IO_FILE* %4), !dbg !1091
  br label %if.end18, !dbg !1092

if.end18:                                         ; preds = %while.end, %entry
  store i32 0, i32* %retval, align 4, !dbg !1093
  br label %return, !dbg !1093

return:                                           ; preds = %if.end18, %if.then13
  %5 = load i32, i32* %retval, align 4, !dbg !1094
  ret i32 %5, !dbg !1094
}

declare i8* @fgets(i8*, i32, %struct._IO_FILE*) #2

; Function Attrs: nounwind uwtable
define i32 @checkshell() #0 !dbg !108 {
entry:
  %retval = alloca i32, align 4
  %cp = alloca i8*, align 8
  %pwd = alloca %struct.passwd*, align 8
  call void @llvm.dbg.declare(metadata i8** %cp, metadata !1095, metadata !135), !dbg !1096
  call void @llvm.dbg.declare(metadata %struct.passwd** %pwd, metadata !1097, metadata !135), !dbg !1099
  %call = call i8* @config_getoption(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.55, i32 0, i32 0)), !dbg !1100
  %call1 = call i32 @strcasecmp(i8* %call, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.3, i32 0, i32 0)) #8, !dbg !1102
  %tobool = icmp ne i32 %call1, 0, !dbg !1104
  br i1 %tobool, label %if.end, label %if.then, !dbg !1105

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1106
  br label %return, !dbg !1106

if.end:                                           ; preds = %entry
  %call2 = call %struct.passwd* @getpwnam(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0)), !dbg !1107
  store %struct.passwd* %call2, %struct.passwd** %pwd, align 8, !dbg !1108
  br label %while.cond, !dbg !1109

while.cond:                                       ; preds = %if.end8, %if.end
  %call3 = call i8* @getusershell() #9, !dbg !1110
  store i8* %call3, i8** %cp, align 8, !dbg !1112
  %tobool4 = icmp ne i8* %call3, null, !dbg !1113
  br i1 %tobool4, label %while.body, label %while.end, !dbg !1113

while.body:                                       ; preds = %while.cond
  %0 = load i8*, i8** %cp, align 8, !dbg !1114
  %1 = load %struct.passwd*, %struct.passwd** %pwd, align 8, !dbg !1116
  %pw_shell = getelementptr inbounds %struct.passwd, %struct.passwd* %1, i32 0, i32 6, !dbg !1117
  %2 = load i8*, i8** %pw_shell, align 8, !dbg !1117
  %call5 = call i32 @strcmp(i8* %0, i8* %2) #8, !dbg !1118
  %tobool6 = icmp ne i32 %call5, 0, !dbg !1118
  br i1 %tobool6, label %if.end8, label %if.then7, !dbg !1119

if.then7:                                         ; preds = %while.body
  br label %while.end, !dbg !1120

if.end8:                                          ; preds = %while.body
  br label %while.cond, !dbg !1121

while.end:                                        ; preds = %if.then7, %while.cond
  call void @endusershell() #9, !dbg !1123
  %3 = load i8*, i8** %cp, align 8, !dbg !1124
  %tobool9 = icmp ne i8* %3, null, !dbg !1124
  br i1 %tobool9, label %if.else, label %if.then10, !dbg !1126

if.then10:                                        ; preds = %while.end
  store i32 1, i32* %retval, align 4, !dbg !1127
  br label %return, !dbg !1127

if.else:                                          ; preds = %while.end
  store i32 0, i32* %retval, align 4, !dbg !1128
  br label %return, !dbg !1128

return:                                           ; preds = %if.else, %if.then10, %if.then
  %4 = load i32, i32* %retval, align 4, !dbg !1129
  ret i32 %4, !dbg !1129
}

; Function Attrs: nounwind
declare i8* @getusershell() #4

; Function Attrs: nounwind
declare void @endusershell() #4

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #4

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { nounwind readonly }
attributes #9 = { nounwind }
attributes #10 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!131, !132}
!llvm.ident = !{!133}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !11, subprograms: !16, globals: !112)
!1 = !DIFile(filename: "login.c", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 15, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "./commands.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!5 = !{!6, !7, !8, !9, !10}
!6 = !DIEnumerator(name: "STATE_CONNECTED", value: 0)
!7 = !DIEnumerator(name: "STATE_USER", value: 1)
!8 = !DIEnumerator(name: "STATE_AUTHENTICATED", value: 2)
!9 = !DIEnumerator(name: "STATE_RENAME", value: 3)
!10 = !DIEnumerator(name: "STATE_ADMIN", value: 4)
!11 = !{!12, !13, !14}
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!13 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !15, size: 64, align: 64)
!15 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!16 = !{!17, !81, !84, !87, !90, !91, !92, !99, !102, !103, !104, !105, !108, !109}
!17 = distinct !DISubprogram(name: "mygetpwuid", scope: !18, file: !18, line: 66, type: !19, isLocal: false, isDefinition: true, scopeLine: 67, flags: DIFlagPrototyped, isOptimized: false, variables: !80)
!18 = !DIFile(filename: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/login.c", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!19 = !DISubroutineType(types: !20)
!20 = !{!14, !13, !21, !14}
!21 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !22, size: 64, align: 64)
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !23, line: 48, baseType: !24)
!23 = !DIFile(filename: "/usr/include/stdio.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!24 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !25, line: 245, size: 1728, align: 64, elements: !26)
!25 = !DIFile(filename: "/usr/include/libio.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!26 = !{!27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37, !38, !39, !47, !48, !49, !50, !54, !56, !58, !62, !65, !67, !68, !69, !70, !71, !75, !76}
!27 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !24, file: !25, line: 246, baseType: !13, size: 32, align: 32)
!28 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !24, file: !25, line: 251, baseType: !14, size: 64, align: 64, offset: 64)
!29 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !24, file: !25, line: 252, baseType: !14, size: 64, align: 64, offset: 128)
!30 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !24, file: !25, line: 253, baseType: !14, size: 64, align: 64, offset: 192)
!31 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !24, file: !25, line: 254, baseType: !14, size: 64, align: 64, offset: 256)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !24, file: !25, line: 255, baseType: !14, size: 64, align: 64, offset: 320)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !24, file: !25, line: 256, baseType: !14, size: 64, align: 64, offset: 384)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !24, file: !25, line: 257, baseType: !14, size: 64, align: 64, offset: 448)
!35 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !24, file: !25, line: 258, baseType: !14, size: 64, align: 64, offset: 512)
!36 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !24, file: !25, line: 260, baseType: !14, size: 64, align: 64, offset: 576)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !24, file: !25, line: 261, baseType: !14, size: 64, align: 64, offset: 640)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !24, file: !25, line: 262, baseType: !14, size: 64, align: 64, offset: 704)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !24, file: !25, line: 264, baseType: !40, size: 64, align: 64, offset: 768)
!40 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64, align: 64)
!41 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !25, line: 160, size: 192, align: 64, elements: !42)
!42 = !{!43, !44, !46}
!43 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !41, file: !25, line: 161, baseType: !40, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !41, file: !25, line: 162, baseType: !45, size: 64, align: 64, offset: 64)
!45 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64, align: 64)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !41, file: !25, line: 166, baseType: !13, size: 32, align: 32, offset: 128)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !24, file: !25, line: 266, baseType: !45, size: 64, align: 64, offset: 832)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !24, file: !25, line: 268, baseType: !13, size: 32, align: 32, offset: 896)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !24, file: !25, line: 272, baseType: !13, size: 32, align: 32, offset: 928)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !24, file: !25, line: 274, baseType: !51, size: 64, align: 64, offset: 960)
!51 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !52, line: 131, baseType: !53)
!52 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!53 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !24, file: !25, line: 278, baseType: !55, size: 16, align: 16, offset: 1024)
!55 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !24, file: !25, line: 279, baseType: !57, size: 8, align: 8, offset: 1040)
!57 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !24, file: !25, line: 280, baseType: !59, size: 8, align: 8, offset: 1048)
!59 = !DICompositeType(tag: DW_TAG_array_type, baseType: !15, size: 8, align: 8, elements: !60)
!60 = !{!61}
!61 = !DISubrange(count: 1)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !24, file: !25, line: 284, baseType: !63, size: 64, align: 64, offset: 1088)
!63 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !64, size: 64, align: 64)
!64 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !25, line: 154, baseType: null)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !24, file: !25, line: 293, baseType: !66, size: 64, align: 64, offset: 1152)
!66 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !52, line: 132, baseType: !53)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !24, file: !25, line: 302, baseType: !12, size: 64, align: 64, offset: 1216)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !24, file: !25, line: 303, baseType: !12, size: 64, align: 64, offset: 1280)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !24, file: !25, line: 304, baseType: !12, size: 64, align: 64, offset: 1344)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !24, file: !25, line: 305, baseType: !12, size: 64, align: 64, offset: 1408)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !24, file: !25, line: 306, baseType: !72, size: 64, align: 64, offset: 1472)
!72 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !73, line: 62, baseType: !74)
!73 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!74 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !24, file: !25, line: 308, baseType: !13, size: 32, align: 32, offset: 1536)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !24, file: !25, line: 310, baseType: !77, size: 160, align: 8, offset: 1568)
!77 = !DICompositeType(tag: DW_TAG_array_type, baseType: !15, size: 160, align: 8, elements: !78)
!78 = !{!79}
!79 = !DISubrange(count: 20)
!80 = !{}
!81 = distinct !DISubprogram(name: "mygetpwnam", scope: !18, file: !18, line: 91, type: !82, isLocal: false, isDefinition: true, scopeLine: 92, flags: DIFlagPrototyped, isOptimized: false, variables: !80)
!82 = !DISubroutineType(types: !83)
!83 = !{!13, !14, !21}
!84 = distinct !DISubprogram(name: "wtmp_init", scope: !18, file: !18, line: 115, type: !85, isLocal: false, isDefinition: true, scopeLine: 116, isOptimized: false, variables: !80)
!85 = !DISubroutineType(types: !86)
!86 = !{null}
!87 = distinct !DISubprogram(name: "bftpd_logwtmp", scope: !18, file: !18, line: 123, type: !88, isLocal: false, isDefinition: true, scopeLine: 124, flags: DIFlagPrototyped, isOptimized: false, variables: !80)
!88 = !DISubroutineType(types: !89)
!89 = !{null, !15}
!90 = distinct !DISubprogram(name: "wtmp_end", scope: !18, file: !18, line: 152, type: !85, isLocal: false, isDefinition: true, scopeLine: 153, isOptimized: false, variables: !80)
!91 = distinct !DISubprogram(name: "login_init", scope: !18, file: !18, line: 162, type: !85, isLocal: false, isDefinition: true, scopeLine: 163, isOptimized: false, variables: !80)
!92 = distinct !DISubprogram(name: "bftpd_setuid", scope: !18, file: !18, line: 176, type: !93, isLocal: false, isDefinition: true, scopeLine: 177, flags: DIFlagPrototyped, isOptimized: false, variables: !80)
!93 = !DISubroutineType(types: !94)
!94 = !{!13, !95}
!95 = !DIDerivedType(tag: DW_TAG_typedef, name: "uid_t", file: !96, line: 43, baseType: !97)
!96 = !DIFile(filename: "/usr/include/pwd.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!97 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !52, line: 125, baseType: !98)
!98 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!99 = distinct !DISubprogram(name: "bftpd_login", scope: !18, file: !18, line: 190, type: !100, isLocal: false, isDefinition: true, scopeLine: 191, flags: DIFlagPrototyped, isOptimized: false, variables: !80)
!100 = !DISubroutineType(types: !101)
!101 = !{!13, !14}
!102 = distinct !DISubprogram(name: "checkpass", scope: !18, file: !18, line: 445, type: !100, isLocal: false, isDefinition: true, scopeLine: 446, flags: DIFlagPrototyped, isOptimized: false, variables: !80)
!103 = distinct !DISubprogram(name: "login_end", scope: !18, file: !18, line: 465, type: !85, isLocal: false, isDefinition: true, scopeLine: 466, isOptimized: false, variables: !80)
!104 = distinct !DISubprogram(name: "checkpass_pwd", scope: !18, file: !18, line: 476, type: !100, isLocal: false, isDefinition: true, scopeLine: 477, flags: DIFlagPrototyped, isOptimized: false, variables: !80)
!105 = distinct !DISubprogram(name: "checkuser", scope: !18, file: !18, line: 541, type: !106, isLocal: false, isDefinition: true, scopeLine: 542, isOptimized: false, variables: !80)
!106 = !DISubroutineType(types: !107)
!107 = !{!13}
!108 = distinct !DISubprogram(name: "checkshell", scope: !18, file: !18, line: 564, type: !106, isLocal: false, isDefinition: true, scopeLine: 565, isOptimized: false, variables: !80)
!109 = distinct !DISubprogram(name: "check_file_password", scope: !18, file: !18, line: 602, type: !110, isLocal: false, isDefinition: true, scopeLine: 603, flags: DIFlagPrototyped, isOptimized: false, variables: !80)
!110 = !DISubroutineType(types: !111)
!111 = !{!14, !14, !14, !14}
!112 = !{!113, !114, !116, !117, !118, !119, !120}
!113 = !DIGlobalVariable(name: "userinfo_set", scope: !0, file: !18, line: 64, type: !15, isLocal: false, isDefinition: true, variable: i8* @userinfo_set)
!114 = !DIGlobalVariable(name: "configpath", scope: !0, file: !115, line: 25, type: !14, isLocal: false, isDefinition: true, variable: i8** @configpath)
!115 = !DIFile(filename: "./main.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!116 = !DIGlobalVariable(name: "daemonmode", scope: !0, file: !115, line: 26, type: !13, isLocal: false, isDefinition: true, variable: i32* @daemonmode)
!117 = !DIGlobalVariable(name: "pre_write_script", scope: !0, file: !115, line: 29, type: !14, isLocal: false, isDefinition: true, variable: i8** @pre_write_script)
!118 = !DIGlobalVariable(name: "post_write_script", scope: !0, file: !115, line: 30, type: !14, isLocal: false, isDefinition: true, variable: i8** @post_write_script)
!119 = !DIGlobalVariable(name: "wtmp", scope: !0, file: !18, line: 60, type: !21, isLocal: false, isDefinition: true, variable: %struct._IO_FILE** @wtmp)
!120 = !DIGlobalVariable(name: "userinfo", scope: !0, file: !18, line: 63, type: !121, isLocal: false, isDefinition: true, variable: %struct.passwd* @userinfo)
!121 = !DICompositeType(tag: DW_TAG_structure_type, name: "passwd", file: !96, line: 49, size: 384, align: 64, elements: !122)
!122 = !{!123, !124, !125, !126, !128, !129, !130}
!123 = !DIDerivedType(tag: DW_TAG_member, name: "pw_name", scope: !121, file: !96, line: 51, baseType: !14, size: 64, align: 64)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "pw_passwd", scope: !121, file: !96, line: 52, baseType: !14, size: 64, align: 64, offset: 64)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "pw_uid", scope: !121, file: !96, line: 53, baseType: !97, size: 32, align: 32, offset: 128)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "pw_gid", scope: !121, file: !96, line: 54, baseType: !127, size: 32, align: 32, offset: 160)
!127 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !52, line: 126, baseType: !98)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "pw_gecos", scope: !121, file: !96, line: 55, baseType: !14, size: 64, align: 64, offset: 192)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "pw_dir", scope: !121, file: !96, line: 56, baseType: !14, size: 64, align: 64, offset: 256)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "pw_shell", scope: !121, file: !96, line: 57, baseType: !14, size: 64, align: 64, offset: 320)
!131 = !{i32 2, !"Dwarf Version", i32 4}
!132 = !{i32 2, !"Debug Info Version", i32 3}
!133 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!134 = !DILocalVariable(name: "uid", arg: 1, scope: !17, file: !18, line: 66, type: !13)
!135 = !DIExpression()
!136 = !DILocation(line: 66, column: 22, scope: !17)
!137 = !DILocalVariable(name: "file", arg: 2, scope: !17, file: !18, line: 66, type: !21)
!138 = !DILocation(line: 66, column: 34, scope: !17)
!139 = !DILocalVariable(name: "name", arg: 3, scope: !17, file: !18, line: 66, type: !14)
!140 = !DILocation(line: 66, column: 46, scope: !17)
!141 = !DILocalVariable(name: "_uid", scope: !17, file: !18, line: 68, type: !13)
!142 = !DILocation(line: 68, column: 6, scope: !17)
!143 = !DILocalVariable(name: "foo", scope: !17, file: !18, line: 69, type: !144)
!144 = !DICompositeType(tag: DW_TAG_array_type, baseType: !15, size: 2048, align: 8, elements: !145)
!145 = !{!146}
!146 = !DISubrange(count: 256)
!147 = !DILocation(line: 69, column: 7, scope: !17)
!148 = !DILocalVariable(name: "i", scope: !17, file: !18, line: 70, type: !13)
!149 = !DILocation(line: 70, column: 9, scope: !17)
!150 = !DILocation(line: 71, column: 6, scope: !151)
!151 = distinct !DILexicalBlock(scope: !17, file: !18, line: 71, column: 6)
!152 = !DILocation(line: 71, column: 6, scope: !17)
!153 = !DILocation(line: 72, column: 10, scope: !154)
!154 = distinct !DILexicalBlock(scope: !151, file: !18, line: 71, column: 12)
!155 = !DILocation(line: 72, column: 3, scope: !154)
!156 = !DILocation(line: 73, column: 9, scope: !154)
!157 = !DILocation(line: 73, column: 23, scope: !158)
!158 = !DILexicalBlockFile(scope: !154, file: !18, discriminator: 1)
!159 = !DILocation(line: 73, column: 47, scope: !158)
!160 = !DILocation(line: 73, column: 16, scope: !158)
!161 = !DILocation(line: 73, column: 52, scope: !158)
!162 = !DILocation(line: 73, column: 9, scope: !158)
!163 = !DILocation(line: 74, column: 18, scope: !164)
!164 = distinct !DILexicalBlock(scope: !165, file: !18, line: 74, column: 17)
!165 = distinct !DILexicalBlock(scope: !154, file: !18, line: 73, column: 60)
!166 = !DILocation(line: 74, column: 25, scope: !164)
!167 = !DILocation(line: 74, column: 33, scope: !164)
!168 = !DILocation(line: 74, column: 45, scope: !169)
!169 = !DILexicalBlockFile(scope: !164, file: !18, discriminator: 1)
!170 = !DILocation(line: 74, column: 38, scope: !169)
!171 = !DILocation(line: 74, column: 56, scope: !169)
!172 = !DILocation(line: 74, column: 67, scope: !173)
!173 = !DILexicalBlockFile(scope: !164, file: !18, discriminator: 2)
!174 = !DILocation(line: 74, column: 60, scope: !173)
!175 = !DILocation(line: 74, column: 79, scope: !173)
!176 = !DILocation(line: 74, column: 83, scope: !173)
!177 = !DILocation(line: 74, column: 93, scope: !173)
!178 = !DILocation(line: 74, column: 77, scope: !173)
!179 = !DILocation(line: 74, column: 17, scope: !173)
!180 = !DILocation(line: 75, column: 17, scope: !164)
!181 = !DILocation(line: 76, column: 24, scope: !165)
!182 = !DILocation(line: 76, column: 17, scope: !165)
!183 = !DILocation(line: 76, column: 36, scope: !165)
!184 = !DILocation(line: 76, column: 34, scope: !165)
!185 = !DILocation(line: 76, column: 15, scope: !165)
!186 = !DILocation(line: 77, column: 21, scope: !165)
!187 = !DILocation(line: 77, column: 27, scope: !165)
!188 = !DILocation(line: 77, column: 32, scope: !165)
!189 = !DILocation(line: 77, column: 13, scope: !165)
!190 = !DILocation(line: 78, column: 18, scope: !165)
!191 = !DILocation(line: 78, column: 13, scope: !165)
!192 = !DILocation(line: 78, column: 21, scope: !165)
!193 = !DILocation(line: 79, column: 18, scope: !165)
!194 = !DILocation(line: 79, column: 24, scope: !165)
!195 = !DILocation(line: 79, column: 22, scope: !165)
!196 = !DILocation(line: 79, column: 26, scope: !165)
!197 = !DILocation(line: 79, column: 11, scope: !165)
!198 = !DILocation(line: 79, column: 36, scope: !165)
!199 = !DILocation(line: 79, column: 4, scope: !200)
!200 = !DILexicalBlockFile(scope: !165, file: !18, discriminator: 1)
!201 = !DILocation(line: 80, column: 8, scope: !202)
!202 = distinct !DILexicalBlock(scope: !165, file: !18, line: 80, column: 8)
!203 = !DILocation(line: 80, column: 16, scope: !202)
!204 = !DILocation(line: 80, column: 13, scope: !202)
!205 = !DILocation(line: 80, column: 8, scope: !165)
!206 = !DILocation(line: 81, column: 9, scope: !207)
!207 = distinct !DILexicalBlock(scope: !208, file: !18, line: 81, column: 9)
!208 = distinct !DILexicalBlock(scope: !202, file: !18, line: 80, column: 21)
!209 = !DILocation(line: 81, column: 17, scope: !207)
!210 = !DILocation(line: 81, column: 9, scope: !208)
!211 = !DILocation(line: 82, column: 12, scope: !207)
!212 = !DILocation(line: 82, column: 6, scope: !207)
!213 = !DILocation(line: 83, column: 12, scope: !208)
!214 = !DILocation(line: 83, column: 5, scope: !208)
!215 = !DILocation(line: 73, column: 9, scope: !216)
!216 = !DILexicalBlockFile(scope: !154, file: !18, discriminator: 2)
!217 = !DILocation(line: 86, column: 2, scope: !154)
!218 = !DILocation(line: 87, column: 10, scope: !17)
!219 = !DILocation(line: 87, column: 22, scope: !17)
!220 = !DILocation(line: 87, column: 2, scope: !17)
!221 = !DILocation(line: 88, column: 9, scope: !17)
!222 = !DILocation(line: 88, column: 2, scope: !17)
!223 = !DILocation(line: 89, column: 1, scope: !17)
!224 = !DILocalVariable(name: "name", arg: 1, scope: !81, file: !18, line: 91, type: !14)
!225 = !DILocation(line: 91, column: 22, scope: !81)
!226 = !DILocalVariable(name: "file", arg: 2, scope: !81, file: !18, line: 91, type: !21)
!227 = !DILocation(line: 91, column: 35, scope: !81)
!228 = !DILocalVariable(name: "_name", scope: !81, file: !18, line: 93, type: !229)
!229 = !DICompositeType(tag: DW_TAG_array_type, baseType: !15, size: 248, align: 8, elements: !230)
!230 = !{!231}
!231 = !DISubrange(count: 31)
!232 = !DILocation(line: 93, column: 7, scope: !81)
!233 = !DILocalVariable(name: "foo", scope: !81, file: !18, line: 94, type: !144)
!234 = !DILocation(line: 94, column: 7, scope: !81)
!235 = !DILocalVariable(name: "uid", scope: !81, file: !18, line: 95, type: !13)
!236 = !DILocation(line: 95, column: 6, scope: !81)
!237 = !DILocalVariable(name: "i", scope: !81, file: !18, line: 95, type: !13)
!238 = !DILocation(line: 95, column: 11, scope: !81)
!239 = !DILocation(line: 96, column: 6, scope: !240)
!240 = distinct !DILexicalBlock(scope: !81, file: !18, line: 96, column: 6)
!241 = !DILocation(line: 96, column: 6, scope: !81)
!242 = !DILocation(line: 97, column: 10, scope: !243)
!243 = distinct !DILexicalBlock(scope: !240, file: !18, line: 96, column: 12)
!244 = !DILocation(line: 97, column: 3, scope: !243)
!245 = !DILocation(line: 98, column: 9, scope: !243)
!246 = !DILocation(line: 98, column: 23, scope: !247)
!247 = !DILexicalBlockFile(scope: !243, file: !18, discriminator: 1)
!248 = !DILocation(line: 98, column: 47, scope: !247)
!249 = !DILocation(line: 98, column: 16, scope: !247)
!250 = !DILocation(line: 98, column: 52, scope: !247)
!251 = !DILocation(line: 98, column: 9, scope: !247)
!252 = !DILocation(line: 99, column: 18, scope: !253)
!253 = distinct !DILexicalBlock(scope: !254, file: !18, line: 99, column: 17)
!254 = distinct !DILexicalBlock(scope: !243, file: !18, line: 98, column: 60)
!255 = !DILocation(line: 99, column: 25, scope: !253)
!256 = !DILocation(line: 99, column: 33, scope: !253)
!257 = !DILocation(line: 99, column: 45, scope: !258)
!258 = !DILexicalBlockFile(scope: !253, file: !18, discriminator: 1)
!259 = !DILocation(line: 99, column: 38, scope: !258)
!260 = !DILocation(line: 99, column: 56, scope: !258)
!261 = !DILocation(line: 99, column: 67, scope: !262)
!262 = !DILexicalBlockFile(scope: !253, file: !18, discriminator: 2)
!263 = !DILocation(line: 99, column: 60, scope: !262)
!264 = !DILocation(line: 99, column: 79, scope: !262)
!265 = !DILocation(line: 99, column: 83, scope: !262)
!266 = !DILocation(line: 99, column: 93, scope: !262)
!267 = !DILocation(line: 99, column: 77, scope: !262)
!268 = !DILocation(line: 99, column: 17, scope: !262)
!269 = !DILocation(line: 100, column: 17, scope: !253)
!270 = !DILocation(line: 101, column: 24, scope: !254)
!271 = !DILocation(line: 101, column: 17, scope: !254)
!272 = !DILocation(line: 101, column: 36, scope: !254)
!273 = !DILocation(line: 101, column: 34, scope: !254)
!274 = !DILocation(line: 101, column: 15, scope: !254)
!275 = !DILocation(line: 102, column: 21, scope: !254)
!276 = !DILocation(line: 102, column: 28, scope: !254)
!277 = !DILocation(line: 102, column: 33, scope: !254)
!278 = !DILocation(line: 102, column: 13, scope: !254)
!279 = !DILocation(line: 103, column: 19, scope: !254)
!280 = !DILocation(line: 103, column: 13, scope: !254)
!281 = !DILocation(line: 103, column: 22, scope: !254)
!282 = !DILocation(line: 104, column: 18, scope: !254)
!283 = !DILocation(line: 104, column: 24, scope: !254)
!284 = !DILocation(line: 104, column: 22, scope: !254)
!285 = !DILocation(line: 104, column: 26, scope: !254)
!286 = !DILocation(line: 104, column: 11, scope: !254)
!287 = !DILocation(line: 104, column: 36, scope: !254)
!288 = !DILocation(line: 104, column: 4, scope: !289)
!289 = !DILexicalBlockFile(scope: !254, file: !18, discriminator: 1)
!290 = !DILocation(line: 105, column: 8, scope: !291)
!291 = distinct !DILexicalBlock(scope: !254, file: !18, line: 105, column: 8)
!292 = !DILocation(line: 105, column: 17, scope: !291)
!293 = !DILocation(line: 105, column: 8, scope: !254)
!294 = !DILocation(line: 106, column: 11, scope: !291)
!295 = !DILocation(line: 106, column: 5, scope: !291)
!296 = !DILocation(line: 107, column: 16, scope: !297)
!297 = distinct !DILexicalBlock(scope: !254, file: !18, line: 107, column: 8)
!298 = !DILocation(line: 107, column: 22, scope: !297)
!299 = !DILocation(line: 107, column: 9, scope: !297)
!300 = !DILocation(line: 107, column: 8, scope: !254)
!301 = !DILocation(line: 108, column: 12, scope: !297)
!302 = !DILocation(line: 108, column: 5, scope: !297)
!303 = !DILocation(line: 98, column: 9, scope: !304)
!304 = !DILexicalBlockFile(scope: !243, file: !18, discriminator: 2)
!305 = !DILocation(line: 110, column: 2, scope: !243)
!306 = !DILocation(line: 111, column: 2, scope: !81)
!307 = !DILocation(line: 112, column: 1, scope: !81)
!308 = !DILocation(line: 117, column: 17, scope: !309)
!309 = distinct !DILexicalBlock(scope: !84, file: !18, line: 117, column: 6)
!310 = !DILocation(line: 117, column: 6, scope: !311)
!311 = !DILexicalBlockFile(scope: !309, file: !18, discriminator: 1)
!312 = !DILocation(line: 117, column: 6, scope: !309)
!313 = !DILocation(line: 117, column: 6, scope: !84)
!314 = !DILocation(line: 118, column: 17, scope: !315)
!315 = distinct !DILexicalBlock(scope: !316, file: !18, line: 118, column: 7)
!316 = distinct !DILexicalBlock(scope: !309, file: !18, line: 117, column: 54)
!317 = !DILocation(line: 118, column: 15, scope: !315)
!318 = !DILocation(line: 118, column: 7, scope: !316)
!319 = !DILocation(line: 119, column: 4, scope: !315)
!320 = !DILocation(line: 120, column: 2, scope: !316)
!321 = !DILocation(line: 121, column: 1, scope: !84)
!322 = !DILocalVariable(name: "type", arg: 1, scope: !87, file: !18, line: 123, type: !15)
!323 = !DILocation(line: 123, column: 25, scope: !87)
!324 = !DILocalVariable(name: "ut", scope: !87, file: !18, line: 125, type: !325)
!325 = !DICompositeType(tag: DW_TAG_structure_type, name: "utmp", file: !326, line: 58, size: 3072, align: 32, elements: !327)
!326 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/utmp.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!327 = !{!328, !330, !334, !338, !342, !343, !344, !349, !351, !356, !358}
!328 = !DIDerivedType(tag: DW_TAG_member, name: "ut_type", scope: !325, file: !326, line: 60, baseType: !329, size: 16, align: 16)
!329 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!330 = !DIDerivedType(tag: DW_TAG_member, name: "ut_pid", scope: !325, file: !326, line: 61, baseType: !331, size: 32, align: 32, offset: 32)
!331 = !DIDerivedType(tag: DW_TAG_typedef, name: "pid_t", file: !332, line: 98, baseType: !333)
!332 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!333 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pid_t", file: !52, line: 133, baseType: !13)
!334 = !DIDerivedType(tag: DW_TAG_member, name: "ut_line", scope: !325, file: !326, line: 62, baseType: !335, size: 256, align: 8, offset: 64)
!335 = !DICompositeType(tag: DW_TAG_array_type, baseType: !15, size: 256, align: 8, elements: !336)
!336 = !{!337}
!337 = !DISubrange(count: 32)
!338 = !DIDerivedType(tag: DW_TAG_member, name: "ut_id", scope: !325, file: !326, line: 63, baseType: !339, size: 32, align: 8, offset: 320)
!339 = !DICompositeType(tag: DW_TAG_array_type, baseType: !15, size: 32, align: 8, elements: !340)
!340 = !{!341}
!341 = !DISubrange(count: 4)
!342 = !DIDerivedType(tag: DW_TAG_member, name: "ut_user", scope: !325, file: !326, line: 64, baseType: !335, size: 256, align: 8, offset: 352)
!343 = !DIDerivedType(tag: DW_TAG_member, name: "ut_host", scope: !325, file: !326, line: 65, baseType: !144, size: 2048, align: 8, offset: 608)
!344 = !DIDerivedType(tag: DW_TAG_member, name: "ut_exit", scope: !325, file: !326, line: 66, baseType: !345, size: 32, align: 16, offset: 2656)
!345 = !DICompositeType(tag: DW_TAG_structure_type, name: "exit_status", file: !326, line: 50, size: 32, align: 16, elements: !346)
!346 = !{!347, !348}
!347 = !DIDerivedType(tag: DW_TAG_member, name: "e_termination", scope: !345, file: !326, line: 52, baseType: !329, size: 16, align: 16)
!348 = !DIDerivedType(tag: DW_TAG_member, name: "e_exit", scope: !345, file: !326, line: 53, baseType: !329, size: 16, align: 16, offset: 16)
!349 = !DIDerivedType(tag: DW_TAG_member, name: "ut_session", scope: !325, file: !326, line: 72, baseType: !350, size: 32, align: 32, offset: 2688)
!350 = !DIDerivedType(tag: DW_TAG_typedef, name: "int32_t", file: !332, line: 196, baseType: !13)
!351 = !DIDerivedType(tag: DW_TAG_member, name: "ut_tv", scope: !325, file: !326, line: 77, baseType: !352, size: 64, align: 32, offset: 2720)
!352 = !DICompositeType(tag: DW_TAG_structure_type, scope: !325, file: !326, line: 73, size: 64, align: 32, elements: !353)
!353 = !{!354, !355}
!354 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !352, file: !326, line: 75, baseType: !350, size: 32, align: 32)
!355 = !DIDerivedType(tag: DW_TAG_member, name: "tv_usec", scope: !352, file: !326, line: 76, baseType: !350, size: 32, align: 32, offset: 32)
!356 = !DIDerivedType(tag: DW_TAG_member, name: "ut_addr_v6", scope: !325, file: !326, line: 83, baseType: !357, size: 128, align: 32, offset: 2784)
!357 = !DICompositeType(tag: DW_TAG_array_type, baseType: !350, size: 128, align: 32, elements: !340)
!358 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !325, file: !326, line: 84, baseType: !77, size: 160, align: 8, offset: 2912)
!359 = !DILocation(line: 125, column: 14, scope: !87)
!360 = !DILocation(line: 126, column: 7, scope: !361)
!361 = distinct !DILexicalBlock(scope: !87, file: !18, line: 126, column: 6)
!362 = !DILocation(line: 126, column: 6, scope: !87)
!363 = !DILocation(line: 127, column: 3, scope: !361)
!364 = !DILocation(line: 128, column: 2, scope: !87)
!365 = !DILocation(line: 130, column: 14, scope: !87)
!366 = !DILocation(line: 130, column: 5, scope: !87)
!367 = !DILocation(line: 130, column: 12, scope: !87)
!368 = !DILocation(line: 132, column: 13, scope: !87)
!369 = !DILocation(line: 132, column: 10, scope: !87)
!370 = !DILocation(line: 132, column: 37, scope: !87)
!371 = !DILocation(line: 132, column: 2, scope: !372)
!372 = !DILexicalBlockFile(scope: !87, file: !18, discriminator: 1)
!373 = !DILocation(line: 133, column: 6, scope: !374)
!374 = distinct !DILexicalBlock(scope: !87, file: !18, line: 133, column: 6)
!375 = !DILocation(line: 133, column: 6, scope: !87)
!376 = !DILocation(line: 135, column: 6, scope: !377)
!377 = distinct !DILexicalBlock(scope: !374, file: !18, line: 133, column: 12)
!378 = !DILocation(line: 135, column: 14, scope: !377)
!379 = !DILocation(line: 137, column: 14, scope: !377)
!380 = !DILocation(line: 137, column: 11, scope: !377)
!381 = !DILocation(line: 137, column: 3, scope: !377)
!382 = !DILocation(line: 139, column: 14, scope: !377)
!383 = !DILocation(line: 139, column: 11, scope: !377)
!384 = !DILocation(line: 139, column: 23, scope: !377)
!385 = !DILocation(line: 139, column: 3, scope: !377)
!386 = !DILocation(line: 141, column: 2, scope: !377)
!387 = !DILocation(line: 143, column: 6, scope: !388)
!388 = distinct !DILexicalBlock(scope: !374, file: !18, line: 141, column: 9)
!389 = !DILocation(line: 143, column: 14, scope: !388)
!390 = !DILocation(line: 146, column: 12, scope: !87)
!391 = !DILocation(line: 146, column: 7, scope: !87)
!392 = !DILocation(line: 146, column: 2, scope: !87)
!393 = !DILocation(line: 147, column: 8, scope: !87)
!394 = !DILocation(line: 147, column: 2, scope: !87)
!395 = !DILocation(line: 148, column: 9, scope: !87)
!396 = !DILocation(line: 148, column: 38, scope: !87)
!397 = !DILocation(line: 148, column: 2, scope: !87)
!398 = !DILocation(line: 149, column: 9, scope: !87)
!399 = !DILocation(line: 149, column: 2, scope: !87)
!400 = !DILocation(line: 150, column: 1, scope: !87)
!401 = !DILocation(line: 150, column: 1, scope: !372)
!402 = !DILocation(line: 154, column: 6, scope: !403)
!403 = distinct !DILexicalBlock(scope: !90, file: !18, line: 154, column: 6)
!404 = !DILocation(line: 154, column: 6, scope: !90)
!405 = !DILocation(line: 155, column: 7, scope: !406)
!406 = distinct !DILexicalBlock(scope: !407, file: !18, line: 155, column: 7)
!407 = distinct !DILexicalBlock(scope: !403, file: !18, line: 154, column: 12)
!408 = !DILocation(line: 155, column: 13, scope: !406)
!409 = !DILocation(line: 155, column: 7, scope: !407)
!410 = !DILocation(line: 156, column: 4, scope: !406)
!411 = !DILocation(line: 157, column: 10, scope: !407)
!412 = !DILocation(line: 157, column: 3, scope: !407)
!413 = !DILocation(line: 158, column: 2, scope: !407)
!414 = !DILocation(line: 159, column: 1, scope: !90)
!415 = !DILocalVariable(name: "foo", scope: !91, file: !18, line: 164, type: !14)
!416 = !DILocation(line: 164, column: 11, scope: !91)
!417 = !DILocation(line: 164, column: 17, scope: !91)
!418 = !DILocation(line: 166, column: 2, scope: !91)
!419 = !DILocation(line: 168, column: 9, scope: !420)
!420 = distinct !DILexicalBlock(scope: !91, file: !18, line: 168, column: 9)
!421 = !DILocation(line: 168, column: 9, scope: !91)
!422 = !DILocation(line: 169, column: 20, scope: !423)
!423 = distinct !DILexicalBlock(scope: !424, file: !18, line: 169, column: 13)
!424 = distinct !DILexicalBlock(scope: !420, file: !18, line: 168, column: 17)
!425 = !DILocation(line: 169, column: 13, scope: !423)
!426 = !DILocation(line: 169, column: 25, scope: !423)
!427 = !DILocation(line: 169, column: 13, scope: !424)
!428 = !DILocation(line: 170, column: 13, scope: !429)
!429 = distinct !DILexicalBlock(scope: !423, file: !18, line: 169, column: 32)
!430 = !DILocation(line: 171, column: 13, scope: !429)
!431 = !DILocation(line: 173, column: 5, scope: !424)
!432 = !DILocation(line: 174, column: 1, scope: !91)
!433 = !DILocalVariable(name: "uid", arg: 1, scope: !92, file: !18, line: 176, type: !95)
!434 = !DILocation(line: 176, column: 24, scope: !92)
!435 = !DILocation(line: 180, column: 21, scope: !436)
!436 = distinct !DILexicalBlock(scope: !92, file: !18, line: 180, column: 9)
!437 = !DILocation(line: 180, column: 10, scope: !438)
!438 = !DILexicalBlockFile(scope: !436, file: !18, discriminator: 1)
!439 = !DILocation(line: 180, column: 10, scope: !436)
!440 = !DILocation(line: 180, column: 9, scope: !92)
!441 = !DILocation(line: 181, column: 24, scope: !436)
!442 = !DILocation(line: 181, column: 16, scope: !436)
!443 = !DILocation(line: 181, column: 9, scope: !436)
!444 = !DILocation(line: 183, column: 23, scope: !436)
!445 = !DILocation(line: 183, column: 16, scope: !436)
!446 = !DILocation(line: 183, column: 9, scope: !436)
!447 = !DILocation(line: 184, column: 1, scope: !92)
!448 = !DILocalVariable(name: "password", arg: 1, scope: !99, file: !18, line: 190, type: !14)
!449 = !DILocation(line: 190, column: 23, scope: !99)
!450 = !DILocalVariable(name: "str", scope: !99, file: !18, line: 192, type: !451)
!451 = !DICompositeType(tag: DW_TAG_array_type, baseType: !15, size: 4104, align: 8, elements: !452)
!452 = !{!453}
!453 = !DISubrange(count: 513)
!454 = !DILocation(line: 192, column: 7, scope: !99)
!455 = !DILocalVariable(name: "foo", scope: !99, file: !18, line: 193, type: !14)
!456 = !DILocation(line: 193, column: 8, scope: !99)
!457 = !DILocalVariable(name: "maxusers", scope: !99, file: !18, line: 194, type: !13)
!458 = !DILocation(line: 194, column: 6, scope: !99)
!459 = !DILocalVariable(name: "file_auth", scope: !99, file: !18, line: 195, type: !14)
!460 = !DILocation(line: 195, column: 15, scope: !99)
!461 = !DILocalVariable(name: "home_directory", scope: !99, file: !18, line: 196, type: !14)
!462 = !DILocation(line: 196, column: 15, scope: !99)
!463 = !DILocalVariable(name: "anonymous", scope: !99, file: !18, line: 197, type: !14)
!464 = !DILocation(line: 197, column: 15, scope: !99)
!465 = !DILocalVariable(name: "get_maxusers", scope: !99, file: !18, line: 198, type: !74)
!466 = !DILocation(line: 198, column: 23, scope: !99)
!467 = !DILocalVariable(name: "anon_ok", scope: !99, file: !18, line: 199, type: !13)
!468 = !DILocation(line: 199, column: 13, scope: !99)
!469 = !DILocation(line: 201, column: 9, scope: !99)
!470 = !DILocation(line: 201, column: 16, scope: !99)
!471 = !DILocation(line: 202, column: 21, scope: !99)
!472 = !DILocation(line: 202, column: 19, scope: !99)
!473 = !DILocation(line: 204, column: 15, scope: !474)
!474 = distinct !DILexicalBlock(scope: !99, file: !18, line: 204, column: 13)
!475 = !DILocation(line: 204, column: 13, scope: !99)
!476 = !DILocation(line: 207, column: 24, scope: !477)
!477 = distinct !DILexicalBlock(scope: !474, file: !18, line: 205, column: 9)
!478 = !DILocation(line: 207, column: 22, scope: !477)
!479 = !DILocation(line: 208, column: 29, scope: !480)
!480 = distinct !DILexicalBlock(scope: !477, file: !18, line: 208, column: 16)
!481 = !DILocation(line: 208, column: 18, scope: !480)
!482 = !DILocation(line: 208, column: 16, scope: !477)
!483 = !DILocation(line: 210, column: 30, scope: !484)
!484 = distinct !DILexicalBlock(scope: !480, file: !18, line: 209, column: 12)
!485 = !DILocation(line: 211, column: 23, scope: !484)
!486 = !DILocation(line: 212, column: 12, scope: !484)
!487 = !DILocation(line: 214, column: 15, scope: !488)
!488 = distinct !DILexicalBlock(scope: !480, file: !18, line: 214, column: 14)
!489 = !DILocation(line: 214, column: 14, scope: !480)
!490 = !DILocation(line: 215, column: 17, scope: !491)
!491 = distinct !DILexicalBlock(scope: !488, file: !18, line: 214, column: 31)
!492 = !DILocation(line: 217, column: 17, scope: !491)
!493 = !DILocation(line: 220, column: 9, scope: !477)
!494 = !DILocation(line: 224, column: 49, scope: !495)
!495 = distinct !DILexicalBlock(scope: !474, file: !18, line: 223, column: 9)
!496 = !DILocation(line: 224, column: 66, scope: !495)
!497 = !DILocation(line: 224, column: 29, scope: !495)
!498 = !DILocation(line: 224, column: 27, scope: !495)
!499 = !DILocation(line: 225, column: 24, scope: !495)
!500 = !DILocation(line: 225, column: 22, scope: !495)
!501 = !DILocation(line: 226, column: 18, scope: !502)
!502 = distinct !DILexicalBlock(scope: !495, file: !18, line: 226, column: 16)
!503 = !DILocation(line: 226, column: 16, scope: !495)
!504 = !DILocation(line: 228, column: 33, scope: !505)
!505 = distinct !DILexicalBlock(scope: !506, file: !18, line: 228, column: 20)
!506 = distinct !DILexicalBlock(scope: !502, file: !18, line: 227, column: 12)
!507 = !DILocation(line: 228, column: 22, scope: !505)
!508 = !DILocation(line: 228, column: 20, scope: !506)
!509 = !DILocation(line: 229, column: 35, scope: !505)
!510 = !DILocation(line: 229, column: 20, scope: !505)
!511 = !DILocation(line: 232, column: 19, scope: !512)
!512 = distinct !DILexicalBlock(scope: !505, file: !18, line: 231, column: 16)
!513 = !DILocation(line: 234, column: 19, scope: !512)
!514 = !DILocation(line: 236, column: 12, scope: !506)
!515 = !DILocation(line: 239, column: 24, scope: !516)
!516 = distinct !DILexicalBlock(scope: !99, file: !18, line: 239, column: 6)
!517 = !DILocation(line: 239, column: 22, scope: !516)
!518 = !DILocation(line: 239, column: 6, scope: !519)
!519 = !DILexicalBlockFile(scope: !516, file: !18, discriminator: 1)
!520 = !DILocation(line: 239, column: 6, scope: !516)
!521 = !DILocation(line: 239, column: 6, scope: !99)
!522 = !DILocation(line: 240, column: 7, scope: !523)
!523 = distinct !DILexicalBlock(scope: !524, file: !18, line: 240, column: 7)
!524 = distinct !DILexicalBlock(scope: !516, file: !18, line: 239, column: 66)
!525 = !DILocation(line: 240, column: 14, scope: !523)
!526 = !DILocation(line: 240, column: 7, scope: !524)
!527 = !DILocation(line: 241, column: 20, scope: !528)
!528 = distinct !DILexicalBlock(scope: !529, file: !18, line: 241, column: 8)
!529 = distinct !DILexicalBlock(scope: !523, file: !18, line: 240, column: 23)
!530 = !DILocation(line: 241, column: 8, scope: !528)
!531 = !DILocation(line: 241, column: 8, scope: !529)
!532 = !DILocation(line: 242, column: 74, scope: !528)
!533 = !DILocation(line: 242, column: 5, scope: !528)
!534 = !DILocation(line: 244, column: 5, scope: !528)
!535 = !DILocation(line: 245, column: 4, scope: !529)
!536 = !DILocation(line: 246, column: 4, scope: !529)
!537 = !DILocation(line: 248, column: 2, scope: !524)
!538 = !DILocation(line: 249, column: 25, scope: !99)
!539 = !DILocation(line: 249, column: 17, scope: !540)
!540 = !DILexicalBlockFile(scope: !99, file: !18, discriminator: 1)
!541 = !DILocation(line: 249, column: 15, scope: !99)
!542 = !DILocation(line: 250, column: 13, scope: !543)
!543 = distinct !DILexicalBlock(scope: !99, file: !18, line: 250, column: 13)
!544 = !DILocation(line: 250, column: 26, scope: !543)
!545 = !DILocation(line: 250, column: 13, scope: !99)
!546 = !DILocation(line: 251, column: 23, scope: !543)
!547 = !DILocation(line: 251, column: 21, scope: !543)
!548 = !DILocation(line: 251, column: 12, scope: !543)
!549 = !DILocation(line: 254, column: 12, scope: !550)
!550 = distinct !DILexicalBlock(scope: !543, file: !18, line: 253, column: 9)
!551 = !DILocation(line: 255, column: 21, scope: !550)
!552 = !DILocation(line: 257, column: 7, scope: !553)
!553 = distinct !DILexicalBlock(scope: !99, file: !18, line: 257, column: 6)
!554 = !DILocation(line: 257, column: 6, scope: !553)
!555 = !DILocation(line: 257, column: 17, scope: !553)
!556 = !DILocation(line: 257, column: 21, scope: !557)
!557 = !DILexicalBlockFile(scope: !553, file: !18, discriminator: 1)
!558 = !DILocation(line: 257, column: 33, scope: !557)
!559 = !DILocation(line: 257, column: 30, scope: !557)
!560 = !DILocation(line: 257, column: 6, scope: !557)
!561 = !DILocation(line: 258, column: 75, scope: !562)
!562 = distinct !DILexicalBlock(scope: !553, file: !18, line: 257, column: 60)
!563 = !DILocation(line: 258, column: 3, scope: !562)
!564 = !DILocation(line: 259, column: 17, scope: !562)
!565 = !DILocation(line: 260, column: 3, scope: !562)
!566 = !DILocation(line: 262, column: 25, scope: !99)
!567 = !DILocation(line: 262, column: 17, scope: !540)
!568 = !DILocation(line: 262, column: 15, scope: !99)
!569 = !DILocation(line: 263, column: 13, scope: !570)
!570 = distinct !DILexicalBlock(scope: !99, file: !18, line: 263, column: 13)
!571 = !DILocation(line: 263, column: 26, scope: !570)
!572 = !DILocation(line: 263, column: 13, scope: !99)
!573 = !DILocation(line: 264, column: 23, scope: !570)
!574 = !DILocation(line: 264, column: 21, scope: !570)
!575 = !DILocation(line: 264, column: 12, scope: !570)
!576 = !DILocation(line: 267, column: 12, scope: !577)
!577 = distinct !DILexicalBlock(scope: !570, file: !18, line: 266, column: 9)
!578 = !DILocation(line: 268, column: 21, scope: !577)
!579 = !DILocation(line: 270, column: 7, scope: !580)
!580 = distinct !DILexicalBlock(scope: !99, file: !18, line: 270, column: 6)
!581 = !DILocation(line: 270, column: 6, scope: !580)
!582 = !DILocation(line: 270, column: 17, scope: !580)
!583 = !DILocation(line: 270, column: 21, scope: !584)
!584 = !DILexicalBlockFile(scope: !580, file: !18, discriminator: 1)
!585 = !DILocation(line: 270, column: 33, scope: !584)
!586 = !DILocation(line: 270, column: 30, scope: !584)
!587 = !DILocation(line: 270, column: 6, scope: !584)
!588 = !DILocation(line: 271, column: 82, scope: !589)
!589 = distinct !DILexicalBlock(scope: !580, file: !18, line: 270, column: 61)
!590 = !DILocation(line: 271, column: 3, scope: !589)
!591 = !DILocation(line: 272, column: 85, scope: !589)
!592 = !DILocation(line: 272, column: 17, scope: !589)
!593 = !DILocation(line: 273, column: 3, scope: !589)
!594 = !DILocation(line: 279, column: 33, scope: !99)
!595 = !DILocation(line: 279, column: 24, scope: !540)
!596 = !DILocation(line: 279, column: 22, scope: !99)
!597 = !DILocation(line: 280, column: 13, scope: !598)
!598 = distinct !DILexicalBlock(scope: !99, file: !18, line: 280, column: 13)
!599 = !DILocation(line: 280, column: 26, scope: !598)
!600 = !DILocation(line: 280, column: 13, scope: !99)
!601 = !DILocation(line: 281, column: 23, scope: !598)
!602 = !DILocation(line: 281, column: 21, scope: !598)
!603 = !DILocation(line: 281, column: 12, scope: !598)
!604 = !DILocation(line: 284, column: 13, scope: !605)
!605 = distinct !DILexicalBlock(scope: !598, file: !18, line: 283, column: 9)
!606 = !DILocation(line: 285, column: 22, scope: !605)
!607 = !DILocation(line: 288, column: 15, scope: !608)
!608 = distinct !DILexicalBlock(scope: !99, file: !18, line: 288, column: 14)
!609 = !DILocation(line: 288, column: 14, scope: !608)
!610 = !DILocation(line: 288, column: 25, scope: !608)
!611 = !DILocation(line: 288, column: 29, scope: !612)
!612 = !DILexicalBlockFile(scope: !608, file: !18, discriminator: 1)
!613 = !DILocation(line: 288, column: 64, scope: !612)
!614 = !DILocation(line: 288, column: 41, scope: !612)
!615 = !DILocation(line: 288, column: 38, scope: !612)
!616 = !DILocation(line: 288, column: 14, scope: !612)
!617 = !DILocation(line: 290, column: 13, scope: !618)
!618 = distinct !DILexicalBlock(scope: !608, file: !18, line: 289, column: 9)
!619 = !DILocation(line: 291, column: 93, scope: !618)
!620 = !DILocation(line: 291, column: 103, scope: !618)
!621 = !DILocation(line: 291, column: 13, scope: !618)
!622 = !DILocation(line: 292, column: 13, scope: !618)
!623 = !DILocation(line: 296, column: 17, scope: !624)
!624 = distinct !DILexicalBlock(scope: !99, file: !18, line: 296, column: 14)
!625 = !DILocation(line: 296, column: 32, scope: !624)
!626 = !DILocation(line: 296, column: 37, scope: !627)
!627 = !DILexicalBlockFile(scope: !624, file: !18, discriminator: 1)
!628 = !DILocation(line: 296, column: 14, scope: !627)
!629 = !DILocation(line: 299, column: 9, scope: !630)
!630 = distinct !DILexicalBlock(scope: !631, file: !18, line: 299, column: 9)
!631 = distinct !DILexicalBlock(scope: !624, file: !18, line: 297, column: 9)
!632 = !DILocation(line: 299, column: 21, scope: !630)
!633 = !DILocation(line: 299, column: 24, scope: !634)
!634 = !DILexicalBlockFile(scope: !630, file: !18, discriminator: 1)
!635 = !DILocation(line: 299, column: 9, scope: !634)
!636 = !DILocation(line: 300, column: 3, scope: !637)
!637 = distinct !DILexicalBlock(scope: !630, file: !18, line: 299, column: 38)
!638 = !DILocation(line: 302, column: 17, scope: !637)
!639 = !DILocation(line: 305, column: 9, scope: !631)
!640 = !DILocation(line: 308, column: 17, scope: !641)
!641 = distinct !DILexicalBlock(scope: !99, file: !18, line: 308, column: 14)
!642 = !DILocation(line: 308, column: 32, scope: !641)
!643 = !DILocation(line: 308, column: 38, scope: !644)
!644 = !DILexicalBlockFile(scope: !641, file: !18, discriminator: 1)
!645 = !DILocation(line: 308, column: 14, scope: !644)
!646 = !DILocation(line: 311, column: 20, scope: !647)
!647 = distinct !DILexicalBlock(scope: !648, file: !18, line: 311, column: 10)
!648 = distinct !DILexicalBlock(scope: !641, file: !18, line: 309, column: 9)
!649 = !DILocation(line: 311, column: 10, scope: !647)
!650 = !DILocation(line: 311, column: 10, scope: !648)
!651 = !DILocation(line: 312, column: 3, scope: !647)
!652 = !DILocation(line: 314, column: 9, scope: !648)
!653 = !DILocation(line: 316, column: 26, scope: !654)
!654 = distinct !DILexicalBlock(scope: !99, file: !18, line: 316, column: 6)
!655 = !DILocation(line: 316, column: 6, scope: !656)
!656 = !DILexicalBlockFile(scope: !654, file: !18, discriminator: 1)
!657 = !DILocation(line: 316, column: 6, scope: !654)
!658 = !DILocation(line: 316, column: 6, scope: !99)
!659 = !DILocation(line: 317, column: 19, scope: !660)
!660 = distinct !DILexicalBlock(scope: !654, file: !18, line: 316, column: 62)
!661 = !DILocation(line: 317, column: 3, scope: !662)
!662 = !DILexicalBlockFile(scope: !660, file: !18, discriminator: 1)
!663 = !DILocation(line: 319, column: 2, scope: !660)
!664 = !DILocation(line: 322, column: 17, scope: !665)
!665 = distinct !DILexicalBlock(scope: !99, file: !18, line: 322, column: 14)
!666 = !DILocation(line: 322, column: 31, scope: !665)
!667 = !DILocation(line: 322, column: 37, scope: !668)
!668 = !DILexicalBlockFile(scope: !665, file: !18, discriminator: 1)
!669 = !DILocation(line: 322, column: 14, scope: !668)
!670 = !DILocation(line: 324, column: 14, scope: !671)
!671 = distinct !DILexicalBlock(scope: !665, file: !18, line: 323, column: 9)
!672 = !DILocation(line: 324, column: 19, scope: !671)
!673 = !DILocation(line: 324, column: 7, scope: !674)
!674 = !DILexicalBlockFile(scope: !671, file: !18, discriminator: 1)
!675 = !DILocation(line: 325, column: 12, scope: !676)
!676 = distinct !DILexicalBlock(scope: !671, file: !18, line: 325, column: 11)
!677 = !DILocation(line: 325, column: 11, scope: !671)
!678 = !DILocation(line: 326, column: 10, scope: !676)
!679 = !DILocation(line: 326, column: 3, scope: !676)
!680 = !DILocation(line: 327, column: 15, scope: !671)
!681 = !DILocation(line: 327, column: 35, scope: !671)
!682 = !DILocation(line: 327, column: 7, scope: !671)
!683 = !DILocation(line: 328, column: 15, scope: !671)
!684 = !DILocation(line: 328, column: 35, scope: !671)
!685 = !DILocation(line: 328, column: 7, scope: !671)
!686 = !DILocation(line: 329, column: 23, scope: !687)
!687 = distinct !DILexicalBlock(scope: !671, file: !18, line: 329, column: 11)
!688 = !DILocation(line: 329, column: 12, scope: !689)
!689 = !DILexicalBlockFile(scope: !687, file: !18, discriminator: 1)
!690 = !DILocation(line: 329, column: 12, scope: !687)
!691 = !DILocation(line: 329, column: 11, scope: !671)
!692 = !DILocation(line: 331, column: 16, scope: !693)
!693 = distinct !DILexicalBlock(scope: !687, file: !18, line: 330, column: 14)
!694 = !DILocation(line: 331, column: 14, scope: !693)
!695 = !DILocation(line: 332, column: 15, scope: !693)
!696 = !DILocation(line: 332, column: 13, scope: !693)
!697 = !DILocation(line: 333, column: 7, scope: !693)
!698 = !DILocation(line: 335, column: 18, scope: !671)
!699 = !DILocation(line: 335, column: 2, scope: !671)
!700 = !DILocation(line: 336, column: 22, scope: !671)
!701 = !DILocation(line: 336, column: 40, scope: !671)
!702 = !DILocation(line: 336, column: 2, scope: !671)
!703 = !DILocation(line: 337, column: 17, scope: !704)
!704 = distinct !DILexicalBlock(scope: !671, file: !18, line: 337, column: 6)
!705 = !DILocation(line: 337, column: 6, scope: !706)
!706 = !DILexicalBlockFile(scope: !704, file: !18, discriminator: 1)
!707 = !DILocation(line: 337, column: 6, scope: !704)
!708 = !DILocation(line: 337, column: 6, scope: !671)
!709 = !DILocation(line: 338, column: 14, scope: !710)
!710 = distinct !DILexicalBlock(scope: !711, file: !18, line: 338, column: 7)
!711 = distinct !DILexicalBlock(scope: !704, file: !18, line: 337, column: 55)
!712 = !DILocation(line: 338, column: 7, scope: !710)
!713 = !DILocation(line: 338, column: 7, scope: !711)
!714 = !DILocation(line: 340, column: 15, scope: !715)
!715 = distinct !DILexicalBlock(scope: !710, file: !18, line: 338, column: 20)
!716 = !DILocation(line: 340, column: 6, scope: !717)
!717 = !DILexicalBlockFile(scope: !715, file: !18, discriminator: 1)
!718 = !DILocation(line: 339, column: 4, scope: !715)
!719 = !DILocation(line: 341, column: 4, scope: !715)
!720 = !DILocation(line: 343, column: 29, scope: !721)
!721 = distinct !DILexicalBlock(scope: !711, file: !18, line: 343, column: 7)
!722 = !DILocation(line: 343, column: 7, scope: !721)
!723 = !DILocation(line: 343, column: 7, scope: !711)
!724 = !DILocation(line: 344, column: 4, scope: !725)
!725 = distinct !DILexicalBlock(scope: !721, file: !18, line: 343, column: 38)
!726 = !DILocation(line: 345, column: 4, scope: !725)
!727 = !DILocation(line: 347, column: 7, scope: !728)
!728 = distinct !DILexicalBlock(scope: !711, file: !18, line: 347, column: 7)
!729 = !DILocation(line: 347, column: 7, scope: !711)
!730 = !DILocation(line: 349, column: 16, scope: !731)
!731 = distinct !DILexicalBlock(scope: !728, file: !18, line: 347, column: 19)
!732 = !DILocation(line: 349, column: 7, scope: !733)
!733 = !DILexicalBlockFile(scope: !731, file: !18, discriminator: 1)
!734 = !DILocation(line: 348, column: 4, scope: !731)
!735 = !DILocation(line: 350, column: 4, scope: !731)
!736 = !DILocation(line: 352, column: 2, scope: !711)
!737 = !DILocation(line: 353, column: 29, scope: !738)
!738 = distinct !DILexicalBlock(scope: !739, file: !18, line: 353, column: 7)
!739 = distinct !DILexicalBlock(scope: !704, file: !18, line: 352, column: 9)
!740 = !DILocation(line: 353, column: 7, scope: !738)
!741 = !DILocation(line: 353, column: 7, scope: !739)
!742 = !DILocation(line: 354, column: 4, scope: !743)
!743 = distinct !DILexicalBlock(scope: !738, file: !18, line: 353, column: 38)
!744 = !DILocation(line: 355, column: 4, scope: !743)
!745 = !DILocation(line: 357, column: 13, scope: !746)
!746 = distinct !DILexicalBlock(scope: !739, file: !18, line: 357, column: 7)
!747 = !DILocation(line: 357, column: 7, scope: !746)
!748 = !DILocation(line: 357, column: 7, scope: !739)
!749 = !DILocation(line: 358, column: 75, scope: !750)
!750 = distinct !DILexicalBlock(scope: !746, file: !18, line: 357, column: 19)
!751 = !DILocation(line: 359, column: 16, scope: !750)
!752 = !DILocation(line: 359, column: 7, scope: !753)
!753 = !DILexicalBlockFile(scope: !750, file: !18, discriminator: 1)
!754 = !DILocation(line: 358, column: 4, scope: !750)
!755 = !DILocation(line: 360, column: 4, scope: !750)
!756 = !DILocation(line: 361, column: 3, scope: !750)
!757 = !DILocation(line: 364, column: 9, scope: !671)
!758 = !DILocation(line: 367, column: 22, scope: !759)
!759 = distinct !DILexicalBlock(scope: !665, file: !18, line: 367, column: 19)
!760 = !DILocation(line: 367, column: 36, scope: !759)
!761 = !DILocation(line: 367, column: 40, scope: !762)
!762 = !DILexicalBlockFile(scope: !759, file: !18, discriminator: 1)
!763 = !DILocation(line: 367, column: 39, scope: !762)
!764 = !DILocation(line: 367, column: 19, scope: !762)
!765 = !DILocation(line: 369, column: 18, scope: !766)
!766 = distinct !DILexicalBlock(scope: !759, file: !18, line: 368, column: 9)
!767 = !DILocation(line: 369, column: 23, scope: !766)
!768 = !DILocation(line: 369, column: 11, scope: !769)
!769 = !DILexicalBlockFile(scope: !766, file: !18, discriminator: 1)
!770 = !DILocation(line: 370, column: 17, scope: !771)
!771 = distinct !DILexicalBlock(scope: !766, file: !18, line: 370, column: 15)
!772 = !DILocation(line: 370, column: 15, scope: !766)
!773 = !DILocation(line: 371, column: 14, scope: !771)
!774 = !DILocation(line: 371, column: 21, scope: !771)
!775 = !DILocation(line: 372, column: 19, scope: !766)
!776 = !DILocation(line: 372, column: 30, scope: !766)
!777 = !DILocation(line: 372, column: 11, scope: !766)
!778 = !DILocation(line: 373, column: 19, scope: !766)
!779 = !DILocation(line: 373, column: 11, scope: !766)
!780 = !DILocation(line: 375, column: 28, scope: !781)
!781 = distinct !DILexicalBlock(scope: !766, file: !18, line: 375, column: 15)
!782 = !DILocation(line: 375, column: 17, scope: !783)
!783 = !DILexicalBlockFile(scope: !781, file: !18, discriminator: 1)
!784 = !DILocation(line: 375, column: 17, scope: !781)
!785 = !DILocation(line: 375, column: 15, scope: !766)
!786 = !DILocation(line: 377, column: 26, scope: !787)
!787 = distinct !DILexicalBlock(scope: !788, file: !18, line: 377, column: 19)
!788 = distinct !DILexicalBlock(scope: !781, file: !18, line: 376, column: 11)
!789 = !DILocation(line: 377, column: 19, scope: !787)
!790 = !DILocation(line: 377, column: 19, scope: !788)
!791 = !DILocation(line: 379, column: 18, scope: !792)
!792 = distinct !DILexicalBlock(scope: !787, file: !18, line: 378, column: 14)
!793 = !DILocation(line: 380, column: 18, scope: !792)
!794 = !DILocation(line: 382, column: 19, scope: !795)
!795 = distinct !DILexicalBlock(scope: !788, file: !18, line: 382, column: 19)
!796 = !DILocation(line: 382, column: 19, scope: !788)
!797 = !DILocation(line: 384, column: 18, scope: !798)
!798 = distinct !DILexicalBlock(scope: !795, file: !18, line: 383, column: 14)
!799 = !DILocation(line: 385, column: 18, scope: !798)
!800 = !DILocation(line: 387, column: 11, scope: !788)
!801 = !DILocation(line: 389, column: 9, scope: !766)
!802 = !DILocation(line: 393, column: 13, scope: !803)
!803 = distinct !DILexicalBlock(scope: !759, file: !18, line: 391, column: 9)
!804 = !DILocation(line: 393, column: 18, scope: !803)
!805 = !DILocation(line: 393, column: 6, scope: !806)
!806 = !DILexicalBlockFile(scope: !803, file: !18, discriminator: 1)
!807 = !DILocation(line: 394, column: 19, scope: !808)
!808 = distinct !DILexicalBlock(scope: !803, file: !18, line: 394, column: 17)
!809 = !DILocation(line: 394, column: 17, scope: !803)
!810 = !DILocation(line: 395, column: 24, scope: !808)
!811 = !DILocation(line: 395, column: 17, scope: !808)
!812 = !DILocation(line: 396, column: 14, scope: !803)
!813 = !DILocation(line: 396, column: 25, scope: !803)
!814 = !DILocation(line: 396, column: 6, scope: !803)
!815 = !DILocation(line: 397, column: 21, scope: !803)
!816 = !DILocation(line: 397, column: 13, scope: !803)
!817 = !DILocation(line: 400, column: 30, scope: !818)
!818 = distinct !DILexicalBlock(scope: !803, file: !18, line: 400, column: 17)
!819 = !DILocation(line: 400, column: 19, scope: !820)
!820 = !DILexicalBlockFile(scope: !818, file: !18, discriminator: 1)
!821 = !DILocation(line: 400, column: 19, scope: !818)
!822 = !DILocation(line: 400, column: 17, scope: !803)
!823 = !DILocation(line: 402, column: 29, scope: !824)
!824 = distinct !DILexicalBlock(scope: !825, file: !18, line: 402, column: 22)
!825 = distinct !DILexicalBlock(scope: !818, file: !18, line: 401, column: 13)
!826 = !DILocation(line: 402, column: 22, scope: !824)
!827 = !DILocation(line: 402, column: 22, scope: !825)
!828 = !DILocation(line: 404, column: 21, scope: !829)
!829 = distinct !DILexicalBlock(scope: !824, file: !18, line: 403, column: 17)
!830 = !DILocation(line: 405, column: 21, scope: !829)
!831 = !DILocation(line: 407, column: 22, scope: !832)
!832 = distinct !DILexicalBlock(scope: !825, file: !18, line: 407, column: 22)
!833 = !DILocation(line: 407, column: 22, scope: !825)
!834 = !DILocation(line: 409, column: 21, scope: !835)
!835 = distinct !DILexicalBlock(scope: !832, file: !18, line: 408, column: 17)
!836 = !DILocation(line: 410, column: 21, scope: !835)
!837 = !DILocation(line: 412, column: 13, scope: !825)
!838 = !DILocation(line: 416, column: 9, scope: !99)
!839 = !DILocation(line: 418, column: 16, scope: !99)
!840 = !DILocation(line: 418, column: 21, scope: !99)
!841 = !DILocation(line: 418, column: 9, scope: !540)
!842 = !DILocation(line: 420, column: 17, scope: !99)
!843 = !DILocation(line: 420, column: 28, scope: !99)
!844 = !DILocation(line: 420, column: 9, scope: !99)
!845 = !DILocation(line: 421, column: 17, scope: !99)
!846 = !DILocation(line: 421, column: 9, scope: !99)
!847 = !DILocation(line: 422, column: 25, scope: !99)
!848 = !DILocation(line: 422, column: 9, scope: !99)
!849 = !DILocation(line: 424, column: 2, scope: !99)
!850 = !DILocation(line: 426, column: 2, scope: !99)
!851 = !DILocation(line: 428, column: 9, scope: !99)
!852 = !DILocation(line: 429, column: 2, scope: !99)
!853 = !DILocation(line: 430, column: 13, scope: !854)
!854 = distinct !DILexicalBlock(scope: !99, file: !18, line: 430, column: 13)
!855 = !DILocation(line: 430, column: 13, scope: !99)
!856 = !DILocation(line: 431, column: 19, scope: !854)
!857 = !DILocation(line: 431, column: 13, scope: !858)
!858 = !DILexicalBlockFile(scope: !854, file: !18, discriminator: 1)
!859 = !DILocation(line: 431, column: 13, scope: !854)
!860 = !DILocation(line: 433, column: 8, scope: !99)
!861 = !DILocation(line: 434, column: 2, scope: !99)
!862 = !DILocation(line: 437, column: 15, scope: !863)
!863 = distinct !DILexicalBlock(scope: !99, file: !18, line: 437, column: 14)
!864 = !DILocation(line: 437, column: 14, scope: !863)
!865 = !DILocation(line: 437, column: 31, scope: !863)
!866 = !DILocation(line: 437, column: 43, scope: !867)
!867 = !DILexicalBlockFile(scope: !863, file: !18, discriminator: 1)
!868 = !DILocation(line: 437, column: 36, scope: !867)
!869 = !DILocation(line: 437, column: 14, scope: !867)
!870 = !DILocation(line: 438, column: 18, scope: !863)
!871 = !DILocation(line: 438, column: 13, scope: !863)
!872 = !DILocation(line: 440, column: 2, scope: !99)
!873 = !DILocation(line: 441, column: 1, scope: !99)
!874 = !DILocalVariable(name: "my_filename", arg: 1, scope: !109, file: !18, line: 602, type: !14)
!875 = !DILocation(line: 602, column: 33, scope: !109)
!876 = !DILocalVariable(name: "my_username", arg: 2, scope: !109, file: !18, line: 602, type: !14)
!877 = !DILocation(line: 602, column: 52, scope: !109)
!878 = !DILocalVariable(name: "my_password", arg: 3, scope: !109, file: !18, line: 602, type: !14)
!879 = !DILocation(line: 602, column: 71, scope: !109)
!880 = !DILocalVariable(name: "my_file", scope: !109, file: !18, line: 604, type: !21)
!881 = !DILocation(line: 604, column: 10, scope: !109)
!882 = !DILocalVariable(name: "found_user", scope: !109, file: !18, line: 605, type: !13)
!883 = !DILocation(line: 605, column: 8, scope: !109)
!884 = !DILocalVariable(name: "user", scope: !109, file: !18, line: 606, type: !885)
!885 = !DICompositeType(tag: DW_TAG_array_type, baseType: !15, size: 264, align: 8, elements: !886)
!886 = !{!887}
!887 = !DISubrange(count: 33)
!888 = !DILocation(line: 606, column: 9, scope: !109)
!889 = !DILocalVariable(name: "password", scope: !109, file: !18, line: 606, type: !885)
!890 = !DILocation(line: 606, column: 19, scope: !109)
!891 = !DILocalVariable(name: "group", scope: !109, file: !18, line: 606, type: !885)
!892 = !DILocation(line: 606, column: 33, scope: !109)
!893 = !DILocalVariable(name: "home_dir", scope: !109, file: !18, line: 606, type: !885)
!894 = !DILocation(line: 606, column: 44, scope: !109)
!895 = !DILocalVariable(name: "my_home_dir", scope: !109, file: !18, line: 607, type: !14)
!896 = !DILocation(line: 607, column: 10, scope: !109)
!897 = !DILocalVariable(name: "return_value", scope: !109, file: !18, line: 608, type: !13)
!898 = !DILocation(line: 608, column: 8, scope: !109)
!899 = !DILocation(line: 610, column: 20, scope: !109)
!900 = !DILocation(line: 610, column: 14, scope: !109)
!901 = !DILocation(line: 610, column: 12, scope: !109)
!902 = !DILocation(line: 611, column: 10, scope: !903)
!903 = distinct !DILexicalBlock(scope: !109, file: !18, line: 611, column: 8)
!904 = !DILocation(line: 611, column: 8, scope: !109)
!905 = !DILocation(line: 612, column: 7, scope: !903)
!906 = !DILocation(line: 614, column: 26, scope: !109)
!907 = !DILocation(line: 614, column: 58, scope: !109)
!908 = !DILocation(line: 614, column: 64, scope: !109)
!909 = !DILocation(line: 614, column: 74, scope: !109)
!910 = !DILocation(line: 614, column: 81, scope: !109)
!911 = !DILocation(line: 614, column: 19, scope: !109)
!912 = !DILocation(line: 614, column: 17, scope: !109)
!913 = !DILocation(line: 615, column: 17, scope: !914)
!914 = distinct !DILexicalBlock(scope: !109, file: !18, line: 615, column: 8)
!915 = !DILocation(line: 615, column: 23, scope: !914)
!916 = !DILocation(line: 615, column: 10, scope: !914)
!917 = !DILocation(line: 615, column: 8, scope: !109)
!918 = !DILocation(line: 616, column: 18, scope: !914)
!919 = !DILocation(line: 616, column: 7, scope: !914)
!920 = !DILocation(line: 618, column: 4, scope: !109)
!921 = !DILocation(line: 618, column: 15, scope: !922)
!922 = !DILexicalBlockFile(scope: !109, file: !18, discriminator: 1)
!923 = !DILocation(line: 618, column: 27, scope: !922)
!924 = !DILocation(line: 618, column: 32, scope: !925)
!925 = !DILexicalBlockFile(scope: !109, file: !18, discriminator: 2)
!926 = !DILocation(line: 618, column: 45, scope: !925)
!927 = !DILocation(line: 618, column: 4, scope: !928)
!928 = !DILexicalBlockFile(scope: !109, file: !18, discriminator: 3)
!929 = !DILocation(line: 620, column: 30, scope: !930)
!930 = distinct !DILexicalBlock(scope: !109, file: !18, line: 619, column: 4)
!931 = !DILocation(line: 620, column: 62, scope: !930)
!932 = !DILocation(line: 620, column: 68, scope: !930)
!933 = !DILocation(line: 620, column: 78, scope: !930)
!934 = !DILocation(line: 620, column: 85, scope: !930)
!935 = !DILocation(line: 620, column: 23, scope: !930)
!936 = !DILocation(line: 620, column: 21, scope: !930)
!937 = !DILocation(line: 621, column: 21, scope: !938)
!938 = distinct !DILexicalBlock(scope: !930, file: !18, line: 621, column: 12)
!939 = !DILocation(line: 621, column: 27, scope: !938)
!940 = !DILocation(line: 621, column: 14, scope: !938)
!941 = !DILocation(line: 621, column: 12, scope: !930)
!942 = !DILocation(line: 622, column: 22, scope: !938)
!943 = !DILocation(line: 622, column: 11, scope: !938)
!944 = !DILocation(line: 618, column: 4, scope: !945)
!945 = !DILexicalBlockFile(scope: !109, file: !18, discriminator: 4)
!946 = !DILocation(line: 625, column: 11, scope: !109)
!947 = !DILocation(line: 625, column: 4, scope: !109)
!948 = !DILocation(line: 626, column: 8, scope: !949)
!949 = distinct !DILexicalBlock(scope: !109, file: !18, line: 626, column: 8)
!950 = !DILocation(line: 626, column: 8, scope: !109)
!951 = !DILocation(line: 629, column: 20, scope: !952)
!952 = distinct !DILexicalBlock(scope: !953, file: !18, line: 629, column: 11)
!953 = distinct !DILexicalBlock(scope: !949, file: !18, line: 627, column: 4)
!954 = !DILocation(line: 629, column: 13, scope: !952)
!955 = !DILocation(line: 629, column: 11, scope: !953)
!956 = !DILocation(line: 631, column: 7, scope: !957)
!957 = distinct !DILexicalBlock(scope: !952, file: !18, line: 630, column: 7)
!958 = !DILocation(line: 632, column: 24, scope: !959)
!959 = distinct !DILexicalBlock(scope: !952, file: !18, line: 632, column: 17)
!960 = !DILocation(line: 632, column: 34, scope: !959)
!961 = !DILocation(line: 632, column: 17, scope: !959)
!962 = !DILocation(line: 632, column: 17, scope: !952)
!963 = !DILocation(line: 633, column: 10, scope: !959)
!964 = !DILocation(line: 635, column: 36, scope: !953)
!965 = !DILocation(line: 635, column: 29, scope: !953)
!966 = !DILocation(line: 635, column: 46, scope: !953)
!967 = !DILocation(line: 635, column: 21, scope: !968)
!968 = !DILexicalBlockFile(scope: !953, file: !18, discriminator: 1)
!969 = !DILocation(line: 635, column: 19, scope: !953)
!970 = !DILocation(line: 636, column: 13, scope: !971)
!971 = distinct !DILexicalBlock(scope: !953, file: !18, line: 636, column: 11)
!972 = !DILocation(line: 636, column: 11, scope: !953)
!973 = !DILocation(line: 637, column: 11, scope: !971)
!974 = !DILocation(line: 638, column: 14, scope: !953)
!975 = !DILocation(line: 638, column: 27, scope: !953)
!976 = !DILocation(line: 638, column: 7, scope: !953)
!977 = !DILocation(line: 639, column: 4, scope: !953)
!978 = !DILocation(line: 641, column: 11, scope: !109)
!979 = !DILocation(line: 641, column: 4, scope: !109)
!980 = !DILocation(line: 642, column: 1, scope: !109)
!981 = !DILocalVariable(name: "password", arg: 1, scope: !102, file: !18, line: 445, type: !14)
!982 = !DILocation(line: 445, column: 21, scope: !102)
!983 = !DILocation(line: 448, column: 10, scope: !984)
!984 = distinct !DILexicalBlock(scope: !102, file: !18, line: 448, column: 9)
!985 = !DILocation(line: 448, column: 9, scope: !102)
!986 = !DILocation(line: 449, column: 3, scope: !984)
!987 = !DILocation(line: 452, column: 18, scope: !988)
!988 = distinct !DILexicalBlock(scope: !102, file: !18, line: 452, column: 6)
!989 = !DILocation(line: 452, column: 7, scope: !990)
!990 = !DILexicalBlockFile(scope: !988, file: !18, discriminator: 1)
!991 = !DILocation(line: 452, column: 7, scope: !988)
!992 = !DILocation(line: 452, column: 6, scope: !102)
!993 = !DILocation(line: 453, column: 3, scope: !988)
!994 = !DILocation(line: 460, column: 24, scope: !102)
!995 = !DILocation(line: 460, column: 10, scope: !102)
!996 = !DILocation(line: 460, column: 3, scope: !102)
!997 = !DILocation(line: 461, column: 1, scope: !102)
!998 = !DILocalVariable(name: "password", arg: 1, scope: !104, file: !18, line: 476, type: !14)
!999 = !DILocation(line: 476, column: 25, scope: !104)
!1000 = !DILocalVariable(name: "shd", scope: !104, file: !18, line: 479, type: !1001)
!1001 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1002, size: 64, align: 64)
!1002 = !DICompositeType(tag: DW_TAG_structure_type, name: "spwd", file: !1003, line: 39, size: 576, align: 64, elements: !1004)
!1003 = !DIFile(filename: "/usr/include/shadow.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!1004 = !{!1005, !1006, !1007, !1008, !1009, !1010, !1011, !1012, !1013}
!1005 = !DIDerivedType(tag: DW_TAG_member, name: "sp_namp", scope: !1002, file: !1003, line: 41, baseType: !14, size: 64, align: 64)
!1006 = !DIDerivedType(tag: DW_TAG_member, name: "sp_pwdp", scope: !1002, file: !1003, line: 42, baseType: !14, size: 64, align: 64, offset: 64)
!1007 = !DIDerivedType(tag: DW_TAG_member, name: "sp_lstchg", scope: !1002, file: !1003, line: 43, baseType: !53, size: 64, align: 64, offset: 128)
!1008 = !DIDerivedType(tag: DW_TAG_member, name: "sp_min", scope: !1002, file: !1003, line: 44, baseType: !53, size: 64, align: 64, offset: 192)
!1009 = !DIDerivedType(tag: DW_TAG_member, name: "sp_max", scope: !1002, file: !1003, line: 45, baseType: !53, size: 64, align: 64, offset: 256)
!1010 = !DIDerivedType(tag: DW_TAG_member, name: "sp_warn", scope: !1002, file: !1003, line: 46, baseType: !53, size: 64, align: 64, offset: 320)
!1011 = !DIDerivedType(tag: DW_TAG_member, name: "sp_inact", scope: !1002, file: !1003, line: 48, baseType: !53, size: 64, align: 64, offset: 384)
!1012 = !DIDerivedType(tag: DW_TAG_member, name: "sp_expire", scope: !1002, file: !1003, line: 50, baseType: !53, size: 64, align: 64, offset: 448)
!1013 = !DIDerivedType(tag: DW_TAG_member, name: "sp_flag", scope: !1002, file: !1003, line: 52, baseType: !74, size: 64, align: 64, offset: 512)
!1014 = !DILocation(line: 479, column: 15, scope: !104)
!1015 = !DILocation(line: 481, column: 22, scope: !1016)
!1016 = distinct !DILexicalBlock(scope: !104, file: !18, line: 481, column: 6)
!1017 = !DILocation(line: 481, column: 48, scope: !1016)
!1018 = !DILocation(line: 481, column: 67, scope: !1016)
!1019 = !DILocation(line: 481, column: 42, scope: !1016)
!1020 = !DILocation(line: 481, column: 6, scope: !1021)
!1021 = !DILexicalBlockFile(scope: !1016, file: !18, discriminator: 1)
!1022 = !DILocation(line: 481, column: 6, scope: !1016)
!1023 = !DILocation(line: 481, column: 6, scope: !104)
!1024 = !DILocation(line: 483, column: 15, scope: !1025)
!1025 = distinct !DILexicalBlock(scope: !1026, file: !18, line: 483, column: 7)
!1026 = distinct !DILexicalBlock(scope: !1016, file: !18, line: 481, column: 80)
!1027 = !DILocation(line: 483, column: 13, scope: !1025)
!1028 = !DILocation(line: 483, column: 7, scope: !1026)
!1029 = !DILocation(line: 484, column: 4, scope: !1025)
!1030 = !DILocation(line: 485, column: 14, scope: !1031)
!1031 = distinct !DILexicalBlock(scope: !1026, file: !18, line: 485, column: 7)
!1032 = !DILocation(line: 485, column: 19, scope: !1031)
!1033 = !DILocation(line: 485, column: 43, scope: !1031)
!1034 = !DILocation(line: 485, column: 53, scope: !1031)
!1035 = !DILocation(line: 485, column: 58, scope: !1031)
!1036 = !DILocation(line: 485, column: 37, scope: !1031)
!1037 = !DILocation(line: 485, column: 7, scope: !1038)
!1038 = !DILexicalBlockFile(scope: !1031, file: !18, discriminator: 1)
!1039 = !DILocation(line: 485, column: 7, scope: !1031)
!1040 = !DILocation(line: 485, column: 7, scope: !1026)
!1041 = !DILocation(line: 487, column: 4, scope: !1031)
!1042 = !DILocation(line: 488, column: 2, scope: !1026)
!1043 = !DILocation(line: 489, column: 2, scope: !104)
!1044 = !DILocation(line: 490, column: 1, scope: !104)
!1045 = !DILocation(line: 472, column: 2, scope: !103)
!1046 = !DILocation(line: 474, column: 1, scope: !103)
!1047 = !DILocalVariable(name: "fd", scope: !105, file: !18, line: 544, type: !21)
!1048 = !DILocation(line: 544, column: 8, scope: !105)
!1049 = !DILocalVariable(name: "p", scope: !105, file: !18, line: 545, type: !14)
!1050 = !DILocation(line: 545, column: 8, scope: !105)
!1051 = !DILocalVariable(name: "line", scope: !105, file: !18, line: 546, type: !144)
!1052 = !DILocation(line: 546, column: 7, scope: !105)
!1053 = !DILocation(line: 548, column: 18, scope: !1054)
!1054 = distinct !DILexicalBlock(scope: !105, file: !18, line: 548, column: 6)
!1055 = !DILocation(line: 548, column: 12, scope: !1056)
!1056 = !DILexicalBlockFile(scope: !1054, file: !18, discriminator: 1)
!1057 = !DILocation(line: 548, column: 10, scope: !1054)
!1058 = !DILocation(line: 548, column: 6, scope: !105)
!1059 = !DILocation(line: 549, column: 3, scope: !1060)
!1060 = distinct !DILexicalBlock(scope: !1054, file: !18, line: 548, column: 60)
!1061 = !DILocation(line: 549, column: 16, scope: !1062)
!1062 = !DILexicalBlockFile(scope: !1060, file: !18, discriminator: 1)
!1063 = !DILocation(line: 549, column: 36, scope: !1062)
!1064 = !DILocation(line: 549, column: 10, scope: !1062)
!1065 = !DILocation(line: 549, column: 3, scope: !1062)
!1066 = !DILocation(line: 550, column: 20, scope: !1067)
!1067 = distinct !DILexicalBlock(scope: !1060, file: !18, line: 550, column: 8)
!1068 = !DILocation(line: 550, column: 13, scope: !1067)
!1069 = !DILocation(line: 550, column: 11, scope: !1067)
!1070 = !DILocation(line: 550, column: 8, scope: !1060)
!1071 = !DILocation(line: 551, column: 6, scope: !1072)
!1072 = distinct !DILexicalBlock(scope: !1067, file: !18, line: 550, column: 34)
!1073 = !DILocation(line: 551, column: 8, scope: !1072)
!1074 = !DILocation(line: 552, column: 9, scope: !1075)
!1075 = distinct !DILexicalBlock(scope: !1072, file: !18, line: 552, column: 9)
!1076 = !DILocation(line: 552, column: 17, scope: !1075)
!1077 = !DILocation(line: 552, column: 9, scope: !1072)
!1078 = !DILocation(line: 553, column: 6, scope: !1075)
!1079 = !DILocation(line: 554, column: 21, scope: !1080)
!1080 = distinct !DILexicalBlock(scope: !1072, file: !18, line: 554, column: 9)
!1081 = !DILocation(line: 554, column: 10, scope: !1080)
!1082 = !DILocation(line: 554, column: 9, scope: !1072)
!1083 = !DILocation(line: 555, column: 13, scope: !1084)
!1084 = distinct !DILexicalBlock(scope: !1080, file: !18, line: 554, column: 34)
!1085 = !DILocation(line: 555, column: 6, scope: !1084)
!1086 = !DILocation(line: 556, column: 6, scope: !1084)
!1087 = !DILocation(line: 558, column: 4, scope: !1072)
!1088 = !DILocation(line: 549, column: 3, scope: !1089)
!1089 = !DILexicalBlockFile(scope: !1060, file: !18, discriminator: 2)
!1090 = !DILocation(line: 559, column: 10, scope: !1060)
!1091 = !DILocation(line: 559, column: 3, scope: !1060)
!1092 = !DILocation(line: 560, column: 2, scope: !1060)
!1093 = !DILocation(line: 561, column: 2, scope: !105)
!1094 = !DILocation(line: 562, column: 1, scope: !105)
!1095 = !DILocalVariable(name: "cp", scope: !108, file: !18, line: 567, type: !14)
!1096 = !DILocation(line: 567, column: 8, scope: !108)
!1097 = !DILocalVariable(name: "pwd", scope: !108, file: !18, line: 568, type: !1098)
!1098 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !121, size: 64, align: 64)
!1099 = !DILocation(line: 568, column: 17, scope: !108)
!1100 = !DILocation(line: 570, column: 21, scope: !1101)
!1101 = distinct !DILexicalBlock(scope: !108, file: !18, line: 570, column: 9)
!1102 = !DILocation(line: 570, column: 10, scope: !1103)
!1103 = !DILexicalBlockFile(scope: !1101, file: !18, discriminator: 1)
!1104 = !DILocation(line: 570, column: 10, scope: !1101)
!1105 = !DILocation(line: 570, column: 9, scope: !108)
!1106 = !DILocation(line: 571, column: 9, scope: !1101)
!1107 = !DILocation(line: 573, column: 8, scope: !108)
!1108 = !DILocation(line: 573, column: 6, scope: !108)
!1109 = !DILocation(line: 574, column: 2, scope: !108)
!1110 = !DILocation(line: 574, column: 15, scope: !1111)
!1111 = !DILexicalBlockFile(scope: !108, file: !18, discriminator: 1)
!1112 = !DILocation(line: 574, column: 13, scope: !1111)
!1113 = !DILocation(line: 574, column: 2, scope: !1111)
!1114 = !DILocation(line: 575, column: 15, scope: !1115)
!1115 = distinct !DILexicalBlock(scope: !108, file: !18, line: 575, column: 7)
!1116 = !DILocation(line: 575, column: 19, scope: !1115)
!1117 = !DILocation(line: 575, column: 24, scope: !1115)
!1118 = !DILocation(line: 575, column: 8, scope: !1115)
!1119 = !DILocation(line: 575, column: 7, scope: !108)
!1120 = !DILocation(line: 576, column: 4, scope: !1115)
!1121 = !DILocation(line: 574, column: 2, scope: !1122)
!1122 = !DILexicalBlockFile(scope: !108, file: !18, discriminator: 2)
!1123 = !DILocation(line: 577, column: 2, scope: !108)
!1124 = !DILocation(line: 579, column: 7, scope: !1125)
!1125 = distinct !DILexicalBlock(scope: !108, file: !18, line: 579, column: 6)
!1126 = !DILocation(line: 579, column: 6, scope: !108)
!1127 = !DILocation(line: 580, column: 3, scope: !1125)
!1128 = !DILocation(line: 582, column: 3, scope: !1125)
!1129 = !DILocation(line: 588, column: 1, scope: !108)
