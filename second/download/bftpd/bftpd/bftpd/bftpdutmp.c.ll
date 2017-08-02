; ModuleID = '/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/bftpdutmp.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.bftpdutmp = type { i8, i32, [31 x i8], [256 x i8], i64 }

@bftpdutmp = global %struct._IO_FILE* null, align 8
@bftpdutmp_offset = global i64 4294967295, align 8
@.str = private unnamed_addr constant [15 x i8] c"PATH_BFTPDUTMP\00", align 1
@.str.1 = private unnamed_addr constant [5 x i8] c"none\00", align 1
@.str.2 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@.str.3 = private unnamed_addr constant [3 x i8] c"r+\00", align 1
@.str.4 = private unnamed_addr constant [29 x i8] c"Could not open log file %s.\0A\00", align 1
@.str.5 = private unnamed_addr constant [70 x i8] c"421-Could not open file %s\0D\0A421 Server disabled for security reasons.\00", align 1
@user = external global [31 x i8], align 16
@remotehostname = external global i8*, align 8
@.str.6 = private unnamed_addr constant [2 x i8] c"*\00", align 1
@configpath = common global i8* null, align 8
@daemonmode = common global i32 0, align 4
@pre_write_script = common global i8* null, align 8
@post_write_script = common global i8* null, align 8

; Function Attrs: nounwind uwtable
define void @bftpdutmp_create_dir(i8* %path_to_file) #0 !dbg !6 {
entry:
  %path_to_file.addr = alloca i8*, align 8
  %dir_name = alloca i8*, align 8
  %index = alloca i8*, align 8
  store i8* %path_to_file, i8** %path_to_file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path_to_file.addr, metadata !103, metadata !104), !dbg !105
  call void @llvm.dbg.declare(metadata i8** %dir_name, metadata !106, metadata !104), !dbg !107
  call void @llvm.dbg.declare(metadata i8** %index, metadata !108, metadata !104), !dbg !109
  %0 = load i8*, i8** %path_to_file.addr, align 8, !dbg !110
  %tobool = icmp ne i8* %0, null, !dbg !110
  br i1 %tobool, label %if.end, label %if.then, !dbg !112

if.then:                                          ; preds = %entry
  br label %return, !dbg !113

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %path_to_file.addr, align 8, !dbg !115
  %call = call noalias i8* @strdup(i8* %1) #7, !dbg !116
  store i8* %call, i8** %dir_name, align 8, !dbg !117
  %2 = load i8*, i8** %dir_name, align 8, !dbg !118
  %tobool1 = icmp ne i8* %2, null, !dbg !118
  br i1 %tobool1, label %if.end3, label %if.then2, !dbg !120

if.then2:                                         ; preds = %if.end
  br label %return, !dbg !121

if.end3:                                          ; preds = %if.end
  %3 = load i8*, i8** %dir_name, align 8, !dbg !122
  %call4 = call i8* @strrchr(i8* %3, i32 47) #8, !dbg !123
  store i8* %call4, i8** %index, align 8, !dbg !124
  %4 = load i8*, i8** %index, align 8, !dbg !125
  %tobool5 = icmp ne i8* %4, null, !dbg !125
  br i1 %tobool5, label %if.then6, label %if.end8, !dbg !127

if.then6:                                         ; preds = %if.end3
  %5 = load i8*, i8** %index, align 8, !dbg !128
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 0, !dbg !128
  store i8 0, i8* %arrayidx, align 1, !dbg !130
  %6 = load i8*, i8** %dir_name, align 8, !dbg !131
  %call7 = call i32 (i8*, i32, ...) bitcast (i32 (...)* @mkdir to i32 (i8*, i32, ...)*)(i8* %6, i32 493), !dbg !132
  br label %if.end8, !dbg !133

if.end8:                                          ; preds = %if.then6, %if.end3
  %7 = load i8*, i8** %dir_name, align 8, !dbg !134
  call void @free(i8* %7) #7, !dbg !135
  br label %return, !dbg !136

return:                                           ; preds = %if.end8, %if.then2, %if.then
  ret void, !dbg !137
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare noalias i8* @strdup(i8*) #2

; Function Attrs: nounwind readonly
declare i8* @strrchr(i8*, i32) #3

declare i32 @mkdir(...) #4

; Function Attrs: nounwind
declare void @free(i8*) #2

; Function Attrs: nounwind uwtable
define void @bftpdutmp_init() #0 !dbg !12 {
entry:
  %filename = alloca i8*, align 8
  call void @llvm.dbg.declare(metadata i8** %filename, metadata !139, metadata !104), !dbg !140
  %call = call i8* @config_getoption(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str, i32 0, i32 0)), !dbg !141
  %call1 = call noalias i8* @strdup(i8* %call) #7, !dbg !142
  store i8* %call1, i8** %filename, align 8, !dbg !140
  %0 = load i8*, i8** %filename, align 8, !dbg !144
  %tobool = icmp ne i8* %0, null, !dbg !144
  br i1 %tobool, label %if.end, label %if.then, !dbg !146

if.then:                                          ; preds = %entry
  br label %return, !dbg !147

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %filename, align 8, !dbg !148
  %call2 = call i32 @strcasecmp(i8* %1, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.1, i32 0, i32 0)) #8, !dbg !150
  %tobool3 = icmp ne i32 %call2, 0, !dbg !150
  br i1 %tobool3, label %lor.lhs.false, label %if.then5, !dbg !151

lor.lhs.false:                                    ; preds = %if.end
  %2 = load i8*, i8** %filename, align 8, !dbg !152
  %arrayidx = getelementptr inbounds i8, i8* %2, i64 0, !dbg !152
  %3 = load i8, i8* %arrayidx, align 1, !dbg !152
  %tobool4 = icmp ne i8 %3, 0, !dbg !152
  br i1 %tobool4, label %if.end6, label %if.then5, !dbg !154

if.then5:                                         ; preds = %lor.lhs.false, %if.end
  br label %return, !dbg !155

if.end6:                                          ; preds = %lor.lhs.false
  %4 = load i8*, i8** %filename, align 8, !dbg !156
  call void @bftpdutmp_create_dir(i8* %4), !dbg !157
  %5 = load i8*, i8** %filename, align 8, !dbg !158
  %call7 = call %struct._IO_FILE* @fopen64(i8* %5, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0)), !dbg !159
  store %struct._IO_FILE* %call7, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !160
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !161
  %tobool8 = icmp ne %struct._IO_FILE* %6, null, !dbg !161
  br i1 %tobool8, label %if.then9, label %if.end11, !dbg !163

if.then9:                                         ; preds = %if.end6
  %7 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !164
  %call10 = call i32 @fclose(%struct._IO_FILE* %7), !dbg !165
  br label %if.end11, !dbg !165

if.end11:                                         ; preds = %if.then9, %if.end6
  %8 = load i8*, i8** %filename, align 8, !dbg !166
  %call12 = call %struct._IO_FILE* @fopen64(i8* %8, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.3, i32 0, i32 0)), !dbg !168
  store %struct._IO_FILE* %call12, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !169
  %tobool13 = icmp ne %struct._IO_FILE* %call12, null, !dbg !169
  br i1 %tobool13, label %if.end15, label %if.then14, !dbg !170

if.then14:                                        ; preds = %if.end11
  %9 = load i8*, i8** %filename, align 8, !dbg !171
  call void (i8*, ...) @bftpd_log(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.4, i32 0, i32 0), i8* %9), !dbg !173
  %10 = load i8*, i8** %filename, align 8, !dbg !174
  call void (i8, i8*, ...) @control_printf(i8 signext 2, i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.5, i32 0, i32 0), i8* %10), !dbg !175
  call void @exit(i32 1) #9, !dbg !176
  unreachable, !dbg !176

if.end15:                                         ; preds = %if.end11
  %11 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !177
  call void @rewind(%struct._IO_FILE* %11), !dbg !178
  %12 = load i8*, i8** %filename, align 8, !dbg !179
  call void @free(i8* %12) #7, !dbg !180
  br label %return, !dbg !181

return:                                           ; preds = %if.end15, %if.then5, %if.then
  ret void, !dbg !182
}

declare i8* @config_getoption(i8*) #4

; Function Attrs: nounwind readonly
declare i32 @strcasecmp(i8*, i8*) #3

declare %struct._IO_FILE* @fopen64(i8*, i8*) #4

declare i32 @fclose(%struct._IO_FILE*) #4

declare void @bftpd_log(i8*, ...) #4

declare void @control_printf(i8 signext, i8*, ...) #4

; Function Attrs: noreturn nounwind
declare void @exit(i32) #5

declare void @rewind(%struct._IO_FILE*) #4

; Function Attrs: nounwind uwtable
define void @bftpdutmp_end() #0 !dbg !15 {
entry:
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !183
  %tobool = icmp ne %struct._IO_FILE* %0, null, !dbg !183
  br i1 %tobool, label %if.then, label %if.end2, !dbg !185

if.then:                                          ; preds = %entry
  %1 = load i64, i64* @bftpdutmp_offset, align 8, !dbg !186
  %cmp = icmp ne i64 %1, -1, !dbg !189
  br i1 %cmp, label %if.then1, label %if.end, !dbg !190

if.then1:                                         ; preds = %if.then
  call void @bftpdutmp_log(i8 signext 0), !dbg !191
  br label %if.end, !dbg !191

if.end:                                           ; preds = %if.then1, %if.then
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !192
  %call = call i32 @fclose(%struct._IO_FILE* %2), !dbg !193
  store %struct._IO_FILE* null, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !194
  br label %if.end2, !dbg !195

if.end2:                                          ; preds = %if.end, %entry
  ret void, !dbg !196
}

; Function Attrs: nounwind uwtable
define void @bftpdutmp_log(i8 signext %type) #0 !dbg !16 {
entry:
  %type.addr = alloca i8, align 1
  %ut = alloca %struct.bftpdutmp, align 8
  %tmp = alloca %struct.bftpdutmp, align 8
  %i = alloca i64, align 8
  %max_length = alloca i32, align 4
  store i8 %type, i8* %type.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %type.addr, metadata !197, metadata !104), !dbg !198
  call void @llvm.dbg.declare(metadata %struct.bftpdutmp* %ut, metadata !199, metadata !104), !dbg !217
  call void @llvm.dbg.declare(metadata %struct.bftpdutmp* %tmp, metadata !218, metadata !104), !dbg !219
  call void @llvm.dbg.declare(metadata i64* %i, metadata !220, metadata !104), !dbg !221
  call void @llvm.dbg.declare(metadata i32* %max_length, metadata !222, metadata !104), !dbg !223
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !224
  %tobool = icmp ne %struct._IO_FILE* %0, null, !dbg !224
  br i1 %tobool, label %if.end, label %if.then, !dbg !226

if.then:                                          ; preds = %entry
  br label %return, !dbg !227

if.end:                                           ; preds = %entry
  %1 = bitcast %struct.bftpdutmp* %ut to i8*, !dbg !228
  call void @llvm.memset.p0i8.i64(i8* %1, i8 0, i64 304, i32 8, i1 false), !dbg !228
  %call = call i32 @getpid() #7, !dbg !229
  %bu_pid = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %ut, i32 0, i32 1, !dbg !230
  store i32 %call, i32* %bu_pid, align 4, !dbg !231
  %2 = load i8, i8* %type.addr, align 1, !dbg !232
  %tobool3 = icmp ne i8 %2, 0, !dbg !232
  br i1 %tobool3, label %if.then4, label %if.else, !dbg !234

if.then4:                                         ; preds = %if.end
  %bu_type = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %ut, i32 0, i32 0, !dbg !235
  store i8 1, i8* %bu_type, align 8, !dbg !237
  %bu_name = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %ut, i32 0, i32 2, !dbg !238
  %arraydecay = getelementptr inbounds [31 x i8], [31 x i8]* %bu_name, i32 0, i32 0, !dbg !239
  %call5 = call i8* @strncpy(i8* %arraydecay, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @user, i32 0, i32 0), i64 31) #7, !dbg !240
  store i32 256, i32* %max_length, align 4, !dbg !241
  %bu_host = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %ut, i32 0, i32 3, !dbg !242
  %arraydecay6 = getelementptr inbounds [256 x i8], [256 x i8]* %bu_host, i32 0, i32 0, !dbg !243
  %3 = load i8*, i8** @remotehostname, align 8, !dbg !244
  %4 = load i32, i32* %max_length, align 4, !dbg !245
  %conv = sext i32 %4 to i64, !dbg !245
  %call7 = call i8* @strncpy(i8* %arraydecay6, i8* %3, i64 %conv) #7, !dbg !246
  %5 = load i32, i32* %max_length, align 4, !dbg !247
  %sub = sub nsw i32 %5, 1, !dbg !248
  %idxprom = sext i32 %sub to i64, !dbg !249
  %bu_host8 = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %ut, i32 0, i32 3, !dbg !250
  %arrayidx = getelementptr inbounds [256 x i8], [256 x i8]* %bu_host8, i64 0, i64 %idxprom, !dbg !249
  store i8 0, i8* %arrayidx, align 1, !dbg !251
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !252
  call void @rewind(%struct._IO_FILE* %6), !dbg !253
  store i64 0, i64* %i, align 8, !dbg !254
  br label %while.cond, !dbg !255

while.cond:                                       ; preds = %if.end14, %if.then4
  %7 = bitcast %struct.bftpdutmp* %tmp to i8*, !dbg !256
  %8 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !258
  %call9 = call i64 @fread(i8* %7, i64 304, i64 1, %struct._IO_FILE* %8), !dbg !259
  %tobool10 = icmp ne i64 %call9, 0, !dbg !260
  br i1 %tobool10, label %while.body, label %while.end, !dbg !260

while.body:                                       ; preds = %while.cond
  %bu_type11 = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %tmp, i32 0, i32 0, !dbg !261
  %9 = load i8, i8* %bu_type11, align 8, !dbg !261
  %tobool12 = icmp ne i8 %9, 0, !dbg !264
  br i1 %tobool12, label %if.end14, label %if.then13, !dbg !265

if.then13:                                        ; preds = %while.body
  br label %while.end, !dbg !266

if.end14:                                         ; preds = %while.body
  %10 = load i64, i64* %i, align 8, !dbg !267
  %inc = add nsw i64 %10, 1, !dbg !267
  store i64 %inc, i64* %i, align 8, !dbg !267
  br label %while.cond, !dbg !268

while.end:                                        ; preds = %if.then13, %while.cond
  %11 = load i64, i64* %i, align 8, !dbg !270
  %mul = mul i64 %11, 304, !dbg !271
  store i64 %mul, i64* @bftpdutmp_offset, align 8, !dbg !272
  br label %if.end16, !dbg !273

if.else:                                          ; preds = %if.end
  %bu_type15 = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %ut, i32 0, i32 0, !dbg !274
  store i8 0, i8* %bu_type15, align 8, !dbg !275
  br label %if.end16

if.end16:                                         ; preds = %if.else, %while.end
  %bu_time = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %ut, i32 0, i32 4, !dbg !276
  %call17 = call i64 @time(i64* %bu_time) #7, !dbg !277
  %12 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !278
  %13 = load i64, i64* @bftpdutmp_offset, align 8, !dbg !279
  %call18 = call i32 @fseek(%struct._IO_FILE* %12, i64 %13, i32 0), !dbg !280
  %14 = bitcast %struct.bftpdutmp* %ut to i8*, !dbg !281
  %15 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !282
  %call19 = call i64 @fwrite(i8* %14, i64 304, i64 1, %struct._IO_FILE* %15), !dbg !283
  %16 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !284
  %call20 = call i32 @fflush(%struct._IO_FILE* %16), !dbg !285
  br label %return, !dbg !286

return:                                           ; preds = %if.end16, %if.then
  ret void, !dbg !287
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #6

; Function Attrs: nounwind
declare i32 @getpid() #2

; Function Attrs: nounwind
declare i8* @strncpy(i8*, i8*, i64) #2

declare i64 @fread(i8*, i64, i64, %struct._IO_FILE*) #4

; Function Attrs: nounwind
declare i64 @time(i64*) #2

declare i32 @fseek(%struct._IO_FILE*, i64, i32) #4

declare i64 @fwrite(i8*, i64, i64, %struct._IO_FILE*) #4

declare i32 @fflush(%struct._IO_FILE*) #4

; Function Attrs: nounwind uwtable
define signext i8 @bftpdutmp_pidexists(i32 %pid) #0 !dbg !19 {
entry:
  %retval = alloca i8, align 1
  %pid.addr = alloca i32, align 4
  %tmp = alloca %struct.bftpdutmp, align 8
  store i32 %pid, i32* %pid.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pid.addr, metadata !289, metadata !104), !dbg !290
  call void @llvm.dbg.declare(metadata %struct.bftpdutmp* %tmp, metadata !291, metadata !104), !dbg !292
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !293
  %tobool = icmp ne %struct._IO_FILE* %0, null, !dbg !293
  br i1 %tobool, label %if.end, label %if.then, !dbg !295

if.then:                                          ; preds = %entry
  store i8 0, i8* %retval, align 1, !dbg !296
  br label %return, !dbg !296

if.end:                                           ; preds = %entry
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !297
  call void @rewind(%struct._IO_FILE* %1), !dbg !298
  br label %while.cond, !dbg !299

while.cond:                                       ; preds = %if.end4, %if.end
  %2 = bitcast %struct.bftpdutmp* %tmp to i8*, !dbg !300
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !302
  %call = call i64 @fread(i8* %2, i64 304, i64 1, %struct._IO_FILE* %3), !dbg !303
  %tobool1 = icmp ne i64 %call, 0, !dbg !304
  br i1 %tobool1, label %while.body, label %while.end, !dbg !304

while.body:                                       ; preds = %while.cond
  %bu_pid = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %tmp, i32 0, i32 1, !dbg !305
  %4 = load i32, i32* %bu_pid, align 4, !dbg !305
  %5 = load i32, i32* %pid.addr, align 4, !dbg !308
  %cmp = icmp eq i32 %4, %5, !dbg !309
  br i1 %cmp, label %land.lhs.true, label %if.end4, !dbg !310

land.lhs.true:                                    ; preds = %while.body
  %bu_type = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %tmp, i32 0, i32 0, !dbg !311
  %6 = load i8, i8* %bu_type, align 8, !dbg !311
  %conv = sext i8 %6 to i32, !dbg !313
  %tobool2 = icmp ne i32 %conv, 0, !dbg !313
  br i1 %tobool2, label %if.then3, label %if.end4, !dbg !314

if.then3:                                         ; preds = %land.lhs.true
  store i8 1, i8* %retval, align 1, !dbg !315
  br label %return, !dbg !315

if.end4:                                          ; preds = %land.lhs.true, %while.body
  br label %while.cond, !dbg !316

while.end:                                        ; preds = %while.cond
  store i8 0, i8* %retval, align 1, !dbg !318
  br label %return, !dbg !318

return:                                           ; preds = %while.end, %if.then3, %if.then
  %7 = load i8, i8* %retval, align 1, !dbg !319
  ret i8 %7, !dbg !319
}

; Function Attrs: nounwind uwtable
define i32 @bftpdutmp_usercount(i8* %username) #0 !dbg !27 {
entry:
  %retval = alloca i32, align 4
  %username.addr = alloca i8*, align 8
  %tmp = alloca %struct.bftpdutmp, align 8
  %count = alloca i32, align 4
  store i8* %username, i8** %username.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %username.addr, metadata !320, metadata !104), !dbg !321
  call void @llvm.dbg.declare(metadata %struct.bftpdutmp* %tmp, metadata !322, metadata !104), !dbg !323
  call void @llvm.dbg.declare(metadata i32* %count, metadata !324, metadata !104), !dbg !325
  store i32 0, i32* %count, align 4, !dbg !325
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !326
  %tobool = icmp ne %struct._IO_FILE* %0, null, !dbg !326
  br i1 %tobool, label %if.end, label %if.then, !dbg !328

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !329
  br label %return, !dbg !329

if.end:                                           ; preds = %entry
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !330
  call void @rewind(%struct._IO_FILE* %1), !dbg !331
  br label %while.cond, !dbg !332

while.cond:                                       ; preds = %if.end9, %if.end
  %2 = bitcast %struct.bftpdutmp* %tmp to i8*, !dbg !333
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !335
  %call = call i64 @fread(i8* %2, i64 304, i64 1, %struct._IO_FILE* %3), !dbg !336
  %tobool2 = icmp ne i64 %call, 0, !dbg !337
  br i1 %tobool2, label %while.body, label %while.end, !dbg !337

while.body:                                       ; preds = %while.cond
  %bu_type = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %tmp, i32 0, i32 0, !dbg !338
  %4 = load i8, i8* %bu_type, align 8, !dbg !338
  %conv = sext i8 %4 to i32, !dbg !341
  %tobool3 = icmp ne i32 %conv, 0, !dbg !341
  br i1 %tobool3, label %land.lhs.true, label %if.end9, !dbg !342

land.lhs.true:                                    ; preds = %while.body
  %bu_name = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %tmp, i32 0, i32 2, !dbg !343
  %arraydecay = getelementptr inbounds [31 x i8], [31 x i8]* %bu_name, i32 0, i32 0, !dbg !345
  %5 = load i8*, i8** %username.addr, align 8, !dbg !346
  %call4 = call i32 @strcmp(i8* %arraydecay, i8* %5) #8, !dbg !347
  %tobool5 = icmp ne i32 %call4, 0, !dbg !347
  br i1 %tobool5, label %lor.lhs.false, label %if.then8, !dbg !348

lor.lhs.false:                                    ; preds = %land.lhs.true
  %6 = load i8*, i8** %username.addr, align 8, !dbg !349
  %call6 = call i32 @strcmp(i8* %6, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.6, i32 0, i32 0)) #8, !dbg !351
  %tobool7 = icmp ne i32 %call6, 0, !dbg !351
  br i1 %tobool7, label %if.end9, label %if.then8, !dbg !352

if.then8:                                         ; preds = %lor.lhs.false, %land.lhs.true
  %7 = load i32, i32* %count, align 4, !dbg !353
  %inc = add nsw i32 %7, 1, !dbg !353
  store i32 %inc, i32* %count, align 4, !dbg !353
  br label %if.end9, !dbg !354

if.end9:                                          ; preds = %if.then8, %lor.lhs.false, %while.body
  br label %while.cond, !dbg !355

while.end:                                        ; preds = %while.cond
  %8 = load i32, i32* %count, align 4, !dbg !357
  %cmp = icmp slt i32 %8, 0, !dbg !359
  br i1 %cmp, label %if.then11, label %if.end12, !dbg !360

if.then11:                                        ; preds = %while.end
  store i32 1, i32* %count, align 4, !dbg !361
  br label %if.end12, !dbg !362

if.end12:                                         ; preds = %if.then11, %while.end
  %9 = load i32, i32* %count, align 4, !dbg !363
  store i32 %9, i32* %retval, align 4, !dbg !364
  br label %return, !dbg !364

return:                                           ; preds = %if.end12, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !365
  ret i32 %10, !dbg !365
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #3

; Function Attrs: nounwind uwtable
define i32 @bftpdutmp_dup_ip_count(i8* %ip_address) #0 !dbg !30 {
entry:
  %retval = alloca i32, align 4
  %ip_address.addr = alloca i8*, align 8
  %tmp = alloca %struct.bftpdutmp, align 8
  %count = alloca i32, align 4
  store i8* %ip_address, i8** %ip_address.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ip_address.addr, metadata !366, metadata !104), !dbg !367
  call void @llvm.dbg.declare(metadata %struct.bftpdutmp* %tmp, metadata !368, metadata !104), !dbg !369
  call void @llvm.dbg.declare(metadata i32* %count, metadata !370, metadata !104), !dbg !371
  store i32 0, i32* %count, align 4, !dbg !371
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !372
  %tobool = icmp ne %struct._IO_FILE* %0, null, !dbg !372
  br i1 %tobool, label %if.end, label %if.then, !dbg !374

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !375
  br label %return, !dbg !375

if.end:                                           ; preds = %entry
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !376
  call void @rewind(%struct._IO_FILE* %1), !dbg !377
  br label %while.cond, !dbg !378

while.cond:                                       ; preds = %if.end7, %if.end
  %2 = bitcast %struct.bftpdutmp* %tmp to i8*, !dbg !379
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !381
  %call = call i64 @fread(i8* %2, i64 304, i64 1, %struct._IO_FILE* %3), !dbg !382
  %tobool2 = icmp ne i64 %call, 0, !dbg !383
  br i1 %tobool2, label %while.body, label %while.end, !dbg !383

while.body:                                       ; preds = %while.cond
  %bu_type = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %tmp, i32 0, i32 0, !dbg !384
  %4 = load i8, i8* %bu_type, align 8, !dbg !384
  %conv = sext i8 %4 to i32, !dbg !387
  %tobool3 = icmp ne i32 %conv, 0, !dbg !387
  br i1 %tobool3, label %land.lhs.true, label %if.end7, !dbg !388

land.lhs.true:                                    ; preds = %while.body
  %bu_host = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %tmp, i32 0, i32 3, !dbg !389
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %bu_host, i32 0, i32 0, !dbg !391
  %5 = load i8*, i8** %ip_address.addr, align 8, !dbg !392
  %call4 = call i32 @strcmp(i8* %arraydecay, i8* %5) #8, !dbg !393
  %tobool5 = icmp ne i32 %call4, 0, !dbg !393
  br i1 %tobool5, label %if.end7, label %if.then6, !dbg !394

if.then6:                                         ; preds = %land.lhs.true
  %6 = load i32, i32* %count, align 4, !dbg !395
  %inc = add nsw i32 %6, 1, !dbg !395
  store i32 %inc, i32* %count, align 4, !dbg !395
  br label %if.end7, !dbg !396

if.end7:                                          ; preds = %if.then6, %land.lhs.true, %while.body
  br label %while.cond, !dbg !397

while.end:                                        ; preds = %while.cond
  %7 = load i32, i32* %count, align 4, !dbg !399
  store i32 %7, i32* %retval, align 4, !dbg !400
  br label %return, !dbg !400

return:                                           ; preds = %while.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !401
  ret i32 %8, !dbg !401
}

; Function Attrs: nounwind uwtable
define void @bftpdutmp_remove_pid(i32 %pid) #0 !dbg !31 {
entry:
  %pid.addr = alloca i32, align 4
  %current = alloca %struct.bftpdutmp, align 8
  %index = alloca i32, align 4
  store i32 %pid, i32* %pid.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pid.addr, metadata !402, metadata !104), !dbg !403
  call void @llvm.dbg.declare(metadata %struct.bftpdutmp* %current, metadata !404, metadata !104), !dbg !405
  call void @llvm.dbg.declare(metadata i32* %index, metadata !406, metadata !104), !dbg !407
  store i32 0, i32* %index, align 4, !dbg !407
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !408
  %tobool = icmp ne %struct._IO_FILE* %0, null, !dbg !408
  br i1 %tobool, label %if.end, label %if.then, !dbg !410

if.then:                                          ; preds = %entry
  br label %while.end, !dbg !411

if.end:                                           ; preds = %entry
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !412
  call void @rewind(%struct._IO_FILE* %1), !dbg !413
  br label %while.cond, !dbg !414

while.cond:                                       ; preds = %if.end5, %if.end
  %2 = bitcast %struct.bftpdutmp* %current to i8*, !dbg !415
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !417
  %call = call i64 @fread(i8* %2, i64 304, i64 1, %struct._IO_FILE* %3), !dbg !418
  %tobool1 = icmp ne i64 %call, 0, !dbg !419
  br i1 %tobool1, label %while.body, label %while.end, !dbg !419

while.body:                                       ; preds = %while.cond
  %bu_pid = getelementptr inbounds %struct.bftpdutmp, %struct.bftpdutmp* %current, i32 0, i32 1, !dbg !420
  %4 = load i32, i32* %bu_pid, align 4, !dbg !420
  %5 = load i32, i32* %pid.addr, align 4, !dbg !423
  %cmp = icmp eq i32 %4, %5, !dbg !424
  br i1 %cmp, label %if.then2, label %if.end5, !dbg !425

if.then2:                                         ; preds = %while.body
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !426
  %7 = load i32, i32* %index, align 4, !dbg !428
  %conv = sext i32 %7 to i64, !dbg !428
  %mul = mul i64 %conv, 304, !dbg !429
  %call3 = call i32 @fseek(%struct._IO_FILE* %6, i64 %mul, i32 0), !dbg !430
  %8 = bitcast %struct.bftpdutmp* %current to i8*, !dbg !431
  call void @llvm.memset.p0i8.i64(i8* %8, i8 0, i64 304, i32 8, i1 false), !dbg !431
  %9 = bitcast %struct.bftpdutmp* %current to i8*, !dbg !432
  %10 = load %struct._IO_FILE*, %struct._IO_FILE** @bftpdutmp, align 8, !dbg !433
  %call4 = call i64 @fwrite(i8* %9, i64 304, i64 1, %struct._IO_FILE* %10), !dbg !434
  br label %if.end5, !dbg !435

if.end5:                                          ; preds = %if.then2, %while.body
  %11 = load i32, i32* %index, align 4, !dbg !436
  %inc = add nsw i32 %11, 1, !dbg !436
  store i32 %inc, i32* %index, align 4, !dbg !436
  br label %while.cond, !dbg !437

while.end:                                        ; preds = %if.then, %while.cond
  ret void, !dbg !439
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { argmemonly nounwind }
attributes #7 = { nounwind }
attributes #8 = { nounwind readonly }
attributes #9 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!100, !101}
!llvm.ident = !{!102}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !5, globals: !34)
!1 = !DIFile(filename: "bftpdutmp.c", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!2 = !{}
!3 = !{!4}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !{!6, !12, !15, !16, !19, !27, !30, !31}
!6 = distinct !DISubprogram(name: "bftpdutmp_create_dir", scope: !7, file: !7, line: 17, type: !8, isLocal: false, isDefinition: true, scopeLine: 18, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!7 = !DIFile(filename: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/bftpdutmp.c", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!8 = !DISubroutineType(types: !9)
!9 = !{null, !10}
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!11 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!12 = distinct !DISubprogram(name: "bftpdutmp_init", scope: !7, file: !7, line: 38, type: !13, isLocal: false, isDefinition: true, scopeLine: 39, isOptimized: false, variables: !2)
!13 = !DISubroutineType(types: !14)
!14 = !{null}
!15 = distinct !DISubprogram(name: "bftpdutmp_end", scope: !7, file: !7, line: 67, type: !13, isLocal: false, isDefinition: true, scopeLine: 68, isOptimized: false, variables: !2)
!16 = distinct !DISubprogram(name: "bftpdutmp_log", scope: !7, file: !7, line: 77, type: !17, isLocal: false, isDefinition: true, scopeLine: 78, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!17 = !DISubroutineType(types: !18)
!18 = !{null, !11}
!19 = distinct !DISubprogram(name: "bftpdutmp_pidexists", scope: !7, file: !7, line: 113, type: !20, isLocal: false, isDefinition: true, scopeLine: 114, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!20 = !DISubroutineType(types: !21)
!21 = !{!11, !22}
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "pid_t", file: !23, line: 98, baseType: !24)
!23 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!24 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pid_t", file: !25, line: 133, baseType: !26)
!25 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!26 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!27 = distinct !DISubprogram(name: "bftpdutmp_usercount", scope: !7, file: !7, line: 126, type: !28, isLocal: false, isDefinition: true, scopeLine: 127, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!28 = !DISubroutineType(types: !29)
!29 = !{!26, !10}
!30 = distinct !DISubprogram(name: "bftpdutmp_dup_ip_count", scope: !7, file: !7, line: 147, type: !28, isLocal: false, isDefinition: true, scopeLine: 148, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!31 = distinct !DISubprogram(name: "bftpdutmp_remove_pid", scope: !7, file: !7, line: 176, type: !32, isLocal: false, isDefinition: true, scopeLine: 177, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!32 = !DISubroutineType(types: !33)
!33 = !{null, !26}
!34 = !{!35, !94, !95, !97, !98, !99}
!35 = !DIGlobalVariable(name: "bftpdutmp", scope: !0, file: !7, line: 14, type: !36, isLocal: false, isDefinition: true, variable: %struct._IO_FILE** @bftpdutmp)
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64, align: 64)
!37 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !38, line: 48, baseType: !39)
!38 = !DIFile(filename: "/usr/include/stdio.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!39 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !40, line: 245, size: 1728, align: 64, elements: !41)
!40 = !DIFile(filename: "/usr/include/libio.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!41 = !{!42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !62, !63, !64, !65, !68, !70, !72, !76, !79, !81, !82, !83, !84, !85, !89, !90}
!42 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !39, file: !40, line: 246, baseType: !26, size: 32, align: 32)
!43 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !39, file: !40, line: 251, baseType: !10, size: 64, align: 64, offset: 64)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !39, file: !40, line: 252, baseType: !10, size: 64, align: 64, offset: 128)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !39, file: !40, line: 253, baseType: !10, size: 64, align: 64, offset: 192)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !39, file: !40, line: 254, baseType: !10, size: 64, align: 64, offset: 256)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !39, file: !40, line: 255, baseType: !10, size: 64, align: 64, offset: 320)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !39, file: !40, line: 256, baseType: !10, size: 64, align: 64, offset: 384)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !39, file: !40, line: 257, baseType: !10, size: 64, align: 64, offset: 448)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !39, file: !40, line: 258, baseType: !10, size: 64, align: 64, offset: 512)
!51 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !39, file: !40, line: 260, baseType: !10, size: 64, align: 64, offset: 576)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !39, file: !40, line: 261, baseType: !10, size: 64, align: 64, offset: 640)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !39, file: !40, line: 262, baseType: !10, size: 64, align: 64, offset: 704)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !39, file: !40, line: 264, baseType: !55, size: 64, align: 64, offset: 768)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !40, line: 160, size: 192, align: 64, elements: !57)
!57 = !{!58, !59, !61}
!58 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !56, file: !40, line: 161, baseType: !55, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !56, file: !40, line: 162, baseType: !60, size: 64, align: 64, offset: 64)
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !39, size: 64, align: 64)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !56, file: !40, line: 166, baseType: !26, size: 32, align: 32, offset: 128)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !39, file: !40, line: 266, baseType: !60, size: 64, align: 64, offset: 832)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !39, file: !40, line: 268, baseType: !26, size: 32, align: 32, offset: 896)
!64 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !39, file: !40, line: 272, baseType: !26, size: 32, align: 32, offset: 928)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !39, file: !40, line: 274, baseType: !66, size: 64, align: 64, offset: 960)
!66 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !25, line: 131, baseType: !67)
!67 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !39, file: !40, line: 278, baseType: !69, size: 16, align: 16, offset: 1024)
!69 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !39, file: !40, line: 279, baseType: !71, size: 8, align: 8, offset: 1040)
!71 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !39, file: !40, line: 280, baseType: !73, size: 8, align: 8, offset: 1048)
!73 = !DICompositeType(tag: DW_TAG_array_type, baseType: !11, size: 8, align: 8, elements: !74)
!74 = !{!75}
!75 = !DISubrange(count: 1)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !39, file: !40, line: 284, baseType: !77, size: 64, align: 64, offset: 1088)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !40, line: 154, baseType: null)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !39, file: !40, line: 293, baseType: !80, size: 64, align: 64, offset: 1152)
!80 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !25, line: 132, baseType: !67)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !39, file: !40, line: 302, baseType: !4, size: 64, align: 64, offset: 1216)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !39, file: !40, line: 303, baseType: !4, size: 64, align: 64, offset: 1280)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !39, file: !40, line: 304, baseType: !4, size: 64, align: 64, offset: 1344)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !39, file: !40, line: 305, baseType: !4, size: 64, align: 64, offset: 1408)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !39, file: !40, line: 306, baseType: !86, size: 64, align: 64, offset: 1472)
!86 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !87, line: 62, baseType: !88)
!87 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!88 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !39, file: !40, line: 308, baseType: !26, size: 32, align: 32, offset: 1536)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !39, file: !40, line: 310, baseType: !91, size: 160, align: 8, offset: 1568)
!91 = !DICompositeType(tag: DW_TAG_array_type, baseType: !11, size: 160, align: 8, elements: !92)
!92 = !{!93}
!93 = !DISubrange(count: 20)
!94 = !DIGlobalVariable(name: "bftpdutmp_offset", scope: !0, file: !7, line: 15, type: !67, isLocal: false, isDefinition: true, variable: i64* @bftpdutmp_offset)
!95 = !DIGlobalVariable(name: "configpath", scope: !0, file: !96, line: 25, type: !10, isLocal: false, isDefinition: true, variable: i8** @configpath)
!96 = !DIFile(filename: "./main.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!97 = !DIGlobalVariable(name: "daemonmode", scope: !0, file: !96, line: 26, type: !26, isLocal: false, isDefinition: true, variable: i32* @daemonmode)
!98 = !DIGlobalVariable(name: "pre_write_script", scope: !0, file: !96, line: 29, type: !10, isLocal: false, isDefinition: true, variable: i8** @pre_write_script)
!99 = !DIGlobalVariable(name: "post_write_script", scope: !0, file: !96, line: 30, type: !10, isLocal: false, isDefinition: true, variable: i8** @post_write_script)
!100 = !{i32 2, !"Dwarf Version", i32 4}
!101 = !{i32 2, !"Debug Info Version", i32 3}
!102 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!103 = !DILocalVariable(name: "path_to_file", arg: 1, scope: !6, file: !7, line: 17, type: !10)
!104 = !DIExpression()
!105 = !DILocation(line: 17, column: 33, scope: !6)
!106 = !DILocalVariable(name: "dir_name", scope: !6, file: !7, line: 19, type: !10)
!107 = !DILocation(line: 19, column: 11, scope: !6)
!108 = !DILocalVariable(name: "index", scope: !6, file: !7, line: 19, type: !10)
!109 = !DILocation(line: 19, column: 22, scope: !6)
!110 = !DILocation(line: 21, column: 11, scope: !111)
!111 = distinct !DILexicalBlock(scope: !6, file: !7, line: 21, column: 9)
!112 = !DILocation(line: 21, column: 9, scope: !6)
!113 = !DILocation(line: 21, column: 25, scope: !114)
!114 = !DILexicalBlockFile(scope: !111, file: !7, discriminator: 1)
!115 = !DILocation(line: 23, column: 23, scope: !6)
!116 = !DILocation(line: 23, column: 16, scope: !6)
!117 = !DILocation(line: 23, column: 14, scope: !6)
!118 = !DILocation(line: 24, column: 11, scope: !119)
!119 = distinct !DILexicalBlock(scope: !6, file: !7, line: 24, column: 9)
!120 = !DILocation(line: 24, column: 9, scope: !6)
!121 = !DILocation(line: 25, column: 8, scope: !119)
!122 = !DILocation(line: 27, column: 21, scope: !6)
!123 = !DILocation(line: 27, column: 13, scope: !6)
!124 = !DILocation(line: 27, column: 11, scope: !6)
!125 = !DILocation(line: 28, column: 9, scope: !126)
!126 = distinct !DILexicalBlock(scope: !6, file: !7, line: 28, column: 9)
!127 = !DILocation(line: 28, column: 9, scope: !6)
!128 = !DILocation(line: 30, column: 9, scope: !129)
!129 = distinct !DILexicalBlock(scope: !126, file: !7, line: 29, column: 5)
!130 = !DILocation(line: 30, column: 18, scope: !129)
!131 = !DILocation(line: 31, column: 15, scope: !129)
!132 = !DILocation(line: 31, column: 9, scope: !129)
!133 = !DILocation(line: 32, column: 5, scope: !129)
!134 = !DILocation(line: 33, column: 10, scope: !6)
!135 = !DILocation(line: 33, column: 5, scope: !6)
!136 = !DILocation(line: 34, column: 1, scope: !6)
!137 = !DILocation(line: 34, column: 1, scope: !138)
!138 = !DILexicalBlockFile(scope: !6, file: !7, discriminator: 1)
!139 = !DILocalVariable(name: "filename", scope: !12, file: !7, line: 40, type: !10)
!140 = !DILocation(line: 40, column: 8, scope: !12)
!141 = !DILocation(line: 40, column: 26, scope: !12)
!142 = !DILocation(line: 40, column: 19, scope: !143)
!143 = !DILexicalBlockFile(scope: !12, file: !7, discriminator: 1)
!144 = !DILocation(line: 42, column: 15, scope: !145)
!145 = distinct !DILexicalBlock(scope: !12, file: !7, line: 42, column: 13)
!146 = !DILocation(line: 42, column: 13, scope: !12)
!147 = !DILocation(line: 43, column: 13, scope: !145)
!148 = !DILocation(line: 45, column: 19, scope: !149)
!149 = distinct !DILexicalBlock(scope: !12, file: !7, line: 45, column: 6)
!150 = !DILocation(line: 45, column: 8, scope: !149)
!151 = !DILocation(line: 45, column: 38, scope: !149)
!152 = !DILocation(line: 45, column: 43, scope: !153)
!153 = !DILexicalBlockFile(scope: !149, file: !7, discriminator: 1)
!154 = !DILocation(line: 45, column: 6, scope: !153)
!155 = !DILocation(line: 46, column: 3, scope: !149)
!156 = !DILocation(line: 49, column: 26, scope: !12)
!157 = !DILocation(line: 49, column: 5, scope: !12)
!158 = !DILocation(line: 52, column: 23, scope: !12)
!159 = !DILocation(line: 52, column: 17, scope: !12)
!160 = !DILocation(line: 52, column: 15, scope: !12)
!161 = !DILocation(line: 53, column: 9, scope: !162)
!162 = distinct !DILexicalBlock(scope: !12, file: !7, line: 53, column: 9)
!163 = !DILocation(line: 53, column: 9, scope: !12)
!164 = !DILocation(line: 54, column: 16, scope: !162)
!165 = !DILocation(line: 54, column: 9, scope: !162)
!166 = !DILocation(line: 56, column: 29, scope: !167)
!167 = distinct !DILexicalBlock(scope: !12, file: !7, line: 56, column: 9)
!168 = !DILocation(line: 56, column: 23, scope: !167)
!169 = !DILocation(line: 56, column: 21, scope: !167)
!170 = !DILocation(line: 56, column: 9, scope: !12)
!171 = !DILocation(line: 57, column: 52, scope: !172)
!172 = distinct !DILexicalBlock(scope: !167, file: !7, line: 56, column: 47)
!173 = !DILocation(line: 57, column: 9, scope: !172)
!174 = !DILocation(line: 59, column: 63, scope: !172)
!175 = !DILocation(line: 58, column: 9, scope: !172)
!176 = !DILocation(line: 60, column: 9, scope: !172)
!177 = !DILocation(line: 62, column: 12, scope: !12)
!178 = !DILocation(line: 62, column: 5, scope: !12)
!179 = !DILocation(line: 64, column: 10, scope: !12)
!180 = !DILocation(line: 64, column: 5, scope: !12)
!181 = !DILocation(line: 65, column: 1, scope: !12)
!182 = !DILocation(line: 65, column: 1, scope: !143)
!183 = !DILocation(line: 69, column: 9, scope: !184)
!184 = distinct !DILexicalBlock(scope: !15, file: !7, line: 69, column: 9)
!185 = !DILocation(line: 69, column: 9, scope: !15)
!186 = !DILocation(line: 70, column: 13, scope: !187)
!187 = distinct !DILexicalBlock(scope: !188, file: !7, line: 70, column: 13)
!188 = distinct !DILexicalBlock(scope: !184, file: !7, line: 69, column: 20)
!189 = !DILocation(line: 70, column: 30, scope: !187)
!190 = !DILocation(line: 70, column: 13, scope: !188)
!191 = !DILocation(line: 71, column: 13, scope: !187)
!192 = !DILocation(line: 72, column: 16, scope: !188)
!193 = !DILocation(line: 72, column: 9, scope: !188)
!194 = !DILocation(line: 73, column: 19, scope: !188)
!195 = !DILocation(line: 74, column: 5, scope: !188)
!196 = !DILocation(line: 75, column: 1, scope: !15)
!197 = !DILocalVariable(name: "type", arg: 1, scope: !16, file: !7, line: 77, type: !11)
!198 = !DILocation(line: 77, column: 25, scope: !16)
!199 = !DILocalVariable(name: "ut", scope: !16, file: !7, line: 79, type: !200)
!200 = !DICompositeType(tag: DW_TAG_structure_type, name: "bftpdutmp", file: !201, line: 9, size: 2432, align: 64, elements: !202)
!201 = !DIFile(filename: "./bftpdutmp.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!202 = !{!203, !204, !205, !209, !213}
!203 = !DIDerivedType(tag: DW_TAG_member, name: "bu_type", scope: !200, file: !201, line: 10, baseType: !11, size: 8, align: 8)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "bu_pid", scope: !200, file: !201, line: 11, baseType: !22, size: 32, align: 32, offset: 32)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "bu_name", scope: !200, file: !201, line: 12, baseType: !206, size: 248, align: 8, offset: 64)
!206 = !DICompositeType(tag: DW_TAG_array_type, baseType: !11, size: 248, align: 8, elements: !207)
!207 = !{!208}
!208 = !DISubrange(count: 31)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "bu_host", scope: !200, file: !201, line: 13, baseType: !210, size: 2048, align: 8, offset: 312)
!210 = !DICompositeType(tag: DW_TAG_array_type, baseType: !11, size: 2048, align: 8, elements: !211)
!211 = !{!212}
!212 = !DISubrange(count: 256)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "bu_time", scope: !200, file: !201, line: 14, baseType: !214, size: 64, align: 64, offset: 2368)
!214 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !215, line: 75, baseType: !216)
!215 = !DIFile(filename: "/usr/include/time.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!216 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !25, line: 139, baseType: !67)
!217 = !DILocation(line: 79, column: 22, scope: !16)
!218 = !DILocalVariable(name: "tmp", scope: !16, file: !7, line: 79, type: !200)
!219 = !DILocation(line: 79, column: 26, scope: !16)
!220 = !DILocalVariable(name: "i", scope: !16, file: !7, line: 80, type: !67)
!221 = !DILocation(line: 80, column: 10, scope: !16)
!222 = !DILocalVariable(name: "max_length", scope: !16, file: !7, line: 81, type: !26)
!223 = !DILocation(line: 81, column: 9, scope: !16)
!224 = !DILocation(line: 83, column: 10, scope: !225)
!225 = distinct !DILexicalBlock(scope: !16, file: !7, line: 83, column: 9)
!226 = !DILocation(line: 83, column: 9, scope: !16)
!227 = !DILocation(line: 84, column: 9, scope: !225)
!228 = !DILocation(line: 85, column: 5, scope: !16)
!229 = !DILocation(line: 86, column: 17, scope: !16)
!230 = !DILocation(line: 86, column: 8, scope: !16)
!231 = !DILocation(line: 86, column: 15, scope: !16)
!232 = !DILocation(line: 87, column: 9, scope: !233)
!233 = distinct !DILexicalBlock(scope: !16, file: !7, line: 87, column: 9)
!234 = !DILocation(line: 87, column: 9, scope: !16)
!235 = !DILocation(line: 88, column: 12, scope: !236)
!236 = distinct !DILexicalBlock(scope: !233, file: !7, line: 87, column: 15)
!237 = !DILocation(line: 88, column: 20, scope: !236)
!238 = !DILocation(line: 89, column: 20, scope: !236)
!239 = !DILocation(line: 89, column: 17, scope: !236)
!240 = !DILocation(line: 89, column: 9, scope: !236)
!241 = !DILocation(line: 90, column: 20, scope: !236)
!242 = !DILocation(line: 91, column: 20, scope: !236)
!243 = !DILocation(line: 91, column: 17, scope: !236)
!244 = !DILocation(line: 91, column: 29, scope: !236)
!245 = !DILocation(line: 91, column: 45, scope: !236)
!246 = !DILocation(line: 91, column: 9, scope: !236)
!247 = !DILocation(line: 92, column: 20, scope: !236)
!248 = !DILocation(line: 92, column: 31, scope: !236)
!249 = !DILocation(line: 92, column: 9, scope: !236)
!250 = !DILocation(line: 92, column: 12, scope: !236)
!251 = !DILocation(line: 92, column: 36, scope: !236)
!252 = !DILocation(line: 94, column: 16, scope: !236)
!253 = !DILocation(line: 94, column: 9, scope: !236)
!254 = !DILocation(line: 95, column: 11, scope: !236)
!255 = !DILocation(line: 96, column: 9, scope: !236)
!256 = !DILocation(line: 96, column: 22, scope: !257)
!257 = !DILexicalBlockFile(scope: !236, file: !7, discriminator: 1)
!258 = !DILocation(line: 96, column: 53, scope: !257)
!259 = !DILocation(line: 96, column: 16, scope: !257)
!260 = !DILocation(line: 96, column: 9, scope: !257)
!261 = !DILocation(line: 97, column: 22, scope: !262)
!262 = distinct !DILexicalBlock(scope: !263, file: !7, line: 97, column: 17)
!263 = distinct !DILexicalBlock(scope: !236, file: !7, line: 96, column: 65)
!264 = !DILocation(line: 97, column: 18, scope: !262)
!265 = !DILocation(line: 97, column: 17, scope: !263)
!266 = !DILocation(line: 98, column: 17, scope: !262)
!267 = !DILocation(line: 99, column: 14, scope: !263)
!268 = !DILocation(line: 96, column: 9, scope: !269)
!269 = !DILexicalBlockFile(scope: !236, file: !7, discriminator: 2)
!270 = !DILocation(line: 101, column: 28, scope: !236)
!271 = !DILocation(line: 101, column: 30, scope: !236)
!272 = !DILocation(line: 101, column: 26, scope: !236)
!273 = !DILocation(line: 102, column: 5, scope: !236)
!274 = !DILocation(line: 105, column: 12, scope: !233)
!275 = !DILocation(line: 105, column: 20, scope: !233)
!276 = !DILocation(line: 107, column: 15, scope: !16)
!277 = !DILocation(line: 107, column: 5, scope: !16)
!278 = !DILocation(line: 108, column: 11, scope: !16)
!279 = !DILocation(line: 108, column: 22, scope: !16)
!280 = !DILocation(line: 108, column: 5, scope: !16)
!281 = !DILocation(line: 109, column: 12, scope: !16)
!282 = !DILocation(line: 109, column: 41, scope: !16)
!283 = !DILocation(line: 109, column: 5, scope: !16)
!284 = !DILocation(line: 110, column: 12, scope: !16)
!285 = !DILocation(line: 110, column: 5, scope: !16)
!286 = !DILocation(line: 111, column: 1, scope: !16)
!287 = !DILocation(line: 111, column: 1, scope: !288)
!288 = !DILexicalBlockFile(scope: !16, file: !7, discriminator: 1)
!289 = !DILocalVariable(name: "pid", arg: 1, scope: !19, file: !7, line: 113, type: !22)
!290 = !DILocation(line: 113, column: 32, scope: !19)
!291 = !DILocalVariable(name: "tmp", scope: !19, file: !7, line: 115, type: !200)
!292 = !DILocation(line: 115, column: 22, scope: !19)
!293 = !DILocation(line: 116, column: 7, scope: !294)
!294 = distinct !DILexicalBlock(scope: !19, file: !7, line: 116, column: 6)
!295 = !DILocation(line: 116, column: 6, scope: !19)
!296 = !DILocation(line: 117, column: 3, scope: !294)
!297 = !DILocation(line: 118, column: 12, scope: !19)
!298 = !DILocation(line: 118, column: 5, scope: !19)
!299 = !DILocation(line: 119, column: 5, scope: !19)
!300 = !DILocation(line: 119, column: 18, scope: !301)
!301 = !DILexicalBlockFile(scope: !19, file: !7, discriminator: 1)
!302 = !DILocation(line: 119, column: 49, scope: !301)
!303 = !DILocation(line: 119, column: 12, scope: !301)
!304 = !DILocation(line: 119, column: 5, scope: !301)
!305 = !DILocation(line: 120, column: 18, scope: !306)
!306 = distinct !DILexicalBlock(scope: !307, file: !7, line: 120, column: 13)
!307 = distinct !DILexicalBlock(scope: !19, file: !7, line: 119, column: 61)
!308 = !DILocation(line: 120, column: 28, scope: !306)
!309 = !DILocation(line: 120, column: 25, scope: !306)
!310 = !DILocation(line: 120, column: 33, scope: !306)
!311 = !DILocation(line: 120, column: 41, scope: !312)
!312 = !DILexicalBlockFile(scope: !306, file: !7, discriminator: 1)
!313 = !DILocation(line: 120, column: 36, scope: !312)
!314 = !DILocation(line: 120, column: 13, scope: !312)
!315 = !DILocation(line: 121, column: 13, scope: !306)
!316 = !DILocation(line: 119, column: 5, scope: !317)
!317 = !DILexicalBlockFile(scope: !19, file: !7, discriminator: 2)
!318 = !DILocation(line: 123, column: 5, scope: !19)
!319 = !DILocation(line: 124, column: 1, scope: !19)
!320 = !DILocalVariable(name: "username", arg: 1, scope: !27, file: !7, line: 126, type: !10)
!321 = !DILocation(line: 126, column: 31, scope: !27)
!322 = !DILocalVariable(name: "tmp", scope: !27, file: !7, line: 128, type: !200)
!323 = !DILocation(line: 128, column: 22, scope: !27)
!324 = !DILocalVariable(name: "count", scope: !27, file: !7, line: 129, type: !26)
!325 = !DILocation(line: 129, column: 6, scope: !27)
!326 = !DILocation(line: 130, column: 7, scope: !327)
!327 = distinct !DILexicalBlock(scope: !27, file: !7, line: 130, column: 6)
!328 = !DILocation(line: 130, column: 6, scope: !27)
!329 = !DILocation(line: 131, column: 3, scope: !327)
!330 = !DILocation(line: 132, column: 12, scope: !27)
!331 = !DILocation(line: 132, column: 5, scope: !27)
!332 = !DILocation(line: 133, column: 5, scope: !27)
!333 = !DILocation(line: 133, column: 19, scope: !334)
!334 = !DILexicalBlockFile(scope: !27, file: !7, discriminator: 1)
!335 = !DILocation(line: 133, column: 50, scope: !334)
!336 = !DILocation(line: 133, column: 13, scope: !334)
!337 = !DILocation(line: 133, column: 5, scope: !334)
!338 = !DILocation(line: 138, column: 17, scope: !339)
!339 = distinct !DILexicalBlock(scope: !340, file: !7, line: 138, column: 13)
!340 = distinct !DILexicalBlock(scope: !27, file: !7, line: 133, column: 63)
!341 = !DILocation(line: 138, column: 13, scope: !339)
!342 = !DILocation(line: 138, column: 25, scope: !339)
!343 = !DILocation(line: 138, column: 42, scope: !344)
!344 = !DILexicalBlockFile(scope: !339, file: !7, discriminator: 1)
!345 = !DILocation(line: 138, column: 38, scope: !344)
!346 = !DILocation(line: 138, column: 51, scope: !344)
!347 = !DILocation(line: 138, column: 31, scope: !344)
!348 = !DILocation(line: 138, column: 61, scope: !344)
!349 = !DILocation(line: 138, column: 72, scope: !350)
!350 = !DILexicalBlockFile(scope: !339, file: !7, discriminator: 2)
!351 = !DILocation(line: 138, column: 65, scope: !350)
!352 = !DILocation(line: 138, column: 13, scope: !350)
!353 = !DILocation(line: 139, column: 9, scope: !339)
!354 = !DILocation(line: 139, column: 4, scope: !339)
!355 = !DILocation(line: 133, column: 5, scope: !356)
!356 = !DILexicalBlockFile(scope: !27, file: !7, discriminator: 2)
!357 = !DILocation(line: 142, column: 9, scope: !358)
!358 = distinct !DILexicalBlock(scope: !27, file: !7, line: 142, column: 9)
!359 = !DILocation(line: 142, column: 15, scope: !358)
!360 = !DILocation(line: 142, column: 9, scope: !27)
!361 = !DILocation(line: 143, column: 14, scope: !358)
!362 = !DILocation(line: 143, column: 8, scope: !358)
!363 = !DILocation(line: 144, column: 12, scope: !27)
!364 = !DILocation(line: 144, column: 5, scope: !27)
!365 = !DILocation(line: 145, column: 1, scope: !27)
!366 = !DILocalVariable(name: "ip_address", arg: 1, scope: !30, file: !7, line: 147, type: !10)
!367 = !DILocation(line: 147, column: 34, scope: !30)
!368 = !DILocalVariable(name: "tmp", scope: !30, file: !7, line: 149, type: !200)
!369 = !DILocation(line: 149, column: 21, scope: !30)
!370 = !DILocalVariable(name: "count", scope: !30, file: !7, line: 150, type: !26)
!371 = !DILocation(line: 150, column: 8, scope: !30)
!372 = !DILocation(line: 152, column: 10, scope: !373)
!373 = distinct !DILexicalBlock(scope: !30, file: !7, line: 152, column: 8)
!374 = !DILocation(line: 152, column: 8, scope: !30)
!375 = !DILocation(line: 153, column: 7, scope: !373)
!376 = !DILocation(line: 155, column: 11, scope: !30)
!377 = !DILocation(line: 155, column: 4, scope: !30)
!378 = !DILocation(line: 156, column: 4, scope: !30)
!379 = !DILocation(line: 156, column: 19, scope: !380)
!380 = !DILexicalBlockFile(scope: !30, file: !7, discriminator: 1)
!381 = !DILocation(line: 156, column: 50, scope: !380)
!382 = !DILocation(line: 156, column: 12, scope: !380)
!383 = !DILocation(line: 156, column: 4, scope: !380)
!384 = !DILocation(line: 158, column: 15, scope: !385)
!385 = distinct !DILexicalBlock(scope: !386, file: !7, line: 158, column: 11)
!386 = distinct !DILexicalBlock(scope: !30, file: !7, line: 157, column: 4)
!387 = !DILocation(line: 158, column: 11, scope: !385)
!388 = !DILocation(line: 158, column: 23, scope: !385)
!389 = !DILocation(line: 158, column: 40, scope: !390)
!390 = !DILexicalBlockFile(scope: !385, file: !7, discriminator: 1)
!391 = !DILocation(line: 158, column: 36, scope: !390)
!392 = !DILocation(line: 158, column: 49, scope: !390)
!393 = !DILocation(line: 158, column: 29, scope: !390)
!394 = !DILocation(line: 158, column: 11, scope: !390)
!395 = !DILocation(line: 159, column: 15, scope: !385)
!396 = !DILocation(line: 159, column: 10, scope: !385)
!397 = !DILocation(line: 156, column: 4, scope: !398)
!398 = !DILexicalBlockFile(scope: !30, file: !7, discriminator: 2)
!399 = !DILocation(line: 162, column: 11, scope: !30)
!400 = !DILocation(line: 162, column: 4, scope: !30)
!401 = !DILocation(line: 163, column: 1, scope: !30)
!402 = !DILocalVariable(name: "pid", arg: 1, scope: !31, file: !7, line: 176, type: !26)
!403 = !DILocation(line: 176, column: 31, scope: !31)
!404 = !DILocalVariable(name: "current", scope: !31, file: !7, line: 178, type: !200)
!405 = !DILocation(line: 178, column: 22, scope: !31)
!406 = !DILocalVariable(name: "index", scope: !31, file: !7, line: 179, type: !26)
!407 = !DILocation(line: 179, column: 9, scope: !31)
!408 = !DILocation(line: 181, column: 11, scope: !409)
!409 = distinct !DILexicalBlock(scope: !31, file: !7, line: 181, column: 9)
!410 = !DILocation(line: 181, column: 9, scope: !31)
!411 = !DILocation(line: 182, column: 8, scope: !409)
!412 = !DILocation(line: 184, column: 12, scope: !31)
!413 = !DILocation(line: 184, column: 5, scope: !31)
!414 = !DILocation(line: 186, column: 5, scope: !31)
!415 = !DILocation(line: 186, column: 20, scope: !416)
!416 = !DILexicalBlockFile(scope: !31, file: !7, discriminator: 1)
!417 = !DILocation(line: 186, column: 59, scope: !416)
!418 = !DILocation(line: 186, column: 13, scope: !416)
!419 = !DILocation(line: 186, column: 5, scope: !416)
!420 = !DILocation(line: 189, column: 21, scope: !421)
!421 = distinct !DILexicalBlock(scope: !422, file: !7, line: 189, column: 13)
!422 = distinct !DILexicalBlock(scope: !31, file: !7, line: 187, column: 5)
!423 = !DILocation(line: 189, column: 31, scope: !421)
!424 = !DILocation(line: 189, column: 28, scope: !421)
!425 = !DILocation(line: 189, column: 13, scope: !422)
!426 = !DILocation(line: 191, column: 18, scope: !427)
!427 = distinct !DILexicalBlock(scope: !421, file: !7, line: 190, column: 8)
!428 = !DILocation(line: 191, column: 29, scope: !427)
!429 = !DILocation(line: 191, column: 35, scope: !427)
!430 = !DILocation(line: 191, column: 12, scope: !427)
!431 = !DILocation(line: 192, column: 12, scope: !427)
!432 = !DILocation(line: 193, column: 20, scope: !427)
!433 = !DILocation(line: 193, column: 59, scope: !427)
!434 = !DILocation(line: 193, column: 12, scope: !427)
!435 = !DILocation(line: 194, column: 8, scope: !427)
!436 = !DILocation(line: 195, column: 13, scope: !422)
!437 = !DILocation(line: 186, column: 5, scope: !438)
!438 = !DILexicalBlockFile(scope: !31, file: !7, discriminator: 2)
!439 = !DILocation(line: 197, column: 1, scope: !31)
