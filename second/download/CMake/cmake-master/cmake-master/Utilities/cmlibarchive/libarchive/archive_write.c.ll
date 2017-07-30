; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_entry = type opaque
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.archive_none = type { i64, i64, i8*, i8* }

@.str = private unnamed_addr constant [34 x i8] c"archive_write_set_bytes_per_block\00", align 1
@.str.1 = private unnamed_addr constant [34 x i8] c"archive_write_get_bytes_per_block\00", align 1
@.str.2 = private unnamed_addr constant [38 x i8] c"archive_write_set_bytes_in_last_block\00", align 1
@.str.3 = private unnamed_addr constant [38 x i8] c"archive_write_get_bytes_in_last_block\00", align 1
@.str.4 = private unnamed_addr constant [28 x i8] c"archive_write_set_skip_file\00", align 1
@.str.5 = private unnamed_addr constant [19 x i8] c"archive_write_open\00", align 1
@archive_write_vtable.av = internal global %struct.archive_vtable zeroinitializer, align 8
@archive_write_vtable.inited = internal global i32 0, align 4
@.str.6 = private unnamed_addr constant [20 x i8] c"archive_write_close\00", align 1
@.str.7 = private unnamed_addr constant [19 x i8] c"archive_write_free\00", align 1
@.str.8 = private unnamed_addr constant [21 x i8] c"archive_write_header\00", align 1
@.str.9 = private unnamed_addr constant [55 x i8] c"Format must be set before you can write to an archive.\00", align 1
@.str.10 = private unnamed_addr constant [28 x i8] c"Can't add archive to itself\00", align 1
@.str.11 = private unnamed_addr constant [27 x i8] c"archive_write_finish_entry\00", align 1
@.str.12 = private unnamed_addr constant [19 x i8] c"archive_write_data\00", align 1
@.str.13 = private unnamed_addr constant [41 x i8] c"Can't allocate data for output buffering\00", align 1
@.str.14 = private unnamed_addr constant [14 x i8] c"write overrun\00", align 1

; Function Attrs: nounwind uwtable
define %struct.archive* @archive_write_new() #0 !dbg !204 {
entry:
  %retval = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %nulls = alloca i8*, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !256, metadata !257), !dbg !258
  call void @llvm.dbg.declare(metadata i8** %nulls, metadata !259, metadata !257), !dbg !260
  %call = call noalias i8* @calloc(i64 1, i64 352) #6, !dbg !261
  %0 = bitcast i8* %call to %struct.archive_write*, !dbg !262
  store %struct.archive_write* %0, %struct.archive_write** %a, align 8, !dbg !263
  %1 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !264
  %cmp = icmp eq %struct.archive_write* %1, null, !dbg !266
  br i1 %cmp, label %if.then, label %if.end, !dbg !267

if.then:                                          ; preds = %entry
  store %struct.archive* null, %struct.archive** %retval, align 8, !dbg !268
  br label %return, !dbg !268

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !269
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 0, !dbg !270
  %magic = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 0, !dbg !271
  store i32 -1329217314, i32* %magic, align 8, !dbg !272
  %3 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !273
  %archive1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %3, i32 0, i32 0, !dbg !274
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive1, i32 0, i32 1, !dbg !275
  store i32 1, i32* %state, align 4, !dbg !276
  %call2 = call %struct.archive_vtable* @archive_write_vtable(), !dbg !277
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !278
  %archive3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 0, !dbg !279
  %vtable = getelementptr inbounds %struct.archive, %struct.archive* %archive3, i32 0, i32 2, !dbg !280
  store %struct.archive_vtable* %call2, %struct.archive_vtable** %vtable, align 8, !dbg !281
  %5 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !282
  %bytes_per_block = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 10, !dbg !283
  store i32 10240, i32* %bytes_per_block, align 8, !dbg !284
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !285
  %bytes_in_last_block = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 11, !dbg !286
  store i32 -1, i32* %bytes_in_last_block, align 4, !dbg !287
  %7 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !288
  %null_length = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 5, !dbg !289
  store i64 1024, i64* %null_length, align 8, !dbg !290
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !291
  %null_length4 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 5, !dbg !292
  %9 = load i64, i64* %null_length4, align 8, !dbg !292
  %call5 = call noalias i8* @calloc(i64 1, i64 %9) #6, !dbg !293
  store i8* %call5, i8** %nulls, align 8, !dbg !294
  %10 = load i8*, i8** %nulls, align 8, !dbg !295
  %cmp6 = icmp eq i8* %10, null, !dbg !297
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !298

if.then7:                                         ; preds = %if.end
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !299
  %12 = bitcast %struct.archive_write* %11 to i8*, !dbg !299
  call void @free(i8* %12) #6, !dbg !301
  store %struct.archive* null, %struct.archive** %retval, align 8, !dbg !302
  br label %return, !dbg !302

if.end8:                                          ; preds = %if.end
  %13 = load i8*, i8** %nulls, align 8, !dbg !303
  %14 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !304
  %nulls9 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %14, i32 0, i32 4, !dbg !305
  store i8* %13, i8** %nulls9, align 8, !dbg !306
  %15 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !307
  %archive10 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %15, i32 0, i32 0, !dbg !308
  store %struct.archive* %archive10, %struct.archive** %retval, align 8, !dbg !309
  br label %return, !dbg !309

return:                                           ; preds = %if.end8, %if.then7, %if.then
  %16 = load %struct.archive*, %struct.archive** %retval, align 8, !dbg !310
  ret %struct.archive* %16, !dbg !310
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #2

; Function Attrs: nounwind uwtable
define internal %struct.archive_vtable* @archive_write_vtable() #0 !dbg !232 {
entry:
  %0 = load i32, i32* @archive_write_vtable.inited, align 4, !dbg !311
  %tobool = icmp ne i32 %0, 0, !dbg !311
  br i1 %tobool, label %if.end, label %if.then, !dbg !313

if.then:                                          ; preds = %entry
  store i32 (%struct.archive*)* @_archive_write_close, i32 (%struct.archive*)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_write_vtable.av, i32 0, i32 0), align 8, !dbg !314
  store i64 (%struct.archive*, i32)* @_archive_filter_bytes, i64 (%struct.archive*, i32)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_write_vtable.av, i32 0, i32 10), align 8, !dbg !316
  store i32 (%struct.archive*, i32)* @_archive_filter_code, i32 (%struct.archive*, i32)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_write_vtable.av, i32 0, i32 11), align 8, !dbg !317
  store i8* (%struct.archive*, i32)* @_archive_filter_name, i8* (%struct.archive*, i32)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_write_vtable.av, i32 0, i32 12), align 8, !dbg !318
  store i32 (%struct.archive*)* @_archive_write_filter_count, i32 (%struct.archive*)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_write_vtable.av, i32 0, i32 9), align 8, !dbg !319
  store i32 (%struct.archive*)* @_archive_write_free, i32 (%struct.archive*)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_write_vtable.av, i32 0, i32 1), align 8, !dbg !320
  store i32 (%struct.archive*, %struct.archive_entry*)* @_archive_write_header, i32 (%struct.archive*, %struct.archive_entry*)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_write_vtable.av, i32 0, i32 2), align 8, !dbg !321
  store i32 (%struct.archive*)* @_archive_write_finish_entry, i32 (%struct.archive*)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_write_vtable.av, i32 0, i32 3), align 8, !dbg !322
  store i64 (%struct.archive*, i8*, i64)* @_archive_write_data, i64 (%struct.archive*, i8*, i64)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_write_vtable.av, i32 0, i32 4), align 8, !dbg !323
  store i32 1, i32* @archive_write_vtable.inited, align 4, !dbg !324
  br label %if.end, !dbg !325

if.end:                                           ; preds = %if.then, %entry
  ret %struct.archive_vtable* @archive_write_vtable.av, !dbg !326
}

; Function Attrs: nounwind
declare void @free(i8*) #2

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_bytes_per_block(%struct.archive* %_a, i32 %bytes_per_block) #0 !dbg !207 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %bytes_per_block.addr = alloca i32, align 4
  %a = alloca %struct.archive_write*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !327, metadata !257), !dbg !328
  store i32 %bytes_per_block, i32* %bytes_per_block.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %bytes_per_block.addr, metadata !329, metadata !257), !dbg !330
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !331, metadata !257), !dbg !332
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !333
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !334
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !332
  br label %do.body, !dbg !335

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !336, metadata !257), !dbg !338
  %2 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !339
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 0, !dbg !339
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1329217314, i32 1, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str, i32 0, i32 0)), !dbg !339
  store i32 %call, i32* %magic_test, align 4, !dbg !339
  %3 = load i32, i32* %magic_test, align 4, !dbg !339
  %cmp = icmp eq i32 %3, -30, !dbg !339
  br i1 %cmp, label %if.then, label %if.end, !dbg !339

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !341
  br label %return, !dbg !341

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !344

do.end:                                           ; preds = %if.end
  %4 = load i32, i32* %bytes_per_block.addr, align 4, !dbg !346
  %5 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !347
  %bytes_per_block1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 10, !dbg !348
  store i32 %4, i32* %bytes_per_block1, align 8, !dbg !349
  store i32 0, i32* %retval, align 4, !dbg !350
  br label %return, !dbg !350

return:                                           ; preds = %do.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !351
  ret i32 %6, !dbg !351
}

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #3

; Function Attrs: nounwind uwtable
define i32 @archive_write_get_bytes_per_block(%struct.archive* %_a) #0 !dbg !208 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !352, metadata !257), !dbg !353
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !354, metadata !257), !dbg !355
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !356
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !357
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !355
  br label %do.body, !dbg !358

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !359, metadata !257), !dbg !361
  %2 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !362
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 0, !dbg !362
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1329217314, i32 32767, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.1, i32 0, i32 0)), !dbg !362
  store i32 %call, i32* %magic_test, align 4, !dbg !362
  %3 = load i32, i32* %magic_test, align 4, !dbg !362
  %cmp = icmp eq i32 %3, -30, !dbg !362
  br i1 %cmp, label %if.then, label %if.end, !dbg !362

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !364
  br label %return, !dbg !364

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !367

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !369
  %bytes_per_block = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 10, !dbg !370
  %5 = load i32, i32* %bytes_per_block, align 8, !dbg !370
  store i32 %5, i32* %retval, align 4, !dbg !371
  br label %return, !dbg !371

return:                                           ; preds = %do.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !372
  ret i32 %6, !dbg !372
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_bytes_in_last_block(%struct.archive* %_a, i32 %bytes) #0 !dbg !209 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %bytes.addr = alloca i32, align 4
  %a = alloca %struct.archive_write*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !373, metadata !257), !dbg !374
  store i32 %bytes, i32* %bytes.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %bytes.addr, metadata !375, metadata !257), !dbg !376
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !377, metadata !257), !dbg !378
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !379
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !380
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !378
  br label %do.body, !dbg !381

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !382, metadata !257), !dbg !384
  %2 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !385
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 0, !dbg !385
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1329217314, i32 32767, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.2, i32 0, i32 0)), !dbg !385
  store i32 %call, i32* %magic_test, align 4, !dbg !385
  %3 = load i32, i32* %magic_test, align 4, !dbg !385
  %cmp = icmp eq i32 %3, -30, !dbg !385
  br i1 %cmp, label %if.then, label %if.end, !dbg !385

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !387
  br label %return, !dbg !387

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !390

do.end:                                           ; preds = %if.end
  %4 = load i32, i32* %bytes.addr, align 4, !dbg !392
  %5 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !393
  %bytes_in_last_block = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 11, !dbg !394
  store i32 %4, i32* %bytes_in_last_block, align 4, !dbg !395
  store i32 0, i32* %retval, align 4, !dbg !396
  br label %return, !dbg !396

return:                                           ; preds = %do.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !397
  ret i32 %6, !dbg !397
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_get_bytes_in_last_block(%struct.archive* %_a) #0 !dbg !210 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !398, metadata !257), !dbg !399
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !400, metadata !257), !dbg !401
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !402
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !403
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !401
  br label %do.body, !dbg !404

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !405, metadata !257), !dbg !407
  %2 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !408
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 0, !dbg !408
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1329217314, i32 32767, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.3, i32 0, i32 0)), !dbg !408
  store i32 %call, i32* %magic_test, align 4, !dbg !408
  %3 = load i32, i32* %magic_test, align 4, !dbg !408
  %cmp = icmp eq i32 %3, -30, !dbg !408
  br i1 %cmp, label %if.then, label %if.end, !dbg !408

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !410
  br label %return, !dbg !410

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !413

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !415
  %bytes_in_last_block = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 11, !dbg !416
  %5 = load i32, i32* %bytes_in_last_block, align 4, !dbg !416
  store i32 %5, i32* %retval, align 4, !dbg !417
  br label %return, !dbg !417

return:                                           ; preds = %do.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !418
  ret i32 %6, !dbg !418
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_skip_file(%struct.archive* %_a, i64 %d, i64 %i) #0 !dbg !211 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %d.addr = alloca i64, align 8
  %i.addr = alloca i64, align 8
  %a = alloca %struct.archive_write*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !419, metadata !257), !dbg !420
  store i64 %d, i64* %d.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %d.addr, metadata !421, metadata !257), !dbg !422
  store i64 %i, i64* %i.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %i.addr, metadata !423, metadata !257), !dbg !424
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !425, metadata !257), !dbg !426
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !427
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !428
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !426
  br label %do.body, !dbg !429

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !430, metadata !257), !dbg !432
  %2 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !433
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 0, !dbg !433
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1329217314, i32 32767, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.4, i32 0, i32 0)), !dbg !433
  store i32 %call, i32* %magic_test, align 4, !dbg !433
  %3 = load i32, i32* %magic_test, align 4, !dbg !433
  %cmp = icmp eq i32 %3, -30, !dbg !433
  br i1 %cmp, label %if.then, label %if.end, !dbg !433

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !435
  br label %return, !dbg !435

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !438

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !440
  %skip_file_set = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 1, !dbg !441
  store i32 1, i32* %skip_file_set, align 8, !dbg !442
  %5 = load i64, i64* %d.addr, align 8, !dbg !443
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !444
  %skip_file_dev = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 2, !dbg !445
  store i64 %5, i64* %skip_file_dev, align 8, !dbg !446
  %7 = load i64, i64* %i.addr, align 8, !dbg !447
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !448
  %skip_file_ino = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 3, !dbg !449
  store i64 %7, i64* %skip_file_ino, align 8, !dbg !450
  store i32 0, i32* %retval, align 4, !dbg !451
  br label %return, !dbg !451

return:                                           ; preds = %do.end, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !452
  ret i32 %9, !dbg !452
}

; Function Attrs: nounwind uwtable
define %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive* %_a) #0 !dbg !214 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %f = alloca %struct.archive_write_filter*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !453, metadata !257), !dbg !454
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !455, metadata !257), !dbg !456
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !457
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !458
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !456
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f, metadata !459, metadata !257), !dbg !460
  %call = call noalias i8* @calloc(i64 1, i64 96) #6, !dbg !461
  %2 = bitcast i8* %call to %struct.archive_write_filter*, !dbg !461
  store %struct.archive_write_filter* %2, %struct.archive_write_filter** %f, align 8, !dbg !462
  %3 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !463
  %4 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !464
  %archive = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %4, i32 0, i32 1, !dbg !465
  store %struct.archive* %3, %struct.archive** %archive, align 8, !dbg !466
  %5 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !467
  %filter_first = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 12, !dbg !469
  %6 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter_first, align 8, !dbg !469
  %cmp = icmp eq %struct.archive_write_filter* %6, null, !dbg !470
  br i1 %cmp, label %if.then, label %if.else, !dbg !471

if.then:                                          ; preds = %entry
  %7 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !472
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !473
  %filter_first1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 12, !dbg !474
  store %struct.archive_write_filter* %7, %struct.archive_write_filter** %filter_first1, align 8, !dbg !475
  br label %if.end, !dbg !473

if.else:                                          ; preds = %entry
  %9 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !476
  %10 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !477
  %filter_last = getelementptr inbounds %struct.archive_write, %struct.archive_write* %10, i32 0, i32 13, !dbg !478
  %11 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter_last, align 8, !dbg !478
  %next_filter = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %11, i32 0, i32 2, !dbg !479
  store %struct.archive_write_filter* %9, %struct.archive_write_filter** %next_filter, align 8, !dbg !480
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %12 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !481
  %13 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !482
  %filter_last2 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %13, i32 0, i32 13, !dbg !483
  store %struct.archive_write_filter* %12, %struct.archive_write_filter** %filter_last2, align 8, !dbg !484
  %14 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !485
  ret %struct.archive_write_filter* %14, !dbg !486
}

; Function Attrs: nounwind uwtable
define i32 @__archive_write_filter(%struct.archive_write_filter* %f, i8* %buff, i64 %length) #0 !dbg !217 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %buff.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %r = alloca i32, align 4
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !487, metadata !257), !dbg !488
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !489, metadata !257), !dbg !490
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !491, metadata !257), !dbg !492
  call void @llvm.dbg.declare(metadata i32* %r, metadata !493, metadata !257), !dbg !494
  %0 = load i64, i64* %length.addr, align 8, !dbg !495
  %cmp = icmp eq i64 %0, 0, !dbg !497
  br i1 %cmp, label %if.then, label %if.end, !dbg !498

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !499
  br label %return, !dbg !499

if.end:                                           ; preds = %entry
  %1 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !500
  %write = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %1, i32 0, i32 5, !dbg !502
  %2 = load i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*, i8*, i64)** %write, align 8, !dbg !502
  %cmp1 = icmp eq i32 (%struct.archive_write_filter*, i8*, i64)* %2, null, !dbg !503
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !504

if.then2:                                         ; preds = %if.end
  store i32 -30, i32* %retval, align 4, !dbg !505
  br label %return, !dbg !505

if.end3:                                          ; preds = %if.end
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !506
  %write4 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %3, i32 0, i32 5, !dbg !507
  %4 = load i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*, i8*, i64)** %write4, align 8, !dbg !507
  %5 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !508
  %6 = load i8*, i8** %buff.addr, align 8, !dbg !509
  %7 = load i64, i64* %length.addr, align 8, !dbg !510
  %call = call i32 %4(%struct.archive_write_filter* %5, i8* %6, i64 %7), !dbg !511
  store i32 %call, i32* %r, align 4, !dbg !512
  %8 = load i64, i64* %length.addr, align 8, !dbg !513
  %9 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !514
  %bytes_written = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %9, i32 0, i32 0, !dbg !515
  %10 = load i64, i64* %bytes_written, align 8, !dbg !516
  %add = add i64 %10, %8, !dbg !516
  store i64 %add, i64* %bytes_written, align 8, !dbg !516
  %11 = load i32, i32* %r, align 4, !dbg !517
  store i32 %11, i32* %retval, align 4, !dbg !518
  br label %return, !dbg !518

return:                                           ; preds = %if.end3, %if.then2, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !519
  ret i32 %12, !dbg !519
}

; Function Attrs: nounwind uwtable
define i32 @__archive_write_open_filter(%struct.archive_write_filter* %f) #0 !dbg !218 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !520, metadata !257), !dbg !521
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !522
  %open = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 4, !dbg !524
  %1 = load i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)** %open, align 8, !dbg !524
  %cmp = icmp eq i32 (%struct.archive_write_filter*)* %1, null, !dbg !525
  br i1 %cmp, label %if.then, label %if.end, !dbg !526

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !527
  br label %return, !dbg !527

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !528
  %open1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %2, i32 0, i32 4, !dbg !529
  %3 = load i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)** %open1, align 8, !dbg !529
  %4 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !530
  %call = call i32 %3(%struct.archive_write_filter* %4), !dbg !531
  store i32 %call, i32* %retval, align 4, !dbg !532
  br label %return, !dbg !532

return:                                           ; preds = %if.end, %if.then
  %5 = load i32, i32* %retval, align 4, !dbg !533
  ret i32 %5, !dbg !533
}

; Function Attrs: nounwind uwtable
define i32 @__archive_write_close_filter(%struct.archive_write_filter* %f) #0 !dbg !219 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !534, metadata !257), !dbg !535
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !536
  %close = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 6, !dbg !538
  %1 = load i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)** %close, align 8, !dbg !538
  %cmp = icmp ne i32 (%struct.archive_write_filter*)* %1, null, !dbg !539
  br i1 %cmp, label %if.then, label %if.end, !dbg !540

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !541
  %close1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %2, i32 0, i32 6, !dbg !542
  %3 = load i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)** %close1, align 8, !dbg !542
  %4 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !543
  %call = call i32 %3(%struct.archive_write_filter* %4), !dbg !544
  store i32 %call, i32* %retval, align 4, !dbg !545
  br label %return, !dbg !545

if.end:                                           ; preds = %entry
  %5 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !546
  %next_filter = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %5, i32 0, i32 2, !dbg !548
  %6 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter, align 8, !dbg !548
  %cmp2 = icmp ne %struct.archive_write_filter* %6, null, !dbg !549
  br i1 %cmp2, label %if.then3, label %if.end6, !dbg !550

if.then3:                                         ; preds = %if.end
  %7 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !551
  %next_filter4 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %7, i32 0, i32 2, !dbg !552
  %8 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter4, align 8, !dbg !552
  %call5 = call i32 @__archive_write_close_filter(%struct.archive_write_filter* %8), !dbg !553
  store i32 %call5, i32* %retval, align 4, !dbg !554
  br label %return, !dbg !554

if.end6:                                          ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !555
  br label %return, !dbg !555

return:                                           ; preds = %if.end6, %if.then3, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !556
  ret i32 %9, !dbg !556
}

; Function Attrs: nounwind uwtable
define i32 @__archive_write_output(%struct.archive_write* %a, i8* %buff, i64 %length) #0 !dbg !220 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %buff.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !557, metadata !257), !dbg !558
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !559, metadata !257), !dbg !560
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !561, metadata !257), !dbg !562
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !563
  %filter_first = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 12, !dbg !564
  %1 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter_first, align 8, !dbg !564
  %2 = load i8*, i8** %buff.addr, align 8, !dbg !565
  %3 = load i64, i64* %length.addr, align 8, !dbg !566
  %call = call i32 @__archive_write_filter(%struct.archive_write_filter* %1, i8* %2, i64 %3), !dbg !567
  ret i32 %call, !dbg !568
}

; Function Attrs: nounwind uwtable
define i32 @__archive_write_nulls(%struct.archive_write* %a, i64 %length) #0 !dbg !223 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %length.addr = alloca i64, align 8
  %to_write = alloca i64, align 8
  %r = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !569, metadata !257), !dbg !570
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !571, metadata !257), !dbg !572
  %0 = load i64, i64* %length.addr, align 8, !dbg !573
  %cmp = icmp eq i64 %0, 0, !dbg !575
  br i1 %cmp, label %if.then, label %if.end, !dbg !576

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !577
  br label %return, !dbg !577

if.end:                                           ; preds = %entry
  br label %while.cond, !dbg !578

while.cond:                                       ; preds = %if.end6, %if.end
  %1 = load i64, i64* %length.addr, align 8, !dbg !579
  %cmp1 = icmp ugt i64 %1, 0, !dbg !581
  br i1 %cmp1, label %while.body, label %while.end, !dbg !582

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i64* %to_write, metadata !583, metadata !257), !dbg !585
  %2 = load i64, i64* %length.addr, align 8, !dbg !586
  %3 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !587
  %null_length = getelementptr inbounds %struct.archive_write, %struct.archive_write* %3, i32 0, i32 5, !dbg !588
  %4 = load i64, i64* %null_length, align 8, !dbg !588
  %cmp2 = icmp ult i64 %2, %4, !dbg !589
  br i1 %cmp2, label %cond.true, label %cond.false, !dbg !586

cond.true:                                        ; preds = %while.body
  %5 = load i64, i64* %length.addr, align 8, !dbg !590
  br label %cond.end, !dbg !592

cond.false:                                       ; preds = %while.body
  %6 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !593
  %null_length3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 5, !dbg !595
  %7 = load i64, i64* %null_length3, align 8, !dbg !595
  br label %cond.end, !dbg !596

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %5, %cond.true ], [ %7, %cond.false ], !dbg !597
  store i64 %cond, i64* %to_write, align 8, !dbg !599
  call void @llvm.dbg.declare(metadata i32* %r, metadata !600, metadata !257), !dbg !601
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !602
  %9 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !603
  %nulls = getelementptr inbounds %struct.archive_write, %struct.archive_write* %9, i32 0, i32 4, !dbg !604
  %10 = load i8*, i8** %nulls, align 8, !dbg !604
  %11 = load i64, i64* %to_write, align 8, !dbg !605
  %call = call i32 @__archive_write_output(%struct.archive_write* %8, i8* %10, i64 %11), !dbg !606
  store i32 %call, i32* %r, align 4, !dbg !601
  %12 = load i32, i32* %r, align 4, !dbg !607
  %cmp4 = icmp slt i32 %12, 0, !dbg !609
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !610

if.then5:                                         ; preds = %cond.end
  %13 = load i32, i32* %r, align 4, !dbg !611
  store i32 %13, i32* %retval, align 4, !dbg !612
  br label %return, !dbg !612

if.end6:                                          ; preds = %cond.end
  %14 = load i64, i64* %to_write, align 8, !dbg !613
  %15 = load i64, i64* %length.addr, align 8, !dbg !614
  %sub = sub i64 %15, %14, !dbg !614
  store i64 %sub, i64* %length.addr, align 8, !dbg !614
  br label %while.cond, !dbg !615

while.end:                                        ; preds = %while.cond
  store i32 0, i32* %retval, align 4, !dbg !617
  br label %return, !dbg !617

return:                                           ; preds = %while.end, %if.then5, %if.then
  %16 = load i32, i32* %retval, align 4, !dbg !618
  ret i32 %16, !dbg !618
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_open(%struct.archive* %_a, i8* %client_data, i32 (%struct.archive*, i8*)* %opener, i64 (%struct.archive*, i8*, i8*, i64)* %writer, i32 (%struct.archive*, i8*)* %closer) #0 !dbg !226 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %opener.addr = alloca i32 (%struct.archive*, i8*)*, align 8
  %writer.addr = alloca i64 (%struct.archive*, i8*, i8*, i64)*, align 8
  %closer.addr = alloca i32 (%struct.archive*, i8*)*, align 8
  %a = alloca %struct.archive_write*, align 8
  %client_filter = alloca %struct.archive_write_filter*, align 8
  %ret = alloca i32, align 4
  %r1 = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !619, metadata !257), !dbg !620
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !621, metadata !257), !dbg !622
  store i32 (%struct.archive*, i8*)* %opener, i32 (%struct.archive*, i8*)** %opener.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.archive*, i8*)** %opener.addr, metadata !623, metadata !257), !dbg !624
  store i64 (%struct.archive*, i8*, i8*, i64)* %writer, i64 (%struct.archive*, i8*, i8*, i64)** %writer.addr, align 8
  call void @llvm.dbg.declare(metadata i64 (%struct.archive*, i8*, i8*, i64)** %writer.addr, metadata !625, metadata !257), !dbg !626
  store i32 (%struct.archive*, i8*)* %closer, i32 (%struct.archive*, i8*)** %closer.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.archive*, i8*)** %closer.addr, metadata !627, metadata !257), !dbg !628
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !629, metadata !257), !dbg !630
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !631
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !632
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !630
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %client_filter, metadata !633, metadata !257), !dbg !634
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !635, metadata !257), !dbg !636
  call void @llvm.dbg.declare(metadata i32* %r1, metadata !637, metadata !257), !dbg !638
  br label %do.body, !dbg !639

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !640, metadata !257), !dbg !642
  %2 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !643
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 0, !dbg !643
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1329217314, i32 1, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.5, i32 0, i32 0)), !dbg !643
  store i32 %call, i32* %magic_test, align 4, !dbg !643
  %3 = load i32, i32* %magic_test, align 4, !dbg !643
  %cmp = icmp eq i32 %3, -30, !dbg !643
  br i1 %cmp, label %if.then, label %if.end, !dbg !643

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !645
  br label %return, !dbg !645

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !648

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !650
  %archive1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 0, !dbg !651
  call void @archive_clear_error(%struct.archive* %archive1), !dbg !652
  %5 = load i64 (%struct.archive*, i8*, i8*, i64)*, i64 (%struct.archive*, i8*, i8*, i64)** %writer.addr, align 8, !dbg !653
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !654
  %client_writer = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 7, !dbg !655
  store i64 (%struct.archive*, i8*, i8*, i64)* %5, i64 (%struct.archive*, i8*, i8*, i64)** %client_writer, align 8, !dbg !656
  %7 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %opener.addr, align 8, !dbg !657
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !658
  %client_opener = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 6, !dbg !659
  store i32 (%struct.archive*, i8*)* %7, i32 (%struct.archive*, i8*)** %client_opener, align 8, !dbg !660
  %9 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %closer.addr, align 8, !dbg !661
  %10 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !662
  %client_closer = getelementptr inbounds %struct.archive_write, %struct.archive_write* %10, i32 0, i32 8, !dbg !663
  store i32 (%struct.archive*, i8*)* %9, i32 (%struct.archive*, i8*)** %client_closer, align 8, !dbg !664
  %11 = load i8*, i8** %client_data.addr, align 8, !dbg !665
  %12 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !666
  %client_data2 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %12, i32 0, i32 9, !dbg !667
  store i8* %11, i8** %client_data2, align 8, !dbg !668
  %13 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !669
  %call3 = call %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive* %13), !dbg !670
  store %struct.archive_write_filter* %call3, %struct.archive_write_filter** %client_filter, align 8, !dbg !671
  %14 = load %struct.archive_write_filter*, %struct.archive_write_filter** %client_filter, align 8, !dbg !672
  %open = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %14, i32 0, i32 4, !dbg !673
  store i32 (%struct.archive_write_filter*)* @archive_write_client_open, i32 (%struct.archive_write_filter*)** %open, align 8, !dbg !674
  %15 = load %struct.archive_write_filter*, %struct.archive_write_filter** %client_filter, align 8, !dbg !675
  %write = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %15, i32 0, i32 5, !dbg !676
  store i32 (%struct.archive_write_filter*, i8*, i64)* @archive_write_client_write, i32 (%struct.archive_write_filter*, i8*, i64)** %write, align 8, !dbg !677
  %16 = load %struct.archive_write_filter*, %struct.archive_write_filter** %client_filter, align 8, !dbg !678
  %close = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %16, i32 0, i32 6, !dbg !679
  store i32 (%struct.archive_write_filter*)* @archive_write_client_close, i32 (%struct.archive_write_filter*)** %close, align 8, !dbg !680
  %17 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !681
  %filter_first = getelementptr inbounds %struct.archive_write, %struct.archive_write* %17, i32 0, i32 12, !dbg !682
  %18 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter_first, align 8, !dbg !682
  %call4 = call i32 @__archive_write_open_filter(%struct.archive_write_filter* %18), !dbg !683
  store i32 %call4, i32* %ret, align 4, !dbg !684
  %19 = load i32, i32* %ret, align 4, !dbg !685
  %cmp5 = icmp slt i32 %19, -20, !dbg !687
  br i1 %cmp5, label %if.then6, label %if.end10, !dbg !688

if.then6:                                         ; preds = %do.end
  %20 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !689
  %filter_first7 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %20, i32 0, i32 12, !dbg !691
  %21 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter_first7, align 8, !dbg !691
  %call8 = call i32 @__archive_write_close_filter(%struct.archive_write_filter* %21), !dbg !692
  store i32 %call8, i32* %r1, align 4, !dbg !693
  %22 = load i32, i32* %r1, align 4, !dbg !694
  %23 = load i32, i32* %ret, align 4, !dbg !695
  %cmp9 = icmp slt i32 %22, %23, !dbg !696
  br i1 %cmp9, label %cond.true, label %cond.false, !dbg !694

cond.true:                                        ; preds = %if.then6
  %24 = load i32, i32* %r1, align 4, !dbg !697
  br label %cond.end, !dbg !699

cond.false:                                       ; preds = %if.then6
  %25 = load i32, i32* %ret, align 4, !dbg !700
  br label %cond.end, !dbg !702

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %24, %cond.true ], [ %25, %cond.false ], !dbg !703
  store i32 %cond, i32* %retval, align 4, !dbg !705
  br label %return, !dbg !705

if.end10:                                         ; preds = %do.end
  %26 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !706
  %archive11 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %26, i32 0, i32 0, !dbg !707
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive11, i32 0, i32 1, !dbg !708
  store i32 2, i32* %state, align 4, !dbg !709
  %27 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !710
  %format_init = getelementptr inbounds %struct.archive_write, %struct.archive_write* %27, i32 0, i32 16, !dbg !712
  %28 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_init, align 8, !dbg !712
  %tobool = icmp ne i32 (%struct.archive_write*)* %28, null, !dbg !710
  br i1 %tobool, label %if.then12, label %if.end15, !dbg !713

if.then12:                                        ; preds = %if.end10
  %29 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !714
  %format_init13 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %29, i32 0, i32 16, !dbg !715
  %30 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_init13, align 8, !dbg !715
  %31 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !716
  %call14 = call i32 %30(%struct.archive_write* %31), !dbg !717
  store i32 %call14, i32* %ret, align 4, !dbg !718
  br label %if.end15, !dbg !719

if.end15:                                         ; preds = %if.then12, %if.end10
  %32 = load i32, i32* %ret, align 4, !dbg !720
  store i32 %32, i32* %retval, align 4, !dbg !721
  br label %return, !dbg !721

return:                                           ; preds = %if.end15, %cond.end, %if.then
  %33 = load i32, i32* %retval, align 4, !dbg !722
  ret i32 %33, !dbg !722
}

declare void @archive_clear_error(%struct.archive*) #3

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_client_open(%struct.archive_write_filter* %f) #0 !dbg !247 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %a = alloca %struct.archive_write*, align 8
  %state = alloca %struct.archive_none*, align 8
  %buffer = alloca i8*, align 8
  %buffer_size = alloca i64, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !723, metadata !257), !dbg !724
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !725, metadata !257), !dbg !726
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !727
  %archive = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 1, !dbg !728
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !728
  %2 = bitcast %struct.archive* %1 to %struct.archive_write*, !dbg !729
  store %struct.archive_write* %2, %struct.archive_write** %a, align 8, !dbg !726
  call void @llvm.dbg.declare(metadata %struct.archive_none** %state, metadata !730, metadata !257), !dbg !731
  call void @llvm.dbg.declare(metadata i8** %buffer, metadata !732, metadata !257), !dbg !733
  call void @llvm.dbg.declare(metadata i64* %buffer_size, metadata !734, metadata !257), !dbg !735
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !736
  %archive1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %3, i32 0, i32 1, !dbg !737
  %4 = load %struct.archive*, %struct.archive** %archive1, align 8, !dbg !737
  %call = call i32 @archive_write_get_bytes_per_block(%struct.archive* %4), !dbg !738
  %5 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !739
  %bytes_per_block = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %5, i32 0, i32 11, !dbg !740
  store i32 %call, i32* %bytes_per_block, align 4, !dbg !741
  %6 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !742
  %archive2 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %6, i32 0, i32 1, !dbg !743
  %7 = load %struct.archive*, %struct.archive** %archive2, align 8, !dbg !743
  %call3 = call i32 @archive_write_get_bytes_in_last_block(%struct.archive* %7), !dbg !744
  %8 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !745
  %bytes_in_last_block = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %8, i32 0, i32 12, !dbg !746
  store i32 %call3, i32* %bytes_in_last_block, align 8, !dbg !747
  %9 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !748
  %bytes_per_block4 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %9, i32 0, i32 11, !dbg !749
  %10 = load i32, i32* %bytes_per_block4, align 4, !dbg !749
  %conv = sext i32 %10 to i64, !dbg !748
  store i64 %conv, i64* %buffer_size, align 8, !dbg !750
  %call5 = call noalias i8* @calloc(i64 1, i64 32) #6, !dbg !751
  %11 = bitcast i8* %call5 to %struct.archive_none*, !dbg !752
  store %struct.archive_none* %11, %struct.archive_none** %state, align 8, !dbg !753
  %12 = load i64, i64* %buffer_size, align 8, !dbg !754
  %call6 = call noalias i8* @malloc(i64 %12) #6, !dbg !755
  store i8* %call6, i8** %buffer, align 8, !dbg !756
  %13 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !757
  %cmp = icmp eq %struct.archive_none* %13, null, !dbg !759
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !760

lor.lhs.false:                                    ; preds = %entry
  %14 = load i8*, i8** %buffer, align 8, !dbg !761
  %cmp8 = icmp eq i8* %14, null, !dbg !763
  br i1 %cmp8, label %if.then, label %if.end, !dbg !764

if.then:                                          ; preds = %lor.lhs.false, %entry
  %15 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !765
  %16 = bitcast %struct.archive_none* %15 to i8*, !dbg !765
  call void @free(i8* %16) #6, !dbg !767
  %17 = load i8*, i8** %buffer, align 8, !dbg !768
  call void @free(i8* %17) #6, !dbg !769
  %18 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !770
  %archive10 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %18, i32 0, i32 1, !dbg !771
  %19 = load %struct.archive*, %struct.archive** %archive10, align 8, !dbg !771
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %19, i32 12, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.13, i32 0, i32 0)), !dbg !772
  store i32 -30, i32* %retval, align 4, !dbg !773
  br label %return, !dbg !773

if.end:                                           ; preds = %lor.lhs.false
  %20 = load i64, i64* %buffer_size, align 8, !dbg !774
  %21 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !775
  %buffer_size11 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %21, i32 0, i32 0, !dbg !776
  store i64 %20, i64* %buffer_size11, align 8, !dbg !777
  %22 = load i8*, i8** %buffer, align 8, !dbg !778
  %23 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !779
  %buffer12 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %23, i32 0, i32 2, !dbg !780
  store i8* %22, i8** %buffer12, align 8, !dbg !781
  %24 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !782
  %buffer13 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %24, i32 0, i32 2, !dbg !783
  %25 = load i8*, i8** %buffer13, align 8, !dbg !783
  %26 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !784
  %next = getelementptr inbounds %struct.archive_none, %struct.archive_none* %26, i32 0, i32 3, !dbg !785
  store i8* %25, i8** %next, align 8, !dbg !786
  %27 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !787
  %buffer_size14 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %27, i32 0, i32 0, !dbg !788
  %28 = load i64, i64* %buffer_size14, align 8, !dbg !788
  %29 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !789
  %avail = getelementptr inbounds %struct.archive_none, %struct.archive_none* %29, i32 0, i32 1, !dbg !790
  store i64 %28, i64* %avail, align 8, !dbg !791
  %30 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !792
  %31 = bitcast %struct.archive_none* %30 to i8*, !dbg !792
  %32 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !793
  %data = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %32, i32 0, i32 8, !dbg !794
  store i8* %31, i8** %data, align 8, !dbg !795
  %33 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !796
  %client_opener = getelementptr inbounds %struct.archive_write, %struct.archive_write* %33, i32 0, i32 6, !dbg !798
  %34 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %client_opener, align 8, !dbg !798
  %cmp15 = icmp eq i32 (%struct.archive*, i8*)* %34, null, !dbg !799
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !800

if.then17:                                        ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !801
  br label %return, !dbg !801

if.end18:                                         ; preds = %if.end
  %35 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !802
  %client_opener19 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %35, i32 0, i32 6, !dbg !803
  %36 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %client_opener19, align 8, !dbg !803
  %37 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !804
  %archive20 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %37, i32 0, i32 1, !dbg !805
  %38 = load %struct.archive*, %struct.archive** %archive20, align 8, !dbg !805
  %39 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !806
  %client_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %39, i32 0, i32 9, !dbg !807
  %40 = load i8*, i8** %client_data, align 8, !dbg !807
  %call21 = call i32 %36(%struct.archive* %38, i8* %40), !dbg !802
  store i32 %call21, i32* %retval, align 4, !dbg !808
  br label %return, !dbg !808

return:                                           ; preds = %if.end18, %if.then17, %if.then
  %41 = load i32, i32* %retval, align 4, !dbg !809
  ret i32 %41, !dbg !809
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_client_write(%struct.archive_write_filter* %f, i8* %_buff, i64 %length) #0 !dbg !248 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %_buff.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %a = alloca %struct.archive_write*, align 8
  %state = alloca %struct.archive_none*, align 8
  %buff = alloca i8*, align 8
  %remaining = alloca i64, align 8
  %to_copy = alloca i64, align 8
  %bytes_written = alloca i64, align 8
  %p = alloca i8*, align 8
  %to_write = alloca i64, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !810, metadata !257), !dbg !811
  store i8* %_buff, i8** %_buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %_buff.addr, metadata !812, metadata !257), !dbg !813
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !814, metadata !257), !dbg !815
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !816, metadata !257), !dbg !817
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !818
  %archive = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 1, !dbg !819
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !819
  %2 = bitcast %struct.archive* %1 to %struct.archive_write*, !dbg !820
  store %struct.archive_write* %2, %struct.archive_write** %a, align 8, !dbg !817
  call void @llvm.dbg.declare(metadata %struct.archive_none** %state, metadata !821, metadata !257), !dbg !822
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !823
  %data = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %3, i32 0, i32 8, !dbg !824
  %4 = load i8*, i8** %data, align 8, !dbg !824
  %5 = bitcast i8* %4 to %struct.archive_none*, !dbg !825
  store %struct.archive_none* %5, %struct.archive_none** %state, align 8, !dbg !822
  call void @llvm.dbg.declare(metadata i8** %buff, metadata !826, metadata !257), !dbg !827
  %6 = load i8*, i8** %_buff.addr, align 8, !dbg !828
  store i8* %6, i8** %buff, align 8, !dbg !827
  call void @llvm.dbg.declare(metadata i64* %remaining, metadata !829, metadata !257), !dbg !830
  call void @llvm.dbg.declare(metadata i64* %to_copy, metadata !831, metadata !257), !dbg !832
  call void @llvm.dbg.declare(metadata i64* %bytes_written, metadata !833, metadata !257), !dbg !834
  %7 = load i64, i64* %length.addr, align 8, !dbg !835
  store i64 %7, i64* %remaining, align 8, !dbg !836
  %8 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !837
  %buffer_size = getelementptr inbounds %struct.archive_none, %struct.archive_none* %8, i32 0, i32 0, !dbg !839
  %9 = load i64, i64* %buffer_size, align 8, !dbg !839
  %cmp = icmp eq i64 %9, 0, !dbg !840
  br i1 %cmp, label %if.then, label %if.end5, !dbg !841

if.then:                                          ; preds = %entry
  br label %while.cond, !dbg !842

while.cond:                                       ; preds = %if.end, %if.then
  %10 = load i64, i64* %remaining, align 8, !dbg !844
  %cmp1 = icmp sgt i64 %10, 0, !dbg !846
  br i1 %cmp1, label %while.body, label %while.end, !dbg !847

while.body:                                       ; preds = %while.cond
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !848
  %client_writer = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 7, !dbg !850
  %12 = load i64 (%struct.archive*, i8*, i8*, i64)*, i64 (%struct.archive*, i8*, i8*, i64)** %client_writer, align 8, !dbg !850
  %13 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !851
  %archive2 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %13, i32 0, i32 0, !dbg !852
  %14 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !853
  %client_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %14, i32 0, i32 9, !dbg !854
  %15 = load i8*, i8** %client_data, align 8, !dbg !854
  %16 = load i8*, i8** %buff, align 8, !dbg !855
  %17 = load i64, i64* %remaining, align 8, !dbg !856
  %call = call i64 %12(%struct.archive* %archive2, i8* %15, i8* %16, i64 %17), !dbg !857
  store i64 %call, i64* %bytes_written, align 8, !dbg !858
  %18 = load i64, i64* %bytes_written, align 8, !dbg !859
  %cmp3 = icmp sle i64 %18, 0, !dbg !861
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !862

if.then4:                                         ; preds = %while.body
  store i32 -30, i32* %retval, align 4, !dbg !863
  br label %return, !dbg !863

if.end:                                           ; preds = %while.body
  %19 = load i64, i64* %bytes_written, align 8, !dbg !864
  %20 = load i64, i64* %remaining, align 8, !dbg !865
  %sub = sub nsw i64 %20, %19, !dbg !865
  store i64 %sub, i64* %remaining, align 8, !dbg !865
  %21 = load i64, i64* %bytes_written, align 8, !dbg !866
  %22 = load i8*, i8** %buff, align 8, !dbg !867
  %add.ptr = getelementptr inbounds i8, i8* %22, i64 %21, !dbg !867
  store i8* %add.ptr, i8** %buff, align 8, !dbg !867
  br label %while.cond, !dbg !868

while.end:                                        ; preds = %while.cond
  store i32 0, i32* %retval, align 4, !dbg !870
  br label %return, !dbg !870

if.end5:                                          ; preds = %entry
  %23 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !871
  %avail = getelementptr inbounds %struct.archive_none, %struct.archive_none* %23, i32 0, i32 1, !dbg !873
  %24 = load i64, i64* %avail, align 8, !dbg !873
  %25 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !874
  %buffer_size6 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %25, i32 0, i32 0, !dbg !875
  %26 = load i64, i64* %buffer_size6, align 8, !dbg !875
  %cmp7 = icmp ult i64 %24, %26, !dbg !876
  br i1 %cmp7, label %if.then8, label %if.end44, !dbg !877

if.then8:                                         ; preds = %if.end5
  %27 = load i64, i64* %remaining, align 8, !dbg !878
  %28 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !880
  %avail9 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %28, i32 0, i32 1, !dbg !881
  %29 = load i64, i64* %avail9, align 8, !dbg !881
  %cmp10 = icmp ugt i64 %27, %29, !dbg !882
  br i1 %cmp10, label %cond.true, label %cond.false, !dbg !883

cond.true:                                        ; preds = %if.then8
  %30 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !884
  %avail11 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %30, i32 0, i32 1, !dbg !885
  %31 = load i64, i64* %avail11, align 8, !dbg !885
  br label %cond.end, !dbg !886

cond.false:                                       ; preds = %if.then8
  %32 = load i64, i64* %remaining, align 8, !dbg !888
  br label %cond.end, !dbg !889

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %31, %cond.true ], [ %32, %cond.false ], !dbg !891
  store i64 %cond, i64* %to_copy, align 8, !dbg !893
  %33 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !894
  %next = getelementptr inbounds %struct.archive_none, %struct.archive_none* %33, i32 0, i32 3, !dbg !895
  %34 = load i8*, i8** %next, align 8, !dbg !895
  %35 = load i8*, i8** %buff, align 8, !dbg !896
  %36 = load i64, i64* %to_copy, align 8, !dbg !897
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %34, i8* %35, i64 %36, i32 1, i1 false), !dbg !898
  %37 = load i64, i64* %to_copy, align 8, !dbg !899
  %38 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !900
  %next12 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %38, i32 0, i32 3, !dbg !901
  %39 = load i8*, i8** %next12, align 8, !dbg !902
  %add.ptr13 = getelementptr inbounds i8, i8* %39, i64 %37, !dbg !902
  store i8* %add.ptr13, i8** %next12, align 8, !dbg !902
  %40 = load i64, i64* %to_copy, align 8, !dbg !903
  %41 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !904
  %avail14 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %41, i32 0, i32 1, !dbg !905
  %42 = load i64, i64* %avail14, align 8, !dbg !906
  %sub15 = sub i64 %42, %40, !dbg !906
  store i64 %sub15, i64* %avail14, align 8, !dbg !906
  %43 = load i64, i64* %to_copy, align 8, !dbg !907
  %44 = load i8*, i8** %buff, align 8, !dbg !908
  %add.ptr16 = getelementptr inbounds i8, i8* %44, i64 %43, !dbg !908
  store i8* %add.ptr16, i8** %buff, align 8, !dbg !908
  %45 = load i64, i64* %to_copy, align 8, !dbg !909
  %46 = load i64, i64* %remaining, align 8, !dbg !910
  %sub17 = sub nsw i64 %46, %45, !dbg !910
  store i64 %sub17, i64* %remaining, align 8, !dbg !910
  %47 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !911
  %avail18 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %47, i32 0, i32 1, !dbg !913
  %48 = load i64, i64* %avail18, align 8, !dbg !913
  %cmp19 = icmp eq i64 %48, 0, !dbg !914
  br i1 %cmp19, label %if.then20, label %if.end43, !dbg !915

if.then20:                                        ; preds = %cond.end
  call void @llvm.dbg.declare(metadata i8** %p, metadata !916, metadata !257), !dbg !918
  %49 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !919
  %buffer = getelementptr inbounds %struct.archive_none, %struct.archive_none* %49, i32 0, i32 2, !dbg !920
  %50 = load i8*, i8** %buffer, align 8, !dbg !920
  store i8* %50, i8** %p, align 8, !dbg !918
  call void @llvm.dbg.declare(metadata i64* %to_write, metadata !921, metadata !257), !dbg !922
  %51 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !923
  %buffer_size21 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %51, i32 0, i32 0, !dbg !924
  %52 = load i64, i64* %buffer_size21, align 8, !dbg !924
  store i64 %52, i64* %to_write, align 8, !dbg !922
  br label %while.cond22, !dbg !925

while.cond22:                                     ; preds = %if.end35, %if.then20
  %53 = load i64, i64* %to_write, align 8, !dbg !926
  %cmp23 = icmp ugt i64 %53, 0, !dbg !928
  br i1 %cmp23, label %while.body24, label %while.end38, !dbg !929

while.body24:                                     ; preds = %while.cond22
  %54 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !930
  %client_writer25 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %54, i32 0, i32 7, !dbg !932
  %55 = load i64 (%struct.archive*, i8*, i8*, i64)*, i64 (%struct.archive*, i8*, i8*, i64)** %client_writer25, align 8, !dbg !932
  %56 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !933
  %archive26 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %56, i32 0, i32 0, !dbg !934
  %57 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !935
  %client_data27 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %57, i32 0, i32 9, !dbg !936
  %58 = load i8*, i8** %client_data27, align 8, !dbg !936
  %59 = load i8*, i8** %p, align 8, !dbg !937
  %60 = load i64, i64* %to_write, align 8, !dbg !938
  %call28 = call i64 %55(%struct.archive* %archive26, i8* %58, i8* %59, i64 %60), !dbg !939
  store i64 %call28, i64* %bytes_written, align 8, !dbg !940
  %61 = load i64, i64* %bytes_written, align 8, !dbg !941
  %cmp29 = icmp sle i64 %61, 0, !dbg !943
  br i1 %cmp29, label %if.then30, label %if.end31, !dbg !944

if.then30:                                        ; preds = %while.body24
  store i32 -30, i32* %retval, align 4, !dbg !945
  br label %return, !dbg !945

if.end31:                                         ; preds = %while.body24
  %62 = load i64, i64* %bytes_written, align 8, !dbg !946
  %63 = load i64, i64* %to_write, align 8, !dbg !948
  %cmp32 = icmp ugt i64 %62, %63, !dbg !949
  br i1 %cmp32, label %if.then33, label %if.end35, !dbg !950

if.then33:                                        ; preds = %if.end31
  %64 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !951
  %archive34 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %64, i32 0, i32 0, !dbg !953
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive34, i32 -1, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.14, i32 0, i32 0)), !dbg !954
  store i32 -30, i32* %retval, align 4, !dbg !955
  br label %return, !dbg !955

if.end35:                                         ; preds = %if.end31
  %65 = load i64, i64* %bytes_written, align 8, !dbg !956
  %66 = load i8*, i8** %p, align 8, !dbg !957
  %add.ptr36 = getelementptr inbounds i8, i8* %66, i64 %65, !dbg !957
  store i8* %add.ptr36, i8** %p, align 8, !dbg !957
  %67 = load i64, i64* %bytes_written, align 8, !dbg !958
  %68 = load i64, i64* %to_write, align 8, !dbg !959
  %sub37 = sub i64 %68, %67, !dbg !959
  store i64 %sub37, i64* %to_write, align 8, !dbg !959
  br label %while.cond22, !dbg !960

while.end38:                                      ; preds = %while.cond22
  %69 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !962
  %buffer39 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %69, i32 0, i32 2, !dbg !963
  %70 = load i8*, i8** %buffer39, align 8, !dbg !963
  %71 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !964
  %next40 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %71, i32 0, i32 3, !dbg !965
  store i8* %70, i8** %next40, align 8, !dbg !966
  %72 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !967
  %buffer_size41 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %72, i32 0, i32 0, !dbg !968
  %73 = load i64, i64* %buffer_size41, align 8, !dbg !968
  %74 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !969
  %avail42 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %74, i32 0, i32 1, !dbg !970
  store i64 %73, i64* %avail42, align 8, !dbg !971
  br label %if.end43, !dbg !972

if.end43:                                         ; preds = %while.end38, %cond.end
  br label %if.end44, !dbg !973

if.end44:                                         ; preds = %if.end43, %if.end5
  br label %while.cond45, !dbg !974

while.cond45:                                     ; preds = %if.end56, %if.end44
  %75 = load i64, i64* %remaining, align 8, !dbg !975
  %76 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !977
  %buffer_size46 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %76, i32 0, i32 0, !dbg !978
  %77 = load i64, i64* %buffer_size46, align 8, !dbg !978
  %cmp47 = icmp uge i64 %75, %77, !dbg !979
  br i1 %cmp47, label %while.body48, label %while.end59, !dbg !980

while.body48:                                     ; preds = %while.cond45
  %78 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !981
  %client_writer49 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %78, i32 0, i32 7, !dbg !983
  %79 = load i64 (%struct.archive*, i8*, i8*, i64)*, i64 (%struct.archive*, i8*, i8*, i64)** %client_writer49, align 8, !dbg !983
  %80 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !984
  %archive50 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %80, i32 0, i32 0, !dbg !985
  %81 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !986
  %client_data51 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %81, i32 0, i32 9, !dbg !987
  %82 = load i8*, i8** %client_data51, align 8, !dbg !987
  %83 = load i8*, i8** %buff, align 8, !dbg !988
  %84 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !989
  %buffer_size52 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %84, i32 0, i32 0, !dbg !990
  %85 = load i64, i64* %buffer_size52, align 8, !dbg !990
  %call53 = call i64 %79(%struct.archive* %archive50, i8* %82, i8* %83, i64 %85), !dbg !991
  store i64 %call53, i64* %bytes_written, align 8, !dbg !992
  %86 = load i64, i64* %bytes_written, align 8, !dbg !993
  %cmp54 = icmp sle i64 %86, 0, !dbg !995
  br i1 %cmp54, label %if.then55, label %if.end56, !dbg !996

if.then55:                                        ; preds = %while.body48
  store i32 -30, i32* %retval, align 4, !dbg !997
  br label %return, !dbg !997

if.end56:                                         ; preds = %while.body48
  %87 = load i64, i64* %bytes_written, align 8, !dbg !998
  %88 = load i8*, i8** %buff, align 8, !dbg !999
  %add.ptr57 = getelementptr inbounds i8, i8* %88, i64 %87, !dbg !999
  store i8* %add.ptr57, i8** %buff, align 8, !dbg !999
  %89 = load i64, i64* %bytes_written, align 8, !dbg !1000
  %90 = load i64, i64* %remaining, align 8, !dbg !1001
  %sub58 = sub nsw i64 %90, %89, !dbg !1001
  store i64 %sub58, i64* %remaining, align 8, !dbg !1001
  br label %while.cond45, !dbg !1002

while.end59:                                      ; preds = %while.cond45
  %91 = load i64, i64* %remaining, align 8, !dbg !1004
  %cmp60 = icmp sgt i64 %91, 0, !dbg !1006
  br i1 %cmp60, label %if.then61, label %if.end67, !dbg !1007

if.then61:                                        ; preds = %while.end59
  %92 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !1008
  %next62 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %92, i32 0, i32 3, !dbg !1010
  %93 = load i8*, i8** %next62, align 8, !dbg !1010
  %94 = load i8*, i8** %buff, align 8, !dbg !1011
  %95 = load i64, i64* %remaining, align 8, !dbg !1012
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %93, i8* %94, i64 %95, i32 1, i1 false), !dbg !1013
  %96 = load i64, i64* %remaining, align 8, !dbg !1014
  %97 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !1015
  %next63 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %97, i32 0, i32 3, !dbg !1016
  %98 = load i8*, i8** %next63, align 8, !dbg !1017
  %add.ptr64 = getelementptr inbounds i8, i8* %98, i64 %96, !dbg !1017
  store i8* %add.ptr64, i8** %next63, align 8, !dbg !1017
  %99 = load i64, i64* %remaining, align 8, !dbg !1018
  %100 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !1019
  %avail65 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %100, i32 0, i32 1, !dbg !1020
  %101 = load i64, i64* %avail65, align 8, !dbg !1021
  %sub66 = sub i64 %101, %99, !dbg !1021
  store i64 %sub66, i64* %avail65, align 8, !dbg !1021
  br label %if.end67, !dbg !1022

if.end67:                                         ; preds = %if.then61, %while.end59
  store i32 0, i32* %retval, align 4, !dbg !1023
  br label %return, !dbg !1023

return:                                           ; preds = %if.end67, %if.then55, %if.then33, %if.then30, %while.end, %if.then4
  %102 = load i32, i32* %retval, align 4, !dbg !1024
  ret i32 %102, !dbg !1024
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_client_close(%struct.archive_write_filter* %f) #0 !dbg !249 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %a = alloca %struct.archive_write*, align 8
  %state = alloca %struct.archive_none*, align 8
  %block_length = alloca i64, align 8
  %target_block_length = alloca i64, align 8
  %bytes_written = alloca i64, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !1025, metadata !257), !dbg !1026
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !1027, metadata !257), !dbg !1028
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !1029
  %archive = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 1, !dbg !1030
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1030
  %2 = bitcast %struct.archive* %1 to %struct.archive_write*, !dbg !1031
  store %struct.archive_write* %2, %struct.archive_write** %a, align 8, !dbg !1028
  call void @llvm.dbg.declare(metadata %struct.archive_none** %state, metadata !1032, metadata !257), !dbg !1033
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !1034
  %data = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %3, i32 0, i32 8, !dbg !1035
  %4 = load i8*, i8** %data, align 8, !dbg !1035
  %5 = bitcast i8* %4 to %struct.archive_none*, !dbg !1036
  store %struct.archive_none* %5, %struct.archive_none** %state, align 8, !dbg !1033
  call void @llvm.dbg.declare(metadata i64* %block_length, metadata !1037, metadata !257), !dbg !1038
  call void @llvm.dbg.declare(metadata i64* %target_block_length, metadata !1039, metadata !257), !dbg !1040
  call void @llvm.dbg.declare(metadata i64* %bytes_written, metadata !1041, metadata !257), !dbg !1042
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !1043, metadata !257), !dbg !1044
  store i32 0, i32* %ret, align 4, !dbg !1044
  %6 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !1045
  %next = getelementptr inbounds %struct.archive_none, %struct.archive_none* %6, i32 0, i32 3, !dbg !1047
  %7 = load i8*, i8** %next, align 8, !dbg !1047
  %8 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !1048
  %buffer = getelementptr inbounds %struct.archive_none, %struct.archive_none* %8, i32 0, i32 2, !dbg !1049
  %9 = load i8*, i8** %buffer, align 8, !dbg !1049
  %cmp = icmp ne i8* %7, %9, !dbg !1050
  br i1 %cmp, label %if.then, label %if.end28, !dbg !1051

if.then:                                          ; preds = %entry
  %10 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !1052
  %buffer_size = getelementptr inbounds %struct.archive_none, %struct.archive_none* %10, i32 0, i32 0, !dbg !1054
  %11 = load i64, i64* %buffer_size, align 8, !dbg !1054
  %12 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !1055
  %avail = getelementptr inbounds %struct.archive_none, %struct.archive_none* %12, i32 0, i32 1, !dbg !1056
  %13 = load i64, i64* %avail, align 8, !dbg !1056
  %sub = sub i64 %11, %13, !dbg !1057
  store i64 %sub, i64* %block_length, align 8, !dbg !1058
  %14 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1059
  %bytes_in_last_block = getelementptr inbounds %struct.archive_write, %struct.archive_write* %14, i32 0, i32 11, !dbg !1061
  %15 = load i32, i32* %bytes_in_last_block, align 4, !dbg !1061
  %cmp1 = icmp sle i32 %15, 0, !dbg !1062
  br i1 %cmp1, label %if.then2, label %if.else, !dbg !1063

if.then2:                                         ; preds = %if.then
  %16 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1064
  %bytes_per_block = getelementptr inbounds %struct.archive_write, %struct.archive_write* %16, i32 0, i32 10, !dbg !1065
  %17 = load i32, i32* %bytes_per_block, align 8, !dbg !1065
  %conv = sext i32 %17 to i64, !dbg !1064
  store i64 %conv, i64* %target_block_length, align 8, !dbg !1066
  br label %if.end, !dbg !1067

if.else:                                          ; preds = %if.then
  %18 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1068
  %bytes_in_last_block3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %18, i32 0, i32 11, !dbg !1069
  %19 = load i32, i32* %bytes_in_last_block3, align 4, !dbg !1069
  %conv4 = sext i32 %19 to i64, !dbg !1068
  %20 = load i64, i64* %block_length, align 8, !dbg !1070
  %21 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1071
  %bytes_in_last_block5 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %21, i32 0, i32 11, !dbg !1072
  %22 = load i32, i32* %bytes_in_last_block5, align 4, !dbg !1072
  %conv6 = sext i32 %22 to i64, !dbg !1071
  %add = add nsw i64 %20, %conv6, !dbg !1073
  %sub7 = sub nsw i64 %add, 1, !dbg !1074
  %23 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1075
  %bytes_in_last_block8 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %23, i32 0, i32 11, !dbg !1076
  %24 = load i32, i32* %bytes_in_last_block8, align 4, !dbg !1076
  %conv9 = sext i32 %24 to i64, !dbg !1075
  %div = sdiv i64 %sub7, %conv9, !dbg !1077
  %mul = mul nsw i64 %conv4, %div, !dbg !1078
  store i64 %mul, i64* %target_block_length, align 8, !dbg !1079
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then2
  %25 = load i64, i64* %target_block_length, align 8, !dbg !1080
  %26 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1082
  %bytes_per_block10 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %26, i32 0, i32 10, !dbg !1083
  %27 = load i32, i32* %bytes_per_block10, align 8, !dbg !1083
  %conv11 = sext i32 %27 to i64, !dbg !1082
  %cmp12 = icmp sgt i64 %25, %conv11, !dbg !1084
  br i1 %cmp12, label %if.then14, label %if.end17, !dbg !1085

if.then14:                                        ; preds = %if.end
  %28 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1086
  %bytes_per_block15 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %28, i32 0, i32 10, !dbg !1087
  %29 = load i32, i32* %bytes_per_block15, align 8, !dbg !1087
  %conv16 = sext i32 %29 to i64, !dbg !1086
  store i64 %conv16, i64* %target_block_length, align 8, !dbg !1088
  br label %if.end17, !dbg !1089

if.end17:                                         ; preds = %if.then14, %if.end
  %30 = load i64, i64* %block_length, align 8, !dbg !1090
  %31 = load i64, i64* %target_block_length, align 8, !dbg !1092
  %cmp18 = icmp slt i64 %30, %31, !dbg !1093
  br i1 %cmp18, label %if.then20, label %if.end23, !dbg !1094

if.then20:                                        ; preds = %if.end17
  %32 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !1095
  %next21 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %32, i32 0, i32 3, !dbg !1097
  %33 = load i8*, i8** %next21, align 8, !dbg !1097
  %34 = load i64, i64* %target_block_length, align 8, !dbg !1098
  %35 = load i64, i64* %block_length, align 8, !dbg !1099
  %sub22 = sub nsw i64 %34, %35, !dbg !1100
  call void @llvm.memset.p0i8.i64(i8* %33, i8 0, i64 %sub22, i32 1, i1 false), !dbg !1101
  %36 = load i64, i64* %target_block_length, align 8, !dbg !1102
  store i64 %36, i64* %block_length, align 8, !dbg !1103
  br label %if.end23, !dbg !1104

if.end23:                                         ; preds = %if.then20, %if.end17
  %37 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1105
  %client_writer = getelementptr inbounds %struct.archive_write, %struct.archive_write* %37, i32 0, i32 7, !dbg !1106
  %38 = load i64 (%struct.archive*, i8*, i8*, i64)*, i64 (%struct.archive*, i8*, i8*, i64)** %client_writer, align 8, !dbg !1106
  %39 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1107
  %archive24 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %39, i32 0, i32 0, !dbg !1108
  %40 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1109
  %client_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %40, i32 0, i32 9, !dbg !1110
  %41 = load i8*, i8** %client_data, align 8, !dbg !1110
  %42 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !1111
  %buffer25 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %42, i32 0, i32 2, !dbg !1112
  %43 = load i8*, i8** %buffer25, align 8, !dbg !1112
  %44 = load i64, i64* %block_length, align 8, !dbg !1113
  %call = call i64 %38(%struct.archive* %archive24, i8* %41, i8* %43, i64 %44), !dbg !1114
  store i64 %call, i64* %bytes_written, align 8, !dbg !1115
  %45 = load i64, i64* %bytes_written, align 8, !dbg !1116
  %cmp26 = icmp sle i64 %45, 0, !dbg !1117
  %cond = select i1 %cmp26, i32 -30, i32 0, !dbg !1116
  store i32 %cond, i32* %ret, align 4, !dbg !1118
  br label %if.end28, !dbg !1119

if.end28:                                         ; preds = %if.end23, %entry
  %46 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1120
  %client_closer = getelementptr inbounds %struct.archive_write, %struct.archive_write* %46, i32 0, i32 8, !dbg !1122
  %47 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %client_closer, align 8, !dbg !1122
  %tobool = icmp ne i32 (%struct.archive*, i8*)* %47, null, !dbg !1120
  br i1 %tobool, label %if.then29, label %if.end34, !dbg !1123

if.then29:                                        ; preds = %if.end28
  %48 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1124
  %client_closer30 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %48, i32 0, i32 8, !dbg !1125
  %49 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %client_closer30, align 8, !dbg !1125
  %50 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1126
  %archive31 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %50, i32 0, i32 0, !dbg !1127
  %51 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1128
  %client_data32 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %51, i32 0, i32 9, !dbg !1129
  %52 = load i8*, i8** %client_data32, align 8, !dbg !1129
  %call33 = call i32 %49(%struct.archive* %archive31, i8* %52), !dbg !1130
  br label %if.end34, !dbg !1130

if.end34:                                         ; preds = %if.then29, %if.end28
  %53 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !1131
  %buffer35 = getelementptr inbounds %struct.archive_none, %struct.archive_none* %53, i32 0, i32 2, !dbg !1132
  %54 = load i8*, i8** %buffer35, align 8, !dbg !1132
  call void @free(i8* %54) #6, !dbg !1133
  %55 = load %struct.archive_none*, %struct.archive_none** %state, align 8, !dbg !1134
  %56 = bitcast %struct.archive_none* %55 to i8*, !dbg !1134
  call void @free(i8* %56) #6, !dbg !1135
  %57 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !1136
  %close = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %57, i32 0, i32 6, !dbg !1137
  store i32 (%struct.archive_write_filter*)* null, i32 (%struct.archive_write_filter*)** %close, align 8, !dbg !1138
  %58 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1139
  %client_data36 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %58, i32 0, i32 9, !dbg !1140
  store i8* null, i8** %client_data36, align 8, !dbg !1141
  %59 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1142
  %passphrase = getelementptr inbounds %struct.archive_write, %struct.archive_write* %59, i32 0, i32 23, !dbg !1144
  %60 = load i8*, i8** %passphrase, align 8, !dbg !1144
  %cmp37 = icmp ne i8* %60, null, !dbg !1145
  br i1 %cmp37, label %if.then39, label %if.end45, !dbg !1146

if.then39:                                        ; preds = %if.end34
  %61 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1147
  %passphrase40 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %61, i32 0, i32 23, !dbg !1149
  %62 = load i8*, i8** %passphrase40, align 8, !dbg !1149
  %63 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1150
  %passphrase41 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %63, i32 0, i32 23, !dbg !1151
  %64 = load i8*, i8** %passphrase41, align 8, !dbg !1151
  %call42 = call i64 @strlen(i8* %64) #7, !dbg !1152
  call void @llvm.memset.p0i8.i64(i8* %62, i8 0, i64 %call42, i32 1, i1 false), !dbg !1153
  %65 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1155
  %passphrase43 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %65, i32 0, i32 23, !dbg !1156
  %66 = load i8*, i8** %passphrase43, align 8, !dbg !1156
  call void @free(i8* %66) #6, !dbg !1157
  %67 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1158
  %passphrase44 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %67, i32 0, i32 23, !dbg !1159
  store i8* null, i8** %passphrase44, align 8, !dbg !1160
  br label %if.end45, !dbg !1161

if.end45:                                         ; preds = %if.then39, %if.end34
  %68 = load i32, i32* %ret, align 4, !dbg !1162
  ret i32 %68, !dbg !1163
}

; Function Attrs: nounwind uwtable
define void @__archive_write_filters_free(%struct.archive* %_a) #0 !dbg !229 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %r = alloca i32, align 4
  %r1 = alloca i32, align 4
  %next = alloca %struct.archive_write_filter*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1164, metadata !257), !dbg !1165
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !1166, metadata !257), !dbg !1167
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1168
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !1169
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !1167
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1170, metadata !257), !dbg !1171
  store i32 0, i32* %r, align 4, !dbg !1171
  call void @llvm.dbg.declare(metadata i32* %r1, metadata !1172, metadata !257), !dbg !1173
  br label %while.cond, !dbg !1174

while.cond:                                       ; preds = %if.end9, %entry
  %2 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1175
  %filter_first = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 12, !dbg !1177
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter_first, align 8, !dbg !1177
  %cmp = icmp ne %struct.archive_write_filter* %3, null, !dbg !1178
  br i1 %cmp, label %while.body, label %while.end, !dbg !1179

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %next, metadata !1180, metadata !257), !dbg !1182
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1183
  %filter_first1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 12, !dbg !1184
  %5 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter_first1, align 8, !dbg !1184
  %next_filter = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %5, i32 0, i32 2, !dbg !1185
  %6 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter, align 8, !dbg !1185
  store %struct.archive_write_filter* %6, %struct.archive_write_filter** %next, align 8, !dbg !1182
  %7 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1186
  %filter_first2 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 12, !dbg !1188
  %8 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter_first2, align 8, !dbg !1188
  %free = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %8, i32 0, i32 7, !dbg !1189
  %9 = load i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)** %free, align 8, !dbg !1189
  %cmp3 = icmp ne i32 (%struct.archive_write_filter*)* %9, null, !dbg !1190
  br i1 %cmp3, label %if.then, label %if.end9, !dbg !1191

if.then:                                          ; preds = %while.body
  %10 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1192
  %filter_first4 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %10, i32 0, i32 12, !dbg !1194
  %11 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter_first4, align 8, !dbg !1194
  %free5 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %11, i32 0, i32 7, !dbg !1195
  %12 = load i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)** %free5, align 8, !dbg !1195
  %13 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1196
  %filter_first6 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %13, i32 0, i32 12, !dbg !1197
  %14 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter_first6, align 8, !dbg !1197
  %call = call i32 %12(%struct.archive_write_filter* %14), !dbg !1198
  store i32 %call, i32* %r1, align 4, !dbg !1199
  %15 = load i32, i32* %r, align 4, !dbg !1200
  %16 = load i32, i32* %r1, align 4, !dbg !1202
  %cmp7 = icmp sgt i32 %15, %16, !dbg !1203
  br i1 %cmp7, label %if.then8, label %if.end, !dbg !1204

if.then8:                                         ; preds = %if.then
  %17 = load i32, i32* %r1, align 4, !dbg !1205
  store i32 %17, i32* %r, align 4, !dbg !1206
  br label %if.end, !dbg !1207

if.end:                                           ; preds = %if.then8, %if.then
  br label %if.end9, !dbg !1208

if.end9:                                          ; preds = %if.end, %while.body
  %18 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1209
  %filter_first10 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %18, i32 0, i32 12, !dbg !1210
  %19 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter_first10, align 8, !dbg !1210
  %20 = bitcast %struct.archive_write_filter* %19 to i8*, !dbg !1209
  call void @free(i8* %20) #6, !dbg !1211
  %21 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next, align 8, !dbg !1212
  %22 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1213
  %filter_first11 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %22, i32 0, i32 12, !dbg !1214
  store %struct.archive_write_filter* %21, %struct.archive_write_filter** %filter_first11, align 8, !dbg !1215
  br label %while.cond, !dbg !1216

while.end:                                        ; preds = %while.cond
  %23 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1218
  %filter_last = getelementptr inbounds %struct.archive_write, %struct.archive_write* %23, i32 0, i32 13, !dbg !1219
  store %struct.archive_write_filter* null, %struct.archive_write_filter** %filter_last, align 8, !dbg !1220
  ret void, !dbg !1221
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_write_close(%struct.archive* %_a) #0 !dbg !235 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %r = alloca i32, align 4
  %r1 = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1222, metadata !257), !dbg !1223
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !1224, metadata !257), !dbg !1225
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1226
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !1227
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !1225
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1228, metadata !257), !dbg !1229
  store i32 0, i32* %r, align 4, !dbg !1229
  call void @llvm.dbg.declare(metadata i32* %r1, metadata !1230, metadata !257), !dbg !1231
  store i32 0, i32* %r1, align 4, !dbg !1231
  br label %do.body, !dbg !1232

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1233, metadata !257), !dbg !1235
  %2 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1236
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 0, !dbg !1236
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1329217314, i32 65535, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.6, i32 0, i32 0)), !dbg !1236
  store i32 %call, i32* %magic_test, align 4, !dbg !1236
  %3 = load i32, i32* %magic_test, align 4, !dbg !1236
  %cmp = icmp eq i32 %3, -30, !dbg !1236
  br i1 %cmp, label %if.then, label %if.end, !dbg !1236

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1238
  br label %return, !dbg !1238

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1241

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1243
  %archive1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 0, !dbg !1245
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive1, i32 0, i32 1, !dbg !1246
  %5 = load i32, i32* %state, align 4, !dbg !1246
  %cmp2 = icmp eq i32 %5, 1, !dbg !1247
  br i1 %cmp2, label %if.then6, label %lor.lhs.false, !dbg !1248

lor.lhs.false:                                    ; preds = %do.end
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1249
  %archive3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 0, !dbg !1251
  %state4 = getelementptr inbounds %struct.archive, %struct.archive* %archive3, i32 0, i32 1, !dbg !1252
  %7 = load i32, i32* %state4, align 4, !dbg !1252
  %cmp5 = icmp eq i32 %7, 32, !dbg !1253
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !1254

if.then6:                                         ; preds = %lor.lhs.false, %do.end
  store i32 0, i32* %retval, align 4, !dbg !1256
  br label %return, !dbg !1256

if.end7:                                          ; preds = %lor.lhs.false
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1257
  %archive8 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 0, !dbg !1258
  call void @archive_clear_error(%struct.archive* %archive8), !dbg !1259
  %9 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1260
  %archive9 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %9, i32 0, i32 0, !dbg !1262
  %state10 = getelementptr inbounds %struct.archive, %struct.archive* %archive9, i32 0, i32 1, !dbg !1263
  %10 = load i32, i32* %state10, align 4, !dbg !1263
  %cmp11 = icmp eq i32 %10, 4, !dbg !1264
  br i1 %cmp11, label %land.lhs.true, label %if.end16, !dbg !1265

land.lhs.true:                                    ; preds = %if.end7
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1266
  %format_finish_entry = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 18, !dbg !1268
  %12 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_finish_entry, align 8, !dbg !1268
  %cmp12 = icmp ne i32 (%struct.archive_write*)* %12, null, !dbg !1269
  br i1 %cmp12, label %if.then13, label %if.end16, !dbg !1270

if.then13:                                        ; preds = %land.lhs.true
  %13 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1271
  %format_finish_entry14 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %13, i32 0, i32 18, !dbg !1272
  %14 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_finish_entry14, align 8, !dbg !1272
  %15 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1273
  %call15 = call i32 %14(%struct.archive_write* %15), !dbg !1274
  store i32 %call15, i32* %r, align 4, !dbg !1275
  br label %if.end16, !dbg !1276

if.end16:                                         ; preds = %if.then13, %land.lhs.true, %if.end7
  %16 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1277
  %format_close = getelementptr inbounds %struct.archive_write, %struct.archive_write* %16, i32 0, i32 21, !dbg !1279
  %17 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_close, align 8, !dbg !1279
  %cmp17 = icmp ne i32 (%struct.archive_write*)* %17, null, !dbg !1280
  br i1 %cmp17, label %if.then18, label %if.end24, !dbg !1281

if.then18:                                        ; preds = %if.end16
  %18 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1282
  %format_close19 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %18, i32 0, i32 21, !dbg !1284
  %19 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_close19, align 8, !dbg !1284
  %20 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1285
  %call20 = call i32 %19(%struct.archive_write* %20), !dbg !1286
  store i32 %call20, i32* %r1, align 4, !dbg !1287
  %21 = load i32, i32* %r1, align 4, !dbg !1288
  %22 = load i32, i32* %r, align 4, !dbg !1290
  %cmp21 = icmp slt i32 %21, %22, !dbg !1291
  br i1 %cmp21, label %if.then22, label %if.end23, !dbg !1292

if.then22:                                        ; preds = %if.then18
  %23 = load i32, i32* %r1, align 4, !dbg !1293
  store i32 %23, i32* %r, align 4, !dbg !1294
  br label %if.end23, !dbg !1295

if.end23:                                         ; preds = %if.then22, %if.then18
  br label %if.end24, !dbg !1296

if.end24:                                         ; preds = %if.end23, %if.end16
  %24 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1297
  %filter_first = getelementptr inbounds %struct.archive_write, %struct.archive_write* %24, i32 0, i32 12, !dbg !1298
  %25 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter_first, align 8, !dbg !1298
  %call25 = call i32 @__archive_write_close_filter(%struct.archive_write_filter* %25), !dbg !1299
  store i32 %call25, i32* %r1, align 4, !dbg !1300
  %26 = load i32, i32* %r1, align 4, !dbg !1301
  %27 = load i32, i32* %r, align 4, !dbg !1303
  %cmp26 = icmp slt i32 %26, %27, !dbg !1304
  br i1 %cmp26, label %if.then27, label %if.end28, !dbg !1305

if.then27:                                        ; preds = %if.end24
  %28 = load i32, i32* %r1, align 4, !dbg !1306
  store i32 %28, i32* %r, align 4, !dbg !1307
  br label %if.end28, !dbg !1308

if.end28:                                         ; preds = %if.then27, %if.end24
  %29 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1309
  %archive29 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %29, i32 0, i32 0, !dbg !1311
  %state30 = getelementptr inbounds %struct.archive, %struct.archive* %archive29, i32 0, i32 1, !dbg !1312
  %30 = load i32, i32* %state30, align 4, !dbg !1312
  %cmp31 = icmp ne i32 %30, 32768, !dbg !1313
  br i1 %cmp31, label %if.then32, label %if.end35, !dbg !1314

if.then32:                                        ; preds = %if.end28
  %31 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1315
  %archive33 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %31, i32 0, i32 0, !dbg !1316
  %state34 = getelementptr inbounds %struct.archive, %struct.archive* %archive33, i32 0, i32 1, !dbg !1317
  store i32 32, i32* %state34, align 4, !dbg !1318
  br label %if.end35, !dbg !1315

if.end35:                                         ; preds = %if.then32, %if.end28
  %32 = load i32, i32* %r, align 4, !dbg !1319
  store i32 %32, i32* %retval, align 4, !dbg !1320
  br label %return, !dbg !1320

return:                                           ; preds = %if.end35, %if.then6, %if.then
  %33 = load i32, i32* %retval, align 4, !dbg !1321
  ret i32 %33, !dbg !1321
}

; Function Attrs: nounwind uwtable
define internal i64 @_archive_filter_bytes(%struct.archive* %_a, i32 %n) #0 !dbg !236 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %n.addr = alloca i32, align 4
  %f = alloca %struct.archive_write_filter*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1322, metadata !257), !dbg !1323
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !1324, metadata !257), !dbg !1325
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f, metadata !1326, metadata !257), !dbg !1327
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1328
  %1 = load i32, i32* %n.addr, align 4, !dbg !1329
  %call = call %struct.archive_write_filter* @filter_lookup(%struct.archive* %0, i32 %1), !dbg !1330
  store %struct.archive_write_filter* %call, %struct.archive_write_filter** %f, align 8, !dbg !1327
  %2 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !1331
  %cmp = icmp eq %struct.archive_write_filter* %2, null, !dbg !1332
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1331

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1333

cond.false:                                       ; preds = %entry
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !1335
  %bytes_written = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %3, i32 0, i32 0, !dbg !1337
  %4 = load i64, i64* %bytes_written, align 8, !dbg !1337
  br label %cond.end, !dbg !1338

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ -1, %cond.true ], [ %4, %cond.false ], !dbg !1339
  ret i64 %cond, !dbg !1341
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_filter_code(%struct.archive* %_a, i32 %n) #0 !dbg !240 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %n.addr = alloca i32, align 4
  %f = alloca %struct.archive_write_filter*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1342, metadata !257), !dbg !1343
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !1344, metadata !257), !dbg !1345
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f, metadata !1346, metadata !257), !dbg !1347
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1348
  %1 = load i32, i32* %n.addr, align 4, !dbg !1349
  %call = call %struct.archive_write_filter* @filter_lookup(%struct.archive* %0, i32 %1), !dbg !1350
  store %struct.archive_write_filter* %call, %struct.archive_write_filter** %f, align 8, !dbg !1347
  %2 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !1351
  %cmp = icmp eq %struct.archive_write_filter* %2, null, !dbg !1352
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1351

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1353

cond.false:                                       ; preds = %entry
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !1355
  %code = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %3, i32 0, i32 10, !dbg !1357
  %4 = load i32, i32* %code, align 8, !dbg !1357
  br label %cond.end, !dbg !1358

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ -1, %cond.true ], [ %4, %cond.false ], !dbg !1359
  ret i32 %cond, !dbg !1361
}

; Function Attrs: nounwind uwtable
define internal i8* @_archive_filter_name(%struct.archive* %_a, i32 %n) #0 !dbg !241 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %n.addr = alloca i32, align 4
  %f = alloca %struct.archive_write_filter*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1362, metadata !257), !dbg !1363
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !1364, metadata !257), !dbg !1365
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f, metadata !1366, metadata !257), !dbg !1367
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1368
  %1 = load i32, i32* %n.addr, align 4, !dbg !1369
  %call = call %struct.archive_write_filter* @filter_lookup(%struct.archive* %0, i32 %1), !dbg !1370
  store %struct.archive_write_filter* %call, %struct.archive_write_filter** %f, align 8, !dbg !1367
  %2 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !1371
  %cmp = icmp ne %struct.archive_write_filter* %2, null, !dbg !1372
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1371

cond.true:                                        ; preds = %entry
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !1373
  %name = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %3, i32 0, i32 9, !dbg !1375
  %4 = load i8*, i8** %name, align 8, !dbg !1375
  br label %cond.end, !dbg !1376

cond.false:                                       ; preds = %entry
  br label %cond.end, !dbg !1377

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i8* [ %4, %cond.true ], [ null, %cond.false ], !dbg !1379
  ret i8* %cond, !dbg !1381
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_write_filter_count(%struct.archive* %_a) #0 !dbg !242 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %p = alloca %struct.archive_write_filter*, align 8
  %count = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1382, metadata !257), !dbg !1383
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !1384, metadata !257), !dbg !1385
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1386
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !1387
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !1385
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %p, metadata !1388, metadata !257), !dbg !1389
  %2 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1390
  %filter_first = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 12, !dbg !1391
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter_first, align 8, !dbg !1391
  store %struct.archive_write_filter* %3, %struct.archive_write_filter** %p, align 8, !dbg !1389
  call void @llvm.dbg.declare(metadata i32* %count, metadata !1392, metadata !257), !dbg !1393
  store i32 0, i32* %count, align 4, !dbg !1393
  br label %while.cond, !dbg !1394

while.cond:                                       ; preds = %while.body, %entry
  %4 = load %struct.archive_write_filter*, %struct.archive_write_filter** %p, align 8, !dbg !1395
  %tobool = icmp ne %struct.archive_write_filter* %4, null, !dbg !1397
  br i1 %tobool, label %while.body, label %while.end, !dbg !1397

while.body:                                       ; preds = %while.cond
  %5 = load i32, i32* %count, align 4, !dbg !1398
  %inc = add nsw i32 %5, 1, !dbg !1398
  store i32 %inc, i32* %count, align 4, !dbg !1398
  %6 = load %struct.archive_write_filter*, %struct.archive_write_filter** %p, align 8, !dbg !1400
  %next_filter = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %6, i32 0, i32 2, !dbg !1401
  %7 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter, align 8, !dbg !1401
  store %struct.archive_write_filter* %7, %struct.archive_write_filter** %p, align 8, !dbg !1402
  br label %while.cond, !dbg !1403

while.end:                                        ; preds = %while.cond
  %8 = load i32, i32* %count, align 4, !dbg !1405
  ret i32 %8, !dbg !1406
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_write_free(%struct.archive* %_a) #0 !dbg !243 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %r = alloca i32, align 4
  %r1 = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1407, metadata !257), !dbg !1408
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !1409, metadata !257), !dbg !1410
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1411
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !1412
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !1410
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1413, metadata !257), !dbg !1414
  store i32 0, i32* %r, align 4, !dbg !1414
  call void @llvm.dbg.declare(metadata i32* %r1, metadata !1415, metadata !257), !dbg !1416
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1417
  %cmp = icmp eq %struct.archive* %2, null, !dbg !1419
  br i1 %cmp, label %if.then, label %if.end, !dbg !1420

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1421
  br label %return, !dbg !1421

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !1422

do.body:                                          ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1423, metadata !257), !dbg !1425
  %3 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1426
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %3, i32 0, i32 0, !dbg !1426
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1329217314, i32 65535, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.7, i32 0, i32 0)), !dbg !1426
  store i32 %call, i32* %magic_test, align 4, !dbg !1426
  %4 = load i32, i32* %magic_test, align 4, !dbg !1426
  %cmp1 = icmp eq i32 %4, -30, !dbg !1426
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !1426

if.then2:                                         ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1428
  br label %return, !dbg !1428

if.end3:                                          ; preds = %do.body
  br label %do.end, !dbg !1431

do.end:                                           ; preds = %if.end3
  %5 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1433
  %archive4 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 0, !dbg !1435
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive4, i32 0, i32 1, !dbg !1436
  %6 = load i32, i32* %state, align 4, !dbg !1436
  %cmp5 = icmp ne i32 %6, 32768, !dbg !1437
  br i1 %cmp5, label %if.then6, label %if.end9, !dbg !1438

if.then6:                                         ; preds = %do.end
  %7 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1439
  %archive7 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !1440
  %call8 = call i32 @archive_write_close(%struct.archive* %archive7), !dbg !1441
  store i32 %call8, i32* %r, align 4, !dbg !1442
  br label %if.end9, !dbg !1443

if.end9:                                          ; preds = %if.then6, %do.end
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1444
  %format_free = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 22, !dbg !1446
  %9 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free, align 8, !dbg !1446
  %cmp10 = icmp ne i32 (%struct.archive_write*)* %9, null, !dbg !1447
  br i1 %cmp10, label %if.then11, label %if.end17, !dbg !1448

if.then11:                                        ; preds = %if.end9
  %10 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1449
  %format_free12 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %10, i32 0, i32 22, !dbg !1451
  %11 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free12, align 8, !dbg !1451
  %12 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1452
  %call13 = call i32 %11(%struct.archive_write* %12), !dbg !1453
  store i32 %call13, i32* %r1, align 4, !dbg !1454
  %13 = load i32, i32* %r1, align 4, !dbg !1455
  %14 = load i32, i32* %r, align 4, !dbg !1457
  %cmp14 = icmp slt i32 %13, %14, !dbg !1458
  br i1 %cmp14, label %if.then15, label %if.end16, !dbg !1459

if.then15:                                        ; preds = %if.then11
  %15 = load i32, i32* %r1, align 4, !dbg !1460
  store i32 %15, i32* %r, align 4, !dbg !1461
  br label %if.end16, !dbg !1462

if.end16:                                         ; preds = %if.then15, %if.then11
  br label %if.end17, !dbg !1463

if.end17:                                         ; preds = %if.end16, %if.end9
  %16 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1464
  call void @__archive_write_filters_free(%struct.archive* %16), !dbg !1465
  %17 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1466
  %nulls = getelementptr inbounds %struct.archive_write, %struct.archive_write* %17, i32 0, i32 4, !dbg !1467
  %18 = load i8*, i8** %nulls, align 8, !dbg !1467
  %19 = ptrtoint i8* %18 to i64, !dbg !1468
  %20 = inttoptr i64 %19 to i8*, !dbg !1469
  call void @free(i8* %20) #6, !dbg !1470
  %21 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1471
  %archive18 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %21, i32 0, i32 0, !dbg !1472
  %error_string = getelementptr inbounds %struct.archive, %struct.archive* %archive18, i32 0, i32 10, !dbg !1473
  call void @archive_string_free(%struct.archive_string* %error_string), !dbg !1474
  %22 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1475
  %passphrase = getelementptr inbounds %struct.archive_write, %struct.archive_write* %22, i32 0, i32 23, !dbg !1477
  %23 = load i8*, i8** %passphrase, align 8, !dbg !1477
  %cmp19 = icmp ne i8* %23, null, !dbg !1478
  br i1 %cmp19, label %if.then20, label %if.end25, !dbg !1479

if.then20:                                        ; preds = %if.end17
  %24 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1480
  %passphrase21 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %24, i32 0, i32 23, !dbg !1482
  %25 = load i8*, i8** %passphrase21, align 8, !dbg !1482
  %26 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1483
  %passphrase22 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %26, i32 0, i32 23, !dbg !1484
  %27 = load i8*, i8** %passphrase22, align 8, !dbg !1484
  %call23 = call i64 @strlen(i8* %27) #7, !dbg !1485
  call void @llvm.memset.p0i8.i64(i8* %25, i8 0, i64 %call23, i32 1, i1 false), !dbg !1486
  %28 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1488
  %passphrase24 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %28, i32 0, i32 23, !dbg !1489
  %29 = load i8*, i8** %passphrase24, align 8, !dbg !1489
  call void @free(i8* %29) #6, !dbg !1490
  br label %if.end25, !dbg !1491

if.end25:                                         ; preds = %if.then20, %if.end17
  %30 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1492
  %archive26 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %30, i32 0, i32 0, !dbg !1493
  %magic = getelementptr inbounds %struct.archive, %struct.archive* %archive26, i32 0, i32 0, !dbg !1494
  store i32 0, i32* %magic, align 8, !dbg !1495
  %31 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1496
  %archive27 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %31, i32 0, i32 0, !dbg !1497
  %call28 = call i32 @__archive_clean(%struct.archive* %archive27), !dbg !1498
  %32 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1499
  %33 = bitcast %struct.archive_write* %32 to i8*, !dbg !1499
  call void @free(i8* %33) #6, !dbg !1500
  %34 = load i32, i32* %r, align 4, !dbg !1501
  store i32 %34, i32* %retval, align 4, !dbg !1502
  br label %return, !dbg !1502

return:                                           ; preds = %if.end25, %if.then2, %if.then
  %35 = load i32, i32* %retval, align 4, !dbg !1503
  ret i32 %35, !dbg !1503
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_write_header(%struct.archive* %_a, %struct.archive_entry* %entry1) #0 !dbg !244 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %a = alloca %struct.archive_write*, align 8
  %ret = alloca i32, align 4
  %r2 = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1504, metadata !257), !dbg !1505
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1506, metadata !257), !dbg !1507
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !1508, metadata !257), !dbg !1509
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1510
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !1511
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !1509
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !1512, metadata !257), !dbg !1513
  call void @llvm.dbg.declare(metadata i32* %r2, metadata !1514, metadata !257), !dbg !1515
  br label %do.body, !dbg !1516

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1517, metadata !257), !dbg !1519
  %2 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1520
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 0, !dbg !1520
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1329217314, i32 6, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.8, i32 0, i32 0)), !dbg !1520
  store i32 %call, i32* %magic_test, align 4, !dbg !1520
  %3 = load i32, i32* %magic_test, align 4, !dbg !1520
  %cmp = icmp eq i32 %3, -30, !dbg !1520
  br i1 %cmp, label %if.then, label %if.end, !dbg !1520

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1522
  br label %return, !dbg !1522

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1525

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1527
  %archive2 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 0, !dbg !1528
  call void @archive_clear_error(%struct.archive* %archive2), !dbg !1529
  %5 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1530
  %format_write_header = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 19, !dbg !1532
  %6 = load i32 (%struct.archive_write*, %struct.archive_entry*)*, i32 (%struct.archive_write*, %struct.archive_entry*)** %format_write_header, align 8, !dbg !1532
  %cmp3 = icmp eq i32 (%struct.archive_write*, %struct.archive_entry*)* %6, null, !dbg !1533
  br i1 %cmp3, label %if.then4, label %if.end7, !dbg !1534

if.then4:                                         ; preds = %do.end
  %7 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1535
  %archive5 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !1537
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive5, i32 -1, i8* getelementptr inbounds ([55 x i8], [55 x i8]* @.str.9, i32 0, i32 0)), !dbg !1538
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1539
  %archive6 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 0, !dbg !1540
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive6, i32 0, i32 1, !dbg !1541
  store i32 32768, i32* %state, align 4, !dbg !1542
  store i32 -30, i32* %retval, align 4, !dbg !1543
  br label %return, !dbg !1543

if.end7:                                          ; preds = %do.end
  %9 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1544
  %archive8 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %9, i32 0, i32 0, !dbg !1545
  %call9 = call i32 @archive_write_finish_entry(%struct.archive* %archive8), !dbg !1546
  store i32 %call9, i32* %ret, align 4, !dbg !1547
  %10 = load i32, i32* %ret, align 4, !dbg !1548
  %cmp10 = icmp eq i32 %10, -30, !dbg !1550
  br i1 %cmp10, label %if.then11, label %if.end14, !dbg !1551

if.then11:                                        ; preds = %if.end7
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1552
  %archive12 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 0, !dbg !1554
  %state13 = getelementptr inbounds %struct.archive, %struct.archive* %archive12, i32 0, i32 1, !dbg !1555
  store i32 32768, i32* %state13, align 4, !dbg !1556
  store i32 -30, i32* %retval, align 4, !dbg !1557
  br label %return, !dbg !1557

if.end14:                                         ; preds = %if.end7
  %12 = load i32, i32* %ret, align 4, !dbg !1558
  %cmp15 = icmp slt i32 %12, 0, !dbg !1560
  br i1 %cmp15, label %land.lhs.true, label %if.end18, !dbg !1561

land.lhs.true:                                    ; preds = %if.end14
  %13 = load i32, i32* %ret, align 4, !dbg !1562
  %cmp16 = icmp ne i32 %13, -20, !dbg !1564
  br i1 %cmp16, label %if.then17, label %if.end18, !dbg !1565

if.then17:                                        ; preds = %land.lhs.true
  %14 = load i32, i32* %ret, align 4, !dbg !1566
  store i32 %14, i32* %retval, align 4, !dbg !1567
  br label %return, !dbg !1567

if.end18:                                         ; preds = %land.lhs.true, %if.end14
  %15 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1568
  %skip_file_set = getelementptr inbounds %struct.archive_write, %struct.archive_write* %15, i32 0, i32 1, !dbg !1570
  %16 = load i32, i32* %skip_file_set, align 8, !dbg !1570
  %tobool = icmp ne i32 %16, 0, !dbg !1568
  br i1 %tobool, label %land.lhs.true19, label %if.end33, !dbg !1571

land.lhs.true19:                                  ; preds = %if.end18
  %17 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1572
  %call20 = call i32 @archive_entry_dev_is_set(%struct.archive_entry* %17), !dbg !1573
  %tobool21 = icmp ne i32 %call20, 0, !dbg !1573
  br i1 %tobool21, label %land.lhs.true22, label %if.end33, !dbg !1574

land.lhs.true22:                                  ; preds = %land.lhs.true19
  %18 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1575
  %call23 = call i32 @archive_entry_ino_is_set(%struct.archive_entry* %18), !dbg !1576
  %tobool24 = icmp ne i32 %call23, 0, !dbg !1576
  br i1 %tobool24, label %land.lhs.true25, label %if.end33, !dbg !1577

land.lhs.true25:                                  ; preds = %land.lhs.true22
  %19 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1578
  %call26 = call i64 @archive_entry_dev(%struct.archive_entry* %19), !dbg !1579
  %20 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1580
  %skip_file_dev = getelementptr inbounds %struct.archive_write, %struct.archive_write* %20, i32 0, i32 2, !dbg !1581
  %21 = load i64, i64* %skip_file_dev, align 8, !dbg !1581
  %cmp27 = icmp eq i64 %call26, %21, !dbg !1582
  br i1 %cmp27, label %land.lhs.true28, label %if.end33, !dbg !1583

land.lhs.true28:                                  ; preds = %land.lhs.true25
  %22 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1584
  %call29 = call i64 @archive_entry_ino64(%struct.archive_entry* %22), !dbg !1585
  %23 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1586
  %skip_file_ino = getelementptr inbounds %struct.archive_write, %struct.archive_write* %23, i32 0, i32 3, !dbg !1587
  %24 = load i64, i64* %skip_file_ino, align 8, !dbg !1587
  %cmp30 = icmp eq i64 %call29, %24, !dbg !1588
  br i1 %cmp30, label %if.then31, label %if.end33, !dbg !1589

if.then31:                                        ; preds = %land.lhs.true28
  %25 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1591
  %archive32 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %25, i32 0, i32 0, !dbg !1593
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive32, i32 0, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.10, i32 0, i32 0)), !dbg !1594
  store i32 -25, i32* %retval, align 4, !dbg !1595
  br label %return, !dbg !1595

if.end33:                                         ; preds = %land.lhs.true28, %land.lhs.true25, %land.lhs.true22, %land.lhs.true19, %if.end18
  %26 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1596
  %format_write_header34 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %26, i32 0, i32 19, !dbg !1597
  %27 = load i32 (%struct.archive_write*, %struct.archive_entry*)*, i32 (%struct.archive_write*, %struct.archive_entry*)** %format_write_header34, align 8, !dbg !1597
  %28 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1598
  %29 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1599
  %call35 = call i32 %27(%struct.archive_write* %28, %struct.archive_entry* %29), !dbg !1600
  store i32 %call35, i32* %r2, align 4, !dbg !1601
  %30 = load i32, i32* %r2, align 4, !dbg !1602
  %cmp36 = icmp eq i32 %30, -25, !dbg !1604
  br i1 %cmp36, label %if.then37, label %if.end38, !dbg !1605

if.then37:                                        ; preds = %if.end33
  store i32 -25, i32* %retval, align 4, !dbg !1606
  br label %return, !dbg !1606

if.end38:                                         ; preds = %if.end33
  %31 = load i32, i32* %r2, align 4, !dbg !1608
  %cmp39 = icmp eq i32 %31, -30, !dbg !1610
  br i1 %cmp39, label %if.then40, label %if.end43, !dbg !1611

if.then40:                                        ; preds = %if.end38
  %32 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1612
  %archive41 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %32, i32 0, i32 0, !dbg !1614
  %state42 = getelementptr inbounds %struct.archive, %struct.archive* %archive41, i32 0, i32 1, !dbg !1615
  store i32 32768, i32* %state42, align 4, !dbg !1616
  store i32 -30, i32* %retval, align 4, !dbg !1617
  br label %return, !dbg !1617

if.end43:                                         ; preds = %if.end38
  %33 = load i32, i32* %r2, align 4, !dbg !1618
  %34 = load i32, i32* %ret, align 4, !dbg !1620
  %cmp44 = icmp slt i32 %33, %34, !dbg !1621
  br i1 %cmp44, label %if.then45, label %if.end46, !dbg !1622

if.then45:                                        ; preds = %if.end43
  %35 = load i32, i32* %r2, align 4, !dbg !1623
  store i32 %35, i32* %ret, align 4, !dbg !1624
  br label %if.end46, !dbg !1625

if.end46:                                         ; preds = %if.then45, %if.end43
  %36 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1626
  %archive47 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %36, i32 0, i32 0, !dbg !1627
  %state48 = getelementptr inbounds %struct.archive, %struct.archive* %archive47, i32 0, i32 1, !dbg !1628
  store i32 4, i32* %state48, align 4, !dbg !1629
  %37 = load i32, i32* %ret, align 4, !dbg !1630
  store i32 %37, i32* %retval, align 4, !dbg !1631
  br label %return, !dbg !1631

return:                                           ; preds = %if.end46, %if.then40, %if.then37, %if.then31, %if.then17, %if.then11, %if.then4, %if.then
  %38 = load i32, i32* %retval, align 4, !dbg !1632
  ret i32 %38, !dbg !1632
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_write_finish_entry(%struct.archive* %_a) #0 !dbg !245 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %ret = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1633, metadata !257), !dbg !1634
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !1635, metadata !257), !dbg !1636
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1637
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !1638
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !1636
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !1639, metadata !257), !dbg !1640
  store i32 0, i32* %ret, align 4, !dbg !1640
  br label %do.body, !dbg !1641

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1642, metadata !257), !dbg !1644
  %2 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1645
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 0, !dbg !1645
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1329217314, i32 6, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.11, i32 0, i32 0)), !dbg !1645
  store i32 %call, i32* %magic_test, align 4, !dbg !1645
  %3 = load i32, i32* %magic_test, align 4, !dbg !1645
  %cmp = icmp eq i32 %3, -30, !dbg !1645
  br i1 %cmp, label %if.then, label %if.end, !dbg !1645

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1647
  br label %return, !dbg !1647

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1650

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1652
  %archive1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 0, !dbg !1654
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive1, i32 0, i32 1, !dbg !1655
  %5 = load i32, i32* %state, align 4, !dbg !1655
  %and = and i32 %5, 4, !dbg !1656
  %tobool = icmp ne i32 %and, 0, !dbg !1656
  br i1 %tobool, label %land.lhs.true, label %if.end6, !dbg !1657

land.lhs.true:                                    ; preds = %do.end
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1658
  %format_finish_entry = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 18, !dbg !1660
  %7 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_finish_entry, align 8, !dbg !1660
  %cmp2 = icmp ne i32 (%struct.archive_write*)* %7, null, !dbg !1661
  br i1 %cmp2, label %if.then3, label %if.end6, !dbg !1662

if.then3:                                         ; preds = %land.lhs.true
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1664
  %format_finish_entry4 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 18, !dbg !1665
  %9 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_finish_entry4, align 8, !dbg !1665
  %10 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1666
  %call5 = call i32 %9(%struct.archive_write* %10), !dbg !1667
  store i32 %call5, i32* %ret, align 4, !dbg !1668
  br label %if.end6, !dbg !1669

if.end6:                                          ; preds = %if.then3, %land.lhs.true, %do.end
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1670
  %archive7 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 0, !dbg !1671
  %state8 = getelementptr inbounds %struct.archive, %struct.archive* %archive7, i32 0, i32 1, !dbg !1672
  store i32 2, i32* %state8, align 4, !dbg !1673
  %12 = load i32, i32* %ret, align 4, !dbg !1674
  store i32 %12, i32* %retval, align 4, !dbg !1675
  br label %return, !dbg !1675

return:                                           ; preds = %if.end6, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !1676
  ret i32 %13, !dbg !1676
}

; Function Attrs: nounwind uwtable
define internal i64 @_archive_write_data(%struct.archive* %_a, i8* %buff, i64 %s) #0 !dbg !246 {
entry:
  %retval = alloca i64, align 8
  %_a.addr = alloca %struct.archive*, align 8
  %buff.addr = alloca i8*, align 8
  %s.addr = alloca i64, align 8
  %a = alloca %struct.archive_write*, align 8
  %max_write = alloca i64, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1677, metadata !257), !dbg !1678
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !1679, metadata !257), !dbg !1680
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !1681, metadata !257), !dbg !1682
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !1683, metadata !257), !dbg !1684
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1685
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !1686
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !1684
  call void @llvm.dbg.declare(metadata i64* %max_write, metadata !1687, metadata !257), !dbg !1689
  store i64 2147483647, i64* %max_write, align 8, !dbg !1689
  br label %do.body, !dbg !1690

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1691, metadata !257), !dbg !1693
  %2 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1694
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 0, !dbg !1694
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1329217314, i32 4, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.12, i32 0, i32 0)), !dbg !1694
  store i32 %call, i32* %magic_test, align 4, !dbg !1694
  %3 = load i32, i32* %magic_test, align 4, !dbg !1694
  %cmp = icmp eq i32 %3, -30, !dbg !1694
  br i1 %cmp, label %if.then, label %if.end, !dbg !1694

if.then:                                          ; preds = %do.body
  store i64 -30, i64* %retval, align 8, !dbg !1696
  br label %return, !dbg !1696

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1699

do.end:                                           ; preds = %if.end
  %4 = load i64, i64* %s.addr, align 8, !dbg !1701
  %cmp1 = icmp ugt i64 %4, 2147483647, !dbg !1703
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !1704

if.then2:                                         ; preds = %do.end
  store i64 2147483647, i64* %s.addr, align 8, !dbg !1705
  br label %if.end3, !dbg !1706

if.end3:                                          ; preds = %if.then2, %do.end
  %5 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1707
  %archive4 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 0, !dbg !1708
  call void @archive_clear_error(%struct.archive* %archive4), !dbg !1709
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1710
  %format_write_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 20, !dbg !1711
  %7 = load i64 (%struct.archive_write*, i8*, i64)*, i64 (%struct.archive_write*, i8*, i64)** %format_write_data, align 8, !dbg !1711
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1712
  %9 = load i8*, i8** %buff.addr, align 8, !dbg !1713
  %10 = load i64, i64* %s.addr, align 8, !dbg !1714
  %call5 = call i64 %7(%struct.archive_write* %8, i8* %9, i64 %10), !dbg !1715
  store i64 %call5, i64* %retval, align 8, !dbg !1716
  br label %return, !dbg !1716

return:                                           ; preds = %if.end3, %if.then
  %11 = load i64, i64* %retval, align 8, !dbg !1717
  ret i64 %11, !dbg !1717
}

; Function Attrs: nounwind uwtable
define internal %struct.archive_write_filter* @filter_lookup(%struct.archive* %_a, i32 %n) #0 !dbg !237 {
entry:
  %retval = alloca %struct.archive_write_filter*, align 8
  %_a.addr = alloca %struct.archive*, align 8
  %n.addr = alloca i32, align 4
  %a = alloca %struct.archive_write*, align 8
  %f = alloca %struct.archive_write_filter*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1718, metadata !257), !dbg !1719
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !1720, metadata !257), !dbg !1721
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !1722, metadata !257), !dbg !1723
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1724
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !1725
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !1723
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f, metadata !1726, metadata !257), !dbg !1727
  %2 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1728
  %filter_first = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 12, !dbg !1729
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter_first, align 8, !dbg !1729
  store %struct.archive_write_filter* %3, %struct.archive_write_filter** %f, align 8, !dbg !1727
  %4 = load i32, i32* %n.addr, align 4, !dbg !1730
  %cmp = icmp eq i32 %4, -1, !dbg !1732
  br i1 %cmp, label %if.then, label %if.end, !dbg !1733

if.then:                                          ; preds = %entry
  %5 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1734
  %filter_last = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 13, !dbg !1735
  %6 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter_last, align 8, !dbg !1735
  store %struct.archive_write_filter* %6, %struct.archive_write_filter** %retval, align 8, !dbg !1736
  br label %return, !dbg !1736

if.end:                                           ; preds = %entry
  %7 = load i32, i32* %n.addr, align 4, !dbg !1737
  %cmp1 = icmp slt i32 %7, 0, !dbg !1739
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !1740

if.then2:                                         ; preds = %if.end
  store %struct.archive_write_filter* null, %struct.archive_write_filter** %retval, align 8, !dbg !1741
  br label %return, !dbg !1741

if.end3:                                          ; preds = %if.end
  br label %while.cond, !dbg !1742

while.cond:                                       ; preds = %while.body, %if.end3
  %8 = load i32, i32* %n.addr, align 4, !dbg !1743
  %cmp4 = icmp sgt i32 %8, 0, !dbg !1745
  br i1 %cmp4, label %land.rhs, label %land.end, !dbg !1746

land.rhs:                                         ; preds = %while.cond
  %9 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !1747
  %cmp5 = icmp ne %struct.archive_write_filter* %9, null, !dbg !1749
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %10 = phi i1 [ false, %while.cond ], [ %cmp5, %land.rhs ]
  br i1 %10, label %while.body, label %while.end, !dbg !1750

while.body:                                       ; preds = %land.end
  %11 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !1752
  %next_filter = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %11, i32 0, i32 2, !dbg !1754
  %12 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter, align 8, !dbg !1754
  store %struct.archive_write_filter* %12, %struct.archive_write_filter** %f, align 8, !dbg !1755
  %13 = load i32, i32* %n.addr, align 4, !dbg !1756
  %dec = add nsw i32 %13, -1, !dbg !1756
  store i32 %dec, i32* %n.addr, align 4, !dbg !1756
  br label %while.cond, !dbg !1757

while.end:                                        ; preds = %land.end
  %14 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !1759
  store %struct.archive_write_filter* %14, %struct.archive_write_filter** %retval, align 8, !dbg !1760
  br label %return, !dbg !1760

return:                                           ; preds = %while.end, %if.then2, %if.then
  %15 = load %struct.archive_write_filter*, %struct.archive_write_filter** %retval, align 8, !dbg !1761
  ret %struct.archive_write_filter* %15, !dbg !1761
}

declare i32 @archive_write_close(%struct.archive*) #3

declare void @archive_string_free(%struct.archive_string*) #3

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #5

declare i32 @__archive_clean(%struct.archive*) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #3

declare i32 @archive_write_finish_entry(%struct.archive*) #3

declare i32 @archive_entry_dev_is_set(%struct.archive_entry*) #3

declare i32 @archive_entry_ino_is_set(%struct.archive_entry*) #3

declare i64 @archive_entry_dev(%struct.archive_entry*) #3

declare i64 @archive_entry_ino64(%struct.archive_entry*) #3

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind }
attributes #7 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!253, !254}
!llvm.ident = !{!255}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !203, globals: !250)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !123, !191, !192, !43, !193, !196, !95, !80, !45}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write", file: !6, line: 72, size: 2816, align: 64, elements: !7)
!6 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!7 = !{!8, !110, !111, !112, !113, !117, !118, !124, !130, !133, !134, !135, !136, !162, !163, !164, !165, !169, !173, !174, !178, !182, !183, !184, !185, !190}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !5, file: !6, line: 73, baseType: !9, size: 1280, align: 64)
!9 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !10, line: 89, size: 1280, align: 64, elements: !11)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !{!12, !14, !15, !83, !84, !85, !86, !87, !88, !89, !90, !98, !99, !100, !101, !104, !105, !106, !107, !108, !109}
!12 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !9, file: !10, line: 96, baseType: !13, size: 32, align: 32)
!13 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !9, file: !10, line: 97, baseType: !13, size: 32, align: 32, offset: 32)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !9, file: !10, line: 103, baseType: !16, size: 64, align: 64, offset: 64)
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !17, size: 64, align: 64)
!17 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !10, line: 63, size: 832, align: 64, elements: !18)
!18 = !{!19, !25, !26, !33, !34, !48, !54, !59, !60, !67, !68, !72, !76}
!19 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !17, file: !10, line: 64, baseType: !20, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !21, size: 64, align: 64)
!21 = !DISubroutineType(types: !22)
!22 = !{!23, !24}
!23 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !17, file: !10, line: 65, baseType: !20, size: 64, align: 64, offset: 64)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !17, file: !10, line: 66, baseType: !27, size: 64, align: 64, offset: 128)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DISubroutineType(types: !29)
!29 = !{!23, !24, !30}
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!31 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !32, line: 180, flags: DIFlagFwdDecl)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!33 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !17, file: !10, line: 68, baseType: !20, size: 64, align: 64, offset: 192)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !17, file: !10, line: 69, baseType: !35, size: 64, align: 64, offset: 256)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DISubroutineType(types: !37)
!37 = !{!38, !24, !43, !45}
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !39, line: 102, baseType: !40)
!39 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !41, line: 172, baseType: !42)
!41 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!42 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !46, line: 62, baseType: !47)
!46 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!47 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !17, file: !10, line: 71, baseType: !49, size: 64, align: 64, offset: 320)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DISubroutineType(types: !51)
!51 = !{!38, !24, !43, !45, !52}
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !53, line: 40, baseType: !42)
!53 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!54 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !17, file: !10, line: 74, baseType: !55, size: 64, align: 64, offset: 384)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DISubroutineType(types: !57)
!57 = !{!23, !24, !58}
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !17, file: !10, line: 76, baseType: !27, size: 64, align: 64, offset: 448)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !17, file: !10, line: 78, baseType: !61, size: 64, align: 64, offset: 512)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DISubroutineType(types: !63)
!63 = !{!23, !24, !64, !65, !66}
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !17, file: !10, line: 81, baseType: !20, size: 64, align: 64, offset: 576)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !17, file: !10, line: 82, baseType: !69, size: 64, align: 64, offset: 640)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DISubroutineType(types: !71)
!71 = !{!52, !24, !23}
!72 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !17, file: !10, line: 83, baseType: !73, size: 64, align: 64, offset: 704)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!74 = !DISubroutineType(types: !75)
!75 = !{!23, !24, !23}
!76 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !17, file: !10, line: 84, baseType: !77, size: 64, align: 64, offset: 768)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DISubroutineType(types: !79)
!79 = !{!80, !24, !23}
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !82)
!82 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !9, file: !10, line: 105, baseType: !23, size: 32, align: 32, offset: 128)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !9, file: !10, line: 106, baseType: !80, size: 64, align: 64, offset: 192)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !9, file: !10, line: 108, baseType: !23, size: 32, align: 32, offset: 256)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !9, file: !10, line: 109, baseType: !80, size: 64, align: 64, offset: 320)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !9, file: !10, line: 112, baseType: !23, size: 32, align: 32, offset: 384)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !9, file: !10, line: 114, baseType: !23, size: 32, align: 32, offset: 416)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !9, file: !10, line: 115, baseType: !80, size: 64, align: 64, offset: 448)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !9, file: !10, line: 116, baseType: !91, size: 192, align: 64, offset: 512)
!91 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !92, line: 58, size: 192, align: 64, elements: !93)
!92 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!93 = !{!94, !96, !97}
!94 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !91, file: !92, line: 59, baseType: !95, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !91, file: !92, line: 60, baseType: !45, size: 64, align: 64, offset: 64)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !91, file: !92, line: 61, baseType: !45, size: 64, align: 64, offset: 128)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !9, file: !10, line: 118, baseType: !95, size: 64, align: 64, offset: 704)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !9, file: !10, line: 119, baseType: !13, size: 32, align: 32, offset: 768)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !9, file: !10, line: 120, baseType: !13, size: 32, align: 32, offset: 800)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !9, file: !10, line: 121, baseType: !102, size: 64, align: 64, offset: 832)
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!103 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !92, line: 70, flags: DIFlagFwdDecl)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !9, file: !10, line: 127, baseType: !80, size: 64, align: 64, offset: 896)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !9, file: !10, line: 128, baseType: !52, size: 64, align: 64, offset: 960)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !9, file: !10, line: 129, baseType: !52, size: 64, align: 64, offset: 1024)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !9, file: !10, line: 130, baseType: !45, size: 64, align: 64, offset: 1088)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !9, file: !10, line: 137, baseType: !82, size: 8, align: 8, offset: 1152)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !9, file: !10, line: 138, baseType: !45, size: 64, align: 64, offset: 1216)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !5, file: !6, line: 76, baseType: !23, size: 32, align: 32, offset: 1280)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !5, file: !6, line: 77, baseType: !52, size: 64, align: 64, offset: 1344)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !5, file: !6, line: 78, baseType: !52, size: 64, align: 64, offset: 1408)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "nulls", scope: !5, file: !6, line: 81, baseType: !114, size: 64, align: 64, offset: 1472)
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !115, size: 64, align: 64)
!115 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !116)
!116 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "null_length", scope: !5, file: !6, line: 82, baseType: !45, size: 64, align: 64, offset: 1536)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "client_opener", scope: !5, file: !6, line: 85, baseType: !119, size: 64, align: 64, offset: 1600)
!119 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !120, size: 64, align: 64)
!120 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !32, line: 241, baseType: !121)
!121 = !DISubroutineType(types: !122)
!122 = !{!23, !24, !123}
!123 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "client_writer", scope: !5, file: !6, line: 86, baseType: !125, size: 64, align: 64, offset: 1664)
!125 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !126, size: 64, align: 64)
!126 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_write_callback", file: !32, line: 237, baseType: !127)
!127 = !DISubroutineType(types: !128)
!128 = !{!129, !24, !123, !43, !45}
!129 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !32, line: 95, baseType: !38)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "client_closer", scope: !5, file: !6, line: 87, baseType: !131, size: 64, align: 64, offset: 1728)
!131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !132, size: 64, align: 64)
!132 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !32, line: 243, baseType: !121)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !5, file: !6, line: 88, baseType: !123, size: 64, align: 64, offset: 1792)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !5, file: !6, line: 96, baseType: !23, size: 32, align: 32, offset: 1856)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !5, file: !6, line: 97, baseType: !23, size: 32, align: 32, offset: 1888)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "filter_first", scope: !5, file: !6, line: 102, baseType: !137, size: 64, align: 64, offset: 1920)
!137 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !138, size: 64, align: 64)
!138 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_filter", file: !6, line: 43, size: 768, align: 64, elements: !139)
!139 = !{!140, !141, !142, !143, !147, !151, !155, !156, !157, !158, !159, !160, !161}
!140 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_written", scope: !138, file: !6, line: 44, baseType: !52, size: 64, align: 64)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !138, file: !6, line: 45, baseType: !24, size: 64, align: 64, offset: 64)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "next_filter", scope: !138, file: !6, line: 46, baseType: !137, size: 64, align: 64, offset: 128)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !138, file: !6, line: 47, baseType: !144, size: 64, align: 64, offset: 192)
!144 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !145, size: 64, align: 64)
!145 = !DISubroutineType(types: !146)
!146 = !{!23, !137, !80, !80}
!147 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !138, file: !6, line: 49, baseType: !148, size: 64, align: 64, offset: 256)
!148 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !149, size: 64, align: 64)
!149 = !DISubroutineType(types: !150)
!150 = !{!23, !137}
!151 = !DIDerivedType(tag: DW_TAG_member, name: "write", scope: !138, file: !6, line: 50, baseType: !152, size: 64, align: 64, offset: 320)
!152 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !153, size: 64, align: 64)
!153 = !DISubroutineType(types: !154)
!154 = !{!23, !137, !43, !45}
!155 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !138, file: !6, line: 51, baseType: !148, size: 64, align: 64, offset: 384)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !138, file: !6, line: 52, baseType: !148, size: 64, align: 64, offset: 448)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !138, file: !6, line: 53, baseType: !123, size: 64, align: 64, offset: 512)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !138, file: !6, line: 54, baseType: !80, size: 64, align: 64, offset: 576)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !138, file: !6, line: 55, baseType: !23, size: 32, align: 32, offset: 640)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !138, file: !6, line: 56, baseType: !23, size: 32, align: 32, offset: 672)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !138, file: !6, line: 57, baseType: !23, size: 32, align: 32, offset: 704)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "filter_last", scope: !5, file: !6, line: 103, baseType: !137, size: 64, align: 64, offset: 1984)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "format_data", scope: !5, file: !6, line: 109, baseType: !123, size: 64, align: 64, offset: 2048)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "format_name", scope: !5, file: !6, line: 110, baseType: !80, size: 64, align: 64, offset: 2112)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "format_init", scope: !5, file: !6, line: 111, baseType: !166, size: 64, align: 64, offset: 2176)
!166 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !167, size: 64, align: 64)
!167 = !DISubroutineType(types: !168)
!168 = !{!23, !4}
!169 = !DIDerivedType(tag: DW_TAG_member, name: "format_options", scope: !5, file: !6, line: 112, baseType: !170, size: 64, align: 64, offset: 2240)
!170 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !171, size: 64, align: 64)
!171 = !DISubroutineType(types: !172)
!172 = !{!23, !4, !80, !80}
!173 = !DIDerivedType(tag: DW_TAG_member, name: "format_finish_entry", scope: !5, file: !6, line: 114, baseType: !166, size: 64, align: 64, offset: 2304)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_header", scope: !5, file: !6, line: 115, baseType: !175, size: 64, align: 64, offset: 2368)
!175 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !176, size: 64, align: 64)
!176 = !DISubroutineType(types: !177)
!177 = !{!23, !4, !30}
!178 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_data", scope: !5, file: !6, line: 117, baseType: !179, size: 64, align: 64, offset: 2432)
!179 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !180, size: 64, align: 64)
!180 = !DISubroutineType(types: !181)
!181 = !{!38, !4, !43, !45}
!182 = !DIDerivedType(tag: DW_TAG_member, name: "format_close", scope: !5, file: !6, line: 119, baseType: !166, size: 64, align: 64, offset: 2496)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "format_free", scope: !5, file: !6, line: 120, baseType: !166, size: 64, align: 64, offset: 2560)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !5, file: !6, line: 126, baseType: !95, size: 64, align: 64, offset: 2624)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_callback", scope: !5, file: !6, line: 127, baseType: !186, size: 64, align: 64, offset: 2688)
!186 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !187, size: 64, align: 64)
!187 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !32, line: 256, baseType: !188)
!188 = !DISubroutineType(types: !189)
!189 = !{!80, !24, !123}
!190 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_client_data", scope: !5, file: !6, line: 128, baseType: !123, size: 64, align: 64, offset: 2752)
!191 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !116, size: 64, align: 64)
!192 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !53, line: 122, baseType: !47)
!193 = !DIDerivedType(tag: DW_TAG_typedef, name: "dev_t", file: !194, line: 60, baseType: !195)
!194 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!195 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !41, line: 124, baseType: !47)
!196 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !197, size: 64, align: 64)
!197 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_none", file: !1, line: 75, size: 256, align: 64, elements: !198)
!198 = !{!199, !200, !201, !202}
!199 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_size", scope: !197, file: !1, line: 76, baseType: !45, size: 64, align: 64)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "avail", scope: !197, file: !1, line: 77, baseType: !45, size: 64, align: 64, offset: 64)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !197, file: !1, line: 78, baseType: !95, size: 64, align: 64, offset: 128)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !197, file: !1, line: 79, baseType: !95, size: 64, align: 64, offset: 192)
!203 = !{!204, !207, !208, !209, !210, !211, !214, !217, !218, !219, !220, !223, !226, !229, !232, !235, !236, !237, !240, !241, !242, !243, !244, !245, !246, !247, !248, !249}
!204 = distinct !DISubprogram(name: "archive_write_new", scope: !1, file: !1, line: 107, type: !205, isLocal: false, isDefinition: true, scopeLine: 108, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!205 = !DISubroutineType(types: !206)
!206 = !{!24}
!207 = distinct !DISubprogram(name: "archive_write_set_bytes_per_block", scope: !1, file: !1, line: 141, type: !74, isLocal: false, isDefinition: true, scopeLine: 142, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!208 = distinct !DISubprogram(name: "archive_write_get_bytes_per_block", scope: !1, file: !1, line: 154, type: !21, isLocal: false, isDefinition: true, scopeLine: 155, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!209 = distinct !DISubprogram(name: "archive_write_set_bytes_in_last_block", scope: !1, file: !1, line: 167, type: !74, isLocal: false, isDefinition: true, scopeLine: 168, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!210 = distinct !DISubprogram(name: "archive_write_get_bytes_in_last_block", scope: !1, file: !1, line: 180, type: !21, isLocal: false, isDefinition: true, scopeLine: 181, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!211 = distinct !DISubprogram(name: "archive_write_set_skip_file", scope: !1, file: !1, line: 193, type: !212, isLocal: false, isDefinition: true, scopeLine: 194, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!212 = !DISubroutineType(types: !213)
!213 = !{!23, !24, !52, !52}
!214 = distinct !DISubprogram(name: "__archive_write_allocate_filter", scope: !1, file: !1, line: 208, type: !215, isLocal: false, isDefinition: true, scopeLine: 209, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!215 = !DISubroutineType(types: !216)
!216 = !{!137, !24}
!217 = distinct !DISubprogram(name: "__archive_write_filter", scope: !1, file: !1, line: 227, type: !153, isLocal: false, isDefinition: true, scopeLine: 229, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!218 = distinct !DISubprogram(name: "__archive_write_open_filter", scope: !1, file: !1, line: 246, type: !149, isLocal: false, isDefinition: true, scopeLine: 247, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!219 = distinct !DISubprogram(name: "__archive_write_close_filter", scope: !1, file: !1, line: 257, type: !149, isLocal: false, isDefinition: true, scopeLine: 258, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!220 = distinct !DISubprogram(name: "__archive_write_output", scope: !1, file: !1, line: 267, type: !221, isLocal: false, isDefinition: true, scopeLine: 268, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!221 = !DISubroutineType(types: !222)
!222 = !{!23, !4, !43, !45}
!223 = distinct !DISubprogram(name: "__archive_write_nulls", scope: !1, file: !1, line: 273, type: !224, isLocal: false, isDefinition: true, scopeLine: 274, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!224 = !DISubroutineType(types: !225)
!225 = !{!23, !4, !45}
!226 = distinct !DISubprogram(name: "archive_write_open", scope: !1, file: !1, line: 458, type: !227, isLocal: false, isDefinition: true, scopeLine: 461, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!227 = !DISubroutineType(types: !228)
!228 = !{!23, !24, !123, !119, !125, !131}
!229 = distinct !DISubprogram(name: "__archive_write_filters_free", scope: !1, file: !1, line: 547, type: !230, isLocal: false, isDefinition: true, scopeLine: 548, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!230 = !DISubroutineType(types: !231)
!231 = !{null, !24}
!232 = distinct !DISubprogram(name: "archive_write_vtable", scope: !1, file: !1, line: 83, type: !233, isLocal: true, isDefinition: true, scopeLine: 84, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!233 = !DISubroutineType(types: !234)
!234 = !{!16}
!235 = distinct !DISubprogram(name: "_archive_write_close", scope: !1, file: !1, line: 496, type: !21, isLocal: true, isDefinition: true, scopeLine: 497, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!236 = distinct !DISubprogram(name: "_archive_filter_bytes", scope: !1, file: !1, line: 730, type: !70, isLocal: true, isDefinition: true, scopeLine: 731, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!237 = distinct !DISubprogram(name: "filter_lookup", scope: !1, file: !1, line: 700, type: !238, isLocal: true, isDefinition: true, scopeLine: 701, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!238 = !DISubroutineType(types: !239)
!239 = !{!137, !24, !23}
!240 = distinct !DISubprogram(name: "_archive_filter_code", scope: !1, file: !1, line: 716, type: !74, isLocal: true, isDefinition: true, scopeLine: 717, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!241 = distinct !DISubprogram(name: "_archive_filter_name", scope: !1, file: !1, line: 723, type: !78, isLocal: true, isDefinition: true, scopeLine: 724, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!242 = distinct !DISubprogram(name: "_archive_write_filter_count", scope: !1, file: !1, line: 534, type: !21, isLocal: true, isDefinition: true, scopeLine: 535, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!243 = distinct !DISubprogram(name: "_archive_write_free", scope: !1, file: !1, line: 574, type: !21, isLocal: true, isDefinition: true, scopeLine: 575, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!244 = distinct !DISubprogram(name: "_archive_write_header", scope: !1, file: !1, line: 614, type: !28, isLocal: true, isDefinition: true, scopeLine: 615, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!245 = distinct !DISubprogram(name: "_archive_write_finish_entry", scope: !1, file: !1, line: 666, type: !21, isLocal: true, isDefinition: true, scopeLine: 667, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!246 = distinct !DISubprogram(name: "_archive_write_data", scope: !1, file: !1, line: 685, type: !36, isLocal: true, isDefinition: true, scopeLine: 686, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!247 = distinct !DISubprogram(name: "archive_write_client_open", scope: !1, file: !1, line: 289, type: !149, isLocal: true, isDefinition: true, scopeLine: 290, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!248 = distinct !DISubprogram(name: "archive_write_client_write", scope: !1, file: !1, line: 323, type: !153, isLocal: true, isDefinition: true, scopeLine: 325, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!249 = distinct !DISubprogram(name: "archive_write_client_close", scope: !1, file: !1, line: 405, type: !149, isLocal: true, isDefinition: true, scopeLine: 406, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!250 = !{!251, !252}
!251 = !DIGlobalVariable(name: "av", scope: !232, file: !1, line: 85, type: !17, isLocal: true, isDefinition: true, variable: %struct.archive_vtable* @archive_write_vtable.av)
!252 = !DIGlobalVariable(name: "inited", scope: !232, file: !1, line: 86, type: !23, isLocal: true, isDefinition: true, variable: i32* @archive_write_vtable.inited)
!253 = !{i32 2, !"Dwarf Version", i32 4}
!254 = !{i32 2, !"Debug Info Version", i32 3}
!255 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!256 = !DILocalVariable(name: "a", scope: !204, file: !1, line: 109, type: !4)
!257 = !DIExpression()
!258 = !DILocation(line: 109, column: 24, scope: !204)
!259 = !DILocalVariable(name: "nulls", scope: !204, file: !1, line: 110, type: !191)
!260 = !DILocation(line: 110, column: 17, scope: !204)
!261 = !DILocation(line: 112, column: 30, scope: !204)
!262 = !DILocation(line: 112, column: 6, scope: !204)
!263 = !DILocation(line: 112, column: 4, scope: !204)
!264 = !DILocation(line: 113, column: 6, scope: !265)
!265 = distinct !DILexicalBlock(scope: !204, file: !1, line: 113, column: 6)
!266 = !DILocation(line: 113, column: 8, scope: !265)
!267 = !DILocation(line: 113, column: 6, scope: !204)
!268 = !DILocation(line: 114, column: 3, scope: !265)
!269 = !DILocation(line: 115, column: 2, scope: !204)
!270 = !DILocation(line: 115, column: 5, scope: !204)
!271 = !DILocation(line: 115, column: 13, scope: !204)
!272 = !DILocation(line: 115, column: 19, scope: !204)
!273 = !DILocation(line: 116, column: 2, scope: !204)
!274 = !DILocation(line: 116, column: 5, scope: !204)
!275 = !DILocation(line: 116, column: 13, scope: !204)
!276 = !DILocation(line: 116, column: 19, scope: !204)
!277 = !DILocation(line: 117, column: 22, scope: !204)
!278 = !DILocation(line: 117, column: 2, scope: !204)
!279 = !DILocation(line: 117, column: 5, scope: !204)
!280 = !DILocation(line: 117, column: 13, scope: !204)
!281 = !DILocation(line: 117, column: 20, scope: !204)
!282 = !DILocation(line: 123, column: 2, scope: !204)
!283 = !DILocation(line: 123, column: 5, scope: !204)
!284 = !DILocation(line: 123, column: 21, scope: !204)
!285 = !DILocation(line: 124, column: 2, scope: !204)
!286 = !DILocation(line: 124, column: 5, scope: !204)
!287 = !DILocation(line: 124, column: 25, scope: !204)
!288 = !DILocation(line: 127, column: 2, scope: !204)
!289 = !DILocation(line: 127, column: 5, scope: !204)
!290 = !DILocation(line: 127, column: 17, scope: !204)
!291 = !DILocation(line: 128, column: 37, scope: !204)
!292 = !DILocation(line: 128, column: 40, scope: !204)
!293 = !DILocation(line: 128, column: 27, scope: !204)
!294 = !DILocation(line: 128, column: 8, scope: !204)
!295 = !DILocation(line: 129, column: 6, scope: !296)
!296 = distinct !DILexicalBlock(scope: !204, file: !1, line: 129, column: 6)
!297 = !DILocation(line: 129, column: 12, scope: !296)
!298 = !DILocation(line: 129, column: 6, scope: !204)
!299 = !DILocation(line: 130, column: 8, scope: !300)
!300 = distinct !DILexicalBlock(scope: !296, file: !1, line: 129, column: 21)
!301 = !DILocation(line: 130, column: 3, scope: !300)
!302 = !DILocation(line: 131, column: 3, scope: !300)
!303 = !DILocation(line: 133, column: 13, scope: !204)
!304 = !DILocation(line: 133, column: 2, scope: !204)
!305 = !DILocation(line: 133, column: 5, scope: !204)
!306 = !DILocation(line: 133, column: 11, scope: !204)
!307 = !DILocation(line: 134, column: 11, scope: !204)
!308 = !DILocation(line: 134, column: 14, scope: !204)
!309 = !DILocation(line: 134, column: 2, scope: !204)
!310 = !DILocation(line: 135, column: 1, scope: !204)
!311 = !DILocation(line: 88, column: 7, scope: !312)
!312 = distinct !DILexicalBlock(scope: !232, file: !1, line: 88, column: 6)
!313 = !DILocation(line: 88, column: 6, scope: !232)
!314 = !DILocation(line: 89, column: 20, scope: !315)
!315 = distinct !DILexicalBlock(scope: !312, file: !1, line: 88, column: 15)
!316 = !DILocation(line: 90, column: 27, scope: !315)
!317 = !DILocation(line: 91, column: 26, scope: !315)
!318 = !DILocation(line: 92, column: 26, scope: !315)
!319 = !DILocation(line: 93, column: 27, scope: !315)
!320 = !DILocation(line: 94, column: 19, scope: !315)
!321 = !DILocation(line: 95, column: 27, scope: !315)
!322 = !DILocation(line: 96, column: 33, scope: !315)
!323 = !DILocation(line: 97, column: 25, scope: !315)
!324 = !DILocation(line: 98, column: 10, scope: !315)
!325 = !DILocation(line: 99, column: 2, scope: !315)
!326 = !DILocation(line: 100, column: 2, scope: !232)
!327 = !DILocalVariable(name: "_a", arg: 1, scope: !207, file: !1, line: 141, type: !24)
!328 = !DILocation(line: 141, column: 51, scope: !207)
!329 = !DILocalVariable(name: "bytes_per_block", arg: 2, scope: !207, file: !1, line: 141, type: !23)
!330 = !DILocation(line: 141, column: 59, scope: !207)
!331 = !DILocalVariable(name: "a", scope: !207, file: !1, line: 143, type: !4)
!332 = !DILocation(line: 143, column: 24, scope: !207)
!333 = !DILocation(line: 143, column: 52, scope: !207)
!334 = !DILocation(line: 143, column: 28, scope: !207)
!335 = !DILocation(line: 144, column: 2, scope: !207)
!336 = !DILocalVariable(name: "magic_test", scope: !337, file: !1, line: 144, type: !23)
!337 = distinct !DILexicalBlock(scope: !207, file: !1, line: 144, column: 2)
!338 = !DILocation(line: 144, column: 2, scope: !337)
!339 = !DILocation(line: 144, column: 2, scope: !340)
!340 = !DILexicalBlockFile(scope: !337, file: !1, discriminator: 1)
!341 = !DILocation(line: 144, column: 2, scope: !342)
!342 = !DILexicalBlockFile(scope: !343, file: !1, discriminator: 2)
!343 = distinct !DILexicalBlock(scope: !337, file: !1, line: 144, column: 2)
!344 = !DILocation(line: 144, column: 2, scope: !345)
!345 = !DILexicalBlockFile(scope: !337, file: !1, discriminator: 3)
!346 = !DILocation(line: 146, column: 23, scope: !207)
!347 = !DILocation(line: 146, column: 2, scope: !207)
!348 = !DILocation(line: 146, column: 5, scope: !207)
!349 = !DILocation(line: 146, column: 21, scope: !207)
!350 = !DILocation(line: 147, column: 2, scope: !207)
!351 = !DILocation(line: 148, column: 1, scope: !207)
!352 = !DILocalVariable(name: "_a", arg: 1, scope: !208, file: !1, line: 154, type: !24)
!353 = !DILocation(line: 154, column: 51, scope: !208)
!354 = !DILocalVariable(name: "a", scope: !208, file: !1, line: 156, type: !4)
!355 = !DILocation(line: 156, column: 24, scope: !208)
!356 = !DILocation(line: 156, column: 52, scope: !208)
!357 = !DILocation(line: 156, column: 28, scope: !208)
!358 = !DILocation(line: 157, column: 2, scope: !208)
!359 = !DILocalVariable(name: "magic_test", scope: !360, file: !1, line: 157, type: !23)
!360 = distinct !DILexicalBlock(scope: !208, file: !1, line: 157, column: 2)
!361 = !DILocation(line: 157, column: 2, scope: !360)
!362 = !DILocation(line: 157, column: 2, scope: !363)
!363 = !DILexicalBlockFile(scope: !360, file: !1, discriminator: 1)
!364 = !DILocation(line: 157, column: 2, scope: !365)
!365 = !DILexicalBlockFile(scope: !366, file: !1, discriminator: 2)
!366 = distinct !DILexicalBlock(scope: !360, file: !1, line: 157, column: 2)
!367 = !DILocation(line: 157, column: 2, scope: !368)
!368 = !DILexicalBlockFile(scope: !360, file: !1, discriminator: 3)
!369 = !DILocation(line: 159, column: 10, scope: !208)
!370 = !DILocation(line: 159, column: 13, scope: !208)
!371 = !DILocation(line: 159, column: 2, scope: !208)
!372 = !DILocation(line: 160, column: 1, scope: !208)
!373 = !DILocalVariable(name: "_a", arg: 1, scope: !209, file: !1, line: 167, type: !24)
!374 = !DILocation(line: 167, column: 55, scope: !209)
!375 = !DILocalVariable(name: "bytes", arg: 2, scope: !209, file: !1, line: 167, type: !23)
!376 = !DILocation(line: 167, column: 63, scope: !209)
!377 = !DILocalVariable(name: "a", scope: !209, file: !1, line: 169, type: !4)
!378 = !DILocation(line: 169, column: 24, scope: !209)
!379 = !DILocation(line: 169, column: 52, scope: !209)
!380 = !DILocation(line: 169, column: 28, scope: !209)
!381 = !DILocation(line: 170, column: 2, scope: !209)
!382 = !DILocalVariable(name: "magic_test", scope: !383, file: !1, line: 170, type: !23)
!383 = distinct !DILexicalBlock(scope: !209, file: !1, line: 170, column: 2)
!384 = !DILocation(line: 170, column: 2, scope: !383)
!385 = !DILocation(line: 170, column: 2, scope: !386)
!386 = !DILexicalBlockFile(scope: !383, file: !1, discriminator: 1)
!387 = !DILocation(line: 170, column: 2, scope: !388)
!388 = !DILexicalBlockFile(scope: !389, file: !1, discriminator: 2)
!389 = distinct !DILexicalBlock(scope: !383, file: !1, line: 170, column: 2)
!390 = !DILocation(line: 170, column: 2, scope: !391)
!391 = !DILexicalBlockFile(scope: !383, file: !1, discriminator: 3)
!392 = !DILocation(line: 172, column: 27, scope: !209)
!393 = !DILocation(line: 172, column: 2, scope: !209)
!394 = !DILocation(line: 172, column: 5, scope: !209)
!395 = !DILocation(line: 172, column: 25, scope: !209)
!396 = !DILocation(line: 173, column: 2, scope: !209)
!397 = !DILocation(line: 174, column: 1, scope: !209)
!398 = !DILocalVariable(name: "_a", arg: 1, scope: !210, file: !1, line: 180, type: !24)
!399 = !DILocation(line: 180, column: 55, scope: !210)
!400 = !DILocalVariable(name: "a", scope: !210, file: !1, line: 182, type: !4)
!401 = !DILocation(line: 182, column: 24, scope: !210)
!402 = !DILocation(line: 182, column: 52, scope: !210)
!403 = !DILocation(line: 182, column: 28, scope: !210)
!404 = !DILocation(line: 183, column: 2, scope: !210)
!405 = !DILocalVariable(name: "magic_test", scope: !406, file: !1, line: 183, type: !23)
!406 = distinct !DILexicalBlock(scope: !210, file: !1, line: 183, column: 2)
!407 = !DILocation(line: 183, column: 2, scope: !406)
!408 = !DILocation(line: 183, column: 2, scope: !409)
!409 = !DILexicalBlockFile(scope: !406, file: !1, discriminator: 1)
!410 = !DILocation(line: 183, column: 2, scope: !411)
!411 = !DILexicalBlockFile(scope: !412, file: !1, discriminator: 2)
!412 = distinct !DILexicalBlock(scope: !406, file: !1, line: 183, column: 2)
!413 = !DILocation(line: 183, column: 2, scope: !414)
!414 = !DILexicalBlockFile(scope: !406, file: !1, discriminator: 3)
!415 = !DILocation(line: 185, column: 10, scope: !210)
!416 = !DILocation(line: 185, column: 13, scope: !210)
!417 = !DILocation(line: 185, column: 2, scope: !210)
!418 = !DILocation(line: 186, column: 1, scope: !210)
!419 = !DILocalVariable(name: "_a", arg: 1, scope: !211, file: !1, line: 193, type: !24)
!420 = !DILocation(line: 193, column: 45, scope: !211)
!421 = !DILocalVariable(name: "d", arg: 2, scope: !211, file: !1, line: 193, type: !52)
!422 = !DILocation(line: 193, column: 57, scope: !211)
!423 = !DILocalVariable(name: "i", arg: 3, scope: !211, file: !1, line: 193, type: !52)
!424 = !DILocation(line: 193, column: 68, scope: !211)
!425 = !DILocalVariable(name: "a", scope: !211, file: !1, line: 195, type: !4)
!426 = !DILocation(line: 195, column: 24, scope: !211)
!427 = !DILocation(line: 195, column: 52, scope: !211)
!428 = !DILocation(line: 195, column: 28, scope: !211)
!429 = !DILocation(line: 196, column: 2, scope: !211)
!430 = !DILocalVariable(name: "magic_test", scope: !431, file: !1, line: 196, type: !23)
!431 = distinct !DILexicalBlock(scope: !211, file: !1, line: 196, column: 2)
!432 = !DILocation(line: 196, column: 2, scope: !431)
!433 = !DILocation(line: 196, column: 2, scope: !434)
!434 = !DILexicalBlockFile(scope: !431, file: !1, discriminator: 1)
!435 = !DILocation(line: 196, column: 2, scope: !436)
!436 = !DILexicalBlockFile(scope: !437, file: !1, discriminator: 2)
!437 = distinct !DILexicalBlock(scope: !431, file: !1, line: 196, column: 2)
!438 = !DILocation(line: 196, column: 2, scope: !439)
!439 = !DILexicalBlockFile(scope: !431, file: !1, discriminator: 3)
!440 = !DILocation(line: 198, column: 2, scope: !211)
!441 = !DILocation(line: 198, column: 5, scope: !211)
!442 = !DILocation(line: 198, column: 19, scope: !211)
!443 = !DILocation(line: 199, column: 21, scope: !211)
!444 = !DILocation(line: 199, column: 2, scope: !211)
!445 = !DILocation(line: 199, column: 5, scope: !211)
!446 = !DILocation(line: 199, column: 19, scope: !211)
!447 = !DILocation(line: 200, column: 21, scope: !211)
!448 = !DILocation(line: 200, column: 2, scope: !211)
!449 = !DILocation(line: 200, column: 5, scope: !211)
!450 = !DILocation(line: 200, column: 19, scope: !211)
!451 = !DILocation(line: 201, column: 2, scope: !211)
!452 = !DILocation(line: 202, column: 1, scope: !211)
!453 = !DILocalVariable(name: "_a", arg: 1, scope: !214, file: !1, line: 208, type: !24)
!454 = !DILocation(line: 208, column: 49, scope: !214)
!455 = !DILocalVariable(name: "a", scope: !214, file: !1, line: 210, type: !4)
!456 = !DILocation(line: 210, column: 24, scope: !214)
!457 = !DILocation(line: 210, column: 52, scope: !214)
!458 = !DILocation(line: 210, column: 28, scope: !214)
!459 = !DILocalVariable(name: "f", scope: !214, file: !1, line: 211, type: !137)
!460 = !DILocation(line: 211, column: 31, scope: !214)
!461 = !DILocation(line: 213, column: 6, scope: !214)
!462 = !DILocation(line: 213, column: 4, scope: !214)
!463 = !DILocation(line: 214, column: 15, scope: !214)
!464 = !DILocation(line: 214, column: 2, scope: !214)
!465 = !DILocation(line: 214, column: 5, scope: !214)
!466 = !DILocation(line: 214, column: 13, scope: !214)
!467 = !DILocation(line: 215, column: 6, scope: !468)
!468 = distinct !DILexicalBlock(scope: !214, file: !1, line: 215, column: 6)
!469 = !DILocation(line: 215, column: 9, scope: !468)
!470 = !DILocation(line: 215, column: 22, scope: !468)
!471 = !DILocation(line: 215, column: 6, scope: !214)
!472 = !DILocation(line: 216, column: 21, scope: !468)
!473 = !DILocation(line: 216, column: 3, scope: !468)
!474 = !DILocation(line: 216, column: 6, scope: !468)
!475 = !DILocation(line: 216, column: 19, scope: !468)
!476 = !DILocation(line: 218, column: 33, scope: !468)
!477 = !DILocation(line: 218, column: 3, scope: !468)
!478 = !DILocation(line: 218, column: 6, scope: !468)
!479 = !DILocation(line: 218, column: 19, scope: !468)
!480 = !DILocation(line: 218, column: 31, scope: !468)
!481 = !DILocation(line: 219, column: 19, scope: !214)
!482 = !DILocation(line: 219, column: 2, scope: !214)
!483 = !DILocation(line: 219, column: 5, scope: !214)
!484 = !DILocation(line: 219, column: 17, scope: !214)
!485 = !DILocation(line: 220, column: 9, scope: !214)
!486 = !DILocation(line: 220, column: 2, scope: !214)
!487 = !DILocalVariable(name: "f", arg: 1, scope: !217, file: !1, line: 227, type: !137)
!488 = !DILocation(line: 227, column: 53, scope: !217)
!489 = !DILocalVariable(name: "buff", arg: 2, scope: !217, file: !1, line: 228, type: !43)
!490 = !DILocation(line: 228, column: 17, scope: !217)
!491 = !DILocalVariable(name: "length", arg: 3, scope: !217, file: !1, line: 228, type: !45)
!492 = !DILocation(line: 228, column: 30, scope: !217)
!493 = !DILocalVariable(name: "r", scope: !217, file: !1, line: 230, type: !23)
!494 = !DILocation(line: 230, column: 6, scope: !217)
!495 = !DILocation(line: 231, column: 6, scope: !496)
!496 = distinct !DILexicalBlock(scope: !217, file: !1, line: 231, column: 6)
!497 = !DILocation(line: 231, column: 13, scope: !496)
!498 = !DILocation(line: 231, column: 6, scope: !217)
!499 = !DILocation(line: 232, column: 3, scope: !496)
!500 = !DILocation(line: 233, column: 6, scope: !501)
!501 = distinct !DILexicalBlock(scope: !217, file: !1, line: 233, column: 6)
!502 = !DILocation(line: 233, column: 9, scope: !501)
!503 = !DILocation(line: 233, column: 15, scope: !501)
!504 = !DILocation(line: 233, column: 6, scope: !217)
!505 = !DILocation(line: 236, column: 3, scope: !501)
!506 = !DILocation(line: 237, column: 7, scope: !217)
!507 = !DILocation(line: 237, column: 10, scope: !217)
!508 = !DILocation(line: 237, column: 17, scope: !217)
!509 = !DILocation(line: 237, column: 20, scope: !217)
!510 = !DILocation(line: 237, column: 26, scope: !217)
!511 = !DILocation(line: 237, column: 6, scope: !217)
!512 = !DILocation(line: 237, column: 4, scope: !217)
!513 = !DILocation(line: 238, column: 22, scope: !217)
!514 = !DILocation(line: 238, column: 2, scope: !217)
!515 = !DILocation(line: 238, column: 5, scope: !217)
!516 = !DILocation(line: 238, column: 19, scope: !217)
!517 = !DILocation(line: 239, column: 10, scope: !217)
!518 = !DILocation(line: 239, column: 2, scope: !217)
!519 = !DILocation(line: 240, column: 1, scope: !217)
!520 = !DILocalVariable(name: "f", arg: 1, scope: !218, file: !1, line: 246, type: !137)
!521 = !DILocation(line: 246, column: 58, scope: !218)
!522 = !DILocation(line: 248, column: 6, scope: !523)
!523 = distinct !DILexicalBlock(scope: !218, file: !1, line: 248, column: 6)
!524 = !DILocation(line: 248, column: 9, scope: !523)
!525 = !DILocation(line: 248, column: 14, scope: !523)
!526 = !DILocation(line: 248, column: 6, scope: !218)
!527 = !DILocation(line: 249, column: 3, scope: !523)
!528 = !DILocation(line: 250, column: 10, scope: !218)
!529 = !DILocation(line: 250, column: 13, scope: !218)
!530 = !DILocation(line: 250, column: 19, scope: !218)
!531 = !DILocation(line: 250, column: 9, scope: !218)
!532 = !DILocation(line: 250, column: 2, scope: !218)
!533 = !DILocation(line: 251, column: 1, scope: !218)
!534 = !DILocalVariable(name: "f", arg: 1, scope: !219, file: !1, line: 257, type: !137)
!535 = !DILocation(line: 257, column: 59, scope: !219)
!536 = !DILocation(line: 259, column: 6, scope: !537)
!537 = distinct !DILexicalBlock(scope: !219, file: !1, line: 259, column: 6)
!538 = !DILocation(line: 259, column: 9, scope: !537)
!539 = !DILocation(line: 259, column: 15, scope: !537)
!540 = !DILocation(line: 259, column: 6, scope: !219)
!541 = !DILocation(line: 260, column: 11, scope: !537)
!542 = !DILocation(line: 260, column: 14, scope: !537)
!543 = !DILocation(line: 260, column: 21, scope: !537)
!544 = !DILocation(line: 260, column: 10, scope: !537)
!545 = !DILocation(line: 260, column: 3, scope: !537)
!546 = !DILocation(line: 261, column: 6, scope: !547)
!547 = distinct !DILexicalBlock(scope: !219, file: !1, line: 261, column: 6)
!548 = !DILocation(line: 261, column: 9, scope: !547)
!549 = !DILocation(line: 261, column: 21, scope: !547)
!550 = !DILocation(line: 261, column: 6, scope: !219)
!551 = !DILocation(line: 262, column: 40, scope: !547)
!552 = !DILocation(line: 262, column: 43, scope: !547)
!553 = !DILocation(line: 262, column: 11, scope: !547)
!554 = !DILocation(line: 262, column: 3, scope: !547)
!555 = !DILocation(line: 263, column: 2, scope: !219)
!556 = !DILocation(line: 264, column: 1, scope: !219)
!557 = !DILocalVariable(name: "a", arg: 1, scope: !220, file: !1, line: 267, type: !4)
!558 = !DILocation(line: 267, column: 46, scope: !220)
!559 = !DILocalVariable(name: "buff", arg: 2, scope: !220, file: !1, line: 267, type: !43)
!560 = !DILocation(line: 267, column: 61, scope: !220)
!561 = !DILocalVariable(name: "length", arg: 3, scope: !220, file: !1, line: 267, type: !45)
!562 = !DILocation(line: 267, column: 74, scope: !220)
!563 = !DILocation(line: 269, column: 33, scope: !220)
!564 = !DILocation(line: 269, column: 36, scope: !220)
!565 = !DILocation(line: 269, column: 50, scope: !220)
!566 = !DILocation(line: 269, column: 56, scope: !220)
!567 = !DILocation(line: 269, column: 10, scope: !220)
!568 = !DILocation(line: 269, column: 2, scope: !220)
!569 = !DILocalVariable(name: "a", arg: 1, scope: !223, file: !1, line: 273, type: !4)
!570 = !DILocation(line: 273, column: 45, scope: !223)
!571 = !DILocalVariable(name: "length", arg: 2, scope: !223, file: !1, line: 273, type: !45)
!572 = !DILocation(line: 273, column: 55, scope: !223)
!573 = !DILocation(line: 275, column: 6, scope: !574)
!574 = distinct !DILexicalBlock(scope: !223, file: !1, line: 275, column: 6)
!575 = !DILocation(line: 275, column: 13, scope: !574)
!576 = !DILocation(line: 275, column: 6, scope: !223)
!577 = !DILocation(line: 276, column: 3, scope: !574)
!578 = !DILocation(line: 278, column: 2, scope: !223)
!579 = !DILocation(line: 278, column: 9, scope: !580)
!580 = !DILexicalBlockFile(scope: !223, file: !1, discriminator: 1)
!581 = !DILocation(line: 278, column: 16, scope: !580)
!582 = !DILocation(line: 278, column: 2, scope: !580)
!583 = !DILocalVariable(name: "to_write", scope: !584, file: !1, line: 279, type: !45)
!584 = distinct !DILexicalBlock(scope: !223, file: !1, line: 278, column: 21)
!585 = !DILocation(line: 279, column: 10, scope: !584)
!586 = !DILocation(line: 279, column: 21, scope: !584)
!587 = !DILocation(line: 279, column: 30, scope: !584)
!588 = !DILocation(line: 279, column: 33, scope: !584)
!589 = !DILocation(line: 279, column: 28, scope: !584)
!590 = !DILocation(line: 279, column: 47, scope: !591)
!591 = !DILexicalBlockFile(scope: !584, file: !1, discriminator: 1)
!592 = !DILocation(line: 279, column: 21, scope: !591)
!593 = !DILocation(line: 279, column: 56, scope: !594)
!594 = !DILexicalBlockFile(scope: !584, file: !1, discriminator: 2)
!595 = !DILocation(line: 279, column: 59, scope: !594)
!596 = !DILocation(line: 279, column: 21, scope: !594)
!597 = !DILocation(line: 279, column: 21, scope: !598)
!598 = !DILexicalBlockFile(scope: !584, file: !1, discriminator: 3)
!599 = !DILocation(line: 279, column: 10, scope: !598)
!600 = !DILocalVariable(name: "r", scope: !584, file: !1, line: 280, type: !23)
!601 = !DILocation(line: 280, column: 7, scope: !584)
!602 = !DILocation(line: 280, column: 34, scope: !584)
!603 = !DILocation(line: 280, column: 37, scope: !584)
!604 = !DILocation(line: 280, column: 40, scope: !584)
!605 = !DILocation(line: 280, column: 47, scope: !584)
!606 = !DILocation(line: 280, column: 11, scope: !584)
!607 = !DILocation(line: 281, column: 7, scope: !608)
!608 = distinct !DILexicalBlock(scope: !584, file: !1, line: 281, column: 7)
!609 = !DILocation(line: 281, column: 9, scope: !608)
!610 = !DILocation(line: 281, column: 7, scope: !584)
!611 = !DILocation(line: 282, column: 12, scope: !608)
!612 = !DILocation(line: 282, column: 4, scope: !608)
!613 = !DILocation(line: 283, column: 13, scope: !584)
!614 = !DILocation(line: 283, column: 10, scope: !584)
!615 = !DILocation(line: 278, column: 2, scope: !616)
!616 = !DILexicalBlockFile(scope: !223, file: !1, discriminator: 2)
!617 = !DILocation(line: 285, column: 2, scope: !223)
!618 = !DILocation(line: 286, column: 1, scope: !223)
!619 = !DILocalVariable(name: "_a", arg: 1, scope: !226, file: !1, line: 458, type: !24)
!620 = !DILocation(line: 458, column: 36, scope: !226)
!621 = !DILocalVariable(name: "client_data", arg: 2, scope: !226, file: !1, line: 458, type: !123)
!622 = !DILocation(line: 458, column: 46, scope: !226)
!623 = !DILocalVariable(name: "opener", arg: 3, scope: !226, file: !1, line: 459, type: !119)
!624 = !DILocation(line: 459, column: 28, scope: !226)
!625 = !DILocalVariable(name: "writer", arg: 4, scope: !226, file: !1, line: 459, type: !125)
!626 = !DILocation(line: 459, column: 60, scope: !226)
!627 = !DILocalVariable(name: "closer", arg: 5, scope: !226, file: !1, line: 460, type: !131)
!628 = !DILocation(line: 460, column: 29, scope: !226)
!629 = !DILocalVariable(name: "a", scope: !226, file: !1, line: 462, type: !4)
!630 = !DILocation(line: 462, column: 24, scope: !226)
!631 = !DILocation(line: 462, column: 52, scope: !226)
!632 = !DILocation(line: 462, column: 28, scope: !226)
!633 = !DILocalVariable(name: "client_filter", scope: !226, file: !1, line: 463, type: !137)
!634 = !DILocation(line: 463, column: 31, scope: !226)
!635 = !DILocalVariable(name: "ret", scope: !226, file: !1, line: 464, type: !23)
!636 = !DILocation(line: 464, column: 6, scope: !226)
!637 = !DILocalVariable(name: "r1", scope: !226, file: !1, line: 464, type: !23)
!638 = !DILocation(line: 464, column: 11, scope: !226)
!639 = !DILocation(line: 466, column: 2, scope: !226)
!640 = !DILocalVariable(name: "magic_test", scope: !641, file: !1, line: 466, type: !23)
!641 = distinct !DILexicalBlock(scope: !226, file: !1, line: 466, column: 2)
!642 = !DILocation(line: 466, column: 2, scope: !641)
!643 = !DILocation(line: 466, column: 2, scope: !644)
!644 = !DILexicalBlockFile(scope: !641, file: !1, discriminator: 1)
!645 = !DILocation(line: 466, column: 2, scope: !646)
!646 = !DILexicalBlockFile(scope: !647, file: !1, discriminator: 2)
!647 = distinct !DILexicalBlock(scope: !641, file: !1, line: 466, column: 2)
!648 = !DILocation(line: 466, column: 2, scope: !649)
!649 = !DILexicalBlockFile(scope: !641, file: !1, discriminator: 3)
!650 = !DILocation(line: 468, column: 23, scope: !226)
!651 = !DILocation(line: 468, column: 26, scope: !226)
!652 = !DILocation(line: 468, column: 2, scope: !226)
!653 = !DILocation(line: 470, column: 21, scope: !226)
!654 = !DILocation(line: 470, column: 2, scope: !226)
!655 = !DILocation(line: 470, column: 5, scope: !226)
!656 = !DILocation(line: 470, column: 19, scope: !226)
!657 = !DILocation(line: 471, column: 21, scope: !226)
!658 = !DILocation(line: 471, column: 2, scope: !226)
!659 = !DILocation(line: 471, column: 5, scope: !226)
!660 = !DILocation(line: 471, column: 19, scope: !226)
!661 = !DILocation(line: 472, column: 21, scope: !226)
!662 = !DILocation(line: 472, column: 2, scope: !226)
!663 = !DILocation(line: 472, column: 5, scope: !226)
!664 = !DILocation(line: 472, column: 19, scope: !226)
!665 = !DILocation(line: 473, column: 19, scope: !226)
!666 = !DILocation(line: 473, column: 2, scope: !226)
!667 = !DILocation(line: 473, column: 5, scope: !226)
!668 = !DILocation(line: 473, column: 17, scope: !226)
!669 = !DILocation(line: 475, column: 50, scope: !226)
!670 = !DILocation(line: 475, column: 18, scope: !226)
!671 = !DILocation(line: 475, column: 16, scope: !226)
!672 = !DILocation(line: 476, column: 2, scope: !226)
!673 = !DILocation(line: 476, column: 17, scope: !226)
!674 = !DILocation(line: 476, column: 22, scope: !226)
!675 = !DILocation(line: 477, column: 2, scope: !226)
!676 = !DILocation(line: 477, column: 17, scope: !226)
!677 = !DILocation(line: 477, column: 23, scope: !226)
!678 = !DILocation(line: 478, column: 2, scope: !226)
!679 = !DILocation(line: 478, column: 17, scope: !226)
!680 = !DILocation(line: 478, column: 23, scope: !226)
!681 = !DILocation(line: 480, column: 36, scope: !226)
!682 = !DILocation(line: 480, column: 39, scope: !226)
!683 = !DILocation(line: 480, column: 8, scope: !226)
!684 = !DILocation(line: 480, column: 6, scope: !226)
!685 = !DILocation(line: 481, column: 6, scope: !686)
!686 = distinct !DILexicalBlock(scope: !226, file: !1, line: 481, column: 6)
!687 = !DILocation(line: 481, column: 10, scope: !686)
!688 = !DILocation(line: 481, column: 6, scope: !226)
!689 = !DILocation(line: 482, column: 37, scope: !690)
!690 = distinct !DILexicalBlock(scope: !686, file: !1, line: 481, column: 26)
!691 = !DILocation(line: 482, column: 40, scope: !690)
!692 = !DILocation(line: 482, column: 8, scope: !690)
!693 = !DILocation(line: 482, column: 6, scope: !690)
!694 = !DILocation(line: 483, column: 11, scope: !690)
!695 = !DILocation(line: 483, column: 16, scope: !690)
!696 = !DILocation(line: 483, column: 14, scope: !690)
!697 = !DILocation(line: 483, column: 22, scope: !698)
!698 = !DILexicalBlockFile(scope: !690, file: !1, discriminator: 1)
!699 = !DILocation(line: 483, column: 11, scope: !698)
!700 = !DILocation(line: 483, column: 27, scope: !701)
!701 = !DILexicalBlockFile(scope: !690, file: !1, discriminator: 2)
!702 = !DILocation(line: 483, column: 11, scope: !701)
!703 = !DILocation(line: 483, column: 11, scope: !704)
!704 = !DILexicalBlockFile(scope: !690, file: !1, discriminator: 3)
!705 = !DILocation(line: 483, column: 3, scope: !704)
!706 = !DILocation(line: 486, column: 2, scope: !226)
!707 = !DILocation(line: 486, column: 5, scope: !226)
!708 = !DILocation(line: 486, column: 13, scope: !226)
!709 = !DILocation(line: 486, column: 19, scope: !226)
!710 = !DILocation(line: 487, column: 6, scope: !711)
!711 = distinct !DILexicalBlock(scope: !226, file: !1, line: 487, column: 6)
!712 = !DILocation(line: 487, column: 9, scope: !711)
!713 = !DILocation(line: 487, column: 6, scope: !226)
!714 = !DILocation(line: 488, column: 10, scope: !711)
!715 = !DILocation(line: 488, column: 13, scope: !711)
!716 = !DILocation(line: 488, column: 26, scope: !711)
!717 = !DILocation(line: 488, column: 9, scope: !711)
!718 = !DILocation(line: 488, column: 7, scope: !711)
!719 = !DILocation(line: 488, column: 3, scope: !711)
!720 = !DILocation(line: 489, column: 10, scope: !226)
!721 = !DILocation(line: 489, column: 2, scope: !226)
!722 = !DILocation(line: 490, column: 1, scope: !226)
!723 = !DILocalVariable(name: "f", arg: 1, scope: !247, file: !1, line: 289, type: !137)
!724 = !DILocation(line: 289, column: 56, scope: !247)
!725 = !DILocalVariable(name: "a", scope: !247, file: !1, line: 291, type: !4)
!726 = !DILocation(line: 291, column: 24, scope: !247)
!727 = !DILocation(line: 291, column: 52, scope: !247)
!728 = !DILocation(line: 291, column: 55, scope: !247)
!729 = !DILocation(line: 291, column: 28, scope: !247)
!730 = !DILocalVariable(name: "state", scope: !247, file: !1, line: 292, type: !196)
!731 = !DILocation(line: 292, column: 23, scope: !247)
!732 = !DILocalVariable(name: "buffer", scope: !247, file: !1, line: 293, type: !123)
!733 = !DILocation(line: 293, column: 8, scope: !247)
!734 = !DILocalVariable(name: "buffer_size", scope: !247, file: !1, line: 294, type: !45)
!735 = !DILocation(line: 294, column: 9, scope: !247)
!736 = !DILocation(line: 296, column: 57, scope: !247)
!737 = !DILocation(line: 296, column: 60, scope: !247)
!738 = !DILocation(line: 296, column: 23, scope: !247)
!739 = !DILocation(line: 296, column: 2, scope: !247)
!740 = !DILocation(line: 296, column: 5, scope: !247)
!741 = !DILocation(line: 296, column: 21, scope: !247)
!742 = !DILocation(line: 298, column: 44, scope: !247)
!743 = !DILocation(line: 298, column: 47, scope: !247)
!744 = !DILocation(line: 298, column: 6, scope: !247)
!745 = !DILocation(line: 297, column: 2, scope: !247)
!746 = !DILocation(line: 297, column: 5, scope: !247)
!747 = !DILocation(line: 297, column: 25, scope: !247)
!748 = !DILocation(line: 299, column: 16, scope: !247)
!749 = !DILocation(line: 299, column: 19, scope: !247)
!750 = !DILocation(line: 299, column: 14, scope: !247)
!751 = !DILocation(line: 301, column: 33, scope: !247)
!752 = !DILocation(line: 301, column: 10, scope: !247)
!753 = !DILocation(line: 301, column: 8, scope: !247)
!754 = !DILocation(line: 302, column: 26, scope: !247)
!755 = !DILocation(line: 302, column: 19, scope: !247)
!756 = !DILocation(line: 302, column: 9, scope: !247)
!757 = !DILocation(line: 303, column: 6, scope: !758)
!758 = distinct !DILexicalBlock(scope: !247, file: !1, line: 303, column: 6)
!759 = !DILocation(line: 303, column: 12, scope: !758)
!760 = !DILocation(line: 303, column: 20, scope: !758)
!761 = !DILocation(line: 303, column: 23, scope: !762)
!762 = !DILexicalBlockFile(scope: !758, file: !1, discriminator: 1)
!763 = !DILocation(line: 303, column: 30, scope: !762)
!764 = !DILocation(line: 303, column: 6, scope: !762)
!765 = !DILocation(line: 304, column: 8, scope: !766)
!766 = distinct !DILexicalBlock(scope: !758, file: !1, line: 303, column: 39)
!767 = !DILocation(line: 304, column: 3, scope: !766)
!768 = !DILocation(line: 305, column: 8, scope: !766)
!769 = !DILocation(line: 305, column: 3, scope: !766)
!770 = !DILocation(line: 306, column: 21, scope: !766)
!771 = !DILocation(line: 306, column: 24, scope: !766)
!772 = !DILocation(line: 306, column: 3, scope: !766)
!773 = !DILocation(line: 308, column: 3, scope: !766)
!774 = !DILocation(line: 311, column: 23, scope: !247)
!775 = !DILocation(line: 311, column: 2, scope: !247)
!776 = !DILocation(line: 311, column: 9, scope: !247)
!777 = !DILocation(line: 311, column: 21, scope: !247)
!778 = !DILocation(line: 312, column: 18, scope: !247)
!779 = !DILocation(line: 312, column: 2, scope: !247)
!780 = !DILocation(line: 312, column: 9, scope: !247)
!781 = !DILocation(line: 312, column: 16, scope: !247)
!782 = !DILocation(line: 313, column: 16, scope: !247)
!783 = !DILocation(line: 313, column: 23, scope: !247)
!784 = !DILocation(line: 313, column: 2, scope: !247)
!785 = !DILocation(line: 313, column: 9, scope: !247)
!786 = !DILocation(line: 313, column: 14, scope: !247)
!787 = !DILocation(line: 314, column: 17, scope: !247)
!788 = !DILocation(line: 314, column: 24, scope: !247)
!789 = !DILocation(line: 314, column: 2, scope: !247)
!790 = !DILocation(line: 314, column: 9, scope: !247)
!791 = !DILocation(line: 314, column: 15, scope: !247)
!792 = !DILocation(line: 315, column: 12, scope: !247)
!793 = !DILocation(line: 315, column: 2, scope: !247)
!794 = !DILocation(line: 315, column: 5, scope: !247)
!795 = !DILocation(line: 315, column: 10, scope: !247)
!796 = !DILocation(line: 317, column: 6, scope: !797)
!797 = distinct !DILexicalBlock(scope: !247, file: !1, line: 317, column: 6)
!798 = !DILocation(line: 317, column: 9, scope: !797)
!799 = !DILocation(line: 317, column: 23, scope: !797)
!800 = !DILocation(line: 317, column: 6, scope: !247)
!801 = !DILocation(line: 318, column: 3, scope: !797)
!802 = !DILocation(line: 319, column: 10, scope: !247)
!803 = !DILocation(line: 319, column: 13, scope: !247)
!804 = !DILocation(line: 319, column: 27, scope: !247)
!805 = !DILocation(line: 319, column: 30, scope: !247)
!806 = !DILocation(line: 319, column: 39, scope: !247)
!807 = !DILocation(line: 319, column: 42, scope: !247)
!808 = !DILocation(line: 319, column: 2, scope: !247)
!809 = !DILocation(line: 320, column: 1, scope: !247)
!810 = !DILocalVariable(name: "f", arg: 1, scope: !248, file: !1, line: 323, type: !137)
!811 = !DILocation(line: 323, column: 57, scope: !248)
!812 = !DILocalVariable(name: "_buff", arg: 2, scope: !248, file: !1, line: 324, type: !43)
!813 = !DILocation(line: 324, column: 17, scope: !248)
!814 = !DILocalVariable(name: "length", arg: 3, scope: !248, file: !1, line: 324, type: !45)
!815 = !DILocation(line: 324, column: 31, scope: !248)
!816 = !DILocalVariable(name: "a", scope: !248, file: !1, line: 326, type: !4)
!817 = !DILocation(line: 326, column: 24, scope: !248)
!818 = !DILocation(line: 326, column: 52, scope: !248)
!819 = !DILocation(line: 326, column: 55, scope: !248)
!820 = !DILocation(line: 326, column: 28, scope: !248)
!821 = !DILocalVariable(name: "state", scope: !248, file: !1, line: 327, type: !196)
!822 = !DILocation(line: 327, column: 30, scope: !248)
!823 = !DILocation(line: 327, column: 61, scope: !248)
!824 = !DILocation(line: 327, column: 64, scope: !248)
!825 = !DILocation(line: 327, column: 38, scope: !248)
!826 = !DILocalVariable(name: "buff", scope: !248, file: !1, line: 328, type: !80)
!827 = !DILocation(line: 328, column: 14, scope: !248)
!828 = !DILocation(line: 328, column: 35, scope: !248)
!829 = !DILocalVariable(name: "remaining", scope: !248, file: !1, line: 329, type: !38)
!830 = !DILocation(line: 329, column: 10, scope: !248)
!831 = !DILocalVariable(name: "to_copy", scope: !248, file: !1, line: 329, type: !38)
!832 = !DILocation(line: 329, column: 21, scope: !248)
!833 = !DILocalVariable(name: "bytes_written", scope: !248, file: !1, line: 330, type: !38)
!834 = !DILocation(line: 330, column: 10, scope: !248)
!835 = !DILocation(line: 332, column: 14, scope: !248)
!836 = !DILocation(line: 332, column: 12, scope: !248)
!837 = !DILocation(line: 340, column: 6, scope: !838)
!838 = distinct !DILexicalBlock(scope: !248, file: !1, line: 340, column: 6)
!839 = !DILocation(line: 340, column: 13, scope: !838)
!840 = !DILocation(line: 340, column: 25, scope: !838)
!841 = !DILocation(line: 340, column: 6, scope: !248)
!842 = !DILocation(line: 341, column: 3, scope: !843)
!843 = distinct !DILexicalBlock(scope: !838, file: !1, line: 340, column: 31)
!844 = !DILocation(line: 341, column: 10, scope: !845)
!845 = !DILexicalBlockFile(scope: !843, file: !1, discriminator: 1)
!846 = !DILocation(line: 341, column: 20, scope: !845)
!847 = !DILocation(line: 341, column: 3, scope: !845)
!848 = !DILocation(line: 342, column: 21, scope: !849)
!849 = distinct !DILexicalBlock(scope: !843, file: !1, line: 341, column: 25)
!850 = !DILocation(line: 342, column: 24, scope: !849)
!851 = !DILocation(line: 342, column: 40, scope: !849)
!852 = !DILocation(line: 342, column: 43, scope: !849)
!853 = !DILocation(line: 343, column: 8, scope: !849)
!854 = !DILocation(line: 343, column: 11, scope: !849)
!855 = !DILocation(line: 343, column: 24, scope: !849)
!856 = !DILocation(line: 343, column: 30, scope: !849)
!857 = !DILocation(line: 342, column: 20, scope: !849)
!858 = !DILocation(line: 342, column: 18, scope: !849)
!859 = !DILocation(line: 344, column: 8, scope: !860)
!860 = distinct !DILexicalBlock(scope: !849, file: !1, line: 344, column: 8)
!861 = !DILocation(line: 344, column: 22, scope: !860)
!862 = !DILocation(line: 344, column: 8, scope: !849)
!863 = !DILocation(line: 345, column: 5, scope: !860)
!864 = !DILocation(line: 346, column: 17, scope: !849)
!865 = !DILocation(line: 346, column: 14, scope: !849)
!866 = !DILocation(line: 347, column: 12, scope: !849)
!867 = !DILocation(line: 347, column: 9, scope: !849)
!868 = !DILocation(line: 341, column: 3, scope: !869)
!869 = !DILexicalBlockFile(scope: !843, file: !1, discriminator: 2)
!870 = !DILocation(line: 349, column: 3, scope: !843)
!871 = !DILocation(line: 353, column: 6, scope: !872)
!872 = distinct !DILexicalBlock(scope: !248, file: !1, line: 353, column: 6)
!873 = !DILocation(line: 353, column: 13, scope: !872)
!874 = !DILocation(line: 353, column: 21, scope: !872)
!875 = !DILocation(line: 353, column: 28, scope: !872)
!876 = !DILocation(line: 353, column: 19, scope: !872)
!877 = !DILocation(line: 353, column: 6, scope: !248)
!878 = !DILocation(line: 356, column: 22, scope: !879)
!879 = distinct !DILexicalBlock(scope: !872, file: !1, line: 353, column: 41)
!880 = !DILocation(line: 356, column: 34, scope: !879)
!881 = !DILocation(line: 356, column: 41, scope: !879)
!882 = !DILocation(line: 356, column: 32, scope: !879)
!883 = !DILocation(line: 356, column: 13, scope: !879)
!884 = !DILocation(line: 357, column: 4, scope: !879)
!885 = !DILocation(line: 357, column: 11, scope: !879)
!886 = !DILocation(line: 356, column: 13, scope: !887)
!887 = !DILexicalBlockFile(scope: !879, file: !1, discriminator: 1)
!888 = !DILocation(line: 357, column: 27, scope: !887)
!889 = !DILocation(line: 356, column: 13, scope: !890)
!890 = !DILexicalBlockFile(scope: !879, file: !1, discriminator: 2)
!891 = !DILocation(line: 356, column: 13, scope: !892)
!892 = !DILexicalBlockFile(scope: !879, file: !1, discriminator: 3)
!893 = !DILocation(line: 356, column: 11, scope: !892)
!894 = !DILocation(line: 358, column: 10, scope: !879)
!895 = !DILocation(line: 358, column: 17, scope: !879)
!896 = !DILocation(line: 358, column: 23, scope: !879)
!897 = !DILocation(line: 358, column: 29, scope: !879)
!898 = !DILocation(line: 358, column: 3, scope: !879)
!899 = !DILocation(line: 359, column: 18, scope: !879)
!900 = !DILocation(line: 359, column: 3, scope: !879)
!901 = !DILocation(line: 359, column: 10, scope: !879)
!902 = !DILocation(line: 359, column: 15, scope: !879)
!903 = !DILocation(line: 360, column: 19, scope: !879)
!904 = !DILocation(line: 360, column: 3, scope: !879)
!905 = !DILocation(line: 360, column: 10, scope: !879)
!906 = !DILocation(line: 360, column: 16, scope: !879)
!907 = !DILocation(line: 361, column: 11, scope: !879)
!908 = !DILocation(line: 361, column: 8, scope: !879)
!909 = !DILocation(line: 362, column: 16, scope: !879)
!910 = !DILocation(line: 362, column: 13, scope: !879)
!911 = !DILocation(line: 364, column: 7, scope: !912)
!912 = distinct !DILexicalBlock(scope: !879, file: !1, line: 364, column: 7)
!913 = !DILocation(line: 364, column: 14, scope: !912)
!914 = !DILocation(line: 364, column: 20, scope: !912)
!915 = !DILocation(line: 364, column: 7, scope: !879)
!916 = !DILocalVariable(name: "p", scope: !917, file: !1, line: 365, type: !95)
!917 = distinct !DILexicalBlock(scope: !912, file: !1, line: 364, column: 26)
!918 = !DILocation(line: 365, column: 10, scope: !917)
!919 = !DILocation(line: 365, column: 14, scope: !917)
!920 = !DILocation(line: 365, column: 21, scope: !917)
!921 = !DILocalVariable(name: "to_write", scope: !917, file: !1, line: 366, type: !45)
!922 = !DILocation(line: 366, column: 11, scope: !917)
!923 = !DILocation(line: 366, column: 22, scope: !917)
!924 = !DILocation(line: 366, column: 29, scope: !917)
!925 = !DILocation(line: 367, column: 4, scope: !917)
!926 = !DILocation(line: 367, column: 11, scope: !927)
!927 = !DILexicalBlockFile(scope: !917, file: !1, discriminator: 1)
!928 = !DILocation(line: 367, column: 20, scope: !927)
!929 = !DILocation(line: 367, column: 4, scope: !927)
!930 = !DILocation(line: 368, column: 22, scope: !931)
!931 = distinct !DILexicalBlock(scope: !917, file: !1, line: 367, column: 25)
!932 = !DILocation(line: 368, column: 25, scope: !931)
!933 = !DILocation(line: 368, column: 41, scope: !931)
!934 = !DILocation(line: 368, column: 44, scope: !931)
!935 = !DILocation(line: 369, column: 9, scope: !931)
!936 = !DILocation(line: 369, column: 12, scope: !931)
!937 = !DILocation(line: 369, column: 25, scope: !931)
!938 = !DILocation(line: 369, column: 28, scope: !931)
!939 = !DILocation(line: 368, column: 21, scope: !931)
!940 = !DILocation(line: 368, column: 19, scope: !931)
!941 = !DILocation(line: 370, column: 9, scope: !942)
!942 = distinct !DILexicalBlock(scope: !931, file: !1, line: 370, column: 9)
!943 = !DILocation(line: 370, column: 23, scope: !942)
!944 = !DILocation(line: 370, column: 9, scope: !931)
!945 = !DILocation(line: 371, column: 6, scope: !942)
!946 = !DILocation(line: 372, column: 17, scope: !947)
!947 = distinct !DILexicalBlock(scope: !931, file: !1, line: 372, column: 9)
!948 = !DILocation(line: 372, column: 33, scope: !947)
!949 = !DILocation(line: 372, column: 31, scope: !947)
!950 = !DILocation(line: 372, column: 9, scope: !931)
!951 = !DILocation(line: 373, column: 26, scope: !952)
!952 = distinct !DILexicalBlock(scope: !947, file: !1, line: 372, column: 43)
!953 = !DILocation(line: 373, column: 29, scope: !952)
!954 = !DILocation(line: 373, column: 6, scope: !952)
!955 = !DILocation(line: 375, column: 6, scope: !952)
!956 = !DILocation(line: 377, column: 10, scope: !931)
!957 = !DILocation(line: 377, column: 7, scope: !931)
!958 = !DILocation(line: 378, column: 17, scope: !931)
!959 = !DILocation(line: 378, column: 14, scope: !931)
!960 = !DILocation(line: 367, column: 4, scope: !961)
!961 = !DILexicalBlockFile(scope: !917, file: !1, discriminator: 2)
!962 = !DILocation(line: 380, column: 18, scope: !917)
!963 = !DILocation(line: 380, column: 25, scope: !917)
!964 = !DILocation(line: 380, column: 4, scope: !917)
!965 = !DILocation(line: 380, column: 11, scope: !917)
!966 = !DILocation(line: 380, column: 16, scope: !917)
!967 = !DILocation(line: 381, column: 19, scope: !917)
!968 = !DILocation(line: 381, column: 26, scope: !917)
!969 = !DILocation(line: 381, column: 4, scope: !917)
!970 = !DILocation(line: 381, column: 11, scope: !917)
!971 = !DILocation(line: 381, column: 17, scope: !917)
!972 = !DILocation(line: 382, column: 3, scope: !917)
!973 = !DILocation(line: 383, column: 2, scope: !879)
!974 = !DILocation(line: 385, column: 2, scope: !248)
!975 = !DILocation(line: 385, column: 17, scope: !976)
!976 = !DILexicalBlockFile(scope: !248, file: !1, discriminator: 1)
!977 = !DILocation(line: 385, column: 30, scope: !976)
!978 = !DILocation(line: 385, column: 37, scope: !976)
!979 = !DILocation(line: 385, column: 27, scope: !976)
!980 = !DILocation(line: 385, column: 2, scope: !976)
!981 = !DILocation(line: 387, column: 20, scope: !982)
!982 = distinct !DILexicalBlock(scope: !248, file: !1, line: 385, column: 50)
!983 = !DILocation(line: 387, column: 23, scope: !982)
!984 = !DILocation(line: 387, column: 39, scope: !982)
!985 = !DILocation(line: 387, column: 42, scope: !982)
!986 = !DILocation(line: 388, column: 7, scope: !982)
!987 = !DILocation(line: 388, column: 10, scope: !982)
!988 = !DILocation(line: 388, column: 23, scope: !982)
!989 = !DILocation(line: 388, column: 29, scope: !982)
!990 = !DILocation(line: 388, column: 36, scope: !982)
!991 = !DILocation(line: 387, column: 19, scope: !982)
!992 = !DILocation(line: 387, column: 17, scope: !982)
!993 = !DILocation(line: 389, column: 7, scope: !994)
!994 = distinct !DILexicalBlock(scope: !982, file: !1, line: 389, column: 7)
!995 = !DILocation(line: 389, column: 21, scope: !994)
!996 = !DILocation(line: 389, column: 7, scope: !982)
!997 = !DILocation(line: 390, column: 4, scope: !994)
!998 = !DILocation(line: 391, column: 11, scope: !982)
!999 = !DILocation(line: 391, column: 8, scope: !982)
!1000 = !DILocation(line: 392, column: 16, scope: !982)
!1001 = !DILocation(line: 392, column: 13, scope: !982)
!1002 = !DILocation(line: 385, column: 2, scope: !1003)
!1003 = !DILexicalBlockFile(scope: !248, file: !1, discriminator: 2)
!1004 = !DILocation(line: 395, column: 6, scope: !1005)
!1005 = distinct !DILexicalBlock(scope: !248, file: !1, line: 395, column: 6)
!1006 = !DILocation(line: 395, column: 16, scope: !1005)
!1007 = !DILocation(line: 395, column: 6, scope: !248)
!1008 = !DILocation(line: 397, column: 10, scope: !1009)
!1009 = distinct !DILexicalBlock(scope: !1005, file: !1, line: 395, column: 21)
!1010 = !DILocation(line: 397, column: 17, scope: !1009)
!1011 = !DILocation(line: 397, column: 23, scope: !1009)
!1012 = !DILocation(line: 397, column: 29, scope: !1009)
!1013 = !DILocation(line: 397, column: 3, scope: !1009)
!1014 = !DILocation(line: 398, column: 18, scope: !1009)
!1015 = !DILocation(line: 398, column: 3, scope: !1009)
!1016 = !DILocation(line: 398, column: 10, scope: !1009)
!1017 = !DILocation(line: 398, column: 15, scope: !1009)
!1018 = !DILocation(line: 399, column: 19, scope: !1009)
!1019 = !DILocation(line: 399, column: 3, scope: !1009)
!1020 = !DILocation(line: 399, column: 10, scope: !1009)
!1021 = !DILocation(line: 399, column: 16, scope: !1009)
!1022 = !DILocation(line: 400, column: 2, scope: !1009)
!1023 = !DILocation(line: 401, column: 2, scope: !248)
!1024 = !DILocation(line: 402, column: 1, scope: !248)
!1025 = !DILocalVariable(name: "f", arg: 1, scope: !249, file: !1, line: 405, type: !137)
!1026 = !DILocation(line: 405, column: 57, scope: !249)
!1027 = !DILocalVariable(name: "a", scope: !249, file: !1, line: 407, type: !4)
!1028 = !DILocation(line: 407, column: 24, scope: !249)
!1029 = !DILocation(line: 407, column: 52, scope: !249)
!1030 = !DILocation(line: 407, column: 55, scope: !249)
!1031 = !DILocation(line: 407, column: 28, scope: !249)
!1032 = !DILocalVariable(name: "state", scope: !249, file: !1, line: 408, type: !196)
!1033 = !DILocation(line: 408, column: 23, scope: !249)
!1034 = !DILocation(line: 408, column: 54, scope: !249)
!1035 = !DILocation(line: 408, column: 57, scope: !249)
!1036 = !DILocation(line: 408, column: 31, scope: !249)
!1037 = !DILocalVariable(name: "block_length", scope: !249, file: !1, line: 409, type: !38)
!1038 = !DILocation(line: 409, column: 10, scope: !249)
!1039 = !DILocalVariable(name: "target_block_length", scope: !249, file: !1, line: 410, type: !38)
!1040 = !DILocation(line: 410, column: 10, scope: !249)
!1041 = !DILocalVariable(name: "bytes_written", scope: !249, file: !1, line: 411, type: !38)
!1042 = !DILocation(line: 411, column: 10, scope: !249)
!1043 = !DILocalVariable(name: "ret", scope: !249, file: !1, line: 412, type: !23)
!1044 = !DILocation(line: 412, column: 6, scope: !249)
!1045 = !DILocation(line: 415, column: 6, scope: !1046)
!1046 = distinct !DILexicalBlock(scope: !249, file: !1, line: 415, column: 6)
!1047 = !DILocation(line: 415, column: 13, scope: !1046)
!1048 = !DILocation(line: 415, column: 21, scope: !1046)
!1049 = !DILocation(line: 415, column: 28, scope: !1046)
!1050 = !DILocation(line: 415, column: 18, scope: !1046)
!1051 = !DILocation(line: 415, column: 6, scope: !249)
!1052 = !DILocation(line: 416, column: 18, scope: !1053)
!1053 = distinct !DILexicalBlock(scope: !1046, file: !1, line: 415, column: 36)
!1054 = !DILocation(line: 416, column: 25, scope: !1053)
!1055 = !DILocation(line: 416, column: 39, scope: !1053)
!1056 = !DILocation(line: 416, column: 46, scope: !1053)
!1057 = !DILocation(line: 416, column: 37, scope: !1053)
!1058 = !DILocation(line: 416, column: 16, scope: !1053)
!1059 = !DILocation(line: 419, column: 7, scope: !1060)
!1060 = distinct !DILexicalBlock(scope: !1053, file: !1, line: 419, column: 7)
!1061 = !DILocation(line: 419, column: 10, scope: !1060)
!1062 = !DILocation(line: 419, column: 30, scope: !1060)
!1063 = !DILocation(line: 419, column: 7, scope: !1053)
!1064 = !DILocation(line: 421, column: 26, scope: !1060)
!1065 = !DILocation(line: 421, column: 29, scope: !1060)
!1066 = !DILocation(line: 421, column: 24, scope: !1060)
!1067 = !DILocation(line: 421, column: 4, scope: !1060)
!1068 = !DILocation(line: 424, column: 26, scope: !1060)
!1069 = !DILocation(line: 424, column: 29, scope: !1060)
!1070 = !DILocation(line: 425, column: 11, scope: !1060)
!1071 = !DILocation(line: 425, column: 26, scope: !1060)
!1072 = !DILocation(line: 425, column: 29, scope: !1060)
!1073 = !DILocation(line: 425, column: 24, scope: !1060)
!1074 = !DILocation(line: 425, column: 49, scope: !1060)
!1075 = !DILocation(line: 426, column: 12, scope: !1060)
!1076 = !DILocation(line: 426, column: 15, scope: !1060)
!1077 = !DILocation(line: 425, column: 54, scope: !1060)
!1078 = !DILocation(line: 424, column: 49, scope: !1060)
!1079 = !DILocation(line: 424, column: 24, scope: !1060)
!1080 = !DILocation(line: 427, column: 7, scope: !1081)
!1081 = distinct !DILexicalBlock(scope: !1053, file: !1, line: 427, column: 7)
!1082 = !DILocation(line: 427, column: 29, scope: !1081)
!1083 = !DILocation(line: 427, column: 32, scope: !1081)
!1084 = !DILocation(line: 427, column: 27, scope: !1081)
!1085 = !DILocation(line: 427, column: 7, scope: !1053)
!1086 = !DILocation(line: 428, column: 26, scope: !1081)
!1087 = !DILocation(line: 428, column: 29, scope: !1081)
!1088 = !DILocation(line: 428, column: 24, scope: !1081)
!1089 = !DILocation(line: 428, column: 4, scope: !1081)
!1090 = !DILocation(line: 429, column: 7, scope: !1091)
!1091 = distinct !DILexicalBlock(scope: !1053, file: !1, line: 429, column: 7)
!1092 = !DILocation(line: 429, column: 22, scope: !1091)
!1093 = !DILocation(line: 429, column: 20, scope: !1091)
!1094 = !DILocation(line: 429, column: 7, scope: !1053)
!1095 = !DILocation(line: 430, column: 11, scope: !1096)
!1096 = distinct !DILexicalBlock(scope: !1091, file: !1, line: 429, column: 43)
!1097 = !DILocation(line: 430, column: 18, scope: !1096)
!1098 = !DILocation(line: 431, column: 8, scope: !1096)
!1099 = !DILocation(line: 431, column: 30, scope: !1096)
!1100 = !DILocation(line: 431, column: 28, scope: !1096)
!1101 = !DILocation(line: 430, column: 4, scope: !1096)
!1102 = !DILocation(line: 432, column: 19, scope: !1096)
!1103 = !DILocation(line: 432, column: 17, scope: !1096)
!1104 = !DILocation(line: 433, column: 3, scope: !1096)
!1105 = !DILocation(line: 434, column: 20, scope: !1053)
!1106 = !DILocation(line: 434, column: 23, scope: !1053)
!1107 = !DILocation(line: 434, column: 39, scope: !1053)
!1108 = !DILocation(line: 434, column: 42, scope: !1053)
!1109 = !DILocation(line: 435, column: 7, scope: !1053)
!1110 = !DILocation(line: 435, column: 10, scope: !1053)
!1111 = !DILocation(line: 435, column: 23, scope: !1053)
!1112 = !DILocation(line: 435, column: 30, scope: !1053)
!1113 = !DILocation(line: 435, column: 38, scope: !1053)
!1114 = !DILocation(line: 434, column: 19, scope: !1053)
!1115 = !DILocation(line: 434, column: 17, scope: !1053)
!1116 = !DILocation(line: 436, column: 9, scope: !1053)
!1117 = !DILocation(line: 436, column: 23, scope: !1053)
!1118 = !DILocation(line: 436, column: 7, scope: !1053)
!1119 = !DILocation(line: 437, column: 2, scope: !1053)
!1120 = !DILocation(line: 438, column: 6, scope: !1121)
!1121 = distinct !DILexicalBlock(scope: !249, file: !1, line: 438, column: 6)
!1122 = !DILocation(line: 438, column: 9, scope: !1121)
!1123 = !DILocation(line: 438, column: 6, scope: !249)
!1124 = !DILocation(line: 439, column: 5, scope: !1121)
!1125 = !DILocation(line: 439, column: 8, scope: !1121)
!1126 = !DILocation(line: 439, column: 24, scope: !1121)
!1127 = !DILocation(line: 439, column: 27, scope: !1121)
!1128 = !DILocation(line: 439, column: 36, scope: !1121)
!1129 = !DILocation(line: 439, column: 39, scope: !1121)
!1130 = !DILocation(line: 439, column: 3, scope: !1121)
!1131 = !DILocation(line: 440, column: 7, scope: !249)
!1132 = !DILocation(line: 440, column: 14, scope: !249)
!1133 = !DILocation(line: 440, column: 2, scope: !249)
!1134 = !DILocation(line: 441, column: 7, scope: !249)
!1135 = !DILocation(line: 441, column: 2, scope: !249)
!1136 = !DILocation(line: 443, column: 2, scope: !249)
!1137 = !DILocation(line: 443, column: 5, scope: !249)
!1138 = !DILocation(line: 443, column: 11, scope: !249)
!1139 = !DILocation(line: 444, column: 2, scope: !249)
!1140 = !DILocation(line: 444, column: 5, scope: !249)
!1141 = !DILocation(line: 444, column: 17, scope: !249)
!1142 = !DILocation(line: 446, column: 6, scope: !1143)
!1143 = distinct !DILexicalBlock(scope: !249, file: !1, line: 446, column: 6)
!1144 = !DILocation(line: 446, column: 9, scope: !1143)
!1145 = !DILocation(line: 446, column: 20, scope: !1143)
!1146 = !DILocation(line: 446, column: 6, scope: !249)
!1147 = !DILocation(line: 447, column: 10, scope: !1148)
!1148 = distinct !DILexicalBlock(scope: !1143, file: !1, line: 446, column: 29)
!1149 = !DILocation(line: 447, column: 13, scope: !1148)
!1150 = !DILocation(line: 447, column: 35, scope: !1148)
!1151 = !DILocation(line: 447, column: 38, scope: !1148)
!1152 = !DILocation(line: 447, column: 28, scope: !1148)
!1153 = !DILocation(line: 447, column: 3, scope: !1154)
!1154 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 1)
!1155 = !DILocation(line: 448, column: 8, scope: !1148)
!1156 = !DILocation(line: 448, column: 11, scope: !1148)
!1157 = !DILocation(line: 448, column: 3, scope: !1148)
!1158 = !DILocation(line: 449, column: 3, scope: !1148)
!1159 = !DILocation(line: 449, column: 6, scope: !1148)
!1160 = !DILocation(line: 449, column: 17, scope: !1148)
!1161 = !DILocation(line: 450, column: 2, scope: !1148)
!1162 = !DILocation(line: 451, column: 10, scope: !249)
!1163 = !DILocation(line: 451, column: 2, scope: !249)
!1164 = !DILocalVariable(name: "_a", arg: 1, scope: !229, file: !1, line: 547, type: !24)
!1165 = !DILocation(line: 547, column: 46, scope: !229)
!1166 = !DILocalVariable(name: "a", scope: !229, file: !1, line: 549, type: !4)
!1167 = !DILocation(line: 549, column: 24, scope: !229)
!1168 = !DILocation(line: 549, column: 52, scope: !229)
!1169 = !DILocation(line: 549, column: 28, scope: !229)
!1170 = !DILocalVariable(name: "r", scope: !229, file: !1, line: 550, type: !23)
!1171 = !DILocation(line: 550, column: 6, scope: !229)
!1172 = !DILocalVariable(name: "r1", scope: !229, file: !1, line: 550, type: !23)
!1173 = !DILocation(line: 550, column: 22, scope: !229)
!1174 = !DILocation(line: 552, column: 2, scope: !229)
!1175 = !DILocation(line: 552, column: 9, scope: !1176)
!1176 = !DILexicalBlockFile(scope: !229, file: !1, discriminator: 1)
!1177 = !DILocation(line: 552, column: 12, scope: !1176)
!1178 = !DILocation(line: 552, column: 25, scope: !1176)
!1179 = !DILocation(line: 552, column: 2, scope: !1176)
!1180 = !DILocalVariable(name: "next", scope: !1181, file: !1, line: 553, type: !137)
!1181 = distinct !DILexicalBlock(scope: !229, file: !1, line: 552, column: 34)
!1182 = !DILocation(line: 553, column: 32, scope: !1181)
!1183 = !DILocation(line: 554, column: 9, scope: !1181)
!1184 = !DILocation(line: 554, column: 12, scope: !1181)
!1185 = !DILocation(line: 554, column: 26, scope: !1181)
!1186 = !DILocation(line: 555, column: 7, scope: !1187)
!1187 = distinct !DILexicalBlock(scope: !1181, file: !1, line: 555, column: 7)
!1188 = !DILocation(line: 555, column: 10, scope: !1187)
!1189 = !DILocation(line: 555, column: 24, scope: !1187)
!1190 = !DILocation(line: 555, column: 29, scope: !1187)
!1191 = !DILocation(line: 555, column: 7, scope: !1181)
!1192 = !DILocation(line: 556, column: 11, scope: !1193)
!1193 = distinct !DILexicalBlock(scope: !1187, file: !1, line: 555, column: 38)
!1194 = !DILocation(line: 556, column: 14, scope: !1193)
!1195 = !DILocation(line: 556, column: 28, scope: !1193)
!1196 = !DILocation(line: 556, column: 34, scope: !1193)
!1197 = !DILocation(line: 556, column: 37, scope: !1193)
!1198 = !DILocation(line: 556, column: 9, scope: !1193)
!1199 = !DILocation(line: 556, column: 7, scope: !1193)
!1200 = !DILocation(line: 557, column: 8, scope: !1201)
!1201 = distinct !DILexicalBlock(scope: !1193, file: !1, line: 557, column: 8)
!1202 = !DILocation(line: 557, column: 12, scope: !1201)
!1203 = !DILocation(line: 557, column: 10, scope: !1201)
!1204 = !DILocation(line: 557, column: 8, scope: !1193)
!1205 = !DILocation(line: 558, column: 9, scope: !1201)
!1206 = !DILocation(line: 558, column: 7, scope: !1201)
!1207 = !DILocation(line: 558, column: 5, scope: !1201)
!1208 = !DILocation(line: 559, column: 3, scope: !1193)
!1209 = !DILocation(line: 560, column: 8, scope: !1181)
!1210 = !DILocation(line: 560, column: 11, scope: !1181)
!1211 = !DILocation(line: 560, column: 3, scope: !1181)
!1212 = !DILocation(line: 561, column: 21, scope: !1181)
!1213 = !DILocation(line: 561, column: 3, scope: !1181)
!1214 = !DILocation(line: 561, column: 6, scope: !1181)
!1215 = !DILocation(line: 561, column: 19, scope: !1181)
!1216 = !DILocation(line: 552, column: 2, scope: !1217)
!1217 = !DILexicalBlockFile(scope: !229, file: !1, discriminator: 2)
!1218 = !DILocation(line: 563, column: 2, scope: !229)
!1219 = !DILocation(line: 563, column: 5, scope: !229)
!1220 = !DILocation(line: 563, column: 17, scope: !229)
!1221 = !DILocation(line: 564, column: 1, scope: !229)
!1222 = !DILocalVariable(name: "_a", arg: 1, scope: !235, file: !1, line: 496, type: !24)
!1223 = !DILocation(line: 496, column: 38, scope: !235)
!1224 = !DILocalVariable(name: "a", scope: !235, file: !1, line: 498, type: !4)
!1225 = !DILocation(line: 498, column: 24, scope: !235)
!1226 = !DILocation(line: 498, column: 52, scope: !235)
!1227 = !DILocation(line: 498, column: 28, scope: !235)
!1228 = !DILocalVariable(name: "r", scope: !235, file: !1, line: 499, type: !23)
!1229 = !DILocation(line: 499, column: 6, scope: !235)
!1230 = !DILocalVariable(name: "r1", scope: !235, file: !1, line: 499, type: !23)
!1231 = !DILocation(line: 499, column: 22, scope: !235)
!1232 = !DILocation(line: 501, column: 2, scope: !235)
!1233 = !DILocalVariable(name: "magic_test", scope: !1234, file: !1, line: 501, type: !23)
!1234 = distinct !DILexicalBlock(scope: !235, file: !1, line: 501, column: 2)
!1235 = !DILocation(line: 501, column: 2, scope: !1234)
!1236 = !DILocation(line: 501, column: 2, scope: !1237)
!1237 = !DILexicalBlockFile(scope: !1234, file: !1, discriminator: 1)
!1238 = !DILocation(line: 501, column: 2, scope: !1239)
!1239 = !DILexicalBlockFile(scope: !1240, file: !1, discriminator: 2)
!1240 = distinct !DILexicalBlock(scope: !1234, file: !1, line: 501, column: 2)
!1241 = !DILocation(line: 501, column: 2, scope: !1242)
!1242 = !DILexicalBlockFile(scope: !1234, file: !1, discriminator: 3)
!1243 = !DILocation(line: 504, column: 6, scope: !1244)
!1244 = distinct !DILexicalBlock(scope: !235, file: !1, line: 504, column: 6)
!1245 = !DILocation(line: 504, column: 9, scope: !1244)
!1246 = !DILocation(line: 504, column: 17, scope: !1244)
!1247 = !DILocation(line: 504, column: 23, scope: !1244)
!1248 = !DILocation(line: 505, column: 6, scope: !1244)
!1249 = !DILocation(line: 505, column: 9, scope: !1250)
!1250 = !DILexicalBlockFile(scope: !1244, file: !1, discriminator: 1)
!1251 = !DILocation(line: 505, column: 12, scope: !1250)
!1252 = !DILocation(line: 505, column: 20, scope: !1250)
!1253 = !DILocation(line: 505, column: 26, scope: !1250)
!1254 = !DILocation(line: 504, column: 6, scope: !1255)
!1255 = !DILexicalBlockFile(scope: !235, file: !1, discriminator: 1)
!1256 = !DILocation(line: 506, column: 3, scope: !1244)
!1257 = !DILocation(line: 508, column: 23, scope: !235)
!1258 = !DILocation(line: 508, column: 26, scope: !235)
!1259 = !DILocation(line: 508, column: 2, scope: !235)
!1260 = !DILocation(line: 511, column: 6, scope: !1261)
!1261 = distinct !DILexicalBlock(scope: !235, file: !1, line: 511, column: 6)
!1262 = !DILocation(line: 511, column: 9, scope: !1261)
!1263 = !DILocation(line: 511, column: 17, scope: !1261)
!1264 = !DILocation(line: 511, column: 23, scope: !1261)
!1265 = !DILocation(line: 512, column: 6, scope: !1261)
!1266 = !DILocation(line: 512, column: 9, scope: !1267)
!1267 = !DILexicalBlockFile(scope: !1261, file: !1, discriminator: 1)
!1268 = !DILocation(line: 512, column: 12, scope: !1267)
!1269 = !DILocation(line: 512, column: 32, scope: !1267)
!1270 = !DILocation(line: 511, column: 6, scope: !1255)
!1271 = !DILocation(line: 513, column: 9, scope: !1261)
!1272 = !DILocation(line: 513, column: 12, scope: !1261)
!1273 = !DILocation(line: 513, column: 33, scope: !1261)
!1274 = !DILocation(line: 513, column: 8, scope: !1261)
!1275 = !DILocation(line: 513, column: 5, scope: !1261)
!1276 = !DILocation(line: 513, column: 3, scope: !1261)
!1277 = !DILocation(line: 517, column: 6, scope: !1278)
!1278 = distinct !DILexicalBlock(scope: !235, file: !1, line: 517, column: 6)
!1279 = !DILocation(line: 517, column: 9, scope: !1278)
!1280 = !DILocation(line: 517, column: 22, scope: !1278)
!1281 = !DILocation(line: 517, column: 6, scope: !235)
!1282 = !DILocation(line: 518, column: 9, scope: !1283)
!1283 = distinct !DILexicalBlock(scope: !1278, file: !1, line: 517, column: 31)
!1284 = !DILocation(line: 518, column: 12, scope: !1283)
!1285 = !DILocation(line: 518, column: 26, scope: !1283)
!1286 = !DILocation(line: 518, column: 8, scope: !1283)
!1287 = !DILocation(line: 518, column: 6, scope: !1283)
!1288 = !DILocation(line: 519, column: 7, scope: !1289)
!1289 = distinct !DILexicalBlock(scope: !1283, file: !1, line: 519, column: 7)
!1290 = !DILocation(line: 519, column: 12, scope: !1289)
!1291 = !DILocation(line: 519, column: 10, scope: !1289)
!1292 = !DILocation(line: 519, column: 7, scope: !1283)
!1293 = !DILocation(line: 520, column: 8, scope: !1289)
!1294 = !DILocation(line: 520, column: 6, scope: !1289)
!1295 = !DILocation(line: 520, column: 4, scope: !1289)
!1296 = !DILocation(line: 521, column: 2, scope: !1283)
!1297 = !DILocation(line: 524, column: 36, scope: !235)
!1298 = !DILocation(line: 524, column: 39, scope: !235)
!1299 = !DILocation(line: 524, column: 7, scope: !235)
!1300 = !DILocation(line: 524, column: 5, scope: !235)
!1301 = !DILocation(line: 525, column: 6, scope: !1302)
!1302 = distinct !DILexicalBlock(scope: !235, file: !1, line: 525, column: 6)
!1303 = !DILocation(line: 525, column: 11, scope: !1302)
!1304 = !DILocation(line: 525, column: 9, scope: !1302)
!1305 = !DILocation(line: 525, column: 6, scope: !235)
!1306 = !DILocation(line: 526, column: 7, scope: !1302)
!1307 = !DILocation(line: 526, column: 5, scope: !1302)
!1308 = !DILocation(line: 526, column: 3, scope: !1302)
!1309 = !DILocation(line: 528, column: 6, scope: !1310)
!1310 = distinct !DILexicalBlock(scope: !235, file: !1, line: 528, column: 6)
!1311 = !DILocation(line: 528, column: 9, scope: !1310)
!1312 = !DILocation(line: 528, column: 17, scope: !1310)
!1313 = !DILocation(line: 528, column: 23, scope: !1310)
!1314 = !DILocation(line: 528, column: 6, scope: !235)
!1315 = !DILocation(line: 529, column: 3, scope: !1310)
!1316 = !DILocation(line: 529, column: 6, scope: !1310)
!1317 = !DILocation(line: 529, column: 14, scope: !1310)
!1318 = !DILocation(line: 529, column: 20, scope: !1310)
!1319 = !DILocation(line: 530, column: 10, scope: !235)
!1320 = !DILocation(line: 530, column: 2, scope: !235)
!1321 = !DILocation(line: 531, column: 1, scope: !235)
!1322 = !DILocalVariable(name: "_a", arg: 1, scope: !236, file: !1, line: 730, type: !24)
!1323 = !DILocation(line: 730, column: 39, scope: !236)
!1324 = !DILocalVariable(name: "n", arg: 2, scope: !236, file: !1, line: 730, type: !23)
!1325 = !DILocation(line: 730, column: 47, scope: !236)
!1326 = !DILocalVariable(name: "f", scope: !236, file: !1, line: 732, type: !137)
!1327 = !DILocation(line: 732, column: 31, scope: !236)
!1328 = !DILocation(line: 732, column: 49, scope: !236)
!1329 = !DILocation(line: 732, column: 53, scope: !236)
!1330 = !DILocation(line: 732, column: 35, scope: !236)
!1331 = !DILocation(line: 733, column: 9, scope: !236)
!1332 = !DILocation(line: 733, column: 11, scope: !236)
!1333 = !DILocation(line: 733, column: 9, scope: !1334)
!1334 = !DILexicalBlockFile(scope: !236, file: !1, discriminator: 1)
!1335 = !DILocation(line: 733, column: 26, scope: !1336)
!1336 = !DILexicalBlockFile(scope: !236, file: !1, discriminator: 2)
!1337 = !DILocation(line: 733, column: 29, scope: !1336)
!1338 = !DILocation(line: 733, column: 9, scope: !1336)
!1339 = !DILocation(line: 733, column: 9, scope: !1340)
!1340 = !DILexicalBlockFile(scope: !236, file: !1, discriminator: 3)
!1341 = !DILocation(line: 733, column: 2, scope: !1340)
!1342 = !DILocalVariable(name: "_a", arg: 1, scope: !240, file: !1, line: 716, type: !24)
!1343 = !DILocation(line: 716, column: 38, scope: !240)
!1344 = !DILocalVariable(name: "n", arg: 2, scope: !240, file: !1, line: 716, type: !23)
!1345 = !DILocation(line: 716, column: 46, scope: !240)
!1346 = !DILocalVariable(name: "f", scope: !240, file: !1, line: 718, type: !137)
!1347 = !DILocation(line: 718, column: 31, scope: !240)
!1348 = !DILocation(line: 718, column: 49, scope: !240)
!1349 = !DILocation(line: 718, column: 53, scope: !240)
!1350 = !DILocation(line: 718, column: 35, scope: !240)
!1351 = !DILocation(line: 719, column: 9, scope: !240)
!1352 = !DILocation(line: 719, column: 11, scope: !240)
!1353 = !DILocation(line: 719, column: 9, scope: !1354)
!1354 = !DILexicalBlockFile(scope: !240, file: !1, discriminator: 1)
!1355 = !DILocation(line: 719, column: 26, scope: !1356)
!1356 = !DILexicalBlockFile(scope: !240, file: !1, discriminator: 2)
!1357 = !DILocation(line: 719, column: 29, scope: !1356)
!1358 = !DILocation(line: 719, column: 9, scope: !1356)
!1359 = !DILocation(line: 719, column: 9, scope: !1360)
!1360 = !DILexicalBlockFile(scope: !240, file: !1, discriminator: 3)
!1361 = !DILocation(line: 719, column: 2, scope: !1360)
!1362 = !DILocalVariable(name: "_a", arg: 1, scope: !241, file: !1, line: 723, type: !24)
!1363 = !DILocation(line: 723, column: 38, scope: !241)
!1364 = !DILocalVariable(name: "n", arg: 2, scope: !241, file: !1, line: 723, type: !23)
!1365 = !DILocation(line: 723, column: 46, scope: !241)
!1366 = !DILocalVariable(name: "f", scope: !241, file: !1, line: 725, type: !137)
!1367 = !DILocation(line: 725, column: 31, scope: !241)
!1368 = !DILocation(line: 725, column: 49, scope: !241)
!1369 = !DILocation(line: 725, column: 53, scope: !241)
!1370 = !DILocation(line: 725, column: 35, scope: !241)
!1371 = !DILocation(line: 726, column: 9, scope: !241)
!1372 = !DILocation(line: 726, column: 11, scope: !241)
!1373 = !DILocation(line: 726, column: 21, scope: !1374)
!1374 = !DILexicalBlockFile(scope: !241, file: !1, discriminator: 1)
!1375 = !DILocation(line: 726, column: 24, scope: !1374)
!1376 = !DILocation(line: 726, column: 9, scope: !1374)
!1377 = !DILocation(line: 726, column: 9, scope: !1378)
!1378 = !DILexicalBlockFile(scope: !241, file: !1, discriminator: 2)
!1379 = !DILocation(line: 726, column: 9, scope: !1380)
!1380 = !DILexicalBlockFile(scope: !241, file: !1, discriminator: 3)
!1381 = !DILocation(line: 726, column: 2, scope: !1380)
!1382 = !DILocalVariable(name: "_a", arg: 1, scope: !242, file: !1, line: 534, type: !24)
!1383 = !DILocation(line: 534, column: 45, scope: !242)
!1384 = !DILocalVariable(name: "a", scope: !242, file: !1, line: 536, type: !4)
!1385 = !DILocation(line: 536, column: 24, scope: !242)
!1386 = !DILocation(line: 536, column: 52, scope: !242)
!1387 = !DILocation(line: 536, column: 28, scope: !242)
!1388 = !DILocalVariable(name: "p", scope: !242, file: !1, line: 537, type: !137)
!1389 = !DILocation(line: 537, column: 31, scope: !242)
!1390 = !DILocation(line: 537, column: 35, scope: !242)
!1391 = !DILocation(line: 537, column: 38, scope: !242)
!1392 = !DILocalVariable(name: "count", scope: !242, file: !1, line: 538, type: !23)
!1393 = !DILocation(line: 538, column: 6, scope: !242)
!1394 = !DILocation(line: 539, column: 2, scope: !242)
!1395 = !DILocation(line: 539, column: 8, scope: !1396)
!1396 = !DILexicalBlockFile(scope: !242, file: !1, discriminator: 1)
!1397 = !DILocation(line: 539, column: 2, scope: !1396)
!1398 = !DILocation(line: 540, column: 8, scope: !1399)
!1399 = distinct !DILexicalBlock(scope: !242, file: !1, line: 539, column: 11)
!1400 = !DILocation(line: 541, column: 7, scope: !1399)
!1401 = !DILocation(line: 541, column: 10, scope: !1399)
!1402 = !DILocation(line: 541, column: 5, scope: !1399)
!1403 = !DILocation(line: 539, column: 2, scope: !1404)
!1404 = !DILexicalBlockFile(scope: !242, file: !1, discriminator: 2)
!1405 = !DILocation(line: 543, column: 9, scope: !242)
!1406 = !DILocation(line: 543, column: 2, scope: !242)
!1407 = !DILocalVariable(name: "_a", arg: 1, scope: !243, file: !1, line: 574, type: !24)
!1408 = !DILocation(line: 574, column: 37, scope: !243)
!1409 = !DILocalVariable(name: "a", scope: !243, file: !1, line: 576, type: !4)
!1410 = !DILocation(line: 576, column: 24, scope: !243)
!1411 = !DILocation(line: 576, column: 52, scope: !243)
!1412 = !DILocation(line: 576, column: 28, scope: !243)
!1413 = !DILocalVariable(name: "r", scope: !243, file: !1, line: 577, type: !23)
!1414 = !DILocation(line: 577, column: 6, scope: !243)
!1415 = !DILocalVariable(name: "r1", scope: !243, file: !1, line: 577, type: !23)
!1416 = !DILocation(line: 577, column: 22, scope: !243)
!1417 = !DILocation(line: 579, column: 6, scope: !1418)
!1418 = distinct !DILexicalBlock(scope: !243, file: !1, line: 579, column: 6)
!1419 = !DILocation(line: 579, column: 9, scope: !1418)
!1420 = !DILocation(line: 579, column: 6, scope: !243)
!1421 = !DILocation(line: 580, column: 3, scope: !1418)
!1422 = !DILocation(line: 582, column: 2, scope: !243)
!1423 = !DILocalVariable(name: "magic_test", scope: !1424, file: !1, line: 582, type: !23)
!1424 = distinct !DILexicalBlock(scope: !243, file: !1, line: 582, column: 2)
!1425 = !DILocation(line: 582, column: 2, scope: !1424)
!1426 = !DILocation(line: 582, column: 2, scope: !1427)
!1427 = !DILexicalBlockFile(scope: !1424, file: !1, discriminator: 1)
!1428 = !DILocation(line: 582, column: 2, scope: !1429)
!1429 = !DILexicalBlockFile(scope: !1430, file: !1, discriminator: 2)
!1430 = distinct !DILexicalBlock(scope: !1424, file: !1, line: 582, column: 2)
!1431 = !DILocation(line: 582, column: 2, scope: !1432)
!1432 = !DILexicalBlockFile(scope: !1424, file: !1, discriminator: 3)
!1433 = !DILocation(line: 584, column: 6, scope: !1434)
!1434 = distinct !DILexicalBlock(scope: !243, file: !1, line: 584, column: 6)
!1435 = !DILocation(line: 584, column: 9, scope: !1434)
!1436 = !DILocation(line: 584, column: 17, scope: !1434)
!1437 = !DILocation(line: 584, column: 23, scope: !1434)
!1438 = !DILocation(line: 584, column: 6, scope: !243)
!1439 = !DILocation(line: 585, column: 28, scope: !1434)
!1440 = !DILocation(line: 585, column: 31, scope: !1434)
!1441 = !DILocation(line: 585, column: 7, scope: !1434)
!1442 = !DILocation(line: 585, column: 5, scope: !1434)
!1443 = !DILocation(line: 585, column: 3, scope: !1434)
!1444 = !DILocation(line: 588, column: 6, scope: !1445)
!1445 = distinct !DILexicalBlock(scope: !243, file: !1, line: 588, column: 6)
!1446 = !DILocation(line: 588, column: 9, scope: !1445)
!1447 = !DILocation(line: 588, column: 21, scope: !1445)
!1448 = !DILocation(line: 588, column: 6, scope: !243)
!1449 = !DILocation(line: 589, column: 9, scope: !1450)
!1450 = distinct !DILexicalBlock(scope: !1445, file: !1, line: 588, column: 30)
!1451 = !DILocation(line: 589, column: 12, scope: !1450)
!1452 = !DILocation(line: 589, column: 25, scope: !1450)
!1453 = !DILocation(line: 589, column: 8, scope: !1450)
!1454 = !DILocation(line: 589, column: 6, scope: !1450)
!1455 = !DILocation(line: 590, column: 7, scope: !1456)
!1456 = distinct !DILexicalBlock(scope: !1450, file: !1, line: 590, column: 7)
!1457 = !DILocation(line: 590, column: 12, scope: !1456)
!1458 = !DILocation(line: 590, column: 10, scope: !1456)
!1459 = !DILocation(line: 590, column: 7, scope: !1450)
!1460 = !DILocation(line: 591, column: 8, scope: !1456)
!1461 = !DILocation(line: 591, column: 6, scope: !1456)
!1462 = !DILocation(line: 591, column: 4, scope: !1456)
!1463 = !DILocation(line: 592, column: 2, scope: !1450)
!1464 = !DILocation(line: 594, column: 31, scope: !243)
!1465 = !DILocation(line: 594, column: 2, scope: !243)
!1466 = !DILocation(line: 597, column: 40, scope: !243)
!1467 = !DILocation(line: 597, column: 43, scope: !243)
!1468 = !DILocation(line: 597, column: 15, scope: !243)
!1469 = !DILocation(line: 597, column: 7, scope: !243)
!1470 = !DILocation(line: 597, column: 2, scope: !243)
!1471 = !DILocation(line: 598, column: 23, scope: !243)
!1472 = !DILocation(line: 598, column: 26, scope: !243)
!1473 = !DILocation(line: 598, column: 34, scope: !243)
!1474 = !DILocation(line: 598, column: 2, scope: !243)
!1475 = !DILocation(line: 599, column: 6, scope: !1476)
!1476 = distinct !DILexicalBlock(scope: !243, file: !1, line: 599, column: 6)
!1477 = !DILocation(line: 599, column: 9, scope: !1476)
!1478 = !DILocation(line: 599, column: 20, scope: !1476)
!1479 = !DILocation(line: 599, column: 6, scope: !243)
!1480 = !DILocation(line: 601, column: 10, scope: !1481)
!1481 = distinct !DILexicalBlock(scope: !1476, file: !1, line: 599, column: 29)
!1482 = !DILocation(line: 601, column: 13, scope: !1481)
!1483 = !DILocation(line: 601, column: 35, scope: !1481)
!1484 = !DILocation(line: 601, column: 38, scope: !1481)
!1485 = !DILocation(line: 601, column: 28, scope: !1481)
!1486 = !DILocation(line: 601, column: 3, scope: !1487)
!1487 = !DILexicalBlockFile(scope: !1481, file: !1, discriminator: 1)
!1488 = !DILocation(line: 602, column: 8, scope: !1481)
!1489 = !DILocation(line: 602, column: 11, scope: !1481)
!1490 = !DILocation(line: 602, column: 3, scope: !1481)
!1491 = !DILocation(line: 603, column: 2, scope: !1481)
!1492 = !DILocation(line: 604, column: 2, scope: !243)
!1493 = !DILocation(line: 604, column: 5, scope: !243)
!1494 = !DILocation(line: 604, column: 13, scope: !243)
!1495 = !DILocation(line: 604, column: 19, scope: !243)
!1496 = !DILocation(line: 605, column: 19, scope: !243)
!1497 = !DILocation(line: 605, column: 22, scope: !243)
!1498 = !DILocation(line: 605, column: 2, scope: !243)
!1499 = !DILocation(line: 606, column: 7, scope: !243)
!1500 = !DILocation(line: 606, column: 2, scope: !243)
!1501 = !DILocation(line: 607, column: 10, scope: !243)
!1502 = !DILocation(line: 607, column: 2, scope: !243)
!1503 = !DILocation(line: 608, column: 1, scope: !243)
!1504 = !DILocalVariable(name: "_a", arg: 1, scope: !244, file: !1, line: 614, type: !24)
!1505 = !DILocation(line: 614, column: 39, scope: !244)
!1506 = !DILocalVariable(name: "entry", arg: 2, scope: !244, file: !1, line: 614, type: !30)
!1507 = !DILocation(line: 614, column: 65, scope: !244)
!1508 = !DILocalVariable(name: "a", scope: !244, file: !1, line: 616, type: !4)
!1509 = !DILocation(line: 616, column: 24, scope: !244)
!1510 = !DILocation(line: 616, column: 52, scope: !244)
!1511 = !DILocation(line: 616, column: 28, scope: !244)
!1512 = !DILocalVariable(name: "ret", scope: !244, file: !1, line: 617, type: !23)
!1513 = !DILocation(line: 617, column: 6, scope: !244)
!1514 = !DILocalVariable(name: "r2", scope: !244, file: !1, line: 617, type: !23)
!1515 = !DILocation(line: 617, column: 11, scope: !244)
!1516 = !DILocation(line: 619, column: 2, scope: !244)
!1517 = !DILocalVariable(name: "magic_test", scope: !1518, file: !1, line: 619, type: !23)
!1518 = distinct !DILexicalBlock(scope: !244, file: !1, line: 619, column: 2)
!1519 = !DILocation(line: 619, column: 2, scope: !1518)
!1520 = !DILocation(line: 619, column: 2, scope: !1521)
!1521 = !DILexicalBlockFile(scope: !1518, file: !1, discriminator: 1)
!1522 = !DILocation(line: 619, column: 2, scope: !1523)
!1523 = !DILexicalBlockFile(scope: !1524, file: !1, discriminator: 2)
!1524 = distinct !DILexicalBlock(scope: !1518, file: !1, line: 619, column: 2)
!1525 = !DILocation(line: 619, column: 2, scope: !1526)
!1526 = !DILexicalBlockFile(scope: !1518, file: !1, discriminator: 3)
!1527 = !DILocation(line: 621, column: 23, scope: !244)
!1528 = !DILocation(line: 621, column: 26, scope: !244)
!1529 = !DILocation(line: 621, column: 2, scope: !244)
!1530 = !DILocation(line: 623, column: 6, scope: !1531)
!1531 = distinct !DILexicalBlock(scope: !244, file: !1, line: 623, column: 6)
!1532 = !DILocation(line: 623, column: 9, scope: !1531)
!1533 = !DILocation(line: 623, column: 29, scope: !1531)
!1534 = !DILocation(line: 623, column: 6, scope: !244)
!1535 = !DILocation(line: 624, column: 23, scope: !1536)
!1536 = distinct !DILexicalBlock(scope: !1531, file: !1, line: 623, column: 38)
!1537 = !DILocation(line: 624, column: 26, scope: !1536)
!1538 = !DILocation(line: 624, column: 3, scope: !1536)
!1539 = !DILocation(line: 626, column: 3, scope: !1536)
!1540 = !DILocation(line: 626, column: 6, scope: !1536)
!1541 = !DILocation(line: 626, column: 14, scope: !1536)
!1542 = !DILocation(line: 626, column: 20, scope: !1536)
!1543 = !DILocation(line: 627, column: 3, scope: !1536)
!1544 = !DILocation(line: 631, column: 36, scope: !244)
!1545 = !DILocation(line: 631, column: 39, scope: !244)
!1546 = !DILocation(line: 631, column: 8, scope: !244)
!1547 = !DILocation(line: 631, column: 6, scope: !244)
!1548 = !DILocation(line: 632, column: 6, scope: !1549)
!1549 = distinct !DILexicalBlock(scope: !244, file: !1, line: 632, column: 6)
!1550 = !DILocation(line: 632, column: 10, scope: !1549)
!1551 = !DILocation(line: 632, column: 6, scope: !244)
!1552 = !DILocation(line: 633, column: 3, scope: !1553)
!1553 = distinct !DILexicalBlock(scope: !1549, file: !1, line: 632, column: 28)
!1554 = !DILocation(line: 633, column: 6, scope: !1553)
!1555 = !DILocation(line: 633, column: 14, scope: !1553)
!1556 = !DILocation(line: 633, column: 20, scope: !1553)
!1557 = !DILocation(line: 634, column: 3, scope: !1553)
!1558 = !DILocation(line: 636, column: 6, scope: !1559)
!1559 = distinct !DILexicalBlock(scope: !244, file: !1, line: 636, column: 6)
!1560 = !DILocation(line: 636, column: 10, scope: !1559)
!1561 = !DILocation(line: 636, column: 23, scope: !1559)
!1562 = !DILocation(line: 636, column: 26, scope: !1563)
!1563 = !DILexicalBlockFile(scope: !1559, file: !1, discriminator: 1)
!1564 = !DILocation(line: 636, column: 30, scope: !1563)
!1565 = !DILocation(line: 636, column: 6, scope: !1563)
!1566 = !DILocation(line: 637, column: 11, scope: !1559)
!1567 = !DILocation(line: 637, column: 3, scope: !1559)
!1568 = !DILocation(line: 639, column: 6, scope: !1569)
!1569 = distinct !DILexicalBlock(scope: !244, file: !1, line: 639, column: 6)
!1570 = !DILocation(line: 639, column: 9, scope: !1569)
!1571 = !DILocation(line: 639, column: 23, scope: !1569)
!1572 = !DILocation(line: 640, column: 31, scope: !1569)
!1573 = !DILocation(line: 640, column: 6, scope: !1569)
!1574 = !DILocation(line: 640, column: 38, scope: !1569)
!1575 = !DILocation(line: 641, column: 31, scope: !1569)
!1576 = !DILocation(line: 641, column: 6, scope: !1569)
!1577 = !DILocation(line: 641, column: 38, scope: !1569)
!1578 = !DILocation(line: 642, column: 24, scope: !1569)
!1579 = !DILocation(line: 642, column: 6, scope: !1569)
!1580 = !DILocation(line: 642, column: 41, scope: !1569)
!1581 = !DILocation(line: 642, column: 44, scope: !1569)
!1582 = !DILocation(line: 642, column: 31, scope: !1569)
!1583 = !DILocation(line: 642, column: 58, scope: !1569)
!1584 = !DILocation(line: 643, column: 26, scope: !1569)
!1585 = !DILocation(line: 643, column: 6, scope: !1569)
!1586 = !DILocation(line: 643, column: 36, scope: !1569)
!1587 = !DILocation(line: 643, column: 39, scope: !1569)
!1588 = !DILocation(line: 643, column: 33, scope: !1569)
!1589 = !DILocation(line: 639, column: 6, scope: !1590)
!1590 = !DILexicalBlockFile(scope: !244, file: !1, discriminator: 1)
!1591 = !DILocation(line: 644, column: 22, scope: !1592)
!1592 = distinct !DILexicalBlock(scope: !1569, file: !1, line: 643, column: 54)
!1593 = !DILocation(line: 644, column: 25, scope: !1592)
!1594 = !DILocation(line: 644, column: 3, scope: !1592)
!1595 = !DILocation(line: 646, column: 3, scope: !1592)
!1596 = !DILocation(line: 650, column: 9, scope: !244)
!1597 = !DILocation(line: 650, column: 12, scope: !244)
!1598 = !DILocation(line: 650, column: 33, scope: !244)
!1599 = !DILocation(line: 650, column: 36, scope: !244)
!1600 = !DILocation(line: 650, column: 8, scope: !244)
!1601 = !DILocation(line: 650, column: 5, scope: !244)
!1602 = !DILocation(line: 651, column: 6, scope: !1603)
!1603 = distinct !DILexicalBlock(scope: !244, file: !1, line: 651, column: 6)
!1604 = !DILocation(line: 651, column: 9, scope: !1603)
!1605 = !DILocation(line: 651, column: 6, scope: !244)
!1606 = !DILocation(line: 652, column: 3, scope: !1607)
!1607 = distinct !DILexicalBlock(scope: !1603, file: !1, line: 651, column: 28)
!1608 = !DILocation(line: 654, column: 6, scope: !1609)
!1609 = distinct !DILexicalBlock(scope: !244, file: !1, line: 654, column: 6)
!1610 = !DILocation(line: 654, column: 9, scope: !1609)
!1611 = !DILocation(line: 654, column: 6, scope: !244)
!1612 = !DILocation(line: 655, column: 3, scope: !1613)
!1613 = distinct !DILexicalBlock(scope: !1609, file: !1, line: 654, column: 27)
!1614 = !DILocation(line: 655, column: 6, scope: !1613)
!1615 = !DILocation(line: 655, column: 14, scope: !1613)
!1616 = !DILocation(line: 655, column: 20, scope: !1613)
!1617 = !DILocation(line: 656, column: 3, scope: !1613)
!1618 = !DILocation(line: 658, column: 6, scope: !1619)
!1619 = distinct !DILexicalBlock(scope: !244, file: !1, line: 658, column: 6)
!1620 = !DILocation(line: 658, column: 11, scope: !1619)
!1621 = !DILocation(line: 658, column: 9, scope: !1619)
!1622 = !DILocation(line: 658, column: 6, scope: !244)
!1623 = !DILocation(line: 659, column: 9, scope: !1619)
!1624 = !DILocation(line: 659, column: 7, scope: !1619)
!1625 = !DILocation(line: 659, column: 3, scope: !1619)
!1626 = !DILocation(line: 661, column: 2, scope: !244)
!1627 = !DILocation(line: 661, column: 5, scope: !244)
!1628 = !DILocation(line: 661, column: 13, scope: !244)
!1629 = !DILocation(line: 661, column: 19, scope: !244)
!1630 = !DILocation(line: 662, column: 10, scope: !244)
!1631 = !DILocation(line: 662, column: 2, scope: !244)
!1632 = !DILocation(line: 663, column: 1, scope: !244)
!1633 = !DILocalVariable(name: "_a", arg: 1, scope: !245, file: !1, line: 666, type: !24)
!1634 = !DILocation(line: 666, column: 45, scope: !245)
!1635 = !DILocalVariable(name: "a", scope: !245, file: !1, line: 668, type: !4)
!1636 = !DILocation(line: 668, column: 24, scope: !245)
!1637 = !DILocation(line: 668, column: 52, scope: !245)
!1638 = !DILocation(line: 668, column: 28, scope: !245)
!1639 = !DILocalVariable(name: "ret", scope: !245, file: !1, line: 669, type: !23)
!1640 = !DILocation(line: 669, column: 6, scope: !245)
!1641 = !DILocation(line: 671, column: 2, scope: !245)
!1642 = !DILocalVariable(name: "magic_test", scope: !1643, file: !1, line: 671, type: !23)
!1643 = distinct !DILexicalBlock(scope: !245, file: !1, line: 671, column: 2)
!1644 = !DILocation(line: 671, column: 2, scope: !1643)
!1645 = !DILocation(line: 671, column: 2, scope: !1646)
!1646 = !DILexicalBlockFile(scope: !1643, file: !1, discriminator: 1)
!1647 = !DILocation(line: 671, column: 2, scope: !1648)
!1648 = !DILexicalBlockFile(scope: !1649, file: !1, discriminator: 2)
!1649 = distinct !DILexicalBlock(scope: !1643, file: !1, line: 671, column: 2)
!1650 = !DILocation(line: 671, column: 2, scope: !1651)
!1651 = !DILexicalBlockFile(scope: !1643, file: !1, discriminator: 3)
!1652 = !DILocation(line: 674, column: 6, scope: !1653)
!1653 = distinct !DILexicalBlock(scope: !245, file: !1, line: 674, column: 6)
!1654 = !DILocation(line: 674, column: 9, scope: !1653)
!1655 = !DILocation(line: 674, column: 17, scope: !1653)
!1656 = !DILocation(line: 674, column: 23, scope: !1653)
!1657 = !DILocation(line: 675, column: 6, scope: !1653)
!1658 = !DILocation(line: 675, column: 9, scope: !1659)
!1659 = !DILexicalBlockFile(scope: !1653, file: !1, discriminator: 1)
!1660 = !DILocation(line: 675, column: 12, scope: !1659)
!1661 = !DILocation(line: 675, column: 32, scope: !1659)
!1662 = !DILocation(line: 674, column: 6, scope: !1663)
!1663 = !DILexicalBlockFile(scope: !245, file: !1, discriminator: 1)
!1664 = !DILocation(line: 676, column: 10, scope: !1653)
!1665 = !DILocation(line: 676, column: 13, scope: !1653)
!1666 = !DILocation(line: 676, column: 34, scope: !1653)
!1667 = !DILocation(line: 676, column: 9, scope: !1653)
!1668 = !DILocation(line: 676, column: 7, scope: !1653)
!1669 = !DILocation(line: 676, column: 3, scope: !1653)
!1670 = !DILocation(line: 677, column: 2, scope: !245)
!1671 = !DILocation(line: 677, column: 5, scope: !245)
!1672 = !DILocation(line: 677, column: 13, scope: !245)
!1673 = !DILocation(line: 677, column: 19, scope: !245)
!1674 = !DILocation(line: 678, column: 10, scope: !245)
!1675 = !DILocation(line: 678, column: 2, scope: !245)
!1676 = !DILocation(line: 679, column: 1, scope: !245)
!1677 = !DILocalVariable(name: "_a", arg: 1, scope: !246, file: !1, line: 685, type: !24)
!1678 = !DILocation(line: 685, column: 37, scope: !246)
!1679 = !DILocalVariable(name: "buff", arg: 2, scope: !246, file: !1, line: 685, type: !43)
!1680 = !DILocation(line: 685, column: 53, scope: !246)
!1681 = !DILocalVariable(name: "s", arg: 3, scope: !246, file: !1, line: 685, type: !45)
!1682 = !DILocation(line: 685, column: 66, scope: !246)
!1683 = !DILocalVariable(name: "a", scope: !246, file: !1, line: 687, type: !4)
!1684 = !DILocation(line: 687, column: 24, scope: !246)
!1685 = !DILocation(line: 687, column: 52, scope: !246)
!1686 = !DILocation(line: 687, column: 28, scope: !246)
!1687 = !DILocalVariable(name: "max_write", scope: !246, file: !1, line: 688, type: !1688)
!1688 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !45)
!1689 = !DILocation(line: 688, column: 15, scope: !246)
!1690 = !DILocation(line: 690, column: 2, scope: !246)
!1691 = !DILocalVariable(name: "magic_test", scope: !1692, file: !1, line: 690, type: !23)
!1692 = distinct !DILexicalBlock(scope: !246, file: !1, line: 690, column: 2)
!1693 = !DILocation(line: 690, column: 2, scope: !1692)
!1694 = !DILocation(line: 690, column: 2, scope: !1695)
!1695 = !DILexicalBlockFile(scope: !1692, file: !1, discriminator: 1)
!1696 = !DILocation(line: 690, column: 2, scope: !1697)
!1697 = !DILexicalBlockFile(scope: !1698, file: !1, discriminator: 2)
!1698 = distinct !DILexicalBlock(scope: !1692, file: !1, line: 690, column: 2)
!1699 = !DILocation(line: 690, column: 2, scope: !1700)
!1700 = !DILexicalBlockFile(scope: !1692, file: !1, discriminator: 3)
!1701 = !DILocation(line: 693, column: 6, scope: !1702)
!1702 = distinct !DILexicalBlock(scope: !246, file: !1, line: 693, column: 6)
!1703 = !DILocation(line: 693, column: 8, scope: !1702)
!1704 = !DILocation(line: 693, column: 6, scope: !246)
!1705 = !DILocation(line: 694, column: 5, scope: !1702)
!1706 = !DILocation(line: 694, column: 3, scope: !1702)
!1707 = !DILocation(line: 695, column: 23, scope: !246)
!1708 = !DILocation(line: 695, column: 26, scope: !246)
!1709 = !DILocation(line: 695, column: 2, scope: !246)
!1710 = !DILocation(line: 696, column: 11, scope: !246)
!1711 = !DILocation(line: 696, column: 14, scope: !246)
!1712 = !DILocation(line: 696, column: 33, scope: !246)
!1713 = !DILocation(line: 696, column: 36, scope: !246)
!1714 = !DILocation(line: 696, column: 42, scope: !246)
!1715 = !DILocation(line: 696, column: 10, scope: !246)
!1716 = !DILocation(line: 696, column: 2, scope: !246)
!1717 = !DILocation(line: 697, column: 1, scope: !246)
!1718 = !DILocalVariable(name: "_a", arg: 1, scope: !237, file: !1, line: 700, type: !24)
!1719 = !DILocation(line: 700, column: 31, scope: !237)
!1720 = !DILocalVariable(name: "n", arg: 2, scope: !237, file: !1, line: 700, type: !23)
!1721 = !DILocation(line: 700, column: 39, scope: !237)
!1722 = !DILocalVariable(name: "a", scope: !237, file: !1, line: 702, type: !4)
!1723 = !DILocation(line: 702, column: 24, scope: !237)
!1724 = !DILocation(line: 702, column: 52, scope: !237)
!1725 = !DILocation(line: 702, column: 28, scope: !237)
!1726 = !DILocalVariable(name: "f", scope: !237, file: !1, line: 703, type: !137)
!1727 = !DILocation(line: 703, column: 31, scope: !237)
!1728 = !DILocation(line: 703, column: 35, scope: !237)
!1729 = !DILocation(line: 703, column: 38, scope: !237)
!1730 = !DILocation(line: 704, column: 6, scope: !1731)
!1731 = distinct !DILexicalBlock(scope: !237, file: !1, line: 704, column: 6)
!1732 = !DILocation(line: 704, column: 8, scope: !1731)
!1733 = !DILocation(line: 704, column: 6, scope: !237)
!1734 = !DILocation(line: 705, column: 10, scope: !1731)
!1735 = !DILocation(line: 705, column: 13, scope: !1731)
!1736 = !DILocation(line: 705, column: 3, scope: !1731)
!1737 = !DILocation(line: 706, column: 6, scope: !1738)
!1738 = distinct !DILexicalBlock(scope: !237, file: !1, line: 706, column: 6)
!1739 = !DILocation(line: 706, column: 8, scope: !1738)
!1740 = !DILocation(line: 706, column: 6, scope: !237)
!1741 = !DILocation(line: 707, column: 3, scope: !1738)
!1742 = !DILocation(line: 708, column: 2, scope: !237)
!1743 = !DILocation(line: 708, column: 9, scope: !1744)
!1744 = !DILexicalBlockFile(scope: !237, file: !1, discriminator: 1)
!1745 = !DILocation(line: 708, column: 11, scope: !1744)
!1746 = !DILocation(line: 708, column: 15, scope: !1744)
!1747 = !DILocation(line: 708, column: 18, scope: !1748)
!1748 = !DILexicalBlockFile(scope: !237, file: !1, discriminator: 2)
!1749 = !DILocation(line: 708, column: 20, scope: !1748)
!1750 = !DILocation(line: 708, column: 2, scope: !1751)
!1751 = !DILexicalBlockFile(scope: !237, file: !1, discriminator: 3)
!1752 = !DILocation(line: 709, column: 7, scope: !1753)
!1753 = distinct !DILexicalBlock(scope: !237, file: !1, line: 708, column: 29)
!1754 = !DILocation(line: 709, column: 10, scope: !1753)
!1755 = !DILocation(line: 709, column: 5, scope: !1753)
!1756 = !DILocation(line: 710, column: 3, scope: !1753)
!1757 = !DILocation(line: 708, column: 2, scope: !1758)
!1758 = !DILexicalBlockFile(scope: !237, file: !1, discriminator: 4)
!1759 = !DILocation(line: 712, column: 9, scope: !237)
!1760 = !DILocation(line: 712, column: 2, scope: !237)
!1761 = !DILocation(line: 713, column: 1, scope: !237)
