; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_open_file.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type opaque
%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }
%struct.read_FILE_data = type { %struct._IO_FILE*, i64, i8*, i8 }

@.str = private unnamed_addr constant [10 x i8] c"No memory\00", align 1
@.str.1 = private unnamed_addr constant [19 x i8] c"Error reading file\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_open_FILE(%struct.archive* %a, %struct._IO_FILE* %f) #0 !dbg !77 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %f.addr = alloca %struct._IO_FILE*, align 8
  %st = alloca %struct.stat, align 8
  %mine = alloca %struct.read_FILE_data*, align 8
  %block_size = alloca i64, align 8
  %b = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !103, metadata !104), !dbg !105
  store %struct._IO_FILE* %f, %struct._IO_FILE** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %f.addr, metadata !106, metadata !104), !dbg !107
  call void @llvm.dbg.declare(metadata %struct.stat* %st, metadata !108, metadata !104), !dbg !146
  call void @llvm.dbg.declare(metadata %struct.read_FILE_data** %mine, metadata !147, metadata !104), !dbg !148
  call void @llvm.dbg.declare(metadata i64* %block_size, metadata !149, metadata !104), !dbg !150
  store i64 131072, i64* %block_size, align 8, !dbg !150
  call void @llvm.dbg.declare(metadata i8** %b, metadata !151, metadata !104), !dbg !152
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !153
  call void @archive_clear_error(%struct.archive* %0), !dbg !154
  %call = call noalias i8* @malloc(i64 32) #5, !dbg !155
  %1 = bitcast i8* %call to %struct.read_FILE_data*, !dbg !156
  store %struct.read_FILE_data* %1, %struct.read_FILE_data** %mine, align 8, !dbg !157
  %2 = load i64, i64* %block_size, align 8, !dbg !158
  %call1 = call noalias i8* @malloc(i64 %2) #5, !dbg !159
  store i8* %call1, i8** %b, align 8, !dbg !160
  %3 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !161
  %cmp = icmp eq %struct.read_FILE_data* %3, null, !dbg !163
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !164

lor.lhs.false:                                    ; preds = %entry
  %4 = load i8*, i8** %b, align 8, !dbg !165
  %cmp2 = icmp eq i8* %4, null, !dbg !167
  br i1 %cmp2, label %if.then, label %if.end, !dbg !168

if.then:                                          ; preds = %lor.lhs.false, %entry
  %5 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !169
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %5, i32 12, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)), !dbg !171
  %6 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !172
  %7 = bitcast %struct.read_FILE_data* %6 to i8*, !dbg !172
  call void @free(i8* %7) #5, !dbg !173
  %8 = load i8*, i8** %b, align 8, !dbg !174
  call void @free(i8* %8) #5, !dbg !175
  store i32 -30, i32* %retval, align 4, !dbg !176
  br label %return, !dbg !176

if.end:                                           ; preds = %lor.lhs.false
  %9 = load i64, i64* %block_size, align 8, !dbg !177
  %10 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !178
  %block_size3 = getelementptr inbounds %struct.read_FILE_data, %struct.read_FILE_data* %10, i32 0, i32 1, !dbg !179
  store i64 %9, i64* %block_size3, align 8, !dbg !180
  %11 = load i8*, i8** %b, align 8, !dbg !181
  %12 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !182
  %buffer = getelementptr inbounds %struct.read_FILE_data, %struct.read_FILE_data* %12, i32 0, i32 2, !dbg !183
  store i8* %11, i8** %buffer, align 8, !dbg !184
  %13 = load %struct._IO_FILE*, %struct._IO_FILE** %f.addr, align 8, !dbg !185
  %14 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !186
  %f4 = getelementptr inbounds %struct.read_FILE_data, %struct.read_FILE_data* %14, i32 0, i32 0, !dbg !187
  store %struct._IO_FILE* %13, %struct._IO_FILE** %f4, align 8, !dbg !188
  %15 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !189
  %f5 = getelementptr inbounds %struct.read_FILE_data, %struct.read_FILE_data* %15, i32 0, i32 0, !dbg !191
  %16 = load %struct._IO_FILE*, %struct._IO_FILE** %f5, align 8, !dbg !191
  %call6 = call i32 @fileno(%struct._IO_FILE* %16) #5, !dbg !192
  %call7 = call i32 @fstat(i32 %call6, %struct.stat* %st) #5, !dbg !193
  %cmp8 = icmp eq i32 %call7, 0, !dbg !195
  br i1 %cmp8, label %land.lhs.true, label %if.else, !dbg !196

land.lhs.true:                                    ; preds = %if.end
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !197
  %17 = load i32, i32* %st_mode, align 8, !dbg !197
  %and = and i32 %17, 61440, !dbg !197
  %cmp9 = icmp eq i32 %and, 32768, !dbg !197
  br i1 %cmp9, label %if.then10, label %if.else, !dbg !199

if.then10:                                        ; preds = %land.lhs.true
  %18 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !200
  %st_dev = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 0, !dbg !202
  %19 = load i64, i64* %st_dev, align 8, !dbg !202
  %st_ino = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 1, !dbg !203
  %20 = load i64, i64* %st_ino, align 8, !dbg !203
  call void @archive_read_extract_set_skip_file(%struct.archive* %18, i64 %19, i64 %20), !dbg !204
  %21 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !205
  %can_skip = getelementptr inbounds %struct.read_FILE_data, %struct.read_FILE_data* %21, i32 0, i32 3, !dbg !206
  store i8 1, i8* %can_skip, align 8, !dbg !207
  br label %if.end12, !dbg !208

if.else:                                          ; preds = %land.lhs.true, %if.end
  %22 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !209
  %can_skip11 = getelementptr inbounds %struct.read_FILE_data, %struct.read_FILE_data* %22, i32 0, i32 3, !dbg !210
  store i8 0, i8* %can_skip11, align 8, !dbg !211
  br label %if.end12

if.end12:                                         ; preds = %if.else, %if.then10
  %23 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !212
  %call13 = call i32 @archive_read_set_read_callback(%struct.archive* %23, i64 (%struct.archive*, i8*, i8**)* @file_read), !dbg !213
  %24 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !214
  %call14 = call i32 @archive_read_set_skip_callback(%struct.archive* %24, i64 (%struct.archive*, i8*, i64)* @file_skip), !dbg !215
  %25 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !216
  %call15 = call i32 @archive_read_set_close_callback(%struct.archive* %25, i32 (%struct.archive*, i8*)* @file_close), !dbg !217
  %26 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !218
  %27 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !219
  %28 = bitcast %struct.read_FILE_data* %27 to i8*, !dbg !219
  %call16 = call i32 @archive_read_set_callback_data(%struct.archive* %26, i8* %28), !dbg !220
  %29 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !221
  %call17 = call i32 @archive_read_open1(%struct.archive* %29), !dbg !222
  store i32 %call17, i32* %retval, align 4, !dbg !223
  br label %return, !dbg !223

return:                                           ; preds = %if.end12, %if.then
  %30 = load i32, i32* %retval, align 4, !dbg !224
  ret i32 %30, !dbg !224
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @archive_clear_error(%struct.archive*) #2

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind
declare i32 @fstat(i32, %struct.stat*) #3

; Function Attrs: nounwind
declare i32 @fileno(%struct._IO_FILE*) #3

declare void @archive_read_extract_set_skip_file(%struct.archive*, i64, i64) #2

declare i32 @archive_read_set_read_callback(%struct.archive*, i64 (%struct.archive*, i8*, i8**)*) #2

; Function Attrs: nounwind uwtable
define internal i64 @file_read(%struct.archive* %a, i8* %client_data, i8** %buff) #0 !dbg !83 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %buff.addr = alloca i8**, align 8
  %mine = alloca %struct.read_FILE_data*, align 8
  %bytes_read = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !225, metadata !104), !dbg !226
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !227, metadata !104), !dbg !228
  store i8** %buff, i8*** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buff.addr, metadata !229, metadata !104), !dbg !230
  call void @llvm.dbg.declare(metadata %struct.read_FILE_data** %mine, metadata !231, metadata !104), !dbg !232
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !233
  %1 = bitcast i8* %0 to %struct.read_FILE_data*, !dbg !234
  store %struct.read_FILE_data* %1, %struct.read_FILE_data** %mine, align 8, !dbg !232
  call void @llvm.dbg.declare(metadata i64* %bytes_read, metadata !235, metadata !104), !dbg !236
  %2 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !237
  %buffer = getelementptr inbounds %struct.read_FILE_data, %struct.read_FILE_data* %2, i32 0, i32 2, !dbg !238
  %3 = load i8*, i8** %buffer, align 8, !dbg !238
  %4 = load i8**, i8*** %buff.addr, align 8, !dbg !239
  store i8* %3, i8** %4, align 8, !dbg !240
  %5 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !241
  %buffer1 = getelementptr inbounds %struct.read_FILE_data, %struct.read_FILE_data* %5, i32 0, i32 2, !dbg !242
  %6 = load i8*, i8** %buffer1, align 8, !dbg !242
  %7 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !243
  %block_size = getelementptr inbounds %struct.read_FILE_data, %struct.read_FILE_data* %7, i32 0, i32 1, !dbg !244
  %8 = load i64, i64* %block_size, align 8, !dbg !244
  %9 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !245
  %f = getelementptr inbounds %struct.read_FILE_data, %struct.read_FILE_data* %9, i32 0, i32 0, !dbg !246
  %10 = load %struct._IO_FILE*, %struct._IO_FILE** %f, align 8, !dbg !246
  %call = call i64 @fread(i8* %6, i64 1, i64 %8, %struct._IO_FILE* %10), !dbg !247
  store i64 %call, i64* %bytes_read, align 8, !dbg !248
  %11 = load i64, i64* %bytes_read, align 8, !dbg !249
  %12 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !251
  %block_size2 = getelementptr inbounds %struct.read_FILE_data, %struct.read_FILE_data* %12, i32 0, i32 1, !dbg !252
  %13 = load i64, i64* %block_size2, align 8, !dbg !252
  %cmp = icmp ult i64 %11, %13, !dbg !253
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !254

land.lhs.true:                                    ; preds = %entry
  %14 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !255
  %f3 = getelementptr inbounds %struct.read_FILE_data, %struct.read_FILE_data* %14, i32 0, i32 0, !dbg !257
  %15 = load %struct._IO_FILE*, %struct._IO_FILE** %f3, align 8, !dbg !257
  %call4 = call i32 @ferror(%struct._IO_FILE* %15) #5, !dbg !258
  %tobool = icmp ne i32 %call4, 0, !dbg !258
  br i1 %tobool, label %if.then, label %if.end, !dbg !259

if.then:                                          ; preds = %land.lhs.true
  %16 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !260
  %call5 = call i32* @__errno_location() #1, !dbg !262
  %17 = load i32, i32* %call5, align 4, !dbg !262
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %16, i32 %17, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.1, i32 0, i32 0)), !dbg !263
  br label %if.end, !dbg !265

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  %18 = load i64, i64* %bytes_read, align 8, !dbg !266
  ret i64 %18, !dbg !267
}

declare i32 @archive_read_set_skip_callback(%struct.archive*, i64 (%struct.archive*, i8*, i64)*) #2

; Function Attrs: nounwind uwtable
define internal i64 @file_skip(%struct.archive* %a, i8* %client_data, i64 %request) #0 !dbg !92 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %request.addr = alloca i64, align 8
  %mine = alloca %struct.read_FILE_data*, align 8
  %skip = alloca i64, align 8
  %skip_bits = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !268, metadata !104), !dbg !269
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !270, metadata !104), !dbg !271
  store i64 %request, i64* %request.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %request.addr, metadata !272, metadata !104), !dbg !273
  call void @llvm.dbg.declare(metadata %struct.read_FILE_data** %mine, metadata !274, metadata !104), !dbg !275
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !276
  %1 = bitcast i8* %0 to %struct.read_FILE_data*, !dbg !277
  store %struct.read_FILE_data* %1, %struct.read_FILE_data** %mine, align 8, !dbg !275
  call void @llvm.dbg.declare(metadata i64* %skip, metadata !278, metadata !104), !dbg !279
  %2 = load i64, i64* %request.addr, align 8, !dbg !280
  store i64 %2, i64* %skip, align 8, !dbg !279
  call void @llvm.dbg.declare(metadata i32* %skip_bits, metadata !281, metadata !104), !dbg !282
  store i32 63, i32* %skip_bits, align 4, !dbg !282
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !283
  %4 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !284
  %can_skip = getelementptr inbounds %struct.read_FILE_data, %struct.read_FILE_data* %4, i32 0, i32 3, !dbg !286
  %5 = load i8, i8* %can_skip, align 8, !dbg !286
  %tobool = icmp ne i8 %5, 0, !dbg !284
  br i1 %tobool, label %if.end, label %if.then, !dbg !287

if.then:                                          ; preds = %entry
  store i64 0, i64* %retval, align 8, !dbg !288
  br label %return, !dbg !288

if.end:                                           ; preds = %entry
  %6 = load i64, i64* %request.addr, align 8, !dbg !289
  %cmp = icmp eq i64 %6, 0, !dbg !291
  br i1 %cmp, label %if.then1, label %if.end2, !dbg !292

if.then1:                                         ; preds = %if.end
  store i64 0, i64* %retval, align 8, !dbg !293
  br label %return, !dbg !293

if.end2:                                          ; preds = %if.end
  %7 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !294
  %f = getelementptr inbounds %struct.read_FILE_data, %struct.read_FILE_data* %7, i32 0, i32 0, !dbg !296
  %8 = load %struct._IO_FILE*, %struct._IO_FILE** %f, align 8, !dbg !296
  %9 = load i64, i64* %skip, align 8, !dbg !297
  %call = call i32 @fseeko(%struct._IO_FILE* %8, i64 %9, i32 1), !dbg !298
  %cmp3 = icmp ne i32 %call, 0, !dbg !299
  br i1 %cmp3, label %if.then4, label %if.end6, !dbg !300

if.then4:                                         ; preds = %if.end2
  %10 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !301
  %can_skip5 = getelementptr inbounds %struct.read_FILE_data, %struct.read_FILE_data* %10, i32 0, i32 3, !dbg !303
  store i8 0, i8* %can_skip5, align 8, !dbg !304
  store i64 0, i64* %retval, align 8, !dbg !305
  br label %return, !dbg !305

if.end6:                                          ; preds = %if.end2
  %11 = load i64, i64* %request.addr, align 8, !dbg !306
  store i64 %11, i64* %retval, align 8, !dbg !307
  br label %return, !dbg !307

return:                                           ; preds = %if.end6, %if.then4, %if.then1, %if.then
  %12 = load i64, i64* %retval, align 8, !dbg !308
  ret i64 %12, !dbg !308
}

declare i32 @archive_read_set_close_callback(%struct.archive*, i32 (%struct.archive*, i8*)*) #2

; Function Attrs: nounwind uwtable
define internal i32 @file_close(%struct.archive* %a, i8* %client_data) #0 !dbg !97 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %mine = alloca %struct.read_FILE_data*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !309, metadata !104), !dbg !310
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !311, metadata !104), !dbg !312
  call void @llvm.dbg.declare(metadata %struct.read_FILE_data** %mine, metadata !313, metadata !104), !dbg !314
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !315
  %1 = bitcast i8* %0 to %struct.read_FILE_data*, !dbg !316
  store %struct.read_FILE_data* %1, %struct.read_FILE_data** %mine, align 8, !dbg !314
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !317
  %3 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !318
  %buffer = getelementptr inbounds %struct.read_FILE_data, %struct.read_FILE_data* %3, i32 0, i32 2, !dbg !320
  %4 = load i8*, i8** %buffer, align 8, !dbg !320
  %cmp = icmp ne i8* %4, null, !dbg !321
  br i1 %cmp, label %if.then, label %if.end, !dbg !322

if.then:                                          ; preds = %entry
  %5 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !323
  %buffer1 = getelementptr inbounds %struct.read_FILE_data, %struct.read_FILE_data* %5, i32 0, i32 2, !dbg !324
  %6 = load i8*, i8** %buffer1, align 8, !dbg !324
  call void @free(i8* %6) #5, !dbg !325
  br label %if.end, !dbg !325

if.end:                                           ; preds = %if.then, %entry
  %7 = load %struct.read_FILE_data*, %struct.read_FILE_data** %mine, align 8, !dbg !326
  %8 = bitcast %struct.read_FILE_data* %7 to i8*, !dbg !326
  call void @free(i8* %8) #5, !dbg !327
  ret i32 0, !dbg !328
}

declare i32 @archive_read_set_callback_data(%struct.archive*, i8*) #2

declare i32 @archive_read_open1(%struct.archive*) #2

declare i64 @fread(i8*, i64, i64, %struct._IO_FILE*) #2

; Function Attrs: nounwind
declare i32 @ferror(%struct._IO_FILE*) #3

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #4

declare i32 @fseeko(%struct._IO_FILE*, i64, i32) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!100, !101}
!llvm.ident = !{!102}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !76)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_open_file.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !58, !74}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "read_FILE_data", file: !1, line: 53, size: 256, align: 64, elements: !6)
!6 = !{!7, !71, !72, !73}
!7 = !DIDerivedType(tag: DW_TAG_member, name: "f", scope: !5, file: !1, line: 54, baseType: !8, size: 64, align: 64)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!9 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !10, line: 48, baseType: !11)
!10 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !12, line: 245, size: 1728, align: 64, elements: !13)
!12 = !DIFile(filename: "/usr/include/libio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!13 = !{!14, !16, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29, !37, !38, !39, !40, !44, !46, !48, !52, !55, !57, !59, !60, !61, !62, !66, !67}
!14 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !11, file: !12, line: 246, baseType: !15, size: 32, align: 32)
!15 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!16 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !11, file: !12, line: 251, baseType: !17, size: 64, align: 64, offset: 64)
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !18, size: 64, align: 64)
!18 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!19 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !11, file: !12, line: 252, baseType: !17, size: 64, align: 64, offset: 128)
!20 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !11, file: !12, line: 253, baseType: !17, size: 64, align: 64, offset: 192)
!21 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !11, file: !12, line: 254, baseType: !17, size: 64, align: 64, offset: 256)
!22 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !11, file: !12, line: 255, baseType: !17, size: 64, align: 64, offset: 320)
!23 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !11, file: !12, line: 256, baseType: !17, size: 64, align: 64, offset: 384)
!24 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !11, file: !12, line: 257, baseType: !17, size: 64, align: 64, offset: 448)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !11, file: !12, line: 258, baseType: !17, size: 64, align: 64, offset: 512)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !11, file: !12, line: 260, baseType: !17, size: 64, align: 64, offset: 576)
!27 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !11, file: !12, line: 261, baseType: !17, size: 64, align: 64, offset: 640)
!28 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !11, file: !12, line: 262, baseType: !17, size: 64, align: 64, offset: 704)
!29 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !11, file: !12, line: 264, baseType: !30, size: 64, align: 64, offset: 768)
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!31 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !12, line: 160, size: 192, align: 64, elements: !32)
!32 = !{!33, !34, !36}
!33 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !31, file: !12, line: 161, baseType: !30, size: 64, align: 64)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !31, file: !12, line: 162, baseType: !35, size: 64, align: 64, offset: 64)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!36 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !31, file: !12, line: 166, baseType: !15, size: 32, align: 32, offset: 128)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !11, file: !12, line: 266, baseType: !35, size: 64, align: 64, offset: 832)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !11, file: !12, line: 268, baseType: !15, size: 32, align: 32, offset: 896)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !11, file: !12, line: 272, baseType: !15, size: 32, align: 32, offset: 928)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !11, file: !12, line: 274, baseType: !41, size: 64, align: 64, offset: 960)
!41 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !42, line: 131, baseType: !43)
!42 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!43 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !11, file: !12, line: 278, baseType: !45, size: 16, align: 16, offset: 1024)
!45 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !11, file: !12, line: 279, baseType: !47, size: 8, align: 8, offset: 1040)
!47 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !11, file: !12, line: 280, baseType: !49, size: 8, align: 8, offset: 1048)
!49 = !DICompositeType(tag: DW_TAG_array_type, baseType: !18, size: 8, align: 8, elements: !50)
!50 = !{!51}
!51 = !DISubrange(count: 1)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !11, file: !12, line: 284, baseType: !53, size: 64, align: 64, offset: 1088)
!53 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64, align: 64)
!54 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !12, line: 154, baseType: null)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !11, file: !12, line: 293, baseType: !56, size: 64, align: 64, offset: 1152)
!56 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !42, line: 132, baseType: !43)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !11, file: !12, line: 302, baseType: !58, size: 64, align: 64, offset: 1216)
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !11, file: !12, line: 303, baseType: !58, size: 64, align: 64, offset: 1280)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !11, file: !12, line: 304, baseType: !58, size: 64, align: 64, offset: 1344)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !11, file: !12, line: 305, baseType: !58, size: 64, align: 64, offset: 1408)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !11, file: !12, line: 306, baseType: !63, size: 64, align: 64, offset: 1472)
!63 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !64, line: 62, baseType: !65)
!64 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!65 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !11, file: !12, line: 308, baseType: !15, size: 32, align: 32, offset: 1536)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !11, file: !12, line: 310, baseType: !68, size: 160, align: 8, offset: 1568)
!68 = !DICompositeType(tag: DW_TAG_array_type, baseType: !18, size: 160, align: 8, elements: !69)
!69 = !{!70}
!70 = !DISubrange(count: 20)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "block_size", scope: !5, file: !1, line: 55, baseType: !63, size: 64, align: 64, offset: 64)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !5, file: !1, line: 56, baseType: !58, size: 64, align: 64, offset: 128)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "can_skip", scope: !5, file: !1, line: 57, baseType: !18, size: 8, align: 8, offset: 192)
!74 = !DIDerivedType(tag: DW_TAG_typedef, name: "off_t", file: !75, line: 74, baseType: !41)
!75 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!76 = !{!77, !83, !92, !97}
!77 = distinct !DISubprogram(name: "archive_read_open_FILE", scope: !1, file: !1, line: 65, type: !78, isLocal: false, isDefinition: true, scopeLine: 66, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!78 = !DISubroutineType(types: !79)
!79 = !{!15, !80, !8}
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!81 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !82, line: 179, flags: DIFlagFwdDecl)
!82 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!83 = distinct !DISubprogram(name: "file_read", scope: !1, file: !1, line: 109, type: !84, isLocal: true, isDefinition: true, scopeLine: 110, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!84 = !DISubroutineType(types: !85)
!85 = !{!86, !80, !58, !89}
!86 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !87, line: 109, baseType: !88)
!87 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!88 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !42, line: 172, baseType: !43)
!89 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !90, size: 64, align: 64)
!90 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !91, size: 64, align: 64)
!91 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!92 = distinct !DISubprogram(name: "file_skip", scope: !1, file: !1, line: 123, type: !93, isLocal: true, isDefinition: true, scopeLine: 124, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!93 = !DISubroutineType(types: !94)
!94 = !{!95, !80, !58, !95}
!95 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !96, line: 40, baseType: !43)
!96 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!97 = distinct !DISubprogram(name: "file_close", scope: !1, file: !1, line: 172, type: !98, isLocal: true, isDefinition: true, scopeLine: 173, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!98 = !DISubroutineType(types: !99)
!99 = !{!15, !80, !58}
!100 = !{i32 2, !"Dwarf Version", i32 4}
!101 = !{i32 2, !"Debug Info Version", i32 3}
!102 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!103 = !DILocalVariable(name: "a", arg: 1, scope: !77, file: !1, line: 65, type: !80)
!104 = !DIExpression()
!105 = !DILocation(line: 65, column: 40, scope: !77)
!106 = !DILocalVariable(name: "f", arg: 2, scope: !77, file: !1, line: 65, type: !8)
!107 = !DILocation(line: 65, column: 49, scope: !77)
!108 = !DILocalVariable(name: "st", scope: !77, file: !1, line: 67, type: !109)
!109 = !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !110, line: 46, size: 1152, align: 64, elements: !111)
!110 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!111 = !{!112, !114, !116, !118, !121, !123, !125, !126, !127, !128, !130, !132, !140, !141, !142}
!112 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !109, file: !110, line: 48, baseType: !113, size: 64, align: 64)
!113 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !42, line: 124, baseType: !65)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !109, file: !110, line: 53, baseType: !115, size: 64, align: 64, offset: 64)
!115 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino_t", file: !42, line: 127, baseType: !65)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !109, file: !110, line: 61, baseType: !117, size: 64, align: 64, offset: 128)
!117 = !DIDerivedType(tag: DW_TAG_typedef, name: "__nlink_t", file: !42, line: 130, baseType: !65)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !109, file: !110, line: 62, baseType: !119, size: 32, align: 32, offset: 192)
!119 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !42, line: 129, baseType: !120)
!120 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !109, file: !110, line: 64, baseType: !122, size: 32, align: 32, offset: 224)
!122 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !42, line: 125, baseType: !120)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !109, file: !110, line: 65, baseType: !124, size: 32, align: 32, offset: 256)
!124 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !42, line: 126, baseType: !120)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "__pad0", scope: !109, file: !110, line: 67, baseType: !15, size: 32, align: 32, offset: 288)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !109, file: !110, line: 69, baseType: !113, size: 64, align: 64, offset: 320)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !109, file: !110, line: 74, baseType: !41, size: 64, align: 64, offset: 384)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !109, file: !110, line: 78, baseType: !129, size: 64, align: 64, offset: 448)
!129 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blksize_t", file: !42, line: 153, baseType: !43)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !109, file: !110, line: 80, baseType: !131, size: 64, align: 64, offset: 512)
!131 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blkcnt_t", file: !42, line: 158, baseType: !43)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !109, file: !110, line: 91, baseType: !133, size: 128, align: 64, offset: 576)
!133 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !134, line: 120, size: 128, align: 64, elements: !135)
!134 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!135 = !{!136, !138}
!136 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !133, file: !134, line: 122, baseType: !137, size: 64, align: 64)
!137 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !42, line: 139, baseType: !43)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !133, file: !134, line: 123, baseType: !139, size: 64, align: 64, offset: 64)
!139 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !42, line: 175, baseType: !43)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !109, file: !110, line: 92, baseType: !133, size: 128, align: 64, offset: 704)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !109, file: !110, line: 93, baseType: !133, size: 128, align: 64, offset: 832)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !109, file: !110, line: 106, baseType: !143, size: 192, align: 64, offset: 960)
!143 = !DICompositeType(tag: DW_TAG_array_type, baseType: !139, size: 192, align: 64, elements: !144)
!144 = !{!145}
!145 = !DISubrange(count: 3)
!146 = !DILocation(line: 67, column: 14, scope: !77)
!147 = !DILocalVariable(name: "mine", scope: !77, file: !1, line: 68, type: !4)
!148 = !DILocation(line: 68, column: 25, scope: !77)
!149 = !DILocalVariable(name: "block_size", scope: !77, file: !1, line: 69, type: !63)
!150 = !DILocation(line: 69, column: 9, scope: !77)
!151 = !DILocalVariable(name: "b", scope: !77, file: !1, line: 70, type: !58)
!152 = !DILocation(line: 70, column: 8, scope: !77)
!153 = !DILocation(line: 72, column: 22, scope: !77)
!154 = !DILocation(line: 72, column: 2, scope: !77)
!155 = !DILocation(line: 73, column: 34, scope: !77)
!156 = !DILocation(line: 73, column: 9, scope: !77)
!157 = !DILocation(line: 73, column: 7, scope: !77)
!158 = !DILocation(line: 74, column: 13, scope: !77)
!159 = !DILocation(line: 74, column: 6, scope: !77)
!160 = !DILocation(line: 74, column: 4, scope: !77)
!161 = !DILocation(line: 75, column: 6, scope: !162)
!162 = distinct !DILexicalBlock(scope: !77, file: !1, line: 75, column: 6)
!163 = !DILocation(line: 75, column: 11, scope: !162)
!164 = !DILocation(line: 75, column: 19, scope: !162)
!165 = !DILocation(line: 75, column: 22, scope: !166)
!166 = !DILexicalBlockFile(scope: !162, file: !1, discriminator: 1)
!167 = !DILocation(line: 75, column: 24, scope: !166)
!168 = !DILocation(line: 75, column: 6, scope: !166)
!169 = !DILocation(line: 76, column: 21, scope: !170)
!170 = distinct !DILexicalBlock(scope: !162, file: !1, line: 75, column: 33)
!171 = !DILocation(line: 76, column: 3, scope: !170)
!172 = !DILocation(line: 77, column: 8, scope: !170)
!173 = !DILocation(line: 77, column: 3, scope: !170)
!174 = !DILocation(line: 78, column: 8, scope: !170)
!175 = !DILocation(line: 78, column: 3, scope: !170)
!176 = !DILocation(line: 79, column: 3, scope: !170)
!177 = !DILocation(line: 81, column: 21, scope: !77)
!178 = !DILocation(line: 81, column: 2, scope: !77)
!179 = !DILocation(line: 81, column: 8, scope: !77)
!180 = !DILocation(line: 81, column: 19, scope: !77)
!181 = !DILocation(line: 82, column: 17, scope: !77)
!182 = !DILocation(line: 82, column: 2, scope: !77)
!183 = !DILocation(line: 82, column: 8, scope: !77)
!184 = !DILocation(line: 82, column: 15, scope: !77)
!185 = !DILocation(line: 83, column: 12, scope: !77)
!186 = !DILocation(line: 83, column: 2, scope: !77)
!187 = !DILocation(line: 83, column: 8, scope: !77)
!188 = !DILocation(line: 83, column: 10, scope: !77)
!189 = !DILocation(line: 90, column: 19, scope: !190)
!190 = distinct !DILexicalBlock(scope: !77, file: !1, line: 90, column: 6)
!191 = !DILocation(line: 90, column: 25, scope: !190)
!192 = !DILocation(line: 90, column: 12, scope: !190)
!193 = !DILocation(line: 90, column: 6, scope: !194)
!194 = !DILexicalBlockFile(scope: !190, file: !1, discriminator: 2)
!195 = !DILocation(line: 90, column: 34, scope: !190)
!196 = !DILocation(line: 90, column: 39, scope: !190)
!197 = !DILocation(line: 90, column: 42, scope: !198)
!198 = !DILexicalBlockFile(scope: !190, file: !1, discriminator: 1)
!199 = !DILocation(line: 90, column: 6, scope: !198)
!200 = !DILocation(line: 91, column: 38, scope: !201)
!201 = distinct !DILexicalBlock(scope: !190, file: !1, line: 90, column: 63)
!202 = !DILocation(line: 91, column: 44, scope: !201)
!203 = !DILocation(line: 91, column: 55, scope: !201)
!204 = !DILocation(line: 91, column: 3, scope: !201)
!205 = !DILocation(line: 93, column: 3, scope: !201)
!206 = !DILocation(line: 93, column: 9, scope: !201)
!207 = !DILocation(line: 93, column: 18, scope: !201)
!208 = !DILocation(line: 94, column: 2, scope: !201)
!209 = !DILocation(line: 95, column: 3, scope: !190)
!210 = !DILocation(line: 95, column: 9, scope: !190)
!211 = !DILocation(line: 95, column: 18, scope: !190)
!212 = !DILocation(line: 101, column: 33, scope: !77)
!213 = !DILocation(line: 101, column: 2, scope: !77)
!214 = !DILocation(line: 102, column: 33, scope: !77)
!215 = !DILocation(line: 102, column: 2, scope: !77)
!216 = !DILocation(line: 103, column: 34, scope: !77)
!217 = !DILocation(line: 103, column: 2, scope: !77)
!218 = !DILocation(line: 104, column: 33, scope: !77)
!219 = !DILocation(line: 104, column: 36, scope: !77)
!220 = !DILocation(line: 104, column: 2, scope: !77)
!221 = !DILocation(line: 105, column: 29, scope: !77)
!222 = !DILocation(line: 105, column: 10, scope: !77)
!223 = !DILocation(line: 105, column: 2, scope: !77)
!224 = !DILocation(line: 106, column: 1, scope: !77)
!225 = !DILocalVariable(name: "a", arg: 1, scope: !83, file: !1, line: 109, type: !80)
!226 = !DILocation(line: 109, column: 27, scope: !83)
!227 = !DILocalVariable(name: "client_data", arg: 2, scope: !83, file: !1, line: 109, type: !58)
!228 = !DILocation(line: 109, column: 36, scope: !83)
!229 = !DILocalVariable(name: "buff", arg: 3, scope: !83, file: !1, line: 109, type: !89)
!230 = !DILocation(line: 109, column: 62, scope: !83)
!231 = !DILocalVariable(name: "mine", scope: !83, file: !1, line: 111, type: !4)
!232 = !DILocation(line: 111, column: 25, scope: !83)
!233 = !DILocation(line: 111, column: 57, scope: !83)
!234 = !DILocation(line: 111, column: 32, scope: !83)
!235 = !DILocalVariable(name: "bytes_read", scope: !83, file: !1, line: 112, type: !63)
!236 = !DILocation(line: 112, column: 9, scope: !83)
!237 = !DILocation(line: 114, column: 10, scope: !83)
!238 = !DILocation(line: 114, column: 16, scope: !83)
!239 = !DILocation(line: 114, column: 3, scope: !83)
!240 = !DILocation(line: 114, column: 8, scope: !83)
!241 = !DILocation(line: 115, column: 21, scope: !83)
!242 = !DILocation(line: 115, column: 27, scope: !83)
!243 = !DILocation(line: 115, column: 38, scope: !83)
!244 = !DILocation(line: 115, column: 44, scope: !83)
!245 = !DILocation(line: 115, column: 56, scope: !83)
!246 = !DILocation(line: 115, column: 62, scope: !83)
!247 = !DILocation(line: 115, column: 15, scope: !83)
!248 = !DILocation(line: 115, column: 13, scope: !83)
!249 = !DILocation(line: 116, column: 6, scope: !250)
!250 = distinct !DILexicalBlock(scope: !83, file: !1, line: 116, column: 6)
!251 = !DILocation(line: 116, column: 19, scope: !250)
!252 = !DILocation(line: 116, column: 25, scope: !250)
!253 = !DILocation(line: 116, column: 17, scope: !250)
!254 = !DILocation(line: 116, column: 36, scope: !250)
!255 = !DILocation(line: 116, column: 46, scope: !256)
!256 = !DILexicalBlockFile(scope: !250, file: !1, discriminator: 1)
!257 = !DILocation(line: 116, column: 52, scope: !256)
!258 = !DILocation(line: 116, column: 39, scope: !256)
!259 = !DILocation(line: 116, column: 6, scope: !256)
!260 = !DILocation(line: 117, column: 21, scope: !261)
!261 = distinct !DILexicalBlock(scope: !250, file: !1, line: 116, column: 56)
!262 = !DILocation(line: 117, column: 24, scope: !261)
!263 = !DILocation(line: 117, column: 3, scope: !264)
!264 = !DILexicalBlockFile(scope: !261, file: !1, discriminator: 1)
!265 = !DILocation(line: 118, column: 2, scope: !261)
!266 = !DILocation(line: 119, column: 10, scope: !83)
!267 = !DILocation(line: 119, column: 2, scope: !83)
!268 = !DILocalVariable(name: "a", arg: 1, scope: !92, file: !1, line: 123, type: !80)
!269 = !DILocation(line: 123, column: 27, scope: !92)
!270 = !DILocalVariable(name: "client_data", arg: 2, scope: !92, file: !1, line: 123, type: !58)
!271 = !DILocation(line: 123, column: 36, scope: !92)
!272 = !DILocalVariable(name: "request", arg: 3, scope: !92, file: !1, line: 123, type: !95)
!273 = !DILocation(line: 123, column: 57, scope: !92)
!274 = !DILocalVariable(name: "mine", scope: !92, file: !1, line: 125, type: !4)
!275 = !DILocation(line: 125, column: 25, scope: !92)
!276 = !DILocation(line: 125, column: 57, scope: !92)
!277 = !DILocation(line: 125, column: 32, scope: !92)
!278 = !DILocalVariable(name: "skip", scope: !92, file: !1, line: 127, type: !74)
!279 = !DILocation(line: 127, column: 8, scope: !92)
!280 = !DILocation(line: 127, column: 22, scope: !92)
!281 = !DILocalVariable(name: "skip_bits", scope: !92, file: !1, line: 133, type: !15)
!282 = !DILocation(line: 133, column: 6, scope: !92)
!283 = !DILocation(line: 135, column: 8, scope: !92)
!284 = !DILocation(line: 141, column: 7, scope: !285)
!285 = distinct !DILexicalBlock(scope: !92, file: !1, line: 141, column: 6)
!286 = !DILocation(line: 141, column: 13, scope: !285)
!287 = !DILocation(line: 141, column: 6, scope: !92)
!288 = !DILocation(line: 142, column: 3, scope: !285)
!289 = !DILocation(line: 143, column: 6, scope: !290)
!290 = distinct !DILexicalBlock(scope: !92, file: !1, line: 143, column: 6)
!291 = !DILocation(line: 143, column: 14, scope: !290)
!292 = !DILocation(line: 143, column: 6, scope: !92)
!293 = !DILocation(line: 144, column: 3, scope: !290)
!294 = !DILocation(line: 158, column: 13, scope: !295)
!295 = distinct !DILexicalBlock(scope: !92, file: !1, line: 158, column: 6)
!296 = !DILocation(line: 158, column: 19, scope: !295)
!297 = !DILocation(line: 158, column: 22, scope: !295)
!298 = !DILocation(line: 158, column: 6, scope: !295)
!299 = !DILocation(line: 158, column: 38, scope: !295)
!300 = !DILocation(line: 158, column: 6, scope: !92)
!301 = !DILocation(line: 165, column: 3, scope: !302)
!302 = distinct !DILexicalBlock(scope: !295, file: !1, line: 164, column: 2)
!303 = !DILocation(line: 165, column: 9, scope: !302)
!304 = !DILocation(line: 165, column: 18, scope: !302)
!305 = !DILocation(line: 166, column: 3, scope: !302)
!306 = !DILocation(line: 168, column: 10, scope: !92)
!307 = !DILocation(line: 168, column: 2, scope: !92)
!308 = !DILocation(line: 169, column: 1, scope: !92)
!309 = !DILocalVariable(name: "a", arg: 1, scope: !97, file: !1, line: 172, type: !80)
!310 = !DILocation(line: 172, column: 28, scope: !97)
!311 = !DILocalVariable(name: "client_data", arg: 2, scope: !97, file: !1, line: 172, type: !58)
!312 = !DILocation(line: 172, column: 37, scope: !97)
!313 = !DILocalVariable(name: "mine", scope: !97, file: !1, line: 174, type: !4)
!314 = !DILocation(line: 174, column: 25, scope: !97)
!315 = !DILocation(line: 174, column: 57, scope: !97)
!316 = !DILocation(line: 174, column: 32, scope: !97)
!317 = !DILocation(line: 176, column: 8, scope: !97)
!318 = !DILocation(line: 177, column: 6, scope: !319)
!319 = distinct !DILexicalBlock(scope: !97, file: !1, line: 177, column: 6)
!320 = !DILocation(line: 177, column: 12, scope: !319)
!321 = !DILocation(line: 177, column: 19, scope: !319)
!322 = !DILocation(line: 177, column: 6, scope: !97)
!323 = !DILocation(line: 178, column: 8, scope: !319)
!324 = !DILocation(line: 178, column: 14, scope: !319)
!325 = !DILocation(line: 178, column: 3, scope: !319)
!326 = !DILocation(line: 179, column: 7, scope: !97)
!327 = !DILocation(line: 179, column: 2, scope: !97)
!328 = !DILocation(line: 180, column: 2, scope: !97)
