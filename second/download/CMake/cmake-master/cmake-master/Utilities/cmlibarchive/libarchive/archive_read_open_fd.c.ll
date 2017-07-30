; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_open_fd.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type opaque
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }
%struct.read_fd_data = type { i32, i64, i8, i8* }

@.str = private unnamed_addr constant [17 x i8] c"Can't stat fd %d\00", align 1
@.str.1 = private unnamed_addr constant [10 x i8] c"No memory\00", align 1
@.str.2 = private unnamed_addr constant [20 x i8] c"Error reading fd %d\00", align 1
@.str.3 = private unnamed_addr constant [14 x i8] c"Error seeking\00", align 1
@.str.4 = private unnamed_addr constant [44 x i8] c"A file descriptor(%d) is not seekable(PIPE)\00", align 1
@.str.5 = private unnamed_addr constant [39 x i8] c"Error seeking in a file descriptor(%d)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_open_fd(%struct.archive* %a, i32 %fd, i64 %block_size) #0 !dbg !18 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %fd.addr = alloca i32, align 4
  %block_size.addr = alloca i64, align 8
  %st = alloca %struct.stat, align 8
  %mine = alloca %struct.read_fd_data*, align 8
  %b = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !49, metadata !50), !dbg !51
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !52, metadata !50), !dbg !53
  store i64 %block_size, i64* %block_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %block_size.addr, metadata !54, metadata !50), !dbg !55
  call void @llvm.dbg.declare(metadata %struct.stat* %st, metadata !56, metadata !50), !dbg !95
  call void @llvm.dbg.declare(metadata %struct.read_fd_data** %mine, metadata !96, metadata !50), !dbg !97
  call void @llvm.dbg.declare(metadata i8** %b, metadata !98, metadata !50), !dbg !99
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !100
  call void @archive_clear_error(%struct.archive* %0), !dbg !101
  %1 = load i32, i32* %fd.addr, align 4, !dbg !102
  %call = call i32 @fstat(i32 %1, %struct.stat* %st) #5, !dbg !104
  %cmp = icmp ne i32 %call, 0, !dbg !105
  br i1 %cmp, label %if.then, label %if.end, !dbg !106

if.then:                                          ; preds = %entry
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !107
  %call1 = call i32* @__errno_location() #1, !dbg !109
  %3 = load i32, i32* %call1, align 4, !dbg !109
  %4 = load i32, i32* %fd.addr, align 4, !dbg !110
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %2, i32 %3, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str, i32 0, i32 0), i32 %4), !dbg !111
  store i32 -30, i32* %retval, align 4, !dbg !113
  br label %return, !dbg !113

if.end:                                           ; preds = %entry
  %call2 = call noalias i8* @calloc(i64 1, i64 32) #5, !dbg !114
  %5 = bitcast i8* %call2 to %struct.read_fd_data*, !dbg !115
  store %struct.read_fd_data* %5, %struct.read_fd_data** %mine, align 8, !dbg !116
  %6 = load i64, i64* %block_size.addr, align 8, !dbg !117
  %call3 = call noalias i8* @malloc(i64 %6) #5, !dbg !118
  store i8* %call3, i8** %b, align 8, !dbg !119
  %7 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !120
  %cmp4 = icmp eq %struct.read_fd_data* %7, null, !dbg !122
  br i1 %cmp4, label %if.then6, label %lor.lhs.false, !dbg !123

lor.lhs.false:                                    ; preds = %if.end
  %8 = load i8*, i8** %b, align 8, !dbg !124
  %cmp5 = icmp eq i8* %8, null, !dbg !126
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !127

if.then6:                                         ; preds = %lor.lhs.false, %if.end
  %9 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !128
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %9, i32 12, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.1, i32 0, i32 0)), !dbg !130
  %10 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !131
  %11 = bitcast %struct.read_fd_data* %10 to i8*, !dbg !131
  call void @free(i8* %11) #5, !dbg !132
  %12 = load i8*, i8** %b, align 8, !dbg !133
  call void @free(i8* %12) #5, !dbg !134
  store i32 -30, i32* %retval, align 4, !dbg !135
  br label %return, !dbg !135

if.end7:                                          ; preds = %lor.lhs.false
  %13 = load i64, i64* %block_size.addr, align 8, !dbg !136
  %14 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !137
  %block_size8 = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %14, i32 0, i32 1, !dbg !138
  store i64 %13, i64* %block_size8, align 8, !dbg !139
  %15 = load i8*, i8** %b, align 8, !dbg !140
  %16 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !141
  %buffer = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %16, i32 0, i32 3, !dbg !142
  store i8* %15, i8** %buffer, align 8, !dbg !143
  %17 = load i32, i32* %fd.addr, align 4, !dbg !144
  %18 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !145
  %fd9 = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %18, i32 0, i32 0, !dbg !146
  store i32 %17, i32* %fd9, align 8, !dbg !147
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !148
  %19 = load i32, i32* %st_mode, align 8, !dbg !148
  %and = and i32 %19, 61440, !dbg !148
  %cmp10 = icmp eq i32 %and, 32768, !dbg !148
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !150

if.then11:                                        ; preds = %if.end7
  %20 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !151
  %st_dev = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 0, !dbg !153
  %21 = load i64, i64* %st_dev, align 8, !dbg !153
  %st_ino = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 1, !dbg !154
  %22 = load i64, i64* %st_ino, align 8, !dbg !154
  call void @archive_read_extract_set_skip_file(%struct.archive* %20, i64 %21, i64 %22), !dbg !155
  %23 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !156
  %use_lseek = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %23, i32 0, i32 2, !dbg !157
  store i8 1, i8* %use_lseek, align 8, !dbg !158
  br label %if.end12, !dbg !159

if.end12:                                         ; preds = %if.then11, %if.end7
  %24 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !160
  %call13 = call i32 @archive_read_set_read_callback(%struct.archive* %24, i64 (%struct.archive*, i8*, i8**)* @file_read), !dbg !161
  %25 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !162
  %call14 = call i32 @archive_read_set_skip_callback(%struct.archive* %25, i64 (%struct.archive*, i8*, i64)* @file_skip), !dbg !163
  %26 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !164
  %call15 = call i32 @archive_read_set_seek_callback(%struct.archive* %26, i64 (%struct.archive*, i8*, i64, i32)* @file_seek), !dbg !165
  %27 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !166
  %call16 = call i32 @archive_read_set_close_callback(%struct.archive* %27, i32 (%struct.archive*, i8*)* @file_close), !dbg !167
  %28 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !168
  %29 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !169
  %30 = bitcast %struct.read_fd_data* %29 to i8*, !dbg !169
  %call17 = call i32 @archive_read_set_callback_data(%struct.archive* %28, i8* %30), !dbg !170
  %31 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !171
  %call18 = call i32 @archive_read_open1(%struct.archive* %31), !dbg !172
  store i32 %call18, i32* %retval, align 4, !dbg !173
  br label %return, !dbg !173

return:                                           ; preds = %if.end12, %if.then6, %if.then
  %32 = load i32, i32* %retval, align 4, !dbg !174
  ret i32 %32, !dbg !174
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @archive_clear_error(%struct.archive*) #2

; Function Attrs: nounwind
declare i32 @fstat(i32, %struct.stat*) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #4

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: nounwind
declare void @free(i8*) #3

declare void @archive_read_extract_set_skip_file(%struct.archive*, i64, i64) #2

declare i32 @archive_read_set_read_callback(%struct.archive*, i64 (%struct.archive*, i8*, i8**)*) #2

; Function Attrs: nounwind uwtable
define internal i64 @file_read(%struct.archive* %a, i8* %client_data, i8** %buff) #0 !dbg !24 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %buff.addr = alloca i8**, align 8
  %mine = alloca %struct.read_fd_data*, align 8
  %bytes_read = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !175, metadata !50), !dbg !176
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !177, metadata !50), !dbg !178
  store i8** %buff, i8*** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buff.addr, metadata !179, metadata !50), !dbg !180
  call void @llvm.dbg.declare(metadata %struct.read_fd_data** %mine, metadata !181, metadata !50), !dbg !182
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !183
  %1 = bitcast i8* %0 to %struct.read_fd_data*, !dbg !184
  store %struct.read_fd_data* %1, %struct.read_fd_data** %mine, align 8, !dbg !182
  call void @llvm.dbg.declare(metadata i64* %bytes_read, metadata !185, metadata !50), !dbg !186
  %2 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !187
  %buffer = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %2, i32 0, i32 3, !dbg !188
  %3 = load i8*, i8** %buffer, align 8, !dbg !188
  %4 = load i8**, i8*** %buff.addr, align 8, !dbg !189
  store i8* %3, i8** %4, align 8, !dbg !190
  br label %for.cond, !dbg !191

for.cond:                                         ; preds = %if.then4, %entry
  %5 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !192
  %fd = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %5, i32 0, i32 0, !dbg !196
  %6 = load i32, i32* %fd, align 8, !dbg !196
  %7 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !197
  %buffer1 = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %7, i32 0, i32 3, !dbg !198
  %8 = load i8*, i8** %buffer1, align 8, !dbg !198
  %9 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !199
  %block_size = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %9, i32 0, i32 1, !dbg !200
  %10 = load i64, i64* %block_size, align 8, !dbg !200
  %call = call i64 @read(i32 %6, i8* %8, i64 %10), !dbg !201
  store i64 %call, i64* %bytes_read, align 8, !dbg !202
  %11 = load i64, i64* %bytes_read, align 8, !dbg !203
  %cmp = icmp slt i64 %11, 0, !dbg !205
  br i1 %cmp, label %if.then, label %if.end7, !dbg !206

if.then:                                          ; preds = %for.cond
  %call2 = call i32* @__errno_location() #1, !dbg !207
  %12 = load i32, i32* %call2, align 4, !dbg !207
  %cmp3 = icmp eq i32 %12, 4, !dbg !210
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !211

if.then4:                                         ; preds = %if.then
  br label %for.cond, !dbg !212

if.end:                                           ; preds = %if.then
  %13 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !213
  %call5 = call i32* @__errno_location() #1, !dbg !214
  %14 = load i32, i32* %call5, align 4, !dbg !214
  %15 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !215
  %fd6 = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %15, i32 0, i32 0, !dbg !216
  %16 = load i32, i32* %fd6, align 8, !dbg !216
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %13, i32 %14, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.2, i32 0, i32 0), i32 %16), !dbg !217
  br label %if.end7, !dbg !219

if.end7:                                          ; preds = %if.end, %for.cond
  %17 = load i64, i64* %bytes_read, align 8, !dbg !220
  ret i64 %17, !dbg !221
}

declare i32 @archive_read_set_skip_callback(%struct.archive*, i64 (%struct.archive*, i8*, i64)*) #2

; Function Attrs: nounwind uwtable
define internal i64 @file_skip(%struct.archive* %a, i8* %client_data, i64 %request) #0 !dbg !35 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %request.addr = alloca i64, align 8
  %mine = alloca %struct.read_fd_data*, align 8
  %skip = alloca i64, align 8
  %old_offset = alloca i64, align 8
  %new_offset = alloca i64, align 8
  %skip_bits = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !222, metadata !50), !dbg !223
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !224, metadata !50), !dbg !225
  store i64 %request, i64* %request.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %request.addr, metadata !226, metadata !50), !dbg !227
  call void @llvm.dbg.declare(metadata %struct.read_fd_data** %mine, metadata !228, metadata !50), !dbg !229
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !230
  %1 = bitcast i8* %0 to %struct.read_fd_data*, !dbg !231
  store %struct.read_fd_data* %1, %struct.read_fd_data** %mine, align 8, !dbg !229
  call void @llvm.dbg.declare(metadata i64* %skip, metadata !232, metadata !50), !dbg !233
  %2 = load i64, i64* %request.addr, align 8, !dbg !234
  store i64 %2, i64* %skip, align 8, !dbg !233
  call void @llvm.dbg.declare(metadata i64* %old_offset, metadata !235, metadata !50), !dbg !236
  call void @llvm.dbg.declare(metadata i64* %new_offset, metadata !237, metadata !50), !dbg !238
  call void @llvm.dbg.declare(metadata i32* %skip_bits, metadata !239, metadata !50), !dbg !240
  store i32 63, i32* %skip_bits, align 4, !dbg !240
  %3 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !241
  %use_lseek = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %3, i32 0, i32 2, !dbg !243
  %4 = load i8, i8* %use_lseek, align 8, !dbg !243
  %tobool = icmp ne i8 %4, 0, !dbg !241
  br i1 %tobool, label %if.end, label %if.then, !dbg !244

if.then:                                          ; preds = %entry
  store i64 0, i64* %retval, align 8, !dbg !245
  br label %return, !dbg !245

if.end:                                           ; preds = %entry
  %5 = load i64, i64* %request.addr, align 8, !dbg !246
  %6 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !247
  %block_size = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %6, i32 0, i32 1, !dbg !248
  %7 = load i64, i64* %block_size, align 8, !dbg !248
  %div = udiv i64 %5, %7, !dbg !249
  %8 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !250
  %block_size1 = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %8, i32 0, i32 1, !dbg !251
  %9 = load i64, i64* %block_size1, align 8, !dbg !251
  %mul = mul i64 %div, %9, !dbg !252
  store i64 %mul, i64* %request.addr, align 8, !dbg !253
  %10 = load i64, i64* %request.addr, align 8, !dbg !254
  %cmp = icmp eq i64 %10, 0, !dbg !256
  br i1 %cmp, label %if.then2, label %if.end3, !dbg !257

if.then2:                                         ; preds = %if.end
  store i64 0, i64* %retval, align 8, !dbg !258
  br label %return, !dbg !258

if.end3:                                          ; preds = %if.end
  %11 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !259
  %fd = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %11, i32 0, i32 0, !dbg !261
  %12 = load i32, i32* %fd, align 8, !dbg !261
  %call = call i64 @lseek(i32 %12, i64 0, i32 1) #5, !dbg !262
  store i64 %call, i64* %old_offset, align 8, !dbg !263
  %cmp4 = icmp sge i64 %call, 0, !dbg !264
  br i1 %cmp4, label %land.lhs.true, label %if.end9, !dbg !265

land.lhs.true:                                    ; preds = %if.end3
  %13 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !266
  %fd5 = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %13, i32 0, i32 0, !dbg !267
  %14 = load i32, i32* %fd5, align 8, !dbg !267
  %15 = load i64, i64* %skip, align 8, !dbg !268
  %call6 = call i64 @lseek(i32 %14, i64 %15, i32 1) #5, !dbg !269
  store i64 %call6, i64* %new_offset, align 8, !dbg !270
  %cmp7 = icmp sge i64 %call6, 0, !dbg !271
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !272

if.then8:                                         ; preds = %land.lhs.true
  %16 = load i64, i64* %new_offset, align 8, !dbg !274
  %17 = load i64, i64* %old_offset, align 8, !dbg !275
  %sub = sub nsw i64 %16, %17, !dbg !276
  store i64 %sub, i64* %retval, align 8, !dbg !277
  br label %return, !dbg !277

if.end9:                                          ; preds = %land.lhs.true, %if.end3
  %18 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !278
  %use_lseek10 = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %18, i32 0, i32 2, !dbg !279
  store i8 0, i8* %use_lseek10, align 8, !dbg !280
  %call11 = call i32* @__errno_location() #1, !dbg !281
  %19 = load i32, i32* %call11, align 4, !dbg !281
  %cmp12 = icmp eq i32 %19, 29, !dbg !283
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !284

if.then13:                                        ; preds = %if.end9
  store i64 0, i64* %retval, align 8, !dbg !285
  br label %return, !dbg !285

if.end14:                                         ; preds = %if.end9
  %20 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !286
  %call15 = call i32* @__errno_location() #1, !dbg !287
  %21 = load i32, i32* %call15, align 4, !dbg !287
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %20, i32 %21, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.3, i32 0, i32 0)), !dbg !288
  store i64 -1, i64* %retval, align 8, !dbg !289
  br label %return, !dbg !289

return:                                           ; preds = %if.end14, %if.then13, %if.then8, %if.then2, %if.then
  %22 = load i64, i64* %retval, align 8, !dbg !290
  ret i64 %22, !dbg !290
}

declare i32 @archive_read_set_seek_callback(%struct.archive*, i64 (%struct.archive*, i8*, i64, i32)*) #2

; Function Attrs: nounwind uwtable
define internal i64 @file_seek(%struct.archive* %a, i8* %client_data, i64 %request, i32 %whence) #0 !dbg !40 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %request.addr = alloca i64, align 8
  %whence.addr = alloca i32, align 4
  %mine = alloca %struct.read_fd_data*, align 8
  %r = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !291, metadata !50), !dbg !292
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !293, metadata !50), !dbg !294
  store i64 %request, i64* %request.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %request.addr, metadata !295, metadata !50), !dbg !296
  store i32 %whence, i32* %whence.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %whence.addr, metadata !297, metadata !50), !dbg !298
  call void @llvm.dbg.declare(metadata %struct.read_fd_data** %mine, metadata !299, metadata !50), !dbg !300
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !301
  %1 = bitcast i8* %0 to %struct.read_fd_data*, !dbg !302
  store %struct.read_fd_data* %1, %struct.read_fd_data** %mine, align 8, !dbg !300
  call void @llvm.dbg.declare(metadata i64* %r, metadata !303, metadata !50), !dbg !304
  %2 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !305
  %fd = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %2, i32 0, i32 0, !dbg !306
  %3 = load i32, i32* %fd, align 8, !dbg !306
  %4 = load i64, i64* %request.addr, align 8, !dbg !307
  %5 = load i32, i32* %whence.addr, align 4, !dbg !308
  %call = call i64 @lseek(i32 %3, i64 %4, i32 %5) #5, !dbg !309
  store i64 %call, i64* %r, align 8, !dbg !310
  %6 = load i64, i64* %r, align 8, !dbg !311
  %cmp = icmp sge i64 %6, 0, !dbg !313
  br i1 %cmp, label %if.then, label %if.end, !dbg !314

if.then:                                          ; preds = %entry
  %7 = load i64, i64* %r, align 8, !dbg !315
  store i64 %7, i64* %retval, align 8, !dbg !316
  br label %return, !dbg !316

if.end:                                           ; preds = %entry
  %call1 = call i32* @__errno_location() #1, !dbg !317
  %8 = load i32, i32* %call1, align 4, !dbg !317
  %cmp2 = icmp eq i32 %8, 29, !dbg !319
  br i1 %cmp2, label %if.then3, label %if.else, !dbg !320

if.then3:                                         ; preds = %if.end
  %9 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !321
  %call4 = call i32* @__errno_location() #1, !dbg !323
  %10 = load i32, i32* %call4, align 4, !dbg !323
  %11 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !324
  %fd5 = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %11, i32 0, i32 0, !dbg !325
  %12 = load i32, i32* %fd5, align 8, !dbg !325
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %9, i32 %10, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.4, i32 0, i32 0), i32 %12), !dbg !326
  store i64 -25, i64* %retval, align 8, !dbg !328
  br label %return, !dbg !328

if.else:                                          ; preds = %if.end
  %13 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !329
  %call6 = call i32* @__errno_location() #1, !dbg !331
  %14 = load i32, i32* %call6, align 4, !dbg !331
  %15 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !332
  %fd7 = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %15, i32 0, i32 0, !dbg !333
  %16 = load i32, i32* %fd7, align 8, !dbg !333
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %13, i32 %14, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.5, i32 0, i32 0), i32 %16), !dbg !334
  store i64 -30, i64* %retval, align 8, !dbg !336
  br label %return, !dbg !336

return:                                           ; preds = %if.else, %if.then3, %if.then
  %17 = load i64, i64* %retval, align 8, !dbg !337
  ret i64 %17, !dbg !337
}

declare i32 @archive_read_set_close_callback(%struct.archive*, i32 (%struct.archive*, i8*)*) #2

; Function Attrs: nounwind uwtable
define internal i32 @file_close(%struct.archive* %a, i8* %client_data) #0 !dbg !43 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %mine = alloca %struct.read_fd_data*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !338, metadata !50), !dbg !339
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !340, metadata !50), !dbg !341
  call void @llvm.dbg.declare(metadata %struct.read_fd_data** %mine, metadata !342, metadata !50), !dbg !343
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !344
  %1 = bitcast i8* %0 to %struct.read_fd_data*, !dbg !345
  store %struct.read_fd_data* %1, %struct.read_fd_data** %mine, align 8, !dbg !343
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !346
  %3 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !347
  %buffer = getelementptr inbounds %struct.read_fd_data, %struct.read_fd_data* %3, i32 0, i32 3, !dbg !348
  %4 = load i8*, i8** %buffer, align 8, !dbg !348
  call void @free(i8* %4) #5, !dbg !349
  %5 = load %struct.read_fd_data*, %struct.read_fd_data** %mine, align 8, !dbg !350
  %6 = bitcast %struct.read_fd_data* %5 to i8*, !dbg !350
  call void @free(i8* %6) #5, !dbg !351
  ret i32 0, !dbg !352
}

declare i32 @archive_read_set_callback_data(%struct.archive*, i8*) #2

declare i32 @archive_read_open1(%struct.archive*) #2

declare i64 @read(i32, i8*, i64) #2

; Function Attrs: nounwind
declare i64 @lseek(i32, i64, i32) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!46, !47}
!llvm.ident = !{!48}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !17)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_open_fd.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !16}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "read_fd_data", file: !1, line: 53, size: 256, align: 64, elements: !6)
!6 = !{!7, !9, !13, !15}
!7 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !5, file: !1, line: 54, baseType: !8, size: 32, align: 32)
!8 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!9 = !DIDerivedType(tag: DW_TAG_member, name: "block_size", scope: !5, file: !1, line: 55, baseType: !10, size: 64, align: 64, offset: 64)
!10 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !11, line: 62, baseType: !12)
!11 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!12 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!13 = !DIDerivedType(tag: DW_TAG_member, name: "use_lseek", scope: !5, file: !1, line: 56, baseType: !14, size: 8, align: 8, offset: 128)
!14 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !5, file: !1, line: 57, baseType: !16, size: 64, align: 64, offset: 192)
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!17 = !{!18, !24, !35, !40, !43}
!18 = distinct !DISubprogram(name: "archive_read_open_fd", scope: !1, file: !1, line: 66, type: !19, isLocal: false, isDefinition: true, scopeLine: 67, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!19 = !DISubroutineType(types: !20)
!20 = !{!8, !21, !8, !10}
!21 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !22, size: 64, align: 64)
!22 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !23, line: 179, flags: DIFlagFwdDecl)
!23 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!24 = distinct !DISubprogram(name: "file_read", scope: !1, file: !1, line: 113, type: !25, isLocal: true, isDefinition: true, scopeLine: 114, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!25 = !DISubroutineType(types: !26)
!26 = !{!27, !21, !16, !32}
!27 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !28, line: 109, baseType: !29)
!28 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!29 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !30, line: 172, baseType: !31)
!30 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!31 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!32 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !33, size: 64, align: 64)
!33 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !34, size: 64, align: 64)
!34 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!35 = distinct !DISubprogram(name: "file_skip", scope: !1, file: !1, line: 132, type: !36, isLocal: true, isDefinition: true, scopeLine: 133, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!36 = !DISubroutineType(types: !37)
!37 = !{!38, !21, !16, !38}
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !39, line: 40, baseType: !31)
!39 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!40 = distinct !DISubprogram(name: "file_seek", scope: !1, file: !1, line: 179, type: !41, isLocal: true, isDefinition: true, scopeLine: 180, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!41 = !DISubroutineType(types: !42)
!42 = !{!38, !21, !16, !38, !8}
!43 = distinct !DISubprogram(name: "file_close", scope: !1, file: !1, line: 203, type: !44, isLocal: true, isDefinition: true, scopeLine: 204, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!44 = !DISubroutineType(types: !45)
!45 = !{!8, !21, !16}
!46 = !{i32 2, !"Dwarf Version", i32 4}
!47 = !{i32 2, !"Debug Info Version", i32 3}
!48 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!49 = !DILocalVariable(name: "a", arg: 1, scope: !18, file: !1, line: 66, type: !21)
!50 = !DIExpression()
!51 = !DILocation(line: 66, column: 38, scope: !18)
!52 = !DILocalVariable(name: "fd", arg: 2, scope: !18, file: !1, line: 66, type: !8)
!53 = !DILocation(line: 66, column: 45, scope: !18)
!54 = !DILocalVariable(name: "block_size", arg: 3, scope: !18, file: !1, line: 66, type: !10)
!55 = !DILocation(line: 66, column: 56, scope: !18)
!56 = !DILocalVariable(name: "st", scope: !18, file: !1, line: 68, type: !57)
!57 = !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !58, line: 46, size: 1152, align: 64, elements: !59)
!58 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!59 = !{!60, !62, !64, !66, !69, !71, !73, !74, !75, !77, !79, !81, !89, !90, !91}
!60 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !57, file: !58, line: 48, baseType: !61, size: 64, align: 64)
!61 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !30, line: 124, baseType: !12)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !57, file: !58, line: 53, baseType: !63, size: 64, align: 64, offset: 64)
!63 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino_t", file: !30, line: 127, baseType: !12)
!64 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !57, file: !58, line: 61, baseType: !65, size: 64, align: 64, offset: 128)
!65 = !DIDerivedType(tag: DW_TAG_typedef, name: "__nlink_t", file: !30, line: 130, baseType: !12)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !57, file: !58, line: 62, baseType: !67, size: 32, align: 32, offset: 192)
!67 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !30, line: 129, baseType: !68)
!68 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !57, file: !58, line: 64, baseType: !70, size: 32, align: 32, offset: 224)
!70 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !30, line: 125, baseType: !68)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !57, file: !58, line: 65, baseType: !72, size: 32, align: 32, offset: 256)
!72 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !30, line: 126, baseType: !68)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "__pad0", scope: !57, file: !58, line: 67, baseType: !8, size: 32, align: 32, offset: 288)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !57, file: !58, line: 69, baseType: !61, size: 64, align: 64, offset: 320)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !57, file: !58, line: 74, baseType: !76, size: 64, align: 64, offset: 384)
!76 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !30, line: 131, baseType: !31)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !57, file: !58, line: 78, baseType: !78, size: 64, align: 64, offset: 448)
!78 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blksize_t", file: !30, line: 153, baseType: !31)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !57, file: !58, line: 80, baseType: !80, size: 64, align: 64, offset: 512)
!80 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blkcnt_t", file: !30, line: 158, baseType: !31)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !57, file: !58, line: 91, baseType: !82, size: 128, align: 64, offset: 576)
!82 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !83, line: 120, size: 128, align: 64, elements: !84)
!83 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!84 = !{!85, !87}
!85 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !82, file: !83, line: 122, baseType: !86, size: 64, align: 64)
!86 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !30, line: 139, baseType: !31)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !82, file: !83, line: 123, baseType: !88, size: 64, align: 64, offset: 64)
!88 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !30, line: 175, baseType: !31)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !57, file: !58, line: 92, baseType: !82, size: 128, align: 64, offset: 704)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !57, file: !58, line: 93, baseType: !82, size: 128, align: 64, offset: 832)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !57, file: !58, line: 106, baseType: !92, size: 192, align: 64, offset: 960)
!92 = !DICompositeType(tag: DW_TAG_array_type, baseType: !88, size: 192, align: 64, elements: !93)
!93 = !{!94}
!94 = !DISubrange(count: 3)
!95 = !DILocation(line: 68, column: 14, scope: !18)
!96 = !DILocalVariable(name: "mine", scope: !18, file: !1, line: 69, type: !4)
!97 = !DILocation(line: 69, column: 23, scope: !18)
!98 = !DILocalVariable(name: "b", scope: !18, file: !1, line: 70, type: !16)
!99 = !DILocation(line: 70, column: 8, scope: !18)
!100 = !DILocation(line: 72, column: 22, scope: !18)
!101 = !DILocation(line: 72, column: 2, scope: !18)
!102 = !DILocation(line: 73, column: 12, scope: !103)
!103 = distinct !DILexicalBlock(scope: !18, file: !1, line: 73, column: 6)
!104 = !DILocation(line: 73, column: 6, scope: !103)
!105 = !DILocation(line: 73, column: 21, scope: !103)
!106 = !DILocation(line: 73, column: 6, scope: !18)
!107 = !DILocation(line: 74, column: 21, scope: !108)
!108 = distinct !DILexicalBlock(scope: !103, file: !1, line: 73, column: 27)
!109 = !DILocation(line: 74, column: 24, scope: !108)
!110 = !DILocation(line: 74, column: 51, scope: !108)
!111 = !DILocation(line: 74, column: 3, scope: !112)
!112 = !DILexicalBlockFile(scope: !108, file: !1, discriminator: 1)
!113 = !DILocation(line: 75, column: 3, scope: !108)
!114 = !DILocation(line: 78, column: 32, scope: !18)
!115 = !DILocation(line: 78, column: 9, scope: !18)
!116 = !DILocation(line: 78, column: 7, scope: !18)
!117 = !DILocation(line: 79, column: 13, scope: !18)
!118 = !DILocation(line: 79, column: 6, scope: !18)
!119 = !DILocation(line: 79, column: 4, scope: !18)
!120 = !DILocation(line: 80, column: 6, scope: !121)
!121 = distinct !DILexicalBlock(scope: !18, file: !1, line: 80, column: 6)
!122 = !DILocation(line: 80, column: 11, scope: !121)
!123 = !DILocation(line: 80, column: 19, scope: !121)
!124 = !DILocation(line: 80, column: 22, scope: !125)
!125 = !DILexicalBlockFile(scope: !121, file: !1, discriminator: 1)
!126 = !DILocation(line: 80, column: 24, scope: !125)
!127 = !DILocation(line: 80, column: 6, scope: !125)
!128 = !DILocation(line: 81, column: 21, scope: !129)
!129 = distinct !DILexicalBlock(scope: !121, file: !1, line: 80, column: 33)
!130 = !DILocation(line: 81, column: 3, scope: !129)
!131 = !DILocation(line: 82, column: 8, scope: !129)
!132 = !DILocation(line: 82, column: 3, scope: !129)
!133 = !DILocation(line: 83, column: 8, scope: !129)
!134 = !DILocation(line: 83, column: 3, scope: !129)
!135 = !DILocation(line: 84, column: 3, scope: !129)
!136 = !DILocation(line: 86, column: 21, scope: !18)
!137 = !DILocation(line: 86, column: 2, scope: !18)
!138 = !DILocation(line: 86, column: 8, scope: !18)
!139 = !DILocation(line: 86, column: 19, scope: !18)
!140 = !DILocation(line: 87, column: 17, scope: !18)
!141 = !DILocation(line: 87, column: 2, scope: !18)
!142 = !DILocation(line: 87, column: 8, scope: !18)
!143 = !DILocation(line: 87, column: 15, scope: !18)
!144 = !DILocation(line: 88, column: 13, scope: !18)
!145 = !DILocation(line: 88, column: 2, scope: !18)
!146 = !DILocation(line: 88, column: 8, scope: !18)
!147 = !DILocation(line: 88, column: 11, scope: !18)
!148 = !DILocation(line: 96, column: 6, scope: !149)
!149 = distinct !DILexicalBlock(scope: !18, file: !1, line: 96, column: 6)
!150 = !DILocation(line: 96, column: 6, scope: !18)
!151 = !DILocation(line: 97, column: 38, scope: !152)
!152 = distinct !DILexicalBlock(scope: !149, file: !1, line: 96, column: 27)
!153 = !DILocation(line: 97, column: 44, scope: !152)
!154 = !DILocation(line: 97, column: 55, scope: !152)
!155 = !DILocation(line: 97, column: 3, scope: !152)
!156 = !DILocation(line: 98, column: 3, scope: !152)
!157 = !DILocation(line: 98, column: 9, scope: !152)
!158 = !DILocation(line: 98, column: 19, scope: !152)
!159 = !DILocation(line: 99, column: 2, scope: !152)
!160 = !DILocation(line: 104, column: 33, scope: !18)
!161 = !DILocation(line: 104, column: 2, scope: !18)
!162 = !DILocation(line: 105, column: 33, scope: !18)
!163 = !DILocation(line: 105, column: 2, scope: !18)
!164 = !DILocation(line: 106, column: 33, scope: !18)
!165 = !DILocation(line: 106, column: 2, scope: !18)
!166 = !DILocation(line: 107, column: 34, scope: !18)
!167 = !DILocation(line: 107, column: 2, scope: !18)
!168 = !DILocation(line: 108, column: 33, scope: !18)
!169 = !DILocation(line: 108, column: 36, scope: !18)
!170 = !DILocation(line: 108, column: 2, scope: !18)
!171 = !DILocation(line: 109, column: 29, scope: !18)
!172 = !DILocation(line: 109, column: 10, scope: !18)
!173 = !DILocation(line: 109, column: 2, scope: !18)
!174 = !DILocation(line: 110, column: 1, scope: !18)
!175 = !DILocalVariable(name: "a", arg: 1, scope: !24, file: !1, line: 113, type: !21)
!176 = !DILocation(line: 113, column: 27, scope: !24)
!177 = !DILocalVariable(name: "client_data", arg: 2, scope: !24, file: !1, line: 113, type: !16)
!178 = !DILocation(line: 113, column: 36, scope: !24)
!179 = !DILocalVariable(name: "buff", arg: 3, scope: !24, file: !1, line: 113, type: !32)
!180 = !DILocation(line: 113, column: 62, scope: !24)
!181 = !DILocalVariable(name: "mine", scope: !24, file: !1, line: 115, type: !4)
!182 = !DILocation(line: 115, column: 23, scope: !24)
!183 = !DILocation(line: 115, column: 53, scope: !24)
!184 = !DILocation(line: 115, column: 30, scope: !24)
!185 = !DILocalVariable(name: "bytes_read", scope: !24, file: !1, line: 116, type: !27)
!186 = !DILocation(line: 116, column: 10, scope: !24)
!187 = !DILocation(line: 118, column: 10, scope: !24)
!188 = !DILocation(line: 118, column: 16, scope: !24)
!189 = !DILocation(line: 118, column: 3, scope: !24)
!190 = !DILocation(line: 118, column: 8, scope: !24)
!191 = !DILocation(line: 119, column: 2, scope: !24)
!192 = !DILocation(line: 120, column: 21, scope: !193)
!193 = distinct !DILexicalBlock(scope: !194, file: !1, line: 119, column: 11)
!194 = distinct !DILexicalBlock(scope: !195, file: !1, line: 119, column: 2)
!195 = distinct !DILexicalBlock(scope: !24, file: !1, line: 119, column: 2)
!196 = !DILocation(line: 120, column: 27, scope: !193)
!197 = !DILocation(line: 120, column: 31, scope: !193)
!198 = !DILocation(line: 120, column: 37, scope: !193)
!199 = !DILocation(line: 120, column: 45, scope: !193)
!200 = !DILocation(line: 120, column: 51, scope: !193)
!201 = !DILocation(line: 120, column: 16, scope: !193)
!202 = !DILocation(line: 120, column: 14, scope: !193)
!203 = !DILocation(line: 121, column: 7, scope: !204)
!204 = distinct !DILexicalBlock(scope: !193, file: !1, line: 121, column: 7)
!205 = !DILocation(line: 121, column: 18, scope: !204)
!206 = !DILocation(line: 121, column: 7, scope: !193)
!207 = !DILocation(line: 122, column: 8, scope: !208)
!208 = distinct !DILexicalBlock(scope: !209, file: !1, line: 122, column: 8)
!209 = distinct !DILexicalBlock(scope: !204, file: !1, line: 121, column: 23)
!210 = !DILocation(line: 122, column: 14, scope: !208)
!211 = !DILocation(line: 122, column: 8, scope: !209)
!212 = !DILocation(line: 123, column: 5, scope: !208)
!213 = !DILocation(line: 124, column: 22, scope: !209)
!214 = !DILocation(line: 124, column: 25, scope: !209)
!215 = !DILocation(line: 125, column: 8, scope: !209)
!216 = !DILocation(line: 125, column: 14, scope: !209)
!217 = !DILocation(line: 124, column: 4, scope: !218)
!218 = !DILexicalBlockFile(scope: !209, file: !1, discriminator: 1)
!219 = !DILocation(line: 126, column: 3, scope: !209)
!220 = !DILocation(line: 127, column: 11, scope: !193)
!221 = !DILocation(line: 127, column: 3, scope: !193)
!222 = !DILocalVariable(name: "a", arg: 1, scope: !35, file: !1, line: 132, type: !21)
!223 = !DILocation(line: 132, column: 27, scope: !35)
!224 = !DILocalVariable(name: "client_data", arg: 2, scope: !35, file: !1, line: 132, type: !16)
!225 = !DILocation(line: 132, column: 36, scope: !35)
!226 = !DILocalVariable(name: "request", arg: 3, scope: !35, file: !1, line: 132, type: !38)
!227 = !DILocation(line: 132, column: 57, scope: !35)
!228 = !DILocalVariable(name: "mine", scope: !35, file: !1, line: 134, type: !4)
!229 = !DILocation(line: 134, column: 23, scope: !35)
!230 = !DILocation(line: 134, column: 53, scope: !35)
!231 = !DILocation(line: 134, column: 30, scope: !35)
!232 = !DILocalVariable(name: "skip", scope: !35, file: !1, line: 135, type: !38)
!233 = !DILocation(line: 135, column: 10, scope: !35)
!234 = !DILocation(line: 135, column: 17, scope: !35)
!235 = !DILocalVariable(name: "old_offset", scope: !35, file: !1, line: 136, type: !38)
!236 = !DILocation(line: 136, column: 10, scope: !35)
!237 = !DILocalVariable(name: "new_offset", scope: !35, file: !1, line: 136, type: !38)
!238 = !DILocation(line: 136, column: 22, scope: !35)
!239 = !DILocalVariable(name: "skip_bits", scope: !35, file: !1, line: 137, type: !8)
!240 = !DILocation(line: 137, column: 6, scope: !35)
!241 = !DILocation(line: 139, column: 7, scope: !242)
!242 = distinct !DILexicalBlock(scope: !35, file: !1, line: 139, column: 6)
!243 = !DILocation(line: 139, column: 13, scope: !242)
!244 = !DILocation(line: 139, column: 6, scope: !35)
!245 = !DILocation(line: 140, column: 3, scope: !242)
!246 = !DILocation(line: 151, column: 13, scope: !35)
!247 = !DILocation(line: 151, column: 23, scope: !35)
!248 = !DILocation(line: 151, column: 29, scope: !35)
!249 = !DILocation(line: 151, column: 21, scope: !35)
!250 = !DILocation(line: 151, column: 43, scope: !35)
!251 = !DILocation(line: 151, column: 49, scope: !35)
!252 = !DILocation(line: 151, column: 41, scope: !35)
!253 = !DILocation(line: 151, column: 10, scope: !35)
!254 = !DILocation(line: 152, column: 6, scope: !255)
!255 = distinct !DILexicalBlock(scope: !35, file: !1, line: 152, column: 6)
!256 = !DILocation(line: 152, column: 14, scope: !255)
!257 = !DILocation(line: 152, column: 6, scope: !35)
!258 = !DILocation(line: 153, column: 3, scope: !255)
!259 = !DILocation(line: 155, column: 27, scope: !260)
!260 = distinct !DILexicalBlock(scope: !35, file: !1, line: 155, column: 6)
!261 = !DILocation(line: 155, column: 33, scope: !260)
!262 = !DILocation(line: 155, column: 21, scope: !260)
!263 = !DILocation(line: 155, column: 19, scope: !260)
!264 = !DILocation(line: 155, column: 51, scope: !260)
!265 = !DILocation(line: 155, column: 57, scope: !260)
!266 = !DILocation(line: 156, column: 27, scope: !260)
!267 = !DILocation(line: 156, column: 33, scope: !260)
!268 = !DILocation(line: 156, column: 37, scope: !260)
!269 = !DILocation(line: 156, column: 21, scope: !260)
!270 = !DILocation(line: 156, column: 19, scope: !260)
!271 = !DILocation(line: 156, column: 54, scope: !260)
!272 = !DILocation(line: 155, column: 6, scope: !273)
!273 = !DILexicalBlockFile(scope: !35, file: !1, discriminator: 1)
!274 = !DILocation(line: 157, column: 11, scope: !260)
!275 = !DILocation(line: 157, column: 24, scope: !260)
!276 = !DILocation(line: 157, column: 22, scope: !260)
!277 = !DILocation(line: 157, column: 3, scope: !260)
!278 = !DILocation(line: 160, column: 2, scope: !35)
!279 = !DILocation(line: 160, column: 8, scope: !35)
!280 = !DILocation(line: 160, column: 18, scope: !35)
!281 = !DILocation(line: 163, column: 6, scope: !282)
!282 = distinct !DILexicalBlock(scope: !35, file: !1, line: 163, column: 6)
!283 = !DILocation(line: 163, column: 12, scope: !282)
!284 = !DILocation(line: 163, column: 6, scope: !35)
!285 = !DILocation(line: 164, column: 3, scope: !282)
!286 = !DILocation(line: 171, column: 20, scope: !35)
!287 = !DILocation(line: 171, column: 23, scope: !35)
!288 = !DILocation(line: 171, column: 2, scope: !273)
!289 = !DILocation(line: 172, column: 2, scope: !35)
!290 = !DILocation(line: 173, column: 1, scope: !35)
!291 = !DILocalVariable(name: "a", arg: 1, scope: !40, file: !1, line: 179, type: !21)
!292 = !DILocation(line: 179, column: 27, scope: !40)
!293 = !DILocalVariable(name: "client_data", arg: 2, scope: !40, file: !1, line: 179, type: !16)
!294 = !DILocation(line: 179, column: 36, scope: !40)
!295 = !DILocalVariable(name: "request", arg: 3, scope: !40, file: !1, line: 179, type: !38)
!296 = !DILocation(line: 179, column: 57, scope: !40)
!297 = !DILocalVariable(name: "whence", arg: 4, scope: !40, file: !1, line: 179, type: !8)
!298 = !DILocation(line: 179, column: 70, scope: !40)
!299 = !DILocalVariable(name: "mine", scope: !40, file: !1, line: 181, type: !4)
!300 = !DILocation(line: 181, column: 23, scope: !40)
!301 = !DILocation(line: 181, column: 53, scope: !40)
!302 = !DILocation(line: 181, column: 30, scope: !40)
!303 = !DILocalVariable(name: "r", scope: !40, file: !1, line: 182, type: !38)
!304 = !DILocation(line: 182, column: 10, scope: !40)
!305 = !DILocation(line: 186, column: 12, scope: !40)
!306 = !DILocation(line: 186, column: 18, scope: !40)
!307 = !DILocation(line: 186, column: 22, scope: !40)
!308 = !DILocation(line: 186, column: 31, scope: !40)
!309 = !DILocation(line: 186, column: 6, scope: !40)
!310 = !DILocation(line: 186, column: 4, scope: !40)
!311 = !DILocation(line: 187, column: 6, scope: !312)
!312 = distinct !DILexicalBlock(scope: !40, file: !1, line: 187, column: 6)
!313 = !DILocation(line: 187, column: 8, scope: !312)
!314 = !DILocation(line: 187, column: 6, scope: !40)
!315 = !DILocation(line: 188, column: 10, scope: !312)
!316 = !DILocation(line: 188, column: 3, scope: !312)
!317 = !DILocation(line: 190, column: 6, scope: !318)
!318 = distinct !DILexicalBlock(scope: !40, file: !1, line: 190, column: 6)
!319 = !DILocation(line: 190, column: 12, scope: !318)
!320 = !DILocation(line: 190, column: 6, scope: !40)
!321 = !DILocation(line: 191, column: 21, scope: !322)
!322 = distinct !DILexicalBlock(scope: !318, file: !1, line: 190, column: 23)
!323 = !DILocation(line: 191, column: 24, scope: !322)
!324 = !DILocation(line: 192, column: 54, scope: !322)
!325 = !DILocation(line: 192, column: 60, scope: !322)
!326 = !DILocation(line: 191, column: 3, scope: !327)
!327 = !DILexicalBlockFile(scope: !322, file: !1, discriminator: 1)
!328 = !DILocation(line: 193, column: 3, scope: !322)
!329 = !DILocation(line: 196, column: 21, scope: !330)
!330 = distinct !DILexicalBlock(scope: !318, file: !1, line: 194, column: 9)
!331 = !DILocation(line: 196, column: 24, scope: !330)
!332 = !DILocation(line: 197, column: 49, scope: !330)
!333 = !DILocation(line: 197, column: 55, scope: !330)
!334 = !DILocation(line: 196, column: 3, scope: !335)
!335 = !DILexicalBlockFile(scope: !330, file: !1, discriminator: 1)
!336 = !DILocation(line: 198, column: 3, scope: !330)
!337 = !DILocation(line: 200, column: 1, scope: !40)
!338 = !DILocalVariable(name: "a", arg: 1, scope: !43, file: !1, line: 203, type: !21)
!339 = !DILocation(line: 203, column: 28, scope: !43)
!340 = !DILocalVariable(name: "client_data", arg: 2, scope: !43, file: !1, line: 203, type: !16)
!341 = !DILocation(line: 203, column: 37, scope: !43)
!342 = !DILocalVariable(name: "mine", scope: !43, file: !1, line: 205, type: !4)
!343 = !DILocation(line: 205, column: 23, scope: !43)
!344 = !DILocation(line: 205, column: 53, scope: !43)
!345 = !DILocation(line: 205, column: 30, scope: !43)
!346 = !DILocation(line: 207, column: 8, scope: !43)
!347 = !DILocation(line: 208, column: 7, scope: !43)
!348 = !DILocation(line: 208, column: 13, scope: !43)
!349 = !DILocation(line: 208, column: 2, scope: !43)
!350 = !DILocation(line: 209, column: 7, scope: !43)
!351 = !DILocation(line: 209, column: 2, scope: !43)
!352 = !DILocation(line: 210, column: 2, scope: !43)
