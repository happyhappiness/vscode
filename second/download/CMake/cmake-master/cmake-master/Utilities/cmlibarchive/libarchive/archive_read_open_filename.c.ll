; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_open_filename.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.read_file_data = type { i32, i64, i8*, i32, i8, i32, %union.anon }
%union.anon = type { [1 x i32] }
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }

@.str = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.1 = private unnamed_addr constant [10 x i8] c"No memory\00", align 1
@.str.2 = private unnamed_addr constant [22 x i8] c"Can't allocate memory\00", align 1
@.str.3 = private unnamed_addr constant [69 x i8] c"Failed to convert a wide-character filename to a multi-byte filename\00", align 1
@.str.4 = private unnamed_addr constant [20 x i8] c"Failed to open '%s'\00", align 1
@.str.5 = private unnamed_addr constant [51 x i8] c"Unexpedted operation in archive_read_open_filename\00", align 1
@.str.6 = private unnamed_addr constant [16 x i8] c"Can't stat '%S'\00", align 1
@.str.7 = private unnamed_addr constant [16 x i8] c"Can't stat '%s'\00", align 1
@.str.8 = private unnamed_addr constant [20 x i8] c"Error reading stdin\00", align 1
@.str.9 = private unnamed_addr constant [19 x i8] c"Error reading '%s'\00", align 1
@.str.10 = private unnamed_addr constant [19 x i8] c"Error reading '%S'\00", align 1
@.str.11 = private unnamed_addr constant [23 x i8] c"Error seeking in stdin\00", align 1
@.str.12 = private unnamed_addr constant [22 x i8] c"Error seeking in '%s'\00", align 1
@.str.13 = private unnamed_addr constant [22 x i8] c"Error seeking in '%S'\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_open_file(%struct.archive* %a, i8* %filename, i64 %block_size) #0 !dbg !40 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %filename.addr = alloca i8*, align 8
  %block_size.addr = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !169, metadata !170), !dbg !171
  store i8* %filename, i8** %filename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filename.addr, metadata !172, metadata !170), !dbg !173
  store i64 %block_size, i64* %block_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %block_size.addr, metadata !174, metadata !170), !dbg !175
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !176
  %1 = load i8*, i8** %filename.addr, align 8, !dbg !177
  %2 = load i64, i64* %block_size.addr, align 8, !dbg !178
  %call = call i32 @archive_read_open_filename(%struct.archive* %0, i8* %1, i64 %2), !dbg !179
  ret i32 %call, !dbg !180
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @archive_read_open_filename(%struct.archive* %a, i8* %filename, i64 %block_size) #0 !dbg !138 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %filename.addr = alloca i8*, align 8
  %block_size.addr = alloca i64, align 8
  %filenames = alloca [2 x i8*], align 16
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !181, metadata !170), !dbg !182
  store i8* %filename, i8** %filename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filename.addr, metadata !183, metadata !170), !dbg !184
  store i64 %block_size, i64* %block_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %block_size.addr, metadata !185, metadata !170), !dbg !186
  call void @llvm.dbg.declare(metadata [2 x i8*]* %filenames, metadata !187, metadata !170), !dbg !191
  %0 = load i8*, i8** %filename.addr, align 8, !dbg !192
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %filenames, i64 0, i64 0, !dbg !193
  store i8* %0, i8** %arrayidx, align 16, !dbg !194
  %arrayidx1 = getelementptr inbounds [2 x i8*], [2 x i8*]* %filenames, i64 0, i64 1, !dbg !195
  store i8* null, i8** %arrayidx1, align 8, !dbg !196
  %1 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !197
  %arraydecay = getelementptr inbounds [2 x i8*], [2 x i8*]* %filenames, i32 0, i32 0, !dbg !198
  %2 = load i64, i64* %block_size.addr, align 8, !dbg !199
  %call = call i32 @archive_read_open_filenames(%struct.archive* %1, i8** %arraydecay, i64 %2), !dbg !200
  ret i32 %call, !dbg !201
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_open_filenames(%struct.archive* %a, i8** %filenames, i64 %block_size) #0 !dbg !139 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %filenames.addr = alloca i8**, align 8
  %block_size.addr = alloca i64, align 8
  %mine = alloca %struct.read_file_data*, align 8
  %filename = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !202, metadata !170), !dbg !203
  store i8** %filenames, i8*** %filenames.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %filenames.addr, metadata !204, metadata !170), !dbg !205
  store i64 %block_size, i64* %block_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %block_size.addr, metadata !206, metadata !170), !dbg !207
  call void @llvm.dbg.declare(metadata %struct.read_file_data** %mine, metadata !208, metadata !170), !dbg !209
  call void @llvm.dbg.declare(metadata i8** %filename, metadata !210, metadata !170), !dbg !211
  store i8* null, i8** %filename, align 8, !dbg !211
  %0 = load i8**, i8*** %filenames.addr, align 8, !dbg !212
  %tobool = icmp ne i8** %0, null, !dbg !212
  br i1 %tobool, label %if.then, label %if.end, !dbg !214

if.then:                                          ; preds = %entry
  %1 = load i8**, i8*** %filenames.addr, align 8, !dbg !215
  %incdec.ptr = getelementptr inbounds i8*, i8** %1, i32 1, !dbg !215
  store i8** %incdec.ptr, i8*** %filenames.addr, align 8, !dbg !215
  %2 = load i8*, i8** %1, align 8, !dbg !216
  store i8* %2, i8** %filename, align 8, !dbg !217
  br label %if.end, !dbg !218

if.end:                                           ; preds = %if.then, %entry
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !219
  call void @archive_clear_error(%struct.archive* %3), !dbg !220
  br label %do.body, !dbg !221

do.body:                                          ; preds = %land.end, %if.end
  %4 = load i8*, i8** %filename, align 8, !dbg !222
  %cmp = icmp eq i8* %4, null, !dbg !225
  br i1 %cmp, label %if.then1, label %if.end2, !dbg !226

if.then1:                                         ; preds = %do.body
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str, i32 0, i32 0), i8** %filename, align 8, !dbg !227
  br label %if.end2, !dbg !228

if.end2:                                          ; preds = %if.then1, %do.body
  %5 = load i8*, i8** %filename, align 8, !dbg !229
  %call = call i64 @strlen(i8* %5) #6, !dbg !230
  %add = add i64 40, %call, !dbg !231
  %call3 = call noalias i8* @calloc(i64 1, i64 %add) #7, !dbg !232
  %6 = bitcast i8* %call3 to %struct.read_file_data*, !dbg !233
  store %struct.read_file_data* %6, %struct.read_file_data** %mine, align 8, !dbg !234
  %7 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !235
  %cmp4 = icmp eq %struct.read_file_data* %7, null, !dbg !237
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !238

if.then5:                                         ; preds = %if.end2
  br label %no_memory, !dbg !239

if.end6:                                          ; preds = %if.end2
  %8 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !240
  %filename7 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %8, i32 0, i32 6, !dbg !241
  %m = bitcast %union.anon* %filename7 to [1 x i8]*, !dbg !242
  %arraydecay = getelementptr inbounds [1 x i8], [1 x i8]* %m, i32 0, i32 0, !dbg !240
  %9 = load i8*, i8** %filename, align 8, !dbg !243
  %call8 = call i8* @strcpy(i8* %arraydecay, i8* %9) #7, !dbg !244
  %10 = load i64, i64* %block_size.addr, align 8, !dbg !245
  %11 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !246
  %block_size9 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %11, i32 0, i32 1, !dbg !247
  store i64 %10, i64* %block_size9, align 8, !dbg !248
  %12 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !249
  %fd = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %12, i32 0, i32 0, !dbg !250
  store i32 -1, i32* %fd, align 8, !dbg !251
  %13 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !252
  %buffer = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %13, i32 0, i32 2, !dbg !253
  store i8* null, i8** %buffer, align 8, !dbg !254
  %14 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !255
  %use_lseek = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %14, i32 0, i32 4, !dbg !256
  store i8 0, i8* %use_lseek, align 4, !dbg !257
  %15 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !258
  %st_mode = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %15, i32 0, i32 3, !dbg !259
  store i32 0, i32* %st_mode, align 8, !dbg !260
  %16 = load i8*, i8** %filename, align 8, !dbg !261
  %cmp10 = icmp eq i8* %16, null, !dbg !263
  br i1 %cmp10, label %if.then13, label %lor.lhs.false, !dbg !264

lor.lhs.false:                                    ; preds = %if.end6
  %17 = load i8*, i8** %filename, align 8, !dbg !265
  %arrayidx = getelementptr inbounds i8, i8* %17, i64 0, !dbg !265
  %18 = load i8, i8* %arrayidx, align 1, !dbg !265
  %conv = sext i8 %18 to i32, !dbg !265
  %cmp11 = icmp eq i32 %conv, 0, !dbg !267
  br i1 %cmp11, label %if.then13, label %if.else, !dbg !268

if.then13:                                        ; preds = %lor.lhs.false, %if.end6
  %19 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !269
  %filename_type = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %19, i32 0, i32 5, !dbg !271
  store i32 0, i32* %filename_type, align 8, !dbg !272
  br label %if.end15, !dbg !273

if.else:                                          ; preds = %lor.lhs.false
  %20 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !274
  %filename_type14 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %20, i32 0, i32 5, !dbg !275
  store i32 1, i32* %filename_type14, align 8, !dbg !276
  br label %if.end15

if.end15:                                         ; preds = %if.else, %if.then13
  %21 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !277
  %22 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !279
  %23 = bitcast %struct.read_file_data* %22 to i8*, !dbg !279
  %call16 = call i32 @archive_read_append_callback_data(%struct.archive* %21, i8* %23), !dbg !280
  %cmp17 = icmp ne i32 %call16, 0, !dbg !281
  br i1 %cmp17, label %if.then19, label %if.end20, !dbg !282

if.then19:                                        ; preds = %if.end15
  store i32 -30, i32* %retval, align 4, !dbg !283
  br label %return, !dbg !283

if.end20:                                         ; preds = %if.end15
  %24 = load i8**, i8*** %filenames.addr, align 8, !dbg !284
  %cmp21 = icmp eq i8** %24, null, !dbg !286
  br i1 %cmp21, label %if.then23, label %if.end24, !dbg !287

if.then23:                                        ; preds = %if.end20
  br label %do.end, !dbg !288

if.end24:                                         ; preds = %if.end20
  %25 = load i8**, i8*** %filenames.addr, align 8, !dbg !289
  %incdec.ptr25 = getelementptr inbounds i8*, i8** %25, i32 1, !dbg !289
  store i8** %incdec.ptr25, i8*** %filenames.addr, align 8, !dbg !289
  %26 = load i8*, i8** %25, align 8, !dbg !290
  store i8* %26, i8** %filename, align 8, !dbg !291
  br label %do.cond, !dbg !292

do.cond:                                          ; preds = %if.end24
  %27 = load i8*, i8** %filename, align 8, !dbg !293
  %cmp26 = icmp ne i8* %27, null, !dbg !295
  br i1 %cmp26, label %land.rhs, label %land.end, !dbg !296

land.rhs:                                         ; preds = %do.cond
  %28 = load i8*, i8** %filename, align 8, !dbg !297
  %arrayidx28 = getelementptr inbounds i8, i8* %28, i64 0, !dbg !297
  %29 = load i8, i8* %arrayidx28, align 1, !dbg !297
  %conv29 = sext i8 %29 to i32, !dbg !297
  %cmp30 = icmp ne i32 %conv29, 0, !dbg !299
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %30 = phi i1 [ false, %do.cond ], [ %cmp30, %land.rhs ]
  br i1 %30, label %do.body, label %do.end, !dbg !300

do.end:                                           ; preds = %land.end, %if.then23
  %31 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !302
  %call32 = call i32 @archive_read_set_open_callback(%struct.archive* %31, i32 (%struct.archive*, i8*)* @file_open), !dbg !303
  %32 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !304
  %call33 = call i32 @archive_read_set_read_callback(%struct.archive* %32, i64 (%struct.archive*, i8*, i8**)* @file_read), !dbg !305
  %33 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !306
  %call34 = call i32 @archive_read_set_skip_callback(%struct.archive* %33, i64 (%struct.archive*, i8*, i64)* @file_skip), !dbg !307
  %34 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !308
  %call35 = call i32 @archive_read_set_close_callback(%struct.archive* %34, i32 (%struct.archive*, i8*)* @file_close), !dbg !309
  %35 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !310
  %call36 = call i32 @archive_read_set_switch_callback(%struct.archive* %35, i32 (%struct.archive*, i8*, i8*)* @file_switch), !dbg !311
  %36 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !312
  %call37 = call i32 @archive_read_set_seek_callback(%struct.archive* %36, i64 (%struct.archive*, i8*, i64, i32)* @file_seek), !dbg !313
  %37 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !314
  %call38 = call i32 @archive_read_open1(%struct.archive* %37), !dbg !315
  store i32 %call38, i32* %retval, align 4, !dbg !316
  br label %return, !dbg !316

no_memory:                                        ; preds = %if.then5
  %38 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !317
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %38, i32 12, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.1, i32 0, i32 0)), !dbg !318
  store i32 -30, i32* %retval, align 4, !dbg !319
  br label %return, !dbg !319

return:                                           ; preds = %no_memory, %do.end, %if.then19
  %39 = load i32, i32* %retval, align 4, !dbg !320
  ret i32 %39, !dbg !320
}

declare void @archive_clear_error(%struct.archive*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #3

declare i32 @archive_read_append_callback_data(%struct.archive*, i8*) #2

declare i32 @archive_read_set_open_callback(%struct.archive*, i32 (%struct.archive*, i8*)*) #2

; Function Attrs: nounwind uwtable
define internal i32 @file_open(%struct.archive* %a, i8* %client_data) #0 !dbg !148 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %st = alloca %struct.stat, align 8
  %mine = alloca %struct.read_file_data*, align 8
  %buffer = alloca i8*, align 8
  %filename = alloca i8*, align 8
  %wfilename = alloca i32*, align 8
  %fd = alloca i32, align 4
  %is_disk_like = alloca i32, align 4
  %new_block_size = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !321, metadata !170), !dbg !322
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !323, metadata !170), !dbg !324
  call void @llvm.dbg.declare(metadata %struct.stat* %st, metadata !325, metadata !170), !dbg !362
  call void @llvm.dbg.declare(metadata %struct.read_file_data** %mine, metadata !363, metadata !170), !dbg !364
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !365
  %1 = bitcast i8* %0 to %struct.read_file_data*, !dbg !366
  store %struct.read_file_data* %1, %struct.read_file_data** %mine, align 8, !dbg !364
  call void @llvm.dbg.declare(metadata i8** %buffer, metadata !367, metadata !170), !dbg !368
  call void @llvm.dbg.declare(metadata i8** %filename, metadata !369, metadata !170), !dbg !370
  store i8* null, i8** %filename, align 8, !dbg !370
  call void @llvm.dbg.declare(metadata i32** %wfilename, metadata !371, metadata !170), !dbg !372
  store i32* null, i32** %wfilename, align 8, !dbg !372
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !373, metadata !170), !dbg !374
  store i32 -1, i32* %fd, align 4, !dbg !374
  call void @llvm.dbg.declare(metadata i32* %is_disk_like, metadata !375, metadata !170), !dbg !376
  store i32 0, i32* %is_disk_like, align 4, !dbg !376
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !377
  call void @archive_clear_error(%struct.archive* %2), !dbg !378
  %3 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !379
  %filename_type = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %3, i32 0, i32 5, !dbg !381
  %4 = load i32, i32* %filename_type, align 8, !dbg !381
  %cmp = icmp eq i32 %4, 0, !dbg !382
  br i1 %cmp, label %if.then, label %if.else, !dbg !383

if.then:                                          ; preds = %entry
  store i32 0, i32* %fd, align 4, !dbg !384
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str, i32 0, i32 0), i8** %filename, align 8, !dbg !386
  br label %if.end10, !dbg !387

if.else:                                          ; preds = %entry
  %5 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !388
  %filename_type1 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %5, i32 0, i32 5, !dbg !391
  %6 = load i32, i32* %filename_type1, align 8, !dbg !391
  %cmp2 = icmp eq i32 %6, 1, !dbg !392
  br i1 %cmp2, label %if.then3, label %if.else8, !dbg !388

if.then3:                                         ; preds = %if.else
  %7 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !393
  %filename4 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %7, i32 0, i32 6, !dbg !395
  %m = bitcast %union.anon* %filename4 to [1 x i8]*, !dbg !396
  %arraydecay = getelementptr inbounds [1 x i8], [1 x i8]* %m, i32 0, i32 0, !dbg !393
  store i8* %arraydecay, i8** %filename, align 8, !dbg !397
  %8 = load i8*, i8** %filename, align 8, !dbg !398
  %call = call i32 (i8*, i32, ...) @open(i8* %8, i32 524288), !dbg !399
  store i32 %call, i32* %fd, align 4, !dbg !400
  %9 = load i32, i32* %fd, align 4, !dbg !401
  call void @__archive_ensure_cloexec_flag(i32 %9), !dbg !402
  %10 = load i32, i32* %fd, align 4, !dbg !403
  %cmp5 = icmp slt i32 %10, 0, !dbg !405
  br i1 %cmp5, label %if.then6, label %if.end, !dbg !406

if.then6:                                         ; preds = %if.then3
  %11 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !407
  %call7 = call i32* @__errno_location() #1, !dbg !409
  %12 = load i32, i32* %call7, align 4, !dbg !409
  %13 = load i8*, i8** %filename, align 8, !dbg !410
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %11, i32 %12, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.4, i32 0, i32 0), i8* %13), !dbg !411
  store i32 -30, i32* %retval, align 4, !dbg !413
  br label %return, !dbg !413

if.end:                                           ; preds = %if.then3
  br label %if.end9, !dbg !414

if.else8:                                         ; preds = %if.else
  %14 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !415
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %14, i32 -1, i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.5, i32 0, i32 0)), !dbg !417
  br label %fail, !dbg !418

if.end9:                                          ; preds = %if.end
  br label %if.end10

if.end10:                                         ; preds = %if.end9, %if.then
  %15 = load i32, i32* %fd, align 4, !dbg !419
  %call11 = call i32 @fstat(i32 %15, %struct.stat* %st) #7, !dbg !421
  %cmp12 = icmp ne i32 %call11, 0, !dbg !422
  br i1 %cmp12, label %if.then13, label %if.end21, !dbg !423

if.then13:                                        ; preds = %if.end10
  %16 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !424
  %filename_type14 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %16, i32 0, i32 5, !dbg !427
  %17 = load i32, i32* %filename_type14, align 8, !dbg !427
  %cmp15 = icmp eq i32 %17, 2, !dbg !428
  br i1 %cmp15, label %if.then16, label %if.else18, !dbg !429

if.then16:                                        ; preds = %if.then13
  %18 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !430
  %call17 = call i32* @__errno_location() #1, !dbg !431
  %19 = load i32, i32* %call17, align 4, !dbg !431
  %20 = load i32*, i32** %wfilename, align 8, !dbg !432
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %18, i32 %19, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.6, i32 0, i32 0), i32* %20), !dbg !433
  br label %if.end20, !dbg !435

if.else18:                                        ; preds = %if.then13
  %21 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !436
  %call19 = call i32* @__errno_location() #1, !dbg !437
  %22 = load i32, i32* %call19, align 4, !dbg !437
  %23 = load i8*, i8** %filename, align 8, !dbg !438
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %21, i32 %22, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.7, i32 0, i32 0), i8* %23), !dbg !439
  br label %if.end20

if.end20:                                         ; preds = %if.else18, %if.then16
  br label %fail, !dbg !440

if.end21:                                         ; preds = %if.end10
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !441
  %24 = load i32, i32* %st_mode, align 8, !dbg !441
  %and = and i32 %24, 61440, !dbg !441
  %cmp22 = icmp eq i32 %and, 32768, !dbg !441
  br i1 %cmp22, label %if.then23, label %if.else24, !dbg !443

if.then23:                                        ; preds = %if.end21
  %25 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !444
  %st_dev = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 0, !dbg !446
  %26 = load i64, i64* %st_dev, align 8, !dbg !446
  %st_ino = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 1, !dbg !447
  %27 = load i64, i64* %st_ino, align 8, !dbg !447
  call void @archive_read_extract_set_skip_file(%struct.archive* %25, i64 %26, i64 %27), !dbg !448
  store i32 1, i32* %is_disk_like, align 4, !dbg !449
  br label %if.end41, !dbg !450

if.else24:                                        ; preds = %if.end21
  %st_mode25 = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !451
  %28 = load i32, i32* %st_mode25, align 8, !dbg !451
  %and26 = and i32 %28, 61440, !dbg !451
  %cmp27 = icmp eq i32 %and26, 24576, !dbg !451
  br i1 %cmp27, label %land.lhs.true, label %if.end40, !dbg !453

land.lhs.true:                                    ; preds = %if.else24
  %29 = load i32, i32* %fd, align 4, !dbg !454
  %call28 = call i64 @lseek(i32 %29, i64 0, i32 1) #7, !dbg !455
  %cmp29 = icmp eq i64 %call28, 0, !dbg !456
  br i1 %cmp29, label %land.lhs.true30, label %if.end40, !dbg !457

land.lhs.true30:                                  ; preds = %land.lhs.true
  %30 = load i32, i32* %fd, align 4, !dbg !458
  %call31 = call i64 @lseek(i32 %30, i64 0, i32 0) #7, !dbg !459
  %cmp32 = icmp eq i64 %call31, 0, !dbg !460
  br i1 %cmp32, label %land.lhs.true33, label %if.end40, !dbg !461

land.lhs.true33:                                  ; preds = %land.lhs.true30
  %31 = load i32, i32* %fd, align 4, !dbg !462
  %call34 = call i64 @lseek(i32 %31, i64 0, i32 2) #7, !dbg !463
  %cmp35 = icmp sgt i64 %call34, 0, !dbg !464
  br i1 %cmp35, label %land.lhs.true36, label %if.end40, !dbg !465

land.lhs.true36:                                  ; preds = %land.lhs.true33
  %32 = load i32, i32* %fd, align 4, !dbg !466
  %call37 = call i64 @lseek(i32 %32, i64 0, i32 0) #7, !dbg !467
  %cmp38 = icmp eq i64 %call37, 0, !dbg !468
  br i1 %cmp38, label %if.then39, label %if.end40, !dbg !469

if.then39:                                        ; preds = %land.lhs.true36
  store i32 1, i32* %is_disk_like, align 4, !dbg !471
  br label %if.end40, !dbg !473

if.end40:                                         ; preds = %if.then39, %land.lhs.true36, %land.lhs.true33, %land.lhs.true30, %land.lhs.true, %if.else24
  br label %if.end41

if.end41:                                         ; preds = %if.end40, %if.then23
  %33 = load i32, i32* %is_disk_like, align 4, !dbg !474
  %tobool = icmp ne i32 %33, 0, !dbg !474
  br i1 %tobool, label %if.then42, label %if.end46, !dbg !476

if.then42:                                        ; preds = %if.end41
  call void @llvm.dbg.declare(metadata i64* %new_block_size, metadata !477, metadata !170), !dbg !479
  store i64 65536, i64* %new_block_size, align 8, !dbg !479
  br label %while.cond, !dbg !480

while.cond:                                       ; preds = %while.body, %if.then42
  %34 = load i64, i64* %new_block_size, align 8, !dbg !481
  %35 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !483
  %block_size = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %35, i32 0, i32 1, !dbg !484
  %36 = load i64, i64* %block_size, align 8, !dbg !484
  %cmp43 = icmp ult i64 %34, %36, !dbg !485
  br i1 %cmp43, label %land.rhs, label %land.end, !dbg !486

land.rhs:                                         ; preds = %while.cond
  %37 = load i64, i64* %new_block_size, align 8, !dbg !487
  %cmp44 = icmp ult i64 %37, 67108864, !dbg !488
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %38 = phi i1 [ false, %while.cond ], [ %cmp44, %land.rhs ]
  br i1 %38, label %while.body, label %while.end, !dbg !489

while.body:                                       ; preds = %land.end
  %39 = load i64, i64* %new_block_size, align 8, !dbg !491
  %mul = mul i64 %39, 2, !dbg !491
  store i64 %mul, i64* %new_block_size, align 8, !dbg !491
  br label %while.cond, !dbg !492

while.end:                                        ; preds = %land.end
  %40 = load i64, i64* %new_block_size, align 8, !dbg !494
  %41 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !495
  %block_size45 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %41, i32 0, i32 1, !dbg !496
  store i64 %40, i64* %block_size45, align 8, !dbg !497
  br label %if.end46, !dbg !498

if.end46:                                         ; preds = %while.end, %if.end41
  %42 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !499
  %block_size47 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %42, i32 0, i32 1, !dbg !500
  %43 = load i64, i64* %block_size47, align 8, !dbg !500
  %call48 = call noalias i8* @malloc(i64 %43) #7, !dbg !501
  store i8* %call48, i8** %buffer, align 8, !dbg !502
  %44 = load i8*, i8** %buffer, align 8, !dbg !503
  %cmp49 = icmp eq i8* %44, null, !dbg !505
  br i1 %cmp49, label %if.then50, label %if.end51, !dbg !506

if.then50:                                        ; preds = %if.end46
  %45 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !507
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %45, i32 12, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.1, i32 0, i32 0)), !dbg !509
  br label %fail, !dbg !510

if.end51:                                         ; preds = %if.end46
  %46 = load i8*, i8** %buffer, align 8, !dbg !511
  %47 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !512
  %buffer52 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %47, i32 0, i32 2, !dbg !513
  store i8* %46, i8** %buffer52, align 8, !dbg !514
  %48 = load i32, i32* %fd, align 4, !dbg !515
  %49 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !516
  %fd53 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %49, i32 0, i32 0, !dbg !517
  store i32 %48, i32* %fd53, align 8, !dbg !518
  %st_mode54 = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !519
  %50 = load i32, i32* %st_mode54, align 8, !dbg !519
  %51 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !520
  %st_mode55 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %51, i32 0, i32 3, !dbg !521
  store i32 %50, i32* %st_mode55, align 8, !dbg !522
  %52 = load i32, i32* %is_disk_like, align 4, !dbg !523
  %tobool56 = icmp ne i32 %52, 0, !dbg !523
  br i1 %tobool56, label %if.then57, label %if.end58, !dbg !525

if.then57:                                        ; preds = %if.end51
  %53 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !526
  %use_lseek = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %53, i32 0, i32 4, !dbg !527
  store i8 1, i8* %use_lseek, align 4, !dbg !528
  br label %if.end58, !dbg !526

if.end58:                                         ; preds = %if.then57, %if.end51
  store i32 0, i32* %retval, align 4, !dbg !529
  br label %return, !dbg !529

fail:                                             ; preds = %if.then50, %if.end20, %if.else8
  %54 = load i32, i32* %fd, align 4, !dbg !530
  %cmp59 = icmp ne i32 %54, -1, !dbg !532
  br i1 %cmp59, label %land.lhs.true60, label %if.end64, !dbg !533

land.lhs.true60:                                  ; preds = %fail
  %55 = load i32, i32* %fd, align 4, !dbg !534
  %cmp61 = icmp ne i32 %55, 0, !dbg !536
  br i1 %cmp61, label %if.then62, label %if.end64, !dbg !537

if.then62:                                        ; preds = %land.lhs.true60
  %56 = load i32, i32* %fd, align 4, !dbg !538
  %call63 = call i32 @close(i32 %56), !dbg !539
  br label %if.end64, !dbg !539

if.end64:                                         ; preds = %if.then62, %land.lhs.true60, %fail
  store i32 -30, i32* %retval, align 4, !dbg !540
  br label %return, !dbg !540

return:                                           ; preds = %if.end64, %if.end58, %if.then6
  %57 = load i32, i32* %retval, align 4, !dbg !541
  ret i32 %57, !dbg !541
}

declare i32 @archive_read_set_read_callback(%struct.archive*, i64 (%struct.archive*, i8*, i8**)*) #2

; Function Attrs: nounwind uwtable
define internal i64 @file_read(%struct.archive* %a, i8* %client_data, i8** %buff) #0 !dbg !151 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %buff.addr = alloca i8**, align 8
  %mine = alloca %struct.read_file_data*, align 8
  %bytes_read = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !542, metadata !170), !dbg !543
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !544, metadata !170), !dbg !545
  store i8** %buff, i8*** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buff.addr, metadata !546, metadata !170), !dbg !547
  call void @llvm.dbg.declare(metadata %struct.read_file_data** %mine, metadata !548, metadata !170), !dbg !549
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !550
  %1 = bitcast i8* %0 to %struct.read_file_data*, !dbg !551
  store %struct.read_file_data* %1, %struct.read_file_data** %mine, align 8, !dbg !549
  call void @llvm.dbg.declare(metadata i64* %bytes_read, metadata !552, metadata !170), !dbg !553
  %2 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !554
  %buffer = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %2, i32 0, i32 2, !dbg !555
  %3 = load i8*, i8** %buffer, align 8, !dbg !555
  %4 = load i8**, i8*** %buff.addr, align 8, !dbg !556
  store i8* %3, i8** %4, align 8, !dbg !557
  br label %for.cond, !dbg !558

for.cond:                                         ; preds = %if.then4, %entry
  %5 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !559
  %fd = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %5, i32 0, i32 0, !dbg !563
  %6 = load i32, i32* %fd, align 8, !dbg !563
  %7 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !564
  %buffer1 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %7, i32 0, i32 2, !dbg !565
  %8 = load i8*, i8** %buffer1, align 8, !dbg !565
  %9 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !566
  %block_size = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %9, i32 0, i32 1, !dbg !567
  %10 = load i64, i64* %block_size, align 8, !dbg !567
  %call = call i64 @read(i32 %6, i8* %8, i64 %10), !dbg !568
  store i64 %call, i64* %bytes_read, align 8, !dbg !569
  %11 = load i64, i64* %bytes_read, align 8, !dbg !570
  %cmp = icmp slt i64 %11, 0, !dbg !572
  br i1 %cmp, label %if.then, label %if.end19, !dbg !573

if.then:                                          ; preds = %for.cond
  %call2 = call i32* @__errno_location() #1, !dbg !574
  %12 = load i32, i32* %call2, align 4, !dbg !574
  %cmp3 = icmp eq i32 %12, 4, !dbg !577
  br i1 %cmp3, label %if.then4, label %if.else, !dbg !578

if.then4:                                         ; preds = %if.then
  br label %for.cond, !dbg !579

if.else:                                          ; preds = %if.then
  %13 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !580
  %filename_type = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %13, i32 0, i32 5, !dbg !582
  %14 = load i32, i32* %filename_type, align 8, !dbg !582
  %cmp5 = icmp eq i32 %14, 0, !dbg !583
  br i1 %cmp5, label %if.then6, label %if.else8, !dbg !584

if.then6:                                         ; preds = %if.else
  %15 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !585
  %call7 = call i32* @__errno_location() #1, !dbg !586
  %16 = load i32, i32* %call7, align 4, !dbg !586
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %15, i32 %16, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.8, i32 0, i32 0)), !dbg !587
  br label %if.end17, !dbg !589

if.else8:                                         ; preds = %if.else
  %17 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !590
  %filename_type9 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %17, i32 0, i32 5, !dbg !592
  %18 = load i32, i32* %filename_type9, align 8, !dbg !592
  %cmp10 = icmp eq i32 %18, 1, !dbg !593
  br i1 %cmp10, label %if.then11, label %if.else13, !dbg !594

if.then11:                                        ; preds = %if.else8
  %19 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !595
  %call12 = call i32* @__errno_location() #1, !dbg !596
  %20 = load i32, i32* %call12, align 4, !dbg !596
  %21 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !597
  %filename = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %21, i32 0, i32 6, !dbg !598
  %m = bitcast %union.anon* %filename to [1 x i8]*, !dbg !599
  %arraydecay = getelementptr inbounds [1 x i8], [1 x i8]* %m, i32 0, i32 0, !dbg !597
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %19, i32 %20, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.9, i32 0, i32 0), i8* %arraydecay), !dbg !600
  br label %if.end, !dbg !602

if.else13:                                        ; preds = %if.else8
  %22 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !603
  %call14 = call i32* @__errno_location() #1, !dbg !604
  %23 = load i32, i32* %call14, align 4, !dbg !604
  %24 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !605
  %filename15 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %24, i32 0, i32 6, !dbg !606
  %w = bitcast %union.anon* %filename15 to [1 x i32]*, !dbg !607
  %arraydecay16 = getelementptr inbounds [1 x i32], [1 x i32]* %w, i32 0, i32 0, !dbg !605
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %22, i32 %23, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.10, i32 0, i32 0), i32* %arraydecay16), !dbg !608
  br label %if.end

if.end:                                           ; preds = %if.else13, %if.then11
  br label %if.end17

if.end17:                                         ; preds = %if.end, %if.then6
  br label %if.end18

if.end18:                                         ; preds = %if.end17
  br label %if.end19, !dbg !609

if.end19:                                         ; preds = %if.end18, %for.cond
  %25 = load i64, i64* %bytes_read, align 8, !dbg !610
  ret i64 %25, !dbg !611
}

declare i32 @archive_read_set_skip_callback(%struct.archive*, i64 (%struct.archive*, i8*, i64)*) #2

; Function Attrs: nounwind uwtable
define internal i64 @file_skip(%struct.archive* %a, i8* %client_data, i64 %request) #0 !dbg !154 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %request.addr = alloca i64, align 8
  %mine = alloca %struct.read_file_data*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !612, metadata !170), !dbg !613
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !614, metadata !170), !dbg !615
  store i64 %request, i64* %request.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %request.addr, metadata !616, metadata !170), !dbg !617
  call void @llvm.dbg.declare(metadata %struct.read_file_data** %mine, metadata !618, metadata !170), !dbg !619
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !620
  %1 = bitcast i8* %0 to %struct.read_file_data*, !dbg !621
  store %struct.read_file_data* %1, %struct.read_file_data** %mine, align 8, !dbg !619
  %2 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !622
  %use_lseek = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %2, i32 0, i32 4, !dbg !624
  %3 = load i8, i8* %use_lseek, align 4, !dbg !624
  %tobool = icmp ne i8 %3, 0, !dbg !622
  br i1 %tobool, label %if.then, label %if.end, !dbg !625

if.then:                                          ; preds = %entry
  %4 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !626
  %5 = load i8*, i8** %client_data.addr, align 8, !dbg !627
  %6 = load i64, i64* %request.addr, align 8, !dbg !628
  %call = call i64 @file_skip_lseek(%struct.archive* %4, i8* %5, i64 %6), !dbg !629
  store i64 %call, i64* %retval, align 8, !dbg !630
  br label %return, !dbg !630

if.end:                                           ; preds = %entry
  store i64 0, i64* %retval, align 8, !dbg !631
  br label %return, !dbg !631

return:                                           ; preds = %if.end, %if.then
  %7 = load i64, i64* %retval, align 8, !dbg !632
  ret i64 %7, !dbg !632
}

declare i32 @archive_read_set_close_callback(%struct.archive*, i32 (%struct.archive*, i8*)*) #2

; Function Attrs: nounwind uwtable
define internal i32 @file_close(%struct.archive* %a, i8* %client_data) #0 !dbg !161 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %mine = alloca %struct.read_file_data*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !633, metadata !170), !dbg !634
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !635, metadata !170), !dbg !636
  call void @llvm.dbg.declare(metadata %struct.read_file_data** %mine, metadata !637, metadata !170), !dbg !638
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !639
  %1 = bitcast i8* %0 to %struct.read_file_data*, !dbg !640
  store %struct.read_file_data* %1, %struct.read_file_data** %mine, align 8, !dbg !638
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !641
  %3 = load i8*, i8** %client_data.addr, align 8, !dbg !642
  %call = call i32 @file_close2(%struct.archive* %2, i8* %3), !dbg !643
  %4 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !644
  %5 = bitcast %struct.read_file_data* %4 to i8*, !dbg !644
  call void @free(i8* %5) #7, !dbg !645
  ret i32 0, !dbg !646
}

declare i32 @archive_read_set_switch_callback(%struct.archive*, i32 (%struct.archive*, i8*, i8*)*) #2

; Function Attrs: nounwind uwtable
define internal i32 @file_switch(%struct.archive* %a, i8* %client_data1, i8* %client_data2) #0 !dbg !163 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data1.addr = alloca i8*, align 8
  %client_data2.addr = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !647, metadata !170), !dbg !648
  store i8* %client_data1, i8** %client_data1.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data1.addr, metadata !649, metadata !170), !dbg !650
  store i8* %client_data2, i8** %client_data2.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data2.addr, metadata !651, metadata !170), !dbg !652
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !653
  %1 = load i8*, i8** %client_data1.addr, align 8, !dbg !654
  %call = call i32 @file_close2(%struct.archive* %0, i8* %1), !dbg !655
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !656
  %3 = load i8*, i8** %client_data2.addr, align 8, !dbg !657
  %call1 = call i32 @file_open(%struct.archive* %2, i8* %3), !dbg !658
  ret i32 %call1, !dbg !659
}

declare i32 @archive_read_set_seek_callback(%struct.archive*, i64 (%struct.archive*, i8*, i64, i32)*) #2

; Function Attrs: nounwind uwtable
define internal i64 @file_seek(%struct.archive* %a, i8* %client_data, i64 %request, i32 %whence) #0 !dbg !158 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %request.addr = alloca i64, align 8
  %whence.addr = alloca i32, align 4
  %mine = alloca %struct.read_file_data*, align 8
  %r = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !660, metadata !170), !dbg !661
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !662, metadata !170), !dbg !663
  store i64 %request, i64* %request.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %request.addr, metadata !664, metadata !170), !dbg !665
  store i32 %whence, i32* %whence.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %whence.addr, metadata !666, metadata !170), !dbg !667
  call void @llvm.dbg.declare(metadata %struct.read_file_data** %mine, metadata !668, metadata !170), !dbg !669
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !670
  %1 = bitcast i8* %0 to %struct.read_file_data*, !dbg !671
  store %struct.read_file_data* %1, %struct.read_file_data** %mine, align 8, !dbg !669
  call void @llvm.dbg.declare(metadata i64* %r, metadata !672, metadata !170), !dbg !673
  %2 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !674
  %fd = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %2, i32 0, i32 0, !dbg !675
  %3 = load i32, i32* %fd, align 8, !dbg !675
  %4 = load i64, i64* %request.addr, align 8, !dbg !676
  %5 = load i32, i32* %whence.addr, align 4, !dbg !677
  %call = call i64 @lseek(i32 %3, i64 %4, i32 %5) #7, !dbg !678
  store i64 %call, i64* %r, align 8, !dbg !679
  %6 = load i64, i64* %r, align 8, !dbg !680
  %cmp = icmp sge i64 %6, 0, !dbg !682
  br i1 %cmp, label %if.then, label %if.end, !dbg !683

if.then:                                          ; preds = %entry
  %7 = load i64, i64* %r, align 8, !dbg !684
  store i64 %7, i64* %retval, align 8, !dbg !685
  br label %return, !dbg !685

if.end:                                           ; preds = %entry
  %8 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !686
  %filename_type = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %8, i32 0, i32 5, !dbg !688
  %9 = load i32, i32* %filename_type, align 8, !dbg !688
  %cmp1 = icmp eq i32 %9, 0, !dbg !689
  br i1 %cmp1, label %if.then2, label %if.else, !dbg !690

if.then2:                                         ; preds = %if.end
  %10 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !691
  %call3 = call i32* @__errno_location() #1, !dbg !692
  %11 = load i32, i32* %call3, align 4, !dbg !692
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %10, i32 %11, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.11, i32 0, i32 0)), !dbg !693
  br label %if.end13, !dbg !695

if.else:                                          ; preds = %if.end
  %12 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !696
  %filename_type4 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %12, i32 0, i32 5, !dbg !698
  %13 = load i32, i32* %filename_type4, align 8, !dbg !698
  %cmp5 = icmp eq i32 %13, 1, !dbg !699
  br i1 %cmp5, label %if.then6, label %if.else8, !dbg !700

if.then6:                                         ; preds = %if.else
  %14 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !701
  %call7 = call i32* @__errno_location() #1, !dbg !702
  %15 = load i32, i32* %call7, align 4, !dbg !702
  %16 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !703
  %filename = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %16, i32 0, i32 6, !dbg !704
  %m = bitcast %union.anon* %filename to [1 x i8]*, !dbg !705
  %arraydecay = getelementptr inbounds [1 x i8], [1 x i8]* %m, i32 0, i32 0, !dbg !703
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %14, i32 %15, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.12, i32 0, i32 0), i8* %arraydecay), !dbg !706
  br label %if.end12, !dbg !708

if.else8:                                         ; preds = %if.else
  %17 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !709
  %call9 = call i32* @__errno_location() #1, !dbg !710
  %18 = load i32, i32* %call9, align 4, !dbg !710
  %19 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !711
  %filename10 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %19, i32 0, i32 6, !dbg !712
  %w = bitcast %union.anon* %filename10 to [1 x i32]*, !dbg !713
  %arraydecay11 = getelementptr inbounds [1 x i32], [1 x i32]* %w, i32 0, i32 0, !dbg !711
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %17, i32 %18, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.13, i32 0, i32 0), i32* %arraydecay11), !dbg !714
  br label %if.end12

if.end12:                                         ; preds = %if.else8, %if.then6
  br label %if.end13

if.end13:                                         ; preds = %if.end12, %if.then2
  store i64 -30, i64* %retval, align 8, !dbg !715
  br label %return, !dbg !715

return:                                           ; preds = %if.end13, %if.then
  %20 = load i64, i64* %retval, align 8, !dbg !716
  ret i64 %20, !dbg !716
}

declare i32 @archive_read_open1(%struct.archive*) #2

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define i32 @archive_read_open_filename_w(%struct.archive* %a, i32* %wfilename, i64 %block_size) #0 !dbg !143 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %wfilename.addr = alloca i32*, align 8
  %block_size.addr = alloca i64, align 8
  %mine = alloca %struct.read_file_data*, align 8
  %fn = alloca %struct.archive_string, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !717, metadata !170), !dbg !718
  store i32* %wfilename, i32** %wfilename.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %wfilename.addr, metadata !719, metadata !170), !dbg !720
  store i64 %block_size, i64* %block_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %block_size.addr, metadata !721, metadata !170), !dbg !722
  call void @llvm.dbg.declare(metadata %struct.read_file_data** %mine, metadata !723, metadata !170), !dbg !724
  %0 = load i32*, i32** %wfilename.addr, align 8, !dbg !725
  %call = call i64 @wcslen(i32* %0) #6, !dbg !726
  %mul = mul i64 %call, 4, !dbg !727
  %add = add i64 40, %mul, !dbg !728
  %call1 = call noalias i8* @calloc(i64 1, i64 %add) #7, !dbg !729
  %1 = bitcast i8* %call1 to %struct.read_file_data*, !dbg !730
  store %struct.read_file_data* %1, %struct.read_file_data** %mine, align 8, !dbg !724
  %2 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !731
  %tobool = icmp ne %struct.read_file_data* %2, null, !dbg !731
  br i1 %tobool, label %if.end, label %if.then, !dbg !733

if.then:                                          ; preds = %entry
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !734
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %3, i32 12, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.1, i32 0, i32 0)), !dbg !736
  store i32 -30, i32* %retval, align 4, !dbg !737
  br label %return, !dbg !737

if.end:                                           ; preds = %entry
  %4 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !738
  %fd = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %4, i32 0, i32 0, !dbg !739
  store i32 -1, i32* %fd, align 8, !dbg !740
  %5 = load i64, i64* %block_size.addr, align 8, !dbg !741
  %6 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !742
  %block_size2 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %6, i32 0, i32 1, !dbg !743
  store i64 %5, i64* %block_size2, align 8, !dbg !744
  %7 = load i32*, i32** %wfilename.addr, align 8, !dbg !745
  %cmp = icmp eq i32* %7, null, !dbg !747
  br i1 %cmp, label %if.then4, label %lor.lhs.false, !dbg !748

lor.lhs.false:                                    ; preds = %if.end
  %8 = load i32*, i32** %wfilename.addr, align 8, !dbg !749
  %arrayidx = getelementptr inbounds i32, i32* %8, i64 0, !dbg !749
  %9 = load i32, i32* %arrayidx, align 4, !dbg !749
  %cmp3 = icmp eq i32 %9, 0, !dbg !751
  br i1 %cmp3, label %if.then4, label %if.else, !dbg !752

if.then4:                                         ; preds = %lor.lhs.false, %if.end
  %10 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !753
  %filename_type = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %10, i32 0, i32 5, !dbg !755
  store i32 0, i32* %filename_type, align 8, !dbg !756
  br label %if.end19, !dbg !757

if.else:                                          ; preds = %lor.lhs.false
  call void @llvm.dbg.declare(metadata %struct.archive_string* %fn, metadata !758, metadata !170), !dbg !760
  br label %do.body, !dbg !761

do.body:                                          ; preds = %if.else
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %fn, i32 0, i32 0, !dbg !762
  store i8* null, i8** %s, align 8, !dbg !762
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %fn, i32 0, i32 1, !dbg !762
  store i64 0, i64* %length, align 8, !dbg !762
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %fn, i32 0, i32 2, !dbg !762
  store i64 0, i64* %buffer_length, align 8, !dbg !762
  br label %do.end, !dbg !762

do.end:                                           ; preds = %do.body
  %11 = load i32*, i32** %wfilename.addr, align 8, !dbg !765
  %12 = load i32*, i32** %wfilename.addr, align 8, !dbg !767
  %call5 = call i64 @wcslen(i32* %12) #6, !dbg !768
  %call6 = call i32 @archive_string_append_from_wcs(%struct.archive_string* %fn, i32* %11, i64 %call5), !dbg !769
  %cmp7 = icmp ne i32 %call6, 0, !dbg !770
  br i1 %cmp7, label %if.then8, label %if.end15, !dbg !771

if.then8:                                         ; preds = %do.end
  %call9 = call i32* @__errno_location() #1, !dbg !772
  %13 = load i32, i32* %call9, align 4, !dbg !772
  %cmp10 = icmp eq i32 %13, 12, !dbg !775
  br i1 %cmp10, label %if.then11, label %if.else13, !dbg !776

if.then11:                                        ; preds = %if.then8
  %14 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !777
  %call12 = call i32* @__errno_location() #1, !dbg !778
  %15 = load i32, i32* %call12, align 4, !dbg !778
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %14, i32 %15, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.2, i32 0, i32 0)), !dbg !779
  br label %if.end14, !dbg !781

if.else13:                                        ; preds = %if.then8
  %16 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !782
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %16, i32 22, i8* getelementptr inbounds ([69 x i8], [69 x i8]* @.str.3, i32 0, i32 0)), !dbg !783
  br label %if.end14

if.end14:                                         ; preds = %if.else13, %if.then11
  call void @archive_string_free(%struct.archive_string* %fn), !dbg !784
  %17 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !785
  %18 = bitcast %struct.read_file_data* %17 to i8*, !dbg !785
  call void @free(i8* %18) #7, !dbg !786
  store i32 -30, i32* %retval, align 4, !dbg !787
  br label %return, !dbg !787

if.end15:                                         ; preds = %do.end
  %19 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !788
  %filename_type16 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %19, i32 0, i32 5, !dbg !789
  store i32 1, i32* %filename_type16, align 8, !dbg !790
  %20 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !791
  %filename = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %20, i32 0, i32 6, !dbg !792
  %m = bitcast %union.anon* %filename to [1 x i8]*, !dbg !793
  %arraydecay = getelementptr inbounds [1 x i8], [1 x i8]* %m, i32 0, i32 0, !dbg !791
  %s17 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %fn, i32 0, i32 0, !dbg !794
  %21 = load i8*, i8** %s17, align 8, !dbg !794
  %call18 = call i8* @strcpy(i8* %arraydecay, i8* %21) #7, !dbg !795
  call void @archive_string_free(%struct.archive_string* %fn), !dbg !796
  br label %if.end19

if.end19:                                         ; preds = %if.end15, %if.then4
  %22 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !797
  %23 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !799
  %24 = bitcast %struct.read_file_data* %23 to i8*, !dbg !799
  %call20 = call i32 @archive_read_append_callback_data(%struct.archive* %22, i8* %24), !dbg !800
  %cmp21 = icmp ne i32 %call20, 0, !dbg !801
  br i1 %cmp21, label %if.then22, label %if.end23, !dbg !802

if.then22:                                        ; preds = %if.end19
  store i32 -30, i32* %retval, align 4, !dbg !803
  br label %return, !dbg !803

if.end23:                                         ; preds = %if.end19
  %25 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !804
  %call24 = call i32 @archive_read_set_open_callback(%struct.archive* %25, i32 (%struct.archive*, i8*)* @file_open), !dbg !805
  %26 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !806
  %call25 = call i32 @archive_read_set_read_callback(%struct.archive* %26, i64 (%struct.archive*, i8*, i8**)* @file_read), !dbg !807
  %27 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !808
  %call26 = call i32 @archive_read_set_skip_callback(%struct.archive* %27, i64 (%struct.archive*, i8*, i64)* @file_skip), !dbg !809
  %28 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !810
  %call27 = call i32 @archive_read_set_close_callback(%struct.archive* %28, i32 (%struct.archive*, i8*)* @file_close), !dbg !811
  %29 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !812
  %call28 = call i32 @archive_read_set_switch_callback(%struct.archive* %29, i32 (%struct.archive*, i8*, i8*)* @file_switch), !dbg !813
  %30 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !814
  %call29 = call i32 @archive_read_set_seek_callback(%struct.archive* %30, i64 (%struct.archive*, i8*, i64, i32)* @file_seek), !dbg !815
  %31 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !816
  %call30 = call i32 @archive_read_open1(%struct.archive* %31), !dbg !817
  store i32 %call30, i32* %retval, align 4, !dbg !818
  br label %return, !dbg !818

return:                                           ; preds = %if.end23, %if.then22, %if.end14, %if.then
  %32 = load i32, i32* %retval, align 4, !dbg !819
  ret i32 %32, !dbg !819
}

; Function Attrs: nounwind readonly
declare i64 @wcslen(i32*) #4

declare i32 @archive_string_append_from_wcs(%struct.archive_string*, i32*, i64) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

declare void @archive_string_free(%struct.archive_string*) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

declare i32 @open(i8*, i32, ...) #2

declare void @__archive_ensure_cloexec_flag(i32) #2

; Function Attrs: nounwind
declare i32 @fstat(i32, %struct.stat*) #3

declare void @archive_read_extract_set_skip_file(%struct.archive*, i64, i64) #2

; Function Attrs: nounwind
declare i64 @lseek(i32, i64, i32) #3

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

declare i32 @close(i32) #2

declare i64 @read(i32, i8*, i64) #2

; Function Attrs: nounwind uwtable
define internal i64 @file_skip_lseek(%struct.archive* %a, i8* %client_data, i64 %request) #0 !dbg !157 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %request.addr = alloca i64, align 8
  %mine = alloca %struct.read_file_data*, align 8
  %old_offset = alloca i64, align 8
  %new_offset = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !820, metadata !170), !dbg !821
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !822, metadata !170), !dbg !823
  store i64 %request, i64* %request.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %request.addr, metadata !824, metadata !170), !dbg !825
  call void @llvm.dbg.declare(metadata %struct.read_file_data** %mine, metadata !826, metadata !170), !dbg !827
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !828
  %1 = bitcast i8* %0 to %struct.read_file_data*, !dbg !829
  store %struct.read_file_data* %1, %struct.read_file_data** %mine, align 8, !dbg !827
  call void @llvm.dbg.declare(metadata i64* %old_offset, metadata !830, metadata !170), !dbg !832
  call void @llvm.dbg.declare(metadata i64* %new_offset, metadata !833, metadata !170), !dbg !834
  %2 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !835
  %fd = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %2, i32 0, i32 0, !dbg !837
  %3 = load i32, i32* %fd, align 8, !dbg !837
  %call = call i64 @lseek(i32 %3, i64 0, i32 1) #7, !dbg !838
  store i64 %call, i64* %old_offset, align 8, !dbg !839
  %cmp = icmp sge i64 %call, 0, !dbg !840
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !841

land.lhs.true:                                    ; preds = %entry
  %4 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !842
  %fd1 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %4, i32 0, i32 0, !dbg !843
  %5 = load i32, i32* %fd1, align 8, !dbg !843
  %6 = load i64, i64* %request.addr, align 8, !dbg !844
  %call2 = call i64 @lseek(i32 %5, i64 %6, i32 1) #7, !dbg !845
  store i64 %call2, i64* %new_offset, align 8, !dbg !846
  %cmp3 = icmp sge i64 %call2, 0, !dbg !847
  br i1 %cmp3, label %if.then, label %if.end, !dbg !848

if.then:                                          ; preds = %land.lhs.true
  %7 = load i64, i64* %new_offset, align 8, !dbg !850
  %8 = load i64, i64* %old_offset, align 8, !dbg !851
  %sub = sub nsw i64 %7, %8, !dbg !852
  store i64 %sub, i64* %retval, align 8, !dbg !853
  br label %return, !dbg !853

if.end:                                           ; preds = %land.lhs.true, %entry
  %9 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !854
  %use_lseek = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %9, i32 0, i32 4, !dbg !855
  store i8 0, i8* %use_lseek, align 4, !dbg !856
  %call4 = call i32* @__errno_location() #1, !dbg !857
  %10 = load i32, i32* %call4, align 4, !dbg !857
  %cmp5 = icmp eq i32 %10, 29, !dbg !859
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !860

if.then6:                                         ; preds = %if.end
  store i64 0, i64* %retval, align 8, !dbg !861
  br label %return, !dbg !861

if.end7:                                          ; preds = %if.end
  %11 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !862
  %filename_type = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %11, i32 0, i32 5, !dbg !864
  %12 = load i32, i32* %filename_type, align 8, !dbg !864
  %cmp8 = icmp eq i32 %12, 0, !dbg !865
  br i1 %cmp8, label %if.then9, label %if.else, !dbg !866

if.then9:                                         ; preds = %if.end7
  %13 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !867
  %call10 = call i32* @__errno_location() #1, !dbg !868
  %14 = load i32, i32* %call10, align 4, !dbg !868
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %13, i32 %14, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.11, i32 0, i32 0)), !dbg !869
  br label %if.end20, !dbg !871

if.else:                                          ; preds = %if.end7
  %15 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !872
  %filename_type11 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %15, i32 0, i32 5, !dbg !874
  %16 = load i32, i32* %filename_type11, align 8, !dbg !874
  %cmp12 = icmp eq i32 %16, 1, !dbg !875
  br i1 %cmp12, label %if.then13, label %if.else15, !dbg !876

if.then13:                                        ; preds = %if.else
  %17 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !877
  %call14 = call i32* @__errno_location() #1, !dbg !878
  %18 = load i32, i32* %call14, align 4, !dbg !878
  %19 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !879
  %filename = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %19, i32 0, i32 6, !dbg !880
  %m = bitcast %union.anon* %filename to [1 x i8]*, !dbg !881
  %arraydecay = getelementptr inbounds [1 x i8], [1 x i8]* %m, i32 0, i32 0, !dbg !879
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %17, i32 %18, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.12, i32 0, i32 0), i8* %arraydecay), !dbg !882
  br label %if.end19, !dbg !884

if.else15:                                        ; preds = %if.else
  %20 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !885
  %call16 = call i32* @__errno_location() #1, !dbg !886
  %21 = load i32, i32* %call16, align 4, !dbg !886
  %22 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !887
  %filename17 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %22, i32 0, i32 6, !dbg !888
  %w = bitcast %union.anon* %filename17 to [1 x i32]*, !dbg !889
  %arraydecay18 = getelementptr inbounds [1 x i32], [1 x i32]* %w, i32 0, i32 0, !dbg !887
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %20, i32 %21, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.13, i32 0, i32 0), i32* %arraydecay18), !dbg !890
  br label %if.end19

if.end19:                                         ; preds = %if.else15, %if.then13
  br label %if.end20

if.end20:                                         ; preds = %if.end19, %if.then9
  store i64 -1, i64* %retval, align 8, !dbg !891
  br label %return, !dbg !891

return:                                           ; preds = %if.end20, %if.then6, %if.then
  %23 = load i64, i64* %retval, align 8, !dbg !892
  ret i64 %23, !dbg !892
}

; Function Attrs: nounwind uwtable
define internal i32 @file_close2(%struct.archive* %a, i8* %client_data) #0 !dbg !162 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %mine = alloca %struct.read_file_data*, align 8
  %bytesRead = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !893, metadata !170), !dbg !894
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !895, metadata !170), !dbg !896
  call void @llvm.dbg.declare(metadata %struct.read_file_data** %mine, metadata !897, metadata !170), !dbg !898
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !899
  %1 = bitcast i8* %0 to %struct.read_file_data*, !dbg !900
  store %struct.read_file_data* %1, %struct.read_file_data** %mine, align 8, !dbg !898
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !901
  %3 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !902
  %fd = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %3, i32 0, i32 0, !dbg !904
  %4 = load i32, i32* %fd, align 8, !dbg !904
  %cmp = icmp sge i32 %4, 0, !dbg !905
  br i1 %cmp, label %if.then, label %if.end17, !dbg !906

if.then:                                          ; preds = %entry
  %5 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !907
  %st_mode = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %5, i32 0, i32 3, !dbg !907
  %6 = load i32, i32* %st_mode, align 8, !dbg !907
  %and = and i32 %6, 61440, !dbg !907
  %cmp1 = icmp eq i32 %and, 32768, !dbg !907
  br i1 %cmp1, label %if.end, label %land.lhs.true, !dbg !910

land.lhs.true:                                    ; preds = %if.then
  %7 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !911
  %st_mode2 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %7, i32 0, i32 3, !dbg !911
  %8 = load i32, i32* %st_mode2, align 8, !dbg !911
  %and3 = and i32 %8, 61440, !dbg !911
  %cmp4 = icmp eq i32 %and3, 8192, !dbg !911
  br i1 %cmp4, label %if.end, label %land.lhs.true5, !dbg !913

land.lhs.true5:                                   ; preds = %land.lhs.true
  %9 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !914
  %st_mode6 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %9, i32 0, i32 3, !dbg !914
  %10 = load i32, i32* %st_mode6, align 8, !dbg !914
  %and7 = and i32 %10, 61440, !dbg !914
  %cmp8 = icmp eq i32 %and7, 24576, !dbg !914
  br i1 %cmp8, label %if.end, label %if.then9, !dbg !915

if.then9:                                         ; preds = %land.lhs.true5
  call void @llvm.dbg.declare(metadata i64* %bytesRead, metadata !917, metadata !170), !dbg !919
  br label %do.body, !dbg !920

do.body:                                          ; preds = %do.cond, %if.then9
  %11 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !921
  %fd10 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %11, i32 0, i32 0, !dbg !923
  %12 = load i32, i32* %fd10, align 8, !dbg !923
  %13 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !924
  %buffer = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %13, i32 0, i32 2, !dbg !925
  %14 = load i8*, i8** %buffer, align 8, !dbg !925
  %15 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !926
  %block_size = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %15, i32 0, i32 1, !dbg !927
  %16 = load i64, i64* %block_size, align 8, !dbg !927
  %call = call i64 @read(i32 %12, i8* %14, i64 %16), !dbg !928
  store i64 %call, i64* %bytesRead, align 8, !dbg !929
  br label %do.cond, !dbg !930

do.cond:                                          ; preds = %do.body
  %17 = load i64, i64* %bytesRead, align 8, !dbg !931
  %cmp11 = icmp sgt i64 %17, 0, !dbg !933
  br i1 %cmp11, label %do.body, label %do.end, !dbg !934

do.end:                                           ; preds = %do.cond
  br label %if.end, !dbg !935

if.end:                                           ; preds = %do.end, %land.lhs.true5, %land.lhs.true, %if.then
  %18 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !936
  %filename_type = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %18, i32 0, i32 5, !dbg !938
  %19 = load i32, i32* %filename_type, align 8, !dbg !938
  %cmp12 = icmp ne i32 %19, 0, !dbg !939
  br i1 %cmp12, label %if.then13, label %if.end16, !dbg !940

if.then13:                                        ; preds = %if.end
  %20 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !941
  %fd14 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %20, i32 0, i32 0, !dbg !942
  %21 = load i32, i32* %fd14, align 8, !dbg !942
  %call15 = call i32 @close(i32 %21), !dbg !943
  br label %if.end16, !dbg !943

if.end16:                                         ; preds = %if.then13, %if.end
  br label %if.end17, !dbg !944

if.end17:                                         ; preds = %if.end16, %entry
  %22 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !945
  %buffer18 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %22, i32 0, i32 2, !dbg !946
  %23 = load i8*, i8** %buffer18, align 8, !dbg !946
  call void @free(i8* %23) #7, !dbg !947
  %24 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !948
  %buffer19 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %24, i32 0, i32 2, !dbg !949
  store i8* null, i8** %buffer19, align 8, !dbg !950
  %25 = load %struct.read_file_data*, %struct.read_file_data** %mine, align 8, !dbg !951
  %fd20 = getelementptr inbounds %struct.read_file_data, %struct.read_file_data* %25, i32 0, i32 0, !dbg !952
  store i32 -1, i32* %fd20, align 8, !dbg !953
  ret i32 0, !dbg !954
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly }
attributes #7 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!166, !167}
!llvm.ident = !{!168}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !8, subprograms: !39)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_open_filename.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "fnt_e", file: !1, line: 79, size: 32, align: 32, elements: !4)
!4 = !{!5, !6, !7}
!5 = !DIEnumerator(name: "FNT_STDIN", value: 0)
!6 = !DIEnumerator(name: "FNT_MBS", value: 1)
!7 = !DIEnumerator(name: "FNT_WCS", value: 2)
!8 = !{!9, !10}
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!11 = !DICompositeType(tag: DW_TAG_structure_type, name: "read_file_data", file: !1, line: 73, size: 320, align: 64, elements: !12)
!12 = !{!13, !15, !19, !20, !26, !28, !29}
!13 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !11, file: !1, line: 74, baseType: !14, size: 32, align: 32)
!14 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "block_size", scope: !11, file: !1, line: 75, baseType: !16, size: 64, align: 64, offset: 64)
!16 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !17, line: 62, baseType: !18)
!17 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!18 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!19 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !11, file: !1, line: 76, baseType: !9, size: 64, align: 64, offset: 128)
!20 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !11, file: !1, line: 77, baseType: !21, size: 32, align: 32, offset: 192)
!21 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !22, line: 63, baseType: !23)
!22 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!23 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !24, line: 129, baseType: !25)
!24 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!25 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "use_lseek", scope: !11, file: !1, line: 78, baseType: !27, size: 8, align: 8, offset: 224)
!27 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!28 = !DIDerivedType(tag: DW_TAG_member, name: "filename_type", scope: !11, file: !1, line: 79, baseType: !3, size: 32, align: 32, offset: 256)
!29 = !DIDerivedType(tag: DW_TAG_member, name: "filename", scope: !11, file: !1, line: 83, baseType: !30, size: 32, align: 32, offset: 288)
!30 = !DICompositeType(tag: DW_TAG_union_type, scope: !11, file: !1, line: 80, size: 32, align: 32, elements: !31)
!31 = !{!32, !36}
!32 = !DIDerivedType(tag: DW_TAG_member, name: "m", scope: !30, file: !1, line: 81, baseType: !33, size: 8, align: 8)
!33 = !DICompositeType(tag: DW_TAG_array_type, baseType: !27, size: 8, align: 8, elements: !34)
!34 = !{!35}
!35 = !DISubrange(count: 1)
!36 = !DIDerivedType(tag: DW_TAG_member, name: "w", scope: !30, file: !1, line: 82, baseType: !37, size: 32, align: 32)
!37 = !DICompositeType(tag: DW_TAG_array_type, baseType: !38, size: 32, align: 32, elements: !34)
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "wchar_t", file: !17, line: 90, baseType: !14)
!39 = !{!40, !138, !139, !143, !148, !151, !154, !157, !158, !161, !162, !163}
!40 = distinct !DISubprogram(name: "archive_read_open_file", scope: !1, file: !1, line: 96, type: !41, isLocal: false, isDefinition: true, scopeLine: 98, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!41 = !DISubroutineType(types: !42)
!42 = !{!14, !43, !108, !16}
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !45, line: 89, size: 1280, align: 64, elements: !46)
!45 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!46 = !{!47, !48, !49, !110, !111, !112, !113, !114, !115, !116, !117, !125, !126, !127, !128, !131, !132, !133, !134, !135, !136}
!47 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !44, file: !45, line: 96, baseType: !25, size: 32, align: 32)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !44, file: !45, line: 97, baseType: !25, size: 32, align: 32, offset: 32)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !44, file: !45, line: 103, baseType: !50, size: 64, align: 64, offset: 64)
!50 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !51, size: 64, align: 64)
!51 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !45, line: 63, size: 832, align: 64, elements: !52)
!52 = !{!53, !57, !58, !65, !66, !76, !82, !87, !88, !95, !96, !100, !104}
!53 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !51, file: !45, line: 64, baseType: !54, size: 64, align: 64)
!54 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!55 = !DISubroutineType(types: !56)
!56 = !{!14, !43}
!57 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !51, file: !45, line: 65, baseType: !54, size: 64, align: 64, offset: 64)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !51, file: !45, line: 66, baseType: !59, size: 64, align: 64, offset: 128)
!59 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!60 = !DISubroutineType(types: !61)
!61 = !{!14, !43, !62}
!62 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!63 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !64, line: 180, flags: DIFlagFwdDecl)
!64 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!65 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !51, file: !45, line: 68, baseType: !54, size: 64, align: 64, offset: 192)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !51, file: !45, line: 69, baseType: !67, size: 64, align: 64, offset: 256)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64, align: 64)
!68 = !DISubroutineType(types: !69)
!69 = !{!70, !43, !74, !16}
!70 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !71, line: 109, baseType: !72)
!71 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!72 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !24, line: 172, baseType: !73)
!73 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!74 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !75, size: 64, align: 64)
!75 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !51, file: !45, line: 71, baseType: !77, size: 64, align: 64, offset: 320)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DISubroutineType(types: !79)
!79 = !{!70, !43, !74, !16, !80}
!80 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !81, line: 40, baseType: !73)
!81 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!82 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !51, file: !45, line: 74, baseType: !83, size: 64, align: 64, offset: 384)
!83 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !84, size: 64, align: 64)
!84 = !DISubroutineType(types: !85)
!85 = !{!14, !43, !86}
!86 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !51, file: !45, line: 76, baseType: !59, size: 64, align: 64, offset: 448)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !51, file: !45, line: 78, baseType: !89, size: 64, align: 64, offset: 512)
!89 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !90, size: 64, align: 64)
!90 = !DISubroutineType(types: !91)
!91 = !{!14, !43, !92, !93, !94}
!92 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!93 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !16, size: 64, align: 64)
!94 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !80, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !51, file: !45, line: 81, baseType: !54, size: 64, align: 64, offset: 576)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !51, file: !45, line: 82, baseType: !97, size: 64, align: 64, offset: 640)
!97 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !98, size: 64, align: 64)
!98 = !DISubroutineType(types: !99)
!99 = !{!80, !43, !14}
!100 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !51, file: !45, line: 83, baseType: !101, size: 64, align: 64, offset: 704)
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !102, size: 64, align: 64)
!102 = !DISubroutineType(types: !103)
!103 = !{!14, !43, !14}
!104 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !51, file: !45, line: 84, baseType: !105, size: 64, align: 64, offset: 768)
!105 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !106, size: 64, align: 64)
!106 = !DISubroutineType(types: !107)
!107 = !{!108, !43, !14}
!108 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !109, size: 64, align: 64)
!109 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !27)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !44, file: !45, line: 105, baseType: !14, size: 32, align: 32, offset: 128)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !44, file: !45, line: 106, baseType: !108, size: 64, align: 64, offset: 192)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !44, file: !45, line: 108, baseType: !14, size: 32, align: 32, offset: 256)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !44, file: !45, line: 109, baseType: !108, size: 64, align: 64, offset: 320)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !44, file: !45, line: 112, baseType: !14, size: 32, align: 32, offset: 384)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !44, file: !45, line: 114, baseType: !14, size: 32, align: 32, offset: 416)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !44, file: !45, line: 115, baseType: !108, size: 64, align: 64, offset: 448)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !44, file: !45, line: 116, baseType: !118, size: 192, align: 64, offset: 512)
!118 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !119, line: 58, size: 192, align: 64, elements: !120)
!119 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!120 = !{!121, !123, !124}
!121 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !118, file: !119, line: 59, baseType: !122, size: 64, align: 64)
!122 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !27, size: 64, align: 64)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !118, file: !119, line: 60, baseType: !16, size: 64, align: 64, offset: 64)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !118, file: !119, line: 61, baseType: !16, size: 64, align: 64, offset: 128)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !44, file: !45, line: 118, baseType: !122, size: 64, align: 64, offset: 704)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !44, file: !45, line: 119, baseType: !25, size: 32, align: 32, offset: 768)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !44, file: !45, line: 120, baseType: !25, size: 32, align: 32, offset: 800)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !44, file: !45, line: 121, baseType: !129, size: 64, align: 64, offset: 832)
!129 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !130, size: 64, align: 64)
!130 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !119, line: 70, flags: DIFlagFwdDecl)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !44, file: !45, line: 127, baseType: !108, size: 64, align: 64, offset: 896)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !44, file: !45, line: 128, baseType: !80, size: 64, align: 64, offset: 960)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !44, file: !45, line: 129, baseType: !80, size: 64, align: 64, offset: 1024)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !44, file: !45, line: 130, baseType: !16, size: 64, align: 64, offset: 1088)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !44, file: !45, line: 137, baseType: !27, size: 8, align: 8, offset: 1152)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !44, file: !45, line: 138, baseType: !16, size: 64, align: 64, offset: 1216)
!137 = !{}
!138 = distinct !DISubprogram(name: "archive_read_open_filename", scope: !1, file: !1, line: 103, type: !41, isLocal: false, isDefinition: true, scopeLine: 105, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!139 = distinct !DISubprogram(name: "archive_read_open_filenames", scope: !1, file: !1, line: 113, type: !140, isLocal: false, isDefinition: true, scopeLine: 115, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!140 = !DISubroutineType(types: !141)
!141 = !{!14, !43, !142, !16}
!142 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !108, size: 64, align: 64)
!143 = distinct !DISubprogram(name: "archive_read_open_filename_w", scope: !1, file: !1, line: 159, type: !144, isLocal: false, isDefinition: true, scopeLine: 161, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!144 = !DISubroutineType(types: !145)
!145 = !{!14, !43, !146, !16}
!146 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !147, size: 64, align: 64)
!147 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !38)
!148 = distinct !DISubprogram(name: "file_open", scope: !1, file: !1, line: 218, type: !149, isLocal: true, isDefinition: true, scopeLine: 219, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!149 = !DISubroutineType(types: !150)
!150 = !{!14, !43, !9}
!151 = distinct !DISubprogram(name: "file_read", scope: !1, file: !1, line: 384, type: !152, isLocal: true, isDefinition: true, scopeLine: 385, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!152 = !DISubroutineType(types: !153)
!153 = !{!70, !43, !9, !92}
!154 = distinct !DISubprogram(name: "file_skip", scope: !1, file: !1, line: 490, type: !155, isLocal: true, isDefinition: true, scopeLine: 491, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!155 = !DISubroutineType(types: !156)
!156 = !{!80, !43, !9, !80}
!157 = distinct !DISubprogram(name: "file_skip_lseek", scope: !1, file: !1, line: 443, type: !155, isLocal: true, isDefinition: true, scopeLine: 444, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!158 = distinct !DISubprogram(name: "file_seek", scope: !1, file: !1, line: 506, type: !159, isLocal: true, isDefinition: true, scopeLine: 507, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!159 = !DISubroutineType(types: !160)
!160 = !{!80, !43, !9, !80, !14}
!161 = distinct !DISubprogram(name: "file_close", scope: !1, file: !1, line: 569, type: !149, isLocal: true, isDefinition: true, scopeLine: 570, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!162 = distinct !DISubprogram(name: "file_close2", scope: !1, file: !1, line: 530, type: !149, isLocal: true, isDefinition: true, scopeLine: 531, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!163 = distinct !DISubprogram(name: "file_switch", scope: !1, file: !1, line: 578, type: !164, isLocal: true, isDefinition: true, scopeLine: 579, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!164 = !DISubroutineType(types: !165)
!165 = !{!14, !43, !9, !9}
!166 = !{i32 2, !"Dwarf Version", i32 4}
!167 = !{i32 2, !"Debug Info Version", i32 3}
!168 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!169 = !DILocalVariable(name: "a", arg: 1, scope: !40, file: !1, line: 96, type: !43)
!170 = !DIExpression()
!171 = !DILocation(line: 96, column: 40, scope: !40)
!172 = !DILocalVariable(name: "filename", arg: 2, scope: !40, file: !1, line: 96, type: !108)
!173 = !DILocation(line: 96, column: 55, scope: !40)
!174 = !DILocalVariable(name: "block_size", arg: 3, scope: !40, file: !1, line: 97, type: !16)
!175 = !DILocation(line: 97, column: 12, scope: !40)
!176 = !DILocation(line: 99, column: 37, scope: !40)
!177 = !DILocation(line: 99, column: 40, scope: !40)
!178 = !DILocation(line: 99, column: 50, scope: !40)
!179 = !DILocation(line: 99, column: 10, scope: !40)
!180 = !DILocation(line: 99, column: 2, scope: !40)
!181 = !DILocalVariable(name: "a", arg: 1, scope: !138, file: !1, line: 103, type: !43)
!182 = !DILocation(line: 103, column: 44, scope: !138)
!183 = !DILocalVariable(name: "filename", arg: 2, scope: !138, file: !1, line: 103, type: !108)
!184 = !DILocation(line: 103, column: 59, scope: !138)
!185 = !DILocalVariable(name: "block_size", arg: 3, scope: !138, file: !1, line: 104, type: !16)
!186 = !DILocation(line: 104, column: 12, scope: !138)
!187 = !DILocalVariable(name: "filenames", scope: !138, file: !1, line: 106, type: !188)
!188 = !DICompositeType(tag: DW_TAG_array_type, baseType: !108, size: 128, align: 64, elements: !189)
!189 = !{!190}
!190 = !DISubrange(count: 2)
!191 = !DILocation(line: 106, column: 14, scope: !138)
!192 = !DILocation(line: 107, column: 17, scope: !138)
!193 = !DILocation(line: 107, column: 2, scope: !138)
!194 = !DILocation(line: 107, column: 15, scope: !138)
!195 = !DILocation(line: 108, column: 2, scope: !138)
!196 = !DILocation(line: 108, column: 15, scope: !138)
!197 = !DILocation(line: 109, column: 37, scope: !138)
!198 = !DILocation(line: 109, column: 40, scope: !138)
!199 = !DILocation(line: 109, column: 51, scope: !138)
!200 = !DILocation(line: 109, column: 9, scope: !138)
!201 = !DILocation(line: 109, column: 2, scope: !138)
!202 = !DILocalVariable(name: "a", arg: 1, scope: !139, file: !1, line: 113, type: !43)
!203 = !DILocation(line: 113, column: 45, scope: !139)
!204 = !DILocalVariable(name: "filenames", arg: 2, scope: !139, file: !1, line: 113, type: !142)
!205 = !DILocation(line: 113, column: 61, scope: !139)
!206 = !DILocalVariable(name: "block_size", arg: 3, scope: !139, file: !1, line: 114, type: !16)
!207 = !DILocation(line: 114, column: 12, scope: !139)
!208 = !DILocalVariable(name: "mine", scope: !139, file: !1, line: 116, type: !10)
!209 = !DILocation(line: 116, column: 25, scope: !139)
!210 = !DILocalVariable(name: "filename", scope: !139, file: !1, line: 117, type: !108)
!211 = !DILocation(line: 117, column: 14, scope: !139)
!212 = !DILocation(line: 118, column: 6, scope: !213)
!213 = distinct !DILexicalBlock(scope: !139, file: !1, line: 118, column: 6)
!214 = !DILocation(line: 118, column: 6, scope: !139)
!215 = !DILocation(line: 119, column: 25, scope: !213)
!216 = !DILocation(line: 119, column: 14, scope: !213)
!217 = !DILocation(line: 119, column: 12, scope: !213)
!218 = !DILocation(line: 119, column: 3, scope: !213)
!219 = !DILocation(line: 121, column: 22, scope: !139)
!220 = !DILocation(line: 121, column: 2, scope: !139)
!221 = !DILocation(line: 122, column: 2, scope: !139)
!222 = !DILocation(line: 124, column: 7, scope: !223)
!223 = distinct !DILexicalBlock(scope: !224, file: !1, line: 124, column: 7)
!224 = distinct !DILexicalBlock(scope: !139, file: !1, line: 123, column: 2)
!225 = !DILocation(line: 124, column: 16, scope: !223)
!226 = !DILocation(line: 124, column: 7, scope: !224)
!227 = !DILocation(line: 125, column: 13, scope: !223)
!228 = !DILocation(line: 125, column: 4, scope: !223)
!229 = !DILocation(line: 127, column: 27, scope: !224)
!230 = !DILocation(line: 127, column: 20, scope: !224)
!231 = !DILocation(line: 127, column: 18, scope: !224)
!232 = !DILocation(line: 126, column: 35, scope: !224)
!233 = !DILocation(line: 126, column: 10, scope: !224)
!234 = !DILocation(line: 126, column: 8, scope: !224)
!235 = !DILocation(line: 128, column: 7, scope: !236)
!236 = distinct !DILexicalBlock(scope: !224, file: !1, line: 128, column: 7)
!237 = !DILocation(line: 128, column: 12, scope: !236)
!238 = !DILocation(line: 128, column: 7, scope: !224)
!239 = !DILocation(line: 129, column: 4, scope: !236)
!240 = !DILocation(line: 130, column: 10, scope: !224)
!241 = !DILocation(line: 130, column: 16, scope: !224)
!242 = !DILocation(line: 130, column: 25, scope: !224)
!243 = !DILocation(line: 130, column: 28, scope: !224)
!244 = !DILocation(line: 130, column: 3, scope: !224)
!245 = !DILocation(line: 131, column: 22, scope: !224)
!246 = !DILocation(line: 131, column: 3, scope: !224)
!247 = !DILocation(line: 131, column: 9, scope: !224)
!248 = !DILocation(line: 131, column: 20, scope: !224)
!249 = !DILocation(line: 132, column: 3, scope: !224)
!250 = !DILocation(line: 132, column: 9, scope: !224)
!251 = !DILocation(line: 132, column: 12, scope: !224)
!252 = !DILocation(line: 133, column: 3, scope: !224)
!253 = !DILocation(line: 133, column: 9, scope: !224)
!254 = !DILocation(line: 133, column: 16, scope: !224)
!255 = !DILocation(line: 134, column: 19, scope: !224)
!256 = !DILocation(line: 134, column: 25, scope: !224)
!257 = !DILocation(line: 134, column: 35, scope: !224)
!258 = !DILocation(line: 134, column: 3, scope: !224)
!259 = !DILocation(line: 134, column: 9, scope: !224)
!260 = !DILocation(line: 134, column: 17, scope: !224)
!261 = !DILocation(line: 135, column: 7, scope: !262)
!262 = distinct !DILexicalBlock(scope: !224, file: !1, line: 135, column: 7)
!263 = !DILocation(line: 135, column: 16, scope: !262)
!264 = !DILocation(line: 135, column: 24, scope: !262)
!265 = !DILocation(line: 135, column: 27, scope: !266)
!266 = !DILexicalBlockFile(scope: !262, file: !1, discriminator: 1)
!267 = !DILocation(line: 135, column: 39, scope: !266)
!268 = !DILocation(line: 135, column: 7, scope: !266)
!269 = !DILocation(line: 136, column: 4, scope: !270)
!270 = distinct !DILexicalBlock(scope: !262, file: !1, line: 135, column: 48)
!271 = !DILocation(line: 136, column: 10, scope: !270)
!272 = !DILocation(line: 136, column: 24, scope: !270)
!273 = !DILocation(line: 137, column: 3, scope: !270)
!274 = !DILocation(line: 138, column: 4, scope: !262)
!275 = !DILocation(line: 138, column: 10, scope: !262)
!276 = !DILocation(line: 138, column: 24, scope: !262)
!277 = !DILocation(line: 139, column: 41, scope: !278)
!278 = distinct !DILexicalBlock(scope: !224, file: !1, line: 139, column: 7)
!279 = !DILocation(line: 139, column: 44, scope: !278)
!280 = !DILocation(line: 139, column: 7, scope: !278)
!281 = !DILocation(line: 139, column: 50, scope: !278)
!282 = !DILocation(line: 139, column: 7, scope: !224)
!283 = !DILocation(line: 140, column: 4, scope: !278)
!284 = !DILocation(line: 141, column: 7, scope: !285)
!285 = distinct !DILexicalBlock(scope: !224, file: !1, line: 141, column: 7)
!286 = !DILocation(line: 141, column: 17, scope: !285)
!287 = !DILocation(line: 141, column: 7, scope: !224)
!288 = !DILocation(line: 142, column: 4, scope: !285)
!289 = !DILocation(line: 143, column: 25, scope: !224)
!290 = !DILocation(line: 143, column: 14, scope: !224)
!291 = !DILocation(line: 143, column: 12, scope: !224)
!292 = !DILocation(line: 144, column: 2, scope: !224)
!293 = !DILocation(line: 144, column: 11, scope: !294)
!294 = !DILexicalBlockFile(scope: !139, file: !1, discriminator: 1)
!295 = !DILocation(line: 144, column: 20, scope: !294)
!296 = !DILocation(line: 144, column: 28, scope: !294)
!297 = !DILocation(line: 144, column: 31, scope: !298)
!298 = !DILexicalBlockFile(scope: !139, file: !1, discriminator: 2)
!299 = !DILocation(line: 144, column: 43, scope: !298)
!300 = !DILocation(line: 144, column: 2, scope: !301)
!301 = !DILexicalBlockFile(scope: !224, file: !1, discriminator: 3)
!302 = !DILocation(line: 145, column: 33, scope: !139)
!303 = !DILocation(line: 145, column: 2, scope: !139)
!304 = !DILocation(line: 146, column: 33, scope: !139)
!305 = !DILocation(line: 146, column: 2, scope: !139)
!306 = !DILocation(line: 147, column: 33, scope: !139)
!307 = !DILocation(line: 147, column: 2, scope: !139)
!308 = !DILocation(line: 148, column: 34, scope: !139)
!309 = !DILocation(line: 148, column: 2, scope: !139)
!310 = !DILocation(line: 149, column: 35, scope: !139)
!311 = !DILocation(line: 149, column: 2, scope: !139)
!312 = !DILocation(line: 150, column: 33, scope: !139)
!313 = !DILocation(line: 150, column: 2, scope: !139)
!314 = !DILocation(line: 152, column: 29, scope: !139)
!315 = !DILocation(line: 152, column: 10, scope: !139)
!316 = !DILocation(line: 152, column: 2, scope: !139)
!317 = !DILocation(line: 154, column: 20, scope: !139)
!318 = !DILocation(line: 154, column: 2, scope: !139)
!319 = !DILocation(line: 155, column: 2, scope: !139)
!320 = !DILocation(line: 156, column: 1, scope: !139)
!321 = !DILocalVariable(name: "a", arg: 1, scope: !148, file: !1, line: 218, type: !43)
!322 = !DILocation(line: 218, column: 27, scope: !148)
!323 = !DILocalVariable(name: "client_data", arg: 2, scope: !148, file: !1, line: 218, type: !9)
!324 = !DILocation(line: 218, column: 36, scope: !148)
!325 = !DILocalVariable(name: "st", scope: !148, file: !1, line: 220, type: !326)
!326 = !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !327, line: 46, size: 1152, align: 64, elements: !328)
!327 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!328 = !{!329, !331, !333, !335, !336, !338, !340, !341, !342, !344, !346, !348, !356, !357, !358}
!329 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !326, file: !327, line: 48, baseType: !330, size: 64, align: 64)
!330 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !24, line: 124, baseType: !18)
!331 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !326, file: !327, line: 53, baseType: !332, size: 64, align: 64, offset: 64)
!332 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino_t", file: !24, line: 127, baseType: !18)
!333 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !326, file: !327, line: 61, baseType: !334, size: 64, align: 64, offset: 128)
!334 = !DIDerivedType(tag: DW_TAG_typedef, name: "__nlink_t", file: !24, line: 130, baseType: !18)
!335 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !326, file: !327, line: 62, baseType: !23, size: 32, align: 32, offset: 192)
!336 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !326, file: !327, line: 64, baseType: !337, size: 32, align: 32, offset: 224)
!337 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !24, line: 125, baseType: !25)
!338 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !326, file: !327, line: 65, baseType: !339, size: 32, align: 32, offset: 256)
!339 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !24, line: 126, baseType: !25)
!340 = !DIDerivedType(tag: DW_TAG_member, name: "__pad0", scope: !326, file: !327, line: 67, baseType: !14, size: 32, align: 32, offset: 288)
!341 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !326, file: !327, line: 69, baseType: !330, size: 64, align: 64, offset: 320)
!342 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !326, file: !327, line: 74, baseType: !343, size: 64, align: 64, offset: 384)
!343 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !24, line: 131, baseType: !73)
!344 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !326, file: !327, line: 78, baseType: !345, size: 64, align: 64, offset: 448)
!345 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blksize_t", file: !24, line: 153, baseType: !73)
!346 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !326, file: !327, line: 80, baseType: !347, size: 64, align: 64, offset: 512)
!347 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blkcnt_t", file: !24, line: 158, baseType: !73)
!348 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !326, file: !327, line: 91, baseType: !349, size: 128, align: 64, offset: 576)
!349 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !350, line: 120, size: 128, align: 64, elements: !351)
!350 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!351 = !{!352, !354}
!352 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !349, file: !350, line: 122, baseType: !353, size: 64, align: 64)
!353 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !24, line: 139, baseType: !73)
!354 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !349, file: !350, line: 123, baseType: !355, size: 64, align: 64, offset: 64)
!355 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !24, line: 175, baseType: !73)
!356 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !326, file: !327, line: 92, baseType: !349, size: 128, align: 64, offset: 704)
!357 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !326, file: !327, line: 93, baseType: !349, size: 128, align: 64, offset: 832)
!358 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !326, file: !327, line: 106, baseType: !359, size: 192, align: 64, offset: 960)
!359 = !DICompositeType(tag: DW_TAG_array_type, baseType: !355, size: 192, align: 64, elements: !360)
!360 = !{!361}
!361 = !DISubrange(count: 3)
!362 = !DILocation(line: 220, column: 14, scope: !148)
!363 = !DILocalVariable(name: "mine", scope: !148, file: !1, line: 221, type: !10)
!364 = !DILocation(line: 221, column: 25, scope: !148)
!365 = !DILocation(line: 221, column: 57, scope: !148)
!366 = !DILocation(line: 221, column: 32, scope: !148)
!367 = !DILocalVariable(name: "buffer", scope: !148, file: !1, line: 222, type: !9)
!368 = !DILocation(line: 222, column: 8, scope: !148)
!369 = !DILocalVariable(name: "filename", scope: !148, file: !1, line: 223, type: !108)
!370 = !DILocation(line: 223, column: 14, scope: !148)
!371 = !DILocalVariable(name: "wfilename", scope: !148, file: !1, line: 224, type: !146)
!372 = !DILocation(line: 224, column: 17, scope: !148)
!373 = !DILocalVariable(name: "fd", scope: !148, file: !1, line: 225, type: !14)
!374 = !DILocation(line: 225, column: 6, scope: !148)
!375 = !DILocalVariable(name: "is_disk_like", scope: !148, file: !1, line: 226, type: !14)
!376 = !DILocation(line: 226, column: 6, scope: !148)
!377 = !DILocation(line: 235, column: 22, scope: !148)
!378 = !DILocation(line: 235, column: 2, scope: !148)
!379 = !DILocation(line: 236, column: 6, scope: !380)
!380 = distinct !DILexicalBlock(scope: !148, file: !1, line: 236, column: 6)
!381 = !DILocation(line: 236, column: 12, scope: !380)
!382 = !DILocation(line: 236, column: 26, scope: !380)
!383 = !DILocation(line: 236, column: 6, scope: !148)
!384 = !DILocation(line: 246, column: 6, scope: !385)
!385 = distinct !DILexicalBlock(scope: !380, file: !1, line: 236, column: 40)
!386 = !DILocation(line: 250, column: 12, scope: !385)
!387 = !DILocation(line: 251, column: 2, scope: !385)
!388 = !DILocation(line: 251, column: 13, scope: !389)
!389 = !DILexicalBlockFile(scope: !390, file: !1, discriminator: 1)
!390 = distinct !DILexicalBlock(scope: !380, file: !1, line: 251, column: 13)
!391 = !DILocation(line: 251, column: 19, scope: !389)
!392 = !DILocation(line: 251, column: 33, scope: !389)
!393 = !DILocation(line: 252, column: 14, scope: !394)
!394 = distinct !DILexicalBlock(scope: !390, file: !1, line: 251, column: 45)
!395 = !DILocation(line: 252, column: 20, scope: !394)
!396 = !DILocation(line: 252, column: 29, scope: !394)
!397 = !DILocation(line: 252, column: 12, scope: !394)
!398 = !DILocation(line: 253, column: 13, scope: !394)
!399 = !DILocation(line: 253, column: 8, scope: !394)
!400 = !DILocation(line: 253, column: 6, scope: !394)
!401 = !DILocation(line: 254, column: 33, scope: !394)
!402 = !DILocation(line: 254, column: 3, scope: !394)
!403 = !DILocation(line: 255, column: 7, scope: !404)
!404 = distinct !DILexicalBlock(scope: !394, file: !1, line: 255, column: 7)
!405 = !DILocation(line: 255, column: 10, scope: !404)
!406 = !DILocation(line: 255, column: 7, scope: !394)
!407 = !DILocation(line: 256, column: 22, scope: !408)
!408 = distinct !DILexicalBlock(scope: !404, file: !1, line: 255, column: 15)
!409 = !DILocation(line: 256, column: 25, scope: !408)
!410 = !DILocation(line: 257, column: 31, scope: !408)
!411 = !DILocation(line: 256, column: 4, scope: !412)
!412 = !DILexicalBlockFile(scope: !408, file: !1, discriminator: 1)
!413 = !DILocation(line: 258, column: 4, scope: !408)
!414 = !DILocation(line: 260, column: 2, scope: !394)
!415 = !DILocation(line: 278, column: 21, scope: !416)
!416 = distinct !DILexicalBlock(scope: !390, file: !1, line: 260, column: 9)
!417 = !DILocation(line: 278, column: 3, scope: !416)
!418 = !DILocation(line: 280, column: 3, scope: !416)
!419 = !DILocation(line: 283, column: 12, scope: !420)
!420 = distinct !DILexicalBlock(scope: !148, file: !1, line: 283, column: 6)
!421 = !DILocation(line: 283, column: 6, scope: !420)
!422 = !DILocation(line: 283, column: 21, scope: !420)
!423 = !DILocation(line: 283, column: 6, scope: !148)
!424 = !DILocation(line: 284, column: 7, scope: !425)
!425 = distinct !DILexicalBlock(scope: !426, file: !1, line: 284, column: 7)
!426 = distinct !DILexicalBlock(scope: !420, file: !1, line: 283, column: 27)
!427 = !DILocation(line: 284, column: 13, scope: !425)
!428 = !DILocation(line: 284, column: 27, scope: !425)
!429 = !DILocation(line: 284, column: 7, scope: !426)
!430 = !DILocation(line: 285, column: 22, scope: !425)
!431 = !DILocation(line: 285, column: 25, scope: !425)
!432 = !DILocation(line: 286, column: 8, scope: !425)
!433 = !DILocation(line: 285, column: 4, scope: !434)
!434 = !DILexicalBlockFile(scope: !425, file: !1, discriminator: 1)
!435 = !DILocation(line: 285, column: 4, scope: !425)
!436 = !DILocation(line: 288, column: 22, scope: !425)
!437 = !DILocation(line: 288, column: 25, scope: !425)
!438 = !DILocation(line: 289, column: 8, scope: !425)
!439 = !DILocation(line: 288, column: 4, scope: !434)
!440 = !DILocation(line: 290, column: 3, scope: !426)
!441 = !DILocation(line: 310, column: 6, scope: !442)
!442 = distinct !DILexicalBlock(scope: !148, file: !1, line: 310, column: 6)
!443 = !DILocation(line: 310, column: 6, scope: !148)
!444 = !DILocation(line: 312, column: 38, scope: !445)
!445 = distinct !DILexicalBlock(scope: !442, file: !1, line: 310, column: 27)
!446 = !DILocation(line: 312, column: 44, scope: !445)
!447 = !DILocation(line: 312, column: 55, scope: !445)
!448 = !DILocation(line: 312, column: 3, scope: !445)
!449 = !DILocation(line: 314, column: 16, scope: !445)
!450 = !DILocation(line: 315, column: 2, scope: !445)
!451 = !DILocation(line: 339, column: 11, scope: !452)
!452 = distinct !DILexicalBlock(scope: !442, file: !1, line: 339, column: 11)
!453 = !DILocation(line: 339, column: 31, scope: !452)
!454 = !DILocation(line: 340, column: 12, scope: !452)
!455 = !DILocation(line: 340, column: 6, scope: !452)
!456 = !DILocation(line: 340, column: 29, scope: !452)
!457 = !DILocation(line: 340, column: 34, scope: !452)
!458 = !DILocation(line: 341, column: 12, scope: !452)
!459 = !DILocation(line: 341, column: 6, scope: !452)
!460 = !DILocation(line: 341, column: 29, scope: !452)
!461 = !DILocation(line: 341, column: 34, scope: !452)
!462 = !DILocation(line: 342, column: 12, scope: !452)
!463 = !DILocation(line: 342, column: 6, scope: !452)
!464 = !DILocation(line: 342, column: 29, scope: !452)
!465 = !DILocation(line: 342, column: 33, scope: !452)
!466 = !DILocation(line: 343, column: 12, scope: !452)
!467 = !DILocation(line: 343, column: 6, scope: !452)
!468 = !DILocation(line: 343, column: 29, scope: !452)
!469 = !DILocation(line: 339, column: 11, scope: !470)
!470 = !DILexicalBlockFile(scope: !442, file: !1, discriminator: 1)
!471 = !DILocation(line: 344, column: 16, scope: !472)
!472 = distinct !DILexicalBlock(scope: !452, file: !1, line: 343, column: 35)
!473 = !DILocation(line: 345, column: 2, scope: !472)
!474 = !DILocation(line: 351, column: 6, scope: !475)
!475 = distinct !DILexicalBlock(scope: !148, file: !1, line: 351, column: 6)
!476 = !DILocation(line: 351, column: 6, scope: !148)
!477 = !DILocalVariable(name: "new_block_size", scope: !478, file: !1, line: 352, type: !16)
!478 = distinct !DILexicalBlock(scope: !475, file: !1, line: 351, column: 20)
!479 = !DILocation(line: 352, column: 10, scope: !478)
!480 = !DILocation(line: 353, column: 3, scope: !478)
!481 = !DILocation(line: 353, column: 10, scope: !482)
!482 = !DILexicalBlockFile(scope: !478, file: !1, discriminator: 1)
!483 = !DILocation(line: 353, column: 27, scope: !482)
!484 = !DILocation(line: 353, column: 33, scope: !482)
!485 = !DILocation(line: 353, column: 25, scope: !482)
!486 = !DILocation(line: 354, column: 7, scope: !478)
!487 = !DILocation(line: 354, column: 10, scope: !482)
!488 = !DILocation(line: 354, column: 25, scope: !482)
!489 = !DILocation(line: 353, column: 3, scope: !490)
!490 = !DILexicalBlockFile(scope: !478, file: !1, discriminator: 2)
!491 = !DILocation(line: 355, column: 19, scope: !478)
!492 = !DILocation(line: 353, column: 3, scope: !493)
!493 = !DILexicalBlockFile(scope: !478, file: !1, discriminator: 3)
!494 = !DILocation(line: 356, column: 22, scope: !478)
!495 = !DILocation(line: 356, column: 3, scope: !478)
!496 = !DILocation(line: 356, column: 9, scope: !478)
!497 = !DILocation(line: 356, column: 20, scope: !478)
!498 = !DILocation(line: 357, column: 2, scope: !478)
!499 = !DILocation(line: 358, column: 18, scope: !148)
!500 = !DILocation(line: 358, column: 24, scope: !148)
!501 = !DILocation(line: 358, column: 11, scope: !148)
!502 = !DILocation(line: 358, column: 9, scope: !148)
!503 = !DILocation(line: 359, column: 6, scope: !504)
!504 = distinct !DILexicalBlock(scope: !148, file: !1, line: 359, column: 6)
!505 = !DILocation(line: 359, column: 13, scope: !504)
!506 = !DILocation(line: 359, column: 6, scope: !148)
!507 = !DILocation(line: 360, column: 21, scope: !508)
!508 = distinct !DILexicalBlock(scope: !504, file: !1, line: 359, column: 22)
!509 = !DILocation(line: 360, column: 3, scope: !508)
!510 = !DILocation(line: 361, column: 3, scope: !508)
!511 = !DILocation(line: 363, column: 17, scope: !148)
!512 = !DILocation(line: 363, column: 2, scope: !148)
!513 = !DILocation(line: 363, column: 8, scope: !148)
!514 = !DILocation(line: 363, column: 15, scope: !148)
!515 = !DILocation(line: 364, column: 13, scope: !148)
!516 = !DILocation(line: 364, column: 2, scope: !148)
!517 = !DILocation(line: 364, column: 8, scope: !148)
!518 = !DILocation(line: 364, column: 11, scope: !148)
!519 = !DILocation(line: 366, column: 21, scope: !148)
!520 = !DILocation(line: 366, column: 2, scope: !148)
!521 = !DILocation(line: 366, column: 8, scope: !148)
!522 = !DILocation(line: 366, column: 16, scope: !148)
!523 = !DILocation(line: 369, column: 6, scope: !524)
!524 = distinct !DILexicalBlock(scope: !148, file: !1, line: 369, column: 6)
!525 = !DILocation(line: 369, column: 6, scope: !148)
!526 = !DILocation(line: 370, column: 3, scope: !524)
!527 = !DILocation(line: 370, column: 9, scope: !524)
!528 = !DILocation(line: 370, column: 19, scope: !524)
!529 = !DILocation(line: 372, column: 2, scope: !148)
!530 = !DILocation(line: 378, column: 6, scope: !531)
!531 = distinct !DILexicalBlock(scope: !148, file: !1, line: 378, column: 6)
!532 = !DILocation(line: 378, column: 9, scope: !531)
!533 = !DILocation(line: 378, column: 15, scope: !531)
!534 = !DILocation(line: 378, column: 18, scope: !535)
!535 = !DILexicalBlockFile(scope: !531, file: !1, discriminator: 1)
!536 = !DILocation(line: 378, column: 21, scope: !535)
!537 = !DILocation(line: 378, column: 6, scope: !535)
!538 = !DILocation(line: 379, column: 9, scope: !531)
!539 = !DILocation(line: 379, column: 3, scope: !531)
!540 = !DILocation(line: 380, column: 2, scope: !148)
!541 = !DILocation(line: 381, column: 1, scope: !148)
!542 = !DILocalVariable(name: "a", arg: 1, scope: !151, file: !1, line: 384, type: !43)
!543 = !DILocation(line: 384, column: 27, scope: !151)
!544 = !DILocalVariable(name: "client_data", arg: 2, scope: !151, file: !1, line: 384, type: !9)
!545 = !DILocation(line: 384, column: 36, scope: !151)
!546 = !DILocalVariable(name: "buff", arg: 3, scope: !151, file: !1, line: 384, type: !92)
!547 = !DILocation(line: 384, column: 62, scope: !151)
!548 = !DILocalVariable(name: "mine", scope: !151, file: !1, line: 386, type: !10)
!549 = !DILocation(line: 386, column: 25, scope: !151)
!550 = !DILocation(line: 386, column: 57, scope: !151)
!551 = !DILocation(line: 386, column: 32, scope: !151)
!552 = !DILocalVariable(name: "bytes_read", scope: !151, file: !1, line: 387, type: !70)
!553 = !DILocation(line: 387, column: 10, scope: !151)
!554 = !DILocation(line: 402, column: 10, scope: !151)
!555 = !DILocation(line: 402, column: 16, scope: !151)
!556 = !DILocation(line: 402, column: 3, scope: !151)
!557 = !DILocation(line: 402, column: 8, scope: !151)
!558 = !DILocation(line: 403, column: 2, scope: !151)
!559 = !DILocation(line: 404, column: 21, scope: !560)
!560 = distinct !DILexicalBlock(scope: !561, file: !1, line: 403, column: 11)
!561 = distinct !DILexicalBlock(scope: !562, file: !1, line: 403, column: 2)
!562 = distinct !DILexicalBlock(scope: !151, file: !1, line: 403, column: 2)
!563 = !DILocation(line: 404, column: 27, scope: !560)
!564 = !DILocation(line: 404, column: 31, scope: !560)
!565 = !DILocation(line: 404, column: 37, scope: !560)
!566 = !DILocation(line: 404, column: 45, scope: !560)
!567 = !DILocation(line: 404, column: 51, scope: !560)
!568 = !DILocation(line: 404, column: 16, scope: !560)
!569 = !DILocation(line: 404, column: 14, scope: !560)
!570 = !DILocation(line: 405, column: 7, scope: !571)
!571 = distinct !DILexicalBlock(scope: !560, file: !1, line: 405, column: 7)
!572 = !DILocation(line: 405, column: 18, scope: !571)
!573 = !DILocation(line: 405, column: 7, scope: !560)
!574 = !DILocation(line: 406, column: 8, scope: !575)
!575 = distinct !DILexicalBlock(scope: !576, file: !1, line: 406, column: 8)
!576 = distinct !DILexicalBlock(scope: !571, file: !1, line: 405, column: 23)
!577 = !DILocation(line: 406, column: 14, scope: !575)
!578 = !DILocation(line: 406, column: 8, scope: !576)
!579 = !DILocation(line: 407, column: 5, scope: !575)
!580 = !DILocation(line: 408, column: 13, scope: !581)
!581 = distinct !DILexicalBlock(scope: !575, file: !1, line: 408, column: 13)
!582 = !DILocation(line: 408, column: 19, scope: !581)
!583 = !DILocation(line: 408, column: 33, scope: !581)
!584 = !DILocation(line: 408, column: 13, scope: !575)
!585 = !DILocation(line: 409, column: 23, scope: !581)
!586 = !DILocation(line: 409, column: 26, scope: !581)
!587 = !DILocation(line: 409, column: 5, scope: !588)
!588 = !DILexicalBlockFile(scope: !581, file: !1, discriminator: 1)
!589 = !DILocation(line: 409, column: 5, scope: !581)
!590 = !DILocation(line: 411, column: 13, scope: !591)
!591 = distinct !DILexicalBlock(scope: !581, file: !1, line: 411, column: 13)
!592 = !DILocation(line: 411, column: 19, scope: !591)
!593 = !DILocation(line: 411, column: 33, scope: !591)
!594 = !DILocation(line: 411, column: 13, scope: !581)
!595 = !DILocation(line: 412, column: 23, scope: !591)
!596 = !DILocation(line: 412, column: 26, scope: !591)
!597 = !DILocation(line: 413, column: 31, scope: !591)
!598 = !DILocation(line: 413, column: 37, scope: !591)
!599 = !DILocation(line: 413, column: 46, scope: !591)
!600 = !DILocation(line: 412, column: 5, scope: !601)
!601 = !DILexicalBlockFile(scope: !591, file: !1, discriminator: 1)
!602 = !DILocation(line: 412, column: 5, scope: !591)
!603 = !DILocation(line: 415, column: 23, scope: !591)
!604 = !DILocation(line: 415, column: 26, scope: !591)
!605 = !DILocation(line: 416, column: 31, scope: !591)
!606 = !DILocation(line: 416, column: 37, scope: !591)
!607 = !DILocation(line: 416, column: 46, scope: !591)
!608 = !DILocation(line: 415, column: 5, scope: !601)
!609 = !DILocation(line: 417, column: 3, scope: !576)
!610 = !DILocation(line: 418, column: 11, scope: !560)
!611 = !DILocation(line: 418, column: 3, scope: !560)
!612 = !DILocalVariable(name: "a", arg: 1, scope: !154, file: !1, line: 490, type: !43)
!613 = !DILocation(line: 490, column: 27, scope: !154)
!614 = !DILocalVariable(name: "client_data", arg: 2, scope: !154, file: !1, line: 490, type: !9)
!615 = !DILocation(line: 490, column: 36, scope: !154)
!616 = !DILocalVariable(name: "request", arg: 3, scope: !154, file: !1, line: 490, type: !80)
!617 = !DILocation(line: 490, column: 57, scope: !154)
!618 = !DILocalVariable(name: "mine", scope: !154, file: !1, line: 492, type: !10)
!619 = !DILocation(line: 492, column: 25, scope: !154)
!620 = !DILocation(line: 492, column: 57, scope: !154)
!621 = !DILocation(line: 492, column: 32, scope: !154)
!622 = !DILocation(line: 495, column: 6, scope: !623)
!623 = distinct !DILexicalBlock(scope: !154, file: !1, line: 495, column: 6)
!624 = !DILocation(line: 495, column: 12, scope: !623)
!625 = !DILocation(line: 495, column: 6, scope: !154)
!626 = !DILocation(line: 496, column: 27, scope: !623)
!627 = !DILocation(line: 496, column: 30, scope: !623)
!628 = !DILocation(line: 496, column: 43, scope: !623)
!629 = !DILocation(line: 496, column: 11, scope: !623)
!630 = !DILocation(line: 496, column: 3, scope: !623)
!631 = !DILocation(line: 499, column: 2, scope: !154)
!632 = !DILocation(line: 500, column: 1, scope: !154)
!633 = !DILocalVariable(name: "a", arg: 1, scope: !161, file: !1, line: 569, type: !43)
!634 = !DILocation(line: 569, column: 28, scope: !161)
!635 = !DILocalVariable(name: "client_data", arg: 2, scope: !161, file: !1, line: 569, type: !9)
!636 = !DILocation(line: 569, column: 37, scope: !161)
!637 = !DILocalVariable(name: "mine", scope: !161, file: !1, line: 571, type: !10)
!638 = !DILocation(line: 571, column: 25, scope: !161)
!639 = !DILocation(line: 571, column: 57, scope: !161)
!640 = !DILocation(line: 571, column: 32, scope: !161)
!641 = !DILocation(line: 572, column: 14, scope: !161)
!642 = !DILocation(line: 572, column: 17, scope: !161)
!643 = !DILocation(line: 572, column: 2, scope: !161)
!644 = !DILocation(line: 573, column: 7, scope: !161)
!645 = !DILocation(line: 573, column: 2, scope: !161)
!646 = !DILocation(line: 574, column: 2, scope: !161)
!647 = !DILocalVariable(name: "a", arg: 1, scope: !163, file: !1, line: 578, type: !43)
!648 = !DILocation(line: 578, column: 29, scope: !163)
!649 = !DILocalVariable(name: "client_data1", arg: 2, scope: !163, file: !1, line: 578, type: !9)
!650 = !DILocation(line: 578, column: 38, scope: !163)
!651 = !DILocalVariable(name: "client_data2", arg: 3, scope: !163, file: !1, line: 578, type: !9)
!652 = !DILocation(line: 578, column: 58, scope: !163)
!653 = !DILocation(line: 580, column: 14, scope: !163)
!654 = !DILocation(line: 580, column: 17, scope: !163)
!655 = !DILocation(line: 580, column: 2, scope: !163)
!656 = !DILocation(line: 581, column: 19, scope: !163)
!657 = !DILocation(line: 581, column: 22, scope: !163)
!658 = !DILocation(line: 581, column: 9, scope: !163)
!659 = !DILocation(line: 581, column: 2, scope: !163)
!660 = !DILocalVariable(name: "a", arg: 1, scope: !158, file: !1, line: 506, type: !43)
!661 = !DILocation(line: 506, column: 27, scope: !158)
!662 = !DILocalVariable(name: "client_data", arg: 2, scope: !158, file: !1, line: 506, type: !9)
!663 = !DILocation(line: 506, column: 36, scope: !158)
!664 = !DILocalVariable(name: "request", arg: 3, scope: !158, file: !1, line: 506, type: !80)
!665 = !DILocation(line: 506, column: 57, scope: !158)
!666 = !DILocalVariable(name: "whence", arg: 4, scope: !158, file: !1, line: 506, type: !14)
!667 = !DILocation(line: 506, column: 70, scope: !158)
!668 = !DILocalVariable(name: "mine", scope: !158, file: !1, line: 508, type: !10)
!669 = !DILocation(line: 508, column: 25, scope: !158)
!670 = !DILocation(line: 508, column: 57, scope: !158)
!671 = !DILocation(line: 508, column: 32, scope: !158)
!672 = !DILocalVariable(name: "r", scope: !158, file: !1, line: 509, type: !80)
!673 = !DILocation(line: 509, column: 10, scope: !158)
!674 = !DILocation(line: 513, column: 12, scope: !158)
!675 = !DILocation(line: 513, column: 18, scope: !158)
!676 = !DILocation(line: 513, column: 22, scope: !158)
!677 = !DILocation(line: 513, column: 31, scope: !158)
!678 = !DILocation(line: 513, column: 6, scope: !158)
!679 = !DILocation(line: 513, column: 4, scope: !158)
!680 = !DILocation(line: 514, column: 6, scope: !681)
!681 = distinct !DILexicalBlock(scope: !158, file: !1, line: 514, column: 6)
!682 = !DILocation(line: 514, column: 8, scope: !681)
!683 = !DILocation(line: 514, column: 6, scope: !158)
!684 = !DILocation(line: 515, column: 10, scope: !681)
!685 = !DILocation(line: 515, column: 3, scope: !681)
!686 = !DILocation(line: 518, column: 6, scope: !687)
!687 = distinct !DILexicalBlock(scope: !158, file: !1, line: 518, column: 6)
!688 = !DILocation(line: 518, column: 12, scope: !687)
!689 = !DILocation(line: 518, column: 26, scope: !687)
!690 = !DILocation(line: 518, column: 6, scope: !158)
!691 = !DILocation(line: 519, column: 21, scope: !687)
!692 = !DILocation(line: 519, column: 24, scope: !687)
!693 = !DILocation(line: 519, column: 3, scope: !694)
!694 = !DILexicalBlockFile(scope: !687, file: !1, discriminator: 1)
!695 = !DILocation(line: 519, column: 3, scope: !687)
!696 = !DILocation(line: 520, column: 11, scope: !697)
!697 = distinct !DILexicalBlock(scope: !687, file: !1, line: 520, column: 11)
!698 = !DILocation(line: 520, column: 17, scope: !697)
!699 = !DILocation(line: 520, column: 31, scope: !697)
!700 = !DILocation(line: 520, column: 11, scope: !687)
!701 = !DILocation(line: 521, column: 21, scope: !697)
!702 = !DILocation(line: 521, column: 24, scope: !697)
!703 = !DILocation(line: 522, column: 7, scope: !697)
!704 = !DILocation(line: 522, column: 13, scope: !697)
!705 = !DILocation(line: 522, column: 22, scope: !697)
!706 = !DILocation(line: 521, column: 3, scope: !707)
!707 = !DILexicalBlockFile(scope: !697, file: !1, discriminator: 1)
!708 = !DILocation(line: 521, column: 3, scope: !697)
!709 = !DILocation(line: 524, column: 21, scope: !697)
!710 = !DILocation(line: 524, column: 24, scope: !697)
!711 = !DILocation(line: 525, column: 7, scope: !697)
!712 = !DILocation(line: 525, column: 13, scope: !697)
!713 = !DILocation(line: 525, column: 22, scope: !697)
!714 = !DILocation(line: 524, column: 3, scope: !707)
!715 = !DILocation(line: 526, column: 2, scope: !158)
!716 = !DILocation(line: 527, column: 1, scope: !158)
!717 = !DILocalVariable(name: "a", arg: 1, scope: !143, file: !1, line: 159, type: !43)
!718 = !DILocation(line: 159, column: 46, scope: !143)
!719 = !DILocalVariable(name: "wfilename", arg: 2, scope: !143, file: !1, line: 159, type: !146)
!720 = !DILocation(line: 159, column: 64, scope: !143)
!721 = !DILocalVariable(name: "block_size", arg: 3, scope: !143, file: !1, line: 160, type: !16)
!722 = !DILocation(line: 160, column: 12, scope: !143)
!723 = !DILocalVariable(name: "mine", scope: !143, file: !1, line: 162, type: !10)
!724 = !DILocation(line: 162, column: 25, scope: !143)
!725 = !DILocation(line: 163, column: 26, scope: !143)
!726 = !DILocation(line: 163, column: 19, scope: !143)
!727 = !DILocation(line: 163, column: 37, scope: !143)
!728 = !DILocation(line: 163, column: 17, scope: !143)
!729 = !DILocation(line: 162, column: 57, scope: !143)
!730 = !DILocation(line: 162, column: 32, scope: !143)
!731 = !DILocation(line: 164, column: 7, scope: !732)
!732 = distinct !DILexicalBlock(scope: !143, file: !1, line: 164, column: 6)
!733 = !DILocation(line: 164, column: 6, scope: !143)
!734 = !DILocation(line: 166, column: 21, scope: !735)
!735 = distinct !DILexicalBlock(scope: !732, file: !1, line: 165, column: 2)
!736 = !DILocation(line: 166, column: 3, scope: !735)
!737 = !DILocation(line: 167, column: 3, scope: !735)
!738 = !DILocation(line: 169, column: 2, scope: !143)
!739 = !DILocation(line: 169, column: 8, scope: !143)
!740 = !DILocation(line: 169, column: 11, scope: !143)
!741 = !DILocation(line: 170, column: 21, scope: !143)
!742 = !DILocation(line: 170, column: 2, scope: !143)
!743 = !DILocation(line: 170, column: 8, scope: !143)
!744 = !DILocation(line: 170, column: 19, scope: !143)
!745 = !DILocation(line: 172, column: 6, scope: !746)
!746 = distinct !DILexicalBlock(scope: !143, file: !1, line: 172, column: 6)
!747 = !DILocation(line: 172, column: 16, scope: !746)
!748 = !DILocation(line: 172, column: 24, scope: !746)
!749 = !DILocation(line: 172, column: 27, scope: !750)
!750 = !DILexicalBlockFile(scope: !746, file: !1, discriminator: 1)
!751 = !DILocation(line: 172, column: 40, scope: !750)
!752 = !DILocation(line: 172, column: 6, scope: !750)
!753 = !DILocation(line: 173, column: 3, scope: !754)
!754 = distinct !DILexicalBlock(scope: !746, file: !1, line: 172, column: 50)
!755 = !DILocation(line: 173, column: 9, scope: !754)
!756 = !DILocation(line: 173, column: 23, scope: !754)
!757 = !DILocation(line: 174, column: 2, scope: !754)
!758 = !DILocalVariable(name: "fn", scope: !759, file: !1, line: 184, type: !118)
!759 = distinct !DILexicalBlock(scope: !746, file: !1, line: 174, column: 9)
!760 = !DILocation(line: 184, column: 25, scope: !759)
!761 = !DILocation(line: 186, column: 3, scope: !759)
!762 = !DILocation(line: 186, column: 3, scope: !763)
!763 = !DILexicalBlockFile(scope: !764, file: !1, discriminator: 1)
!764 = distinct !DILexicalBlock(scope: !759, file: !1, line: 186, column: 3)
!765 = !DILocation(line: 187, column: 43, scope: !766)
!766 = distinct !DILexicalBlock(scope: !759, file: !1, line: 187, column: 7)
!767 = !DILocation(line: 188, column: 14, scope: !766)
!768 = !DILocation(line: 188, column: 7, scope: !766)
!769 = !DILocation(line: 187, column: 7, scope: !766)
!770 = !DILocation(line: 188, column: 26, scope: !766)
!771 = !DILocation(line: 187, column: 7, scope: !759)
!772 = !DILocation(line: 189, column: 8, scope: !773)
!773 = distinct !DILexicalBlock(scope: !774, file: !1, line: 189, column: 8)
!774 = distinct !DILexicalBlock(scope: !766, file: !1, line: 188, column: 32)
!775 = !DILocation(line: 189, column: 14, scope: !773)
!776 = !DILocation(line: 189, column: 8, scope: !774)
!777 = !DILocation(line: 190, column: 23, scope: !773)
!778 = !DILocation(line: 190, column: 26, scope: !773)
!779 = !DILocation(line: 190, column: 5, scope: !780)
!780 = !DILexicalBlockFile(scope: !773, file: !1, discriminator: 1)
!781 = !DILocation(line: 190, column: 5, scope: !773)
!782 = !DILocation(line: 193, column: 23, scope: !773)
!783 = !DILocation(line: 193, column: 5, scope: !773)
!784 = !DILocation(line: 196, column: 4, scope: !774)
!785 = !DILocation(line: 197, column: 9, scope: !774)
!786 = !DILocation(line: 197, column: 4, scope: !774)
!787 = !DILocation(line: 198, column: 4, scope: !774)
!788 = !DILocation(line: 200, column: 3, scope: !759)
!789 = !DILocation(line: 200, column: 9, scope: !759)
!790 = !DILocation(line: 200, column: 23, scope: !759)
!791 = !DILocation(line: 201, column: 10, scope: !759)
!792 = !DILocation(line: 201, column: 16, scope: !759)
!793 = !DILocation(line: 201, column: 25, scope: !759)
!794 = !DILocation(line: 201, column: 31, scope: !759)
!795 = !DILocation(line: 201, column: 3, scope: !759)
!796 = !DILocation(line: 202, column: 3, scope: !759)
!797 = !DILocation(line: 205, column: 40, scope: !798)
!798 = distinct !DILexicalBlock(scope: !143, file: !1, line: 205, column: 6)
!799 = !DILocation(line: 205, column: 43, scope: !798)
!800 = !DILocation(line: 205, column: 6, scope: !798)
!801 = !DILocation(line: 205, column: 49, scope: !798)
!802 = !DILocation(line: 205, column: 6, scope: !143)
!803 = !DILocation(line: 206, column: 3, scope: !798)
!804 = !DILocation(line: 207, column: 33, scope: !143)
!805 = !DILocation(line: 207, column: 2, scope: !143)
!806 = !DILocation(line: 208, column: 33, scope: !143)
!807 = !DILocation(line: 208, column: 2, scope: !143)
!808 = !DILocation(line: 209, column: 33, scope: !143)
!809 = !DILocation(line: 209, column: 2, scope: !143)
!810 = !DILocation(line: 210, column: 34, scope: !143)
!811 = !DILocation(line: 210, column: 2, scope: !143)
!812 = !DILocation(line: 211, column: 35, scope: !143)
!813 = !DILocation(line: 211, column: 2, scope: !143)
!814 = !DILocation(line: 212, column: 33, scope: !143)
!815 = !DILocation(line: 212, column: 2, scope: !143)
!816 = !DILocation(line: 214, column: 29, scope: !143)
!817 = !DILocation(line: 214, column: 10, scope: !143)
!818 = !DILocation(line: 214, column: 2, scope: !143)
!819 = !DILocation(line: 215, column: 1, scope: !143)
!820 = !DILocalVariable(name: "a", arg: 1, scope: !157, file: !1, line: 443, type: !43)
!821 = !DILocation(line: 443, column: 33, scope: !157)
!822 = !DILocalVariable(name: "client_data", arg: 2, scope: !157, file: !1, line: 443, type: !9)
!823 = !DILocation(line: 443, column: 42, scope: !157)
!824 = !DILocalVariable(name: "request", arg: 3, scope: !157, file: !1, line: 443, type: !80)
!825 = !DILocation(line: 443, column: 63, scope: !157)
!826 = !DILocalVariable(name: "mine", scope: !157, file: !1, line: 445, type: !10)
!827 = !DILocation(line: 445, column: 25, scope: !157)
!828 = !DILocation(line: 445, column: 57, scope: !157)
!829 = !DILocation(line: 445, column: 32, scope: !157)
!830 = !DILocalVariable(name: "old_offset", scope: !157, file: !1, line: 450, type: !831)
!831 = !DIDerivedType(tag: DW_TAG_typedef, name: "off_t", file: !22, line: 74, baseType: !343)
!832 = !DILocation(line: 450, column: 8, scope: !157)
!833 = !DILocalVariable(name: "new_offset", scope: !157, file: !1, line: 450, type: !831)
!834 = !DILocation(line: 450, column: 20, scope: !157)
!835 = !DILocation(line: 460, column: 26, scope: !836)
!836 = distinct !DILexicalBlock(scope: !157, file: !1, line: 460, column: 6)
!837 = !DILocation(line: 460, column: 32, scope: !836)
!838 = !DILocation(line: 460, column: 20, scope: !836)
!839 = !DILocation(line: 460, column: 18, scope: !836)
!840 = !DILocation(line: 460, column: 50, scope: !836)
!841 = !DILocation(line: 460, column: 55, scope: !836)
!842 = !DILocation(line: 461, column: 26, scope: !836)
!843 = !DILocation(line: 461, column: 32, scope: !836)
!844 = !DILocation(line: 461, column: 36, scope: !836)
!845 = !DILocation(line: 461, column: 20, scope: !836)
!846 = !DILocation(line: 461, column: 18, scope: !836)
!847 = !DILocation(line: 461, column: 56, scope: !836)
!848 = !DILocation(line: 460, column: 6, scope: !849)
!849 = !DILexicalBlockFile(scope: !157, file: !1, discriminator: 1)
!850 = !DILocation(line: 462, column: 11, scope: !836)
!851 = !DILocation(line: 462, column: 24, scope: !836)
!852 = !DILocation(line: 462, column: 22, scope: !836)
!853 = !DILocation(line: 462, column: 3, scope: !836)
!854 = !DILocation(line: 465, column: 2, scope: !157)
!855 = !DILocation(line: 465, column: 8, scope: !157)
!856 = !DILocation(line: 465, column: 18, scope: !157)
!857 = !DILocation(line: 468, column: 6, scope: !858)
!858 = distinct !DILexicalBlock(scope: !157, file: !1, line: 468, column: 6)
!859 = !DILocation(line: 468, column: 12, scope: !858)
!860 = !DILocation(line: 468, column: 6, scope: !157)
!861 = !DILocation(line: 469, column: 3, scope: !858)
!862 = !DILocation(line: 472, column: 6, scope: !863)
!863 = distinct !DILexicalBlock(scope: !157, file: !1, line: 472, column: 6)
!864 = !DILocation(line: 472, column: 12, scope: !863)
!865 = !DILocation(line: 472, column: 26, scope: !863)
!866 = !DILocation(line: 472, column: 6, scope: !157)
!867 = !DILocation(line: 473, column: 21, scope: !863)
!868 = !DILocation(line: 473, column: 24, scope: !863)
!869 = !DILocation(line: 473, column: 3, scope: !870)
!870 = !DILexicalBlockFile(scope: !863, file: !1, discriminator: 1)
!871 = !DILocation(line: 473, column: 3, scope: !863)
!872 = !DILocation(line: 474, column: 11, scope: !873)
!873 = distinct !DILexicalBlock(scope: !863, file: !1, line: 474, column: 11)
!874 = !DILocation(line: 474, column: 17, scope: !873)
!875 = !DILocation(line: 474, column: 31, scope: !873)
!876 = !DILocation(line: 474, column: 11, scope: !863)
!877 = !DILocation(line: 475, column: 21, scope: !873)
!878 = !DILocation(line: 475, column: 24, scope: !873)
!879 = !DILocation(line: 476, column: 7, scope: !873)
!880 = !DILocation(line: 476, column: 13, scope: !873)
!881 = !DILocation(line: 476, column: 22, scope: !873)
!882 = !DILocation(line: 475, column: 3, scope: !883)
!883 = !DILexicalBlockFile(scope: !873, file: !1, discriminator: 1)
!884 = !DILocation(line: 475, column: 3, scope: !873)
!885 = !DILocation(line: 478, column: 21, scope: !873)
!886 = !DILocation(line: 478, column: 24, scope: !873)
!887 = !DILocation(line: 479, column: 7, scope: !873)
!888 = !DILocation(line: 479, column: 13, scope: !873)
!889 = !DILocation(line: 479, column: 22, scope: !873)
!890 = !DILocation(line: 478, column: 3, scope: !883)
!891 = !DILocation(line: 480, column: 2, scope: !157)
!892 = !DILocation(line: 481, column: 1, scope: !157)
!893 = !DILocalVariable(name: "a", arg: 1, scope: !162, file: !1, line: 530, type: !43)
!894 = !DILocation(line: 530, column: 29, scope: !162)
!895 = !DILocalVariable(name: "client_data", arg: 2, scope: !162, file: !1, line: 530, type: !9)
!896 = !DILocation(line: 530, column: 38, scope: !162)
!897 = !DILocalVariable(name: "mine", scope: !162, file: !1, line: 532, type: !10)
!898 = !DILocation(line: 532, column: 25, scope: !162)
!899 = !DILocation(line: 532, column: 57, scope: !162)
!900 = !DILocation(line: 532, column: 32, scope: !162)
!901 = !DILocation(line: 534, column: 8, scope: !162)
!902 = !DILocation(line: 537, column: 6, scope: !903)
!903 = distinct !DILexicalBlock(scope: !162, file: !1, line: 537, column: 6)
!904 = !DILocation(line: 537, column: 12, scope: !903)
!905 = !DILocation(line: 537, column: 15, scope: !903)
!906 = !DILocation(line: 537, column: 6, scope: !162)
!907 = !DILocation(line: 549, column: 8, scope: !908)
!908 = distinct !DILexicalBlock(scope: !909, file: !1, line: 549, column: 7)
!909 = distinct !DILexicalBlock(scope: !903, file: !1, line: 537, column: 21)
!910 = !DILocation(line: 550, column: 7, scope: !908)
!911 = !DILocation(line: 550, column: 11, scope: !912)
!912 = !DILexicalBlockFile(scope: !908, file: !1, discriminator: 1)
!913 = !DILocation(line: 551, column: 7, scope: !908)
!914 = !DILocation(line: 551, column: 11, scope: !912)
!915 = !DILocation(line: 549, column: 7, scope: !916)
!916 = !DILexicalBlockFile(scope: !909, file: !1, discriminator: 1)
!917 = !DILocalVariable(name: "bytesRead", scope: !918, file: !1, line: 552, type: !70)
!918 = distinct !DILexicalBlock(scope: !908, file: !1, line: 551, column: 35)
!919 = !DILocation(line: 552, column: 12, scope: !918)
!920 = !DILocation(line: 553, column: 4, scope: !918)
!921 = !DILocation(line: 554, column: 22, scope: !922)
!922 = distinct !DILexicalBlock(scope: !918, file: !1, line: 553, column: 7)
!923 = !DILocation(line: 554, column: 28, scope: !922)
!924 = !DILocation(line: 554, column: 32, scope: !922)
!925 = !DILocation(line: 554, column: 38, scope: !922)
!926 = !DILocation(line: 555, column: 9, scope: !922)
!927 = !DILocation(line: 555, column: 15, scope: !922)
!928 = !DILocation(line: 554, column: 17, scope: !922)
!929 = !DILocation(line: 554, column: 15, scope: !922)
!930 = !DILocation(line: 556, column: 4, scope: !922)
!931 = !DILocation(line: 556, column: 13, scope: !932)
!932 = !DILexicalBlockFile(scope: !918, file: !1, discriminator: 1)
!933 = !DILocation(line: 556, column: 23, scope: !932)
!934 = !DILocation(line: 556, column: 4, scope: !932)
!935 = !DILocation(line: 557, column: 3, scope: !918)
!936 = !DILocation(line: 559, column: 7, scope: !937)
!937 = distinct !DILexicalBlock(scope: !909, file: !1, line: 559, column: 7)
!938 = !DILocation(line: 559, column: 13, scope: !937)
!939 = !DILocation(line: 559, column: 27, scope: !937)
!940 = !DILocation(line: 559, column: 7, scope: !909)
!941 = !DILocation(line: 560, column: 10, scope: !937)
!942 = !DILocation(line: 560, column: 16, scope: !937)
!943 = !DILocation(line: 560, column: 4, scope: !937)
!944 = !DILocation(line: 561, column: 2, scope: !909)
!945 = !DILocation(line: 562, column: 7, scope: !162)
!946 = !DILocation(line: 562, column: 13, scope: !162)
!947 = !DILocation(line: 562, column: 2, scope: !162)
!948 = !DILocation(line: 563, column: 2, scope: !162)
!949 = !DILocation(line: 563, column: 8, scope: !162)
!950 = !DILocation(line: 563, column: 15, scope: !162)
!951 = !DILocation(line: 564, column: 2, scope: !162)
!952 = !DILocation(line: 564, column: 8, scope: !162)
!953 = !DILocation(line: 564, column: 11, scope: !162)
!954 = !DILocation(line: 565, column: 2, scope: !162)
