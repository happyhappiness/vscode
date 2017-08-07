; ModuleID = '/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/main.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.bftpd_list_element = type { i8*, %struct.bftpd_list_element* }
%struct.hostent = type { i8*, i8**, i32, i32, i8** }
%struct.sockaddr_in = type { i16, i16, %struct.in_addr, [8 x i8] }
%struct.in_addr = type { i32 }
%struct.bftpd_childpid = type { i32, i32 }
%struct.sockaddr = type { i16, [14 x i8] }

@isparent = global i32 1, align 4
@passwdfile = global %struct._IO_FILE* null, align 8
@groupfile = global %struct._IO_FILE* null, align 8
@alarm_type = global i32 0, align 4
@.str = private unnamed_addr constant [16 x i8] c"/etc/bftpd.conf\00", align 1
@configpath = global i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str, i32 0, i32 0), align 8
@daemonmode = global i32 0, align 4
@.str.1 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c"%i-%s\00", align 1
@.str.3 = private unnamed_addr constant [11 x i8] c"Quitting.\0A\00", align 1
@.str.4 = private unnamed_addr constant [5 x i8] c"quit\00", align 1
@sock = common global i32 0, align 4
@.str.5 = private unnamed_addr constant [44 x i8] c"Caught HUP signal. Re-reading config file.\0A\00", align 1
@child_list = common global %struct.bftpd_list_element* null, align 8
@.str.6 = private unnamed_addr constant [56 x i8] c"Kicked from the server due to data connection timeout.\0A\00", align 1
@.str.7 = private unnamed_addr constant [59 x i8] c"421 Kicked from the server due to data connection timeout.\00", align 1
@.str.8 = private unnamed_addr constant [59 x i8] c"Kicked from the server due to control connection timeout.\0A\00", align 1
@.str.9 = private unnamed_addr constant [62 x i8] c"421 Kicked from the server due to control connection timeout.\00", align 1
@main.he = internal global %struct.hostent* null, align 8
@my_argv_list = common global i8** null, align 8
@.str.10 = private unnamed_addr constant [8 x i8] c"c:hdDin\00", align 1
@.str.11 = private unnamed_addr constant [291 x i8] c"Usage: %s [-h] [-i|-d|-D] [-c <filename>|-n]\0A-h print this help\0A-i (default) run from inetd\0A-d daemon mode: fork() and run in TCP listen mode\0A-D run in TCP listen mode, but don't pre-fork()\0A-c read the config file named \22filename\22 instead of /etc/bftpd.conf\0A-n no config file, use defaults\0A\00", align 1
@optarg = external global i8*, align 8
@.str.12 = private unnamed_addr constant [2 x i8] c"/\00", align 1
@listensocket = common global i32 0, align 4
@.str.13 = private unnamed_addr constant [5 x i8] c"PORT\00", align 1
@.str.14 = private unnamed_addr constant [13 x i8] c"BIND_TO_ADDR\00", align 1
@.str.15 = private unnamed_addr constant [4 x i8] c"any\00", align 1
@stderr = external global %struct._IO_FILE*, align 8
@.str.16 = private unnamed_addr constant [17 x i8] c"Bind failed: %s\0A\00", align 1
@.str.17 = private unnamed_addr constant [19 x i8] c"Listen failed: %s\0A\00", align 1
@.str.18 = private unnamed_addr constant [10 x i8] c"/dev/null\00", align 1
@stdin = external global %struct._IO_FILE*, align 8
@.str.19 = private unnamed_addr constant [2 x i8] c"w\00", align 1
@devnull = common global %struct._IO_FILE* null, align 8
@global_argc = common global i32 0, align 4
@global_argv = common global i8** null, align 8
@.str.20 = private unnamed_addr constant [16 x i8] c"CONTROL_TIMEOUT\00", align 1
@control_timeout = common global i32 0, align 4
@.str.21 = private unnamed_addr constant [13 x i8] c"DATA_TIMEOUT\00", align 1
@data_timeout = common global i32 0, align 4
@.str.22 = private unnamed_addr constant [13 x i8] c"XFER_BUFSIZE\00", align 1
@xfer_bufsize = external global i32, align 4
@.str.23 = private unnamed_addr constant [17 x i8] c"PRE_WRITE_SCRIPT\00", align 1
@pre_write_script = common global i8* null, align 8
@.str.24 = private unnamed_addr constant [18 x i8] c"POST_WRITE_SCRIPT\00", align 1
@post_write_script = common global i8* null, align 8
@remotename = common global %struct.sockaddr_in zeroinitializer, align 4
@.str.25 = private unnamed_addr constant [44 x i8] c"421-Could not get peer IP address.\0D\0A421 %s.\00", align 1
@.str.26 = private unnamed_addr constant [18 x i8] c"RESOLVE_CLIENT_IP\00", align 1
@.str.27 = private unnamed_addr constant [4 x i8] c"yes\00", align 1
@remotehostname = common global i8* null, align 8
@.str.28 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.29 = private unnamed_addr constant [30 x i8] c"Incoming connection from %s.\0A\00", align 1
@.str.30 = private unnamed_addr constant [11 x i8] c"connect %s\00", align 1
@name = common global %struct.sockaddr_in zeroinitializer, align 4
@.str.31 = private unnamed_addr constant [12 x i8] c"MOTD_GLOBAL\00", align 1
@.str.32 = private unnamed_addr constant [13 x i8] c"HELLO_STRING\00", align 1
@.str.33 = private unnamed_addr constant [3 x i8] c"%v\00", align 1
@.str.34 = private unnamed_addr constant [4 x i8] c"3.2\00", align 1
@.str.35 = private unnamed_addr constant [3 x i8] c"%h\00", align 1
@.str.36 = private unnamed_addr constant [3 x i8] c"%i\00", align 1
@.str.37 = private unnamed_addr constant [7 x i8] c"220 %s\00", align 1
@.str.38 = private unnamed_addr constant [3 x i8] c"%s\00", align 1

; Function Attrs: nounwind uwtable
define void @print_file(i32 %number, i8* %filename) #0 !dbg !37 {
entry:
  %number.addr = alloca i32, align 4
  %filename.addr = alloca i8*, align 8
  %phile = alloca %struct._IO_FILE*, align 8
  %foo = alloca [512 x i8], align 16
  store i32 %number, i32* %number.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %number.addr, metadata !171, metadata !172), !dbg !173
  store i8* %filename, i8** %filename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filename.addr, metadata !174, metadata !172), !dbg !175
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %phile, metadata !176, metadata !172), !dbg !177
  call void @llvm.dbg.declare(metadata [512 x i8]* %foo, metadata !178, metadata !172), !dbg !182
  %0 = load i8*, i8** %filename.addr, align 8, !dbg !183
  %call = call %struct._IO_FILE* @fopen64(i8* %0, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.1, i32 0, i32 0)), !dbg !184
  store %struct._IO_FILE* %call, %struct._IO_FILE** %phile, align 8, !dbg !185
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** %phile, align 8, !dbg !186
  %tobool = icmp ne %struct._IO_FILE* %1, null, !dbg !186
  br i1 %tobool, label %if.then, label %if.end, !dbg !188

if.then:                                          ; preds = %entry
  br label %while.cond, !dbg !189

while.cond:                                       ; preds = %while.body, %if.then
  %arraydecay = getelementptr inbounds [512 x i8], [512 x i8]* %foo, i32 0, i32 0, !dbg !191
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** %phile, align 8, !dbg !193
  %call1 = call i8* @fgets(i8* %arraydecay, i32 512, %struct._IO_FILE* %2), !dbg !194
  %tobool2 = icmp ne i8* %call1, null, !dbg !195
  br i1 %tobool2, label %while.body, label %while.end, !dbg !195

while.body:                                       ; preds = %while.cond
  %arraydecay3 = getelementptr inbounds [512 x i8], [512 x i8]* %foo, i32 0, i32 0, !dbg !196
  %call4 = call i64 @strlen(i8* %arraydecay3) #8, !dbg !198
  %sub = sub i64 %call4, 1, !dbg !199
  %arrayidx = getelementptr inbounds [512 x i8], [512 x i8]* %foo, i64 0, i64 %sub, !dbg !200
  store i8 0, i8* %arrayidx, align 1, !dbg !201
  %3 = load i32, i32* %number.addr, align 4, !dbg !202
  %arraydecay5 = getelementptr inbounds [512 x i8], [512 x i8]* %foo, i32 0, i32 0, !dbg !203
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i32 0, i32 0), i32 %3, i8* %arraydecay5), !dbg !204
  br label %while.cond, !dbg !205

while.end:                                        ; preds = %while.cond
  %4 = load %struct._IO_FILE*, %struct._IO_FILE** %phile, align 8, !dbg !207
  %call6 = call i32 @fclose(%struct._IO_FILE* %4), !dbg !208
  br label %if.end, !dbg !209

if.end:                                           ; preds = %while.end, %entry
  ret void, !dbg !210
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare %struct._IO_FILE* @fopen64(i8*, i8*) #2

declare i8* @fgets(i8*, i32, %struct._IO_FILE*) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #3

declare void @control_printf(i8 signext, i8*, ...) #2

declare i32 @fclose(%struct._IO_FILE*) #2

; Function Attrs: nounwind uwtable
define void @end_child() #0 !dbg !43 {
entry:
  call void (...) @Force_Update_Sent_Recv_Log(), !dbg !211
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @passwdfile, align 8, !dbg !212
  %tobool = icmp ne %struct._IO_FILE* %0, null, !dbg !212
  br i1 %tobool, label %if.then, label %if.end, !dbg !214

if.then:                                          ; preds = %entry
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @passwdfile, align 8, !dbg !215
  %call = call i32 @fclose(%struct._IO_FILE* %1), !dbg !216
  br label %if.end, !dbg !216

if.end:                                           ; preds = %if.then, %entry
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** @groupfile, align 8, !dbg !217
  %tobool1 = icmp ne %struct._IO_FILE* %2, null, !dbg !217
  br i1 %tobool1, label %if.then2, label %if.end4, !dbg !219

if.then2:                                         ; preds = %if.end
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** @groupfile, align 8, !dbg !220
  %call3 = call i32 @fclose(%struct._IO_FILE* %3), !dbg !221
  br label %if.end4, !dbg !221

if.end4:                                          ; preds = %if.then2, %if.end
  call void (...) @config_end(), !dbg !222
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.3, i32 0, i32 0)), !dbg !223
  call void (i8, i8, i8*, ...) @bftpd_statuslog(i8 signext 1, i8 signext 0, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.4, i32 0, i32 0)), !dbg !224
  call void (...) @bftpdutmp_end(), !dbg !225
  call void (...) @log_end(), !dbg !226
  call void (...) @login_end(), !dbg !227
  call void (...) @bftpd_cwd_end(), !dbg !228
  %4 = load i32, i32* @daemonmode, align 4, !dbg !229
  %tobool5 = icmp ne i32 %4, 0, !dbg !229
  br i1 %tobool5, label %if.then6, label %if.end11, !dbg !231

if.then6:                                         ; preds = %if.end4
  %5 = load i32, i32* @sock, align 4, !dbg !232
  %call7 = call i32 @close(i32 %5), !dbg !234
  %call8 = call i32 @close(i32 0), !dbg !235
  %call9 = call i32 @close(i32 1), !dbg !236
  %call10 = call i32 @close(i32 2), !dbg !237
  br label %if.end11, !dbg !238

if.end11:                                         ; preds = %if.then6, %if.end4
  ret void, !dbg !239
}

declare void @Force_Update_Sent_Recv_Log(...) #2

declare void @config_end(...) #2

declare void @bftpd_log(i8*, ...) #2

declare void @bftpd_statuslog(i8 signext, i8 signext, i8*, ...) #2

declare void @bftpdutmp_end(...) #2

declare void @log_end(...) #2

declare void @login_end(...) #2

declare void @bftpd_cwd_end(...) #2

declare i32 @close(i32) #2

; Function Attrs: nounwind uwtable
define void @handler_sighup(i32 %sig) #0 !dbg !46 {
entry:
  %sig.addr = alloca i32, align 4
  store i32 %sig, i32* %sig.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sig.addr, metadata !240, metadata !172), !dbg !241
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.5, i32 0, i32 0)), !dbg !242
  call void (...) @Reread_Config_File(), !dbg !243
  %0 = load i32, i32* %sig.addr, align 4, !dbg !244
  %call = call void (i32)* @signal(i32 %0, void (i32)* @handler_sighup) #9, !dbg !245
  ret void, !dbg !246
}

declare void @Reread_Config_File(...) #2

; Function Attrs: nounwind
declare void (i32)* @signal(i32, void (i32)*) #4

; Function Attrs: nounwind uwtable
define void @handler_sigchld(i32 %sig) #0 !dbg !49 {
entry:
  %sig.addr = alloca i32, align 4
  %pid = alloca i32, align 4
  %i = alloca i32, align 4
  %childpid = alloca %struct.bftpd_childpid*, align 8
  store i32 %sig, i32* %sig.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sig.addr, metadata !247, metadata !172), !dbg !248
  call void @llvm.dbg.declare(metadata i32* %pid, metadata !249, metadata !172), !dbg !253
  call void @llvm.dbg.declare(metadata i32* %i, metadata !254, metadata !172), !dbg !255
  call void @llvm.dbg.declare(metadata %struct.bftpd_childpid** %childpid, metadata !256, metadata !172), !dbg !262
  %call = call i32 @waitpid(i32 -1, i32* null, i32 1), !dbg !263
  store i32 %call, i32* %pid, align 4, !dbg !264
  br label %while.cond, !dbg !265

while.cond:                                       ; preds = %for.end, %entry
  %0 = load i32, i32* %pid, align 4, !dbg !266
  %cmp = icmp sgt i32 %0, 0, !dbg !268
  br i1 %cmp, label %while.body, label %while.end, !dbg !269

while.body:                                       ; preds = %while.cond
  store i32 0, i32* %i, align 4, !dbg !270
  br label %for.cond, !dbg !273

for.cond:                                         ; preds = %for.inc, %while.body
  %1 = load i32, i32* %i, align 4, !dbg !274
  %2 = load %struct.bftpd_list_element*, %struct.bftpd_list_element** @child_list, align 8, !dbg !277
  %call1 = call i32 @bftpd_list_count(%struct.bftpd_list_element* %2), !dbg !278
  %cmp2 = icmp slt i32 %1, %call1, !dbg !279
  br i1 %cmp2, label %for.body, label %for.end, !dbg !280

for.body:                                         ; preds = %for.cond
  %3 = load %struct.bftpd_list_element*, %struct.bftpd_list_element** @child_list, align 8, !dbg !281
  %4 = load i32, i32* %i, align 4, !dbg !283
  %call3 = call i8* @bftpd_list_get(%struct.bftpd_list_element* %3, i32 %4), !dbg !284
  %5 = bitcast i8* %call3 to %struct.bftpd_childpid*, !dbg !284
  store %struct.bftpd_childpid* %5, %struct.bftpd_childpid** %childpid, align 8, !dbg !285
  %6 = load %struct.bftpd_childpid*, %struct.bftpd_childpid** %childpid, align 8, !dbg !286
  %tobool = icmp ne %struct.bftpd_childpid* %6, null, !dbg !288
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !289

land.lhs.true:                                    ; preds = %for.body
  %7 = load %struct.bftpd_childpid*, %struct.bftpd_childpid** %childpid, align 8, !dbg !290
  %pid4 = getelementptr inbounds %struct.bftpd_childpid, %struct.bftpd_childpid* %7, i32 0, i32 0, !dbg !292
  %8 = load i32, i32* %pid4, align 4, !dbg !292
  %9 = load i32, i32* %pid, align 4, !dbg !293
  %cmp5 = icmp eq i32 %8, %9, !dbg !294
  br i1 %cmp5, label %if.then, label %if.end, !dbg !295

if.then:                                          ; preds = %land.lhs.true
  %10 = load %struct.bftpd_childpid*, %struct.bftpd_childpid** %childpid, align 8, !dbg !296
  %sock = getelementptr inbounds %struct.bftpd_childpid, %struct.bftpd_childpid* %10, i32 0, i32 1, !dbg !298
  %11 = load i32, i32* %sock, align 4, !dbg !298
  %call6 = call i32 @close(i32 %11), !dbg !299
  %12 = load i32, i32* %i, align 4, !dbg !300
  call void @bftpd_list_del(%struct.bftpd_list_element** @child_list, i32 %12), !dbg !301
  %13 = load %struct.bftpd_childpid*, %struct.bftpd_childpid** %childpid, align 8, !dbg !302
  %14 = bitcast %struct.bftpd_childpid* %13 to i8*, !dbg !302
  call void @free(i8* %14) #9, !dbg !303
  %15 = load i32, i32* %pid, align 4, !dbg !304
  call void @bftpdutmp_remove_pid(i32 %15), !dbg !305
  br label %if.end, !dbg !306

if.end:                                           ; preds = %if.then, %land.lhs.true, %for.body
  br label %for.inc, !dbg !307

for.inc:                                          ; preds = %if.end
  %16 = load i32, i32* %i, align 4, !dbg !308
  %inc = add nsw i32 %16, 1, !dbg !308
  store i32 %inc, i32* %i, align 4, !dbg !308
  br label %for.cond, !dbg !310

for.end:                                          ; preds = %for.cond
  %call7 = call i32 @waitpid(i32 -1, i32* null, i32 1), !dbg !311
  store i32 %call7, i32* %pid, align 4, !dbg !312
  br label %while.cond, !dbg !313

while.end:                                        ; preds = %while.cond
  ret void, !dbg !315
}

declare i32 @waitpid(i32, i32*, i32) #2

declare i32 @bftpd_list_count(%struct.bftpd_list_element*) #2

declare i8* @bftpd_list_get(%struct.bftpd_list_element*, i32) #2

declare void @bftpd_list_del(%struct.bftpd_list_element**, i32) #2

; Function Attrs: nounwind
declare void @free(i8*) #4

declare void @bftpdutmp_remove_pid(i32) #2

; Function Attrs: nounwind uwtable
define void @handler_sigterm(i32 %signum) #0 !dbg !50 {
entry:
  %signum.addr = alloca i32, align 4
  store i32 %signum, i32* %signum.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %signum.addr, metadata !316, metadata !172), !dbg !317
  call void (...) @bftpdutmp_end(), !dbg !318
  call void @exit(i32 0) #10, !dbg !319
  unreachable, !dbg !319

return:                                           ; No predecessors!
  ret void, !dbg !320
}

; Function Attrs: noreturn nounwind
declare void @exit(i32) #5

; Function Attrs: nounwind uwtable
define void @handler_sigalrm(i32 %signum) #0 !dbg !51 {
entry:
  %signum.addr = alloca i32, align 4
  store i32 %signum, i32* %signum.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %signum.addr, metadata !321, metadata !172), !dbg !322
  call void (...) @bftpdutmp_end(), !dbg !323
  %0 = load i32, i32* @alarm_type, align 4, !dbg !324
  %tobool = icmp ne i32 %0, 0, !dbg !324
  br i1 %tobool, label %if.then, label %if.else, !dbg !326

if.then:                                          ; preds = %entry
  %1 = load i32, i32* @alarm_type, align 4, !dbg !327
  %call = call i32 @close(i32 %1), !dbg !329
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([56 x i8], [56 x i8]* @.str.6, i32 0, i32 0)), !dbg !330
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([59 x i8], [59 x i8]* @.str.7, i32 0, i32 0)), !dbg !331
  call void @exit(i32 0) #10, !dbg !332
  unreachable, !dbg !332

if.else:                                          ; preds = %entry
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([59 x i8], [59 x i8]* @.str.8, i32 0, i32 0)), !dbg !333
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([62 x i8], [62 x i8]* @.str.9, i32 0, i32 0)), !dbg !335
  call void @exit(i32 0) #10, !dbg !336
  unreachable, !dbg !336

return:                                           ; No predecessors!
  ret void, !dbg !337
}

; Function Attrs: nounwind uwtable
define void @init_everything() #0 !dbg !52 {
entry:
  %0 = load i32, i32* @daemonmode, align 4, !dbg !338
  %tobool = icmp ne i32 %0, 0, !dbg !338
  br i1 %tobool, label %if.end, label %if.then, !dbg !340

if.then:                                          ; preds = %entry
  call void (...) @config_init(), !dbg !341
  call void (...) @hidegroups_init(), !dbg !343
  br label %if.end, !dbg !344

if.end:                                           ; preds = %if.then, %entry
  call void (...) @log_init(), !dbg !345
  call void (...) @bftpdutmp_init(), !dbg !346
  call void (...) @login_init(), !dbg !347
  %call = call i32 (...) @Open_Send_Receive_Log(), !dbg !348
  ret void, !dbg !349
}

declare void @config_init(...) #2

declare void @hidegroups_init(...) #2

declare void @log_init(...) #2

declare void @bftpdutmp_init(...) #2

declare void @login_init(...) #2

declare i32 @Open_Send_Receive_Log(...) #2

; Function Attrs: nounwind uwtable
define i32 @main(i32 %argc, i8** %argv) #0 !dbg !53 {
entry:
  %retval = alloca i32, align 4
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  %str = alloca [513 x i8], align 16
  %i = alloca i32, align 4
  %port = alloca i32, align 4
  %retval1 = alloca i32, align 4
  %get_value = alloca i64, align 8
  %my_length = alloca i32, align 4
  %temp_string = alloca i8*, align 8
  %myaddr = alloca %struct.sockaddr_in, align 4
  %new = alloca %struct.sockaddr_in, align 4
  %pid = alloca i32, align 4
  %tmp_pid = alloca %struct.bftpd_childpid*, align 8
  store i32 0, i32* %retval, align 4
  store i32 %argc, i32* %argc.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %argc.addr, metadata !350, metadata !172), !dbg !351
  store i8** %argv, i8*** %argv.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %argv.addr, metadata !352, metadata !172), !dbg !353
  call void @llvm.dbg.declare(metadata [513 x i8]* %str, metadata !354, metadata !172), !dbg !358
  call void @llvm.dbg.declare(metadata i32* %i, metadata !359, metadata !172), !dbg !360
  store i32 1, i32* %i, align 4, !dbg !360
  call void @llvm.dbg.declare(metadata i32* %port, metadata !361, metadata !172), !dbg !362
  call void @llvm.dbg.declare(metadata i32* %retval1, metadata !363, metadata !172), !dbg !364
  call void @llvm.dbg.declare(metadata i64* %get_value, metadata !365, metadata !172), !dbg !366
  call void @llvm.dbg.declare(metadata i32* %my_length, metadata !367, metadata !172), !dbg !370
  call void @llvm.dbg.declare(metadata i8** %temp_string, metadata !371, metadata !172), !dbg !372
  store i8* null, i8** %temp_string, align 8, !dbg !372
  %0 = load i8**, i8*** %argv.addr, align 8, !dbg !373
  store i8** %0, i8*** @my_argv_list, align 8, !dbg !374
  %call = call void (i32)* @signal(i32 1, void (i32)* @handler_sighup) #9, !dbg !375
  br label %while.cond, !dbg !376

while.cond:                                       ; preds = %sw.epilog, %entry
  %1 = load i32, i32* %argc.addr, align 4, !dbg !377
  %2 = load i8**, i8*** %argv.addr, align 8, !dbg !379
  %call2 = call i32 @getopt(i32 %1, i8** %2, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.10, i32 0, i32 0)) #9, !dbg !380
  store i32 %call2, i32* %retval1, align 4, !dbg !381
  %cmp = icmp sgt i32 %call2, -1, !dbg !382
  br i1 %cmp, label %while.body, label %while.end, !dbg !383

while.body:                                       ; preds = %while.cond
  %3 = load i32, i32* %retval1, align 4, !dbg !384
  switch i32 %3, label %sw.epilog [
    i32 104, label %sw.bb
    i32 105, label %sw.bb4
    i32 100, label %sw.bb5
    i32 68, label %sw.bb6
    i32 99, label %sw.bb7
    i32 110, label %sw.bb9
  ], !dbg !386

sw.bb:                                            ; preds = %while.body
  %4 = load i8**, i8*** %argv.addr, align 8, !dbg !387
  %arrayidx = getelementptr inbounds i8*, i8** %4, i64 0, !dbg !387
  %5 = load i8*, i8** %arrayidx, align 8, !dbg !387
  %call3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([291 x i8], [291 x i8]* @.str.11, i32 0, i32 0), i8* %5), !dbg !389
  store i32 0, i32* %retval, align 4, !dbg !390
  br label %return, !dbg !390

sw.bb4:                                           ; preds = %while.body
  store i32 0, i32* @daemonmode, align 4, !dbg !391
  br label %sw.epilog, !dbg !392

sw.bb5:                                           ; preds = %while.body
  store i32 1, i32* @daemonmode, align 4, !dbg !393
  br label %sw.epilog, !dbg !394

sw.bb6:                                           ; preds = %while.body
  store i32 2, i32* @daemonmode, align 4, !dbg !395
  br label %sw.epilog, !dbg !396

sw.bb7:                                           ; preds = %while.body
  %6 = load i8*, i8** @optarg, align 8, !dbg !397
  %call8 = call noalias i8* @strdup(i8* %6) #9, !dbg !398
  store i8* %call8, i8** @configpath, align 8, !dbg !399
  br label %sw.epilog, !dbg !400

sw.bb9:                                           ; preds = %while.body
  store i8* null, i8** @configpath, align 8, !dbg !401
  br label %sw.epilog, !dbg !402

sw.epilog:                                        ; preds = %while.body, %sw.bb9, %sw.bb7, %sw.bb6, %sw.bb5, %sw.bb4
  br label %while.cond, !dbg !403

while.end:                                        ; preds = %while.cond
  %7 = load i32, i32* @daemonmode, align 4, !dbg !405
  %tobool = icmp ne i32 %7, 0, !dbg !405
  br i1 %tobool, label %if.then, label %if.end91, !dbg !407

if.then:                                          ; preds = %while.end
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in* %myaddr, metadata !408, metadata !172), !dbg !410
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in* %new, metadata !411, metadata !172), !dbg !412
  %8 = load i32, i32* @daemonmode, align 4, !dbg !413
  %cmp10 = icmp eq i32 %8, 1, !dbg !415
  br i1 %cmp10, label %if.then11, label %if.end20, !dbg !416

if.then11:                                        ; preds = %if.then
  %call12 = call i32 @fork() #9, !dbg !417
  %tobool13 = icmp ne i32 %call12, 0, !dbg !417
  br i1 %tobool13, label %if.then14, label %if.end, !dbg !420

if.then14:                                        ; preds = %if.then11
  call void @exit(i32 0) #10, !dbg !421
  unreachable, !dbg !421

if.end:                                           ; preds = %if.then11
  %call15 = call i32 @setsid() #9, !dbg !422
  %call16 = call i32 @fork() #9, !dbg !423
  %tobool17 = icmp ne i32 %call16, 0, !dbg !423
  br i1 %tobool17, label %if.then18, label %if.end19, !dbg !425

if.then18:                                        ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !426
  br label %return, !dbg !426

if.end19:                                         ; preds = %if.end
  br label %if.end20, !dbg !427

if.end20:                                         ; preds = %if.end19, %if.then
  %call21 = call void (i32)* @signal(i32 17, void (i32)* @handler_sigchld) #9, !dbg !428
  call void (...) @config_init(), !dbg !429
  %call22 = call i32 @chdir(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.12, i32 0, i32 0)) #9, !dbg !430
  call void (...) @hidegroups_init(), !dbg !431
  %call23 = call i32 @socket(i32 2, i32 1, i32 0) #9, !dbg !432
  store i32 %call23, i32* @listensocket, align 4, !dbg !433
  %9 = load i32, i32* @listensocket, align 4, !dbg !434
  %10 = bitcast i32* %i to i8*, !dbg !435
  %call24 = call i32 @setsockopt(i32 %9, i32 1, i32 2, i8* %10, i32 4) #9, !dbg !436
  %11 = load i32, i32* @listensocket, align 4, !dbg !437
  %12 = bitcast i32* %i to i8*, !dbg !438
  %call25 = call i32 @setsockopt(i32 %11, i32 1, i32 15, i8* %12, i32 4) #9, !dbg !439
  %13 = bitcast %struct.sockaddr_in* %myaddr to i8*, !dbg !440
  call void @llvm.memset.p0i8.i64(i8* %13, i8 0, i64 16, i32 4, i1 false), !dbg !440
  %call26 = call i8* @config_getoption(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.13, i32 0, i32 0)), !dbg !441
  %call27 = call i64 @strtoul(i8* %call26, i8** null, i32 10) #9, !dbg !443
  %conv = trunc i64 %call27 to i32, !dbg !445
  store i32 %conv, i32* %port, align 4, !dbg !446
  %tobool28 = icmp ne i32 %conv, 0, !dbg !446
  br i1 %tobool28, label %if.end30, label %if.then29, !dbg !447

if.then29:                                        ; preds = %if.end20
  store i32 21, i32* %port, align 4, !dbg !448
  br label %if.end30, !dbg !449

if.end30:                                         ; preds = %if.then29, %if.end20
  %14 = load i32, i32* %port, align 4, !dbg !450
  %conv31 = trunc i32 %14 to i16, !dbg !450
  %call32 = call zeroext i16 @htons(i16 zeroext %conv31) #1, !dbg !451
  %sin_port = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %myaddr, i32 0, i32 1, !dbg !452
  store i16 %call32, i16* %sin_port, align 2, !dbg !453
  %call33 = call i8* @config_getoption(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.14, i32 0, i32 0)), !dbg !454
  %call34 = call i32 @strcasecmp(i8* %call33, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.15, i32 0, i32 0)) #8, !dbg !456
  %tobool35 = icmp ne i32 %call34, 0, !dbg !458
  br i1 %tobool35, label %lor.lhs.false, label %if.then39, !dbg !459

lor.lhs.false:                                    ; preds = %if.end30
  %call36 = call i8* @config_getoption(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.14, i32 0, i32 0)), !dbg !460
  %arrayidx37 = getelementptr inbounds i8, i8* %call36, i64 0, !dbg !460
  %15 = load i8, i8* %arrayidx37, align 1, !dbg !460
  %tobool38 = icmp ne i8 %15, 0, !dbg !460
  br i1 %tobool38, label %if.else, label %if.then39, !dbg !462

if.then39:                                        ; preds = %lor.lhs.false, %if.end30
  %sin_addr = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %myaddr, i32 0, i32 2, !dbg !464
  %s_addr = getelementptr inbounds %struct.in_addr, %struct.in_addr* %sin_addr, i32 0, i32 0, !dbg !465
  store i32 0, i32* %s_addr, align 4, !dbg !466
  br label %if.end44, !dbg !467

if.else:                                          ; preds = %lor.lhs.false
  %call40 = call i8* @config_getoption(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.14, i32 0, i32 0)), !dbg !468
  %call41 = call i32 @inet_addr(i8* %call40) #9, !dbg !469
  %sin_addr42 = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %myaddr, i32 0, i32 2, !dbg !470
  %s_addr43 = getelementptr inbounds %struct.in_addr, %struct.in_addr* %sin_addr42, i32 0, i32 0, !dbg !471
  store i32 %call41, i32* %s_addr43, align 4, !dbg !472
  br label %if.end44

if.end44:                                         ; preds = %if.else, %if.then39
  %16 = load i32, i32* @listensocket, align 4, !dbg !473
  %17 = bitcast %struct.sockaddr_in* %myaddr to %struct.sockaddr*, !dbg !475
  %call45 = call i32 @bind(i32 %16, %struct.sockaddr* %17, i32 16) #9, !dbg !476
  %cmp46 = icmp slt i32 %call45, 0, !dbg !477
  br i1 %cmp46, label %if.then48, label %if.end52, !dbg !478

if.then48:                                        ; preds = %if.end44
  %18 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !479
  %call49 = call i32* @__errno_location() #1, !dbg !481
  %19 = load i32, i32* %call49, align 4, !dbg !481
  %call50 = call i8* @strerror(i32 %19) #9, !dbg !482
  %call51 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %18, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.16, i32 0, i32 0), i8* %call50), !dbg !484
  call void @exit(i32 1) #10, !dbg !486
  unreachable, !dbg !486

if.end52:                                         ; preds = %if.end44
  %20 = load i32, i32* @listensocket, align 4, !dbg !487
  %call53 = call i32 @listen(i32 %20, i32 5) #9, !dbg !489
  %tobool54 = icmp ne i32 %call53, 0, !dbg !489
  br i1 %tobool54, label %if.then55, label %if.end59, !dbg !490

if.then55:                                        ; preds = %if.end52
  %21 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !491
  %call56 = call i32* @__errno_location() #1, !dbg !493
  %22 = load i32, i32* %call56, align 4, !dbg !493
  %call57 = call i8* @strerror(i32 %22) #9, !dbg !494
  %call58 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %21, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.17, i32 0, i32 0), i8* %call57), !dbg !496
  call void @exit(i32 1) #10, !dbg !498
  unreachable, !dbg !498

if.end59:                                         ; preds = %if.end52
  %23 = load i32, i32* @listensocket, align 4, !dbg !499
  %cmp60 = icmp sge i32 %23, 3, !dbg !501
  br i1 %cmp60, label %if.then62, label %if.end67, !dbg !502

if.then62:                                        ; preds = %if.end59
  store i32 0, i32* %i, align 4, !dbg !503
  br label %for.cond, !dbg !506

for.cond:                                         ; preds = %for.inc, %if.then62
  %24 = load i32, i32* %i, align 4, !dbg !507
  %cmp63 = icmp slt i32 %24, 3, !dbg !510
  br i1 %cmp63, label %for.body, label %for.end, !dbg !511

for.body:                                         ; preds = %for.cond
  %25 = load i32, i32* %i, align 4, !dbg !512
  %call65 = call i32 @close(i32 %25), !dbg !514
  %call66 = call i32 (i8*, i32, ...) @open64(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.18, i32 0, i32 0), i32 2), !dbg !515
  br label %for.inc, !dbg !516

for.inc:                                          ; preds = %for.body
  %26 = load i32, i32* %i, align 4, !dbg !517
  %inc = add nsw i32 %26, 1, !dbg !517
  store i32 %inc, i32* %i, align 4, !dbg !517
  br label %for.cond, !dbg !519

for.end:                                          ; preds = %for.cond
  br label %if.end67, !dbg !520

if.end67:                                         ; preds = %for.end, %if.end59
  store i32 16, i32* %my_length, align 4, !dbg !521
  br label %while.cond68, !dbg !522

while.cond68:                                     ; preds = %if.end89, %if.end67
  %27 = load i32, i32* @listensocket, align 4, !dbg !523
  %28 = bitcast %struct.sockaddr_in* %new to %struct.sockaddr*, !dbg !524
  %call69 = call i32 @accept(i32 %27, %struct.sockaddr* %28, i32* %my_length), !dbg !525
  store i32 %call69, i32* @sock, align 4, !dbg !526
  %tobool70 = icmp ne i32 %call69, 0, !dbg !527
  br i1 %tobool70, label %while.body71, label %while.end90, !dbg !527

while.body71:                                     ; preds = %while.cond68
  call void @llvm.dbg.declare(metadata i32* %pid, metadata !528, metadata !172), !dbg !530
  %29 = load i32, i32* @sock, align 4, !dbg !531
  %cmp72 = icmp sgt i32 %29, 0, !dbg !533
  br i1 %cmp72, label %if.then74, label %if.end89, !dbg !534

if.then74:                                        ; preds = %while.body71
  %call75 = call i32 @fork() #9, !dbg !535
  store i32 %call75, i32* %pid, align 4, !dbg !537
  %30 = load i32, i32* %pid, align 4, !dbg !538
  %tobool76 = icmp ne i32 %30, 0, !dbg !538
  br i1 %tobool76, label %if.else85, label %if.then77, !dbg !540

if.then77:                                        ; preds = %if.then74
  %call78 = call i32 @close(i32 0), !dbg !541
  %call79 = call i32 @close(i32 1), !dbg !543
  %call80 = call i32 @close(i32 2), !dbg !544
  store i32 0, i32* @isparent, align 4, !dbg !545
  %31 = load i32, i32* @sock, align 4, !dbg !546
  %32 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !547
  %call81 = call i32 @fileno(%struct._IO_FILE* %32) #9, !dbg !548
  %call82 = call i32 @dup2(i32 %31, i32 %call81) #9, !dbg !549
  %33 = load i32, i32* @sock, align 4, !dbg !551
  %34 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !552
  %call83 = call i32 @fileno(%struct._IO_FILE* %34) #9, !dbg !553
  %call84 = call i32 @dup2(i32 %33, i32 %call83) #9, !dbg !554
  br label %while.end90, !dbg !555

if.else85:                                        ; preds = %if.then74
  call void @llvm.dbg.declare(metadata %struct.bftpd_childpid** %tmp_pid, metadata !556, metadata !172), !dbg !558
  %call86 = call noalias i8* @malloc(i64 8) #9, !dbg !559
  %35 = bitcast i8* %call86 to %struct.bftpd_childpid*, !dbg !559
  store %struct.bftpd_childpid* %35, %struct.bftpd_childpid** %tmp_pid, align 8, !dbg !558
  %36 = load i32, i32* %pid, align 4, !dbg !560
  %37 = load %struct.bftpd_childpid*, %struct.bftpd_childpid** %tmp_pid, align 8, !dbg !561
  %pid87 = getelementptr inbounds %struct.bftpd_childpid, %struct.bftpd_childpid* %37, i32 0, i32 0, !dbg !562
  store i32 %36, i32* %pid87, align 4, !dbg !563
  %38 = load i32, i32* @sock, align 4, !dbg !564
  %39 = load %struct.bftpd_childpid*, %struct.bftpd_childpid** %tmp_pid, align 8, !dbg !565
  %sock = getelementptr inbounds %struct.bftpd_childpid, %struct.bftpd_childpid* %39, i32 0, i32 1, !dbg !566
  store i32 %38, i32* %sock, align 4, !dbg !567
  %40 = load %struct.bftpd_childpid*, %struct.bftpd_childpid** %tmp_pid, align 8, !dbg !568
  %41 = bitcast %struct.bftpd_childpid* %40 to i8*, !dbg !568
  call void @bftpd_list_add(%struct.bftpd_list_element** @child_list, i8* %41), !dbg !569
  br label %if.end88

if.end88:                                         ; preds = %if.else85
  br label %if.end89, !dbg !570

if.end89:                                         ; preds = %if.end88, %while.body71
  br label %while.cond68, !dbg !571

while.end90:                                      ; preds = %if.then77, %while.cond68
  br label %if.end91, !dbg !573

if.end91:                                         ; preds = %while.end90, %while.end
  %call92 = call %struct._IO_FILE* @fopen64(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.18, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i32 0, i32 0)), !dbg !574
  store %struct._IO_FILE* %call92, %struct._IO_FILE** @devnull, align 8, !dbg !575
  %42 = load i32, i32* %argc.addr, align 4, !dbg !576
  store i32 %42, i32* @global_argc, align 4, !dbg !577
  %43 = load i8**, i8*** %argv.addr, align 8, !dbg !578
  store i8** %43, i8*** @global_argv, align 8, !dbg !579
  call void @init_everything(), !dbg !580
  %call93 = call i32 @atexit(void ()* @end_child) #9, !dbg !581
  %call94 = call void (i32)* @signal(i32 15, void (i32)* @handler_sigterm) #9, !dbg !582
  %call95 = call void (i32)* @signal(i32 14, void (i32)* @handler_sigalrm) #9, !dbg !583
  %call96 = call i8* @config_getoption(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.20, i32 0, i32 0)), !dbg !584
  %call97 = call i64 @strtoul(i8* %call96, i8** null, i32 0) #9, !dbg !585
  store i64 %call97, i64* %get_value, align 8, !dbg !586
  %44 = load i64, i64* %get_value, align 8, !dbg !587
  %cmp98 = icmp ule i64 %44, 2147483647, !dbg !589
  br i1 %cmp98, label %if.then100, label %if.else102, !dbg !590

if.then100:                                       ; preds = %if.end91
  %45 = load i64, i64* %get_value, align 8, !dbg !591
  %conv101 = trunc i64 %45 to i32, !dbg !591
  store i32 %conv101, i32* @control_timeout, align 4, !dbg !592
  br label %if.end103, !dbg !593

if.else102:                                       ; preds = %if.end91
  store i32 0, i32* @control_timeout, align 4, !dbg !594
  br label %if.end103

if.end103:                                        ; preds = %if.else102, %if.then100
  %46 = load i32, i32* @control_timeout, align 4, !dbg !595
  %tobool104 = icmp ne i32 %46, 0, !dbg !595
  br i1 %tobool104, label %if.end106, label %if.then105, !dbg !597

if.then105:                                       ; preds = %if.end103
  store i32 300, i32* @control_timeout, align 4, !dbg !598
  br label %if.end106, !dbg !599

if.end106:                                        ; preds = %if.then105, %if.end103
  %call107 = call i8* @config_getoption(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.21, i32 0, i32 0)), !dbg !600
  %call108 = call i64 @strtoul(i8* %call107, i8** null, i32 0) #9, !dbg !601
  store i64 %call108, i64* %get_value, align 8, !dbg !602
  %47 = load i64, i64* %get_value, align 8, !dbg !603
  %cmp109 = icmp ule i64 %47, 2147483647, !dbg !605
  br i1 %cmp109, label %if.then111, label %if.else113, !dbg !606

if.then111:                                       ; preds = %if.end106
  %48 = load i64, i64* %get_value, align 8, !dbg !607
  %conv112 = trunc i64 %48 to i32, !dbg !607
  store i32 %conv112, i32* @data_timeout, align 4, !dbg !608
  br label %if.end114, !dbg !609

if.else113:                                       ; preds = %if.end106
  store i32 0, i32* @data_timeout, align 4, !dbg !610
  br label %if.end114

if.end114:                                        ; preds = %if.else113, %if.then111
  %49 = load i32, i32* @data_timeout, align 4, !dbg !611
  %tobool115 = icmp ne i32 %49, 0, !dbg !611
  br i1 %tobool115, label %if.end117, label %if.then116, !dbg !613

if.then116:                                       ; preds = %if.end114
  store i32 300, i32* @data_timeout, align 4, !dbg !614
  br label %if.end117, !dbg !615

if.end117:                                        ; preds = %if.then116, %if.end114
  %call118 = call i8* @config_getoption(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.22, i32 0, i32 0)), !dbg !616
  %call119 = call i64 @strtoul(i8* %call118, i8** null, i32 0) #9, !dbg !617
  store i64 %call119, i64* %get_value, align 8, !dbg !618
  %50 = load i64, i64* %get_value, align 8, !dbg !619
  %cmp120 = icmp ule i64 %50, 2147483647, !dbg !621
  br i1 %cmp120, label %if.then122, label %if.else124, !dbg !622

if.then122:                                       ; preds = %if.end117
  %51 = load i64, i64* %get_value, align 8, !dbg !623
  %conv123 = trunc i64 %51 to i32, !dbg !623
  store i32 %conv123, i32* @xfer_bufsize, align 4, !dbg !624
  br label %if.end125, !dbg !625

if.else124:                                       ; preds = %if.end117
  store i32 9, i32* @xfer_bufsize, align 4, !dbg !626
  br label %if.end125

if.end125:                                        ; preds = %if.else124, %if.then122
  %52 = load i32, i32* @xfer_bufsize, align 4, !dbg !627
  %cmp126 = icmp sle i32 %52, 0, !dbg !629
  br i1 %cmp126, label %if.then131, label %lor.lhs.false128, !dbg !630

lor.lhs.false128:                                 ; preds = %if.end125
  %53 = load i32, i32* @xfer_bufsize, align 4, !dbg !631
  %cmp129 = icmp sgt i32 %53, 1000000, !dbg !633
  br i1 %cmp129, label %if.then131, label %if.end132, !dbg !634

if.then131:                                       ; preds = %lor.lhs.false128, %if.end125
  store i32 4096, i32* @xfer_bufsize, align 4, !dbg !635
  br label %if.end132, !dbg !636

if.end132:                                        ; preds = %if.then131, %lor.lhs.false128
  %call133 = call i8* @config_getoption(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.23, i32 0, i32 0)), !dbg !637
  store i8* %call133, i8** @pre_write_script, align 8, !dbg !638
  %54 = load i8*, i8** @pre_write_script, align 8, !dbg !639
  %arrayidx134 = getelementptr inbounds i8, i8* %54, i64 0, !dbg !639
  %55 = load i8, i8* %arrayidx134, align 1, !dbg !639
  %tobool135 = icmp ne i8 %55, 0, !dbg !639
  br i1 %tobool135, label %if.end137, label %if.then136, !dbg !641

if.then136:                                       ; preds = %if.end132
  store i8* null, i8** @pre_write_script, align 8, !dbg !642
  br label %if.end137, !dbg !643

if.end137:                                        ; preds = %if.then136, %if.end132
  %call138 = call i8* @config_getoption(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.24, i32 0, i32 0)), !dbg !644
  store i8* %call138, i8** @post_write_script, align 8, !dbg !645
  %56 = load i8*, i8** @post_write_script, align 8, !dbg !646
  %arrayidx139 = getelementptr inbounds i8, i8* %56, i64 0, !dbg !646
  %57 = load i8, i8* %arrayidx139, align 1, !dbg !646
  %tobool140 = icmp ne i8 %57, 0, !dbg !646
  br i1 %tobool140, label %if.end142, label %if.then141, !dbg !648

if.then141:                                       ; preds = %if.end137
  store i8* null, i8** @post_write_script, align 8, !dbg !649
  br label %if.end142, !dbg !650

if.end142:                                        ; preds = %if.then141, %if.end137
  store i32 16, i32* %my_length, align 4, !dbg !651
  %58 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !652
  %call143 = call i32 @fileno(%struct._IO_FILE* %58) #9, !dbg !654
  %call144 = call i32 @getpeername(i32 %call143, %struct.sockaddr* bitcast (%struct.sockaddr_in* @remotename to %struct.sockaddr*), i32* %my_length) #9, !dbg !655
  %tobool145 = icmp ne i32 %call144, 0, !dbg !657
  br i1 %tobool145, label %if.then146, label %if.end149, !dbg !658

if.then146:                                       ; preds = %if.end142
  %call147 = call i32* @__errno_location() #1, !dbg !659
  %59 = load i32, i32* %call147, align 4, !dbg !659
  %call148 = call i8* @strerror(i32 %59) #9, !dbg !661
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.25, i32 0, i32 0), i8* %call148), !dbg !663
  store i32 0, i32* %retval, align 4, !dbg !664
  br label %return, !dbg !664

if.end149:                                        ; preds = %if.end142
  store i32 1, i32* %i, align 4, !dbg !665
  %60 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !666
  %call150 = call i32 @fileno(%struct._IO_FILE* %60) #9, !dbg !667
  %61 = bitcast i32* %i to i8*, !dbg !668
  %call151 = call i32 @setsockopt(i32 %call150, i32 1, i32 10, i8* %61, i32 4) #9, !dbg !669
  %62 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !670
  %call152 = call i32 @fileno(%struct._IO_FILE* %62) #9, !dbg !671
  %63 = bitcast i32* %i to i8*, !dbg !672
  %call153 = call i32 @setsockopt(i32 %call152, i32 1, i32 9, i8* %63, i32 4) #9, !dbg !673
  %call154 = call i8* @config_getoption(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.26, i32 0, i32 0)), !dbg !674
  %call155 = call i32 @strcasecmp(i8* %call154, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.27, i32 0, i32 0)) #8, !dbg !676
  %tobool156 = icmp ne i32 %call155, 0, !dbg !678
  br i1 %tobool156, label %if.else175, label %if.then157, !dbg !679

if.then157:                                       ; preds = %if.end149
  %call158 = call %struct.hostent* @gethostbyaddr(i8* bitcast (%struct.in_addr* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @remotename, i32 0, i32 2) to i8*), i32 4, i32 2), !dbg !680
  store %struct.hostent* %call158, %struct.hostent** @main.he, align 8, !dbg !683
  %tobool159 = icmp ne %struct.hostent* %call158, null, !dbg !683
  br i1 %tobool159, label %if.then160, label %if.else167, !dbg !684

if.then160:                                       ; preds = %if.then157
  %64 = load %struct.hostent*, %struct.hostent** @main.he, align 8, !dbg !685
  %h_name = getelementptr inbounds %struct.hostent, %struct.hostent* %64, i32 0, i32 0, !dbg !688
  %65 = load i8*, i8** %h_name, align 8, !dbg !688
  %tobool161 = icmp ne i8* %65, null, !dbg !685
  br i1 %tobool161, label %if.then162, label %if.else165, !dbg !689

if.then162:                                       ; preds = %if.then160
  %66 = load %struct.hostent*, %struct.hostent** @main.he, align 8, !dbg !690
  %h_name163 = getelementptr inbounds %struct.hostent, %struct.hostent* %66, i32 0, i32 0, !dbg !691
  %67 = load i8*, i8** %h_name163, align 8, !dbg !691
  %call164 = call noalias i8* @strdup(i8* %67) #9, !dbg !692
  store i8* %call164, i8** @remotehostname, align 8, !dbg !693
  br label %if.end166, !dbg !694

if.else165:                                       ; preds = %if.then160
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.28, i32 0, i32 0), i8** @remotehostname, align 8, !dbg !695
  br label %if.end166

if.end166:                                        ; preds = %if.else165, %if.then162
  br label %if.end174, !dbg !696

if.else167:                                       ; preds = %if.then157
  %68 = load i32, i32* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @remotename, i32 0, i32 2, i32 0), align 4, !dbg !697
  %call168 = call i8* @inet_ntoa(i32 %68) #9, !dbg !697
  store i8* %call168, i8** %temp_string, align 8, !dbg !699
  %69 = load i8*, i8** %temp_string, align 8, !dbg !700
  %tobool169 = icmp ne i8* %69, null, !dbg !700
  br i1 %tobool169, label %if.then170, label %if.else172, !dbg !702

if.then170:                                       ; preds = %if.else167
  %70 = load i8*, i8** %temp_string, align 8, !dbg !703
  %call171 = call noalias i8* @strdup(i8* %70) #9, !dbg !704
  store i8* %call171, i8** @remotehostname, align 8, !dbg !705
  br label %if.end173, !dbg !706

if.else172:                                       ; preds = %if.else167
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.28, i32 0, i32 0), i8** @remotehostname, align 8, !dbg !707
  br label %if.end173

if.end173:                                        ; preds = %if.else172, %if.then170
  br label %if.end174

if.end174:                                        ; preds = %if.end173, %if.end166
  br label %if.end182, !dbg !708

if.else175:                                       ; preds = %if.end149
  %71 = load i32, i32* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @remotename, i32 0, i32 2, i32 0), align 4, !dbg !709
  %call176 = call i8* @inet_ntoa(i32 %71) #9, !dbg !709
  store i8* %call176, i8** %temp_string, align 8, !dbg !711
  %72 = load i8*, i8** %temp_string, align 8, !dbg !712
  %tobool177 = icmp ne i8* %72, null, !dbg !712
  br i1 %tobool177, label %if.then178, label %if.else180, !dbg !714

if.then178:                                       ; preds = %if.else175
  %73 = load i8*, i8** %temp_string, align 8, !dbg !715
  %call179 = call noalias i8* @strdup(i8* %73) #9, !dbg !716
  store i8* %call179, i8** @remotehostname, align 8, !dbg !717
  br label %if.end181, !dbg !718

if.else180:                                       ; preds = %if.else175
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.28, i32 0, i32 0), i8** @remotehostname, align 8, !dbg !719
  br label %if.end181

if.end181:                                        ; preds = %if.else180, %if.then178
  br label %if.end182

if.end182:                                        ; preds = %if.end181, %if.end174
  %74 = load i8*, i8** @remotehostname, align 8, !dbg !720
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.29, i32 0, i32 0), i8* %74), !dbg !721
  %75 = load i8*, i8** @remotehostname, align 8, !dbg !722
  call void (i8, i8, i8*, ...) @bftpd_statuslog(i8 signext 1, i8 signext 0, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.30, i32 0, i32 0), i8* %75), !dbg !723
  store i32 16, i32* %my_length, align 4, !dbg !724
  %76 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !725
  %call183 = call i32 @fileno(%struct._IO_FILE* %76) #9, !dbg !726
  %call184 = call i32 @getsockname(i32 %call183, %struct.sockaddr* bitcast (%struct.sockaddr_in* @name to %struct.sockaddr*), i32* %my_length) #9, !dbg !727
  %call185 = call i8* @config_getoption(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.31, i32 0, i32 0)), !dbg !728
  call void @print_file(i32 220, i8* %call185), !dbg !729
  %arraydecay = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !730
  %call186 = call i8* @config_getoption(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.32, i32 0, i32 0)), !dbg !731
  %call187 = call i8* @strcpy(i8* %arraydecay, i8* %call186) #9, !dbg !732
  %arraydecay188 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !733
  %call189 = call i32 @replace(i8* %arraydecay188, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.33, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.34, i32 0, i32 0), i32 512), !dbg !734
  %arraydecay190 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !735
  %call191 = call i8* @strstr(i8* %arraydecay190, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.35, i32 0, i32 0)) #8, !dbg !737
  %tobool192 = icmp ne i8* %call191, null, !dbg !737
  br i1 %tobool192, label %if.then193, label %if.end205, !dbg !738

if.then193:                                       ; preds = %if.end182
  %call194 = call %struct.hostent* @gethostbyaddr(i8* bitcast (%struct.in_addr* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @name, i32 0, i32 2) to i8*), i32 4, i32 2), !dbg !739
  store %struct.hostent* %call194, %struct.hostent** @main.he, align 8, !dbg !742
  %tobool195 = icmp ne %struct.hostent* %call194, null, !dbg !742
  br i1 %tobool195, label %if.then196, label %if.else200, !dbg !743

if.then196:                                       ; preds = %if.then193
  %arraydecay197 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !744
  %77 = load %struct.hostent*, %struct.hostent** @main.he, align 8, !dbg !745
  %h_name198 = getelementptr inbounds %struct.hostent, %struct.hostent* %77, i32 0, i32 0, !dbg !746
  %78 = load i8*, i8** %h_name198, align 8, !dbg !746
  %call199 = call i32 @replace(i8* %arraydecay197, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.35, i32 0, i32 0), i8* %78, i32 512), !dbg !747
  br label %if.end204, !dbg !747

if.else200:                                       ; preds = %if.then193
  %arraydecay201 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !748
  %79 = load i32, i32* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @name, i32 0, i32 2, i32 0), align 4, !dbg !749
  %call202 = call i8* @inet_ntoa(i32 %79) #9, !dbg !749
  %call203 = call i32 @replace(i8* %arraydecay201, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.35, i32 0, i32 0), i8* %call202, i32 512), !dbg !750
  br label %if.end204

if.end204:                                        ; preds = %if.else200, %if.then196
  br label %if.end205, !dbg !752

if.end205:                                        ; preds = %if.end204, %if.end182
  %arraydecay206 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !753
  %80 = load i32, i32* getelementptr inbounds (%struct.sockaddr_in, %struct.sockaddr_in* @name, i32 0, i32 2, i32 0), align 4, !dbg !754
  %call207 = call i8* @inet_ntoa(i32 %80) #9, !dbg !754
  %call208 = call i32 @replace(i8* %arraydecay206, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.36, i32 0, i32 0), i8* %call207, i32 512), !dbg !755
  %arraydecay209 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !756
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.37, i32 0, i32 0), i8* %arraydecay209), !dbg !757
  %81 = load i32, i32* @control_timeout, align 4, !dbg !758
  %call210 = call i32 @alarm(i32 %81) #9, !dbg !759
  br label %while.cond211, !dbg !760

while.cond211:                                    ; preds = %while.body215, %if.end205
  %arraydecay212 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !761
  %82 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !762
  %call213 = call i8* @fgets(i8* %arraydecay212, i32 255, %struct._IO_FILE* %82), !dbg !763
  %tobool214 = icmp ne i8* %call213, null, !dbg !764
  br i1 %tobool214, label %while.body215, label %while.end223, !dbg !764

while.body215:                                    ; preds = %while.cond211
  %83 = load i32, i32* @control_timeout, align 4, !dbg !765
  %call216 = call i32 @alarm(i32 %83) #9, !dbg !767
  %arraydecay217 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !768
  %call218 = call i64 @strlen(i8* %arraydecay217) #8, !dbg !769
  %sub = sub i64 %call218, 2, !dbg !770
  %arrayidx219 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i64 0, i64 %sub, !dbg !771
  store i8 0, i8* %arrayidx219, align 1, !dbg !772
  %arraydecay220 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !773
  call void (i8, i8, i8*, ...) @bftpd_statuslog(i8 signext 2, i8 signext 0, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.38, i32 0, i32 0), i8* %arraydecay220), !dbg !774
  %arraydecay221 = getelementptr inbounds [513 x i8], [513 x i8]* %str, i32 0, i32 0, !dbg !775
  %call222 = call i32 @parsecmd(i8* %arraydecay221), !dbg !776
  br label %while.cond211, !dbg !777

while.end223:                                     ; preds = %while.cond211
  %84 = load i8*, i8** @remotehostname, align 8, !dbg !778
  %tobool224 = icmp ne i8* %84, null, !dbg !778
  br i1 %tobool224, label %if.then225, label %if.end226, !dbg !780

if.then225:                                       ; preds = %while.end223
  %85 = load i8*, i8** @remotehostname, align 8, !dbg !781
  call void @free(i8* %85) #9, !dbg !783
  br label %if.end226, !dbg !783

if.end226:                                        ; preds = %if.then225, %while.end223
  store i32 0, i32* %retval, align 4, !dbg !784
  br label %return, !dbg !784

return:                                           ; preds = %if.end226, %if.then146, %if.then18, %sw.bb
  %86 = load i32, i32* %retval, align 4, !dbg !785
  ret i32 %86, !dbg !785
}

; Function Attrs: nounwind
declare i32 @getopt(i32, i8**, i8*) #4

declare i32 @printf(i8*, ...) #2

; Function Attrs: nounwind
declare noalias i8* @strdup(i8*) #4

; Function Attrs: nounwind
declare i32 @fork() #4

; Function Attrs: nounwind
declare i32 @setsid() #4

; Function Attrs: nounwind
declare i32 @chdir(i8*) #4

; Function Attrs: nounwind
declare i32 @socket(i32, i32, i32) #4

; Function Attrs: nounwind
declare i32 @setsockopt(i32, i32, i32, i8*, i32) #4

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #6

; Function Attrs: nounwind
declare i64 @strtoul(i8*, i8**, i32) #4

declare i8* @config_getoption(i8*) #2

; Function Attrs: nounwind readnone
declare zeroext i16 @htons(i16 zeroext) #7

; Function Attrs: nounwind readonly
declare i32 @strcasecmp(i8*, i8*) #3

; Function Attrs: nounwind
declare i32 @inet_addr(i8*) #4

; Function Attrs: nounwind
declare i32 @bind(i32, %struct.sockaddr*, i32) #4

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #2

; Function Attrs: nounwind
declare i8* @strerror(i32) #4

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #7

; Function Attrs: nounwind
declare i32 @listen(i32, i32) #4

declare i32 @open64(i8*, i32, ...) #2

declare i32 @accept(i32, %struct.sockaddr*, i32*) #2

; Function Attrs: nounwind
declare i32 @dup2(i32, i32) #4

; Function Attrs: nounwind
declare i32 @fileno(%struct._IO_FILE*) #4

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #4

declare void @bftpd_list_add(%struct.bftpd_list_element**, i8*) #2

; Function Attrs: nounwind
declare i32 @atexit(void ()*) #4

; Function Attrs: nounwind
declare i32 @getpeername(i32, %struct.sockaddr*, i32*) #4

declare %struct.hostent* @gethostbyaddr(i8*, i32, i32) #2

; Function Attrs: nounwind
declare i8* @inet_ntoa(i32) #4

; Function Attrs: nounwind
declare i32 @getsockname(i32, %struct.sockaddr*, i32*) #4

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #4

declare i32 @replace(i8*, i8*, i8*, i32) #2

; Function Attrs: nounwind readonly
declare i8* @strstr(i8*, i8*) #3

; Function Attrs: nounwind
declare i32 @alarm(i32) #4

declare i32 @parsecmd(i8*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { argmemonly nounwind }
attributes #7 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { nounwind readonly }
attributes #9 = { nounwind }
attributes #10 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!168, !169}
!llvm.ident = !{!170}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !15, subprograms: !36, globals: !57)
!1 = !DIFile(filename: "main.c", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!2 = !{!3}
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
!15 = !{!16, !17, !22, !35}
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!17 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_addr_t", file: !18, line: 30, baseType: !19)
!18 = !DIFile(filename: "/usr/include/netinet/in.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!19 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !20, line: 51, baseType: !21)
!20 = !DIFile(filename: "/usr/include/stdint.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!21 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!23 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !24, line: 149, size: 128, align: 16, elements: !25)
!24 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!25 = !{!26, !30}
!26 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !23, file: !24, line: 151, baseType: !27, size: 16, align: 16)
!27 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !28, line: 28, baseType: !29)
!28 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!29 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!30 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !23, file: !24, line: 152, baseType: !31, size: 112, align: 8, offset: 16)
!31 = !DICompositeType(tag: DW_TAG_array_type, baseType: !32, size: 112, align: 8, elements: !33)
!32 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!33 = !{!34}
!34 = !DISubrange(count: 14)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64, align: 64)
!36 = !{!37, !43, !46, !49, !50, !51, !52, !53}
!37 = distinct !DISubprogram(name: "print_file", scope: !38, file: !38, line: 80, type: !39, isLocal: false, isDefinition: true, scopeLine: 81, flags: DIFlagPrototyped, isOptimized: false, variables: !42)
!38 = !DIFile(filename: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/main.c", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!39 = !DISubroutineType(types: !40)
!40 = !{null, !41, !35}
!41 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!42 = !{}
!43 = distinct !DISubprogram(name: "end_child", scope: !38, file: !38, line: 94, type: !44, isLocal: false, isDefinition: true, scopeLine: 95, isOptimized: false, variables: !42)
!44 = !DISubroutineType(types: !45)
!45 = !{null}
!46 = distinct !DISubprogram(name: "handler_sighup", scope: !38, file: !38, line: 124, type: !47, isLocal: false, isDefinition: true, scopeLine: 125, flags: DIFlagPrototyped, isOptimized: false, variables: !42)
!47 = !DISubroutineType(types: !48)
!48 = !{null, !41}
!49 = distinct !DISubprogram(name: "handler_sigchld", scope: !38, file: !38, line: 134, type: !47, isLocal: false, isDefinition: true, scopeLine: 135, flags: DIFlagPrototyped, isOptimized: false, variables: !42)
!50 = distinct !DISubprogram(name: "handler_sigterm", scope: !38, file: !38, line: 159, type: !47, isLocal: false, isDefinition: true, scopeLine: 160, flags: DIFlagPrototyped, isOptimized: false, variables: !42)
!51 = distinct !DISubprogram(name: "handler_sigalrm", scope: !38, file: !38, line: 165, type: !47, isLocal: false, isDefinition: true, scopeLine: 166, flags: DIFlagPrototyped, isOptimized: false, variables: !42)
!52 = distinct !DISubprogram(name: "init_everything", scope: !38, file: !38, line: 183, type: !44, isLocal: false, isDefinition: true, scopeLine: 184, isOptimized: false, variables: !42)
!53 = distinct !DISubprogram(name: "main", scope: !38, file: !38, line: 196, type: !54, isLocal: false, isDefinition: true, scopeLine: 197, flags: DIFlagPrototyped, isOptimized: false, variables: !42)
!54 = !DISubroutineType(types: !55)
!55 = !{!41, !41, !56}
!56 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !35, size: 64, align: 64)
!57 = !{!58, !59, !118, !119, !120, !121, !122, !132, !134, !135, !136, !137, !138, !154, !155, !156, !157, !158, !159, !160, !161}
!58 = !DIGlobalVariable(name: "isparent", scope: !0, file: !38, line: 66, type: !41, isLocal: false, isDefinition: true, variable: i32* @isparent)
!59 = !DIGlobalVariable(name: "passwdfile", scope: !0, file: !38, line: 68, type: !60, isLocal: false, isDefinition: true, variable: %struct._IO_FILE** @passwdfile)
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!61 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !62, line: 48, baseType: !63)
!62 = !DIFile(filename: "/usr/include/stdio.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!63 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !64, line: 245, size: 1728, align: 64, elements: !65)
!64 = !DIFile(filename: "/usr/include/libio.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!65 = !{!66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !86, !87, !88, !89, !93, !94, !96, !100, !103, !105, !106, !107, !108, !109, !113, !114}
!66 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !63, file: !64, line: 246, baseType: !41, size: 32, align: 32)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !63, file: !64, line: 251, baseType: !35, size: 64, align: 64, offset: 64)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !63, file: !64, line: 252, baseType: !35, size: 64, align: 64, offset: 128)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !63, file: !64, line: 253, baseType: !35, size: 64, align: 64, offset: 192)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !63, file: !64, line: 254, baseType: !35, size: 64, align: 64, offset: 256)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !63, file: !64, line: 255, baseType: !35, size: 64, align: 64, offset: 320)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !63, file: !64, line: 256, baseType: !35, size: 64, align: 64, offset: 384)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !63, file: !64, line: 257, baseType: !35, size: 64, align: 64, offset: 448)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !63, file: !64, line: 258, baseType: !35, size: 64, align: 64, offset: 512)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !63, file: !64, line: 260, baseType: !35, size: 64, align: 64, offset: 576)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !63, file: !64, line: 261, baseType: !35, size: 64, align: 64, offset: 640)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !63, file: !64, line: 262, baseType: !35, size: 64, align: 64, offset: 704)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !63, file: !64, line: 264, baseType: !79, size: 64, align: 64, offset: 768)
!79 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !80, size: 64, align: 64)
!80 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !64, line: 160, size: 192, align: 64, elements: !81)
!81 = !{!82, !83, !85}
!82 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !80, file: !64, line: 161, baseType: !79, size: 64, align: 64)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !80, file: !64, line: 162, baseType: !84, size: 64, align: 64, offset: 64)
!84 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !80, file: !64, line: 166, baseType: !41, size: 32, align: 32, offset: 128)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !63, file: !64, line: 266, baseType: !84, size: 64, align: 64, offset: 832)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !63, file: !64, line: 268, baseType: !41, size: 32, align: 32, offset: 896)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !63, file: !64, line: 272, baseType: !41, size: 32, align: 32, offset: 928)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !63, file: !64, line: 274, baseType: !90, size: 64, align: 64, offset: 960)
!90 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !91, line: 131, baseType: !92)
!91 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!92 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !63, file: !64, line: 278, baseType: !29, size: 16, align: 16, offset: 1024)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !63, file: !64, line: 279, baseType: !95, size: 8, align: 8, offset: 1040)
!95 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !63, file: !64, line: 280, baseType: !97, size: 8, align: 8, offset: 1048)
!97 = !DICompositeType(tag: DW_TAG_array_type, baseType: !32, size: 8, align: 8, elements: !98)
!98 = !{!99}
!99 = !DISubrange(count: 1)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !63, file: !64, line: 284, baseType: !101, size: 64, align: 64, offset: 1088)
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !102, size: 64, align: 64)
!102 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !64, line: 154, baseType: null)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !63, file: !64, line: 293, baseType: !104, size: 64, align: 64, offset: 1152)
!104 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !91, line: 132, baseType: !92)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !63, file: !64, line: 302, baseType: !16, size: 64, align: 64, offset: 1216)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !63, file: !64, line: 303, baseType: !16, size: 64, align: 64, offset: 1280)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !63, file: !64, line: 304, baseType: !16, size: 64, align: 64, offset: 1344)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !63, file: !64, line: 305, baseType: !16, size: 64, align: 64, offset: 1408)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !63, file: !64, line: 306, baseType: !110, size: 64, align: 64, offset: 1472)
!110 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !111, line: 62, baseType: !112)
!111 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!112 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !63, file: !64, line: 308, baseType: !41, size: 32, align: 32, offset: 1536)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !63, file: !64, line: 310, baseType: !115, size: 160, align: 8, offset: 1568)
!115 = !DICompositeType(tag: DW_TAG_array_type, baseType: !32, size: 160, align: 8, elements: !116)
!116 = !{!117}
!117 = !DISubrange(count: 20)
!118 = !DIGlobalVariable(name: "groupfile", scope: !0, file: !38, line: 68, type: !60, isLocal: false, isDefinition: true, variable: %struct._IO_FILE** @groupfile)
!119 = !DIGlobalVariable(name: "alarm_type", scope: !0, file: !38, line: 72, type: !41, isLocal: false, isDefinition: true, variable: i32* @alarm_type)
!120 = !DIGlobalVariable(name: "configpath", scope: !0, file: !38, line: 77, type: !35, isLocal: false, isDefinition: true, variable: i8** @configpath)
!121 = !DIGlobalVariable(name: "daemonmode", scope: !0, file: !38, line: 78, type: !41, isLocal: false, isDefinition: true, variable: i32* @daemonmode)
!122 = !DIGlobalVariable(name: "he", scope: !53, file: !38, line: 199, type: !123, isLocal: true, isDefinition: true, variable: %struct.hostent** @main.he)
!123 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !124, size: 64, align: 64)
!124 = !DICompositeType(tag: DW_TAG_structure_type, name: "hostent", file: !125, line: 100, size: 256, align: 64, elements: !126)
!125 = !DIFile(filename: "/usr/include/netdb.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!126 = !{!127, !128, !129, !130, !131}
!127 = !DIDerivedType(tag: DW_TAG_member, name: "h_name", scope: !124, file: !125, line: 102, baseType: !35, size: 64, align: 64)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "h_aliases", scope: !124, file: !125, line: 103, baseType: !56, size: 64, align: 64, offset: 64)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "h_addrtype", scope: !124, file: !125, line: 104, baseType: !41, size: 32, align: 32, offset: 128)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "h_length", scope: !124, file: !125, line: 105, baseType: !41, size: 32, align: 32, offset: 160)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "h_addr_list", scope: !124, file: !125, line: 106, baseType: !56, size: 64, align: 64, offset: 192)
!132 = !DIGlobalVariable(name: "pre_write_script", scope: !0, file: !133, line: 29, type: !35, isLocal: false, isDefinition: true, variable: i8** @pre_write_script)
!133 = !DIFile(filename: "./main.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!134 = !DIGlobalVariable(name: "post_write_script", scope: !0, file: !133, line: 30, type: !35, isLocal: false, isDefinition: true, variable: i8** @post_write_script)
!135 = !DIGlobalVariable(name: "global_argc", scope: !0, file: !38, line: 62, type: !41, isLocal: false, isDefinition: true, variable: i32* @global_argc)
!136 = !DIGlobalVariable(name: "global_argv", scope: !0, file: !38, line: 63, type: !56, isLocal: false, isDefinition: true, variable: i8*** @global_argv)
!137 = !DIGlobalVariable(name: "my_argv_list", scope: !0, file: !38, line: 64, type: !56, isLocal: false, isDefinition: true, variable: i8*** @my_argv_list)
!138 = !DIGlobalVariable(name: "name", scope: !0, file: !38, line: 65, type: !139, isLocal: false, isDefinition: true, variable: %struct.sockaddr_in* @name)
!139 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_in", file: !18, line: 237, size: 128, align: 32, elements: !140)
!140 = !{!141, !142, !145, !149}
!141 = !DIDerivedType(tag: DW_TAG_member, name: "sin_family", scope: !139, file: !18, line: 239, baseType: !27, size: 16, align: 16)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "sin_port", scope: !139, file: !18, line: 240, baseType: !143, size: 16, align: 16, offset: 16)
!143 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_port_t", file: !18, line: 117, baseType: !144)
!144 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !20, line: 49, baseType: !29)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "sin_addr", scope: !139, file: !18, line: 241, baseType: !146, size: 32, align: 32, offset: 32)
!146 = !DICompositeType(tag: DW_TAG_structure_type, name: "in_addr", file: !18, line: 31, size: 32, align: 32, elements: !147)
!147 = !{!148}
!148 = !DIDerivedType(tag: DW_TAG_member, name: "s_addr", scope: !146, file: !18, line: 33, baseType: !17, size: 32, align: 32)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "sin_zero", scope: !139, file: !18, line: 244, baseType: !150, size: 64, align: 8, offset: 64)
!150 = !DICompositeType(tag: DW_TAG_array_type, baseType: !151, size: 64, align: 8, elements: !152)
!151 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!152 = !{!153}
!153 = !DISubrange(count: 8)
!154 = !DIGlobalVariable(name: "listensocket", scope: !0, file: !38, line: 67, type: !41, isLocal: false, isDefinition: true, variable: i32* @listensocket)
!155 = !DIGlobalVariable(name: "sock", scope: !0, file: !38, line: 67, type: !41, isLocal: false, isDefinition: true, variable: i32* @sock)
!156 = !DIGlobalVariable(name: "devnull", scope: !0, file: !38, line: 68, type: !60, isLocal: false, isDefinition: true, variable: %struct._IO_FILE** @devnull)
!157 = !DIGlobalVariable(name: "remotename", scope: !0, file: !38, line: 69, type: !139, isLocal: false, isDefinition: true, variable: %struct.sockaddr_in* @remotename)
!158 = !DIGlobalVariable(name: "remotehostname", scope: !0, file: !38, line: 70, type: !35, isLocal: false, isDefinition: true, variable: i8** @remotehostname)
!159 = !DIGlobalVariable(name: "control_timeout", scope: !0, file: !38, line: 71, type: !41, isLocal: false, isDefinition: true, variable: i32* @control_timeout)
!160 = !DIGlobalVariable(name: "data_timeout", scope: !0, file: !38, line: 71, type: !41, isLocal: false, isDefinition: true, variable: i32* @data_timeout)
!161 = !DIGlobalVariable(name: "child_list", scope: !0, file: !38, line: 74, type: !162, isLocal: false, isDefinition: true, variable: %struct.bftpd_list_element** @child_list)
!162 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !163, size: 64, align: 64)
!163 = !DICompositeType(tag: DW_TAG_structure_type, name: "bftpd_list_element", file: !164, line: 6, size: 128, align: 64, elements: !165)
!164 = !DIFile(filename: "./list.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!165 = !{!166, !167}
!166 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !163, file: !164, line: 7, baseType: !16, size: 64, align: 64)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !163, file: !164, line: 8, baseType: !162, size: 64, align: 64, offset: 64)
!168 = !{i32 2, !"Dwarf Version", i32 4}
!169 = !{i32 2, !"Debug Info Version", i32 3}
!170 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!171 = !DILocalVariable(name: "number", arg: 1, scope: !37, file: !38, line: 80, type: !41)
!172 = !DIExpression()
!173 = !DILocation(line: 80, column: 21, scope: !37)
!174 = !DILocalVariable(name: "filename", arg: 2, scope: !37, file: !38, line: 80, type: !35)
!175 = !DILocation(line: 80, column: 35, scope: !37)
!176 = !DILocalVariable(name: "phile", scope: !37, file: !38, line: 82, type: !60)
!177 = !DILocation(line: 82, column: 8, scope: !37)
!178 = !DILocalVariable(name: "foo", scope: !37, file: !38, line: 83, type: !179)
!179 = !DICompositeType(tag: DW_TAG_array_type, baseType: !32, size: 4096, align: 8, elements: !180)
!180 = !{!181}
!181 = !DISubrange(count: 512)
!182 = !DILocation(line: 83, column: 7, scope: !37)
!183 = !DILocation(line: 84, column: 16, scope: !37)
!184 = !DILocation(line: 84, column: 10, scope: !37)
!185 = !DILocation(line: 84, column: 8, scope: !37)
!186 = !DILocation(line: 85, column: 6, scope: !187)
!187 = distinct !DILexicalBlock(scope: !37, file: !38, line: 85, column: 6)
!188 = !DILocation(line: 85, column: 6, scope: !37)
!189 = !DILocation(line: 86, column: 3, scope: !190)
!190 = distinct !DILexicalBlock(scope: !187, file: !38, line: 85, column: 13)
!191 = !DILocation(line: 86, column: 16, scope: !192)
!192 = !DILexicalBlockFile(scope: !190, file: !38, discriminator: 1)
!193 = !DILocation(line: 86, column: 40, scope: !192)
!194 = !DILocation(line: 86, column: 10, scope: !192)
!195 = !DILocation(line: 86, column: 3, scope: !192)
!196 = !DILocation(line: 87, column: 15, scope: !197)
!197 = distinct !DILexicalBlock(scope: !190, file: !38, line: 86, column: 48)
!198 = !DILocation(line: 87, column: 8, scope: !197)
!199 = !DILocation(line: 87, column: 20, scope: !197)
!200 = !DILocation(line: 87, column: 4, scope: !197)
!201 = !DILocation(line: 87, column: 25, scope: !197)
!202 = !DILocation(line: 88, column: 40, scope: !197)
!203 = !DILocation(line: 88, column: 48, scope: !197)
!204 = !DILocation(line: 88, column: 4, scope: !197)
!205 = !DILocation(line: 86, column: 3, scope: !206)
!206 = !DILexicalBlockFile(scope: !190, file: !38, discriminator: 2)
!207 = !DILocation(line: 90, column: 10, scope: !190)
!208 = !DILocation(line: 90, column: 3, scope: !190)
!209 = !DILocation(line: 91, column: 2, scope: !190)
!210 = !DILocation(line: 92, column: 1, scope: !37)
!211 = !DILocation(line: 96, column: 5, scope: !43)
!212 = !DILocation(line: 97, column: 6, scope: !213)
!213 = distinct !DILexicalBlock(scope: !43, file: !38, line: 97, column: 6)
!214 = !DILocation(line: 97, column: 6, scope: !43)
!215 = !DILocation(line: 98, column: 10, scope: !213)
!216 = !DILocation(line: 98, column: 3, scope: !213)
!217 = !DILocation(line: 99, column: 6, scope: !218)
!218 = distinct !DILexicalBlock(scope: !43, file: !38, line: 99, column: 6)
!219 = !DILocation(line: 99, column: 6, scope: !43)
!220 = !DILocation(line: 100, column: 10, scope: !218)
!221 = !DILocation(line: 100, column: 3, scope: !218)
!222 = !DILocation(line: 101, column: 2, scope: !43)
!223 = !DILocation(line: 102, column: 2, scope: !43)
!224 = !DILocation(line: 103, column: 5, scope: !43)
!225 = !DILocation(line: 104, column: 5, scope: !43)
!226 = !DILocation(line: 105, column: 2, scope: !43)
!227 = !DILocation(line: 106, column: 2, scope: !43)
!228 = !DILocation(line: 107, column: 2, scope: !43)
!229 = !DILocation(line: 108, column: 6, scope: !230)
!230 = distinct !DILexicalBlock(scope: !43, file: !38, line: 108, column: 6)
!231 = !DILocation(line: 108, column: 6, scope: !43)
!232 = !DILocation(line: 109, column: 9, scope: !233)
!233 = distinct !DILexicalBlock(scope: !230, file: !38, line: 108, column: 18)
!234 = !DILocation(line: 109, column: 3, scope: !233)
!235 = !DILocation(line: 110, column: 3, scope: !233)
!236 = !DILocation(line: 111, column: 3, scope: !233)
!237 = !DILocation(line: 112, column: 3, scope: !233)
!238 = !DILocation(line: 113, column: 2, scope: !233)
!239 = !DILocation(line: 114, column: 1, scope: !43)
!240 = !DILocalVariable(name: "sig", arg: 1, scope: !46, file: !38, line: 124, type: !41)
!241 = !DILocation(line: 124, column: 25, scope: !46)
!242 = !DILocation(line: 126, column: 4, scope: !46)
!243 = !DILocation(line: 127, column: 4, scope: !46)
!244 = !DILocation(line: 128, column: 11, scope: !46)
!245 = !DILocation(line: 128, column: 4, scope: !46)
!246 = !DILocation(line: 129, column: 1, scope: !46)
!247 = !DILocalVariable(name: "sig", arg: 1, scope: !49, file: !38, line: 134, type: !41)
!248 = !DILocation(line: 134, column: 26, scope: !49)
!249 = !DILocalVariable(name: "pid", scope: !49, file: !38, line: 136, type: !250)
!250 = !DIDerivedType(tag: DW_TAG_typedef, name: "pid_t", file: !251, line: 98, baseType: !252)
!251 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!252 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pid_t", file: !91, line: 133, baseType: !41)
!253 = !DILocation(line: 136, column: 8, scope: !49)
!254 = !DILocalVariable(name: "i", scope: !49, file: !38, line: 137, type: !41)
!255 = !DILocation(line: 137, column: 6, scope: !49)
!256 = !DILocalVariable(name: "childpid", scope: !49, file: !38, line: 138, type: !257)
!257 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !258, size: 64, align: 64)
!258 = !DICompositeType(tag: DW_TAG_structure_type, name: "bftpd_childpid", file: !133, line: 10, size: 64, align: 32, elements: !259)
!259 = !{!260, !261}
!260 = !DIDerivedType(tag: DW_TAG_member, name: "pid", scope: !258, file: !133, line: 11, baseType: !250, size: 32, align: 32)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "sock", scope: !258, file: !133, line: 12, baseType: !41, size: 32, align: 32, offset: 32)
!262 = !DILocation(line: 138, column: 25, scope: !49)
!263 = !DILocation(line: 142, column: 15, scope: !49)
!264 = !DILocation(line: 142, column: 13, scope: !49)
!265 = !DILocation(line: 143, column: 9, scope: !49)
!266 = !DILocation(line: 143, column: 16, scope: !267)
!267 = !DILexicalBlockFile(scope: !49, file: !38, discriminator: 1)
!268 = !DILocation(line: 143, column: 20, scope: !267)
!269 = !DILocation(line: 143, column: 9, scope: !267)
!270 = !DILocation(line: 145, column: 14, scope: !271)
!271 = distinct !DILexicalBlock(scope: !272, file: !38, line: 145, column: 7)
!272 = distinct !DILexicalBlock(scope: !49, file: !38, line: 144, column: 9)
!273 = !DILocation(line: 145, column: 12, scope: !271)
!274 = !DILocation(line: 145, column: 19, scope: !275)
!275 = !DILexicalBlockFile(scope: !276, file: !38, discriminator: 1)
!276 = distinct !DILexicalBlock(scope: !271, file: !38, line: 145, column: 7)
!277 = !DILocation(line: 145, column: 40, scope: !275)
!278 = !DILocation(line: 145, column: 23, scope: !275)
!279 = !DILocation(line: 145, column: 21, scope: !275)
!280 = !DILocation(line: 145, column: 7, scope: !275)
!281 = !DILocation(line: 146, column: 29, scope: !282)
!282 = distinct !DILexicalBlock(scope: !276, file: !38, line: 145, column: 58)
!283 = !DILocation(line: 146, column: 41, scope: !282)
!284 = !DILocation(line: 146, column: 14, scope: !282)
!285 = !DILocation(line: 146, column: 12, scope: !282)
!286 = !DILocation(line: 147, column: 9, scope: !287)
!287 = distinct !DILexicalBlock(scope: !282, file: !38, line: 147, column: 8)
!288 = !DILocation(line: 147, column: 8, scope: !287)
!289 = !DILocation(line: 147, column: 19, scope: !287)
!290 = !DILocation(line: 147, column: 23, scope: !291)
!291 = !DILexicalBlockFile(scope: !287, file: !38, discriminator: 1)
!292 = !DILocation(line: 147, column: 33, scope: !291)
!293 = !DILocation(line: 147, column: 40, scope: !291)
!294 = !DILocation(line: 147, column: 37, scope: !291)
!295 = !DILocation(line: 147, column: 8, scope: !291)
!296 = !DILocation(line: 148, column: 10, scope: !297)
!297 = distinct !DILexicalBlock(scope: !287, file: !38, line: 147, column: 47)
!298 = !DILocation(line: 148, column: 20, scope: !297)
!299 = !DILocation(line: 148, column: 4, scope: !297)
!300 = !DILocation(line: 149, column: 32, scope: !297)
!301 = !DILocation(line: 149, column: 4, scope: !297)
!302 = !DILocation(line: 150, column: 9, scope: !297)
!303 = !DILocation(line: 150, column: 4, scope: !297)
!304 = !DILocation(line: 152, column: 46, scope: !297)
!305 = !DILocation(line: 152, column: 25, scope: !297)
!306 = !DILocation(line: 153, column: 3, scope: !297)
!307 = !DILocation(line: 154, column: 7, scope: !282)
!308 = !DILocation(line: 145, column: 54, scope: !309)
!309 = !DILexicalBlockFile(scope: !276, file: !38, discriminator: 2)
!310 = !DILocation(line: 145, column: 7, scope: !309)
!311 = !DILocation(line: 155, column: 20, scope: !272)
!312 = !DILocation(line: 155, column: 18, scope: !272)
!313 = !DILocation(line: 143, column: 9, scope: !314)
!314 = !DILexicalBlockFile(scope: !49, file: !38, discriminator: 2)
!315 = !DILocation(line: 157, column: 1, scope: !49)
!316 = !DILocalVariable(name: "signum", arg: 1, scope: !50, file: !38, line: 159, type: !41)
!317 = !DILocation(line: 159, column: 26, scope: !50)
!318 = !DILocation(line: 161, column: 9, scope: !50)
!319 = !DILocation(line: 162, column: 2, scope: !50)
!320 = !DILocation(line: 163, column: 1, scope: !50)
!321 = !DILocalVariable(name: "signum", arg: 1, scope: !51, file: !38, line: 165, type: !41)
!322 = !DILocation(line: 165, column: 26, scope: !51)
!323 = !DILocation(line: 168, column: 5, scope: !51)
!324 = !DILocation(line: 171, column: 9, scope: !325)
!325 = distinct !DILexicalBlock(scope: !51, file: !38, line: 171, column: 9)
!326 = !DILocation(line: 171, column: 9, scope: !51)
!327 = !DILocation(line: 172, column: 15, scope: !328)
!328 = distinct !DILexicalBlock(scope: !325, file: !38, line: 171, column: 21)
!329 = !DILocation(line: 172, column: 9, scope: !328)
!330 = !DILocation(line: 173, column: 9, scope: !328)
!331 = !DILocation(line: 174, column: 9, scope: !328)
!332 = !DILocation(line: 175, column: 9, scope: !328)
!333 = !DILocation(line: 177, column: 9, scope: !334)
!334 = distinct !DILexicalBlock(scope: !325, file: !38, line: 176, column: 12)
!335 = !DILocation(line: 178, column: 9, scope: !334)
!336 = !DILocation(line: 179, column: 9, scope: !334)
!337 = !DILocation(line: 181, column: 1, scope: !51)
!338 = !DILocation(line: 185, column: 7, scope: !339)
!339 = distinct !DILexicalBlock(scope: !52, file: !38, line: 185, column: 6)
!340 = !DILocation(line: 185, column: 6, scope: !52)
!341 = !DILocation(line: 187, column: 6, scope: !342)
!342 = distinct !DILexicalBlock(scope: !339, file: !38, line: 186, column: 9)
!343 = !DILocation(line: 188, column: 13, scope: !342)
!344 = !DILocation(line: 189, column: 9, scope: !342)
!345 = !DILocation(line: 190, column: 2, scope: !52)
!346 = !DILocation(line: 191, column: 9, scope: !52)
!347 = !DILocation(line: 192, column: 2, scope: !52)
!348 = !DILocation(line: 193, column: 9, scope: !52)
!349 = !DILocation(line: 194, column: 1, scope: !52)
!350 = !DILocalVariable(name: "argc", arg: 1, scope: !53, file: !38, line: 196, type: !41)
!351 = !DILocation(line: 196, column: 14, scope: !53)
!352 = !DILocalVariable(name: "argv", arg: 2, scope: !53, file: !38, line: 196, type: !56)
!353 = !DILocation(line: 196, column: 27, scope: !53)
!354 = !DILocalVariable(name: "str", scope: !53, file: !38, line: 198, type: !355)
!355 = !DICompositeType(tag: DW_TAG_array_type, baseType: !32, size: 4104, align: 8, elements: !356)
!356 = !{!357}
!357 = !DISubrange(count: 513)
!358 = !DILocation(line: 198, column: 7, scope: !53)
!359 = !DILocalVariable(name: "i", scope: !53, file: !38, line: 200, type: !41)
!360 = !DILocation(line: 200, column: 6, scope: !53)
!361 = !DILocalVariable(name: "port", scope: !53, file: !38, line: 200, type: !41)
!362 = !DILocation(line: 200, column: 13, scope: !53)
!363 = !DILocalVariable(name: "retval", scope: !53, file: !38, line: 201, type: !41)
!364 = !DILocation(line: 201, column: 6, scope: !53)
!365 = !DILocalVariable(name: "get_value", scope: !53, file: !38, line: 202, type: !112)
!366 = !DILocation(line: 202, column: 23, scope: !53)
!367 = !DILocalVariable(name: "my_length", scope: !53, file: !38, line: 203, type: !368)
!368 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !24, line: 33, baseType: !369)
!369 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !91, line: 189, baseType: !21)
!370 = !DILocation(line: 203, column: 19, scope: !53)
!371 = !DILocalVariable(name: "temp_string", scope: !53, file: !38, line: 204, type: !35)
!372 = !DILocation(line: 204, column: 15, scope: !53)
!373 = !DILocation(line: 206, column: 24, scope: !53)
!374 = !DILocation(line: 206, column: 22, scope: !53)
!375 = !DILocation(line: 207, column: 9, scope: !53)
!376 = !DILocation(line: 209, column: 2, scope: !53)
!377 = !DILocation(line: 209, column: 27, scope: !378)
!378 = !DILexicalBlockFile(scope: !53, file: !38, discriminator: 1)
!379 = !DILocation(line: 209, column: 33, scope: !378)
!380 = !DILocation(line: 209, column: 20, scope: !378)
!381 = !DILocation(line: 209, column: 18, scope: !378)
!382 = !DILocation(line: 209, column: 52, scope: !378)
!383 = !DILocation(line: 209, column: 2, scope: !378)
!384 = !DILocation(line: 210, column: 11, scope: !385)
!385 = distinct !DILexicalBlock(scope: !53, file: !38, line: 209, column: 58)
!386 = !DILocation(line: 210, column: 3, scope: !385)
!387 = !DILocation(line: 219, column: 43, scope: !388)
!388 = distinct !DILexicalBlock(scope: !385, file: !38, line: 210, column: 19)
!389 = !DILocation(line: 212, column: 5, scope: !388)
!390 = !DILocation(line: 220, column: 5, scope: !388)
!391 = !DILocation(line: 221, column: 25, scope: !388)
!392 = !DILocation(line: 221, column: 30, scope: !388)
!393 = !DILocation(line: 222, column: 25, scope: !388)
!394 = !DILocation(line: 222, column: 30, scope: !388)
!395 = !DILocation(line: 223, column: 25, scope: !388)
!396 = !DILocation(line: 223, column: 30, scope: !388)
!397 = !DILocation(line: 224, column: 34, scope: !388)
!398 = !DILocation(line: 224, column: 27, scope: !388)
!399 = !DILocation(line: 224, column: 25, scope: !388)
!400 = !DILocation(line: 224, column: 43, scope: !388)
!401 = !DILocation(line: 225, column: 25, scope: !388)
!402 = !DILocation(line: 225, column: 33, scope: !388)
!403 = !DILocation(line: 209, column: 2, scope: !404)
!404 = !DILexicalBlockFile(scope: !53, file: !38, discriminator: 2)
!405 = !DILocation(line: 228, column: 6, scope: !406)
!406 = distinct !DILexicalBlock(scope: !53, file: !38, line: 228, column: 6)
!407 = !DILocation(line: 228, column: 6, scope: !53)
!408 = !DILocalVariable(name: "myaddr", scope: !409, file: !38, line: 229, type: !139)
!409 = distinct !DILexicalBlock(scope: !406, file: !38, line: 228, column: 18)
!410 = !DILocation(line: 229, column: 22, scope: !409)
!411 = !DILocalVariable(name: "new", scope: !409, file: !38, line: 229, type: !139)
!412 = !DILocation(line: 229, column: 30, scope: !409)
!413 = !DILocation(line: 230, column: 7, scope: !414)
!414 = distinct !DILexicalBlock(scope: !409, file: !38, line: 230, column: 7)
!415 = !DILocation(line: 230, column: 18, scope: !414)
!416 = !DILocation(line: 230, column: 7, scope: !409)
!417 = !DILocation(line: 231, column: 8, scope: !418)
!418 = distinct !DILexicalBlock(scope: !419, file: !38, line: 231, column: 8)
!419 = distinct !DILexicalBlock(scope: !414, file: !38, line: 230, column: 24)
!420 = !DILocation(line: 231, column: 8, scope: !419)
!421 = !DILocation(line: 232, column: 5, scope: !418)
!422 = !DILocation(line: 233, column: 4, scope: !419)
!423 = !DILocation(line: 234, column: 8, scope: !424)
!424 = distinct !DILexicalBlock(scope: !419, file: !38, line: 234, column: 8)
!425 = !DILocation(line: 234, column: 8, scope: !419)
!426 = !DILocation(line: 235, column: 5, scope: !424)
!427 = !DILocation(line: 236, column: 3, scope: !419)
!428 = !DILocation(line: 237, column: 3, scope: !409)
!429 = !DILocation(line: 238, column: 3, scope: !409)
!430 = !DILocation(line: 239, column: 3, scope: !409)
!431 = !DILocation(line: 240, column: 17, scope: !409)
!432 = !DILocation(line: 241, column: 18, scope: !409)
!433 = !DILocation(line: 241, column: 16, scope: !409)
!434 = !DILocation(line: 243, column: 14, scope: !409)
!435 = !DILocation(line: 243, column: 54, scope: !409)
!436 = !DILocation(line: 243, column: 3, scope: !409)
!437 = !DILocation(line: 247, column: 14, scope: !409)
!438 = !DILocation(line: 247, column: 54, scope: !409)
!439 = !DILocation(line: 247, column: 3, scope: !409)
!440 = !DILocation(line: 250, column: 3, scope: !409)
!441 = !DILocation(line: 251, column: 31, scope: !442)
!442 = distinct !DILexicalBlock(scope: !409, file: !38, line: 251, column: 13)
!443 = !DILocation(line: 251, column: 23, scope: !444)
!444 = !DILexicalBlockFile(scope: !442, file: !38, discriminator: 1)
!445 = !DILocation(line: 251, column: 23, scope: !442)
!446 = !DILocation(line: 251, column: 21, scope: !442)
!447 = !DILocation(line: 251, column: 13, scope: !409)
!448 = !DILocation(line: 252, column: 18, scope: !442)
!449 = !DILocation(line: 252, column: 13, scope: !442)
!450 = !DILocation(line: 253, column: 27, scope: !409)
!451 = !DILocation(line: 253, column: 21, scope: !409)
!452 = !DILocation(line: 253, column: 10, scope: !409)
!453 = !DILocation(line: 253, column: 19, scope: !409)
!454 = !DILocation(line: 254, column: 19, scope: !455)
!455 = distinct !DILexicalBlock(scope: !409, file: !38, line: 254, column: 7)
!456 = !DILocation(line: 254, column: 8, scope: !457)
!457 = !DILexicalBlockFile(scope: !455, file: !38, discriminator: 2)
!458 = !DILocation(line: 254, column: 8, scope: !455)
!459 = !DILocation(line: 255, column: 4, scope: !455)
!460 = !DILocation(line: 255, column: 8, scope: !461)
!461 = !DILexicalBlockFile(scope: !455, file: !38, discriminator: 1)
!462 = !DILocation(line: 254, column: 7, scope: !463)
!463 = !DILexicalBlockFile(scope: !409, file: !38, discriminator: 1)
!464 = !DILocation(line: 256, column: 11, scope: !455)
!465 = !DILocation(line: 256, column: 20, scope: !455)
!466 = !DILocation(line: 256, column: 27, scope: !455)
!467 = !DILocation(line: 256, column: 4, scope: !455)
!468 = !DILocation(line: 258, column: 39, scope: !455)
!469 = !DILocation(line: 258, column: 29, scope: !461)
!470 = !DILocation(line: 258, column: 11, scope: !455)
!471 = !DILocation(line: 258, column: 20, scope: !455)
!472 = !DILocation(line: 258, column: 27, scope: !455)
!473 = !DILocation(line: 259, column: 12, scope: !474)
!474 = distinct !DILexicalBlock(scope: !409, file: !38, line: 259, column: 7)
!475 = !DILocation(line: 259, column: 26, scope: !474)
!476 = !DILocation(line: 259, column: 7, scope: !474)
!477 = !DILocation(line: 259, column: 71, scope: !474)
!478 = !DILocation(line: 259, column: 7, scope: !409)
!479 = !DILocation(line: 260, column: 12, scope: !480)
!480 = distinct !DILexicalBlock(scope: !474, file: !38, line: 259, column: 76)
!481 = !DILocation(line: 260, column: 50, scope: !480)
!482 = !DILocation(line: 260, column: 41, scope: !483)
!483 = !DILexicalBlockFile(scope: !480, file: !38, discriminator: 1)
!484 = !DILocation(line: 260, column: 4, scope: !485)
!485 = !DILexicalBlockFile(scope: !480, file: !38, discriminator: 2)
!486 = !DILocation(line: 261, column: 4, scope: !480)
!487 = !DILocation(line: 263, column: 14, scope: !488)
!488 = distinct !DILexicalBlock(scope: !409, file: !38, line: 263, column: 7)
!489 = !DILocation(line: 263, column: 7, scope: !488)
!490 = !DILocation(line: 263, column: 7, scope: !409)
!491 = !DILocation(line: 264, column: 12, scope: !492)
!492 = distinct !DILexicalBlock(scope: !488, file: !38, line: 263, column: 32)
!493 = !DILocation(line: 264, column: 52, scope: !492)
!494 = !DILocation(line: 264, column: 43, scope: !495)
!495 = !DILexicalBlockFile(scope: !492, file: !38, discriminator: 1)
!496 = !DILocation(line: 264, column: 4, scope: !497)
!497 = !DILexicalBlockFile(scope: !492, file: !38, discriminator: 2)
!498 = !DILocation(line: 265, column: 4, scope: !492)
!499 = !DILocation(line: 269, column: 21, scope: !500)
!500 = distinct !DILexicalBlock(scope: !409, file: !38, line: 269, column: 21)
!501 = !DILocation(line: 269, column: 34, scope: !500)
!502 = !DILocation(line: 269, column: 21, scope: !409)
!503 = !DILocation(line: 271, column: 14, scope: !504)
!504 = distinct !DILexicalBlock(scope: !505, file: !38, line: 271, column: 7)
!505 = distinct !DILexicalBlock(scope: !500, file: !38, line: 270, column: 17)
!506 = !DILocation(line: 271, column: 12, scope: !504)
!507 = !DILocation(line: 271, column: 19, scope: !508)
!508 = !DILexicalBlockFile(scope: !509, file: !38, discriminator: 1)
!509 = distinct !DILexicalBlock(scope: !504, file: !38, line: 271, column: 7)
!510 = !DILocation(line: 271, column: 21, scope: !508)
!511 = !DILocation(line: 271, column: 7, scope: !508)
!512 = !DILocation(line: 272, column: 10, scope: !513)
!513 = distinct !DILexicalBlock(scope: !509, file: !38, line: 271, column: 31)
!514 = !DILocation(line: 272, column: 4, scope: !513)
!515 = !DILocation(line: 273, column: 4, scope: !513)
!516 = !DILocation(line: 274, column: 8, scope: !513)
!517 = !DILocation(line: 271, column: 27, scope: !518)
!518 = !DILexicalBlockFile(scope: !509, file: !38, discriminator: 2)
!519 = !DILocation(line: 271, column: 7, scope: !518)
!520 = !DILocation(line: 275, column: 17, scope: !505)
!521 = !DILocation(line: 277, column: 13, scope: !409)
!522 = !DILocation(line: 278, column: 3, scope: !409)
!523 = !DILocation(line: 278, column: 25, scope: !463)
!524 = !DILocation(line: 278, column: 39, scope: !463)
!525 = !DILocation(line: 278, column: 18, scope: !463)
!526 = !DILocation(line: 278, column: 16, scope: !463)
!527 = !DILocation(line: 278, column: 3, scope: !463)
!528 = !DILocalVariable(name: "pid", scope: !529, file: !38, line: 279, type: !250)
!529 = distinct !DILexicalBlock(scope: !409, file: !38, line: 278, column: 79)
!530 = !DILocation(line: 279, column: 10, scope: !529)
!531 = !DILocation(line: 284, column: 8, scope: !532)
!532 = distinct !DILexicalBlock(scope: !529, file: !38, line: 284, column: 8)
!533 = !DILocation(line: 284, column: 13, scope: !532)
!534 = !DILocation(line: 284, column: 8, scope: !529)
!535 = !DILocation(line: 285, column: 11, scope: !536)
!536 = distinct !DILexicalBlock(scope: !532, file: !38, line: 284, column: 18)
!537 = !DILocation(line: 285, column: 9, scope: !536)
!538 = !DILocation(line: 286, column: 10, scope: !539)
!539 = distinct !DILexicalBlock(scope: !536, file: !38, line: 286, column: 9)
!540 = !DILocation(line: 286, column: 9, scope: !536)
!541 = !DILocation(line: 287, column: 6, scope: !542)
!542 = distinct !DILexicalBlock(scope: !539, file: !38, line: 286, column: 15)
!543 = !DILocation(line: 288, column: 6, scope: !542)
!544 = !DILocation(line: 289, column: 6, scope: !542)
!545 = !DILocation(line: 290, column: 15, scope: !542)
!546 = !DILocation(line: 291, column: 11, scope: !542)
!547 = !DILocation(line: 291, column: 24, scope: !542)
!548 = !DILocation(line: 291, column: 17, scope: !542)
!549 = !DILocation(line: 291, column: 6, scope: !550)
!550 = !DILexicalBlockFile(scope: !542, file: !38, discriminator: 1)
!551 = !DILocation(line: 292, column: 11, scope: !542)
!552 = !DILocation(line: 292, column: 24, scope: !542)
!553 = !DILocation(line: 292, column: 17, scope: !542)
!554 = !DILocation(line: 292, column: 6, scope: !550)
!555 = !DILocation(line: 293, column: 6, scope: !542)
!556 = !DILocalVariable(name: "tmp_pid", scope: !557, file: !38, line: 295, type: !257)
!557 = distinct !DILexicalBlock(scope: !539, file: !38, line: 294, column: 12)
!558 = !DILocation(line: 295, column: 29, scope: !557)
!559 = !DILocation(line: 295, column: 39, scope: !557)
!560 = !DILocation(line: 296, column: 21, scope: !557)
!561 = !DILocation(line: 296, column: 6, scope: !557)
!562 = !DILocation(line: 296, column: 15, scope: !557)
!563 = !DILocation(line: 296, column: 19, scope: !557)
!564 = !DILocation(line: 297, column: 22, scope: !557)
!565 = !DILocation(line: 297, column: 6, scope: !557)
!566 = !DILocation(line: 297, column: 15, scope: !557)
!567 = !DILocation(line: 297, column: 20, scope: !557)
!568 = !DILocation(line: 298, column: 34, scope: !557)
!569 = !DILocation(line: 298, column: 6, scope: !557)
!570 = !DILocation(line: 300, column: 4, scope: !536)
!571 = !DILocation(line: 278, column: 3, scope: !572)
!572 = !DILexicalBlockFile(scope: !409, file: !38, discriminator: 2)
!573 = !DILocation(line: 302, column: 2, scope: !409)
!574 = !DILocation(line: 306, column: 12, scope: !53)
!575 = !DILocation(line: 306, column: 10, scope: !53)
!576 = !DILocation(line: 307, column: 16, scope: !53)
!577 = !DILocation(line: 307, column: 14, scope: !53)
!578 = !DILocation(line: 308, column: 16, scope: !53)
!579 = !DILocation(line: 308, column: 14, scope: !53)
!580 = !DILocation(line: 309, column: 2, scope: !53)
!581 = !DILocation(line: 310, column: 2, scope: !53)
!582 = !DILocation(line: 311, column: 2, scope: !53)
!583 = !DILocation(line: 312, column: 5, scope: !53)
!584 = !DILocation(line: 330, column: 25, scope: !53)
!585 = !DILocation(line: 330, column: 17, scope: !378)
!586 = !DILocation(line: 330, column: 15, scope: !53)
!587 = !DILocation(line: 331, column: 9, scope: !588)
!588 = distinct !DILexicalBlock(scope: !53, file: !38, line: 331, column: 9)
!589 = !DILocation(line: 331, column: 19, scope: !588)
!590 = !DILocation(line: 331, column: 9, scope: !53)
!591 = !DILocation(line: 332, column: 26, scope: !588)
!592 = !DILocation(line: 332, column: 24, scope: !588)
!593 = !DILocation(line: 332, column: 8, scope: !588)
!594 = !DILocation(line: 334, column: 24, scope: !588)
!595 = !DILocation(line: 335, column: 10, scope: !596)
!596 = distinct !DILexicalBlock(scope: !53, file: !38, line: 335, column: 9)
!597 = !DILocation(line: 335, column: 9, scope: !53)
!598 = !DILocation(line: 336, column: 25, scope: !596)
!599 = !DILocation(line: 336, column: 9, scope: !596)
!600 = !DILocation(line: 338, column: 25, scope: !53)
!601 = !DILocation(line: 338, column: 17, scope: !378)
!602 = !DILocation(line: 338, column: 15, scope: !53)
!603 = !DILocation(line: 339, column: 9, scope: !604)
!604 = distinct !DILexicalBlock(scope: !53, file: !38, line: 339, column: 9)
!605 = !DILocation(line: 339, column: 19, scope: !604)
!606 = !DILocation(line: 339, column: 9, scope: !53)
!607 = !DILocation(line: 340, column: 23, scope: !604)
!608 = !DILocation(line: 340, column: 21, scope: !604)
!609 = !DILocation(line: 340, column: 8, scope: !604)
!610 = !DILocation(line: 342, column: 21, scope: !604)
!611 = !DILocation(line: 343, column: 10, scope: !612)
!612 = distinct !DILexicalBlock(scope: !53, file: !38, line: 343, column: 9)
!613 = !DILocation(line: 343, column: 9, scope: !53)
!614 = !DILocation(line: 344, column: 22, scope: !612)
!615 = !DILocation(line: 344, column: 9, scope: !612)
!616 = !DILocation(line: 345, column: 25, scope: !53)
!617 = !DILocation(line: 345, column: 17, scope: !378)
!618 = !DILocation(line: 345, column: 15, scope: !53)
!619 = !DILocation(line: 346, column: 9, scope: !620)
!620 = distinct !DILexicalBlock(scope: !53, file: !38, line: 346, column: 9)
!621 = !DILocation(line: 346, column: 19, scope: !620)
!622 = !DILocation(line: 346, column: 9, scope: !53)
!623 = !DILocation(line: 347, column: 23, scope: !620)
!624 = !DILocation(line: 347, column: 21, scope: !620)
!625 = !DILocation(line: 347, column: 8, scope: !620)
!626 = !DILocation(line: 349, column: 21, scope: !620)
!627 = !DILocation(line: 356, column: 11, scope: !628)
!628 = distinct !DILexicalBlock(scope: !53, file: !38, line: 356, column: 10)
!629 = !DILocation(line: 356, column: 24, scope: !628)
!630 = !DILocation(line: 356, column: 30, scope: !628)
!631 = !DILocation(line: 356, column: 34, scope: !632)
!632 = !DILexicalBlockFile(scope: !628, file: !38, discriminator: 1)
!633 = !DILocation(line: 356, column: 47, scope: !632)
!634 = !DILocation(line: 356, column: 10, scope: !632)
!635 = !DILocation(line: 357, column: 21, scope: !628)
!636 = !DILocation(line: 357, column: 8, scope: !628)
!637 = !DILocation(line: 360, column: 24, scope: !53)
!638 = !DILocation(line: 360, column: 22, scope: !53)
!639 = !DILocation(line: 361, column: 11, scope: !640)
!640 = distinct !DILexicalBlock(scope: !53, file: !38, line: 361, column: 9)
!641 = !DILocation(line: 361, column: 9, scope: !53)
!642 = !DILocation(line: 362, column: 25, scope: !640)
!643 = !DILocation(line: 362, column: 8, scope: !640)
!644 = !DILocation(line: 363, column: 25, scope: !53)
!645 = !DILocation(line: 363, column: 23, scope: !53)
!646 = !DILocation(line: 364, column: 11, scope: !647)
!647 = distinct !DILexicalBlock(scope: !53, file: !38, line: 364, column: 9)
!648 = !DILocation(line: 364, column: 9, scope: !53)
!649 = !DILocation(line: 365, column: 26, scope: !647)
!650 = !DILocation(line: 365, column: 8, scope: !647)
!651 = !DILocation(line: 368, column: 12, scope: !53)
!652 = !DILocation(line: 369, column: 28, scope: !653)
!653 = distinct !DILexicalBlock(scope: !53, file: !38, line: 369, column: 9)
!654 = !DILocation(line: 369, column: 21, scope: !653)
!655 = !DILocation(line: 369, column: 9, scope: !656)
!656 = !DILexicalBlockFile(scope: !653, file: !38, discriminator: 1)
!657 = !DILocation(line: 369, column: 9, scope: !653)
!658 = !DILocation(line: 369, column: 9, scope: !53)
!659 = !DILocation(line: 371, column: 27, scope: !660)
!660 = distinct !DILexicalBlock(scope: !653, file: !38, line: 369, column: 83)
!661 = !DILocation(line: 371, column: 18, scope: !662)
!662 = !DILexicalBlockFile(scope: !660, file: !38, discriminator: 1)
!663 = !DILocation(line: 370, column: 3, scope: !660)
!664 = !DILocation(line: 372, column: 3, scope: !660)
!665 = !DILocation(line: 374, column: 4, scope: !53)
!666 = !DILocation(line: 375, column: 20, scope: !53)
!667 = !DILocation(line: 375, column: 13, scope: !53)
!668 = !DILocation(line: 375, column: 54, scope: !53)
!669 = !DILocation(line: 375, column: 2, scope: !378)
!670 = !DILocation(line: 377, column: 20, scope: !53)
!671 = !DILocation(line: 377, column: 13, scope: !53)
!672 = !DILocation(line: 377, column: 54, scope: !53)
!673 = !DILocation(line: 377, column: 2, scope: !378)
!674 = !DILocation(line: 380, column: 27, scope: !675)
!675 = distinct !DILexicalBlock(scope: !53, file: !38, line: 380, column: 6)
!676 = !DILocation(line: 380, column: 7, scope: !677)
!677 = !DILexicalBlockFile(scope: !675, file: !38, discriminator: 1)
!678 = !DILocation(line: 380, column: 7, scope: !675)
!679 = !DILocation(line: 380, column: 6, scope: !53)
!680 = !DILocation(line: 381, column: 13, scope: !681)
!681 = distinct !DILexicalBlock(scope: !682, file: !38, line: 381, column: 7)
!682 = distinct !DILexicalBlock(scope: !675, file: !38, line: 380, column: 74)
!683 = !DILocation(line: 381, column: 11, scope: !681)
!684 = !DILocation(line: 381, column: 7, scope: !682)
!685 = !DILocation(line: 383, column: 24, scope: !686)
!686 = distinct !DILexicalBlock(scope: !687, file: !38, line: 383, column: 24)
!687 = distinct !DILexicalBlock(scope: !681, file: !38, line: 382, column: 17)
!688 = !DILocation(line: 383, column: 28, scope: !686)
!689 = !DILocation(line: 383, column: 24, scope: !687)
!690 = !DILocation(line: 384, column: 28, scope: !686)
!691 = !DILocation(line: 384, column: 32, scope: !686)
!692 = !DILocation(line: 384, column: 21, scope: !686)
!693 = !DILocation(line: 384, column: 19, scope: !686)
!694 = !DILocation(line: 384, column: 4, scope: !686)
!695 = !DILocation(line: 386, column: 40, scope: !686)
!696 = !DILocation(line: 387, column: 17, scope: !687)
!697 = !DILocation(line: 390, column: 39, scope: !698)
!698 = distinct !DILexicalBlock(scope: !681, file: !38, line: 389, column: 17)
!699 = !DILocation(line: 390, column: 37, scope: !698)
!700 = !DILocation(line: 391, column: 29, scope: !701)
!701 = distinct !DILexicalBlock(scope: !698, file: !38, line: 391, column: 29)
!702 = !DILocation(line: 391, column: 29, scope: !698)
!703 = !DILocation(line: 392, column: 52, scope: !701)
!704 = !DILocation(line: 392, column: 45, scope: !701)
!705 = !DILocation(line: 392, column: 43, scope: !701)
!706 = !DILocation(line: 392, column: 28, scope: !701)
!707 = !DILocation(line: 394, column: 43, scope: !701)
!708 = !DILocation(line: 397, column: 2, scope: !682)
!709 = !DILocation(line: 400, column: 29, scope: !710)
!710 = distinct !DILexicalBlock(scope: !675, file: !38, line: 399, column: 9)
!711 = !DILocation(line: 400, column: 27, scope: !710)
!712 = !DILocation(line: 401, column: 19, scope: !713)
!713 = distinct !DILexicalBlock(scope: !710, file: !38, line: 401, column: 19)
!714 = !DILocation(line: 401, column: 19, scope: !710)
!715 = !DILocation(line: 402, column: 42, scope: !713)
!716 = !DILocation(line: 402, column: 35, scope: !713)
!717 = !DILocation(line: 402, column: 33, scope: !713)
!718 = !DILocation(line: 402, column: 18, scope: !713)
!719 = !DILocation(line: 404, column: 33, scope: !713)
!720 = !DILocation(line: 407, column: 46, scope: !53)
!721 = !DILocation(line: 407, column: 2, scope: !53)
!722 = !DILocation(line: 408, column: 45, scope: !53)
!723 = !DILocation(line: 408, column: 9, scope: !53)
!724 = !DILocation(line: 409, column: 12, scope: !53)
!725 = !DILocation(line: 410, column: 21, scope: !53)
!726 = !DILocation(line: 410, column: 14, scope: !53)
!727 = !DILocation(line: 410, column: 2, scope: !378)
!728 = !DILocation(line: 411, column: 18, scope: !53)
!729 = !DILocation(line: 411, column: 2, scope: !378)
!730 = !DILocation(line: 413, column: 9, scope: !53)
!731 = !DILocation(line: 413, column: 23, scope: !53)
!732 = !DILocation(line: 413, column: 2, scope: !378)
!733 = !DILocation(line: 414, column: 10, scope: !53)
!734 = !DILocation(line: 414, column: 2, scope: !53)
!735 = !DILocation(line: 415, column: 13, scope: !736)
!736 = distinct !DILexicalBlock(scope: !53, file: !38, line: 415, column: 6)
!737 = !DILocation(line: 415, column: 6, scope: !736)
!738 = !DILocation(line: 415, column: 6, scope: !53)
!739 = !DILocation(line: 416, column: 13, scope: !740)
!740 = distinct !DILexicalBlock(scope: !741, file: !38, line: 416, column: 7)
!741 = distinct !DILexicalBlock(scope: !736, file: !38, line: 415, column: 25)
!742 = !DILocation(line: 416, column: 11, scope: !740)
!743 = !DILocation(line: 416, column: 7, scope: !741)
!744 = !DILocation(line: 417, column: 12, scope: !740)
!745 = !DILocation(line: 417, column: 23, scope: !740)
!746 = !DILocation(line: 417, column: 27, scope: !740)
!747 = !DILocation(line: 417, column: 4, scope: !740)
!748 = !DILocation(line: 419, column: 12, scope: !740)
!749 = !DILocation(line: 419, column: 32, scope: !740)
!750 = !DILocation(line: 419, column: 4, scope: !751)
!751 = !DILexicalBlockFile(scope: !740, file: !38, discriminator: 1)
!752 = !DILocation(line: 420, column: 2, scope: !741)
!753 = !DILocation(line: 421, column: 10, scope: !53)
!754 = !DILocation(line: 421, column: 30, scope: !53)
!755 = !DILocation(line: 421, column: 2, scope: !378)
!756 = !DILocation(line: 422, column: 39, scope: !53)
!757 = !DILocation(line: 422, column: 2, scope: !53)
!758 = !DILocation(line: 426, column: 15, scope: !53)
!759 = !DILocation(line: 426, column: 9, scope: !53)
!760 = !DILocation(line: 429, column: 2, scope: !53)
!761 = !DILocation(line: 429, column: 15, scope: !378)
!762 = !DILocation(line: 429, column: 28, scope: !378)
!763 = !DILocation(line: 429, column: 9, scope: !378)
!764 = !DILocation(line: 429, column: 2, scope: !378)
!765 = !DILocation(line: 430, column: 15, scope: !766)
!766 = distinct !DILexicalBlock(scope: !53, file: !38, line: 429, column: 36)
!767 = !DILocation(line: 430, column: 9, scope: !766)
!768 = !DILocation(line: 431, column: 20, scope: !766)
!769 = !DILocation(line: 431, column: 13, scope: !766)
!770 = !DILocation(line: 431, column: 25, scope: !766)
!771 = !DILocation(line: 431, column: 9, scope: !766)
!772 = !DILocation(line: 431, column: 30, scope: !766)
!773 = !DILocation(line: 432, column: 37, scope: !766)
!774 = !DILocation(line: 432, column: 9, scope: !766)
!775 = !DILocation(line: 436, column: 12, scope: !766)
!776 = !DILocation(line: 436, column: 3, scope: !766)
!777 = !DILocation(line: 429, column: 2, scope: !404)
!778 = !DILocation(line: 439, column: 13, scope: !779)
!779 = distinct !DILexicalBlock(scope: !53, file: !38, line: 439, column: 13)
!780 = !DILocation(line: 439, column: 13, scope: !53)
!781 = !DILocation(line: 439, column: 34, scope: !782)
!782 = !DILexicalBlockFile(scope: !779, file: !38, discriminator: 1)
!783 = !DILocation(line: 439, column: 29, scope: !782)
!784 = !DILocation(line: 440, column: 2, scope: !53)
!785 = !DILocation(line: 441, column: 1, scope: !53)
