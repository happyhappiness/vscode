; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmzlib/deflate.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.config_s = type { i16, i16, i16, i16, i32 (%struct.internal_state*, i32)* }
%struct.internal_state = type { %struct.z_stream_s*, i32, i8*, i64, i8*, i32, i32, %struct.gz_header_s*, i32, i8, i32, i32, i32, i32, i8*, i64, i16*, i16*, i32, i32, i32, i32, i32, i64, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, [573 x %struct.ct_data_s], [61 x %struct.ct_data_s], [39 x %struct.ct_data_s], %struct.tree_desc_s, %struct.tree_desc_s, %struct.tree_desc_s, [16 x i16], [573 x i32], i32, i32, [573 x i8], i8*, i32, i32, i16*, i64, i64, i32, i32, i16, i32 }
%struct.z_stream_s = type { i8*, i32, i64, i8*, i32, i64, i8*, %struct.internal_state*, i8* (i8*, i32, i32)*, void (i8*, i8*)*, i8*, i32, i64, i64 }
%struct.gz_header_s = type { i32, i64, i32, i32, i8*, i32, i32, i8*, i32, i8*, i32, i32, i32 }
%struct.ct_data_s = type { %union.anon, %union.anon.0 }
%union.anon = type { i16 }
%union.anon.0 = type { i16 }
%struct.tree_desc_s = type { %struct.ct_data_s*, i32, %struct.static_tree_desc_s* }
%struct.static_tree_desc_s = type { i32 }

@cm_zlib_deflate_copyright = constant [53 x i8] c" deflate 1.2.3 Copyright 1995-2005 Jean-loup Gailly \00", align 16
@cm_zlib_deflateInit2_.my_version = internal constant [6 x i8] c"1.2.3\00", align 1
@cm_zlib_z_errmsg = external constant [10 x i8*], align 16
@configuration_table = internal constant [10 x %struct.config_s] [%struct.config_s { i16 0, i16 0, i16 0, i16 0, i32 (%struct.internal_state*, i32)* @deflate_stored }, %struct.config_s { i16 4, i16 4, i16 8, i16 4, i32 (%struct.internal_state*, i32)* @deflate_fast }, %struct.config_s { i16 4, i16 5, i16 16, i16 8, i32 (%struct.internal_state*, i32)* @deflate_fast }, %struct.config_s { i16 4, i16 6, i16 32, i16 32, i32 (%struct.internal_state*, i32)* @deflate_fast }, %struct.config_s { i16 4, i16 4, i16 16, i16 16, i32 (%struct.internal_state*, i32)* @deflate_slow }, %struct.config_s { i16 8, i16 16, i16 32, i16 32, i32 (%struct.internal_state*, i32)* @deflate_slow }, %struct.config_s { i16 8, i16 16, i16 128, i16 128, i32 (%struct.internal_state*, i32)* @deflate_slow }, %struct.config_s { i16 8, i16 32, i16 128, i16 256, i32 (%struct.internal_state*, i32)* @deflate_slow }, %struct.config_s { i16 32, i16 128, i16 258, i16 1024, i32 (%struct.internal_state*, i32)* @deflate_slow }, %struct.config_s { i16 32, i16 258, i16 258, i16 4096, i32 (%struct.internal_state*, i32)* @deflate_slow }], align 16
@cm_zlib__length_code = external constant [0 x i8], align 1
@cm_zlib__dist_code = external constant [0 x i8], align 1

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_deflateInit_(%struct.z_stream_s* %strm, i32 %level, i8* %version, i32 %stream_size) #0 !dbg !189 {
entry:
  %strm.addr = alloca %struct.z_stream_s*, align 8
  %level.addr = alloca i32, align 4
  %version.addr = alloca i8*, align 8
  %stream_size.addr = alloca i32, align 4
  store %struct.z_stream_s* %strm, %struct.z_stream_s** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.z_stream_s** %strm.addr, metadata !276, metadata !277), !dbg !278
  store i32 %level, i32* %level.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %level.addr, metadata !279, metadata !277), !dbg !280
  store i8* %version, i8** %version.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %version.addr, metadata !281, metadata !277), !dbg !282
  store i32 %stream_size, i32* %stream_size.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %stream_size.addr, metadata !283, metadata !277), !dbg !284
  %0 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !285
  %1 = load i32, i32* %level.addr, align 4, !dbg !286
  %2 = load i8*, i8** %version.addr, align 8, !dbg !287
  %3 = load i32, i32* %stream_size.addr, align 4, !dbg !288
  %call = call i32 @cm_zlib_deflateInit2_(%struct.z_stream_s* %0, i32 %1, i32 8, i32 15, i32 8, i32 0, i8* %2, i32 %3), !dbg !289
  ret i32 %call, !dbg !290
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_deflateInit2_(%struct.z_stream_s* %strm, i32 %level, i32 %method, i32 %windowBits, i32 %memLevel, i32 %strategy, i8* %version, i32 %stream_size) #0 !dbg !195 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.z_stream_s*, align 8
  %level.addr = alloca i32, align 4
  %method.addr = alloca i32, align 4
  %windowBits.addr = alloca i32, align 4
  %memLevel.addr = alloca i32, align 4
  %strategy.addr = alloca i32, align 4
  %version.addr = alloca i8*, align 8
  %stream_size.addr = alloca i32, align 4
  %s = alloca %struct.internal_state*, align 8
  %wrap = alloca i32, align 4
  %overlay = alloca i16*, align 8
  store %struct.z_stream_s* %strm, %struct.z_stream_s** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.z_stream_s** %strm.addr, metadata !291, metadata !277), !dbg !292
  store i32 %level, i32* %level.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %level.addr, metadata !293, metadata !277), !dbg !294
  store i32 %method, i32* %method.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %method.addr, metadata !295, metadata !277), !dbg !296
  store i32 %windowBits, i32* %windowBits.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %windowBits.addr, metadata !297, metadata !277), !dbg !298
  store i32 %memLevel, i32* %memLevel.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %memLevel.addr, metadata !299, metadata !277), !dbg !300
  store i32 %strategy, i32* %strategy.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %strategy.addr, metadata !301, metadata !277), !dbg !302
  store i8* %version, i8** %version.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %version.addr, metadata !303, metadata !277), !dbg !304
  store i32 %stream_size, i32* %stream_size.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %stream_size.addr, metadata !305, metadata !277), !dbg !306
  call void @llvm.dbg.declare(metadata %struct.internal_state** %s, metadata !307, metadata !277), !dbg !308
  call void @llvm.dbg.declare(metadata i32* %wrap, metadata !309, metadata !277), !dbg !310
  store i32 1, i32* %wrap, align 4, !dbg !310
  call void @llvm.dbg.declare(metadata i16** %overlay, metadata !311, metadata !277), !dbg !312
  %0 = load i8*, i8** %version.addr, align 8, !dbg !313
  %cmp = icmp eq i8* %0, null, !dbg !315
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !316

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8*, i8** %version.addr, align 8, !dbg !317
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 0, !dbg !317
  %2 = load i8, i8* %arrayidx, align 1, !dbg !317
  %conv = sext i8 %2 to i32, !dbg !317
  %3 = load i8, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @cm_zlib_deflateInit2_.my_version, i64 0, i64 0), align 1, !dbg !319
  %conv1 = sext i8 %3 to i32, !dbg !319
  %cmp2 = icmp ne i32 %conv, %conv1, !dbg !320
  br i1 %cmp2, label %if.then, label %lor.lhs.false4, !dbg !321

lor.lhs.false4:                                   ; preds = %lor.lhs.false
  %4 = load i32, i32* %stream_size.addr, align 4, !dbg !322
  %conv5 = sext i32 %4 to i64, !dbg !322
  %cmp6 = icmp ne i64 %conv5, 112, !dbg !323
  br i1 %cmp6, label %if.then, label %if.end, !dbg !324

if.then:                                          ; preds = %lor.lhs.false4, %lor.lhs.false, %entry
  store i32 -6, i32* %retval, align 4, !dbg !326
  br label %return, !dbg !326

if.end:                                           ; preds = %lor.lhs.false4
  %5 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !328
  %cmp8 = icmp eq %struct.z_stream_s* %5, null, !dbg !330
  br i1 %cmp8, label %if.then10, label %if.end11, !dbg !331

if.then10:                                        ; preds = %if.end
  store i32 -2, i32* %retval, align 4, !dbg !332
  br label %return, !dbg !332

if.end11:                                         ; preds = %if.end
  %6 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !334
  %msg = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %6, i32 0, i32 6, !dbg !335
  store i8* null, i8** %msg, align 8, !dbg !336
  %7 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !337
  %zalloc = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %7, i32 0, i32 8, !dbg !339
  %8 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %zalloc, align 8, !dbg !339
  %cmp12 = icmp eq i8* (i8*, i32, i32)* %8, null, !dbg !340
  br i1 %cmp12, label %if.then14, label %if.end16, !dbg !341

if.then14:                                        ; preds = %if.end11
  %9 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !342
  %zalloc15 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %9, i32 0, i32 8, !dbg !344
  store i8* (i8*, i32, i32)* @cm_zlib_zcalloc, i8* (i8*, i32, i32)** %zalloc15, align 8, !dbg !345
  %10 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !346
  %opaque = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %10, i32 0, i32 10, !dbg !347
  store i8* null, i8** %opaque, align 8, !dbg !348
  br label %if.end16, !dbg !349

if.end16:                                         ; preds = %if.then14, %if.end11
  %11 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !350
  %zfree = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %11, i32 0, i32 9, !dbg !352
  %12 = load void (i8*, i8*)*, void (i8*, i8*)** %zfree, align 8, !dbg !352
  %cmp17 = icmp eq void (i8*, i8*)* %12, null, !dbg !353
  br i1 %cmp17, label %if.then19, label %if.end21, !dbg !354

if.then19:                                        ; preds = %if.end16
  %13 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !355
  %zfree20 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %13, i32 0, i32 9, !dbg !357
  store void (i8*, i8*)* @cm_zlib_zcfree, void (i8*, i8*)** %zfree20, align 8, !dbg !358
  br label %if.end21, !dbg !355

if.end21:                                         ; preds = %if.then19, %if.end16
  %14 = load i32, i32* %level.addr, align 4, !dbg !359
  %cmp22 = icmp eq i32 %14, -1, !dbg !361
  br i1 %cmp22, label %if.then24, label %if.end25, !dbg !362

if.then24:                                        ; preds = %if.end21
  store i32 6, i32* %level.addr, align 4, !dbg !363
  br label %if.end25, !dbg !365

if.end25:                                         ; preds = %if.then24, %if.end21
  %15 = load i32, i32* %windowBits.addr, align 4, !dbg !366
  %cmp26 = icmp slt i32 %15, 0, !dbg !368
  br i1 %cmp26, label %if.then28, label %if.else, !dbg !369

if.then28:                                        ; preds = %if.end25
  store i32 0, i32* %wrap, align 4, !dbg !370
  %16 = load i32, i32* %windowBits.addr, align 4, !dbg !372
  %sub = sub nsw i32 0, %16, !dbg !373
  store i32 %sub, i32* %windowBits.addr, align 4, !dbg !374
  br label %if.end34, !dbg !375

if.else:                                          ; preds = %if.end25
  %17 = load i32, i32* %windowBits.addr, align 4, !dbg !376
  %cmp29 = icmp sgt i32 %17, 15, !dbg !378
  br i1 %cmp29, label %if.then31, label %if.end33, !dbg !379

if.then31:                                        ; preds = %if.else
  store i32 2, i32* %wrap, align 4, !dbg !380
  %18 = load i32, i32* %windowBits.addr, align 4, !dbg !382
  %sub32 = sub nsw i32 %18, 16, !dbg !382
  store i32 %sub32, i32* %windowBits.addr, align 4, !dbg !382
  br label %if.end33, !dbg !383

if.end33:                                         ; preds = %if.then31, %if.else
  br label %if.end34

if.end34:                                         ; preds = %if.end33, %if.then28
  %19 = load i32, i32* %memLevel.addr, align 4, !dbg !384
  %cmp35 = icmp slt i32 %19, 1, !dbg !386
  br i1 %cmp35, label %if.then61, label %lor.lhs.false37, !dbg !387

lor.lhs.false37:                                  ; preds = %if.end34
  %20 = load i32, i32* %memLevel.addr, align 4, !dbg !388
  %cmp38 = icmp sgt i32 %20, 9, !dbg !390
  br i1 %cmp38, label %if.then61, label %lor.lhs.false40, !dbg !391

lor.lhs.false40:                                  ; preds = %lor.lhs.false37
  %21 = load i32, i32* %method.addr, align 4, !dbg !392
  %cmp41 = icmp ne i32 %21, 8, !dbg !394
  br i1 %cmp41, label %if.then61, label %lor.lhs.false43, !dbg !395

lor.lhs.false43:                                  ; preds = %lor.lhs.false40
  %22 = load i32, i32* %windowBits.addr, align 4, !dbg !396
  %cmp44 = icmp slt i32 %22, 8, !dbg !397
  br i1 %cmp44, label %if.then61, label %lor.lhs.false46, !dbg !398

lor.lhs.false46:                                  ; preds = %lor.lhs.false43
  %23 = load i32, i32* %windowBits.addr, align 4, !dbg !399
  %cmp47 = icmp sgt i32 %23, 15, !dbg !400
  br i1 %cmp47, label %if.then61, label %lor.lhs.false49, !dbg !401

lor.lhs.false49:                                  ; preds = %lor.lhs.false46
  %24 = load i32, i32* %level.addr, align 4, !dbg !402
  %cmp50 = icmp slt i32 %24, 0, !dbg !403
  br i1 %cmp50, label %if.then61, label %lor.lhs.false52, !dbg !404

lor.lhs.false52:                                  ; preds = %lor.lhs.false49
  %25 = load i32, i32* %level.addr, align 4, !dbg !405
  %cmp53 = icmp sgt i32 %25, 9, !dbg !407
  br i1 %cmp53, label %if.then61, label %lor.lhs.false55, !dbg !408

lor.lhs.false55:                                  ; preds = %lor.lhs.false52
  %26 = load i32, i32* %strategy.addr, align 4, !dbg !409
  %cmp56 = icmp slt i32 %26, 0, !dbg !410
  br i1 %cmp56, label %if.then61, label %lor.lhs.false58, !dbg !411

lor.lhs.false58:                                  ; preds = %lor.lhs.false55
  %27 = load i32, i32* %strategy.addr, align 4, !dbg !412
  %cmp59 = icmp sgt i32 %27, 4, !dbg !413
  br i1 %cmp59, label %if.then61, label %if.end62, !dbg !414

if.then61:                                        ; preds = %lor.lhs.false58, %lor.lhs.false55, %lor.lhs.false52, %lor.lhs.false49, %lor.lhs.false46, %lor.lhs.false43, %lor.lhs.false40, %lor.lhs.false37, %if.end34
  store i32 -2, i32* %retval, align 4, !dbg !416
  br label %return, !dbg !416

if.end62:                                         ; preds = %lor.lhs.false58
  %28 = load i32, i32* %windowBits.addr, align 4, !dbg !418
  %cmp63 = icmp eq i32 %28, 8, !dbg !420
  br i1 %cmp63, label %if.then65, label %if.end66, !dbg !421

if.then65:                                        ; preds = %if.end62
  store i32 9, i32* %windowBits.addr, align 4, !dbg !422
  br label %if.end66, !dbg !424

if.end66:                                         ; preds = %if.then65, %if.end62
  %29 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !425
  %zalloc67 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %29, i32 0, i32 8, !dbg !425
  %30 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %zalloc67, align 8, !dbg !425
  %31 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !425
  %opaque68 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %31, i32 0, i32 10, !dbg !425
  %32 = load i8*, i8** %opaque68, align 8, !dbg !425
  %call = call i8* %30(i8* %32, i32 1, i32 5928), !dbg !425
  %33 = bitcast i8* %call to %struct.internal_state*, !dbg !426
  store %struct.internal_state* %33, %struct.internal_state** %s, align 8, !dbg !427
  %34 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !428
  %cmp69 = icmp eq %struct.internal_state* %34, null, !dbg !430
  br i1 %cmp69, label %if.then71, label %if.end72, !dbg !431

if.then71:                                        ; preds = %if.end66
  store i32 -4, i32* %retval, align 4, !dbg !432
  br label %return, !dbg !432

if.end72:                                         ; preds = %if.end66
  %35 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !434
  %36 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !435
  %state = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %36, i32 0, i32 7, !dbg !436
  store %struct.internal_state* %35, %struct.internal_state** %state, align 8, !dbg !437
  %37 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !438
  %38 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !439
  %strm73 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %38, i32 0, i32 0, !dbg !440
  store %struct.z_stream_s* %37, %struct.z_stream_s** %strm73, align 8, !dbg !441
  %39 = load i32, i32* %wrap, align 4, !dbg !442
  %40 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !443
  %wrap74 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %40, i32 0, i32 6, !dbg !444
  store i32 %39, i32* %wrap74, align 4, !dbg !445
  %41 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !446
  %gzhead = getelementptr inbounds %struct.internal_state, %struct.internal_state* %41, i32 0, i32 7, !dbg !447
  store %struct.gz_header_s* null, %struct.gz_header_s** %gzhead, align 8, !dbg !448
  %42 = load i32, i32* %windowBits.addr, align 4, !dbg !449
  %43 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !450
  %w_bits = getelementptr inbounds %struct.internal_state, %struct.internal_state* %43, i32 0, i32 12, !dbg !451
  store i32 %42, i32* %w_bits, align 8, !dbg !452
  %44 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !453
  %w_bits75 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %44, i32 0, i32 12, !dbg !454
  %45 = load i32, i32* %w_bits75, align 8, !dbg !454
  %shl = shl i32 1, %45, !dbg !455
  %46 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !456
  %w_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %46, i32 0, i32 11, !dbg !457
  store i32 %shl, i32* %w_size, align 4, !dbg !458
  %47 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !459
  %w_size76 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %47, i32 0, i32 11, !dbg !460
  %48 = load i32, i32* %w_size76, align 4, !dbg !460
  %sub77 = sub i32 %48, 1, !dbg !461
  %49 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !462
  %w_mask = getelementptr inbounds %struct.internal_state, %struct.internal_state* %49, i32 0, i32 13, !dbg !463
  store i32 %sub77, i32* %w_mask, align 4, !dbg !464
  %50 = load i32, i32* %memLevel.addr, align 4, !dbg !465
  %add = add nsw i32 %50, 7, !dbg !466
  %51 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !467
  %hash_bits = getelementptr inbounds %struct.internal_state, %struct.internal_state* %51, i32 0, i32 20, !dbg !468
  store i32 %add, i32* %hash_bits, align 8, !dbg !469
  %52 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !470
  %hash_bits78 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %52, i32 0, i32 20, !dbg !471
  %53 = load i32, i32* %hash_bits78, align 8, !dbg !471
  %shl79 = shl i32 1, %53, !dbg !472
  %54 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !473
  %hash_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %54, i32 0, i32 19, !dbg !474
  store i32 %shl79, i32* %hash_size, align 4, !dbg !475
  %55 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !476
  %hash_size80 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %55, i32 0, i32 19, !dbg !477
  %56 = load i32, i32* %hash_size80, align 4, !dbg !477
  %sub81 = sub i32 %56, 1, !dbg !478
  %57 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !479
  %hash_mask = getelementptr inbounds %struct.internal_state, %struct.internal_state* %57, i32 0, i32 21, !dbg !480
  store i32 %sub81, i32* %hash_mask, align 4, !dbg !481
  %58 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !482
  %hash_bits82 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %58, i32 0, i32 20, !dbg !483
  %59 = load i32, i32* %hash_bits82, align 8, !dbg !483
  %add83 = add i32 %59, 3, !dbg !484
  %sub84 = sub i32 %add83, 1, !dbg !485
  %div = udiv i32 %sub84, 3, !dbg !486
  %60 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !487
  %hash_shift = getelementptr inbounds %struct.internal_state, %struct.internal_state* %60, i32 0, i32 22, !dbg !488
  store i32 %div, i32* %hash_shift, align 8, !dbg !489
  %61 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !490
  %zalloc85 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %61, i32 0, i32 8, !dbg !490
  %62 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %zalloc85, align 8, !dbg !490
  %63 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !490
  %opaque86 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %63, i32 0, i32 10, !dbg !490
  %64 = load i8*, i8** %opaque86, align 8, !dbg !490
  %65 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !490
  %w_size87 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %65, i32 0, i32 11, !dbg !490
  %66 = load i32, i32* %w_size87, align 4, !dbg !490
  %call88 = call i8* %62(i8* %64, i32 %66, i32 2), !dbg !490
  %67 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !491
  %window = getelementptr inbounds %struct.internal_state, %struct.internal_state* %67, i32 0, i32 14, !dbg !492
  store i8* %call88, i8** %window, align 8, !dbg !493
  %68 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !494
  %window89 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %68, i32 0, i32 14, !dbg !495
  %69 = load i8*, i8** %window89, align 8, !dbg !495
  %70 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !496
  %w_size90 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %70, i32 0, i32 11, !dbg !497
  %71 = load i32, i32* %w_size90, align 4, !dbg !497
  %mul = mul i32 %71, 2, !dbg !498
  %conv91 = zext i32 %mul to i64, !dbg !496
  %mul92 = mul i64 %conv91, 1, !dbg !499
  call void @llvm.memset.p0i8.i64(i8* %69, i8 0, i64 %mul92, i32 1, i1 false), !dbg !500
  %72 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !501
  %zalloc93 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %72, i32 0, i32 8, !dbg !501
  %73 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %zalloc93, align 8, !dbg !501
  %74 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !501
  %opaque94 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %74, i32 0, i32 10, !dbg !501
  %75 = load i8*, i8** %opaque94, align 8, !dbg !501
  %76 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !501
  %w_size95 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %76, i32 0, i32 11, !dbg !501
  %77 = load i32, i32* %w_size95, align 4, !dbg !501
  %call96 = call i8* %73(i8* %75, i32 %77, i32 2), !dbg !501
  %78 = bitcast i8* %call96 to i16*, !dbg !502
  %79 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !503
  %prev = getelementptr inbounds %struct.internal_state, %struct.internal_state* %79, i32 0, i32 16, !dbg !504
  store i16* %78, i16** %prev, align 8, !dbg !505
  %80 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !506
  %zalloc97 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %80, i32 0, i32 8, !dbg !506
  %81 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %zalloc97, align 8, !dbg !506
  %82 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !506
  %opaque98 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %82, i32 0, i32 10, !dbg !506
  %83 = load i8*, i8** %opaque98, align 8, !dbg !506
  %84 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !506
  %hash_size99 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %84, i32 0, i32 19, !dbg !506
  %85 = load i32, i32* %hash_size99, align 4, !dbg !506
  %call100 = call i8* %81(i8* %83, i32 %85, i32 2), !dbg !506
  %86 = bitcast i8* %call100 to i16*, !dbg !507
  %87 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !508
  %head = getelementptr inbounds %struct.internal_state, %struct.internal_state* %87, i32 0, i32 17, !dbg !509
  store i16* %86, i16** %head, align 8, !dbg !510
  %88 = load i32, i32* %memLevel.addr, align 4, !dbg !511
  %add101 = add nsw i32 %88, 6, !dbg !512
  %shl102 = shl i32 1, %add101, !dbg !513
  %89 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !514
  %lit_bufsize = getelementptr inbounds %struct.internal_state, %struct.internal_state* %89, i32 0, i32 49, !dbg !515
  store i32 %shl102, i32* %lit_bufsize, align 8, !dbg !516
  %90 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !517
  %zalloc103 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %90, i32 0, i32 8, !dbg !517
  %91 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %zalloc103, align 8, !dbg !517
  %92 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !517
  %opaque104 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %92, i32 0, i32 10, !dbg !517
  %93 = load i8*, i8** %opaque104, align 8, !dbg !517
  %94 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !517
  %lit_bufsize105 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %94, i32 0, i32 49, !dbg !517
  %95 = load i32, i32* %lit_bufsize105, align 8, !dbg !517
  %call106 = call i8* %91(i8* %93, i32 %95, i32 4), !dbg !517
  %96 = bitcast i8* %call106 to i16*, !dbg !518
  store i16* %96, i16** %overlay, align 8, !dbg !519
  %97 = load i16*, i16** %overlay, align 8, !dbg !520
  %98 = bitcast i16* %97 to i8*, !dbg !521
  %99 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !522
  %pending_buf = getelementptr inbounds %struct.internal_state, %struct.internal_state* %99, i32 0, i32 2, !dbg !523
  store i8* %98, i8** %pending_buf, align 8, !dbg !524
  %100 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !525
  %lit_bufsize107 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %100, i32 0, i32 49, !dbg !526
  %101 = load i32, i32* %lit_bufsize107, align 8, !dbg !526
  %conv108 = zext i32 %101 to i64, !dbg !527
  %mul109 = mul i64 %conv108, 4, !dbg !528
  %102 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !529
  %pending_buf_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %102, i32 0, i32 3, !dbg !530
  store i64 %mul109, i64* %pending_buf_size, align 8, !dbg !531
  %103 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !532
  %window110 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %103, i32 0, i32 14, !dbg !534
  %104 = load i8*, i8** %window110, align 8, !dbg !534
  %cmp111 = icmp eq i8* %104, null, !dbg !535
  br i1 %cmp111, label %if.then125, label %lor.lhs.false113, !dbg !536

lor.lhs.false113:                                 ; preds = %if.end72
  %105 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !537
  %prev114 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %105, i32 0, i32 16, !dbg !539
  %106 = load i16*, i16** %prev114, align 8, !dbg !539
  %cmp115 = icmp eq i16* %106, null, !dbg !540
  br i1 %cmp115, label %if.then125, label %lor.lhs.false117, !dbg !541

lor.lhs.false117:                                 ; preds = %lor.lhs.false113
  %107 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !542
  %head118 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %107, i32 0, i32 17, !dbg !544
  %108 = load i16*, i16** %head118, align 8, !dbg !544
  %cmp119 = icmp eq i16* %108, null, !dbg !545
  br i1 %cmp119, label %if.then125, label %lor.lhs.false121, !dbg !546

lor.lhs.false121:                                 ; preds = %lor.lhs.false117
  %109 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !547
  %pending_buf122 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %109, i32 0, i32 2, !dbg !548
  %110 = load i8*, i8** %pending_buf122, align 8, !dbg !548
  %cmp123 = icmp eq i8* %110, null, !dbg !549
  br i1 %cmp123, label %if.then125, label %if.end128, !dbg !550

if.then125:                                       ; preds = %lor.lhs.false121, %lor.lhs.false117, %lor.lhs.false113, %if.end72
  %111 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !551
  %status = getelementptr inbounds %struct.internal_state, %struct.internal_state* %111, i32 0, i32 1, !dbg !553
  store i32 666, i32* %status, align 8, !dbg !554
  %112 = load i8*, i8** getelementptr inbounds ([10 x i8*], [10 x i8*]* @cm_zlib_z_errmsg, i64 0, i64 6), align 16, !dbg !555
  %113 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !556
  %msg126 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %113, i32 0, i32 6, !dbg !557
  store i8* %112, i8** %msg126, align 8, !dbg !558
  %114 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !559
  %call127 = call i32 @cm_zlib_deflateEnd(%struct.z_stream_s* %114), !dbg !560
  store i32 -4, i32* %retval, align 4, !dbg !561
  br label %return, !dbg !561

if.end128:                                        ; preds = %lor.lhs.false121
  %115 = load i16*, i16** %overlay, align 8, !dbg !562
  %116 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !563
  %lit_bufsize129 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %116, i32 0, i32 49, !dbg !564
  %117 = load i32, i32* %lit_bufsize129, align 8, !dbg !564
  %conv130 = zext i32 %117 to i64, !dbg !563
  %div131 = udiv i64 %conv130, 2, !dbg !565
  %add.ptr = getelementptr inbounds i16, i16* %115, i64 %div131, !dbg !566
  %118 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !567
  %d_buf = getelementptr inbounds %struct.internal_state, %struct.internal_state* %118, i32 0, i32 51, !dbg !568
  store i16* %add.ptr, i16** %d_buf, align 8, !dbg !569
  %119 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !570
  %pending_buf132 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %119, i32 0, i32 2, !dbg !571
  %120 = load i8*, i8** %pending_buf132, align 8, !dbg !571
  %121 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !572
  %lit_bufsize133 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %121, i32 0, i32 49, !dbg !573
  %122 = load i32, i32* %lit_bufsize133, align 8, !dbg !573
  %conv134 = zext i32 %122 to i64, !dbg !572
  %mul135 = mul i64 3, %conv134, !dbg !574
  %add.ptr136 = getelementptr inbounds i8, i8* %120, i64 %mul135, !dbg !575
  %123 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !576
  %l_buf = getelementptr inbounds %struct.internal_state, %struct.internal_state* %123, i32 0, i32 48, !dbg !577
  store i8* %add.ptr136, i8** %l_buf, align 8, !dbg !578
  %124 = load i32, i32* %level.addr, align 4, !dbg !579
  %125 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !580
  %level137 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %125, i32 0, i32 33, !dbg !581
  store i32 %124, i32* %level137, align 4, !dbg !582
  %126 = load i32, i32* %strategy.addr, align 4, !dbg !583
  %127 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !584
  %strategy138 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %127, i32 0, i32 34, !dbg !585
  store i32 %126, i32* %strategy138, align 8, !dbg !586
  %128 = load i32, i32* %method.addr, align 4, !dbg !587
  %conv139 = trunc i32 %128 to i8, !dbg !588
  %129 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !589
  %method140 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %129, i32 0, i32 9, !dbg !590
  store i8 %conv139, i8* %method140, align 4, !dbg !591
  %130 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !592
  %call141 = call i32 @cm_zlib_deflateReset(%struct.z_stream_s* %130), !dbg !593
  store i32 %call141, i32* %retval, align 4, !dbg !594
  br label %return, !dbg !594

return:                                           ; preds = %if.end128, %if.then125, %if.then71, %if.then61, %if.then10, %if.then
  %131 = load i32, i32* %retval, align 4, !dbg !595
  ret i32 %131, !dbg !595
}

declare i8* @cm_zlib_zcalloc(i8*, i32, i32) #2

declare void @cm_zlib_zcfree(i8*, i8*) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #3

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_deflateEnd(%struct.z_stream_s* %strm) #0 !dbg !222 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.z_stream_s*, align 8
  %status = alloca i32, align 4
  store %struct.z_stream_s* %strm, %struct.z_stream_s** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.z_stream_s** %strm.addr, metadata !596, metadata !277), !dbg !597
  call void @llvm.dbg.declare(metadata i32* %status, metadata !598, metadata !277), !dbg !599
  %0 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !600
  %cmp = icmp eq %struct.z_stream_s* %0, null, !dbg !602
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !603

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !604
  %state = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %1, i32 0, i32 7, !dbg !606
  %2 = load %struct.internal_state*, %struct.internal_state** %state, align 8, !dbg !606
  %cmp1 = icmp eq %struct.internal_state* %2, null, !dbg !607
  br i1 %cmp1, label %if.then, label %if.end, !dbg !608

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -2, i32* %retval, align 4, !dbg !609
  br label %return, !dbg !609

if.end:                                           ; preds = %lor.lhs.false
  %3 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !611
  %state2 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %3, i32 0, i32 7, !dbg !612
  %4 = load %struct.internal_state*, %struct.internal_state** %state2, align 8, !dbg !612
  %status3 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %4, i32 0, i32 1, !dbg !613
  %5 = load i32, i32* %status3, align 8, !dbg !613
  store i32 %5, i32* %status, align 4, !dbg !614
  %6 = load i32, i32* %status, align 4, !dbg !615
  %cmp4 = icmp ne i32 %6, 42, !dbg !617
  br i1 %cmp4, label %land.lhs.true, label %if.end17, !dbg !618

land.lhs.true:                                    ; preds = %if.end
  %7 = load i32, i32* %status, align 4, !dbg !619
  %cmp5 = icmp ne i32 %7, 69, !dbg !620
  br i1 %cmp5, label %land.lhs.true6, label %if.end17, !dbg !621

land.lhs.true6:                                   ; preds = %land.lhs.true
  %8 = load i32, i32* %status, align 4, !dbg !622
  %cmp7 = icmp ne i32 %8, 73, !dbg !623
  br i1 %cmp7, label %land.lhs.true8, label %if.end17, !dbg !624

land.lhs.true8:                                   ; preds = %land.lhs.true6
  %9 = load i32, i32* %status, align 4, !dbg !625
  %cmp9 = icmp ne i32 %9, 91, !dbg !626
  br i1 %cmp9, label %land.lhs.true10, label %if.end17, !dbg !627

land.lhs.true10:                                  ; preds = %land.lhs.true8
  %10 = load i32, i32* %status, align 4, !dbg !628
  %cmp11 = icmp ne i32 %10, 103, !dbg !629
  br i1 %cmp11, label %land.lhs.true12, label %if.end17, !dbg !630

land.lhs.true12:                                  ; preds = %land.lhs.true10
  %11 = load i32, i32* %status, align 4, !dbg !631
  %cmp13 = icmp ne i32 %11, 113, !dbg !632
  br i1 %cmp13, label %land.lhs.true14, label %if.end17, !dbg !633

land.lhs.true14:                                  ; preds = %land.lhs.true12
  %12 = load i32, i32* %status, align 4, !dbg !634
  %cmp15 = icmp ne i32 %12, 666, !dbg !635
  br i1 %cmp15, label %if.then16, label %if.end17, !dbg !636

if.then16:                                        ; preds = %land.lhs.true14
  store i32 -2, i32* %retval, align 4, !dbg !638
  br label %return, !dbg !638

if.end17:                                         ; preds = %land.lhs.true14, %land.lhs.true12, %land.lhs.true10, %land.lhs.true8, %land.lhs.true6, %land.lhs.true, %if.end
  %13 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !640
  %state18 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %13, i32 0, i32 7, !dbg !640
  %14 = load %struct.internal_state*, %struct.internal_state** %state18, align 8, !dbg !640
  %pending_buf = getelementptr inbounds %struct.internal_state, %struct.internal_state* %14, i32 0, i32 2, !dbg !640
  %15 = load i8*, i8** %pending_buf, align 8, !dbg !640
  %tobool = icmp ne i8* %15, null, !dbg !640
  br i1 %tobool, label %if.then19, label %if.end22, !dbg !643

if.then19:                                        ; preds = %if.end17
  %16 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !644
  %zfree = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %16, i32 0, i32 9, !dbg !644
  %17 = load void (i8*, i8*)*, void (i8*, i8*)** %zfree, align 8, !dbg !644
  %18 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !644
  %opaque = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %18, i32 0, i32 10, !dbg !644
  %19 = load i8*, i8** %opaque, align 8, !dbg !644
  %20 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !644
  %state20 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %20, i32 0, i32 7, !dbg !644
  %21 = load %struct.internal_state*, %struct.internal_state** %state20, align 8, !dbg !644
  %pending_buf21 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %21, i32 0, i32 2, !dbg !644
  %22 = load i8*, i8** %pending_buf21, align 8, !dbg !644
  call void %17(i8* %19, i8* %22), !dbg !644
  br label %if.end22, !dbg !644

if.end22:                                         ; preds = %if.then19, %if.end17
  %23 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !646
  %state23 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %23, i32 0, i32 7, !dbg !646
  %24 = load %struct.internal_state*, %struct.internal_state** %state23, align 8, !dbg !646
  %head = getelementptr inbounds %struct.internal_state, %struct.internal_state* %24, i32 0, i32 17, !dbg !646
  %25 = load i16*, i16** %head, align 8, !dbg !646
  %tobool24 = icmp ne i16* %25, null, !dbg !646
  br i1 %tobool24, label %if.then25, label %if.end30, !dbg !649

if.then25:                                        ; preds = %if.end22
  %26 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !650
  %zfree26 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %26, i32 0, i32 9, !dbg !650
  %27 = load void (i8*, i8*)*, void (i8*, i8*)** %zfree26, align 8, !dbg !650
  %28 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !650
  %opaque27 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %28, i32 0, i32 10, !dbg !650
  %29 = load i8*, i8** %opaque27, align 8, !dbg !650
  %30 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !650
  %state28 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %30, i32 0, i32 7, !dbg !650
  %31 = load %struct.internal_state*, %struct.internal_state** %state28, align 8, !dbg !650
  %head29 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %31, i32 0, i32 17, !dbg !650
  %32 = load i16*, i16** %head29, align 8, !dbg !650
  %33 = bitcast i16* %32 to i8*, !dbg !650
  call void %27(i8* %29, i8* %33), !dbg !650
  br label %if.end30, !dbg !650

if.end30:                                         ; preds = %if.then25, %if.end22
  %34 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !652
  %state31 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %34, i32 0, i32 7, !dbg !652
  %35 = load %struct.internal_state*, %struct.internal_state** %state31, align 8, !dbg !652
  %prev = getelementptr inbounds %struct.internal_state, %struct.internal_state* %35, i32 0, i32 16, !dbg !652
  %36 = load i16*, i16** %prev, align 8, !dbg !652
  %tobool32 = icmp ne i16* %36, null, !dbg !652
  br i1 %tobool32, label %if.then33, label %if.end38, !dbg !655

if.then33:                                        ; preds = %if.end30
  %37 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !656
  %zfree34 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %37, i32 0, i32 9, !dbg !656
  %38 = load void (i8*, i8*)*, void (i8*, i8*)** %zfree34, align 8, !dbg !656
  %39 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !656
  %opaque35 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %39, i32 0, i32 10, !dbg !656
  %40 = load i8*, i8** %opaque35, align 8, !dbg !656
  %41 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !656
  %state36 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %41, i32 0, i32 7, !dbg !656
  %42 = load %struct.internal_state*, %struct.internal_state** %state36, align 8, !dbg !656
  %prev37 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %42, i32 0, i32 16, !dbg !656
  %43 = load i16*, i16** %prev37, align 8, !dbg !656
  %44 = bitcast i16* %43 to i8*, !dbg !656
  call void %38(i8* %40, i8* %44), !dbg !656
  br label %if.end38, !dbg !656

if.end38:                                         ; preds = %if.then33, %if.end30
  %45 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !658
  %state39 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %45, i32 0, i32 7, !dbg !658
  %46 = load %struct.internal_state*, %struct.internal_state** %state39, align 8, !dbg !658
  %window = getelementptr inbounds %struct.internal_state, %struct.internal_state* %46, i32 0, i32 14, !dbg !658
  %47 = load i8*, i8** %window, align 8, !dbg !658
  %tobool40 = icmp ne i8* %47, null, !dbg !658
  br i1 %tobool40, label %if.then41, label %if.end46, !dbg !661

if.then41:                                        ; preds = %if.end38
  %48 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !662
  %zfree42 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %48, i32 0, i32 9, !dbg !662
  %49 = load void (i8*, i8*)*, void (i8*, i8*)** %zfree42, align 8, !dbg !662
  %50 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !662
  %opaque43 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %50, i32 0, i32 10, !dbg !662
  %51 = load i8*, i8** %opaque43, align 8, !dbg !662
  %52 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !662
  %state44 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %52, i32 0, i32 7, !dbg !662
  %53 = load %struct.internal_state*, %struct.internal_state** %state44, align 8, !dbg !662
  %window45 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %53, i32 0, i32 14, !dbg !662
  %54 = load i8*, i8** %window45, align 8, !dbg !662
  call void %49(i8* %51, i8* %54), !dbg !662
  br label %if.end46, !dbg !662

if.end46:                                         ; preds = %if.then41, %if.end38
  %55 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !664
  %zfree47 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %55, i32 0, i32 9, !dbg !664
  %56 = load void (i8*, i8*)*, void (i8*, i8*)** %zfree47, align 8, !dbg !664
  %57 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !664
  %opaque48 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %57, i32 0, i32 10, !dbg !664
  %58 = load i8*, i8** %opaque48, align 8, !dbg !664
  %59 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !664
  %state49 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %59, i32 0, i32 7, !dbg !664
  %60 = load %struct.internal_state*, %struct.internal_state** %state49, align 8, !dbg !664
  %61 = bitcast %struct.internal_state* %60 to i8*, !dbg !664
  call void %56(i8* %58, i8* %61), !dbg !664
  %62 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !665
  %state50 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %62, i32 0, i32 7, !dbg !666
  store %struct.internal_state* null, %struct.internal_state** %state50, align 8, !dbg !667
  %63 = load i32, i32* %status, align 4, !dbg !668
  %cmp51 = icmp eq i32 %63, 113, !dbg !669
  %cond = select i1 %cmp51, i32 -3, i32 0, !dbg !668
  store i32 %cond, i32* %retval, align 4, !dbg !670
  br label %return, !dbg !670

return:                                           ; preds = %if.end46, %if.then16, %if.then
  %64 = load i32, i32* %retval, align 4, !dbg !671
  ret i32 %64, !dbg !671
}

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_deflateReset(%struct.z_stream_s* %strm) #0 !dbg !203 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.z_stream_s*, align 8
  %s = alloca %struct.internal_state*, align 8
  store %struct.z_stream_s* %strm, %struct.z_stream_s** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.z_stream_s** %strm.addr, metadata !672, metadata !277), !dbg !673
  call void @llvm.dbg.declare(metadata %struct.internal_state** %s, metadata !674, metadata !277), !dbg !675
  %0 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !676
  %cmp = icmp eq %struct.z_stream_s* %0, null, !dbg !678
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !679

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !680
  %state = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %1, i32 0, i32 7, !dbg !682
  %2 = load %struct.internal_state*, %struct.internal_state** %state, align 8, !dbg !682
  %cmp1 = icmp eq %struct.internal_state* %2, null, !dbg !683
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !684

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %3 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !685
  %zalloc = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %3, i32 0, i32 8, !dbg !686
  %4 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %zalloc, align 8, !dbg !686
  %cmp3 = icmp eq i8* (i8*, i32, i32)* %4, null, !dbg !687
  br i1 %cmp3, label %if.then, label %lor.lhs.false4, !dbg !688

lor.lhs.false4:                                   ; preds = %lor.lhs.false2
  %5 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !689
  %zfree = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %5, i32 0, i32 9, !dbg !690
  %6 = load void (i8*, i8*)*, void (i8*, i8*)** %zfree, align 8, !dbg !690
  %cmp5 = icmp eq void (i8*, i8*)* %6, null, !dbg !691
  br i1 %cmp5, label %if.then, label %if.end, !dbg !692

if.then:                                          ; preds = %lor.lhs.false4, %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 -2, i32* %retval, align 4, !dbg !694
  br label %return, !dbg !694

if.end:                                           ; preds = %lor.lhs.false4
  %7 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !696
  %total_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %7, i32 0, i32 5, !dbg !697
  store i64 0, i64* %total_out, align 8, !dbg !698
  %8 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !699
  %total_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %8, i32 0, i32 2, !dbg !700
  store i64 0, i64* %total_in, align 8, !dbg !701
  %9 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !702
  %msg = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %9, i32 0, i32 6, !dbg !703
  store i8* null, i8** %msg, align 8, !dbg !704
  %10 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !705
  %data_type = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %10, i32 0, i32 11, !dbg !706
  store i32 2, i32* %data_type, align 8, !dbg !707
  %11 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !708
  %state6 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %11, i32 0, i32 7, !dbg !709
  %12 = load %struct.internal_state*, %struct.internal_state** %state6, align 8, !dbg !709
  store %struct.internal_state* %12, %struct.internal_state** %s, align 8, !dbg !710
  %13 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !711
  %pending = getelementptr inbounds %struct.internal_state, %struct.internal_state* %13, i32 0, i32 5, !dbg !712
  store i32 0, i32* %pending, align 8, !dbg !713
  %14 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !714
  %pending_buf = getelementptr inbounds %struct.internal_state, %struct.internal_state* %14, i32 0, i32 2, !dbg !715
  %15 = load i8*, i8** %pending_buf, align 8, !dbg !715
  %16 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !716
  %pending_out = getelementptr inbounds %struct.internal_state, %struct.internal_state* %16, i32 0, i32 4, !dbg !717
  store i8* %15, i8** %pending_out, align 8, !dbg !718
  %17 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !719
  %wrap = getelementptr inbounds %struct.internal_state, %struct.internal_state* %17, i32 0, i32 6, !dbg !721
  %18 = load i32, i32* %wrap, align 4, !dbg !721
  %cmp7 = icmp slt i32 %18, 0, !dbg !722
  br i1 %cmp7, label %if.then8, label %if.end11, !dbg !723

if.then8:                                         ; preds = %if.end
  %19 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !724
  %wrap9 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %19, i32 0, i32 6, !dbg !726
  %20 = load i32, i32* %wrap9, align 4, !dbg !726
  %sub = sub nsw i32 0, %20, !dbg !727
  %21 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !728
  %wrap10 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %21, i32 0, i32 6, !dbg !729
  store i32 %sub, i32* %wrap10, align 4, !dbg !730
  br label %if.end11, !dbg !731

if.end11:                                         ; preds = %if.then8, %if.end
  %22 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !732
  %wrap12 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %22, i32 0, i32 6, !dbg !733
  %23 = load i32, i32* %wrap12, align 4, !dbg !733
  %tobool = icmp ne i32 %23, 0, !dbg !732
  %cond = select i1 %tobool, i32 42, i32 113, !dbg !732
  %24 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !734
  %status = getelementptr inbounds %struct.internal_state, %struct.internal_state* %24, i32 0, i32 1, !dbg !735
  store i32 %cond, i32* %status, align 8, !dbg !736
  %25 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !737
  %wrap13 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %25, i32 0, i32 6, !dbg !738
  %26 = load i32, i32* %wrap13, align 4, !dbg !738
  %cmp14 = icmp eq i32 %26, 2, !dbg !739
  br i1 %cmp14, label %cond.true, label %cond.false, !dbg !737

cond.true:                                        ; preds = %if.end11
  %call = call i64 @cm_zlib_crc32(i64 0, i8* null, i32 0), !dbg !740
  br label %cond.end, !dbg !742

cond.false:                                       ; preds = %if.end11
  %call15 = call i64 @cm_zlib_adler32(i64 0, i8* null, i32 0), !dbg !743
  br label %cond.end, !dbg !744

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond16 = phi i64 [ %call, %cond.true ], [ %call15, %cond.false ], !dbg !745
  %27 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !747
  %adler = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %27, i32 0, i32 12, !dbg !748
  store i64 %cond16, i64* %adler, align 8, !dbg !749
  %28 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !750
  %last_flush = getelementptr inbounds %struct.internal_state, %struct.internal_state* %28, i32 0, i32 10, !dbg !751
  store i32 0, i32* %last_flush, align 8, !dbg !752
  %29 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !753
  call void @cm_zlib__tr_init(%struct.internal_state* %29), !dbg !754
  %30 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !755
  call void @lm_init(%struct.internal_state* %30), !dbg !756
  store i32 0, i32* %retval, align 4, !dbg !757
  br label %return, !dbg !757

return:                                           ; preds = %cond.end, %if.then
  %31 = load i32, i32* %retval, align 4, !dbg !758
  ret i32 %31, !dbg !758
}

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_deflateSetDictionary(%struct.z_stream_s* %strm, i8* %dictionary, i32 %dictLength) #0 !dbg !198 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.z_stream_s*, align 8
  %dictionary.addr = alloca i8*, align 8
  %dictLength.addr = alloca i32, align 4
  %s = alloca %struct.internal_state*, align 8
  %length = alloca i32, align 4
  %n = alloca i32, align 4
  %hash_head = alloca i32, align 4
  store %struct.z_stream_s* %strm, %struct.z_stream_s** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.z_stream_s** %strm.addr, metadata !759, metadata !277), !dbg !760
  store i8* %dictionary, i8** %dictionary.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dictionary.addr, metadata !761, metadata !277), !dbg !762
  store i32 %dictLength, i32* %dictLength.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %dictLength.addr, metadata !763, metadata !277), !dbg !764
  call void @llvm.dbg.declare(metadata %struct.internal_state** %s, metadata !765, metadata !277), !dbg !766
  call void @llvm.dbg.declare(metadata i32* %length, metadata !767, metadata !277), !dbg !768
  %0 = load i32, i32* %dictLength.addr, align 4, !dbg !769
  store i32 %0, i32* %length, align 4, !dbg !768
  call void @llvm.dbg.declare(metadata i32* %n, metadata !770, metadata !277), !dbg !771
  call void @llvm.dbg.declare(metadata i32* %hash_head, metadata !772, metadata !277), !dbg !773
  store i32 0, i32* %hash_head, align 4, !dbg !773
  %1 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !774
  %cmp = icmp eq %struct.z_stream_s* %1, null, !dbg !776
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !777

lor.lhs.false:                                    ; preds = %entry
  %2 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !778
  %state = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %2, i32 0, i32 7, !dbg !780
  %3 = load %struct.internal_state*, %struct.internal_state** %state, align 8, !dbg !780
  %cmp1 = icmp eq %struct.internal_state* %3, null, !dbg !781
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !782

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %4 = load i8*, i8** %dictionary.addr, align 8, !dbg !783
  %cmp3 = icmp eq i8* %4, null, !dbg !785
  br i1 %cmp3, label %if.then, label %lor.lhs.false4, !dbg !786

lor.lhs.false4:                                   ; preds = %lor.lhs.false2
  %5 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !787
  %state5 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %5, i32 0, i32 7, !dbg !788
  %6 = load %struct.internal_state*, %struct.internal_state** %state5, align 8, !dbg !788
  %wrap = getelementptr inbounds %struct.internal_state, %struct.internal_state* %6, i32 0, i32 6, !dbg !789
  %7 = load i32, i32* %wrap, align 4, !dbg !789
  %cmp6 = icmp eq i32 %7, 2, !dbg !790
  br i1 %cmp6, label %if.then, label %lor.lhs.false7, !dbg !791

lor.lhs.false7:                                   ; preds = %lor.lhs.false4
  %8 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !792
  %state8 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %8, i32 0, i32 7, !dbg !793
  %9 = load %struct.internal_state*, %struct.internal_state** %state8, align 8, !dbg !793
  %wrap9 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %9, i32 0, i32 6, !dbg !794
  %10 = load i32, i32* %wrap9, align 4, !dbg !794
  %cmp10 = icmp eq i32 %10, 1, !dbg !795
  br i1 %cmp10, label %land.lhs.true, label %if.end, !dbg !796

land.lhs.true:                                    ; preds = %lor.lhs.false7
  %11 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !797
  %state11 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %11, i32 0, i32 7, !dbg !798
  %12 = load %struct.internal_state*, %struct.internal_state** %state11, align 8, !dbg !798
  %status = getelementptr inbounds %struct.internal_state, %struct.internal_state* %12, i32 0, i32 1, !dbg !799
  %13 = load i32, i32* %status, align 8, !dbg !799
  %cmp12 = icmp ne i32 %13, 42, !dbg !800
  br i1 %cmp12, label %if.then, label %if.end, !dbg !801

if.then:                                          ; preds = %land.lhs.true, %lor.lhs.false4, %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 -2, i32* %retval, align 4, !dbg !803
  br label %return, !dbg !803

if.end:                                           ; preds = %land.lhs.true, %lor.lhs.false7
  %14 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !804
  %state13 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %14, i32 0, i32 7, !dbg !805
  %15 = load %struct.internal_state*, %struct.internal_state** %state13, align 8, !dbg !805
  store %struct.internal_state* %15, %struct.internal_state** %s, align 8, !dbg !806
  %16 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !807
  %wrap14 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %16, i32 0, i32 6, !dbg !809
  %17 = load i32, i32* %wrap14, align 4, !dbg !809
  %tobool = icmp ne i32 %17, 0, !dbg !807
  br i1 %tobool, label %if.then15, label %if.end17, !dbg !810

if.then15:                                        ; preds = %if.end
  %18 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !811
  %adler = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %18, i32 0, i32 12, !dbg !812
  %19 = load i64, i64* %adler, align 8, !dbg !812
  %20 = load i8*, i8** %dictionary.addr, align 8, !dbg !813
  %21 = load i32, i32* %dictLength.addr, align 4, !dbg !814
  %call = call i64 @cm_zlib_adler32(i64 %19, i8* %20, i32 %21), !dbg !815
  %22 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !816
  %adler16 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %22, i32 0, i32 12, !dbg !817
  store i64 %call, i64* %adler16, align 8, !dbg !818
  br label %if.end17, !dbg !816

if.end17:                                         ; preds = %if.then15, %if.end
  %23 = load i32, i32* %length, align 4, !dbg !819
  %cmp18 = icmp ult i32 %23, 3, !dbg !821
  br i1 %cmp18, label %if.then19, label %if.end20, !dbg !822

if.then19:                                        ; preds = %if.end17
  store i32 0, i32* %retval, align 4, !dbg !823
  br label %return, !dbg !823

if.end20:                                         ; preds = %if.end17
  %24 = load i32, i32* %length, align 4, !dbg !825
  %25 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !827
  %w_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %25, i32 0, i32 11, !dbg !827
  %26 = load i32, i32* %w_size, align 4, !dbg !827
  %sub = sub i32 %26, 262, !dbg !827
  %cmp21 = icmp ugt i32 %24, %sub, !dbg !828
  br i1 %cmp21, label %if.then22, label %if.end26, !dbg !829

if.then22:                                        ; preds = %if.end20
  %27 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !830
  %w_size23 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %27, i32 0, i32 11, !dbg !830
  %28 = load i32, i32* %w_size23, align 4, !dbg !830
  %sub24 = sub i32 %28, 262, !dbg !830
  store i32 %sub24, i32* %length, align 4, !dbg !832
  %29 = load i32, i32* %dictLength.addr, align 4, !dbg !833
  %30 = load i32, i32* %length, align 4, !dbg !834
  %sub25 = sub i32 %29, %30, !dbg !835
  %31 = load i8*, i8** %dictionary.addr, align 8, !dbg !836
  %idx.ext = zext i32 %sub25 to i64, !dbg !836
  %add.ptr = getelementptr inbounds i8, i8* %31, i64 %idx.ext, !dbg !836
  store i8* %add.ptr, i8** %dictionary.addr, align 8, !dbg !836
  br label %if.end26, !dbg !837

if.end26:                                         ; preds = %if.then22, %if.end20
  %32 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !838
  %window = getelementptr inbounds %struct.internal_state, %struct.internal_state* %32, i32 0, i32 14, !dbg !839
  %33 = load i8*, i8** %window, align 8, !dbg !839
  %34 = load i8*, i8** %dictionary.addr, align 8, !dbg !840
  %35 = load i32, i32* %length, align 4, !dbg !841
  %conv = zext i32 %35 to i64, !dbg !841
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %33, i8* %34, i64 %conv, i32 1, i1 false), !dbg !842
  %36 = load i32, i32* %length, align 4, !dbg !843
  %37 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !844
  %strstart = getelementptr inbounds %struct.internal_state, %struct.internal_state* %37, i32 0, i32 27, !dbg !845
  store i32 %36, i32* %strstart, align 4, !dbg !846
  %38 = load i32, i32* %length, align 4, !dbg !847
  %conv27 = zext i32 %38 to i64, !dbg !848
  %39 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !849
  %block_start = getelementptr inbounds %struct.internal_state, %struct.internal_state* %39, i32 0, i32 23, !dbg !850
  store i64 %conv27, i64* %block_start, align 8, !dbg !851
  %40 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !852
  %window28 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %40, i32 0, i32 14, !dbg !853
  %41 = load i8*, i8** %window28, align 8, !dbg !853
  %arrayidx = getelementptr inbounds i8, i8* %41, i64 0, !dbg !852
  %42 = load i8, i8* %arrayidx, align 1, !dbg !852
  %conv29 = zext i8 %42 to i32, !dbg !852
  %43 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !854
  %ins_h = getelementptr inbounds %struct.internal_state, %struct.internal_state* %43, i32 0, i32 18, !dbg !855
  store i32 %conv29, i32* %ins_h, align 8, !dbg !856
  %44 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !857
  %ins_h30 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %44, i32 0, i32 18, !dbg !857
  %45 = load i32, i32* %ins_h30, align 8, !dbg !857
  %46 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !857
  %hash_shift = getelementptr inbounds %struct.internal_state, %struct.internal_state* %46, i32 0, i32 22, !dbg !857
  %47 = load i32, i32* %hash_shift, align 8, !dbg !857
  %shl = shl i32 %45, %47, !dbg !857
  %48 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !857
  %window31 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %48, i32 0, i32 14, !dbg !857
  %49 = load i8*, i8** %window31, align 8, !dbg !857
  %arrayidx32 = getelementptr inbounds i8, i8* %49, i64 1, !dbg !857
  %50 = load i8, i8* %arrayidx32, align 1, !dbg !857
  %conv33 = zext i8 %50 to i32, !dbg !857
  %xor = xor i32 %shl, %conv33, !dbg !857
  %51 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !857
  %hash_mask = getelementptr inbounds %struct.internal_state, %struct.internal_state* %51, i32 0, i32 21, !dbg !857
  %52 = load i32, i32* %hash_mask, align 4, !dbg !857
  %and = and i32 %xor, %52, !dbg !857
  %53 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !857
  %ins_h34 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %53, i32 0, i32 18, !dbg !857
  store i32 %and, i32* %ins_h34, align 8, !dbg !857
  store i32 0, i32* %n, align 4, !dbg !858
  br label %for.cond, !dbg !860

for.cond:                                         ; preds = %for.inc, %if.end26
  %54 = load i32, i32* %n, align 4, !dbg !861
  %55 = load i32, i32* %length, align 4, !dbg !864
  %sub35 = sub i32 %55, 3, !dbg !865
  %cmp36 = icmp ule i32 %54, %sub35, !dbg !866
  br i1 %cmp36, label %for.body, label %for.end, !dbg !867

for.body:                                         ; preds = %for.cond
  %56 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !868
  %ins_h38 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %56, i32 0, i32 18, !dbg !868
  %57 = load i32, i32* %ins_h38, align 8, !dbg !868
  %58 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !868
  %hash_shift39 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %58, i32 0, i32 22, !dbg !868
  %59 = load i32, i32* %hash_shift39, align 8, !dbg !868
  %shl40 = shl i32 %57, %59, !dbg !868
  %60 = load i32, i32* %n, align 4, !dbg !868
  %add = add i32 %60, 2, !dbg !868
  %idxprom = zext i32 %add to i64, !dbg !868
  %61 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !868
  %window41 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %61, i32 0, i32 14, !dbg !868
  %62 = load i8*, i8** %window41, align 8, !dbg !868
  %arrayidx42 = getelementptr inbounds i8, i8* %62, i64 %idxprom, !dbg !868
  %63 = load i8, i8* %arrayidx42, align 1, !dbg !868
  %conv43 = zext i8 %63 to i32, !dbg !868
  %xor44 = xor i32 %shl40, %conv43, !dbg !868
  %64 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !868
  %hash_mask45 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %64, i32 0, i32 21, !dbg !868
  %65 = load i32, i32* %hash_mask45, align 4, !dbg !868
  %and46 = and i32 %xor44, %65, !dbg !868
  %66 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !868
  %ins_h47 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %66, i32 0, i32 18, !dbg !868
  store i32 %and46, i32* %ins_h47, align 8, !dbg !868
  %67 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !868
  %ins_h48 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %67, i32 0, i32 18, !dbg !868
  %68 = load i32, i32* %ins_h48, align 8, !dbg !868
  %idxprom49 = zext i32 %68 to i64, !dbg !868
  %69 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !868
  %head = getelementptr inbounds %struct.internal_state, %struct.internal_state* %69, i32 0, i32 17, !dbg !868
  %70 = load i16*, i16** %head, align 8, !dbg !868
  %arrayidx50 = getelementptr inbounds i16, i16* %70, i64 %idxprom49, !dbg !868
  %71 = load i16, i16* %arrayidx50, align 2, !dbg !868
  %72 = load i32, i32* %n, align 4, !dbg !868
  %73 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !868
  %w_mask = getelementptr inbounds %struct.internal_state, %struct.internal_state* %73, i32 0, i32 13, !dbg !868
  %74 = load i32, i32* %w_mask, align 4, !dbg !868
  %and51 = and i32 %72, %74, !dbg !868
  %idxprom52 = zext i32 %and51 to i64, !dbg !868
  %75 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !868
  %prev = getelementptr inbounds %struct.internal_state, %struct.internal_state* %75, i32 0, i32 16, !dbg !868
  %76 = load i16*, i16** %prev, align 8, !dbg !868
  %arrayidx53 = getelementptr inbounds i16, i16* %76, i64 %idxprom52, !dbg !868
  store i16 %71, i16* %arrayidx53, align 2, !dbg !868
  %conv54 = zext i16 %71 to i32, !dbg !868
  store i32 %conv54, i32* %hash_head, align 4, !dbg !868
  %77 = load i32, i32* %n, align 4, !dbg !868
  %conv55 = trunc i32 %77 to i16, !dbg !868
  %78 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !868
  %ins_h56 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %78, i32 0, i32 18, !dbg !868
  %79 = load i32, i32* %ins_h56, align 8, !dbg !868
  %idxprom57 = zext i32 %79 to i64, !dbg !868
  %80 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !868
  %head58 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %80, i32 0, i32 17, !dbg !868
  %81 = load i16*, i16** %head58, align 8, !dbg !868
  %arrayidx59 = getelementptr inbounds i16, i16* %81, i64 %idxprom57, !dbg !868
  store i16 %conv55, i16* %arrayidx59, align 2, !dbg !868
  br label %for.inc, !dbg !870

for.inc:                                          ; preds = %for.body
  %82 = load i32, i32* %n, align 4, !dbg !871
  %inc = add i32 %82, 1, !dbg !871
  store i32 %inc, i32* %n, align 4, !dbg !871
  br label %for.cond, !dbg !873

for.end:                                          ; preds = %for.cond
  %83 = load i32, i32* %hash_head, align 4, !dbg !874
  %tobool60 = icmp ne i32 %83, 0, !dbg !874
  br i1 %tobool60, label %if.then61, label %if.end62, !dbg !876

if.then61:                                        ; preds = %for.end
  store i32 0, i32* %hash_head, align 4, !dbg !877
  br label %if.end62, !dbg !879

if.end62:                                         ; preds = %if.then61, %for.end
  store i32 0, i32* %retval, align 4, !dbg !880
  br label %return, !dbg !880

return:                                           ; preds = %if.end62, %if.then19, %if.then
  %84 = load i32, i32* %retval, align 4, !dbg !881
  ret i32 %84, !dbg !881
}

declare i64 @cm_zlib_adler32(i64, i8*, i32) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

declare i64 @cm_zlib_crc32(i64, i8*, i32) #2

declare void @cm_zlib__tr_init(%struct.internal_state*) #2

; Function Attrs: nounwind uwtable
define internal void @lm_init(%struct.internal_state* %s) #0 !dbg !248 {
entry:
  %s.addr = alloca %struct.internal_state*, align 8
  store %struct.internal_state* %s, %struct.internal_state** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.internal_state** %s.addr, metadata !882, metadata !277), !dbg !883
  %0 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !884
  %w_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %0, i32 0, i32 11, !dbg !885
  %1 = load i32, i32* %w_size, align 4, !dbg !885
  %conv = zext i32 %1 to i64, !dbg !884
  %mul = mul i64 2, %conv, !dbg !886
  %2 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !887
  %window_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %2, i32 0, i32 15, !dbg !888
  store i64 %mul, i64* %window_size, align 8, !dbg !889
  %3 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !890
  %hash_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %3, i32 0, i32 19, !dbg !890
  %4 = load i32, i32* %hash_size, align 4, !dbg !890
  %sub = sub i32 %4, 1, !dbg !890
  %idxprom = zext i32 %sub to i64, !dbg !890
  %5 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !890
  %head = getelementptr inbounds %struct.internal_state, %struct.internal_state* %5, i32 0, i32 17, !dbg !890
  %6 = load i16*, i16** %head, align 8, !dbg !890
  %arrayidx = getelementptr inbounds i16, i16* %6, i64 %idxprom, !dbg !890
  store i16 0, i16* %arrayidx, align 2, !dbg !890
  %7 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !890
  %head1 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %7, i32 0, i32 17, !dbg !890
  %8 = load i16*, i16** %head1, align 8, !dbg !890
  %9 = bitcast i16* %8 to i8*, !dbg !890
  %10 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !890
  %hash_size2 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %10, i32 0, i32 19, !dbg !890
  %11 = load i32, i32* %hash_size2, align 4, !dbg !890
  %sub3 = sub i32 %11, 1, !dbg !890
  %conv4 = zext i32 %sub3 to i64, !dbg !890
  %mul5 = mul i64 %conv4, 2, !dbg !890
  call void @llvm.memset.p0i8.i64(i8* %9, i8 0, i64 %mul5, i32 1, i1 false), !dbg !890
  %12 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !891
  %level = getelementptr inbounds %struct.internal_state, %struct.internal_state* %12, i32 0, i32 33, !dbg !892
  %13 = load i32, i32* %level, align 4, !dbg !892
  %idxprom6 = sext i32 %13 to i64, !dbg !893
  %arrayidx7 = getelementptr inbounds [10 x %struct.config_s], [10 x %struct.config_s]* @configuration_table, i64 0, i64 %idxprom6, !dbg !893
  %max_lazy = getelementptr inbounds %struct.config_s, %struct.config_s* %arrayidx7, i32 0, i32 1, !dbg !894
  %14 = load i16, i16* %max_lazy, align 2, !dbg !894
  %conv8 = zext i16 %14 to i32, !dbg !893
  %15 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !895
  %max_lazy_match = getelementptr inbounds %struct.internal_state, %struct.internal_state* %15, i32 0, i32 32, !dbg !896
  store i32 %conv8, i32* %max_lazy_match, align 8, !dbg !897
  %16 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !898
  %level9 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %16, i32 0, i32 33, !dbg !899
  %17 = load i32, i32* %level9, align 4, !dbg !899
  %idxprom10 = sext i32 %17 to i64, !dbg !900
  %arrayidx11 = getelementptr inbounds [10 x %struct.config_s], [10 x %struct.config_s]* @configuration_table, i64 0, i64 %idxprom10, !dbg !900
  %good_length = getelementptr inbounds %struct.config_s, %struct.config_s* %arrayidx11, i32 0, i32 0, !dbg !901
  %18 = load i16, i16* %good_length, align 16, !dbg !901
  %conv12 = zext i16 %18 to i32, !dbg !900
  %19 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !902
  %good_match = getelementptr inbounds %struct.internal_state, %struct.internal_state* %19, i32 0, i32 35, !dbg !903
  store i32 %conv12, i32* %good_match, align 4, !dbg !904
  %20 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !905
  %level13 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %20, i32 0, i32 33, !dbg !906
  %21 = load i32, i32* %level13, align 4, !dbg !906
  %idxprom14 = sext i32 %21 to i64, !dbg !907
  %arrayidx15 = getelementptr inbounds [10 x %struct.config_s], [10 x %struct.config_s]* @configuration_table, i64 0, i64 %idxprom14, !dbg !907
  %nice_length = getelementptr inbounds %struct.config_s, %struct.config_s* %arrayidx15, i32 0, i32 2, !dbg !908
  %22 = load i16, i16* %nice_length, align 4, !dbg !908
  %conv16 = zext i16 %22 to i32, !dbg !907
  %23 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !909
  %nice_match = getelementptr inbounds %struct.internal_state, %struct.internal_state* %23, i32 0, i32 36, !dbg !910
  store i32 %conv16, i32* %nice_match, align 8, !dbg !911
  %24 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !912
  %level17 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %24, i32 0, i32 33, !dbg !913
  %25 = load i32, i32* %level17, align 4, !dbg !913
  %idxprom18 = sext i32 %25 to i64, !dbg !914
  %arrayidx19 = getelementptr inbounds [10 x %struct.config_s], [10 x %struct.config_s]* @configuration_table, i64 0, i64 %idxprom18, !dbg !914
  %max_chain = getelementptr inbounds %struct.config_s, %struct.config_s* %arrayidx19, i32 0, i32 3, !dbg !915
  %26 = load i16, i16* %max_chain, align 2, !dbg !915
  %conv20 = zext i16 %26 to i32, !dbg !914
  %27 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !916
  %max_chain_length = getelementptr inbounds %struct.internal_state, %struct.internal_state* %27, i32 0, i32 31, !dbg !917
  store i32 %conv20, i32* %max_chain_length, align 4, !dbg !918
  %28 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !919
  %strstart = getelementptr inbounds %struct.internal_state, %struct.internal_state* %28, i32 0, i32 27, !dbg !920
  store i32 0, i32* %strstart, align 4, !dbg !921
  %29 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !922
  %block_start = getelementptr inbounds %struct.internal_state, %struct.internal_state* %29, i32 0, i32 23, !dbg !923
  store i64 0, i64* %block_start, align 8, !dbg !924
  %30 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !925
  %lookahead = getelementptr inbounds %struct.internal_state, %struct.internal_state* %30, i32 0, i32 29, !dbg !926
  store i32 0, i32* %lookahead, align 4, !dbg !927
  %31 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !928
  %prev_length = getelementptr inbounds %struct.internal_state, %struct.internal_state* %31, i32 0, i32 30, !dbg !929
  store i32 2, i32* %prev_length, align 8, !dbg !930
  %32 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !931
  %match_length = getelementptr inbounds %struct.internal_state, %struct.internal_state* %32, i32 0, i32 24, !dbg !932
  store i32 2, i32* %match_length, align 8, !dbg !933
  %33 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !934
  %match_available = getelementptr inbounds %struct.internal_state, %struct.internal_state* %33, i32 0, i32 26, !dbg !935
  store i32 0, i32* %match_available, align 8, !dbg !936
  %34 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !937
  %ins_h = getelementptr inbounds %struct.internal_state, %struct.internal_state* %34, i32 0, i32 18, !dbg !938
  store i32 0, i32* %ins_h, align 8, !dbg !939
  ret void, !dbg !940
}

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_deflateSetHeader(%struct.z_stream_s* %strm, %struct.gz_header_s* %head) #0 !dbg !206 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.z_stream_s*, align 8
  %head.addr = alloca %struct.gz_header_s*, align 8
  store %struct.z_stream_s* %strm, %struct.z_stream_s** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.z_stream_s** %strm.addr, metadata !941, metadata !277), !dbg !942
  store %struct.gz_header_s* %head, %struct.gz_header_s** %head.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.gz_header_s** %head.addr, metadata !943, metadata !277), !dbg !944
  %0 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !945
  %cmp = icmp eq %struct.z_stream_s* %0, null, !dbg !947
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !948

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !949
  %state = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %1, i32 0, i32 7, !dbg !951
  %2 = load %struct.internal_state*, %struct.internal_state** %state, align 8, !dbg !951
  %cmp1 = icmp eq %struct.internal_state* %2, null, !dbg !952
  br i1 %cmp1, label %if.then, label %if.end, !dbg !953

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -2, i32* %retval, align 4, !dbg !954
  br label %return, !dbg !954

if.end:                                           ; preds = %lor.lhs.false
  %3 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !956
  %state2 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %3, i32 0, i32 7, !dbg !958
  %4 = load %struct.internal_state*, %struct.internal_state** %state2, align 8, !dbg !958
  %wrap = getelementptr inbounds %struct.internal_state, %struct.internal_state* %4, i32 0, i32 6, !dbg !959
  %5 = load i32, i32* %wrap, align 4, !dbg !959
  %cmp3 = icmp ne i32 %5, 2, !dbg !960
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !961

if.then4:                                         ; preds = %if.end
  store i32 -2, i32* %retval, align 4, !dbg !962
  br label %return, !dbg !962

if.end5:                                          ; preds = %if.end
  %6 = load %struct.gz_header_s*, %struct.gz_header_s** %head.addr, align 8, !dbg !964
  %7 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !965
  %state6 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %7, i32 0, i32 7, !dbg !966
  %8 = load %struct.internal_state*, %struct.internal_state** %state6, align 8, !dbg !966
  %gzhead = getelementptr inbounds %struct.internal_state, %struct.internal_state* %8, i32 0, i32 7, !dbg !967
  store %struct.gz_header_s* %6, %struct.gz_header_s** %gzhead, align 8, !dbg !968
  store i32 0, i32* %retval, align 4, !dbg !969
  br label %return, !dbg !969

return:                                           ; preds = %if.end5, %if.then4, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !970
  ret i32 %9, !dbg !970
}

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_deflatePrime(%struct.z_stream_s* %strm, i32 %bits, i32 %value) #0 !dbg !209 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.z_stream_s*, align 8
  %bits.addr = alloca i32, align 4
  %value.addr = alloca i32, align 4
  store %struct.z_stream_s* %strm, %struct.z_stream_s** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.z_stream_s** %strm.addr, metadata !971, metadata !277), !dbg !972
  store i32 %bits, i32* %bits.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %bits.addr, metadata !973, metadata !277), !dbg !974
  store i32 %value, i32* %value.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %value.addr, metadata !975, metadata !277), !dbg !976
  %0 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !977
  %cmp = icmp eq %struct.z_stream_s* %0, null, !dbg !979
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !980

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !981
  %state = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %1, i32 0, i32 7, !dbg !983
  %2 = load %struct.internal_state*, %struct.internal_state** %state, align 8, !dbg !983
  %cmp1 = icmp eq %struct.internal_state* %2, null, !dbg !984
  br i1 %cmp1, label %if.then, label %if.end, !dbg !985

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -2, i32* %retval, align 4, !dbg !986
  br label %return, !dbg !986

if.end:                                           ; preds = %lor.lhs.false
  %3 = load i32, i32* %bits.addr, align 4, !dbg !988
  %4 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !989
  %state2 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %4, i32 0, i32 7, !dbg !990
  %5 = load %struct.internal_state*, %struct.internal_state** %state2, align 8, !dbg !990
  %bi_valid = getelementptr inbounds %struct.internal_state, %struct.internal_state* %5, i32 0, i32 57, !dbg !991
  store i32 %3, i32* %bi_valid, align 4, !dbg !992
  %6 = load i32, i32* %value.addr, align 4, !dbg !993
  %7 = load i32, i32* %bits.addr, align 4, !dbg !994
  %shl = shl i32 1, %7, !dbg !995
  %sub = sub nsw i32 %shl, 1, !dbg !996
  %and = and i32 %6, %sub, !dbg !997
  %conv = trunc i32 %and to i16, !dbg !998
  %8 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !999
  %state3 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %8, i32 0, i32 7, !dbg !1000
  %9 = load %struct.internal_state*, %struct.internal_state** %state3, align 8, !dbg !1000
  %bi_buf = getelementptr inbounds %struct.internal_state, %struct.internal_state* %9, i32 0, i32 56, !dbg !1001
  store i16 %conv, i16* %bi_buf, align 8, !dbg !1002
  store i32 0, i32* %retval, align 4, !dbg !1003
  br label %return, !dbg !1003

return:                                           ; preds = %if.end, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !1004
  ret i32 %10, !dbg !1004
}

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_deflateParams(%struct.z_stream_s* %strm, i32 %level, i32 %strategy) #0 !dbg !212 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.z_stream_s*, align 8
  %level.addr = alloca i32, align 4
  %strategy.addr = alloca i32, align 4
  %s = alloca %struct.internal_state*, align 8
  %func = alloca i32 (%struct.internal_state*, i32)*, align 8
  %err = alloca i32, align 4
  store %struct.z_stream_s* %strm, %struct.z_stream_s** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.z_stream_s** %strm.addr, metadata !1005, metadata !277), !dbg !1006
  store i32 %level, i32* %level.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %level.addr, metadata !1007, metadata !277), !dbg !1008
  store i32 %strategy, i32* %strategy.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %strategy.addr, metadata !1009, metadata !277), !dbg !1010
  call void @llvm.dbg.declare(metadata %struct.internal_state** %s, metadata !1011, metadata !277), !dbg !1012
  call void @llvm.dbg.declare(metadata i32 (%struct.internal_state*, i32)** %func, metadata !1013, metadata !277), !dbg !1014
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1015, metadata !277), !dbg !1016
  store i32 0, i32* %err, align 4, !dbg !1016
  %0 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1017
  %cmp = icmp eq %struct.z_stream_s* %0, null, !dbg !1019
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1020

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1021
  %state = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %1, i32 0, i32 7, !dbg !1023
  %2 = load %struct.internal_state*, %struct.internal_state** %state, align 8, !dbg !1023
  %cmp1 = icmp eq %struct.internal_state* %2, null, !dbg !1024
  br i1 %cmp1, label %if.then, label %if.end, !dbg !1025

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -2, i32* %retval, align 4, !dbg !1026
  br label %return, !dbg !1026

if.end:                                           ; preds = %lor.lhs.false
  %3 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1028
  %state2 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %3, i32 0, i32 7, !dbg !1029
  %4 = load %struct.internal_state*, %struct.internal_state** %state2, align 8, !dbg !1029
  store %struct.internal_state* %4, %struct.internal_state** %s, align 8, !dbg !1030
  %5 = load i32, i32* %level.addr, align 4, !dbg !1031
  %cmp3 = icmp eq i32 %5, -1, !dbg !1033
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1034

if.then4:                                         ; preds = %if.end
  store i32 6, i32* %level.addr, align 4, !dbg !1035
  br label %if.end5, !dbg !1037

if.end5:                                          ; preds = %if.then4, %if.end
  %6 = load i32, i32* %level.addr, align 4, !dbg !1038
  %cmp6 = icmp slt i32 %6, 0, !dbg !1040
  br i1 %cmp6, label %if.then13, label %lor.lhs.false7, !dbg !1041

lor.lhs.false7:                                   ; preds = %if.end5
  %7 = load i32, i32* %level.addr, align 4, !dbg !1042
  %cmp8 = icmp sgt i32 %7, 9, !dbg !1044
  br i1 %cmp8, label %if.then13, label %lor.lhs.false9, !dbg !1045

lor.lhs.false9:                                   ; preds = %lor.lhs.false7
  %8 = load i32, i32* %strategy.addr, align 4, !dbg !1046
  %cmp10 = icmp slt i32 %8, 0, !dbg !1048
  br i1 %cmp10, label %if.then13, label %lor.lhs.false11, !dbg !1049

lor.lhs.false11:                                  ; preds = %lor.lhs.false9
  %9 = load i32, i32* %strategy.addr, align 4, !dbg !1050
  %cmp12 = icmp sgt i32 %9, 4, !dbg !1052
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !1053

if.then13:                                        ; preds = %lor.lhs.false11, %lor.lhs.false9, %lor.lhs.false7, %if.end5
  store i32 -2, i32* %retval, align 4, !dbg !1054
  br label %return, !dbg !1054

if.end14:                                         ; preds = %lor.lhs.false11
  %10 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1056
  %level15 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %10, i32 0, i32 33, !dbg !1057
  %11 = load i32, i32* %level15, align 4, !dbg !1057
  %idxprom = sext i32 %11 to i64, !dbg !1058
  %arrayidx = getelementptr inbounds [10 x %struct.config_s], [10 x %struct.config_s]* @configuration_table, i64 0, i64 %idxprom, !dbg !1058
  %func16 = getelementptr inbounds %struct.config_s, %struct.config_s* %arrayidx, i32 0, i32 4, !dbg !1059
  %12 = load i32 (%struct.internal_state*, i32)*, i32 (%struct.internal_state*, i32)** %func16, align 8, !dbg !1059
  store i32 (%struct.internal_state*, i32)* %12, i32 (%struct.internal_state*, i32)** %func, align 8, !dbg !1060
  %13 = load i32 (%struct.internal_state*, i32)*, i32 (%struct.internal_state*, i32)** %func, align 8, !dbg !1061
  %14 = load i32, i32* %level.addr, align 4, !dbg !1063
  %idxprom17 = sext i32 %14 to i64, !dbg !1064
  %arrayidx18 = getelementptr inbounds [10 x %struct.config_s], [10 x %struct.config_s]* @configuration_table, i64 0, i64 %idxprom17, !dbg !1064
  %func19 = getelementptr inbounds %struct.config_s, %struct.config_s* %arrayidx18, i32 0, i32 4, !dbg !1065
  %15 = load i32 (%struct.internal_state*, i32)*, i32 (%struct.internal_state*, i32)** %func19, align 8, !dbg !1065
  %cmp20 = icmp ne i32 (%struct.internal_state*, i32)* %13, %15, !dbg !1066
  br i1 %cmp20, label %land.lhs.true, label %if.end23, !dbg !1067

land.lhs.true:                                    ; preds = %if.end14
  %16 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1068
  %total_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %16, i32 0, i32 2, !dbg !1070
  %17 = load i64, i64* %total_in, align 8, !dbg !1070
  %cmp21 = icmp ne i64 %17, 0, !dbg !1071
  br i1 %cmp21, label %if.then22, label %if.end23, !dbg !1072

if.then22:                                        ; preds = %land.lhs.true
  %18 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1073
  %call = call i32 @cm_zlib_deflate(%struct.z_stream_s* %18, i32 1), !dbg !1075
  store i32 %call, i32* %err, align 4, !dbg !1076
  br label %if.end23, !dbg !1077

if.end23:                                         ; preds = %if.then22, %land.lhs.true, %if.end14
  %19 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1078
  %level24 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %19, i32 0, i32 33, !dbg !1080
  %20 = load i32, i32* %level24, align 4, !dbg !1080
  %21 = load i32, i32* %level.addr, align 4, !dbg !1081
  %cmp25 = icmp ne i32 %20, %21, !dbg !1082
  br i1 %cmp25, label %if.then26, label %if.end39, !dbg !1083

if.then26:                                        ; preds = %if.end23
  %22 = load i32, i32* %level.addr, align 4, !dbg !1084
  %23 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1086
  %level27 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %23, i32 0, i32 33, !dbg !1087
  store i32 %22, i32* %level27, align 4, !dbg !1088
  %24 = load i32, i32* %level.addr, align 4, !dbg !1089
  %idxprom28 = sext i32 %24 to i64, !dbg !1090
  %arrayidx29 = getelementptr inbounds [10 x %struct.config_s], [10 x %struct.config_s]* @configuration_table, i64 0, i64 %idxprom28, !dbg !1090
  %max_lazy = getelementptr inbounds %struct.config_s, %struct.config_s* %arrayidx29, i32 0, i32 1, !dbg !1091
  %25 = load i16, i16* %max_lazy, align 2, !dbg !1091
  %conv = zext i16 %25 to i32, !dbg !1090
  %26 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1092
  %max_lazy_match = getelementptr inbounds %struct.internal_state, %struct.internal_state* %26, i32 0, i32 32, !dbg !1093
  store i32 %conv, i32* %max_lazy_match, align 8, !dbg !1094
  %27 = load i32, i32* %level.addr, align 4, !dbg !1095
  %idxprom30 = sext i32 %27 to i64, !dbg !1096
  %arrayidx31 = getelementptr inbounds [10 x %struct.config_s], [10 x %struct.config_s]* @configuration_table, i64 0, i64 %idxprom30, !dbg !1096
  %good_length = getelementptr inbounds %struct.config_s, %struct.config_s* %arrayidx31, i32 0, i32 0, !dbg !1097
  %28 = load i16, i16* %good_length, align 16, !dbg !1097
  %conv32 = zext i16 %28 to i32, !dbg !1096
  %29 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1098
  %good_match = getelementptr inbounds %struct.internal_state, %struct.internal_state* %29, i32 0, i32 35, !dbg !1099
  store i32 %conv32, i32* %good_match, align 4, !dbg !1100
  %30 = load i32, i32* %level.addr, align 4, !dbg !1101
  %idxprom33 = sext i32 %30 to i64, !dbg !1102
  %arrayidx34 = getelementptr inbounds [10 x %struct.config_s], [10 x %struct.config_s]* @configuration_table, i64 0, i64 %idxprom33, !dbg !1102
  %nice_length = getelementptr inbounds %struct.config_s, %struct.config_s* %arrayidx34, i32 0, i32 2, !dbg !1103
  %31 = load i16, i16* %nice_length, align 4, !dbg !1103
  %conv35 = zext i16 %31 to i32, !dbg !1102
  %32 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1104
  %nice_match = getelementptr inbounds %struct.internal_state, %struct.internal_state* %32, i32 0, i32 36, !dbg !1105
  store i32 %conv35, i32* %nice_match, align 8, !dbg !1106
  %33 = load i32, i32* %level.addr, align 4, !dbg !1107
  %idxprom36 = sext i32 %33 to i64, !dbg !1108
  %arrayidx37 = getelementptr inbounds [10 x %struct.config_s], [10 x %struct.config_s]* @configuration_table, i64 0, i64 %idxprom36, !dbg !1108
  %max_chain = getelementptr inbounds %struct.config_s, %struct.config_s* %arrayidx37, i32 0, i32 3, !dbg !1109
  %34 = load i16, i16* %max_chain, align 2, !dbg !1109
  %conv38 = zext i16 %34 to i32, !dbg !1108
  %35 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1110
  %max_chain_length = getelementptr inbounds %struct.internal_state, %struct.internal_state* %35, i32 0, i32 31, !dbg !1111
  store i32 %conv38, i32* %max_chain_length, align 4, !dbg !1112
  br label %if.end39, !dbg !1113

if.end39:                                         ; preds = %if.then26, %if.end23
  %36 = load i32, i32* %strategy.addr, align 4, !dbg !1114
  %37 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1115
  %strategy40 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %37, i32 0, i32 34, !dbg !1116
  store i32 %36, i32* %strategy40, align 8, !dbg !1117
  %38 = load i32, i32* %err, align 4, !dbg !1118
  store i32 %38, i32* %retval, align 4, !dbg !1119
  br label %return, !dbg !1119

return:                                           ; preds = %if.end39, %if.then13, %if.then
  %39 = load i32, i32* %retval, align 4, !dbg !1120
  ret i32 %39, !dbg !1120
}

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_deflate(%struct.z_stream_s* %strm, i32 %flush) #0 !dbg !219 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.z_stream_s*, align 8
  %flush.addr = alloca i32, align 4
  %old_flush = alloca i32, align 4
  %s = alloca %struct.internal_state*, align 8
  %header = alloca i32, align 4
  %level_flags = alloca i32, align 4
  %beg = alloca i32, align 4
  %beg354 = alloca i32, align 4
  %val = alloca i32, align 4
  %beg439 = alloca i32, align 4
  %val441 = alloca i32, align 4
  %bstate = alloca i32, align 4
  store %struct.z_stream_s* %strm, %struct.z_stream_s** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.z_stream_s** %strm.addr, metadata !1121, metadata !277), !dbg !1122
  store i32 %flush, i32* %flush.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flush.addr, metadata !1123, metadata !277), !dbg !1124
  call void @llvm.dbg.declare(metadata i32* %old_flush, metadata !1125, metadata !277), !dbg !1126
  call void @llvm.dbg.declare(metadata %struct.internal_state** %s, metadata !1127, metadata !277), !dbg !1128
  %0 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1129
  %cmp = icmp eq %struct.z_stream_s* %0, null, !dbg !1131
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1132

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1133
  %state = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %1, i32 0, i32 7, !dbg !1135
  %2 = load %struct.internal_state*, %struct.internal_state** %state, align 8, !dbg !1135
  %cmp1 = icmp eq %struct.internal_state* %2, null, !dbg !1136
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !1137

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %3 = load i32, i32* %flush.addr, align 4, !dbg !1138
  %cmp3 = icmp sgt i32 %3, 4, !dbg !1139
  br i1 %cmp3, label %if.then, label %lor.lhs.false4, !dbg !1140

lor.lhs.false4:                                   ; preds = %lor.lhs.false2
  %4 = load i32, i32* %flush.addr, align 4, !dbg !1141
  %cmp5 = icmp slt i32 %4, 0, !dbg !1142
  br i1 %cmp5, label %if.then, label %if.end, !dbg !1143

if.then:                                          ; preds = %lor.lhs.false4, %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 -2, i32* %retval, align 4, !dbg !1145
  br label %return, !dbg !1145

if.end:                                           ; preds = %lor.lhs.false4
  %5 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1147
  %state6 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %5, i32 0, i32 7, !dbg !1148
  %6 = load %struct.internal_state*, %struct.internal_state** %state6, align 8, !dbg !1148
  store %struct.internal_state* %6, %struct.internal_state** %s, align 8, !dbg !1149
  %7 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1150
  %next_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %7, i32 0, i32 3, !dbg !1152
  %8 = load i8*, i8** %next_out, align 8, !dbg !1152
  %cmp7 = icmp eq i8* %8, null, !dbg !1153
  br i1 %cmp7, label %if.then15, label %lor.lhs.false8, !dbg !1154

lor.lhs.false8:                                   ; preds = %if.end
  %9 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1155
  %next_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %9, i32 0, i32 0, !dbg !1156
  %10 = load i8*, i8** %next_in, align 8, !dbg !1156
  %cmp9 = icmp eq i8* %10, null, !dbg !1157
  br i1 %cmp9, label %land.lhs.true, label %lor.lhs.false11, !dbg !1158

land.lhs.true:                                    ; preds = %lor.lhs.false8
  %11 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1159
  %avail_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %11, i32 0, i32 1, !dbg !1161
  %12 = load i32, i32* %avail_in, align 8, !dbg !1161
  %cmp10 = icmp ne i32 %12, 0, !dbg !1162
  br i1 %cmp10, label %if.then15, label %lor.lhs.false11, !dbg !1163

lor.lhs.false11:                                  ; preds = %land.lhs.true, %lor.lhs.false8
  %13 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1164
  %status = getelementptr inbounds %struct.internal_state, %struct.internal_state* %13, i32 0, i32 1, !dbg !1165
  %14 = load i32, i32* %status, align 8, !dbg !1165
  %cmp12 = icmp eq i32 %14, 666, !dbg !1166
  br i1 %cmp12, label %land.lhs.true13, label %if.end16, !dbg !1167

land.lhs.true13:                                  ; preds = %lor.lhs.false11
  %15 = load i32, i32* %flush.addr, align 4, !dbg !1168
  %cmp14 = icmp ne i32 %15, 4, !dbg !1169
  br i1 %cmp14, label %if.then15, label %if.end16, !dbg !1170

if.then15:                                        ; preds = %land.lhs.true13, %land.lhs.true, %if.end
  %16 = load i8*, i8** getelementptr inbounds ([10 x i8*], [10 x i8*]* @cm_zlib_z_errmsg, i64 0, i64 4), align 16, !dbg !1172
  %17 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1172
  %msg = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %17, i32 0, i32 6, !dbg !1172
  store i8* %16, i8** %msg, align 8, !dbg !1172
  store i32 -2, i32* %retval, align 4, !dbg !1172
  br label %return, !dbg !1172

if.end16:                                         ; preds = %land.lhs.true13, %lor.lhs.false11
  %18 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1174
  %avail_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %18, i32 0, i32 4, !dbg !1176
  %19 = load i32, i32* %avail_out, align 8, !dbg !1176
  %cmp17 = icmp eq i32 %19, 0, !dbg !1177
  br i1 %cmp17, label %if.then18, label %if.end20, !dbg !1178

if.then18:                                        ; preds = %if.end16
  %20 = load i8*, i8** getelementptr inbounds ([10 x i8*], [10 x i8*]* @cm_zlib_z_errmsg, i64 0, i64 7), align 8, !dbg !1179
  %21 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1179
  %msg19 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %21, i32 0, i32 6, !dbg !1179
  store i8* %20, i8** %msg19, align 8, !dbg !1179
  store i32 -5, i32* %retval, align 4, !dbg !1179
  br label %return, !dbg !1179

if.end20:                                         ; preds = %if.end16
  %22 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1181
  %23 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1182
  %strm21 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %23, i32 0, i32 0, !dbg !1183
  store %struct.z_stream_s* %22, %struct.z_stream_s** %strm21, align 8, !dbg !1184
  %24 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1185
  %last_flush = getelementptr inbounds %struct.internal_state, %struct.internal_state* %24, i32 0, i32 10, !dbg !1186
  %25 = load i32, i32* %last_flush, align 8, !dbg !1186
  store i32 %25, i32* %old_flush, align 4, !dbg !1187
  %26 = load i32, i32* %flush.addr, align 4, !dbg !1188
  %27 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1189
  %last_flush22 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %27, i32 0, i32 10, !dbg !1190
  store i32 %26, i32* %last_flush22, align 8, !dbg !1191
  %28 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1192
  %status23 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %28, i32 0, i32 1, !dbg !1194
  %29 = load i32, i32* %status23, align 8, !dbg !1194
  %cmp24 = icmp eq i32 %29, 42, !dbg !1195
  br i1 %cmp24, label %if.then25, label %if.end257, !dbg !1196

if.then25:                                        ; preds = %if.end20
  %30 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1197
  %wrap = getelementptr inbounds %struct.internal_state, %struct.internal_state* %30, i32 0, i32 6, !dbg !1200
  %31 = load i32, i32* %wrap, align 4, !dbg !1200
  %cmp26 = icmp eq i32 %31, 2, !dbg !1201
  br i1 %cmp26, label %if.then27, label %if.else209, !dbg !1202

if.then27:                                        ; preds = %if.then25
  %call = call i64 @cm_zlib_crc32(i64 0, i8* null, i32 0), !dbg !1203
  %32 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1205
  %adler = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %32, i32 0, i32 12, !dbg !1206
  store i64 %call, i64* %adler, align 8, !dbg !1207
  %33 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1208
  %pending = getelementptr inbounds %struct.internal_state, %struct.internal_state* %33, i32 0, i32 5, !dbg !1208
  %34 = load i32, i32* %pending, align 8, !dbg !1208
  %inc = add i32 %34, 1, !dbg !1208
  store i32 %inc, i32* %pending, align 8, !dbg !1208
  %idxprom = zext i32 %34 to i64, !dbg !1208
  %35 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1208
  %pending_buf = getelementptr inbounds %struct.internal_state, %struct.internal_state* %35, i32 0, i32 2, !dbg !1208
  %36 = load i8*, i8** %pending_buf, align 8, !dbg !1208
  %arrayidx = getelementptr inbounds i8, i8* %36, i64 %idxprom, !dbg !1208
  store i8 31, i8* %arrayidx, align 1, !dbg !1208
  %37 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1210
  %pending28 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %37, i32 0, i32 5, !dbg !1210
  %38 = load i32, i32* %pending28, align 8, !dbg !1210
  %inc29 = add i32 %38, 1, !dbg !1210
  store i32 %inc29, i32* %pending28, align 8, !dbg !1210
  %idxprom30 = zext i32 %38 to i64, !dbg !1210
  %39 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1210
  %pending_buf31 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %39, i32 0, i32 2, !dbg !1210
  %40 = load i8*, i8** %pending_buf31, align 8, !dbg !1210
  %arrayidx32 = getelementptr inbounds i8, i8* %40, i64 %idxprom30, !dbg !1210
  store i8 -117, i8* %arrayidx32, align 1, !dbg !1210
  %41 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1212
  %pending33 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %41, i32 0, i32 5, !dbg !1212
  %42 = load i32, i32* %pending33, align 8, !dbg !1212
  %inc34 = add i32 %42, 1, !dbg !1212
  store i32 %inc34, i32* %pending33, align 8, !dbg !1212
  %idxprom35 = zext i32 %42 to i64, !dbg !1212
  %43 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1212
  %pending_buf36 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %43, i32 0, i32 2, !dbg !1212
  %44 = load i8*, i8** %pending_buf36, align 8, !dbg !1212
  %arrayidx37 = getelementptr inbounds i8, i8* %44, i64 %idxprom35, !dbg !1212
  store i8 8, i8* %arrayidx37, align 1, !dbg !1212
  %45 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1214
  %gzhead = getelementptr inbounds %struct.internal_state, %struct.internal_state* %45, i32 0, i32 7, !dbg !1216
  %46 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead, align 8, !dbg !1216
  %cmp38 = icmp eq %struct.gz_header_s* %46, null, !dbg !1217
  br i1 %cmp38, label %if.then39, label %if.else, !dbg !1218

if.then39:                                        ; preds = %if.then27
  %47 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1219
  %pending40 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %47, i32 0, i32 5, !dbg !1219
  %48 = load i32, i32* %pending40, align 8, !dbg !1219
  %inc41 = add i32 %48, 1, !dbg !1219
  store i32 %inc41, i32* %pending40, align 8, !dbg !1219
  %idxprom42 = zext i32 %48 to i64, !dbg !1219
  %49 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1219
  %pending_buf43 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %49, i32 0, i32 2, !dbg !1219
  %50 = load i8*, i8** %pending_buf43, align 8, !dbg !1219
  %arrayidx44 = getelementptr inbounds i8, i8* %50, i64 %idxprom42, !dbg !1219
  store i8 0, i8* %arrayidx44, align 1, !dbg !1219
  %51 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1222
  %pending45 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %51, i32 0, i32 5, !dbg !1222
  %52 = load i32, i32* %pending45, align 8, !dbg !1222
  %inc46 = add i32 %52, 1, !dbg !1222
  store i32 %inc46, i32* %pending45, align 8, !dbg !1222
  %idxprom47 = zext i32 %52 to i64, !dbg !1222
  %53 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1222
  %pending_buf48 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %53, i32 0, i32 2, !dbg !1222
  %54 = load i8*, i8** %pending_buf48, align 8, !dbg !1222
  %arrayidx49 = getelementptr inbounds i8, i8* %54, i64 %idxprom47, !dbg !1222
  store i8 0, i8* %arrayidx49, align 1, !dbg !1222
  %55 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1224
  %pending50 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %55, i32 0, i32 5, !dbg !1224
  %56 = load i32, i32* %pending50, align 8, !dbg !1224
  %inc51 = add i32 %56, 1, !dbg !1224
  store i32 %inc51, i32* %pending50, align 8, !dbg !1224
  %idxprom52 = zext i32 %56 to i64, !dbg !1224
  %57 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1224
  %pending_buf53 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %57, i32 0, i32 2, !dbg !1224
  %58 = load i8*, i8** %pending_buf53, align 8, !dbg !1224
  %arrayidx54 = getelementptr inbounds i8, i8* %58, i64 %idxprom52, !dbg !1224
  store i8 0, i8* %arrayidx54, align 1, !dbg !1224
  %59 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1226
  %pending55 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %59, i32 0, i32 5, !dbg !1226
  %60 = load i32, i32* %pending55, align 8, !dbg !1226
  %inc56 = add i32 %60, 1, !dbg !1226
  store i32 %inc56, i32* %pending55, align 8, !dbg !1226
  %idxprom57 = zext i32 %60 to i64, !dbg !1226
  %61 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1226
  %pending_buf58 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %61, i32 0, i32 2, !dbg !1226
  %62 = load i8*, i8** %pending_buf58, align 8, !dbg !1226
  %arrayidx59 = getelementptr inbounds i8, i8* %62, i64 %idxprom57, !dbg !1226
  store i8 0, i8* %arrayidx59, align 1, !dbg !1226
  %63 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1228
  %pending60 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %63, i32 0, i32 5, !dbg !1228
  %64 = load i32, i32* %pending60, align 8, !dbg !1228
  %inc61 = add i32 %64, 1, !dbg !1228
  store i32 %inc61, i32* %pending60, align 8, !dbg !1228
  %idxprom62 = zext i32 %64 to i64, !dbg !1228
  %65 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1228
  %pending_buf63 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %65, i32 0, i32 2, !dbg !1228
  %66 = load i8*, i8** %pending_buf63, align 8, !dbg !1228
  %arrayidx64 = getelementptr inbounds i8, i8* %66, i64 %idxprom62, !dbg !1228
  store i8 0, i8* %arrayidx64, align 1, !dbg !1228
  %67 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1230
  %level = getelementptr inbounds %struct.internal_state, %struct.internal_state* %67, i32 0, i32 33, !dbg !1230
  %68 = load i32, i32* %level, align 4, !dbg !1230
  %cmp65 = icmp eq i32 %68, 9, !dbg !1230
  br i1 %cmp65, label %cond.true, label %cond.false, !dbg !1230

cond.true:                                        ; preds = %if.then39
  br label %cond.end, !dbg !1232

cond.false:                                       ; preds = %if.then39
  %69 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1234
  %strategy = getelementptr inbounds %struct.internal_state, %struct.internal_state* %69, i32 0, i32 34, !dbg !1234
  %70 = load i32, i32* %strategy, align 8, !dbg !1234
  %cmp66 = icmp sge i32 %70, 2, !dbg !1234
  br i1 %cmp66, label %lor.end, label %lor.rhs, !dbg !1234

lor.rhs:                                          ; preds = %cond.false
  %71 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1236
  %level67 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %71, i32 0, i32 33, !dbg !1236
  %72 = load i32, i32* %level67, align 4, !dbg !1236
  %cmp68 = icmp slt i32 %72, 2, !dbg !1236
  br label %lor.end, !dbg !1236

lor.end:                                          ; preds = %lor.rhs, %cond.false
  %73 = phi i1 [ true, %cond.false ], [ %cmp68, %lor.rhs ]
  %cond = select i1 %73, i32 4, i32 0, !dbg !1238
  br label %cond.end, !dbg !1238

cond.end:                                         ; preds = %lor.end, %cond.true
  %cond69 = phi i32 [ 2, %cond.true ], [ %cond, %lor.end ], !dbg !1240
  %conv = trunc i32 %cond69 to i8, !dbg !1240
  %74 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1240
  %pending70 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %74, i32 0, i32 5, !dbg !1240
  %75 = load i32, i32* %pending70, align 8, !dbg !1240
  %inc71 = add i32 %75, 1, !dbg !1240
  store i32 %inc71, i32* %pending70, align 8, !dbg !1240
  %idxprom72 = zext i32 %75 to i64, !dbg !1240
  %76 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1240
  %pending_buf73 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %76, i32 0, i32 2, !dbg !1240
  %77 = load i8*, i8** %pending_buf73, align 8, !dbg !1240
  %arrayidx74 = getelementptr inbounds i8, i8* %77, i64 %idxprom72, !dbg !1240
  store i8 %conv, i8* %arrayidx74, align 1, !dbg !1240
  %78 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1242
  %pending75 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %78, i32 0, i32 5, !dbg !1242
  %79 = load i32, i32* %pending75, align 8, !dbg !1242
  %inc76 = add i32 %79, 1, !dbg !1242
  store i32 %inc76, i32* %pending75, align 8, !dbg !1242
  %idxprom77 = zext i32 %79 to i64, !dbg !1242
  %80 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1242
  %pending_buf78 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %80, i32 0, i32 2, !dbg !1242
  %81 = load i8*, i8** %pending_buf78, align 8, !dbg !1242
  %arrayidx79 = getelementptr inbounds i8, i8* %81, i64 %idxprom77, !dbg !1242
  store i8 3, i8* %arrayidx79, align 1, !dbg !1242
  %82 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1244
  %status80 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %82, i32 0, i32 1, !dbg !1245
  store i32 113, i32* %status80, align 8, !dbg !1246
  br label %if.end208, !dbg !1247

if.else:                                          ; preds = %if.then27
  %83 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1248
  %gzhead81 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %83, i32 0, i32 7, !dbg !1248
  %84 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead81, align 8, !dbg !1248
  %text = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %84, i32 0, i32 0, !dbg !1248
  %85 = load i32, i32* %text, align 8, !dbg !1248
  %tobool = icmp ne i32 %85, 0, !dbg !1248
  %cond82 = select i1 %tobool, i32 1, i32 0, !dbg !1248
  %86 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1248
  %gzhead83 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %86, i32 0, i32 7, !dbg !1248
  %87 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead83, align 8, !dbg !1248
  %hcrc = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %87, i32 0, i32 11, !dbg !1248
  %88 = load i32, i32* %hcrc, align 4, !dbg !1248
  %tobool84 = icmp ne i32 %88, 0, !dbg !1248
  %cond85 = select i1 %tobool84, i32 2, i32 0, !dbg !1248
  %add = add nsw i32 %cond82, %cond85, !dbg !1248
  %89 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1248
  %gzhead86 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %89, i32 0, i32 7, !dbg !1248
  %90 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead86, align 8, !dbg !1248
  %extra = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %90, i32 0, i32 4, !dbg !1248
  %91 = load i8*, i8** %extra, align 8, !dbg !1248
  %cmp87 = icmp eq i8* %91, null, !dbg !1248
  %cond89 = select i1 %cmp87, i32 0, i32 4, !dbg !1248
  %add90 = add nsw i32 %add, %cond89, !dbg !1248
  %92 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1248
  %gzhead91 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %92, i32 0, i32 7, !dbg !1248
  %93 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead91, align 8, !dbg !1248
  %name = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %93, i32 0, i32 7, !dbg !1248
  %94 = load i8*, i8** %name, align 8, !dbg !1248
  %cmp92 = icmp eq i8* %94, null, !dbg !1248
  %cond94 = select i1 %cmp92, i32 0, i32 8, !dbg !1248
  %add95 = add nsw i32 %add90, %cond94, !dbg !1248
  %95 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1248
  %gzhead96 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %95, i32 0, i32 7, !dbg !1248
  %96 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead96, align 8, !dbg !1248
  %comment = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %96, i32 0, i32 9, !dbg !1248
  %97 = load i8*, i8** %comment, align 8, !dbg !1248
  %cmp97 = icmp eq i8* %97, null, !dbg !1248
  %cond99 = select i1 %cmp97, i32 0, i32 16, !dbg !1248
  %add100 = add nsw i32 %add95, %cond99, !dbg !1248
  %conv101 = trunc i32 %add100 to i8, !dbg !1248
  %98 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1248
  %pending102 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %98, i32 0, i32 5, !dbg !1248
  %99 = load i32, i32* %pending102, align 8, !dbg !1248
  %inc103 = add i32 %99, 1, !dbg !1248
  store i32 %inc103, i32* %pending102, align 8, !dbg !1248
  %idxprom104 = zext i32 %99 to i64, !dbg !1248
  %100 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1248
  %pending_buf105 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %100, i32 0, i32 2, !dbg !1248
  %101 = load i8*, i8** %pending_buf105, align 8, !dbg !1248
  %arrayidx106 = getelementptr inbounds i8, i8* %101, i64 %idxprom104, !dbg !1248
  store i8 %conv101, i8* %arrayidx106, align 1, !dbg !1248
  %102 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1251
  %gzhead107 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %102, i32 0, i32 7, !dbg !1251
  %103 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead107, align 8, !dbg !1251
  %time = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %103, i32 0, i32 1, !dbg !1251
  %104 = load i64, i64* %time, align 8, !dbg !1251
  %and = and i64 %104, 255, !dbg !1251
  %conv108 = trunc i64 %and to i8, !dbg !1251
  %105 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1251
  %pending109 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %105, i32 0, i32 5, !dbg !1251
  %106 = load i32, i32* %pending109, align 8, !dbg !1251
  %inc110 = add i32 %106, 1, !dbg !1251
  store i32 %inc110, i32* %pending109, align 8, !dbg !1251
  %idxprom111 = zext i32 %106 to i64, !dbg !1251
  %107 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1251
  %pending_buf112 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %107, i32 0, i32 2, !dbg !1251
  %108 = load i8*, i8** %pending_buf112, align 8, !dbg !1251
  %arrayidx113 = getelementptr inbounds i8, i8* %108, i64 %idxprom111, !dbg !1251
  store i8 %conv108, i8* %arrayidx113, align 1, !dbg !1251
  %109 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1253
  %gzhead114 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %109, i32 0, i32 7, !dbg !1253
  %110 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead114, align 8, !dbg !1253
  %time115 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %110, i32 0, i32 1, !dbg !1253
  %111 = load i64, i64* %time115, align 8, !dbg !1253
  %shr = lshr i64 %111, 8, !dbg !1253
  %and116 = and i64 %shr, 255, !dbg !1253
  %conv117 = trunc i64 %and116 to i8, !dbg !1253
  %112 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1253
  %pending118 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %112, i32 0, i32 5, !dbg !1253
  %113 = load i32, i32* %pending118, align 8, !dbg !1253
  %inc119 = add i32 %113, 1, !dbg !1253
  store i32 %inc119, i32* %pending118, align 8, !dbg !1253
  %idxprom120 = zext i32 %113 to i64, !dbg !1253
  %114 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1253
  %pending_buf121 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %114, i32 0, i32 2, !dbg !1253
  %115 = load i8*, i8** %pending_buf121, align 8, !dbg !1253
  %arrayidx122 = getelementptr inbounds i8, i8* %115, i64 %idxprom120, !dbg !1253
  store i8 %conv117, i8* %arrayidx122, align 1, !dbg !1253
  %116 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1255
  %gzhead123 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %116, i32 0, i32 7, !dbg !1255
  %117 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead123, align 8, !dbg !1255
  %time124 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %117, i32 0, i32 1, !dbg !1255
  %118 = load i64, i64* %time124, align 8, !dbg !1255
  %shr125 = lshr i64 %118, 16, !dbg !1255
  %and126 = and i64 %shr125, 255, !dbg !1255
  %conv127 = trunc i64 %and126 to i8, !dbg !1255
  %119 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1255
  %pending128 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %119, i32 0, i32 5, !dbg !1255
  %120 = load i32, i32* %pending128, align 8, !dbg !1255
  %inc129 = add i32 %120, 1, !dbg !1255
  store i32 %inc129, i32* %pending128, align 8, !dbg !1255
  %idxprom130 = zext i32 %120 to i64, !dbg !1255
  %121 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1255
  %pending_buf131 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %121, i32 0, i32 2, !dbg !1255
  %122 = load i8*, i8** %pending_buf131, align 8, !dbg !1255
  %arrayidx132 = getelementptr inbounds i8, i8* %122, i64 %idxprom130, !dbg !1255
  store i8 %conv127, i8* %arrayidx132, align 1, !dbg !1255
  %123 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1257
  %gzhead133 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %123, i32 0, i32 7, !dbg !1257
  %124 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead133, align 8, !dbg !1257
  %time134 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %124, i32 0, i32 1, !dbg !1257
  %125 = load i64, i64* %time134, align 8, !dbg !1257
  %shr135 = lshr i64 %125, 24, !dbg !1257
  %and136 = and i64 %shr135, 255, !dbg !1257
  %conv137 = trunc i64 %and136 to i8, !dbg !1257
  %126 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1257
  %pending138 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %126, i32 0, i32 5, !dbg !1257
  %127 = load i32, i32* %pending138, align 8, !dbg !1257
  %inc139 = add i32 %127, 1, !dbg !1257
  store i32 %inc139, i32* %pending138, align 8, !dbg !1257
  %idxprom140 = zext i32 %127 to i64, !dbg !1257
  %128 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1257
  %pending_buf141 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %128, i32 0, i32 2, !dbg !1257
  %129 = load i8*, i8** %pending_buf141, align 8, !dbg !1257
  %arrayidx142 = getelementptr inbounds i8, i8* %129, i64 %idxprom140, !dbg !1257
  store i8 %conv137, i8* %arrayidx142, align 1, !dbg !1257
  %130 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1259
  %level143 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %130, i32 0, i32 33, !dbg !1259
  %131 = load i32, i32* %level143, align 4, !dbg !1259
  %cmp144 = icmp eq i32 %131, 9, !dbg !1259
  br i1 %cmp144, label %cond.true146, label %cond.false147, !dbg !1259

cond.true146:                                     ; preds = %if.else
  br label %cond.end157, !dbg !1261

cond.false147:                                    ; preds = %if.else
  %132 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1263
  %strategy148 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %132, i32 0, i32 34, !dbg !1263
  %133 = load i32, i32* %strategy148, align 8, !dbg !1263
  %cmp149 = icmp sge i32 %133, 2, !dbg !1263
  br i1 %cmp149, label %lor.end155, label %lor.rhs151, !dbg !1263

lor.rhs151:                                       ; preds = %cond.false147
  %134 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1265
  %level152 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %134, i32 0, i32 33, !dbg !1265
  %135 = load i32, i32* %level152, align 4, !dbg !1265
  %cmp153 = icmp slt i32 %135, 2, !dbg !1265
  br label %lor.end155, !dbg !1265

lor.end155:                                       ; preds = %lor.rhs151, %cond.false147
  %136 = phi i1 [ true, %cond.false147 ], [ %cmp153, %lor.rhs151 ]
  %cond156 = select i1 %136, i32 4, i32 0, !dbg !1267
  br label %cond.end157, !dbg !1267

cond.end157:                                      ; preds = %lor.end155, %cond.true146
  %cond158 = phi i32 [ 2, %cond.true146 ], [ %cond156, %lor.end155 ], !dbg !1269
  %conv159 = trunc i32 %cond158 to i8, !dbg !1269
  %137 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1269
  %pending160 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %137, i32 0, i32 5, !dbg !1269
  %138 = load i32, i32* %pending160, align 8, !dbg !1269
  %inc161 = add i32 %138, 1, !dbg !1269
  store i32 %inc161, i32* %pending160, align 8, !dbg !1269
  %idxprom162 = zext i32 %138 to i64, !dbg !1269
  %139 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1269
  %pending_buf163 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %139, i32 0, i32 2, !dbg !1269
  %140 = load i8*, i8** %pending_buf163, align 8, !dbg !1269
  %arrayidx164 = getelementptr inbounds i8, i8* %140, i64 %idxprom162, !dbg !1269
  store i8 %conv159, i8* %arrayidx164, align 1, !dbg !1269
  %141 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1271
  %gzhead165 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %141, i32 0, i32 7, !dbg !1271
  %142 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead165, align 8, !dbg !1271
  %os = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %142, i32 0, i32 3, !dbg !1271
  %143 = load i32, i32* %os, align 4, !dbg !1271
  %and166 = and i32 %143, 255, !dbg !1271
  %conv167 = trunc i32 %and166 to i8, !dbg !1271
  %144 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1271
  %pending168 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %144, i32 0, i32 5, !dbg !1271
  %145 = load i32, i32* %pending168, align 8, !dbg !1271
  %inc169 = add i32 %145, 1, !dbg !1271
  store i32 %inc169, i32* %pending168, align 8, !dbg !1271
  %idxprom170 = zext i32 %145 to i64, !dbg !1271
  %146 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1271
  %pending_buf171 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %146, i32 0, i32 2, !dbg !1271
  %147 = load i8*, i8** %pending_buf171, align 8, !dbg !1271
  %arrayidx172 = getelementptr inbounds i8, i8* %147, i64 %idxprom170, !dbg !1271
  store i8 %conv167, i8* %arrayidx172, align 1, !dbg !1271
  %148 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1273
  %gzhead173 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %148, i32 0, i32 7, !dbg !1275
  %149 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead173, align 8, !dbg !1275
  %extra174 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %149, i32 0, i32 4, !dbg !1276
  %150 = load i8*, i8** %extra174, align 8, !dbg !1276
  %cmp175 = icmp ne i8* %150, null, !dbg !1277
  br i1 %cmp175, label %if.then177, label %if.end196, !dbg !1278

if.then177:                                       ; preds = %cond.end157
  %151 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1279
  %gzhead178 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %151, i32 0, i32 7, !dbg !1279
  %152 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead178, align 8, !dbg !1279
  %extra_len = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %152, i32 0, i32 5, !dbg !1279
  %153 = load i32, i32* %extra_len, align 8, !dbg !1279
  %and179 = and i32 %153, 255, !dbg !1279
  %conv180 = trunc i32 %and179 to i8, !dbg !1279
  %154 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1279
  %pending181 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %154, i32 0, i32 5, !dbg !1279
  %155 = load i32, i32* %pending181, align 8, !dbg !1279
  %inc182 = add i32 %155, 1, !dbg !1279
  store i32 %inc182, i32* %pending181, align 8, !dbg !1279
  %idxprom183 = zext i32 %155 to i64, !dbg !1279
  %156 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1279
  %pending_buf184 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %156, i32 0, i32 2, !dbg !1279
  %157 = load i8*, i8** %pending_buf184, align 8, !dbg !1279
  %arrayidx185 = getelementptr inbounds i8, i8* %157, i64 %idxprom183, !dbg !1279
  store i8 %conv180, i8* %arrayidx185, align 1, !dbg !1279
  %158 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1282
  %gzhead186 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %158, i32 0, i32 7, !dbg !1282
  %159 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead186, align 8, !dbg !1282
  %extra_len187 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %159, i32 0, i32 5, !dbg !1282
  %160 = load i32, i32* %extra_len187, align 8, !dbg !1282
  %shr188 = lshr i32 %160, 8, !dbg !1282
  %and189 = and i32 %shr188, 255, !dbg !1282
  %conv190 = trunc i32 %and189 to i8, !dbg !1282
  %161 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1282
  %pending191 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %161, i32 0, i32 5, !dbg !1282
  %162 = load i32, i32* %pending191, align 8, !dbg !1282
  %inc192 = add i32 %162, 1, !dbg !1282
  store i32 %inc192, i32* %pending191, align 8, !dbg !1282
  %idxprom193 = zext i32 %162 to i64, !dbg !1282
  %163 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1282
  %pending_buf194 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %163, i32 0, i32 2, !dbg !1282
  %164 = load i8*, i8** %pending_buf194, align 8, !dbg !1282
  %arrayidx195 = getelementptr inbounds i8, i8* %164, i64 %idxprom193, !dbg !1282
  store i8 %conv190, i8* %arrayidx195, align 1, !dbg !1282
  br label %if.end196, !dbg !1284

if.end196:                                        ; preds = %if.then177, %cond.end157
  %165 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1285
  %gzhead197 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %165, i32 0, i32 7, !dbg !1287
  %166 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead197, align 8, !dbg !1287
  %hcrc198 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %166, i32 0, i32 11, !dbg !1288
  %167 = load i32, i32* %hcrc198, align 4, !dbg !1288
  %tobool199 = icmp ne i32 %167, 0, !dbg !1285
  br i1 %tobool199, label %if.then200, label %if.end206, !dbg !1289

if.then200:                                       ; preds = %if.end196
  %168 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1290
  %adler201 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %168, i32 0, i32 12, !dbg !1291
  %169 = load i64, i64* %adler201, align 8, !dbg !1291
  %170 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1292
  %pending_buf202 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %170, i32 0, i32 2, !dbg !1293
  %171 = load i8*, i8** %pending_buf202, align 8, !dbg !1293
  %172 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1294
  %pending203 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %172, i32 0, i32 5, !dbg !1295
  %173 = load i32, i32* %pending203, align 8, !dbg !1295
  %call204 = call i64 @cm_zlib_crc32(i64 %169, i8* %171, i32 %173), !dbg !1296
  %174 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1297
  %adler205 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %174, i32 0, i32 12, !dbg !1298
  store i64 %call204, i64* %adler205, align 8, !dbg !1299
  br label %if.end206, !dbg !1297

if.end206:                                        ; preds = %if.then200, %if.end196
  %175 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1300
  %gzindex = getelementptr inbounds %struct.internal_state, %struct.internal_state* %175, i32 0, i32 8, !dbg !1301
  store i32 0, i32* %gzindex, align 8, !dbg !1302
  %176 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1303
  %status207 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %176, i32 0, i32 1, !dbg !1304
  store i32 69, i32* %status207, align 8, !dbg !1305
  br label %if.end208

if.end208:                                        ; preds = %if.end206, %cond.end
  br label %if.end256, !dbg !1306

if.else209:                                       ; preds = %if.then25
  call void @llvm.dbg.declare(metadata i32* %header, metadata !1307, metadata !277), !dbg !1309
  %177 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1310
  %w_bits = getelementptr inbounds %struct.internal_state, %struct.internal_state* %177, i32 0, i32 12, !dbg !1311
  %178 = load i32, i32* %w_bits, align 8, !dbg !1311
  %sub = sub i32 %178, 8, !dbg !1312
  %shl = shl i32 %sub, 4, !dbg !1313
  %add210 = add i32 8, %shl, !dbg !1314
  %shl211 = shl i32 %add210, 8, !dbg !1315
  store i32 %shl211, i32* %header, align 4, !dbg !1309
  call void @llvm.dbg.declare(metadata i32* %level_flags, metadata !1316, metadata !277), !dbg !1317
  %179 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1318
  %strategy212 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %179, i32 0, i32 34, !dbg !1320
  %180 = load i32, i32* %strategy212, align 8, !dbg !1320
  %cmp213 = icmp sge i32 %180, 2, !dbg !1321
  br i1 %cmp213, label %if.then219, label %lor.lhs.false215, !dbg !1322

lor.lhs.false215:                                 ; preds = %if.else209
  %181 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1323
  %level216 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %181, i32 0, i32 33, !dbg !1325
  %182 = load i32, i32* %level216, align 4, !dbg !1325
  %cmp217 = icmp slt i32 %182, 2, !dbg !1326
  br i1 %cmp217, label %if.then219, label %if.else220, !dbg !1327

if.then219:                                       ; preds = %lor.lhs.false215, %if.else209
  store i32 0, i32* %level_flags, align 4, !dbg !1328
  br label %if.end233, !dbg !1329

if.else220:                                       ; preds = %lor.lhs.false215
  %183 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1330
  %level221 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %183, i32 0, i32 33, !dbg !1332
  %184 = load i32, i32* %level221, align 4, !dbg !1332
  %cmp222 = icmp slt i32 %184, 6, !dbg !1333
  br i1 %cmp222, label %if.then224, label %if.else225, !dbg !1334

if.then224:                                       ; preds = %if.else220
  store i32 1, i32* %level_flags, align 4, !dbg !1335
  br label %if.end232, !dbg !1336

if.else225:                                       ; preds = %if.else220
  %185 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1337
  %level226 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %185, i32 0, i32 33, !dbg !1339
  %186 = load i32, i32* %level226, align 4, !dbg !1339
  %cmp227 = icmp eq i32 %186, 6, !dbg !1340
  br i1 %cmp227, label %if.then229, label %if.else230, !dbg !1341

if.then229:                                       ; preds = %if.else225
  store i32 2, i32* %level_flags, align 4, !dbg !1342
  br label %if.end231, !dbg !1343

if.else230:                                       ; preds = %if.else225
  store i32 3, i32* %level_flags, align 4, !dbg !1344
  br label %if.end231

if.end231:                                        ; preds = %if.else230, %if.then229
  br label %if.end232

if.end232:                                        ; preds = %if.end231, %if.then224
  br label %if.end233

if.end233:                                        ; preds = %if.end232, %if.then219
  %187 = load i32, i32* %level_flags, align 4, !dbg !1345
  %shl234 = shl i32 %187, 6, !dbg !1346
  %188 = load i32, i32* %header, align 4, !dbg !1347
  %or = or i32 %188, %shl234, !dbg !1347
  store i32 %or, i32* %header, align 4, !dbg !1347
  %189 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1348
  %strstart = getelementptr inbounds %struct.internal_state, %struct.internal_state* %189, i32 0, i32 27, !dbg !1350
  %190 = load i32, i32* %strstart, align 4, !dbg !1350
  %cmp235 = icmp ne i32 %190, 0, !dbg !1351
  br i1 %cmp235, label %if.then237, label %if.end239, !dbg !1352

if.then237:                                       ; preds = %if.end233
  %191 = load i32, i32* %header, align 4, !dbg !1353
  %or238 = or i32 %191, 32, !dbg !1353
  store i32 %or238, i32* %header, align 4, !dbg !1353
  br label %if.end239, !dbg !1355

if.end239:                                        ; preds = %if.then237, %if.end233
  %192 = load i32, i32* %header, align 4, !dbg !1356
  %rem = urem i32 %192, 31, !dbg !1357
  %sub240 = sub i32 31, %rem, !dbg !1358
  %193 = load i32, i32* %header, align 4, !dbg !1359
  %add241 = add i32 %193, %sub240, !dbg !1359
  store i32 %add241, i32* %header, align 4, !dbg !1359
  %194 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1360
  %status242 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %194, i32 0, i32 1, !dbg !1361
  store i32 113, i32* %status242, align 8, !dbg !1362
  %195 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1363
  %196 = load i32, i32* %header, align 4, !dbg !1364
  call void @putShortMSB(%struct.internal_state* %195, i32 %196), !dbg !1365
  %197 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1366
  %strstart243 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %197, i32 0, i32 27, !dbg !1368
  %198 = load i32, i32* %strstart243, align 4, !dbg !1368
  %cmp244 = icmp ne i32 %198, 0, !dbg !1369
  br i1 %cmp244, label %if.then246, label %if.end253, !dbg !1370

if.then246:                                       ; preds = %if.end239
  %199 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1371
  %200 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1373
  %adler247 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %200, i32 0, i32 12, !dbg !1374
  %201 = load i64, i64* %adler247, align 8, !dbg !1374
  %shr248 = lshr i64 %201, 16, !dbg !1375
  %conv249 = trunc i64 %shr248 to i32, !dbg !1376
  call void @putShortMSB(%struct.internal_state* %199, i32 %conv249), !dbg !1377
  %202 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1378
  %203 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1379
  %adler250 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %203, i32 0, i32 12, !dbg !1380
  %204 = load i64, i64* %adler250, align 8, !dbg !1380
  %and251 = and i64 %204, 65535, !dbg !1381
  %conv252 = trunc i64 %and251 to i32, !dbg !1382
  call void @putShortMSB(%struct.internal_state* %202, i32 %conv252), !dbg !1383
  br label %if.end253, !dbg !1384

if.end253:                                        ; preds = %if.then246, %if.end239
  %call254 = call i64 @cm_zlib_adler32(i64 0, i8* null, i32 0), !dbg !1385
  %205 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1386
  %adler255 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %205, i32 0, i32 12, !dbg !1387
  store i64 %call254, i64* %adler255, align 8, !dbg !1388
  br label %if.end256

if.end256:                                        ; preds = %if.end253, %if.end208
  br label %if.end257, !dbg !1389

if.end257:                                        ; preds = %if.end256, %if.end20
  %206 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1390
  %status258 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %206, i32 0, i32 1, !dbg !1392
  %207 = load i32, i32* %status258, align 8, !dbg !1392
  %cmp259 = icmp eq i32 %207, 69, !dbg !1393
  br i1 %cmp259, label %if.then261, label %if.end344, !dbg !1394

if.then261:                                       ; preds = %if.end257
  %208 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1395
  %gzhead262 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %208, i32 0, i32 7, !dbg !1398
  %209 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead262, align 8, !dbg !1398
  %extra263 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %209, i32 0, i32 4, !dbg !1399
  %210 = load i8*, i8** %extra263, align 8, !dbg !1399
  %cmp264 = icmp ne i8* %210, null, !dbg !1400
  br i1 %cmp264, label %if.then266, label %if.else341, !dbg !1401

if.then266:                                       ; preds = %if.then261
  call void @llvm.dbg.declare(metadata i32* %beg, metadata !1402, metadata !277), !dbg !1404
  %211 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1405
  %pending267 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %211, i32 0, i32 5, !dbg !1406
  %212 = load i32, i32* %pending267, align 8, !dbg !1406
  store i32 %212, i32* %beg, align 4, !dbg !1404
  br label %while.cond, !dbg !1407

while.cond:                                       ; preds = %if.end302, %if.then266
  %213 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1408
  %gzindex268 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %213, i32 0, i32 8, !dbg !1410
  %214 = load i32, i32* %gzindex268, align 8, !dbg !1410
  %215 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1411
  %gzhead269 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %215, i32 0, i32 7, !dbg !1412
  %216 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead269, align 8, !dbg !1412
  %extra_len270 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %216, i32 0, i32 5, !dbg !1413
  %217 = load i32, i32* %extra_len270, align 8, !dbg !1413
  %and271 = and i32 %217, 65535, !dbg !1414
  %cmp272 = icmp ult i32 %214, %and271, !dbg !1415
  br i1 %cmp272, label %while.body, label %while.end, !dbg !1416

while.body:                                       ; preds = %while.cond
  %218 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1417
  %pending274 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %218, i32 0, i32 5, !dbg !1420
  %219 = load i32, i32* %pending274, align 8, !dbg !1420
  %conv275 = zext i32 %219 to i64, !dbg !1417
  %220 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1421
  %pending_buf_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %220, i32 0, i32 3, !dbg !1422
  %221 = load i64, i64* %pending_buf_size, align 8, !dbg !1422
  %cmp276 = icmp eq i64 %conv275, %221, !dbg !1423
  br i1 %cmp276, label %if.then278, label %if.end302, !dbg !1424

if.then278:                                       ; preds = %while.body
  %222 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1425
  %gzhead279 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %222, i32 0, i32 7, !dbg !1428
  %223 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead279, align 8, !dbg !1428
  %hcrc280 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %223, i32 0, i32 11, !dbg !1429
  %224 = load i32, i32* %hcrc280, align 4, !dbg !1429
  %tobool281 = icmp ne i32 %224, 0, !dbg !1425
  br i1 %tobool281, label %land.lhs.true282, label %if.end293, !dbg !1430

land.lhs.true282:                                 ; preds = %if.then278
  %225 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1431
  %pending283 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %225, i32 0, i32 5, !dbg !1433
  %226 = load i32, i32* %pending283, align 8, !dbg !1433
  %227 = load i32, i32* %beg, align 4, !dbg !1434
  %cmp284 = icmp ugt i32 %226, %227, !dbg !1435
  br i1 %cmp284, label %if.then286, label %if.end293, !dbg !1436

if.then286:                                       ; preds = %land.lhs.true282
  %228 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1437
  %adler287 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %228, i32 0, i32 12, !dbg !1438
  %229 = load i64, i64* %adler287, align 8, !dbg !1438
  %230 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1439
  %pending_buf288 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %230, i32 0, i32 2, !dbg !1440
  %231 = load i8*, i8** %pending_buf288, align 8, !dbg !1440
  %232 = load i32, i32* %beg, align 4, !dbg !1441
  %idx.ext = zext i32 %232 to i64, !dbg !1442
  %add.ptr = getelementptr inbounds i8, i8* %231, i64 %idx.ext, !dbg !1442
  %233 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1443
  %pending289 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %233, i32 0, i32 5, !dbg !1444
  %234 = load i32, i32* %pending289, align 8, !dbg !1444
  %235 = load i32, i32* %beg, align 4, !dbg !1445
  %sub290 = sub i32 %234, %235, !dbg !1446
  %call291 = call i64 @cm_zlib_crc32(i64 %229, i8* %add.ptr, i32 %sub290), !dbg !1447
  %236 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1448
  %adler292 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %236, i32 0, i32 12, !dbg !1449
  store i64 %call291, i64* %adler292, align 8, !dbg !1450
  br label %if.end293, !dbg !1448

if.end293:                                        ; preds = %if.then286, %land.lhs.true282, %if.then278
  %237 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1451
  call void @flush_pending(%struct.z_stream_s* %237), !dbg !1452
  %238 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1453
  %pending294 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %238, i32 0, i32 5, !dbg !1454
  %239 = load i32, i32* %pending294, align 8, !dbg !1454
  store i32 %239, i32* %beg, align 4, !dbg !1455
  %240 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1456
  %pending295 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %240, i32 0, i32 5, !dbg !1458
  %241 = load i32, i32* %pending295, align 8, !dbg !1458
  %conv296 = zext i32 %241 to i64, !dbg !1456
  %242 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1459
  %pending_buf_size297 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %242, i32 0, i32 3, !dbg !1460
  %243 = load i64, i64* %pending_buf_size297, align 8, !dbg !1460
  %cmp298 = icmp eq i64 %conv296, %243, !dbg !1461
  br i1 %cmp298, label %if.then300, label %if.end301, !dbg !1462

if.then300:                                       ; preds = %if.end293
  br label %while.end, !dbg !1463

if.end301:                                        ; preds = %if.end293
  br label %if.end302, !dbg !1464

if.end302:                                        ; preds = %if.end301, %while.body
  %244 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1465
  %gzindex303 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %244, i32 0, i32 8, !dbg !1465
  %245 = load i32, i32* %gzindex303, align 8, !dbg !1465
  %idxprom304 = zext i32 %245 to i64, !dbg !1465
  %246 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1465
  %gzhead305 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %246, i32 0, i32 7, !dbg !1465
  %247 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead305, align 8, !dbg !1465
  %extra306 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %247, i32 0, i32 4, !dbg !1465
  %248 = load i8*, i8** %extra306, align 8, !dbg !1465
  %arrayidx307 = getelementptr inbounds i8, i8* %248, i64 %idxprom304, !dbg !1465
  %249 = load i8, i8* %arrayidx307, align 1, !dbg !1465
  %250 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1465
  %pending308 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %250, i32 0, i32 5, !dbg !1465
  %251 = load i32, i32* %pending308, align 8, !dbg !1465
  %inc309 = add i32 %251, 1, !dbg !1465
  store i32 %inc309, i32* %pending308, align 8, !dbg !1465
  %idxprom310 = zext i32 %251 to i64, !dbg !1465
  %252 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1465
  %pending_buf311 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %252, i32 0, i32 2, !dbg !1465
  %253 = load i8*, i8** %pending_buf311, align 8, !dbg !1465
  %arrayidx312 = getelementptr inbounds i8, i8* %253, i64 %idxprom310, !dbg !1465
  store i8 %249, i8* %arrayidx312, align 1, !dbg !1465
  %254 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1467
  %gzindex313 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %254, i32 0, i32 8, !dbg !1468
  %255 = load i32, i32* %gzindex313, align 8, !dbg !1469
  %inc314 = add i32 %255, 1, !dbg !1469
  store i32 %inc314, i32* %gzindex313, align 8, !dbg !1469
  br label %while.cond, !dbg !1470

while.end:                                        ; preds = %if.then300, %while.cond
  %256 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1472
  %gzhead315 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %256, i32 0, i32 7, !dbg !1474
  %257 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead315, align 8, !dbg !1474
  %hcrc316 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %257, i32 0, i32 11, !dbg !1475
  %258 = load i32, i32* %hcrc316, align 4, !dbg !1475
  %tobool317 = icmp ne i32 %258, 0, !dbg !1472
  br i1 %tobool317, label %land.lhs.true318, label %if.end331, !dbg !1476

land.lhs.true318:                                 ; preds = %while.end
  %259 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1477
  %pending319 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %259, i32 0, i32 5, !dbg !1479
  %260 = load i32, i32* %pending319, align 8, !dbg !1479
  %261 = load i32, i32* %beg, align 4, !dbg !1480
  %cmp320 = icmp ugt i32 %260, %261, !dbg !1481
  br i1 %cmp320, label %if.then322, label %if.end331, !dbg !1482

if.then322:                                       ; preds = %land.lhs.true318
  %262 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1483
  %adler323 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %262, i32 0, i32 12, !dbg !1484
  %263 = load i64, i64* %adler323, align 8, !dbg !1484
  %264 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1485
  %pending_buf324 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %264, i32 0, i32 2, !dbg !1486
  %265 = load i8*, i8** %pending_buf324, align 8, !dbg !1486
  %266 = load i32, i32* %beg, align 4, !dbg !1487
  %idx.ext325 = zext i32 %266 to i64, !dbg !1488
  %add.ptr326 = getelementptr inbounds i8, i8* %265, i64 %idx.ext325, !dbg !1488
  %267 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1489
  %pending327 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %267, i32 0, i32 5, !dbg !1490
  %268 = load i32, i32* %pending327, align 8, !dbg !1490
  %269 = load i32, i32* %beg, align 4, !dbg !1491
  %sub328 = sub i32 %268, %269, !dbg !1492
  %call329 = call i64 @cm_zlib_crc32(i64 %263, i8* %add.ptr326, i32 %sub328), !dbg !1493
  %270 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1494
  %adler330 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %270, i32 0, i32 12, !dbg !1495
  store i64 %call329, i64* %adler330, align 8, !dbg !1496
  br label %if.end331, !dbg !1494

if.end331:                                        ; preds = %if.then322, %land.lhs.true318, %while.end
  %271 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1497
  %gzindex332 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %271, i32 0, i32 8, !dbg !1499
  %272 = load i32, i32* %gzindex332, align 8, !dbg !1499
  %273 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1500
  %gzhead333 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %273, i32 0, i32 7, !dbg !1501
  %274 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead333, align 8, !dbg !1501
  %extra_len334 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %274, i32 0, i32 5, !dbg !1502
  %275 = load i32, i32* %extra_len334, align 8, !dbg !1502
  %cmp335 = icmp eq i32 %272, %275, !dbg !1503
  br i1 %cmp335, label %if.then337, label %if.end340, !dbg !1504

if.then337:                                       ; preds = %if.end331
  %276 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1505
  %gzindex338 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %276, i32 0, i32 8, !dbg !1507
  store i32 0, i32* %gzindex338, align 8, !dbg !1508
  %277 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1509
  %status339 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %277, i32 0, i32 1, !dbg !1510
  store i32 73, i32* %status339, align 8, !dbg !1511
  br label %if.end340, !dbg !1512

if.end340:                                        ; preds = %if.then337, %if.end331
  br label %if.end343, !dbg !1513

if.else341:                                       ; preds = %if.then261
  %278 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1514
  %status342 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %278, i32 0, i32 1, !dbg !1515
  store i32 73, i32* %status342, align 8, !dbg !1516
  br label %if.end343

if.end343:                                        ; preds = %if.else341, %if.end340
  br label %if.end344, !dbg !1517

if.end344:                                        ; preds = %if.end343, %if.end257
  %279 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1518
  %status345 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %279, i32 0, i32 1, !dbg !1520
  %280 = load i32, i32* %status345, align 8, !dbg !1520
  %cmp346 = icmp eq i32 %280, 73, !dbg !1521
  br i1 %cmp346, label %if.then348, label %if.end429, !dbg !1522

if.then348:                                       ; preds = %if.end344
  %281 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1523
  %gzhead349 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %281, i32 0, i32 7, !dbg !1526
  %282 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead349, align 8, !dbg !1526
  %name350 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %282, i32 0, i32 7, !dbg !1527
  %283 = load i8*, i8** %name350, align 8, !dbg !1527
  %cmp351 = icmp ne i8* %283, null, !dbg !1528
  br i1 %cmp351, label %if.then353, label %if.else426, !dbg !1529

if.then353:                                       ; preds = %if.then348
  call void @llvm.dbg.declare(metadata i32* %beg354, metadata !1530, metadata !277), !dbg !1532
  %284 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1533
  %pending355 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %284, i32 0, i32 5, !dbg !1534
  %285 = load i32, i32* %pending355, align 8, !dbg !1534
  store i32 %285, i32* %beg354, align 4, !dbg !1532
  call void @llvm.dbg.declare(metadata i32* %val, metadata !1535, metadata !277), !dbg !1536
  br label %do.body, !dbg !1537

do.body:                                          ; preds = %do.cond, %if.then353
  %286 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1538
  %pending356 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %286, i32 0, i32 5, !dbg !1541
  %287 = load i32, i32* %pending356, align 8, !dbg !1541
  %conv357 = zext i32 %287 to i64, !dbg !1538
  %288 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1542
  %pending_buf_size358 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %288, i32 0, i32 3, !dbg !1543
  %289 = load i64, i64* %pending_buf_size358, align 8, !dbg !1543
  %cmp359 = icmp eq i64 %conv357, %289, !dbg !1544
  br i1 %cmp359, label %if.then361, label %if.end387, !dbg !1545

if.then361:                                       ; preds = %do.body
  %290 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1546
  %gzhead362 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %290, i32 0, i32 7, !dbg !1549
  %291 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead362, align 8, !dbg !1549
  %hcrc363 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %291, i32 0, i32 11, !dbg !1550
  %292 = load i32, i32* %hcrc363, align 4, !dbg !1550
  %tobool364 = icmp ne i32 %292, 0, !dbg !1546
  br i1 %tobool364, label %land.lhs.true365, label %if.end378, !dbg !1551

land.lhs.true365:                                 ; preds = %if.then361
  %293 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1552
  %pending366 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %293, i32 0, i32 5, !dbg !1554
  %294 = load i32, i32* %pending366, align 8, !dbg !1554
  %295 = load i32, i32* %beg354, align 4, !dbg !1555
  %cmp367 = icmp ugt i32 %294, %295, !dbg !1556
  br i1 %cmp367, label %if.then369, label %if.end378, !dbg !1557

if.then369:                                       ; preds = %land.lhs.true365
  %296 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1558
  %adler370 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %296, i32 0, i32 12, !dbg !1559
  %297 = load i64, i64* %adler370, align 8, !dbg !1559
  %298 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1560
  %pending_buf371 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %298, i32 0, i32 2, !dbg !1561
  %299 = load i8*, i8** %pending_buf371, align 8, !dbg !1561
  %300 = load i32, i32* %beg354, align 4, !dbg !1562
  %idx.ext372 = zext i32 %300 to i64, !dbg !1563
  %add.ptr373 = getelementptr inbounds i8, i8* %299, i64 %idx.ext372, !dbg !1563
  %301 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1564
  %pending374 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %301, i32 0, i32 5, !dbg !1565
  %302 = load i32, i32* %pending374, align 8, !dbg !1565
  %303 = load i32, i32* %beg354, align 4, !dbg !1566
  %sub375 = sub i32 %302, %303, !dbg !1567
  %call376 = call i64 @cm_zlib_crc32(i64 %297, i8* %add.ptr373, i32 %sub375), !dbg !1568
  %304 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1569
  %adler377 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %304, i32 0, i32 12, !dbg !1570
  store i64 %call376, i64* %adler377, align 8, !dbg !1571
  br label %if.end378, !dbg !1569

if.end378:                                        ; preds = %if.then369, %land.lhs.true365, %if.then361
  %305 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1572
  call void @flush_pending(%struct.z_stream_s* %305), !dbg !1573
  %306 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1574
  %pending379 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %306, i32 0, i32 5, !dbg !1575
  %307 = load i32, i32* %pending379, align 8, !dbg !1575
  store i32 %307, i32* %beg354, align 4, !dbg !1576
  %308 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1577
  %pending380 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %308, i32 0, i32 5, !dbg !1579
  %309 = load i32, i32* %pending380, align 8, !dbg !1579
  %conv381 = zext i32 %309 to i64, !dbg !1577
  %310 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1580
  %pending_buf_size382 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %310, i32 0, i32 3, !dbg !1581
  %311 = load i64, i64* %pending_buf_size382, align 8, !dbg !1581
  %cmp383 = icmp eq i64 %conv381, %311, !dbg !1582
  br i1 %cmp383, label %if.then385, label %if.end386, !dbg !1583

if.then385:                                       ; preds = %if.end378
  store i32 1, i32* %val, align 4, !dbg !1584
  br label %do.end, !dbg !1586

if.end386:                                        ; preds = %if.end378
  br label %if.end387, !dbg !1587

if.end387:                                        ; preds = %if.end386, %do.body
  %312 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1588
  %gzindex388 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %312, i32 0, i32 8, !dbg !1589
  %313 = load i32, i32* %gzindex388, align 8, !dbg !1590
  %inc389 = add i32 %313, 1, !dbg !1590
  store i32 %inc389, i32* %gzindex388, align 8, !dbg !1590
  %idxprom390 = zext i32 %313 to i64, !dbg !1591
  %314 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1591
  %gzhead391 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %314, i32 0, i32 7, !dbg !1592
  %315 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead391, align 8, !dbg !1592
  %name392 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %315, i32 0, i32 7, !dbg !1593
  %316 = load i8*, i8** %name392, align 8, !dbg !1593
  %arrayidx393 = getelementptr inbounds i8, i8* %316, i64 %idxprom390, !dbg !1591
  %317 = load i8, i8* %arrayidx393, align 1, !dbg !1591
  %conv394 = zext i8 %317 to i32, !dbg !1591
  store i32 %conv394, i32* %val, align 4, !dbg !1594
  %318 = load i32, i32* %val, align 4, !dbg !1595
  %conv395 = trunc i32 %318 to i8, !dbg !1595
  %319 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1595
  %pending396 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %319, i32 0, i32 5, !dbg !1595
  %320 = load i32, i32* %pending396, align 8, !dbg !1595
  %inc397 = add i32 %320, 1, !dbg !1595
  store i32 %inc397, i32* %pending396, align 8, !dbg !1595
  %idxprom398 = zext i32 %320 to i64, !dbg !1595
  %321 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1595
  %pending_buf399 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %321, i32 0, i32 2, !dbg !1595
  %322 = load i8*, i8** %pending_buf399, align 8, !dbg !1595
  %arrayidx400 = getelementptr inbounds i8, i8* %322, i64 %idxprom398, !dbg !1595
  store i8 %conv395, i8* %arrayidx400, align 1, !dbg !1595
  br label %do.cond, !dbg !1597

do.cond:                                          ; preds = %if.end387
  %323 = load i32, i32* %val, align 4, !dbg !1598
  %cmp401 = icmp ne i32 %323, 0, !dbg !1600
  br i1 %cmp401, label %do.body, label %do.end, !dbg !1601

do.end:                                           ; preds = %do.cond, %if.then385
  %324 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1602
  %gzhead403 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %324, i32 0, i32 7, !dbg !1604
  %325 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead403, align 8, !dbg !1604
  %hcrc404 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %325, i32 0, i32 11, !dbg !1605
  %326 = load i32, i32* %hcrc404, align 4, !dbg !1605
  %tobool405 = icmp ne i32 %326, 0, !dbg !1602
  br i1 %tobool405, label %land.lhs.true406, label %if.end419, !dbg !1606

land.lhs.true406:                                 ; preds = %do.end
  %327 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1607
  %pending407 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %327, i32 0, i32 5, !dbg !1609
  %328 = load i32, i32* %pending407, align 8, !dbg !1609
  %329 = load i32, i32* %beg354, align 4, !dbg !1610
  %cmp408 = icmp ugt i32 %328, %329, !dbg !1611
  br i1 %cmp408, label %if.then410, label %if.end419, !dbg !1612

if.then410:                                       ; preds = %land.lhs.true406
  %330 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1613
  %adler411 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %330, i32 0, i32 12, !dbg !1614
  %331 = load i64, i64* %adler411, align 8, !dbg !1614
  %332 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1615
  %pending_buf412 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %332, i32 0, i32 2, !dbg !1616
  %333 = load i8*, i8** %pending_buf412, align 8, !dbg !1616
  %334 = load i32, i32* %beg354, align 4, !dbg !1617
  %idx.ext413 = zext i32 %334 to i64, !dbg !1618
  %add.ptr414 = getelementptr inbounds i8, i8* %333, i64 %idx.ext413, !dbg !1618
  %335 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1619
  %pending415 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %335, i32 0, i32 5, !dbg !1620
  %336 = load i32, i32* %pending415, align 8, !dbg !1620
  %337 = load i32, i32* %beg354, align 4, !dbg !1621
  %sub416 = sub i32 %336, %337, !dbg !1622
  %call417 = call i64 @cm_zlib_crc32(i64 %331, i8* %add.ptr414, i32 %sub416), !dbg !1623
  %338 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1624
  %adler418 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %338, i32 0, i32 12, !dbg !1625
  store i64 %call417, i64* %adler418, align 8, !dbg !1626
  br label %if.end419, !dbg !1624

if.end419:                                        ; preds = %if.then410, %land.lhs.true406, %do.end
  %339 = load i32, i32* %val, align 4, !dbg !1627
  %cmp420 = icmp eq i32 %339, 0, !dbg !1629
  br i1 %cmp420, label %if.then422, label %if.end425, !dbg !1630

if.then422:                                       ; preds = %if.end419
  %340 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1631
  %gzindex423 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %340, i32 0, i32 8, !dbg !1633
  store i32 0, i32* %gzindex423, align 8, !dbg !1634
  %341 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1635
  %status424 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %341, i32 0, i32 1, !dbg !1636
  store i32 91, i32* %status424, align 8, !dbg !1637
  br label %if.end425, !dbg !1638

if.end425:                                        ; preds = %if.then422, %if.end419
  br label %if.end428, !dbg !1639

if.else426:                                       ; preds = %if.then348
  %342 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1640
  %status427 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %342, i32 0, i32 1, !dbg !1641
  store i32 91, i32* %status427, align 8, !dbg !1642
  br label %if.end428

if.end428:                                        ; preds = %if.else426, %if.end425
  br label %if.end429, !dbg !1643

if.end429:                                        ; preds = %if.end428, %if.end344
  %343 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1644
  %status430 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %343, i32 0, i32 1, !dbg !1646
  %344 = load i32, i32* %status430, align 8, !dbg !1646
  %cmp431 = icmp eq i32 %344, 91, !dbg !1647
  br i1 %cmp431, label %if.then433, label %if.end517, !dbg !1648

if.then433:                                       ; preds = %if.end429
  %345 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1649
  %gzhead434 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %345, i32 0, i32 7, !dbg !1652
  %346 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead434, align 8, !dbg !1652
  %comment435 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %346, i32 0, i32 9, !dbg !1653
  %347 = load i8*, i8** %comment435, align 8, !dbg !1653
  %cmp436 = icmp ne i8* %347, null, !dbg !1654
  br i1 %cmp436, label %if.then438, label %if.else514, !dbg !1655

if.then438:                                       ; preds = %if.then433
  call void @llvm.dbg.declare(metadata i32* %beg439, metadata !1656, metadata !277), !dbg !1658
  %348 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1659
  %pending440 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %348, i32 0, i32 5, !dbg !1660
  %349 = load i32, i32* %pending440, align 8, !dbg !1660
  store i32 %349, i32* %beg439, align 4, !dbg !1658
  call void @llvm.dbg.declare(metadata i32* %val441, metadata !1661, metadata !277), !dbg !1662
  br label %do.body442, !dbg !1663

do.body442:                                       ; preds = %do.cond488, %if.then438
  %350 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1664
  %pending443 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %350, i32 0, i32 5, !dbg !1667
  %351 = load i32, i32* %pending443, align 8, !dbg !1667
  %conv444 = zext i32 %351 to i64, !dbg !1664
  %352 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1668
  %pending_buf_size445 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %352, i32 0, i32 3, !dbg !1669
  %353 = load i64, i64* %pending_buf_size445, align 8, !dbg !1669
  %cmp446 = icmp eq i64 %conv444, %353, !dbg !1670
  br i1 %cmp446, label %if.then448, label %if.end474, !dbg !1671

if.then448:                                       ; preds = %do.body442
  %354 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1672
  %gzhead449 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %354, i32 0, i32 7, !dbg !1675
  %355 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead449, align 8, !dbg !1675
  %hcrc450 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %355, i32 0, i32 11, !dbg !1676
  %356 = load i32, i32* %hcrc450, align 4, !dbg !1676
  %tobool451 = icmp ne i32 %356, 0, !dbg !1672
  br i1 %tobool451, label %land.lhs.true452, label %if.end465, !dbg !1677

land.lhs.true452:                                 ; preds = %if.then448
  %357 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1678
  %pending453 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %357, i32 0, i32 5, !dbg !1680
  %358 = load i32, i32* %pending453, align 8, !dbg !1680
  %359 = load i32, i32* %beg439, align 4, !dbg !1681
  %cmp454 = icmp ugt i32 %358, %359, !dbg !1682
  br i1 %cmp454, label %if.then456, label %if.end465, !dbg !1683

if.then456:                                       ; preds = %land.lhs.true452
  %360 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1684
  %adler457 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %360, i32 0, i32 12, !dbg !1685
  %361 = load i64, i64* %adler457, align 8, !dbg !1685
  %362 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1686
  %pending_buf458 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %362, i32 0, i32 2, !dbg !1687
  %363 = load i8*, i8** %pending_buf458, align 8, !dbg !1687
  %364 = load i32, i32* %beg439, align 4, !dbg !1688
  %idx.ext459 = zext i32 %364 to i64, !dbg !1689
  %add.ptr460 = getelementptr inbounds i8, i8* %363, i64 %idx.ext459, !dbg !1689
  %365 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1690
  %pending461 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %365, i32 0, i32 5, !dbg !1691
  %366 = load i32, i32* %pending461, align 8, !dbg !1691
  %367 = load i32, i32* %beg439, align 4, !dbg !1692
  %sub462 = sub i32 %366, %367, !dbg !1693
  %call463 = call i64 @cm_zlib_crc32(i64 %361, i8* %add.ptr460, i32 %sub462), !dbg !1694
  %368 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1695
  %adler464 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %368, i32 0, i32 12, !dbg !1696
  store i64 %call463, i64* %adler464, align 8, !dbg !1697
  br label %if.end465, !dbg !1695

if.end465:                                        ; preds = %if.then456, %land.lhs.true452, %if.then448
  %369 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1698
  call void @flush_pending(%struct.z_stream_s* %369), !dbg !1699
  %370 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1700
  %pending466 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %370, i32 0, i32 5, !dbg !1701
  %371 = load i32, i32* %pending466, align 8, !dbg !1701
  store i32 %371, i32* %beg439, align 4, !dbg !1702
  %372 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1703
  %pending467 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %372, i32 0, i32 5, !dbg !1705
  %373 = load i32, i32* %pending467, align 8, !dbg !1705
  %conv468 = zext i32 %373 to i64, !dbg !1703
  %374 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1706
  %pending_buf_size469 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %374, i32 0, i32 3, !dbg !1707
  %375 = load i64, i64* %pending_buf_size469, align 8, !dbg !1707
  %cmp470 = icmp eq i64 %conv468, %375, !dbg !1708
  br i1 %cmp470, label %if.then472, label %if.end473, !dbg !1709

if.then472:                                       ; preds = %if.end465
  store i32 1, i32* %val441, align 4, !dbg !1710
  br label %do.end491, !dbg !1712

if.end473:                                        ; preds = %if.end465
  br label %if.end474, !dbg !1713

if.end474:                                        ; preds = %if.end473, %do.body442
  %376 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1714
  %gzindex475 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %376, i32 0, i32 8, !dbg !1715
  %377 = load i32, i32* %gzindex475, align 8, !dbg !1716
  %inc476 = add i32 %377, 1, !dbg !1716
  store i32 %inc476, i32* %gzindex475, align 8, !dbg !1716
  %idxprom477 = zext i32 %377 to i64, !dbg !1717
  %378 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1717
  %gzhead478 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %378, i32 0, i32 7, !dbg !1718
  %379 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead478, align 8, !dbg !1718
  %comment479 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %379, i32 0, i32 9, !dbg !1719
  %380 = load i8*, i8** %comment479, align 8, !dbg !1719
  %arrayidx480 = getelementptr inbounds i8, i8* %380, i64 %idxprom477, !dbg !1717
  %381 = load i8, i8* %arrayidx480, align 1, !dbg !1717
  %conv481 = zext i8 %381 to i32, !dbg !1717
  store i32 %conv481, i32* %val441, align 4, !dbg !1720
  %382 = load i32, i32* %val441, align 4, !dbg !1721
  %conv482 = trunc i32 %382 to i8, !dbg !1721
  %383 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1721
  %pending483 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %383, i32 0, i32 5, !dbg !1721
  %384 = load i32, i32* %pending483, align 8, !dbg !1721
  %inc484 = add i32 %384, 1, !dbg !1721
  store i32 %inc484, i32* %pending483, align 8, !dbg !1721
  %idxprom485 = zext i32 %384 to i64, !dbg !1721
  %385 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1721
  %pending_buf486 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %385, i32 0, i32 2, !dbg !1721
  %386 = load i8*, i8** %pending_buf486, align 8, !dbg !1721
  %arrayidx487 = getelementptr inbounds i8, i8* %386, i64 %idxprom485, !dbg !1721
  store i8 %conv482, i8* %arrayidx487, align 1, !dbg !1721
  br label %do.cond488, !dbg !1723

do.cond488:                                       ; preds = %if.end474
  %387 = load i32, i32* %val441, align 4, !dbg !1724
  %cmp489 = icmp ne i32 %387, 0, !dbg !1726
  br i1 %cmp489, label %do.body442, label %do.end491, !dbg !1727

do.end491:                                        ; preds = %do.cond488, %if.then472
  %388 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1728
  %gzhead492 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %388, i32 0, i32 7, !dbg !1730
  %389 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead492, align 8, !dbg !1730
  %hcrc493 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %389, i32 0, i32 11, !dbg !1731
  %390 = load i32, i32* %hcrc493, align 4, !dbg !1731
  %tobool494 = icmp ne i32 %390, 0, !dbg !1728
  br i1 %tobool494, label %land.lhs.true495, label %if.end508, !dbg !1732

land.lhs.true495:                                 ; preds = %do.end491
  %391 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1733
  %pending496 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %391, i32 0, i32 5, !dbg !1735
  %392 = load i32, i32* %pending496, align 8, !dbg !1735
  %393 = load i32, i32* %beg439, align 4, !dbg !1736
  %cmp497 = icmp ugt i32 %392, %393, !dbg !1737
  br i1 %cmp497, label %if.then499, label %if.end508, !dbg !1738

if.then499:                                       ; preds = %land.lhs.true495
  %394 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1739
  %adler500 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %394, i32 0, i32 12, !dbg !1740
  %395 = load i64, i64* %adler500, align 8, !dbg !1740
  %396 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1741
  %pending_buf501 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %396, i32 0, i32 2, !dbg !1742
  %397 = load i8*, i8** %pending_buf501, align 8, !dbg !1742
  %398 = load i32, i32* %beg439, align 4, !dbg !1743
  %idx.ext502 = zext i32 %398 to i64, !dbg !1744
  %add.ptr503 = getelementptr inbounds i8, i8* %397, i64 %idx.ext502, !dbg !1744
  %399 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1745
  %pending504 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %399, i32 0, i32 5, !dbg !1746
  %400 = load i32, i32* %pending504, align 8, !dbg !1746
  %401 = load i32, i32* %beg439, align 4, !dbg !1747
  %sub505 = sub i32 %400, %401, !dbg !1748
  %call506 = call i64 @cm_zlib_crc32(i64 %395, i8* %add.ptr503, i32 %sub505), !dbg !1749
  %402 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1750
  %adler507 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %402, i32 0, i32 12, !dbg !1751
  store i64 %call506, i64* %adler507, align 8, !dbg !1752
  br label %if.end508, !dbg !1750

if.end508:                                        ; preds = %if.then499, %land.lhs.true495, %do.end491
  %403 = load i32, i32* %val441, align 4, !dbg !1753
  %cmp509 = icmp eq i32 %403, 0, !dbg !1755
  br i1 %cmp509, label %if.then511, label %if.end513, !dbg !1756

if.then511:                                       ; preds = %if.end508
  %404 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1757
  %status512 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %404, i32 0, i32 1, !dbg !1758
  store i32 103, i32* %status512, align 8, !dbg !1759
  br label %if.end513, !dbg !1757

if.end513:                                        ; preds = %if.then511, %if.end508
  br label %if.end516, !dbg !1760

if.else514:                                       ; preds = %if.then433
  %405 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1761
  %status515 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %405, i32 0, i32 1, !dbg !1762
  store i32 103, i32* %status515, align 8, !dbg !1763
  br label %if.end516

if.end516:                                        ; preds = %if.else514, %if.end513
  br label %if.end517, !dbg !1764

if.end517:                                        ; preds = %if.end516, %if.end429
  %406 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1765
  %status518 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %406, i32 0, i32 1, !dbg !1767
  %407 = load i32, i32* %status518, align 8, !dbg !1767
  %cmp519 = icmp eq i32 %407, 103, !dbg !1768
  br i1 %cmp519, label %if.then521, label %if.end565, !dbg !1769

if.then521:                                       ; preds = %if.end517
  %408 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1770
  %gzhead522 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %408, i32 0, i32 7, !dbg !1773
  %409 = load %struct.gz_header_s*, %struct.gz_header_s** %gzhead522, align 8, !dbg !1773
  %hcrc523 = getelementptr inbounds %struct.gz_header_s, %struct.gz_header_s* %409, i32 0, i32 11, !dbg !1774
  %410 = load i32, i32* %hcrc523, align 4, !dbg !1774
  %tobool524 = icmp ne i32 %410, 0, !dbg !1770
  br i1 %tobool524, label %if.then525, label %if.else562, !dbg !1775

if.then525:                                       ; preds = %if.then521
  %411 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1776
  %pending526 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %411, i32 0, i32 5, !dbg !1779
  %412 = load i32, i32* %pending526, align 8, !dbg !1779
  %add527 = add i32 %412, 2, !dbg !1780
  %conv528 = zext i32 %add527 to i64, !dbg !1776
  %413 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1781
  %pending_buf_size529 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %413, i32 0, i32 3, !dbg !1782
  %414 = load i64, i64* %pending_buf_size529, align 8, !dbg !1782
  %cmp530 = icmp ugt i64 %conv528, %414, !dbg !1783
  br i1 %cmp530, label %if.then532, label %if.end533, !dbg !1784

if.then532:                                       ; preds = %if.then525
  %415 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1785
  call void @flush_pending(%struct.z_stream_s* %415), !dbg !1786
  br label %if.end533, !dbg !1786

if.end533:                                        ; preds = %if.then532, %if.then525
  %416 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1787
  %pending534 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %416, i32 0, i32 5, !dbg !1789
  %417 = load i32, i32* %pending534, align 8, !dbg !1789
  %add535 = add i32 %417, 2, !dbg !1790
  %conv536 = zext i32 %add535 to i64, !dbg !1787
  %418 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1791
  %pending_buf_size537 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %418, i32 0, i32 3, !dbg !1792
  %419 = load i64, i64* %pending_buf_size537, align 8, !dbg !1792
  %cmp538 = icmp ule i64 %conv536, %419, !dbg !1793
  br i1 %cmp538, label %if.then540, label %if.end561, !dbg !1794

if.then540:                                       ; preds = %if.end533
  %420 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1795
  %adler541 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %420, i32 0, i32 12, !dbg !1795
  %421 = load i64, i64* %adler541, align 8, !dbg !1795
  %and542 = and i64 %421, 255, !dbg !1795
  %conv543 = trunc i64 %and542 to i8, !dbg !1795
  %422 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1795
  %pending544 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %422, i32 0, i32 5, !dbg !1795
  %423 = load i32, i32* %pending544, align 8, !dbg !1795
  %inc545 = add i32 %423, 1, !dbg !1795
  store i32 %inc545, i32* %pending544, align 8, !dbg !1795
  %idxprom546 = zext i32 %423 to i64, !dbg !1795
  %424 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1795
  %pending_buf547 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %424, i32 0, i32 2, !dbg !1795
  %425 = load i8*, i8** %pending_buf547, align 8, !dbg !1795
  %arrayidx548 = getelementptr inbounds i8, i8* %425, i64 %idxprom546, !dbg !1795
  store i8 %conv543, i8* %arrayidx548, align 1, !dbg !1795
  %426 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1798
  %adler549 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %426, i32 0, i32 12, !dbg !1798
  %427 = load i64, i64* %adler549, align 8, !dbg !1798
  %shr550 = lshr i64 %427, 8, !dbg !1798
  %and551 = and i64 %shr550, 255, !dbg !1798
  %conv552 = trunc i64 %and551 to i8, !dbg !1798
  %428 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1798
  %pending553 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %428, i32 0, i32 5, !dbg !1798
  %429 = load i32, i32* %pending553, align 8, !dbg !1798
  %inc554 = add i32 %429, 1, !dbg !1798
  store i32 %inc554, i32* %pending553, align 8, !dbg !1798
  %idxprom555 = zext i32 %429 to i64, !dbg !1798
  %430 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1798
  %pending_buf556 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %430, i32 0, i32 2, !dbg !1798
  %431 = load i8*, i8** %pending_buf556, align 8, !dbg !1798
  %arrayidx557 = getelementptr inbounds i8, i8* %431, i64 %idxprom555, !dbg !1798
  store i8 %conv552, i8* %arrayidx557, align 1, !dbg !1798
  %call558 = call i64 @cm_zlib_crc32(i64 0, i8* null, i32 0), !dbg !1800
  %432 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1801
  %adler559 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %432, i32 0, i32 12, !dbg !1802
  store i64 %call558, i64* %adler559, align 8, !dbg !1803
  %433 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1804
  %status560 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %433, i32 0, i32 1, !dbg !1805
  store i32 113, i32* %status560, align 8, !dbg !1806
  br label %if.end561, !dbg !1807

if.end561:                                        ; preds = %if.then540, %if.end533
  br label %if.end564, !dbg !1808

if.else562:                                       ; preds = %if.then521
  %434 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1809
  %status563 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %434, i32 0, i32 1, !dbg !1810
  store i32 113, i32* %status563, align 8, !dbg !1811
  br label %if.end564

if.end564:                                        ; preds = %if.else562, %if.end561
  br label %if.end565, !dbg !1812

if.end565:                                        ; preds = %if.end564, %if.end517
  %435 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1813
  %pending566 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %435, i32 0, i32 5, !dbg !1815
  %436 = load i32, i32* %pending566, align 8, !dbg !1815
  %cmp567 = icmp ne i32 %436, 0, !dbg !1816
  br i1 %cmp567, label %if.then569, label %if.else576, !dbg !1817

if.then569:                                       ; preds = %if.end565
  %437 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1818
  call void @flush_pending(%struct.z_stream_s* %437), !dbg !1820
  %438 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1821
  %avail_out570 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %438, i32 0, i32 4, !dbg !1823
  %439 = load i32, i32* %avail_out570, align 8, !dbg !1823
  %cmp571 = icmp eq i32 %439, 0, !dbg !1824
  br i1 %cmp571, label %if.then573, label %if.end575, !dbg !1825

if.then573:                                       ; preds = %if.then569
  %440 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1826
  %last_flush574 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %440, i32 0, i32 10, !dbg !1828
  store i32 -1, i32* %last_flush574, align 8, !dbg !1829
  store i32 0, i32* %retval, align 4, !dbg !1830
  br label %return, !dbg !1830

if.end575:                                        ; preds = %if.then569
  br label %if.end589, !dbg !1831

if.else576:                                       ; preds = %if.end565
  %441 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1832
  %avail_in577 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %441, i32 0, i32 1, !dbg !1835
  %442 = load i32, i32* %avail_in577, align 8, !dbg !1835
  %cmp578 = icmp eq i32 %442, 0, !dbg !1836
  br i1 %cmp578, label %land.lhs.true580, label %if.end588, !dbg !1837

land.lhs.true580:                                 ; preds = %if.else576
  %443 = load i32, i32* %flush.addr, align 4, !dbg !1838
  %444 = load i32, i32* %old_flush, align 4, !dbg !1840
  %cmp581 = icmp sle i32 %443, %444, !dbg !1841
  br i1 %cmp581, label %land.lhs.true583, label %if.end588, !dbg !1842

land.lhs.true583:                                 ; preds = %land.lhs.true580
  %445 = load i32, i32* %flush.addr, align 4, !dbg !1843
  %cmp584 = icmp ne i32 %445, 4, !dbg !1844
  br i1 %cmp584, label %if.then586, label %if.end588, !dbg !1845

if.then586:                                       ; preds = %land.lhs.true583
  %446 = load i8*, i8** getelementptr inbounds ([10 x i8*], [10 x i8*]* @cm_zlib_z_errmsg, i64 0, i64 7), align 8, !dbg !1847
  %447 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1847
  %msg587 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %447, i32 0, i32 6, !dbg !1847
  store i8* %446, i8** %msg587, align 8, !dbg !1847
  store i32 -5, i32* %retval, align 4, !dbg !1847
  br label %return, !dbg !1847

if.end588:                                        ; preds = %land.lhs.true583, %land.lhs.true580, %if.else576
  br label %if.end589

if.end589:                                        ; preds = %if.end588, %if.end575
  %448 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1849
  %status590 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %448, i32 0, i32 1, !dbg !1851
  %449 = load i32, i32* %status590, align 8, !dbg !1851
  %cmp591 = icmp eq i32 %449, 666, !dbg !1852
  br i1 %cmp591, label %land.lhs.true593, label %if.end599, !dbg !1853

land.lhs.true593:                                 ; preds = %if.end589
  %450 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1854
  %avail_in594 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %450, i32 0, i32 1, !dbg !1856
  %451 = load i32, i32* %avail_in594, align 8, !dbg !1856
  %cmp595 = icmp ne i32 %451, 0, !dbg !1857
  br i1 %cmp595, label %if.then597, label %if.end599, !dbg !1858

if.then597:                                       ; preds = %land.lhs.true593
  %452 = load i8*, i8** getelementptr inbounds ([10 x i8*], [10 x i8*]* @cm_zlib_z_errmsg, i64 0, i64 7), align 8, !dbg !1859
  %453 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1859
  %msg598 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %453, i32 0, i32 6, !dbg !1859
  store i8* %452, i8** %msg598, align 8, !dbg !1859
  store i32 -5, i32* %retval, align 4, !dbg !1859
  br label %return, !dbg !1859

if.end599:                                        ; preds = %land.lhs.true593, %if.end589
  %454 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1861
  %avail_in600 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %454, i32 0, i32 1, !dbg !1863
  %455 = load i32, i32* %avail_in600, align 8, !dbg !1863
  %cmp601 = icmp ne i32 %455, 0, !dbg !1864
  br i1 %cmp601, label %if.then613, label %lor.lhs.false603, !dbg !1865

lor.lhs.false603:                                 ; preds = %if.end599
  %456 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1866
  %lookahead = getelementptr inbounds %struct.internal_state, %struct.internal_state* %456, i32 0, i32 29, !dbg !1868
  %457 = load i32, i32* %lookahead, align 4, !dbg !1868
  %cmp604 = icmp ne i32 %457, 0, !dbg !1869
  br i1 %cmp604, label %if.then613, label %lor.lhs.false606, !dbg !1870

lor.lhs.false606:                                 ; preds = %lor.lhs.false603
  %458 = load i32, i32* %flush.addr, align 4, !dbg !1871
  %cmp607 = icmp ne i32 %458, 0, !dbg !1872
  br i1 %cmp607, label %land.lhs.true609, label %if.end665, !dbg !1873

land.lhs.true609:                                 ; preds = %lor.lhs.false606
  %459 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1874
  %status610 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %459, i32 0, i32 1, !dbg !1875
  %460 = load i32, i32* %status610, align 8, !dbg !1875
  %cmp611 = icmp ne i32 %460, 666, !dbg !1876
  br i1 %cmp611, label %if.then613, label %if.end665, !dbg !1877

if.then613:                                       ; preds = %land.lhs.true609, %lor.lhs.false603, %if.end599
  call void @llvm.dbg.declare(metadata i32* %bstate, metadata !1878, metadata !277), !dbg !1880
  %461 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1881
  %level614 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %461, i32 0, i32 33, !dbg !1882
  %462 = load i32, i32* %level614, align 4, !dbg !1882
  %idxprom615 = sext i32 %462 to i64, !dbg !1883
  %arrayidx616 = getelementptr inbounds [10 x %struct.config_s], [10 x %struct.config_s]* @configuration_table, i64 0, i64 %idxprom615, !dbg !1883
  %func = getelementptr inbounds %struct.config_s, %struct.config_s* %arrayidx616, i32 0, i32 4, !dbg !1884
  %463 = load i32 (%struct.internal_state*, i32)*, i32 (%struct.internal_state*, i32)** %func, align 8, !dbg !1884
  %464 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1885
  %465 = load i32, i32* %flush.addr, align 4, !dbg !1886
  %call617 = call i32 %463(%struct.internal_state* %464, i32 %465), !dbg !1887
  store i32 %call617, i32* %bstate, align 4, !dbg !1888
  %466 = load i32, i32* %bstate, align 4, !dbg !1889
  %cmp618 = icmp eq i32 %466, 2, !dbg !1891
  br i1 %cmp618, label %if.then623, label %lor.lhs.false620, !dbg !1892

lor.lhs.false620:                                 ; preds = %if.then613
  %467 = load i32, i32* %bstate, align 4, !dbg !1893
  %cmp621 = icmp eq i32 %467, 3, !dbg !1895
  br i1 %cmp621, label %if.then623, label %if.end625, !dbg !1896

if.then623:                                       ; preds = %lor.lhs.false620, %if.then613
  %468 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1897
  %status624 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %468, i32 0, i32 1, !dbg !1899
  store i32 666, i32* %status624, align 8, !dbg !1900
  br label %if.end625, !dbg !1901

if.end625:                                        ; preds = %if.then623, %lor.lhs.false620
  %469 = load i32, i32* %bstate, align 4, !dbg !1902
  %cmp626 = icmp eq i32 %469, 0, !dbg !1904
  br i1 %cmp626, label %if.then631, label %lor.lhs.false628, !dbg !1905

lor.lhs.false628:                                 ; preds = %if.end625
  %470 = load i32, i32* %bstate, align 4, !dbg !1906
  %cmp629 = icmp eq i32 %470, 2, !dbg !1908
  br i1 %cmp629, label %if.then631, label %if.end638, !dbg !1909

if.then631:                                       ; preds = %lor.lhs.false628, %if.end625
  %471 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1910
  %avail_out632 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %471, i32 0, i32 4, !dbg !1913
  %472 = load i32, i32* %avail_out632, align 8, !dbg !1913
  %cmp633 = icmp eq i32 %472, 0, !dbg !1914
  br i1 %cmp633, label %if.then635, label %if.end637, !dbg !1915

if.then635:                                       ; preds = %if.then631
  %473 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1916
  %last_flush636 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %473, i32 0, i32 10, !dbg !1918
  store i32 -1, i32* %last_flush636, align 8, !dbg !1919
  br label %if.end637, !dbg !1920

if.end637:                                        ; preds = %if.then635, %if.then631
  store i32 0, i32* %retval, align 4, !dbg !1921
  br label %return, !dbg !1921

if.end638:                                        ; preds = %lor.lhs.false628
  %474 = load i32, i32* %bstate, align 4, !dbg !1922
  %cmp639 = icmp eq i32 %474, 1, !dbg !1924
  br i1 %cmp639, label %if.then641, label %if.end664, !dbg !1925

if.then641:                                       ; preds = %if.end638
  %475 = load i32, i32* %flush.addr, align 4, !dbg !1926
  %cmp642 = icmp eq i32 %475, 1, !dbg !1929
  br i1 %cmp642, label %if.then644, label %if.else645, !dbg !1930

if.then644:                                       ; preds = %if.then641
  %476 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1931
  call void @cm_zlib__tr_align(%struct.internal_state* %476), !dbg !1933
  br label %if.end657, !dbg !1934

if.else645:                                       ; preds = %if.then641
  %477 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1935
  call void @cm_zlib__tr_stored_block(%struct.internal_state* %477, i8* null, i64 0, i32 0), !dbg !1937
  %478 = load i32, i32* %flush.addr, align 4, !dbg !1938
  %cmp646 = icmp eq i32 %478, 3, !dbg !1940
  br i1 %cmp646, label %if.then648, label %if.end656, !dbg !1941

if.then648:                                       ; preds = %if.else645
  %479 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1942
  %hash_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %479, i32 0, i32 19, !dbg !1942
  %480 = load i32, i32* %hash_size, align 4, !dbg !1942
  %sub649 = sub i32 %480, 1, !dbg !1942
  %idxprom650 = zext i32 %sub649 to i64, !dbg !1942
  %481 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1942
  %head = getelementptr inbounds %struct.internal_state, %struct.internal_state* %481, i32 0, i32 17, !dbg !1942
  %482 = load i16*, i16** %head, align 8, !dbg !1942
  %arrayidx651 = getelementptr inbounds i16, i16* %482, i64 %idxprom650, !dbg !1942
  store i16 0, i16* %arrayidx651, align 2, !dbg !1942
  %483 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1942
  %head652 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %483, i32 0, i32 17, !dbg !1942
  %484 = load i16*, i16** %head652, align 8, !dbg !1942
  %485 = bitcast i16* %484 to i8*, !dbg !1942
  %486 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1942
  %hash_size653 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %486, i32 0, i32 19, !dbg !1942
  %487 = load i32, i32* %hash_size653, align 4, !dbg !1942
  %sub654 = sub i32 %487, 1, !dbg !1942
  %conv655 = zext i32 %sub654 to i64, !dbg !1942
  %mul = mul i64 %conv655, 2, !dbg !1942
  call void @llvm.memset.p0i8.i64(i8* %485, i8 0, i64 %mul, i32 1, i1 false), !dbg !1942
  br label %if.end656, !dbg !1944

if.end656:                                        ; preds = %if.then648, %if.else645
  br label %if.end657

if.end657:                                        ; preds = %if.end656, %if.then644
  %488 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1945
  call void @flush_pending(%struct.z_stream_s* %488), !dbg !1946
  %489 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1947
  %avail_out658 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %489, i32 0, i32 4, !dbg !1949
  %490 = load i32, i32* %avail_out658, align 8, !dbg !1949
  %cmp659 = icmp eq i32 %490, 0, !dbg !1950
  br i1 %cmp659, label %if.then661, label %if.end663, !dbg !1951

if.then661:                                       ; preds = %if.end657
  %491 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1952
  %last_flush662 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %491, i32 0, i32 10, !dbg !1954
  store i32 -1, i32* %last_flush662, align 8, !dbg !1955
  store i32 0, i32* %retval, align 4, !dbg !1956
  br label %return, !dbg !1956

if.end663:                                        ; preds = %if.end657
  br label %if.end664, !dbg !1957

if.end664:                                        ; preds = %if.end663, %if.end638
  br label %if.end665, !dbg !1958

if.end665:                                        ; preds = %if.end664, %land.lhs.true609, %lor.lhs.false606
  %492 = load i32, i32* %flush.addr, align 4, !dbg !1959
  %cmp666 = icmp ne i32 %492, 4, !dbg !1961
  br i1 %cmp666, label %if.then668, label %if.end669, !dbg !1962

if.then668:                                       ; preds = %if.end665
  store i32 0, i32* %retval, align 4, !dbg !1963
  br label %return, !dbg !1963

if.end669:                                        ; preds = %if.end665
  %493 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1965
  %wrap670 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %493, i32 0, i32 6, !dbg !1967
  %494 = load i32, i32* %wrap670, align 4, !dbg !1967
  %cmp671 = icmp sle i32 %494, 0, !dbg !1968
  br i1 %cmp671, label %if.then673, label %if.end674, !dbg !1969

if.then673:                                       ; preds = %if.end669
  store i32 1, i32* %retval, align 4, !dbg !1970
  br label %return, !dbg !1970

if.end674:                                        ; preds = %if.end669
  %495 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1972
  %wrap675 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %495, i32 0, i32 6, !dbg !1974
  %496 = load i32, i32* %wrap675, align 4, !dbg !1974
  %cmp676 = icmp eq i32 %496, 2, !dbg !1975
  br i1 %cmp676, label %if.then678, label %if.else748, !dbg !1976

if.then678:                                       ; preds = %if.end674
  %497 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1977
  %adler679 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %497, i32 0, i32 12, !dbg !1977
  %498 = load i64, i64* %adler679, align 8, !dbg !1977
  %and680 = and i64 %498, 255, !dbg !1977
  %conv681 = trunc i64 %and680 to i8, !dbg !1977
  %499 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1977
  %pending682 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %499, i32 0, i32 5, !dbg !1977
  %500 = load i32, i32* %pending682, align 8, !dbg !1977
  %inc683 = add i32 %500, 1, !dbg !1977
  store i32 %inc683, i32* %pending682, align 8, !dbg !1977
  %idxprom684 = zext i32 %500 to i64, !dbg !1977
  %501 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1977
  %pending_buf685 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %501, i32 0, i32 2, !dbg !1977
  %502 = load i8*, i8** %pending_buf685, align 8, !dbg !1977
  %arrayidx686 = getelementptr inbounds i8, i8* %502, i64 %idxprom684, !dbg !1977
  store i8 %conv681, i8* %arrayidx686, align 1, !dbg !1977
  %503 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1980
  %adler687 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %503, i32 0, i32 12, !dbg !1980
  %504 = load i64, i64* %adler687, align 8, !dbg !1980
  %shr688 = lshr i64 %504, 8, !dbg !1980
  %and689 = and i64 %shr688, 255, !dbg !1980
  %conv690 = trunc i64 %and689 to i8, !dbg !1980
  %505 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1980
  %pending691 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %505, i32 0, i32 5, !dbg !1980
  %506 = load i32, i32* %pending691, align 8, !dbg !1980
  %inc692 = add i32 %506, 1, !dbg !1980
  store i32 %inc692, i32* %pending691, align 8, !dbg !1980
  %idxprom693 = zext i32 %506 to i64, !dbg !1980
  %507 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1980
  %pending_buf694 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %507, i32 0, i32 2, !dbg !1980
  %508 = load i8*, i8** %pending_buf694, align 8, !dbg !1980
  %arrayidx695 = getelementptr inbounds i8, i8* %508, i64 %idxprom693, !dbg !1980
  store i8 %conv690, i8* %arrayidx695, align 1, !dbg !1980
  %509 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1982
  %adler696 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %509, i32 0, i32 12, !dbg !1982
  %510 = load i64, i64* %adler696, align 8, !dbg !1982
  %shr697 = lshr i64 %510, 16, !dbg !1982
  %and698 = and i64 %shr697, 255, !dbg !1982
  %conv699 = trunc i64 %and698 to i8, !dbg !1982
  %511 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1982
  %pending700 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %511, i32 0, i32 5, !dbg !1982
  %512 = load i32, i32* %pending700, align 8, !dbg !1982
  %inc701 = add i32 %512, 1, !dbg !1982
  store i32 %inc701, i32* %pending700, align 8, !dbg !1982
  %idxprom702 = zext i32 %512 to i64, !dbg !1982
  %513 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1982
  %pending_buf703 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %513, i32 0, i32 2, !dbg !1982
  %514 = load i8*, i8** %pending_buf703, align 8, !dbg !1982
  %arrayidx704 = getelementptr inbounds i8, i8* %514, i64 %idxprom702, !dbg !1982
  store i8 %conv699, i8* %arrayidx704, align 1, !dbg !1982
  %515 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1984
  %adler705 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %515, i32 0, i32 12, !dbg !1984
  %516 = load i64, i64* %adler705, align 8, !dbg !1984
  %shr706 = lshr i64 %516, 24, !dbg !1984
  %and707 = and i64 %shr706, 255, !dbg !1984
  %conv708 = trunc i64 %and707 to i8, !dbg !1984
  %517 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1984
  %pending709 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %517, i32 0, i32 5, !dbg !1984
  %518 = load i32, i32* %pending709, align 8, !dbg !1984
  %inc710 = add i32 %518, 1, !dbg !1984
  store i32 %inc710, i32* %pending709, align 8, !dbg !1984
  %idxprom711 = zext i32 %518 to i64, !dbg !1984
  %519 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1984
  %pending_buf712 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %519, i32 0, i32 2, !dbg !1984
  %520 = load i8*, i8** %pending_buf712, align 8, !dbg !1984
  %arrayidx713 = getelementptr inbounds i8, i8* %520, i64 %idxprom711, !dbg !1984
  store i8 %conv708, i8* %arrayidx713, align 1, !dbg !1984
  %521 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1986
  %total_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %521, i32 0, i32 2, !dbg !1986
  %522 = load i64, i64* %total_in, align 8, !dbg !1986
  %and714 = and i64 %522, 255, !dbg !1986
  %conv715 = trunc i64 %and714 to i8, !dbg !1986
  %523 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1986
  %pending716 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %523, i32 0, i32 5, !dbg !1986
  %524 = load i32, i32* %pending716, align 8, !dbg !1986
  %inc717 = add i32 %524, 1, !dbg !1986
  store i32 %inc717, i32* %pending716, align 8, !dbg !1986
  %idxprom718 = zext i32 %524 to i64, !dbg !1986
  %525 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1986
  %pending_buf719 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %525, i32 0, i32 2, !dbg !1986
  %526 = load i8*, i8** %pending_buf719, align 8, !dbg !1986
  %arrayidx720 = getelementptr inbounds i8, i8* %526, i64 %idxprom718, !dbg !1986
  store i8 %conv715, i8* %arrayidx720, align 1, !dbg !1986
  %527 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1988
  %total_in721 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %527, i32 0, i32 2, !dbg !1988
  %528 = load i64, i64* %total_in721, align 8, !dbg !1988
  %shr722 = lshr i64 %528, 8, !dbg !1988
  %and723 = and i64 %shr722, 255, !dbg !1988
  %conv724 = trunc i64 %and723 to i8, !dbg !1988
  %529 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1988
  %pending725 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %529, i32 0, i32 5, !dbg !1988
  %530 = load i32, i32* %pending725, align 8, !dbg !1988
  %inc726 = add i32 %530, 1, !dbg !1988
  store i32 %inc726, i32* %pending725, align 8, !dbg !1988
  %idxprom727 = zext i32 %530 to i64, !dbg !1988
  %531 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1988
  %pending_buf728 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %531, i32 0, i32 2, !dbg !1988
  %532 = load i8*, i8** %pending_buf728, align 8, !dbg !1988
  %arrayidx729 = getelementptr inbounds i8, i8* %532, i64 %idxprom727, !dbg !1988
  store i8 %conv724, i8* %arrayidx729, align 1, !dbg !1988
  %533 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1990
  %total_in730 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %533, i32 0, i32 2, !dbg !1990
  %534 = load i64, i64* %total_in730, align 8, !dbg !1990
  %shr731 = lshr i64 %534, 16, !dbg !1990
  %and732 = and i64 %shr731, 255, !dbg !1990
  %conv733 = trunc i64 %and732 to i8, !dbg !1990
  %535 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1990
  %pending734 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %535, i32 0, i32 5, !dbg !1990
  %536 = load i32, i32* %pending734, align 8, !dbg !1990
  %inc735 = add i32 %536, 1, !dbg !1990
  store i32 %inc735, i32* %pending734, align 8, !dbg !1990
  %idxprom736 = zext i32 %536 to i64, !dbg !1990
  %537 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1990
  %pending_buf737 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %537, i32 0, i32 2, !dbg !1990
  %538 = load i8*, i8** %pending_buf737, align 8, !dbg !1990
  %arrayidx738 = getelementptr inbounds i8, i8* %538, i64 %idxprom736, !dbg !1990
  store i8 %conv733, i8* %arrayidx738, align 1, !dbg !1990
  %539 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1992
  %total_in739 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %539, i32 0, i32 2, !dbg !1992
  %540 = load i64, i64* %total_in739, align 8, !dbg !1992
  %shr740 = lshr i64 %540, 24, !dbg !1992
  %and741 = and i64 %shr740, 255, !dbg !1992
  %conv742 = trunc i64 %and741 to i8, !dbg !1992
  %541 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1992
  %pending743 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %541, i32 0, i32 5, !dbg !1992
  %542 = load i32, i32* %pending743, align 8, !dbg !1992
  %inc744 = add i32 %542, 1, !dbg !1992
  store i32 %inc744, i32* %pending743, align 8, !dbg !1992
  %idxprom745 = zext i32 %542 to i64, !dbg !1992
  %543 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1992
  %pending_buf746 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %543, i32 0, i32 2, !dbg !1992
  %544 = load i8*, i8** %pending_buf746, align 8, !dbg !1992
  %arrayidx747 = getelementptr inbounds i8, i8* %544, i64 %idxprom745, !dbg !1992
  store i8 %conv742, i8* %arrayidx747, align 1, !dbg !1992
  br label %if.end755, !dbg !1994

if.else748:                                       ; preds = %if.end674
  %545 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !1995
  %546 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !1997
  %adler749 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %546, i32 0, i32 12, !dbg !1998
  %547 = load i64, i64* %adler749, align 8, !dbg !1998
  %shr750 = lshr i64 %547, 16, !dbg !1999
  %conv751 = trunc i64 %shr750 to i32, !dbg !2000
  call void @putShortMSB(%struct.internal_state* %545, i32 %conv751), !dbg !2001
  %548 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !2002
  %549 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2003
  %adler752 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %549, i32 0, i32 12, !dbg !2004
  %550 = load i64, i64* %adler752, align 8, !dbg !2004
  %and753 = and i64 %550, 65535, !dbg !2005
  %conv754 = trunc i64 %and753 to i32, !dbg !2006
  call void @putShortMSB(%struct.internal_state* %548, i32 %conv754), !dbg !2007
  br label %if.end755

if.end755:                                        ; preds = %if.else748, %if.then678
  %551 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2008
  call void @flush_pending(%struct.z_stream_s* %551), !dbg !2009
  %552 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !2010
  %wrap756 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %552, i32 0, i32 6, !dbg !2012
  %553 = load i32, i32* %wrap756, align 4, !dbg !2012
  %cmp757 = icmp sgt i32 %553, 0, !dbg !2013
  br i1 %cmp757, label %if.then759, label %if.end763, !dbg !2014

if.then759:                                       ; preds = %if.end755
  %554 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !2015
  %wrap760 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %554, i32 0, i32 6, !dbg !2017
  %555 = load i32, i32* %wrap760, align 4, !dbg !2017
  %sub761 = sub nsw i32 0, %555, !dbg !2018
  %556 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !2019
  %wrap762 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %556, i32 0, i32 6, !dbg !2020
  store i32 %sub761, i32* %wrap762, align 4, !dbg !2021
  br label %if.end763, !dbg !2019

if.end763:                                        ; preds = %if.then759, %if.end755
  %557 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !2022
  %pending764 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %557, i32 0, i32 5, !dbg !2023
  %558 = load i32, i32* %pending764, align 8, !dbg !2023
  %cmp765 = icmp ne i32 %558, 0, !dbg !2024
  %cond767 = select i1 %cmp765, i32 0, i32 1, !dbg !2022
  store i32 %cond767, i32* %retval, align 4, !dbg !2025
  br label %return, !dbg !2025

return:                                           ; preds = %if.end763, %if.then673, %if.then668, %if.then661, %if.end637, %if.then597, %if.then586, %if.then573, %if.then18, %if.then15, %if.then
  %559 = load i32, i32* %retval, align 4, !dbg !2026
  ret i32 %559, !dbg !2026
}

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_deflateTune(%struct.z_stream_s* %strm, i32 %good_length, i32 %max_lazy, i32 %nice_length, i32 %max_chain) #0 !dbg !213 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.z_stream_s*, align 8
  %good_length.addr = alloca i32, align 4
  %max_lazy.addr = alloca i32, align 4
  %nice_length.addr = alloca i32, align 4
  %max_chain.addr = alloca i32, align 4
  %s = alloca %struct.internal_state*, align 8
  store %struct.z_stream_s* %strm, %struct.z_stream_s** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.z_stream_s** %strm.addr, metadata !2027, metadata !277), !dbg !2028
  store i32 %good_length, i32* %good_length.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %good_length.addr, metadata !2029, metadata !277), !dbg !2030
  store i32 %max_lazy, i32* %max_lazy.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %max_lazy.addr, metadata !2031, metadata !277), !dbg !2032
  store i32 %nice_length, i32* %nice_length.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nice_length.addr, metadata !2033, metadata !277), !dbg !2034
  store i32 %max_chain, i32* %max_chain.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %max_chain.addr, metadata !2035, metadata !277), !dbg !2036
  call void @llvm.dbg.declare(metadata %struct.internal_state** %s, metadata !2037, metadata !277), !dbg !2038
  %0 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2039
  %cmp = icmp eq %struct.z_stream_s* %0, null, !dbg !2041
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2042

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2043
  %state = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %1, i32 0, i32 7, !dbg !2045
  %2 = load %struct.internal_state*, %struct.internal_state** %state, align 8, !dbg !2045
  %cmp1 = icmp eq %struct.internal_state* %2, null, !dbg !2046
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2047

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -2, i32* %retval, align 4, !dbg !2048
  br label %return, !dbg !2048

if.end:                                           ; preds = %lor.lhs.false
  %3 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2050
  %state2 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %3, i32 0, i32 7, !dbg !2051
  %4 = load %struct.internal_state*, %struct.internal_state** %state2, align 8, !dbg !2051
  store %struct.internal_state* %4, %struct.internal_state** %s, align 8, !dbg !2052
  %5 = load i32, i32* %good_length.addr, align 4, !dbg !2053
  %6 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !2054
  %good_match = getelementptr inbounds %struct.internal_state, %struct.internal_state* %6, i32 0, i32 35, !dbg !2055
  store i32 %5, i32* %good_match, align 4, !dbg !2056
  %7 = load i32, i32* %max_lazy.addr, align 4, !dbg !2057
  %8 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !2058
  %max_lazy_match = getelementptr inbounds %struct.internal_state, %struct.internal_state* %8, i32 0, i32 32, !dbg !2059
  store i32 %7, i32* %max_lazy_match, align 8, !dbg !2060
  %9 = load i32, i32* %nice_length.addr, align 4, !dbg !2061
  %10 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !2062
  %nice_match = getelementptr inbounds %struct.internal_state, %struct.internal_state* %10, i32 0, i32 36, !dbg !2063
  store i32 %9, i32* %nice_match, align 8, !dbg !2064
  %11 = load i32, i32* %max_chain.addr, align 4, !dbg !2065
  %12 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !2066
  %max_chain_length = getelementptr inbounds %struct.internal_state, %struct.internal_state* %12, i32 0, i32 31, !dbg !2067
  store i32 %11, i32* %max_chain_length, align 4, !dbg !2068
  store i32 0, i32* %retval, align 4, !dbg !2069
  br label %return, !dbg !2069

return:                                           ; preds = %if.end, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !2070
  ret i32 %13, !dbg !2070
}

; Function Attrs: nounwind uwtable
define i64 @cm_zlib_deflateBound(%struct.z_stream_s* %strm, i64 %sourceLen) #0 !dbg !216 {
entry:
  %retval = alloca i64, align 8
  %strm.addr = alloca %struct.z_stream_s*, align 8
  %sourceLen.addr = alloca i64, align 8
  %s = alloca %struct.internal_state*, align 8
  %destLen = alloca i64, align 8
  store %struct.z_stream_s* %strm, %struct.z_stream_s** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.z_stream_s** %strm.addr, metadata !2071, metadata !277), !dbg !2072
  store i64 %sourceLen, i64* %sourceLen.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %sourceLen.addr, metadata !2073, metadata !277), !dbg !2074
  call void @llvm.dbg.declare(metadata %struct.internal_state** %s, metadata !2075, metadata !277), !dbg !2076
  call void @llvm.dbg.declare(metadata i64* %destLen, metadata !2077, metadata !277), !dbg !2078
  %0 = load i64, i64* %sourceLen.addr, align 8, !dbg !2079
  %1 = load i64, i64* %sourceLen.addr, align 8, !dbg !2080
  %add = add i64 %1, 7, !dbg !2081
  %shr = lshr i64 %add, 3, !dbg !2082
  %add1 = add i64 %0, %shr, !dbg !2083
  %2 = load i64, i64* %sourceLen.addr, align 8, !dbg !2084
  %add2 = add i64 %2, 63, !dbg !2085
  %shr3 = lshr i64 %add2, 6, !dbg !2086
  %add4 = add i64 %add1, %shr3, !dbg !2087
  %add5 = add i64 %add4, 11, !dbg !2088
  store i64 %add5, i64* %destLen, align 8, !dbg !2089
  %3 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2090
  %cmp = icmp eq %struct.z_stream_s* %3, null, !dbg !2092
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2093

lor.lhs.false:                                    ; preds = %entry
  %4 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2094
  %state = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %4, i32 0, i32 7, !dbg !2096
  %5 = load %struct.internal_state*, %struct.internal_state** %state, align 8, !dbg !2096
  %cmp6 = icmp eq %struct.internal_state* %5, null, !dbg !2097
  br i1 %cmp6, label %if.then, label %if.end, !dbg !2098

if.then:                                          ; preds = %lor.lhs.false, %entry
  %6 = load i64, i64* %destLen, align 8, !dbg !2099
  store i64 %6, i64* %retval, align 8, !dbg !2100
  br label %return, !dbg !2100

if.end:                                           ; preds = %lor.lhs.false
  %7 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2101
  %state7 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %7, i32 0, i32 7, !dbg !2102
  %8 = load %struct.internal_state*, %struct.internal_state** %state7, align 8, !dbg !2102
  store %struct.internal_state* %8, %struct.internal_state** %s, align 8, !dbg !2103
  %9 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !2104
  %w_bits = getelementptr inbounds %struct.internal_state, %struct.internal_state* %9, i32 0, i32 12, !dbg !2106
  %10 = load i32, i32* %w_bits, align 8, !dbg !2106
  %cmp8 = icmp ne i32 %10, 15, !dbg !2107
  br i1 %cmp8, label %if.then11, label %lor.lhs.false9, !dbg !2108

lor.lhs.false9:                                   ; preds = %if.end
  %11 = load %struct.internal_state*, %struct.internal_state** %s, align 8, !dbg !2109
  %hash_bits = getelementptr inbounds %struct.internal_state, %struct.internal_state* %11, i32 0, i32 20, !dbg !2111
  %12 = load i32, i32* %hash_bits, align 8, !dbg !2111
  %cmp10 = icmp ne i32 %12, 15, !dbg !2112
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !2113

if.then11:                                        ; preds = %lor.lhs.false9, %if.end
  %13 = load i64, i64* %destLen, align 8, !dbg !2114
  store i64 %13, i64* %retval, align 8, !dbg !2115
  br label %return, !dbg !2115

if.end12:                                         ; preds = %lor.lhs.false9
  %14 = load i64, i64* %sourceLen.addr, align 8, !dbg !2116
  %call = call i64 @cm_zlib_compressBound(i64 %14), !dbg !2117
  store i64 %call, i64* %retval, align 8, !dbg !2118
  br label %return, !dbg !2118

return:                                           ; preds = %if.end12, %if.then11, %if.then
  %15 = load i64, i64* %retval, align 8, !dbg !2119
  ret i64 %15, !dbg !2119
}

declare i64 @cm_zlib_compressBound(i64) #2

; Function Attrs: nounwind uwtable
define internal void @putShortMSB(%struct.internal_state* %s, i32 %b) #0 !dbg !242 {
entry:
  %s.addr = alloca %struct.internal_state*, align 8
  %b.addr = alloca i32, align 4
  store %struct.internal_state* %s, %struct.internal_state** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.internal_state** %s.addr, metadata !2120, metadata !277), !dbg !2121
  store i32 %b, i32* %b.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %b.addr, metadata !2122, metadata !277), !dbg !2123
  %0 = load i32, i32* %b.addr, align 4, !dbg !2124
  %shr = lshr i32 %0, 8, !dbg !2124
  %conv = trunc i32 %shr to i8, !dbg !2124
  %1 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2124
  %pending = getelementptr inbounds %struct.internal_state, %struct.internal_state* %1, i32 0, i32 5, !dbg !2124
  %2 = load i32, i32* %pending, align 8, !dbg !2124
  %inc = add i32 %2, 1, !dbg !2124
  store i32 %inc, i32* %pending, align 8, !dbg !2124
  %idxprom = zext i32 %2 to i64, !dbg !2124
  %3 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2124
  %pending_buf = getelementptr inbounds %struct.internal_state, %struct.internal_state* %3, i32 0, i32 2, !dbg !2124
  %4 = load i8*, i8** %pending_buf, align 8, !dbg !2124
  %arrayidx = getelementptr inbounds i8, i8* %4, i64 %idxprom, !dbg !2124
  store i8 %conv, i8* %arrayidx, align 1, !dbg !2124
  %5 = load i32, i32* %b.addr, align 4, !dbg !2126
  %and = and i32 %5, 255, !dbg !2126
  %conv1 = trunc i32 %and to i8, !dbg !2126
  %6 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2126
  %pending2 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %6, i32 0, i32 5, !dbg !2126
  %7 = load i32, i32* %pending2, align 8, !dbg !2126
  %inc3 = add i32 %7, 1, !dbg !2126
  store i32 %inc3, i32* %pending2, align 8, !dbg !2126
  %idxprom4 = zext i32 %7 to i64, !dbg !2126
  %8 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2126
  %pending_buf5 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %8, i32 0, i32 2, !dbg !2126
  %9 = load i8*, i8** %pending_buf5, align 8, !dbg !2126
  %arrayidx6 = getelementptr inbounds i8, i8* %9, i64 %idxprom4, !dbg !2126
  store i8 %conv1, i8* %arrayidx6, align 1, !dbg !2126
  ret void, !dbg !2128
}

; Function Attrs: nounwind uwtable
define internal void @flush_pending(%struct.z_stream_s* %strm) #0 !dbg !245 {
entry:
  %strm.addr = alloca %struct.z_stream_s*, align 8
  %len = alloca i32, align 4
  store %struct.z_stream_s* %strm, %struct.z_stream_s** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.z_stream_s** %strm.addr, metadata !2129, metadata !277), !dbg !2130
  call void @llvm.dbg.declare(metadata i32* %len, metadata !2131, metadata !277), !dbg !2132
  %0 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2133
  %state = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %0, i32 0, i32 7, !dbg !2134
  %1 = load %struct.internal_state*, %struct.internal_state** %state, align 8, !dbg !2134
  %pending = getelementptr inbounds %struct.internal_state, %struct.internal_state* %1, i32 0, i32 5, !dbg !2135
  %2 = load i32, i32* %pending, align 8, !dbg !2135
  store i32 %2, i32* %len, align 4, !dbg !2132
  %3 = load i32, i32* %len, align 4, !dbg !2136
  %4 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2138
  %avail_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %4, i32 0, i32 4, !dbg !2139
  %5 = load i32, i32* %avail_out, align 8, !dbg !2139
  %cmp = icmp ugt i32 %3, %5, !dbg !2140
  br i1 %cmp, label %if.then, label %if.end, !dbg !2141

if.then:                                          ; preds = %entry
  %6 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2142
  %avail_out1 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %6, i32 0, i32 4, !dbg !2144
  %7 = load i32, i32* %avail_out1, align 8, !dbg !2144
  store i32 %7, i32* %len, align 4, !dbg !2145
  br label %if.end, !dbg !2146

if.end:                                           ; preds = %if.then, %entry
  %8 = load i32, i32* %len, align 4, !dbg !2147
  %cmp2 = icmp eq i32 %8, 0, !dbg !2149
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !2150

if.then3:                                         ; preds = %if.end
  br label %if.end24, !dbg !2151

if.end4:                                          ; preds = %if.end
  %9 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2153
  %next_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %9, i32 0, i32 3, !dbg !2154
  %10 = load i8*, i8** %next_out, align 8, !dbg !2154
  %11 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2155
  %state5 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %11, i32 0, i32 7, !dbg !2156
  %12 = load %struct.internal_state*, %struct.internal_state** %state5, align 8, !dbg !2156
  %pending_out = getelementptr inbounds %struct.internal_state, %struct.internal_state* %12, i32 0, i32 4, !dbg !2157
  %13 = load i8*, i8** %pending_out, align 8, !dbg !2157
  %14 = load i32, i32* %len, align 4, !dbg !2158
  %conv = zext i32 %14 to i64, !dbg !2158
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %10, i8* %13, i64 %conv, i32 1, i1 false), !dbg !2159
  %15 = load i32, i32* %len, align 4, !dbg !2160
  %16 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2161
  %next_out6 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %16, i32 0, i32 3, !dbg !2162
  %17 = load i8*, i8** %next_out6, align 8, !dbg !2163
  %idx.ext = zext i32 %15 to i64, !dbg !2163
  %add.ptr = getelementptr inbounds i8, i8* %17, i64 %idx.ext, !dbg !2163
  store i8* %add.ptr, i8** %next_out6, align 8, !dbg !2163
  %18 = load i32, i32* %len, align 4, !dbg !2164
  %19 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2165
  %state7 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %19, i32 0, i32 7, !dbg !2166
  %20 = load %struct.internal_state*, %struct.internal_state** %state7, align 8, !dbg !2166
  %pending_out8 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %20, i32 0, i32 4, !dbg !2167
  %21 = load i8*, i8** %pending_out8, align 8, !dbg !2168
  %idx.ext9 = zext i32 %18 to i64, !dbg !2168
  %add.ptr10 = getelementptr inbounds i8, i8* %21, i64 %idx.ext9, !dbg !2168
  store i8* %add.ptr10, i8** %pending_out8, align 8, !dbg !2168
  %22 = load i32, i32* %len, align 4, !dbg !2169
  %conv11 = zext i32 %22 to i64, !dbg !2169
  %23 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2170
  %total_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %23, i32 0, i32 5, !dbg !2171
  %24 = load i64, i64* %total_out, align 8, !dbg !2172
  %add = add i64 %24, %conv11, !dbg !2172
  store i64 %add, i64* %total_out, align 8, !dbg !2172
  %25 = load i32, i32* %len, align 4, !dbg !2173
  %26 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2174
  %avail_out12 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %26, i32 0, i32 4, !dbg !2175
  %27 = load i32, i32* %avail_out12, align 8, !dbg !2176
  %sub = sub i32 %27, %25, !dbg !2176
  store i32 %sub, i32* %avail_out12, align 8, !dbg !2176
  %28 = load i32, i32* %len, align 4, !dbg !2177
  %29 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2178
  %state13 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %29, i32 0, i32 7, !dbg !2179
  %30 = load %struct.internal_state*, %struct.internal_state** %state13, align 8, !dbg !2179
  %pending14 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %30, i32 0, i32 5, !dbg !2180
  %31 = load i32, i32* %pending14, align 8, !dbg !2181
  %sub15 = sub i32 %31, %28, !dbg !2181
  store i32 %sub15, i32* %pending14, align 8, !dbg !2181
  %32 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2182
  %state16 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %32, i32 0, i32 7, !dbg !2184
  %33 = load %struct.internal_state*, %struct.internal_state** %state16, align 8, !dbg !2184
  %pending17 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %33, i32 0, i32 5, !dbg !2185
  %34 = load i32, i32* %pending17, align 8, !dbg !2185
  %cmp18 = icmp eq i32 %34, 0, !dbg !2186
  br i1 %cmp18, label %if.then20, label %if.end24, !dbg !2187

if.then20:                                        ; preds = %if.end4
  %35 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2188
  %state21 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %35, i32 0, i32 7, !dbg !2190
  %36 = load %struct.internal_state*, %struct.internal_state** %state21, align 8, !dbg !2190
  %pending_buf = getelementptr inbounds %struct.internal_state, %struct.internal_state* %36, i32 0, i32 2, !dbg !2191
  %37 = load i8*, i8** %pending_buf, align 8, !dbg !2191
  %38 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !2192
  %state22 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %38, i32 0, i32 7, !dbg !2193
  %39 = load %struct.internal_state*, %struct.internal_state** %state22, align 8, !dbg !2193
  %pending_out23 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %39, i32 0, i32 4, !dbg !2194
  store i8* %37, i8** %pending_out23, align 8, !dbg !2195
  br label %if.end24, !dbg !2196

if.end24:                                         ; preds = %if.then3, %if.then20, %if.end4
  ret void, !dbg !2197
}

declare void @cm_zlib__tr_align(%struct.internal_state*) #2

declare void @cm_zlib__tr_stored_block(%struct.internal_state*, i8*, i64, i32) #2

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_deflateCopy(%struct.z_stream_s* %dest, %struct.z_stream_s* %source) #0 !dbg !223 {
entry:
  %retval = alloca i32, align 4
  %dest.addr = alloca %struct.z_stream_s*, align 8
  %source.addr = alloca %struct.z_stream_s*, align 8
  %ds = alloca %struct.internal_state*, align 8
  %ss = alloca %struct.internal_state*, align 8
  %overlay = alloca i16*, align 8
  store %struct.z_stream_s* %dest, %struct.z_stream_s** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.z_stream_s** %dest.addr, metadata !2198, metadata !277), !dbg !2199
  store %struct.z_stream_s* %source, %struct.z_stream_s** %source.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.z_stream_s** %source.addr, metadata !2200, metadata !277), !dbg !2201
  call void @llvm.dbg.declare(metadata %struct.internal_state** %ds, metadata !2202, metadata !277), !dbg !2203
  call void @llvm.dbg.declare(metadata %struct.internal_state** %ss, metadata !2204, metadata !277), !dbg !2205
  call void @llvm.dbg.declare(metadata i16** %overlay, metadata !2206, metadata !277), !dbg !2207
  %0 = load %struct.z_stream_s*, %struct.z_stream_s** %source.addr, align 8, !dbg !2208
  %cmp = icmp eq %struct.z_stream_s* %0, null, !dbg !2210
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2211

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.z_stream_s*, %struct.z_stream_s** %dest.addr, align 8, !dbg !2212
  %cmp1 = icmp eq %struct.z_stream_s* %1, null, !dbg !2214
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !2215

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %2 = load %struct.z_stream_s*, %struct.z_stream_s** %source.addr, align 8, !dbg !2216
  %state = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %2, i32 0, i32 7, !dbg !2218
  %3 = load %struct.internal_state*, %struct.internal_state** %state, align 8, !dbg !2218
  %cmp3 = icmp eq %struct.internal_state* %3, null, !dbg !2219
  br i1 %cmp3, label %if.then, label %if.end, !dbg !2220

if.then:                                          ; preds = %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 -2, i32* %retval, align 4, !dbg !2221
  br label %return, !dbg !2221

if.end:                                           ; preds = %lor.lhs.false2
  %4 = load %struct.z_stream_s*, %struct.z_stream_s** %source.addr, align 8, !dbg !2223
  %state4 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %4, i32 0, i32 7, !dbg !2224
  %5 = load %struct.internal_state*, %struct.internal_state** %state4, align 8, !dbg !2224
  store %struct.internal_state* %5, %struct.internal_state** %ss, align 8, !dbg !2225
  %6 = load %struct.z_stream_s*, %struct.z_stream_s** %dest.addr, align 8, !dbg !2226
  %7 = bitcast %struct.z_stream_s* %6 to i8*, !dbg !2227
  %8 = load %struct.z_stream_s*, %struct.z_stream_s** %source.addr, align 8, !dbg !2228
  %9 = bitcast %struct.z_stream_s* %8 to i8*, !dbg !2227
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %7, i8* %9, i64 112, i32 8, i1 false), !dbg !2227
  %10 = load %struct.z_stream_s*, %struct.z_stream_s** %dest.addr, align 8, !dbg !2229
  %zalloc = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %10, i32 0, i32 8, !dbg !2229
  %11 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %zalloc, align 8, !dbg !2229
  %12 = load %struct.z_stream_s*, %struct.z_stream_s** %dest.addr, align 8, !dbg !2229
  %opaque = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %12, i32 0, i32 10, !dbg !2229
  %13 = load i8*, i8** %opaque, align 8, !dbg !2229
  %call = call i8* %11(i8* %13, i32 1, i32 5928), !dbg !2229
  %14 = bitcast i8* %call to %struct.internal_state*, !dbg !2230
  store %struct.internal_state* %14, %struct.internal_state** %ds, align 8, !dbg !2231
  %15 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2232
  %cmp5 = icmp eq %struct.internal_state* %15, null, !dbg !2234
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !2235

if.then6:                                         ; preds = %if.end
  store i32 -4, i32* %retval, align 4, !dbg !2236
  br label %return, !dbg !2236

if.end7:                                          ; preds = %if.end
  %16 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2238
  %17 = load %struct.z_stream_s*, %struct.z_stream_s** %dest.addr, align 8, !dbg !2239
  %state8 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %17, i32 0, i32 7, !dbg !2240
  store %struct.internal_state* %16, %struct.internal_state** %state8, align 8, !dbg !2241
  %18 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2242
  %19 = bitcast %struct.internal_state* %18 to i8*, !dbg !2243
  %20 = load %struct.internal_state*, %struct.internal_state** %ss, align 8, !dbg !2244
  %21 = bitcast %struct.internal_state* %20 to i8*, !dbg !2243
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %19, i8* %21, i64 5928, i32 8, i1 false), !dbg !2243
  %22 = load %struct.z_stream_s*, %struct.z_stream_s** %dest.addr, align 8, !dbg !2245
  %23 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2246
  %strm = getelementptr inbounds %struct.internal_state, %struct.internal_state* %23, i32 0, i32 0, !dbg !2247
  store %struct.z_stream_s* %22, %struct.z_stream_s** %strm, align 8, !dbg !2248
  %24 = load %struct.z_stream_s*, %struct.z_stream_s** %dest.addr, align 8, !dbg !2249
  %zalloc9 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %24, i32 0, i32 8, !dbg !2249
  %25 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %zalloc9, align 8, !dbg !2249
  %26 = load %struct.z_stream_s*, %struct.z_stream_s** %dest.addr, align 8, !dbg !2249
  %opaque10 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %26, i32 0, i32 10, !dbg !2249
  %27 = load i8*, i8** %opaque10, align 8, !dbg !2249
  %28 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2249
  %w_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %28, i32 0, i32 11, !dbg !2249
  %29 = load i32, i32* %w_size, align 4, !dbg !2249
  %call11 = call i8* %25(i8* %27, i32 %29, i32 2), !dbg !2249
  %30 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2250
  %window = getelementptr inbounds %struct.internal_state, %struct.internal_state* %30, i32 0, i32 14, !dbg !2251
  store i8* %call11, i8** %window, align 8, !dbg !2252
  %31 = load %struct.z_stream_s*, %struct.z_stream_s** %dest.addr, align 8, !dbg !2253
  %zalloc12 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %31, i32 0, i32 8, !dbg !2253
  %32 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %zalloc12, align 8, !dbg !2253
  %33 = load %struct.z_stream_s*, %struct.z_stream_s** %dest.addr, align 8, !dbg !2253
  %opaque13 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %33, i32 0, i32 10, !dbg !2253
  %34 = load i8*, i8** %opaque13, align 8, !dbg !2253
  %35 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2253
  %w_size14 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %35, i32 0, i32 11, !dbg !2253
  %36 = load i32, i32* %w_size14, align 4, !dbg !2253
  %call15 = call i8* %32(i8* %34, i32 %36, i32 2), !dbg !2253
  %37 = bitcast i8* %call15 to i16*, !dbg !2254
  %38 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2255
  %prev = getelementptr inbounds %struct.internal_state, %struct.internal_state* %38, i32 0, i32 16, !dbg !2256
  store i16* %37, i16** %prev, align 8, !dbg !2257
  %39 = load %struct.z_stream_s*, %struct.z_stream_s** %dest.addr, align 8, !dbg !2258
  %zalloc16 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %39, i32 0, i32 8, !dbg !2258
  %40 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %zalloc16, align 8, !dbg !2258
  %41 = load %struct.z_stream_s*, %struct.z_stream_s** %dest.addr, align 8, !dbg !2258
  %opaque17 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %41, i32 0, i32 10, !dbg !2258
  %42 = load i8*, i8** %opaque17, align 8, !dbg !2258
  %43 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2258
  %hash_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %43, i32 0, i32 19, !dbg !2258
  %44 = load i32, i32* %hash_size, align 4, !dbg !2258
  %call18 = call i8* %40(i8* %42, i32 %44, i32 2), !dbg !2258
  %45 = bitcast i8* %call18 to i16*, !dbg !2259
  %46 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2260
  %head = getelementptr inbounds %struct.internal_state, %struct.internal_state* %46, i32 0, i32 17, !dbg !2261
  store i16* %45, i16** %head, align 8, !dbg !2262
  %47 = load %struct.z_stream_s*, %struct.z_stream_s** %dest.addr, align 8, !dbg !2263
  %zalloc19 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %47, i32 0, i32 8, !dbg !2263
  %48 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %zalloc19, align 8, !dbg !2263
  %49 = load %struct.z_stream_s*, %struct.z_stream_s** %dest.addr, align 8, !dbg !2263
  %opaque20 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %49, i32 0, i32 10, !dbg !2263
  %50 = load i8*, i8** %opaque20, align 8, !dbg !2263
  %51 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2263
  %lit_bufsize = getelementptr inbounds %struct.internal_state, %struct.internal_state* %51, i32 0, i32 49, !dbg !2263
  %52 = load i32, i32* %lit_bufsize, align 8, !dbg !2263
  %call21 = call i8* %48(i8* %50, i32 %52, i32 4), !dbg !2263
  %53 = bitcast i8* %call21 to i16*, !dbg !2264
  store i16* %53, i16** %overlay, align 8, !dbg !2265
  %54 = load i16*, i16** %overlay, align 8, !dbg !2266
  %55 = bitcast i16* %54 to i8*, !dbg !2267
  %56 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2268
  %pending_buf = getelementptr inbounds %struct.internal_state, %struct.internal_state* %56, i32 0, i32 2, !dbg !2269
  store i8* %55, i8** %pending_buf, align 8, !dbg !2270
  %57 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2271
  %window22 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %57, i32 0, i32 14, !dbg !2273
  %58 = load i8*, i8** %window22, align 8, !dbg !2273
  %cmp23 = icmp eq i8* %58, null, !dbg !2274
  br i1 %cmp23, label %if.then33, label %lor.lhs.false24, !dbg !2275

lor.lhs.false24:                                  ; preds = %if.end7
  %59 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2276
  %prev25 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %59, i32 0, i32 16, !dbg !2278
  %60 = load i16*, i16** %prev25, align 8, !dbg !2278
  %cmp26 = icmp eq i16* %60, null, !dbg !2279
  br i1 %cmp26, label %if.then33, label %lor.lhs.false27, !dbg !2280

lor.lhs.false27:                                  ; preds = %lor.lhs.false24
  %61 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2281
  %head28 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %61, i32 0, i32 17, !dbg !2283
  %62 = load i16*, i16** %head28, align 8, !dbg !2283
  %cmp29 = icmp eq i16* %62, null, !dbg !2284
  br i1 %cmp29, label %if.then33, label %lor.lhs.false30, !dbg !2285

lor.lhs.false30:                                  ; preds = %lor.lhs.false27
  %63 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2286
  %pending_buf31 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %63, i32 0, i32 2, !dbg !2287
  %64 = load i8*, i8** %pending_buf31, align 8, !dbg !2287
  %cmp32 = icmp eq i8* %64, null, !dbg !2288
  br i1 %cmp32, label %if.then33, label %if.end35, !dbg !2289

if.then33:                                        ; preds = %lor.lhs.false30, %lor.lhs.false27, %lor.lhs.false24, %if.end7
  %65 = load %struct.z_stream_s*, %struct.z_stream_s** %dest.addr, align 8, !dbg !2291
  %call34 = call i32 @cm_zlib_deflateEnd(%struct.z_stream_s* %65), !dbg !2293
  store i32 -4, i32* %retval, align 4, !dbg !2294
  br label %return, !dbg !2294

if.end35:                                         ; preds = %lor.lhs.false30
  %66 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2295
  %window36 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %66, i32 0, i32 14, !dbg !2296
  %67 = load i8*, i8** %window36, align 8, !dbg !2296
  %68 = load %struct.internal_state*, %struct.internal_state** %ss, align 8, !dbg !2297
  %window37 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %68, i32 0, i32 14, !dbg !2298
  %69 = load i8*, i8** %window37, align 8, !dbg !2298
  %70 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2299
  %w_size38 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %70, i32 0, i32 11, !dbg !2300
  %71 = load i32, i32* %w_size38, align 4, !dbg !2300
  %mul = mul i32 %71, 2, !dbg !2301
  %conv = zext i32 %mul to i64, !dbg !2299
  %mul39 = mul i64 %conv, 1, !dbg !2302
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %67, i8* %69, i64 %mul39, i32 1, i1 false), !dbg !2303
  %72 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2304
  %prev40 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %72, i32 0, i32 16, !dbg !2305
  %73 = load i16*, i16** %prev40, align 8, !dbg !2305
  %74 = bitcast i16* %73 to i8*, !dbg !2306
  %75 = load %struct.internal_state*, %struct.internal_state** %ss, align 8, !dbg !2307
  %prev41 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %75, i32 0, i32 16, !dbg !2308
  %76 = load i16*, i16** %prev41, align 8, !dbg !2308
  %77 = bitcast i16* %76 to i8*, !dbg !2306
  %78 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2309
  %w_size42 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %78, i32 0, i32 11, !dbg !2310
  %79 = load i32, i32* %w_size42, align 4, !dbg !2310
  %conv43 = zext i32 %79 to i64, !dbg !2309
  %mul44 = mul i64 %conv43, 2, !dbg !2311
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %74, i8* %77, i64 %mul44, i32 2, i1 false), !dbg !2306
  %80 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2312
  %head45 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %80, i32 0, i32 17, !dbg !2313
  %81 = load i16*, i16** %head45, align 8, !dbg !2313
  %82 = bitcast i16* %81 to i8*, !dbg !2314
  %83 = load %struct.internal_state*, %struct.internal_state** %ss, align 8, !dbg !2315
  %head46 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %83, i32 0, i32 17, !dbg !2316
  %84 = load i16*, i16** %head46, align 8, !dbg !2316
  %85 = bitcast i16* %84 to i8*, !dbg !2314
  %86 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2317
  %hash_size47 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %86, i32 0, i32 19, !dbg !2318
  %87 = load i32, i32* %hash_size47, align 4, !dbg !2318
  %conv48 = zext i32 %87 to i64, !dbg !2317
  %mul49 = mul i64 %conv48, 2, !dbg !2319
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %82, i8* %85, i64 %mul49, i32 2, i1 false), !dbg !2314
  %88 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2320
  %pending_buf50 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %88, i32 0, i32 2, !dbg !2321
  %89 = load i8*, i8** %pending_buf50, align 8, !dbg !2321
  %90 = load %struct.internal_state*, %struct.internal_state** %ss, align 8, !dbg !2322
  %pending_buf51 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %90, i32 0, i32 2, !dbg !2323
  %91 = load i8*, i8** %pending_buf51, align 8, !dbg !2323
  %92 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2324
  %pending_buf_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %92, i32 0, i32 3, !dbg !2325
  %93 = load i64, i64* %pending_buf_size, align 8, !dbg !2325
  %conv52 = trunc i64 %93 to i32, !dbg !2326
  %conv53 = zext i32 %conv52 to i64, !dbg !2326
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %89, i8* %91, i64 %conv53, i32 1, i1 false), !dbg !2327
  %94 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2328
  %pending_buf54 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %94, i32 0, i32 2, !dbg !2329
  %95 = load i8*, i8** %pending_buf54, align 8, !dbg !2329
  %96 = load %struct.internal_state*, %struct.internal_state** %ss, align 8, !dbg !2330
  %pending_out = getelementptr inbounds %struct.internal_state, %struct.internal_state* %96, i32 0, i32 4, !dbg !2331
  %97 = load i8*, i8** %pending_out, align 8, !dbg !2331
  %98 = load %struct.internal_state*, %struct.internal_state** %ss, align 8, !dbg !2332
  %pending_buf55 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %98, i32 0, i32 2, !dbg !2333
  %99 = load i8*, i8** %pending_buf55, align 8, !dbg !2333
  %sub.ptr.lhs.cast = ptrtoint i8* %97 to i64, !dbg !2334
  %sub.ptr.rhs.cast = ptrtoint i8* %99 to i64, !dbg !2334
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !2334
  %add.ptr = getelementptr inbounds i8, i8* %95, i64 %sub.ptr.sub, !dbg !2335
  %100 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2336
  %pending_out56 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %100, i32 0, i32 4, !dbg !2337
  store i8* %add.ptr, i8** %pending_out56, align 8, !dbg !2338
  %101 = load i16*, i16** %overlay, align 8, !dbg !2339
  %102 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2340
  %lit_bufsize57 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %102, i32 0, i32 49, !dbg !2341
  %103 = load i32, i32* %lit_bufsize57, align 8, !dbg !2341
  %conv58 = zext i32 %103 to i64, !dbg !2340
  %div = udiv i64 %conv58, 2, !dbg !2342
  %add.ptr59 = getelementptr inbounds i16, i16* %101, i64 %div, !dbg !2343
  %104 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2344
  %d_buf = getelementptr inbounds %struct.internal_state, %struct.internal_state* %104, i32 0, i32 51, !dbg !2345
  store i16* %add.ptr59, i16** %d_buf, align 8, !dbg !2346
  %105 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2347
  %pending_buf60 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %105, i32 0, i32 2, !dbg !2348
  %106 = load i8*, i8** %pending_buf60, align 8, !dbg !2348
  %107 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2349
  %lit_bufsize61 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %107, i32 0, i32 49, !dbg !2350
  %108 = load i32, i32* %lit_bufsize61, align 8, !dbg !2350
  %conv62 = zext i32 %108 to i64, !dbg !2349
  %mul63 = mul i64 3, %conv62, !dbg !2351
  %add.ptr64 = getelementptr inbounds i8, i8* %106, i64 %mul63, !dbg !2352
  %109 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2353
  %l_buf = getelementptr inbounds %struct.internal_state, %struct.internal_state* %109, i32 0, i32 48, !dbg !2354
  store i8* %add.ptr64, i8** %l_buf, align 8, !dbg !2355
  %110 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2356
  %dyn_ltree = getelementptr inbounds %struct.internal_state, %struct.internal_state* %110, i32 0, i32 37, !dbg !2357
  %arraydecay = getelementptr inbounds [573 x %struct.ct_data_s], [573 x %struct.ct_data_s]* %dyn_ltree, i32 0, i32 0, !dbg !2356
  %111 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2358
  %l_desc = getelementptr inbounds %struct.internal_state, %struct.internal_state* %111, i32 0, i32 40, !dbg !2359
  %dyn_tree = getelementptr inbounds %struct.tree_desc_s, %struct.tree_desc_s* %l_desc, i32 0, i32 0, !dbg !2360
  store %struct.ct_data_s* %arraydecay, %struct.ct_data_s** %dyn_tree, align 8, !dbg !2361
  %112 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2362
  %dyn_dtree = getelementptr inbounds %struct.internal_state, %struct.internal_state* %112, i32 0, i32 38, !dbg !2363
  %arraydecay65 = getelementptr inbounds [61 x %struct.ct_data_s], [61 x %struct.ct_data_s]* %dyn_dtree, i32 0, i32 0, !dbg !2362
  %113 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2364
  %d_desc = getelementptr inbounds %struct.internal_state, %struct.internal_state* %113, i32 0, i32 41, !dbg !2365
  %dyn_tree66 = getelementptr inbounds %struct.tree_desc_s, %struct.tree_desc_s* %d_desc, i32 0, i32 0, !dbg !2366
  store %struct.ct_data_s* %arraydecay65, %struct.ct_data_s** %dyn_tree66, align 8, !dbg !2367
  %114 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2368
  %bl_tree = getelementptr inbounds %struct.internal_state, %struct.internal_state* %114, i32 0, i32 39, !dbg !2369
  %arraydecay67 = getelementptr inbounds [39 x %struct.ct_data_s], [39 x %struct.ct_data_s]* %bl_tree, i32 0, i32 0, !dbg !2368
  %115 = load %struct.internal_state*, %struct.internal_state** %ds, align 8, !dbg !2370
  %bl_desc = getelementptr inbounds %struct.internal_state, %struct.internal_state* %115, i32 0, i32 42, !dbg !2371
  %dyn_tree68 = getelementptr inbounds %struct.tree_desc_s, %struct.tree_desc_s* %bl_desc, i32 0, i32 0, !dbg !2372
  store %struct.ct_data_s* %arraydecay67, %struct.ct_data_s** %dyn_tree68, align 8, !dbg !2373
  store i32 0, i32* %retval, align 4, !dbg !2374
  br label %return, !dbg !2374

return:                                           ; preds = %if.end35, %if.then33, %if.then6, %if.then
  %116 = load i32, i32* %retval, align 4, !dbg !2375
  ret i32 %116, !dbg !2375
}

; Function Attrs: nounwind uwtable
define internal i32 @deflate_stored(%struct.internal_state* %s, i32 %flush) #0 !dbg !226 {
entry:
  %retval = alloca i32, align 4
  %s.addr = alloca %struct.internal_state*, align 8
  %flush.addr = alloca i32, align 4
  %max_block_size = alloca i64, align 8
  %max_start = alloca i64, align 8
  store %struct.internal_state* %s, %struct.internal_state** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.internal_state** %s.addr, metadata !2376, metadata !277), !dbg !2377
  store i32 %flush, i32* %flush.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flush.addr, metadata !2378, metadata !277), !dbg !2379
  call void @llvm.dbg.declare(metadata i64* %max_block_size, metadata !2380, metadata !277), !dbg !2381
  store i64 65535, i64* %max_block_size, align 8, !dbg !2381
  call void @llvm.dbg.declare(metadata i64* %max_start, metadata !2382, metadata !277), !dbg !2383
  %0 = load i64, i64* %max_block_size, align 8, !dbg !2384
  %1 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2386
  %pending_buf_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %1, i32 0, i32 3, !dbg !2387
  %2 = load i64, i64* %pending_buf_size, align 8, !dbg !2387
  %sub = sub i64 %2, 5, !dbg !2388
  %cmp = icmp ugt i64 %0, %sub, !dbg !2389
  br i1 %cmp, label %if.then, label %if.end, !dbg !2390

if.then:                                          ; preds = %entry
  %3 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2391
  %pending_buf_size1 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %3, i32 0, i32 3, !dbg !2393
  %4 = load i64, i64* %pending_buf_size1, align 8, !dbg !2393
  %sub2 = sub i64 %4, 5, !dbg !2394
  store i64 %sub2, i64* %max_block_size, align 8, !dbg !2395
  br label %if.end, !dbg !2396

if.end:                                           ; preds = %if.then, %entry
  br label %for.cond, !dbg !2397

for.cond:                                         ; preds = %if.end83, %if.end
  %5 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2398
  %lookahead = getelementptr inbounds %struct.internal_state, %struct.internal_state* %5, i32 0, i32 29, !dbg !2403
  %6 = load i32, i32* %lookahead, align 4, !dbg !2403
  %cmp3 = icmp ule i32 %6, 1, !dbg !2404
  br i1 %cmp3, label %if.then4, label %if.end14, !dbg !2405

if.then4:                                         ; preds = %for.cond
  %7 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2406
  call void @fill_window(%struct.internal_state* %7), !dbg !2408
  %8 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2409
  %lookahead5 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %8, i32 0, i32 29, !dbg !2411
  %9 = load i32, i32* %lookahead5, align 4, !dbg !2411
  %cmp6 = icmp eq i32 %9, 0, !dbg !2412
  br i1 %cmp6, label %land.lhs.true, label %if.end9, !dbg !2413

land.lhs.true:                                    ; preds = %if.then4
  %10 = load i32, i32* %flush.addr, align 4, !dbg !2414
  %cmp7 = icmp eq i32 %10, 0, !dbg !2416
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !2417

if.then8:                                         ; preds = %land.lhs.true
  store i32 0, i32* %retval, align 4, !dbg !2418
  br label %return, !dbg !2418

if.end9:                                          ; preds = %land.lhs.true, %if.then4
  %11 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2420
  %lookahead10 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %11, i32 0, i32 29, !dbg !2422
  %12 = load i32, i32* %lookahead10, align 4, !dbg !2422
  %cmp11 = icmp eq i32 %12, 0, !dbg !2423
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !2424

if.then12:                                        ; preds = %if.end9
  br label %for.end, !dbg !2425

if.end13:                                         ; preds = %if.end9
  br label %if.end14, !dbg !2427

if.end14:                                         ; preds = %if.end13, %for.cond
  %13 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2428
  %lookahead15 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %13, i32 0, i32 29, !dbg !2429
  %14 = load i32, i32* %lookahead15, align 4, !dbg !2429
  %15 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2430
  %strstart = getelementptr inbounds %struct.internal_state, %struct.internal_state* %15, i32 0, i32 27, !dbg !2431
  %16 = load i32, i32* %strstart, align 4, !dbg !2432
  %add = add i32 %16, %14, !dbg !2432
  store i32 %add, i32* %strstart, align 4, !dbg !2432
  %17 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2433
  %lookahead16 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %17, i32 0, i32 29, !dbg !2434
  store i32 0, i32* %lookahead16, align 4, !dbg !2435
  %18 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2436
  %block_start = getelementptr inbounds %struct.internal_state, %struct.internal_state* %18, i32 0, i32 23, !dbg !2437
  %19 = load i64, i64* %block_start, align 8, !dbg !2437
  %20 = load i64, i64* %max_block_size, align 8, !dbg !2438
  %add17 = add i64 %19, %20, !dbg !2439
  store i64 %add17, i64* %max_start, align 8, !dbg !2440
  %21 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2441
  %strstart18 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %21, i32 0, i32 27, !dbg !2443
  %22 = load i32, i32* %strstart18, align 4, !dbg !2443
  %cmp19 = icmp eq i32 %22, 0, !dbg !2444
  br i1 %cmp19, label %if.then23, label %lor.lhs.false, !dbg !2445

lor.lhs.false:                                    ; preds = %if.end14
  %23 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2446
  %strstart20 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %23, i32 0, i32 27, !dbg !2448
  %24 = load i32, i32* %strstart20, align 4, !dbg !2448
  %conv = zext i32 %24 to i64, !dbg !2449
  %25 = load i64, i64* %max_start, align 8, !dbg !2450
  %cmp21 = icmp uge i64 %conv, %25, !dbg !2451
  br i1 %cmp21, label %if.then23, label %if.end48, !dbg !2452

if.then23:                                        ; preds = %lor.lhs.false, %if.end14
  %26 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2453
  %strstart24 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %26, i32 0, i32 27, !dbg !2455
  %27 = load i32, i32* %strstart24, align 4, !dbg !2455
  %conv25 = zext i32 %27 to i64, !dbg !2453
  %28 = load i64, i64* %max_start, align 8, !dbg !2456
  %sub26 = sub i64 %conv25, %28, !dbg !2457
  %conv27 = trunc i64 %sub26 to i32, !dbg !2458
  %29 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2459
  %lookahead28 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %29, i32 0, i32 29, !dbg !2460
  store i32 %conv27, i32* %lookahead28, align 4, !dbg !2461
  %30 = load i64, i64* %max_start, align 8, !dbg !2462
  %conv29 = trunc i64 %30 to i32, !dbg !2463
  %31 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2464
  %strstart30 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %31, i32 0, i32 27, !dbg !2465
  store i32 %conv29, i32* %strstart30, align 4, !dbg !2466
  %32 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2467
  %33 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2467
  %block_start31 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %33, i32 0, i32 23, !dbg !2467
  %34 = load i64, i64* %block_start31, align 8, !dbg !2467
  %cmp32 = icmp sge i64 %34, 0, !dbg !2467
  br i1 %cmp32, label %cond.true, label %cond.false, !dbg !2467

cond.true:                                        ; preds = %if.then23
  %35 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2470
  %block_start34 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %35, i32 0, i32 23, !dbg !2470
  %36 = load i64, i64* %block_start34, align 8, !dbg !2470
  %conv35 = trunc i64 %36 to i32, !dbg !2470
  %idxprom = zext i32 %conv35 to i64, !dbg !2470
  %37 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2470
  %window = getelementptr inbounds %struct.internal_state, %struct.internal_state* %37, i32 0, i32 14, !dbg !2470
  %38 = load i8*, i8** %window, align 8, !dbg !2470
  %arrayidx = getelementptr inbounds i8, i8* %38, i64 %idxprom, !dbg !2470
  br label %cond.end, !dbg !2470

cond.false:                                       ; preds = %if.then23
  br label %cond.end, !dbg !2472

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i8* [ %arrayidx, %cond.true ], [ null, %cond.false ], !dbg !2474
  %39 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2474
  %strstart36 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %39, i32 0, i32 27, !dbg !2474
  %40 = load i32, i32* %strstart36, align 4, !dbg !2474
  %conv37 = zext i32 %40 to i64, !dbg !2474
  %41 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2474
  %block_start38 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %41, i32 0, i32 23, !dbg !2474
  %42 = load i64, i64* %block_start38, align 8, !dbg !2474
  %sub39 = sub nsw i64 %conv37, %42, !dbg !2474
  call void @cm_zlib__tr_flush_block(%struct.internal_state* %32, i8* %cond, i64 %sub39, i32 0), !dbg !2474
  %43 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2474
  %strstart40 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %43, i32 0, i32 27, !dbg !2474
  %44 = load i32, i32* %strstart40, align 4, !dbg !2474
  %conv41 = zext i32 %44 to i64, !dbg !2474
  %45 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2474
  %block_start42 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %45, i32 0, i32 23, !dbg !2474
  store i64 %conv41, i64* %block_start42, align 8, !dbg !2474
  %46 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2474
  %strm = getelementptr inbounds %struct.internal_state, %struct.internal_state* %46, i32 0, i32 0, !dbg !2474
  %47 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2474
  call void @flush_pending(%struct.z_stream_s* %47), !dbg !2476
  %48 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2474
  %strm43 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %48, i32 0, i32 0, !dbg !2474
  %49 = load %struct.z_stream_s*, %struct.z_stream_s** %strm43, align 8, !dbg !2474
  %avail_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %49, i32 0, i32 4, !dbg !2474
  %50 = load i32, i32* %avail_out, align 8, !dbg !2474
  %cmp44 = icmp eq i32 %50, 0, !dbg !2474
  br i1 %cmp44, label %if.then46, label %if.end47, !dbg !2474

if.then46:                                        ; preds = %cond.end
  store i32 0, i32* %retval, align 4, !dbg !2478
  br label %return, !dbg !2478

if.end47:                                         ; preds = %cond.end
  br label %if.end48, !dbg !2481

if.end48:                                         ; preds = %if.end47, %lor.lhs.false
  %51 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2482
  %strstart49 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %51, i32 0, i32 27, !dbg !2484
  %52 = load i32, i32* %strstart49, align 4, !dbg !2484
  %53 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2485
  %block_start50 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %53, i32 0, i32 23, !dbg !2486
  %54 = load i64, i64* %block_start50, align 8, !dbg !2486
  %conv51 = trunc i64 %54 to i32, !dbg !2487
  %sub52 = sub i32 %52, %conv51, !dbg !2488
  %55 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2489
  %w_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %55, i32 0, i32 11, !dbg !2489
  %56 = load i32, i32* %w_size, align 4, !dbg !2489
  %sub53 = sub i32 %56, 262, !dbg !2489
  %cmp54 = icmp uge i32 %sub52, %sub53, !dbg !2490
  br i1 %cmp54, label %if.then56, label %if.end83, !dbg !2491

if.then56:                                        ; preds = %if.end48
  %57 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2492
  %58 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2492
  %block_start57 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %58, i32 0, i32 23, !dbg !2492
  %59 = load i64, i64* %block_start57, align 8, !dbg !2492
  %cmp58 = icmp sge i64 %59, 0, !dbg !2492
  br i1 %cmp58, label %cond.true60, label %cond.false66, !dbg !2492

cond.true60:                                      ; preds = %if.then56
  %60 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2496
  %block_start61 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %60, i32 0, i32 23, !dbg !2496
  %61 = load i64, i64* %block_start61, align 8, !dbg !2496
  %conv62 = trunc i64 %61 to i32, !dbg !2496
  %idxprom63 = zext i32 %conv62 to i64, !dbg !2496
  %62 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2496
  %window64 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %62, i32 0, i32 14, !dbg !2496
  %63 = load i8*, i8** %window64, align 8, !dbg !2496
  %arrayidx65 = getelementptr inbounds i8, i8* %63, i64 %idxprom63, !dbg !2496
  br label %cond.end67, !dbg !2496

cond.false66:                                     ; preds = %if.then56
  br label %cond.end67, !dbg !2498

cond.end67:                                       ; preds = %cond.false66, %cond.true60
  %cond68 = phi i8* [ %arrayidx65, %cond.true60 ], [ null, %cond.false66 ], !dbg !2500
  %64 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2500
  %strstart69 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %64, i32 0, i32 27, !dbg !2500
  %65 = load i32, i32* %strstart69, align 4, !dbg !2500
  %conv70 = zext i32 %65 to i64, !dbg !2500
  %66 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2500
  %block_start71 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %66, i32 0, i32 23, !dbg !2500
  %67 = load i64, i64* %block_start71, align 8, !dbg !2500
  %sub72 = sub nsw i64 %conv70, %67, !dbg !2500
  call void @cm_zlib__tr_flush_block(%struct.internal_state* %57, i8* %cond68, i64 %sub72, i32 0), !dbg !2500
  %68 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2500
  %strstart73 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %68, i32 0, i32 27, !dbg !2500
  %69 = load i32, i32* %strstart73, align 4, !dbg !2500
  %conv74 = zext i32 %69 to i64, !dbg !2500
  %70 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2500
  %block_start75 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %70, i32 0, i32 23, !dbg !2500
  store i64 %conv74, i64* %block_start75, align 8, !dbg !2500
  %71 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2500
  %strm76 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %71, i32 0, i32 0, !dbg !2500
  %72 = load %struct.z_stream_s*, %struct.z_stream_s** %strm76, align 8, !dbg !2500
  call void @flush_pending(%struct.z_stream_s* %72), !dbg !2502
  %73 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2500
  %strm77 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %73, i32 0, i32 0, !dbg !2500
  %74 = load %struct.z_stream_s*, %struct.z_stream_s** %strm77, align 8, !dbg !2500
  %avail_out78 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %74, i32 0, i32 4, !dbg !2500
  %75 = load i32, i32* %avail_out78, align 8, !dbg !2500
  %cmp79 = icmp eq i32 %75, 0, !dbg !2500
  br i1 %cmp79, label %if.then81, label %if.end82, !dbg !2500

if.then81:                                        ; preds = %cond.end67
  store i32 0, i32* %retval, align 4, !dbg !2504
  br label %return, !dbg !2504

if.end82:                                         ; preds = %cond.end67
  br label %if.end83, !dbg !2507

if.end83:                                         ; preds = %if.end82, %if.end48
  br label %for.cond, !dbg !2508

for.end:                                          ; preds = %if.then12
  %76 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2510
  %77 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2510
  %block_start84 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %77, i32 0, i32 23, !dbg !2510
  %78 = load i64, i64* %block_start84, align 8, !dbg !2510
  %cmp85 = icmp sge i64 %78, 0, !dbg !2510
  br i1 %cmp85, label %cond.true87, label %cond.false93, !dbg !2510

cond.true87:                                      ; preds = %for.end
  %79 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2513
  %block_start88 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %79, i32 0, i32 23, !dbg !2513
  %80 = load i64, i64* %block_start88, align 8, !dbg !2513
  %conv89 = trunc i64 %80 to i32, !dbg !2513
  %idxprom90 = zext i32 %conv89 to i64, !dbg !2513
  %81 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2513
  %window91 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %81, i32 0, i32 14, !dbg !2513
  %82 = load i8*, i8** %window91, align 8, !dbg !2513
  %arrayidx92 = getelementptr inbounds i8, i8* %82, i64 %idxprom90, !dbg !2513
  br label %cond.end94, !dbg !2513

cond.false93:                                     ; preds = %for.end
  br label %cond.end94, !dbg !2515

cond.end94:                                       ; preds = %cond.false93, %cond.true87
  %cond95 = phi i8* [ %arrayidx92, %cond.true87 ], [ null, %cond.false93 ], !dbg !2517
  %83 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2517
  %strstart96 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %83, i32 0, i32 27, !dbg !2517
  %84 = load i32, i32* %strstart96, align 4, !dbg !2517
  %conv97 = zext i32 %84 to i64, !dbg !2517
  %85 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2517
  %block_start98 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %85, i32 0, i32 23, !dbg !2517
  %86 = load i64, i64* %block_start98, align 8, !dbg !2517
  %sub99 = sub nsw i64 %conv97, %86, !dbg !2517
  %87 = load i32, i32* %flush.addr, align 4, !dbg !2517
  %cmp100 = icmp eq i32 %87, 4, !dbg !2517
  %conv101 = zext i1 %cmp100 to i32, !dbg !2517
  call void @cm_zlib__tr_flush_block(%struct.internal_state* %76, i8* %cond95, i64 %sub99, i32 %conv101), !dbg !2517
  %88 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2517
  %strstart102 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %88, i32 0, i32 27, !dbg !2517
  %89 = load i32, i32* %strstart102, align 4, !dbg !2517
  %conv103 = zext i32 %89 to i64, !dbg !2517
  %90 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2517
  %block_start104 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %90, i32 0, i32 23, !dbg !2517
  store i64 %conv103, i64* %block_start104, align 8, !dbg !2517
  %91 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2517
  %strm105 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %91, i32 0, i32 0, !dbg !2517
  %92 = load %struct.z_stream_s*, %struct.z_stream_s** %strm105, align 8, !dbg !2517
  call void @flush_pending(%struct.z_stream_s* %92), !dbg !2519
  %93 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2517
  %strm106 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %93, i32 0, i32 0, !dbg !2517
  %94 = load %struct.z_stream_s*, %struct.z_stream_s** %strm106, align 8, !dbg !2517
  %avail_out107 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %94, i32 0, i32 4, !dbg !2517
  %95 = load i32, i32* %avail_out107, align 8, !dbg !2517
  %cmp108 = icmp eq i32 %95, 0, !dbg !2517
  br i1 %cmp108, label %if.then110, label %if.end114, !dbg !2517

if.then110:                                       ; preds = %cond.end94
  %96 = load i32, i32* %flush.addr, align 4, !dbg !2521
  %cmp111 = icmp eq i32 %96, 4, !dbg !2521
  %cond113 = select i1 %cmp111, i32 2, i32 0, !dbg !2521
  store i32 %cond113, i32* %retval, align 4, !dbg !2521
  br label %return, !dbg !2521

if.end114:                                        ; preds = %cond.end94
  %97 = load i32, i32* %flush.addr, align 4, !dbg !2524
  %cmp115 = icmp eq i32 %97, 4, !dbg !2525
  %cond117 = select i1 %cmp115, i32 3, i32 1, !dbg !2524
  store i32 %cond117, i32* %retval, align 4, !dbg !2526
  br label %return, !dbg !2526

return:                                           ; preds = %if.end114, %if.then110, %if.then81, %if.then46, %if.then8
  %98 = load i32, i32* %retval, align 4, !dbg !2527
  ret i32 %98, !dbg !2527
}

; Function Attrs: nounwind uwtable
define internal i32 @deflate_fast(%struct.internal_state* %s, i32 %flush) #0 !dbg !236 {
entry:
  %retval = alloca i32, align 4
  %s.addr = alloca %struct.internal_state*, align 8
  %flush.addr = alloca i32, align 4
  %hash_head = alloca i32, align 4
  %bflush = alloca i32, align 4
  %len = alloca i8, align 1
  %dist = alloca i16, align 2
  %cc = alloca i8, align 1
  store %struct.internal_state* %s, %struct.internal_state** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.internal_state** %s.addr, metadata !2528, metadata !277), !dbg !2529
  store i32 %flush, i32* %flush.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flush.addr, metadata !2530, metadata !277), !dbg !2531
  call void @llvm.dbg.declare(metadata i32* %hash_head, metadata !2532, metadata !277), !dbg !2533
  store i32 0, i32* %hash_head, align 4, !dbg !2533
  call void @llvm.dbg.declare(metadata i32* %bflush, metadata !2534, metadata !277), !dbg !2535
  br label %for.cond, !dbg !2536

for.cond:                                         ; preds = %if.end231, %entry
  %0 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2537
  %lookahead = getelementptr inbounds %struct.internal_state, %struct.internal_state* %0, i32 0, i32 29, !dbg !2542
  %1 = load i32, i32* %lookahead, align 4, !dbg !2542
  %cmp = icmp ult i32 %1, 262, !dbg !2543
  br i1 %cmp, label %if.then, label %if.end9, !dbg !2544

if.then:                                          ; preds = %for.cond
  %2 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2545
  call void @fill_window(%struct.internal_state* %2), !dbg !2547
  %3 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2548
  %lookahead1 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %3, i32 0, i32 29, !dbg !2550
  %4 = load i32, i32* %lookahead1, align 4, !dbg !2550
  %cmp2 = icmp ult i32 %4, 262, !dbg !2551
  br i1 %cmp2, label %land.lhs.true, label %if.end, !dbg !2552

land.lhs.true:                                    ; preds = %if.then
  %5 = load i32, i32* %flush.addr, align 4, !dbg !2553
  %cmp3 = icmp eq i32 %5, 0, !dbg !2555
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !2556

if.then4:                                         ; preds = %land.lhs.true
  store i32 0, i32* %retval, align 4, !dbg !2557
  br label %return, !dbg !2557

if.end:                                           ; preds = %land.lhs.true, %if.then
  %6 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2559
  %lookahead5 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %6, i32 0, i32 29, !dbg !2561
  %7 = load i32, i32* %lookahead5, align 4, !dbg !2561
  %cmp6 = icmp eq i32 %7, 0, !dbg !2562
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !2563

if.then7:                                         ; preds = %if.end
  br label %for.end, !dbg !2564

if.end8:                                          ; preds = %if.end
  br label %if.end9, !dbg !2566

if.end9:                                          ; preds = %if.end8, %for.cond
  %8 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2567
  %lookahead10 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %8, i32 0, i32 29, !dbg !2569
  %9 = load i32, i32* %lookahead10, align 4, !dbg !2569
  %cmp11 = icmp uge i32 %9, 3, !dbg !2570
  br i1 %cmp11, label %if.then12, label %if.end28, !dbg !2571

if.then12:                                        ; preds = %if.end9
  %10 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2572
  %ins_h = getelementptr inbounds %struct.internal_state, %struct.internal_state* %10, i32 0, i32 18, !dbg !2572
  %11 = load i32, i32* %ins_h, align 8, !dbg !2572
  %12 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2572
  %hash_shift = getelementptr inbounds %struct.internal_state, %struct.internal_state* %12, i32 0, i32 22, !dbg !2572
  %13 = load i32, i32* %hash_shift, align 8, !dbg !2572
  %shl = shl i32 %11, %13, !dbg !2572
  %14 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2572
  %strstart = getelementptr inbounds %struct.internal_state, %struct.internal_state* %14, i32 0, i32 27, !dbg !2572
  %15 = load i32, i32* %strstart, align 4, !dbg !2572
  %add = add i32 %15, 2, !dbg !2572
  %idxprom = zext i32 %add to i64, !dbg !2572
  %16 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2572
  %window = getelementptr inbounds %struct.internal_state, %struct.internal_state* %16, i32 0, i32 14, !dbg !2572
  %17 = load i8*, i8** %window, align 8, !dbg !2572
  %arrayidx = getelementptr inbounds i8, i8* %17, i64 %idxprom, !dbg !2572
  %18 = load i8, i8* %arrayidx, align 1, !dbg !2572
  %conv = zext i8 %18 to i32, !dbg !2572
  %xor = xor i32 %shl, %conv, !dbg !2572
  %19 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2572
  %hash_mask = getelementptr inbounds %struct.internal_state, %struct.internal_state* %19, i32 0, i32 21, !dbg !2572
  %20 = load i32, i32* %hash_mask, align 4, !dbg !2572
  %and = and i32 %xor, %20, !dbg !2572
  %21 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2572
  %ins_h13 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %21, i32 0, i32 18, !dbg !2572
  store i32 %and, i32* %ins_h13, align 8, !dbg !2572
  %22 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2572
  %ins_h14 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %22, i32 0, i32 18, !dbg !2572
  %23 = load i32, i32* %ins_h14, align 8, !dbg !2572
  %idxprom15 = zext i32 %23 to i64, !dbg !2572
  %24 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2572
  %head = getelementptr inbounds %struct.internal_state, %struct.internal_state* %24, i32 0, i32 17, !dbg !2572
  %25 = load i16*, i16** %head, align 8, !dbg !2572
  %arrayidx16 = getelementptr inbounds i16, i16* %25, i64 %idxprom15, !dbg !2572
  %26 = load i16, i16* %arrayidx16, align 2, !dbg !2572
  %27 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2572
  %strstart17 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %27, i32 0, i32 27, !dbg !2572
  %28 = load i32, i32* %strstart17, align 4, !dbg !2572
  %29 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2572
  %w_mask = getelementptr inbounds %struct.internal_state, %struct.internal_state* %29, i32 0, i32 13, !dbg !2572
  %30 = load i32, i32* %w_mask, align 4, !dbg !2572
  %and18 = and i32 %28, %30, !dbg !2572
  %idxprom19 = zext i32 %and18 to i64, !dbg !2572
  %31 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2572
  %prev = getelementptr inbounds %struct.internal_state, %struct.internal_state* %31, i32 0, i32 16, !dbg !2572
  %32 = load i16*, i16** %prev, align 8, !dbg !2572
  %arrayidx20 = getelementptr inbounds i16, i16* %32, i64 %idxprom19, !dbg !2572
  store i16 %26, i16* %arrayidx20, align 2, !dbg !2572
  %conv21 = zext i16 %26 to i32, !dbg !2572
  store i32 %conv21, i32* %hash_head, align 4, !dbg !2572
  %33 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2572
  %strstart22 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %33, i32 0, i32 27, !dbg !2572
  %34 = load i32, i32* %strstart22, align 4, !dbg !2572
  %conv23 = trunc i32 %34 to i16, !dbg !2572
  %35 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2572
  %ins_h24 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %35, i32 0, i32 18, !dbg !2572
  %36 = load i32, i32* %ins_h24, align 8, !dbg !2572
  %idxprom25 = zext i32 %36 to i64, !dbg !2572
  %37 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2572
  %head26 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %37, i32 0, i32 17, !dbg !2572
  %38 = load i16*, i16** %head26, align 8, !dbg !2572
  %arrayidx27 = getelementptr inbounds i16, i16* %38, i64 %idxprom25, !dbg !2572
  store i16 %conv23, i16* %arrayidx27, align 2, !dbg !2572
  br label %if.end28, !dbg !2574

if.end28:                                         ; preds = %if.then12, %if.end9
  %39 = load i32, i32* %hash_head, align 4, !dbg !2575
  %cmp29 = icmp ne i32 %39, 0, !dbg !2577
  br i1 %cmp29, label %land.lhs.true31, label %if.end57, !dbg !2578

land.lhs.true31:                                  ; preds = %if.end28
  %40 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2579
  %strstart32 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %40, i32 0, i32 27, !dbg !2581
  %41 = load i32, i32* %strstart32, align 4, !dbg !2581
  %42 = load i32, i32* %hash_head, align 4, !dbg !2582
  %sub = sub i32 %41, %42, !dbg !2583
  %43 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2584
  %w_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %43, i32 0, i32 11, !dbg !2584
  %44 = load i32, i32* %w_size, align 4, !dbg !2584
  %sub33 = sub i32 %44, 262, !dbg !2584
  %cmp34 = icmp ule i32 %sub, %sub33, !dbg !2585
  br i1 %cmp34, label %if.then36, label %if.end57, !dbg !2586

if.then36:                                        ; preds = %land.lhs.true31
  %45 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2587
  %strategy = getelementptr inbounds %struct.internal_state, %struct.internal_state* %45, i32 0, i32 34, !dbg !2590
  %46 = load i32, i32* %strategy, align 8, !dbg !2590
  %cmp37 = icmp ne i32 %46, 2, !dbg !2591
  br i1 %cmp37, label %land.lhs.true39, label %if.else, !dbg !2592

land.lhs.true39:                                  ; preds = %if.then36
  %47 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2593
  %strategy40 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %47, i32 0, i32 34, !dbg !2595
  %48 = load i32, i32* %strategy40, align 8, !dbg !2595
  %cmp41 = icmp ne i32 %48, 3, !dbg !2596
  br i1 %cmp41, label %if.then43, label %if.else, !dbg !2597

if.then43:                                        ; preds = %land.lhs.true39
  %49 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2598
  %50 = load i32, i32* %hash_head, align 4, !dbg !2600
  %call = call i32 @longest_match(%struct.internal_state* %49, i32 %50), !dbg !2601
  %51 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2602
  %match_length = getelementptr inbounds %struct.internal_state, %struct.internal_state* %51, i32 0, i32 24, !dbg !2603
  store i32 %call, i32* %match_length, align 8, !dbg !2604
  br label %if.end56, !dbg !2605

if.else:                                          ; preds = %land.lhs.true39, %if.then36
  %52 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2606
  %strategy44 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %52, i32 0, i32 34, !dbg !2609
  %53 = load i32, i32* %strategy44, align 8, !dbg !2609
  %cmp45 = icmp eq i32 %53, 3, !dbg !2610
  br i1 %cmp45, label %land.lhs.true47, label %if.end55, !dbg !2611

land.lhs.true47:                                  ; preds = %if.else
  %54 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2612
  %strstart48 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %54, i32 0, i32 27, !dbg !2614
  %55 = load i32, i32* %strstart48, align 4, !dbg !2614
  %56 = load i32, i32* %hash_head, align 4, !dbg !2615
  %sub49 = sub i32 %55, %56, !dbg !2616
  %cmp50 = icmp eq i32 %sub49, 1, !dbg !2617
  br i1 %cmp50, label %if.then52, label %if.end55, !dbg !2618

if.then52:                                        ; preds = %land.lhs.true47
  %57 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2619
  %58 = load i32, i32* %hash_head, align 4, !dbg !2621
  %call53 = call i32 @longest_match_fast(%struct.internal_state* %57, i32 %58), !dbg !2622
  %59 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2623
  %match_length54 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %59, i32 0, i32 24, !dbg !2624
  store i32 %call53, i32* %match_length54, align 8, !dbg !2625
  br label %if.end55, !dbg !2626

if.end55:                                         ; preds = %if.then52, %land.lhs.true47, %if.else
  br label %if.end56

if.end56:                                         ; preds = %if.end55, %if.then43
  br label %if.end57, !dbg !2627

if.end57:                                         ; preds = %if.end56, %land.lhs.true31, %if.end28
  %60 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2628
  %match_length58 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %60, i32 0, i32 24, !dbg !2630
  %61 = load i32, i32* %match_length58, align 8, !dbg !2630
  %cmp59 = icmp uge i32 %61, 3, !dbg !2631
  br i1 %cmp59, label %if.then61, label %if.else177, !dbg !2632

if.then61:                                        ; preds = %if.end57
  call void @llvm.dbg.declare(metadata i8* %len, metadata !2633, metadata !277), !dbg !2636
  %62 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2636
  %match_length62 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %62, i32 0, i32 24, !dbg !2636
  %63 = load i32, i32* %match_length62, align 8, !dbg !2636
  %sub63 = sub i32 %63, 3, !dbg !2636
  %conv64 = trunc i32 %sub63 to i8, !dbg !2636
  store i8 %conv64, i8* %len, align 1, !dbg !2636
  call void @llvm.dbg.declare(metadata i16* %dist, metadata !2637, metadata !277), !dbg !2636
  %64 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2636
  %strstart65 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %64, i32 0, i32 27, !dbg !2636
  %65 = load i32, i32* %strstart65, align 4, !dbg !2636
  %66 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2636
  %match_start = getelementptr inbounds %struct.internal_state, %struct.internal_state* %66, i32 0, i32 28, !dbg !2636
  %67 = load i32, i32* %match_start, align 8, !dbg !2636
  %sub66 = sub i32 %65, %67, !dbg !2636
  %conv67 = trunc i32 %sub66 to i16, !dbg !2636
  store i16 %conv67, i16* %dist, align 2, !dbg !2636
  %68 = load i16, i16* %dist, align 2, !dbg !2636
  %69 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2636
  %last_lit = getelementptr inbounds %struct.internal_state, %struct.internal_state* %69, i32 0, i32 50, !dbg !2636
  %70 = load i32, i32* %last_lit, align 4, !dbg !2636
  %idxprom68 = zext i32 %70 to i64, !dbg !2636
  %71 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2636
  %d_buf = getelementptr inbounds %struct.internal_state, %struct.internal_state* %71, i32 0, i32 51, !dbg !2636
  %72 = load i16*, i16** %d_buf, align 8, !dbg !2636
  %arrayidx69 = getelementptr inbounds i16, i16* %72, i64 %idxprom68, !dbg !2636
  store i16 %68, i16* %arrayidx69, align 2, !dbg !2636
  %73 = load i8, i8* %len, align 1, !dbg !2636
  %74 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2636
  %last_lit70 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %74, i32 0, i32 50, !dbg !2636
  %75 = load i32, i32* %last_lit70, align 4, !dbg !2636
  %inc = add i32 %75, 1, !dbg !2636
  store i32 %inc, i32* %last_lit70, align 4, !dbg !2636
  %idxprom71 = zext i32 %75 to i64, !dbg !2636
  %76 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2636
  %l_buf = getelementptr inbounds %struct.internal_state, %struct.internal_state* %76, i32 0, i32 48, !dbg !2636
  %77 = load i8*, i8** %l_buf, align 8, !dbg !2636
  %arrayidx72 = getelementptr inbounds i8, i8* %77, i64 %idxprom71, !dbg !2636
  store i8 %73, i8* %arrayidx72, align 1, !dbg !2636
  %78 = load i16, i16* %dist, align 2, !dbg !2636
  %dec = add i16 %78, -1, !dbg !2636
  store i16 %dec, i16* %dist, align 2, !dbg !2636
  %79 = load i8, i8* %len, align 1, !dbg !2636
  %idxprom73 = zext i8 %79 to i64, !dbg !2636
  %arrayidx74 = getelementptr inbounds [0 x i8], [0 x i8]* @cm_zlib__length_code, i64 0, i64 %idxprom73, !dbg !2636
  %80 = load i8, i8* %arrayidx74, align 1, !dbg !2636
  %conv75 = zext i8 %80 to i32, !dbg !2636
  %add76 = add nsw i32 %conv75, 256, !dbg !2636
  %add77 = add nsw i32 %add76, 1, !dbg !2636
  %idxprom78 = sext i32 %add77 to i64, !dbg !2636
  %81 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2636
  %dyn_ltree = getelementptr inbounds %struct.internal_state, %struct.internal_state* %81, i32 0, i32 37, !dbg !2636
  %arrayidx79 = getelementptr inbounds [573 x %struct.ct_data_s], [573 x %struct.ct_data_s]* %dyn_ltree, i64 0, i64 %idxprom78, !dbg !2636
  %fc = getelementptr inbounds %struct.ct_data_s, %struct.ct_data_s* %arrayidx79, i32 0, i32 0, !dbg !2636
  %freq = bitcast %union.anon* %fc to i16*, !dbg !2636
  %82 = load i16, i16* %freq, align 4, !dbg !2636
  %inc80 = add i16 %82, 1, !dbg !2636
  store i16 %inc80, i16* %freq, align 4, !dbg !2636
  %83 = load i16, i16* %dist, align 2, !dbg !2636
  %conv81 = zext i16 %83 to i32, !dbg !2636
  %cmp82 = icmp slt i32 %conv81, 256, !dbg !2636
  br i1 %cmp82, label %cond.true, label %cond.false, !dbg !2636

cond.true:                                        ; preds = %if.then61
  %84 = load i16, i16* %dist, align 2, !dbg !2638
  %idxprom84 = zext i16 %84 to i64, !dbg !2638
  %arrayidx85 = getelementptr inbounds [0 x i8], [0 x i8]* @cm_zlib__dist_code, i64 0, i64 %idxprom84, !dbg !2638
  %85 = load i8, i8* %arrayidx85, align 1, !dbg !2638
  %conv86 = zext i8 %85 to i32, !dbg !2638
  br label %cond.end, !dbg !2638

cond.false:                                       ; preds = %if.then61
  %86 = load i16, i16* %dist, align 2, !dbg !2640
  %conv87 = zext i16 %86 to i32, !dbg !2640
  %shr = ashr i32 %conv87, 7, !dbg !2640
  %add88 = add nsw i32 256, %shr, !dbg !2640
  %idxprom89 = sext i32 %add88 to i64, !dbg !2640
  %arrayidx90 = getelementptr inbounds [0 x i8], [0 x i8]* @cm_zlib__dist_code, i64 0, i64 %idxprom89, !dbg !2640
  %87 = load i8, i8* %arrayidx90, align 1, !dbg !2640
  %conv91 = zext i8 %87 to i32, !dbg !2640
  br label %cond.end, !dbg !2640

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %conv86, %cond.true ], [ %conv91, %cond.false ], !dbg !2642
  %idxprom92 = sext i32 %cond to i64, !dbg !2642
  %88 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2642
  %dyn_dtree = getelementptr inbounds %struct.internal_state, %struct.internal_state* %88, i32 0, i32 38, !dbg !2642
  %arrayidx93 = getelementptr inbounds [61 x %struct.ct_data_s], [61 x %struct.ct_data_s]* %dyn_dtree, i64 0, i64 %idxprom92, !dbg !2642
  %fc94 = getelementptr inbounds %struct.ct_data_s, %struct.ct_data_s* %arrayidx93, i32 0, i32 0, !dbg !2642
  %freq95 = bitcast %union.anon* %fc94 to i16*, !dbg !2642
  %89 = load i16, i16* %freq95, align 4, !dbg !2642
  %inc96 = add i16 %89, 1, !dbg !2642
  store i16 %inc96, i16* %freq95, align 4, !dbg !2642
  %90 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2642
  %last_lit97 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %90, i32 0, i32 50, !dbg !2642
  %91 = load i32, i32* %last_lit97, align 4, !dbg !2642
  %92 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2642
  %lit_bufsize = getelementptr inbounds %struct.internal_state, %struct.internal_state* %92, i32 0, i32 49, !dbg !2642
  %93 = load i32, i32* %lit_bufsize, align 8, !dbg !2642
  %sub98 = sub i32 %93, 1, !dbg !2642
  %cmp99 = icmp eq i32 %91, %sub98, !dbg !2642
  %conv100 = zext i1 %cmp99 to i32, !dbg !2642
  store i32 %conv100, i32* %bflush, align 4, !dbg !2642
  %94 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2644
  %match_length101 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %94, i32 0, i32 24, !dbg !2645
  %95 = load i32, i32* %match_length101, align 8, !dbg !2645
  %96 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2646
  %lookahead102 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %96, i32 0, i32 29, !dbg !2647
  %97 = load i32, i32* %lookahead102, align 4, !dbg !2648
  %sub103 = sub i32 %97, %95, !dbg !2648
  store i32 %sub103, i32* %lookahead102, align 4, !dbg !2648
  %98 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2649
  %match_length104 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %98, i32 0, i32 24, !dbg !2651
  %99 = load i32, i32* %match_length104, align 8, !dbg !2651
  %100 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2652
  %max_lazy_match = getelementptr inbounds %struct.internal_state, %struct.internal_state* %100, i32 0, i32 32, !dbg !2653
  %101 = load i32, i32* %max_lazy_match, align 8, !dbg !2653
  %cmp105 = icmp ule i32 %99, %101, !dbg !2654
  br i1 %cmp105, label %land.lhs.true107, label %if.else152, !dbg !2655

land.lhs.true107:                                 ; preds = %cond.end
  %102 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2656
  %lookahead108 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %102, i32 0, i32 29, !dbg !2657
  %103 = load i32, i32* %lookahead108, align 4, !dbg !2657
  %cmp109 = icmp uge i32 %103, 3, !dbg !2658
  br i1 %cmp109, label %if.then111, label %if.else152, !dbg !2659

if.then111:                                       ; preds = %land.lhs.true107
  %104 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2661
  %match_length112 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %104, i32 0, i32 24, !dbg !2663
  %105 = load i32, i32* %match_length112, align 8, !dbg !2664
  %dec113 = add i32 %105, -1, !dbg !2664
  store i32 %dec113, i32* %match_length112, align 8, !dbg !2664
  br label %do.body, !dbg !2665

do.body:                                          ; preds = %do.cond, %if.then111
  %106 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2666
  %strstart114 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %106, i32 0, i32 27, !dbg !2668
  %107 = load i32, i32* %strstart114, align 4, !dbg !2669
  %inc115 = add i32 %107, 1, !dbg !2669
  store i32 %inc115, i32* %strstart114, align 4, !dbg !2669
  %108 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2670
  %ins_h116 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %108, i32 0, i32 18, !dbg !2670
  %109 = load i32, i32* %ins_h116, align 8, !dbg !2670
  %110 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2670
  %hash_shift117 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %110, i32 0, i32 22, !dbg !2670
  %111 = load i32, i32* %hash_shift117, align 8, !dbg !2670
  %shl118 = shl i32 %109, %111, !dbg !2670
  %112 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2670
  %strstart119 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %112, i32 0, i32 27, !dbg !2670
  %113 = load i32, i32* %strstart119, align 4, !dbg !2670
  %add120 = add i32 %113, 2, !dbg !2670
  %idxprom121 = zext i32 %add120 to i64, !dbg !2670
  %114 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2670
  %window122 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %114, i32 0, i32 14, !dbg !2670
  %115 = load i8*, i8** %window122, align 8, !dbg !2670
  %arrayidx123 = getelementptr inbounds i8, i8* %115, i64 %idxprom121, !dbg !2670
  %116 = load i8, i8* %arrayidx123, align 1, !dbg !2670
  %conv124 = zext i8 %116 to i32, !dbg !2670
  %xor125 = xor i32 %shl118, %conv124, !dbg !2670
  %117 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2670
  %hash_mask126 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %117, i32 0, i32 21, !dbg !2670
  %118 = load i32, i32* %hash_mask126, align 4, !dbg !2670
  %and127 = and i32 %xor125, %118, !dbg !2670
  %119 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2670
  %ins_h128 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %119, i32 0, i32 18, !dbg !2670
  store i32 %and127, i32* %ins_h128, align 8, !dbg !2670
  %120 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2670
  %ins_h129 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %120, i32 0, i32 18, !dbg !2670
  %121 = load i32, i32* %ins_h129, align 8, !dbg !2670
  %idxprom130 = zext i32 %121 to i64, !dbg !2670
  %122 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2670
  %head131 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %122, i32 0, i32 17, !dbg !2670
  %123 = load i16*, i16** %head131, align 8, !dbg !2670
  %arrayidx132 = getelementptr inbounds i16, i16* %123, i64 %idxprom130, !dbg !2670
  %124 = load i16, i16* %arrayidx132, align 2, !dbg !2670
  %125 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2670
  %strstart133 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %125, i32 0, i32 27, !dbg !2670
  %126 = load i32, i32* %strstart133, align 4, !dbg !2670
  %127 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2670
  %w_mask134 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %127, i32 0, i32 13, !dbg !2670
  %128 = load i32, i32* %w_mask134, align 4, !dbg !2670
  %and135 = and i32 %126, %128, !dbg !2670
  %idxprom136 = zext i32 %and135 to i64, !dbg !2670
  %129 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2670
  %prev137 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %129, i32 0, i32 16, !dbg !2670
  %130 = load i16*, i16** %prev137, align 8, !dbg !2670
  %arrayidx138 = getelementptr inbounds i16, i16* %130, i64 %idxprom136, !dbg !2670
  store i16 %124, i16* %arrayidx138, align 2, !dbg !2670
  %conv139 = zext i16 %124 to i32, !dbg !2670
  store i32 %conv139, i32* %hash_head, align 4, !dbg !2670
  %131 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2670
  %strstart140 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %131, i32 0, i32 27, !dbg !2670
  %132 = load i32, i32* %strstart140, align 4, !dbg !2670
  %conv141 = trunc i32 %132 to i16, !dbg !2670
  %133 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2670
  %ins_h142 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %133, i32 0, i32 18, !dbg !2670
  %134 = load i32, i32* %ins_h142, align 8, !dbg !2670
  %idxprom143 = zext i32 %134 to i64, !dbg !2670
  %135 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2670
  %head144 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %135, i32 0, i32 17, !dbg !2670
  %136 = load i16*, i16** %head144, align 8, !dbg !2670
  %arrayidx145 = getelementptr inbounds i16, i16* %136, i64 %idxprom143, !dbg !2670
  store i16 %conv141, i16* %arrayidx145, align 2, !dbg !2670
  br label %do.cond, !dbg !2671

do.cond:                                          ; preds = %do.body
  %137 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2672
  %match_length146 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %137, i32 0, i32 24, !dbg !2674
  %138 = load i32, i32* %match_length146, align 8, !dbg !2675
  %dec147 = add i32 %138, -1, !dbg !2675
  store i32 %dec147, i32* %match_length146, align 8, !dbg !2675
  %cmp148 = icmp ne i32 %dec147, 0, !dbg !2676
  br i1 %cmp148, label %do.body, label %do.end, !dbg !2677

do.end:                                           ; preds = %do.cond
  %139 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2678
  %strstart150 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %139, i32 0, i32 27, !dbg !2679
  %140 = load i32, i32* %strstart150, align 4, !dbg !2680
  %inc151 = add i32 %140, 1, !dbg !2680
  store i32 %inc151, i32* %strstart150, align 4, !dbg !2680
  br label %if.end176, !dbg !2681

if.else152:                                       ; preds = %land.lhs.true107, %cond.end
  %141 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2682
  %match_length153 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %141, i32 0, i32 24, !dbg !2684
  %142 = load i32, i32* %match_length153, align 8, !dbg !2684
  %143 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2685
  %strstart154 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %143, i32 0, i32 27, !dbg !2686
  %144 = load i32, i32* %strstart154, align 4, !dbg !2687
  %add155 = add i32 %144, %142, !dbg !2687
  store i32 %add155, i32* %strstart154, align 4, !dbg !2687
  %145 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2688
  %match_length156 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %145, i32 0, i32 24, !dbg !2689
  store i32 0, i32* %match_length156, align 8, !dbg !2690
  %146 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2691
  %strstart157 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %146, i32 0, i32 27, !dbg !2692
  %147 = load i32, i32* %strstart157, align 4, !dbg !2692
  %idxprom158 = zext i32 %147 to i64, !dbg !2693
  %148 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2693
  %window159 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %148, i32 0, i32 14, !dbg !2694
  %149 = load i8*, i8** %window159, align 8, !dbg !2694
  %arrayidx160 = getelementptr inbounds i8, i8* %149, i64 %idxprom158, !dbg !2693
  %150 = load i8, i8* %arrayidx160, align 1, !dbg !2693
  %conv161 = zext i8 %150 to i32, !dbg !2693
  %151 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2695
  %ins_h162 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %151, i32 0, i32 18, !dbg !2696
  store i32 %conv161, i32* %ins_h162, align 8, !dbg !2697
  %152 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2698
  %ins_h163 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %152, i32 0, i32 18, !dbg !2698
  %153 = load i32, i32* %ins_h163, align 8, !dbg !2698
  %154 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2698
  %hash_shift164 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %154, i32 0, i32 22, !dbg !2698
  %155 = load i32, i32* %hash_shift164, align 8, !dbg !2698
  %shl165 = shl i32 %153, %155, !dbg !2698
  %156 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2698
  %strstart166 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %156, i32 0, i32 27, !dbg !2698
  %157 = load i32, i32* %strstart166, align 4, !dbg !2698
  %add167 = add i32 %157, 1, !dbg !2698
  %idxprom168 = zext i32 %add167 to i64, !dbg !2698
  %158 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2698
  %window169 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %158, i32 0, i32 14, !dbg !2698
  %159 = load i8*, i8** %window169, align 8, !dbg !2698
  %arrayidx170 = getelementptr inbounds i8, i8* %159, i64 %idxprom168, !dbg !2698
  %160 = load i8, i8* %arrayidx170, align 1, !dbg !2698
  %conv171 = zext i8 %160 to i32, !dbg !2698
  %xor172 = xor i32 %shl165, %conv171, !dbg !2698
  %161 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2698
  %hash_mask173 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %161, i32 0, i32 21, !dbg !2698
  %162 = load i32, i32* %hash_mask173, align 4, !dbg !2698
  %and174 = and i32 %xor172, %162, !dbg !2698
  %163 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2698
  %ins_h175 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %163, i32 0, i32 18, !dbg !2698
  store i32 %and174, i32* %ins_h175, align 8, !dbg !2698
  br label %if.end176

if.end176:                                        ; preds = %if.else152, %do.end
  br label %if.end206, !dbg !2699

if.else177:                                       ; preds = %if.end57
  call void @llvm.dbg.declare(metadata i8* %cc, metadata !2700, metadata !277), !dbg !2703
  %164 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2703
  %strstart178 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %164, i32 0, i32 27, !dbg !2703
  %165 = load i32, i32* %strstart178, align 4, !dbg !2703
  %idxprom179 = zext i32 %165 to i64, !dbg !2703
  %166 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2703
  %window180 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %166, i32 0, i32 14, !dbg !2703
  %167 = load i8*, i8** %window180, align 8, !dbg !2703
  %arrayidx181 = getelementptr inbounds i8, i8* %167, i64 %idxprom179, !dbg !2703
  %168 = load i8, i8* %arrayidx181, align 1, !dbg !2703
  store i8 %168, i8* %cc, align 1, !dbg !2703
  %169 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2703
  %last_lit182 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %169, i32 0, i32 50, !dbg !2703
  %170 = load i32, i32* %last_lit182, align 4, !dbg !2703
  %idxprom183 = zext i32 %170 to i64, !dbg !2703
  %171 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2703
  %d_buf184 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %171, i32 0, i32 51, !dbg !2703
  %172 = load i16*, i16** %d_buf184, align 8, !dbg !2703
  %arrayidx185 = getelementptr inbounds i16, i16* %172, i64 %idxprom183, !dbg !2703
  store i16 0, i16* %arrayidx185, align 2, !dbg !2703
  %173 = load i8, i8* %cc, align 1, !dbg !2703
  %174 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2703
  %last_lit186 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %174, i32 0, i32 50, !dbg !2703
  %175 = load i32, i32* %last_lit186, align 4, !dbg !2703
  %inc187 = add i32 %175, 1, !dbg !2703
  store i32 %inc187, i32* %last_lit186, align 4, !dbg !2703
  %idxprom188 = zext i32 %175 to i64, !dbg !2703
  %176 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2703
  %l_buf189 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %176, i32 0, i32 48, !dbg !2703
  %177 = load i8*, i8** %l_buf189, align 8, !dbg !2703
  %arrayidx190 = getelementptr inbounds i8, i8* %177, i64 %idxprom188, !dbg !2703
  store i8 %173, i8* %arrayidx190, align 1, !dbg !2703
  %178 = load i8, i8* %cc, align 1, !dbg !2703
  %idxprom191 = zext i8 %178 to i64, !dbg !2703
  %179 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2703
  %dyn_ltree192 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %179, i32 0, i32 37, !dbg !2703
  %arrayidx193 = getelementptr inbounds [573 x %struct.ct_data_s], [573 x %struct.ct_data_s]* %dyn_ltree192, i64 0, i64 %idxprom191, !dbg !2703
  %fc194 = getelementptr inbounds %struct.ct_data_s, %struct.ct_data_s* %arrayidx193, i32 0, i32 0, !dbg !2703
  %freq195 = bitcast %union.anon* %fc194 to i16*, !dbg !2703
  %180 = load i16, i16* %freq195, align 4, !dbg !2703
  %inc196 = add i16 %180, 1, !dbg !2703
  store i16 %inc196, i16* %freq195, align 4, !dbg !2703
  %181 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2703
  %last_lit197 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %181, i32 0, i32 50, !dbg !2703
  %182 = load i32, i32* %last_lit197, align 4, !dbg !2703
  %183 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2703
  %lit_bufsize198 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %183, i32 0, i32 49, !dbg !2703
  %184 = load i32, i32* %lit_bufsize198, align 8, !dbg !2703
  %sub199 = sub i32 %184, 1, !dbg !2703
  %cmp200 = icmp eq i32 %182, %sub199, !dbg !2703
  %conv201 = zext i1 %cmp200 to i32, !dbg !2703
  store i32 %conv201, i32* %bflush, align 4, !dbg !2703
  %185 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2704
  %lookahead202 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %185, i32 0, i32 29, !dbg !2705
  %186 = load i32, i32* %lookahead202, align 4, !dbg !2706
  %dec203 = add i32 %186, -1, !dbg !2706
  store i32 %dec203, i32* %lookahead202, align 4, !dbg !2706
  %187 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2707
  %strstart204 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %187, i32 0, i32 27, !dbg !2708
  %188 = load i32, i32* %strstart204, align 4, !dbg !2709
  %inc205 = add i32 %188, 1, !dbg !2709
  store i32 %inc205, i32* %strstart204, align 4, !dbg !2709
  br label %if.end206

if.end206:                                        ; preds = %if.else177, %if.end176
  %189 = load i32, i32* %bflush, align 4, !dbg !2710
  %tobool = icmp ne i32 %189, 0, !dbg !2710
  br i1 %tobool, label %if.then207, label %if.end231, !dbg !2712

if.then207:                                       ; preds = %if.end206
  %190 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2713
  %191 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2713
  %block_start = getelementptr inbounds %struct.internal_state, %struct.internal_state* %191, i32 0, i32 23, !dbg !2713
  %192 = load i64, i64* %block_start, align 8, !dbg !2713
  %cmp208 = icmp sge i64 %192, 0, !dbg !2713
  br i1 %cmp208, label %cond.true210, label %cond.false216, !dbg !2713

cond.true210:                                     ; preds = %if.then207
  %193 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2717
  %block_start211 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %193, i32 0, i32 23, !dbg !2717
  %194 = load i64, i64* %block_start211, align 8, !dbg !2717
  %conv212 = trunc i64 %194 to i32, !dbg !2717
  %idxprom213 = zext i32 %conv212 to i64, !dbg !2717
  %195 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2717
  %window214 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %195, i32 0, i32 14, !dbg !2717
  %196 = load i8*, i8** %window214, align 8, !dbg !2717
  %arrayidx215 = getelementptr inbounds i8, i8* %196, i64 %idxprom213, !dbg !2717
  br label %cond.end217, !dbg !2717

cond.false216:                                    ; preds = %if.then207
  br label %cond.end217, !dbg !2719

cond.end217:                                      ; preds = %cond.false216, %cond.true210
  %cond218 = phi i8* [ %arrayidx215, %cond.true210 ], [ null, %cond.false216 ], !dbg !2721
  %197 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2721
  %strstart219 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %197, i32 0, i32 27, !dbg !2721
  %198 = load i32, i32* %strstart219, align 4, !dbg !2721
  %conv220 = zext i32 %198 to i64, !dbg !2721
  %199 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2721
  %block_start221 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %199, i32 0, i32 23, !dbg !2721
  %200 = load i64, i64* %block_start221, align 8, !dbg !2721
  %sub222 = sub nsw i64 %conv220, %200, !dbg !2721
  call void @cm_zlib__tr_flush_block(%struct.internal_state* %190, i8* %cond218, i64 %sub222, i32 0), !dbg !2721
  %201 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2721
  %strstart223 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %201, i32 0, i32 27, !dbg !2721
  %202 = load i32, i32* %strstart223, align 4, !dbg !2721
  %conv224 = zext i32 %202 to i64, !dbg !2721
  %203 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2721
  %block_start225 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %203, i32 0, i32 23, !dbg !2721
  store i64 %conv224, i64* %block_start225, align 8, !dbg !2721
  %204 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2721
  %strm = getelementptr inbounds %struct.internal_state, %struct.internal_state* %204, i32 0, i32 0, !dbg !2721
  %205 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2721
  call void @flush_pending(%struct.z_stream_s* %205), !dbg !2723
  %206 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2721
  %strm226 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %206, i32 0, i32 0, !dbg !2721
  %207 = load %struct.z_stream_s*, %struct.z_stream_s** %strm226, align 8, !dbg !2721
  %avail_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %207, i32 0, i32 4, !dbg !2721
  %208 = load i32, i32* %avail_out, align 8, !dbg !2721
  %cmp227 = icmp eq i32 %208, 0, !dbg !2721
  br i1 %cmp227, label %if.then229, label %if.end230, !dbg !2721

if.then229:                                       ; preds = %cond.end217
  store i32 0, i32* %retval, align 4, !dbg !2725
  br label %return, !dbg !2725

if.end230:                                        ; preds = %cond.end217
  br label %if.end231, !dbg !2728

if.end231:                                        ; preds = %if.end230, %if.end206
  br label %for.cond, !dbg !2730

for.end:                                          ; preds = %if.then7
  %209 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2732
  %210 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2732
  %block_start232 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %210, i32 0, i32 23, !dbg !2732
  %211 = load i64, i64* %block_start232, align 8, !dbg !2732
  %cmp233 = icmp sge i64 %211, 0, !dbg !2732
  br i1 %cmp233, label %cond.true235, label %cond.false241, !dbg !2732

cond.true235:                                     ; preds = %for.end
  %212 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2735
  %block_start236 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %212, i32 0, i32 23, !dbg !2735
  %213 = load i64, i64* %block_start236, align 8, !dbg !2735
  %conv237 = trunc i64 %213 to i32, !dbg !2735
  %idxprom238 = zext i32 %conv237 to i64, !dbg !2735
  %214 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2735
  %window239 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %214, i32 0, i32 14, !dbg !2735
  %215 = load i8*, i8** %window239, align 8, !dbg !2735
  %arrayidx240 = getelementptr inbounds i8, i8* %215, i64 %idxprom238, !dbg !2735
  br label %cond.end242, !dbg !2735

cond.false241:                                    ; preds = %for.end
  br label %cond.end242, !dbg !2737

cond.end242:                                      ; preds = %cond.false241, %cond.true235
  %cond243 = phi i8* [ %arrayidx240, %cond.true235 ], [ null, %cond.false241 ], !dbg !2739
  %216 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2739
  %strstart244 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %216, i32 0, i32 27, !dbg !2739
  %217 = load i32, i32* %strstart244, align 4, !dbg !2739
  %conv245 = zext i32 %217 to i64, !dbg !2739
  %218 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2739
  %block_start246 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %218, i32 0, i32 23, !dbg !2739
  %219 = load i64, i64* %block_start246, align 8, !dbg !2739
  %sub247 = sub nsw i64 %conv245, %219, !dbg !2739
  %220 = load i32, i32* %flush.addr, align 4, !dbg !2739
  %cmp248 = icmp eq i32 %220, 4, !dbg !2739
  %conv249 = zext i1 %cmp248 to i32, !dbg !2739
  call void @cm_zlib__tr_flush_block(%struct.internal_state* %209, i8* %cond243, i64 %sub247, i32 %conv249), !dbg !2739
  %221 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2739
  %strstart250 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %221, i32 0, i32 27, !dbg !2739
  %222 = load i32, i32* %strstart250, align 4, !dbg !2739
  %conv251 = zext i32 %222 to i64, !dbg !2739
  %223 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2739
  %block_start252 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %223, i32 0, i32 23, !dbg !2739
  store i64 %conv251, i64* %block_start252, align 8, !dbg !2739
  %224 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2739
  %strm253 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %224, i32 0, i32 0, !dbg !2739
  %225 = load %struct.z_stream_s*, %struct.z_stream_s** %strm253, align 8, !dbg !2739
  call void @flush_pending(%struct.z_stream_s* %225), !dbg !2741
  %226 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2739
  %strm254 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %226, i32 0, i32 0, !dbg !2739
  %227 = load %struct.z_stream_s*, %struct.z_stream_s** %strm254, align 8, !dbg !2739
  %avail_out255 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %227, i32 0, i32 4, !dbg !2739
  %228 = load i32, i32* %avail_out255, align 8, !dbg !2739
  %cmp256 = icmp eq i32 %228, 0, !dbg !2739
  br i1 %cmp256, label %if.then258, label %if.end262, !dbg !2739

if.then258:                                       ; preds = %cond.end242
  %229 = load i32, i32* %flush.addr, align 4, !dbg !2743
  %cmp259 = icmp eq i32 %229, 4, !dbg !2743
  %cond261 = select i1 %cmp259, i32 2, i32 0, !dbg !2743
  store i32 %cond261, i32* %retval, align 4, !dbg !2743
  br label %return, !dbg !2743

if.end262:                                        ; preds = %cond.end242
  %230 = load i32, i32* %flush.addr, align 4, !dbg !2746
  %cmp263 = icmp eq i32 %230, 4, !dbg !2747
  %cond265 = select i1 %cmp263, i32 3, i32 1, !dbg !2746
  store i32 %cond265, i32* %retval, align 4, !dbg !2748
  br label %return, !dbg !2748

return:                                           ; preds = %if.end262, %if.then258, %if.then229, %if.then4
  %231 = load i32, i32* %retval, align 4, !dbg !2749
  ret i32 %231, !dbg !2749
}

; Function Attrs: nounwind uwtable
define internal i32 @deflate_slow(%struct.internal_state* %s, i32 %flush) #0 !dbg !241 {
entry:
  %retval = alloca i32, align 4
  %s.addr = alloca %struct.internal_state*, align 8
  %flush.addr = alloca i32, align 4
  %hash_head = alloca i32, align 4
  %bflush = alloca i32, align 4
  %max_insert = alloca i32, align 4
  %len = alloca i8, align 1
  %dist = alloca i16, align 2
  %cc = alloca i8, align 1
  %cc284 = alloca i8, align 1
  store %struct.internal_state* %s, %struct.internal_state** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.internal_state** %s.addr, metadata !2750, metadata !277), !dbg !2751
  store i32 %flush, i32* %flush.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flush.addr, metadata !2752, metadata !277), !dbg !2753
  call void @llvm.dbg.declare(metadata i32* %hash_head, metadata !2754, metadata !277), !dbg !2755
  store i32 0, i32* %hash_head, align 4, !dbg !2755
  call void @llvm.dbg.declare(metadata i32* %bflush, metadata !2756, metadata !277), !dbg !2757
  br label %for.cond, !dbg !2758

for.cond:                                         ; preds = %if.end280, %entry
  %0 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2759
  %lookahead = getelementptr inbounds %struct.internal_state, %struct.internal_state* %0, i32 0, i32 29, !dbg !2764
  %1 = load i32, i32* %lookahead, align 4, !dbg !2764
  %cmp = icmp ult i32 %1, 262, !dbg !2765
  br i1 %cmp, label %if.then, label %if.end9, !dbg !2766

if.then:                                          ; preds = %for.cond
  %2 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2767
  call void @fill_window(%struct.internal_state* %2), !dbg !2769
  %3 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2770
  %lookahead1 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %3, i32 0, i32 29, !dbg !2772
  %4 = load i32, i32* %lookahead1, align 4, !dbg !2772
  %cmp2 = icmp ult i32 %4, 262, !dbg !2773
  br i1 %cmp2, label %land.lhs.true, label %if.end, !dbg !2774

land.lhs.true:                                    ; preds = %if.then
  %5 = load i32, i32* %flush.addr, align 4, !dbg !2775
  %cmp3 = icmp eq i32 %5, 0, !dbg !2777
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !2778

if.then4:                                         ; preds = %land.lhs.true
  store i32 0, i32* %retval, align 4, !dbg !2779
  br label %return, !dbg !2779

if.end:                                           ; preds = %land.lhs.true, %if.then
  %6 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2781
  %lookahead5 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %6, i32 0, i32 29, !dbg !2783
  %7 = load i32, i32* %lookahead5, align 4, !dbg !2783
  %cmp6 = icmp eq i32 %7, 0, !dbg !2784
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !2785

if.then7:                                         ; preds = %if.end
  br label %for.end, !dbg !2786

if.end8:                                          ; preds = %if.end
  br label %if.end9, !dbg !2788

if.end9:                                          ; preds = %if.end8, %for.cond
  %8 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2789
  %lookahead10 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %8, i32 0, i32 29, !dbg !2791
  %9 = load i32, i32* %lookahead10, align 4, !dbg !2791
  %cmp11 = icmp uge i32 %9, 3, !dbg !2792
  br i1 %cmp11, label %if.then12, label %if.end28, !dbg !2793

if.then12:                                        ; preds = %if.end9
  %10 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2794
  %ins_h = getelementptr inbounds %struct.internal_state, %struct.internal_state* %10, i32 0, i32 18, !dbg !2794
  %11 = load i32, i32* %ins_h, align 8, !dbg !2794
  %12 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2794
  %hash_shift = getelementptr inbounds %struct.internal_state, %struct.internal_state* %12, i32 0, i32 22, !dbg !2794
  %13 = load i32, i32* %hash_shift, align 8, !dbg !2794
  %shl = shl i32 %11, %13, !dbg !2794
  %14 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2794
  %strstart = getelementptr inbounds %struct.internal_state, %struct.internal_state* %14, i32 0, i32 27, !dbg !2794
  %15 = load i32, i32* %strstart, align 4, !dbg !2794
  %add = add i32 %15, 2, !dbg !2794
  %idxprom = zext i32 %add to i64, !dbg !2794
  %16 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2794
  %window = getelementptr inbounds %struct.internal_state, %struct.internal_state* %16, i32 0, i32 14, !dbg !2794
  %17 = load i8*, i8** %window, align 8, !dbg !2794
  %arrayidx = getelementptr inbounds i8, i8* %17, i64 %idxprom, !dbg !2794
  %18 = load i8, i8* %arrayidx, align 1, !dbg !2794
  %conv = zext i8 %18 to i32, !dbg !2794
  %xor = xor i32 %shl, %conv, !dbg !2794
  %19 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2794
  %hash_mask = getelementptr inbounds %struct.internal_state, %struct.internal_state* %19, i32 0, i32 21, !dbg !2794
  %20 = load i32, i32* %hash_mask, align 4, !dbg !2794
  %and = and i32 %xor, %20, !dbg !2794
  %21 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2794
  %ins_h13 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %21, i32 0, i32 18, !dbg !2794
  store i32 %and, i32* %ins_h13, align 8, !dbg !2794
  %22 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2794
  %ins_h14 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %22, i32 0, i32 18, !dbg !2794
  %23 = load i32, i32* %ins_h14, align 8, !dbg !2794
  %idxprom15 = zext i32 %23 to i64, !dbg !2794
  %24 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2794
  %head = getelementptr inbounds %struct.internal_state, %struct.internal_state* %24, i32 0, i32 17, !dbg !2794
  %25 = load i16*, i16** %head, align 8, !dbg !2794
  %arrayidx16 = getelementptr inbounds i16, i16* %25, i64 %idxprom15, !dbg !2794
  %26 = load i16, i16* %arrayidx16, align 2, !dbg !2794
  %27 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2794
  %strstart17 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %27, i32 0, i32 27, !dbg !2794
  %28 = load i32, i32* %strstart17, align 4, !dbg !2794
  %29 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2794
  %w_mask = getelementptr inbounds %struct.internal_state, %struct.internal_state* %29, i32 0, i32 13, !dbg !2794
  %30 = load i32, i32* %w_mask, align 4, !dbg !2794
  %and18 = and i32 %28, %30, !dbg !2794
  %idxprom19 = zext i32 %and18 to i64, !dbg !2794
  %31 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2794
  %prev = getelementptr inbounds %struct.internal_state, %struct.internal_state* %31, i32 0, i32 16, !dbg !2794
  %32 = load i16*, i16** %prev, align 8, !dbg !2794
  %arrayidx20 = getelementptr inbounds i16, i16* %32, i64 %idxprom19, !dbg !2794
  store i16 %26, i16* %arrayidx20, align 2, !dbg !2794
  %conv21 = zext i16 %26 to i32, !dbg !2794
  store i32 %conv21, i32* %hash_head, align 4, !dbg !2794
  %33 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2794
  %strstart22 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %33, i32 0, i32 27, !dbg !2794
  %34 = load i32, i32* %strstart22, align 4, !dbg !2794
  %conv23 = trunc i32 %34 to i16, !dbg !2794
  %35 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2794
  %ins_h24 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %35, i32 0, i32 18, !dbg !2794
  %36 = load i32, i32* %ins_h24, align 8, !dbg !2794
  %idxprom25 = zext i32 %36 to i64, !dbg !2794
  %37 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2794
  %head26 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %37, i32 0, i32 17, !dbg !2794
  %38 = load i16*, i16** %head26, align 8, !dbg !2794
  %arrayidx27 = getelementptr inbounds i16, i16* %38, i64 %idxprom25, !dbg !2794
  store i16 %conv23, i16* %arrayidx27, align 2, !dbg !2794
  br label %if.end28, !dbg !2796

if.end28:                                         ; preds = %if.then12, %if.end9
  %39 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2797
  %match_length = getelementptr inbounds %struct.internal_state, %struct.internal_state* %39, i32 0, i32 24, !dbg !2798
  %40 = load i32, i32* %match_length, align 8, !dbg !2798
  %41 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2799
  %prev_length = getelementptr inbounds %struct.internal_state, %struct.internal_state* %41, i32 0, i32 30, !dbg !2800
  store i32 %40, i32* %prev_length, align 8, !dbg !2801
  %42 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2802
  %match_start = getelementptr inbounds %struct.internal_state, %struct.internal_state* %42, i32 0, i32 28, !dbg !2803
  %43 = load i32, i32* %match_start, align 8, !dbg !2803
  %44 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2804
  %prev_match = getelementptr inbounds %struct.internal_state, %struct.internal_state* %44, i32 0, i32 25, !dbg !2805
  store i32 %43, i32* %prev_match, align 4, !dbg !2806
  %45 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2807
  %match_length29 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %45, i32 0, i32 24, !dbg !2808
  store i32 2, i32* %match_length29, align 8, !dbg !2809
  %46 = load i32, i32* %hash_head, align 4, !dbg !2810
  %cmp30 = icmp ne i32 %46, 0, !dbg !2812
  br i1 %cmp30, label %land.lhs.true32, label %if.end82, !dbg !2813

land.lhs.true32:                                  ; preds = %if.end28
  %47 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2814
  %prev_length33 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %47, i32 0, i32 30, !dbg !2816
  %48 = load i32, i32* %prev_length33, align 8, !dbg !2816
  %49 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2817
  %max_lazy_match = getelementptr inbounds %struct.internal_state, %struct.internal_state* %49, i32 0, i32 32, !dbg !2818
  %50 = load i32, i32* %max_lazy_match, align 8, !dbg !2818
  %cmp34 = icmp ult i32 %48, %50, !dbg !2819
  br i1 %cmp34, label %land.lhs.true36, label %if.end82, !dbg !2820

land.lhs.true36:                                  ; preds = %land.lhs.true32
  %51 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2821
  %strstart37 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %51, i32 0, i32 27, !dbg !2822
  %52 = load i32, i32* %strstart37, align 4, !dbg !2822
  %53 = load i32, i32* %hash_head, align 4, !dbg !2823
  %sub = sub i32 %52, %53, !dbg !2824
  %54 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2825
  %w_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %54, i32 0, i32 11, !dbg !2825
  %55 = load i32, i32* %w_size, align 4, !dbg !2825
  %sub38 = sub i32 %55, 262, !dbg !2825
  %cmp39 = icmp ule i32 %sub, %sub38, !dbg !2826
  br i1 %cmp39, label %if.then41, label %if.end82, !dbg !2827

if.then41:                                        ; preds = %land.lhs.true36
  %56 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2829
  %strategy = getelementptr inbounds %struct.internal_state, %struct.internal_state* %56, i32 0, i32 34, !dbg !2832
  %57 = load i32, i32* %strategy, align 8, !dbg !2832
  %cmp42 = icmp ne i32 %57, 2, !dbg !2833
  br i1 %cmp42, label %land.lhs.true44, label %if.else, !dbg !2834

land.lhs.true44:                                  ; preds = %if.then41
  %58 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2835
  %strategy45 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %58, i32 0, i32 34, !dbg !2837
  %59 = load i32, i32* %strategy45, align 8, !dbg !2837
  %cmp46 = icmp ne i32 %59, 3, !dbg !2838
  br i1 %cmp46, label %if.then48, label %if.else, !dbg !2839

if.then48:                                        ; preds = %land.lhs.true44
  %60 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2840
  %61 = load i32, i32* %hash_head, align 4, !dbg !2842
  %call = call i32 @longest_match(%struct.internal_state* %60, i32 %61), !dbg !2843
  %62 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2844
  %match_length49 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %62, i32 0, i32 24, !dbg !2845
  store i32 %call, i32* %match_length49, align 8, !dbg !2846
  br label %if.end62, !dbg !2847

if.else:                                          ; preds = %land.lhs.true44, %if.then41
  %63 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2848
  %strategy50 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %63, i32 0, i32 34, !dbg !2851
  %64 = load i32, i32* %strategy50, align 8, !dbg !2851
  %cmp51 = icmp eq i32 %64, 3, !dbg !2852
  br i1 %cmp51, label %land.lhs.true53, label %if.end61, !dbg !2853

land.lhs.true53:                                  ; preds = %if.else
  %65 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2854
  %strstart54 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %65, i32 0, i32 27, !dbg !2856
  %66 = load i32, i32* %strstart54, align 4, !dbg !2856
  %67 = load i32, i32* %hash_head, align 4, !dbg !2857
  %sub55 = sub i32 %66, %67, !dbg !2858
  %cmp56 = icmp eq i32 %sub55, 1, !dbg !2859
  br i1 %cmp56, label %if.then58, label %if.end61, !dbg !2860

if.then58:                                        ; preds = %land.lhs.true53
  %68 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2861
  %69 = load i32, i32* %hash_head, align 4, !dbg !2863
  %call59 = call i32 @longest_match_fast(%struct.internal_state* %68, i32 %69), !dbg !2864
  %70 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2865
  %match_length60 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %70, i32 0, i32 24, !dbg !2866
  store i32 %call59, i32* %match_length60, align 8, !dbg !2867
  br label %if.end61, !dbg !2868

if.end61:                                         ; preds = %if.then58, %land.lhs.true53, %if.else
  br label %if.end62

if.end62:                                         ; preds = %if.end61, %if.then48
  %71 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2869
  %match_length63 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %71, i32 0, i32 24, !dbg !2871
  %72 = load i32, i32* %match_length63, align 8, !dbg !2871
  %cmp64 = icmp ule i32 %72, 5, !dbg !2872
  br i1 %cmp64, label %land.lhs.true66, label %if.end81, !dbg !2873

land.lhs.true66:                                  ; preds = %if.end62
  %73 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2874
  %strategy67 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %73, i32 0, i32 34, !dbg !2876
  %74 = load i32, i32* %strategy67, align 8, !dbg !2876
  %cmp68 = icmp eq i32 %74, 1, !dbg !2877
  br i1 %cmp68, label %if.then79, label %lor.lhs.false, !dbg !2878

lor.lhs.false:                                    ; preds = %land.lhs.true66
  %75 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2879
  %match_length70 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %75, i32 0, i32 24, !dbg !2880
  %76 = load i32, i32* %match_length70, align 8, !dbg !2880
  %cmp71 = icmp eq i32 %76, 3, !dbg !2881
  br i1 %cmp71, label %land.lhs.true73, label %if.end81, !dbg !2882

land.lhs.true73:                                  ; preds = %lor.lhs.false
  %77 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2883
  %strstart74 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %77, i32 0, i32 27, !dbg !2884
  %78 = load i32, i32* %strstart74, align 4, !dbg !2884
  %79 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2885
  %match_start75 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %79, i32 0, i32 28, !dbg !2886
  %80 = load i32, i32* %match_start75, align 8, !dbg !2886
  %sub76 = sub i32 %78, %80, !dbg !2887
  %cmp77 = icmp ugt i32 %sub76, 4096, !dbg !2888
  br i1 %cmp77, label %if.then79, label %if.end81, !dbg !2889

if.then79:                                        ; preds = %land.lhs.true73, %land.lhs.true66
  %81 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2891
  %match_length80 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %81, i32 0, i32 24, !dbg !2893
  store i32 2, i32* %match_length80, align 8, !dbg !2894
  br label %if.end81, !dbg !2895

if.end81:                                         ; preds = %if.then79, %land.lhs.true73, %lor.lhs.false, %if.end62
  br label %if.end82, !dbg !2896

if.end82:                                         ; preds = %if.end81, %land.lhs.true36, %land.lhs.true32, %if.end28
  %82 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2897
  %prev_length83 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %82, i32 0, i32 30, !dbg !2899
  %83 = load i32, i32* %prev_length83, align 8, !dbg !2899
  %cmp84 = icmp uge i32 %83, 3, !dbg !2900
  br i1 %cmp84, label %land.lhs.true86, label %if.else211, !dbg !2901

land.lhs.true86:                                  ; preds = %if.end82
  %84 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2902
  %match_length87 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %84, i32 0, i32 24, !dbg !2904
  %85 = load i32, i32* %match_length87, align 8, !dbg !2904
  %86 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2905
  %prev_length88 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %86, i32 0, i32 30, !dbg !2906
  %87 = load i32, i32* %prev_length88, align 8, !dbg !2906
  %cmp89 = icmp ule i32 %85, %87, !dbg !2907
  br i1 %cmp89, label %if.then91, label %if.else211, !dbg !2908

if.then91:                                        ; preds = %land.lhs.true86
  call void @llvm.dbg.declare(metadata i32* %max_insert, metadata !2909, metadata !277), !dbg !2911
  %88 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2912
  %strstart92 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %88, i32 0, i32 27, !dbg !2913
  %89 = load i32, i32* %strstart92, align 4, !dbg !2913
  %90 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2914
  %lookahead93 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %90, i32 0, i32 29, !dbg !2915
  %91 = load i32, i32* %lookahead93, align 4, !dbg !2915
  %add94 = add i32 %89, %91, !dbg !2916
  %sub95 = sub i32 %add94, 3, !dbg !2917
  store i32 %sub95, i32* %max_insert, align 4, !dbg !2911
  call void @llvm.dbg.declare(metadata i8* %len, metadata !2918, metadata !277), !dbg !2920
  %92 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2920
  %prev_length96 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %92, i32 0, i32 30, !dbg !2920
  %93 = load i32, i32* %prev_length96, align 8, !dbg !2920
  %sub97 = sub i32 %93, 3, !dbg !2920
  %conv98 = trunc i32 %sub97 to i8, !dbg !2920
  store i8 %conv98, i8* %len, align 1, !dbg !2920
  call void @llvm.dbg.declare(metadata i16* %dist, metadata !2921, metadata !277), !dbg !2920
  %94 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2920
  %strstart99 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %94, i32 0, i32 27, !dbg !2920
  %95 = load i32, i32* %strstart99, align 4, !dbg !2920
  %sub100 = sub i32 %95, 1, !dbg !2920
  %96 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2920
  %prev_match101 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %96, i32 0, i32 25, !dbg !2920
  %97 = load i32, i32* %prev_match101, align 4, !dbg !2920
  %sub102 = sub i32 %sub100, %97, !dbg !2920
  %conv103 = trunc i32 %sub102 to i16, !dbg !2920
  store i16 %conv103, i16* %dist, align 2, !dbg !2920
  %98 = load i16, i16* %dist, align 2, !dbg !2920
  %99 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2920
  %last_lit = getelementptr inbounds %struct.internal_state, %struct.internal_state* %99, i32 0, i32 50, !dbg !2920
  %100 = load i32, i32* %last_lit, align 4, !dbg !2920
  %idxprom104 = zext i32 %100 to i64, !dbg !2920
  %101 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2920
  %d_buf = getelementptr inbounds %struct.internal_state, %struct.internal_state* %101, i32 0, i32 51, !dbg !2920
  %102 = load i16*, i16** %d_buf, align 8, !dbg !2920
  %arrayidx105 = getelementptr inbounds i16, i16* %102, i64 %idxprom104, !dbg !2920
  store i16 %98, i16* %arrayidx105, align 2, !dbg !2920
  %103 = load i8, i8* %len, align 1, !dbg !2920
  %104 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2920
  %last_lit106 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %104, i32 0, i32 50, !dbg !2920
  %105 = load i32, i32* %last_lit106, align 4, !dbg !2920
  %inc = add i32 %105, 1, !dbg !2920
  store i32 %inc, i32* %last_lit106, align 4, !dbg !2920
  %idxprom107 = zext i32 %105 to i64, !dbg !2920
  %106 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2920
  %l_buf = getelementptr inbounds %struct.internal_state, %struct.internal_state* %106, i32 0, i32 48, !dbg !2920
  %107 = load i8*, i8** %l_buf, align 8, !dbg !2920
  %arrayidx108 = getelementptr inbounds i8, i8* %107, i64 %idxprom107, !dbg !2920
  store i8 %103, i8* %arrayidx108, align 1, !dbg !2920
  %108 = load i16, i16* %dist, align 2, !dbg !2920
  %dec = add i16 %108, -1, !dbg !2920
  store i16 %dec, i16* %dist, align 2, !dbg !2920
  %109 = load i8, i8* %len, align 1, !dbg !2920
  %idxprom109 = zext i8 %109 to i64, !dbg !2920
  %arrayidx110 = getelementptr inbounds [0 x i8], [0 x i8]* @cm_zlib__length_code, i64 0, i64 %idxprom109, !dbg !2920
  %110 = load i8, i8* %arrayidx110, align 1, !dbg !2920
  %conv111 = zext i8 %110 to i32, !dbg !2920
  %add112 = add nsw i32 %conv111, 256, !dbg !2920
  %add113 = add nsw i32 %add112, 1, !dbg !2920
  %idxprom114 = sext i32 %add113 to i64, !dbg !2920
  %111 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2920
  %dyn_ltree = getelementptr inbounds %struct.internal_state, %struct.internal_state* %111, i32 0, i32 37, !dbg !2920
  %arrayidx115 = getelementptr inbounds [573 x %struct.ct_data_s], [573 x %struct.ct_data_s]* %dyn_ltree, i64 0, i64 %idxprom114, !dbg !2920
  %fc = getelementptr inbounds %struct.ct_data_s, %struct.ct_data_s* %arrayidx115, i32 0, i32 0, !dbg !2920
  %freq = bitcast %union.anon* %fc to i16*, !dbg !2920
  %112 = load i16, i16* %freq, align 4, !dbg !2920
  %inc116 = add i16 %112, 1, !dbg !2920
  store i16 %inc116, i16* %freq, align 4, !dbg !2920
  %113 = load i16, i16* %dist, align 2, !dbg !2920
  %conv117 = zext i16 %113 to i32, !dbg !2920
  %cmp118 = icmp slt i32 %conv117, 256, !dbg !2920
  br i1 %cmp118, label %cond.true, label %cond.false, !dbg !2920

cond.true:                                        ; preds = %if.then91
  %114 = load i16, i16* %dist, align 2, !dbg !2922
  %idxprom120 = zext i16 %114 to i64, !dbg !2922
  %arrayidx121 = getelementptr inbounds [0 x i8], [0 x i8]* @cm_zlib__dist_code, i64 0, i64 %idxprom120, !dbg !2922
  %115 = load i8, i8* %arrayidx121, align 1, !dbg !2922
  %conv122 = zext i8 %115 to i32, !dbg !2922
  br label %cond.end, !dbg !2922

cond.false:                                       ; preds = %if.then91
  %116 = load i16, i16* %dist, align 2, !dbg !2924
  %conv123 = zext i16 %116 to i32, !dbg !2924
  %shr = ashr i32 %conv123, 7, !dbg !2924
  %add124 = add nsw i32 256, %shr, !dbg !2924
  %idxprom125 = sext i32 %add124 to i64, !dbg !2924
  %arrayidx126 = getelementptr inbounds [0 x i8], [0 x i8]* @cm_zlib__dist_code, i64 0, i64 %idxprom125, !dbg !2924
  %117 = load i8, i8* %arrayidx126, align 1, !dbg !2924
  %conv127 = zext i8 %117 to i32, !dbg !2924
  br label %cond.end, !dbg !2924

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %conv122, %cond.true ], [ %conv127, %cond.false ], !dbg !2926
  %idxprom128 = sext i32 %cond to i64, !dbg !2926
  %118 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2926
  %dyn_dtree = getelementptr inbounds %struct.internal_state, %struct.internal_state* %118, i32 0, i32 38, !dbg !2926
  %arrayidx129 = getelementptr inbounds [61 x %struct.ct_data_s], [61 x %struct.ct_data_s]* %dyn_dtree, i64 0, i64 %idxprom128, !dbg !2926
  %fc130 = getelementptr inbounds %struct.ct_data_s, %struct.ct_data_s* %arrayidx129, i32 0, i32 0, !dbg !2926
  %freq131 = bitcast %union.anon* %fc130 to i16*, !dbg !2926
  %119 = load i16, i16* %freq131, align 4, !dbg !2926
  %inc132 = add i16 %119, 1, !dbg !2926
  store i16 %inc132, i16* %freq131, align 4, !dbg !2926
  %120 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2926
  %last_lit133 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %120, i32 0, i32 50, !dbg !2926
  %121 = load i32, i32* %last_lit133, align 4, !dbg !2926
  %122 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2926
  %lit_bufsize = getelementptr inbounds %struct.internal_state, %struct.internal_state* %122, i32 0, i32 49, !dbg !2926
  %123 = load i32, i32* %lit_bufsize, align 8, !dbg !2926
  %sub134 = sub i32 %123, 1, !dbg !2926
  %cmp135 = icmp eq i32 %121, %sub134, !dbg !2926
  %conv136 = zext i1 %cmp135 to i32, !dbg !2926
  store i32 %conv136, i32* %bflush, align 4, !dbg !2926
  %124 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2928
  %prev_length137 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %124, i32 0, i32 30, !dbg !2929
  %125 = load i32, i32* %prev_length137, align 8, !dbg !2929
  %sub138 = sub i32 %125, 1, !dbg !2930
  %126 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2931
  %lookahead139 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %126, i32 0, i32 29, !dbg !2932
  %127 = load i32, i32* %lookahead139, align 4, !dbg !2933
  %sub140 = sub i32 %127, %sub138, !dbg !2933
  store i32 %sub140, i32* %lookahead139, align 4, !dbg !2933
  %128 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2934
  %prev_length141 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %128, i32 0, i32 30, !dbg !2935
  %129 = load i32, i32* %prev_length141, align 8, !dbg !2936
  %sub142 = sub i32 %129, 2, !dbg !2936
  store i32 %sub142, i32* %prev_length141, align 8, !dbg !2936
  br label %do.body, !dbg !2937

do.body:                                          ; preds = %do.cond, %cond.end
  %130 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2938
  %strstart143 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %130, i32 0, i32 27, !dbg !2941
  %131 = load i32, i32* %strstart143, align 4, !dbg !2942
  %inc144 = add i32 %131, 1, !dbg !2942
  store i32 %inc144, i32* %strstart143, align 4, !dbg !2942
  %132 = load i32, i32* %max_insert, align 4, !dbg !2943
  %cmp145 = icmp ule i32 %inc144, %132, !dbg !2944
  br i1 %cmp145, label %if.then147, label %if.end178, !dbg !2945

if.then147:                                       ; preds = %do.body
  %133 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2946
  %ins_h148 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %133, i32 0, i32 18, !dbg !2946
  %134 = load i32, i32* %ins_h148, align 8, !dbg !2946
  %135 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2946
  %hash_shift149 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %135, i32 0, i32 22, !dbg !2946
  %136 = load i32, i32* %hash_shift149, align 8, !dbg !2946
  %shl150 = shl i32 %134, %136, !dbg !2946
  %137 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2946
  %strstart151 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %137, i32 0, i32 27, !dbg !2946
  %138 = load i32, i32* %strstart151, align 4, !dbg !2946
  %add152 = add i32 %138, 2, !dbg !2946
  %idxprom153 = zext i32 %add152 to i64, !dbg !2946
  %139 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2946
  %window154 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %139, i32 0, i32 14, !dbg !2946
  %140 = load i8*, i8** %window154, align 8, !dbg !2946
  %arrayidx155 = getelementptr inbounds i8, i8* %140, i64 %idxprom153, !dbg !2946
  %141 = load i8, i8* %arrayidx155, align 1, !dbg !2946
  %conv156 = zext i8 %141 to i32, !dbg !2946
  %xor157 = xor i32 %shl150, %conv156, !dbg !2946
  %142 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2946
  %hash_mask158 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %142, i32 0, i32 21, !dbg !2946
  %143 = load i32, i32* %hash_mask158, align 4, !dbg !2946
  %and159 = and i32 %xor157, %143, !dbg !2946
  %144 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2946
  %ins_h160 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %144, i32 0, i32 18, !dbg !2946
  store i32 %and159, i32* %ins_h160, align 8, !dbg !2946
  %145 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2946
  %ins_h161 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %145, i32 0, i32 18, !dbg !2946
  %146 = load i32, i32* %ins_h161, align 8, !dbg !2946
  %idxprom162 = zext i32 %146 to i64, !dbg !2946
  %147 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2946
  %head163 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %147, i32 0, i32 17, !dbg !2946
  %148 = load i16*, i16** %head163, align 8, !dbg !2946
  %arrayidx164 = getelementptr inbounds i16, i16* %148, i64 %idxprom162, !dbg !2946
  %149 = load i16, i16* %arrayidx164, align 2, !dbg !2946
  %150 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2946
  %strstart165 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %150, i32 0, i32 27, !dbg !2946
  %151 = load i32, i32* %strstart165, align 4, !dbg !2946
  %152 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2946
  %w_mask166 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %152, i32 0, i32 13, !dbg !2946
  %153 = load i32, i32* %w_mask166, align 4, !dbg !2946
  %and167 = and i32 %151, %153, !dbg !2946
  %idxprom168 = zext i32 %and167 to i64, !dbg !2946
  %154 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2946
  %prev169 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %154, i32 0, i32 16, !dbg !2946
  %155 = load i16*, i16** %prev169, align 8, !dbg !2946
  %arrayidx170 = getelementptr inbounds i16, i16* %155, i64 %idxprom168, !dbg !2946
  store i16 %149, i16* %arrayidx170, align 2, !dbg !2946
  %conv171 = zext i16 %149 to i32, !dbg !2946
  store i32 %conv171, i32* %hash_head, align 4, !dbg !2946
  %156 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2946
  %strstart172 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %156, i32 0, i32 27, !dbg !2946
  %157 = load i32, i32* %strstart172, align 4, !dbg !2946
  %conv173 = trunc i32 %157 to i16, !dbg !2946
  %158 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2946
  %ins_h174 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %158, i32 0, i32 18, !dbg !2946
  %159 = load i32, i32* %ins_h174, align 8, !dbg !2946
  %idxprom175 = zext i32 %159 to i64, !dbg !2946
  %160 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2946
  %head176 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %160, i32 0, i32 17, !dbg !2946
  %161 = load i16*, i16** %head176, align 8, !dbg !2946
  %arrayidx177 = getelementptr inbounds i16, i16* %161, i64 %idxprom175, !dbg !2946
  store i16 %conv173, i16* %arrayidx177, align 2, !dbg !2946
  br label %if.end178, !dbg !2948

if.end178:                                        ; preds = %if.then147, %do.body
  br label %do.cond, !dbg !2949

do.cond:                                          ; preds = %if.end178
  %162 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2950
  %prev_length179 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %162, i32 0, i32 30, !dbg !2952
  %163 = load i32, i32* %prev_length179, align 8, !dbg !2953
  %dec180 = add i32 %163, -1, !dbg !2953
  store i32 %dec180, i32* %prev_length179, align 8, !dbg !2953
  %cmp181 = icmp ne i32 %dec180, 0, !dbg !2954
  br i1 %cmp181, label %do.body, label %do.end, !dbg !2955

do.end:                                           ; preds = %do.cond
  %164 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2956
  %match_available = getelementptr inbounds %struct.internal_state, %struct.internal_state* %164, i32 0, i32 26, !dbg !2957
  store i32 0, i32* %match_available, align 8, !dbg !2958
  %165 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2959
  %match_length183 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %165, i32 0, i32 24, !dbg !2960
  store i32 2, i32* %match_length183, align 8, !dbg !2961
  %166 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2962
  %strstart184 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %166, i32 0, i32 27, !dbg !2963
  %167 = load i32, i32* %strstart184, align 4, !dbg !2964
  %inc185 = add i32 %167, 1, !dbg !2964
  store i32 %inc185, i32* %strstart184, align 4, !dbg !2964
  %168 = load i32, i32* %bflush, align 4, !dbg !2965
  %tobool = icmp ne i32 %168, 0, !dbg !2965
  br i1 %tobool, label %if.then186, label %if.end210, !dbg !2967

if.then186:                                       ; preds = %do.end
  %169 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2968
  %170 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2968
  %block_start = getelementptr inbounds %struct.internal_state, %struct.internal_state* %170, i32 0, i32 23, !dbg !2968
  %171 = load i64, i64* %block_start, align 8, !dbg !2968
  %cmp187 = icmp sge i64 %171, 0, !dbg !2968
  br i1 %cmp187, label %cond.true189, label %cond.false195, !dbg !2968

cond.true189:                                     ; preds = %if.then186
  %172 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2972
  %block_start190 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %172, i32 0, i32 23, !dbg !2972
  %173 = load i64, i64* %block_start190, align 8, !dbg !2972
  %conv191 = trunc i64 %173 to i32, !dbg !2972
  %idxprom192 = zext i32 %conv191 to i64, !dbg !2972
  %174 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2972
  %window193 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %174, i32 0, i32 14, !dbg !2972
  %175 = load i8*, i8** %window193, align 8, !dbg !2972
  %arrayidx194 = getelementptr inbounds i8, i8* %175, i64 %idxprom192, !dbg !2972
  br label %cond.end196, !dbg !2972

cond.false195:                                    ; preds = %if.then186
  br label %cond.end196, !dbg !2974

cond.end196:                                      ; preds = %cond.false195, %cond.true189
  %cond197 = phi i8* [ %arrayidx194, %cond.true189 ], [ null, %cond.false195 ], !dbg !2976
  %176 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2976
  %strstart198 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %176, i32 0, i32 27, !dbg !2976
  %177 = load i32, i32* %strstart198, align 4, !dbg !2976
  %conv199 = zext i32 %177 to i64, !dbg !2976
  %178 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2976
  %block_start200 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %178, i32 0, i32 23, !dbg !2976
  %179 = load i64, i64* %block_start200, align 8, !dbg !2976
  %sub201 = sub nsw i64 %conv199, %179, !dbg !2976
  call void @cm_zlib__tr_flush_block(%struct.internal_state* %169, i8* %cond197, i64 %sub201, i32 0), !dbg !2976
  %180 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2976
  %strstart202 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %180, i32 0, i32 27, !dbg !2976
  %181 = load i32, i32* %strstart202, align 4, !dbg !2976
  %conv203 = zext i32 %181 to i64, !dbg !2976
  %182 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2976
  %block_start204 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %182, i32 0, i32 23, !dbg !2976
  store i64 %conv203, i64* %block_start204, align 8, !dbg !2976
  %183 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2976
  %strm = getelementptr inbounds %struct.internal_state, %struct.internal_state* %183, i32 0, i32 0, !dbg !2976
  %184 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2976
  call void @flush_pending(%struct.z_stream_s* %184), !dbg !2978
  %185 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2976
  %strm205 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %185, i32 0, i32 0, !dbg !2976
  %186 = load %struct.z_stream_s*, %struct.z_stream_s** %strm205, align 8, !dbg !2976
  %avail_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %186, i32 0, i32 4, !dbg !2976
  %187 = load i32, i32* %avail_out, align 8, !dbg !2976
  %cmp206 = icmp eq i32 %187, 0, !dbg !2976
  br i1 %cmp206, label %if.then208, label %if.end209, !dbg !2976

if.then208:                                       ; preds = %cond.end196
  store i32 0, i32* %retval, align 4, !dbg !2980
  br label %return, !dbg !2980

if.end209:                                        ; preds = %cond.end196
  br label %if.end210, !dbg !2983

if.end210:                                        ; preds = %if.end209, %do.end
  br label %if.end280, !dbg !2985

if.else211:                                       ; preds = %land.lhs.true86, %if.end82
  %188 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2986
  %match_available212 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %188, i32 0, i32 26, !dbg !2989
  %189 = load i32, i32* %match_available212, align 8, !dbg !2989
  %tobool213 = icmp ne i32 %189, 0, !dbg !2986
  br i1 %tobool213, label %if.then214, label %if.else273, !dbg !2986

if.then214:                                       ; preds = %if.else211
  call void @llvm.dbg.declare(metadata i8* %cc, metadata !2990, metadata !277), !dbg !2993
  %190 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2993
  %strstart215 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %190, i32 0, i32 27, !dbg !2993
  %191 = load i32, i32* %strstart215, align 4, !dbg !2993
  %sub216 = sub i32 %191, 1, !dbg !2993
  %idxprom217 = zext i32 %sub216 to i64, !dbg !2993
  %192 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2993
  %window218 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %192, i32 0, i32 14, !dbg !2993
  %193 = load i8*, i8** %window218, align 8, !dbg !2993
  %arrayidx219 = getelementptr inbounds i8, i8* %193, i64 %idxprom217, !dbg !2993
  %194 = load i8, i8* %arrayidx219, align 1, !dbg !2993
  store i8 %194, i8* %cc, align 1, !dbg !2993
  %195 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2993
  %last_lit220 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %195, i32 0, i32 50, !dbg !2993
  %196 = load i32, i32* %last_lit220, align 4, !dbg !2993
  %idxprom221 = zext i32 %196 to i64, !dbg !2993
  %197 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2993
  %d_buf222 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %197, i32 0, i32 51, !dbg !2993
  %198 = load i16*, i16** %d_buf222, align 8, !dbg !2993
  %arrayidx223 = getelementptr inbounds i16, i16* %198, i64 %idxprom221, !dbg !2993
  store i16 0, i16* %arrayidx223, align 2, !dbg !2993
  %199 = load i8, i8* %cc, align 1, !dbg !2993
  %200 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2993
  %last_lit224 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %200, i32 0, i32 50, !dbg !2993
  %201 = load i32, i32* %last_lit224, align 4, !dbg !2993
  %inc225 = add i32 %201, 1, !dbg !2993
  store i32 %inc225, i32* %last_lit224, align 4, !dbg !2993
  %idxprom226 = zext i32 %201 to i64, !dbg !2993
  %202 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2993
  %l_buf227 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %202, i32 0, i32 48, !dbg !2993
  %203 = load i8*, i8** %l_buf227, align 8, !dbg !2993
  %arrayidx228 = getelementptr inbounds i8, i8* %203, i64 %idxprom226, !dbg !2993
  store i8 %199, i8* %arrayidx228, align 1, !dbg !2993
  %204 = load i8, i8* %cc, align 1, !dbg !2993
  %idxprom229 = zext i8 %204 to i64, !dbg !2993
  %205 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2993
  %dyn_ltree230 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %205, i32 0, i32 37, !dbg !2993
  %arrayidx231 = getelementptr inbounds [573 x %struct.ct_data_s], [573 x %struct.ct_data_s]* %dyn_ltree230, i64 0, i64 %idxprom229, !dbg !2993
  %fc232 = getelementptr inbounds %struct.ct_data_s, %struct.ct_data_s* %arrayidx231, i32 0, i32 0, !dbg !2993
  %freq233 = bitcast %union.anon* %fc232 to i16*, !dbg !2993
  %206 = load i16, i16* %freq233, align 4, !dbg !2993
  %inc234 = add i16 %206, 1, !dbg !2993
  store i16 %inc234, i16* %freq233, align 4, !dbg !2993
  %207 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2993
  %last_lit235 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %207, i32 0, i32 50, !dbg !2993
  %208 = load i32, i32* %last_lit235, align 4, !dbg !2993
  %209 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2993
  %lit_bufsize236 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %209, i32 0, i32 49, !dbg !2993
  %210 = load i32, i32* %lit_bufsize236, align 8, !dbg !2993
  %sub237 = sub i32 %210, 1, !dbg !2993
  %cmp238 = icmp eq i32 %208, %sub237, !dbg !2993
  %conv239 = zext i1 %cmp238 to i32, !dbg !2993
  store i32 %conv239, i32* %bflush, align 4, !dbg !2993
  %211 = load i32, i32* %bflush, align 4, !dbg !2994
  %tobool240 = icmp ne i32 %211, 0, !dbg !2994
  br i1 %tobool240, label %if.then241, label %if.end262, !dbg !2996

if.then241:                                       ; preds = %if.then214
  %212 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2997
  %213 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !2997
  %block_start242 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %213, i32 0, i32 23, !dbg !2997
  %214 = load i64, i64* %block_start242, align 8, !dbg !2997
  %cmp243 = icmp sge i64 %214, 0, !dbg !2997
  br i1 %cmp243, label %cond.true245, label %cond.false251, !dbg !2997

cond.true245:                                     ; preds = %if.then241
  %215 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3000
  %block_start246 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %215, i32 0, i32 23, !dbg !3000
  %216 = load i64, i64* %block_start246, align 8, !dbg !3000
  %conv247 = trunc i64 %216 to i32, !dbg !3000
  %idxprom248 = zext i32 %conv247 to i64, !dbg !3000
  %217 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3000
  %window249 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %217, i32 0, i32 14, !dbg !3000
  %218 = load i8*, i8** %window249, align 8, !dbg !3000
  %arrayidx250 = getelementptr inbounds i8, i8* %218, i64 %idxprom248, !dbg !3000
  br label %cond.end252, !dbg !3000

cond.false251:                                    ; preds = %if.then241
  br label %cond.end252, !dbg !3002

cond.end252:                                      ; preds = %cond.false251, %cond.true245
  %cond253 = phi i8* [ %arrayidx250, %cond.true245 ], [ null, %cond.false251 ], !dbg !3004
  %219 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3004
  %strstart254 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %219, i32 0, i32 27, !dbg !3004
  %220 = load i32, i32* %strstart254, align 4, !dbg !3004
  %conv255 = zext i32 %220 to i64, !dbg !3004
  %221 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3004
  %block_start256 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %221, i32 0, i32 23, !dbg !3004
  %222 = load i64, i64* %block_start256, align 8, !dbg !3004
  %sub257 = sub nsw i64 %conv255, %222, !dbg !3004
  call void @cm_zlib__tr_flush_block(%struct.internal_state* %212, i8* %cond253, i64 %sub257, i32 0), !dbg !3004
  %223 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3004
  %strstart258 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %223, i32 0, i32 27, !dbg !3004
  %224 = load i32, i32* %strstart258, align 4, !dbg !3004
  %conv259 = zext i32 %224 to i64, !dbg !3004
  %225 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3004
  %block_start260 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %225, i32 0, i32 23, !dbg !3004
  store i64 %conv259, i64* %block_start260, align 8, !dbg !3004
  %226 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3004
  %strm261 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %226, i32 0, i32 0, !dbg !3004
  %227 = load %struct.z_stream_s*, %struct.z_stream_s** %strm261, align 8, !dbg !3004
  call void @flush_pending(%struct.z_stream_s* %227), !dbg !3006
  br label %if.end262, !dbg !3008

if.end262:                                        ; preds = %cond.end252, %if.then214
  %228 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3009
  %strstart263 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %228, i32 0, i32 27, !dbg !3010
  %229 = load i32, i32* %strstart263, align 4, !dbg !3011
  %inc264 = add i32 %229, 1, !dbg !3011
  store i32 %inc264, i32* %strstart263, align 4, !dbg !3011
  %230 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3012
  %lookahead265 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %230, i32 0, i32 29, !dbg !3013
  %231 = load i32, i32* %lookahead265, align 4, !dbg !3014
  %dec266 = add i32 %231, -1, !dbg !3014
  store i32 %dec266, i32* %lookahead265, align 4, !dbg !3014
  %232 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3015
  %strm267 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %232, i32 0, i32 0, !dbg !3017
  %233 = load %struct.z_stream_s*, %struct.z_stream_s** %strm267, align 8, !dbg !3017
  %avail_out268 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %233, i32 0, i32 4, !dbg !3018
  %234 = load i32, i32* %avail_out268, align 8, !dbg !3018
  %cmp269 = icmp eq i32 %234, 0, !dbg !3019
  br i1 %cmp269, label %if.then271, label %if.end272, !dbg !3020

if.then271:                                       ; preds = %if.end262
  store i32 0, i32* %retval, align 4, !dbg !3021
  br label %return, !dbg !3021

if.end272:                                        ; preds = %if.end262
  br label %if.end279, !dbg !3023

if.else273:                                       ; preds = %if.else211
  %235 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3024
  %match_available274 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %235, i32 0, i32 26, !dbg !3026
  store i32 1, i32* %match_available274, align 8, !dbg !3027
  %236 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3028
  %strstart275 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %236, i32 0, i32 27, !dbg !3029
  %237 = load i32, i32* %strstart275, align 4, !dbg !3030
  %inc276 = add i32 %237, 1, !dbg !3030
  store i32 %inc276, i32* %strstart275, align 4, !dbg !3030
  %238 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3031
  %lookahead277 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %238, i32 0, i32 29, !dbg !3032
  %239 = load i32, i32* %lookahead277, align 4, !dbg !3033
  %dec278 = add i32 %239, -1, !dbg !3033
  store i32 %dec278, i32* %lookahead277, align 4, !dbg !3033
  br label %if.end279

if.end279:                                        ; preds = %if.else273, %if.end272
  br label %if.end280

if.end280:                                        ; preds = %if.end279, %if.end210
  br label %for.cond, !dbg !3034

for.end:                                          ; preds = %if.then7
  %240 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3036
  %match_available281 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %240, i32 0, i32 26, !dbg !3038
  %241 = load i32, i32* %match_available281, align 8, !dbg !3038
  %tobool282 = icmp ne i32 %241, 0, !dbg !3036
  br i1 %tobool282, label %if.then283, label %if.end311, !dbg !3039

if.then283:                                       ; preds = %for.end
  call void @llvm.dbg.declare(metadata i8* %cc284, metadata !3040, metadata !277), !dbg !3043
  %242 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3043
  %strstart285 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %242, i32 0, i32 27, !dbg !3043
  %243 = load i32, i32* %strstart285, align 4, !dbg !3043
  %sub286 = sub i32 %243, 1, !dbg !3043
  %idxprom287 = zext i32 %sub286 to i64, !dbg !3043
  %244 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3043
  %window288 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %244, i32 0, i32 14, !dbg !3043
  %245 = load i8*, i8** %window288, align 8, !dbg !3043
  %arrayidx289 = getelementptr inbounds i8, i8* %245, i64 %idxprom287, !dbg !3043
  %246 = load i8, i8* %arrayidx289, align 1, !dbg !3043
  store i8 %246, i8* %cc284, align 1, !dbg !3043
  %247 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3043
  %last_lit290 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %247, i32 0, i32 50, !dbg !3043
  %248 = load i32, i32* %last_lit290, align 4, !dbg !3043
  %idxprom291 = zext i32 %248 to i64, !dbg !3043
  %249 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3043
  %d_buf292 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %249, i32 0, i32 51, !dbg !3043
  %250 = load i16*, i16** %d_buf292, align 8, !dbg !3043
  %arrayidx293 = getelementptr inbounds i16, i16* %250, i64 %idxprom291, !dbg !3043
  store i16 0, i16* %arrayidx293, align 2, !dbg !3043
  %251 = load i8, i8* %cc284, align 1, !dbg !3043
  %252 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3043
  %last_lit294 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %252, i32 0, i32 50, !dbg !3043
  %253 = load i32, i32* %last_lit294, align 4, !dbg !3043
  %inc295 = add i32 %253, 1, !dbg !3043
  store i32 %inc295, i32* %last_lit294, align 4, !dbg !3043
  %idxprom296 = zext i32 %253 to i64, !dbg !3043
  %254 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3043
  %l_buf297 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %254, i32 0, i32 48, !dbg !3043
  %255 = load i8*, i8** %l_buf297, align 8, !dbg !3043
  %arrayidx298 = getelementptr inbounds i8, i8* %255, i64 %idxprom296, !dbg !3043
  store i8 %251, i8* %arrayidx298, align 1, !dbg !3043
  %256 = load i8, i8* %cc284, align 1, !dbg !3043
  %idxprom299 = zext i8 %256 to i64, !dbg !3043
  %257 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3043
  %dyn_ltree300 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %257, i32 0, i32 37, !dbg !3043
  %arrayidx301 = getelementptr inbounds [573 x %struct.ct_data_s], [573 x %struct.ct_data_s]* %dyn_ltree300, i64 0, i64 %idxprom299, !dbg !3043
  %fc302 = getelementptr inbounds %struct.ct_data_s, %struct.ct_data_s* %arrayidx301, i32 0, i32 0, !dbg !3043
  %freq303 = bitcast %union.anon* %fc302 to i16*, !dbg !3043
  %258 = load i16, i16* %freq303, align 4, !dbg !3043
  %inc304 = add i16 %258, 1, !dbg !3043
  store i16 %inc304, i16* %freq303, align 4, !dbg !3043
  %259 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3043
  %last_lit305 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %259, i32 0, i32 50, !dbg !3043
  %260 = load i32, i32* %last_lit305, align 4, !dbg !3043
  %261 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3043
  %lit_bufsize306 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %261, i32 0, i32 49, !dbg !3043
  %262 = load i32, i32* %lit_bufsize306, align 8, !dbg !3043
  %sub307 = sub i32 %262, 1, !dbg !3043
  %cmp308 = icmp eq i32 %260, %sub307, !dbg !3043
  %conv309 = zext i1 %cmp308 to i32, !dbg !3043
  store i32 %conv309, i32* %bflush, align 4, !dbg !3043
  %263 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3044
  %match_available310 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %263, i32 0, i32 26, !dbg !3045
  store i32 0, i32* %match_available310, align 8, !dbg !3046
  br label %if.end311, !dbg !3047

if.end311:                                        ; preds = %if.then283, %for.end
  %264 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3048
  %265 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3048
  %block_start312 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %265, i32 0, i32 23, !dbg !3048
  %266 = load i64, i64* %block_start312, align 8, !dbg !3048
  %cmp313 = icmp sge i64 %266, 0, !dbg !3048
  br i1 %cmp313, label %cond.true315, label %cond.false321, !dbg !3048

cond.true315:                                     ; preds = %if.end311
  %267 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3051
  %block_start316 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %267, i32 0, i32 23, !dbg !3051
  %268 = load i64, i64* %block_start316, align 8, !dbg !3051
  %conv317 = trunc i64 %268 to i32, !dbg !3051
  %idxprom318 = zext i32 %conv317 to i64, !dbg !3051
  %269 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3051
  %window319 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %269, i32 0, i32 14, !dbg !3051
  %270 = load i8*, i8** %window319, align 8, !dbg !3051
  %arrayidx320 = getelementptr inbounds i8, i8* %270, i64 %idxprom318, !dbg !3051
  br label %cond.end322, !dbg !3051

cond.false321:                                    ; preds = %if.end311
  br label %cond.end322, !dbg !3053

cond.end322:                                      ; preds = %cond.false321, %cond.true315
  %cond323 = phi i8* [ %arrayidx320, %cond.true315 ], [ null, %cond.false321 ], !dbg !3055
  %271 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3055
  %strstart324 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %271, i32 0, i32 27, !dbg !3055
  %272 = load i32, i32* %strstart324, align 4, !dbg !3055
  %conv325 = zext i32 %272 to i64, !dbg !3055
  %273 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3055
  %block_start326 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %273, i32 0, i32 23, !dbg !3055
  %274 = load i64, i64* %block_start326, align 8, !dbg !3055
  %sub327 = sub nsw i64 %conv325, %274, !dbg !3055
  %275 = load i32, i32* %flush.addr, align 4, !dbg !3055
  %cmp328 = icmp eq i32 %275, 4, !dbg !3055
  %conv329 = zext i1 %cmp328 to i32, !dbg !3055
  call void @cm_zlib__tr_flush_block(%struct.internal_state* %264, i8* %cond323, i64 %sub327, i32 %conv329), !dbg !3055
  %276 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3055
  %strstart330 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %276, i32 0, i32 27, !dbg !3055
  %277 = load i32, i32* %strstart330, align 4, !dbg !3055
  %conv331 = zext i32 %277 to i64, !dbg !3055
  %278 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3055
  %block_start332 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %278, i32 0, i32 23, !dbg !3055
  store i64 %conv331, i64* %block_start332, align 8, !dbg !3055
  %279 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3055
  %strm333 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %279, i32 0, i32 0, !dbg !3055
  %280 = load %struct.z_stream_s*, %struct.z_stream_s** %strm333, align 8, !dbg !3055
  call void @flush_pending(%struct.z_stream_s* %280), !dbg !3057
  %281 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3055
  %strm334 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %281, i32 0, i32 0, !dbg !3055
  %282 = load %struct.z_stream_s*, %struct.z_stream_s** %strm334, align 8, !dbg !3055
  %avail_out335 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %282, i32 0, i32 4, !dbg !3055
  %283 = load i32, i32* %avail_out335, align 8, !dbg !3055
  %cmp336 = icmp eq i32 %283, 0, !dbg !3055
  br i1 %cmp336, label %if.then338, label %if.end342, !dbg !3055

if.then338:                                       ; preds = %cond.end322
  %284 = load i32, i32* %flush.addr, align 4, !dbg !3059
  %cmp339 = icmp eq i32 %284, 4, !dbg !3059
  %cond341 = select i1 %cmp339, i32 2, i32 0, !dbg !3059
  store i32 %cond341, i32* %retval, align 4, !dbg !3059
  br label %return, !dbg !3059

if.end342:                                        ; preds = %cond.end322
  %285 = load i32, i32* %flush.addr, align 4, !dbg !3062
  %cmp343 = icmp eq i32 %285, 4, !dbg !3063
  %cond345 = select i1 %cmp343, i32 3, i32 1, !dbg !3062
  store i32 %cond345, i32* %retval, align 4, !dbg !3064
  br label %return, !dbg !3064

return:                                           ; preds = %if.end342, %if.then338, %if.then271, %if.then208, %if.then4
  %286 = load i32, i32* %retval, align 4, !dbg !3065
  ret i32 %286, !dbg !3065
}

; Function Attrs: nounwind uwtable
define internal void @fill_window(%struct.internal_state* %s) #0 !dbg !230 {
entry:
  %s.addr = alloca %struct.internal_state*, align 8
  %n = alloca i32, align 4
  %m = alloca i32, align 4
  %p = alloca i16*, align 8
  %more = alloca i32, align 4
  %wsize = alloca i32, align 4
  store %struct.internal_state* %s, %struct.internal_state** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.internal_state** %s.addr, metadata !3066, metadata !277), !dbg !3067
  call void @llvm.dbg.declare(metadata i32* %n, metadata !3068, metadata !277), !dbg !3069
  call void @llvm.dbg.declare(metadata i32* %m, metadata !3070, metadata !277), !dbg !3071
  call void @llvm.dbg.declare(metadata i16** %p, metadata !3072, metadata !277), !dbg !3073
  call void @llvm.dbg.declare(metadata i32* %more, metadata !3074, metadata !277), !dbg !3075
  call void @llvm.dbg.declare(metadata i32* %wsize, metadata !3076, metadata !277), !dbg !3077
  %0 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3078
  %w_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %0, i32 0, i32 11, !dbg !3079
  %1 = load i32, i32* %w_size, align 4, !dbg !3079
  store i32 %1, i32* %wsize, align 4, !dbg !3077
  br label %do.body, !dbg !3080

do.body:                                          ; preds = %land.end, %entry
  %2 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3081
  %window_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %2, i32 0, i32 15, !dbg !3083
  %3 = load i64, i64* %window_size, align 8, !dbg !3083
  %4 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3084
  %lookahead = getelementptr inbounds %struct.internal_state, %struct.internal_state* %4, i32 0, i32 29, !dbg !3085
  %5 = load i32, i32* %lookahead, align 4, !dbg !3085
  %conv = zext i32 %5 to i64, !dbg !3086
  %sub = sub i64 %3, %conv, !dbg !3087
  %6 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3088
  %strstart = getelementptr inbounds %struct.internal_state, %struct.internal_state* %6, i32 0, i32 27, !dbg !3089
  %7 = load i32, i32* %strstart, align 4, !dbg !3089
  %conv1 = zext i32 %7 to i64, !dbg !3090
  %sub2 = sub i64 %sub, %conv1, !dbg !3091
  %conv3 = trunc i64 %sub2 to i32, !dbg !3092
  store i32 %conv3, i32* %more, align 4, !dbg !3093
  %8 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3094
  %strstart4 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %8, i32 0, i32 27, !dbg !3096
  %9 = load i32, i32* %strstart4, align 4, !dbg !3096
  %10 = load i32, i32* %wsize, align 4, !dbg !3097
  %11 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3098
  %w_size5 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %11, i32 0, i32 11, !dbg !3098
  %12 = load i32, i32* %w_size5, align 4, !dbg !3098
  %sub6 = sub i32 %12, 262, !dbg !3098
  %add = add i32 %10, %sub6, !dbg !3099
  %cmp = icmp uge i32 %9, %add, !dbg !3100
  br i1 %cmp, label %if.then, label %if.end, !dbg !3101

if.then:                                          ; preds = %do.body
  %13 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3102
  %window = getelementptr inbounds %struct.internal_state, %struct.internal_state* %13, i32 0, i32 14, !dbg !3104
  %14 = load i8*, i8** %window, align 8, !dbg !3104
  %15 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3105
  %window8 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %15, i32 0, i32 14, !dbg !3106
  %16 = load i8*, i8** %window8, align 8, !dbg !3106
  %17 = load i32, i32* %wsize, align 4, !dbg !3107
  %idx.ext = zext i32 %17 to i64, !dbg !3108
  %add.ptr = getelementptr inbounds i8, i8* %16, i64 %idx.ext, !dbg !3108
  %18 = load i32, i32* %wsize, align 4, !dbg !3109
  %conv9 = zext i32 %18 to i64, !dbg !3110
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %14, i8* %add.ptr, i64 %conv9, i32 1, i1 false), !dbg !3111
  %19 = load i32, i32* %wsize, align 4, !dbg !3112
  %20 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3113
  %match_start = getelementptr inbounds %struct.internal_state, %struct.internal_state* %20, i32 0, i32 28, !dbg !3114
  %21 = load i32, i32* %match_start, align 8, !dbg !3115
  %sub10 = sub i32 %21, %19, !dbg !3115
  store i32 %sub10, i32* %match_start, align 8, !dbg !3115
  %22 = load i32, i32* %wsize, align 4, !dbg !3116
  %23 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3117
  %strstart11 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %23, i32 0, i32 27, !dbg !3118
  %24 = load i32, i32* %strstart11, align 4, !dbg !3119
  %sub12 = sub i32 %24, %22, !dbg !3119
  store i32 %sub12, i32* %strstart11, align 4, !dbg !3119
  %25 = load i32, i32* %wsize, align 4, !dbg !3120
  %conv13 = zext i32 %25 to i64, !dbg !3121
  %26 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3122
  %block_start = getelementptr inbounds %struct.internal_state, %struct.internal_state* %26, i32 0, i32 23, !dbg !3123
  %27 = load i64, i64* %block_start, align 8, !dbg !3124
  %sub14 = sub nsw i64 %27, %conv13, !dbg !3124
  store i64 %sub14, i64* %block_start, align 8, !dbg !3124
  %28 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3125
  %hash_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %28, i32 0, i32 19, !dbg !3126
  %29 = load i32, i32* %hash_size, align 4, !dbg !3126
  store i32 %29, i32* %n, align 4, !dbg !3127
  %30 = load i32, i32* %n, align 4, !dbg !3128
  %idxprom = zext i32 %30 to i64, !dbg !3129
  %31 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3129
  %head = getelementptr inbounds %struct.internal_state, %struct.internal_state* %31, i32 0, i32 17, !dbg !3130
  %32 = load i16*, i16** %head, align 8, !dbg !3130
  %arrayidx = getelementptr inbounds i16, i16* %32, i64 %idxprom, !dbg !3129
  store i16* %arrayidx, i16** %p, align 8, !dbg !3131
  br label %do.body15, !dbg !3132

do.body15:                                        ; preds = %do.cond, %if.then
  %33 = load i16*, i16** %p, align 8, !dbg !3133
  %incdec.ptr = getelementptr inbounds i16, i16* %33, i32 -1, !dbg !3133
  store i16* %incdec.ptr, i16** %p, align 8, !dbg !3133
  %34 = load i16, i16* %incdec.ptr, align 2, !dbg !3135
  %conv16 = zext i16 %34 to i32, !dbg !3135
  store i32 %conv16, i32* %m, align 4, !dbg !3136
  %35 = load i32, i32* %m, align 4, !dbg !3137
  %36 = load i32, i32* %wsize, align 4, !dbg !3138
  %cmp17 = icmp uge i32 %35, %36, !dbg !3139
  br i1 %cmp17, label %cond.true, label %cond.false, !dbg !3137

cond.true:                                        ; preds = %do.body15
  %37 = load i32, i32* %m, align 4, !dbg !3140
  %38 = load i32, i32* %wsize, align 4, !dbg !3142
  %sub19 = sub i32 %37, %38, !dbg !3143
  br label %cond.end, !dbg !3144

cond.false:                                       ; preds = %do.body15
  br label %cond.end, !dbg !3145

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %sub19, %cond.true ], [ 0, %cond.false ], !dbg !3147
  %conv20 = trunc i32 %cond to i16, !dbg !3149
  %39 = load i16*, i16** %p, align 8, !dbg !3150
  store i16 %conv20, i16* %39, align 2, !dbg !3151
  br label %do.cond, !dbg !3152

do.cond:                                          ; preds = %cond.end
  %40 = load i32, i32* %n, align 4, !dbg !3153
  %dec = add i32 %40, -1, !dbg !3153
  store i32 %dec, i32* %n, align 4, !dbg !3153
  %tobool = icmp ne i32 %dec, 0, !dbg !3155
  br i1 %tobool, label %do.body15, label %do.end, !dbg !3155

do.end:                                           ; preds = %do.cond
  %41 = load i32, i32* %wsize, align 4, !dbg !3156
  store i32 %41, i32* %n, align 4, !dbg !3157
  %42 = load i32, i32* %n, align 4, !dbg !3158
  %idxprom21 = zext i32 %42 to i64, !dbg !3159
  %43 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3159
  %prev = getelementptr inbounds %struct.internal_state, %struct.internal_state* %43, i32 0, i32 16, !dbg !3160
  %44 = load i16*, i16** %prev, align 8, !dbg !3160
  %arrayidx22 = getelementptr inbounds i16, i16* %44, i64 %idxprom21, !dbg !3159
  store i16* %arrayidx22, i16** %p, align 8, !dbg !3161
  br label %do.body23, !dbg !3162

do.body23:                                        ; preds = %do.cond34, %do.end
  %45 = load i16*, i16** %p, align 8, !dbg !3163
  %incdec.ptr24 = getelementptr inbounds i16, i16* %45, i32 -1, !dbg !3163
  store i16* %incdec.ptr24, i16** %p, align 8, !dbg !3163
  %46 = load i16, i16* %incdec.ptr24, align 2, !dbg !3165
  %conv25 = zext i16 %46 to i32, !dbg !3165
  store i32 %conv25, i32* %m, align 4, !dbg !3166
  %47 = load i32, i32* %m, align 4, !dbg !3167
  %48 = load i32, i32* %wsize, align 4, !dbg !3168
  %cmp26 = icmp uge i32 %47, %48, !dbg !3169
  br i1 %cmp26, label %cond.true28, label %cond.false30, !dbg !3167

cond.true28:                                      ; preds = %do.body23
  %49 = load i32, i32* %m, align 4, !dbg !3170
  %50 = load i32, i32* %wsize, align 4, !dbg !3172
  %sub29 = sub i32 %49, %50, !dbg !3173
  br label %cond.end31, !dbg !3174

cond.false30:                                     ; preds = %do.body23
  br label %cond.end31, !dbg !3175

cond.end31:                                       ; preds = %cond.false30, %cond.true28
  %cond32 = phi i32 [ %sub29, %cond.true28 ], [ 0, %cond.false30 ], !dbg !3177
  %conv33 = trunc i32 %cond32 to i16, !dbg !3179
  %51 = load i16*, i16** %p, align 8, !dbg !3180
  store i16 %conv33, i16* %51, align 2, !dbg !3181
  br label %do.cond34, !dbg !3182

do.cond34:                                        ; preds = %cond.end31
  %52 = load i32, i32* %n, align 4, !dbg !3183
  %dec35 = add i32 %52, -1, !dbg !3183
  store i32 %dec35, i32* %n, align 4, !dbg !3183
  %tobool36 = icmp ne i32 %dec35, 0, !dbg !3184
  br i1 %tobool36, label %do.body23, label %do.end37, !dbg !3184

do.end37:                                         ; preds = %do.cond34
  %53 = load i32, i32* %wsize, align 4, !dbg !3185
  %54 = load i32, i32* %more, align 4, !dbg !3186
  %add38 = add i32 %54, %53, !dbg !3186
  store i32 %add38, i32* %more, align 4, !dbg !3186
  br label %if.end, !dbg !3187

if.end:                                           ; preds = %do.end37, %do.body
  %55 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3188
  %strm = getelementptr inbounds %struct.internal_state, %struct.internal_state* %55, i32 0, i32 0, !dbg !3190
  %56 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !3190
  %avail_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %56, i32 0, i32 1, !dbg !3191
  %57 = load i32, i32* %avail_in, align 8, !dbg !3191
  %cmp39 = icmp eq i32 %57, 0, !dbg !3192
  br i1 %cmp39, label %if.then41, label %if.end42, !dbg !3193

if.then41:                                        ; preds = %if.end
  br label %do.end79, !dbg !3194

if.end42:                                         ; preds = %if.end
  %58 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3196
  %strm43 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %58, i32 0, i32 0, !dbg !3197
  %59 = load %struct.z_stream_s*, %struct.z_stream_s** %strm43, align 8, !dbg !3197
  %60 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3198
  %window44 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %60, i32 0, i32 14, !dbg !3199
  %61 = load i8*, i8** %window44, align 8, !dbg !3199
  %62 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3200
  %strstart45 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %62, i32 0, i32 27, !dbg !3201
  %63 = load i32, i32* %strstart45, align 4, !dbg !3201
  %idx.ext46 = zext i32 %63 to i64, !dbg !3202
  %add.ptr47 = getelementptr inbounds i8, i8* %61, i64 %idx.ext46, !dbg !3202
  %64 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3203
  %lookahead48 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %64, i32 0, i32 29, !dbg !3204
  %65 = load i32, i32* %lookahead48, align 4, !dbg !3204
  %idx.ext49 = zext i32 %65 to i64, !dbg !3205
  %add.ptr50 = getelementptr inbounds i8, i8* %add.ptr47, i64 %idx.ext49, !dbg !3205
  %66 = load i32, i32* %more, align 4, !dbg !3206
  %call = call i32 @read_buf(%struct.z_stream_s* %59, i8* %add.ptr50, i32 %66), !dbg !3207
  store i32 %call, i32* %n, align 4, !dbg !3208
  %67 = load i32, i32* %n, align 4, !dbg !3209
  %68 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3210
  %lookahead51 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %68, i32 0, i32 29, !dbg !3211
  %69 = load i32, i32* %lookahead51, align 4, !dbg !3212
  %add52 = add i32 %69, %67, !dbg !3212
  store i32 %add52, i32* %lookahead51, align 4, !dbg !3212
  %70 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3213
  %lookahead53 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %70, i32 0, i32 29, !dbg !3215
  %71 = load i32, i32* %lookahead53, align 4, !dbg !3215
  %cmp54 = icmp uge i32 %71, 3, !dbg !3216
  br i1 %cmp54, label %if.then56, label %if.end70, !dbg !3217

if.then56:                                        ; preds = %if.end42
  %72 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3218
  %strstart57 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %72, i32 0, i32 27, !dbg !3220
  %73 = load i32, i32* %strstart57, align 4, !dbg !3220
  %idxprom58 = zext i32 %73 to i64, !dbg !3221
  %74 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3221
  %window59 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %74, i32 0, i32 14, !dbg !3222
  %75 = load i8*, i8** %window59, align 8, !dbg !3222
  %arrayidx60 = getelementptr inbounds i8, i8* %75, i64 %idxprom58, !dbg !3221
  %76 = load i8, i8* %arrayidx60, align 1, !dbg !3221
  %conv61 = zext i8 %76 to i32, !dbg !3221
  %77 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3223
  %ins_h = getelementptr inbounds %struct.internal_state, %struct.internal_state* %77, i32 0, i32 18, !dbg !3224
  store i32 %conv61, i32* %ins_h, align 8, !dbg !3225
  %78 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3226
  %ins_h62 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %78, i32 0, i32 18, !dbg !3226
  %79 = load i32, i32* %ins_h62, align 8, !dbg !3226
  %80 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3226
  %hash_shift = getelementptr inbounds %struct.internal_state, %struct.internal_state* %80, i32 0, i32 22, !dbg !3226
  %81 = load i32, i32* %hash_shift, align 8, !dbg !3226
  %shl = shl i32 %79, %81, !dbg !3226
  %82 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3226
  %strstart63 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %82, i32 0, i32 27, !dbg !3226
  %83 = load i32, i32* %strstart63, align 4, !dbg !3226
  %add64 = add i32 %83, 1, !dbg !3226
  %idxprom65 = zext i32 %add64 to i64, !dbg !3226
  %84 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3226
  %window66 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %84, i32 0, i32 14, !dbg !3226
  %85 = load i8*, i8** %window66, align 8, !dbg !3226
  %arrayidx67 = getelementptr inbounds i8, i8* %85, i64 %idxprom65, !dbg !3226
  %86 = load i8, i8* %arrayidx67, align 1, !dbg !3226
  %conv68 = zext i8 %86 to i32, !dbg !3226
  %xor = xor i32 %shl, %conv68, !dbg !3226
  %87 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3226
  %hash_mask = getelementptr inbounds %struct.internal_state, %struct.internal_state* %87, i32 0, i32 21, !dbg !3226
  %88 = load i32, i32* %hash_mask, align 4, !dbg !3226
  %and = and i32 %xor, %88, !dbg !3226
  %89 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3226
  %ins_h69 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %89, i32 0, i32 18, !dbg !3226
  store i32 %and, i32* %ins_h69, align 8, !dbg !3226
  br label %if.end70, !dbg !3227

if.end70:                                         ; preds = %if.then56, %if.end42
  br label %do.cond71, !dbg !3228

do.cond71:                                        ; preds = %if.end70
  %90 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3229
  %lookahead72 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %90, i32 0, i32 29, !dbg !3231
  %91 = load i32, i32* %lookahead72, align 4, !dbg !3231
  %cmp73 = icmp ult i32 %91, 262, !dbg !3232
  br i1 %cmp73, label %land.rhs, label %land.end, !dbg !3233

land.rhs:                                         ; preds = %do.cond71
  %92 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3234
  %strm75 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %92, i32 0, i32 0, !dbg !3236
  %93 = load %struct.z_stream_s*, %struct.z_stream_s** %strm75, align 8, !dbg !3236
  %avail_in76 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %93, i32 0, i32 1, !dbg !3237
  %94 = load i32, i32* %avail_in76, align 8, !dbg !3237
  %cmp77 = icmp ne i32 %94, 0, !dbg !3238
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond71
  %95 = phi i1 [ false, %do.cond71 ], [ %cmp77, %land.rhs ]
  br i1 %95, label %do.body, label %do.end79, !dbg !3239

do.end79:                                         ; preds = %if.then41, %land.end
  ret void, !dbg !3241
}

declare void @cm_zlib__tr_flush_block(%struct.internal_state*, i8*, i64, i32) #2

; Function Attrs: nounwind uwtable
define internal i32 @read_buf(%struct.z_stream_s* %strm, i8* %buf, i32 %size) #0 !dbg !233 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.z_stream_s*, align 8
  %buf.addr = alloca i8*, align 8
  %size.addr = alloca i32, align 4
  %len = alloca i32, align 4
  store %struct.z_stream_s* %strm, %struct.z_stream_s** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.z_stream_s** %strm.addr, metadata !3242, metadata !277), !dbg !3243
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !3244, metadata !277), !dbg !3245
  store i32 %size, i32* %size.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %size.addr, metadata !3246, metadata !277), !dbg !3247
  call void @llvm.dbg.declare(metadata i32* %len, metadata !3248, metadata !277), !dbg !3249
  %0 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !3250
  %avail_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %0, i32 0, i32 1, !dbg !3251
  %1 = load i32, i32* %avail_in, align 8, !dbg !3251
  store i32 %1, i32* %len, align 4, !dbg !3249
  %2 = load i32, i32* %len, align 4, !dbg !3252
  %3 = load i32, i32* %size.addr, align 4, !dbg !3254
  %cmp = icmp ugt i32 %2, %3, !dbg !3255
  br i1 %cmp, label %if.then, label %if.end, !dbg !3256

if.then:                                          ; preds = %entry
  %4 = load i32, i32* %size.addr, align 4, !dbg !3257
  store i32 %4, i32* %len, align 4, !dbg !3259
  br label %if.end, !dbg !3260

if.end:                                           ; preds = %if.then, %entry
  %5 = load i32, i32* %len, align 4, !dbg !3261
  %cmp1 = icmp eq i32 %5, 0, !dbg !3263
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !3264

if.then2:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !3265
  br label %return, !dbg !3265

if.end3:                                          ; preds = %if.end
  %6 = load i32, i32* %len, align 4, !dbg !3267
  %7 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !3268
  %avail_in4 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %7, i32 0, i32 1, !dbg !3269
  %8 = load i32, i32* %avail_in4, align 8, !dbg !3270
  %sub = sub i32 %8, %6, !dbg !3270
  store i32 %sub, i32* %avail_in4, align 8, !dbg !3270
  %9 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !3271
  %state = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %9, i32 0, i32 7, !dbg !3273
  %10 = load %struct.internal_state*, %struct.internal_state** %state, align 8, !dbg !3273
  %wrap = getelementptr inbounds %struct.internal_state, %struct.internal_state* %10, i32 0, i32 6, !dbg !3274
  %11 = load i32, i32* %wrap, align 4, !dbg !3274
  %cmp5 = icmp eq i32 %11, 1, !dbg !3275
  br i1 %cmp5, label %if.then6, label %if.else, !dbg !3276

if.then6:                                         ; preds = %if.end3
  %12 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !3277
  %adler = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %12, i32 0, i32 12, !dbg !3279
  %13 = load i64, i64* %adler, align 8, !dbg !3279
  %14 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !3280
  %next_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %14, i32 0, i32 0, !dbg !3281
  %15 = load i8*, i8** %next_in, align 8, !dbg !3281
  %16 = load i32, i32* %len, align 4, !dbg !3282
  %call = call i64 @cm_zlib_adler32(i64 %13, i8* %15, i32 %16), !dbg !3283
  %17 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !3284
  %adler7 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %17, i32 0, i32 12, !dbg !3285
  store i64 %call, i64* %adler7, align 8, !dbg !3286
  br label %if.end17, !dbg !3287

if.else:                                          ; preds = %if.end3
  %18 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !3288
  %state8 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %18, i32 0, i32 7, !dbg !3290
  %19 = load %struct.internal_state*, %struct.internal_state** %state8, align 8, !dbg !3290
  %wrap9 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %19, i32 0, i32 6, !dbg !3291
  %20 = load i32, i32* %wrap9, align 4, !dbg !3291
  %cmp10 = icmp eq i32 %20, 2, !dbg !3292
  br i1 %cmp10, label %if.then11, label %if.end16, !dbg !3293

if.then11:                                        ; preds = %if.else
  %21 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !3294
  %adler12 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %21, i32 0, i32 12, !dbg !3296
  %22 = load i64, i64* %adler12, align 8, !dbg !3296
  %23 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !3297
  %next_in13 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %23, i32 0, i32 0, !dbg !3298
  %24 = load i8*, i8** %next_in13, align 8, !dbg !3298
  %25 = load i32, i32* %len, align 4, !dbg !3299
  %call14 = call i64 @cm_zlib_crc32(i64 %22, i8* %24, i32 %25), !dbg !3300
  %26 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !3301
  %adler15 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %26, i32 0, i32 12, !dbg !3302
  store i64 %call14, i64* %adler15, align 8, !dbg !3303
  br label %if.end16, !dbg !3304

if.end16:                                         ; preds = %if.then11, %if.else
  br label %if.end17

if.end17:                                         ; preds = %if.end16, %if.then6
  %27 = load i8*, i8** %buf.addr, align 8, !dbg !3305
  %28 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !3306
  %next_in18 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %28, i32 0, i32 0, !dbg !3307
  %29 = load i8*, i8** %next_in18, align 8, !dbg !3307
  %30 = load i32, i32* %len, align 4, !dbg !3308
  %conv = zext i32 %30 to i64, !dbg !3308
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %27, i8* %29, i64 %conv, i32 1, i1 false), !dbg !3309
  %31 = load i32, i32* %len, align 4, !dbg !3310
  %32 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !3311
  %next_in19 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %32, i32 0, i32 0, !dbg !3312
  %33 = load i8*, i8** %next_in19, align 8, !dbg !3313
  %idx.ext = zext i32 %31 to i64, !dbg !3313
  %add.ptr = getelementptr inbounds i8, i8* %33, i64 %idx.ext, !dbg !3313
  store i8* %add.ptr, i8** %next_in19, align 8, !dbg !3313
  %34 = load i32, i32* %len, align 4, !dbg !3314
  %conv20 = zext i32 %34 to i64, !dbg !3314
  %35 = load %struct.z_stream_s*, %struct.z_stream_s** %strm.addr, align 8, !dbg !3315
  %total_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %35, i32 0, i32 2, !dbg !3316
  %36 = load i64, i64* %total_in, align 8, !dbg !3317
  %add = add i64 %36, %conv20, !dbg !3317
  store i64 %add, i64* %total_in, align 8, !dbg !3317
  %37 = load i32, i32* %len, align 4, !dbg !3318
  store i32 %37, i32* %retval, align 4, !dbg !3319
  br label %return, !dbg !3319

return:                                           ; preds = %if.end17, %if.then2
  %38 = load i32, i32* %retval, align 4, !dbg !3320
  ret i32 %38, !dbg !3320
}

; Function Attrs: nounwind uwtable
define internal i32 @longest_match(%struct.internal_state* %s, i32 %cur_match) #0 !dbg !237 {
entry:
  %retval = alloca i32, align 4
  %s.addr = alloca %struct.internal_state*, align 8
  %cur_match.addr = alloca i32, align 4
  %chain_length = alloca i32, align 4
  %scan = alloca i8*, align 8
  %match = alloca i8*, align 8
  %len = alloca i32, align 4
  %best_len = alloca i32, align 4
  %nice_match = alloca i32, align 4
  %limit = alloca i32, align 4
  %prev = alloca i16*, align 8
  %wmask = alloca i32, align 4
  %strend = alloca i8*, align 8
  %scan_end1 = alloca i8, align 1
  %scan_end = alloca i8, align 1
  store %struct.internal_state* %s, %struct.internal_state** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.internal_state** %s.addr, metadata !3321, metadata !277), !dbg !3322
  store i32 %cur_match, i32* %cur_match.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %cur_match.addr, metadata !3323, metadata !277), !dbg !3324
  call void @llvm.dbg.declare(metadata i32* %chain_length, metadata !3325, metadata !277), !dbg !3326
  %0 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3327
  %max_chain_length = getelementptr inbounds %struct.internal_state, %struct.internal_state* %0, i32 0, i32 31, !dbg !3328
  %1 = load i32, i32* %max_chain_length, align 4, !dbg !3328
  store i32 %1, i32* %chain_length, align 4, !dbg !3326
  call void @llvm.dbg.declare(metadata i8** %scan, metadata !3329, metadata !277), !dbg !3330
  %2 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3331
  %window = getelementptr inbounds %struct.internal_state, %struct.internal_state* %2, i32 0, i32 14, !dbg !3332
  %3 = load i8*, i8** %window, align 8, !dbg !3332
  %4 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3333
  %strstart = getelementptr inbounds %struct.internal_state, %struct.internal_state* %4, i32 0, i32 27, !dbg !3334
  %5 = load i32, i32* %strstart, align 4, !dbg !3334
  %idx.ext = zext i32 %5 to i64, !dbg !3335
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 %idx.ext, !dbg !3335
  store i8* %add.ptr, i8** %scan, align 8, !dbg !3330
  call void @llvm.dbg.declare(metadata i8** %match, metadata !3336, metadata !277), !dbg !3337
  call void @llvm.dbg.declare(metadata i32* %len, metadata !3338, metadata !277), !dbg !3339
  call void @llvm.dbg.declare(metadata i32* %best_len, metadata !3340, metadata !277), !dbg !3341
  %6 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3342
  %prev_length = getelementptr inbounds %struct.internal_state, %struct.internal_state* %6, i32 0, i32 30, !dbg !3343
  %7 = load i32, i32* %prev_length, align 8, !dbg !3343
  store i32 %7, i32* %best_len, align 4, !dbg !3341
  call void @llvm.dbg.declare(metadata i32* %nice_match, metadata !3344, metadata !277), !dbg !3345
  %8 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3346
  %nice_match1 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %8, i32 0, i32 36, !dbg !3347
  %9 = load i32, i32* %nice_match1, align 8, !dbg !3347
  store i32 %9, i32* %nice_match, align 4, !dbg !3345
  call void @llvm.dbg.declare(metadata i32* %limit, metadata !3348, metadata !277), !dbg !3349
  %10 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3350
  %strstart2 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %10, i32 0, i32 27, !dbg !3351
  %11 = load i32, i32* %strstart2, align 4, !dbg !3351
  %12 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3352
  %w_size = getelementptr inbounds %struct.internal_state, %struct.internal_state* %12, i32 0, i32 11, !dbg !3352
  %13 = load i32, i32* %w_size, align 4, !dbg !3352
  %sub = sub i32 %13, 262, !dbg !3352
  %cmp = icmp ugt i32 %11, %sub, !dbg !3353
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !3350

cond.true:                                        ; preds = %entry
  %14 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3354
  %strstart3 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %14, i32 0, i32 27, !dbg !3355
  %15 = load i32, i32* %strstart3, align 4, !dbg !3355
  %16 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3356
  %w_size4 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %16, i32 0, i32 11, !dbg !3356
  %17 = load i32, i32* %w_size4, align 4, !dbg !3356
  %sub5 = sub i32 %17, 262, !dbg !3356
  %sub6 = sub i32 %15, %sub5, !dbg !3357
  br label %cond.end, !dbg !3358

cond.false:                                       ; preds = %entry
  br label %cond.end, !dbg !3360

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %sub6, %cond.true ], [ 0, %cond.false ], !dbg !3362
  store i32 %cond, i32* %limit, align 4, !dbg !3364
  call void @llvm.dbg.declare(metadata i16** %prev, metadata !3365, metadata !277), !dbg !3366
  %18 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3367
  %prev7 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %18, i32 0, i32 16, !dbg !3368
  %19 = load i16*, i16** %prev7, align 8, !dbg !3368
  store i16* %19, i16** %prev, align 8, !dbg !3366
  call void @llvm.dbg.declare(metadata i32* %wmask, metadata !3369, metadata !277), !dbg !3370
  %20 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3371
  %w_mask = getelementptr inbounds %struct.internal_state, %struct.internal_state* %20, i32 0, i32 13, !dbg !3372
  %21 = load i32, i32* %w_mask, align 4, !dbg !3372
  store i32 %21, i32* %wmask, align 4, !dbg !3370
  call void @llvm.dbg.declare(metadata i8** %strend, metadata !3373, metadata !277), !dbg !3374
  %22 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3375
  %window8 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %22, i32 0, i32 14, !dbg !3376
  %23 = load i8*, i8** %window8, align 8, !dbg !3376
  %24 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3377
  %strstart9 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %24, i32 0, i32 27, !dbg !3378
  %25 = load i32, i32* %strstart9, align 4, !dbg !3378
  %idx.ext10 = zext i32 %25 to i64, !dbg !3379
  %add.ptr11 = getelementptr inbounds i8, i8* %23, i64 %idx.ext10, !dbg !3379
  %add.ptr12 = getelementptr inbounds i8, i8* %add.ptr11, i64 258, !dbg !3380
  store i8* %add.ptr12, i8** %strend, align 8, !dbg !3374
  call void @llvm.dbg.declare(metadata i8* %scan_end1, metadata !3381, metadata !277), !dbg !3382
  %26 = load i32, i32* %best_len, align 4, !dbg !3383
  %sub13 = sub nsw i32 %26, 1, !dbg !3384
  %idxprom = sext i32 %sub13 to i64, !dbg !3385
  %27 = load i8*, i8** %scan, align 8, !dbg !3385
  %arrayidx = getelementptr inbounds i8, i8* %27, i64 %idxprom, !dbg !3385
  %28 = load i8, i8* %arrayidx, align 1, !dbg !3385
  store i8 %28, i8* %scan_end1, align 1, !dbg !3382
  call void @llvm.dbg.declare(metadata i8* %scan_end, metadata !3386, metadata !277), !dbg !3387
  %29 = load i32, i32* %best_len, align 4, !dbg !3388
  %idxprom14 = sext i32 %29 to i64, !dbg !3389
  %30 = load i8*, i8** %scan, align 8, !dbg !3389
  %arrayidx15 = getelementptr inbounds i8, i8* %30, i64 %idxprom14, !dbg !3389
  %31 = load i8, i8* %arrayidx15, align 1, !dbg !3389
  store i8 %31, i8* %scan_end, align 1, !dbg !3387
  %32 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3390
  %prev_length16 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %32, i32 0, i32 30, !dbg !3392
  %33 = load i32, i32* %prev_length16, align 8, !dbg !3392
  %34 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3393
  %good_match = getelementptr inbounds %struct.internal_state, %struct.internal_state* %34, i32 0, i32 35, !dbg !3394
  %35 = load i32, i32* %good_match, align 4, !dbg !3394
  %cmp17 = icmp uge i32 %33, %35, !dbg !3395
  br i1 %cmp17, label %if.then, label %if.end, !dbg !3396

if.then:                                          ; preds = %cond.end
  %36 = load i32, i32* %chain_length, align 4, !dbg !3397
  %shr = lshr i32 %36, 2, !dbg !3397
  store i32 %shr, i32* %chain_length, align 4, !dbg !3397
  br label %if.end, !dbg !3399

if.end:                                           ; preds = %if.then, %cond.end
  %37 = load i32, i32* %nice_match, align 4, !dbg !3400
  %38 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3402
  %lookahead = getelementptr inbounds %struct.internal_state, %struct.internal_state* %38, i32 0, i32 29, !dbg !3403
  %39 = load i32, i32* %lookahead, align 4, !dbg !3403
  %cmp18 = icmp ugt i32 %37, %39, !dbg !3404
  br i1 %cmp18, label %if.then19, label %if.end21, !dbg !3405

if.then19:                                        ; preds = %if.end
  %40 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3406
  %lookahead20 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %40, i32 0, i32 29, !dbg !3408
  %41 = load i32, i32* %lookahead20, align 4, !dbg !3408
  store i32 %41, i32* %nice_match, align 4, !dbg !3409
  br label %if.end21, !dbg !3410

if.end21:                                         ; preds = %if.then19, %if.end
  br label %do.body, !dbg !3411

do.body:                                          ; preds = %land.end134, %if.end21
  %42 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3412
  %window22 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %42, i32 0, i32 14, !dbg !3414
  %43 = load i8*, i8** %window22, align 8, !dbg !3414
  %44 = load i32, i32* %cur_match.addr, align 4, !dbg !3415
  %idx.ext23 = zext i32 %44 to i64, !dbg !3416
  %add.ptr24 = getelementptr inbounds i8, i8* %43, i64 %idx.ext23, !dbg !3416
  store i8* %add.ptr24, i8** %match, align 8, !dbg !3417
  %45 = load i32, i32* %best_len, align 4, !dbg !3418
  %idxprom25 = sext i32 %45 to i64, !dbg !3420
  %46 = load i8*, i8** %match, align 8, !dbg !3420
  %arrayidx26 = getelementptr inbounds i8, i8* %46, i64 %idxprom25, !dbg !3420
  %47 = load i8, i8* %arrayidx26, align 1, !dbg !3420
  %conv = zext i8 %47 to i32, !dbg !3420
  %48 = load i8, i8* %scan_end, align 1, !dbg !3421
  %conv27 = zext i8 %48 to i32, !dbg !3421
  %cmp28 = icmp ne i32 %conv, %conv27, !dbg !3422
  br i1 %cmp28, label %if.then48, label %lor.lhs.false, !dbg !3423

lor.lhs.false:                                    ; preds = %do.body
  %49 = load i32, i32* %best_len, align 4, !dbg !3424
  %sub30 = sub nsw i32 %49, 1, !dbg !3425
  %idxprom31 = sext i32 %sub30 to i64, !dbg !3426
  %50 = load i8*, i8** %match, align 8, !dbg !3426
  %arrayidx32 = getelementptr inbounds i8, i8* %50, i64 %idxprom31, !dbg !3426
  %51 = load i8, i8* %arrayidx32, align 1, !dbg !3426
  %conv33 = zext i8 %51 to i32, !dbg !3426
  %52 = load i8, i8* %scan_end1, align 1, !dbg !3427
  %conv34 = zext i8 %52 to i32, !dbg !3427
  %cmp35 = icmp ne i32 %conv33, %conv34, !dbg !3428
  br i1 %cmp35, label %if.then48, label %lor.lhs.false37, !dbg !3429

lor.lhs.false37:                                  ; preds = %lor.lhs.false
  %53 = load i8*, i8** %match, align 8, !dbg !3430
  %54 = load i8, i8* %53, align 1, !dbg !3431
  %conv38 = zext i8 %54 to i32, !dbg !3431
  %55 = load i8*, i8** %scan, align 8, !dbg !3432
  %56 = load i8, i8* %55, align 1, !dbg !3433
  %conv39 = zext i8 %56 to i32, !dbg !3433
  %cmp40 = icmp ne i32 %conv38, %conv39, !dbg !3434
  br i1 %cmp40, label %if.then48, label %lor.lhs.false42, !dbg !3435

lor.lhs.false42:                                  ; preds = %lor.lhs.false37
  %57 = load i8*, i8** %match, align 8, !dbg !3436
  %incdec.ptr = getelementptr inbounds i8, i8* %57, i32 1, !dbg !3436
  store i8* %incdec.ptr, i8** %match, align 8, !dbg !3436
  %58 = load i8, i8* %incdec.ptr, align 1, !dbg !3437
  %conv43 = zext i8 %58 to i32, !dbg !3437
  %59 = load i8*, i8** %scan, align 8, !dbg !3438
  %arrayidx44 = getelementptr inbounds i8, i8* %59, i64 1, !dbg !3438
  %60 = load i8, i8* %arrayidx44, align 1, !dbg !3438
  %conv45 = zext i8 %60 to i32, !dbg !3438
  %cmp46 = icmp ne i32 %conv43, %conv45, !dbg !3439
  br i1 %cmp46, label %if.then48, label %if.end49, !dbg !3440

if.then48:                                        ; preds = %lor.lhs.false42, %lor.lhs.false37, %lor.lhs.false, %do.body
  br label %do.cond125, !dbg !3442

if.end49:                                         ; preds = %lor.lhs.false42
  %61 = load i8*, i8** %scan, align 8, !dbg !3444
  %add.ptr50 = getelementptr inbounds i8, i8* %61, i64 2, !dbg !3444
  store i8* %add.ptr50, i8** %scan, align 8, !dbg !3444
  %62 = load i8*, i8** %match, align 8, !dbg !3445
  %incdec.ptr51 = getelementptr inbounds i8, i8* %62, i32 1, !dbg !3445
  store i8* %incdec.ptr51, i8** %match, align 8, !dbg !3445
  br label %do.body52, !dbg !3446

do.body52:                                        ; preds = %land.end, %if.end49
  br label %do.cond, !dbg !3447

do.cond:                                          ; preds = %do.body52
  %63 = load i8*, i8** %scan, align 8, !dbg !3449
  %incdec.ptr53 = getelementptr inbounds i8, i8* %63, i32 1, !dbg !3449
  store i8* %incdec.ptr53, i8** %scan, align 8, !dbg !3449
  %64 = load i8, i8* %incdec.ptr53, align 1, !dbg !3450
  %conv54 = zext i8 %64 to i32, !dbg !3450
  %65 = load i8*, i8** %match, align 8, !dbg !3451
  %incdec.ptr55 = getelementptr inbounds i8, i8* %65, i32 1, !dbg !3451
  store i8* %incdec.ptr55, i8** %match, align 8, !dbg !3451
  %66 = load i8, i8* %incdec.ptr55, align 1, !dbg !3452
  %conv56 = zext i8 %66 to i32, !dbg !3452
  %cmp57 = icmp eq i32 %conv54, %conv56, !dbg !3453
  br i1 %cmp57, label %land.lhs.true, label %land.end, !dbg !3454

land.lhs.true:                                    ; preds = %do.cond
  %67 = load i8*, i8** %scan, align 8, !dbg !3455
  %incdec.ptr59 = getelementptr inbounds i8, i8* %67, i32 1, !dbg !3455
  store i8* %incdec.ptr59, i8** %scan, align 8, !dbg !3455
  %68 = load i8, i8* %incdec.ptr59, align 1, !dbg !3457
  %conv60 = zext i8 %68 to i32, !dbg !3457
  %69 = load i8*, i8** %match, align 8, !dbg !3458
  %incdec.ptr61 = getelementptr inbounds i8, i8* %69, i32 1, !dbg !3458
  store i8* %incdec.ptr61, i8** %match, align 8, !dbg !3458
  %70 = load i8, i8* %incdec.ptr61, align 1, !dbg !3459
  %conv62 = zext i8 %70 to i32, !dbg !3459
  %cmp63 = icmp eq i32 %conv60, %conv62, !dbg !3460
  br i1 %cmp63, label %land.lhs.true65, label %land.end, !dbg !3461

land.lhs.true65:                                  ; preds = %land.lhs.true
  %71 = load i8*, i8** %scan, align 8, !dbg !3462
  %incdec.ptr66 = getelementptr inbounds i8, i8* %71, i32 1, !dbg !3462
  store i8* %incdec.ptr66, i8** %scan, align 8, !dbg !3462
  %72 = load i8, i8* %incdec.ptr66, align 1, !dbg !3463
  %conv67 = zext i8 %72 to i32, !dbg !3463
  %73 = load i8*, i8** %match, align 8, !dbg !3464
  %incdec.ptr68 = getelementptr inbounds i8, i8* %73, i32 1, !dbg !3464
  store i8* %incdec.ptr68, i8** %match, align 8, !dbg !3464
  %74 = load i8, i8* %incdec.ptr68, align 1, !dbg !3465
  %conv69 = zext i8 %74 to i32, !dbg !3465
  %cmp70 = icmp eq i32 %conv67, %conv69, !dbg !3466
  br i1 %cmp70, label %land.lhs.true72, label %land.end, !dbg !3467

land.lhs.true72:                                  ; preds = %land.lhs.true65
  %75 = load i8*, i8** %scan, align 8, !dbg !3468
  %incdec.ptr73 = getelementptr inbounds i8, i8* %75, i32 1, !dbg !3468
  store i8* %incdec.ptr73, i8** %scan, align 8, !dbg !3468
  %76 = load i8, i8* %incdec.ptr73, align 1, !dbg !3469
  %conv74 = zext i8 %76 to i32, !dbg !3469
  %77 = load i8*, i8** %match, align 8, !dbg !3470
  %incdec.ptr75 = getelementptr inbounds i8, i8* %77, i32 1, !dbg !3470
  store i8* %incdec.ptr75, i8** %match, align 8, !dbg !3470
  %78 = load i8, i8* %incdec.ptr75, align 1, !dbg !3471
  %conv76 = zext i8 %78 to i32, !dbg !3471
  %cmp77 = icmp eq i32 %conv74, %conv76, !dbg !3472
  br i1 %cmp77, label %land.lhs.true79, label %land.end, !dbg !3473

land.lhs.true79:                                  ; preds = %land.lhs.true72
  %79 = load i8*, i8** %scan, align 8, !dbg !3474
  %incdec.ptr80 = getelementptr inbounds i8, i8* %79, i32 1, !dbg !3474
  store i8* %incdec.ptr80, i8** %scan, align 8, !dbg !3474
  %80 = load i8, i8* %incdec.ptr80, align 1, !dbg !3475
  %conv81 = zext i8 %80 to i32, !dbg !3475
  %81 = load i8*, i8** %match, align 8, !dbg !3476
  %incdec.ptr82 = getelementptr inbounds i8, i8* %81, i32 1, !dbg !3476
  store i8* %incdec.ptr82, i8** %match, align 8, !dbg !3476
  %82 = load i8, i8* %incdec.ptr82, align 1, !dbg !3477
  %conv83 = zext i8 %82 to i32, !dbg !3477
  %cmp84 = icmp eq i32 %conv81, %conv83, !dbg !3478
  br i1 %cmp84, label %land.lhs.true86, label %land.end, !dbg !3479

land.lhs.true86:                                  ; preds = %land.lhs.true79
  %83 = load i8*, i8** %scan, align 8, !dbg !3480
  %incdec.ptr87 = getelementptr inbounds i8, i8* %83, i32 1, !dbg !3480
  store i8* %incdec.ptr87, i8** %scan, align 8, !dbg !3480
  %84 = load i8, i8* %incdec.ptr87, align 1, !dbg !3481
  %conv88 = zext i8 %84 to i32, !dbg !3481
  %85 = load i8*, i8** %match, align 8, !dbg !3482
  %incdec.ptr89 = getelementptr inbounds i8, i8* %85, i32 1, !dbg !3482
  store i8* %incdec.ptr89, i8** %match, align 8, !dbg !3482
  %86 = load i8, i8* %incdec.ptr89, align 1, !dbg !3483
  %conv90 = zext i8 %86 to i32, !dbg !3483
  %cmp91 = icmp eq i32 %conv88, %conv90, !dbg !3484
  br i1 %cmp91, label %land.lhs.true93, label %land.end, !dbg !3485

land.lhs.true93:                                  ; preds = %land.lhs.true86
  %87 = load i8*, i8** %scan, align 8, !dbg !3486
  %incdec.ptr94 = getelementptr inbounds i8, i8* %87, i32 1, !dbg !3486
  store i8* %incdec.ptr94, i8** %scan, align 8, !dbg !3486
  %88 = load i8, i8* %incdec.ptr94, align 1, !dbg !3487
  %conv95 = zext i8 %88 to i32, !dbg !3487
  %89 = load i8*, i8** %match, align 8, !dbg !3488
  %incdec.ptr96 = getelementptr inbounds i8, i8* %89, i32 1, !dbg !3488
  store i8* %incdec.ptr96, i8** %match, align 8, !dbg !3488
  %90 = load i8, i8* %incdec.ptr96, align 1, !dbg !3489
  %conv97 = zext i8 %90 to i32, !dbg !3489
  %cmp98 = icmp eq i32 %conv95, %conv97, !dbg !3490
  br i1 %cmp98, label %land.lhs.true100, label %land.end, !dbg !3491

land.lhs.true100:                                 ; preds = %land.lhs.true93
  %91 = load i8*, i8** %scan, align 8, !dbg !3492
  %incdec.ptr101 = getelementptr inbounds i8, i8* %91, i32 1, !dbg !3492
  store i8* %incdec.ptr101, i8** %scan, align 8, !dbg !3492
  %92 = load i8, i8* %incdec.ptr101, align 1, !dbg !3493
  %conv102 = zext i8 %92 to i32, !dbg !3493
  %93 = load i8*, i8** %match, align 8, !dbg !3494
  %incdec.ptr103 = getelementptr inbounds i8, i8* %93, i32 1, !dbg !3494
  store i8* %incdec.ptr103, i8** %match, align 8, !dbg !3494
  %94 = load i8, i8* %incdec.ptr103, align 1, !dbg !3495
  %conv104 = zext i8 %94 to i32, !dbg !3495
  %cmp105 = icmp eq i32 %conv102, %conv104, !dbg !3496
  br i1 %cmp105, label %land.rhs, label %land.end, !dbg !3497

land.rhs:                                         ; preds = %land.lhs.true100
  %95 = load i8*, i8** %scan, align 8, !dbg !3498
  %96 = load i8*, i8** %strend, align 8, !dbg !3499
  %cmp107 = icmp ult i8* %95, %96, !dbg !3500
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true100, %land.lhs.true93, %land.lhs.true86, %land.lhs.true79, %land.lhs.true72, %land.lhs.true65, %land.lhs.true, %do.cond
  %97 = phi i1 [ false, %land.lhs.true100 ], [ false, %land.lhs.true93 ], [ false, %land.lhs.true86 ], [ false, %land.lhs.true79 ], [ false, %land.lhs.true72 ], [ false, %land.lhs.true65 ], [ false, %land.lhs.true ], [ false, %do.cond ], [ %cmp107, %land.rhs ]
  br i1 %97, label %do.body52, label %do.end, !dbg !3501

do.end:                                           ; preds = %land.end
  %98 = load i8*, i8** %strend, align 8, !dbg !3503
  %99 = load i8*, i8** %scan, align 8, !dbg !3504
  %sub.ptr.lhs.cast = ptrtoint i8* %98 to i64, !dbg !3505
  %sub.ptr.rhs.cast = ptrtoint i8* %99 to i64, !dbg !3505
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !3505
  %conv109 = trunc i64 %sub.ptr.sub to i32, !dbg !3506
  %sub110 = sub nsw i32 258, %conv109, !dbg !3507
  store i32 %sub110, i32* %len, align 4, !dbg !3508
  %100 = load i8*, i8** %strend, align 8, !dbg !3509
  %add.ptr111 = getelementptr inbounds i8, i8* %100, i64 -258, !dbg !3510
  store i8* %add.ptr111, i8** %scan, align 8, !dbg !3511
  %101 = load i32, i32* %len, align 4, !dbg !3512
  %102 = load i32, i32* %best_len, align 4, !dbg !3514
  %cmp112 = icmp sgt i32 %101, %102, !dbg !3515
  br i1 %cmp112, label %if.then114, label %if.end124, !dbg !3516

if.then114:                                       ; preds = %do.end
  %103 = load i32, i32* %cur_match.addr, align 4, !dbg !3517
  %104 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3519
  %match_start = getelementptr inbounds %struct.internal_state, %struct.internal_state* %104, i32 0, i32 28, !dbg !3520
  store i32 %103, i32* %match_start, align 8, !dbg !3521
  %105 = load i32, i32* %len, align 4, !dbg !3522
  store i32 %105, i32* %best_len, align 4, !dbg !3523
  %106 = load i32, i32* %len, align 4, !dbg !3524
  %107 = load i32, i32* %nice_match, align 4, !dbg !3526
  %cmp115 = icmp sge i32 %106, %107, !dbg !3527
  br i1 %cmp115, label %if.then117, label %if.end118, !dbg !3528

if.then117:                                       ; preds = %if.then114
  br label %do.end135, !dbg !3529

if.end118:                                        ; preds = %if.then114
  %108 = load i32, i32* %best_len, align 4, !dbg !3531
  %sub119 = sub nsw i32 %108, 1, !dbg !3532
  %idxprom120 = sext i32 %sub119 to i64, !dbg !3533
  %109 = load i8*, i8** %scan, align 8, !dbg !3533
  %arrayidx121 = getelementptr inbounds i8, i8* %109, i64 %idxprom120, !dbg !3533
  %110 = load i8, i8* %arrayidx121, align 1, !dbg !3533
  store i8 %110, i8* %scan_end1, align 1, !dbg !3534
  %111 = load i32, i32* %best_len, align 4, !dbg !3535
  %idxprom122 = sext i32 %111 to i64, !dbg !3536
  %112 = load i8*, i8** %scan, align 8, !dbg !3536
  %arrayidx123 = getelementptr inbounds i8, i8* %112, i64 %idxprom122, !dbg !3536
  %113 = load i8, i8* %arrayidx123, align 1, !dbg !3536
  store i8 %113, i8* %scan_end, align 1, !dbg !3537
  br label %if.end124, !dbg !3538

if.end124:                                        ; preds = %if.end118, %do.end
  br label %do.cond125, !dbg !3539

do.cond125:                                       ; preds = %if.end124, %if.then48
  %114 = load i32, i32* %cur_match.addr, align 4, !dbg !3540
  %115 = load i32, i32* %wmask, align 4, !dbg !3541
  %and = and i32 %114, %115, !dbg !3542
  %idxprom126 = zext i32 %and to i64, !dbg !3543
  %116 = load i16*, i16** %prev, align 8, !dbg !3543
  %arrayidx127 = getelementptr inbounds i16, i16* %116, i64 %idxprom126, !dbg !3543
  %117 = load i16, i16* %arrayidx127, align 2, !dbg !3543
  %conv128 = zext i16 %117 to i32, !dbg !3543
  store i32 %conv128, i32* %cur_match.addr, align 4, !dbg !3544
  %118 = load i32, i32* %limit, align 4, !dbg !3545
  %cmp129 = icmp ugt i32 %conv128, %118, !dbg !3546
  br i1 %cmp129, label %land.rhs131, label %land.end134, !dbg !3547

land.rhs131:                                      ; preds = %do.cond125
  %119 = load i32, i32* %chain_length, align 4, !dbg !3548
  %dec = add i32 %119, -1, !dbg !3548
  store i32 %dec, i32* %chain_length, align 4, !dbg !3548
  %cmp132 = icmp ne i32 %dec, 0, !dbg !3549
  br label %land.end134

land.end134:                                      ; preds = %land.rhs131, %do.cond125
  %120 = phi i1 [ false, %do.cond125 ], [ %cmp132, %land.rhs131 ]
  br i1 %120, label %do.body, label %do.end135, !dbg !3550

do.end135:                                        ; preds = %land.end134, %if.then117
  %121 = load i32, i32* %best_len, align 4, !dbg !3551
  %122 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3553
  %lookahead136 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %122, i32 0, i32 29, !dbg !3554
  %123 = load i32, i32* %lookahead136, align 4, !dbg !3554
  %cmp137 = icmp ule i32 %121, %123, !dbg !3555
  br i1 %cmp137, label %if.then139, label %if.end140, !dbg !3556

if.then139:                                       ; preds = %do.end135
  %124 = load i32, i32* %best_len, align 4, !dbg !3557
  store i32 %124, i32* %retval, align 4, !dbg !3559
  br label %return, !dbg !3559

if.end140:                                        ; preds = %do.end135
  %125 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3560
  %lookahead141 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %125, i32 0, i32 29, !dbg !3561
  %126 = load i32, i32* %lookahead141, align 4, !dbg !3561
  store i32 %126, i32* %retval, align 4, !dbg !3562
  br label %return, !dbg !3562

return:                                           ; preds = %if.end140, %if.then139
  %127 = load i32, i32* %retval, align 4, !dbg !3563
  ret i32 %127, !dbg !3563
}

; Function Attrs: nounwind uwtable
define internal i32 @longest_match_fast(%struct.internal_state* %s, i32 %cur_match) #0 !dbg !240 {
entry:
  %retval = alloca i32, align 4
  %s.addr = alloca %struct.internal_state*, align 8
  %cur_match.addr = alloca i32, align 4
  %scan = alloca i8*, align 8
  %match = alloca i8*, align 8
  %len = alloca i32, align 4
  %strend = alloca i8*, align 8
  store %struct.internal_state* %s, %struct.internal_state** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.internal_state** %s.addr, metadata !3564, metadata !277), !dbg !3565
  store i32 %cur_match, i32* %cur_match.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %cur_match.addr, metadata !3566, metadata !277), !dbg !3567
  call void @llvm.dbg.declare(metadata i8** %scan, metadata !3568, metadata !277), !dbg !3569
  %0 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3570
  %window = getelementptr inbounds %struct.internal_state, %struct.internal_state* %0, i32 0, i32 14, !dbg !3571
  %1 = load i8*, i8** %window, align 8, !dbg !3571
  %2 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3572
  %strstart = getelementptr inbounds %struct.internal_state, %struct.internal_state* %2, i32 0, i32 27, !dbg !3573
  %3 = load i32, i32* %strstart, align 4, !dbg !3573
  %idx.ext = zext i32 %3 to i64, !dbg !3574
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 %idx.ext, !dbg !3574
  store i8* %add.ptr, i8** %scan, align 8, !dbg !3569
  call void @llvm.dbg.declare(metadata i8** %match, metadata !3575, metadata !277), !dbg !3576
  call void @llvm.dbg.declare(metadata i32* %len, metadata !3577, metadata !277), !dbg !3578
  call void @llvm.dbg.declare(metadata i8** %strend, metadata !3579, metadata !277), !dbg !3580
  %4 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3581
  %window1 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %4, i32 0, i32 14, !dbg !3582
  %5 = load i8*, i8** %window1, align 8, !dbg !3582
  %6 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3583
  %strstart2 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %6, i32 0, i32 27, !dbg !3584
  %7 = load i32, i32* %strstart2, align 4, !dbg !3584
  %idx.ext3 = zext i32 %7 to i64, !dbg !3585
  %add.ptr4 = getelementptr inbounds i8, i8* %5, i64 %idx.ext3, !dbg !3585
  %add.ptr5 = getelementptr inbounds i8, i8* %add.ptr4, i64 258, !dbg !3586
  store i8* %add.ptr5, i8** %strend, align 8, !dbg !3580
  %8 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3587
  %window6 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %8, i32 0, i32 14, !dbg !3588
  %9 = load i8*, i8** %window6, align 8, !dbg !3588
  %10 = load i32, i32* %cur_match.addr, align 4, !dbg !3589
  %idx.ext7 = zext i32 %10 to i64, !dbg !3590
  %add.ptr8 = getelementptr inbounds i8, i8* %9, i64 %idx.ext7, !dbg !3590
  store i8* %add.ptr8, i8** %match, align 8, !dbg !3591
  %11 = load i8*, i8** %match, align 8, !dbg !3592
  %arrayidx = getelementptr inbounds i8, i8* %11, i64 0, !dbg !3592
  %12 = load i8, i8* %arrayidx, align 1, !dbg !3592
  %conv = zext i8 %12 to i32, !dbg !3592
  %13 = load i8*, i8** %scan, align 8, !dbg !3594
  %arrayidx9 = getelementptr inbounds i8, i8* %13, i64 0, !dbg !3594
  %14 = load i8, i8* %arrayidx9, align 1, !dbg !3594
  %conv10 = zext i8 %14 to i32, !dbg !3594
  %cmp = icmp ne i32 %conv, %conv10, !dbg !3595
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !3596

lor.lhs.false:                                    ; preds = %entry
  %15 = load i8*, i8** %match, align 8, !dbg !3597
  %arrayidx12 = getelementptr inbounds i8, i8* %15, i64 1, !dbg !3597
  %16 = load i8, i8* %arrayidx12, align 1, !dbg !3597
  %conv13 = zext i8 %16 to i32, !dbg !3597
  %17 = load i8*, i8** %scan, align 8, !dbg !3599
  %arrayidx14 = getelementptr inbounds i8, i8* %17, i64 1, !dbg !3599
  %18 = load i8, i8* %arrayidx14, align 1, !dbg !3599
  %conv15 = zext i8 %18 to i32, !dbg !3599
  %cmp16 = icmp ne i32 %conv13, %conv15, !dbg !3600
  br i1 %cmp16, label %if.then, label %if.end, !dbg !3601

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 2, i32* %retval, align 4, !dbg !3602
  br label %return, !dbg !3602

if.end:                                           ; preds = %lor.lhs.false
  %19 = load i8*, i8** %scan, align 8, !dbg !3604
  %add.ptr18 = getelementptr inbounds i8, i8* %19, i64 2, !dbg !3604
  store i8* %add.ptr18, i8** %scan, align 8, !dbg !3604
  %20 = load i8*, i8** %match, align 8, !dbg !3605
  %add.ptr19 = getelementptr inbounds i8, i8* %20, i64 2, !dbg !3605
  store i8* %add.ptr19, i8** %match, align 8, !dbg !3605
  br label %do.body, !dbg !3606

do.body:                                          ; preds = %land.end, %if.end
  br label %do.cond, !dbg !3607

do.cond:                                          ; preds = %do.body
  %21 = load i8*, i8** %scan, align 8, !dbg !3609
  %incdec.ptr = getelementptr inbounds i8, i8* %21, i32 1, !dbg !3609
  store i8* %incdec.ptr, i8** %scan, align 8, !dbg !3609
  %22 = load i8, i8* %incdec.ptr, align 1, !dbg !3611
  %conv20 = zext i8 %22 to i32, !dbg !3611
  %23 = load i8*, i8** %match, align 8, !dbg !3612
  %incdec.ptr21 = getelementptr inbounds i8, i8* %23, i32 1, !dbg !3612
  store i8* %incdec.ptr21, i8** %match, align 8, !dbg !3612
  %24 = load i8, i8* %incdec.ptr21, align 1, !dbg !3613
  %conv22 = zext i8 %24 to i32, !dbg !3613
  %cmp23 = icmp eq i32 %conv20, %conv22, !dbg !3614
  br i1 %cmp23, label %land.lhs.true, label %land.end, !dbg !3615

land.lhs.true:                                    ; preds = %do.cond
  %25 = load i8*, i8** %scan, align 8, !dbg !3616
  %incdec.ptr25 = getelementptr inbounds i8, i8* %25, i32 1, !dbg !3616
  store i8* %incdec.ptr25, i8** %scan, align 8, !dbg !3616
  %26 = load i8, i8* %incdec.ptr25, align 1, !dbg !3618
  %conv26 = zext i8 %26 to i32, !dbg !3618
  %27 = load i8*, i8** %match, align 8, !dbg !3619
  %incdec.ptr27 = getelementptr inbounds i8, i8* %27, i32 1, !dbg !3619
  store i8* %incdec.ptr27, i8** %match, align 8, !dbg !3619
  %28 = load i8, i8* %incdec.ptr27, align 1, !dbg !3620
  %conv28 = zext i8 %28 to i32, !dbg !3620
  %cmp29 = icmp eq i32 %conv26, %conv28, !dbg !3621
  br i1 %cmp29, label %land.lhs.true31, label %land.end, !dbg !3622

land.lhs.true31:                                  ; preds = %land.lhs.true
  %29 = load i8*, i8** %scan, align 8, !dbg !3623
  %incdec.ptr32 = getelementptr inbounds i8, i8* %29, i32 1, !dbg !3623
  store i8* %incdec.ptr32, i8** %scan, align 8, !dbg !3623
  %30 = load i8, i8* %incdec.ptr32, align 1, !dbg !3624
  %conv33 = zext i8 %30 to i32, !dbg !3624
  %31 = load i8*, i8** %match, align 8, !dbg !3625
  %incdec.ptr34 = getelementptr inbounds i8, i8* %31, i32 1, !dbg !3625
  store i8* %incdec.ptr34, i8** %match, align 8, !dbg !3625
  %32 = load i8, i8* %incdec.ptr34, align 1, !dbg !3626
  %conv35 = zext i8 %32 to i32, !dbg !3626
  %cmp36 = icmp eq i32 %conv33, %conv35, !dbg !3627
  br i1 %cmp36, label %land.lhs.true38, label %land.end, !dbg !3628

land.lhs.true38:                                  ; preds = %land.lhs.true31
  %33 = load i8*, i8** %scan, align 8, !dbg !3629
  %incdec.ptr39 = getelementptr inbounds i8, i8* %33, i32 1, !dbg !3629
  store i8* %incdec.ptr39, i8** %scan, align 8, !dbg !3629
  %34 = load i8, i8* %incdec.ptr39, align 1, !dbg !3630
  %conv40 = zext i8 %34 to i32, !dbg !3630
  %35 = load i8*, i8** %match, align 8, !dbg !3631
  %incdec.ptr41 = getelementptr inbounds i8, i8* %35, i32 1, !dbg !3631
  store i8* %incdec.ptr41, i8** %match, align 8, !dbg !3631
  %36 = load i8, i8* %incdec.ptr41, align 1, !dbg !3632
  %conv42 = zext i8 %36 to i32, !dbg !3632
  %cmp43 = icmp eq i32 %conv40, %conv42, !dbg !3633
  br i1 %cmp43, label %land.lhs.true45, label %land.end, !dbg !3634

land.lhs.true45:                                  ; preds = %land.lhs.true38
  %37 = load i8*, i8** %scan, align 8, !dbg !3635
  %incdec.ptr46 = getelementptr inbounds i8, i8* %37, i32 1, !dbg !3635
  store i8* %incdec.ptr46, i8** %scan, align 8, !dbg !3635
  %38 = load i8, i8* %incdec.ptr46, align 1, !dbg !3636
  %conv47 = zext i8 %38 to i32, !dbg !3636
  %39 = load i8*, i8** %match, align 8, !dbg !3637
  %incdec.ptr48 = getelementptr inbounds i8, i8* %39, i32 1, !dbg !3637
  store i8* %incdec.ptr48, i8** %match, align 8, !dbg !3637
  %40 = load i8, i8* %incdec.ptr48, align 1, !dbg !3638
  %conv49 = zext i8 %40 to i32, !dbg !3638
  %cmp50 = icmp eq i32 %conv47, %conv49, !dbg !3639
  br i1 %cmp50, label %land.lhs.true52, label %land.end, !dbg !3640

land.lhs.true52:                                  ; preds = %land.lhs.true45
  %41 = load i8*, i8** %scan, align 8, !dbg !3641
  %incdec.ptr53 = getelementptr inbounds i8, i8* %41, i32 1, !dbg !3641
  store i8* %incdec.ptr53, i8** %scan, align 8, !dbg !3641
  %42 = load i8, i8* %incdec.ptr53, align 1, !dbg !3642
  %conv54 = zext i8 %42 to i32, !dbg !3642
  %43 = load i8*, i8** %match, align 8, !dbg !3643
  %incdec.ptr55 = getelementptr inbounds i8, i8* %43, i32 1, !dbg !3643
  store i8* %incdec.ptr55, i8** %match, align 8, !dbg !3643
  %44 = load i8, i8* %incdec.ptr55, align 1, !dbg !3644
  %conv56 = zext i8 %44 to i32, !dbg !3644
  %cmp57 = icmp eq i32 %conv54, %conv56, !dbg !3645
  br i1 %cmp57, label %land.lhs.true59, label %land.end, !dbg !3646

land.lhs.true59:                                  ; preds = %land.lhs.true52
  %45 = load i8*, i8** %scan, align 8, !dbg !3647
  %incdec.ptr60 = getelementptr inbounds i8, i8* %45, i32 1, !dbg !3647
  store i8* %incdec.ptr60, i8** %scan, align 8, !dbg !3647
  %46 = load i8, i8* %incdec.ptr60, align 1, !dbg !3648
  %conv61 = zext i8 %46 to i32, !dbg !3648
  %47 = load i8*, i8** %match, align 8, !dbg !3649
  %incdec.ptr62 = getelementptr inbounds i8, i8* %47, i32 1, !dbg !3649
  store i8* %incdec.ptr62, i8** %match, align 8, !dbg !3649
  %48 = load i8, i8* %incdec.ptr62, align 1, !dbg !3650
  %conv63 = zext i8 %48 to i32, !dbg !3650
  %cmp64 = icmp eq i32 %conv61, %conv63, !dbg !3651
  br i1 %cmp64, label %land.lhs.true66, label %land.end, !dbg !3652

land.lhs.true66:                                  ; preds = %land.lhs.true59
  %49 = load i8*, i8** %scan, align 8, !dbg !3653
  %incdec.ptr67 = getelementptr inbounds i8, i8* %49, i32 1, !dbg !3653
  store i8* %incdec.ptr67, i8** %scan, align 8, !dbg !3653
  %50 = load i8, i8* %incdec.ptr67, align 1, !dbg !3654
  %conv68 = zext i8 %50 to i32, !dbg !3654
  %51 = load i8*, i8** %match, align 8, !dbg !3655
  %incdec.ptr69 = getelementptr inbounds i8, i8* %51, i32 1, !dbg !3655
  store i8* %incdec.ptr69, i8** %match, align 8, !dbg !3655
  %52 = load i8, i8* %incdec.ptr69, align 1, !dbg !3656
  %conv70 = zext i8 %52 to i32, !dbg !3656
  %cmp71 = icmp eq i32 %conv68, %conv70, !dbg !3657
  br i1 %cmp71, label %land.rhs, label %land.end, !dbg !3658

land.rhs:                                         ; preds = %land.lhs.true66
  %53 = load i8*, i8** %scan, align 8, !dbg !3659
  %54 = load i8*, i8** %strend, align 8, !dbg !3660
  %cmp73 = icmp ult i8* %53, %54, !dbg !3661
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true66, %land.lhs.true59, %land.lhs.true52, %land.lhs.true45, %land.lhs.true38, %land.lhs.true31, %land.lhs.true, %do.cond
  %55 = phi i1 [ false, %land.lhs.true66 ], [ false, %land.lhs.true59 ], [ false, %land.lhs.true52 ], [ false, %land.lhs.true45 ], [ false, %land.lhs.true38 ], [ false, %land.lhs.true31 ], [ false, %land.lhs.true ], [ false, %do.cond ], [ %cmp73, %land.rhs ]
  br i1 %55, label %do.body, label %do.end, !dbg !3662

do.end:                                           ; preds = %land.end
  %56 = load i8*, i8** %strend, align 8, !dbg !3664
  %57 = load i8*, i8** %scan, align 8, !dbg !3665
  %sub.ptr.lhs.cast = ptrtoint i8* %56 to i64, !dbg !3666
  %sub.ptr.rhs.cast = ptrtoint i8* %57 to i64, !dbg !3666
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !3666
  %conv75 = trunc i64 %sub.ptr.sub to i32, !dbg !3667
  %sub = sub nsw i32 258, %conv75, !dbg !3668
  store i32 %sub, i32* %len, align 4, !dbg !3669
  %58 = load i32, i32* %len, align 4, !dbg !3670
  %cmp76 = icmp slt i32 %58, 3, !dbg !3672
  br i1 %cmp76, label %if.then78, label %if.end79, !dbg !3673

if.then78:                                        ; preds = %do.end
  store i32 2, i32* %retval, align 4, !dbg !3674
  br label %return, !dbg !3674

if.end79:                                         ; preds = %do.end
  %59 = load i32, i32* %cur_match.addr, align 4, !dbg !3676
  %60 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3677
  %match_start = getelementptr inbounds %struct.internal_state, %struct.internal_state* %60, i32 0, i32 28, !dbg !3678
  store i32 %59, i32* %match_start, align 8, !dbg !3679
  %61 = load i32, i32* %len, align 4, !dbg !3680
  %62 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3681
  %lookahead = getelementptr inbounds %struct.internal_state, %struct.internal_state* %62, i32 0, i32 29, !dbg !3682
  %63 = load i32, i32* %lookahead, align 4, !dbg !3682
  %cmp80 = icmp ule i32 %61, %63, !dbg !3683
  br i1 %cmp80, label %cond.true, label %cond.false, !dbg !3684

cond.true:                                        ; preds = %if.end79
  %64 = load i32, i32* %len, align 4, !dbg !3685
  br label %cond.end, !dbg !3686

cond.false:                                       ; preds = %if.end79
  %65 = load %struct.internal_state*, %struct.internal_state** %s.addr, align 8, !dbg !3687
  %lookahead82 = getelementptr inbounds %struct.internal_state, %struct.internal_state* %65, i32 0, i32 29, !dbg !3688
  %66 = load i32, i32* %lookahead82, align 4, !dbg !3688
  br label %cond.end, !dbg !3689

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %64, %cond.true ], [ %66, %cond.false ], !dbg !3690
  store i32 %cond, i32* %retval, align 4, !dbg !3692
  br label %return, !dbg !3692

return:                                           ; preds = %cond.end, %if.then78, %if.then
  %67 = load i32, i32* %retval, align 4, !dbg !3693
  ret i32 %67, !dbg !3693
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!273, !274}
!llvm.ident = !{!275}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !9, subprograms: !188, globals: !249)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/deflate.c", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !1, line: 66, size: 32, align: 32, elements: !4)
!4 = !{!5, !6, !7, !8}
!5 = !DIEnumerator(name: "need_more", value: 0)
!6 = !DIEnumerator(name: "block_done", value: 1)
!7 = !DIEnumerator(name: "finish_started", value: 2)
!8 = !DIEnumerator(name: "finish_done", value: 3)
!9 = !{!10, !15, !20, !24, !51, !36, !95, !178, !173, !62, !48, !38, !107, !97, !98, !17, !18, !19, !186, !56, !110}
!10 = !DIDerivedType(tag: DW_TAG_typedef, name: "alloc_func", file: !11, line: 77, baseType: !12)
!11 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/zlib.h", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64, align: 64)
!13 = !DISubroutineType(types: !14)
!14 = !{!15, !15, !18, !18}
!15 = !DIDerivedType(tag: DW_TAG_typedef, name: "voidpf", file: !16, line: 285, baseType: !17)
!16 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/zconf.h", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!18 = !DIDerivedType(tag: DW_TAG_typedef, name: "uInt", file: !16, line: 269, baseType: !19)
!19 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "free_func", file: !11, line: 78, baseType: !21)
!21 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !22, size: 64, align: 64)
!22 = !DISubroutineType(types: !23)
!23 = !{null, !15, !15}
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !25, size: 64, align: 64)
!25 = !DIDerivedType(tag: DW_TAG_typedef, name: "deflate_state", file: !26, line: 263, baseType: !27)
!26 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/deflate.h", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!27 = !DICompositeType(tag: DW_TAG_structure_type, name: "internal_state", file: !26, line: 94, size: 47424, align: 64, elements: !28)
!28 = !{!29, !59, !60, !61, !64, !65, !66, !67, !86, !87, !88, !89, !90, !91, !92, !93, !94, !100, !101, !102, !103, !104, !105, !106, !108, !109, !111, !112, !113, !114, !115, !116, !117, !118, !119, !120, !121, !122, !138, !142, !146, !159, !160, !161, !165, !167, !168, !169, !172, !175, !176, !177, !180, !181, !182, !183, !184, !185}
!29 = !DIDerivedType(tag: DW_TAG_member, name: "strm", scope: !27, file: !26, line: 95, baseType: !30, size: 64, align: 64)
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "z_streamp", file: !11, line: 103, baseType: !31)
!31 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64, align: 64)
!32 = !DIDerivedType(tag: DW_TAG_typedef, name: "z_stream", file: !11, line: 101, baseType: !33)
!33 = !DICompositeType(tag: DW_TAG_structure_type, name: "z_stream_s", file: !11, line: 82, size: 896, align: 64, elements: !34)
!34 = !{!35, !40, !41, !44, !45, !46, !47, !50, !52, !53, !54, !55, !57, !58}
!35 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !33, file: !11, line: 83, baseType: !36, size: 64, align: 64)
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64, align: 64)
!37 = !DIDerivedType(tag: DW_TAG_typedef, name: "Bytef", file: !16, line: 276, baseType: !38)
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "Byte", file: !16, line: 267, baseType: !39)
!39 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !33, file: !11, line: 84, baseType: !18, size: 32, align: 32, offset: 64)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !33, file: !11, line: 85, baseType: !42, size: 64, align: 64, offset: 128)
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "uLong", file: !16, line: 270, baseType: !43)
!43 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !33, file: !11, line: 87, baseType: !36, size: 64, align: 64, offset: 192)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !33, file: !11, line: 88, baseType: !18, size: 32, align: 32, offset: 256)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !33, file: !11, line: 89, baseType: !42, size: 64, align: 64, offset: 320)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !33, file: !11, line: 91, baseType: !48, size: 64, align: 64, offset: 384)
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64, align: 64)
!49 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !33, file: !11, line: 92, baseType: !51, size: 64, align: 64, offset: 448)
!51 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !27, size: 64, align: 64)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "zalloc", scope: !33, file: !11, line: 94, baseType: !10, size: 64, align: 64, offset: 512)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "zfree", scope: !33, file: !11, line: 95, baseType: !20, size: 64, align: 64, offset: 576)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !33, file: !11, line: 96, baseType: !15, size: 64, align: 64, offset: 640)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "data_type", scope: !33, file: !11, line: 98, baseType: !56, size: 32, align: 32, offset: 704)
!56 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "adler", scope: !33, file: !11, line: 99, baseType: !42, size: 64, align: 64, offset: 768)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !33, file: !11, line: 100, baseType: !42, size: 64, align: 64, offset: 832)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "status", scope: !27, file: !26, line: 96, baseType: !56, size: 32, align: 32, offset: 64)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "pending_buf", scope: !27, file: !26, line: 97, baseType: !36, size: 64, align: 64, offset: 128)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "pending_buf_size", scope: !27, file: !26, line: 98, baseType: !62, size: 64, align: 64, offset: 192)
!62 = !DIDerivedType(tag: DW_TAG_typedef, name: "ulg", file: !63, line: 51, baseType: !43)
!63 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/zutil.h", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!64 = !DIDerivedType(tag: DW_TAG_member, name: "pending_out", scope: !27, file: !26, line: 99, baseType: !36, size: 64, align: 64, offset: 256)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !27, file: !26, line: 100, baseType: !18, size: 32, align: 32, offset: 320)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "wrap", scope: !27, file: !26, line: 101, baseType: !56, size: 32, align: 32, offset: 352)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "gzhead", scope: !27, file: !26, line: 102, baseType: !68, size: 64, align: 64, offset: 384)
!68 = !DIDerivedType(tag: DW_TAG_typedef, name: "gz_headerp", file: !11, line: 126, baseType: !69)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DIDerivedType(tag: DW_TAG_typedef, name: "gz_header", file: !11, line: 124, baseType: !71)
!71 = !DICompositeType(tag: DW_TAG_structure_type, name: "gz_header_s", file: !11, line: 109, size: 640, align: 64, elements: !72)
!72 = !{!73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !85}
!73 = !DIDerivedType(tag: DW_TAG_member, name: "text", scope: !71, file: !11, line: 110, baseType: !56, size: 32, align: 32)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !71, file: !11, line: 111, baseType: !42, size: 64, align: 64, offset: 64)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "xflags", scope: !71, file: !11, line: 112, baseType: !56, size: 32, align: 32, offset: 128)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "os", scope: !71, file: !11, line: 113, baseType: !56, size: 32, align: 32, offset: 160)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "extra", scope: !71, file: !11, line: 114, baseType: !36, size: 64, align: 64, offset: 192)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "extra_len", scope: !71, file: !11, line: 115, baseType: !18, size: 32, align: 32, offset: 256)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "extra_max", scope: !71, file: !11, line: 116, baseType: !18, size: 32, align: 32, offset: 288)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !71, file: !11, line: 117, baseType: !36, size: 64, align: 64, offset: 320)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "name_max", scope: !71, file: !11, line: 118, baseType: !18, size: 32, align: 32, offset: 384)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "comment", scope: !71, file: !11, line: 119, baseType: !36, size: 64, align: 64, offset: 448)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "comm_max", scope: !71, file: !11, line: 120, baseType: !18, size: 32, align: 32, offset: 512)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "hcrc", scope: !71, file: !11, line: 121, baseType: !56, size: 32, align: 32, offset: 544)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !71, file: !11, line: 122, baseType: !56, size: 32, align: 32, offset: 576)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "gzindex", scope: !27, file: !26, line: 103, baseType: !18, size: 32, align: 32, offset: 448)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "method", scope: !27, file: !26, line: 104, baseType: !38, size: 8, align: 8, offset: 480)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "last_flush", scope: !27, file: !26, line: 105, baseType: !56, size: 32, align: 32, offset: 512)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "w_size", scope: !27, file: !26, line: 109, baseType: !18, size: 32, align: 32, offset: 544)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "w_bits", scope: !27, file: !26, line: 110, baseType: !18, size: 32, align: 32, offset: 576)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "w_mask", scope: !27, file: !26, line: 111, baseType: !18, size: 32, align: 32, offset: 608)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "window", scope: !27, file: !26, line: 113, baseType: !36, size: 64, align: 64, offset: 640)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "window_size", scope: !27, file: !26, line: 123, baseType: !62, size: 64, align: 64, offset: 704)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "prev", scope: !27, file: !26, line: 128, baseType: !95, size: 64, align: 64, offset: 768)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !96, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_typedef, name: "Posf", file: !26, line: 87, baseType: !97)
!97 = !DIDerivedType(tag: DW_TAG_typedef, name: "Pos", file: !26, line: 86, baseType: !98)
!98 = !DIDerivedType(tag: DW_TAG_typedef, name: "ush", file: !63, line: 49, baseType: !99)
!99 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "head", scope: !27, file: !26, line: 134, baseType: !95, size: 64, align: 64, offset: 832)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "ins_h", scope: !27, file: !26, line: 136, baseType: !18, size: 32, align: 32, offset: 896)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "hash_size", scope: !27, file: !26, line: 137, baseType: !18, size: 32, align: 32, offset: 928)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "hash_bits", scope: !27, file: !26, line: 138, baseType: !18, size: 32, align: 32, offset: 960)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "hash_mask", scope: !27, file: !26, line: 139, baseType: !18, size: 32, align: 32, offset: 992)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "hash_shift", scope: !27, file: !26, line: 141, baseType: !18, size: 32, align: 32, offset: 1024)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "block_start", scope: !27, file: !26, line: 148, baseType: !107, size: 64, align: 64, offset: 1088)
!107 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "match_length", scope: !27, file: !26, line: 153, baseType: !18, size: 32, align: 32, offset: 1152)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "prev_match", scope: !27, file: !26, line: 154, baseType: !110, size: 32, align: 32, offset: 1184)
!110 = !DIDerivedType(tag: DW_TAG_typedef, name: "IPos", file: !26, line: 88, baseType: !19)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "match_available", scope: !27, file: !26, line: 155, baseType: !56, size: 32, align: 32, offset: 1216)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "strstart", scope: !27, file: !26, line: 156, baseType: !18, size: 32, align: 32, offset: 1248)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "match_start", scope: !27, file: !26, line: 157, baseType: !18, size: 32, align: 32, offset: 1280)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "lookahead", scope: !27, file: !26, line: 158, baseType: !18, size: 32, align: 32, offset: 1312)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "prev_length", scope: !27, file: !26, line: 160, baseType: !18, size: 32, align: 32, offset: 1344)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "max_chain_length", scope: !27, file: !26, line: 165, baseType: !18, size: 32, align: 32, offset: 1376)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "max_lazy_match", scope: !27, file: !26, line: 171, baseType: !18, size: 32, align: 32, offset: 1408)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "level", scope: !27, file: !26, line: 182, baseType: !56, size: 32, align: 32, offset: 1440)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "strategy", scope: !27, file: !26, line: 183, baseType: !56, size: 32, align: 32, offset: 1472)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "good_match", scope: !27, file: !26, line: 185, baseType: !18, size: 32, align: 32, offset: 1504)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "nice_match", scope: !27, file: !26, line: 188, baseType: !56, size: 32, align: 32, offset: 1536)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "dyn_ltree", scope: !27, file: !26, line: 192, baseType: !123, size: 18336, align: 16, offset: 1568)
!123 = !DICompositeType(tag: DW_TAG_array_type, baseType: !124, size: 18336, align: 16, elements: !136)
!124 = !DICompositeType(tag: DW_TAG_structure_type, name: "ct_data_s", file: !26, line: 62, size: 32, align: 16, elements: !125)
!125 = !{!126, !131}
!126 = !DIDerivedType(tag: DW_TAG_member, name: "fc", scope: !124, file: !26, line: 66, baseType: !127, size: 16, align: 16)
!127 = !DICompositeType(tag: DW_TAG_union_type, scope: !124, file: !26, line: 63, size: 16, align: 16, elements: !128)
!128 = !{!129, !130}
!129 = !DIDerivedType(tag: DW_TAG_member, name: "freq", scope: !127, file: !26, line: 64, baseType: !98, size: 16, align: 16)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !127, file: !26, line: 65, baseType: !98, size: 16, align: 16)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "dl", scope: !124, file: !26, line: 70, baseType: !132, size: 16, align: 16, offset: 16)
!132 = !DICompositeType(tag: DW_TAG_union_type, scope: !124, file: !26, line: 67, size: 16, align: 16, elements: !133)
!133 = !{!134, !135}
!134 = !DIDerivedType(tag: DW_TAG_member, name: "dad", scope: !132, file: !26, line: 68, baseType: !98, size: 16, align: 16)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !132, file: !26, line: 69, baseType: !98, size: 16, align: 16)
!136 = !{!137}
!137 = !DISubrange(count: 573)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "dyn_dtree", scope: !27, file: !26, line: 193, baseType: !139, size: 1952, align: 16, offset: 19904)
!139 = !DICompositeType(tag: DW_TAG_array_type, baseType: !124, size: 1952, align: 16, elements: !140)
!140 = !{!141}
!141 = !DISubrange(count: 61)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "bl_tree", scope: !27, file: !26, line: 194, baseType: !143, size: 1248, align: 16, offset: 21856)
!143 = !DICompositeType(tag: DW_TAG_array_type, baseType: !124, size: 1248, align: 16, elements: !144)
!144 = !{!145}
!145 = !DISubrange(count: 39)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "l_desc", scope: !27, file: !26, line: 196, baseType: !147, size: 192, align: 64, offset: 23104)
!147 = !DICompositeType(tag: DW_TAG_structure_type, name: "tree_desc_s", file: !26, line: 80, size: 192, align: 64, elements: !148)
!148 = !{!149, !152, !153}
!149 = !DIDerivedType(tag: DW_TAG_member, name: "dyn_tree", scope: !147, file: !26, line: 81, baseType: !150, size: 64, align: 64)
!150 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !151, size: 64, align: 64)
!151 = !DIDerivedType(tag: DW_TAG_typedef, name: "ct_data", file: !26, line: 71, baseType: !124)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "max_code", scope: !147, file: !26, line: 82, baseType: !56, size: 32, align: 32, offset: 64)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "stat_desc", scope: !147, file: !26, line: 83, baseType: !154, size: 64, align: 64, offset: 128)
!154 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !155, size: 64, align: 64)
!155 = !DIDerivedType(tag: DW_TAG_typedef, name: "static_tree_desc", file: !26, line: 78, baseType: !156)
!156 = !DICompositeType(tag: DW_TAG_structure_type, name: "static_tree_desc_s", file: !1, line: 161, size: 32, align: 32, elements: !157)
!157 = !{!158}
!158 = !DIDerivedType(tag: DW_TAG_member, name: "dummy", scope: !156, file: !1, line: 161, baseType: !56, size: 32, align: 32)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "d_desc", scope: !27, file: !26, line: 197, baseType: !147, size: 192, align: 64, offset: 23296)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "bl_desc", scope: !27, file: !26, line: 198, baseType: !147, size: 192, align: 64, offset: 23488)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "bl_count", scope: !27, file: !26, line: 200, baseType: !162, size: 256, align: 16, offset: 23680)
!162 = !DICompositeType(tag: DW_TAG_array_type, baseType: !98, size: 256, align: 16, elements: !163)
!163 = !{!164}
!164 = !DISubrange(count: 16)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "heap", scope: !27, file: !26, line: 203, baseType: !166, size: 18336, align: 32, offset: 23936)
!166 = !DICompositeType(tag: DW_TAG_array_type, baseType: !56, size: 18336, align: 32, elements: !136)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "heap_len", scope: !27, file: !26, line: 204, baseType: !56, size: 32, align: 32, offset: 42272)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "heap_max", scope: !27, file: !26, line: 205, baseType: !56, size: 32, align: 32, offset: 42304)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !27, file: !26, line: 210, baseType: !170, size: 4584, align: 8, offset: 42336)
!170 = !DICompositeType(tag: DW_TAG_array_type, baseType: !171, size: 4584, align: 8, elements: !136)
!171 = !DIDerivedType(tag: DW_TAG_typedef, name: "uch", file: !63, line: 47, baseType: !39)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "l_buf", scope: !27, file: !26, line: 214, baseType: !173, size: 64, align: 64, offset: 46976)
!173 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !174, size: 64, align: 64)
!174 = !DIDerivedType(tag: DW_TAG_typedef, name: "uchf", file: !63, line: 48, baseType: !171)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "lit_bufsize", scope: !27, file: !26, line: 216, baseType: !18, size: 32, align: 32, offset: 47040)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "last_lit", scope: !27, file: !26, line: 236, baseType: !18, size: 32, align: 32, offset: 47072)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "d_buf", scope: !27, file: !26, line: 238, baseType: !178, size: 64, align: 64, offset: 47104)
!178 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !179, size: 64, align: 64)
!179 = !DIDerivedType(tag: DW_TAG_typedef, name: "ushf", file: !63, line: 50, baseType: !98)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "opt_len", scope: !27, file: !26, line: 244, baseType: !62, size: 64, align: 64, offset: 47168)
!181 = !DIDerivedType(tag: DW_TAG_member, name: "static_len", scope: !27, file: !26, line: 245, baseType: !62, size: 64, align: 64, offset: 47232)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "matches", scope: !27, file: !26, line: 246, baseType: !18, size: 32, align: 32, offset: 47296)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "last_eob_len", scope: !27, file: !26, line: 247, baseType: !56, size: 32, align: 32, offset: 47328)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "bi_buf", scope: !27, file: !26, line: 254, baseType: !98, size: 16, align: 16, offset: 47360)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "bi_valid", scope: !27, file: !26, line: 258, baseType: !56, size: 32, align: 32, offset: 47392)
!186 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !187, size: 64, align: 64)
!187 = !DIDerivedType(tag: DW_TAG_typedef, name: "charf", file: !16, line: 278, baseType: !49)
!188 = !{!189, !195, !198, !203, !206, !209, !212, !213, !216, !219, !222, !223, !226, !230, !233, !236, !237, !240, !241, !242, !245, !248}
!189 = distinct !DISubprogram(name: "cm_zlib_deflateInit_", scope: !1, file: !1, line: 204, type: !190, isLocal: false, isDefinition: true, scopeLine: 209, isOptimized: false, variables: !194)
!190 = !DISubroutineType(types: !191)
!191 = !{!56, !30, !56, !192, !56}
!192 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !193, size: 64, align: 64)
!193 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !49)
!194 = !{}
!195 = distinct !DISubprogram(name: "cm_zlib_deflateInit2_", scope: !1, file: !1, line: 216, type: !196, isLocal: false, isDefinition: true, scopeLine: 226, isOptimized: false, variables: !194)
!196 = !DISubroutineType(types: !197)
!197 = !{!56, !30, !56, !56, !56, !56, !56, !192, !56}
!198 = distinct !DISubprogram(name: "cm_zlib_deflateSetDictionary", scope: !1, file: !1, line: 322, type: !199, isLocal: false, isDefinition: true, scopeLine: 326, isOptimized: false, variables: !194)
!199 = !DISubroutineType(types: !200)
!200 = !{!56, !30, !201, !18}
!201 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !202, size: 64, align: 64)
!202 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !37)
!203 = distinct !DISubprogram(name: "cm_zlib_deflateReset", scope: !1, file: !1, line: 364, type: !204, isLocal: false, isDefinition: true, scopeLine: 366, isOptimized: false, variables: !194)
!204 = !DISubroutineType(types: !205)
!205 = !{!56, !30}
!206 = distinct !DISubprogram(name: "cm_zlib_deflateSetHeader", scope: !1, file: !1, line: 400, type: !207, isLocal: false, isDefinition: true, scopeLine: 403, isOptimized: false, variables: !194)
!207 = !DISubroutineType(types: !208)
!208 = !{!56, !30, !68}
!209 = distinct !DISubprogram(name: "cm_zlib_deflatePrime", scope: !1, file: !1, line: 411, type: !210, isLocal: false, isDefinition: true, scopeLine: 415, isOptimized: false, variables: !194)
!210 = !DISubroutineType(types: !211)
!211 = !{!56, !30, !56, !56}
!212 = distinct !DISubprogram(name: "cm_zlib_deflateParams", scope: !1, file: !1, line: 423, type: !210, isLocal: false, isDefinition: true, scopeLine: 427, isOptimized: false, variables: !194)
!213 = distinct !DISubprogram(name: "cm_zlib_deflateTune", scope: !1, file: !1, line: 461, type: !214, isLocal: false, isDefinition: true, scopeLine: 467, isOptimized: false, variables: !194)
!214 = !DISubroutineType(types: !215)
!215 = !{!56, !30, !56, !56, !56, !56}
!216 = distinct !DISubprogram(name: "cm_zlib_deflateBound", scope: !1, file: !1, line: 496, type: !217, isLocal: false, isDefinition: true, scopeLine: 499, isOptimized: false, variables: !194)
!217 = !DISubroutineType(types: !218)
!218 = !{!42, !30, !42}
!219 = distinct !DISubprogram(name: "cm_zlib_deflate", scope: !1, file: !1, line: 559, type: !220, isLocal: false, isDefinition: true, scopeLine: 562, isOptimized: false, variables: !194)
!220 = !DISubroutineType(types: !221)
!221 = !{!56, !30, !56}
!222 = distinct !DISubprogram(name: "cm_zlib_deflateEnd", scope: !1, file: !1, line: 866, type: !204, isLocal: false, isDefinition: true, scopeLine: 868, isOptimized: false, variables: !194)
!223 = distinct !DISubprogram(name: "cm_zlib_deflateCopy", scope: !1, file: !1, line: 901, type: !224, isLocal: false, isDefinition: true, scopeLine: 904, isOptimized: false, variables: !194)
!224 = !DISubroutineType(types: !225)
!225 = !{!56, !30, !30}
!226 = distinct !DISubprogram(name: "deflate_stored", scope: !1, file: !1, line: 1397, type: !227, isLocal: true, isDefinition: true, scopeLine: 1400, isOptimized: false, variables: !194)
!227 = !DISubroutineType(types: !228)
!228 = !{!229, !24, !56}
!229 = !DIDerivedType(tag: DW_TAG_typedef, name: "block_state", file: !1, line: 71, baseType: !3)
!230 = distinct !DISubprogram(name: "fill_window", scope: !1, file: !1, line: 1273, type: !231, isLocal: true, isDefinition: true, scopeLine: 1275, isOptimized: false, variables: !194)
!231 = !DISubroutineType(types: !232)
!232 = !{null, !24}
!233 = distinct !DISubprogram(name: "read_buf", scope: !1, file: !1, line: 963, type: !234, isLocal: true, isDefinition: true, scopeLine: 967, isOptimized: false, variables: !194)
!234 = !DISubroutineType(types: !235)
!235 = !{!56, !30, !36, !19}
!236 = distinct !DISubprogram(name: "deflate_fast", scope: !1, file: !1, line: 1455, type: !227, isLocal: true, isDefinition: true, scopeLine: 1458, isOptimized: false, variables: !194)
!237 = distinct !DISubprogram(name: "longest_match", scope: !1, file: !1, line: 1034, type: !238, isLocal: true, isDefinition: true, scopeLine: 1037, isOptimized: false, variables: !194)
!238 = !DISubroutineType(types: !239)
!239 = !{!18, !24, !110}
!240 = distinct !DISubprogram(name: "longest_match_fast", scope: !1, file: !1, line: 1182, type: !238, isLocal: true, isDefinition: true, scopeLine: 1185, isOptimized: false, variables: !194)
!241 = distinct !DISubprogram(name: "deflate_slow", scope: !1, file: !1, line: 1561, type: !227, isLocal: true, isDefinition: true, scopeLine: 1564, isOptimized: false, variables: !194)
!242 = distinct !DISubprogram(name: "putShortMSB", scope: !1, file: !1, line: 525, type: !243, isLocal: true, isDefinition: true, scopeLine: 528, isOptimized: false, variables: !194)
!243 = !DISubroutineType(types: !244)
!244 = !{null, !24, !18}
!245 = distinct !DISubprogram(name: "flush_pending", scope: !1, file: !1, line: 539, type: !246, isLocal: true, isDefinition: true, scopeLine: 541, isOptimized: false, variables: !194)
!246 = !DISubroutineType(types: !247)
!247 = !{null, !30}
!248 = distinct !DISubprogram(name: "lm_init", scope: !1, file: !1, line: 993, type: !231, isLocal: true, isDefinition: true, scopeLine: 995, isOptimized: false, variables: !194)
!249 = !{!250, !254, !258}
!250 = !DIGlobalVariable(name: "cm_zlib_deflate_copyright", scope: !0, file: !1, line: 54, type: !251, isLocal: false, isDefinition: true, variable: [53 x i8]* @cm_zlib_deflate_copyright)
!251 = !DICompositeType(tag: DW_TAG_array_type, baseType: !193, size: 424, align: 8, elements: !252)
!252 = !{!253}
!253 = !DISubrange(count: 53)
!254 = !DIGlobalVariable(name: "my_version", scope: !195, file: !1, line: 229, type: !255, isLocal: true, isDefinition: true, variable: [6 x i8]* @cm_zlib_deflateInit2_.my_version)
!255 = !DICompositeType(tag: DW_TAG_array_type, baseType: !193, size: 48, align: 8, elements: !256)
!256 = !{!257}
!257 = !DISubrange(count: 6)
!258 = !DIGlobalVariable(name: "configuration_table", scope: !0, file: !1, line: 137, type: !259, isLocal: true, isDefinition: true, variable: [10 x %struct.config_s]* @configuration_table)
!259 = !DICompositeType(tag: DW_TAG_array_type, baseType: !260, size: 1280, align: 64, elements: !271)
!260 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !261)
!261 = !DIDerivedType(tag: DW_TAG_typedef, name: "config", file: !1, line: 129, baseType: !262)
!262 = !DICompositeType(tag: DW_TAG_structure_type, name: "config_s", file: !1, line: 123, size: 128, align: 64, elements: !263)
!263 = !{!264, !265, !266, !267, !268}
!264 = !DIDerivedType(tag: DW_TAG_member, name: "good_length", scope: !262, file: !1, line: 124, baseType: !98, size: 16, align: 16)
!265 = !DIDerivedType(tag: DW_TAG_member, name: "max_lazy", scope: !262, file: !1, line: 125, baseType: !98, size: 16, align: 16, offset: 16)
!266 = !DIDerivedType(tag: DW_TAG_member, name: "nice_length", scope: !262, file: !1, line: 126, baseType: !98, size: 16, align: 16, offset: 32)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "max_chain", scope: !262, file: !1, line: 127, baseType: !98, size: 16, align: 16, offset: 48)
!268 = !DIDerivedType(tag: DW_TAG_member, name: "func", scope: !262, file: !1, line: 128, baseType: !269, size: 64, align: 64, offset: 64)
!269 = !DIDerivedType(tag: DW_TAG_typedef, name: "compress_func", file: !1, line: 73, baseType: !270)
!270 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !227, size: 64, align: 64)
!271 = !{!272}
!272 = !DISubrange(count: 10)
!273 = !{i32 2, !"Dwarf Version", i32 4}
!274 = !{i32 2, !"Debug Info Version", i32 3}
!275 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!276 = !DILocalVariable(name: "strm", arg: 1, scope: !189, file: !1, line: 205, type: !30)
!277 = !DIExpression()
!278 = !DILocation(line: 205, column: 15, scope: !189)
!279 = !DILocalVariable(name: "level", arg: 2, scope: !189, file: !1, line: 206, type: !56)
!280 = !DILocation(line: 206, column: 9, scope: !189)
!281 = !DILocalVariable(name: "version", arg: 3, scope: !189, file: !1, line: 207, type: !192)
!282 = !DILocation(line: 207, column: 17, scope: !189)
!283 = !DILocalVariable(name: "stream_size", arg: 4, scope: !189, file: !1, line: 208, type: !56)
!284 = !DILocation(line: 208, column: 9, scope: !189)
!285 = !DILocation(line: 210, column: 26, scope: !189)
!286 = !DILocation(line: 210, column: 32, scope: !189)
!287 = !DILocation(line: 211, column: 46, scope: !189)
!288 = !DILocation(line: 211, column: 55, scope: !189)
!289 = !DILocation(line: 210, column: 12, scope: !189)
!290 = !DILocation(line: 210, column: 5, scope: !189)
!291 = !DILocalVariable(name: "strm", arg: 1, scope: !195, file: !1, line: 218, type: !30)
!292 = !DILocation(line: 218, column: 15, scope: !195)
!293 = !DILocalVariable(name: "level", arg: 2, scope: !195, file: !1, line: 219, type: !56)
!294 = !DILocation(line: 219, column: 10, scope: !195)
!295 = !DILocalVariable(name: "method", arg: 3, scope: !195, file: !1, line: 220, type: !56)
!296 = !DILocation(line: 220, column: 10, scope: !195)
!297 = !DILocalVariable(name: "windowBits", arg: 4, scope: !195, file: !1, line: 221, type: !56)
!298 = !DILocation(line: 221, column: 10, scope: !195)
!299 = !DILocalVariable(name: "memLevel", arg: 5, scope: !195, file: !1, line: 222, type: !56)
!300 = !DILocation(line: 222, column: 10, scope: !195)
!301 = !DILocalVariable(name: "strategy", arg: 6, scope: !195, file: !1, line: 223, type: !56)
!302 = !DILocation(line: 223, column: 10, scope: !195)
!303 = !DILocalVariable(name: "version", arg: 7, scope: !195, file: !1, line: 224, type: !192)
!304 = !DILocation(line: 224, column: 17, scope: !195)
!305 = !DILocalVariable(name: "stream_size", arg: 8, scope: !195, file: !1, line: 225, type: !56)
!306 = !DILocation(line: 225, column: 9, scope: !195)
!307 = !DILocalVariable(name: "s", scope: !195, file: !1, line: 227, type: !24)
!308 = !DILocation(line: 227, column: 20, scope: !195)
!309 = !DILocalVariable(name: "wrap", scope: !195, file: !1, line: 228, type: !56)
!310 = !DILocation(line: 228, column: 9, scope: !195)
!311 = !DILocalVariable(name: "overlay", scope: !195, file: !1, line: 231, type: !178)
!312 = !DILocation(line: 231, column: 11, scope: !195)
!313 = !DILocation(line: 236, column: 9, scope: !314)
!314 = distinct !DILexicalBlock(scope: !195, file: !1, line: 236, column: 9)
!315 = !DILocation(line: 236, column: 17, scope: !314)
!316 = !DILocation(line: 236, column: 27, scope: !314)
!317 = !DILocation(line: 236, column: 30, scope: !318)
!318 = !DILexicalBlockFile(scope: !314, file: !1, discriminator: 1)
!319 = !DILocation(line: 236, column: 44, scope: !318)
!320 = !DILocation(line: 236, column: 41, scope: !318)
!321 = !DILocation(line: 236, column: 58, scope: !318)
!322 = !DILocation(line: 237, column: 9, scope: !314)
!323 = !DILocation(line: 237, column: 21, scope: !314)
!324 = !DILocation(line: 236, column: 9, scope: !325)
!325 = !DILexicalBlockFile(scope: !195, file: !1, discriminator: 2)
!326 = !DILocation(line: 238, column: 9, scope: !327)
!327 = distinct !DILexicalBlock(scope: !314, file: !1, line: 237, column: 42)
!328 = !DILocation(line: 240, column: 9, scope: !329)
!329 = distinct !DILexicalBlock(scope: !195, file: !1, line: 240, column: 9)
!330 = !DILocation(line: 240, column: 14, scope: !329)
!331 = !DILocation(line: 240, column: 9, scope: !195)
!332 = !DILocation(line: 240, column: 25, scope: !333)
!333 = !DILexicalBlockFile(scope: !329, file: !1, discriminator: 1)
!334 = !DILocation(line: 242, column: 5, scope: !195)
!335 = !DILocation(line: 242, column: 11, scope: !195)
!336 = !DILocation(line: 242, column: 15, scope: !195)
!337 = !DILocation(line: 243, column: 9, scope: !338)
!338 = distinct !DILexicalBlock(scope: !195, file: !1, line: 243, column: 9)
!339 = !DILocation(line: 243, column: 15, scope: !338)
!340 = !DILocation(line: 243, column: 22, scope: !338)
!341 = !DILocation(line: 243, column: 9, scope: !195)
!342 = !DILocation(line: 244, column: 9, scope: !343)
!343 = distinct !DILexicalBlock(scope: !338, file: !1, line: 243, column: 40)
!344 = !DILocation(line: 244, column: 15, scope: !343)
!345 = !DILocation(line: 244, column: 22, scope: !343)
!346 = !DILocation(line: 245, column: 9, scope: !343)
!347 = !DILocation(line: 245, column: 15, scope: !343)
!348 = !DILocation(line: 245, column: 22, scope: !343)
!349 = !DILocation(line: 246, column: 5, scope: !343)
!350 = !DILocation(line: 247, column: 9, scope: !351)
!351 = distinct !DILexicalBlock(scope: !195, file: !1, line: 247, column: 9)
!352 = !DILocation(line: 247, column: 15, scope: !351)
!353 = !DILocation(line: 247, column: 21, scope: !351)
!354 = !DILocation(line: 247, column: 9, scope: !195)
!355 = !DILocation(line: 247, column: 38, scope: !356)
!356 = !DILexicalBlockFile(scope: !351, file: !1, discriminator: 1)
!357 = !DILocation(line: 247, column: 44, scope: !356)
!358 = !DILocation(line: 247, column: 50, scope: !356)
!359 = !DILocation(line: 252, column: 9, scope: !360)
!360 = distinct !DILexicalBlock(scope: !195, file: !1, line: 252, column: 9)
!361 = !DILocation(line: 252, column: 15, scope: !360)
!362 = !DILocation(line: 252, column: 9, scope: !195)
!363 = !DILocation(line: 252, column: 47, scope: !364)
!364 = !DILexicalBlockFile(scope: !360, file: !1, discriminator: 1)
!365 = !DILocation(line: 252, column: 41, scope: !364)
!366 = !DILocation(line: 255, column: 9, scope: !367)
!367 = distinct !DILexicalBlock(scope: !195, file: !1, line: 255, column: 9)
!368 = !DILocation(line: 255, column: 20, scope: !367)
!369 = !DILocation(line: 255, column: 9, scope: !195)
!370 = !DILocation(line: 256, column: 14, scope: !371)
!371 = distinct !DILexicalBlock(scope: !367, file: !1, line: 255, column: 25)
!372 = !DILocation(line: 257, column: 23, scope: !371)
!373 = !DILocation(line: 257, column: 22, scope: !371)
!374 = !DILocation(line: 257, column: 20, scope: !371)
!375 = !DILocation(line: 258, column: 5, scope: !371)
!376 = !DILocation(line: 260, column: 14, scope: !377)
!377 = distinct !DILexicalBlock(scope: !367, file: !1, line: 260, column: 14)
!378 = !DILocation(line: 260, column: 25, scope: !377)
!379 = !DILocation(line: 260, column: 14, scope: !367)
!380 = !DILocation(line: 261, column: 14, scope: !381)
!381 = distinct !DILexicalBlock(scope: !377, file: !1, line: 260, column: 31)
!382 = !DILocation(line: 262, column: 20, scope: !381)
!383 = !DILocation(line: 263, column: 5, scope: !381)
!384 = !DILocation(line: 265, column: 9, scope: !385)
!385 = distinct !DILexicalBlock(scope: !195, file: !1, line: 265, column: 9)
!386 = !DILocation(line: 265, column: 18, scope: !385)
!387 = !DILocation(line: 265, column: 22, scope: !385)
!388 = !DILocation(line: 265, column: 25, scope: !389)
!389 = !DILexicalBlockFile(scope: !385, file: !1, discriminator: 1)
!390 = !DILocation(line: 265, column: 34, scope: !389)
!391 = !DILocation(line: 265, column: 50, scope: !389)
!392 = !DILocation(line: 265, column: 53, scope: !393)
!393 = !DILexicalBlockFile(scope: !385, file: !1, discriminator: 2)
!394 = !DILocation(line: 265, column: 60, scope: !393)
!395 = !DILocation(line: 265, column: 74, scope: !393)
!396 = !DILocation(line: 266, column: 9, scope: !385)
!397 = !DILocation(line: 266, column: 20, scope: !385)
!398 = !DILocation(line: 266, column: 24, scope: !385)
!399 = !DILocation(line: 266, column: 27, scope: !389)
!400 = !DILocation(line: 266, column: 38, scope: !389)
!401 = !DILocation(line: 266, column: 43, scope: !389)
!402 = !DILocation(line: 266, column: 46, scope: !393)
!403 = !DILocation(line: 266, column: 52, scope: !393)
!404 = !DILocation(line: 266, column: 56, scope: !393)
!405 = !DILocation(line: 266, column: 59, scope: !406)
!406 = !DILexicalBlockFile(scope: !385, file: !1, discriminator: 3)
!407 = !DILocation(line: 266, column: 65, scope: !406)
!408 = !DILocation(line: 266, column: 69, scope: !406)
!409 = !DILocation(line: 267, column: 9, scope: !385)
!410 = !DILocation(line: 267, column: 18, scope: !385)
!411 = !DILocation(line: 267, column: 22, scope: !385)
!412 = !DILocation(line: 267, column: 25, scope: !389)
!413 = !DILocation(line: 267, column: 34, scope: !389)
!414 = !DILocation(line: 265, column: 9, scope: !415)
!415 = !DILexicalBlockFile(scope: !195, file: !1, discriminator: 3)
!416 = !DILocation(line: 268, column: 9, scope: !417)
!417 = distinct !DILexicalBlock(scope: !385, file: !1, line: 267, column: 45)
!418 = !DILocation(line: 270, column: 9, scope: !419)
!419 = distinct !DILexicalBlock(scope: !195, file: !1, line: 270, column: 9)
!420 = !DILocation(line: 270, column: 20, scope: !419)
!421 = !DILocation(line: 270, column: 9, scope: !195)
!422 = !DILocation(line: 270, column: 37, scope: !423)
!423 = !DILexicalBlockFile(scope: !419, file: !1, discriminator: 1)
!424 = !DILocation(line: 270, column: 26, scope: !423)
!425 = !DILocation(line: 271, column: 27, scope: !195)
!426 = !DILocation(line: 271, column: 9, scope: !195)
!427 = !DILocation(line: 271, column: 7, scope: !195)
!428 = !DILocation(line: 272, column: 9, scope: !429)
!429 = distinct !DILexicalBlock(scope: !195, file: !1, line: 272, column: 9)
!430 = !DILocation(line: 272, column: 11, scope: !429)
!431 = !DILocation(line: 272, column: 9, scope: !195)
!432 = !DILocation(line: 272, column: 22, scope: !433)
!433 = !DILexicalBlockFile(scope: !429, file: !1, discriminator: 1)
!434 = !DILocation(line: 273, column: 48, scope: !195)
!435 = !DILocation(line: 273, column: 5, scope: !195)
!436 = !DILocation(line: 273, column: 11, scope: !195)
!437 = !DILocation(line: 273, column: 17, scope: !195)
!438 = !DILocation(line: 274, column: 15, scope: !195)
!439 = !DILocation(line: 274, column: 5, scope: !195)
!440 = !DILocation(line: 274, column: 8, scope: !195)
!441 = !DILocation(line: 274, column: 13, scope: !195)
!442 = !DILocation(line: 276, column: 15, scope: !195)
!443 = !DILocation(line: 276, column: 5, scope: !195)
!444 = !DILocation(line: 276, column: 8, scope: !195)
!445 = !DILocation(line: 276, column: 13, scope: !195)
!446 = !DILocation(line: 277, column: 5, scope: !195)
!447 = !DILocation(line: 277, column: 8, scope: !195)
!448 = !DILocation(line: 277, column: 15, scope: !195)
!449 = !DILocation(line: 278, column: 17, scope: !195)
!450 = !DILocation(line: 278, column: 5, scope: !195)
!451 = !DILocation(line: 278, column: 8, scope: !195)
!452 = !DILocation(line: 278, column: 15, scope: !195)
!453 = !DILocation(line: 279, column: 22, scope: !195)
!454 = !DILocation(line: 279, column: 25, scope: !195)
!455 = !DILocation(line: 279, column: 19, scope: !195)
!456 = !DILocation(line: 279, column: 5, scope: !195)
!457 = !DILocation(line: 279, column: 8, scope: !195)
!458 = !DILocation(line: 279, column: 15, scope: !195)
!459 = !DILocation(line: 280, column: 17, scope: !195)
!460 = !DILocation(line: 280, column: 20, scope: !195)
!461 = !DILocation(line: 280, column: 27, scope: !195)
!462 = !DILocation(line: 280, column: 5, scope: !195)
!463 = !DILocation(line: 280, column: 8, scope: !195)
!464 = !DILocation(line: 280, column: 15, scope: !195)
!465 = !DILocation(line: 282, column: 20, scope: !195)
!466 = !DILocation(line: 282, column: 29, scope: !195)
!467 = !DILocation(line: 282, column: 5, scope: !195)
!468 = !DILocation(line: 282, column: 8, scope: !195)
!469 = !DILocation(line: 282, column: 18, scope: !195)
!470 = !DILocation(line: 283, column: 25, scope: !195)
!471 = !DILocation(line: 283, column: 28, scope: !195)
!472 = !DILocation(line: 283, column: 22, scope: !195)
!473 = !DILocation(line: 283, column: 5, scope: !195)
!474 = !DILocation(line: 283, column: 8, scope: !195)
!475 = !DILocation(line: 283, column: 18, scope: !195)
!476 = !DILocation(line: 284, column: 20, scope: !195)
!477 = !DILocation(line: 284, column: 23, scope: !195)
!478 = !DILocation(line: 284, column: 33, scope: !195)
!479 = !DILocation(line: 284, column: 5, scope: !195)
!480 = !DILocation(line: 284, column: 8, scope: !195)
!481 = !DILocation(line: 284, column: 18, scope: !195)
!482 = !DILocation(line: 285, column: 24, scope: !195)
!483 = !DILocation(line: 285, column: 27, scope: !195)
!484 = !DILocation(line: 285, column: 36, scope: !195)
!485 = !DILocation(line: 285, column: 46, scope: !195)
!486 = !DILocation(line: 285, column: 49, scope: !195)
!487 = !DILocation(line: 285, column: 5, scope: !195)
!488 = !DILocation(line: 285, column: 8, scope: !195)
!489 = !DILocation(line: 285, column: 19, scope: !195)
!490 = !DILocation(line: 287, column: 27, scope: !195)
!491 = !DILocation(line: 287, column: 5, scope: !195)
!492 = !DILocation(line: 287, column: 8, scope: !195)
!493 = !DILocation(line: 287, column: 15, scope: !195)
!494 = !DILocation(line: 293, column: 12, scope: !195)
!495 = !DILocation(line: 293, column: 15, scope: !195)
!496 = !DILocation(line: 293, column: 26, scope: !195)
!497 = !DILocation(line: 293, column: 29, scope: !195)
!498 = !DILocation(line: 293, column: 35, scope: !195)
!499 = !DILocation(line: 293, column: 37, scope: !195)
!500 = !DILocation(line: 293, column: 5, scope: !195)
!501 = !DILocation(line: 295, column: 27, scope: !195)
!502 = !DILocation(line: 295, column: 17, scope: !195)
!503 = !DILocation(line: 295, column: 5, scope: !195)
!504 = !DILocation(line: 295, column: 8, scope: !195)
!505 = !DILocation(line: 295, column: 15, scope: !195)
!506 = !DILocation(line: 296, column: 27, scope: !195)
!507 = !DILocation(line: 296, column: 17, scope: !195)
!508 = !DILocation(line: 296, column: 5, scope: !195)
!509 = !DILocation(line: 296, column: 8, scope: !195)
!510 = !DILocation(line: 296, column: 15, scope: !195)
!511 = !DILocation(line: 298, column: 28, scope: !195)
!512 = !DILocation(line: 298, column: 37, scope: !195)
!513 = !DILocation(line: 298, column: 24, scope: !195)
!514 = !DILocation(line: 298, column: 5, scope: !195)
!515 = !DILocation(line: 298, column: 8, scope: !195)
!516 = !DILocation(line: 298, column: 20, scope: !195)
!517 = !DILocation(line: 300, column: 24, scope: !195)
!518 = !DILocation(line: 300, column: 15, scope: !195)
!519 = !DILocation(line: 300, column: 13, scope: !195)
!520 = !DILocation(line: 301, column: 31, scope: !195)
!521 = !DILocation(line: 301, column: 22, scope: !195)
!522 = !DILocation(line: 301, column: 5, scope: !195)
!523 = !DILocation(line: 301, column: 8, scope: !195)
!524 = !DILocation(line: 301, column: 20, scope: !195)
!525 = !DILocation(line: 302, column: 32, scope: !195)
!526 = !DILocation(line: 302, column: 35, scope: !195)
!527 = !DILocation(line: 302, column: 27, scope: !195)
!528 = !DILocation(line: 302, column: 47, scope: !195)
!529 = !DILocation(line: 302, column: 5, scope: !195)
!530 = !DILocation(line: 302, column: 8, scope: !195)
!531 = !DILocation(line: 302, column: 25, scope: !195)
!532 = !DILocation(line: 304, column: 9, scope: !533)
!533 = distinct !DILexicalBlock(scope: !195, file: !1, line: 304, column: 9)
!534 = !DILocation(line: 304, column: 12, scope: !533)
!535 = !DILocation(line: 304, column: 19, scope: !533)
!536 = !DILocation(line: 304, column: 29, scope: !533)
!537 = !DILocation(line: 304, column: 32, scope: !538)
!538 = !DILexicalBlockFile(scope: !533, file: !1, discriminator: 1)
!539 = !DILocation(line: 304, column: 35, scope: !538)
!540 = !DILocation(line: 304, column: 40, scope: !538)
!541 = !DILocation(line: 304, column: 50, scope: !538)
!542 = !DILocation(line: 304, column: 53, scope: !543)
!543 = !DILexicalBlockFile(scope: !533, file: !1, discriminator: 2)
!544 = !DILocation(line: 304, column: 56, scope: !543)
!545 = !DILocation(line: 304, column: 61, scope: !543)
!546 = !DILocation(line: 304, column: 71, scope: !543)
!547 = !DILocation(line: 305, column: 9, scope: !533)
!548 = !DILocation(line: 305, column: 12, scope: !533)
!549 = !DILocation(line: 305, column: 24, scope: !533)
!550 = !DILocation(line: 304, column: 9, scope: !415)
!551 = !DILocation(line: 306, column: 9, scope: !552)
!552 = distinct !DILexicalBlock(scope: !533, file: !1, line: 305, column: 35)
!553 = !DILocation(line: 306, column: 12, scope: !552)
!554 = !DILocation(line: 306, column: 19, scope: !552)
!555 = !DILocation(line: 307, column: 28, scope: !552)
!556 = !DILocation(line: 307, column: 9, scope: !552)
!557 = !DILocation(line: 307, column: 15, scope: !552)
!558 = !DILocation(line: 307, column: 19, scope: !552)
!559 = !DILocation(line: 308, column: 21, scope: !552)
!560 = !DILocation(line: 308, column: 9, scope: !552)
!561 = !DILocation(line: 309, column: 9, scope: !552)
!562 = !DILocation(line: 311, column: 16, scope: !195)
!563 = !DILocation(line: 311, column: 26, scope: !195)
!564 = !DILocation(line: 311, column: 29, scope: !195)
!565 = !DILocation(line: 311, column: 40, scope: !195)
!566 = !DILocation(line: 311, column: 24, scope: !195)
!567 = !DILocation(line: 311, column: 5, scope: !195)
!568 = !DILocation(line: 311, column: 8, scope: !195)
!569 = !DILocation(line: 311, column: 14, scope: !195)
!570 = !DILocation(line: 312, column: 16, scope: !195)
!571 = !DILocation(line: 312, column: 19, scope: !195)
!572 = !DILocation(line: 312, column: 49, scope: !195)
!573 = !DILocation(line: 312, column: 52, scope: !195)
!574 = !DILocation(line: 312, column: 48, scope: !195)
!575 = !DILocation(line: 312, column: 31, scope: !195)
!576 = !DILocation(line: 312, column: 5, scope: !195)
!577 = !DILocation(line: 312, column: 8, scope: !195)
!578 = !DILocation(line: 312, column: 14, scope: !195)
!579 = !DILocation(line: 314, column: 16, scope: !195)
!580 = !DILocation(line: 314, column: 5, scope: !195)
!581 = !DILocation(line: 314, column: 8, scope: !195)
!582 = !DILocation(line: 314, column: 14, scope: !195)
!583 = !DILocation(line: 315, column: 19, scope: !195)
!584 = !DILocation(line: 315, column: 5, scope: !195)
!585 = !DILocation(line: 315, column: 8, scope: !195)
!586 = !DILocation(line: 315, column: 17, scope: !195)
!587 = !DILocation(line: 316, column: 23, scope: !195)
!588 = !DILocation(line: 316, column: 17, scope: !195)
!589 = !DILocation(line: 316, column: 5, scope: !195)
!590 = !DILocation(line: 316, column: 8, scope: !195)
!591 = !DILocation(line: 316, column: 15, scope: !195)
!592 = !DILocation(line: 318, column: 25, scope: !195)
!593 = !DILocation(line: 318, column: 12, scope: !195)
!594 = !DILocation(line: 318, column: 5, scope: !195)
!595 = !DILocation(line: 319, column: 1, scope: !195)
!596 = !DILocalVariable(name: "strm", arg: 1, scope: !222, file: !1, line: 867, type: !30)
!597 = !DILocation(line: 867, column: 15, scope: !222)
!598 = !DILocalVariable(name: "status", scope: !222, file: !1, line: 869, type: !56)
!599 = !DILocation(line: 869, column: 9, scope: !222)
!600 = !DILocation(line: 871, column: 9, scope: !601)
!601 = distinct !DILexicalBlock(scope: !222, file: !1, line: 871, column: 9)
!602 = !DILocation(line: 871, column: 14, scope: !601)
!603 = !DILocation(line: 871, column: 24, scope: !601)
!604 = !DILocation(line: 871, column: 27, scope: !605)
!605 = !DILexicalBlockFile(scope: !601, file: !1, discriminator: 1)
!606 = !DILocation(line: 871, column: 33, scope: !605)
!607 = !DILocation(line: 871, column: 39, scope: !605)
!608 = !DILocation(line: 871, column: 9, scope: !605)
!609 = !DILocation(line: 871, column: 50, scope: !610)
!610 = !DILexicalBlockFile(scope: !601, file: !1, discriminator: 2)
!611 = !DILocation(line: 873, column: 14, scope: !222)
!612 = !DILocation(line: 873, column: 20, scope: !222)
!613 = !DILocation(line: 873, column: 27, scope: !222)
!614 = !DILocation(line: 873, column: 12, scope: !222)
!615 = !DILocation(line: 874, column: 9, scope: !616)
!616 = distinct !DILexicalBlock(scope: !222, file: !1, line: 874, column: 9)
!617 = !DILocation(line: 874, column: 16, scope: !616)
!618 = !DILocation(line: 874, column: 30, scope: !616)
!619 = !DILocation(line: 875, column: 9, scope: !616)
!620 = !DILocation(line: 875, column: 16, scope: !616)
!621 = !DILocation(line: 875, column: 31, scope: !616)
!622 = !DILocation(line: 876, column: 9, scope: !616)
!623 = !DILocation(line: 876, column: 16, scope: !616)
!624 = !DILocation(line: 876, column: 30, scope: !616)
!625 = !DILocation(line: 877, column: 9, scope: !616)
!626 = !DILocation(line: 877, column: 16, scope: !616)
!627 = !DILocation(line: 877, column: 33, scope: !616)
!628 = !DILocation(line: 878, column: 9, scope: !616)
!629 = !DILocation(line: 878, column: 16, scope: !616)
!630 = !DILocation(line: 878, column: 30, scope: !616)
!631 = !DILocation(line: 879, column: 9, scope: !616)
!632 = !DILocation(line: 879, column: 16, scope: !616)
!633 = !DILocation(line: 879, column: 30, scope: !616)
!634 = !DILocation(line: 880, column: 9, scope: !616)
!635 = !DILocation(line: 880, column: 16, scope: !616)
!636 = !DILocation(line: 874, column: 9, scope: !637)
!637 = !DILexicalBlockFile(scope: !222, file: !1, discriminator: 1)
!638 = !DILocation(line: 881, column: 7, scope: !639)
!639 = distinct !DILexicalBlock(scope: !616, file: !1, line: 880, column: 33)
!640 = !DILocation(line: 885, column: 5, scope: !641)
!641 = distinct !DILexicalBlock(scope: !642, file: !1, line: 885, column: 5)
!642 = distinct !DILexicalBlock(scope: !222, file: !1, line: 885, column: 5)
!643 = !DILocation(line: 885, column: 5, scope: !642)
!644 = !DILocation(line: 885, column: 5, scope: !645)
!645 = !DILexicalBlockFile(scope: !641, file: !1, discriminator: 1)
!646 = !DILocation(line: 886, column: 5, scope: !647)
!647 = distinct !DILexicalBlock(scope: !648, file: !1, line: 886, column: 5)
!648 = distinct !DILexicalBlock(scope: !222, file: !1, line: 886, column: 5)
!649 = !DILocation(line: 886, column: 5, scope: !648)
!650 = !DILocation(line: 886, column: 5, scope: !651)
!651 = !DILexicalBlockFile(scope: !647, file: !1, discriminator: 1)
!652 = !DILocation(line: 887, column: 5, scope: !653)
!653 = distinct !DILexicalBlock(scope: !654, file: !1, line: 887, column: 5)
!654 = distinct !DILexicalBlock(scope: !222, file: !1, line: 887, column: 5)
!655 = !DILocation(line: 887, column: 5, scope: !654)
!656 = !DILocation(line: 887, column: 5, scope: !657)
!657 = !DILexicalBlockFile(scope: !653, file: !1, discriminator: 1)
!658 = !DILocation(line: 888, column: 5, scope: !659)
!659 = distinct !DILexicalBlock(scope: !660, file: !1, line: 888, column: 5)
!660 = distinct !DILexicalBlock(scope: !222, file: !1, line: 888, column: 5)
!661 = !DILocation(line: 888, column: 5, scope: !660)
!662 = !DILocation(line: 888, column: 5, scope: !663)
!663 = !DILexicalBlockFile(scope: !659, file: !1, discriminator: 1)
!664 = !DILocation(line: 890, column: 5, scope: !222)
!665 = !DILocation(line: 891, column: 5, scope: !222)
!666 = !DILocation(line: 891, column: 11, scope: !222)
!667 = !DILocation(line: 891, column: 17, scope: !222)
!668 = !DILocation(line: 893, column: 12, scope: !222)
!669 = !DILocation(line: 893, column: 19, scope: !222)
!670 = !DILocation(line: 893, column: 5, scope: !222)
!671 = !DILocation(line: 894, column: 1, scope: !222)
!672 = !DILocalVariable(name: "strm", arg: 1, scope: !203, file: !1, line: 365, type: !30)
!673 = !DILocation(line: 365, column: 15, scope: !203)
!674 = !DILocalVariable(name: "s", scope: !203, file: !1, line: 367, type: !24)
!675 = !DILocation(line: 367, column: 20, scope: !203)
!676 = !DILocation(line: 369, column: 9, scope: !677)
!677 = distinct !DILexicalBlock(scope: !203, file: !1, line: 369, column: 9)
!678 = !DILocation(line: 369, column: 14, scope: !677)
!679 = !DILocation(line: 369, column: 24, scope: !677)
!680 = !DILocation(line: 369, column: 27, scope: !681)
!681 = !DILexicalBlockFile(scope: !677, file: !1, discriminator: 1)
!682 = !DILocation(line: 369, column: 33, scope: !681)
!683 = !DILocation(line: 369, column: 39, scope: !681)
!684 = !DILocation(line: 369, column: 49, scope: !681)
!685 = !DILocation(line: 370, column: 9, scope: !677)
!686 = !DILocation(line: 370, column: 15, scope: !677)
!687 = !DILocation(line: 370, column: 22, scope: !677)
!688 = !DILocation(line: 370, column: 39, scope: !677)
!689 = !DILocation(line: 370, column: 42, scope: !681)
!690 = !DILocation(line: 370, column: 48, scope: !681)
!691 = !DILocation(line: 370, column: 54, scope: !681)
!692 = !DILocation(line: 369, column: 9, scope: !693)
!693 = !DILexicalBlockFile(scope: !203, file: !1, discriminator: 2)
!694 = !DILocation(line: 371, column: 9, scope: !695)
!695 = distinct !DILexicalBlock(scope: !677, file: !1, line: 370, column: 71)
!696 = !DILocation(line: 374, column: 22, scope: !203)
!697 = !DILocation(line: 374, column: 28, scope: !203)
!698 = !DILocation(line: 374, column: 38, scope: !203)
!699 = !DILocation(line: 374, column: 5, scope: !203)
!700 = !DILocation(line: 374, column: 11, scope: !203)
!701 = !DILocation(line: 374, column: 20, scope: !203)
!702 = !DILocation(line: 375, column: 5, scope: !203)
!703 = !DILocation(line: 375, column: 11, scope: !203)
!704 = !DILocation(line: 375, column: 15, scope: !203)
!705 = !DILocation(line: 376, column: 5, scope: !203)
!706 = !DILocation(line: 376, column: 11, scope: !203)
!707 = !DILocation(line: 376, column: 21, scope: !203)
!708 = !DILocation(line: 378, column: 26, scope: !203)
!709 = !DILocation(line: 378, column: 32, scope: !203)
!710 = !DILocation(line: 378, column: 7, scope: !203)
!711 = !DILocation(line: 379, column: 5, scope: !203)
!712 = !DILocation(line: 379, column: 8, scope: !203)
!713 = !DILocation(line: 379, column: 16, scope: !203)
!714 = !DILocation(line: 380, column: 22, scope: !203)
!715 = !DILocation(line: 380, column: 25, scope: !203)
!716 = !DILocation(line: 380, column: 5, scope: !203)
!717 = !DILocation(line: 380, column: 8, scope: !203)
!718 = !DILocation(line: 380, column: 20, scope: !203)
!719 = !DILocation(line: 382, column: 9, scope: !720)
!720 = distinct !DILexicalBlock(scope: !203, file: !1, line: 382, column: 9)
!721 = !DILocation(line: 382, column: 12, scope: !720)
!722 = !DILocation(line: 382, column: 17, scope: !720)
!723 = !DILocation(line: 382, column: 9, scope: !203)
!724 = !DILocation(line: 383, column: 20, scope: !725)
!725 = distinct !DILexicalBlock(scope: !720, file: !1, line: 382, column: 22)
!726 = !DILocation(line: 383, column: 23, scope: !725)
!727 = !DILocation(line: 383, column: 19, scope: !725)
!728 = !DILocation(line: 383, column: 9, scope: !725)
!729 = !DILocation(line: 383, column: 12, scope: !725)
!730 = !DILocation(line: 383, column: 17, scope: !725)
!731 = !DILocation(line: 384, column: 5, scope: !725)
!732 = !DILocation(line: 385, column: 17, scope: !203)
!733 = !DILocation(line: 385, column: 20, scope: !203)
!734 = !DILocation(line: 385, column: 5, scope: !203)
!735 = !DILocation(line: 385, column: 8, scope: !203)
!736 = !DILocation(line: 385, column: 15, scope: !203)
!737 = !DILocation(line: 388, column: 9, scope: !203)
!738 = !DILocation(line: 388, column: 12, scope: !203)
!739 = !DILocation(line: 388, column: 17, scope: !203)
!740 = !DILocation(line: 388, column: 24, scope: !741)
!741 = !DILexicalBlockFile(scope: !203, file: !1, discriminator: 1)
!742 = !DILocation(line: 388, column: 9, scope: !741)
!743 = !DILocation(line: 390, column: 9, scope: !203)
!744 = !DILocation(line: 388, column: 9, scope: !693)
!745 = !DILocation(line: 388, column: 9, scope: !746)
!746 = !DILexicalBlockFile(scope: !203, file: !1, discriminator: 3)
!747 = !DILocation(line: 386, column: 5, scope: !203)
!748 = !DILocation(line: 386, column: 11, scope: !203)
!749 = !DILocation(line: 386, column: 17, scope: !203)
!750 = !DILocation(line: 391, column: 5, scope: !203)
!751 = !DILocation(line: 391, column: 8, scope: !203)
!752 = !DILocation(line: 391, column: 19, scope: !203)
!753 = !DILocation(line: 393, column: 14, scope: !203)
!754 = !DILocation(line: 393, column: 5, scope: !203)
!755 = !DILocation(line: 394, column: 13, scope: !203)
!756 = !DILocation(line: 394, column: 5, scope: !203)
!757 = !DILocation(line: 396, column: 5, scope: !203)
!758 = !DILocation(line: 397, column: 1, scope: !203)
!759 = !DILocalVariable(name: "strm", arg: 1, scope: !198, file: !1, line: 323, type: !30)
!760 = !DILocation(line: 323, column: 15, scope: !198)
!761 = !DILocalVariable(name: "dictionary", arg: 2, scope: !198, file: !1, line: 324, type: !201)
!762 = !DILocation(line: 324, column: 18, scope: !198)
!763 = !DILocalVariable(name: "dictLength", arg: 3, scope: !198, file: !1, line: 325, type: !18)
!764 = !DILocation(line: 325, column: 11, scope: !198)
!765 = !DILocalVariable(name: "s", scope: !198, file: !1, line: 327, type: !24)
!766 = !DILocation(line: 327, column: 20, scope: !198)
!767 = !DILocalVariable(name: "length", scope: !198, file: !1, line: 328, type: !18)
!768 = !DILocation(line: 328, column: 10, scope: !198)
!769 = !DILocation(line: 328, column: 19, scope: !198)
!770 = !DILocalVariable(name: "n", scope: !198, file: !1, line: 329, type: !18)
!771 = !DILocation(line: 329, column: 10, scope: !198)
!772 = !DILocalVariable(name: "hash_head", scope: !198, file: !1, line: 330, type: !110)
!773 = !DILocation(line: 330, column: 10, scope: !198)
!774 = !DILocation(line: 332, column: 9, scope: !775)
!775 = distinct !DILexicalBlock(scope: !198, file: !1, line: 332, column: 9)
!776 = !DILocation(line: 332, column: 14, scope: !775)
!777 = !DILocation(line: 332, column: 24, scope: !775)
!778 = !DILocation(line: 332, column: 27, scope: !779)
!779 = !DILexicalBlockFile(scope: !775, file: !1, discriminator: 1)
!780 = !DILocation(line: 332, column: 33, scope: !779)
!781 = !DILocation(line: 332, column: 39, scope: !779)
!782 = !DILocation(line: 332, column: 49, scope: !779)
!783 = !DILocation(line: 332, column: 52, scope: !784)
!784 = !DILexicalBlockFile(scope: !775, file: !1, discriminator: 2)
!785 = !DILocation(line: 332, column: 63, scope: !784)
!786 = !DILocation(line: 332, column: 73, scope: !784)
!787 = !DILocation(line: 333, column: 9, scope: !775)
!788 = !DILocation(line: 333, column: 15, scope: !775)
!789 = !DILocation(line: 333, column: 22, scope: !775)
!790 = !DILocation(line: 333, column: 27, scope: !775)
!791 = !DILocation(line: 333, column: 32, scope: !775)
!792 = !DILocation(line: 334, column: 10, scope: !775)
!793 = !DILocation(line: 334, column: 16, scope: !775)
!794 = !DILocation(line: 334, column: 23, scope: !775)
!795 = !DILocation(line: 334, column: 28, scope: !775)
!796 = !DILocation(line: 334, column: 33, scope: !775)
!797 = !DILocation(line: 334, column: 36, scope: !779)
!798 = !DILocation(line: 334, column: 42, scope: !779)
!799 = !DILocation(line: 334, column: 49, scope: !779)
!800 = !DILocation(line: 334, column: 56, scope: !779)
!801 = !DILocation(line: 332, column: 9, scope: !802)
!802 = !DILexicalBlockFile(scope: !198, file: !1, discriminator: 3)
!803 = !DILocation(line: 335, column: 9, scope: !775)
!804 = !DILocation(line: 337, column: 9, scope: !198)
!805 = !DILocation(line: 337, column: 15, scope: !198)
!806 = !DILocation(line: 337, column: 7, scope: !198)
!807 = !DILocation(line: 338, column: 9, scope: !808)
!808 = distinct !DILexicalBlock(scope: !198, file: !1, line: 338, column: 9)
!809 = !DILocation(line: 338, column: 12, scope: !808)
!810 = !DILocation(line: 338, column: 9, scope: !198)
!811 = !DILocation(line: 339, column: 31, scope: !808)
!812 = !DILocation(line: 339, column: 37, scope: !808)
!813 = !DILocation(line: 339, column: 44, scope: !808)
!814 = !DILocation(line: 339, column: 56, scope: !808)
!815 = !DILocation(line: 339, column: 23, scope: !808)
!816 = !DILocation(line: 339, column: 9, scope: !808)
!817 = !DILocation(line: 339, column: 15, scope: !808)
!818 = !DILocation(line: 339, column: 21, scope: !808)
!819 = !DILocation(line: 341, column: 9, scope: !820)
!820 = distinct !DILexicalBlock(scope: !198, file: !1, line: 341, column: 9)
!821 = !DILocation(line: 341, column: 16, scope: !820)
!822 = !DILocation(line: 341, column: 9, scope: !198)
!823 = !DILocation(line: 341, column: 29, scope: !824)
!824 = !DILexicalBlockFile(scope: !820, file: !1, discriminator: 1)
!825 = !DILocation(line: 342, column: 9, scope: !826)
!826 = distinct !DILexicalBlock(scope: !198, file: !1, line: 342, column: 9)
!827 = !DILocation(line: 342, column: 18, scope: !826)
!828 = !DILocation(line: 342, column: 16, scope: !826)
!829 = !DILocation(line: 342, column: 9, scope: !198)
!830 = !DILocation(line: 343, column: 18, scope: !831)
!831 = distinct !DILexicalBlock(scope: !826, file: !1, line: 342, column: 31)
!832 = !DILocation(line: 343, column: 16, scope: !831)
!833 = !DILocation(line: 344, column: 23, scope: !831)
!834 = !DILocation(line: 344, column: 36, scope: !831)
!835 = !DILocation(line: 344, column: 34, scope: !831)
!836 = !DILocation(line: 344, column: 20, scope: !831)
!837 = !DILocation(line: 345, column: 5, scope: !831)
!838 = !DILocation(line: 346, column: 13, scope: !198)
!839 = !DILocation(line: 346, column: 16, scope: !198)
!840 = !DILocation(line: 346, column: 24, scope: !198)
!841 = !DILocation(line: 346, column: 36, scope: !198)
!842 = !DILocation(line: 346, column: 5, scope: !198)
!843 = !DILocation(line: 347, column: 19, scope: !198)
!844 = !DILocation(line: 347, column: 5, scope: !198)
!845 = !DILocation(line: 347, column: 8, scope: !198)
!846 = !DILocation(line: 347, column: 17, scope: !198)
!847 = !DILocation(line: 348, column: 28, scope: !198)
!848 = !DILocation(line: 348, column: 22, scope: !198)
!849 = !DILocation(line: 348, column: 5, scope: !198)
!850 = !DILocation(line: 348, column: 8, scope: !198)
!851 = !DILocation(line: 348, column: 20, scope: !198)
!852 = !DILocation(line: 354, column: 16, scope: !198)
!853 = !DILocation(line: 354, column: 19, scope: !198)
!854 = !DILocation(line: 354, column: 5, scope: !198)
!855 = !DILocation(line: 354, column: 8, scope: !198)
!856 = !DILocation(line: 354, column: 14, scope: !198)
!857 = !DILocation(line: 355, column: 5, scope: !198)
!858 = !DILocation(line: 356, column: 12, scope: !859)
!859 = distinct !DILexicalBlock(scope: !198, file: !1, line: 356, column: 5)
!860 = !DILocation(line: 356, column: 10, scope: !859)
!861 = !DILocation(line: 356, column: 17, scope: !862)
!862 = !DILexicalBlockFile(scope: !863, file: !1, discriminator: 1)
!863 = distinct !DILexicalBlock(scope: !859, file: !1, line: 356, column: 5)
!864 = !DILocation(line: 356, column: 22, scope: !862)
!865 = !DILocation(line: 356, column: 29, scope: !862)
!866 = !DILocation(line: 356, column: 19, scope: !862)
!867 = !DILocation(line: 356, column: 5, scope: !862)
!868 = !DILocation(line: 357, column: 9, scope: !869)
!869 = distinct !DILexicalBlock(scope: !863, file: !1, line: 356, column: 47)
!870 = !DILocation(line: 358, column: 5, scope: !869)
!871 = !DILocation(line: 356, column: 43, scope: !872)
!872 = !DILexicalBlockFile(scope: !863, file: !1, discriminator: 2)
!873 = !DILocation(line: 356, column: 5, scope: !872)
!874 = !DILocation(line: 359, column: 9, scope: !875)
!875 = distinct !DILexicalBlock(scope: !198, file: !1, line: 359, column: 9)
!876 = !DILocation(line: 359, column: 9, scope: !198)
!877 = !DILocation(line: 359, column: 30, scope: !878)
!878 = !DILexicalBlockFile(scope: !875, file: !1, discriminator: 1)
!879 = !DILocation(line: 359, column: 20, scope: !878)
!880 = !DILocation(line: 360, column: 5, scope: !198)
!881 = !DILocation(line: 361, column: 1, scope: !198)
!882 = !DILocalVariable(name: "s", arg: 1, scope: !248, file: !1, line: 994, type: !24)
!883 = !DILocation(line: 994, column: 20, scope: !248)
!884 = !DILocation(line: 996, column: 30, scope: !248)
!885 = !DILocation(line: 996, column: 33, scope: !248)
!886 = !DILocation(line: 996, column: 29, scope: !248)
!887 = !DILocation(line: 996, column: 5, scope: !248)
!888 = !DILocation(line: 996, column: 8, scope: !248)
!889 = !DILocation(line: 996, column: 20, scope: !248)
!890 = !DILocation(line: 998, column: 5, scope: !248)
!891 = !DILocation(line: 1002, column: 47, scope: !248)
!892 = !DILocation(line: 1002, column: 50, scope: !248)
!893 = !DILocation(line: 1002, column: 27, scope: !248)
!894 = !DILocation(line: 1002, column: 57, scope: !248)
!895 = !DILocation(line: 1002, column: 5, scope: !248)
!896 = !DILocation(line: 1002, column: 8, scope: !248)
!897 = !DILocation(line: 1002, column: 25, scope: !248)
!898 = !DILocation(line: 1003, column: 47, scope: !248)
!899 = !DILocation(line: 1003, column: 50, scope: !248)
!900 = !DILocation(line: 1003, column: 27, scope: !248)
!901 = !DILocation(line: 1003, column: 57, scope: !248)
!902 = !DILocation(line: 1003, column: 5, scope: !248)
!903 = !DILocation(line: 1003, column: 8, scope: !248)
!904 = !DILocation(line: 1003, column: 25, scope: !248)
!905 = !DILocation(line: 1004, column: 47, scope: !248)
!906 = !DILocation(line: 1004, column: 50, scope: !248)
!907 = !DILocation(line: 1004, column: 27, scope: !248)
!908 = !DILocation(line: 1004, column: 57, scope: !248)
!909 = !DILocation(line: 1004, column: 5, scope: !248)
!910 = !DILocation(line: 1004, column: 8, scope: !248)
!911 = !DILocation(line: 1004, column: 25, scope: !248)
!912 = !DILocation(line: 1005, column: 47, scope: !248)
!913 = !DILocation(line: 1005, column: 50, scope: !248)
!914 = !DILocation(line: 1005, column: 27, scope: !248)
!915 = !DILocation(line: 1005, column: 57, scope: !248)
!916 = !DILocation(line: 1005, column: 5, scope: !248)
!917 = !DILocation(line: 1005, column: 8, scope: !248)
!918 = !DILocation(line: 1005, column: 25, scope: !248)
!919 = !DILocation(line: 1007, column: 5, scope: !248)
!920 = !DILocation(line: 1007, column: 8, scope: !248)
!921 = !DILocation(line: 1007, column: 17, scope: !248)
!922 = !DILocation(line: 1008, column: 5, scope: !248)
!923 = !DILocation(line: 1008, column: 8, scope: !248)
!924 = !DILocation(line: 1008, column: 20, scope: !248)
!925 = !DILocation(line: 1009, column: 5, scope: !248)
!926 = !DILocation(line: 1009, column: 8, scope: !248)
!927 = !DILocation(line: 1009, column: 18, scope: !248)
!928 = !DILocation(line: 1010, column: 23, scope: !248)
!929 = !DILocation(line: 1010, column: 26, scope: !248)
!930 = !DILocation(line: 1010, column: 38, scope: !248)
!931 = !DILocation(line: 1010, column: 5, scope: !248)
!932 = !DILocation(line: 1010, column: 8, scope: !248)
!933 = !DILocation(line: 1010, column: 21, scope: !248)
!934 = !DILocation(line: 1011, column: 5, scope: !248)
!935 = !DILocation(line: 1011, column: 8, scope: !248)
!936 = !DILocation(line: 1011, column: 24, scope: !248)
!937 = !DILocation(line: 1012, column: 5, scope: !248)
!938 = !DILocation(line: 1012, column: 8, scope: !248)
!939 = !DILocation(line: 1012, column: 14, scope: !248)
!940 = !DILocation(line: 1018, column: 1, scope: !248)
!941 = !DILocalVariable(name: "strm", arg: 1, scope: !206, file: !1, line: 401, type: !30)
!942 = !DILocation(line: 401, column: 15, scope: !206)
!943 = !DILocalVariable(name: "head", arg: 2, scope: !206, file: !1, line: 402, type: !68)
!944 = !DILocation(line: 402, column: 16, scope: !206)
!945 = !DILocation(line: 404, column: 9, scope: !946)
!946 = distinct !DILexicalBlock(scope: !206, file: !1, line: 404, column: 9)
!947 = !DILocation(line: 404, column: 14, scope: !946)
!948 = !DILocation(line: 404, column: 24, scope: !946)
!949 = !DILocation(line: 404, column: 27, scope: !950)
!950 = !DILexicalBlockFile(scope: !946, file: !1, discriminator: 1)
!951 = !DILocation(line: 404, column: 33, scope: !950)
!952 = !DILocation(line: 404, column: 39, scope: !950)
!953 = !DILocation(line: 404, column: 9, scope: !950)
!954 = !DILocation(line: 404, column: 50, scope: !955)
!955 = !DILexicalBlockFile(scope: !946, file: !1, discriminator: 2)
!956 = !DILocation(line: 405, column: 9, scope: !957)
!957 = distinct !DILexicalBlock(scope: !206, file: !1, line: 405, column: 9)
!958 = !DILocation(line: 405, column: 15, scope: !957)
!959 = !DILocation(line: 405, column: 22, scope: !957)
!960 = !DILocation(line: 405, column: 27, scope: !957)
!961 = !DILocation(line: 405, column: 9, scope: !206)
!962 = !DILocation(line: 405, column: 33, scope: !963)
!963 = !DILexicalBlockFile(scope: !957, file: !1, discriminator: 1)
!964 = !DILocation(line: 406, column: 27, scope: !206)
!965 = !DILocation(line: 406, column: 5, scope: !206)
!966 = !DILocation(line: 406, column: 11, scope: !206)
!967 = !DILocation(line: 406, column: 18, scope: !206)
!968 = !DILocation(line: 406, column: 25, scope: !206)
!969 = !DILocation(line: 407, column: 5, scope: !206)
!970 = !DILocation(line: 408, column: 1, scope: !206)
!971 = !DILocalVariable(name: "strm", arg: 1, scope: !209, file: !1, line: 412, type: !30)
!972 = !DILocation(line: 412, column: 15, scope: !209)
!973 = !DILocalVariable(name: "bits", arg: 2, scope: !209, file: !1, line: 413, type: !56)
!974 = !DILocation(line: 413, column: 9, scope: !209)
!975 = !DILocalVariable(name: "value", arg: 3, scope: !209, file: !1, line: 414, type: !56)
!976 = !DILocation(line: 414, column: 9, scope: !209)
!977 = !DILocation(line: 416, column: 9, scope: !978)
!978 = distinct !DILexicalBlock(scope: !209, file: !1, line: 416, column: 9)
!979 = !DILocation(line: 416, column: 14, scope: !978)
!980 = !DILocation(line: 416, column: 24, scope: !978)
!981 = !DILocation(line: 416, column: 27, scope: !982)
!982 = !DILexicalBlockFile(scope: !978, file: !1, discriminator: 1)
!983 = !DILocation(line: 416, column: 33, scope: !982)
!984 = !DILocation(line: 416, column: 39, scope: !982)
!985 = !DILocation(line: 416, column: 9, scope: !982)
!986 = !DILocation(line: 416, column: 50, scope: !987)
!987 = !DILexicalBlockFile(scope: !978, file: !1, discriminator: 2)
!988 = !DILocation(line: 417, column: 29, scope: !209)
!989 = !DILocation(line: 417, column: 5, scope: !209)
!990 = !DILocation(line: 417, column: 11, scope: !209)
!991 = !DILocation(line: 417, column: 18, scope: !209)
!992 = !DILocation(line: 417, column: 27, scope: !209)
!993 = !DILocation(line: 418, column: 33, scope: !209)
!994 = !DILocation(line: 418, column: 48, scope: !209)
!995 = !DILocation(line: 418, column: 45, scope: !209)
!996 = !DILocation(line: 418, column: 54, scope: !209)
!997 = !DILocation(line: 418, column: 39, scope: !209)
!998 = !DILocation(line: 418, column: 27, scope: !209)
!999 = !DILocation(line: 418, column: 5, scope: !209)
!1000 = !DILocation(line: 418, column: 11, scope: !209)
!1001 = !DILocation(line: 418, column: 18, scope: !209)
!1002 = !DILocation(line: 418, column: 25, scope: !209)
!1003 = !DILocation(line: 419, column: 5, scope: !209)
!1004 = !DILocation(line: 420, column: 1, scope: !209)
!1005 = !DILocalVariable(name: "strm", arg: 1, scope: !212, file: !1, line: 424, type: !30)
!1006 = !DILocation(line: 424, column: 15, scope: !212)
!1007 = !DILocalVariable(name: "level", arg: 2, scope: !212, file: !1, line: 425, type: !56)
!1008 = !DILocation(line: 425, column: 9, scope: !212)
!1009 = !DILocalVariable(name: "strategy", arg: 3, scope: !212, file: !1, line: 426, type: !56)
!1010 = !DILocation(line: 426, column: 9, scope: !212)
!1011 = !DILocalVariable(name: "s", scope: !212, file: !1, line: 428, type: !24)
!1012 = !DILocation(line: 428, column: 20, scope: !212)
!1013 = !DILocalVariable(name: "func", scope: !212, file: !1, line: 429, type: !269)
!1014 = !DILocation(line: 429, column: 19, scope: !212)
!1015 = !DILocalVariable(name: "err", scope: !212, file: !1, line: 430, type: !56)
!1016 = !DILocation(line: 430, column: 9, scope: !212)
!1017 = !DILocation(line: 432, column: 9, scope: !1018)
!1018 = distinct !DILexicalBlock(scope: !212, file: !1, line: 432, column: 9)
!1019 = !DILocation(line: 432, column: 14, scope: !1018)
!1020 = !DILocation(line: 432, column: 24, scope: !1018)
!1021 = !DILocation(line: 432, column: 27, scope: !1022)
!1022 = !DILexicalBlockFile(scope: !1018, file: !1, discriminator: 1)
!1023 = !DILocation(line: 432, column: 33, scope: !1022)
!1024 = !DILocation(line: 432, column: 39, scope: !1022)
!1025 = !DILocation(line: 432, column: 9, scope: !1022)
!1026 = !DILocation(line: 432, column: 50, scope: !1027)
!1027 = !DILexicalBlockFile(scope: !1018, file: !1, discriminator: 2)
!1028 = !DILocation(line: 433, column: 9, scope: !212)
!1029 = !DILocation(line: 433, column: 15, scope: !212)
!1030 = !DILocation(line: 433, column: 7, scope: !212)
!1031 = !DILocation(line: 438, column: 9, scope: !1032)
!1032 = distinct !DILexicalBlock(scope: !212, file: !1, line: 438, column: 9)
!1033 = !DILocation(line: 438, column: 15, scope: !1032)
!1034 = !DILocation(line: 438, column: 9, scope: !212)
!1035 = !DILocation(line: 438, column: 47, scope: !1036)
!1036 = !DILexicalBlockFile(scope: !1032, file: !1, discriminator: 1)
!1037 = !DILocation(line: 438, column: 41, scope: !1036)
!1038 = !DILocation(line: 440, column: 9, scope: !1039)
!1039 = distinct !DILexicalBlock(scope: !212, file: !1, line: 440, column: 9)
!1040 = !DILocation(line: 440, column: 15, scope: !1039)
!1041 = !DILocation(line: 440, column: 19, scope: !1039)
!1042 = !DILocation(line: 440, column: 22, scope: !1043)
!1043 = !DILexicalBlockFile(scope: !1039, file: !1, discriminator: 1)
!1044 = !DILocation(line: 440, column: 28, scope: !1043)
!1045 = !DILocation(line: 440, column: 32, scope: !1043)
!1046 = !DILocation(line: 440, column: 35, scope: !1047)
!1047 = !DILexicalBlockFile(scope: !1039, file: !1, discriminator: 2)
!1048 = !DILocation(line: 440, column: 44, scope: !1047)
!1049 = !DILocation(line: 440, column: 48, scope: !1047)
!1050 = !DILocation(line: 440, column: 51, scope: !1051)
!1051 = !DILexicalBlockFile(scope: !1039, file: !1, discriminator: 3)
!1052 = !DILocation(line: 440, column: 60, scope: !1051)
!1053 = !DILocation(line: 440, column: 9, scope: !1051)
!1054 = !DILocation(line: 441, column: 9, scope: !1055)
!1055 = distinct !DILexicalBlock(scope: !1039, file: !1, line: 440, column: 71)
!1056 = !DILocation(line: 443, column: 32, scope: !212)
!1057 = !DILocation(line: 443, column: 35, scope: !212)
!1058 = !DILocation(line: 443, column: 12, scope: !212)
!1059 = !DILocation(line: 443, column: 42, scope: !212)
!1060 = !DILocation(line: 443, column: 10, scope: !212)
!1061 = !DILocation(line: 445, column: 9, scope: !1062)
!1062 = distinct !DILexicalBlock(scope: !212, file: !1, line: 445, column: 9)
!1063 = !DILocation(line: 445, column: 37, scope: !1062)
!1064 = !DILocation(line: 445, column: 17, scope: !1062)
!1065 = !DILocation(line: 445, column: 44, scope: !1062)
!1066 = !DILocation(line: 445, column: 14, scope: !1062)
!1067 = !DILocation(line: 445, column: 49, scope: !1062)
!1068 = !DILocation(line: 445, column: 52, scope: !1069)
!1069 = !DILexicalBlockFile(scope: !1062, file: !1, discriminator: 1)
!1070 = !DILocation(line: 445, column: 58, scope: !1069)
!1071 = !DILocation(line: 445, column: 67, scope: !1069)
!1072 = !DILocation(line: 445, column: 9, scope: !1069)
!1073 = !DILocation(line: 447, column: 23, scope: !1074)
!1074 = distinct !DILexicalBlock(scope: !1062, file: !1, line: 445, column: 73)
!1075 = !DILocation(line: 447, column: 15, scope: !1074)
!1076 = !DILocation(line: 447, column: 13, scope: !1074)
!1077 = !DILocation(line: 448, column: 5, scope: !1074)
!1078 = !DILocation(line: 449, column: 9, scope: !1079)
!1079 = distinct !DILexicalBlock(scope: !212, file: !1, line: 449, column: 9)
!1080 = !DILocation(line: 449, column: 12, scope: !1079)
!1081 = !DILocation(line: 449, column: 21, scope: !1079)
!1082 = !DILocation(line: 449, column: 18, scope: !1079)
!1083 = !DILocation(line: 449, column: 9, scope: !212)
!1084 = !DILocation(line: 450, column: 20, scope: !1085)
!1085 = distinct !DILexicalBlock(scope: !1079, file: !1, line: 449, column: 28)
!1086 = !DILocation(line: 450, column: 9, scope: !1085)
!1087 = !DILocation(line: 450, column: 12, scope: !1085)
!1088 = !DILocation(line: 450, column: 18, scope: !1085)
!1089 = !DILocation(line: 451, column: 51, scope: !1085)
!1090 = !DILocation(line: 451, column: 31, scope: !1085)
!1091 = !DILocation(line: 451, column: 58, scope: !1085)
!1092 = !DILocation(line: 451, column: 9, scope: !1085)
!1093 = !DILocation(line: 451, column: 12, scope: !1085)
!1094 = !DILocation(line: 451, column: 29, scope: !1085)
!1095 = !DILocation(line: 452, column: 51, scope: !1085)
!1096 = !DILocation(line: 452, column: 31, scope: !1085)
!1097 = !DILocation(line: 452, column: 58, scope: !1085)
!1098 = !DILocation(line: 452, column: 9, scope: !1085)
!1099 = !DILocation(line: 452, column: 12, scope: !1085)
!1100 = !DILocation(line: 452, column: 29, scope: !1085)
!1101 = !DILocation(line: 453, column: 51, scope: !1085)
!1102 = !DILocation(line: 453, column: 31, scope: !1085)
!1103 = !DILocation(line: 453, column: 58, scope: !1085)
!1104 = !DILocation(line: 453, column: 9, scope: !1085)
!1105 = !DILocation(line: 453, column: 12, scope: !1085)
!1106 = !DILocation(line: 453, column: 29, scope: !1085)
!1107 = !DILocation(line: 454, column: 51, scope: !1085)
!1108 = !DILocation(line: 454, column: 31, scope: !1085)
!1109 = !DILocation(line: 454, column: 58, scope: !1085)
!1110 = !DILocation(line: 454, column: 9, scope: !1085)
!1111 = !DILocation(line: 454, column: 12, scope: !1085)
!1112 = !DILocation(line: 454, column: 29, scope: !1085)
!1113 = !DILocation(line: 455, column: 5, scope: !1085)
!1114 = !DILocation(line: 456, column: 19, scope: !212)
!1115 = !DILocation(line: 456, column: 5, scope: !212)
!1116 = !DILocation(line: 456, column: 8, scope: !212)
!1117 = !DILocation(line: 456, column: 17, scope: !212)
!1118 = !DILocation(line: 457, column: 12, scope: !212)
!1119 = !DILocation(line: 457, column: 5, scope: !212)
!1120 = !DILocation(line: 458, column: 1, scope: !212)
!1121 = !DILocalVariable(name: "strm", arg: 1, scope: !219, file: !1, line: 560, type: !30)
!1122 = !DILocation(line: 560, column: 15, scope: !219)
!1123 = !DILocalVariable(name: "flush", arg: 2, scope: !219, file: !1, line: 561, type: !56)
!1124 = !DILocation(line: 561, column: 9, scope: !219)
!1125 = !DILocalVariable(name: "old_flush", scope: !219, file: !1, line: 563, type: !56)
!1126 = !DILocation(line: 563, column: 9, scope: !219)
!1127 = !DILocalVariable(name: "s", scope: !219, file: !1, line: 564, type: !24)
!1128 = !DILocation(line: 564, column: 20, scope: !219)
!1129 = !DILocation(line: 566, column: 9, scope: !1130)
!1130 = distinct !DILexicalBlock(scope: !219, file: !1, line: 566, column: 9)
!1131 = !DILocation(line: 566, column: 14, scope: !1130)
!1132 = !DILocation(line: 566, column: 24, scope: !1130)
!1133 = !DILocation(line: 566, column: 27, scope: !1134)
!1134 = !DILexicalBlockFile(scope: !1130, file: !1, discriminator: 1)
!1135 = !DILocation(line: 566, column: 33, scope: !1134)
!1136 = !DILocation(line: 566, column: 39, scope: !1134)
!1137 = !DILocation(line: 566, column: 49, scope: !1134)
!1138 = !DILocation(line: 567, column: 9, scope: !1130)
!1139 = !DILocation(line: 567, column: 15, scope: !1130)
!1140 = !DILocation(line: 567, column: 26, scope: !1130)
!1141 = !DILocation(line: 567, column: 29, scope: !1134)
!1142 = !DILocation(line: 567, column: 35, scope: !1134)
!1143 = !DILocation(line: 566, column: 9, scope: !1144)
!1144 = !DILexicalBlockFile(scope: !219, file: !1, discriminator: 2)
!1145 = !DILocation(line: 568, column: 9, scope: !1146)
!1146 = distinct !DILexicalBlock(scope: !1130, file: !1, line: 567, column: 40)
!1147 = !DILocation(line: 570, column: 9, scope: !219)
!1148 = !DILocation(line: 570, column: 15, scope: !219)
!1149 = !DILocation(line: 570, column: 7, scope: !219)
!1150 = !DILocation(line: 572, column: 9, scope: !1151)
!1151 = distinct !DILexicalBlock(scope: !219, file: !1, line: 572, column: 9)
!1152 = !DILocation(line: 572, column: 15, scope: !1151)
!1153 = !DILocation(line: 572, column: 24, scope: !1151)
!1154 = !DILocation(line: 572, column: 34, scope: !1151)
!1155 = !DILocation(line: 573, column: 10, scope: !1151)
!1156 = !DILocation(line: 573, column: 16, scope: !1151)
!1157 = !DILocation(line: 573, column: 24, scope: !1151)
!1158 = !DILocation(line: 573, column: 34, scope: !1151)
!1159 = !DILocation(line: 573, column: 37, scope: !1160)
!1160 = !DILexicalBlockFile(scope: !1151, file: !1, discriminator: 1)
!1161 = !DILocation(line: 573, column: 43, scope: !1160)
!1162 = !DILocation(line: 573, column: 52, scope: !1160)
!1163 = !DILocation(line: 573, column: 58, scope: !1160)
!1164 = !DILocation(line: 574, column: 10, scope: !1151)
!1165 = !DILocation(line: 574, column: 13, scope: !1151)
!1166 = !DILocation(line: 574, column: 20, scope: !1151)
!1167 = !DILocation(line: 574, column: 36, scope: !1151)
!1168 = !DILocation(line: 574, column: 39, scope: !1160)
!1169 = !DILocation(line: 574, column: 45, scope: !1160)
!1170 = !DILocation(line: 572, column: 9, scope: !1171)
!1171 = !DILexicalBlockFile(scope: !219, file: !1, discriminator: 1)
!1172 = !DILocation(line: 575, column: 9, scope: !1173)
!1173 = distinct !DILexicalBlock(scope: !1151, file: !1, line: 574, column: 59)
!1174 = !DILocation(line: 577, column: 9, scope: !1175)
!1175 = distinct !DILexicalBlock(scope: !219, file: !1, line: 577, column: 9)
!1176 = !DILocation(line: 577, column: 15, scope: !1175)
!1177 = !DILocation(line: 577, column: 25, scope: !1175)
!1178 = !DILocation(line: 577, column: 9, scope: !219)
!1179 = !DILocation(line: 577, column: 31, scope: !1180)
!1180 = !DILexicalBlockFile(scope: !1175, file: !1, discriminator: 1)
!1181 = !DILocation(line: 579, column: 15, scope: !219)
!1182 = !DILocation(line: 579, column: 5, scope: !219)
!1183 = !DILocation(line: 579, column: 8, scope: !219)
!1184 = !DILocation(line: 579, column: 13, scope: !219)
!1185 = !DILocation(line: 580, column: 17, scope: !219)
!1186 = !DILocation(line: 580, column: 20, scope: !219)
!1187 = !DILocation(line: 580, column: 15, scope: !219)
!1188 = !DILocation(line: 581, column: 21, scope: !219)
!1189 = !DILocation(line: 581, column: 5, scope: !219)
!1190 = !DILocation(line: 581, column: 8, scope: !219)
!1191 = !DILocation(line: 581, column: 19, scope: !219)
!1192 = !DILocation(line: 584, column: 9, scope: !1193)
!1193 = distinct !DILexicalBlock(scope: !219, file: !1, line: 584, column: 9)
!1194 = !DILocation(line: 584, column: 12, scope: !1193)
!1195 = !DILocation(line: 584, column: 19, scope: !1193)
!1196 = !DILocation(line: 584, column: 9, scope: !219)
!1197 = !DILocation(line: 586, column: 13, scope: !1198)
!1198 = distinct !DILexicalBlock(scope: !1199, file: !1, line: 586, column: 13)
!1199 = distinct !DILexicalBlock(scope: !1193, file: !1, line: 584, column: 34)
!1200 = !DILocation(line: 586, column: 16, scope: !1198)
!1201 = !DILocation(line: 586, column: 21, scope: !1198)
!1202 = !DILocation(line: 586, column: 13, scope: !1199)
!1203 = !DILocation(line: 587, column: 27, scope: !1204)
!1204 = distinct !DILexicalBlock(scope: !1198, file: !1, line: 586, column: 27)
!1205 = !DILocation(line: 587, column: 13, scope: !1204)
!1206 = !DILocation(line: 587, column: 19, scope: !1204)
!1207 = !DILocation(line: 587, column: 25, scope: !1204)
!1208 = !DILocation(line: 588, column: 13, scope: !1209)
!1209 = distinct !DILexicalBlock(scope: !1204, file: !1, line: 588, column: 13)
!1210 = !DILocation(line: 589, column: 13, scope: !1211)
!1211 = distinct !DILexicalBlock(scope: !1204, file: !1, line: 589, column: 13)
!1212 = !DILocation(line: 590, column: 13, scope: !1213)
!1213 = distinct !DILexicalBlock(scope: !1204, file: !1, line: 590, column: 13)
!1214 = !DILocation(line: 591, column: 17, scope: !1215)
!1215 = distinct !DILexicalBlock(scope: !1204, file: !1, line: 591, column: 17)
!1216 = !DILocation(line: 591, column: 20, scope: !1215)
!1217 = !DILocation(line: 591, column: 27, scope: !1215)
!1218 = !DILocation(line: 591, column: 17, scope: !1204)
!1219 = !DILocation(line: 592, column: 17, scope: !1220)
!1220 = distinct !DILexicalBlock(scope: !1221, file: !1, line: 592, column: 17)
!1221 = distinct !DILexicalBlock(scope: !1215, file: !1, line: 591, column: 36)
!1222 = !DILocation(line: 593, column: 17, scope: !1223)
!1223 = distinct !DILexicalBlock(scope: !1221, file: !1, line: 593, column: 17)
!1224 = !DILocation(line: 594, column: 17, scope: !1225)
!1225 = distinct !DILexicalBlock(scope: !1221, file: !1, line: 594, column: 17)
!1226 = !DILocation(line: 595, column: 17, scope: !1227)
!1227 = distinct !DILexicalBlock(scope: !1221, file: !1, line: 595, column: 17)
!1228 = !DILocation(line: 596, column: 17, scope: !1229)
!1229 = distinct !DILexicalBlock(scope: !1221, file: !1, line: 596, column: 17)
!1230 = !DILocation(line: 597, column: 17, scope: !1231)
!1231 = distinct !DILexicalBlock(scope: !1221, file: !1, line: 597, column: 17)
!1232 = !DILocation(line: 597, column: 17, scope: !1233)
!1233 = !DILexicalBlockFile(scope: !1231, file: !1, discriminator: 1)
!1234 = !DILocation(line: 597, column: 17, scope: !1235)
!1235 = !DILexicalBlockFile(scope: !1231, file: !1, discriminator: 2)
!1236 = !DILocation(line: 597, column: 17, scope: !1237)
!1237 = !DILexicalBlockFile(scope: !1231, file: !1, discriminator: 3)
!1238 = !DILocation(line: 597, column: 17, scope: !1239)
!1239 = !DILexicalBlockFile(scope: !1231, file: !1, discriminator: 4)
!1240 = !DILocation(line: 597, column: 17, scope: !1241)
!1241 = !DILexicalBlockFile(scope: !1231, file: !1, discriminator: 5)
!1242 = !DILocation(line: 600, column: 17, scope: !1243)
!1243 = distinct !DILexicalBlock(scope: !1221, file: !1, line: 600, column: 17)
!1244 = !DILocation(line: 601, column: 17, scope: !1221)
!1245 = !DILocation(line: 601, column: 20, scope: !1221)
!1246 = !DILocation(line: 601, column: 27, scope: !1221)
!1247 = !DILocation(line: 602, column: 13, scope: !1221)
!1248 = !DILocation(line: 604, column: 17, scope: !1249)
!1249 = distinct !DILexicalBlock(scope: !1250, file: !1, line: 604, column: 17)
!1250 = distinct !DILexicalBlock(scope: !1215, file: !1, line: 603, column: 18)
!1251 = !DILocation(line: 610, column: 17, scope: !1252)
!1252 = distinct !DILexicalBlock(scope: !1250, file: !1, line: 610, column: 17)
!1253 = !DILocation(line: 611, column: 17, scope: !1254)
!1254 = distinct !DILexicalBlock(scope: !1250, file: !1, line: 611, column: 17)
!1255 = !DILocation(line: 612, column: 17, scope: !1256)
!1256 = distinct !DILexicalBlock(scope: !1250, file: !1, line: 612, column: 17)
!1257 = !DILocation(line: 613, column: 17, scope: !1258)
!1258 = distinct !DILexicalBlock(scope: !1250, file: !1, line: 613, column: 17)
!1259 = !DILocation(line: 614, column: 17, scope: !1260)
!1260 = distinct !DILexicalBlock(scope: !1250, file: !1, line: 614, column: 17)
!1261 = !DILocation(line: 614, column: 17, scope: !1262)
!1262 = !DILexicalBlockFile(scope: !1260, file: !1, discriminator: 1)
!1263 = !DILocation(line: 614, column: 17, scope: !1264)
!1264 = !DILexicalBlockFile(scope: !1260, file: !1, discriminator: 2)
!1265 = !DILocation(line: 614, column: 17, scope: !1266)
!1266 = !DILexicalBlockFile(scope: !1260, file: !1, discriminator: 3)
!1267 = !DILocation(line: 614, column: 17, scope: !1268)
!1268 = !DILexicalBlockFile(scope: !1260, file: !1, discriminator: 4)
!1269 = !DILocation(line: 614, column: 17, scope: !1270)
!1270 = !DILexicalBlockFile(scope: !1260, file: !1, discriminator: 5)
!1271 = !DILocation(line: 617, column: 17, scope: !1272)
!1272 = distinct !DILexicalBlock(scope: !1250, file: !1, line: 617, column: 17)
!1273 = !DILocation(line: 618, column: 21, scope: !1274)
!1274 = distinct !DILexicalBlock(scope: !1250, file: !1, line: 618, column: 21)
!1275 = !DILocation(line: 618, column: 24, scope: !1274)
!1276 = !DILocation(line: 618, column: 32, scope: !1274)
!1277 = !DILocation(line: 618, column: 38, scope: !1274)
!1278 = !DILocation(line: 618, column: 21, scope: !1250)
!1279 = !DILocation(line: 619, column: 21, scope: !1280)
!1280 = distinct !DILexicalBlock(scope: !1281, file: !1, line: 619, column: 21)
!1281 = distinct !DILexicalBlock(scope: !1274, file: !1, line: 618, column: 47)
!1282 = !DILocation(line: 620, column: 21, scope: !1283)
!1283 = distinct !DILexicalBlock(scope: !1281, file: !1, line: 620, column: 21)
!1284 = !DILocation(line: 621, column: 17, scope: !1281)
!1285 = !DILocation(line: 622, column: 21, scope: !1286)
!1286 = distinct !DILexicalBlock(scope: !1250, file: !1, line: 622, column: 21)
!1287 = !DILocation(line: 622, column: 24, scope: !1286)
!1288 = !DILocation(line: 622, column: 32, scope: !1286)
!1289 = !DILocation(line: 622, column: 21, scope: !1250)
!1290 = !DILocation(line: 623, column: 41, scope: !1286)
!1291 = !DILocation(line: 623, column: 47, scope: !1286)
!1292 = !DILocation(line: 623, column: 54, scope: !1286)
!1293 = !DILocation(line: 623, column: 57, scope: !1286)
!1294 = !DILocation(line: 624, column: 41, scope: !1286)
!1295 = !DILocation(line: 624, column: 44, scope: !1286)
!1296 = !DILocation(line: 623, column: 35, scope: !1286)
!1297 = !DILocation(line: 623, column: 21, scope: !1286)
!1298 = !DILocation(line: 623, column: 27, scope: !1286)
!1299 = !DILocation(line: 623, column: 33, scope: !1286)
!1300 = !DILocation(line: 625, column: 17, scope: !1250)
!1301 = !DILocation(line: 625, column: 20, scope: !1250)
!1302 = !DILocation(line: 625, column: 28, scope: !1250)
!1303 = !DILocation(line: 626, column: 17, scope: !1250)
!1304 = !DILocation(line: 626, column: 20, scope: !1250)
!1305 = !DILocation(line: 626, column: 27, scope: !1250)
!1306 = !DILocation(line: 628, column: 9, scope: !1204)
!1307 = !DILocalVariable(name: "header", scope: !1308, file: !1, line: 632, type: !18)
!1308 = distinct !DILexicalBlock(scope: !1198, file: !1, line: 631, column: 9)
!1309 = !DILocation(line: 632, column: 18, scope: !1308)
!1310 = !DILocation(line: 632, column: 43, scope: !1308)
!1311 = !DILocation(line: 632, column: 46, scope: !1308)
!1312 = !DILocation(line: 632, column: 52, scope: !1308)
!1313 = !DILocation(line: 632, column: 55, scope: !1308)
!1314 = !DILocation(line: 632, column: 39, scope: !1308)
!1315 = !DILocation(line: 632, column: 61, scope: !1308)
!1316 = !DILocalVariable(name: "level_flags", scope: !1308, file: !1, line: 633, type: !18)
!1317 = !DILocation(line: 633, column: 18, scope: !1308)
!1318 = !DILocation(line: 635, column: 17, scope: !1319)
!1319 = distinct !DILexicalBlock(scope: !1308, file: !1, line: 635, column: 17)
!1320 = !DILocation(line: 635, column: 20, scope: !1319)
!1321 = !DILocation(line: 635, column: 29, scope: !1319)
!1322 = !DILocation(line: 635, column: 47, scope: !1319)
!1323 = !DILocation(line: 635, column: 50, scope: !1324)
!1324 = !DILexicalBlockFile(scope: !1319, file: !1, discriminator: 1)
!1325 = !DILocation(line: 635, column: 53, scope: !1324)
!1326 = !DILocation(line: 635, column: 59, scope: !1324)
!1327 = !DILocation(line: 635, column: 17, scope: !1324)
!1328 = !DILocation(line: 636, column: 29, scope: !1319)
!1329 = !DILocation(line: 636, column: 17, scope: !1319)
!1330 = !DILocation(line: 637, column: 22, scope: !1331)
!1331 = distinct !DILexicalBlock(scope: !1319, file: !1, line: 637, column: 22)
!1332 = !DILocation(line: 637, column: 25, scope: !1331)
!1333 = !DILocation(line: 637, column: 31, scope: !1331)
!1334 = !DILocation(line: 637, column: 22, scope: !1319)
!1335 = !DILocation(line: 638, column: 29, scope: !1331)
!1336 = !DILocation(line: 638, column: 17, scope: !1331)
!1337 = !DILocation(line: 639, column: 22, scope: !1338)
!1338 = distinct !DILexicalBlock(scope: !1331, file: !1, line: 639, column: 22)
!1339 = !DILocation(line: 639, column: 25, scope: !1338)
!1340 = !DILocation(line: 639, column: 31, scope: !1338)
!1341 = !DILocation(line: 639, column: 22, scope: !1331)
!1342 = !DILocation(line: 640, column: 29, scope: !1338)
!1343 = !DILocation(line: 640, column: 17, scope: !1338)
!1344 = !DILocation(line: 642, column: 29, scope: !1338)
!1345 = !DILocation(line: 643, column: 24, scope: !1308)
!1346 = !DILocation(line: 643, column: 36, scope: !1308)
!1347 = !DILocation(line: 643, column: 20, scope: !1308)
!1348 = !DILocation(line: 644, column: 17, scope: !1349)
!1349 = distinct !DILexicalBlock(scope: !1308, file: !1, line: 644, column: 17)
!1350 = !DILocation(line: 644, column: 20, scope: !1349)
!1351 = !DILocation(line: 644, column: 29, scope: !1349)
!1352 = !DILocation(line: 644, column: 17, scope: !1308)
!1353 = !DILocation(line: 644, column: 42, scope: !1354)
!1354 = !DILexicalBlockFile(scope: !1349, file: !1, discriminator: 1)
!1355 = !DILocation(line: 644, column: 35, scope: !1354)
!1356 = !DILocation(line: 645, column: 29, scope: !1308)
!1357 = !DILocation(line: 645, column: 36, scope: !1308)
!1358 = !DILocation(line: 645, column: 26, scope: !1308)
!1359 = !DILocation(line: 645, column: 20, scope: !1308)
!1360 = !DILocation(line: 647, column: 13, scope: !1308)
!1361 = !DILocation(line: 647, column: 16, scope: !1308)
!1362 = !DILocation(line: 647, column: 23, scope: !1308)
!1363 = !DILocation(line: 648, column: 25, scope: !1308)
!1364 = !DILocation(line: 648, column: 28, scope: !1308)
!1365 = !DILocation(line: 648, column: 13, scope: !1308)
!1366 = !DILocation(line: 651, column: 17, scope: !1367)
!1367 = distinct !DILexicalBlock(scope: !1308, file: !1, line: 651, column: 17)
!1368 = !DILocation(line: 651, column: 20, scope: !1367)
!1369 = !DILocation(line: 651, column: 29, scope: !1367)
!1370 = !DILocation(line: 651, column: 17, scope: !1308)
!1371 = !DILocation(line: 652, column: 29, scope: !1372)
!1372 = distinct !DILexicalBlock(scope: !1367, file: !1, line: 651, column: 35)
!1373 = !DILocation(line: 652, column: 39, scope: !1372)
!1374 = !DILocation(line: 652, column: 45, scope: !1372)
!1375 = !DILocation(line: 652, column: 51, scope: !1372)
!1376 = !DILocation(line: 652, column: 32, scope: !1372)
!1377 = !DILocation(line: 652, column: 17, scope: !1372)
!1378 = !DILocation(line: 653, column: 29, scope: !1372)
!1379 = !DILocation(line: 653, column: 39, scope: !1372)
!1380 = !DILocation(line: 653, column: 45, scope: !1372)
!1381 = !DILocation(line: 653, column: 51, scope: !1372)
!1382 = !DILocation(line: 653, column: 32, scope: !1372)
!1383 = !DILocation(line: 653, column: 17, scope: !1372)
!1384 = !DILocation(line: 654, column: 13, scope: !1372)
!1385 = !DILocation(line: 655, column: 27, scope: !1308)
!1386 = !DILocation(line: 655, column: 13, scope: !1308)
!1387 = !DILocation(line: 655, column: 19, scope: !1308)
!1388 = !DILocation(line: 655, column: 25, scope: !1308)
!1389 = !DILocation(line: 657, column: 5, scope: !1199)
!1390 = !DILocation(line: 659, column: 9, scope: !1391)
!1391 = distinct !DILexicalBlock(scope: !219, file: !1, line: 659, column: 9)
!1392 = !DILocation(line: 659, column: 12, scope: !1391)
!1393 = !DILocation(line: 659, column: 19, scope: !1391)
!1394 = !DILocation(line: 659, column: 9, scope: !219)
!1395 = !DILocation(line: 660, column: 13, scope: !1396)
!1396 = distinct !DILexicalBlock(scope: !1397, file: !1, line: 660, column: 13)
!1397 = distinct !DILexicalBlock(scope: !1391, file: !1, line: 659, column: 35)
!1398 = !DILocation(line: 660, column: 16, scope: !1396)
!1399 = !DILocation(line: 660, column: 24, scope: !1396)
!1400 = !DILocation(line: 660, column: 30, scope: !1396)
!1401 = !DILocation(line: 660, column: 13, scope: !1397)
!1402 = !DILocalVariable(name: "beg", scope: !1403, file: !1, line: 661, type: !18)
!1403 = distinct !DILexicalBlock(scope: !1396, file: !1, line: 660, column: 39)
!1404 = !DILocation(line: 661, column: 18, scope: !1403)
!1405 = !DILocation(line: 661, column: 24, scope: !1403)
!1406 = !DILocation(line: 661, column: 27, scope: !1403)
!1407 = !DILocation(line: 663, column: 13, scope: !1403)
!1408 = !DILocation(line: 663, column: 20, scope: !1409)
!1409 = !DILexicalBlockFile(scope: !1403, file: !1, discriminator: 1)
!1410 = !DILocation(line: 663, column: 23, scope: !1409)
!1411 = !DILocation(line: 663, column: 34, scope: !1409)
!1412 = !DILocation(line: 663, column: 37, scope: !1409)
!1413 = !DILocation(line: 663, column: 45, scope: !1409)
!1414 = !DILocation(line: 663, column: 55, scope: !1409)
!1415 = !DILocation(line: 663, column: 31, scope: !1409)
!1416 = !DILocation(line: 663, column: 13, scope: !1409)
!1417 = !DILocation(line: 664, column: 21, scope: !1418)
!1418 = distinct !DILexicalBlock(scope: !1419, file: !1, line: 664, column: 21)
!1419 = distinct !DILexicalBlock(scope: !1403, file: !1, line: 663, column: 66)
!1420 = !DILocation(line: 664, column: 24, scope: !1418)
!1421 = !DILocation(line: 664, column: 35, scope: !1418)
!1422 = !DILocation(line: 664, column: 38, scope: !1418)
!1423 = !DILocation(line: 664, column: 32, scope: !1418)
!1424 = !DILocation(line: 664, column: 21, scope: !1419)
!1425 = !DILocation(line: 665, column: 25, scope: !1426)
!1426 = distinct !DILexicalBlock(scope: !1427, file: !1, line: 665, column: 25)
!1427 = distinct !DILexicalBlock(scope: !1418, file: !1, line: 664, column: 56)
!1428 = !DILocation(line: 665, column: 28, scope: !1426)
!1429 = !DILocation(line: 665, column: 36, scope: !1426)
!1430 = !DILocation(line: 665, column: 41, scope: !1426)
!1431 = !DILocation(line: 665, column: 44, scope: !1432)
!1432 = !DILexicalBlockFile(scope: !1426, file: !1, discriminator: 1)
!1433 = !DILocation(line: 665, column: 47, scope: !1432)
!1434 = !DILocation(line: 665, column: 57, scope: !1432)
!1435 = !DILocation(line: 665, column: 55, scope: !1432)
!1436 = !DILocation(line: 665, column: 25, scope: !1432)
!1437 = !DILocation(line: 666, column: 45, scope: !1426)
!1438 = !DILocation(line: 666, column: 51, scope: !1426)
!1439 = !DILocation(line: 666, column: 58, scope: !1426)
!1440 = !DILocation(line: 666, column: 61, scope: !1426)
!1441 = !DILocation(line: 666, column: 75, scope: !1426)
!1442 = !DILocation(line: 666, column: 73, scope: !1426)
!1443 = !DILocation(line: 667, column: 45, scope: !1426)
!1444 = !DILocation(line: 667, column: 48, scope: !1426)
!1445 = !DILocation(line: 667, column: 58, scope: !1426)
!1446 = !DILocation(line: 667, column: 56, scope: !1426)
!1447 = !DILocation(line: 666, column: 39, scope: !1426)
!1448 = !DILocation(line: 666, column: 25, scope: !1426)
!1449 = !DILocation(line: 666, column: 31, scope: !1426)
!1450 = !DILocation(line: 666, column: 37, scope: !1426)
!1451 = !DILocation(line: 668, column: 35, scope: !1427)
!1452 = !DILocation(line: 668, column: 21, scope: !1427)
!1453 = !DILocation(line: 669, column: 27, scope: !1427)
!1454 = !DILocation(line: 669, column: 30, scope: !1427)
!1455 = !DILocation(line: 669, column: 25, scope: !1427)
!1456 = !DILocation(line: 670, column: 25, scope: !1457)
!1457 = distinct !DILexicalBlock(scope: !1427, file: !1, line: 670, column: 25)
!1458 = !DILocation(line: 670, column: 28, scope: !1457)
!1459 = !DILocation(line: 670, column: 39, scope: !1457)
!1460 = !DILocation(line: 670, column: 42, scope: !1457)
!1461 = !DILocation(line: 670, column: 36, scope: !1457)
!1462 = !DILocation(line: 670, column: 25, scope: !1427)
!1463 = !DILocation(line: 671, column: 25, scope: !1457)
!1464 = !DILocation(line: 672, column: 17, scope: !1427)
!1465 = !DILocation(line: 673, column: 17, scope: !1466)
!1466 = distinct !DILexicalBlock(scope: !1419, file: !1, line: 673, column: 17)
!1467 = !DILocation(line: 674, column: 17, scope: !1419)
!1468 = !DILocation(line: 674, column: 20, scope: !1419)
!1469 = !DILocation(line: 674, column: 27, scope: !1419)
!1470 = !DILocation(line: 663, column: 13, scope: !1471)
!1471 = !DILexicalBlockFile(scope: !1403, file: !1, discriminator: 2)
!1472 = !DILocation(line: 676, column: 17, scope: !1473)
!1473 = distinct !DILexicalBlock(scope: !1403, file: !1, line: 676, column: 17)
!1474 = !DILocation(line: 676, column: 20, scope: !1473)
!1475 = !DILocation(line: 676, column: 28, scope: !1473)
!1476 = !DILocation(line: 676, column: 33, scope: !1473)
!1477 = !DILocation(line: 676, column: 36, scope: !1478)
!1478 = !DILexicalBlockFile(scope: !1473, file: !1, discriminator: 1)
!1479 = !DILocation(line: 676, column: 39, scope: !1478)
!1480 = !DILocation(line: 676, column: 49, scope: !1478)
!1481 = !DILocation(line: 676, column: 47, scope: !1478)
!1482 = !DILocation(line: 676, column: 17, scope: !1478)
!1483 = !DILocation(line: 677, column: 37, scope: !1473)
!1484 = !DILocation(line: 677, column: 43, scope: !1473)
!1485 = !DILocation(line: 677, column: 50, scope: !1473)
!1486 = !DILocation(line: 677, column: 53, scope: !1473)
!1487 = !DILocation(line: 677, column: 67, scope: !1473)
!1488 = !DILocation(line: 677, column: 65, scope: !1473)
!1489 = !DILocation(line: 678, column: 37, scope: !1473)
!1490 = !DILocation(line: 678, column: 40, scope: !1473)
!1491 = !DILocation(line: 678, column: 50, scope: !1473)
!1492 = !DILocation(line: 678, column: 48, scope: !1473)
!1493 = !DILocation(line: 677, column: 31, scope: !1473)
!1494 = !DILocation(line: 677, column: 17, scope: !1473)
!1495 = !DILocation(line: 677, column: 23, scope: !1473)
!1496 = !DILocation(line: 677, column: 29, scope: !1473)
!1497 = !DILocation(line: 679, column: 17, scope: !1498)
!1498 = distinct !DILexicalBlock(scope: !1403, file: !1, line: 679, column: 17)
!1499 = !DILocation(line: 679, column: 20, scope: !1498)
!1500 = !DILocation(line: 679, column: 31, scope: !1498)
!1501 = !DILocation(line: 679, column: 34, scope: !1498)
!1502 = !DILocation(line: 679, column: 42, scope: !1498)
!1503 = !DILocation(line: 679, column: 28, scope: !1498)
!1504 = !DILocation(line: 679, column: 17, scope: !1403)
!1505 = !DILocation(line: 680, column: 17, scope: !1506)
!1506 = distinct !DILexicalBlock(scope: !1498, file: !1, line: 679, column: 53)
!1507 = !DILocation(line: 680, column: 20, scope: !1506)
!1508 = !DILocation(line: 680, column: 28, scope: !1506)
!1509 = !DILocation(line: 681, column: 17, scope: !1506)
!1510 = !DILocation(line: 681, column: 20, scope: !1506)
!1511 = !DILocation(line: 681, column: 27, scope: !1506)
!1512 = !DILocation(line: 682, column: 13, scope: !1506)
!1513 = !DILocation(line: 683, column: 9, scope: !1403)
!1514 = !DILocation(line: 685, column: 13, scope: !1396)
!1515 = !DILocation(line: 685, column: 16, scope: !1396)
!1516 = !DILocation(line: 685, column: 23, scope: !1396)
!1517 = !DILocation(line: 686, column: 5, scope: !1397)
!1518 = !DILocation(line: 687, column: 9, scope: !1519)
!1519 = distinct !DILexicalBlock(scope: !219, file: !1, line: 687, column: 9)
!1520 = !DILocation(line: 687, column: 12, scope: !1519)
!1521 = !DILocation(line: 687, column: 19, scope: !1519)
!1522 = !DILocation(line: 687, column: 9, scope: !219)
!1523 = !DILocation(line: 688, column: 13, scope: !1524)
!1524 = distinct !DILexicalBlock(scope: !1525, file: !1, line: 688, column: 13)
!1525 = distinct !DILexicalBlock(scope: !1519, file: !1, line: 687, column: 34)
!1526 = !DILocation(line: 688, column: 16, scope: !1524)
!1527 = !DILocation(line: 688, column: 24, scope: !1524)
!1528 = !DILocation(line: 688, column: 29, scope: !1524)
!1529 = !DILocation(line: 688, column: 13, scope: !1525)
!1530 = !DILocalVariable(name: "beg", scope: !1531, file: !1, line: 689, type: !18)
!1531 = distinct !DILexicalBlock(scope: !1524, file: !1, line: 688, column: 38)
!1532 = !DILocation(line: 689, column: 18, scope: !1531)
!1533 = !DILocation(line: 689, column: 24, scope: !1531)
!1534 = !DILocation(line: 689, column: 27, scope: !1531)
!1535 = !DILocalVariable(name: "val", scope: !1531, file: !1, line: 690, type: !56)
!1536 = !DILocation(line: 690, column: 17, scope: !1531)
!1537 = !DILocation(line: 692, column: 13, scope: !1531)
!1538 = !DILocation(line: 693, column: 21, scope: !1539)
!1539 = distinct !DILexicalBlock(scope: !1540, file: !1, line: 693, column: 21)
!1540 = distinct !DILexicalBlock(scope: !1531, file: !1, line: 692, column: 16)
!1541 = !DILocation(line: 693, column: 24, scope: !1539)
!1542 = !DILocation(line: 693, column: 35, scope: !1539)
!1543 = !DILocation(line: 693, column: 38, scope: !1539)
!1544 = !DILocation(line: 693, column: 32, scope: !1539)
!1545 = !DILocation(line: 693, column: 21, scope: !1540)
!1546 = !DILocation(line: 694, column: 25, scope: !1547)
!1547 = distinct !DILexicalBlock(scope: !1548, file: !1, line: 694, column: 25)
!1548 = distinct !DILexicalBlock(scope: !1539, file: !1, line: 693, column: 56)
!1549 = !DILocation(line: 694, column: 28, scope: !1547)
!1550 = !DILocation(line: 694, column: 36, scope: !1547)
!1551 = !DILocation(line: 694, column: 41, scope: !1547)
!1552 = !DILocation(line: 694, column: 44, scope: !1553)
!1553 = !DILexicalBlockFile(scope: !1547, file: !1, discriminator: 1)
!1554 = !DILocation(line: 694, column: 47, scope: !1553)
!1555 = !DILocation(line: 694, column: 57, scope: !1553)
!1556 = !DILocation(line: 694, column: 55, scope: !1553)
!1557 = !DILocation(line: 694, column: 25, scope: !1553)
!1558 = !DILocation(line: 695, column: 45, scope: !1547)
!1559 = !DILocation(line: 695, column: 51, scope: !1547)
!1560 = !DILocation(line: 695, column: 58, scope: !1547)
!1561 = !DILocation(line: 695, column: 61, scope: !1547)
!1562 = !DILocation(line: 695, column: 75, scope: !1547)
!1563 = !DILocation(line: 695, column: 73, scope: !1547)
!1564 = !DILocation(line: 696, column: 45, scope: !1547)
!1565 = !DILocation(line: 696, column: 48, scope: !1547)
!1566 = !DILocation(line: 696, column: 58, scope: !1547)
!1567 = !DILocation(line: 696, column: 56, scope: !1547)
!1568 = !DILocation(line: 695, column: 39, scope: !1547)
!1569 = !DILocation(line: 695, column: 25, scope: !1547)
!1570 = !DILocation(line: 695, column: 31, scope: !1547)
!1571 = !DILocation(line: 695, column: 37, scope: !1547)
!1572 = !DILocation(line: 697, column: 35, scope: !1548)
!1573 = !DILocation(line: 697, column: 21, scope: !1548)
!1574 = !DILocation(line: 698, column: 27, scope: !1548)
!1575 = !DILocation(line: 698, column: 30, scope: !1548)
!1576 = !DILocation(line: 698, column: 25, scope: !1548)
!1577 = !DILocation(line: 699, column: 25, scope: !1578)
!1578 = distinct !DILexicalBlock(scope: !1548, file: !1, line: 699, column: 25)
!1579 = !DILocation(line: 699, column: 28, scope: !1578)
!1580 = !DILocation(line: 699, column: 39, scope: !1578)
!1581 = !DILocation(line: 699, column: 42, scope: !1578)
!1582 = !DILocation(line: 699, column: 36, scope: !1578)
!1583 = !DILocation(line: 699, column: 25, scope: !1548)
!1584 = !DILocation(line: 700, column: 29, scope: !1585)
!1585 = distinct !DILexicalBlock(scope: !1578, file: !1, line: 699, column: 60)
!1586 = !DILocation(line: 701, column: 25, scope: !1585)
!1587 = !DILocation(line: 703, column: 17, scope: !1548)
!1588 = !DILocation(line: 704, column: 39, scope: !1540)
!1589 = !DILocation(line: 704, column: 42, scope: !1540)
!1590 = !DILocation(line: 704, column: 49, scope: !1540)
!1591 = !DILocation(line: 704, column: 23, scope: !1540)
!1592 = !DILocation(line: 704, column: 26, scope: !1540)
!1593 = !DILocation(line: 704, column: 34, scope: !1540)
!1594 = !DILocation(line: 704, column: 21, scope: !1540)
!1595 = !DILocation(line: 705, column: 17, scope: !1596)
!1596 = distinct !DILexicalBlock(scope: !1540, file: !1, line: 705, column: 17)
!1597 = !DILocation(line: 706, column: 13, scope: !1540)
!1598 = !DILocation(line: 706, column: 22, scope: !1599)
!1599 = !DILexicalBlockFile(scope: !1531, file: !1, discriminator: 1)
!1600 = !DILocation(line: 706, column: 26, scope: !1599)
!1601 = !DILocation(line: 706, column: 13, scope: !1599)
!1602 = !DILocation(line: 707, column: 17, scope: !1603)
!1603 = distinct !DILexicalBlock(scope: !1531, file: !1, line: 707, column: 17)
!1604 = !DILocation(line: 707, column: 20, scope: !1603)
!1605 = !DILocation(line: 707, column: 28, scope: !1603)
!1606 = !DILocation(line: 707, column: 33, scope: !1603)
!1607 = !DILocation(line: 707, column: 36, scope: !1608)
!1608 = !DILexicalBlockFile(scope: !1603, file: !1, discriminator: 1)
!1609 = !DILocation(line: 707, column: 39, scope: !1608)
!1610 = !DILocation(line: 707, column: 49, scope: !1608)
!1611 = !DILocation(line: 707, column: 47, scope: !1608)
!1612 = !DILocation(line: 707, column: 17, scope: !1608)
!1613 = !DILocation(line: 708, column: 37, scope: !1603)
!1614 = !DILocation(line: 708, column: 43, scope: !1603)
!1615 = !DILocation(line: 708, column: 50, scope: !1603)
!1616 = !DILocation(line: 708, column: 53, scope: !1603)
!1617 = !DILocation(line: 708, column: 67, scope: !1603)
!1618 = !DILocation(line: 708, column: 65, scope: !1603)
!1619 = !DILocation(line: 709, column: 37, scope: !1603)
!1620 = !DILocation(line: 709, column: 40, scope: !1603)
!1621 = !DILocation(line: 709, column: 50, scope: !1603)
!1622 = !DILocation(line: 709, column: 48, scope: !1603)
!1623 = !DILocation(line: 708, column: 31, scope: !1603)
!1624 = !DILocation(line: 708, column: 17, scope: !1603)
!1625 = !DILocation(line: 708, column: 23, scope: !1603)
!1626 = !DILocation(line: 708, column: 29, scope: !1603)
!1627 = !DILocation(line: 710, column: 17, scope: !1628)
!1628 = distinct !DILexicalBlock(scope: !1531, file: !1, line: 710, column: 17)
!1629 = !DILocation(line: 710, column: 21, scope: !1628)
!1630 = !DILocation(line: 710, column: 17, scope: !1531)
!1631 = !DILocation(line: 711, column: 17, scope: !1632)
!1632 = distinct !DILexicalBlock(scope: !1628, file: !1, line: 710, column: 27)
!1633 = !DILocation(line: 711, column: 20, scope: !1632)
!1634 = !DILocation(line: 711, column: 28, scope: !1632)
!1635 = !DILocation(line: 712, column: 17, scope: !1632)
!1636 = !DILocation(line: 712, column: 20, scope: !1632)
!1637 = !DILocation(line: 712, column: 27, scope: !1632)
!1638 = !DILocation(line: 713, column: 13, scope: !1632)
!1639 = !DILocation(line: 714, column: 9, scope: !1531)
!1640 = !DILocation(line: 716, column: 13, scope: !1524)
!1641 = !DILocation(line: 716, column: 16, scope: !1524)
!1642 = !DILocation(line: 716, column: 23, scope: !1524)
!1643 = !DILocation(line: 717, column: 5, scope: !1525)
!1644 = !DILocation(line: 718, column: 9, scope: !1645)
!1645 = distinct !DILexicalBlock(scope: !219, file: !1, line: 718, column: 9)
!1646 = !DILocation(line: 718, column: 12, scope: !1645)
!1647 = !DILocation(line: 718, column: 19, scope: !1645)
!1648 = !DILocation(line: 718, column: 9, scope: !219)
!1649 = !DILocation(line: 719, column: 13, scope: !1650)
!1650 = distinct !DILexicalBlock(scope: !1651, file: !1, line: 719, column: 13)
!1651 = distinct !DILexicalBlock(scope: !1645, file: !1, line: 718, column: 37)
!1652 = !DILocation(line: 719, column: 16, scope: !1650)
!1653 = !DILocation(line: 719, column: 24, scope: !1650)
!1654 = !DILocation(line: 719, column: 32, scope: !1650)
!1655 = !DILocation(line: 719, column: 13, scope: !1651)
!1656 = !DILocalVariable(name: "beg", scope: !1657, file: !1, line: 720, type: !18)
!1657 = distinct !DILexicalBlock(scope: !1650, file: !1, line: 719, column: 41)
!1658 = !DILocation(line: 720, column: 18, scope: !1657)
!1659 = !DILocation(line: 720, column: 24, scope: !1657)
!1660 = !DILocation(line: 720, column: 27, scope: !1657)
!1661 = !DILocalVariable(name: "val", scope: !1657, file: !1, line: 721, type: !56)
!1662 = !DILocation(line: 721, column: 17, scope: !1657)
!1663 = !DILocation(line: 723, column: 13, scope: !1657)
!1664 = !DILocation(line: 724, column: 21, scope: !1665)
!1665 = distinct !DILexicalBlock(scope: !1666, file: !1, line: 724, column: 21)
!1666 = distinct !DILexicalBlock(scope: !1657, file: !1, line: 723, column: 16)
!1667 = !DILocation(line: 724, column: 24, scope: !1665)
!1668 = !DILocation(line: 724, column: 35, scope: !1665)
!1669 = !DILocation(line: 724, column: 38, scope: !1665)
!1670 = !DILocation(line: 724, column: 32, scope: !1665)
!1671 = !DILocation(line: 724, column: 21, scope: !1666)
!1672 = !DILocation(line: 725, column: 25, scope: !1673)
!1673 = distinct !DILexicalBlock(scope: !1674, file: !1, line: 725, column: 25)
!1674 = distinct !DILexicalBlock(scope: !1665, file: !1, line: 724, column: 56)
!1675 = !DILocation(line: 725, column: 28, scope: !1673)
!1676 = !DILocation(line: 725, column: 36, scope: !1673)
!1677 = !DILocation(line: 725, column: 41, scope: !1673)
!1678 = !DILocation(line: 725, column: 44, scope: !1679)
!1679 = !DILexicalBlockFile(scope: !1673, file: !1, discriminator: 1)
!1680 = !DILocation(line: 725, column: 47, scope: !1679)
!1681 = !DILocation(line: 725, column: 57, scope: !1679)
!1682 = !DILocation(line: 725, column: 55, scope: !1679)
!1683 = !DILocation(line: 725, column: 25, scope: !1679)
!1684 = !DILocation(line: 726, column: 45, scope: !1673)
!1685 = !DILocation(line: 726, column: 51, scope: !1673)
!1686 = !DILocation(line: 726, column: 58, scope: !1673)
!1687 = !DILocation(line: 726, column: 61, scope: !1673)
!1688 = !DILocation(line: 726, column: 75, scope: !1673)
!1689 = !DILocation(line: 726, column: 73, scope: !1673)
!1690 = !DILocation(line: 727, column: 45, scope: !1673)
!1691 = !DILocation(line: 727, column: 48, scope: !1673)
!1692 = !DILocation(line: 727, column: 58, scope: !1673)
!1693 = !DILocation(line: 727, column: 56, scope: !1673)
!1694 = !DILocation(line: 726, column: 39, scope: !1673)
!1695 = !DILocation(line: 726, column: 25, scope: !1673)
!1696 = !DILocation(line: 726, column: 31, scope: !1673)
!1697 = !DILocation(line: 726, column: 37, scope: !1673)
!1698 = !DILocation(line: 728, column: 35, scope: !1674)
!1699 = !DILocation(line: 728, column: 21, scope: !1674)
!1700 = !DILocation(line: 729, column: 27, scope: !1674)
!1701 = !DILocation(line: 729, column: 30, scope: !1674)
!1702 = !DILocation(line: 729, column: 25, scope: !1674)
!1703 = !DILocation(line: 730, column: 25, scope: !1704)
!1704 = distinct !DILexicalBlock(scope: !1674, file: !1, line: 730, column: 25)
!1705 = !DILocation(line: 730, column: 28, scope: !1704)
!1706 = !DILocation(line: 730, column: 39, scope: !1704)
!1707 = !DILocation(line: 730, column: 42, scope: !1704)
!1708 = !DILocation(line: 730, column: 36, scope: !1704)
!1709 = !DILocation(line: 730, column: 25, scope: !1674)
!1710 = !DILocation(line: 731, column: 29, scope: !1711)
!1711 = distinct !DILexicalBlock(scope: !1704, file: !1, line: 730, column: 60)
!1712 = !DILocation(line: 732, column: 25, scope: !1711)
!1713 = !DILocation(line: 734, column: 17, scope: !1674)
!1714 = !DILocation(line: 735, column: 42, scope: !1666)
!1715 = !DILocation(line: 735, column: 45, scope: !1666)
!1716 = !DILocation(line: 735, column: 52, scope: !1666)
!1717 = !DILocation(line: 735, column: 23, scope: !1666)
!1718 = !DILocation(line: 735, column: 26, scope: !1666)
!1719 = !DILocation(line: 735, column: 34, scope: !1666)
!1720 = !DILocation(line: 735, column: 21, scope: !1666)
!1721 = !DILocation(line: 736, column: 17, scope: !1722)
!1722 = distinct !DILexicalBlock(scope: !1666, file: !1, line: 736, column: 17)
!1723 = !DILocation(line: 737, column: 13, scope: !1666)
!1724 = !DILocation(line: 737, column: 22, scope: !1725)
!1725 = !DILexicalBlockFile(scope: !1657, file: !1, discriminator: 1)
!1726 = !DILocation(line: 737, column: 26, scope: !1725)
!1727 = !DILocation(line: 737, column: 13, scope: !1725)
!1728 = !DILocation(line: 738, column: 17, scope: !1729)
!1729 = distinct !DILexicalBlock(scope: !1657, file: !1, line: 738, column: 17)
!1730 = !DILocation(line: 738, column: 20, scope: !1729)
!1731 = !DILocation(line: 738, column: 28, scope: !1729)
!1732 = !DILocation(line: 738, column: 33, scope: !1729)
!1733 = !DILocation(line: 738, column: 36, scope: !1734)
!1734 = !DILexicalBlockFile(scope: !1729, file: !1, discriminator: 1)
!1735 = !DILocation(line: 738, column: 39, scope: !1734)
!1736 = !DILocation(line: 738, column: 49, scope: !1734)
!1737 = !DILocation(line: 738, column: 47, scope: !1734)
!1738 = !DILocation(line: 738, column: 17, scope: !1734)
!1739 = !DILocation(line: 739, column: 37, scope: !1729)
!1740 = !DILocation(line: 739, column: 43, scope: !1729)
!1741 = !DILocation(line: 739, column: 50, scope: !1729)
!1742 = !DILocation(line: 739, column: 53, scope: !1729)
!1743 = !DILocation(line: 739, column: 67, scope: !1729)
!1744 = !DILocation(line: 739, column: 65, scope: !1729)
!1745 = !DILocation(line: 740, column: 37, scope: !1729)
!1746 = !DILocation(line: 740, column: 40, scope: !1729)
!1747 = !DILocation(line: 740, column: 50, scope: !1729)
!1748 = !DILocation(line: 740, column: 48, scope: !1729)
!1749 = !DILocation(line: 739, column: 31, scope: !1729)
!1750 = !DILocation(line: 739, column: 17, scope: !1729)
!1751 = !DILocation(line: 739, column: 23, scope: !1729)
!1752 = !DILocation(line: 739, column: 29, scope: !1729)
!1753 = !DILocation(line: 741, column: 17, scope: !1754)
!1754 = distinct !DILexicalBlock(scope: !1657, file: !1, line: 741, column: 17)
!1755 = !DILocation(line: 741, column: 21, scope: !1754)
!1756 = !DILocation(line: 741, column: 17, scope: !1657)
!1757 = !DILocation(line: 742, column: 17, scope: !1754)
!1758 = !DILocation(line: 742, column: 20, scope: !1754)
!1759 = !DILocation(line: 742, column: 27, scope: !1754)
!1760 = !DILocation(line: 743, column: 9, scope: !1657)
!1761 = !DILocation(line: 745, column: 13, scope: !1650)
!1762 = !DILocation(line: 745, column: 16, scope: !1650)
!1763 = !DILocation(line: 745, column: 23, scope: !1650)
!1764 = !DILocation(line: 746, column: 5, scope: !1651)
!1765 = !DILocation(line: 747, column: 9, scope: !1766)
!1766 = distinct !DILexicalBlock(scope: !219, file: !1, line: 747, column: 9)
!1767 = !DILocation(line: 747, column: 12, scope: !1766)
!1768 = !DILocation(line: 747, column: 19, scope: !1766)
!1769 = !DILocation(line: 747, column: 9, scope: !219)
!1770 = !DILocation(line: 748, column: 13, scope: !1771)
!1771 = distinct !DILexicalBlock(scope: !1772, file: !1, line: 748, column: 13)
!1772 = distinct !DILexicalBlock(scope: !1766, file: !1, line: 747, column: 34)
!1773 = !DILocation(line: 748, column: 16, scope: !1771)
!1774 = !DILocation(line: 748, column: 24, scope: !1771)
!1775 = !DILocation(line: 748, column: 13, scope: !1772)
!1776 = !DILocation(line: 749, column: 17, scope: !1777)
!1777 = distinct !DILexicalBlock(scope: !1778, file: !1, line: 749, column: 17)
!1778 = distinct !DILexicalBlock(scope: !1771, file: !1, line: 748, column: 30)
!1779 = !DILocation(line: 749, column: 20, scope: !1777)
!1780 = !DILocation(line: 749, column: 28, scope: !1777)
!1781 = !DILocation(line: 749, column: 34, scope: !1777)
!1782 = !DILocation(line: 749, column: 37, scope: !1777)
!1783 = !DILocation(line: 749, column: 32, scope: !1777)
!1784 = !DILocation(line: 749, column: 17, scope: !1778)
!1785 = !DILocation(line: 750, column: 31, scope: !1777)
!1786 = !DILocation(line: 750, column: 17, scope: !1777)
!1787 = !DILocation(line: 751, column: 17, scope: !1788)
!1788 = distinct !DILexicalBlock(scope: !1778, file: !1, line: 751, column: 17)
!1789 = !DILocation(line: 751, column: 20, scope: !1788)
!1790 = !DILocation(line: 751, column: 28, scope: !1788)
!1791 = !DILocation(line: 751, column: 35, scope: !1788)
!1792 = !DILocation(line: 751, column: 38, scope: !1788)
!1793 = !DILocation(line: 751, column: 32, scope: !1788)
!1794 = !DILocation(line: 751, column: 17, scope: !1778)
!1795 = !DILocation(line: 752, column: 17, scope: !1796)
!1796 = distinct !DILexicalBlock(scope: !1797, file: !1, line: 752, column: 17)
!1797 = distinct !DILexicalBlock(scope: !1788, file: !1, line: 751, column: 56)
!1798 = !DILocation(line: 753, column: 17, scope: !1799)
!1799 = distinct !DILexicalBlock(scope: !1797, file: !1, line: 753, column: 17)
!1800 = !DILocation(line: 754, column: 31, scope: !1797)
!1801 = !DILocation(line: 754, column: 17, scope: !1797)
!1802 = !DILocation(line: 754, column: 23, scope: !1797)
!1803 = !DILocation(line: 754, column: 29, scope: !1797)
!1804 = !DILocation(line: 755, column: 17, scope: !1797)
!1805 = !DILocation(line: 755, column: 20, scope: !1797)
!1806 = !DILocation(line: 755, column: 27, scope: !1797)
!1807 = !DILocation(line: 756, column: 13, scope: !1797)
!1808 = !DILocation(line: 757, column: 9, scope: !1778)
!1809 = !DILocation(line: 759, column: 13, scope: !1771)
!1810 = !DILocation(line: 759, column: 16, scope: !1771)
!1811 = !DILocation(line: 759, column: 23, scope: !1771)
!1812 = !DILocation(line: 760, column: 5, scope: !1772)
!1813 = !DILocation(line: 764, column: 9, scope: !1814)
!1814 = distinct !DILexicalBlock(scope: !219, file: !1, line: 764, column: 9)
!1815 = !DILocation(line: 764, column: 12, scope: !1814)
!1816 = !DILocation(line: 764, column: 20, scope: !1814)
!1817 = !DILocation(line: 764, column: 9, scope: !219)
!1818 = !DILocation(line: 765, column: 23, scope: !1819)
!1819 = distinct !DILexicalBlock(scope: !1814, file: !1, line: 764, column: 26)
!1820 = !DILocation(line: 765, column: 9, scope: !1819)
!1821 = !DILocation(line: 766, column: 13, scope: !1822)
!1822 = distinct !DILexicalBlock(scope: !1819, file: !1, line: 766, column: 13)
!1823 = !DILocation(line: 766, column: 19, scope: !1822)
!1824 = !DILocation(line: 766, column: 29, scope: !1822)
!1825 = !DILocation(line: 766, column: 13, scope: !1819)
!1826 = !DILocation(line: 773, column: 13, scope: !1827)
!1827 = distinct !DILexicalBlock(scope: !1822, file: !1, line: 766, column: 35)
!1828 = !DILocation(line: 773, column: 16, scope: !1827)
!1829 = !DILocation(line: 773, column: 27, scope: !1827)
!1830 = !DILocation(line: 774, column: 13, scope: !1827)
!1831 = !DILocation(line: 781, column: 5, scope: !1819)
!1832 = !DILocation(line: 781, column: 16, scope: !1833)
!1833 = !DILexicalBlockFile(scope: !1834, file: !1, discriminator: 1)
!1834 = distinct !DILexicalBlock(scope: !1814, file: !1, line: 781, column: 16)
!1835 = !DILocation(line: 781, column: 22, scope: !1833)
!1836 = !DILocation(line: 781, column: 31, scope: !1833)
!1837 = !DILocation(line: 781, column: 36, scope: !1833)
!1838 = !DILocation(line: 781, column: 39, scope: !1839)
!1839 = !DILexicalBlockFile(scope: !1834, file: !1, discriminator: 2)
!1840 = !DILocation(line: 781, column: 48, scope: !1839)
!1841 = !DILocation(line: 781, column: 45, scope: !1839)
!1842 = !DILocation(line: 781, column: 58, scope: !1839)
!1843 = !DILocation(line: 782, column: 16, scope: !1834)
!1844 = !DILocation(line: 782, column: 22, scope: !1834)
!1845 = !DILocation(line: 781, column: 16, scope: !1846)
!1846 = !DILexicalBlockFile(scope: !1814, file: !1, discriminator: 3)
!1847 = !DILocation(line: 783, column: 9, scope: !1848)
!1848 = distinct !DILexicalBlock(scope: !1834, file: !1, line: 782, column: 35)
!1849 = !DILocation(line: 787, column: 9, scope: !1850)
!1850 = distinct !DILexicalBlock(scope: !219, file: !1, line: 787, column: 9)
!1851 = !DILocation(line: 787, column: 12, scope: !1850)
!1852 = !DILocation(line: 787, column: 19, scope: !1850)
!1853 = !DILocation(line: 787, column: 35, scope: !1850)
!1854 = !DILocation(line: 787, column: 38, scope: !1855)
!1855 = !DILexicalBlockFile(scope: !1850, file: !1, discriminator: 1)
!1856 = !DILocation(line: 787, column: 44, scope: !1855)
!1857 = !DILocation(line: 787, column: 53, scope: !1855)
!1858 = !DILocation(line: 787, column: 9, scope: !1855)
!1859 = !DILocation(line: 788, column: 9, scope: !1860)
!1860 = distinct !DILexicalBlock(scope: !1850, file: !1, line: 787, column: 59)
!1861 = !DILocation(line: 793, column: 9, scope: !1862)
!1862 = distinct !DILexicalBlock(scope: !219, file: !1, line: 793, column: 9)
!1863 = !DILocation(line: 793, column: 15, scope: !1862)
!1864 = !DILocation(line: 793, column: 24, scope: !1862)
!1865 = !DILocation(line: 793, column: 29, scope: !1862)
!1866 = !DILocation(line: 793, column: 32, scope: !1867)
!1867 = !DILexicalBlockFile(scope: !1862, file: !1, discriminator: 1)
!1868 = !DILocation(line: 793, column: 35, scope: !1867)
!1869 = !DILocation(line: 793, column: 45, scope: !1867)
!1870 = !DILocation(line: 793, column: 50, scope: !1867)
!1871 = !DILocation(line: 794, column: 10, scope: !1862)
!1872 = !DILocation(line: 794, column: 16, scope: !1862)
!1873 = !DILocation(line: 794, column: 30, scope: !1862)
!1874 = !DILocation(line: 794, column: 33, scope: !1867)
!1875 = !DILocation(line: 794, column: 36, scope: !1867)
!1876 = !DILocation(line: 794, column: 43, scope: !1867)
!1877 = !DILocation(line: 793, column: 9, scope: !1144)
!1878 = !DILocalVariable(name: "bstate", scope: !1879, file: !1, line: 795, type: !229)
!1879 = distinct !DILexicalBlock(scope: !1862, file: !1, line: 794, column: 61)
!1880 = !DILocation(line: 795, column: 21, scope: !1879)
!1881 = !DILocation(line: 797, column: 41, scope: !1879)
!1882 = !DILocation(line: 797, column: 44, scope: !1879)
!1883 = !DILocation(line: 797, column: 21, scope: !1879)
!1884 = !DILocation(line: 797, column: 51, scope: !1879)
!1885 = !DILocation(line: 797, column: 58, scope: !1879)
!1886 = !DILocation(line: 797, column: 61, scope: !1879)
!1887 = !DILocation(line: 797, column: 18, scope: !1879)
!1888 = !DILocation(line: 797, column: 16, scope: !1879)
!1889 = !DILocation(line: 799, column: 13, scope: !1890)
!1890 = distinct !DILexicalBlock(scope: !1879, file: !1, line: 799, column: 13)
!1891 = !DILocation(line: 799, column: 20, scope: !1890)
!1892 = !DILocation(line: 799, column: 38, scope: !1890)
!1893 = !DILocation(line: 799, column: 41, scope: !1894)
!1894 = !DILexicalBlockFile(scope: !1890, file: !1, discriminator: 1)
!1895 = !DILocation(line: 799, column: 48, scope: !1894)
!1896 = !DILocation(line: 799, column: 13, scope: !1894)
!1897 = !DILocation(line: 800, column: 13, scope: !1898)
!1898 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 799, column: 64)
!1899 = !DILocation(line: 800, column: 16, scope: !1898)
!1900 = !DILocation(line: 800, column: 23, scope: !1898)
!1901 = !DILocation(line: 801, column: 9, scope: !1898)
!1902 = !DILocation(line: 802, column: 13, scope: !1903)
!1903 = distinct !DILexicalBlock(scope: !1879, file: !1, line: 802, column: 13)
!1904 = !DILocation(line: 802, column: 20, scope: !1903)
!1905 = !DILocation(line: 802, column: 33, scope: !1903)
!1906 = !DILocation(line: 802, column: 36, scope: !1907)
!1907 = !DILexicalBlockFile(scope: !1903, file: !1, discriminator: 1)
!1908 = !DILocation(line: 802, column: 43, scope: !1907)
!1909 = !DILocation(line: 802, column: 13, scope: !1907)
!1910 = !DILocation(line: 803, column: 17, scope: !1911)
!1911 = distinct !DILexicalBlock(scope: !1912, file: !1, line: 803, column: 17)
!1912 = distinct !DILexicalBlock(scope: !1903, file: !1, line: 802, column: 62)
!1913 = !DILocation(line: 803, column: 23, scope: !1911)
!1914 = !DILocation(line: 803, column: 33, scope: !1911)
!1915 = !DILocation(line: 803, column: 17, scope: !1912)
!1916 = !DILocation(line: 804, column: 17, scope: !1917)
!1917 = distinct !DILexicalBlock(scope: !1911, file: !1, line: 803, column: 39)
!1918 = !DILocation(line: 804, column: 20, scope: !1917)
!1919 = !DILocation(line: 804, column: 31, scope: !1917)
!1920 = !DILocation(line: 805, column: 13, scope: !1917)
!1921 = !DILocation(line: 806, column: 13, scope: !1912)
!1922 = !DILocation(line: 815, column: 13, scope: !1923)
!1923 = distinct !DILexicalBlock(scope: !1879, file: !1, line: 815, column: 13)
!1924 = !DILocation(line: 815, column: 20, scope: !1923)
!1925 = !DILocation(line: 815, column: 13, scope: !1879)
!1926 = !DILocation(line: 816, column: 17, scope: !1927)
!1927 = distinct !DILexicalBlock(scope: !1928, file: !1, line: 816, column: 17)
!1928 = distinct !DILexicalBlock(scope: !1923, file: !1, line: 815, column: 35)
!1929 = !DILocation(line: 816, column: 23, scope: !1927)
!1930 = !DILocation(line: 816, column: 17, scope: !1928)
!1931 = !DILocation(line: 817, column: 27, scope: !1932)
!1932 = distinct !DILexicalBlock(scope: !1927, file: !1, line: 816, column: 43)
!1933 = !DILocation(line: 817, column: 17, scope: !1932)
!1934 = !DILocation(line: 818, column: 13, scope: !1932)
!1935 = !DILocation(line: 819, column: 34, scope: !1936)
!1936 = distinct !DILexicalBlock(scope: !1927, file: !1, line: 818, column: 20)
!1937 = !DILocation(line: 819, column: 17, scope: !1936)
!1938 = !DILocation(line: 823, column: 21, scope: !1939)
!1939 = distinct !DILexicalBlock(scope: !1936, file: !1, line: 823, column: 21)
!1940 = !DILocation(line: 823, column: 27, scope: !1939)
!1941 = !DILocation(line: 823, column: 21, scope: !1936)
!1942 = !DILocation(line: 824, column: 21, scope: !1943)
!1943 = distinct !DILexicalBlock(scope: !1939, file: !1, line: 823, column: 44)
!1944 = !DILocation(line: 825, column: 17, scope: !1943)
!1945 = !DILocation(line: 827, column: 27, scope: !1928)
!1946 = !DILocation(line: 827, column: 13, scope: !1928)
!1947 = !DILocation(line: 828, column: 17, scope: !1948)
!1948 = distinct !DILexicalBlock(scope: !1928, file: !1, line: 828, column: 17)
!1949 = !DILocation(line: 828, column: 23, scope: !1948)
!1950 = !DILocation(line: 828, column: 33, scope: !1948)
!1951 = !DILocation(line: 828, column: 17, scope: !1928)
!1952 = !DILocation(line: 829, column: 15, scope: !1953)
!1953 = distinct !DILexicalBlock(scope: !1948, file: !1, line: 828, column: 39)
!1954 = !DILocation(line: 829, column: 18, scope: !1953)
!1955 = !DILocation(line: 829, column: 29, scope: !1953)
!1956 = !DILocation(line: 830, column: 15, scope: !1953)
!1957 = !DILocation(line: 832, column: 9, scope: !1928)
!1958 = !DILocation(line: 833, column: 5, scope: !1879)
!1959 = !DILocation(line: 836, column: 9, scope: !1960)
!1960 = distinct !DILexicalBlock(scope: !219, file: !1, line: 836, column: 9)
!1961 = !DILocation(line: 836, column: 15, scope: !1960)
!1962 = !DILocation(line: 836, column: 9, scope: !219)
!1963 = !DILocation(line: 836, column: 28, scope: !1964)
!1964 = !DILexicalBlockFile(scope: !1960, file: !1, discriminator: 1)
!1965 = !DILocation(line: 837, column: 9, scope: !1966)
!1966 = distinct !DILexicalBlock(scope: !219, file: !1, line: 837, column: 9)
!1967 = !DILocation(line: 837, column: 12, scope: !1966)
!1968 = !DILocation(line: 837, column: 17, scope: !1966)
!1969 = !DILocation(line: 837, column: 9, scope: !219)
!1970 = !DILocation(line: 837, column: 23, scope: !1971)
!1971 = !DILexicalBlockFile(scope: !1966, file: !1, discriminator: 1)
!1972 = !DILocation(line: 841, column: 9, scope: !1973)
!1973 = distinct !DILexicalBlock(scope: !219, file: !1, line: 841, column: 9)
!1974 = !DILocation(line: 841, column: 12, scope: !1973)
!1975 = !DILocation(line: 841, column: 17, scope: !1973)
!1976 = !DILocation(line: 841, column: 9, scope: !219)
!1977 = !DILocation(line: 842, column: 9, scope: !1978)
!1978 = distinct !DILexicalBlock(scope: !1979, file: !1, line: 842, column: 9)
!1979 = distinct !DILexicalBlock(scope: !1973, file: !1, line: 841, column: 23)
!1980 = !DILocation(line: 843, column: 9, scope: !1981)
!1981 = distinct !DILexicalBlock(scope: !1979, file: !1, line: 843, column: 9)
!1982 = !DILocation(line: 844, column: 9, scope: !1983)
!1983 = distinct !DILexicalBlock(scope: !1979, file: !1, line: 844, column: 9)
!1984 = !DILocation(line: 845, column: 9, scope: !1985)
!1985 = distinct !DILexicalBlock(scope: !1979, file: !1, line: 845, column: 9)
!1986 = !DILocation(line: 846, column: 9, scope: !1987)
!1987 = distinct !DILexicalBlock(scope: !1979, file: !1, line: 846, column: 9)
!1988 = !DILocation(line: 847, column: 9, scope: !1989)
!1989 = distinct !DILexicalBlock(scope: !1979, file: !1, line: 847, column: 9)
!1990 = !DILocation(line: 848, column: 9, scope: !1991)
!1991 = distinct !DILexicalBlock(scope: !1979, file: !1, line: 848, column: 9)
!1992 = !DILocation(line: 849, column: 9, scope: !1993)
!1993 = distinct !DILexicalBlock(scope: !1979, file: !1, line: 849, column: 9)
!1994 = !DILocation(line: 850, column: 5, scope: !1979)
!1995 = !DILocation(line: 854, column: 21, scope: !1996)
!1996 = distinct !DILexicalBlock(scope: !1973, file: !1, line: 853, column: 5)
!1997 = !DILocation(line: 854, column: 31, scope: !1996)
!1998 = !DILocation(line: 854, column: 37, scope: !1996)
!1999 = !DILocation(line: 854, column: 43, scope: !1996)
!2000 = !DILocation(line: 854, column: 24, scope: !1996)
!2001 = !DILocation(line: 854, column: 9, scope: !1996)
!2002 = !DILocation(line: 855, column: 21, scope: !1996)
!2003 = !DILocation(line: 855, column: 31, scope: !1996)
!2004 = !DILocation(line: 855, column: 37, scope: !1996)
!2005 = !DILocation(line: 855, column: 43, scope: !1996)
!2006 = !DILocation(line: 855, column: 24, scope: !1996)
!2007 = !DILocation(line: 855, column: 9, scope: !1996)
!2008 = !DILocation(line: 857, column: 19, scope: !219)
!2009 = !DILocation(line: 857, column: 5, scope: !219)
!2010 = !DILocation(line: 861, column: 9, scope: !2011)
!2011 = distinct !DILexicalBlock(scope: !219, file: !1, line: 861, column: 9)
!2012 = !DILocation(line: 861, column: 12, scope: !2011)
!2013 = !DILocation(line: 861, column: 17, scope: !2011)
!2014 = !DILocation(line: 861, column: 9, scope: !219)
!2015 = !DILocation(line: 861, column: 33, scope: !2016)
!2016 = !DILexicalBlockFile(scope: !2011, file: !1, discriminator: 1)
!2017 = !DILocation(line: 861, column: 36, scope: !2016)
!2018 = !DILocation(line: 861, column: 32, scope: !2016)
!2019 = !DILocation(line: 861, column: 22, scope: !2016)
!2020 = !DILocation(line: 861, column: 25, scope: !2016)
!2021 = !DILocation(line: 861, column: 30, scope: !2016)
!2022 = !DILocation(line: 862, column: 12, scope: !219)
!2023 = !DILocation(line: 862, column: 15, scope: !219)
!2024 = !DILocation(line: 862, column: 23, scope: !219)
!2025 = !DILocation(line: 862, column: 5, scope: !219)
!2026 = !DILocation(line: 863, column: 1, scope: !219)
!2027 = !DILocalVariable(name: "strm", arg: 1, scope: !213, file: !1, line: 462, type: !30)
!2028 = !DILocation(line: 462, column: 15, scope: !213)
!2029 = !DILocalVariable(name: "good_length", arg: 2, scope: !213, file: !1, line: 463, type: !56)
!2030 = !DILocation(line: 463, column: 9, scope: !213)
!2031 = !DILocalVariable(name: "max_lazy", arg: 3, scope: !213, file: !1, line: 464, type: !56)
!2032 = !DILocation(line: 464, column: 9, scope: !213)
!2033 = !DILocalVariable(name: "nice_length", arg: 4, scope: !213, file: !1, line: 465, type: !56)
!2034 = !DILocation(line: 465, column: 9, scope: !213)
!2035 = !DILocalVariable(name: "max_chain", arg: 5, scope: !213, file: !1, line: 466, type: !56)
!2036 = !DILocation(line: 466, column: 9, scope: !213)
!2037 = !DILocalVariable(name: "s", scope: !213, file: !1, line: 468, type: !24)
!2038 = !DILocation(line: 468, column: 20, scope: !213)
!2039 = !DILocation(line: 470, column: 9, scope: !2040)
!2040 = distinct !DILexicalBlock(scope: !213, file: !1, line: 470, column: 9)
!2041 = !DILocation(line: 470, column: 14, scope: !2040)
!2042 = !DILocation(line: 470, column: 24, scope: !2040)
!2043 = !DILocation(line: 470, column: 27, scope: !2044)
!2044 = !DILexicalBlockFile(scope: !2040, file: !1, discriminator: 1)
!2045 = !DILocation(line: 470, column: 33, scope: !2044)
!2046 = !DILocation(line: 470, column: 39, scope: !2044)
!2047 = !DILocation(line: 470, column: 9, scope: !2044)
!2048 = !DILocation(line: 470, column: 50, scope: !2049)
!2049 = !DILexicalBlockFile(scope: !2040, file: !1, discriminator: 2)
!2050 = !DILocation(line: 471, column: 9, scope: !213)
!2051 = !DILocation(line: 471, column: 15, scope: !213)
!2052 = !DILocation(line: 471, column: 7, scope: !213)
!2053 = !DILocation(line: 472, column: 21, scope: !213)
!2054 = !DILocation(line: 472, column: 5, scope: !213)
!2055 = !DILocation(line: 472, column: 8, scope: !213)
!2056 = !DILocation(line: 472, column: 19, scope: !213)
!2057 = !DILocation(line: 473, column: 25, scope: !213)
!2058 = !DILocation(line: 473, column: 5, scope: !213)
!2059 = !DILocation(line: 473, column: 8, scope: !213)
!2060 = !DILocation(line: 473, column: 23, scope: !213)
!2061 = !DILocation(line: 474, column: 21, scope: !213)
!2062 = !DILocation(line: 474, column: 5, scope: !213)
!2063 = !DILocation(line: 474, column: 8, scope: !213)
!2064 = !DILocation(line: 474, column: 19, scope: !213)
!2065 = !DILocation(line: 475, column: 27, scope: !213)
!2066 = !DILocation(line: 475, column: 5, scope: !213)
!2067 = !DILocation(line: 475, column: 8, scope: !213)
!2068 = !DILocation(line: 475, column: 25, scope: !213)
!2069 = !DILocation(line: 476, column: 5, scope: !213)
!2070 = !DILocation(line: 477, column: 1, scope: !213)
!2071 = !DILocalVariable(name: "strm", arg: 1, scope: !216, file: !1, line: 497, type: !30)
!2072 = !DILocation(line: 497, column: 15, scope: !216)
!2073 = !DILocalVariable(name: "sourceLen", arg: 2, scope: !216, file: !1, line: 498, type: !42)
!2074 = !DILocation(line: 498, column: 11, scope: !216)
!2075 = !DILocalVariable(name: "s", scope: !216, file: !1, line: 500, type: !24)
!2076 = !DILocation(line: 500, column: 20, scope: !216)
!2077 = !DILocalVariable(name: "destLen", scope: !216, file: !1, line: 501, type: !42)
!2078 = !DILocation(line: 501, column: 11, scope: !216)
!2079 = !DILocation(line: 504, column: 15, scope: !216)
!2080 = !DILocation(line: 505, column: 17, scope: !216)
!2081 = !DILocation(line: 505, column: 27, scope: !216)
!2082 = !DILocation(line: 505, column: 32, scope: !216)
!2083 = !DILocation(line: 504, column: 25, scope: !216)
!2084 = !DILocation(line: 505, column: 42, scope: !216)
!2085 = !DILocation(line: 505, column: 52, scope: !216)
!2086 = !DILocation(line: 505, column: 58, scope: !216)
!2087 = !DILocation(line: 505, column: 38, scope: !216)
!2088 = !DILocation(line: 505, column: 64, scope: !216)
!2089 = !DILocation(line: 504, column: 13, scope: !216)
!2090 = !DILocation(line: 508, column: 9, scope: !2091)
!2091 = distinct !DILexicalBlock(scope: !216, file: !1, line: 508, column: 9)
!2092 = !DILocation(line: 508, column: 14, scope: !2091)
!2093 = !DILocation(line: 508, column: 24, scope: !2091)
!2094 = !DILocation(line: 508, column: 27, scope: !2095)
!2095 = !DILexicalBlockFile(scope: !2091, file: !1, discriminator: 1)
!2096 = !DILocation(line: 508, column: 33, scope: !2095)
!2097 = !DILocation(line: 508, column: 39, scope: !2095)
!2098 = !DILocation(line: 508, column: 9, scope: !2095)
!2099 = !DILocation(line: 509, column: 16, scope: !2091)
!2100 = !DILocation(line: 509, column: 9, scope: !2091)
!2101 = !DILocation(line: 512, column: 9, scope: !216)
!2102 = !DILocation(line: 512, column: 15, scope: !216)
!2103 = !DILocation(line: 512, column: 7, scope: !216)
!2104 = !DILocation(line: 513, column: 9, scope: !2105)
!2105 = distinct !DILexicalBlock(scope: !216, file: !1, line: 513, column: 9)
!2106 = !DILocation(line: 513, column: 12, scope: !2105)
!2107 = !DILocation(line: 513, column: 19, scope: !2105)
!2108 = !DILocation(line: 513, column: 25, scope: !2105)
!2109 = !DILocation(line: 513, column: 28, scope: !2110)
!2110 = !DILexicalBlockFile(scope: !2105, file: !1, discriminator: 1)
!2111 = !DILocation(line: 513, column: 31, scope: !2110)
!2112 = !DILocation(line: 513, column: 41, scope: !2110)
!2113 = !DILocation(line: 513, column: 9, scope: !2110)
!2114 = !DILocation(line: 514, column: 16, scope: !2105)
!2115 = !DILocation(line: 514, column: 9, scope: !2105)
!2116 = !DILocation(line: 517, column: 26, scope: !216)
!2117 = !DILocation(line: 517, column: 12, scope: !216)
!2118 = !DILocation(line: 517, column: 5, scope: !216)
!2119 = !DILocation(line: 518, column: 1, scope: !216)
!2120 = !DILocalVariable(name: "s", arg: 1, scope: !242, file: !1, line: 526, type: !24)
!2121 = !DILocation(line: 526, column: 20, scope: !242)
!2122 = !DILocalVariable(name: "b", arg: 2, scope: !242, file: !1, line: 527, type: !18)
!2123 = !DILocation(line: 527, column: 10, scope: !242)
!2124 = !DILocation(line: 529, column: 5, scope: !2125)
!2125 = distinct !DILexicalBlock(scope: !242, file: !1, line: 529, column: 5)
!2126 = !DILocation(line: 530, column: 5, scope: !2127)
!2127 = distinct !DILexicalBlock(scope: !242, file: !1, line: 530, column: 5)
!2128 = !DILocation(line: 531, column: 1, scope: !242)
!2129 = !DILocalVariable(name: "strm", arg: 1, scope: !245, file: !1, line: 540, type: !30)
!2130 = !DILocation(line: 540, column: 15, scope: !245)
!2131 = !DILocalVariable(name: "len", scope: !245, file: !1, line: 542, type: !19)
!2132 = !DILocation(line: 542, column: 14, scope: !245)
!2133 = !DILocation(line: 542, column: 20, scope: !245)
!2134 = !DILocation(line: 542, column: 26, scope: !245)
!2135 = !DILocation(line: 542, column: 33, scope: !245)
!2136 = !DILocation(line: 544, column: 9, scope: !2137)
!2137 = distinct !DILexicalBlock(scope: !245, file: !1, line: 544, column: 9)
!2138 = !DILocation(line: 544, column: 15, scope: !2137)
!2139 = !DILocation(line: 544, column: 21, scope: !2137)
!2140 = !DILocation(line: 544, column: 13, scope: !2137)
!2141 = !DILocation(line: 544, column: 9, scope: !245)
!2142 = !DILocation(line: 544, column: 38, scope: !2143)
!2143 = !DILexicalBlockFile(scope: !2137, file: !1, discriminator: 1)
!2144 = !DILocation(line: 544, column: 44, scope: !2143)
!2145 = !DILocation(line: 544, column: 36, scope: !2143)
!2146 = !DILocation(line: 544, column: 32, scope: !2143)
!2147 = !DILocation(line: 545, column: 9, scope: !2148)
!2148 = distinct !DILexicalBlock(scope: !245, file: !1, line: 545, column: 9)
!2149 = !DILocation(line: 545, column: 13, scope: !2148)
!2150 = !DILocation(line: 545, column: 9, scope: !245)
!2151 = !DILocation(line: 545, column: 19, scope: !2152)
!2152 = !DILexicalBlockFile(scope: !2148, file: !1, discriminator: 1)
!2153 = !DILocation(line: 547, column: 13, scope: !245)
!2154 = !DILocation(line: 547, column: 19, scope: !245)
!2155 = !DILocation(line: 547, column: 29, scope: !245)
!2156 = !DILocation(line: 547, column: 35, scope: !245)
!2157 = !DILocation(line: 547, column: 42, scope: !245)
!2158 = !DILocation(line: 547, column: 55, scope: !245)
!2159 = !DILocation(line: 547, column: 5, scope: !245)
!2160 = !DILocation(line: 548, column: 24, scope: !245)
!2161 = !DILocation(line: 548, column: 5, scope: !245)
!2162 = !DILocation(line: 548, column: 11, scope: !245)
!2163 = !DILocation(line: 548, column: 21, scope: !245)
!2164 = !DILocation(line: 549, column: 34, scope: !245)
!2165 = !DILocation(line: 549, column: 5, scope: !245)
!2166 = !DILocation(line: 549, column: 11, scope: !245)
!2167 = !DILocation(line: 549, column: 18, scope: !245)
!2168 = !DILocation(line: 549, column: 31, scope: !245)
!2169 = !DILocation(line: 550, column: 24, scope: !245)
!2170 = !DILocation(line: 550, column: 5, scope: !245)
!2171 = !DILocation(line: 550, column: 11, scope: !245)
!2172 = !DILocation(line: 550, column: 21, scope: !245)
!2173 = !DILocation(line: 551, column: 25, scope: !245)
!2174 = !DILocation(line: 551, column: 5, scope: !245)
!2175 = !DILocation(line: 551, column: 11, scope: !245)
!2176 = !DILocation(line: 551, column: 22, scope: !245)
!2177 = !DILocation(line: 552, column: 29, scope: !245)
!2178 = !DILocation(line: 552, column: 5, scope: !245)
!2179 = !DILocation(line: 552, column: 11, scope: !245)
!2180 = !DILocation(line: 552, column: 18, scope: !245)
!2181 = !DILocation(line: 552, column: 26, scope: !245)
!2182 = !DILocation(line: 553, column: 9, scope: !2183)
!2183 = distinct !DILexicalBlock(scope: !245, file: !1, line: 553, column: 9)
!2184 = !DILocation(line: 553, column: 15, scope: !2183)
!2185 = !DILocation(line: 553, column: 22, scope: !2183)
!2186 = !DILocation(line: 553, column: 30, scope: !2183)
!2187 = !DILocation(line: 553, column: 9, scope: !245)
!2188 = !DILocation(line: 554, column: 36, scope: !2189)
!2189 = distinct !DILexicalBlock(scope: !2183, file: !1, line: 553, column: 36)
!2190 = !DILocation(line: 554, column: 42, scope: !2189)
!2191 = !DILocation(line: 554, column: 49, scope: !2189)
!2192 = !DILocation(line: 554, column: 9, scope: !2189)
!2193 = !DILocation(line: 554, column: 15, scope: !2189)
!2194 = !DILocation(line: 554, column: 22, scope: !2189)
!2195 = !DILocation(line: 554, column: 34, scope: !2189)
!2196 = !DILocation(line: 555, column: 5, scope: !2189)
!2197 = !DILocation(line: 556, column: 1, scope: !245)
!2198 = !DILocalVariable(name: "dest", arg: 1, scope: !223, file: !1, line: 902, type: !30)
!2199 = !DILocation(line: 902, column: 15, scope: !223)
!2200 = !DILocalVariable(name: "source", arg: 2, scope: !223, file: !1, line: 903, type: !30)
!2201 = !DILocation(line: 903, column: 15, scope: !223)
!2202 = !DILocalVariable(name: "ds", scope: !223, file: !1, line: 908, type: !24)
!2203 = !DILocation(line: 908, column: 20, scope: !223)
!2204 = !DILocalVariable(name: "ss", scope: !223, file: !1, line: 909, type: !24)
!2205 = !DILocation(line: 909, column: 20, scope: !223)
!2206 = !DILocalVariable(name: "overlay", scope: !223, file: !1, line: 910, type: !178)
!2207 = !DILocation(line: 910, column: 11, scope: !223)
!2208 = !DILocation(line: 913, column: 9, scope: !2209)
!2209 = distinct !DILexicalBlock(scope: !223, file: !1, line: 913, column: 9)
!2210 = !DILocation(line: 913, column: 16, scope: !2209)
!2211 = !DILocation(line: 913, column: 26, scope: !2209)
!2212 = !DILocation(line: 913, column: 29, scope: !2213)
!2213 = !DILexicalBlockFile(scope: !2209, file: !1, discriminator: 1)
!2214 = !DILocation(line: 913, column: 34, scope: !2213)
!2215 = !DILocation(line: 913, column: 44, scope: !2213)
!2216 = !DILocation(line: 913, column: 47, scope: !2217)
!2217 = !DILexicalBlockFile(scope: !2209, file: !1, discriminator: 2)
!2218 = !DILocation(line: 913, column: 55, scope: !2217)
!2219 = !DILocation(line: 913, column: 61, scope: !2217)
!2220 = !DILocation(line: 913, column: 9, scope: !2217)
!2221 = !DILocation(line: 914, column: 9, scope: !2222)
!2222 = distinct !DILexicalBlock(scope: !2209, file: !1, line: 913, column: 72)
!2223 = !DILocation(line: 917, column: 10, scope: !223)
!2224 = !DILocation(line: 917, column: 18, scope: !223)
!2225 = !DILocation(line: 917, column: 8, scope: !223)
!2226 = !DILocation(line: 919, column: 13, scope: !223)
!2227 = !DILocation(line: 919, column: 5, scope: !223)
!2228 = !DILocation(line: 919, column: 19, scope: !223)
!2229 = !DILocation(line: 921, column: 28, scope: !223)
!2230 = !DILocation(line: 921, column: 10, scope: !223)
!2231 = !DILocation(line: 921, column: 8, scope: !223)
!2232 = !DILocation(line: 922, column: 9, scope: !2233)
!2233 = distinct !DILexicalBlock(scope: !223, file: !1, line: 922, column: 9)
!2234 = !DILocation(line: 922, column: 12, scope: !2233)
!2235 = !DILocation(line: 922, column: 9, scope: !223)
!2236 = !DILocation(line: 922, column: 23, scope: !2237)
!2237 = !DILexicalBlockFile(scope: !2233, file: !1, discriminator: 1)
!2238 = !DILocation(line: 923, column: 49, scope: !223)
!2239 = !DILocation(line: 923, column: 5, scope: !223)
!2240 = !DILocation(line: 923, column: 11, scope: !223)
!2241 = !DILocation(line: 923, column: 17, scope: !223)
!2242 = !DILocation(line: 924, column: 13, scope: !223)
!2243 = !DILocation(line: 924, column: 5, scope: !223)
!2244 = !DILocation(line: 924, column: 17, scope: !223)
!2245 = !DILocation(line: 925, column: 16, scope: !223)
!2246 = !DILocation(line: 925, column: 5, scope: !223)
!2247 = !DILocation(line: 925, column: 9, scope: !223)
!2248 = !DILocation(line: 925, column: 14, scope: !223)
!2249 = !DILocation(line: 927, column: 28, scope: !223)
!2250 = !DILocation(line: 927, column: 5, scope: !223)
!2251 = !DILocation(line: 927, column: 9, scope: !223)
!2252 = !DILocation(line: 927, column: 16, scope: !223)
!2253 = !DILocation(line: 928, column: 28, scope: !223)
!2254 = !DILocation(line: 928, column: 18, scope: !223)
!2255 = !DILocation(line: 928, column: 5, scope: !223)
!2256 = !DILocation(line: 928, column: 9, scope: !223)
!2257 = !DILocation(line: 928, column: 16, scope: !223)
!2258 = !DILocation(line: 929, column: 28, scope: !223)
!2259 = !DILocation(line: 929, column: 18, scope: !223)
!2260 = !DILocation(line: 929, column: 5, scope: !223)
!2261 = !DILocation(line: 929, column: 9, scope: !223)
!2262 = !DILocation(line: 929, column: 16, scope: !223)
!2263 = !DILocation(line: 930, column: 24, scope: !223)
!2264 = !DILocation(line: 930, column: 15, scope: !223)
!2265 = !DILocation(line: 930, column: 13, scope: !223)
!2266 = !DILocation(line: 931, column: 32, scope: !223)
!2267 = !DILocation(line: 931, column: 23, scope: !223)
!2268 = !DILocation(line: 931, column: 5, scope: !223)
!2269 = !DILocation(line: 931, column: 9, scope: !223)
!2270 = !DILocation(line: 931, column: 21, scope: !223)
!2271 = !DILocation(line: 933, column: 9, scope: !2272)
!2272 = distinct !DILexicalBlock(scope: !223, file: !1, line: 933, column: 9)
!2273 = !DILocation(line: 933, column: 13, scope: !2272)
!2274 = !DILocation(line: 933, column: 20, scope: !2272)
!2275 = !DILocation(line: 933, column: 30, scope: !2272)
!2276 = !DILocation(line: 933, column: 33, scope: !2277)
!2277 = !DILexicalBlockFile(scope: !2272, file: !1, discriminator: 1)
!2278 = !DILocation(line: 933, column: 37, scope: !2277)
!2279 = !DILocation(line: 933, column: 42, scope: !2277)
!2280 = !DILocation(line: 933, column: 52, scope: !2277)
!2281 = !DILocation(line: 933, column: 55, scope: !2282)
!2282 = !DILexicalBlockFile(scope: !2272, file: !1, discriminator: 2)
!2283 = !DILocation(line: 933, column: 59, scope: !2282)
!2284 = !DILocation(line: 933, column: 64, scope: !2282)
!2285 = !DILocation(line: 933, column: 74, scope: !2282)
!2286 = !DILocation(line: 934, column: 9, scope: !2272)
!2287 = !DILocation(line: 934, column: 13, scope: !2272)
!2288 = !DILocation(line: 934, column: 25, scope: !2272)
!2289 = !DILocation(line: 933, column: 9, scope: !2290)
!2290 = !DILexicalBlockFile(scope: !223, file: !1, discriminator: 3)
!2291 = !DILocation(line: 935, column: 21, scope: !2292)
!2292 = distinct !DILexicalBlock(scope: !2272, file: !1, line: 934, column: 36)
!2293 = !DILocation(line: 935, column: 9, scope: !2292)
!2294 = !DILocation(line: 936, column: 9, scope: !2292)
!2295 = !DILocation(line: 939, column: 13, scope: !223)
!2296 = !DILocation(line: 939, column: 17, scope: !223)
!2297 = !DILocation(line: 939, column: 25, scope: !223)
!2298 = !DILocation(line: 939, column: 29, scope: !223)
!2299 = !DILocation(line: 939, column: 37, scope: !223)
!2300 = !DILocation(line: 939, column: 41, scope: !223)
!2301 = !DILocation(line: 939, column: 48, scope: !223)
!2302 = !DILocation(line: 939, column: 52, scope: !223)
!2303 = !DILocation(line: 939, column: 5, scope: !223)
!2304 = !DILocation(line: 940, column: 13, scope: !223)
!2305 = !DILocation(line: 940, column: 17, scope: !223)
!2306 = !DILocation(line: 940, column: 5, scope: !223)
!2307 = !DILocation(line: 940, column: 23, scope: !223)
!2308 = !DILocation(line: 940, column: 27, scope: !223)
!2309 = !DILocation(line: 940, column: 33, scope: !223)
!2310 = !DILocation(line: 940, column: 37, scope: !223)
!2311 = !DILocation(line: 940, column: 44, scope: !223)
!2312 = !DILocation(line: 941, column: 13, scope: !223)
!2313 = !DILocation(line: 941, column: 17, scope: !223)
!2314 = !DILocation(line: 941, column: 5, scope: !223)
!2315 = !DILocation(line: 941, column: 23, scope: !223)
!2316 = !DILocation(line: 941, column: 27, scope: !223)
!2317 = !DILocation(line: 941, column: 33, scope: !223)
!2318 = !DILocation(line: 941, column: 37, scope: !223)
!2319 = !DILocation(line: 941, column: 47, scope: !223)
!2320 = !DILocation(line: 942, column: 13, scope: !223)
!2321 = !DILocation(line: 942, column: 17, scope: !223)
!2322 = !DILocation(line: 942, column: 30, scope: !223)
!2323 = !DILocation(line: 942, column: 34, scope: !223)
!2324 = !DILocation(line: 942, column: 53, scope: !223)
!2325 = !DILocation(line: 942, column: 57, scope: !223)
!2326 = !DILocation(line: 942, column: 47, scope: !223)
!2327 = !DILocation(line: 942, column: 5, scope: !223)
!2328 = !DILocation(line: 944, column: 23, scope: !223)
!2329 = !DILocation(line: 944, column: 27, scope: !223)
!2330 = !DILocation(line: 944, column: 42, scope: !223)
!2331 = !DILocation(line: 944, column: 46, scope: !223)
!2332 = !DILocation(line: 944, column: 60, scope: !223)
!2333 = !DILocation(line: 944, column: 64, scope: !223)
!2334 = !DILocation(line: 944, column: 58, scope: !223)
!2335 = !DILocation(line: 944, column: 39, scope: !223)
!2336 = !DILocation(line: 944, column: 5, scope: !223)
!2337 = !DILocation(line: 944, column: 9, scope: !223)
!2338 = !DILocation(line: 944, column: 21, scope: !223)
!2339 = !DILocation(line: 945, column: 17, scope: !223)
!2340 = !DILocation(line: 945, column: 27, scope: !223)
!2341 = !DILocation(line: 945, column: 31, scope: !223)
!2342 = !DILocation(line: 945, column: 42, scope: !223)
!2343 = !DILocation(line: 945, column: 25, scope: !223)
!2344 = !DILocation(line: 945, column: 5, scope: !223)
!2345 = !DILocation(line: 945, column: 9, scope: !223)
!2346 = !DILocation(line: 945, column: 15, scope: !223)
!2347 = !DILocation(line: 946, column: 17, scope: !223)
!2348 = !DILocation(line: 946, column: 21, scope: !223)
!2349 = !DILocation(line: 946, column: 51, scope: !223)
!2350 = !DILocation(line: 946, column: 55, scope: !223)
!2351 = !DILocation(line: 946, column: 50, scope: !223)
!2352 = !DILocation(line: 946, column: 33, scope: !223)
!2353 = !DILocation(line: 946, column: 5, scope: !223)
!2354 = !DILocation(line: 946, column: 9, scope: !223)
!2355 = !DILocation(line: 946, column: 15, scope: !223)
!2356 = !DILocation(line: 948, column: 27, scope: !223)
!2357 = !DILocation(line: 948, column: 31, scope: !223)
!2358 = !DILocation(line: 948, column: 5, scope: !223)
!2359 = !DILocation(line: 948, column: 9, scope: !223)
!2360 = !DILocation(line: 948, column: 16, scope: !223)
!2361 = !DILocation(line: 948, column: 25, scope: !223)
!2362 = !DILocation(line: 949, column: 27, scope: !223)
!2363 = !DILocation(line: 949, column: 31, scope: !223)
!2364 = !DILocation(line: 949, column: 5, scope: !223)
!2365 = !DILocation(line: 949, column: 9, scope: !223)
!2366 = !DILocation(line: 949, column: 16, scope: !223)
!2367 = !DILocation(line: 949, column: 25, scope: !223)
!2368 = !DILocation(line: 950, column: 28, scope: !223)
!2369 = !DILocation(line: 950, column: 32, scope: !223)
!2370 = !DILocation(line: 950, column: 5, scope: !223)
!2371 = !DILocation(line: 950, column: 9, scope: !223)
!2372 = !DILocation(line: 950, column: 17, scope: !223)
!2373 = !DILocation(line: 950, column: 26, scope: !223)
!2374 = !DILocation(line: 952, column: 5, scope: !223)
!2375 = !DILocation(line: 954, column: 1, scope: !223)
!2376 = !DILocalVariable(name: "s", arg: 1, scope: !226, file: !1, line: 1398, type: !24)
!2377 = !DILocation(line: 1398, column: 20, scope: !226)
!2378 = !DILocalVariable(name: "flush", arg: 2, scope: !226, file: !1, line: 1399, type: !56)
!2379 = !DILocation(line: 1399, column: 9, scope: !226)
!2380 = !DILocalVariable(name: "max_block_size", scope: !226, file: !1, line: 1404, type: !62)
!2381 = !DILocation(line: 1404, column: 9, scope: !226)
!2382 = !DILocalVariable(name: "max_start", scope: !226, file: !1, line: 1405, type: !62)
!2383 = !DILocation(line: 1405, column: 9, scope: !226)
!2384 = !DILocation(line: 1407, column: 9, scope: !2385)
!2385 = distinct !DILexicalBlock(scope: !226, file: !1, line: 1407, column: 9)
!2386 = !DILocation(line: 1407, column: 26, scope: !2385)
!2387 = !DILocation(line: 1407, column: 29, scope: !2385)
!2388 = !DILocation(line: 1407, column: 46, scope: !2385)
!2389 = !DILocation(line: 1407, column: 24, scope: !2385)
!2390 = !DILocation(line: 1407, column: 9, scope: !226)
!2391 = !DILocation(line: 1408, column: 26, scope: !2392)
!2392 = distinct !DILexicalBlock(scope: !2385, file: !1, line: 1407, column: 51)
!2393 = !DILocation(line: 1408, column: 29, scope: !2392)
!2394 = !DILocation(line: 1408, column: 46, scope: !2392)
!2395 = !DILocation(line: 1408, column: 24, scope: !2392)
!2396 = !DILocation(line: 1409, column: 5, scope: !2392)
!2397 = !DILocation(line: 1412, column: 5, scope: !226)
!2398 = !DILocation(line: 1414, column: 13, scope: !2399)
!2399 = distinct !DILexicalBlock(scope: !2400, file: !1, line: 1414, column: 13)
!2400 = distinct !DILexicalBlock(scope: !2401, file: !1, line: 1412, column: 14)
!2401 = distinct !DILexicalBlock(scope: !2402, file: !1, line: 1412, column: 5)
!2402 = distinct !DILexicalBlock(scope: !226, file: !1, line: 1412, column: 5)
!2403 = !DILocation(line: 1414, column: 16, scope: !2399)
!2404 = !DILocation(line: 1414, column: 26, scope: !2399)
!2405 = !DILocation(line: 1414, column: 13, scope: !2400)
!2406 = !DILocation(line: 1419, column: 25, scope: !2407)
!2407 = distinct !DILexicalBlock(scope: !2399, file: !1, line: 1414, column: 32)
!2408 = !DILocation(line: 1419, column: 13, scope: !2407)
!2409 = !DILocation(line: 1420, column: 17, scope: !2410)
!2410 = distinct !DILexicalBlock(scope: !2407, file: !1, line: 1420, column: 17)
!2411 = !DILocation(line: 1420, column: 20, scope: !2410)
!2412 = !DILocation(line: 1420, column: 30, scope: !2410)
!2413 = !DILocation(line: 1420, column: 35, scope: !2410)
!2414 = !DILocation(line: 1420, column: 38, scope: !2415)
!2415 = !DILexicalBlockFile(scope: !2410, file: !1, discriminator: 1)
!2416 = !DILocation(line: 1420, column: 44, scope: !2415)
!2417 = !DILocation(line: 1420, column: 17, scope: !2415)
!2418 = !DILocation(line: 1420, column: 59, scope: !2419)
!2419 = !DILexicalBlockFile(scope: !2410, file: !1, discriminator: 2)
!2420 = !DILocation(line: 1422, column: 17, scope: !2421)
!2421 = distinct !DILexicalBlock(scope: !2407, file: !1, line: 1422, column: 17)
!2422 = !DILocation(line: 1422, column: 20, scope: !2421)
!2423 = !DILocation(line: 1422, column: 30, scope: !2421)
!2424 = !DILocation(line: 1422, column: 17, scope: !2407)
!2425 = !DILocation(line: 1422, column: 36, scope: !2426)
!2426 = !DILexicalBlockFile(scope: !2421, file: !1, discriminator: 1)
!2427 = !DILocation(line: 1423, column: 9, scope: !2407)
!2428 = !DILocation(line: 1426, column: 24, scope: !2400)
!2429 = !DILocation(line: 1426, column: 27, scope: !2400)
!2430 = !DILocation(line: 1426, column: 9, scope: !2400)
!2431 = !DILocation(line: 1426, column: 12, scope: !2400)
!2432 = !DILocation(line: 1426, column: 21, scope: !2400)
!2433 = !DILocation(line: 1427, column: 9, scope: !2400)
!2434 = !DILocation(line: 1427, column: 12, scope: !2400)
!2435 = !DILocation(line: 1427, column: 22, scope: !2400)
!2436 = !DILocation(line: 1430, column: 21, scope: !2400)
!2437 = !DILocation(line: 1430, column: 24, scope: !2400)
!2438 = !DILocation(line: 1430, column: 38, scope: !2400)
!2439 = !DILocation(line: 1430, column: 36, scope: !2400)
!2440 = !DILocation(line: 1430, column: 19, scope: !2400)
!2441 = !DILocation(line: 1431, column: 13, scope: !2442)
!2442 = distinct !DILexicalBlock(scope: !2400, file: !1, line: 1431, column: 13)
!2443 = !DILocation(line: 1431, column: 16, scope: !2442)
!2444 = !DILocation(line: 1431, column: 25, scope: !2442)
!2445 = !DILocation(line: 1431, column: 30, scope: !2442)
!2446 = !DILocation(line: 1431, column: 38, scope: !2447)
!2447 = !DILexicalBlockFile(scope: !2442, file: !1, discriminator: 1)
!2448 = !DILocation(line: 1431, column: 41, scope: !2447)
!2449 = !DILocation(line: 1431, column: 33, scope: !2447)
!2450 = !DILocation(line: 1431, column: 53, scope: !2447)
!2451 = !DILocation(line: 1431, column: 50, scope: !2447)
!2452 = !DILocation(line: 1431, column: 13, scope: !2447)
!2453 = !DILocation(line: 1433, column: 35, scope: !2454)
!2454 = distinct !DILexicalBlock(scope: !2442, file: !1, line: 1431, column: 64)
!2455 = !DILocation(line: 1433, column: 38, scope: !2454)
!2456 = !DILocation(line: 1433, column: 49, scope: !2454)
!2457 = !DILocation(line: 1433, column: 47, scope: !2454)
!2458 = !DILocation(line: 1433, column: 28, scope: !2454)
!2459 = !DILocation(line: 1433, column: 13, scope: !2454)
!2460 = !DILocation(line: 1433, column: 16, scope: !2454)
!2461 = !DILocation(line: 1433, column: 26, scope: !2454)
!2462 = !DILocation(line: 1434, column: 33, scope: !2454)
!2463 = !DILocation(line: 1434, column: 27, scope: !2454)
!2464 = !DILocation(line: 1434, column: 13, scope: !2454)
!2465 = !DILocation(line: 1434, column: 16, scope: !2454)
!2466 = !DILocation(line: 1434, column: 25, scope: !2454)
!2467 = !DILocation(line: 1435, column: 13, scope: !2468)
!2468 = distinct !DILexicalBlock(scope: !2469, file: !1, line: 1435, column: 13)
!2469 = distinct !DILexicalBlock(scope: !2454, file: !1, line: 1435, column: 13)
!2470 = !DILocation(line: 1435, column: 13, scope: !2471)
!2471 = !DILexicalBlockFile(scope: !2468, file: !1, discriminator: 1)
!2472 = !DILocation(line: 1435, column: 13, scope: !2473)
!2473 = !DILexicalBlockFile(scope: !2468, file: !1, discriminator: 2)
!2474 = !DILocation(line: 1435, column: 13, scope: !2475)
!2475 = !DILexicalBlockFile(scope: !2468, file: !1, discriminator: 3)
!2476 = !DILocation(line: 1435, column: 13, scope: !2477)
!2477 = !DILexicalBlockFile(scope: !2475, file: !1, discriminator: 5)
!2478 = !DILocation(line: 1435, column: 13, scope: !2479)
!2479 = !DILexicalBlockFile(scope: !2480, file: !1, discriminator: 4)
!2480 = distinct !DILexicalBlock(scope: !2469, file: !1, line: 1435, column: 13)
!2481 = !DILocation(line: 1436, column: 9, scope: !2454)
!2482 = !DILocation(line: 1440, column: 13, scope: !2483)
!2483 = distinct !DILexicalBlock(scope: !2400, file: !1, line: 1440, column: 13)
!2484 = !DILocation(line: 1440, column: 16, scope: !2483)
!2485 = !DILocation(line: 1440, column: 33, scope: !2483)
!2486 = !DILocation(line: 1440, column: 36, scope: !2483)
!2487 = !DILocation(line: 1440, column: 27, scope: !2483)
!2488 = !DILocation(line: 1440, column: 25, scope: !2483)
!2489 = !DILocation(line: 1440, column: 51, scope: !2483)
!2490 = !DILocation(line: 1440, column: 48, scope: !2483)
!2491 = !DILocation(line: 1440, column: 13, scope: !2400)
!2492 = !DILocation(line: 1441, column: 13, scope: !2493)
!2493 = distinct !DILexicalBlock(scope: !2494, file: !1, line: 1441, column: 13)
!2494 = distinct !DILexicalBlock(scope: !2495, file: !1, line: 1441, column: 13)
!2495 = distinct !DILexicalBlock(scope: !2483, file: !1, line: 1440, column: 64)
!2496 = !DILocation(line: 1441, column: 13, scope: !2497)
!2497 = !DILexicalBlockFile(scope: !2493, file: !1, discriminator: 1)
!2498 = !DILocation(line: 1441, column: 13, scope: !2499)
!2499 = !DILexicalBlockFile(scope: !2493, file: !1, discriminator: 2)
!2500 = !DILocation(line: 1441, column: 13, scope: !2501)
!2501 = !DILexicalBlockFile(scope: !2493, file: !1, discriminator: 3)
!2502 = !DILocation(line: 1441, column: 13, scope: !2503)
!2503 = !DILexicalBlockFile(scope: !2501, file: !1, discriminator: 5)
!2504 = !DILocation(line: 1441, column: 13, scope: !2505)
!2505 = !DILexicalBlockFile(scope: !2506, file: !1, discriminator: 4)
!2506 = distinct !DILexicalBlock(scope: !2494, file: !1, line: 1441, column: 13)
!2507 = !DILocation(line: 1442, column: 9, scope: !2495)
!2508 = !DILocation(line: 1412, column: 5, scope: !2509)
!2509 = !DILexicalBlockFile(scope: !2401, file: !1, discriminator: 1)
!2510 = !DILocation(line: 1444, column: 5, scope: !2511)
!2511 = distinct !DILexicalBlock(scope: !2512, file: !1, line: 1444, column: 5)
!2512 = distinct !DILexicalBlock(scope: !226, file: !1, line: 1444, column: 5)
!2513 = !DILocation(line: 1444, column: 5, scope: !2514)
!2514 = !DILexicalBlockFile(scope: !2511, file: !1, discriminator: 1)
!2515 = !DILocation(line: 1444, column: 5, scope: !2516)
!2516 = !DILexicalBlockFile(scope: !2511, file: !1, discriminator: 2)
!2517 = !DILocation(line: 1444, column: 5, scope: !2518)
!2518 = !DILexicalBlockFile(scope: !2511, file: !1, discriminator: 3)
!2519 = !DILocation(line: 1444, column: 5, scope: !2520)
!2520 = !DILexicalBlockFile(scope: !2518, file: !1, discriminator: 5)
!2521 = !DILocation(line: 1444, column: 5, scope: !2522)
!2522 = !DILexicalBlockFile(scope: !2523, file: !1, discriminator: 4)
!2523 = distinct !DILexicalBlock(scope: !2512, file: !1, line: 1444, column: 5)
!2524 = !DILocation(line: 1445, column: 12, scope: !226)
!2525 = !DILocation(line: 1445, column: 18, scope: !226)
!2526 = !DILocation(line: 1445, column: 5, scope: !226)
!2527 = !DILocation(line: 1446, column: 1, scope: !226)
!2528 = !DILocalVariable(name: "s", arg: 1, scope: !236, file: !1, line: 1456, type: !24)
!2529 = !DILocation(line: 1456, column: 20, scope: !236)
!2530 = !DILocalVariable(name: "flush", arg: 2, scope: !236, file: !1, line: 1457, type: !56)
!2531 = !DILocation(line: 1457, column: 9, scope: !236)
!2532 = !DILocalVariable(name: "hash_head", scope: !236, file: !1, line: 1459, type: !110)
!2533 = !DILocation(line: 1459, column: 10, scope: !236)
!2534 = !DILocalVariable(name: "bflush", scope: !236, file: !1, line: 1460, type: !56)
!2535 = !DILocation(line: 1460, column: 9, scope: !236)
!2536 = !DILocation(line: 1462, column: 5, scope: !236)
!2537 = !DILocation(line: 1468, column: 13, scope: !2538)
!2538 = distinct !DILexicalBlock(scope: !2539, file: !1, line: 1468, column: 13)
!2539 = distinct !DILexicalBlock(scope: !2540, file: !1, line: 1462, column: 14)
!2540 = distinct !DILexicalBlock(scope: !2541, file: !1, line: 1462, column: 5)
!2541 = distinct !DILexicalBlock(scope: !236, file: !1, line: 1462, column: 5)
!2542 = !DILocation(line: 1468, column: 16, scope: !2538)
!2543 = !DILocation(line: 1468, column: 26, scope: !2538)
!2544 = !DILocation(line: 1468, column: 13, scope: !2539)
!2545 = !DILocation(line: 1469, column: 25, scope: !2546)
!2546 = distinct !DILexicalBlock(scope: !2538, file: !1, line: 1468, column: 43)
!2547 = !DILocation(line: 1469, column: 13, scope: !2546)
!2548 = !DILocation(line: 1470, column: 17, scope: !2549)
!2549 = distinct !DILexicalBlock(scope: !2546, file: !1, line: 1470, column: 17)
!2550 = !DILocation(line: 1470, column: 20, scope: !2549)
!2551 = !DILocation(line: 1470, column: 30, scope: !2549)
!2552 = !DILocation(line: 1470, column: 46, scope: !2549)
!2553 = !DILocation(line: 1470, column: 49, scope: !2554)
!2554 = !DILexicalBlockFile(scope: !2549, file: !1, discriminator: 1)
!2555 = !DILocation(line: 1470, column: 55, scope: !2554)
!2556 = !DILocation(line: 1470, column: 17, scope: !2554)
!2557 = !DILocation(line: 1471, column: 17, scope: !2558)
!2558 = distinct !DILexicalBlock(scope: !2549, file: !1, line: 1470, column: 70)
!2559 = !DILocation(line: 1473, column: 17, scope: !2560)
!2560 = distinct !DILexicalBlock(scope: !2546, file: !1, line: 1473, column: 17)
!2561 = !DILocation(line: 1473, column: 20, scope: !2560)
!2562 = !DILocation(line: 1473, column: 30, scope: !2560)
!2563 = !DILocation(line: 1473, column: 17, scope: !2546)
!2564 = !DILocation(line: 1473, column: 36, scope: !2565)
!2565 = !DILexicalBlockFile(scope: !2560, file: !1, discriminator: 1)
!2566 = !DILocation(line: 1474, column: 9, scope: !2546)
!2567 = !DILocation(line: 1479, column: 13, scope: !2568)
!2568 = distinct !DILexicalBlock(scope: !2539, file: !1, line: 1479, column: 13)
!2569 = !DILocation(line: 1479, column: 16, scope: !2568)
!2570 = !DILocation(line: 1479, column: 26, scope: !2568)
!2571 = !DILocation(line: 1479, column: 13, scope: !2539)
!2572 = !DILocation(line: 1480, column: 13, scope: !2573)
!2573 = distinct !DILexicalBlock(scope: !2568, file: !1, line: 1479, column: 40)
!2574 = !DILocation(line: 1481, column: 9, scope: !2573)
!2575 = !DILocation(line: 1486, column: 13, scope: !2576)
!2576 = distinct !DILexicalBlock(scope: !2539, file: !1, line: 1486, column: 13)
!2577 = !DILocation(line: 1486, column: 23, scope: !2576)
!2578 = !DILocation(line: 1486, column: 30, scope: !2576)
!2579 = !DILocation(line: 1486, column: 33, scope: !2580)
!2580 = !DILexicalBlockFile(scope: !2576, file: !1, discriminator: 1)
!2581 = !DILocation(line: 1486, column: 36, scope: !2580)
!2582 = !DILocation(line: 1486, column: 47, scope: !2580)
!2583 = !DILocation(line: 1486, column: 45, scope: !2580)
!2584 = !DILocation(line: 1486, column: 60, scope: !2580)
!2585 = !DILocation(line: 1486, column: 57, scope: !2580)
!2586 = !DILocation(line: 1486, column: 13, scope: !2580)
!2587 = !DILocation(line: 1497, column: 17, scope: !2588)
!2588 = distinct !DILexicalBlock(scope: !2589, file: !1, line: 1497, column: 17)
!2589 = distinct !DILexicalBlock(scope: !2576, file: !1, line: 1486, column: 73)
!2590 = !DILocation(line: 1497, column: 20, scope: !2588)
!2591 = !DILocation(line: 1497, column: 29, scope: !2588)
!2592 = !DILocation(line: 1497, column: 47, scope: !2588)
!2593 = !DILocation(line: 1497, column: 50, scope: !2594)
!2594 = !DILexicalBlockFile(scope: !2588, file: !1, discriminator: 1)
!2595 = !DILocation(line: 1497, column: 53, scope: !2594)
!2596 = !DILocation(line: 1497, column: 62, scope: !2594)
!2597 = !DILocation(line: 1497, column: 17, scope: !2594)
!2598 = !DILocation(line: 1498, column: 50, scope: !2599)
!2599 = distinct !DILexicalBlock(scope: !2588, file: !1, line: 1497, column: 72)
!2600 = !DILocation(line: 1498, column: 53, scope: !2599)
!2601 = !DILocation(line: 1498, column: 35, scope: !2599)
!2602 = !DILocation(line: 1498, column: 17, scope: !2599)
!2603 = !DILocation(line: 1498, column: 20, scope: !2599)
!2604 = !DILocation(line: 1498, column: 33, scope: !2599)
!2605 = !DILocation(line: 1499, column: 13, scope: !2599)
!2606 = !DILocation(line: 1499, column: 24, scope: !2607)
!2607 = !DILexicalBlockFile(scope: !2608, file: !1, discriminator: 1)
!2608 = distinct !DILexicalBlock(scope: !2588, file: !1, line: 1499, column: 24)
!2609 = !DILocation(line: 1499, column: 27, scope: !2607)
!2610 = !DILocation(line: 1499, column: 36, scope: !2607)
!2611 = !DILocation(line: 1499, column: 45, scope: !2607)
!2612 = !DILocation(line: 1499, column: 48, scope: !2613)
!2613 = !DILexicalBlockFile(scope: !2608, file: !1, discriminator: 2)
!2614 = !DILocation(line: 1499, column: 51, scope: !2613)
!2615 = !DILocation(line: 1499, column: 62, scope: !2613)
!2616 = !DILocation(line: 1499, column: 60, scope: !2613)
!2617 = !DILocation(line: 1499, column: 72, scope: !2613)
!2618 = !DILocation(line: 1499, column: 24, scope: !2613)
!2619 = !DILocation(line: 1500, column: 55, scope: !2620)
!2620 = distinct !DILexicalBlock(scope: !2608, file: !1, line: 1499, column: 78)
!2621 = !DILocation(line: 1500, column: 58, scope: !2620)
!2622 = !DILocation(line: 1500, column: 35, scope: !2620)
!2623 = !DILocation(line: 1500, column: 17, scope: !2620)
!2624 = !DILocation(line: 1500, column: 20, scope: !2620)
!2625 = !DILocation(line: 1500, column: 33, scope: !2620)
!2626 = !DILocation(line: 1501, column: 13, scope: !2620)
!2627 = !DILocation(line: 1504, column: 9, scope: !2589)
!2628 = !DILocation(line: 1505, column: 13, scope: !2629)
!2629 = distinct !DILexicalBlock(scope: !2539, file: !1, line: 1505, column: 13)
!2630 = !DILocation(line: 1505, column: 16, scope: !2629)
!2631 = !DILocation(line: 1505, column: 29, scope: !2629)
!2632 = !DILocation(line: 1505, column: 13, scope: !2539)
!2633 = !DILocalVariable(name: "len", scope: !2634, file: !1, line: 1508, type: !171)
!2634 = distinct !DILexicalBlock(scope: !2635, file: !1, line: 1508, column: 13)
!2635 = distinct !DILexicalBlock(scope: !2629, file: !1, line: 1505, column: 43)
!2636 = !DILocation(line: 1508, column: 13, scope: !2634)
!2637 = !DILocalVariable(name: "dist", scope: !2634, file: !1, line: 1508, type: !98)
!2638 = !DILocation(line: 1508, column: 13, scope: !2639)
!2639 = !DILexicalBlockFile(scope: !2634, file: !1, discriminator: 1)
!2640 = !DILocation(line: 1508, column: 13, scope: !2641)
!2641 = !DILexicalBlockFile(scope: !2634, file: !1, discriminator: 2)
!2642 = !DILocation(line: 1508, column: 13, scope: !2643)
!2643 = !DILexicalBlockFile(scope: !2634, file: !1, discriminator: 3)
!2644 = !DILocation(line: 1511, column: 29, scope: !2635)
!2645 = !DILocation(line: 1511, column: 32, scope: !2635)
!2646 = !DILocation(line: 1511, column: 13, scope: !2635)
!2647 = !DILocation(line: 1511, column: 16, scope: !2635)
!2648 = !DILocation(line: 1511, column: 26, scope: !2635)
!2649 = !DILocation(line: 1517, column: 17, scope: !2650)
!2650 = distinct !DILexicalBlock(scope: !2635, file: !1, line: 1517, column: 17)
!2651 = !DILocation(line: 1517, column: 20, scope: !2650)
!2652 = !DILocation(line: 1517, column: 36, scope: !2650)
!2653 = !DILocation(line: 1517, column: 39, scope: !2650)
!2654 = !DILocation(line: 1517, column: 33, scope: !2650)
!2655 = !DILocation(line: 1517, column: 57, scope: !2650)
!2656 = !DILocation(line: 1518, column: 17, scope: !2650)
!2657 = !DILocation(line: 1518, column: 20, scope: !2650)
!2658 = !DILocation(line: 1518, column: 30, scope: !2650)
!2659 = !DILocation(line: 1517, column: 17, scope: !2660)
!2660 = !DILexicalBlockFile(scope: !2635, file: !1, discriminator: 1)
!2661 = !DILocation(line: 1519, column: 17, scope: !2662)
!2662 = distinct !DILexicalBlock(scope: !2650, file: !1, line: 1518, column: 44)
!2663 = !DILocation(line: 1519, column: 20, scope: !2662)
!2664 = !DILocation(line: 1519, column: 32, scope: !2662)
!2665 = !DILocation(line: 1520, column: 17, scope: !2662)
!2666 = !DILocation(line: 1521, column: 21, scope: !2667)
!2667 = distinct !DILexicalBlock(scope: !2662, file: !1, line: 1520, column: 20)
!2668 = !DILocation(line: 1521, column: 24, scope: !2667)
!2669 = !DILocation(line: 1521, column: 32, scope: !2667)
!2670 = !DILocation(line: 1522, column: 21, scope: !2667)
!2671 = !DILocation(line: 1526, column: 17, scope: !2667)
!2672 = !DILocation(line: 1526, column: 28, scope: !2673)
!2673 = !DILexicalBlockFile(scope: !2662, file: !1, discriminator: 1)
!2674 = !DILocation(line: 1526, column: 31, scope: !2673)
!2675 = !DILocation(line: 1526, column: 26, scope: !2673)
!2676 = !DILocation(line: 1526, column: 44, scope: !2673)
!2677 = !DILocation(line: 1526, column: 17, scope: !2673)
!2678 = !DILocation(line: 1527, column: 17, scope: !2662)
!2679 = !DILocation(line: 1527, column: 20, scope: !2662)
!2680 = !DILocation(line: 1527, column: 28, scope: !2662)
!2681 = !DILocation(line: 1528, column: 13, scope: !2662)
!2682 = !DILocation(line: 1531, column: 32, scope: !2683)
!2683 = distinct !DILexicalBlock(scope: !2650, file: !1, line: 1530, column: 13)
!2684 = !DILocation(line: 1531, column: 35, scope: !2683)
!2685 = !DILocation(line: 1531, column: 17, scope: !2683)
!2686 = !DILocation(line: 1531, column: 20, scope: !2683)
!2687 = !DILocation(line: 1531, column: 29, scope: !2683)
!2688 = !DILocation(line: 1532, column: 17, scope: !2683)
!2689 = !DILocation(line: 1532, column: 20, scope: !2683)
!2690 = !DILocation(line: 1532, column: 33, scope: !2683)
!2691 = !DILocation(line: 1533, column: 38, scope: !2683)
!2692 = !DILocation(line: 1533, column: 41, scope: !2683)
!2693 = !DILocation(line: 1533, column: 28, scope: !2683)
!2694 = !DILocation(line: 1533, column: 31, scope: !2683)
!2695 = !DILocation(line: 1533, column: 17, scope: !2683)
!2696 = !DILocation(line: 1533, column: 20, scope: !2683)
!2697 = !DILocation(line: 1533, column: 26, scope: !2683)
!2698 = !DILocation(line: 1534, column: 17, scope: !2683)
!2699 = !DILocation(line: 1542, column: 9, scope: !2635)
!2700 = !DILocalVariable(name: "cc", scope: !2701, file: !1, line: 1545, type: !171)
!2701 = distinct !DILexicalBlock(scope: !2702, file: !1, line: 1545, column: 13)
!2702 = distinct !DILexicalBlock(scope: !2629, file: !1, line: 1542, column: 16)
!2703 = !DILocation(line: 1545, column: 13, scope: !2701)
!2704 = !DILocation(line: 1546, column: 13, scope: !2702)
!2705 = !DILocation(line: 1546, column: 16, scope: !2702)
!2706 = !DILocation(line: 1546, column: 25, scope: !2702)
!2707 = !DILocation(line: 1547, column: 13, scope: !2702)
!2708 = !DILocation(line: 1547, column: 16, scope: !2702)
!2709 = !DILocation(line: 1547, column: 24, scope: !2702)
!2710 = !DILocation(line: 1549, column: 13, scope: !2711)
!2711 = distinct !DILexicalBlock(scope: !2539, file: !1, line: 1549, column: 13)
!2712 = !DILocation(line: 1549, column: 13, scope: !2539)
!2713 = !DILocation(line: 1549, column: 21, scope: !2714)
!2714 = !DILexicalBlockFile(scope: !2715, file: !1, discriminator: 1)
!2715 = distinct !DILexicalBlock(scope: !2716, file: !1, line: 1549, column: 21)
!2716 = distinct !DILexicalBlock(scope: !2711, file: !1, line: 1549, column: 21)
!2717 = !DILocation(line: 1549, column: 21, scope: !2718)
!2718 = !DILexicalBlockFile(scope: !2715, file: !1, discriminator: 2)
!2719 = !DILocation(line: 1549, column: 21, scope: !2720)
!2720 = !DILexicalBlockFile(scope: !2715, file: !1, discriminator: 3)
!2721 = !DILocation(line: 1549, column: 21, scope: !2722)
!2722 = !DILexicalBlockFile(scope: !2715, file: !1, discriminator: 4)
!2723 = !DILocation(line: 1549, column: 21, scope: !2724)
!2724 = !DILexicalBlockFile(scope: !2722, file: !1, discriminator: 7)
!2725 = !DILocation(line: 1549, column: 21, scope: !2726)
!2726 = !DILexicalBlockFile(scope: !2727, file: !1, discriminator: 5)
!2727 = distinct !DILexicalBlock(scope: !2716, file: !1, line: 1549, column: 21)
!2728 = !DILocation(line: 1549, column: 21, scope: !2729)
!2729 = !DILexicalBlockFile(scope: !2716, file: !1, discriminator: 6)
!2730 = !DILocation(line: 1462, column: 5, scope: !2731)
!2731 = !DILexicalBlockFile(scope: !2540, file: !1, discriminator: 1)
!2732 = !DILocation(line: 1551, column: 5, scope: !2733)
!2733 = distinct !DILexicalBlock(scope: !2734, file: !1, line: 1551, column: 5)
!2734 = distinct !DILexicalBlock(scope: !236, file: !1, line: 1551, column: 5)
!2735 = !DILocation(line: 1551, column: 5, scope: !2736)
!2736 = !DILexicalBlockFile(scope: !2733, file: !1, discriminator: 1)
!2737 = !DILocation(line: 1551, column: 5, scope: !2738)
!2738 = !DILexicalBlockFile(scope: !2733, file: !1, discriminator: 2)
!2739 = !DILocation(line: 1551, column: 5, scope: !2740)
!2740 = !DILexicalBlockFile(scope: !2733, file: !1, discriminator: 3)
!2741 = !DILocation(line: 1551, column: 5, scope: !2742)
!2742 = !DILexicalBlockFile(scope: !2740, file: !1, discriminator: 5)
!2743 = !DILocation(line: 1551, column: 5, scope: !2744)
!2744 = !DILexicalBlockFile(scope: !2745, file: !1, discriminator: 4)
!2745 = distinct !DILexicalBlock(scope: !2734, file: !1, line: 1551, column: 5)
!2746 = !DILocation(line: 1552, column: 12, scope: !236)
!2747 = !DILocation(line: 1552, column: 18, scope: !236)
!2748 = !DILocation(line: 1552, column: 5, scope: !236)
!2749 = !DILocation(line: 1553, column: 1, scope: !236)
!2750 = !DILocalVariable(name: "s", arg: 1, scope: !241, file: !1, line: 1562, type: !24)
!2751 = !DILocation(line: 1562, column: 20, scope: !241)
!2752 = !DILocalVariable(name: "flush", arg: 2, scope: !241, file: !1, line: 1563, type: !56)
!2753 = !DILocation(line: 1563, column: 9, scope: !241)
!2754 = !DILocalVariable(name: "hash_head", scope: !241, file: !1, line: 1565, type: !110)
!2755 = !DILocation(line: 1565, column: 10, scope: !241)
!2756 = !DILocalVariable(name: "bflush", scope: !241, file: !1, line: 1566, type: !56)
!2757 = !DILocation(line: 1566, column: 9, scope: !241)
!2758 = !DILocation(line: 1569, column: 5, scope: !241)
!2759 = !DILocation(line: 1575, column: 13, scope: !2760)
!2760 = distinct !DILexicalBlock(scope: !2761, file: !1, line: 1575, column: 13)
!2761 = distinct !DILexicalBlock(scope: !2762, file: !1, line: 1569, column: 14)
!2762 = distinct !DILexicalBlock(scope: !2763, file: !1, line: 1569, column: 5)
!2763 = distinct !DILexicalBlock(scope: !241, file: !1, line: 1569, column: 5)
!2764 = !DILocation(line: 1575, column: 16, scope: !2760)
!2765 = !DILocation(line: 1575, column: 26, scope: !2760)
!2766 = !DILocation(line: 1575, column: 13, scope: !2761)
!2767 = !DILocation(line: 1576, column: 25, scope: !2768)
!2768 = distinct !DILexicalBlock(scope: !2760, file: !1, line: 1575, column: 43)
!2769 = !DILocation(line: 1576, column: 13, scope: !2768)
!2770 = !DILocation(line: 1577, column: 17, scope: !2771)
!2771 = distinct !DILexicalBlock(scope: !2768, file: !1, line: 1577, column: 17)
!2772 = !DILocation(line: 1577, column: 20, scope: !2771)
!2773 = !DILocation(line: 1577, column: 30, scope: !2771)
!2774 = !DILocation(line: 1577, column: 46, scope: !2771)
!2775 = !DILocation(line: 1577, column: 49, scope: !2776)
!2776 = !DILexicalBlockFile(scope: !2771, file: !1, discriminator: 1)
!2777 = !DILocation(line: 1577, column: 55, scope: !2776)
!2778 = !DILocation(line: 1577, column: 17, scope: !2776)
!2779 = !DILocation(line: 1578, column: 17, scope: !2780)
!2780 = distinct !DILexicalBlock(scope: !2771, file: !1, line: 1577, column: 70)
!2781 = !DILocation(line: 1580, column: 17, scope: !2782)
!2782 = distinct !DILexicalBlock(scope: !2768, file: !1, line: 1580, column: 17)
!2783 = !DILocation(line: 1580, column: 20, scope: !2782)
!2784 = !DILocation(line: 1580, column: 30, scope: !2782)
!2785 = !DILocation(line: 1580, column: 17, scope: !2768)
!2786 = !DILocation(line: 1580, column: 36, scope: !2787)
!2787 = !DILexicalBlockFile(scope: !2782, file: !1, discriminator: 1)
!2788 = !DILocation(line: 1581, column: 9, scope: !2768)
!2789 = !DILocation(line: 1586, column: 13, scope: !2790)
!2790 = distinct !DILexicalBlock(scope: !2761, file: !1, line: 1586, column: 13)
!2791 = !DILocation(line: 1586, column: 16, scope: !2790)
!2792 = !DILocation(line: 1586, column: 26, scope: !2790)
!2793 = !DILocation(line: 1586, column: 13, scope: !2761)
!2794 = !DILocation(line: 1587, column: 13, scope: !2795)
!2795 = distinct !DILexicalBlock(scope: !2790, file: !1, line: 1586, column: 40)
!2796 = !DILocation(line: 1588, column: 9, scope: !2795)
!2797 = !DILocation(line: 1592, column: 26, scope: !2761)
!2798 = !DILocation(line: 1592, column: 29, scope: !2761)
!2799 = !DILocation(line: 1592, column: 9, scope: !2761)
!2800 = !DILocation(line: 1592, column: 12, scope: !2761)
!2801 = !DILocation(line: 1592, column: 24, scope: !2761)
!2802 = !DILocation(line: 1592, column: 59, scope: !2761)
!2803 = !DILocation(line: 1592, column: 62, scope: !2761)
!2804 = !DILocation(line: 1592, column: 43, scope: !2761)
!2805 = !DILocation(line: 1592, column: 46, scope: !2761)
!2806 = !DILocation(line: 1592, column: 57, scope: !2761)
!2807 = !DILocation(line: 1593, column: 9, scope: !2761)
!2808 = !DILocation(line: 1593, column: 12, scope: !2761)
!2809 = !DILocation(line: 1593, column: 25, scope: !2761)
!2810 = !DILocation(line: 1595, column: 13, scope: !2811)
!2811 = distinct !DILexicalBlock(scope: !2761, file: !1, line: 1595, column: 13)
!2812 = !DILocation(line: 1595, column: 23, scope: !2811)
!2813 = !DILocation(line: 1595, column: 30, scope: !2811)
!2814 = !DILocation(line: 1595, column: 33, scope: !2815)
!2815 = !DILexicalBlockFile(scope: !2811, file: !1, discriminator: 1)
!2816 = !DILocation(line: 1595, column: 36, scope: !2815)
!2817 = !DILocation(line: 1595, column: 50, scope: !2815)
!2818 = !DILocation(line: 1595, column: 53, scope: !2815)
!2819 = !DILocation(line: 1595, column: 48, scope: !2815)
!2820 = !DILocation(line: 1595, column: 68, scope: !2815)
!2821 = !DILocation(line: 1596, column: 13, scope: !2811)
!2822 = !DILocation(line: 1596, column: 16, scope: !2811)
!2823 = !DILocation(line: 1596, column: 27, scope: !2811)
!2824 = !DILocation(line: 1596, column: 25, scope: !2811)
!2825 = !DILocation(line: 1596, column: 40, scope: !2811)
!2826 = !DILocation(line: 1596, column: 37, scope: !2811)
!2827 = !DILocation(line: 1595, column: 13, scope: !2828)
!2828 = !DILexicalBlockFile(scope: !2761, file: !1, discriminator: 2)
!2829 = !DILocation(line: 1601, column: 17, scope: !2830)
!2830 = distinct !DILexicalBlock(scope: !2831, file: !1, line: 1601, column: 17)
!2831 = distinct !DILexicalBlock(scope: !2811, file: !1, line: 1596, column: 53)
!2832 = !DILocation(line: 1601, column: 20, scope: !2830)
!2833 = !DILocation(line: 1601, column: 29, scope: !2830)
!2834 = !DILocation(line: 1601, column: 47, scope: !2830)
!2835 = !DILocation(line: 1601, column: 50, scope: !2836)
!2836 = !DILexicalBlockFile(scope: !2830, file: !1, discriminator: 1)
!2837 = !DILocation(line: 1601, column: 53, scope: !2836)
!2838 = !DILocation(line: 1601, column: 62, scope: !2836)
!2839 = !DILocation(line: 1601, column: 17, scope: !2836)
!2840 = !DILocation(line: 1602, column: 50, scope: !2841)
!2841 = distinct !DILexicalBlock(scope: !2830, file: !1, line: 1601, column: 72)
!2842 = !DILocation(line: 1602, column: 53, scope: !2841)
!2843 = !DILocation(line: 1602, column: 35, scope: !2841)
!2844 = !DILocation(line: 1602, column: 17, scope: !2841)
!2845 = !DILocation(line: 1602, column: 20, scope: !2841)
!2846 = !DILocation(line: 1602, column: 33, scope: !2841)
!2847 = !DILocation(line: 1603, column: 13, scope: !2841)
!2848 = !DILocation(line: 1603, column: 24, scope: !2849)
!2849 = !DILexicalBlockFile(scope: !2850, file: !1, discriminator: 1)
!2850 = distinct !DILexicalBlock(scope: !2830, file: !1, line: 1603, column: 24)
!2851 = !DILocation(line: 1603, column: 27, scope: !2849)
!2852 = !DILocation(line: 1603, column: 36, scope: !2849)
!2853 = !DILocation(line: 1603, column: 45, scope: !2849)
!2854 = !DILocation(line: 1603, column: 48, scope: !2855)
!2855 = !DILexicalBlockFile(scope: !2850, file: !1, discriminator: 2)
!2856 = !DILocation(line: 1603, column: 51, scope: !2855)
!2857 = !DILocation(line: 1603, column: 62, scope: !2855)
!2858 = !DILocation(line: 1603, column: 60, scope: !2855)
!2859 = !DILocation(line: 1603, column: 72, scope: !2855)
!2860 = !DILocation(line: 1603, column: 24, scope: !2855)
!2861 = !DILocation(line: 1604, column: 55, scope: !2862)
!2862 = distinct !DILexicalBlock(scope: !2850, file: !1, line: 1603, column: 78)
!2863 = !DILocation(line: 1604, column: 58, scope: !2862)
!2864 = !DILocation(line: 1604, column: 35, scope: !2862)
!2865 = !DILocation(line: 1604, column: 17, scope: !2862)
!2866 = !DILocation(line: 1604, column: 20, scope: !2862)
!2867 = !DILocation(line: 1604, column: 33, scope: !2862)
!2868 = !DILocation(line: 1605, column: 13, scope: !2862)
!2869 = !DILocation(line: 1608, column: 17, scope: !2870)
!2870 = distinct !DILexicalBlock(scope: !2831, file: !1, line: 1608, column: 17)
!2871 = !DILocation(line: 1608, column: 20, scope: !2870)
!2872 = !DILocation(line: 1608, column: 33, scope: !2870)
!2873 = !DILocation(line: 1608, column: 38, scope: !2870)
!2874 = !DILocation(line: 1608, column: 42, scope: !2875)
!2875 = !DILexicalBlockFile(scope: !2870, file: !1, discriminator: 1)
!2876 = !DILocation(line: 1608, column: 45, scope: !2875)
!2877 = !DILocation(line: 1608, column: 54, scope: !2875)
!2878 = !DILocation(line: 1610, column: 17, scope: !2870)
!2879 = !DILocation(line: 1610, column: 21, scope: !2875)
!2880 = !DILocation(line: 1610, column: 24, scope: !2875)
!2881 = !DILocation(line: 1610, column: 37, scope: !2875)
!2882 = !DILocation(line: 1610, column: 50, scope: !2875)
!2883 = !DILocation(line: 1611, column: 21, scope: !2870)
!2884 = !DILocation(line: 1611, column: 24, scope: !2870)
!2885 = !DILocation(line: 1611, column: 35, scope: !2870)
!2886 = !DILocation(line: 1611, column: 38, scope: !2870)
!2887 = !DILocation(line: 1611, column: 33, scope: !2870)
!2888 = !DILocation(line: 1611, column: 50, scope: !2870)
!2889 = !DILocation(line: 1608, column: 17, scope: !2890)
!2890 = !DILexicalBlockFile(scope: !2831, file: !1, discriminator: 2)
!2891 = !DILocation(line: 1618, column: 17, scope: !2892)
!2892 = distinct !DILexicalBlock(scope: !2870, file: !1, line: 1613, column: 20)
!2893 = !DILocation(line: 1618, column: 20, scope: !2892)
!2894 = !DILocation(line: 1618, column: 33, scope: !2892)
!2895 = !DILocation(line: 1619, column: 13, scope: !2892)
!2896 = !DILocation(line: 1620, column: 9, scope: !2831)
!2897 = !DILocation(line: 1624, column: 13, scope: !2898)
!2898 = distinct !DILexicalBlock(scope: !2761, file: !1, line: 1624, column: 13)
!2899 = !DILocation(line: 1624, column: 16, scope: !2898)
!2900 = !DILocation(line: 1624, column: 28, scope: !2898)
!2901 = !DILocation(line: 1624, column: 41, scope: !2898)
!2902 = !DILocation(line: 1624, column: 44, scope: !2903)
!2903 = !DILexicalBlockFile(scope: !2898, file: !1, discriminator: 1)
!2904 = !DILocation(line: 1624, column: 47, scope: !2903)
!2905 = !DILocation(line: 1624, column: 63, scope: !2903)
!2906 = !DILocation(line: 1624, column: 66, scope: !2903)
!2907 = !DILocation(line: 1624, column: 60, scope: !2903)
!2908 = !DILocation(line: 1624, column: 13, scope: !2903)
!2909 = !DILocalVariable(name: "max_insert", scope: !2910, file: !1, line: 1625, type: !18)
!2910 = distinct !DILexicalBlock(scope: !2898, file: !1, line: 1624, column: 79)
!2911 = !DILocation(line: 1625, column: 18, scope: !2910)
!2912 = !DILocation(line: 1625, column: 31, scope: !2910)
!2913 = !DILocation(line: 1625, column: 34, scope: !2910)
!2914 = !DILocation(line: 1625, column: 45, scope: !2910)
!2915 = !DILocation(line: 1625, column: 48, scope: !2910)
!2916 = !DILocation(line: 1625, column: 43, scope: !2910)
!2917 = !DILocation(line: 1625, column: 58, scope: !2910)
!2918 = !DILocalVariable(name: "len", scope: !2919, file: !1, line: 1630, type: !171)
!2919 = distinct !DILexicalBlock(scope: !2910, file: !1, line: 1630, column: 13)
!2920 = !DILocation(line: 1630, column: 13, scope: !2919)
!2921 = !DILocalVariable(name: "dist", scope: !2919, file: !1, line: 1630, type: !98)
!2922 = !DILocation(line: 1630, column: 13, scope: !2923)
!2923 = !DILexicalBlockFile(scope: !2919, file: !1, discriminator: 1)
!2924 = !DILocation(line: 1630, column: 13, scope: !2925)
!2925 = !DILexicalBlockFile(scope: !2919, file: !1, discriminator: 2)
!2926 = !DILocation(line: 1630, column: 13, scope: !2927)
!2927 = !DILexicalBlockFile(scope: !2919, file: !1, discriminator: 3)
!2928 = !DILocation(line: 1638, column: 29, scope: !2910)
!2929 = !DILocation(line: 1638, column: 32, scope: !2910)
!2930 = !DILocation(line: 1638, column: 43, scope: !2910)
!2931 = !DILocation(line: 1638, column: 13, scope: !2910)
!2932 = !DILocation(line: 1638, column: 16, scope: !2910)
!2933 = !DILocation(line: 1638, column: 26, scope: !2910)
!2934 = !DILocation(line: 1639, column: 13, scope: !2910)
!2935 = !DILocation(line: 1639, column: 16, scope: !2910)
!2936 = !DILocation(line: 1639, column: 28, scope: !2910)
!2937 = !DILocation(line: 1640, column: 13, scope: !2910)
!2938 = !DILocation(line: 1641, column: 23, scope: !2939)
!2939 = distinct !DILexicalBlock(scope: !2940, file: !1, line: 1641, column: 21)
!2940 = distinct !DILexicalBlock(scope: !2910, file: !1, line: 1640, column: 16)
!2941 = !DILocation(line: 1641, column: 26, scope: !2939)
!2942 = !DILocation(line: 1641, column: 21, scope: !2939)
!2943 = !DILocation(line: 1641, column: 38, scope: !2939)
!2944 = !DILocation(line: 1641, column: 35, scope: !2939)
!2945 = !DILocation(line: 1641, column: 21, scope: !2940)
!2946 = !DILocation(line: 1642, column: 21, scope: !2947)
!2947 = distinct !DILexicalBlock(scope: !2939, file: !1, line: 1641, column: 50)
!2948 = !DILocation(line: 1643, column: 17, scope: !2947)
!2949 = !DILocation(line: 1644, column: 13, scope: !2940)
!2950 = !DILocation(line: 1644, column: 24, scope: !2951)
!2951 = !DILexicalBlockFile(scope: !2910, file: !1, discriminator: 1)
!2952 = !DILocation(line: 1644, column: 27, scope: !2951)
!2953 = !DILocation(line: 1644, column: 22, scope: !2951)
!2954 = !DILocation(line: 1644, column: 39, scope: !2951)
!2955 = !DILocation(line: 1644, column: 13, scope: !2951)
!2956 = !DILocation(line: 1645, column: 13, scope: !2910)
!2957 = !DILocation(line: 1645, column: 16, scope: !2910)
!2958 = !DILocation(line: 1645, column: 32, scope: !2910)
!2959 = !DILocation(line: 1646, column: 13, scope: !2910)
!2960 = !DILocation(line: 1646, column: 16, scope: !2910)
!2961 = !DILocation(line: 1646, column: 29, scope: !2910)
!2962 = !DILocation(line: 1647, column: 13, scope: !2910)
!2963 = !DILocation(line: 1647, column: 16, scope: !2910)
!2964 = !DILocation(line: 1647, column: 24, scope: !2910)
!2965 = !DILocation(line: 1649, column: 17, scope: !2966)
!2966 = distinct !DILexicalBlock(scope: !2910, file: !1, line: 1649, column: 17)
!2967 = !DILocation(line: 1649, column: 17, scope: !2910)
!2968 = !DILocation(line: 1649, column: 25, scope: !2969)
!2969 = !DILexicalBlockFile(scope: !2970, file: !1, discriminator: 1)
!2970 = distinct !DILexicalBlock(scope: !2971, file: !1, line: 1649, column: 25)
!2971 = distinct !DILexicalBlock(scope: !2966, file: !1, line: 1649, column: 25)
!2972 = !DILocation(line: 1649, column: 25, scope: !2973)
!2973 = !DILexicalBlockFile(scope: !2970, file: !1, discriminator: 2)
!2974 = !DILocation(line: 1649, column: 25, scope: !2975)
!2975 = !DILexicalBlockFile(scope: !2970, file: !1, discriminator: 3)
!2976 = !DILocation(line: 1649, column: 25, scope: !2977)
!2977 = !DILexicalBlockFile(scope: !2970, file: !1, discriminator: 4)
!2978 = !DILocation(line: 1649, column: 25, scope: !2979)
!2979 = !DILexicalBlockFile(scope: !2977, file: !1, discriminator: 7)
!2980 = !DILocation(line: 1649, column: 25, scope: !2981)
!2981 = !DILexicalBlockFile(scope: !2982, file: !1, discriminator: 5)
!2982 = distinct !DILexicalBlock(scope: !2971, file: !1, line: 1649, column: 25)
!2983 = !DILocation(line: 1649, column: 25, scope: !2984)
!2984 = !DILexicalBlockFile(scope: !2971, file: !1, discriminator: 6)
!2985 = !DILocation(line: 1651, column: 9, scope: !2910)
!2986 = !DILocation(line: 1651, column: 20, scope: !2987)
!2987 = !DILexicalBlockFile(scope: !2988, file: !1, discriminator: 1)
!2988 = distinct !DILexicalBlock(scope: !2898, file: !1, line: 1651, column: 20)
!2989 = !DILocation(line: 1651, column: 23, scope: !2987)
!2990 = !DILocalVariable(name: "cc", scope: !2991, file: !1, line: 1657, type: !171)
!2991 = distinct !DILexicalBlock(scope: !2992, file: !1, line: 1657, column: 13)
!2992 = distinct !DILexicalBlock(scope: !2988, file: !1, line: 1651, column: 40)
!2993 = !DILocation(line: 1657, column: 13, scope: !2991)
!2994 = !DILocation(line: 1658, column: 17, scope: !2995)
!2995 = distinct !DILexicalBlock(scope: !2992, file: !1, line: 1658, column: 17)
!2996 = !DILocation(line: 1658, column: 17, scope: !2992)
!2997 = !DILocation(line: 1659, column: 17, scope: !2998)
!2998 = distinct !DILexicalBlock(scope: !2999, file: !1, line: 1659, column: 17)
!2999 = distinct !DILexicalBlock(scope: !2995, file: !1, line: 1658, column: 25)
!3000 = !DILocation(line: 1659, column: 17, scope: !3001)
!3001 = !DILexicalBlockFile(scope: !2998, file: !1, discriminator: 1)
!3002 = !DILocation(line: 1659, column: 17, scope: !3003)
!3003 = !DILexicalBlockFile(scope: !2998, file: !1, discriminator: 2)
!3004 = !DILocation(line: 1659, column: 17, scope: !3005)
!3005 = !DILexicalBlockFile(scope: !2998, file: !1, discriminator: 3)
!3006 = !DILocation(line: 1659, column: 17, scope: !3007)
!3007 = !DILexicalBlockFile(scope: !3005, file: !1, discriminator: 4)
!3008 = !DILocation(line: 1660, column: 13, scope: !2999)
!3009 = !DILocation(line: 1661, column: 13, scope: !2992)
!3010 = !DILocation(line: 1661, column: 16, scope: !2992)
!3011 = !DILocation(line: 1661, column: 24, scope: !2992)
!3012 = !DILocation(line: 1662, column: 13, scope: !2992)
!3013 = !DILocation(line: 1662, column: 16, scope: !2992)
!3014 = !DILocation(line: 1662, column: 25, scope: !2992)
!3015 = !DILocation(line: 1663, column: 17, scope: !3016)
!3016 = distinct !DILexicalBlock(scope: !2992, file: !1, line: 1663, column: 17)
!3017 = !DILocation(line: 1663, column: 20, scope: !3016)
!3018 = !DILocation(line: 1663, column: 26, scope: !3016)
!3019 = !DILocation(line: 1663, column: 36, scope: !3016)
!3020 = !DILocation(line: 1663, column: 17, scope: !2992)
!3021 = !DILocation(line: 1663, column: 42, scope: !3022)
!3022 = !DILexicalBlockFile(scope: !3016, file: !1, discriminator: 1)
!3023 = !DILocation(line: 1664, column: 9, scope: !2992)
!3024 = !DILocation(line: 1668, column: 13, scope: !3025)
!3025 = distinct !DILexicalBlock(scope: !2988, file: !1, line: 1664, column: 16)
!3026 = !DILocation(line: 1668, column: 16, scope: !3025)
!3027 = !DILocation(line: 1668, column: 32, scope: !3025)
!3028 = !DILocation(line: 1669, column: 13, scope: !3025)
!3029 = !DILocation(line: 1669, column: 16, scope: !3025)
!3030 = !DILocation(line: 1669, column: 24, scope: !3025)
!3031 = !DILocation(line: 1670, column: 13, scope: !3025)
!3032 = !DILocation(line: 1670, column: 16, scope: !3025)
!3033 = !DILocation(line: 1670, column: 25, scope: !3025)
!3034 = !DILocation(line: 1569, column: 5, scope: !3035)
!3035 = !DILexicalBlockFile(scope: !2762, file: !1, discriminator: 1)
!3036 = !DILocation(line: 1674, column: 9, scope: !3037)
!3037 = distinct !DILexicalBlock(scope: !241, file: !1, line: 1674, column: 9)
!3038 = !DILocation(line: 1674, column: 12, scope: !3037)
!3039 = !DILocation(line: 1674, column: 9, scope: !241)
!3040 = !DILocalVariable(name: "cc", scope: !3041, file: !1, line: 1676, type: !171)
!3041 = distinct !DILexicalBlock(scope: !3042, file: !1, line: 1676, column: 9)
!3042 = distinct !DILexicalBlock(scope: !3037, file: !1, line: 1674, column: 29)
!3043 = !DILocation(line: 1676, column: 9, scope: !3041)
!3044 = !DILocation(line: 1677, column: 9, scope: !3042)
!3045 = !DILocation(line: 1677, column: 12, scope: !3042)
!3046 = !DILocation(line: 1677, column: 28, scope: !3042)
!3047 = !DILocation(line: 1678, column: 5, scope: !3042)
!3048 = !DILocation(line: 1679, column: 5, scope: !3049)
!3049 = distinct !DILexicalBlock(scope: !3050, file: !1, line: 1679, column: 5)
!3050 = distinct !DILexicalBlock(scope: !241, file: !1, line: 1679, column: 5)
!3051 = !DILocation(line: 1679, column: 5, scope: !3052)
!3052 = !DILexicalBlockFile(scope: !3049, file: !1, discriminator: 1)
!3053 = !DILocation(line: 1679, column: 5, scope: !3054)
!3054 = !DILexicalBlockFile(scope: !3049, file: !1, discriminator: 2)
!3055 = !DILocation(line: 1679, column: 5, scope: !3056)
!3056 = !DILexicalBlockFile(scope: !3049, file: !1, discriminator: 3)
!3057 = !DILocation(line: 1679, column: 5, scope: !3058)
!3058 = !DILexicalBlockFile(scope: !3056, file: !1, discriminator: 5)
!3059 = !DILocation(line: 1679, column: 5, scope: !3060)
!3060 = !DILexicalBlockFile(scope: !3061, file: !1, discriminator: 4)
!3061 = distinct !DILexicalBlock(scope: !3050, file: !1, line: 1679, column: 5)
!3062 = !DILocation(line: 1680, column: 12, scope: !241)
!3063 = !DILocation(line: 1680, column: 18, scope: !241)
!3064 = !DILocation(line: 1680, column: 5, scope: !241)
!3065 = !DILocation(line: 1681, column: 1, scope: !241)
!3066 = !DILocalVariable(name: "s", arg: 1, scope: !230, file: !1, line: 1274, type: !24)
!3067 = !DILocation(line: 1274, column: 20, scope: !230)
!3068 = !DILocalVariable(name: "n", scope: !230, file: !1, line: 1276, type: !19)
!3069 = !DILocation(line: 1276, column: 23, scope: !230)
!3070 = !DILocalVariable(name: "m", scope: !230, file: !1, line: 1276, type: !19)
!3071 = !DILocation(line: 1276, column: 26, scope: !230)
!3072 = !DILocalVariable(name: "p", scope: !230, file: !1, line: 1277, type: !95)
!3073 = !DILocation(line: 1277, column: 20, scope: !230)
!3074 = !DILocalVariable(name: "more", scope: !230, file: !1, line: 1278, type: !19)
!3075 = !DILocation(line: 1278, column: 14, scope: !230)
!3076 = !DILocalVariable(name: "wsize", scope: !230, file: !1, line: 1279, type: !18)
!3077 = !DILocation(line: 1279, column: 10, scope: !230)
!3078 = !DILocation(line: 1279, column: 18, scope: !230)
!3079 = !DILocation(line: 1279, column: 21, scope: !230)
!3080 = !DILocation(line: 1281, column: 5, scope: !230)
!3081 = !DILocation(line: 1282, column: 27, scope: !3082)
!3082 = distinct !DILexicalBlock(scope: !230, file: !1, line: 1281, column: 8)
!3083 = !DILocation(line: 1282, column: 30, scope: !3082)
!3084 = !DILocation(line: 1282, column: 48, scope: !3082)
!3085 = !DILocation(line: 1282, column: 51, scope: !3082)
!3086 = !DILocation(line: 1282, column: 43, scope: !3082)
!3087 = !DILocation(line: 1282, column: 42, scope: !3082)
!3088 = !DILocation(line: 1282, column: 67, scope: !3082)
!3089 = !DILocation(line: 1282, column: 70, scope: !3082)
!3090 = !DILocation(line: 1282, column: 62, scope: !3082)
!3091 = !DILocation(line: 1282, column: 61, scope: !3082)
!3092 = !DILocation(line: 1282, column: 16, scope: !3082)
!3093 = !DILocation(line: 1282, column: 14, scope: !3082)
!3094 = !DILocation(line: 1300, column: 13, scope: !3095)
!3095 = distinct !DILexicalBlock(scope: !3082, file: !1, line: 1300, column: 13)
!3096 = !DILocation(line: 1300, column: 16, scope: !3095)
!3097 = !DILocation(line: 1300, column: 28, scope: !3095)
!3098 = !DILocation(line: 1300, column: 34, scope: !3095)
!3099 = !DILocation(line: 1300, column: 33, scope: !3095)
!3100 = !DILocation(line: 1300, column: 25, scope: !3095)
!3101 = !DILocation(line: 1300, column: 13, scope: !3082)
!3102 = !DILocation(line: 1302, column: 21, scope: !3103)
!3103 = distinct !DILexicalBlock(scope: !3095, file: !1, line: 1300, column: 47)
!3104 = !DILocation(line: 1302, column: 24, scope: !3103)
!3105 = !DILocation(line: 1302, column: 32, scope: !3103)
!3106 = !DILocation(line: 1302, column: 35, scope: !3103)
!3107 = !DILocation(line: 1302, column: 42, scope: !3103)
!3108 = !DILocation(line: 1302, column: 41, scope: !3103)
!3109 = !DILocation(line: 1302, column: 59, scope: !3103)
!3110 = !DILocation(line: 1302, column: 49, scope: !3103)
!3111 = !DILocation(line: 1302, column: 13, scope: !3103)
!3112 = !DILocation(line: 1303, column: 31, scope: !3103)
!3113 = !DILocation(line: 1303, column: 13, scope: !3103)
!3114 = !DILocation(line: 1303, column: 16, scope: !3103)
!3115 = !DILocation(line: 1303, column: 28, scope: !3103)
!3116 = !DILocation(line: 1304, column: 31, scope: !3103)
!3117 = !DILocation(line: 1304, column: 13, scope: !3103)
!3118 = !DILocation(line: 1304, column: 16, scope: !3103)
!3119 = !DILocation(line: 1304, column: 28, scope: !3103)
!3120 = !DILocation(line: 1305, column: 38, scope: !3103)
!3121 = !DILocation(line: 1305, column: 31, scope: !3103)
!3122 = !DILocation(line: 1305, column: 13, scope: !3103)
!3123 = !DILocation(line: 1305, column: 16, scope: !3103)
!3124 = !DILocation(line: 1305, column: 28, scope: !3103)
!3125 = !DILocation(line: 1314, column: 17, scope: !3103)
!3126 = !DILocation(line: 1314, column: 20, scope: !3103)
!3127 = !DILocation(line: 1314, column: 15, scope: !3103)
!3128 = !DILocation(line: 1315, column: 26, scope: !3103)
!3129 = !DILocation(line: 1315, column: 18, scope: !3103)
!3130 = !DILocation(line: 1315, column: 21, scope: !3103)
!3131 = !DILocation(line: 1315, column: 15, scope: !3103)
!3132 = !DILocation(line: 1316, column: 13, scope: !3103)
!3133 = !DILocation(line: 1317, column: 22, scope: !3134)
!3134 = distinct !DILexicalBlock(scope: !3103, file: !1, line: 1316, column: 16)
!3135 = !DILocation(line: 1317, column: 21, scope: !3134)
!3136 = !DILocation(line: 1317, column: 19, scope: !3134)
!3137 = !DILocation(line: 1318, column: 28, scope: !3134)
!3138 = !DILocation(line: 1318, column: 33, scope: !3134)
!3139 = !DILocation(line: 1318, column: 30, scope: !3134)
!3140 = !DILocation(line: 1318, column: 41, scope: !3141)
!3141 = !DILexicalBlockFile(scope: !3134, file: !1, discriminator: 1)
!3142 = !DILocation(line: 1318, column: 43, scope: !3141)
!3143 = !DILocation(line: 1318, column: 42, scope: !3141)
!3144 = !DILocation(line: 1318, column: 28, scope: !3141)
!3145 = !DILocation(line: 1318, column: 28, scope: !3146)
!3146 = !DILexicalBlockFile(scope: !3134, file: !1, discriminator: 2)
!3147 = !DILocation(line: 1318, column: 28, scope: !3148)
!3148 = !DILexicalBlockFile(scope: !3134, file: !1, discriminator: 3)
!3149 = !DILocation(line: 1318, column: 22, scope: !3148)
!3150 = !DILocation(line: 1318, column: 18, scope: !3148)
!3151 = !DILocation(line: 1318, column: 20, scope: !3148)
!3152 = !DILocation(line: 1319, column: 13, scope: !3134)
!3153 = !DILocation(line: 1319, column: 22, scope: !3154)
!3154 = !DILexicalBlockFile(scope: !3103, file: !1, discriminator: 1)
!3155 = !DILocation(line: 1319, column: 13, scope: !3154)
!3156 = !DILocation(line: 1321, column: 17, scope: !3103)
!3157 = !DILocation(line: 1321, column: 15, scope: !3103)
!3158 = !DILocation(line: 1323, column: 26, scope: !3103)
!3159 = !DILocation(line: 1323, column: 18, scope: !3103)
!3160 = !DILocation(line: 1323, column: 21, scope: !3103)
!3161 = !DILocation(line: 1323, column: 15, scope: !3103)
!3162 = !DILocation(line: 1324, column: 13, scope: !3103)
!3163 = !DILocation(line: 1325, column: 22, scope: !3164)
!3164 = distinct !DILexicalBlock(scope: !3103, file: !1, line: 1324, column: 16)
!3165 = !DILocation(line: 1325, column: 21, scope: !3164)
!3166 = !DILocation(line: 1325, column: 19, scope: !3164)
!3167 = !DILocation(line: 1326, column: 28, scope: !3164)
!3168 = !DILocation(line: 1326, column: 33, scope: !3164)
!3169 = !DILocation(line: 1326, column: 30, scope: !3164)
!3170 = !DILocation(line: 1326, column: 41, scope: !3171)
!3171 = !DILexicalBlockFile(scope: !3164, file: !1, discriminator: 1)
!3172 = !DILocation(line: 1326, column: 43, scope: !3171)
!3173 = !DILocation(line: 1326, column: 42, scope: !3171)
!3174 = !DILocation(line: 1326, column: 28, scope: !3171)
!3175 = !DILocation(line: 1326, column: 28, scope: !3176)
!3176 = !DILexicalBlockFile(scope: !3164, file: !1, discriminator: 2)
!3177 = !DILocation(line: 1326, column: 28, scope: !3178)
!3178 = !DILexicalBlockFile(scope: !3164, file: !1, discriminator: 3)
!3179 = !DILocation(line: 1326, column: 22, scope: !3178)
!3180 = !DILocation(line: 1326, column: 18, scope: !3178)
!3181 = !DILocation(line: 1326, column: 20, scope: !3178)
!3182 = !DILocation(line: 1330, column: 13, scope: !3164)
!3183 = !DILocation(line: 1330, column: 22, scope: !3154)
!3184 = !DILocation(line: 1330, column: 13, scope: !3154)
!3185 = !DILocation(line: 1332, column: 21, scope: !3103)
!3186 = !DILocation(line: 1332, column: 18, scope: !3103)
!3187 = !DILocation(line: 1333, column: 9, scope: !3103)
!3188 = !DILocation(line: 1334, column: 13, scope: !3189)
!3189 = distinct !DILexicalBlock(scope: !3082, file: !1, line: 1334, column: 13)
!3190 = !DILocation(line: 1334, column: 16, scope: !3189)
!3191 = !DILocation(line: 1334, column: 22, scope: !3189)
!3192 = !DILocation(line: 1334, column: 31, scope: !3189)
!3193 = !DILocation(line: 1334, column: 13, scope: !3082)
!3194 = !DILocation(line: 1334, column: 37, scope: !3195)
!3195 = !DILexicalBlockFile(scope: !3189, file: !1, discriminator: 1)
!3196 = !DILocation(line: 1349, column: 22, scope: !3082)
!3197 = !DILocation(line: 1349, column: 25, scope: !3082)
!3198 = !DILocation(line: 1349, column: 31, scope: !3082)
!3199 = !DILocation(line: 1349, column: 34, scope: !3082)
!3200 = !DILocation(line: 1349, column: 43, scope: !3082)
!3201 = !DILocation(line: 1349, column: 46, scope: !3082)
!3202 = !DILocation(line: 1349, column: 41, scope: !3082)
!3203 = !DILocation(line: 1349, column: 57, scope: !3082)
!3204 = !DILocation(line: 1349, column: 60, scope: !3082)
!3205 = !DILocation(line: 1349, column: 55, scope: !3082)
!3206 = !DILocation(line: 1349, column: 71, scope: !3082)
!3207 = !DILocation(line: 1349, column: 13, scope: !3082)
!3208 = !DILocation(line: 1349, column: 11, scope: !3082)
!3209 = !DILocation(line: 1350, column: 25, scope: !3082)
!3210 = !DILocation(line: 1350, column: 9, scope: !3082)
!3211 = !DILocation(line: 1350, column: 12, scope: !3082)
!3212 = !DILocation(line: 1350, column: 22, scope: !3082)
!3213 = !DILocation(line: 1353, column: 13, scope: !3214)
!3214 = distinct !DILexicalBlock(scope: !3082, file: !1, line: 1353, column: 13)
!3215 = !DILocation(line: 1353, column: 16, scope: !3214)
!3216 = !DILocation(line: 1353, column: 26, scope: !3214)
!3217 = !DILocation(line: 1353, column: 13, scope: !3082)
!3218 = !DILocation(line: 1354, column: 34, scope: !3219)
!3219 = distinct !DILexicalBlock(scope: !3214, file: !1, line: 1353, column: 40)
!3220 = !DILocation(line: 1354, column: 37, scope: !3219)
!3221 = !DILocation(line: 1354, column: 24, scope: !3219)
!3222 = !DILocation(line: 1354, column: 27, scope: !3219)
!3223 = !DILocation(line: 1354, column: 13, scope: !3219)
!3224 = !DILocation(line: 1354, column: 16, scope: !3219)
!3225 = !DILocation(line: 1354, column: 22, scope: !3219)
!3226 = !DILocation(line: 1355, column: 13, scope: !3219)
!3227 = !DILocation(line: 1359, column: 9, scope: !3219)
!3228 = !DILocation(line: 1364, column: 5, scope: !3082)
!3229 = !DILocation(line: 1364, column: 14, scope: !3230)
!3230 = !DILexicalBlockFile(scope: !230, file: !1, discriminator: 1)
!3231 = !DILocation(line: 1364, column: 17, scope: !3230)
!3232 = !DILocation(line: 1364, column: 27, scope: !3230)
!3233 = !DILocation(line: 1364, column: 43, scope: !3230)
!3234 = !DILocation(line: 1364, column: 46, scope: !3235)
!3235 = !DILexicalBlockFile(scope: !230, file: !1, discriminator: 2)
!3236 = !DILocation(line: 1364, column: 49, scope: !3235)
!3237 = !DILocation(line: 1364, column: 55, scope: !3235)
!3238 = !DILocation(line: 1364, column: 64, scope: !3235)
!3239 = !DILocation(line: 1364, column: 5, scope: !3240)
!3240 = !DILexicalBlockFile(scope: !3082, file: !1, discriminator: 3)
!3241 = !DILocation(line: 1365, column: 1, scope: !230)
!3242 = !DILocalVariable(name: "strm", arg: 1, scope: !233, file: !1, line: 964, type: !30)
!3243 = !DILocation(line: 964, column: 15, scope: !233)
!3244 = !DILocalVariable(name: "buf", arg: 2, scope: !233, file: !1, line: 965, type: !36)
!3245 = !DILocation(line: 965, column: 12, scope: !233)
!3246 = !DILocalVariable(name: "size", arg: 3, scope: !233, file: !1, line: 966, type: !19)
!3247 = !DILocation(line: 966, column: 14, scope: !233)
!3248 = !DILocalVariable(name: "len", scope: !233, file: !1, line: 968, type: !19)
!3249 = !DILocation(line: 968, column: 14, scope: !233)
!3250 = !DILocation(line: 968, column: 20, scope: !233)
!3251 = !DILocation(line: 968, column: 26, scope: !233)
!3252 = !DILocation(line: 970, column: 9, scope: !3253)
!3253 = distinct !DILexicalBlock(scope: !233, file: !1, line: 970, column: 9)
!3254 = !DILocation(line: 970, column: 15, scope: !3253)
!3255 = !DILocation(line: 970, column: 13, scope: !3253)
!3256 = !DILocation(line: 970, column: 9, scope: !233)
!3257 = !DILocation(line: 970, column: 27, scope: !3258)
!3258 = !DILexicalBlockFile(scope: !3253, file: !1, discriminator: 1)
!3259 = !DILocation(line: 970, column: 25, scope: !3258)
!3260 = !DILocation(line: 970, column: 21, scope: !3258)
!3261 = !DILocation(line: 971, column: 9, scope: !3262)
!3262 = distinct !DILexicalBlock(scope: !233, file: !1, line: 971, column: 9)
!3263 = !DILocation(line: 971, column: 13, scope: !3262)
!3264 = !DILocation(line: 971, column: 9, scope: !233)
!3265 = !DILocation(line: 971, column: 19, scope: !3266)
!3266 = !DILexicalBlockFile(scope: !3262, file: !1, discriminator: 1)
!3267 = !DILocation(line: 973, column: 24, scope: !233)
!3268 = !DILocation(line: 973, column: 5, scope: !233)
!3269 = !DILocation(line: 973, column: 11, scope: !233)
!3270 = !DILocation(line: 973, column: 21, scope: !233)
!3271 = !DILocation(line: 975, column: 9, scope: !3272)
!3272 = distinct !DILexicalBlock(scope: !233, file: !1, line: 975, column: 9)
!3273 = !DILocation(line: 975, column: 15, scope: !3272)
!3274 = !DILocation(line: 975, column: 22, scope: !3272)
!3275 = !DILocation(line: 975, column: 27, scope: !3272)
!3276 = !DILocation(line: 975, column: 9, scope: !233)
!3277 = !DILocation(line: 976, column: 31, scope: !3278)
!3278 = distinct !DILexicalBlock(scope: !3272, file: !1, line: 975, column: 33)
!3279 = !DILocation(line: 976, column: 37, scope: !3278)
!3280 = !DILocation(line: 976, column: 44, scope: !3278)
!3281 = !DILocation(line: 976, column: 50, scope: !3278)
!3282 = !DILocation(line: 976, column: 59, scope: !3278)
!3283 = !DILocation(line: 976, column: 23, scope: !3278)
!3284 = !DILocation(line: 976, column: 9, scope: !3278)
!3285 = !DILocation(line: 976, column: 15, scope: !3278)
!3286 = !DILocation(line: 976, column: 21, scope: !3278)
!3287 = !DILocation(line: 977, column: 5, scope: !3278)
!3288 = !DILocation(line: 979, column: 14, scope: !3289)
!3289 = distinct !DILexicalBlock(scope: !3272, file: !1, line: 979, column: 14)
!3290 = !DILocation(line: 979, column: 20, scope: !3289)
!3291 = !DILocation(line: 979, column: 27, scope: !3289)
!3292 = !DILocation(line: 979, column: 32, scope: !3289)
!3293 = !DILocation(line: 979, column: 14, scope: !3272)
!3294 = !DILocation(line: 980, column: 29, scope: !3295)
!3295 = distinct !DILexicalBlock(scope: !3289, file: !1, line: 979, column: 38)
!3296 = !DILocation(line: 980, column: 35, scope: !3295)
!3297 = !DILocation(line: 980, column: 42, scope: !3295)
!3298 = !DILocation(line: 980, column: 48, scope: !3295)
!3299 = !DILocation(line: 980, column: 57, scope: !3295)
!3300 = !DILocation(line: 980, column: 23, scope: !3295)
!3301 = !DILocation(line: 980, column: 9, scope: !3295)
!3302 = !DILocation(line: 980, column: 15, scope: !3295)
!3303 = !DILocation(line: 980, column: 21, scope: !3295)
!3304 = !DILocation(line: 981, column: 5, scope: !3295)
!3305 = !DILocation(line: 983, column: 13, scope: !233)
!3306 = !DILocation(line: 983, column: 18, scope: !233)
!3307 = !DILocation(line: 983, column: 24, scope: !233)
!3308 = !DILocation(line: 983, column: 33, scope: !233)
!3309 = !DILocation(line: 983, column: 5, scope: !233)
!3310 = !DILocation(line: 984, column: 23, scope: !233)
!3311 = !DILocation(line: 984, column: 5, scope: !233)
!3312 = !DILocation(line: 984, column: 11, scope: !233)
!3313 = !DILocation(line: 984, column: 20, scope: !233)
!3314 = !DILocation(line: 985, column: 23, scope: !233)
!3315 = !DILocation(line: 985, column: 5, scope: !233)
!3316 = !DILocation(line: 985, column: 11, scope: !233)
!3317 = !DILocation(line: 985, column: 20, scope: !233)
!3318 = !DILocation(line: 987, column: 17, scope: !233)
!3319 = !DILocation(line: 987, column: 5, scope: !233)
!3320 = !DILocation(line: 988, column: 1, scope: !233)
!3321 = !DILocalVariable(name: "s", arg: 1, scope: !237, file: !1, line: 1035, type: !24)
!3322 = !DILocation(line: 1035, column: 20, scope: !237)
!3323 = !DILocalVariable(name: "cur_match", arg: 2, scope: !237, file: !1, line: 1036, type: !110)
!3324 = !DILocation(line: 1036, column: 10, scope: !237)
!3325 = !DILocalVariable(name: "chain_length", scope: !237, file: !1, line: 1038, type: !19)
!3326 = !DILocation(line: 1038, column: 14, scope: !237)
!3327 = !DILocation(line: 1038, column: 29, scope: !237)
!3328 = !DILocation(line: 1038, column: 32, scope: !237)
!3329 = !DILocalVariable(name: "scan", scope: !237, file: !1, line: 1039, type: !36)
!3330 = !DILocation(line: 1039, column: 21, scope: !237)
!3331 = !DILocation(line: 1039, column: 28, scope: !237)
!3332 = !DILocation(line: 1039, column: 31, scope: !237)
!3333 = !DILocation(line: 1039, column: 40, scope: !237)
!3334 = !DILocation(line: 1039, column: 43, scope: !237)
!3335 = !DILocation(line: 1039, column: 38, scope: !237)
!3336 = !DILocalVariable(name: "match", scope: !237, file: !1, line: 1040, type: !36)
!3337 = !DILocation(line: 1040, column: 21, scope: !237)
!3338 = !DILocalVariable(name: "len", scope: !237, file: !1, line: 1041, type: !56)
!3339 = !DILocation(line: 1041, column: 18, scope: !237)
!3340 = !DILocalVariable(name: "best_len", scope: !237, file: !1, line: 1042, type: !56)
!3341 = !DILocation(line: 1042, column: 9, scope: !237)
!3342 = !DILocation(line: 1042, column: 20, scope: !237)
!3343 = !DILocation(line: 1042, column: 23, scope: !237)
!3344 = !DILocalVariable(name: "nice_match", scope: !237, file: !1, line: 1043, type: !56)
!3345 = !DILocation(line: 1043, column: 9, scope: !237)
!3346 = !DILocation(line: 1043, column: 22, scope: !237)
!3347 = !DILocation(line: 1043, column: 25, scope: !237)
!3348 = !DILocalVariable(name: "limit", scope: !237, file: !1, line: 1044, type: !110)
!3349 = !DILocation(line: 1044, column: 10, scope: !237)
!3350 = !DILocation(line: 1044, column: 18, scope: !237)
!3351 = !DILocation(line: 1044, column: 21, scope: !237)
!3352 = !DILocation(line: 1044, column: 38, scope: !237)
!3353 = !DILocation(line: 1044, column: 30, scope: !237)
!3354 = !DILocation(line: 1045, column: 9, scope: !237)
!3355 = !DILocation(line: 1045, column: 12, scope: !237)
!3356 = !DILocation(line: 1045, column: 29, scope: !237)
!3357 = !DILocation(line: 1045, column: 21, scope: !237)
!3358 = !DILocation(line: 1044, column: 18, scope: !3359)
!3359 = !DILexicalBlockFile(scope: !237, file: !1, discriminator: 1)
!3360 = !DILocation(line: 1044, column: 18, scope: !3361)
!3361 = !DILexicalBlockFile(scope: !237, file: !1, discriminator: 2)
!3362 = !DILocation(line: 1044, column: 18, scope: !3363)
!3363 = !DILexicalBlockFile(scope: !237, file: !1, discriminator: 3)
!3364 = !DILocation(line: 1044, column: 10, scope: !3363)
!3365 = !DILocalVariable(name: "prev", scope: !237, file: !1, line: 1049, type: !95)
!3366 = !DILocation(line: 1049, column: 11, scope: !237)
!3367 = !DILocation(line: 1049, column: 18, scope: !237)
!3368 = !DILocation(line: 1049, column: 21, scope: !237)
!3369 = !DILocalVariable(name: "wmask", scope: !237, file: !1, line: 1050, type: !18)
!3370 = !DILocation(line: 1050, column: 10, scope: !237)
!3371 = !DILocation(line: 1050, column: 18, scope: !237)
!3372 = !DILocation(line: 1050, column: 21, scope: !237)
!3373 = !DILocalVariable(name: "strend", scope: !237, file: !1, line: 1060, type: !36)
!3374 = !DILocation(line: 1060, column: 21, scope: !237)
!3375 = !DILocation(line: 1060, column: 30, scope: !237)
!3376 = !DILocation(line: 1060, column: 33, scope: !237)
!3377 = !DILocation(line: 1060, column: 42, scope: !237)
!3378 = !DILocation(line: 1060, column: 45, scope: !237)
!3379 = !DILocation(line: 1060, column: 40, scope: !237)
!3380 = !DILocation(line: 1060, column: 54, scope: !237)
!3381 = !DILocalVariable(name: "scan_end1", scope: !237, file: !1, line: 1061, type: !38)
!3382 = !DILocation(line: 1061, column: 19, scope: !237)
!3383 = !DILocation(line: 1061, column: 37, scope: !237)
!3384 = !DILocation(line: 1061, column: 45, scope: !237)
!3385 = !DILocation(line: 1061, column: 32, scope: !237)
!3386 = !DILocalVariable(name: "scan_end", scope: !237, file: !1, line: 1062, type: !38)
!3387 = !DILocation(line: 1062, column: 19, scope: !237)
!3388 = !DILocation(line: 1062, column: 37, scope: !237)
!3389 = !DILocation(line: 1062, column: 32, scope: !237)
!3390 = !DILocation(line: 1071, column: 9, scope: !3391)
!3391 = distinct !DILexicalBlock(scope: !237, file: !1, line: 1071, column: 9)
!3392 = !DILocation(line: 1071, column: 12, scope: !3391)
!3393 = !DILocation(line: 1071, column: 27, scope: !3391)
!3394 = !DILocation(line: 1071, column: 30, scope: !3391)
!3395 = !DILocation(line: 1071, column: 24, scope: !3391)
!3396 = !DILocation(line: 1071, column: 9, scope: !237)
!3397 = !DILocation(line: 1072, column: 22, scope: !3398)
!3398 = distinct !DILexicalBlock(scope: !3391, file: !1, line: 1071, column: 42)
!3399 = !DILocation(line: 1073, column: 5, scope: !3398)
!3400 = !DILocation(line: 1077, column: 15, scope: !3401)
!3401 = distinct !DILexicalBlock(scope: !237, file: !1, line: 1077, column: 9)
!3402 = !DILocation(line: 1077, column: 28, scope: !3401)
!3403 = !DILocation(line: 1077, column: 31, scope: !3401)
!3404 = !DILocation(line: 1077, column: 26, scope: !3401)
!3405 = !DILocation(line: 1077, column: 9, scope: !237)
!3406 = !DILocation(line: 1077, column: 55, scope: !3407)
!3407 = !DILexicalBlockFile(scope: !3401, file: !1, discriminator: 1)
!3408 = !DILocation(line: 1077, column: 58, scope: !3407)
!3409 = !DILocation(line: 1077, column: 53, scope: !3407)
!3410 = !DILocation(line: 1077, column: 42, scope: !3407)
!3411 = !DILocation(line: 1081, column: 5, scope: !237)
!3412 = !DILocation(line: 1083, column: 17, scope: !3413)
!3413 = distinct !DILexicalBlock(scope: !237, file: !1, line: 1081, column: 8)
!3414 = !DILocation(line: 1083, column: 20, scope: !3413)
!3415 = !DILocation(line: 1083, column: 29, scope: !3413)
!3416 = !DILocation(line: 1083, column: 27, scope: !3413)
!3417 = !DILocation(line: 1083, column: 15, scope: !3413)
!3418 = !DILocation(line: 1128, column: 19, scope: !3419)
!3419 = distinct !DILexicalBlock(scope: !3413, file: !1, line: 1128, column: 13)
!3420 = !DILocation(line: 1128, column: 13, scope: !3419)
!3421 = !DILocation(line: 1128, column: 34, scope: !3419)
!3422 = !DILocation(line: 1128, column: 31, scope: !3419)
!3423 = !DILocation(line: 1128, column: 44, scope: !3419)
!3424 = !DILocation(line: 1129, column: 19, scope: !3419)
!3425 = !DILocation(line: 1129, column: 27, scope: !3419)
!3426 = !DILocation(line: 1129, column: 13, scope: !3419)
!3427 = !DILocation(line: 1129, column: 34, scope: !3419)
!3428 = !DILocation(line: 1129, column: 31, scope: !3419)
!3429 = !DILocation(line: 1129, column: 44, scope: !3419)
!3430 = !DILocation(line: 1130, column: 14, scope: !3419)
!3431 = !DILocation(line: 1130, column: 13, scope: !3419)
!3432 = !DILocation(line: 1130, column: 35, scope: !3419)
!3433 = !DILocation(line: 1130, column: 34, scope: !3419)
!3434 = !DILocation(line: 1130, column: 31, scope: !3419)
!3435 = !DILocation(line: 1130, column: 44, scope: !3419)
!3436 = !DILocation(line: 1131, column: 14, scope: !3419)
!3437 = !DILocation(line: 1131, column: 13, scope: !3419)
!3438 = !DILocation(line: 1131, column: 34, scope: !3419)
!3439 = !DILocation(line: 1131, column: 31, scope: !3419)
!3440 = !DILocation(line: 1128, column: 13, scope: !3441)
!3441 = !DILexicalBlockFile(scope: !3413, file: !1, discriminator: 1)
!3442 = !DILocation(line: 1131, column: 48, scope: !3443)
!3443 = !DILexicalBlockFile(scope: !3419, file: !1, discriminator: 1)
!3444 = !DILocation(line: 1139, column: 14, scope: !3413)
!3445 = !DILocation(line: 1139, column: 25, scope: !3413)
!3446 = !DILocation(line: 1145, column: 9, scope: !3413)
!3447 = !DILocation(line: 1146, column: 9, scope: !3448)
!3448 = distinct !DILexicalBlock(scope: !3413, file: !1, line: 1145, column: 12)
!3449 = !DILocation(line: 1146, column: 19, scope: !3441)
!3450 = !DILocation(line: 1146, column: 18, scope: !3441)
!3451 = !DILocation(line: 1146, column: 30, scope: !3441)
!3452 = !DILocation(line: 1146, column: 29, scope: !3441)
!3453 = !DILocation(line: 1146, column: 26, scope: !3441)
!3454 = !DILocation(line: 1146, column: 38, scope: !3441)
!3455 = !DILocation(line: 1146, column: 42, scope: !3456)
!3456 = !DILexicalBlockFile(scope: !3413, file: !1, discriminator: 2)
!3457 = !DILocation(line: 1146, column: 41, scope: !3456)
!3458 = !DILocation(line: 1146, column: 53, scope: !3456)
!3459 = !DILocation(line: 1146, column: 52, scope: !3456)
!3460 = !DILocation(line: 1146, column: 49, scope: !3456)
!3461 = !DILocation(line: 1146, column: 61, scope: !3456)
!3462 = !DILocation(line: 1147, column: 19, scope: !3413)
!3463 = !DILocation(line: 1147, column: 18, scope: !3413)
!3464 = !DILocation(line: 1147, column: 30, scope: !3413)
!3465 = !DILocation(line: 1147, column: 29, scope: !3413)
!3466 = !DILocation(line: 1147, column: 26, scope: !3413)
!3467 = !DILocation(line: 1147, column: 38, scope: !3413)
!3468 = !DILocation(line: 1147, column: 42, scope: !3441)
!3469 = !DILocation(line: 1147, column: 41, scope: !3441)
!3470 = !DILocation(line: 1147, column: 53, scope: !3441)
!3471 = !DILocation(line: 1147, column: 52, scope: !3441)
!3472 = !DILocation(line: 1147, column: 49, scope: !3441)
!3473 = !DILocation(line: 1147, column: 61, scope: !3441)
!3474 = !DILocation(line: 1148, column: 19, scope: !3413)
!3475 = !DILocation(line: 1148, column: 18, scope: !3413)
!3476 = !DILocation(line: 1148, column: 30, scope: !3413)
!3477 = !DILocation(line: 1148, column: 29, scope: !3413)
!3478 = !DILocation(line: 1148, column: 26, scope: !3413)
!3479 = !DILocation(line: 1148, column: 38, scope: !3413)
!3480 = !DILocation(line: 1148, column: 42, scope: !3441)
!3481 = !DILocation(line: 1148, column: 41, scope: !3441)
!3482 = !DILocation(line: 1148, column: 53, scope: !3441)
!3483 = !DILocation(line: 1148, column: 52, scope: !3441)
!3484 = !DILocation(line: 1148, column: 49, scope: !3441)
!3485 = !DILocation(line: 1148, column: 61, scope: !3441)
!3486 = !DILocation(line: 1149, column: 19, scope: !3413)
!3487 = !DILocation(line: 1149, column: 18, scope: !3413)
!3488 = !DILocation(line: 1149, column: 30, scope: !3413)
!3489 = !DILocation(line: 1149, column: 29, scope: !3413)
!3490 = !DILocation(line: 1149, column: 26, scope: !3413)
!3491 = !DILocation(line: 1149, column: 38, scope: !3413)
!3492 = !DILocation(line: 1149, column: 42, scope: !3441)
!3493 = !DILocation(line: 1149, column: 41, scope: !3441)
!3494 = !DILocation(line: 1149, column: 53, scope: !3441)
!3495 = !DILocation(line: 1149, column: 52, scope: !3441)
!3496 = !DILocation(line: 1149, column: 49, scope: !3441)
!3497 = !DILocation(line: 1149, column: 61, scope: !3441)
!3498 = !DILocation(line: 1150, column: 18, scope: !3413)
!3499 = !DILocation(line: 1150, column: 25, scope: !3413)
!3500 = !DILocation(line: 1150, column: 23, scope: !3413)
!3501 = !DILocation(line: 1146, column: 9, scope: !3502)
!3502 = !DILexicalBlockFile(scope: !3448, file: !1, discriminator: 3)
!3503 = !DILocation(line: 1154, column: 33, scope: !3413)
!3504 = !DILocation(line: 1154, column: 42, scope: !3413)
!3505 = !DILocation(line: 1154, column: 40, scope: !3413)
!3506 = !DILocation(line: 1154, column: 27, scope: !3413)
!3507 = !DILocation(line: 1154, column: 25, scope: !3413)
!3508 = !DILocation(line: 1154, column: 13, scope: !3413)
!3509 = !DILocation(line: 1155, column: 16, scope: !3413)
!3510 = !DILocation(line: 1155, column: 23, scope: !3413)
!3511 = !DILocation(line: 1155, column: 14, scope: !3413)
!3512 = !DILocation(line: 1159, column: 13, scope: !3513)
!3513 = distinct !DILexicalBlock(scope: !3413, file: !1, line: 1159, column: 13)
!3514 = !DILocation(line: 1159, column: 19, scope: !3513)
!3515 = !DILocation(line: 1159, column: 17, scope: !3513)
!3516 = !DILocation(line: 1159, column: 13, scope: !3413)
!3517 = !DILocation(line: 1160, column: 30, scope: !3518)
!3518 = distinct !DILexicalBlock(scope: !3513, file: !1, line: 1159, column: 29)
!3519 = !DILocation(line: 1160, column: 13, scope: !3518)
!3520 = !DILocation(line: 1160, column: 16, scope: !3518)
!3521 = !DILocation(line: 1160, column: 28, scope: !3518)
!3522 = !DILocation(line: 1161, column: 24, scope: !3518)
!3523 = !DILocation(line: 1161, column: 22, scope: !3518)
!3524 = !DILocation(line: 1162, column: 17, scope: !3525)
!3525 = distinct !DILexicalBlock(scope: !3518, file: !1, line: 1162, column: 17)
!3526 = !DILocation(line: 1162, column: 24, scope: !3525)
!3527 = !DILocation(line: 1162, column: 21, scope: !3525)
!3528 = !DILocation(line: 1162, column: 17, scope: !3518)
!3529 = !DILocation(line: 1162, column: 36, scope: !3530)
!3530 = !DILexicalBlockFile(scope: !3525, file: !1, discriminator: 1)
!3531 = !DILocation(line: 1166, column: 31, scope: !3518)
!3532 = !DILocation(line: 1166, column: 39, scope: !3518)
!3533 = !DILocation(line: 1166, column: 26, scope: !3518)
!3534 = !DILocation(line: 1166, column: 24, scope: !3518)
!3535 = !DILocation(line: 1167, column: 31, scope: !3518)
!3536 = !DILocation(line: 1167, column: 26, scope: !3518)
!3537 = !DILocation(line: 1167, column: 24, scope: !3518)
!3538 = !DILocation(line: 1169, column: 9, scope: !3518)
!3539 = !DILocation(line: 1170, column: 5, scope: !3413)
!3540 = !DILocation(line: 1170, column: 32, scope: !3359)
!3541 = !DILocation(line: 1170, column: 44, scope: !3359)
!3542 = !DILocation(line: 1170, column: 42, scope: !3359)
!3543 = !DILocation(line: 1170, column: 27, scope: !3359)
!3544 = !DILocation(line: 1170, column: 25, scope: !3359)
!3545 = !DILocation(line: 1170, column: 54, scope: !3359)
!3546 = !DILocation(line: 1170, column: 52, scope: !3359)
!3547 = !DILocation(line: 1171, column: 14, scope: !237)
!3548 = !DILocation(line: 1171, column: 17, scope: !3359)
!3549 = !DILocation(line: 1171, column: 32, scope: !3359)
!3550 = !DILocation(line: 1170, column: 5, scope: !3456)
!3551 = !DILocation(line: 1173, column: 15, scope: !3552)
!3552 = distinct !DILexicalBlock(scope: !237, file: !1, line: 1173, column: 9)
!3553 = !DILocation(line: 1173, column: 27, scope: !3552)
!3554 = !DILocation(line: 1173, column: 30, scope: !3552)
!3555 = !DILocation(line: 1173, column: 24, scope: !3552)
!3556 = !DILocation(line: 1173, column: 9, scope: !237)
!3557 = !DILocation(line: 1173, column: 54, scope: !3558)
!3558 = !DILexicalBlockFile(scope: !3552, file: !1, discriminator: 1)
!3559 = !DILocation(line: 1173, column: 41, scope: !3558)
!3560 = !DILocation(line: 1174, column: 12, scope: !237)
!3561 = !DILocation(line: 1174, column: 15, scope: !237)
!3562 = !DILocation(line: 1174, column: 5, scope: !237)
!3563 = !DILocation(line: 1175, column: 1, scope: !237)
!3564 = !DILocalVariable(name: "s", arg: 1, scope: !240, file: !1, line: 1183, type: !24)
!3565 = !DILocation(line: 1183, column: 20, scope: !240)
!3566 = !DILocalVariable(name: "cur_match", arg: 2, scope: !240, file: !1, line: 1184, type: !110)
!3567 = !DILocation(line: 1184, column: 10, scope: !240)
!3568 = !DILocalVariable(name: "scan", scope: !240, file: !1, line: 1186, type: !36)
!3569 = !DILocation(line: 1186, column: 21, scope: !240)
!3570 = !DILocation(line: 1186, column: 28, scope: !240)
!3571 = !DILocation(line: 1186, column: 31, scope: !240)
!3572 = !DILocation(line: 1186, column: 40, scope: !240)
!3573 = !DILocation(line: 1186, column: 43, scope: !240)
!3574 = !DILocation(line: 1186, column: 38, scope: !240)
!3575 = !DILocalVariable(name: "match", scope: !240, file: !1, line: 1187, type: !36)
!3576 = !DILocation(line: 1187, column: 21, scope: !240)
!3577 = !DILocalVariable(name: "len", scope: !240, file: !1, line: 1188, type: !56)
!3578 = !DILocation(line: 1188, column: 18, scope: !240)
!3579 = !DILocalVariable(name: "strend", scope: !240, file: !1, line: 1189, type: !36)
!3580 = !DILocation(line: 1189, column: 21, scope: !240)
!3581 = !DILocation(line: 1189, column: 30, scope: !240)
!3582 = !DILocation(line: 1189, column: 33, scope: !240)
!3583 = !DILocation(line: 1189, column: 42, scope: !240)
!3584 = !DILocation(line: 1189, column: 45, scope: !240)
!3585 = !DILocation(line: 1189, column: 40, scope: !240)
!3586 = !DILocation(line: 1189, column: 54, scope: !240)
!3587 = !DILocation(line: 1200, column: 13, scope: !240)
!3588 = !DILocation(line: 1200, column: 16, scope: !240)
!3589 = !DILocation(line: 1200, column: 25, scope: !240)
!3590 = !DILocation(line: 1200, column: 23, scope: !240)
!3591 = !DILocation(line: 1200, column: 11, scope: !240)
!3592 = !DILocation(line: 1204, column: 9, scope: !3593)
!3593 = distinct !DILexicalBlock(scope: !240, file: !1, line: 1204, column: 9)
!3594 = !DILocation(line: 1204, column: 21, scope: !3593)
!3595 = !DILocation(line: 1204, column: 18, scope: !3593)
!3596 = !DILocation(line: 1204, column: 29, scope: !3593)
!3597 = !DILocation(line: 1204, column: 32, scope: !3598)
!3598 = !DILexicalBlockFile(scope: !3593, file: !1, discriminator: 1)
!3599 = !DILocation(line: 1204, column: 44, scope: !3598)
!3600 = !DILocation(line: 1204, column: 41, scope: !3598)
!3601 = !DILocation(line: 1204, column: 9, scope: !3598)
!3602 = !DILocation(line: 1204, column: 53, scope: !3603)
!3603 = !DILexicalBlockFile(scope: !3593, file: !1, discriminator: 2)
!3604 = !DILocation(line: 1212, column: 10, scope: !240)
!3605 = !DILocation(line: 1212, column: 22, scope: !240)
!3606 = !DILocation(line: 1218, column: 5, scope: !240)
!3607 = !DILocation(line: 1219, column: 5, scope: !3608)
!3608 = distinct !DILexicalBlock(scope: !240, file: !1, line: 1218, column: 8)
!3609 = !DILocation(line: 1219, column: 15, scope: !3610)
!3610 = !DILexicalBlockFile(scope: !240, file: !1, discriminator: 1)
!3611 = !DILocation(line: 1219, column: 14, scope: !3610)
!3612 = !DILocation(line: 1219, column: 26, scope: !3610)
!3613 = !DILocation(line: 1219, column: 25, scope: !3610)
!3614 = !DILocation(line: 1219, column: 22, scope: !3610)
!3615 = !DILocation(line: 1219, column: 34, scope: !3610)
!3616 = !DILocation(line: 1219, column: 38, scope: !3617)
!3617 = !DILexicalBlockFile(scope: !240, file: !1, discriminator: 2)
!3618 = !DILocation(line: 1219, column: 37, scope: !3617)
!3619 = !DILocation(line: 1219, column: 49, scope: !3617)
!3620 = !DILocation(line: 1219, column: 48, scope: !3617)
!3621 = !DILocation(line: 1219, column: 45, scope: !3617)
!3622 = !DILocation(line: 1219, column: 57, scope: !3617)
!3623 = !DILocation(line: 1220, column: 15, scope: !240)
!3624 = !DILocation(line: 1220, column: 14, scope: !240)
!3625 = !DILocation(line: 1220, column: 26, scope: !240)
!3626 = !DILocation(line: 1220, column: 25, scope: !240)
!3627 = !DILocation(line: 1220, column: 22, scope: !240)
!3628 = !DILocation(line: 1220, column: 34, scope: !240)
!3629 = !DILocation(line: 1220, column: 38, scope: !3610)
!3630 = !DILocation(line: 1220, column: 37, scope: !3610)
!3631 = !DILocation(line: 1220, column: 49, scope: !3610)
!3632 = !DILocation(line: 1220, column: 48, scope: !3610)
!3633 = !DILocation(line: 1220, column: 45, scope: !3610)
!3634 = !DILocation(line: 1220, column: 57, scope: !3610)
!3635 = !DILocation(line: 1221, column: 15, scope: !240)
!3636 = !DILocation(line: 1221, column: 14, scope: !240)
!3637 = !DILocation(line: 1221, column: 26, scope: !240)
!3638 = !DILocation(line: 1221, column: 25, scope: !240)
!3639 = !DILocation(line: 1221, column: 22, scope: !240)
!3640 = !DILocation(line: 1221, column: 34, scope: !240)
!3641 = !DILocation(line: 1221, column: 38, scope: !3610)
!3642 = !DILocation(line: 1221, column: 37, scope: !3610)
!3643 = !DILocation(line: 1221, column: 49, scope: !3610)
!3644 = !DILocation(line: 1221, column: 48, scope: !3610)
!3645 = !DILocation(line: 1221, column: 45, scope: !3610)
!3646 = !DILocation(line: 1221, column: 57, scope: !3610)
!3647 = !DILocation(line: 1222, column: 15, scope: !240)
!3648 = !DILocation(line: 1222, column: 14, scope: !240)
!3649 = !DILocation(line: 1222, column: 26, scope: !240)
!3650 = !DILocation(line: 1222, column: 25, scope: !240)
!3651 = !DILocation(line: 1222, column: 22, scope: !240)
!3652 = !DILocation(line: 1222, column: 34, scope: !240)
!3653 = !DILocation(line: 1222, column: 38, scope: !3610)
!3654 = !DILocation(line: 1222, column: 37, scope: !3610)
!3655 = !DILocation(line: 1222, column: 49, scope: !3610)
!3656 = !DILocation(line: 1222, column: 48, scope: !3610)
!3657 = !DILocation(line: 1222, column: 45, scope: !3610)
!3658 = !DILocation(line: 1222, column: 57, scope: !3610)
!3659 = !DILocation(line: 1223, column: 14, scope: !240)
!3660 = !DILocation(line: 1223, column: 21, scope: !240)
!3661 = !DILocation(line: 1223, column: 19, scope: !240)
!3662 = !DILocation(line: 1219, column: 5, scope: !3663)
!3663 = !DILexicalBlockFile(scope: !3608, file: !1, discriminator: 3)
!3664 = !DILocation(line: 1227, column: 29, scope: !240)
!3665 = !DILocation(line: 1227, column: 38, scope: !240)
!3666 = !DILocation(line: 1227, column: 36, scope: !240)
!3667 = !DILocation(line: 1227, column: 23, scope: !240)
!3668 = !DILocation(line: 1227, column: 21, scope: !240)
!3669 = !DILocation(line: 1227, column: 9, scope: !240)
!3670 = !DILocation(line: 1229, column: 9, scope: !3671)
!3671 = distinct !DILexicalBlock(scope: !240, file: !1, line: 1229, column: 9)
!3672 = !DILocation(line: 1229, column: 13, scope: !3671)
!3673 = !DILocation(line: 1229, column: 9, scope: !240)
!3674 = !DILocation(line: 1229, column: 26, scope: !3675)
!3675 = !DILexicalBlockFile(scope: !3671, file: !1, discriminator: 1)
!3676 = !DILocation(line: 1231, column: 22, scope: !240)
!3677 = !DILocation(line: 1231, column: 5, scope: !240)
!3678 = !DILocation(line: 1231, column: 8, scope: !240)
!3679 = !DILocation(line: 1231, column: 20, scope: !240)
!3680 = !DILocation(line: 1232, column: 18, scope: !240)
!3681 = !DILocation(line: 1232, column: 25, scope: !240)
!3682 = !DILocation(line: 1232, column: 28, scope: !240)
!3683 = !DILocation(line: 1232, column: 22, scope: !240)
!3684 = !DILocation(line: 1232, column: 12, scope: !240)
!3685 = !DILocation(line: 1232, column: 46, scope: !3610)
!3686 = !DILocation(line: 1232, column: 12, scope: !3610)
!3687 = !DILocation(line: 1232, column: 52, scope: !3617)
!3688 = !DILocation(line: 1232, column: 55, scope: !3617)
!3689 = !DILocation(line: 1232, column: 12, scope: !3617)
!3690 = !DILocation(line: 1232, column: 12, scope: !3691)
!3691 = !DILexicalBlockFile(scope: !240, file: !1, discriminator: 3)
!3692 = !DILocation(line: 1232, column: 5, scope: !3691)
!3693 = !DILocation(line: 1233, column: 1, scope: !240)
