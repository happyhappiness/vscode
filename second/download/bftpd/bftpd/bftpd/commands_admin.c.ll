; ModuleID = '/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/commands_admin.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.admin_command = type { i8*, void (i8*)* }
%struct.fd_set = type { [16 x i64] }
%struct.timeval = type { i64, i64 }
%struct.bftpdutmp = type { i8, i32, [31 x i8], [256 x i8], i64 }

@.str = private unnamed_addr constant [21 x i8] c"421 Login incorrect.\00", align 1
@.str.1 = private unnamed_addr constant [29 x i8] c"Administrative login FAILED\0A\00", align 1
@.str.2 = private unnamed_addr constant [11 x i8] c"ADMIN_PASS\00", align 1
@.str.3 = private unnamed_addr constant [10 x i8] c"%30s %30s\00", align 1
@user = external global [31 x i8], align 16
@.str.4 = private unnamed_addr constant [5 x i8] c"root\00", align 1
@.str.5 = private unnamed_addr constant [37 x i8] c"230 Administrative login successful.\00", align 1
@.str.6 = private unnamed_addr constant [33 x i8] c"Administrative login SUCCESSFUL\0A\00", align 1
@stdin = external global %struct._IO_FILE*, align 8
@.str.7 = private unnamed_addr constant [25 x i8] c"500 Not implemented yet.\00", align 1
@.str.8 = private unnamed_addr constant [35 x i8] c"200 Starting logfile transmission.\00", align 1
@statuslogforreading = external global %struct._IO_FILE*, align 8
@mystatuslog = common global %struct._IO_FILE* null, align 8
@stderr = external global %struct._IO_FILE*, align 8
@.str.9 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.10 = private unnamed_addr constant [34 x i8] c"202 Logfile transmission stopped.\00", align 1
@.str.11 = private unnamed_addr constant [35 x i8] c"201 Stopping logfile transmission.\00", align 1
@.str.12 = private unnamed_addr constant [27 x i8] c"200-User listing follows.\0A\00", align 1
@.str.13 = private unnamed_addr constant [61 x i8] c"200-PID       User           Host                Login time\0A\00", align 1
@bftpdutmp = external global %struct._IO_FILE*, align 8
@.str.14 = private unnamed_addr constant [22 x i8] c"200-%-10i%-15s%-20s%s\00", align 1
@.str.15 = private unnamed_addr constant [28 x i8] c"200 User listing finished.\0A\00", align 1
@.str.16 = private unnamed_addr constant [35 x i8] c"500 Error: Given PID is not valid.\00", align 1
@.str.17 = private unnamed_addr constant [15 x i8] c"500 Error: %s.\00", align 1
@.str.18 = private unnamed_addr constant [7 x i8] c"200 OK\00", align 1
@.str.19 = private unnamed_addr constant [51 x i8] c"500 Error: The given PID does not belong to bftpd.\00", align 1
@.str.20 = private unnamed_addr constant [21 x i8] c"221 See you later...\00", align 1
@.str.21 = private unnamed_addr constant [14 x i8] c"ADMIN_GETCONF\00", align 1
@.str.22 = private unnamed_addr constant [10 x i8] c"ADMIN_LOG\00", align 1
@.str.23 = private unnamed_addr constant [14 x i8] c"ADMIN_STOPLOG\00", align 1
@.str.24 = private unnamed_addr constant [10 x i8] c"ADMIN_WHO\00", align 1
@.str.25 = private unnamed_addr constant [11 x i8] c"ADMIN_KICK\00", align 1
@.str.26 = private unnamed_addr constant [11 x i8] c"ADMIN_QUIT\00", align 1
@admin_commands = constant [7 x %struct.admin_command] [%struct.admin_command { i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.21, i32 0, i32 0), void (i8*)* @command_admingetconf }, %struct.admin_command { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.22, i32 0, i32 0), void (i8*)* @command_adminlog }, %struct.admin_command { i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.23, i32 0, i32 0), void (i8*)* @command_adminstoplog }, %struct.admin_command { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.24, i32 0, i32 0), void (i8*)* @command_adminwho }, %struct.admin_command { i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.25, i32 0, i32 0), void (i8*)* @command_adminkick }, %struct.admin_command { i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.26, i32 0, i32 0), void (i8*)* @command_adminquit }, %struct.admin_command zeroinitializer], align 16
@.str.27 = private unnamed_addr constant [26 x i8] c"500 Unknown command: \22%s\22\00", align 1

; Function Attrs: nounwind uwtable
define void @loginfailed() #0 !dbg !16 {
entry:
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str, i32 0, i32 0)), !dbg !108
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.1, i32 0, i32 0)), !dbg !109
  call void @exit(i32 1) #8, !dbg !110
  unreachable, !dbg !110

return:                                           ; No predecessors!
  ret void, !dbg !111
}

declare void @control_printf(i8 signext, i8*, ...) #1

declare void @bftpd_log(i8*, ...) #1

; Function Attrs: noreturn nounwind
declare void @exit(i32) #2

; Function Attrs: nounwind uwtable
define void @command_adminlogin(i8* %params) #0 !dbg !20 {
entry:
  %params.addr = alloca i8*, align 8
  %adminpass = alloca [31 x i8], align 16
  %rootpass = alloca [31 x i8], align 16
  %buffer = alloca [256 x i8], align 16
  %realadminpass = alloca i8*, align 8
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !112, metadata !113), !dbg !114
  call void @llvm.dbg.declare(metadata [31 x i8]* %adminpass, metadata !115, metadata !113), !dbg !119
  call void @llvm.dbg.declare(metadata [31 x i8]* %rootpass, metadata !120, metadata !113), !dbg !121
  call void @llvm.dbg.declare(metadata [256 x i8]* %buffer, metadata !122, metadata !113), !dbg !126
  call void @llvm.dbg.declare(metadata i8** %realadminpass, metadata !127, metadata !113), !dbg !128
  %call = call i8* @config_getoption(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i32 0, i32 0)), !dbg !129
  store i8* %call, i8** %realadminpass, align 8, !dbg !128
  %0 = load i8*, i8** %params.addr, align 8, !dbg !130
  %arraydecay = getelementptr inbounds [31 x i8], [31 x i8]* %adminpass, i32 0, i32 0, !dbg !132
  %arraydecay1 = getelementptr inbounds [31 x i8], [31 x i8]* %rootpass, i32 0, i32 0, !dbg !133
  %call2 = call i32 (i8*, i8*, ...) @__isoc99_sscanf(i8* %0, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.3, i32 0, i32 0), i8* %arraydecay, i8* %arraydecay1) #9, !dbg !134
  %cmp = icmp slt i32 %call2, 2, !dbg !135
  br i1 %cmp, label %if.then, label %if.end, !dbg !136

if.then:                                          ; preds = %entry
  call void @loginfailed(), !dbg !137
  br label %if.end, !dbg !137

if.end:                                           ; preds = %if.then, %entry
  %1 = load i8*, i8** %realadminpass, align 8, !dbg !138
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 0, !dbg !138
  %2 = load i8, i8* %arrayidx, align 1, !dbg !138
  %tobool = icmp ne i8 %2, 0, !dbg !138
  br i1 %tobool, label %if.end4, label %if.then3, !dbg !140

if.then3:                                         ; preds = %if.end
  call void @loginfailed(), !dbg !141
  br label %if.end4, !dbg !141

if.end4:                                          ; preds = %if.then3, %if.end
  %arraydecay5 = getelementptr inbounds [31 x i8], [31 x i8]* %adminpass, i32 0, i32 0, !dbg !142
  %3 = load i8*, i8** %realadminpass, align 8, !dbg !144
  %call6 = call i8* @crypt(i8* %arraydecay5, i8* %3) #9, !dbg !145
  %4 = load i8*, i8** %realadminpass, align 8, !dbg !146
  %call7 = call i32 @strcmp(i8* %call6, i8* %4) #10, !dbg !147
  %tobool8 = icmp ne i32 %call7, 0, !dbg !149
  br i1 %tobool8, label %if.then9, label %if.end10, !dbg !150

if.then9:                                         ; preds = %if.end4
  call void @loginfailed(), !dbg !151
  br label %if.end10, !dbg !151

if.end10:                                         ; preds = %if.then9, %if.end4
  %call11 = call i8* @strcpy(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.4, i32 0, i32 0)) #9, !dbg !152
  call void (...) @init_userinfo(), !dbg !153
  %arraydecay12 = getelementptr inbounds [31 x i8], [31 x i8]* %rootpass, i32 0, i32 0, !dbg !154
  %call13 = call i32 @checkpass(i8* %arraydecay12), !dbg !156
  %tobool14 = icmp ne i32 %call13, 0, !dbg !156
  br i1 %tobool14, label %if.then15, label %if.end16, !dbg !157

if.then15:                                        ; preds = %if.end10
  call void @loginfailed(), !dbg !158
  br label %if.end16, !dbg !158

if.end16:                                         ; preds = %if.then15, %if.end10
  %call17 = call void (i32)* @signal(i32 14, void (i32)* inttoptr (i64 1 to void (i32)*)) #9, !dbg !159
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.5, i32 0, i32 0)), !dbg !160
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.6, i32 0, i32 0)), !dbg !161
  br label %while.cond, !dbg !162

while.cond:                                       ; preds = %while.body, %if.end16
  %arraydecay18 = getelementptr inbounds [256 x i8], [256 x i8]* %buffer, i32 0, i32 0, !dbg !163
  %5 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !165
  %call19 = call i8* @fgets(i8* %arraydecay18, i32 256, %struct._IO_FILE* %5), !dbg !166
  %tobool20 = icmp ne i8* %call19, null, !dbg !167
  br i1 %tobool20, label %while.body, label %while.end, !dbg !167

while.body:                                       ; preds = %while.cond
  %arraydecay21 = getelementptr inbounds [256 x i8], [256 x i8]* %buffer, i32 0, i32 0, !dbg !168
  %call22 = call i32 @admin_parsecmd(i8* %arraydecay21), !dbg !170
  br label %while.cond, !dbg !171

while.end:                                        ; preds = %while.cond
  call void @exit(i32 0) #8, !dbg !173
  unreachable, !dbg !173

return:                                           ; No predecessors!
  ret void, !dbg !174
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #3

declare i8* @config_getoption(i8*) #1

; Function Attrs: nounwind
declare i32 @__isoc99_sscanf(i8*, i8*, ...) #4

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #5

; Function Attrs: nounwind
declare i8* @crypt(i8*, i8*) #4

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #4

declare void @init_userinfo(...) #1

declare i32 @checkpass(i8*) #1

; Function Attrs: nounwind
declare void (i32)* @signal(i32, void (i32)*) #4

declare i8* @fgets(i8*, i32, %struct._IO_FILE*) #1

; Function Attrs: nounwind uwtable
define i32 @admin_parsecmd(i8* %str) #0 !dbg !31 {
entry:
  %retval = alloca i32, align 4
  %str.addr = alloca i8*, align 8
  %i = alloca i32, align 4
  %p = alloca i8*, align 8
  %pp = alloca i8*, align 8
  store i8* %str, i8** %str.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %str.addr, metadata !175, metadata !113), !dbg !176
  call void @llvm.dbg.declare(metadata i32* %i, metadata !177, metadata !113), !dbg !178
  call void @llvm.dbg.declare(metadata i8** %p, metadata !179, metadata !113), !dbg !180
  call void @llvm.dbg.declare(metadata i8** %pp, metadata !181, metadata !113), !dbg !182
  %0 = load i8*, i8** %str.addr, align 8, !dbg !183
  %call = call i64 @strlen(i8* %0) #10, !dbg !184
  %sub = sub i64 %call, 2, !dbg !185
  %1 = load i8*, i8** %str.addr, align 8, !dbg !186
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 %sub, !dbg !186
  store i8 0, i8* %arrayidx, align 1, !dbg !187
  %2 = load i8*, i8** %str.addr, align 8, !dbg !188
  store i8* %2, i8** %pp, align 8, !dbg !189
  store i8* %2, i8** %p, align 8, !dbg !190
  br label %while.cond, !dbg !191

while.cond:                                       ; preds = %if.end, %entry
  %3 = load i8*, i8** %p, align 8, !dbg !192
  %4 = load i8, i8* %3, align 1, !dbg !194
  %tobool = icmp ne i8 %4, 0, !dbg !195
  br i1 %tobool, label %while.body, label %while.end, !dbg !195

while.body:                                       ; preds = %while.cond
  %5 = load i8*, i8** %p, align 8, !dbg !196
  %6 = load i8, i8* %5, align 1, !dbg !198
  %conv = zext i8 %6 to i32, !dbg !199
  %cmp = icmp slt i32 %conv, 32, !dbg !200
  br i1 %cmp, label %if.then, label %if.else, !dbg !201

if.then:                                          ; preds = %while.body
  %7 = load i8*, i8** %p, align 8, !dbg !202
  %incdec.ptr = getelementptr inbounds i8, i8* %7, i32 1, !dbg !202
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !202
  br label %if.end, !dbg !203

if.else:                                          ; preds = %while.body
  %8 = load i8*, i8** %p, align 8, !dbg !204
  %incdec.ptr2 = getelementptr inbounds i8, i8* %8, i32 1, !dbg !204
  store i8* %incdec.ptr2, i8** %p, align 8, !dbg !204
  %9 = load i8, i8* %8, align 1, !dbg !205
  %10 = load i8*, i8** %pp, align 8, !dbg !206
  %incdec.ptr3 = getelementptr inbounds i8, i8* %10, i32 1, !dbg !206
  store i8* %incdec.ptr3, i8** %pp, align 8, !dbg !206
  store i8 %9, i8* %10, align 1, !dbg !207
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  br label %while.cond, !dbg !208

while.end:                                        ; preds = %while.cond
  %11 = load i8*, i8** %pp, align 8, !dbg !210
  %incdec.ptr4 = getelementptr inbounds i8, i8* %11, i32 1, !dbg !210
  store i8* %incdec.ptr4, i8** %pp, align 8, !dbg !210
  store i8 0, i8* %11, align 1, !dbg !211
  store i32 0, i32* %i, align 4, !dbg !212
  br label %for.cond, !dbg !214

for.cond:                                         ; preds = %for.inc, %while.end
  %12 = load i32, i32* %i, align 4, !dbg !215
  %idxprom = sext i32 %12 to i64, !dbg !218
  %arrayidx5 = getelementptr inbounds [7 x %struct.admin_command], [7 x %struct.admin_command]* @admin_commands, i64 0, i64 %idxprom, !dbg !218
  %name = getelementptr inbounds %struct.admin_command, %struct.admin_command* %arrayidx5, i32 0, i32 0, !dbg !219
  %13 = load i8*, i8** %name, align 16, !dbg !219
  %tobool6 = icmp ne i8* %13, null, !dbg !220
  br i1 %tobool6, label %for.body, label %for.end, !dbg !220

for.body:                                         ; preds = %for.cond
  %14 = load i8*, i8** %str.addr, align 8, !dbg !221
  %15 = load i32, i32* %i, align 4, !dbg !224
  %idxprom7 = sext i32 %15 to i64, !dbg !225
  %arrayidx8 = getelementptr inbounds [7 x %struct.admin_command], [7 x %struct.admin_command]* @admin_commands, i64 0, i64 %idxprom7, !dbg !225
  %name9 = getelementptr inbounds %struct.admin_command, %struct.admin_command* %arrayidx8, i32 0, i32 0, !dbg !226
  %16 = load i8*, i8** %name9, align 16, !dbg !226
  %17 = load i32, i32* %i, align 4, !dbg !227
  %idxprom10 = sext i32 %17 to i64, !dbg !228
  %arrayidx11 = getelementptr inbounds [7 x %struct.admin_command], [7 x %struct.admin_command]* @admin_commands, i64 0, i64 %idxprom10, !dbg !228
  %name12 = getelementptr inbounds %struct.admin_command, %struct.admin_command* %arrayidx11, i32 0, i32 0, !dbg !229
  %18 = load i8*, i8** %name12, align 16, !dbg !229
  %call13 = call i64 @strlen(i8* %18) #10, !dbg !230
  %call14 = call i32 @strncasecmp(i8* %14, i8* %16, i64 %call13) #10, !dbg !231
  %tobool15 = icmp ne i32 %call14, 0, !dbg !233
  br i1 %tobool15, label %if.end38, label %if.then16, !dbg !234

if.then16:                                        ; preds = %for.body
  %19 = load i8*, i8** %str.addr, align 8, !dbg !235
  %20 = load i32, i32* %i, align 4, !dbg !237
  %idxprom17 = sext i32 %20 to i64, !dbg !238
  %arrayidx18 = getelementptr inbounds [7 x %struct.admin_command], [7 x %struct.admin_command]* @admin_commands, i64 0, i64 %idxprom17, !dbg !238
  %name19 = getelementptr inbounds %struct.admin_command, %struct.admin_command* %arrayidx18, i32 0, i32 0, !dbg !239
  %21 = load i8*, i8** %name19, align 16, !dbg !239
  %call20 = call i64 @strlen(i8* %21) #10, !dbg !240
  %conv21 = trunc i64 %call20 to i32, !dbg !240
  call void @cutto(i8* %19, i32 %conv21), !dbg !241
  %22 = load i8*, i8** %str.addr, align 8, !dbg !243
  store i8* %22, i8** %p, align 8, !dbg !244
  br label %while.cond22, !dbg !245

while.cond22:                                     ; preds = %while.body31, %if.then16
  %23 = load i8*, i8** %p, align 8, !dbg !246
  %24 = load i8, i8* %23, align 1, !dbg !247
  %conv23 = sext i8 %24 to i32, !dbg !248
  %tobool24 = icmp ne i32 %conv23, 0, !dbg !248
  br i1 %tobool24, label %land.rhs, label %land.end, !dbg !249

land.rhs:                                         ; preds = %while.cond22
  %25 = load i8*, i8** %p, align 8, !dbg !250
  %26 = load i8, i8* %25, align 1, !dbg !252
  %conv25 = sext i8 %26 to i32, !dbg !252
  %cmp26 = icmp eq i32 %conv25, 32, !dbg !253
  br i1 %cmp26, label %lor.end, label %lor.rhs, !dbg !254

lor.rhs:                                          ; preds = %land.rhs
  %27 = load i8*, i8** %p, align 8, !dbg !255
  %28 = load i8, i8* %27, align 1, !dbg !257
  %conv28 = sext i8 %28 to i32, !dbg !257
  %cmp29 = icmp eq i32 %conv28, 9, !dbg !258
  br label %lor.end, !dbg !259

lor.end:                                          ; preds = %lor.rhs, %land.rhs
  %29 = phi i1 [ true, %land.rhs ], [ %cmp29, %lor.rhs ]
  br label %land.end

land.end:                                         ; preds = %lor.end, %while.cond22
  %30 = phi i1 [ false, %while.cond22 ], [ %29, %lor.end ]
  br i1 %30, label %while.body31, label %while.end33, !dbg !260

while.body31:                                     ; preds = %land.end
  %31 = load i8*, i8** %p, align 8, !dbg !262
  %incdec.ptr32 = getelementptr inbounds i8, i8* %31, i32 1, !dbg !262
  store i8* %incdec.ptr32, i8** %p, align 8, !dbg !262
  br label %while.cond22, !dbg !263

while.end33:                                      ; preds = %land.end
  %32 = load i8*, i8** %str.addr, align 8, !dbg !265
  %33 = load i8*, i8** %p, align 8, !dbg !266
  %34 = load i8*, i8** %str.addr, align 8, !dbg !267
  %call34 = call i64 @strlen(i8* %34) #10, !dbg !268
  %35 = load i8*, i8** %p, align 8, !dbg !269
  %36 = load i8*, i8** %str.addr, align 8, !dbg !270
  %sub.ptr.lhs.cast = ptrtoint i8* %35 to i64, !dbg !271
  %sub.ptr.rhs.cast = ptrtoint i8* %36 to i64, !dbg !271
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !271
  %sub35 = sub i64 %call34, %sub.ptr.sub, !dbg !272
  %add = add i64 %sub35, 1, !dbg !273
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %32, i8* %33, i64 %add, i32 1, i1 false), !dbg !274
  %37 = load i32, i32* %i, align 4, !dbg !275
  %idxprom36 = sext i32 %37 to i64, !dbg !276
  %arrayidx37 = getelementptr inbounds [7 x %struct.admin_command], [7 x %struct.admin_command]* @admin_commands, i64 0, i64 %idxprom36, !dbg !276
  %function = getelementptr inbounds %struct.admin_command, %struct.admin_command* %arrayidx37, i32 0, i32 1, !dbg !277
  %38 = load void (i8*)*, void (i8*)** %function, align 8, !dbg !277
  %39 = load i8*, i8** %str.addr, align 8, !dbg !278
  call void %38(i8* %39), !dbg !276
  store i32 0, i32* %retval, align 4, !dbg !279
  br label %return, !dbg !279

if.end38:                                         ; preds = %for.body
  br label %for.inc, !dbg !280

for.inc:                                          ; preds = %if.end38
  %40 = load i32, i32* %i, align 4, !dbg !281
  %inc = add nsw i32 %40, 1, !dbg !281
  store i32 %inc, i32* %i, align 4, !dbg !281
  br label %for.cond, !dbg !283

for.end:                                          ; preds = %for.cond
  %41 = load i8*, i8** %str.addr, align 8, !dbg !284
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.27, i32 0, i32 0), i8* %41), !dbg !285
  store i32 1, i32* %retval, align 4, !dbg !286
  br label %return, !dbg !286

return:                                           ; preds = %for.end, %while.end33
  %42 = load i32, i32* %retval, align 4, !dbg !287
  ret i32 %42, !dbg !287
}

; Function Attrs: nounwind uwtable
define void @command_admingetconf(i8* %params) #0 !dbg !25 {
entry:
  %params.addr = alloca i8*, align 8
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !288, metadata !113), !dbg !289
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.7, i32 0, i32 0)), !dbg !290
  ret void, !dbg !291
}

; Function Attrs: nounwind uwtable
define void @command_adminlog(i8* %params) #0 !dbg !26 {
entry:
  %params.addr = alloca i8*, align 8
  %rfds = alloca %struct.fd_set, align 8
  %tv = alloca %struct.timeval, align 8
  %buffer = alloca [256 x i8], align 16
  %__d0 = alloca i32, align 4
  %__d1 = alloca i32, align 4
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !292, metadata !113), !dbg !293
  call void @llvm.dbg.declare(metadata %struct.fd_set* %rfds, metadata !294, metadata !113), !dbg !302
  call void @llvm.dbg.declare(metadata %struct.timeval* %tv, metadata !303, metadata !113), !dbg !311
  call void @llvm.dbg.declare(metadata [256 x i8]* %buffer, metadata !312, metadata !113), !dbg !313
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.8, i32 0, i32 0)), !dbg !314
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @statuslogforreading, align 8, !dbg !315
  store %struct._IO_FILE* %0, %struct._IO_FILE** @mystatuslog, align 8, !dbg !316
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @mystatuslog, align 8, !dbg !317
  %call = call i32 @fseek(%struct._IO_FILE* %1, i64 0, i32 2), !dbg !318
  br label %while.cond, !dbg !319

while.cond:                                       ; preds = %if.end17, %entry
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** @mystatuslog, align 8, !dbg !320
  %tobool = icmp ne %struct._IO_FILE* %2, null, !dbg !322
  br i1 %tobool, label %while.body, label %while.end18, !dbg !322

while.body:                                       ; preds = %while.cond
  br label %while.cond1, !dbg !323

while.cond1:                                      ; preds = %while.body4, %while.body
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %buffer, i32 0, i32 0, !dbg !325
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** @mystatuslog, align 8, !dbg !327
  %call2 = call i8* @fgets(i8* %arraydecay, i32 256, %struct._IO_FILE* %3), !dbg !328
  %tobool3 = icmp ne i8* %call2, null, !dbg !329
  br i1 %tobool3, label %while.body4, label %while.end, !dbg !329

while.body4:                                      ; preds = %while.cond1
  %4 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !330
  %arraydecay5 = getelementptr inbounds [256 x i8], [256 x i8]* %buffer, i32 0, i32 0, !dbg !331
  %call6 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %4, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.9, i32 0, i32 0), i8* %arraydecay5), !dbg !332
  br label %while.cond1, !dbg !333

while.end:                                        ; preds = %while.cond1
  br label %do.body, !dbg !335

do.body:                                          ; preds = %while.end
  call void @llvm.dbg.declare(metadata i32* %__d0, metadata !336, metadata !113), !dbg !338
  call void @llvm.dbg.declare(metadata i32* %__d1, metadata !339, metadata !113), !dbg !338
  %__fds_bits = getelementptr inbounds %struct.fd_set, %struct.fd_set* %rfds, i32 0, i32 0, !dbg !340
  %arrayidx = getelementptr inbounds [16 x i64], [16 x i64]* %__fds_bits, i64 0, i64 0, !dbg !340
  %5 = call { i64, i64* } asm sideeffect "cld; rep; stosq", "={cx},={di},{ax},0,1,~{memory},~{dirflag},~{fpsr},~{flags}"(i32 0, i64 16, i64* %arrayidx) #9, !dbg !340, !srcloc !342
  %asmresult = extractvalue { i64, i64* } %5, 0, !dbg !340
  %asmresult7 = extractvalue { i64, i64* } %5, 1, !dbg !340
  %6 = trunc i64 %asmresult to i32, !dbg !340
  store i32 %6, i32* %__d0, align 4, !dbg !340
  %7 = ptrtoint i64* %asmresult7 to i64, !dbg !340
  %8 = trunc i64 %7 to i32, !dbg !340
  store i32 %8, i32* %__d1, align 4, !dbg !340
  br label %do.end, !dbg !340

do.end:                                           ; preds = %do.body
  %__fds_bits8 = getelementptr inbounds %struct.fd_set, %struct.fd_set* %rfds, i32 0, i32 0, !dbg !343
  %arrayidx9 = getelementptr inbounds [16 x i64], [16 x i64]* %__fds_bits8, i64 0, i64 0, !dbg !343
  %9 = load i64, i64* %arrayidx9, align 8, !dbg !343
  %or = or i64 %9, 1, !dbg !343
  store i64 %or, i64* %arrayidx9, align 8, !dbg !343
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %tv, i32 0, i32 0, !dbg !344
  store i64 1, i64* %tv_sec, align 8, !dbg !345
  %tv_usec = getelementptr inbounds %struct.timeval, %struct.timeval* %tv, i32 0, i32 1, !dbg !346
  store i64 0, i64* %tv_usec, align 8, !dbg !347
  %call10 = call i32 @select(i32 1, %struct.fd_set* %rfds, %struct.fd_set* null, %struct.fd_set* null, %struct.timeval* %tv), !dbg !348
  %cmp = icmp sgt i32 %call10, 0, !dbg !350
  br i1 %cmp, label %if.then, label %if.end17, !dbg !351

if.then:                                          ; preds = %do.end
  %arraydecay11 = getelementptr inbounds [256 x i8], [256 x i8]* %buffer, i32 0, i32 0, !dbg !352
  %10 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !355
  %call12 = call i8* @fgets(i8* %arraydecay11, i32 256, %struct._IO_FILE* %10), !dbg !356
  %tobool13 = icmp ne i8* %call12, null, !dbg !356
  br i1 %tobool13, label %if.end, label %if.then14, !dbg !357

if.then14:                                        ; preds = %if.then
  call void @exit(i32 0) #8, !dbg !358
  unreachable, !dbg !358

if.end:                                           ; preds = %if.then
  %arraydecay15 = getelementptr inbounds [256 x i8], [256 x i8]* %buffer, i32 0, i32 0, !dbg !359
  %call16 = call i32 @admin_parsecmd(i8* %arraydecay15), !dbg !360
  br label %if.end17, !dbg !361

if.end17:                                         ; preds = %if.end, %do.end
  br label %while.cond, !dbg !362

while.end18:                                      ; preds = %while.cond
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.10, i32 0, i32 0)), !dbg !364
  ret void, !dbg !365
}

declare i32 @fseek(%struct._IO_FILE*, i64, i32) #1

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #1

declare i32 @select(i32, %struct.fd_set*, %struct.fd_set*, %struct.fd_set*, %struct.timeval*) #1

; Function Attrs: nounwind uwtable
define void @command_adminstoplog(i8* %params) #0 !dbg !27 {
entry:
  %params.addr = alloca i8*, align 8
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !366, metadata !113), !dbg !367
  store %struct._IO_FILE* null, %struct._IO_FILE** @mystatuslog, align 8, !dbg !368
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.11, i32 0, i32 0)), !dbg !369
  ret void, !dbg !370
}

; Function Attrs: nounwind uwtable
define void @command_adminwho(i8* %params) #0 !dbg !28 {
entry:
  %params.addr = alloca i8*, align 8
  %tmp = alloca %struct.bftpdutmp, align 8
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !371, metadata !113), !dbg !372
  call void @llvm.dbg.declare(metadata %struct.bftpdutmp* %tmp, metadata !373, metadata !113), !dbg !386
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !387
  %call = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %0, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.12, i32 0, i32 0)), !dbg !388
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !389
  %call1 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %1, i8* getelementptr inbounds ([61 x i8], [61 x i8]* @.str.13, i32 0, i32 0)), !dbg !390
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !391
  call void @rewind(%struct._IO_FILE* %2), !dbg !392
  br label %while.cond, !dbg !393

while.cond:                                       ; preds = %if.end, %if.then, %entry
  %3 = bitcast %struct.bftpdutmp* %tmp to i8*, !dbg !394
  %4 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !396
  %call2 = call i64 @fread(i8* %3, i64 304, i64 1, %struct._IO_FILE* %4), !dbg !397
  %tobool = icmp ne i64 %call2, 0, !dbg !398
  br i1 %tobool, label %while.body, label %while.end, !dbg !398

while.body:                                       ; preds = %while.cond
  %bu_type = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %tmp, i32 0, i32 0, !dbg !399
  %5 = load i8, i8* %bu_type, align 8, !dbg !399
  %tobool3 = icmp ne i8 %5, 0, !dbg !402
  br i1 %tobool3, label %if.end, label %if.then, !dbg !403

if.then:                                          ; preds = %while.body
  br label %while.cond, !dbg !404

if.end:                                           ; preds = %while.body
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !405
  %bu_pid = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %tmp, i32 0, i32 1, !dbg !406
  %7 = load i32, i32* %bu_pid, align 4, !dbg !406
  %bu_name = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %tmp, i32 0, i32 2, !dbg !407
  %arraydecay = getelementptr inbounds [31 x i8], [31 x i8]* %bu_name, i32 0, i32 0, !dbg !408
  %bu_host = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %tmp, i32 0, i32 3, !dbg !409
  %arraydecay4 = getelementptr inbounds [256 x i8], [256 x i8]* %bu_host, i32 0, i32 0, !dbg !410
  %bu_time = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %tmp, i32 0, i32 4, !dbg !411
  %call5 = call i8* @ctime(i64* %bu_time) #9, !dbg !412
  %call6 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %6, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.14, i32 0, i32 0), i32 %7, i8* %arraydecay, i8* %arraydecay4, i8* %call5), !dbg !413
  br label %while.cond, !dbg !414

while.end:                                        ; preds = %while.cond
  %8 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !416
  %call7 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %8, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.15, i32 0, i32 0)), !dbg !417
  ret void, !dbg !418
}

declare void @rewind(%struct._IO_FILE*) #1

declare i64 @fread(i8*, i64, i64, %struct._IO_FILE*) #1

; Function Attrs: nounwind
declare i8* @ctime(i64*) #4

; Function Attrs: nounwind uwtable
define void @command_adminkick(i8* %strpid) #0 !dbg !29 {
entry:
  %strpid.addr = alloca i8*, align 8
  %get_pid = alloca i64, align 8
  %pid = alloca i32, align 4
  store i8* %strpid, i8** %strpid.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %strpid.addr, metadata !419, metadata !113), !dbg !420
  call void @llvm.dbg.declare(metadata i64* %get_pid, metadata !421, metadata !113), !dbg !422
  %0 = load i8*, i8** %strpid.addr, align 8, !dbg !423
  %call = call i64 @strtoul(i8* %0, i8** null, i32 10) #9, !dbg !424
  store i64 %call, i64* %get_pid, align 8, !dbg !422
  call void @llvm.dbg.declare(metadata i32* %pid, metadata !425, metadata !113), !dbg !426
  %1 = load i64, i64* %get_pid, align 8, !dbg !427
  %cmp = icmp ule i64 %1, 2147483647, !dbg !429
  br i1 %cmp, label %if.then, label %if.else, !dbg !430

if.then:                                          ; preds = %entry
  %2 = load i64, i64* %get_pid, align 8, !dbg !431
  %conv = trunc i64 %2 to i32, !dbg !431
  store i32 %conv, i32* %pid, align 4, !dbg !432
  br label %if.end, !dbg !433

if.else:                                          ; preds = %entry
  store i32 0, i32* %pid, align 4, !dbg !434
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %3 = load i32, i32* %pid, align 4, !dbg !435
  %tobool = icmp ne i32 %3, 0, !dbg !435
  br i1 %tobool, label %if.else2, label %if.then1, !dbg !437

if.then1:                                         ; preds = %if.end
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.16, i32 0, i32 0)), !dbg !438
  br label %if.end15, !dbg !438

if.else2:                                         ; preds = %if.end
  %4 = load i32, i32* %pid, align 4, !dbg !439
  %call3 = call signext i8 @bftpdutmp_pidexists(i32 %4), !dbg !441
  %tobool4 = icmp ne i8 %call3, 0, !dbg !441
  br i1 %tobool4, label %if.then5, label %if.else13, !dbg !442

if.then5:                                         ; preds = %if.else2
  %5 = load i32, i32* %pid, align 4, !dbg !443
  %call6 = call i32 @kill(i32 %5, i32 15) #9, !dbg !446
  %tobool7 = icmp ne i32 %call6, 0, !dbg !446
  br i1 %tobool7, label %if.then8, label %if.else11, !dbg !447

if.then8:                                         ; preds = %if.then5
  %call9 = call i32* @__errno_location() #3, !dbg !448
  %6 = load i32, i32* %call9, align 4, !dbg !448
  %call10 = call i8* @strerror(i32 %6) #9, !dbg !449
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.17, i32 0, i32 0), i8* %call10), !dbg !451
  br label %if.end12, !dbg !453

if.else11:                                        ; preds = %if.then5
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.18, i32 0, i32 0)), !dbg !454
  br label %if.end12

if.end12:                                         ; preds = %if.else11, %if.then8
  br label %if.end14, !dbg !455

if.else13:                                        ; preds = %if.else2
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.19, i32 0, i32 0)), !dbg !456
  br label %if.end14

if.end14:                                         ; preds = %if.else13, %if.end12
  br label %if.end15

if.end15:                                         ; preds = %if.end14, %if.then1
  ret void, !dbg !457
}

; Function Attrs: nounwind
declare i64 @strtoul(i8*, i8**, i32) #4

declare signext i8 @bftpdutmp_pidexists(i32) #1

; Function Attrs: nounwind
declare i32 @kill(i32, i32) #4

; Function Attrs: nounwind
declare i8* @strerror(i32) #4

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #6

; Function Attrs: nounwind uwtable
define void @command_adminquit(i8* %params) #0 !dbg !30 {
entry:
  %params.addr = alloca i8*, align 8
  store i8* %params, i8** %params.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %params.addr, metadata !458, metadata !113), !dbg !459
  call void (i8, i8*, ...) @control_printf(i8 signext 1, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.20, i32 0, i32 0)), !dbg !460
  call void @exit(i32 0) #8, !dbg !461
  unreachable, !dbg !461

return:                                           ; No predecessors!
  ret void, !dbg !462
}

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #5

; Function Attrs: nounwind readonly
declare i32 @strncasecmp(i8*, i8*, i64) #5

declare void @cutto(i8*, i32) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #7

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readnone }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { argmemonly nounwind }
attributes #8 = { noreturn nounwind }
attributes #9 = { nounwind }
attributes #10 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!105, !106}
!llvm.ident = !{!107}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !15, globals: !34)
!1 = !DIFile(filename: "commands_admin.c", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!2 = !{}
!3 = !{!4, !10, !9, !13, !14}
!4 = !DIDerivedType(tag: DW_TAG_typedef, name: "__sighandler_t", file: !5, line: 85, baseType: !6)
!5 = !DIFile(filename: "/usr/include/signal.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!6 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !7, size: 64, align: 64)
!7 = !DISubroutineType(types: !8)
!8 = !{null, !9}
!9 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!10 = !DIDerivedType(tag: DW_TAG_typedef, name: "__fd_mask", file: !11, line: 54, baseType: !12)
!11 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/select.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!12 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!13 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!14 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!15 = !{!16, !20, !25, !26, !27, !28, !29, !30, !31}
!16 = distinct !DISubprogram(name: "loginfailed", scope: !17, file: !17, line: 26, type: !18, isLocal: false, isDefinition: true, scopeLine: 27, isOptimized: false, variables: !2)
!17 = !DIFile(filename: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/commands_admin.c", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!18 = !DISubroutineType(types: !19)
!19 = !{null}
!20 = distinct !DISubprogram(name: "command_adminlogin", scope: !17, file: !17, line: 33, type: !21, isLocal: false, isDefinition: true, scopeLine: 34, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!21 = !DISubroutineType(types: !22)
!22 = !{null, !23}
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64, align: 64)
!24 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!25 = distinct !DISubprogram(name: "command_admingetconf", scope: !17, file: !17, line: 60, type: !21, isLocal: false, isDefinition: true, scopeLine: 61, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!26 = distinct !DISubprogram(name: "command_adminlog", scope: !17, file: !17, line: 65, type: !21, isLocal: false, isDefinition: true, scopeLine: 66, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!27 = distinct !DISubprogram(name: "command_adminstoplog", scope: !17, file: !17, line: 90, type: !21, isLocal: false, isDefinition: true, scopeLine: 91, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!28 = distinct !DISubprogram(name: "command_adminwho", scope: !17, file: !17, line: 96, type: !21, isLocal: false, isDefinition: true, scopeLine: 97, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!29 = distinct !DISubprogram(name: "command_adminkick", scope: !17, file: !17, line: 111, type: !21, isLocal: false, isDefinition: true, scopeLine: 112, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!30 = distinct !DISubprogram(name: "command_adminquit", scope: !17, file: !17, line: 132, type: !21, isLocal: false, isDefinition: true, scopeLine: 133, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!31 = distinct !DISubprogram(name: "admin_parsecmd", scope: !17, file: !17, line: 148, type: !32, isLocal: false, isDefinition: true, scopeLine: 149, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!32 = !DISubroutineType(types: !33)
!33 = !{!9, !23}
!34 = !{!35, !46}
!35 = !DIGlobalVariable(name: "admin_commands", scope: !0, file: !17, line: 138, type: !36, isLocal: false, isDefinition: true, variable: [7 x %struct.admin_command]* @admin_commands)
!36 = !DICompositeType(tag: DW_TAG_array_type, baseType: !37, size: 896, align: 64, elements: !44)
!37 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !38)
!38 = !DICompositeType(tag: DW_TAG_structure_type, name: "admin_command", file: !39, line: 12, size: 128, align: 64, elements: !40)
!39 = !DIFile(filename: "./commands_admin.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!40 = !{!41, !42}
!41 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !38, file: !39, line: 13, baseType: !23, size: 64, align: 64)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "function", scope: !38, file: !39, line: 14, baseType: !43, size: 64, align: 64, offset: 64)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !21, size: 64, align: 64)
!44 = !{!45}
!45 = !DISubrange(count: 7)
!46 = !DIGlobalVariable(name: "mystatuslog", scope: !0, file: !17, line: 24, type: !47, isLocal: false, isDefinition: true, variable: %struct._IO_FILE** @mystatuslog)
!47 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !48, size: 64, align: 64)
!48 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !49, line: 48, baseType: !50)
!49 = !DIFile(filename: "/usr/include/stdio.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!50 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !51, line: 245, size: 1728, align: 64, elements: !52)
!51 = !DIFile(filename: "/usr/include/libio.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!52 = !{!53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !73, !74, !75, !76, !79, !81, !83, !87, !90, !92, !93, !94, !95, !96, !100, !101}
!53 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !50, file: !51, line: 246, baseType: !9, size: 32, align: 32)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !50, file: !51, line: 251, baseType: !23, size: 64, align: 64, offset: 64)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !50, file: !51, line: 252, baseType: !23, size: 64, align: 64, offset: 128)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !50, file: !51, line: 253, baseType: !23, size: 64, align: 64, offset: 192)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !50, file: !51, line: 254, baseType: !23, size: 64, align: 64, offset: 256)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !50, file: !51, line: 255, baseType: !23, size: 64, align: 64, offset: 320)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !50, file: !51, line: 256, baseType: !23, size: 64, align: 64, offset: 384)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !50, file: !51, line: 257, baseType: !23, size: 64, align: 64, offset: 448)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !50, file: !51, line: 258, baseType: !23, size: 64, align: 64, offset: 512)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !50, file: !51, line: 260, baseType: !23, size: 64, align: 64, offset: 576)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !50, file: !51, line: 261, baseType: !23, size: 64, align: 64, offset: 640)
!64 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !50, file: !51, line: 262, baseType: !23, size: 64, align: 64, offset: 704)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !50, file: !51, line: 264, baseType: !66, size: 64, align: 64, offset: 768)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !67, size: 64, align: 64)
!67 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !51, line: 160, size: 192, align: 64, elements: !68)
!68 = !{!69, !70, !72}
!69 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !67, file: !51, line: 161, baseType: !66, size: 64, align: 64)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !67, file: !51, line: 162, baseType: !71, size: 64, align: 64, offset: 64)
!71 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !67, file: !51, line: 166, baseType: !9, size: 32, align: 32, offset: 128)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !50, file: !51, line: 266, baseType: !71, size: 64, align: 64, offset: 832)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !50, file: !51, line: 268, baseType: !9, size: 32, align: 32, offset: 896)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !50, file: !51, line: 272, baseType: !9, size: 32, align: 32, offset: 928)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !50, file: !51, line: 274, baseType: !77, size: 64, align: 64, offset: 960)
!77 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !78, line: 131, baseType: !12)
!78 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!79 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !50, file: !51, line: 278, baseType: !80, size: 16, align: 16, offset: 1024)
!80 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !50, file: !51, line: 279, baseType: !82, size: 8, align: 8, offset: 1040)
!82 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !50, file: !51, line: 280, baseType: !84, size: 8, align: 8, offset: 1048)
!84 = !DICompositeType(tag: DW_TAG_array_type, baseType: !24, size: 8, align: 8, elements: !85)
!85 = !{!86}
!86 = !DISubrange(count: 1)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !50, file: !51, line: 284, baseType: !88, size: 64, align: 64, offset: 1088)
!88 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !89, size: 64, align: 64)
!89 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !51, line: 154, baseType: null)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !50, file: !51, line: 293, baseType: !91, size: 64, align: 64, offset: 1152)
!91 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !78, line: 132, baseType: !12)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !50, file: !51, line: 302, baseType: !13, size: 64, align: 64, offset: 1216)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !50, file: !51, line: 303, baseType: !13, size: 64, align: 64, offset: 1280)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !50, file: !51, line: 304, baseType: !13, size: 64, align: 64, offset: 1344)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !50, file: !51, line: 305, baseType: !13, size: 64, align: 64, offset: 1408)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !50, file: !51, line: 306, baseType: !97, size: 64, align: 64, offset: 1472)
!97 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !98, line: 62, baseType: !99)
!98 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!99 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !50, file: !51, line: 308, baseType: !9, size: 32, align: 32, offset: 1536)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !50, file: !51, line: 310, baseType: !102, size: 160, align: 8, offset: 1568)
!102 = !DICompositeType(tag: DW_TAG_array_type, baseType: !24, size: 160, align: 8, elements: !103)
!103 = !{!104}
!104 = !DISubrange(count: 20)
!105 = !{i32 2, !"Dwarf Version", i32 4}
!106 = !{i32 2, !"Debug Info Version", i32 3}
!107 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!108 = !DILocation(line: 28, column: 5, scope: !16)
!109 = !DILocation(line: 29, column: 5, scope: !16)
!110 = !DILocation(line: 30, column: 5, scope: !16)
!111 = !DILocation(line: 31, column: 1, scope: !16)
!112 = !DILocalVariable(name: "params", arg: 1, scope: !20, file: !17, line: 33, type: !23)
!113 = !DIExpression()
!114 = !DILocation(line: 33, column: 31, scope: !20)
!115 = !DILocalVariable(name: "adminpass", scope: !20, file: !17, line: 35, type: !116)
!116 = !DICompositeType(tag: DW_TAG_array_type, baseType: !24, size: 248, align: 8, elements: !117)
!117 = !{!118}
!118 = !DISubrange(count: 31)
!119 = !DILocation(line: 35, column: 10, scope: !20)
!120 = !DILocalVariable(name: "rootpass", scope: !20, file: !17, line: 36, type: !116)
!121 = !DILocation(line: 36, column: 10, scope: !20)
!122 = !DILocalVariable(name: "buffer", scope: !20, file: !17, line: 37, type: !123)
!123 = !DICompositeType(tag: DW_TAG_array_type, baseType: !24, size: 2048, align: 8, elements: !124)
!124 = !{!125}
!125 = !DISubrange(count: 256)
!126 = !DILocation(line: 37, column: 10, scope: !20)
!127 = !DILocalVariable(name: "realadminpass", scope: !20, file: !17, line: 38, type: !23)
!128 = !DILocation(line: 38, column: 11, scope: !20)
!129 = !DILocation(line: 38, column: 27, scope: !20)
!130 = !DILocation(line: 39, column: 16, scope: !131)
!131 = distinct !DILexicalBlock(scope: !20, file: !17, line: 39, column: 9)
!132 = !DILocation(line: 39, column: 37, scope: !131)
!133 = !DILocation(line: 39, column: 48, scope: !131)
!134 = !DILocation(line: 39, column: 9, scope: !131)
!135 = !DILocation(line: 39, column: 58, scope: !131)
!136 = !DILocation(line: 39, column: 9, scope: !20)
!137 = !DILocation(line: 40, column: 9, scope: !131)
!138 = !DILocation(line: 41, column: 10, scope: !139)
!139 = distinct !DILexicalBlock(scope: !20, file: !17, line: 41, column: 9)
!140 = !DILocation(line: 41, column: 9, scope: !20)
!141 = !DILocation(line: 42, column: 9, scope: !139)
!142 = !DILocation(line: 43, column: 22, scope: !143)
!143 = distinct !DILexicalBlock(scope: !20, file: !17, line: 43, column: 9)
!144 = !DILocation(line: 43, column: 33, scope: !143)
!145 = !DILocation(line: 43, column: 16, scope: !143)
!146 = !DILocation(line: 43, column: 49, scope: !143)
!147 = !DILocation(line: 43, column: 9, scope: !148)
!148 = !DILexicalBlockFile(scope: !143, file: !17, discriminator: 1)
!149 = !DILocation(line: 43, column: 9, scope: !143)
!150 = !DILocation(line: 43, column: 9, scope: !20)
!151 = !DILocation(line: 44, column: 9, scope: !143)
!152 = !DILocation(line: 46, column: 5, scope: !20)
!153 = !DILocation(line: 47, column: 5, scope: !20)
!154 = !DILocation(line: 48, column: 19, scope: !155)
!155 = distinct !DILexicalBlock(scope: !20, file: !17, line: 48, column: 9)
!156 = !DILocation(line: 48, column: 9, scope: !155)
!157 = !DILocation(line: 48, column: 9, scope: !20)
!158 = !DILocation(line: 49, column: 9, scope: !155)
!159 = !DILocation(line: 51, column: 5, scope: !20)
!160 = !DILocation(line: 52, column: 5, scope: !20)
!161 = !DILocation(line: 53, column: 5, scope: !20)
!162 = !DILocation(line: 54, column: 5, scope: !20)
!163 = !DILocation(line: 54, column: 18, scope: !164)
!164 = !DILexicalBlockFile(scope: !20, file: !17, discriminator: 1)
!165 = !DILocation(line: 54, column: 42, scope: !164)
!166 = !DILocation(line: 54, column: 12, scope: !164)
!167 = !DILocation(line: 54, column: 5, scope: !164)
!168 = !DILocation(line: 55, column: 24, scope: !169)
!169 = distinct !DILexicalBlock(scope: !20, file: !17, line: 54, column: 50)
!170 = !DILocation(line: 55, column: 9, scope: !169)
!171 = !DILocation(line: 54, column: 5, scope: !172)
!172 = !DILexicalBlockFile(scope: !20, file: !17, discriminator: 2)
!173 = !DILocation(line: 57, column: 5, scope: !20)
!174 = !DILocation(line: 58, column: 1, scope: !20)
!175 = !DILocalVariable(name: "str", arg: 1, scope: !31, file: !17, line: 148, type: !23)
!176 = !DILocation(line: 148, column: 26, scope: !31)
!177 = !DILocalVariable(name: "i", scope: !31, file: !17, line: 150, type: !9)
!178 = !DILocation(line: 150, column: 6, scope: !31)
!179 = !DILocalVariable(name: "p", scope: !31, file: !17, line: 151, type: !23)
!180 = !DILocation(line: 151, column: 8, scope: !31)
!181 = !DILocalVariable(name: "pp", scope: !31, file: !17, line: 151, type: !23)
!182 = !DILocation(line: 151, column: 12, scope: !31)
!183 = !DILocation(line: 152, column: 13, scope: !31)
!184 = !DILocation(line: 152, column: 6, scope: !31)
!185 = !DILocation(line: 152, column: 18, scope: !31)
!186 = !DILocation(line: 152, column: 2, scope: !31)
!187 = !DILocation(line: 152, column: 23, scope: !31)
!188 = !DILocation(line: 153, column: 11, scope: !31)
!189 = !DILocation(line: 153, column: 9, scope: !31)
!190 = !DILocation(line: 153, column: 4, scope: !31)
!191 = !DILocation(line: 154, column: 2, scope: !31)
!192 = !DILocation(line: 154, column: 10, scope: !193)
!193 = !DILexicalBlockFile(scope: !31, file: !17, discriminator: 1)
!194 = !DILocation(line: 154, column: 9, scope: !193)
!195 = !DILocation(line: 154, column: 2, scope: !193)
!196 = !DILocation(line: 155, column: 24, scope: !197)
!197 = distinct !DILexicalBlock(scope: !31, file: !17, line: 155, column: 7)
!198 = !DILocation(line: 155, column: 23, scope: !197)
!199 = !DILocation(line: 155, column: 7, scope: !197)
!200 = !DILocation(line: 155, column: 26, scope: !197)
!201 = !DILocation(line: 155, column: 7, scope: !31)
!202 = !DILocation(line: 156, column: 5, scope: !197)
!203 = !DILocation(line: 156, column: 4, scope: !197)
!204 = !DILocation(line: 158, column: 14, scope: !197)
!205 = !DILocation(line: 158, column: 12, scope: !197)
!206 = !DILocation(line: 158, column: 7, scope: !197)
!207 = !DILocation(line: 158, column: 10, scope: !197)
!208 = !DILocation(line: 154, column: 2, scope: !209)
!209 = !DILexicalBlockFile(scope: !31, file: !17, discriminator: 2)
!210 = !DILocation(line: 159, column: 5, scope: !31)
!211 = !DILocation(line: 159, column: 8, scope: !31)
!212 = !DILocation(line: 160, column: 9, scope: !213)
!213 = distinct !DILexicalBlock(scope: !31, file: !17, line: 160, column: 2)
!214 = !DILocation(line: 160, column: 7, scope: !213)
!215 = !DILocation(line: 160, column: 29, scope: !216)
!216 = !DILexicalBlockFile(scope: !217, file: !17, discriminator: 1)
!217 = distinct !DILexicalBlock(scope: !213, file: !17, line: 160, column: 2)
!218 = !DILocation(line: 160, column: 14, scope: !216)
!219 = !DILocation(line: 160, column: 32, scope: !216)
!220 = !DILocation(line: 160, column: 2, scope: !216)
!221 = !DILocation(line: 161, column: 20, scope: !222)
!222 = distinct !DILexicalBlock(scope: !223, file: !17, line: 161, column: 7)
!223 = distinct !DILexicalBlock(scope: !217, file: !17, line: 160, column: 43)
!224 = !DILocation(line: 161, column: 40, scope: !222)
!225 = !DILocation(line: 161, column: 25, scope: !222)
!226 = !DILocation(line: 161, column: 43, scope: !222)
!227 = !DILocation(line: 161, column: 71, scope: !222)
!228 = !DILocation(line: 161, column: 56, scope: !222)
!229 = !DILocation(line: 161, column: 74, scope: !222)
!230 = !DILocation(line: 161, column: 49, scope: !222)
!231 = !DILocation(line: 161, column: 8, scope: !232)
!232 = !DILexicalBlockFile(scope: !222, file: !17, discriminator: 1)
!233 = !DILocation(line: 161, column: 8, scope: !222)
!234 = !DILocation(line: 161, column: 7, scope: !223)
!235 = !DILocation(line: 162, column: 10, scope: !236)
!236 = distinct !DILexicalBlock(scope: !222, file: !17, line: 161, column: 82)
!237 = !DILocation(line: 162, column: 37, scope: !236)
!238 = !DILocation(line: 162, column: 22, scope: !236)
!239 = !DILocation(line: 162, column: 40, scope: !236)
!240 = !DILocation(line: 162, column: 15, scope: !236)
!241 = !DILocation(line: 162, column: 4, scope: !242)
!242 = !DILexicalBlockFile(scope: !236, file: !17, discriminator: 1)
!243 = !DILocation(line: 163, column: 8, scope: !236)
!244 = !DILocation(line: 163, column: 6, scope: !236)
!245 = !DILocation(line: 164, column: 4, scope: !236)
!246 = !DILocation(line: 164, column: 13, scope: !242)
!247 = !DILocation(line: 164, column: 12, scope: !242)
!248 = !DILocation(line: 164, column: 11, scope: !242)
!249 = !DILocation(line: 164, column: 16, scope: !242)
!250 = !DILocation(line: 164, column: 22, scope: !251)
!251 = !DILexicalBlockFile(scope: !236, file: !17, discriminator: 2)
!252 = !DILocation(line: 164, column: 21, scope: !251)
!253 = !DILocation(line: 164, column: 24, scope: !251)
!254 = !DILocation(line: 164, column: 32, scope: !251)
!255 = !DILocation(line: 164, column: 37, scope: !256)
!256 = !DILexicalBlockFile(scope: !236, file: !17, discriminator: 3)
!257 = !DILocation(line: 164, column: 36, scope: !256)
!258 = !DILocation(line: 164, column: 39, scope: !256)
!259 = !DILocation(line: 164, column: 32, scope: !256)
!260 = !DILocation(line: 164, column: 4, scope: !261)
!261 = !DILexicalBlockFile(scope: !236, file: !17, discriminator: 4)
!262 = !DILocation(line: 165, column: 6, scope: !236)
!263 = !DILocation(line: 164, column: 4, scope: !264)
!264 = !DILexicalBlockFile(scope: !236, file: !17, discriminator: 5)
!265 = !DILocation(line: 166, column: 12, scope: !236)
!266 = !DILocation(line: 166, column: 17, scope: !236)
!267 = !DILocation(line: 166, column: 27, scope: !236)
!268 = !DILocation(line: 166, column: 20, scope: !236)
!269 = !DILocation(line: 166, column: 35, scope: !236)
!270 = !DILocation(line: 166, column: 39, scope: !236)
!271 = !DILocation(line: 166, column: 37, scope: !236)
!272 = !DILocation(line: 166, column: 32, scope: !236)
!273 = !DILocation(line: 166, column: 44, scope: !236)
!274 = !DILocation(line: 166, column: 4, scope: !242)
!275 = !DILocation(line: 167, column: 19, scope: !236)
!276 = !DILocation(line: 167, column: 4, scope: !236)
!277 = !DILocation(line: 167, column: 22, scope: !236)
!278 = !DILocation(line: 167, column: 31, scope: !236)
!279 = !DILocation(line: 168, column: 4, scope: !236)
!280 = !DILocation(line: 170, column: 2, scope: !223)
!281 = !DILocation(line: 160, column: 39, scope: !282)
!282 = !DILexicalBlockFile(scope: !217, file: !17, discriminator: 2)
!283 = !DILocation(line: 160, column: 2, scope: !282)
!284 = !DILocation(line: 171, column: 60, scope: !31)
!285 = !DILocation(line: 171, column: 2, scope: !31)
!286 = !DILocation(line: 172, column: 2, scope: !31)
!287 = !DILocation(line: 173, column: 1, scope: !31)
!288 = !DILocalVariable(name: "params", arg: 1, scope: !25, file: !17, line: 60, type: !23)
!289 = !DILocation(line: 60, column: 33, scope: !25)
!290 = !DILocation(line: 62, column: 5, scope: !25)
!291 = !DILocation(line: 63, column: 1, scope: !25)
!292 = !DILocalVariable(name: "params", arg: 1, scope: !26, file: !17, line: 65, type: !23)
!293 = !DILocation(line: 65, column: 29, scope: !26)
!294 = !DILocalVariable(name: "rfds", scope: !26, file: !17, line: 67, type: !295)
!295 = !DIDerivedType(tag: DW_TAG_typedef, name: "fd_set", file: !11, line: 75, baseType: !296)
!296 = !DICompositeType(tag: DW_TAG_structure_type, file: !11, line: 64, size: 1024, align: 64, elements: !297)
!297 = !{!298}
!298 = !DIDerivedType(tag: DW_TAG_member, name: "__fds_bits", scope: !296, file: !11, line: 72, baseType: !299, size: 1024, align: 64)
!299 = !DICompositeType(tag: DW_TAG_array_type, baseType: !10, size: 1024, align: 64, elements: !300)
!300 = !{!301}
!301 = !DISubrange(count: 16)
!302 = !DILocation(line: 67, column: 12, scope: !26)
!303 = !DILocalVariable(name: "tv", scope: !26, file: !17, line: 68, type: !304)
!304 = !DICompositeType(tag: DW_TAG_structure_type, name: "timeval", file: !305, line: 30, size: 128, align: 64, elements: !306)
!305 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/time.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!306 = !{!307, !309}
!307 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !304, file: !305, line: 32, baseType: !308, size: 64, align: 64)
!308 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !78, line: 139, baseType: !12)
!309 = !DIDerivedType(tag: DW_TAG_member, name: "tv_usec", scope: !304, file: !305, line: 33, baseType: !310, size: 64, align: 64, offset: 64)
!310 = !DIDerivedType(tag: DW_TAG_typedef, name: "__suseconds_t", file: !78, line: 141, baseType: !12)
!311 = !DILocation(line: 68, column: 20, scope: !26)
!312 = !DILocalVariable(name: "buffer", scope: !26, file: !17, line: 69, type: !123)
!313 = !DILocation(line: 69, column: 10, scope: !26)
!314 = !DILocation(line: 70, column: 5, scope: !26)
!315 = !DILocation(line: 71, column: 19, scope: !26)
!316 = !DILocation(line: 71, column: 17, scope: !26)
!317 = !DILocation(line: 72, column: 11, scope: !26)
!318 = !DILocation(line: 72, column: 5, scope: !26)
!319 = !DILocation(line: 73, column: 5, scope: !26)
!320 = !DILocation(line: 73, column: 12, scope: !321)
!321 = !DILexicalBlockFile(scope: !26, file: !17, discriminator: 1)
!322 = !DILocation(line: 73, column: 5, scope: !321)
!323 = !DILocation(line: 74, column: 9, scope: !324)
!324 = distinct !DILexicalBlock(scope: !26, file: !17, line: 73, column: 25)
!325 = !DILocation(line: 74, column: 22, scope: !326)
!326 = !DILexicalBlockFile(scope: !324, file: !17, discriminator: 1)
!327 = !DILocation(line: 74, column: 46, scope: !326)
!328 = !DILocation(line: 74, column: 16, scope: !326)
!329 = !DILocation(line: 74, column: 9, scope: !326)
!330 = !DILocation(line: 76, column: 21, scope: !324)
!331 = !DILocation(line: 76, column: 35, scope: !324)
!332 = !DILocation(line: 76, column: 13, scope: !324)
!333 = !DILocation(line: 74, column: 9, scope: !334)
!334 = !DILexicalBlockFile(scope: !324, file: !17, discriminator: 2)
!335 = !DILocation(line: 77, column: 9, scope: !324)
!336 = !DILocalVariable(name: "__d0", scope: !337, file: !17, line: 77, type: !9)
!337 = distinct !DILexicalBlock(scope: !324, file: !17, line: 77, column: 9)
!338 = !DILocation(line: 77, column: 9, scope: !337)
!339 = !DILocalVariable(name: "__d1", scope: !337, file: !17, line: 77, type: !9)
!340 = !DILocation(line: 77, column: 9, scope: !341)
!341 = !DILexicalBlockFile(scope: !337, file: !17, discriminator: 1)
!342 = !{i32 -2146757333}
!343 = !DILocation(line: 78, column: 9, scope: !324)
!344 = !DILocation(line: 79, column: 12, scope: !324)
!345 = !DILocation(line: 79, column: 19, scope: !324)
!346 = !DILocation(line: 80, column: 12, scope: !324)
!347 = !DILocation(line: 80, column: 20, scope: !324)
!348 = !DILocation(line: 81, column: 13, scope: !349)
!349 = distinct !DILexicalBlock(scope: !324, file: !17, line: 81, column: 13)
!350 = !DILocation(line: 81, column: 47, scope: !349)
!351 = !DILocation(line: 81, column: 13, scope: !324)
!352 = !DILocation(line: 82, column: 24, scope: !353)
!353 = distinct !DILexicalBlock(scope: !354, file: !17, line: 82, column: 17)
!354 = distinct !DILexicalBlock(scope: !349, file: !17, line: 81, column: 52)
!355 = !DILocation(line: 82, column: 48, scope: !353)
!356 = !DILocation(line: 82, column: 18, scope: !353)
!357 = !DILocation(line: 82, column: 17, scope: !354)
!358 = !DILocation(line: 83, column: 17, scope: !353)
!359 = !DILocation(line: 84, column: 28, scope: !354)
!360 = !DILocation(line: 84, column: 13, scope: !354)
!361 = !DILocation(line: 85, column: 9, scope: !354)
!362 = !DILocation(line: 73, column: 5, scope: !363)
!363 = !DILexicalBlockFile(scope: !26, file: !17, discriminator: 2)
!364 = !DILocation(line: 87, column: 5, scope: !26)
!365 = !DILocation(line: 88, column: 1, scope: !26)
!366 = !DILocalVariable(name: "params", arg: 1, scope: !27, file: !17, line: 90, type: !23)
!367 = !DILocation(line: 90, column: 33, scope: !27)
!368 = !DILocation(line: 92, column: 17, scope: !27)
!369 = !DILocation(line: 93, column: 5, scope: !27)
!370 = !DILocation(line: 94, column: 1, scope: !27)
!371 = !DILocalVariable(name: "params", arg: 1, scope: !28, file: !17, line: 96, type: !23)
!372 = !DILocation(line: 96, column: 29, scope: !28)
!373 = !DILocalVariable(name: "tmp", scope: !28, file: !17, line: 98, type: !374)
!374 = !DICompositeType(tag: DW_TAG_structure_type, name: "bftpdutmp", file: !375, line: 9, size: 2432, align: 64, elements: !376)
!375 = !DIFile(filename: "./bftpdutmp.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!376 = !{!377, !378, !381, !382, !383}
!377 = !DIDerivedType(tag: DW_TAG_member, name: "bu_type", scope: !374, file: !375, line: 10, baseType: !24, size: 8, align: 8)
!378 = !DIDerivedType(tag: DW_TAG_member, name: "bu_pid", scope: !374, file: !375, line: 11, baseType: !379, size: 32, align: 32, offset: 32)
!379 = !DIDerivedType(tag: DW_TAG_typedef, name: "pid_t", file: !5, line: 61, baseType: !380)
!380 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pid_t", file: !78, line: 133, baseType: !9)
!381 = !DIDerivedType(tag: DW_TAG_member, name: "bu_name", scope: !374, file: !375, line: 12, baseType: !116, size: 248, align: 8, offset: 64)
!382 = !DIDerivedType(tag: DW_TAG_member, name: "bu_host", scope: !374, file: !375, line: 13, baseType: !123, size: 2048, align: 8, offset: 312)
!383 = !DIDerivedType(tag: DW_TAG_member, name: "bu_time", scope: !374, file: !375, line: 14, baseType: !384, size: 64, align: 64, offset: 2368)
!384 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !385, line: 75, baseType: !308)
!385 = !DIFile(filename: "/usr/include/time.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!386 = !DILocation(line: 98, column: 22, scope: !28)
!387 = !DILocation(line: 99, column: 13, scope: !28)
!388 = !DILocation(line: 99, column: 5, scope: !28)
!389 = !DILocation(line: 100, column: 13, scope: !28)
!390 = !DILocation(line: 100, column: 5, scope: !28)
!391 = !DILocation(line: 101, column: 12, scope: !28)
!392 = !DILocation(line: 101, column: 5, scope: !28)
!393 = !DILocation(line: 102, column: 5, scope: !28)
!394 = !DILocation(line: 102, column: 18, scope: !395)
!395 = !DILexicalBlockFile(scope: !28, file: !17, discriminator: 1)
!396 = !DILocation(line: 102, column: 49, scope: !395)
!397 = !DILocation(line: 102, column: 12, scope: !395)
!398 = !DILocation(line: 102, column: 5, scope: !395)
!399 = !DILocation(line: 103, column: 18, scope: !400)
!400 = distinct !DILexicalBlock(scope: !401, file: !17, line: 103, column: 13)
!401 = distinct !DILexicalBlock(scope: !28, file: !17, line: 102, column: 61)
!402 = !DILocation(line: 103, column: 14, scope: !400)
!403 = !DILocation(line: 103, column: 13, scope: !401)
!404 = !DILocation(line: 104, column: 13, scope: !400)
!405 = !DILocation(line: 105, column: 17, scope: !401)
!406 = !DILocation(line: 105, column: 54, scope: !401)
!407 = !DILocation(line: 105, column: 66, scope: !401)
!408 = !DILocation(line: 105, column: 62, scope: !401)
!409 = !DILocation(line: 105, column: 79, scope: !401)
!410 = !DILocation(line: 105, column: 75, scope: !401)
!411 = !DILocation(line: 106, column: 30, scope: !401)
!412 = !DILocation(line: 106, column: 18, scope: !401)
!413 = !DILocation(line: 105, column: 9, scope: !401)
!414 = !DILocation(line: 102, column: 5, scope: !415)
!415 = !DILexicalBlockFile(scope: !28, file: !17, discriminator: 2)
!416 = !DILocation(line: 108, column: 13, scope: !28)
!417 = !DILocation(line: 108, column: 5, scope: !28)
!418 = !DILocation(line: 109, column: 1, scope: !28)
!419 = !DILocalVariable(name: "strpid", arg: 1, scope: !29, file: !17, line: 111, type: !23)
!420 = !DILocation(line: 111, column: 30, scope: !29)
!421 = !DILocalVariable(name: "get_pid", scope: !29, file: !17, line: 113, type: !99)
!422 = !DILocation(line: 113, column: 23, scope: !29)
!423 = !DILocation(line: 113, column: 41, scope: !29)
!424 = !DILocation(line: 113, column: 33, scope: !29)
!425 = !DILocalVariable(name: "pid", scope: !29, file: !17, line: 114, type: !9)
!426 = !DILocation(line: 114, column: 9, scope: !29)
!427 = !DILocation(line: 116, column: 9, scope: !428)
!428 = distinct !DILexicalBlock(scope: !29, file: !17, line: 116, column: 9)
!429 = !DILocation(line: 116, column: 17, scope: !428)
!430 = !DILocation(line: 116, column: 9, scope: !29)
!431 = !DILocation(line: 117, column: 14, scope: !428)
!432 = !DILocation(line: 117, column: 12, scope: !428)
!433 = !DILocation(line: 117, column: 8, scope: !428)
!434 = !DILocation(line: 119, column: 12, scope: !428)
!435 = !DILocation(line: 121, column: 10, scope: !436)
!436 = distinct !DILexicalBlock(scope: !29, file: !17, line: 121, column: 9)
!437 = !DILocation(line: 121, column: 9, scope: !29)
!438 = !DILocation(line: 122, column: 9, scope: !436)
!439 = !DILocation(line: 123, column: 34, scope: !440)
!440 = distinct !DILexicalBlock(scope: !436, file: !17, line: 123, column: 14)
!441 = !DILocation(line: 123, column: 14, scope: !440)
!442 = !DILocation(line: 123, column: 14, scope: !436)
!443 = !DILocation(line: 124, column: 18, scope: !444)
!444 = distinct !DILexicalBlock(scope: !445, file: !17, line: 124, column: 13)
!445 = distinct !DILexicalBlock(scope: !440, file: !17, line: 123, column: 40)
!446 = !DILocation(line: 124, column: 13, scope: !444)
!447 = !DILocation(line: 124, column: 13, scope: !445)
!448 = !DILocation(line: 125, column: 67, scope: !444)
!449 = !DILocation(line: 125, column: 58, scope: !450)
!450 = !DILexicalBlockFile(scope: !444, file: !17, discriminator: 1)
!451 = !DILocation(line: 125, column: 13, scope: !452)
!452 = !DILexicalBlockFile(scope: !444, file: !17, discriminator: 2)
!453 = !DILocation(line: 125, column: 13, scope: !444)
!454 = !DILocation(line: 127, column: 13, scope: !444)
!455 = !DILocation(line: 128, column: 5, scope: !445)
!456 = !DILocation(line: 129, column: 9, scope: !440)
!457 = !DILocation(line: 130, column: 1, scope: !29)
!458 = !DILocalVariable(name: "params", arg: 1, scope: !30, file: !17, line: 132, type: !23)
!459 = !DILocation(line: 132, column: 30, scope: !30)
!460 = !DILocation(line: 134, column: 5, scope: !30)
!461 = !DILocation(line: 135, column: 5, scope: !30)
!462 = !DILocation(line: 136, column: 1, scope: !30)
