; ModuleID = '/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/logging.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.__va_list_tag = type { i32, i32, i8*, i8* }
%struct.tm = type { i32, i32, i32, i32, i32, i32, i32, i32, i32, i64, i8* }

@logfile = global %struct._IO_FILE* null, align 8
@send_receive_file = global %struct._IO_FILE* null, align 8
@statuslog = global %struct._IO_FILE* null, align 8
@statuslogforreading = global %struct._IO_FILE* null, align 8
@log_syslog = global i8 0, align 1
@.str = private unnamed_addr constant [8 x i8] c"LOGFILE\00", align 1
@.str.1 = private unnamed_addr constant [7 x i8] c"syslog\00", align 1
@global_argv = external global i8**, align 8
@.str.2 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@.str.3 = private unnamed_addr constant [72 x i8] c"421-Could not open log file.\0D\0A421 Server disabled for security reasons.\00", align 1
@.str.4 = private unnamed_addr constant [10 x i8] c"/dev/null\00", align 1
@.str.5 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@.str.6 = private unnamed_addr constant [13 x i8] c"%i %i %i %s\0A\00", align 1
@.str.7 = private unnamed_addr constant [14 x i8] c"%s %s[%i]: %s\00", align 1
@.str.8 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@Current_Date.output = internal global [32 x i8] zeroinitializer, align 16
@.str.9 = private unnamed_addr constant [9 x i8] c"%d-%d-%d\00", align 1
@.str.10 = private unnamed_addr constant [10 x i8] c"BANDWIDTH\00", align 1
@.str.11 = private unnamed_addr constant [10 x i8] c"%s/%s.txt\00", align 1
@.str.12 = private unnamed_addr constant [14 x i8] c"%s %.0f %.0f\0A\00", align 1
@configpath = common global i8* null, align 8
@daemonmode = common global i32 0, align 4
@pre_write_script = common global i8* null, align 8
@post_write_script = common global i8* null, align 8

; Function Attrs: nounwind uwtable
define void @log_init() #0 !dbg !8 {
entry:
  %foo = alloca i8*, align 8
  call void @llvm.dbg.declare(metadata i8** %foo, metadata !107, metadata !108), !dbg !109
  %call = call i8* @config_getoption(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0)), !dbg !110
  store i8* %call, i8** %foo, align 8, !dbg !109
  %0 = load i8*, i8** %foo, align 8, !dbg !111
  %call1 = call i32 @strcasecmp(i8* %0, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i32 0, i32 0)) #8, !dbg !113
  %tobool = icmp ne i32 %call1, 0, !dbg !113
  br i1 %tobool, label %if.else, label %if.then, !dbg !114

if.then:                                          ; preds = %entry
  store i8 1, i8* @log_syslog, align 1, !dbg !115
  %1 = load i8**, i8*** @global_argv, align 8, !dbg !117
  %arrayidx = getelementptr inbounds i8*, i8** %1, i64 0, !dbg !117
  %2 = load i8*, i8** %arrayidx, align 8, !dbg !117
  call void @openlog(i8* %2, i32 1, i32 24), !dbg !118
  br label %if.end9, !dbg !119

if.else:                                          ; preds = %entry
  %3 = load i8*, i8** %foo, align 8, !dbg !120
  %arrayidx2 = getelementptr inbounds i8, i8* %3, i64 0, !dbg !120
  %4 = load i8, i8* %arrayidx2, align 1, !dbg !120
  %tobool3 = icmp ne i8 %4, 0, !dbg !120
  br i1 %tobool3, label %if.then4, label %if.end8, !dbg !122

if.then4:                                         ; preds = %if.else
  %5 = load i8*, i8** %foo, align 8, !dbg !123
  %call5 = call %struct._IO_FILE* @fopen64(i8* %5, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0)), !dbg !125
  store %struct._IO_FILE* %call5, %struct._IO_FILE** @logfile, align 8, !dbg !126
  %tobool6 = icmp ne %struct._IO_FILE* %call5, null, !dbg !126
  br i1 %tobool6, label %if.end, label %if.then7, !dbg !127

if.then7:                                         ; preds = %if.then4
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.3, i32 0, i32 0)), !dbg !128
  call void @exit(i32 1) #9, !dbg !130
  unreachable, !dbg !130

if.end:                                           ; preds = %if.then4
  br label %if.end8, !dbg !131

if.end8:                                          ; preds = %if.end, %if.else
  br label %if.end9

if.end9:                                          ; preds = %if.end8, %if.then
  %call10 = call %struct._IO_FILE* @fopen64(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0)), !dbg !133
  store %struct._IO_FILE* %call10, %struct._IO_FILE** @statuslog, align 8, !dbg !134
  %call11 = call %struct._IO_FILE* @fopen64(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.5, i32 0, i32 0)), !dbg !135
  store %struct._IO_FILE* %call11, %struct._IO_FILE** @statuslogforreading, align 8, !dbg !136
  ret void, !dbg !137
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i8* @config_getoption(i8*) #2

; Function Attrs: nounwind readonly
declare i32 @strcasecmp(i8*, i8*) #3

declare void @openlog(i8*, i32, i32) #2

declare %struct._IO_FILE* @fopen64(i8*, i8*) #2

declare void @control_printf(i8 signext, i8*, ...) #2

; Function Attrs: noreturn nounwind
declare void @exit(i32) #4

; Function Attrs: nounwind uwtable
define void @bftpd_statuslog(i8 signext %type, i8 signext %type2, i8* %format, ...) #0 !dbg !12 {
entry:
  %type.addr = alloca i8, align 1
  %type2.addr = alloca i8, align 1
  %format.addr = alloca i8*, align 8
  %val = alloca [1 x %struct.__va_list_tag], align 16
  %buffer = alloca [1024 x i8], align 16
  store i8 %type, i8* %type.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %type.addr, metadata !138, metadata !108), !dbg !139
  store i8 %type2, i8* %type2.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %type2.addr, metadata !140, metadata !108), !dbg !141
  store i8* %format, i8** %format.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %format.addr, metadata !142, metadata !108), !dbg !143
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @statuslog, align 8, !dbg !144
  %tobool = icmp ne %struct._IO_FILE* %0, null, !dbg !144
  br i1 %tobool, label %if.then, label %if.end, !dbg !146

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %val, metadata !147, metadata !108), !dbg !161
  call void @llvm.dbg.declare(metadata [1024 x i8]* %buffer, metadata !162, metadata !108), !dbg !166
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %val, i32 0, i32 0, !dbg !167
  %arraydecay1 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !167
  call void @llvm.va_start(i8* %arraydecay1), !dbg !167
  %arraydecay2 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buffer, i32 0, i32 0, !dbg !168
  %1 = load i8*, i8** %format.addr, align 8, !dbg !169
  %arraydecay3 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %val, i32 0, i32 0, !dbg !170
  %call = call i32 @vsnprintf(i8* %arraydecay2, i64 1024, i8* %1, %struct.__va_list_tag* %arraydecay3) #5, !dbg !171
  %arraydecay4 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %val, i32 0, i32 0, !dbg !172
  %arraydecay45 = bitcast %struct.__va_list_tag* %arraydecay4 to i8*, !dbg !172
  call void @llvm.va_end(i8* %arraydecay45), !dbg !172
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** @statuslog, align 8, !dbg !173
  %call6 = call i32 @fseek(%struct._IO_FILE* %2, i64 0, i32 2), !dbg !174
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** @statuslog, align 8, !dbg !175
  %call7 = call i32 @getpid() #5, !dbg !176
  %4 = load i8, i8* %type.addr, align 1, !dbg !177
  %conv = sext i8 %4 to i32, !dbg !177
  %5 = load i8, i8* %type2.addr, align 1, !dbg !178
  %conv8 = sext i8 %5 to i32, !dbg !178
  %arraydecay9 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buffer, i32 0, i32 0, !dbg !179
  %call10 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %3, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.6, i32 0, i32 0), i32 %call7, i32 %conv, i32 %conv8, i8* %arraydecay9), !dbg !180
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** @statuslog, align 8, !dbg !182
  %call11 = call i32 @fflush(%struct._IO_FILE* %6), !dbg !183
  br label %if.end, !dbg !184

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !185
}

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #5

; Function Attrs: nounwind
declare i32 @vsnprintf(i8*, i64, i8*, %struct.__va_list_tag*) #6

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #5

declare i32 @fseek(%struct._IO_FILE*, i64, i32) #2

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #2

; Function Attrs: nounwind
declare i32 @getpid() #6

declare i32 @fflush(%struct._IO_FILE*) #2

; Function Attrs: nounwind uwtable
define void @bftpd_log(i8* %format, ...) #0 !dbg !15 {
entry:
  %format.addr = alloca i8*, align 8
  %val = alloca [1 x %struct.__va_list_tag], align 16
  %buffer = alloca [1024 x i8], align 16
  %timestr = alloca [40 x i8], align 16
  %t = alloca i64, align 8
  store i8* %format, i8** %format.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %format.addr, metadata !186, metadata !108), !dbg !187
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %val, metadata !188, metadata !108), !dbg !189
  call void @llvm.dbg.declare(metadata [1024 x i8]* %buffer, metadata !190, metadata !108), !dbg !191
  call void @llvm.dbg.declare(metadata [40 x i8]* %timestr, metadata !192, metadata !108), !dbg !196
  call void @llvm.dbg.declare(metadata i64* %t, metadata !197, metadata !108), !dbg !201
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %val, i32 0, i32 0, !dbg !202
  %arraydecay1 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !202
  call void @llvm.va_start(i8* %arraydecay1), !dbg !202
  %arraydecay2 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buffer, i32 0, i32 0, !dbg !203
  %0 = load i8*, i8** %format.addr, align 8, !dbg !204
  %arraydecay3 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %val, i32 0, i32 0, !dbg !205
  %call = call i32 @vsnprintf(i8* %arraydecay2, i64 1024, i8* %0, %struct.__va_list_tag* %arraydecay3) #5, !dbg !206
  %arraydecay4 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %val, i32 0, i32 0, !dbg !207
  %arraydecay45 = bitcast %struct.__va_list_tag* %arraydecay4 to i8*, !dbg !207
  call void @llvm.va_end(i8* %arraydecay45), !dbg !207
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @logfile, align 8, !dbg !208
  %tobool = icmp ne %struct._IO_FILE* %1, null, !dbg !208
  br i1 %tobool, label %if.then, label %if.else, !dbg !210

if.then:                                          ; preds = %entry
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** @logfile, align 8, !dbg !211
  %call6 = call i32 @fseek(%struct._IO_FILE* %2, i64 0, i32 2), !dbg !213
  %call7 = call i64 @time(i64* %t) #5, !dbg !214
  %arraydecay8 = getelementptr inbounds [40 x i8], [40 x i8]* %timestr, i32 0, i32 0, !dbg !215
  %call9 = call i8* @ctime(i64* %t) #5, !dbg !216
  %call10 = call i8* @strcpy(i8* %arraydecay8, i8* %call9) #5, !dbg !217
  %arraydecay11 = getelementptr inbounds [40 x i8], [40 x i8]* %timestr, i32 0, i32 0, !dbg !219
  %call12 = call i64 @strlen(i8* %arraydecay11) #8, !dbg !220
  %sub = sub i64 %call12, 1, !dbg !221
  %arrayidx = getelementptr inbounds [40 x i8], [40 x i8]* %timestr, i64 0, i64 %sub, !dbg !222
  store i8 0, i8* %arrayidx, align 1, !dbg !223
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** @logfile, align 8, !dbg !224
  %arraydecay13 = getelementptr inbounds [40 x i8], [40 x i8]* %timestr, i32 0, i32 0, !dbg !225
  %4 = load i8**, i8*** @global_argv, align 8, !dbg !226
  %arrayidx14 = getelementptr inbounds i8*, i8** %4, i64 0, !dbg !226
  %5 = load i8*, i8** %arrayidx14, align 8, !dbg !226
  %call15 = call i32 @getpid() #5, !dbg !227
  %arraydecay16 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buffer, i32 0, i32 0, !dbg !228
  %call17 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %3, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.7, i32 0, i32 0), i8* %arraydecay13, i8* %5, i32 %call15, i8* %arraydecay16), !dbg !229
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** @logfile, align 8, !dbg !230
  %call18 = call i32 @fflush(%struct._IO_FILE* %6), !dbg !231
  br label %if.end22, !dbg !232

if.else:                                          ; preds = %entry
  %7 = load i8, i8* @log_syslog, align 1, !dbg !233
  %tobool19 = icmp ne i8 %7, 0, !dbg !233
  br i1 %tobool19, label %if.then20, label %if.end, !dbg !235

if.then20:                                        ; preds = %if.else
  %arraydecay21 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buffer, i32 0, i32 0, !dbg !236
  call void (i32, i8*, ...) @syslog(i32 30, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.8, i32 0, i32 0), i8* %arraydecay21), !dbg !237
  br label %if.end, !dbg !237

if.end:                                           ; preds = %if.then20, %if.else
  br label %if.end22

if.end22:                                         ; preds = %if.end, %if.then
  ret void, !dbg !238
}

; Function Attrs: nounwind
declare i64 @time(i64*) #6

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #6

; Function Attrs: nounwind
declare i8* @ctime(i64*) #6

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #3

declare void @syslog(i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define void @log_end() #0 !dbg !18 {
entry:
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @logfile, align 8, !dbg !239
  %tobool = icmp ne %struct._IO_FILE* %0, null, !dbg !239
  br i1 %tobool, label %if.then, label %if.else, !dbg !241

if.then:                                          ; preds = %entry
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @logfile, align 8, !dbg !242
  %call = call i32 @fclose(%struct._IO_FILE* %1), !dbg !244
  store %struct._IO_FILE* null, %struct._IO_FILE** @logfile, align 8, !dbg !245
  br label %if.end3, !dbg !246

if.else:                                          ; preds = %entry
  %2 = load i8, i8* @log_syslog, align 1, !dbg !247
  %tobool1 = icmp ne i8 %2, 0, !dbg !247
  br i1 %tobool1, label %if.then2, label %if.end, !dbg !249

if.then2:                                         ; preds = %if.else
  call void @closelog(), !dbg !250
  br label %if.end, !dbg !250

if.end:                                           ; preds = %if.then2, %if.else
  br label %if.end3

if.end3:                                          ; preds = %if.end, %if.then
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** @statuslog, align 8, !dbg !251
  %tobool4 = icmp ne %struct._IO_FILE* %3, null, !dbg !251
  br i1 %tobool4, label %if.then5, label %if.end7, !dbg !253

if.then5:                                         ; preds = %if.end3
  %4 = load %struct._IO_FILE*, %struct._IO_FILE** @statuslog, align 8, !dbg !254
  %call6 = call i32 @fclose(%struct._IO_FILE* %4), !dbg !256
  store %struct._IO_FILE* null, %struct._IO_FILE** @statuslog, align 8, !dbg !257
  br label %if.end7, !dbg !258

if.end7:                                          ; preds = %if.then5, %if.end3
  ret void, !dbg !259
}

declare i32 @fclose(%struct._IO_FILE*) #2

declare void @closelog() #2

; Function Attrs: nounwind uwtable
define i8* @Current_Date() #0 !dbg !19 {
entry:
  %my_time = alloca i64, align 8
  %my_local = alloca %struct.tm*, align 8
  call void @llvm.dbg.declare(metadata i64* %my_time, metadata !260, metadata !108), !dbg !261
  call void @llvm.dbg.declare(metadata %struct.tm** %my_local, metadata !262, metadata !108), !dbg !279
  call void @llvm.memset.p0i8.i64(i8* getelementptr inbounds ([32 x i8], [32 x i8]* @Current_Date.output, i32 0, i32 0), i8 0, i64 32, i32 16, i1 false), !dbg !280
  %call = call i64 @time(i64* null) #5, !dbg !281
  store i64 %call, i64* %my_time, align 8, !dbg !282
  %call1 = call %struct.tm* @localtime(i64* %my_time) #5, !dbg !283
  store %struct.tm* %call1, %struct.tm** %my_local, align 8, !dbg !284
  %0 = load %struct.tm*, %struct.tm** %my_local, align 8, !dbg !285
  %tobool = icmp ne %struct.tm* %0, null, !dbg !285
  br i1 %tobool, label %if.then, label %if.end, !dbg !287

if.then:                                          ; preds = %entry
  %1 = load %struct.tm*, %struct.tm** %my_local, align 8, !dbg !288
  %tm_year = getelementptr inbounds %struct.tm, %struct.tm* %1, i32 0, i32 5, !dbg !289
  %2 = load i32, i32* %tm_year, align 4, !dbg !289
  %add = add nsw i32 %2, 1900, !dbg !290
  %3 = load %struct.tm*, %struct.tm** %my_local, align 8, !dbg !291
  %tm_mon = getelementptr inbounds %struct.tm, %struct.tm* %3, i32 0, i32 4, !dbg !292
  %4 = load i32, i32* %tm_mon, align 8, !dbg !292
  %add2 = add nsw i32 %4, 1, !dbg !293
  %5 = load %struct.tm*, %struct.tm** %my_local, align 8, !dbg !294
  %tm_mday = getelementptr inbounds %struct.tm, %struct.tm* %5, i32 0, i32 3, !dbg !295
  %6 = load i32, i32* %tm_mday, align 4, !dbg !295
  %call3 = call i32 (i8*, i8*, ...) @sprintf(i8* getelementptr inbounds ([32 x i8], [32 x i8]* @Current_Date.output, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.9, i32 0, i32 0), i32 %add, i32 %add2, i32 %6) #5, !dbg !296
  br label %if.end, !dbg !296

if.end:                                           ; preds = %if.then, %entry
  ret i8* getelementptr inbounds ([32 x i8], [32 x i8]* @Current_Date.output, i32 0, i32 0), !dbg !297
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #7

; Function Attrs: nounwind
declare %struct.tm* @localtime(i64*) #6

; Function Attrs: nounwind
declare i32 @sprintf(i8*, i8*, ...) #6

; Function Attrs: nounwind uwtable
define i32 @Open_Send_Receive_Log() #0 !dbg !22 {
entry:
  %retval = alloca i32, align 4
  %foldername = alloca i8*, align 8
  %filename = alloca i8*, align 8
  %my_date = alloca i8*, align 8
  call void @llvm.dbg.declare(metadata i8** %foldername, metadata !298, metadata !108), !dbg !299
  call void @llvm.dbg.declare(metadata i8** %filename, metadata !300, metadata !108), !dbg !301
  call void @llvm.dbg.declare(metadata i8** %my_date, metadata !302, metadata !108), !dbg !303
  %call = call i8* @config_getoption(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.10, i32 0, i32 0)), !dbg !304
  store i8* %call, i8** %foldername, align 8, !dbg !305
  %0 = load i8*, i8** %foldername, align 8, !dbg !306
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !306
  %1 = load i8, i8* %arrayidx, align 1, !dbg !306
  %tobool = icmp ne i8 %1, 0, !dbg !306
  br i1 %tobool, label %if.end, label %if.then, !dbg !308

if.then:                                          ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !309
  br label %return, !dbg !309

if.end:                                           ; preds = %entry
  %call1 = call i8* @Current_Date(), !dbg !310
  store i8* %call1, i8** %my_date, align 8, !dbg !311
  %2 = load i8*, i8** %foldername, align 8, !dbg !312
  %call2 = call i64 @strlen(i8* %2) #8, !dbg !313
  %3 = load i8*, i8** %my_date, align 8, !dbg !314
  %call3 = call i64 @strlen(i8* %3) #8, !dbg !315
  %add = add i64 %call2, %call3, !dbg !317
  %add4 = add i64 %add, 16, !dbg !318
  %call5 = call noalias i8* @calloc(i64 %add4, i64 1) #5, !dbg !319
  store i8* %call5, i8** %filename, align 8, !dbg !321
  %4 = load i8*, i8** %filename, align 8, !dbg !322
  %tobool6 = icmp ne i8* %4, null, !dbg !322
  br i1 %tobool6, label %if.end8, label %if.then7, !dbg !324

if.then7:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !325
  br label %return, !dbg !325

if.end8:                                          ; preds = %if.end
  %5 = load i8*, i8** %filename, align 8, !dbg !326
  %6 = load i8*, i8** %foldername, align 8, !dbg !327
  %7 = load i8*, i8** %my_date, align 8, !dbg !328
  %call9 = call i32 (i8*, i8*, ...) @sprintf(i8* %5, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.11, i32 0, i32 0), i8* %6, i8* %7) #5, !dbg !329
  %8 = load i8*, i8** %filename, align 8, !dbg !330
  %call10 = call %struct._IO_FILE* @fopen64(i8* %8, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0)), !dbg !331
  store %struct._IO_FILE* %call10, %struct._IO_FILE** @send_receive_file, align 8, !dbg !332
  %9 = load i8*, i8** %filename, align 8, !dbg !333
  call void @free(i8* %9) #5, !dbg !334
  %10 = load %struct._IO_FILE*, %struct._IO_FILE** @send_receive_file, align 8, !dbg !335
  %tobool11 = icmp ne %struct._IO_FILE* %10, null, !dbg !335
  br i1 %tobool11, label %if.else, label %if.then12, !dbg !337

if.then12:                                        ; preds = %if.end8
  store i32 0, i32* %retval, align 4, !dbg !338
  br label %return, !dbg !338

if.else:                                          ; preds = %if.end8
  store i32 1, i32* %retval, align 4, !dbg !339
  br label %return, !dbg !339

return:                                           ; preds = %if.else, %if.then12, %if.then7, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !340
  ret i32 %11, !dbg !340
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #6

; Function Attrs: nounwind
declare void @free(i8*) #6

; Function Attrs: nounwind uwtable
define i32 @Update_Send_Recv(i8* %username, double %sent, double %received) #0 !dbg !25 {
entry:
  %retval = alloca i32, align 4
  %username.addr = alloca i8*, align 8
  %sent.addr = alloca double, align 8
  %received.addr = alloca double, align 8
  store i8* %username, i8** %username.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %username.addr, metadata !341, metadata !108), !dbg !342
  store double %sent, double* %sent.addr, align 8
  call void @llvm.dbg.declare(metadata double* %sent.addr, metadata !343, metadata !108), !dbg !344
  store double %received, double* %received.addr, align 8
  call void @llvm.dbg.declare(metadata double* %received.addr, metadata !345, metadata !108), !dbg !346
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @send_receive_file, align 8, !dbg !347
  %tobool = icmp ne %struct._IO_FILE* %0, null, !dbg !347
  br i1 %tobool, label %if.end, label %if.then, !dbg !349

if.then:                                          ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !350
  br label %return, !dbg !350

if.end:                                           ; preds = %entry
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @send_receive_file, align 8, !dbg !351
  %call = call i32 @fseek(%struct._IO_FILE* %1, i64 0, i32 2), !dbg !352
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** @send_receive_file, align 8, !dbg !353
  %3 = load i8*, i8** %username.addr, align 8, !dbg !354
  %4 = load double, double* %sent.addr, align 8, !dbg !355
  %5 = load double, double* %received.addr, align 8, !dbg !356
  %call1 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %2, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.12, i32 0, i32 0), i8* %3, double %4, double %5), !dbg !357
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** @send_receive_file, align 8, !dbg !358
  %call2 = call i32 @fflush(%struct._IO_FILE* %6), !dbg !359
  store i32 1, i32* %retval, align 4, !dbg !360
  br label %return, !dbg !360

return:                                           ; preds = %if.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !361
  ret i32 %7, !dbg !361
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }
attributes #6 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { argmemonly nounwind }
attributes #8 = { nounwind readonly }
attributes #9 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!104, !105}
!llvm.ident = !{!106}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !7, globals: !29)
!1 = !DIFile(filename: "logging.c", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!2 = !{}
!3 = !{!4, !5}
!4 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!7 = !{!8, !12, !15, !18, !19, !22, !25}
!8 = distinct !DISubprogram(name: "log_init", scope: !9, file: !9, line: 30, type: !10, isLocal: false, isDefinition: true, scopeLine: 31, isOptimized: false, variables: !2)
!9 = !DIFile(filename: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/logging.c", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!10 = !DISubroutineType(types: !11)
!11 = !{null}
!12 = distinct !DISubprogram(name: "bftpd_statuslog", scope: !9, file: !9, line: 57, type: !13, isLocal: false, isDefinition: true, scopeLine: 58, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!13 = !DISubroutineType(types: !14)
!14 = !{null, !6, !6, !5, null}
!15 = distinct !DISubprogram(name: "bftpd_log", scope: !9, file: !9, line: 72, type: !16, isLocal: false, isDefinition: true, scopeLine: 73, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!16 = !DISubroutineType(types: !17)
!17 = !{null, !5, null}
!18 = distinct !DISubprogram(name: "log_end", scope: !9, file: !9, line: 95, type: !10, isLocal: false, isDefinition: true, scopeLine: 96, isOptimized: false, variables: !2)
!19 = distinct !DISubprogram(name: "Current_Date", scope: !9, file: !9, line: 116, type: !20, isLocal: false, isDefinition: true, scopeLine: 117, isOptimized: false, variables: !2)
!20 = !DISubroutineType(types: !21)
!21 = !{!5}
!22 = distinct !DISubprogram(name: "Open_Send_Receive_Log", scope: !9, file: !9, line: 136, type: !23, isLocal: false, isDefinition: true, scopeLine: 137, isOptimized: false, variables: !2)
!23 = !DISubroutineType(types: !24)
!24 = !{!4}
!25 = distinct !DISubprogram(name: "Update_Send_Recv", scope: !9, file: !9, line: 168, type: !26, isLocal: false, isDefinition: true, scopeLine: 169, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!26 = !DISubroutineType(types: !27)
!27 = !{!4, !5, !28, !28}
!28 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!29 = !{!30, !91, !92, !93, !94, !95, !99, !101, !102, !103}
!30 = !DIGlobalVariable(name: "logfile", scope: !0, file: !9, line: 23, type: !31, isLocal: false, isDefinition: true, variable: %struct._IO_FILE** @logfile)
!31 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64, align: 64)
!32 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !33, line: 48, baseType: !34)
!33 = !DIFile(filename: "/usr/include/stdio.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!34 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !35, line: 245, size: 1728, align: 64, elements: !36)
!35 = !DIFile(filename: "/usr/include/libio.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!36 = !{!37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !57, !58, !59, !60, !64, !66, !68, !72, !75, !77, !79, !80, !81, !82, !86, !87}
!37 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !34, file: !35, line: 246, baseType: !4, size: 32, align: 32)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !34, file: !35, line: 251, baseType: !5, size: 64, align: 64, offset: 64)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !34, file: !35, line: 252, baseType: !5, size: 64, align: 64, offset: 128)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !34, file: !35, line: 253, baseType: !5, size: 64, align: 64, offset: 192)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !34, file: !35, line: 254, baseType: !5, size: 64, align: 64, offset: 256)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !34, file: !35, line: 255, baseType: !5, size: 64, align: 64, offset: 320)
!43 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !34, file: !35, line: 256, baseType: !5, size: 64, align: 64, offset: 384)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !34, file: !35, line: 257, baseType: !5, size: 64, align: 64, offset: 448)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !34, file: !35, line: 258, baseType: !5, size: 64, align: 64, offset: 512)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !34, file: !35, line: 260, baseType: !5, size: 64, align: 64, offset: 576)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !34, file: !35, line: 261, baseType: !5, size: 64, align: 64, offset: 640)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !34, file: !35, line: 262, baseType: !5, size: 64, align: 64, offset: 704)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !34, file: !35, line: 264, baseType: !50, size: 64, align: 64, offset: 768)
!50 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !51, size: 64, align: 64)
!51 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !35, line: 160, size: 192, align: 64, elements: !52)
!52 = !{!53, !54, !56}
!53 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !51, file: !35, line: 161, baseType: !50, size: 64, align: 64)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !51, file: !35, line: 162, baseType: !55, size: 64, align: 64, offset: 64)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !34, size: 64, align: 64)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !51, file: !35, line: 166, baseType: !4, size: 32, align: 32, offset: 128)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !34, file: !35, line: 266, baseType: !55, size: 64, align: 64, offset: 832)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !34, file: !35, line: 268, baseType: !4, size: 32, align: 32, offset: 896)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !34, file: !35, line: 272, baseType: !4, size: 32, align: 32, offset: 928)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !34, file: !35, line: 274, baseType: !61, size: 64, align: 64, offset: 960)
!61 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !62, line: 131, baseType: !63)
!62 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!63 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!64 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !34, file: !35, line: 278, baseType: !65, size: 16, align: 16, offset: 1024)
!65 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !34, file: !35, line: 279, baseType: !67, size: 8, align: 8, offset: 1040)
!67 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !34, file: !35, line: 280, baseType: !69, size: 8, align: 8, offset: 1048)
!69 = !DICompositeType(tag: DW_TAG_array_type, baseType: !6, size: 8, align: 8, elements: !70)
!70 = !{!71}
!71 = !DISubrange(count: 1)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !34, file: !35, line: 284, baseType: !73, size: 64, align: 64, offset: 1088)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!74 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !35, line: 154, baseType: null)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !34, file: !35, line: 293, baseType: !76, size: 64, align: 64, offset: 1152)
!76 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !62, line: 132, baseType: !63)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !34, file: !35, line: 302, baseType: !78, size: 64, align: 64, offset: 1216)
!78 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !34, file: !35, line: 303, baseType: !78, size: 64, align: 64, offset: 1280)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !34, file: !35, line: 304, baseType: !78, size: 64, align: 64, offset: 1344)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !34, file: !35, line: 305, baseType: !78, size: 64, align: 64, offset: 1408)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !34, file: !35, line: 306, baseType: !83, size: 64, align: 64, offset: 1472)
!83 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !84, line: 62, baseType: !85)
!84 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!85 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !34, file: !35, line: 308, baseType: !4, size: 32, align: 32, offset: 1536)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !34, file: !35, line: 310, baseType: !88, size: 160, align: 8, offset: 1568)
!88 = !DICompositeType(tag: DW_TAG_array_type, baseType: !6, size: 160, align: 8, elements: !89)
!89 = !{!90}
!90 = !DISubrange(count: 20)
!91 = !DIGlobalVariable(name: "send_receive_file", scope: !0, file: !9, line: 24, type: !31, isLocal: false, isDefinition: true, variable: %struct._IO_FILE** @send_receive_file)
!92 = !DIGlobalVariable(name: "statuslog", scope: !0, file: !9, line: 25, type: !31, isLocal: false, isDefinition: true, variable: %struct._IO_FILE** @statuslog)
!93 = !DIGlobalVariable(name: "statuslogforreading", scope: !0, file: !9, line: 26, type: !31, isLocal: false, isDefinition: true, variable: %struct._IO_FILE** @statuslogforreading)
!94 = !DIGlobalVariable(name: "log_syslog", scope: !0, file: !9, line: 28, type: !6, isLocal: false, isDefinition: true, variable: i8* @log_syslog)
!95 = !DIGlobalVariable(name: "output", scope: !19, file: !9, line: 118, type: !96, isLocal: true, isDefinition: true, variable: [32 x i8]* @Current_Date.output)
!96 = !DICompositeType(tag: DW_TAG_array_type, baseType: !6, size: 256, align: 8, elements: !97)
!97 = !{!98}
!98 = !DISubrange(count: 32)
!99 = !DIGlobalVariable(name: "configpath", scope: !0, file: !100, line: 25, type: !5, isLocal: false, isDefinition: true, variable: i8** @configpath)
!100 = !DIFile(filename: "./main.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!101 = !DIGlobalVariable(name: "daemonmode", scope: !0, file: !100, line: 26, type: !4, isLocal: false, isDefinition: true, variable: i32* @daemonmode)
!102 = !DIGlobalVariable(name: "pre_write_script", scope: !0, file: !100, line: 29, type: !5, isLocal: false, isDefinition: true, variable: i8** @pre_write_script)
!103 = !DIGlobalVariable(name: "post_write_script", scope: !0, file: !100, line: 30, type: !5, isLocal: false, isDefinition: true, variable: i8** @post_write_script)
!104 = !{i32 2, !"Dwarf Version", i32 4}
!105 = !{i32 2, !"Debug Info Version", i32 3}
!106 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!107 = !DILocalVariable(name: "foo", scope: !8, file: !9, line: 32, type: !5)
!108 = !DIExpression()
!109 = !DILocation(line: 32, column: 11, scope: !8)
!110 = !DILocation(line: 32, column: 17, scope: !8)
!111 = !DILocation(line: 34, column: 18, scope: !112)
!112 = distinct !DILexicalBlock(scope: !8, file: !9, line: 34, column: 6)
!113 = !DILocation(line: 34, column: 7, scope: !112)
!114 = !DILocation(line: 34, column: 6, scope: !8)
!115 = !DILocation(line: 35, column: 20, scope: !116)
!116 = distinct !DILexicalBlock(scope: !112, file: !9, line: 34, column: 34)
!117 = !DILocation(line: 36, column: 11, scope: !116)
!118 = !DILocation(line: 36, column: 3, scope: !116)
!119 = !DILocation(line: 37, column: 2, scope: !116)
!120 = !DILocation(line: 39, column: 9, scope: !121)
!121 = distinct !DILexicalBlock(scope: !112, file: !9, line: 39, column: 9)
!122 = !DILocation(line: 39, column: 9, scope: !112)
!123 = !DILocation(line: 40, column: 31, scope: !124)
!124 = distinct !DILexicalBlock(scope: !121, file: !9, line: 40, column: 13)
!125 = !DILocation(line: 40, column: 25, scope: !124)
!126 = !DILocation(line: 40, column: 23, scope: !124)
!127 = !DILocation(line: 40, column: 13, scope: !121)
!128 = !DILocation(line: 41, column: 7, scope: !129)
!129 = distinct !DILexicalBlock(scope: !124, file: !9, line: 40, column: 43)
!130 = !DILocation(line: 43, column: 7, scope: !129)
!131 = !DILocation(line: 40, column: 40, scope: !132)
!132 = !DILexicalBlockFile(scope: !124, file: !9, discriminator: 1)
!133 = !DILocation(line: 45, column: 17, scope: !8)
!134 = !DILocation(line: 45, column: 15, scope: !8)
!135 = !DILocation(line: 47, column: 27, scope: !8)
!136 = !DILocation(line: 47, column: 25, scope: !8)
!137 = !DILocation(line: 48, column: 1, scope: !8)
!138 = !DILocalVariable(name: "type", arg: 1, scope: !12, file: !9, line: 57, type: !6)
!139 = !DILocation(line: 57, column: 27, scope: !12)
!140 = !DILocalVariable(name: "type2", arg: 2, scope: !12, file: !9, line: 57, type: !6)
!141 = !DILocation(line: 57, column: 38, scope: !12)
!142 = !DILocalVariable(name: "format", arg: 3, scope: !12, file: !9, line: 57, type: !5)
!143 = !DILocation(line: 57, column: 51, scope: !12)
!144 = !DILocation(line: 59, column: 9, scope: !145)
!145 = distinct !DILexicalBlock(scope: !12, file: !9, line: 59, column: 9)
!146 = !DILocation(line: 59, column: 9, scope: !12)
!147 = !DILocalVariable(name: "val", scope: !148, file: !9, line: 60, type: !149)
!148 = distinct !DILexicalBlock(scope: !145, file: !9, line: 59, column: 20)
!149 = !DIDerivedType(tag: DW_TAG_typedef, name: "va_list", file: !33, line: 79, baseType: !150)
!150 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gnuc_va_list", file: !151, line: 50, baseType: !152)
!151 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stdarg.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!152 = !DIDerivedType(tag: DW_TAG_typedef, name: "__builtin_va_list", file: !1, line: 60, baseType: !153)
!153 = !DICompositeType(tag: DW_TAG_array_type, baseType: !154, size: 192, align: 64, elements: !70)
!154 = !DICompositeType(tag: DW_TAG_structure_type, name: "__va_list_tag", file: !1, line: 60, size: 192, align: 64, elements: !155)
!155 = !{!156, !158, !159, !160}
!156 = !DIDerivedType(tag: DW_TAG_member, name: "gp_offset", scope: !154, file: !1, line: 60, baseType: !157, size: 32, align: 32)
!157 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "fp_offset", scope: !154, file: !1, line: 60, baseType: !157, size: 32, align: 32, offset: 32)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "overflow_arg_area", scope: !154, file: !1, line: 60, baseType: !78, size: 64, align: 64, offset: 64)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "reg_save_area", scope: !154, file: !1, line: 60, baseType: !78, size: 64, align: 64, offset: 128)
!161 = !DILocation(line: 60, column: 17, scope: !148)
!162 = !DILocalVariable(name: "buffer", scope: !148, file: !9, line: 61, type: !163)
!163 = !DICompositeType(tag: DW_TAG_array_type, baseType: !6, size: 8192, align: 8, elements: !164)
!164 = !{!165}
!165 = !DISubrange(count: 1024)
!166 = !DILocation(line: 61, column: 14, scope: !148)
!167 = !DILocation(line: 62, column: 9, scope: !148)
!168 = !DILocation(line: 63, column: 19, scope: !148)
!169 = !DILocation(line: 63, column: 43, scope: !148)
!170 = !DILocation(line: 63, column: 51, scope: !148)
!171 = !DILocation(line: 63, column: 9, scope: !148)
!172 = !DILocation(line: 64, column: 9, scope: !148)
!173 = !DILocation(line: 65, column: 15, scope: !148)
!174 = !DILocation(line: 65, column: 9, scope: !148)
!175 = !DILocation(line: 66, column: 17, scope: !148)
!176 = !DILocation(line: 66, column: 51, scope: !148)
!177 = !DILocation(line: 66, column: 61, scope: !148)
!178 = !DILocation(line: 66, column: 67, scope: !148)
!179 = !DILocation(line: 67, column: 17, scope: !148)
!180 = !DILocation(line: 66, column: 9, scope: !181)
!181 = !DILexicalBlockFile(scope: !148, file: !9, discriminator: 1)
!182 = !DILocation(line: 68, column: 16, scope: !148)
!183 = !DILocation(line: 68, column: 9, scope: !148)
!184 = !DILocation(line: 69, column: 5, scope: !148)
!185 = !DILocation(line: 70, column: 1, scope: !12)
!186 = !DILocalVariable(name: "format", arg: 1, scope: !15, file: !9, line: 72, type: !5)
!187 = !DILocation(line: 72, column: 22, scope: !15)
!188 = !DILocalVariable(name: "val", scope: !15, file: !9, line: 74, type: !149)
!189 = !DILocation(line: 74, column: 10, scope: !15)
!190 = !DILocalVariable(name: "buffer", scope: !15, file: !9, line: 75, type: !163)
!191 = !DILocation(line: 75, column: 7, scope: !15)
!192 = !DILocalVariable(name: "timestr", scope: !15, file: !9, line: 75, type: !193)
!193 = !DICompositeType(tag: DW_TAG_array_type, baseType: !6, size: 320, align: 8, elements: !194)
!194 = !{!195}
!195 = !DISubrange(count: 40)
!196 = !DILocation(line: 75, column: 21, scope: !15)
!197 = !DILocalVariable(name: "t", scope: !15, file: !9, line: 76, type: !198)
!198 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !199, line: 75, baseType: !200)
!199 = !DIFile(filename: "/usr/include/time.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!200 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !62, line: 139, baseType: !63)
!201 = !DILocation(line: 76, column: 9, scope: !15)
!202 = !DILocation(line: 77, column: 2, scope: !15)
!203 = !DILocation(line: 78, column: 12, scope: !15)
!204 = !DILocation(line: 78, column: 36, scope: !15)
!205 = !DILocation(line: 78, column: 44, scope: !15)
!206 = !DILocation(line: 78, column: 2, scope: !15)
!207 = !DILocation(line: 79, column: 2, scope: !15)
!208 = !DILocation(line: 80, column: 6, scope: !209)
!209 = distinct !DILexicalBlock(scope: !15, file: !9, line: 80, column: 6)
!210 = !DILocation(line: 80, column: 6, scope: !15)
!211 = !DILocation(line: 81, column: 9, scope: !212)
!212 = distinct !DILexicalBlock(scope: !209, file: !9, line: 80, column: 15)
!213 = !DILocation(line: 81, column: 3, scope: !212)
!214 = !DILocation(line: 82, column: 3, scope: !212)
!215 = !DILocation(line: 83, column: 10, scope: !212)
!216 = !DILocation(line: 83, column: 28, scope: !212)
!217 = !DILocation(line: 83, column: 3, scope: !218)
!218 = !DILexicalBlockFile(scope: !212, file: !9, discriminator: 1)
!219 = !DILocation(line: 84, column: 18, scope: !212)
!220 = !DILocation(line: 84, column: 11, scope: !212)
!221 = !DILocation(line: 84, column: 27, scope: !212)
!222 = !DILocation(line: 84, column: 3, scope: !212)
!223 = !DILocation(line: 84, column: 32, scope: !212)
!224 = !DILocation(line: 85, column: 11, scope: !212)
!225 = !DILocation(line: 85, column: 37, scope: !212)
!226 = !DILocation(line: 85, column: 46, scope: !212)
!227 = !DILocation(line: 86, column: 11, scope: !212)
!228 = !DILocation(line: 86, column: 21, scope: !212)
!229 = !DILocation(line: 85, column: 3, scope: !212)
!230 = !DILocation(line: 87, column: 10, scope: !212)
!231 = !DILocation(line: 87, column: 3, scope: !212)
!232 = !DILocation(line: 88, column: 2, scope: !212)
!233 = !DILocation(line: 90, column: 14, scope: !234)
!234 = distinct !DILexicalBlock(scope: !209, file: !9, line: 90, column: 14)
!235 = !DILocation(line: 90, column: 14, scope: !209)
!236 = !DILocation(line: 91, column: 45, scope: !234)
!237 = !DILocation(line: 91, column: 9, scope: !234)
!238 = !DILocation(line: 93, column: 1, scope: !15)
!239 = !DILocation(line: 97, column: 6, scope: !240)
!240 = distinct !DILexicalBlock(scope: !18, file: !9, line: 97, column: 6)
!241 = !DILocation(line: 97, column: 6, scope: !18)
!242 = !DILocation(line: 98, column: 10, scope: !243)
!243 = distinct !DILexicalBlock(scope: !240, file: !9, line: 97, column: 15)
!244 = !DILocation(line: 98, column: 3, scope: !243)
!245 = !DILocation(line: 99, column: 11, scope: !243)
!246 = !DILocation(line: 100, column: 2, scope: !243)
!247 = !DILocation(line: 102, column: 14, scope: !248)
!248 = distinct !DILexicalBlock(scope: !240, file: !9, line: 102, column: 14)
!249 = !DILocation(line: 102, column: 14, scope: !240)
!250 = !DILocation(line: 103, column: 3, scope: !248)
!251 = !DILocation(line: 105, column: 9, scope: !252)
!252 = distinct !DILexicalBlock(scope: !18, file: !9, line: 105, column: 9)
!253 = !DILocation(line: 105, column: 9, scope: !18)
!254 = !DILocation(line: 106, column: 16, scope: !255)
!255 = distinct !DILexicalBlock(scope: !252, file: !9, line: 105, column: 20)
!256 = !DILocation(line: 106, column: 9, scope: !255)
!257 = !DILocation(line: 107, column: 19, scope: !255)
!258 = !DILocation(line: 108, column: 5, scope: !255)
!259 = !DILocation(line: 109, column: 1, scope: !18)
!260 = !DILocalVariable(name: "my_time", scope: !19, file: !9, line: 119, type: !198)
!261 = !DILocation(line: 119, column: 11, scope: !19)
!262 = !DILocalVariable(name: "my_local", scope: !19, file: !9, line: 120, type: !263)
!263 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !264, size: 64, align: 64)
!264 = !DICompositeType(tag: DW_TAG_structure_type, name: "tm", file: !199, line: 133, size: 448, align: 64, elements: !265)
!265 = !{!266, !267, !268, !269, !270, !271, !272, !273, !274, !275, !276}
!266 = !DIDerivedType(tag: DW_TAG_member, name: "tm_sec", scope: !264, file: !199, line: 135, baseType: !4, size: 32, align: 32)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "tm_min", scope: !264, file: !199, line: 136, baseType: !4, size: 32, align: 32, offset: 32)
!268 = !DIDerivedType(tag: DW_TAG_member, name: "tm_hour", scope: !264, file: !199, line: 137, baseType: !4, size: 32, align: 32, offset: 64)
!269 = !DIDerivedType(tag: DW_TAG_member, name: "tm_mday", scope: !264, file: !199, line: 138, baseType: !4, size: 32, align: 32, offset: 96)
!270 = !DIDerivedType(tag: DW_TAG_member, name: "tm_mon", scope: !264, file: !199, line: 139, baseType: !4, size: 32, align: 32, offset: 128)
!271 = !DIDerivedType(tag: DW_TAG_member, name: "tm_year", scope: !264, file: !199, line: 140, baseType: !4, size: 32, align: 32, offset: 160)
!272 = !DIDerivedType(tag: DW_TAG_member, name: "tm_wday", scope: !264, file: !199, line: 141, baseType: !4, size: 32, align: 32, offset: 192)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "tm_yday", scope: !264, file: !199, line: 142, baseType: !4, size: 32, align: 32, offset: 224)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "tm_isdst", scope: !264, file: !199, line: 143, baseType: !4, size: 32, align: 32, offset: 256)
!275 = !DIDerivedType(tag: DW_TAG_member, name: "tm_gmtoff", scope: !264, file: !199, line: 146, baseType: !63, size: 64, align: 64, offset: 320)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "tm_zone", scope: !264, file: !199, line: 147, baseType: !277, size: 64, align: 64, offset: 384)
!277 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !278, size: 64, align: 64)
!278 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !6)
!279 = !DILocation(line: 120, column: 15, scope: !19)
!280 = !DILocation(line: 122, column: 4, scope: !19)
!281 = !DILocation(line: 123, column: 14, scope: !19)
!282 = !DILocation(line: 123, column: 12, scope: !19)
!283 = !DILocation(line: 124, column: 15, scope: !19)
!284 = !DILocation(line: 124, column: 13, scope: !19)
!285 = !DILocation(line: 125, column: 8, scope: !286)
!286 = distinct !DILexicalBlock(scope: !19, file: !9, line: 125, column: 8)
!287 = !DILocation(line: 125, column: 8, scope: !19)
!288 = !DILocation(line: 126, column: 36, scope: !286)
!289 = !DILocation(line: 126, column: 46, scope: !286)
!290 = !DILocation(line: 126, column: 54, scope: !286)
!291 = !DILocation(line: 126, column: 62, scope: !286)
!292 = !DILocation(line: 126, column: 72, scope: !286)
!293 = !DILocation(line: 126, column: 79, scope: !286)
!294 = !DILocation(line: 126, column: 84, scope: !286)
!295 = !DILocation(line: 126, column: 94, scope: !286)
!296 = !DILocation(line: 126, column: 8, scope: !286)
!297 = !DILocation(line: 127, column: 4, scope: !19)
!298 = !DILocalVariable(name: "foldername", scope: !22, file: !9, line: 138, type: !5)
!299 = !DILocation(line: 138, column: 11, scope: !22)
!300 = !DILocalVariable(name: "filename", scope: !22, file: !9, line: 138, type: !5)
!301 = !DILocation(line: 138, column: 24, scope: !22)
!302 = !DILocalVariable(name: "my_date", scope: !22, file: !9, line: 138, type: !5)
!303 = !DILocation(line: 138, column: 35, scope: !22)
!304 = !DILocation(line: 140, column: 18, scope: !22)
!305 = !DILocation(line: 140, column: 16, scope: !22)
!306 = !DILocation(line: 141, column: 11, scope: !307)
!307 = distinct !DILexicalBlock(scope: !22, file: !9, line: 141, column: 9)
!308 = !DILocation(line: 141, column: 9, scope: !22)
!309 = !DILocation(line: 142, column: 8, scope: !307)
!310 = !DILocation(line: 144, column: 15, scope: !22)
!311 = !DILocation(line: 144, column: 13, scope: !22)
!312 = !DILocation(line: 145, column: 40, scope: !22)
!313 = !DILocation(line: 145, column: 33, scope: !22)
!314 = !DILocation(line: 145, column: 61, scope: !22)
!315 = !DILocation(line: 145, column: 54, scope: !316)
!316 = !DILexicalBlockFile(scope: !22, file: !9, discriminator: 1)
!317 = !DILocation(line: 145, column: 52, scope: !22)
!318 = !DILocation(line: 145, column: 70, scope: !22)
!319 = !DILocation(line: 145, column: 25, scope: !320)
!320 = !DILexicalBlockFile(scope: !22, file: !9, discriminator: 2)
!321 = !DILocation(line: 145, column: 14, scope: !22)
!322 = !DILocation(line: 146, column: 11, scope: !323)
!323 = distinct !DILexicalBlock(scope: !22, file: !9, line: 146, column: 9)
!324 = !DILocation(line: 146, column: 9, scope: !22)
!325 = !DILocation(line: 147, column: 8, scope: !323)
!326 = !DILocation(line: 149, column: 13, scope: !22)
!327 = !DILocation(line: 149, column: 36, scope: !22)
!328 = !DILocation(line: 149, column: 48, scope: !22)
!329 = !DILocation(line: 149, column: 5, scope: !22)
!330 = !DILocation(line: 150, column: 31, scope: !22)
!331 = !DILocation(line: 150, column: 25, scope: !22)
!332 = !DILocation(line: 150, column: 23, scope: !22)
!333 = !DILocation(line: 151, column: 10, scope: !22)
!334 = !DILocation(line: 151, column: 5, scope: !22)
!335 = !DILocation(line: 152, column: 11, scope: !336)
!336 = distinct !DILexicalBlock(scope: !22, file: !9, line: 152, column: 9)
!337 = !DILocation(line: 152, column: 9, scope: !22)
!338 = !DILocation(line: 153, column: 8, scope: !336)
!339 = !DILocation(line: 155, column: 8, scope: !336)
!340 = !DILocation(line: 156, column: 1, scope: !22)
!341 = !DILocalVariable(name: "username", arg: 1, scope: !25, file: !9, line: 168, type: !5)
!342 = !DILocation(line: 168, column: 28, scope: !25)
!343 = !DILocalVariable(name: "sent", arg: 2, scope: !25, file: !9, line: 168, type: !28)
!344 = !DILocation(line: 168, column: 45, scope: !25)
!345 = !DILocalVariable(name: "received", arg: 3, scope: !25, file: !9, line: 168, type: !28)
!346 = !DILocation(line: 168, column: 58, scope: !25)
!347 = !DILocation(line: 170, column: 11, scope: !348)
!348 = distinct !DILexicalBlock(scope: !25, file: !9, line: 170, column: 9)
!349 = !DILocation(line: 170, column: 9, scope: !25)
!350 = !DILocation(line: 171, column: 8, scope: !348)
!351 = !DILocation(line: 173, column: 11, scope: !25)
!352 = !DILocation(line: 173, column: 5, scope: !25)
!353 = !DILocation(line: 175, column: 13, scope: !25)
!354 = !DILocation(line: 175, column: 50, scope: !25)
!355 = !DILocation(line: 175, column: 60, scope: !25)
!356 = !DILocation(line: 175, column: 66, scope: !25)
!357 = !DILocation(line: 175, column: 5, scope: !25)
!358 = !DILocation(line: 176, column: 12, scope: !25)
!359 = !DILocation(line: 176, column: 5, scope: !25)
!360 = !DILocation(line: 177, column: 5, scope: !25)
!361 = !DILocation(line: 178, column: 1, scope: !25)
