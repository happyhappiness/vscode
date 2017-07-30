; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_bzip2.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.private_data = type { i32, %struct.bz_stream, i64, i8*, i64 }
%struct.bz_stream = type { i8*, i32, i32, i32, i8*, i32, i32, i32, i8*, i8* (i8*, i32, i32)*, void (i8*, i8*)*, i8* }

@.str = private unnamed_addr constant [31 x i8] c"archive_write_add_filter_bzip2\00", align 1
@.str.1 = private unnamed_addr constant [14 x i8] c"Out of memory\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c"bzip2\00", align 1
@.str.3 = private unnamed_addr constant [18 x i8] c"compression-level\00", align 1
@.str.4 = private unnamed_addr constant [43 x i8] c"Can't allocate data for compression buffer\00", align 1
@.str.5 = private unnamed_addr constant [48 x i8] c"Internal error initializing compression library\00", align 1
@.str.6 = private unnamed_addr constant [73 x i8] c"Internal error initializing compression library: invalid setup parameter\00", align 1
@.str.7 = private unnamed_addr constant [63 x i8] c"Internal error initializing compression library: out of memory\00", align 1
@.str.8 = private unnamed_addr constant [70 x i8] c"Internal error initializing compression library: mis-compiled library\00", align 1
@.str.9 = private unnamed_addr constant [55 x i8] c"Bzip2 compression failed; BZ2_bzCompress() returned %d\00", align 1
@.str.10 = private unnamed_addr constant [30 x i8] c"Failed to clean up compressor\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_compression_bzip2(%struct.archive* %a) #0 !dbg !223 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !236, metadata !237), !dbg !238
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !239
  call void @__archive_write_filters_free(%struct.archive* %0), !dbg !240
  %1 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !241
  %call = call i32 @archive_write_add_filter_bzip2(%struct.archive* %1), !dbg !242
  ret i32 %call, !dbg !243
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @__archive_write_filters_free(%struct.archive*) #2

; Function Attrs: nounwind uwtable
define i32 @archive_write_add_filter_bzip2(%struct.archive* %_a) #0 !dbg !224 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %f = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.private_data*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !244, metadata !237), !dbg !245
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !246, metadata !237), !dbg !247
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !248
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !249
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !247
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f, metadata !250, metadata !237), !dbg !251
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !252
  %call = call %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive* %2), !dbg !253
  store %struct.archive_write_filter* %call, %struct.archive_write_filter** %f, align 8, !dbg !251
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !254, metadata !237), !dbg !255
  br label %do.body, !dbg !256

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !257, metadata !237), !dbg !259
  %3 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !260
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %3, i32 0, i32 0, !dbg !260
  %call1 = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1329217314, i32 1, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str, i32 0, i32 0)), !dbg !260
  store i32 %call1, i32* %magic_test, align 4, !dbg !260
  %4 = load i32, i32* %magic_test, align 4, !dbg !260
  %cmp = icmp eq i32 %4, -30, !dbg !260
  br i1 %cmp, label %if.then, label %if.end, !dbg !260

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !262
  br label %return, !dbg !262

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !265

do.end:                                           ; preds = %if.end
  %call2 = call noalias i8* @calloc(i64 1, i64 112) #6, !dbg !267
  %5 = bitcast i8* %call2 to %struct.private_data*, !dbg !267
  store %struct.private_data* %5, %struct.private_data** %data, align 8, !dbg !268
  %6 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !269
  %cmp3 = icmp eq %struct.private_data* %6, null, !dbg !271
  br i1 %cmp3, label %if.then4, label %if.end6, !dbg !272

if.then4:                                         ; preds = %do.end
  %7 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !273
  %archive5 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !275
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive5, i32 12, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.1, i32 0, i32 0)), !dbg !276
  store i32 -30, i32* %retval, align 4, !dbg !277
  br label %return, !dbg !277

if.end6:                                          ; preds = %do.end
  %8 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !278
  %compression_level = getelementptr inbounds %struct.private_data, %struct.private_data* %8, i32 0, i32 0, !dbg !279
  store i32 9, i32* %compression_level, align 8, !dbg !280
  %9 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !281
  %10 = bitcast %struct.private_data* %9 to i8*, !dbg !281
  %11 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !282
  %data7 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %11, i32 0, i32 8, !dbg !283
  store i8* %10, i8** %data7, align 8, !dbg !284
  %12 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !285
  %options = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %12, i32 0, i32 3, !dbg !286
  store i32 (%struct.archive_write_filter*, i8*, i8*)* @archive_compressor_bzip2_options, i32 (%struct.archive_write_filter*, i8*, i8*)** %options, align 8, !dbg !287
  %13 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !288
  %close = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %13, i32 0, i32 6, !dbg !289
  store i32 (%struct.archive_write_filter*)* @archive_compressor_bzip2_close, i32 (%struct.archive_write_filter*)** %close, align 8, !dbg !290
  %14 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !291
  %free = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %14, i32 0, i32 7, !dbg !292
  store i32 (%struct.archive_write_filter*)* @archive_compressor_bzip2_free, i32 (%struct.archive_write_filter*)** %free, align 8, !dbg !293
  %15 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !294
  %open = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %15, i32 0, i32 4, !dbg !295
  store i32 (%struct.archive_write_filter*)* @archive_compressor_bzip2_open, i32 (%struct.archive_write_filter*)** %open, align 8, !dbg !296
  %16 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !297
  %code = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %16, i32 0, i32 10, !dbg !298
  store i32 2, i32* %code, align 8, !dbg !299
  %17 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !300
  %name = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %17, i32 0, i32 9, !dbg !301
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i32 0, i32 0), i8** %name, align 8, !dbg !302
  store i32 0, i32* %retval, align 4, !dbg !303
  br label %return, !dbg !303

return:                                           ; preds = %if.end6, %if.then4, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !304
  ret i32 %18, !dbg !304
}

declare %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive*) #2

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_compressor_bzip2_options(%struct.archive_write_filter* %f, i8* %key, i8* %value) #0 !dbg !225 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %key.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  %data = alloca %struct.private_data*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !305, metadata !237), !dbg !306
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !307, metadata !237), !dbg !308
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !309, metadata !237), !dbg !310
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !311, metadata !237), !dbg !312
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !313
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !314
  %1 = load i8*, i8** %data1, align 8, !dbg !314
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !315
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !312
  %3 = load i8*, i8** %key.addr, align 8, !dbg !316
  %call = call i32 @strcmp(i8* %3, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.3, i32 0, i32 0)) #7, !dbg !318
  %cmp = icmp eq i32 %call, 0, !dbg !319
  br i1 %cmp, label %if.then, label %if.end23, !dbg !320

if.then:                                          ; preds = %entry
  %4 = load i8*, i8** %value.addr, align 8, !dbg !321
  %cmp2 = icmp eq i8* %4, null, !dbg !324
  br i1 %cmp2, label %if.then14, label %lor.lhs.false, !dbg !325

lor.lhs.false:                                    ; preds = %if.then
  %5 = load i8*, i8** %value.addr, align 8, !dbg !326
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 0, !dbg !326
  %6 = load i8, i8* %arrayidx, align 1, !dbg !326
  %conv = sext i8 %6 to i32, !dbg !326
  %cmp3 = icmp sge i32 %conv, 48, !dbg !328
  br i1 %cmp3, label %land.lhs.true, label %if.then14, !dbg !329

land.lhs.true:                                    ; preds = %lor.lhs.false
  %7 = load i8*, i8** %value.addr, align 8, !dbg !330
  %arrayidx5 = getelementptr inbounds i8, i8* %7, i64 0, !dbg !330
  %8 = load i8, i8* %arrayidx5, align 1, !dbg !330
  %conv6 = sext i8 %8 to i32, !dbg !330
  %cmp7 = icmp sle i32 %conv6, 57, !dbg !332
  br i1 %cmp7, label %lor.lhs.false9, label %if.then14, !dbg !333

lor.lhs.false9:                                   ; preds = %land.lhs.true
  %9 = load i8*, i8** %value.addr, align 8, !dbg !334
  %arrayidx10 = getelementptr inbounds i8, i8* %9, i64 1, !dbg !334
  %10 = load i8, i8* %arrayidx10, align 1, !dbg !334
  %conv11 = sext i8 %10 to i32, !dbg !334
  %cmp12 = icmp ne i32 %conv11, 0, !dbg !335
  br i1 %cmp12, label %if.then14, label %if.end, !dbg !336

if.then14:                                        ; preds = %lor.lhs.false9, %land.lhs.true, %lor.lhs.false, %if.then
  store i32 -20, i32* %retval, align 4, !dbg !338
  br label %return, !dbg !338

if.end:                                           ; preds = %lor.lhs.false9
  %11 = load i8*, i8** %value.addr, align 8, !dbg !339
  %arrayidx15 = getelementptr inbounds i8, i8* %11, i64 0, !dbg !339
  %12 = load i8, i8* %arrayidx15, align 1, !dbg !339
  %conv16 = sext i8 %12 to i32, !dbg !339
  %sub = sub nsw i32 %conv16, 48, !dbg !340
  %13 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !341
  %compression_level = getelementptr inbounds %struct.private_data, %struct.private_data* %13, i32 0, i32 0, !dbg !342
  store i32 %sub, i32* %compression_level, align 8, !dbg !343
  %14 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !344
  %compression_level17 = getelementptr inbounds %struct.private_data, %struct.private_data* %14, i32 0, i32 0, !dbg !346
  %15 = load i32, i32* %compression_level17, align 8, !dbg !346
  %cmp18 = icmp slt i32 %15, 1, !dbg !347
  br i1 %cmp18, label %if.then20, label %if.end22, !dbg !348

if.then20:                                        ; preds = %if.end
  %16 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !349
  %compression_level21 = getelementptr inbounds %struct.private_data, %struct.private_data* %16, i32 0, i32 0, !dbg !350
  store i32 1, i32* %compression_level21, align 8, !dbg !351
  br label %if.end22, !dbg !349

if.end22:                                         ; preds = %if.then20, %if.end
  store i32 0, i32* %retval, align 4, !dbg !352
  br label %return, !dbg !352

if.end23:                                         ; preds = %entry
  store i32 -20, i32* %retval, align 4, !dbg !353
  br label %return, !dbg !353

return:                                           ; preds = %if.end23, %if.end22, %if.then14
  %17 = load i32, i32* %retval, align 4, !dbg !354
  ret i32 %17, !dbg !354
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_compressor_bzip2_close(%struct.archive_write_filter* %f) #0 !dbg !231 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.private_data*, align 8
  %ret = alloca i32, align 4
  %r1 = alloca i32, align 4
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !355, metadata !237), !dbg !356
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !357, metadata !237), !dbg !358
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !359
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !360
  %1 = load i8*, i8** %data1, align 8, !dbg !360
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !361
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !358
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !362, metadata !237), !dbg !363
  call void @llvm.dbg.declare(metadata i32* %r1, metadata !364, metadata !237), !dbg !365
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !366
  %4 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !367
  %call = call i32 @drive_compressor(%struct.archive_write_filter* %3, %struct.private_data* %4, i32 1), !dbg !368
  store i32 %call, i32* %ret, align 4, !dbg !369
  %5 = load i32, i32* %ret, align 4, !dbg !370
  %cmp = icmp eq i32 %5, 0, !dbg !372
  br i1 %cmp, label %if.then, label %if.end, !dbg !373

if.then:                                          ; preds = %entry
  %6 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !374
  %next_filter = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %6, i32 0, i32 2, !dbg !376
  %7 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter, align 8, !dbg !376
  %8 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !377
  %compressed = getelementptr inbounds %struct.private_data, %struct.private_data* %8, i32 0, i32 3, !dbg !378
  %9 = load i8*, i8** %compressed, align 8, !dbg !378
  %10 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !379
  %compressed_buffer_size = getelementptr inbounds %struct.private_data, %struct.private_data* %10, i32 0, i32 4, !dbg !380
  %11 = load i64, i64* %compressed_buffer_size, align 8, !dbg !380
  %12 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !381
  %stream = getelementptr inbounds %struct.private_data, %struct.private_data* %12, i32 0, i32 1, !dbg !382
  %avail_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream, i32 0, i32 5, !dbg !383
  %13 = load i32, i32* %avail_out, align 8, !dbg !383
  %conv = zext i32 %13 to i64, !dbg !381
  %sub = sub i64 %11, %conv, !dbg !384
  %call2 = call i32 @__archive_write_filter(%struct.archive_write_filter* %7, i8* %9, i64 %sub), !dbg !385
  store i32 %call2, i32* %ret, align 4, !dbg !386
  br label %if.end, !dbg !387

if.end:                                           ; preds = %if.then, %entry
  %14 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !388
  %stream3 = getelementptr inbounds %struct.private_data, %struct.private_data* %14, i32 0, i32 1, !dbg !389
  %call4 = call i32 @BZ2_bzCompressEnd(%struct.bz_stream* %stream3), !dbg !390
  switch i32 %call4, label %sw.default [
    i32 0, label %sw.bb
  ], !dbg !391

sw.bb:                                            ; preds = %if.end
  br label %sw.epilog, !dbg !392

sw.default:                                       ; preds = %if.end
  %15 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !394
  %archive = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %15, i32 0, i32 1, !dbg !395
  %16 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !395
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %16, i32 22, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.10, i32 0, i32 0)), !dbg !396
  store i32 -30, i32* %ret, align 4, !dbg !397
  br label %sw.epilog, !dbg !398

sw.epilog:                                        ; preds = %sw.default, %sw.bb
  %17 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !399
  %next_filter5 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %17, i32 0, i32 2, !dbg !400
  %18 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter5, align 8, !dbg !400
  %call6 = call i32 @__archive_write_close_filter(%struct.archive_write_filter* %18), !dbg !401
  store i32 %call6, i32* %r1, align 4, !dbg !402
  %19 = load i32, i32* %r1, align 4, !dbg !403
  %20 = load i32, i32* %ret, align 4, !dbg !404
  %cmp7 = icmp slt i32 %19, %20, !dbg !405
  br i1 %cmp7, label %cond.true, label %cond.false, !dbg !403

cond.true:                                        ; preds = %sw.epilog
  %21 = load i32, i32* %r1, align 4, !dbg !406
  br label %cond.end, !dbg !408

cond.false:                                       ; preds = %sw.epilog
  %22 = load i32, i32* %ret, align 4, !dbg !409
  br label %cond.end, !dbg !411

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %21, %cond.true ], [ %22, %cond.false ], !dbg !412
  ret i32 %cond, !dbg !414
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_compressor_bzip2_free(%struct.archive_write_filter* %f) #0 !dbg !232 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.private_data*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !415, metadata !237), !dbg !416
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !417, metadata !237), !dbg !418
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !419
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !420
  %1 = load i8*, i8** %data1, align 8, !dbg !420
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !421
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !418
  %3 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !422
  %compressed = getelementptr inbounds %struct.private_data, %struct.private_data* %3, i32 0, i32 3, !dbg !423
  %4 = load i8*, i8** %compressed, align 8, !dbg !423
  call void @free(i8* %4) #6, !dbg !424
  %5 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !425
  %6 = bitcast %struct.private_data* %5 to i8*, !dbg !425
  call void @free(i8* %6) #6, !dbg !426
  %7 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !427
  %data2 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %7, i32 0, i32 8, !dbg !428
  store i8* null, i8** %data2, align 8, !dbg !429
  ret i32 0, !dbg !430
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_compressor_bzip2_open(%struct.archive_write_filter* %f) #0 !dbg !226 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.private_data*, align 8
  %ret = alloca i32, align 4
  %bs = alloca i64, align 8
  %bpb = alloca i64, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !431, metadata !237), !dbg !432
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !433, metadata !237), !dbg !434
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !435
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !436
  %1 = load i8*, i8** %data1, align 8, !dbg !436
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !437
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !434
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !438, metadata !237), !dbg !439
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !440
  %next_filter = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %3, i32 0, i32 2, !dbg !441
  %4 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter, align 8, !dbg !441
  %call = call i32 @__archive_write_open_filter(%struct.archive_write_filter* %4), !dbg !442
  store i32 %call, i32* %ret, align 4, !dbg !443
  %5 = load i32, i32* %ret, align 4, !dbg !444
  %cmp = icmp ne i32 %5, 0, !dbg !446
  br i1 %cmp, label %if.then, label %if.end, !dbg !447

if.then:                                          ; preds = %entry
  %6 = load i32, i32* %ret, align 4, !dbg !448
  store i32 %6, i32* %retval, align 4, !dbg !449
  br label %return, !dbg !449

if.end:                                           ; preds = %entry
  %7 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !450
  %compressed = getelementptr inbounds %struct.private_data, %struct.private_data* %7, i32 0, i32 3, !dbg !452
  %8 = load i8*, i8** %compressed, align 8, !dbg !452
  %cmp2 = icmp eq i8* %8, null, !dbg !453
  br i1 %cmp2, label %if.then3, label %if.end26, !dbg !454

if.then3:                                         ; preds = %if.end
  call void @llvm.dbg.declare(metadata i64* %bs, metadata !455, metadata !237), !dbg !457
  store i64 65536, i64* %bs, align 8, !dbg !457
  call void @llvm.dbg.declare(metadata i64* %bpb, metadata !458, metadata !237), !dbg !459
  %9 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !460
  %archive = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %9, i32 0, i32 1, !dbg !462
  %10 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !462
  %magic = getelementptr inbounds %struct.archive, %struct.archive* %10, i32 0, i32 0, !dbg !463
  %11 = load i32, i32* %magic, align 8, !dbg !463
  %cmp4 = icmp eq i32 %11, -1329217314, !dbg !464
  br i1 %cmp4, label %if.then5, label %if.end16, !dbg !465

if.then5:                                         ; preds = %if.then3
  %12 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !466
  %archive6 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %12, i32 0, i32 1, !dbg !468
  %13 = load %struct.archive*, %struct.archive** %archive6, align 8, !dbg !468
  %call7 = call i32 @archive_write_get_bytes_per_block(%struct.archive* %13), !dbg !469
  %conv = sext i32 %call7 to i64, !dbg !469
  store i64 %conv, i64* %bpb, align 8, !dbg !470
  %14 = load i64, i64* %bpb, align 8, !dbg !471
  %15 = load i64, i64* %bs, align 8, !dbg !473
  %cmp8 = icmp ugt i64 %14, %15, !dbg !474
  br i1 %cmp8, label %if.then10, label %if.else, !dbg !475

if.then10:                                        ; preds = %if.then5
  %16 = load i64, i64* %bpb, align 8, !dbg !476
  store i64 %16, i64* %bs, align 8, !dbg !477
  br label %if.end15, !dbg !478

if.else:                                          ; preds = %if.then5
  %17 = load i64, i64* %bpb, align 8, !dbg !479
  %cmp11 = icmp ne i64 %17, 0, !dbg !481
  br i1 %cmp11, label %if.then13, label %if.end14, !dbg !482

if.then13:                                        ; preds = %if.else
  %18 = load i64, i64* %bs, align 8, !dbg !483
  %19 = load i64, i64* %bpb, align 8, !dbg !484
  %rem = urem i64 %18, %19, !dbg !485
  %20 = load i64, i64* %bs, align 8, !dbg !486
  %sub = sub i64 %20, %rem, !dbg !486
  store i64 %sub, i64* %bs, align 8, !dbg !486
  br label %if.end14, !dbg !487

if.end14:                                         ; preds = %if.then13, %if.else
  br label %if.end15

if.end15:                                         ; preds = %if.end14, %if.then10
  br label %if.end16, !dbg !488

if.end16:                                         ; preds = %if.end15, %if.then3
  %21 = load i64, i64* %bs, align 8, !dbg !489
  %22 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !490
  %compressed_buffer_size = getelementptr inbounds %struct.private_data, %struct.private_data* %22, i32 0, i32 4, !dbg !491
  store i64 %21, i64* %compressed_buffer_size, align 8, !dbg !492
  %23 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !493
  %compressed_buffer_size17 = getelementptr inbounds %struct.private_data, %struct.private_data* %23, i32 0, i32 4, !dbg !494
  %24 = load i64, i64* %compressed_buffer_size17, align 8, !dbg !494
  %call18 = call noalias i8* @malloc(i64 %24) #6, !dbg !495
  %25 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !496
  %compressed19 = getelementptr inbounds %struct.private_data, %struct.private_data* %25, i32 0, i32 3, !dbg !497
  store i8* %call18, i8** %compressed19, align 8, !dbg !498
  %26 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !499
  %compressed20 = getelementptr inbounds %struct.private_data, %struct.private_data* %26, i32 0, i32 3, !dbg !501
  %27 = load i8*, i8** %compressed20, align 8, !dbg !501
  %cmp21 = icmp eq i8* %27, null, !dbg !502
  br i1 %cmp21, label %if.then23, label %if.end25, !dbg !503

if.then23:                                        ; preds = %if.end16
  %28 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !504
  %archive24 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %28, i32 0, i32 1, !dbg !506
  %29 = load %struct.archive*, %struct.archive** %archive24, align 8, !dbg !506
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %29, i32 12, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.4, i32 0, i32 0)), !dbg !507
  store i32 -30, i32* %retval, align 4, !dbg !508
  br label %return, !dbg !508

if.end25:                                         ; preds = %if.end16
  br label %if.end26, !dbg !509

if.end26:                                         ; preds = %if.end25, %if.end
  %30 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !510
  %stream = getelementptr inbounds %struct.private_data, %struct.private_data* %30, i32 0, i32 1, !dbg !511
  %31 = bitcast %struct.bz_stream* %stream to i8*, !dbg !512
  call void @llvm.memset.p0i8.i64(i8* %31, i8 0, i64 80, i32 8, i1 false), !dbg !512
  %32 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !513
  %compressed27 = getelementptr inbounds %struct.private_data, %struct.private_data* %32, i32 0, i32 3, !dbg !514
  %33 = load i8*, i8** %compressed27, align 8, !dbg !514
  %34 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !515
  %stream28 = getelementptr inbounds %struct.private_data, %struct.private_data* %34, i32 0, i32 1, !dbg !516
  %next_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream28, i32 0, i32 4, !dbg !517
  store i8* %33, i8** %next_out, align 8, !dbg !518
  %35 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !519
  %compressed_buffer_size29 = getelementptr inbounds %struct.private_data, %struct.private_data* %35, i32 0, i32 4, !dbg !520
  %36 = load i64, i64* %compressed_buffer_size29, align 8, !dbg !520
  %conv30 = trunc i64 %36 to i32, !dbg !519
  %37 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !521
  %stream31 = getelementptr inbounds %struct.private_data, %struct.private_data* %37, i32 0, i32 1, !dbg !522
  %avail_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream31, i32 0, i32 5, !dbg !523
  store i32 %conv30, i32* %avail_out, align 8, !dbg !524
  %38 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !525
  %write = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %38, i32 0, i32 5, !dbg !526
  store i32 (%struct.archive_write_filter*, i8*, i64)* @archive_compressor_bzip2_write, i32 (%struct.archive_write_filter*, i8*, i64)** %write, align 8, !dbg !527
  %39 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !528
  %stream32 = getelementptr inbounds %struct.private_data, %struct.private_data* %39, i32 0, i32 1, !dbg !529
  %40 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !530
  %compression_level = getelementptr inbounds %struct.private_data, %struct.private_data* %40, i32 0, i32 0, !dbg !531
  %41 = load i32, i32* %compression_level, align 8, !dbg !531
  %call33 = call i32 @BZ2_bzCompressInit(%struct.bz_stream* %stream32, i32 %41, i32 0, i32 30), !dbg !532
  store i32 %call33, i32* %ret, align 4, !dbg !533
  %42 = load i32, i32* %ret, align 4, !dbg !534
  %cmp34 = icmp eq i32 %42, 0, !dbg !536
  br i1 %cmp34, label %if.then36, label %if.end38, !dbg !537

if.then36:                                        ; preds = %if.end26
  %43 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !538
  %44 = bitcast %struct.private_data* %43 to i8*, !dbg !538
  %45 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !540
  %data37 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %45, i32 0, i32 8, !dbg !541
  store i8* %44, i8** %data37, align 8, !dbg !542
  store i32 0, i32* %retval, align 4, !dbg !543
  br label %return, !dbg !543

if.end38:                                         ; preds = %if.end26
  %46 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !544
  %archive39 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %46, i32 0, i32 1, !dbg !545
  %47 = load %struct.archive*, %struct.archive** %archive39, align 8, !dbg !545
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %47, i32 -1, i8* getelementptr inbounds ([48 x i8], [48 x i8]* @.str.5, i32 0, i32 0)), !dbg !546
  %48 = load i32, i32* %ret, align 4, !dbg !547
  switch i32 %48, label %sw.epilog [
    i32 -2, label %sw.bb
    i32 -3, label %sw.bb41
    i32 -9, label %sw.bb43
  ], !dbg !548

sw.bb:                                            ; preds = %if.end38
  %49 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !549
  %archive40 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %49, i32 0, i32 1, !dbg !551
  %50 = load %struct.archive*, %struct.archive** %archive40, align 8, !dbg !551
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %50, i32 -1, i8* getelementptr inbounds ([73 x i8], [73 x i8]* @.str.6, i32 0, i32 0)), !dbg !552
  br label %sw.epilog, !dbg !553

sw.bb41:                                          ; preds = %if.end38
  %51 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !554
  %archive42 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %51, i32 0, i32 1, !dbg !555
  %52 = load %struct.archive*, %struct.archive** %archive42, align 8, !dbg !555
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %52, i32 12, i8* getelementptr inbounds ([63 x i8], [63 x i8]* @.str.7, i32 0, i32 0)), !dbg !556
  br label %sw.epilog, !dbg !557

sw.bb43:                                          ; preds = %if.end38
  %53 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !558
  %archive44 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %53, i32 0, i32 1, !dbg !559
  %54 = load %struct.archive*, %struct.archive** %archive44, align 8, !dbg !559
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %54, i32 -1, i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.8, i32 0, i32 0)), !dbg !560
  br label %sw.epilog, !dbg !561

sw.epilog:                                        ; preds = %if.end38, %sw.bb43, %sw.bb41, %sw.bb
  store i32 -30, i32* %retval, align 4, !dbg !562
  br label %return, !dbg !562

return:                                           ; preds = %sw.epilog, %if.then36, %if.then23, %if.then
  %55 = load i32, i32* %retval, align 4, !dbg !563
  ret i32 %55, !dbg !563
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

declare i32 @__archive_write_open_filter(%struct.archive_write_filter*) #2

declare i32 @archive_write_get_bytes_per_block(%struct.archive*) #2

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #5

; Function Attrs: nounwind uwtable
define internal i32 @archive_compressor_bzip2_write(%struct.archive_write_filter* %f, i8* %buff, i64 %length) #0 !dbg !227 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %buff.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %data = alloca %struct.private_data*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !564, metadata !237), !dbg !565
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !566, metadata !237), !dbg !567
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !568, metadata !237), !dbg !569
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !570, metadata !237), !dbg !571
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !572
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !573
  %1 = load i8*, i8** %data1, align 8, !dbg !573
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !574
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !571
  %3 = load i64, i64* %length.addr, align 8, !dbg !575
  %4 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !576
  %total_in = getelementptr inbounds %struct.private_data, %struct.private_data* %4, i32 0, i32 2, !dbg !577
  %5 = load i64, i64* %total_in, align 8, !dbg !578
  %add = add i64 %5, %3, !dbg !578
  store i64 %add, i64* %total_in, align 8, !dbg !578
  %6 = load i8*, i8** %buff.addr, align 8, !dbg !579
  %7 = ptrtoint i8* %6 to i64, !dbg !579
  %8 = inttoptr i64 %7 to i8*, !dbg !579
  %9 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !579
  %stream = getelementptr inbounds %struct.private_data, %struct.private_data* %9, i32 0, i32 1, !dbg !579
  %next_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream, i32 0, i32 0, !dbg !579
  store i8* %8, i8** %next_in, align 8, !dbg !579
  %10 = load i64, i64* %length.addr, align 8, !dbg !580
  %conv = trunc i64 %10 to i32, !dbg !580
  %11 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !581
  %stream2 = getelementptr inbounds %struct.private_data, %struct.private_data* %11, i32 0, i32 1, !dbg !582
  %avail_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream2, i32 0, i32 1, !dbg !583
  store i32 %conv, i32* %avail_in, align 8, !dbg !584
  %12 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !585
  %13 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !587
  %call = call i32 @drive_compressor(%struct.archive_write_filter* %12, %struct.private_data* %13, i32 0), !dbg !588
  %tobool = icmp ne i32 %call, 0, !dbg !588
  br i1 %tobool, label %if.then, label %if.end, !dbg !589

if.then:                                          ; preds = %entry
  store i32 -30, i32* %retval, align 4, !dbg !590
  br label %return, !dbg !590

if.end:                                           ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !591
  br label %return, !dbg !591

return:                                           ; preds = %if.end, %if.then
  %14 = load i32, i32* %retval, align 4, !dbg !592
  ret i32 %14, !dbg !592
}

declare i32 @BZ2_bzCompressInit(%struct.bz_stream*, i32, i32, i32) #2

; Function Attrs: nounwind uwtable
define internal i32 @drive_compressor(%struct.archive_write_filter* %f, %struct.private_data* %data, i32 %finishing) #0 !dbg !228 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data.addr = alloca %struct.private_data*, align 8
  %finishing.addr = alloca i32, align 4
  %ret = alloca i32, align 4
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !593, metadata !237), !dbg !594
  store %struct.private_data* %data, %struct.private_data** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.private_data** %data.addr, metadata !595, metadata !237), !dbg !596
  store i32 %finishing, i32* %finishing.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %finishing.addr, metadata !597, metadata !237), !dbg !598
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !599, metadata !237), !dbg !600
  br label %for.cond, !dbg !601

for.cond:                                         ; preds = %sw.epilog, %entry
  %0 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !602
  %stream = getelementptr inbounds %struct.private_data, %struct.private_data* %0, i32 0, i32 1, !dbg !607
  %avail_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream, i32 0, i32 5, !dbg !608
  %1 = load i32, i32* %avail_out, align 8, !dbg !608
  %cmp = icmp eq i32 %1, 0, !dbg !609
  br i1 %cmp, label %if.then, label %if.end8, !dbg !610

if.then:                                          ; preds = %for.cond
  %2 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !611
  %next_filter = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %2, i32 0, i32 2, !dbg !613
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter, align 8, !dbg !613
  %4 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !614
  %compressed = getelementptr inbounds %struct.private_data, %struct.private_data* %4, i32 0, i32 3, !dbg !615
  %5 = load i8*, i8** %compressed, align 8, !dbg !615
  %6 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !616
  %compressed_buffer_size = getelementptr inbounds %struct.private_data, %struct.private_data* %6, i32 0, i32 4, !dbg !617
  %7 = load i64, i64* %compressed_buffer_size, align 8, !dbg !617
  %call = call i32 @__archive_write_filter(%struct.archive_write_filter* %3, i8* %5, i64 %7), !dbg !618
  store i32 %call, i32* %ret, align 4, !dbg !619
  %8 = load i32, i32* %ret, align 4, !dbg !620
  %cmp1 = icmp ne i32 %8, 0, !dbg !622
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !623

if.then2:                                         ; preds = %if.then
  store i32 -30, i32* %retval, align 4, !dbg !624
  br label %return, !dbg !624

if.end:                                           ; preds = %if.then
  %9 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !626
  %compressed3 = getelementptr inbounds %struct.private_data, %struct.private_data* %9, i32 0, i32 3, !dbg !627
  %10 = load i8*, i8** %compressed3, align 8, !dbg !627
  %11 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !628
  %stream4 = getelementptr inbounds %struct.private_data, %struct.private_data* %11, i32 0, i32 1, !dbg !629
  %next_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream4, i32 0, i32 4, !dbg !630
  store i8* %10, i8** %next_out, align 8, !dbg !631
  %12 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !632
  %compressed_buffer_size5 = getelementptr inbounds %struct.private_data, %struct.private_data* %12, i32 0, i32 4, !dbg !633
  %13 = load i64, i64* %compressed_buffer_size5, align 8, !dbg !633
  %conv = trunc i64 %13 to i32, !dbg !632
  %14 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !634
  %stream6 = getelementptr inbounds %struct.private_data, %struct.private_data* %14, i32 0, i32 1, !dbg !635
  %avail_out7 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream6, i32 0, i32 5, !dbg !636
  store i32 %conv, i32* %avail_out7, align 8, !dbg !637
  br label %if.end8, !dbg !638

if.end8:                                          ; preds = %if.end, %for.cond
  %15 = load i32, i32* %finishing.addr, align 4, !dbg !639
  %tobool = icmp ne i32 %15, 0, !dbg !639
  br i1 %tobool, label %if.end13, label %land.lhs.true, !dbg !641

land.lhs.true:                                    ; preds = %if.end8
  %16 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !642
  %stream9 = getelementptr inbounds %struct.private_data, %struct.private_data* %16, i32 0, i32 1, !dbg !644
  %avail_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream9, i32 0, i32 1, !dbg !645
  %17 = load i32, i32* %avail_in, align 8, !dbg !645
  %cmp10 = icmp eq i32 %17, 0, !dbg !646
  br i1 %cmp10, label %if.then12, label %if.end13, !dbg !647

if.then12:                                        ; preds = %land.lhs.true
  store i32 0, i32* %retval, align 4, !dbg !648
  br label %return, !dbg !648

if.end13:                                         ; preds = %land.lhs.true, %if.end8
  %18 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !649
  %stream14 = getelementptr inbounds %struct.private_data, %struct.private_data* %18, i32 0, i32 1, !dbg !650
  %19 = load i32, i32* %finishing.addr, align 4, !dbg !651
  %tobool15 = icmp ne i32 %19, 0, !dbg !651
  %cond = select i1 %tobool15, i32 2, i32 0, !dbg !651
  %call16 = call i32 @BZ2_bzCompress(%struct.bz_stream* %stream14, i32 %cond), !dbg !652
  store i32 %call16, i32* %ret, align 4, !dbg !653
  %20 = load i32, i32* %ret, align 4, !dbg !654
  switch i32 %20, label %sw.default [
    i32 1, label %sw.bb
    i32 3, label %sw.bb25
    i32 4, label %sw.bb26
  ], !dbg !655

sw.bb:                                            ; preds = %if.end13
  %21 = load i32, i32* %finishing.addr, align 4, !dbg !656
  %tobool17 = icmp ne i32 %21, 0, !dbg !656
  br i1 %tobool17, label %if.end24, label %land.lhs.true18, !dbg !659

land.lhs.true18:                                  ; preds = %sw.bb
  %22 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !660
  %stream19 = getelementptr inbounds %struct.private_data, %struct.private_data* %22, i32 0, i32 1, !dbg !662
  %avail_in20 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream19, i32 0, i32 1, !dbg !663
  %23 = load i32, i32* %avail_in20, align 8, !dbg !663
  %cmp21 = icmp eq i32 %23, 0, !dbg !664
  br i1 %cmp21, label %if.then23, label %if.end24, !dbg !665

if.then23:                                        ; preds = %land.lhs.true18
  store i32 0, i32* %retval, align 4, !dbg !666
  br label %return, !dbg !666

if.end24:                                         ; preds = %land.lhs.true18, %sw.bb
  br label %sw.epilog, !dbg !667

sw.bb25:                                          ; preds = %if.end13
  br label %sw.epilog, !dbg !668

sw.bb26:                                          ; preds = %if.end13
  store i32 0, i32* %retval, align 4, !dbg !669
  br label %return, !dbg !669

sw.default:                                       ; preds = %if.end13
  %24 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !670
  %archive = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %24, i32 0, i32 1, !dbg !671
  %25 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !671
  %26 = load i32, i32* %ret, align 4, !dbg !672
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %25, i32 22, i8* getelementptr inbounds ([55 x i8], [55 x i8]* @.str.9, i32 0, i32 0), i32 %26), !dbg !673
  store i32 -30, i32* %retval, align 4, !dbg !674
  br label %return, !dbg !674

sw.epilog:                                        ; preds = %sw.bb25, %if.end24
  br label %for.cond, !dbg !675

return:                                           ; preds = %sw.default, %sw.bb26, %if.then23, %if.then12, %if.then2
  %27 = load i32, i32* %retval, align 4, !dbg !677
  ret i32 %27, !dbg !677
}

declare i32 @__archive_write_filter(%struct.archive_write_filter*, i8*, i64) #2

declare i32 @BZ2_bzCompress(%struct.bz_stream*, i32) #2

declare i32 @BZ2_bzCompressEnd(%struct.bz_stream*) #2

declare i32 @__archive_write_close_filter(%struct.archive_write_filter*) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind }
attributes #7 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!233, !234}
!llvm.ident = !{!235}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !222)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_bzip2.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !123, !191, !95, !221, !43}
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
!191 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !192, size: 64, align: 64)
!192 = !DICompositeType(tag: DW_TAG_structure_type, name: "private_data", file: !1, line: 58, size: 896, align: 64, elements: !193)
!193 = !{!194, !195, !218, !219, !220}
!194 = !DIDerivedType(tag: DW_TAG_member, name: "compression_level", scope: !192, file: !1, line: 59, baseType: !23, size: 32, align: 32)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "stream", scope: !192, file: !1, line: 61, baseType: !196, size: 640, align: 64, offset: 64)
!196 = !DIDerivedType(tag: DW_TAG_typedef, name: "bz_stream", file: !197, line: 66, baseType: !198)
!197 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmbzip2/bzlib.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!198 = !DICompositeType(tag: DW_TAG_structure_type, file: !197, line: 49, size: 640, align: 64, elements: !199)
!199 = !{!200, !201, !202, !203, !204, !205, !206, !207, !208, !209, !213, !217}
!200 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !198, file: !197, line: 50, baseType: !95, size: 64, align: 64)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !198, file: !197, line: 51, baseType: !13, size: 32, align: 32, offset: 64)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "total_in_lo32", scope: !198, file: !197, line: 52, baseType: !13, size: 32, align: 32, offset: 96)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "total_in_hi32", scope: !198, file: !197, line: 53, baseType: !13, size: 32, align: 32, offset: 128)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !198, file: !197, line: 55, baseType: !95, size: 64, align: 64, offset: 192)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !198, file: !197, line: 56, baseType: !13, size: 32, align: 32, offset: 256)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "total_out_lo32", scope: !198, file: !197, line: 57, baseType: !13, size: 32, align: 32, offset: 288)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "total_out_hi32", scope: !198, file: !197, line: 58, baseType: !13, size: 32, align: 32, offset: 320)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !198, file: !197, line: 60, baseType: !123, size: 64, align: 64, offset: 384)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "bzalloc", scope: !198, file: !197, line: 62, baseType: !210, size: 64, align: 64, offset: 448)
!210 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !211, size: 64, align: 64)
!211 = !DISubroutineType(types: !212)
!212 = !{!123, !123, !23, !23}
!213 = !DIDerivedType(tag: DW_TAG_member, name: "bzfree", scope: !198, file: !197, line: 63, baseType: !214, size: 64, align: 64, offset: 512)
!214 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !215, size: 64, align: 64)
!215 = !DISubroutineType(types: !216)
!216 = !{null, !123, !123}
!217 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !198, file: !197, line: 64, baseType: !123, size: 64, align: 64, offset: 576)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !192, file: !1, line: 62, baseType: !52, size: 64, align: 64, offset: 704)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "compressed", scope: !192, file: !1, line: 63, baseType: !95, size: 64, align: 64, offset: 768)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_buffer_size", scope: !192, file: !1, line: 64, baseType: !45, size: 64, align: 64, offset: 832)
!221 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !53, line: 122, baseType: !47)
!222 = !{!223, !224, !225, !226, !227, !228, !231, !232}
!223 = distinct !DISubprogram(name: "archive_write_set_compression_bzip2", scope: !1, file: !1, line: 51, type: !21, isLocal: false, isDefinition: true, scopeLine: 52, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!224 = distinct !DISubprogram(name: "archive_write_add_filter_bzip2", scope: !1, file: !1, line: 82, type: !21, isLocal: false, isDefinition: true, scopeLine: 83, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!225 = distinct !DISubprogram(name: "archive_compressor_bzip2_options", scope: !1, file: !1, line: 125, type: !145, isLocal: true, isDefinition: true, scopeLine: 127, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!226 = distinct !DISubprogram(name: "archive_compressor_bzip2_open", scope: !1, file: !1, line: 165, type: !149, isLocal: true, isDefinition: true, scopeLine: 166, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!227 = distinct !DISubprogram(name: "archive_compressor_bzip2_write", scope: !1, file: !1, line: 241, type: !153, isLocal: true, isDefinition: true, scopeLine: 243, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!228 = distinct !DISubprogram(name: "drive_compressor", scope: !1, file: !1, line: 307, type: !229, isLocal: true, isDefinition: true, scopeLine: 309, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!229 = !DISubroutineType(types: !230)
!230 = !{!23, !137, !191, !23}
!231 = distinct !DISubprogram(name: "archive_compressor_bzip2_close", scope: !1, file: !1, line: 262, type: !149, isLocal: true, isDefinition: true, scopeLine: 263, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!232 = distinct !DISubprogram(name: "archive_compressor_bzip2_free", scope: !1, file: !1, line: 290, type: !149, isLocal: true, isDefinition: true, scopeLine: 291, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!233 = !{i32 2, !"Dwarf Version", i32 4}
!234 = !{i32 2, !"Debug Info Version", i32 3}
!235 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!236 = !DILocalVariable(name: "a", arg: 1, scope: !223, file: !1, line: 51, type: !24)
!237 = !DIExpression()
!238 = !DILocation(line: 51, column: 53, scope: !223)
!239 = !DILocation(line: 53, column: 31, scope: !223)
!240 = !DILocation(line: 53, column: 2, scope: !223)
!241 = !DILocation(line: 54, column: 41, scope: !223)
!242 = !DILocation(line: 54, column: 10, scope: !223)
!243 = !DILocation(line: 54, column: 2, scope: !223)
!244 = !DILocalVariable(name: "_a", arg: 1, scope: !224, file: !1, line: 82, type: !24)
!245 = !DILocation(line: 82, column: 48, scope: !224)
!246 = !DILocalVariable(name: "a", scope: !224, file: !1, line: 84, type: !4)
!247 = !DILocation(line: 84, column: 24, scope: !224)
!248 = !DILocation(line: 84, column: 52, scope: !224)
!249 = !DILocation(line: 84, column: 28, scope: !224)
!250 = !DILocalVariable(name: "f", scope: !224, file: !1, line: 85, type: !137)
!251 = !DILocation(line: 85, column: 31, scope: !224)
!252 = !DILocation(line: 85, column: 67, scope: !224)
!253 = !DILocation(line: 85, column: 35, scope: !224)
!254 = !DILocalVariable(name: "data", scope: !224, file: !1, line: 86, type: !191)
!255 = !DILocation(line: 86, column: 23, scope: !224)
!256 = !DILocation(line: 88, column: 2, scope: !224)
!257 = !DILocalVariable(name: "magic_test", scope: !258, file: !1, line: 88, type: !23)
!258 = distinct !DILexicalBlock(scope: !224, file: !1, line: 88, column: 2)
!259 = !DILocation(line: 88, column: 2, scope: !258)
!260 = !DILocation(line: 88, column: 2, scope: !261)
!261 = !DILexicalBlockFile(scope: !258, file: !1, discriminator: 1)
!262 = !DILocation(line: 88, column: 2, scope: !263)
!263 = !DILexicalBlockFile(scope: !264, file: !1, discriminator: 2)
!264 = distinct !DILexicalBlock(scope: !258, file: !1, line: 88, column: 2)
!265 = !DILocation(line: 88, column: 2, scope: !266)
!266 = !DILexicalBlockFile(scope: !258, file: !1, discriminator: 3)
!267 = !DILocation(line: 91, column: 9, scope: !224)
!268 = !DILocation(line: 91, column: 7, scope: !224)
!269 = !DILocation(line: 92, column: 6, scope: !270)
!270 = distinct !DILexicalBlock(scope: !224, file: !1, line: 92, column: 6)
!271 = !DILocation(line: 92, column: 11, scope: !270)
!272 = !DILocation(line: 92, column: 6, scope: !224)
!273 = !DILocation(line: 93, column: 22, scope: !274)
!274 = distinct !DILexicalBlock(scope: !270, file: !1, line: 92, column: 20)
!275 = !DILocation(line: 93, column: 25, scope: !274)
!276 = !DILocation(line: 93, column: 3, scope: !274)
!277 = !DILocation(line: 94, column: 3, scope: !274)
!278 = !DILocation(line: 96, column: 2, scope: !224)
!279 = !DILocation(line: 96, column: 8, scope: !224)
!280 = !DILocation(line: 96, column: 26, scope: !224)
!281 = !DILocation(line: 98, column: 12, scope: !224)
!282 = !DILocation(line: 98, column: 2, scope: !224)
!283 = !DILocation(line: 98, column: 5, scope: !224)
!284 = !DILocation(line: 98, column: 10, scope: !224)
!285 = !DILocation(line: 99, column: 2, scope: !224)
!286 = !DILocation(line: 99, column: 5, scope: !224)
!287 = !DILocation(line: 99, column: 13, scope: !224)
!288 = !DILocation(line: 100, column: 2, scope: !224)
!289 = !DILocation(line: 100, column: 5, scope: !224)
!290 = !DILocation(line: 100, column: 11, scope: !224)
!291 = !DILocation(line: 101, column: 2, scope: !224)
!292 = !DILocation(line: 101, column: 5, scope: !224)
!293 = !DILocation(line: 101, column: 10, scope: !224)
!294 = !DILocation(line: 102, column: 2, scope: !224)
!295 = !DILocation(line: 102, column: 5, scope: !224)
!296 = !DILocation(line: 102, column: 10, scope: !224)
!297 = !DILocation(line: 103, column: 2, scope: !224)
!298 = !DILocation(line: 103, column: 5, scope: !224)
!299 = !DILocation(line: 103, column: 10, scope: !224)
!300 = !DILocation(line: 104, column: 2, scope: !224)
!301 = !DILocation(line: 104, column: 5, scope: !224)
!302 = !DILocation(line: 104, column: 10, scope: !224)
!303 = !DILocation(line: 106, column: 2, scope: !224)
!304 = !DILocation(line: 119, column: 1, scope: !224)
!305 = !DILocalVariable(name: "f", arg: 1, scope: !225, file: !1, line: 125, type: !137)
!306 = !DILocation(line: 125, column: 63, scope: !225)
!307 = !DILocalVariable(name: "key", arg: 2, scope: !225, file: !1, line: 126, type: !80)
!308 = !DILocation(line: 126, column: 17, scope: !225)
!309 = !DILocalVariable(name: "value", arg: 3, scope: !225, file: !1, line: 126, type: !80)
!310 = !DILocation(line: 126, column: 34, scope: !225)
!311 = !DILocalVariable(name: "data", scope: !225, file: !1, line: 128, type: !191)
!312 = !DILocation(line: 128, column: 23, scope: !225)
!313 = !DILocation(line: 128, column: 53, scope: !225)
!314 = !DILocation(line: 128, column: 56, scope: !225)
!315 = !DILocation(line: 128, column: 30, scope: !225)
!316 = !DILocation(line: 130, column: 13, scope: !317)
!317 = distinct !DILexicalBlock(scope: !225, file: !1, line: 130, column: 6)
!318 = !DILocation(line: 130, column: 6, scope: !317)
!319 = !DILocation(line: 130, column: 39, scope: !317)
!320 = !DILocation(line: 130, column: 6, scope: !225)
!321 = !DILocation(line: 131, column: 7, scope: !322)
!322 = distinct !DILexicalBlock(scope: !323, file: !1, line: 131, column: 7)
!323 = distinct !DILexicalBlock(scope: !317, file: !1, line: 130, column: 45)
!324 = !DILocation(line: 131, column: 13, scope: !322)
!325 = !DILocation(line: 131, column: 21, scope: !322)
!326 = !DILocation(line: 131, column: 26, scope: !327)
!327 = !DILexicalBlockFile(scope: !322, file: !1, discriminator: 1)
!328 = !DILocation(line: 131, column: 35, scope: !327)
!329 = !DILocation(line: 131, column: 42, scope: !327)
!330 = !DILocation(line: 131, column: 45, scope: !331)
!331 = !DILexicalBlockFile(scope: !322, file: !1, discriminator: 2)
!332 = !DILocation(line: 131, column: 54, scope: !331)
!333 = !DILocation(line: 131, column: 62, scope: !331)
!334 = !DILocation(line: 132, column: 7, scope: !322)
!335 = !DILocation(line: 132, column: 16, scope: !322)
!336 = !DILocation(line: 131, column: 7, scope: !337)
!337 = !DILexicalBlockFile(scope: !323, file: !1, discriminator: 3)
!338 = !DILocation(line: 133, column: 4, scope: !322)
!339 = !DILocation(line: 134, column: 29, scope: !323)
!340 = !DILocation(line: 134, column: 38, scope: !323)
!341 = !DILocation(line: 134, column: 3, scope: !323)
!342 = !DILocation(line: 134, column: 9, scope: !323)
!343 = !DILocation(line: 134, column: 27, scope: !323)
!344 = !DILocation(line: 138, column: 7, scope: !345)
!345 = distinct !DILexicalBlock(scope: !323, file: !1, line: 138, column: 7)
!346 = !DILocation(line: 138, column: 13, scope: !345)
!347 = !DILocation(line: 138, column: 31, scope: !345)
!348 = !DILocation(line: 138, column: 7, scope: !323)
!349 = !DILocation(line: 139, column: 4, scope: !345)
!350 = !DILocation(line: 139, column: 10, scope: !345)
!351 = !DILocation(line: 139, column: 28, scope: !345)
!352 = !DILocation(line: 140, column: 3, scope: !323)
!353 = !DILocation(line: 146, column: 2, scope: !225)
!354 = !DILocation(line: 147, column: 1, scope: !225)
!355 = !DILocalVariable(name: "f", arg: 1, scope: !231, file: !1, line: 262, type: !137)
!356 = !DILocation(line: 262, column: 61, scope: !231)
!357 = !DILocalVariable(name: "data", scope: !231, file: !1, line: 264, type: !191)
!358 = !DILocation(line: 264, column: 23, scope: !231)
!359 = !DILocation(line: 264, column: 53, scope: !231)
!360 = !DILocation(line: 264, column: 56, scope: !231)
!361 = !DILocation(line: 264, column: 30, scope: !231)
!362 = !DILocalVariable(name: "ret", scope: !231, file: !1, line: 265, type: !23)
!363 = !DILocation(line: 265, column: 6, scope: !231)
!364 = !DILocalVariable(name: "r1", scope: !231, file: !1, line: 265, type: !23)
!365 = !DILocation(line: 265, column: 11, scope: !231)
!366 = !DILocation(line: 268, column: 25, scope: !231)
!367 = !DILocation(line: 268, column: 28, scope: !231)
!368 = !DILocation(line: 268, column: 8, scope: !231)
!369 = !DILocation(line: 268, column: 6, scope: !231)
!370 = !DILocation(line: 269, column: 6, scope: !371)
!371 = distinct !DILexicalBlock(scope: !231, file: !1, line: 269, column: 6)
!372 = !DILocation(line: 269, column: 10, scope: !371)
!373 = !DILocation(line: 269, column: 6, scope: !231)
!374 = !DILocation(line: 271, column: 32, scope: !375)
!375 = distinct !DILexicalBlock(scope: !371, file: !1, line: 269, column: 25)
!376 = !DILocation(line: 271, column: 35, scope: !375)
!377 = !DILocation(line: 272, column: 7, scope: !375)
!378 = !DILocation(line: 272, column: 13, scope: !375)
!379 = !DILocation(line: 273, column: 7, scope: !375)
!380 = !DILocation(line: 273, column: 13, scope: !375)
!381 = !DILocation(line: 273, column: 38, scope: !375)
!382 = !DILocation(line: 273, column: 44, scope: !375)
!383 = !DILocation(line: 273, column: 51, scope: !375)
!384 = !DILocation(line: 273, column: 36, scope: !375)
!385 = !DILocation(line: 271, column: 9, scope: !375)
!386 = !DILocation(line: 271, column: 7, scope: !375)
!387 = !DILocation(line: 274, column: 2, scope: !375)
!388 = !DILocation(line: 276, column: 30, scope: !231)
!389 = !DILocation(line: 276, column: 36, scope: !231)
!390 = !DILocation(line: 276, column: 10, scope: !231)
!391 = !DILocation(line: 276, column: 2, scope: !231)
!392 = !DILocation(line: 278, column: 3, scope: !393)
!393 = distinct !DILexicalBlock(scope: !231, file: !1, line: 276, column: 46)
!394 = !DILocation(line: 280, column: 21, scope: !393)
!395 = !DILocation(line: 280, column: 24, scope: !393)
!396 = !DILocation(line: 280, column: 3, scope: !393)
!397 = !DILocation(line: 282, column: 7, scope: !393)
!398 = !DILocation(line: 283, column: 2, scope: !393)
!399 = !DILocation(line: 285, column: 36, scope: !231)
!400 = !DILocation(line: 285, column: 39, scope: !231)
!401 = !DILocation(line: 285, column: 7, scope: !231)
!402 = !DILocation(line: 285, column: 5, scope: !231)
!403 = !DILocation(line: 286, column: 10, scope: !231)
!404 = !DILocation(line: 286, column: 15, scope: !231)
!405 = !DILocation(line: 286, column: 13, scope: !231)
!406 = !DILocation(line: 286, column: 21, scope: !407)
!407 = !DILexicalBlockFile(scope: !231, file: !1, discriminator: 1)
!408 = !DILocation(line: 286, column: 10, scope: !407)
!409 = !DILocation(line: 286, column: 26, scope: !410)
!410 = !DILexicalBlockFile(scope: !231, file: !1, discriminator: 2)
!411 = !DILocation(line: 286, column: 10, scope: !410)
!412 = !DILocation(line: 286, column: 10, scope: !413)
!413 = !DILexicalBlockFile(scope: !231, file: !1, discriminator: 3)
!414 = !DILocation(line: 286, column: 2, scope: !413)
!415 = !DILocalVariable(name: "f", arg: 1, scope: !232, file: !1, line: 290, type: !137)
!416 = !DILocation(line: 290, column: 60, scope: !232)
!417 = !DILocalVariable(name: "data", scope: !232, file: !1, line: 292, type: !191)
!418 = !DILocation(line: 292, column: 23, scope: !232)
!419 = !DILocation(line: 292, column: 53, scope: !232)
!420 = !DILocation(line: 292, column: 56, scope: !232)
!421 = !DILocation(line: 292, column: 30, scope: !232)
!422 = !DILocation(line: 293, column: 7, scope: !232)
!423 = !DILocation(line: 293, column: 13, scope: !232)
!424 = !DILocation(line: 293, column: 2, scope: !232)
!425 = !DILocation(line: 294, column: 7, scope: !232)
!426 = !DILocation(line: 294, column: 2, scope: !232)
!427 = !DILocation(line: 295, column: 2, scope: !232)
!428 = !DILocation(line: 295, column: 5, scope: !232)
!429 = !DILocation(line: 295, column: 10, scope: !232)
!430 = !DILocation(line: 296, column: 2, scope: !232)
!431 = !DILocalVariable(name: "f", arg: 1, scope: !226, file: !1, line: 165, type: !137)
!432 = !DILocation(line: 165, column: 60, scope: !226)
!433 = !DILocalVariable(name: "data", scope: !226, file: !1, line: 167, type: !191)
!434 = !DILocation(line: 167, column: 23, scope: !226)
!435 = !DILocation(line: 167, column: 53, scope: !226)
!436 = !DILocation(line: 167, column: 56, scope: !226)
!437 = !DILocation(line: 167, column: 30, scope: !226)
!438 = !DILocalVariable(name: "ret", scope: !226, file: !1, line: 168, type: !23)
!439 = !DILocation(line: 168, column: 6, scope: !226)
!440 = !DILocation(line: 170, column: 36, scope: !226)
!441 = !DILocation(line: 170, column: 39, scope: !226)
!442 = !DILocation(line: 170, column: 8, scope: !226)
!443 = !DILocation(line: 170, column: 6, scope: !226)
!444 = !DILocation(line: 171, column: 6, scope: !445)
!445 = distinct !DILexicalBlock(scope: !226, file: !1, line: 171, column: 6)
!446 = !DILocation(line: 171, column: 10, scope: !445)
!447 = !DILocation(line: 171, column: 6, scope: !226)
!448 = !DILocation(line: 172, column: 11, scope: !445)
!449 = !DILocation(line: 172, column: 3, scope: !445)
!450 = !DILocation(line: 174, column: 6, scope: !451)
!451 = distinct !DILexicalBlock(scope: !226, file: !1, line: 174, column: 6)
!452 = !DILocation(line: 174, column: 12, scope: !451)
!453 = !DILocation(line: 174, column: 23, scope: !451)
!454 = !DILocation(line: 174, column: 6, scope: !226)
!455 = !DILocalVariable(name: "bs", scope: !456, file: !1, line: 175, type: !45)
!456 = distinct !DILexicalBlock(scope: !451, file: !1, line: 174, column: 32)
!457 = !DILocation(line: 175, column: 10, scope: !456)
!458 = !DILocalVariable(name: "bpb", scope: !456, file: !1, line: 175, type: !45)
!459 = !DILocation(line: 175, column: 22, scope: !456)
!460 = !DILocation(line: 176, column: 7, scope: !461)
!461 = distinct !DILexicalBlock(scope: !456, file: !1, line: 176, column: 7)
!462 = !DILocation(line: 176, column: 10, scope: !461)
!463 = !DILocation(line: 176, column: 19, scope: !461)
!464 = !DILocation(line: 176, column: 25, scope: !461)
!465 = !DILocation(line: 176, column: 7, scope: !456)
!466 = !DILocation(line: 179, column: 44, scope: !467)
!467 = distinct !DILexicalBlock(scope: !461, file: !1, line: 176, column: 49)
!468 = !DILocation(line: 179, column: 47, scope: !467)
!469 = !DILocation(line: 179, column: 10, scope: !467)
!470 = !DILocation(line: 179, column: 8, scope: !467)
!471 = !DILocation(line: 180, column: 8, scope: !472)
!472 = distinct !DILexicalBlock(scope: !467, file: !1, line: 180, column: 8)
!473 = !DILocation(line: 180, column: 14, scope: !472)
!474 = !DILocation(line: 180, column: 12, scope: !472)
!475 = !DILocation(line: 180, column: 8, scope: !467)
!476 = !DILocation(line: 181, column: 10, scope: !472)
!477 = !DILocation(line: 181, column: 8, scope: !472)
!478 = !DILocation(line: 181, column: 5, scope: !472)
!479 = !DILocation(line: 182, column: 13, scope: !480)
!480 = distinct !DILexicalBlock(scope: !472, file: !1, line: 182, column: 13)
!481 = !DILocation(line: 182, column: 17, scope: !480)
!482 = !DILocation(line: 182, column: 13, scope: !472)
!483 = !DILocation(line: 183, column: 11, scope: !480)
!484 = !DILocation(line: 183, column: 16, scope: !480)
!485 = !DILocation(line: 183, column: 14, scope: !480)
!486 = !DILocation(line: 183, column: 8, scope: !480)
!487 = !DILocation(line: 183, column: 5, scope: !480)
!488 = !DILocation(line: 184, column: 3, scope: !467)
!489 = !DILocation(line: 185, column: 34, scope: !456)
!490 = !DILocation(line: 185, column: 3, scope: !456)
!491 = !DILocation(line: 185, column: 9, scope: !456)
!492 = !DILocation(line: 185, column: 32, scope: !456)
!493 = !DILocation(line: 187, column: 24, scope: !456)
!494 = !DILocation(line: 187, column: 30, scope: !456)
!495 = !DILocation(line: 187, column: 17, scope: !456)
!496 = !DILocation(line: 186, column: 3, scope: !456)
!497 = !DILocation(line: 186, column: 9, scope: !456)
!498 = !DILocation(line: 187, column: 7, scope: !456)
!499 = !DILocation(line: 188, column: 7, scope: !500)
!500 = distinct !DILexicalBlock(scope: !456, file: !1, line: 188, column: 7)
!501 = !DILocation(line: 188, column: 13, scope: !500)
!502 = !DILocation(line: 188, column: 24, scope: !500)
!503 = !DILocation(line: 188, column: 7, scope: !456)
!504 = !DILocation(line: 189, column: 22, scope: !505)
!505 = distinct !DILexicalBlock(scope: !500, file: !1, line: 188, column: 33)
!506 = !DILocation(line: 189, column: 25, scope: !505)
!507 = !DILocation(line: 189, column: 4, scope: !505)
!508 = !DILocation(line: 191, column: 4, scope: !505)
!509 = !DILocation(line: 193, column: 2, scope: !456)
!510 = !DILocation(line: 195, column: 10, scope: !226)
!511 = !DILocation(line: 195, column: 16, scope: !226)
!512 = !DILocation(line: 195, column: 2, scope: !226)
!513 = !DILocation(line: 196, column: 26, scope: !226)
!514 = !DILocation(line: 196, column: 32, scope: !226)
!515 = !DILocation(line: 196, column: 2, scope: !226)
!516 = !DILocation(line: 196, column: 8, scope: !226)
!517 = !DILocation(line: 196, column: 15, scope: !226)
!518 = !DILocation(line: 196, column: 24, scope: !226)
!519 = !DILocation(line: 197, column: 27, scope: !226)
!520 = !DILocation(line: 197, column: 33, scope: !226)
!521 = !DILocation(line: 197, column: 2, scope: !226)
!522 = !DILocation(line: 197, column: 8, scope: !226)
!523 = !DILocation(line: 197, column: 15, scope: !226)
!524 = !DILocation(line: 197, column: 25, scope: !226)
!525 = !DILocation(line: 198, column: 2, scope: !226)
!526 = !DILocation(line: 198, column: 5, scope: !226)
!527 = !DILocation(line: 198, column: 11, scope: !226)
!528 = !DILocation(line: 201, column: 29, scope: !226)
!529 = !DILocation(line: 201, column: 35, scope: !226)
!530 = !DILocation(line: 202, column: 6, scope: !226)
!531 = !DILocation(line: 202, column: 12, scope: !226)
!532 = !DILocation(line: 201, column: 8, scope: !226)
!533 = !DILocation(line: 201, column: 6, scope: !226)
!534 = !DILocation(line: 203, column: 6, scope: !535)
!535 = distinct !DILexicalBlock(scope: !226, file: !1, line: 203, column: 6)
!536 = !DILocation(line: 203, column: 10, scope: !535)
!537 = !DILocation(line: 203, column: 6, scope: !226)
!538 = !DILocation(line: 204, column: 13, scope: !539)
!539 = distinct !DILexicalBlock(scope: !535, file: !1, line: 203, column: 20)
!540 = !DILocation(line: 204, column: 3, scope: !539)
!541 = !DILocation(line: 204, column: 6, scope: !539)
!542 = !DILocation(line: 204, column: 11, scope: !539)
!543 = !DILocation(line: 205, column: 3, scope: !539)
!544 = !DILocation(line: 209, column: 20, scope: !226)
!545 = !DILocation(line: 209, column: 23, scope: !226)
!546 = !DILocation(line: 209, column: 2, scope: !226)
!547 = !DILocation(line: 213, column: 10, scope: !226)
!548 = !DILocation(line: 213, column: 2, scope: !226)
!549 = !DILocation(line: 215, column: 21, scope: !550)
!550 = distinct !DILexicalBlock(scope: !226, file: !1, line: 213, column: 15)
!551 = !DILocation(line: 215, column: 24, scope: !550)
!552 = !DILocation(line: 215, column: 3, scope: !550)
!553 = !DILocation(line: 218, column: 3, scope: !550)
!554 = !DILocation(line: 220, column: 21, scope: !550)
!555 = !DILocation(line: 220, column: 24, scope: !550)
!556 = !DILocation(line: 220, column: 3, scope: !550)
!557 = !DILocation(line: 223, column: 3, scope: !550)
!558 = !DILocation(line: 225, column: 21, scope: !550)
!559 = !DILocation(line: 225, column: 24, scope: !550)
!560 = !DILocation(line: 225, column: 3, scope: !550)
!561 = !DILocation(line: 228, column: 3, scope: !550)
!562 = !DILocation(line: 231, column: 2, scope: !226)
!563 = !DILocation(line: 233, column: 1, scope: !226)
!564 = !DILocalVariable(name: "f", arg: 1, scope: !227, file: !1, line: 241, type: !137)
!565 = !DILocation(line: 241, column: 61, scope: !227)
!566 = !DILocalVariable(name: "buff", arg: 2, scope: !227, file: !1, line: 242, type: !43)
!567 = !DILocation(line: 242, column: 17, scope: !227)
!568 = !DILocalVariable(name: "length", arg: 3, scope: !227, file: !1, line: 242, type: !45)
!569 = !DILocation(line: 242, column: 30, scope: !227)
!570 = !DILocalVariable(name: "data", scope: !227, file: !1, line: 244, type: !191)
!571 = !DILocation(line: 244, column: 23, scope: !227)
!572 = !DILocation(line: 244, column: 53, scope: !227)
!573 = !DILocation(line: 244, column: 56, scope: !227)
!574 = !DILocation(line: 244, column: 30, scope: !227)
!575 = !DILocation(line: 247, column: 20, scope: !227)
!576 = !DILocation(line: 247, column: 2, scope: !227)
!577 = !DILocation(line: 247, column: 8, scope: !227)
!578 = !DILocation(line: 247, column: 17, scope: !227)
!579 = !DILocation(line: 250, column: 2, scope: !227)
!580 = !DILocation(line: 251, column: 26, scope: !227)
!581 = !DILocation(line: 251, column: 2, scope: !227)
!582 = !DILocation(line: 251, column: 8, scope: !227)
!583 = !DILocation(line: 251, column: 15, scope: !227)
!584 = !DILocation(line: 251, column: 24, scope: !227)
!585 = !DILocation(line: 252, column: 23, scope: !586)
!586 = distinct !DILexicalBlock(scope: !227, file: !1, line: 252, column: 6)
!587 = !DILocation(line: 252, column: 26, scope: !586)
!588 = !DILocation(line: 252, column: 6, scope: !586)
!589 = !DILocation(line: 252, column: 6, scope: !227)
!590 = !DILocation(line: 253, column: 3, scope: !586)
!591 = !DILocation(line: 254, column: 2, scope: !227)
!592 = !DILocation(line: 255, column: 1, scope: !227)
!593 = !DILocalVariable(name: "f", arg: 1, scope: !228, file: !1, line: 307, type: !137)
!594 = !DILocation(line: 307, column: 47, scope: !228)
!595 = !DILocalVariable(name: "data", arg: 2, scope: !228, file: !1, line: 308, type: !191)
!596 = !DILocation(line: 308, column: 26, scope: !228)
!597 = !DILocalVariable(name: "finishing", arg: 3, scope: !228, file: !1, line: 308, type: !23)
!598 = !DILocation(line: 308, column: 36, scope: !228)
!599 = !DILocalVariable(name: "ret", scope: !228, file: !1, line: 310, type: !23)
!600 = !DILocation(line: 310, column: 6, scope: !228)
!601 = !DILocation(line: 312, column: 2, scope: !228)
!602 = !DILocation(line: 313, column: 7, scope: !603)
!603 = distinct !DILexicalBlock(scope: !604, file: !1, line: 313, column: 7)
!604 = distinct !DILexicalBlock(scope: !605, file: !1, line: 312, column: 11)
!605 = distinct !DILexicalBlock(scope: !606, file: !1, line: 312, column: 2)
!606 = distinct !DILexicalBlock(scope: !228, file: !1, line: 312, column: 2)
!607 = !DILocation(line: 313, column: 13, scope: !603)
!608 = !DILocation(line: 313, column: 20, scope: !603)
!609 = !DILocation(line: 313, column: 30, scope: !603)
!610 = !DILocation(line: 313, column: 7, scope: !604)
!611 = !DILocation(line: 314, column: 33, scope: !612)
!612 = distinct !DILexicalBlock(scope: !603, file: !1, line: 313, column: 36)
!613 = !DILocation(line: 314, column: 36, scope: !612)
!614 = !DILocation(line: 315, column: 8, scope: !612)
!615 = !DILocation(line: 315, column: 14, scope: !612)
!616 = !DILocation(line: 316, column: 8, scope: !612)
!617 = !DILocation(line: 316, column: 14, scope: !612)
!618 = !DILocation(line: 314, column: 10, scope: !612)
!619 = !DILocation(line: 314, column: 8, scope: !612)
!620 = !DILocation(line: 317, column: 8, scope: !621)
!621 = distinct !DILexicalBlock(scope: !612, file: !1, line: 317, column: 8)
!622 = !DILocation(line: 317, column: 12, scope: !621)
!623 = !DILocation(line: 317, column: 8, scope: !612)
!624 = !DILocation(line: 319, column: 5, scope: !625)
!625 = distinct !DILexicalBlock(scope: !621, file: !1, line: 317, column: 27)
!626 = !DILocation(line: 321, column: 28, scope: !612)
!627 = !DILocation(line: 321, column: 34, scope: !612)
!628 = !DILocation(line: 321, column: 4, scope: !612)
!629 = !DILocation(line: 321, column: 10, scope: !612)
!630 = !DILocation(line: 321, column: 17, scope: !612)
!631 = !DILocation(line: 321, column: 26, scope: !612)
!632 = !DILocation(line: 322, column: 29, scope: !612)
!633 = !DILocation(line: 322, column: 35, scope: !612)
!634 = !DILocation(line: 322, column: 4, scope: !612)
!635 = !DILocation(line: 322, column: 10, scope: !612)
!636 = !DILocation(line: 322, column: 17, scope: !612)
!637 = !DILocation(line: 322, column: 27, scope: !612)
!638 = !DILocation(line: 323, column: 3, scope: !612)
!639 = !DILocation(line: 326, column: 8, scope: !640)
!640 = distinct !DILexicalBlock(scope: !604, file: !1, line: 326, column: 7)
!641 = !DILocation(line: 326, column: 18, scope: !640)
!642 = !DILocation(line: 326, column: 21, scope: !643)
!643 = !DILexicalBlockFile(scope: !640, file: !1, discriminator: 1)
!644 = !DILocation(line: 326, column: 27, scope: !643)
!645 = !DILocation(line: 326, column: 34, scope: !643)
!646 = !DILocation(line: 326, column: 43, scope: !643)
!647 = !DILocation(line: 326, column: 7, scope: !643)
!648 = !DILocation(line: 327, column: 4, scope: !640)
!649 = !DILocation(line: 329, column: 26, scope: !604)
!650 = !DILocation(line: 329, column: 32, scope: !604)
!651 = !DILocation(line: 330, column: 7, scope: !604)
!652 = !DILocation(line: 329, column: 9, scope: !604)
!653 = !DILocation(line: 329, column: 7, scope: !604)
!654 = !DILocation(line: 332, column: 11, scope: !604)
!655 = !DILocation(line: 332, column: 3, scope: !604)
!656 = !DILocation(line: 336, column: 9, scope: !657)
!657 = distinct !DILexicalBlock(scope: !658, file: !1, line: 336, column: 8)
!658 = distinct !DILexicalBlock(scope: !604, file: !1, line: 332, column: 16)
!659 = !DILocation(line: 336, column: 19, scope: !657)
!660 = !DILocation(line: 336, column: 22, scope: !661)
!661 = !DILexicalBlockFile(scope: !657, file: !1, discriminator: 1)
!662 = !DILocation(line: 336, column: 28, scope: !661)
!663 = !DILocation(line: 336, column: 35, scope: !661)
!664 = !DILocation(line: 336, column: 44, scope: !661)
!665 = !DILocation(line: 336, column: 8, scope: !661)
!666 = !DILocation(line: 337, column: 5, scope: !657)
!667 = !DILocation(line: 338, column: 4, scope: !658)
!668 = !DILocation(line: 340, column: 4, scope: !658)
!669 = !DILocation(line: 343, column: 4, scope: !658)
!670 = !DILocation(line: 346, column: 22, scope: !658)
!671 = !DILocation(line: 346, column: 25, scope: !658)
!672 = !DILocation(line: 350, column: 8, scope: !658)
!673 = !DILocation(line: 346, column: 4, scope: !658)
!674 = !DILocation(line: 351, column: 4, scope: !658)
!675 = !DILocation(line: 312, column: 2, scope: !676)
!676 = !DILexicalBlockFile(scope: !605, file: !1, discriminator: 1)
!677 = !DILocation(line: 354, column: 1, scope: !228)
