; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma2_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type { i32, %struct.lzma_coder_s*, %struct.lzma_options_lzma, i8, i8, i8, i64, i64, i64, [65542 x i8] }
%struct.lzma_options_lzma = type { i32, i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i8*, i8* }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter_info_s = type { i64, {}*, i8* }
%struct.lzma_lz_encoder = type { %struct.lzma_coder_s*, i32 (%struct.lzma_coder_s*, %struct.lzma_mf_s*, i8*, i64*, i64)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*, %struct.lzma_filter*)* }
%struct.lzma_mf_s = type { i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32 (%struct.lzma_mf_s*, %struct.lzma_match*)*, void (%struct.lzma_mf_s*, i32)*, i32*, i32*, i32, i32, i32, i32, i32, i32, i32, i32, i32 }
%struct.lzma_match = type { i32, i32 }
%struct.lzma_lz_options = type { i64, i64, i64, i64, i64, i32, i32, i8*, i32 }

@.str = private unnamed_addr constant [37 x i8] c"coder->compressed_size <= (1U << 16)\00", align 1
@.str.1 = private unnamed_addr constant [83 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma2_encoder.c\00", align 1
@__PRETTY_FUNCTION__.lzma2_encode = private unnamed_addr constant [108 x i8] c"lzma_ret lzma2_encode(lzma_coder *restrict, lzma_mf *restrict, uint8_t *restrict, size_t *restrict, size_t)\00", align 1
@.str.2 = private unnamed_addr constant [39 x i8] c"coder->uncompressed_size <= (1U << 21)\00", align 1
@.str.3 = private unnamed_addr constant [29 x i8] c"coder->uncompressed_size > 0\00", align 1
@__PRETTY_FUNCTION__.lzma2_header_uncompressed = private unnamed_addr constant [45 x i8] c"void lzma2_header_uncompressed(lzma_coder *)\00", align 1
@.str.4 = private unnamed_addr constant [39 x i8] c"coder->uncompressed_size <= (1U << 16)\00", align 1
@__PRETTY_FUNCTION__.lzma2_header_lzma = private unnamed_addr constant [37 x i8] c"void lzma2_header_lzma(lzma_coder *)\00", align 1
@.str.5 = private unnamed_addr constant [27 x i8] c"coder->compressed_size > 0\00", align 1
@.str.6 = private unnamed_addr constant [20 x i8] c"mf->read_ahead == 0\00", align 1
@.str.7 = private unnamed_addr constant [78 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lz/lz_encoder.h\00", align 1
@__PRETTY_FUNCTION__.mf_read = private unnamed_addr constant [63 x i8] c"void mf_read(lzma_mf *, uint8_t *, size_t *, size_t, size_t *)\00", align 1
@.str.8 = private unnamed_addr constant [22 x i8] c"mf->read_pos >= *left\00", align 1
@lzma_fastpos = external constant [8192 x i8], align 16

; Function Attrs: nounwind uwtable
define i32 @lzma_lzma2_encoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter_info_s* %filters) #0 !dbg !117 {
entry:
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter_info_s*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !299, metadata !300), !dbg !301
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !302, metadata !300), !dbg !303
  store %struct.lzma_filter_info_s* %filters, %struct.lzma_filter_info_s** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_info_s** %filters.addr, metadata !304, metadata !300), !dbg !305
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !306
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !307
  %2 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !308
  %call = call i32 @lzma_lz_encoder_init(%struct.lzma_next_coder_s* %0, %struct.lzma_allocator* %1, %struct.lzma_filter_info_s* %2, i32 (%struct.lzma_lz_encoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)* @lzma2_encoder_init), !dbg !309
  ret i32 %call, !dbg !310
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @lzma_lz_encoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*, i32 (%struct.lzma_lz_encoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)*) #2

; Function Attrs: nounwind uwtable
define internal i32 @lzma2_encoder_init(%struct.lzma_lz_encoder* %lz, %struct.lzma_allocator* %allocator, i8* %options, %struct.lzma_lz_options* %lz_options) #0 !dbg !204 {
entry:
  %retval = alloca i32, align 4
  %lz.addr = alloca %struct.lzma_lz_encoder*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %options.addr = alloca i8*, align 8
  %lz_options.addr = alloca %struct.lzma_lz_options*, align 8
  %ret_ = alloca i32, align 4
  store %struct.lzma_lz_encoder* %lz, %struct.lzma_lz_encoder** %lz.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_lz_encoder** %lz.addr, metadata !311, metadata !300), !dbg !312
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !313, metadata !300), !dbg !314
  store i8* %options, i8** %options.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %options.addr, metadata !315, metadata !300), !dbg !316
  store %struct.lzma_lz_options* %lz_options, %struct.lzma_lz_options** %lz_options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_lz_options** %lz_options.addr, metadata !317, metadata !300), !dbg !318
  %0 = load i8*, i8** %options.addr, align 8, !dbg !319
  %cmp = icmp eq i8* %0, null, !dbg !321
  br i1 %cmp, label %if.then, label %if.end, !dbg !322

if.then:                                          ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !323
  br label %return, !dbg !323

if.end:                                           ; preds = %entry
  %1 = load %struct.lzma_lz_encoder*, %struct.lzma_lz_encoder** %lz.addr, align 8, !dbg !324
  %coder = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %1, i32 0, i32 0, !dbg !326
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !326
  %cmp1 = icmp eq %struct.lzma_coder_s* %2, null, !dbg !327
  br i1 %cmp1, label %if.then2, label %if.end9, !dbg !328

if.then2:                                         ; preds = %if.end
  %3 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !329
  %call = call noalias i8* @lzma_alloc(i64 65704, %struct.lzma_allocator* %3), !dbg !331
  %4 = bitcast i8* %call to %struct.lzma_coder_s*, !dbg !331
  %5 = load %struct.lzma_lz_encoder*, %struct.lzma_lz_encoder** %lz.addr, align 8, !dbg !332
  %coder3 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %5, i32 0, i32 0, !dbg !333
  store %struct.lzma_coder_s* %4, %struct.lzma_coder_s** %coder3, align 8, !dbg !334
  %6 = load %struct.lzma_lz_encoder*, %struct.lzma_lz_encoder** %lz.addr, align 8, !dbg !335
  %coder4 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %6, i32 0, i32 0, !dbg !337
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder4, align 8, !dbg !337
  %cmp5 = icmp eq %struct.lzma_coder_s* %7, null, !dbg !338
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !339

if.then6:                                         ; preds = %if.then2
  store i32 5, i32* %retval, align 4, !dbg !340
  br label %return, !dbg !340

if.end7:                                          ; preds = %if.then2
  %8 = load %struct.lzma_lz_encoder*, %struct.lzma_lz_encoder** %lz.addr, align 8, !dbg !341
  %code = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %8, i32 0, i32 1, !dbg !342
  store i32 (%struct.lzma_coder_s*, %struct.lzma_mf_s*, i8*, i64*, i64)* @lzma2_encode, i32 (%struct.lzma_coder_s*, %struct.lzma_mf_s*, i8*, i64*, i64)** %code, align 8, !dbg !343
  %9 = load %struct.lzma_lz_encoder*, %struct.lzma_lz_encoder** %lz.addr, align 8, !dbg !344
  %end = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %9, i32 0, i32 2, !dbg !345
  store void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* @lzma2_encoder_end, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !346
  %10 = load %struct.lzma_lz_encoder*, %struct.lzma_lz_encoder** %lz.addr, align 8, !dbg !347
  %options_update = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %10, i32 0, i32 3, !dbg !348
  store i32 (%struct.lzma_coder_s*, %struct.lzma_filter*)* @lzma2_encoder_options_update, i32 (%struct.lzma_coder_s*, %struct.lzma_filter*)** %options_update, align 8, !dbg !349
  %11 = load %struct.lzma_lz_encoder*, %struct.lzma_lz_encoder** %lz.addr, align 8, !dbg !350
  %coder8 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %11, i32 0, i32 0, !dbg !351
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder8, align 8, !dbg !351
  %lzma = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 1, !dbg !352
  store %struct.lzma_coder_s* null, %struct.lzma_coder_s** %lzma, align 8, !dbg !353
  br label %if.end9, !dbg !354

if.end9:                                          ; preds = %if.end7, %if.end
  %13 = load %struct.lzma_lz_encoder*, %struct.lzma_lz_encoder** %lz.addr, align 8, !dbg !355
  %coder10 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %13, i32 0, i32 0, !dbg !356
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder10, align 8, !dbg !356
  %opt_cur = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 2, !dbg !357
  %15 = load i8*, i8** %options.addr, align 8, !dbg !358
  %16 = bitcast i8* %15 to %struct.lzma_options_lzma*, !dbg !359
  %17 = bitcast %struct.lzma_options_lzma* %opt_cur to i8*, !dbg !360
  %18 = bitcast %struct.lzma_options_lzma* %16 to i8*, !dbg !360
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %17, i8* %18, i64 112, i32 8, i1 false), !dbg !360
  %19 = load %struct.lzma_lz_encoder*, %struct.lzma_lz_encoder** %lz.addr, align 8, !dbg !361
  %coder11 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %19, i32 0, i32 0, !dbg !362
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder11, align 8, !dbg !362
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %20, i32 0, i32 0, !dbg !363
  store i32 0, i32* %sequence, align 8, !dbg !364
  %21 = load %struct.lzma_lz_encoder*, %struct.lzma_lz_encoder** %lz.addr, align 8, !dbg !365
  %coder12 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %21, i32 0, i32 0, !dbg !366
  %22 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder12, align 8, !dbg !366
  %need_properties = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %22, i32 0, i32 3, !dbg !367
  store i8 1, i8* %need_properties, align 8, !dbg !368
  %23 = load %struct.lzma_lz_encoder*, %struct.lzma_lz_encoder** %lz.addr, align 8, !dbg !369
  %coder13 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %23, i32 0, i32 0, !dbg !370
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder13, align 8, !dbg !370
  %need_state_reset = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %24, i32 0, i32 4, !dbg !371
  store i8 0, i8* %need_state_reset, align 1, !dbg !372
  %25 = load %struct.lzma_lz_encoder*, %struct.lzma_lz_encoder** %lz.addr, align 8, !dbg !373
  %coder14 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %25, i32 0, i32 0, !dbg !374
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder14, align 8, !dbg !374
  %opt_cur15 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %26, i32 0, i32 2, !dbg !375
  %preset_dict = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %opt_cur15, i32 0, i32 1, !dbg !376
  %27 = load i8*, i8** %preset_dict, align 8, !dbg !376
  %cmp16 = icmp eq i8* %27, null, !dbg !377
  br i1 %cmp16, label %lor.end, label %lor.rhs, !dbg !378

lor.rhs:                                          ; preds = %if.end9
  %28 = load %struct.lzma_lz_encoder*, %struct.lzma_lz_encoder** %lz.addr, align 8, !dbg !379
  %coder17 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %28, i32 0, i32 0, !dbg !381
  %29 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder17, align 8, !dbg !381
  %opt_cur18 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %29, i32 0, i32 2, !dbg !382
  %preset_dict_size = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %opt_cur18, i32 0, i32 2, !dbg !383
  %30 = load i32, i32* %preset_dict_size, align 8, !dbg !383
  %cmp19 = icmp eq i32 %30, 0, !dbg !384
  br label %lor.end, !dbg !385

lor.end:                                          ; preds = %lor.rhs, %if.end9
  %31 = phi i1 [ true, %if.end9 ], [ %cmp19, %lor.rhs ]
  %32 = load %struct.lzma_lz_encoder*, %struct.lzma_lz_encoder** %lz.addr, align 8, !dbg !386
  %coder20 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %32, i32 0, i32 0, !dbg !387
  %33 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder20, align 8, !dbg !387
  %need_dictionary_reset = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %33, i32 0, i32 5, !dbg !388
  %frombool = zext i1 %31 to i8, !dbg !389
  store i8 %frombool, i8* %need_dictionary_reset, align 2, !dbg !389
  br label %do.body, !dbg !390

do.body:                                          ; preds = %lor.end
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !391, metadata !300), !dbg !394
  %34 = load %struct.lzma_lz_encoder*, %struct.lzma_lz_encoder** %lz.addr, align 8, !dbg !395
  %coder21 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %34, i32 0, i32 0, !dbg !395
  %35 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder21, align 8, !dbg !395
  %lzma22 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %35, i32 0, i32 1, !dbg !395
  %36 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !395
  %37 = load %struct.lzma_lz_encoder*, %struct.lzma_lz_encoder** %lz.addr, align 8, !dbg !395
  %coder23 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %37, i32 0, i32 0, !dbg !395
  %38 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder23, align 8, !dbg !395
  %opt_cur24 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %38, i32 0, i32 2, !dbg !395
  %39 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !395
  %call25 = call i32 @lzma_lzma_encoder_create(%struct.lzma_coder_s** %lzma22, %struct.lzma_allocator* %36, %struct.lzma_options_lzma* %opt_cur24, %struct.lzma_lz_options* %39), !dbg !395
  store i32 %call25, i32* %ret_, align 4, !dbg !395
  %40 = load i32, i32* %ret_, align 4, !dbg !395
  %cmp26 = icmp ne i32 %40, 0, !dbg !395
  br i1 %cmp26, label %if.then27, label %if.end28, !dbg !395

if.then27:                                        ; preds = %do.body
  %41 = load i32, i32* %ret_, align 4, !dbg !397
  store i32 %41, i32* %retval, align 4, !dbg !397
  br label %return, !dbg !397

if.end28:                                         ; preds = %do.body
  br label %do.end, !dbg !400

do.end:                                           ; preds = %if.end28
  %42 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !402
  %before_size = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %42, i32 0, i32 0, !dbg !404
  %43 = load i64, i64* %before_size, align 8, !dbg !404
  %44 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !405
  %dict_size = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %44, i32 0, i32 1, !dbg !406
  %45 = load i64, i64* %dict_size, align 8, !dbg !406
  %add = add i64 %43, %45, !dbg !407
  %cmp29 = icmp ult i64 %add, 65536, !dbg !408
  br i1 %cmp29, label %if.then30, label %if.end33, !dbg !409

if.then30:                                        ; preds = %do.end
  %46 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !410
  %dict_size31 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %46, i32 0, i32 1, !dbg !411
  %47 = load i64, i64* %dict_size31, align 8, !dbg !411
  %sub = sub i64 65536, %47, !dbg !412
  %48 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !413
  %before_size32 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %48, i32 0, i32 0, !dbg !414
  store i64 %sub, i64* %before_size32, align 8, !dbg !415
  br label %if.end33, !dbg !413

if.end33:                                         ; preds = %if.then30, %do.end
  store i32 0, i32* %retval, align 4, !dbg !416
  br label %return, !dbg !416

return:                                           ; preds = %if.end33, %if.then27, %if.then6, %if.then
  %49 = load i32, i32* %retval, align 4, !dbg !417
  ret i32 %49, !dbg !417
}

; Function Attrs: nounwind uwtable
define i64 @lzma_lzma2_encoder_memusage(i8* %options) #0 !dbg !196 {
entry:
  %retval = alloca i64, align 8
  %options.addr = alloca i8*, align 8
  %lzma_mem = alloca i64, align 8
  store i8* %options, i8** %options.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %options.addr, metadata !418, metadata !300), !dbg !419
  call void @llvm.dbg.declare(metadata i64* %lzma_mem, metadata !420, metadata !300), !dbg !422
  %0 = load i8*, i8** %options.addr, align 8, !dbg !423
  %call = call i64 @lzma_lzma_encoder_memusage(i8* %0), !dbg !424
  store i64 %call, i64* %lzma_mem, align 8, !dbg !422
  %1 = load i64, i64* %lzma_mem, align 8, !dbg !425
  %cmp = icmp eq i64 %1, -1, !dbg !427
  br i1 %cmp, label %if.then, label %if.end, !dbg !428

if.then:                                          ; preds = %entry
  store i64 -1, i64* %retval, align 8, !dbg !429
  br label %return, !dbg !429

if.end:                                           ; preds = %entry
  %2 = load i64, i64* %lzma_mem, align 8, !dbg !430
  %add = add i64 65704, %2, !dbg !431
  store i64 %add, i64* %retval, align 8, !dbg !432
  br label %return, !dbg !432

return:                                           ; preds = %if.end, %if.then
  %3 = load i64, i64* %retval, align 8, !dbg !433
  ret i64 %3, !dbg !433
}

declare i64 @lzma_lzma_encoder_memusage(i8*) #2

; Function Attrs: nounwind uwtable
define i32 @lzma_lzma2_props_encode(i8* %options, i8* %out) #0 !dbg !201 {
entry:
  %options.addr = alloca i8*, align 8
  %out.addr = alloca i8*, align 8
  %opt = alloca %struct.lzma_options_lzma*, align 8
  %d = alloca i32, align 4
  store i8* %options, i8** %options.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %options.addr, metadata !434, metadata !300), !dbg !435
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !436, metadata !300), !dbg !437
  call void @llvm.dbg.declare(metadata %struct.lzma_options_lzma** %opt, metadata !438, metadata !300), !dbg !440
  %0 = load i8*, i8** %options.addr, align 8, !dbg !441
  %1 = bitcast i8* %0 to %struct.lzma_options_lzma*, !dbg !441
  store %struct.lzma_options_lzma* %1, %struct.lzma_options_lzma** %opt, align 8, !dbg !440
  call void @llvm.dbg.declare(metadata i32* %d, metadata !442, metadata !300), !dbg !443
  %2 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !444
  %dict_size = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %2, i32 0, i32 0, !dbg !444
  %3 = load i32, i32* %dict_size, align 8, !dbg !444
  %cmp = icmp ugt i32 %3, 4096, !dbg !444
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !444

cond.true:                                        ; preds = %entry
  %4 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !445
  %dict_size1 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %4, i32 0, i32 0, !dbg !445
  %5 = load i32, i32* %dict_size1, align 8, !dbg !445
  br label %cond.end, !dbg !445

cond.false:                                       ; preds = %entry
  br label %cond.end, !dbg !447

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %5, %cond.true ], [ 4096, %cond.false ], !dbg !449
  store i32 %cond, i32* %d, align 4, !dbg !451
  %6 = load i32, i32* %d, align 4, !dbg !452
  %dec = add i32 %6, -1, !dbg !452
  store i32 %dec, i32* %d, align 4, !dbg !452
  %7 = load i32, i32* %d, align 4, !dbg !453
  %shr = lshr i32 %7, 2, !dbg !454
  %8 = load i32, i32* %d, align 4, !dbg !455
  %or = or i32 %8, %shr, !dbg !455
  store i32 %or, i32* %d, align 4, !dbg !455
  %9 = load i32, i32* %d, align 4, !dbg !456
  %shr2 = lshr i32 %9, 3, !dbg !457
  %10 = load i32, i32* %d, align 4, !dbg !458
  %or3 = or i32 %10, %shr2, !dbg !458
  store i32 %or3, i32* %d, align 4, !dbg !458
  %11 = load i32, i32* %d, align 4, !dbg !459
  %shr4 = lshr i32 %11, 4, !dbg !460
  %12 = load i32, i32* %d, align 4, !dbg !461
  %or5 = or i32 %12, %shr4, !dbg !461
  store i32 %or5, i32* %d, align 4, !dbg !461
  %13 = load i32, i32* %d, align 4, !dbg !462
  %shr6 = lshr i32 %13, 8, !dbg !463
  %14 = load i32, i32* %d, align 4, !dbg !464
  %or7 = or i32 %14, %shr6, !dbg !464
  store i32 %or7, i32* %d, align 4, !dbg !464
  %15 = load i32, i32* %d, align 4, !dbg !465
  %shr8 = lshr i32 %15, 16, !dbg !466
  %16 = load i32, i32* %d, align 4, !dbg !467
  %or9 = or i32 %16, %shr8, !dbg !467
  store i32 %or9, i32* %d, align 4, !dbg !467
  %17 = load i32, i32* %d, align 4, !dbg !468
  %cmp10 = icmp eq i32 %17, -1, !dbg !470
  br i1 %cmp10, label %if.then, label %if.else, !dbg !471

if.then:                                          ; preds = %cond.end
  %18 = load i8*, i8** %out.addr, align 8, !dbg !472
  %arrayidx = getelementptr inbounds i8, i8* %18, i64 0, !dbg !472
  store i8 40, i8* %arrayidx, align 1, !dbg !473
  br label %if.end, !dbg !472

if.else:                                          ; preds = %cond.end
  %19 = load i32, i32* %d, align 4, !dbg !474
  %add = add i32 %19, 1, !dbg !475
  %call = call i32 @get_pos_slot(i32 %add), !dbg !476
  %sub = sub i32 %call, 24, !dbg !477
  %conv = trunc i32 %sub to i8, !dbg !476
  %20 = load i8*, i8** %out.addr, align 8, !dbg !478
  %arrayidx11 = getelementptr inbounds i8, i8* %20, i64 0, !dbg !478
  store i8 %conv, i8* %arrayidx11, align 1, !dbg !479
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret i32 0, !dbg !480
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @get_pos_slot(i32 %pos) #3 !dbg !292 {
entry:
  %retval = alloca i32, align 4
  %pos.addr = alloca i32, align 4
  store i32 %pos, i32* %pos.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pos.addr, metadata !481, metadata !300), !dbg !482
  %0 = load i32, i32* %pos.addr, align 4, !dbg !483
  %cmp = icmp ult i32 %0, 8192, !dbg !485
  br i1 %cmp, label %if.then, label %if.end, !dbg !486

if.then:                                          ; preds = %entry
  %1 = load i32, i32* %pos.addr, align 4, !dbg !487
  %idxprom = zext i32 %1 to i64, !dbg !488
  %arrayidx = getelementptr inbounds [8192 x i8], [8192 x i8]* @lzma_fastpos, i64 0, i64 %idxprom, !dbg !488
  %2 = load i8, i8* %arrayidx, align 1, !dbg !488
  %conv = zext i8 %2 to i32, !dbg !488
  store i32 %conv, i32* %retval, align 4, !dbg !489
  br label %return, !dbg !489

if.end:                                           ; preds = %entry
  %3 = load i32, i32* %pos.addr, align 4, !dbg !490
  %cmp1 = icmp ult i32 %3, 33554432, !dbg !492
  br i1 %cmp1, label %if.then3, label %if.end7, !dbg !493

if.then3:                                         ; preds = %if.end
  %4 = load i32, i32* %pos.addr, align 4, !dbg !494
  %shr = lshr i32 %4, 12, !dbg !494
  %idxprom4 = zext i32 %shr to i64, !dbg !494
  %arrayidx5 = getelementptr inbounds [8192 x i8], [8192 x i8]* @lzma_fastpos, i64 0, i64 %idxprom4, !dbg !494
  %5 = load i8, i8* %arrayidx5, align 1, !dbg !494
  %conv6 = zext i8 %5 to i32, !dbg !494
  %add = add nsw i32 %conv6, 24, !dbg !494
  store i32 %add, i32* %retval, align 4, !dbg !495
  br label %return, !dbg !495

if.end7:                                          ; preds = %if.end
  %6 = load i32, i32* %pos.addr, align 4, !dbg !496
  %shr8 = lshr i32 %6, 24, !dbg !496
  %idxprom9 = zext i32 %shr8 to i64, !dbg !496
  %arrayidx10 = getelementptr inbounds [8192 x i8], [8192 x i8]* @lzma_fastpos, i64 0, i64 %idxprom9, !dbg !496
  %7 = load i8, i8* %arrayidx10, align 1, !dbg !496
  %conv11 = zext i8 %7 to i32, !dbg !496
  %add12 = add nsw i32 %conv11, 48, !dbg !496
  store i32 %add12, i32* %retval, align 4, !dbg !497
  br label %return, !dbg !497

return:                                           ; preds = %if.end7, %if.then3, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !498
  ret i32 %8, !dbg !498
}

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #2

; Function Attrs: nounwind uwtable
define internal i32 @lzma2_encode(%struct.lzma_coder_s* noalias %coder, %struct.lzma_mf_s* noalias %mf, i8* noalias %out, i64* noalias %out_pos, i64 %out_size) #0 !dbg !277 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %ret_ = alloca i32, align 4
  %read_start = alloca i32, align 4
  %ret = alloca i32, align 4
  %left = alloca i32, align 4
  %limit = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !499, metadata !300), !dbg !500
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !501, metadata !300), !dbg !502
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !503, metadata !300), !dbg !504
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !505, metadata !300), !dbg !506
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !507, metadata !300), !dbg !508
  br label %while.cond, !dbg !509

while.cond:                                       ; preds = %sw.epilog, %entry
  %0 = load i64*, i64** %out_pos.addr, align 8, !dbg !510
  %1 = load i64, i64* %0, align 8, !dbg !512
  %2 = load i64, i64* %out_size.addr, align 8, !dbg !513
  %cmp = icmp ult i64 %1, %2, !dbg !514
  br i1 %cmp, label %while.body, label %while.end, !dbg !515

while.body:                                       ; preds = %while.cond
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !516
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %3, i32 0, i32 0, !dbg !517
  %4 = load i32, i32* %sequence, align 8, !dbg !517
  switch i32 %4, label %sw.epilog [
    i32 0, label %sw.bb
    i32 1, label %sw.bb14
    i32 2, label %sw.bb69
    i32 3, label %sw.bb81
    i32 4, label %sw.bb92
  ], !dbg !518

sw.bb:                                            ; preds = %while.body
  %5 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !519
  %call = call i32 @mf_unencoded(%struct.lzma_mf_s* %5), !dbg !522
  %cmp1 = icmp eq i32 %call, 0, !dbg !523
  br i1 %cmp1, label %if.then, label %if.end6, !dbg !524

if.then:                                          ; preds = %sw.bb
  %6 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !525
  %action = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %6, i32 0, i32 20, !dbg !528
  %7 = load i32, i32* %action, align 8, !dbg !528
  %cmp2 = icmp eq i32 %7, 3, !dbg !529
  br i1 %cmp2, label %if.then3, label %if.end, !dbg !530

if.then3:                                         ; preds = %if.then
  %8 = load i64*, i64** %out_pos.addr, align 8, !dbg !531
  %9 = load i64, i64* %8, align 8, !dbg !532
  %inc = add i64 %9, 1, !dbg !532
  store i64 %inc, i64* %8, align 8, !dbg !532
  %10 = load i8*, i8** %out.addr, align 8, !dbg !533
  %arrayidx = getelementptr inbounds i8, i8* %10, i64 %9, !dbg !533
  store i8 0, i8* %arrayidx, align 1, !dbg !534
  br label %if.end, !dbg !533

if.end:                                           ; preds = %if.then3, %if.then
  %11 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !535
  %action4 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %11, i32 0, i32 20, !dbg !536
  %12 = load i32, i32* %action4, align 8, !dbg !536
  %cmp5 = icmp eq i32 %12, 0, !dbg !537
  %cond = select i1 %cmp5, i32 0, i32 1, !dbg !535
  store i32 %cond, i32* %retval, align 4, !dbg !538
  br label %return, !dbg !538

if.end6:                                          ; preds = %sw.bb
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !539
  %need_state_reset = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %13, i32 0, i32 4, !dbg !541
  %14 = load i8, i8* %need_state_reset, align 1, !dbg !541
  %tobool = trunc i8 %14 to i1, !dbg !541
  br i1 %tobool, label %if.then7, label %if.end12, !dbg !542

if.then7:                                         ; preds = %if.end6
  br label %do.body, !dbg !543

do.body:                                          ; preds = %if.then7
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !544, metadata !300), !dbg !546
  %15 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !547
  %lzma = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %15, i32 0, i32 1, !dbg !547
  %16 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %lzma, align 8, !dbg !547
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !547
  %opt_cur = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %17, i32 0, i32 2, !dbg !547
  %call8 = call i32 @lzma_lzma_encoder_reset(%struct.lzma_coder_s* %16, %struct.lzma_options_lzma* %opt_cur), !dbg !547
  store i32 %call8, i32* %ret_, align 4, !dbg !547
  %18 = load i32, i32* %ret_, align 4, !dbg !547
  %cmp9 = icmp ne i32 %18, 0, !dbg !547
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !547

if.then10:                                        ; preds = %do.body
  %19 = load i32, i32* %ret_, align 4, !dbg !549
  store i32 %19, i32* %retval, align 4, !dbg !549
  br label %return, !dbg !549

if.end11:                                         ; preds = %do.body
  br label %do.end, !dbg !552

do.end:                                           ; preds = %if.end11
  br label %if.end12, !dbg !554

if.end12:                                         ; preds = %do.end, %if.end6
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !556
  %uncompressed_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %20, i32 0, i32 6, !dbg !557
  store i64 0, i64* %uncompressed_size, align 8, !dbg !558
  %21 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !559
  %compressed_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %21, i32 0, i32 7, !dbg !560
  store i64 0, i64* %compressed_size, align 8, !dbg !561
  %22 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !562
  %sequence13 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %22, i32 0, i32 0, !dbg !563
  store i32 1, i32* %sequence13, align 8, !dbg !564
  br label %sw.bb14, !dbg !562

sw.bb14:                                          ; preds = %while.body, %if.end12
  call void @llvm.dbg.declare(metadata i32* %read_start, metadata !565, metadata !300), !dbg !567
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !568, metadata !300), !dbg !569
  call void @llvm.dbg.declare(metadata i32* %left, metadata !570, metadata !300), !dbg !572
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !573
  %uncompressed_size15 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 6, !dbg !574
  %24 = load i64, i64* %uncompressed_size15, align 8, !dbg !574
  %sub = sub i64 2097152, %24, !dbg !575
  %conv = trunc i64 %sub to i32, !dbg !576
  store i32 %conv, i32* %left, align 4, !dbg !572
  call void @llvm.dbg.declare(metadata i32* %limit, metadata !577, metadata !300), !dbg !578
  %25 = load i32, i32* %left, align 4, !dbg !579
  %26 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !581
  %match_len_max = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %26, i32 0, i32 19, !dbg !582
  %27 = load i32, i32* %match_len_max, align 4, !dbg !582
  %cmp16 = icmp ult i32 %25, %27, !dbg !583
  br i1 %cmp16, label %if.then18, label %if.else, !dbg !584

if.then18:                                        ; preds = %sw.bb14
  store i32 0, i32* %limit, align 4, !dbg !585
  br label %if.end22, !dbg !587

if.else:                                          ; preds = %sw.bb14
  %28 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !588
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %28, i32 0, i32 5, !dbg !590
  %29 = load i32, i32* %read_pos, align 8, !dbg !590
  %30 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !591
  %read_ahead = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %30, i32 0, i32 6, !dbg !592
  %31 = load i32, i32* %read_ahead, align 4, !dbg !592
  %sub19 = sub i32 %29, %31, !dbg !593
  %32 = load i32, i32* %left, align 4, !dbg !594
  %add = add i32 %sub19, %32, !dbg !595
  %33 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !596
  %match_len_max20 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %33, i32 0, i32 19, !dbg !597
  %34 = load i32, i32* %match_len_max20, align 4, !dbg !597
  %sub21 = sub i32 %add, %34, !dbg !598
  store i32 %sub21, i32* %limit, align 4, !dbg !599
  br label %if.end22

if.end22:                                         ; preds = %if.else, %if.then18
  %35 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !600
  %read_pos23 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %35, i32 0, i32 5, !dbg !601
  %36 = load i32, i32* %read_pos23, align 8, !dbg !601
  %37 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !602
  %read_ahead24 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %37, i32 0, i32 6, !dbg !603
  %38 = load i32, i32* %read_ahead24, align 4, !dbg !603
  %sub25 = sub i32 %36, %38, !dbg !604
  store i32 %sub25, i32* %read_start, align 4, !dbg !605
  %39 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !606
  %lzma26 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %39, i32 0, i32 1, !dbg !607
  %40 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %lzma26, align 8, !dbg !607
  %41 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !608
  %42 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !609
  %buf = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %42, i32 0, i32 9, !dbg !610
  %arraydecay = getelementptr inbounds [65542 x i8], [65542 x i8]* %buf, i32 0, i32 0, !dbg !609
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay, i64 6, !dbg !611
  %43 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !612
  %compressed_size27 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %43, i32 0, i32 7, !dbg !613
  %44 = load i32, i32* %limit, align 4, !dbg !614
  %call28 = call i32 @lzma_lzma_encode(%struct.lzma_coder_s* %40, %struct.lzma_mf_s* %41, i8* %add.ptr, i64* %compressed_size27, i64 65536, i32 %44), !dbg !615
  store i32 %call28, i32* %ret, align 4, !dbg !616
  %45 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !617
  %read_pos29 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %45, i32 0, i32 5, !dbg !618
  %46 = load i32, i32* %read_pos29, align 8, !dbg !618
  %47 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !619
  %read_ahead30 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %47, i32 0, i32 6, !dbg !620
  %48 = load i32, i32* %read_ahead30, align 4, !dbg !620
  %sub31 = sub i32 %46, %48, !dbg !621
  %49 = load i32, i32* %read_start, align 4, !dbg !622
  %sub32 = sub i32 %sub31, %49, !dbg !623
  %conv33 = zext i32 %sub32 to i64, !dbg !617
  %50 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !624
  %uncompressed_size34 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %50, i32 0, i32 6, !dbg !625
  %51 = load i64, i64* %uncompressed_size34, align 8, !dbg !626
  %add35 = add i64 %51, %conv33, !dbg !626
  store i64 %add35, i64* %uncompressed_size34, align 8, !dbg !626
  %52 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !627
  %compressed_size36 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %52, i32 0, i32 7, !dbg !627
  %53 = load i64, i64* %compressed_size36, align 8, !dbg !627
  %cmp37 = icmp ule i64 %53, 65536, !dbg !627
  br i1 %cmp37, label %cond.true, label %cond.false, !dbg !627

cond.true:                                        ; preds = %if.end22
  br label %cond.end, !dbg !628

cond.false:                                       ; preds = %if.end22
  call void @__assert_fail(i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([83 x i8], [83 x i8]* @.str.1, i32 0, i32 0), i32 200, i8* getelementptr inbounds ([108 x i8], [108 x i8]* @__PRETTY_FUNCTION__.lzma2_encode, i32 0, i32 0)) #6, !dbg !630
  unreachable, !dbg !630
                                                  ; No predecessors!
  br label %cond.end, !dbg !632

cond.end:                                         ; preds = %54, %cond.true
  %55 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !634
  %uncompressed_size39 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %55, i32 0, i32 6, !dbg !634
  %56 = load i64, i64* %uncompressed_size39, align 8, !dbg !634
  %cmp40 = icmp ule i64 %56, 2097152, !dbg !634
  br i1 %cmp40, label %cond.true42, label %cond.false43, !dbg !634

cond.true42:                                      ; preds = %cond.end
  br label %cond.end44, !dbg !635

cond.false43:                                     ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([83 x i8], [83 x i8]* @.str.1, i32 0, i32 0), i32 201, i8* getelementptr inbounds ([108 x i8], [108 x i8]* @__PRETTY_FUNCTION__.lzma2_encode, i32 0, i32 0)) #6, !dbg !636
  unreachable, !dbg !636
                                                  ; No predecessors!
  br label %cond.end44, !dbg !637

cond.end44:                                       ; preds = %57, %cond.true42
  %58 = load i32, i32* %ret, align 4, !dbg !638
  %cmp45 = icmp ne i32 %58, 1, !dbg !640
  br i1 %cmp45, label %if.then47, label %if.end48, !dbg !641

if.then47:                                        ; preds = %cond.end44
  store i32 0, i32* %retval, align 4, !dbg !642
  br label %return, !dbg !642

if.end48:                                         ; preds = %cond.end44
  %59 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !643
  %compressed_size49 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %59, i32 0, i32 7, !dbg !645
  %60 = load i64, i64* %compressed_size49, align 8, !dbg !645
  %61 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !646
  %uncompressed_size50 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %61, i32 0, i32 6, !dbg !647
  %62 = load i64, i64* %uncompressed_size50, align 8, !dbg !647
  %cmp51 = icmp uge i64 %60, %62, !dbg !648
  br i1 %cmp51, label %if.then53, label %if.end67, !dbg !649

if.then53:                                        ; preds = %if.end48
  %63 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !650
  %read_ahead54 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %63, i32 0, i32 6, !dbg !652
  %64 = load i32, i32* %read_ahead54, align 4, !dbg !652
  %conv55 = zext i32 %64 to i64, !dbg !650
  %65 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !653
  %uncompressed_size56 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %65, i32 0, i32 6, !dbg !654
  %66 = load i64, i64* %uncompressed_size56, align 8, !dbg !655
  %add57 = add i64 %66, %conv55, !dbg !655
  store i64 %add57, i64* %uncompressed_size56, align 8, !dbg !655
  %67 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !656
  %uncompressed_size58 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %67, i32 0, i32 6, !dbg !656
  %68 = load i64, i64* %uncompressed_size58, align 8, !dbg !656
  %cmp59 = icmp ule i64 %68, 2097152, !dbg !656
  br i1 %cmp59, label %cond.true61, label %cond.false62, !dbg !656

cond.true61:                                      ; preds = %if.then53
  br label %cond.end63, !dbg !657

cond.false62:                                     ; preds = %if.then53
  call void @__assert_fail(i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([83 x i8], [83 x i8]* @.str.1, i32 0, i32 0), i32 212, i8* getelementptr inbounds ([108 x i8], [108 x i8]* @__PRETTY_FUNCTION__.lzma2_encode, i32 0, i32 0)) #6, !dbg !659
  unreachable, !dbg !659
                                                  ; No predecessors!
  br label %cond.end63, !dbg !661

cond.end63:                                       ; preds = %69, %cond.true61
  %70 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !663
  %read_ahead64 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %70, i32 0, i32 6, !dbg !664
  store i32 0, i32* %read_ahead64, align 4, !dbg !665
  %71 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !666
  call void @lzma2_header_uncompressed(%struct.lzma_coder_s* %71), !dbg !667
  %72 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !668
  %need_state_reset65 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %72, i32 0, i32 4, !dbg !669
  store i8 1, i8* %need_state_reset65, align 1, !dbg !670
  %73 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !671
  %sequence66 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %73, i32 0, i32 0, !dbg !672
  store i32 3, i32* %sequence66, align 8, !dbg !673
  br label %sw.epilog, !dbg !674

if.end67:                                         ; preds = %if.end48
  %74 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !675
  call void @lzma2_header_lzma(%struct.lzma_coder_s* %74), !dbg !676
  %75 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !677
  %sequence68 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %75, i32 0, i32 0, !dbg !678
  store i32 2, i32* %sequence68, align 8, !dbg !679
  br label %sw.bb69, !dbg !680

sw.bb69:                                          ; preds = %while.body, %if.end67
  %76 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !681
  %buf70 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %76, i32 0, i32 9, !dbg !682
  %arraydecay71 = getelementptr inbounds [65542 x i8], [65542 x i8]* %buf70, i32 0, i32 0, !dbg !681
  %77 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !683
  %buf_pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %77, i32 0, i32 8, !dbg !684
  %78 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !685
  %compressed_size72 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %78, i32 0, i32 7, !dbg !686
  %79 = load i64, i64* %compressed_size72, align 8, !dbg !686
  %80 = load i8*, i8** %out.addr, align 8, !dbg !687
  %81 = load i64*, i64** %out_pos.addr, align 8, !dbg !688
  %82 = load i64, i64* %out_size.addr, align 8, !dbg !689
  %call73 = call i64 @lzma_bufcpy(i8* %arraydecay71, i64* %buf_pos, i64 %79, i8* %80, i64* %81, i64 %82), !dbg !690
  %83 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !691
  %buf_pos74 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %83, i32 0, i32 8, !dbg !693
  %84 = load i64, i64* %buf_pos74, align 8, !dbg !693
  %85 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !694
  %compressed_size75 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %85, i32 0, i32 7, !dbg !695
  %86 = load i64, i64* %compressed_size75, align 8, !dbg !695
  %cmp76 = icmp ne i64 %84, %86, !dbg !696
  br i1 %cmp76, label %if.then78, label %if.end79, !dbg !697

if.then78:                                        ; preds = %sw.bb69
  store i32 0, i32* %retval, align 4, !dbg !698
  br label %return, !dbg !698

if.end79:                                         ; preds = %sw.bb69
  %87 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !699
  %sequence80 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %87, i32 0, i32 0, !dbg !700
  store i32 0, i32* %sequence80, align 8, !dbg !701
  br label %sw.epilog, !dbg !702

sw.bb81:                                          ; preds = %while.body
  %88 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !703
  %buf82 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %88, i32 0, i32 9, !dbg !704
  %arraydecay83 = getelementptr inbounds [65542 x i8], [65542 x i8]* %buf82, i32 0, i32 0, !dbg !703
  %89 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !705
  %buf_pos84 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %89, i32 0, i32 8, !dbg !706
  %90 = load i8*, i8** %out.addr, align 8, !dbg !707
  %91 = load i64*, i64** %out_pos.addr, align 8, !dbg !708
  %92 = load i64, i64* %out_size.addr, align 8, !dbg !709
  %call85 = call i64 @lzma_bufcpy(i8* %arraydecay83, i64* %buf_pos84, i64 3, i8* %90, i64* %91, i64 %92), !dbg !710
  %93 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !711
  %buf_pos86 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %93, i32 0, i32 8, !dbg !713
  %94 = load i64, i64* %buf_pos86, align 8, !dbg !713
  %cmp87 = icmp ne i64 %94, 3, !dbg !714
  br i1 %cmp87, label %if.then89, label %if.end90, !dbg !715

if.then89:                                        ; preds = %sw.bb81
  store i32 0, i32* %retval, align 4, !dbg !716
  br label %return, !dbg !716

if.end90:                                         ; preds = %sw.bb81
  %95 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !717
  %sequence91 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %95, i32 0, i32 0, !dbg !718
  store i32 4, i32* %sequence91, align 8, !dbg !719
  br label %sw.bb92, !dbg !717

sw.bb92:                                          ; preds = %while.body, %if.end90
  %96 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !720
  %97 = load i8*, i8** %out.addr, align 8, !dbg !721
  %98 = load i64*, i64** %out_pos.addr, align 8, !dbg !722
  %99 = load i64, i64* %out_size.addr, align 8, !dbg !723
  %100 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !724
  %uncompressed_size93 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %100, i32 0, i32 6, !dbg !725
  call void @mf_read(%struct.lzma_mf_s* %96, i8* %97, i64* %98, i64 %99, i64* %uncompressed_size93), !dbg !726
  %101 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !727
  %uncompressed_size94 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %101, i32 0, i32 6, !dbg !729
  %102 = load i64, i64* %uncompressed_size94, align 8, !dbg !729
  %cmp95 = icmp ne i64 %102, 0, !dbg !730
  br i1 %cmp95, label %if.then97, label %if.end98, !dbg !731

if.then97:                                        ; preds = %sw.bb92
  store i32 0, i32* %retval, align 4, !dbg !732
  br label %return, !dbg !732

if.end98:                                         ; preds = %sw.bb92
  %103 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !733
  %sequence99 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %103, i32 0, i32 0, !dbg !734
  store i32 0, i32* %sequence99, align 8, !dbg !735
  br label %sw.epilog, !dbg !736

sw.epilog:                                        ; preds = %while.body, %if.end98, %if.end79, %cond.end63
  br label %while.cond, !dbg !737

while.end:                                        ; preds = %while.cond
  store i32 0, i32* %retval, align 4, !dbg !739
  br label %return, !dbg !739

return:                                           ; preds = %while.end, %if.then97, %if.then89, %if.then78, %if.then47, %if.then10, %if.end
  %104 = load i32, i32* %retval, align 4, !dbg !740
  ret i32 %104, !dbg !740
}

; Function Attrs: nounwind uwtable
define internal void @lzma2_encoder_end(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator) #0 !dbg !290 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !741, metadata !300), !dbg !742
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !743, metadata !300), !dbg !744
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !745
  %lzma = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 1, !dbg !746
  %1 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %lzma, align 8, !dbg !746
  %2 = bitcast %struct.lzma_coder_s* %1 to i8*, !dbg !745
  %3 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !747
  call void @lzma_free(i8* %2, %struct.lzma_allocator* %3), !dbg !748
  %4 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !749
  %5 = bitcast %struct.lzma_coder_s* %4 to i8*, !dbg !749
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !750
  call void @lzma_free(i8* %5, %struct.lzma_allocator* %6), !dbg !751
  ret void, !dbg !752
}

; Function Attrs: nounwind uwtable
define internal i32 @lzma2_encoder_options_update(%struct.lzma_coder_s* %coder, %struct.lzma_filter* %filter) #0 !dbg !291 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %filter.addr = alloca %struct.lzma_filter*, align 8
  %opt = alloca %struct.lzma_options_lzma*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !753, metadata !300), !dbg !754
  store %struct.lzma_filter* %filter, %struct.lzma_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filter.addr, metadata !755, metadata !300), !dbg !756
  call void @llvm.dbg.declare(metadata %struct.lzma_options_lzma** %opt, metadata !757, metadata !300), !dbg !759
  %0 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !760
  %options = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %0, i32 0, i32 1, !dbg !762
  %1 = load i8*, i8** %options, align 8, !dbg !762
  %cmp = icmp eq i8* %1, null, !dbg !763
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !764

lor.lhs.false:                                    ; preds = %entry
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !765
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 0, !dbg !767
  %3 = load i32, i32* %sequence, align 8, !dbg !767
  %cmp1 = icmp ne i32 %3, 0, !dbg !768
  br i1 %cmp1, label %if.then, label %if.end, !dbg !769

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 11, i32* %retval, align 4, !dbg !770
  br label %return, !dbg !770

if.end:                                           ; preds = %lor.lhs.false
  %4 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !771
  %options2 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %4, i32 0, i32 1, !dbg !772
  %5 = load i8*, i8** %options2, align 8, !dbg !772
  %6 = bitcast i8* %5 to %struct.lzma_options_lzma*, !dbg !771
  store %struct.lzma_options_lzma* %6, %struct.lzma_options_lzma** %opt, align 8, !dbg !773
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !774
  %opt_cur = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 2, !dbg !776
  %lc = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %opt_cur, i32 0, i32 3, !dbg !777
  %8 = load i32, i32* %lc, align 4, !dbg !777
  %9 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !778
  %lc3 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %9, i32 0, i32 3, !dbg !779
  %10 = load i32, i32* %lc3, align 4, !dbg !779
  %cmp4 = icmp ne i32 %8, %10, !dbg !780
  br i1 %cmp4, label %if.then13, label %lor.lhs.false5, !dbg !781

lor.lhs.false5:                                   ; preds = %if.end
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !782
  %opt_cur6 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 2, !dbg !784
  %lp = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %opt_cur6, i32 0, i32 4, !dbg !785
  %12 = load i32, i32* %lp, align 8, !dbg !785
  %13 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !786
  %lp7 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %13, i32 0, i32 4, !dbg !787
  %14 = load i32, i32* %lp7, align 8, !dbg !787
  %cmp8 = icmp ne i32 %12, %14, !dbg !788
  br i1 %cmp8, label %if.then13, label %lor.lhs.false9, !dbg !789

lor.lhs.false9:                                   ; preds = %lor.lhs.false5
  %15 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !790
  %opt_cur10 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %15, i32 0, i32 2, !dbg !791
  %pb = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %opt_cur10, i32 0, i32 5, !dbg !792
  %16 = load i32, i32* %pb, align 4, !dbg !792
  %17 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !793
  %pb11 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %17, i32 0, i32 5, !dbg !794
  %18 = load i32, i32* %pb11, align 4, !dbg !794
  %cmp12 = icmp ne i32 %16, %18, !dbg !795
  br i1 %cmp12, label %if.then13, label %if.end37, !dbg !796

if.then13:                                        ; preds = %lor.lhs.false9, %lor.lhs.false5, %if.end
  %19 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !798
  %lc14 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %19, i32 0, i32 3, !dbg !801
  %20 = load i32, i32* %lc14, align 4, !dbg !801
  %cmp15 = icmp ugt i32 %20, 4, !dbg !802
  br i1 %cmp15, label %if.then26, label %lor.lhs.false16, !dbg !803

lor.lhs.false16:                                  ; preds = %if.then13
  %21 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !804
  %lp17 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %21, i32 0, i32 4, !dbg !806
  %22 = load i32, i32* %lp17, align 8, !dbg !806
  %cmp18 = icmp ugt i32 %22, 4, !dbg !807
  br i1 %cmp18, label %if.then26, label %lor.lhs.false19, !dbg !808

lor.lhs.false19:                                  ; preds = %lor.lhs.false16
  %23 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !809
  %lc20 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %23, i32 0, i32 3, !dbg !810
  %24 = load i32, i32* %lc20, align 4, !dbg !810
  %25 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !811
  %lp21 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %25, i32 0, i32 4, !dbg !812
  %26 = load i32, i32* %lp21, align 8, !dbg !812
  %add = add i32 %24, %26, !dbg !813
  %cmp22 = icmp ugt i32 %add, 4, !dbg !814
  br i1 %cmp22, label %if.then26, label %lor.lhs.false23, !dbg !815

lor.lhs.false23:                                  ; preds = %lor.lhs.false19
  %27 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !816
  %pb24 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %27, i32 0, i32 5, !dbg !817
  %28 = load i32, i32* %pb24, align 4, !dbg !817
  %cmp25 = icmp ugt i32 %28, 4, !dbg !818
  br i1 %cmp25, label %if.then26, label %if.end27, !dbg !819

if.then26:                                        ; preds = %lor.lhs.false23, %lor.lhs.false19, %lor.lhs.false16, %if.then13
  store i32 8, i32* %retval, align 4, !dbg !821
  br label %return, !dbg !821

if.end27:                                         ; preds = %lor.lhs.false23
  %29 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !822
  %lc28 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %29, i32 0, i32 3, !dbg !823
  %30 = load i32, i32* %lc28, align 4, !dbg !823
  %31 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !824
  %opt_cur29 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %31, i32 0, i32 2, !dbg !825
  %lc30 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %opt_cur29, i32 0, i32 3, !dbg !826
  store i32 %30, i32* %lc30, align 4, !dbg !827
  %32 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !828
  %lp31 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %32, i32 0, i32 4, !dbg !829
  %33 = load i32, i32* %lp31, align 8, !dbg !829
  %34 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !830
  %opt_cur32 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %34, i32 0, i32 2, !dbg !831
  %lp33 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %opt_cur32, i32 0, i32 4, !dbg !832
  store i32 %33, i32* %lp33, align 8, !dbg !833
  %35 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !834
  %pb34 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %35, i32 0, i32 5, !dbg !835
  %36 = load i32, i32* %pb34, align 4, !dbg !835
  %37 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !836
  %opt_cur35 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %37, i32 0, i32 2, !dbg !837
  %pb36 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %opt_cur35, i32 0, i32 5, !dbg !838
  store i32 %36, i32* %pb36, align 4, !dbg !839
  %38 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !840
  %need_properties = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %38, i32 0, i32 3, !dbg !841
  store i8 1, i8* %need_properties, align 8, !dbg !842
  %39 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !843
  %need_state_reset = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %39, i32 0, i32 4, !dbg !844
  store i8 1, i8* %need_state_reset, align 1, !dbg !845
  br label %if.end37, !dbg !846

if.end37:                                         ; preds = %if.end27, %lor.lhs.false9
  store i32 0, i32* %retval, align 4, !dbg !847
  br label %return, !dbg !847

return:                                           ; preds = %if.end37, %if.then26, %if.then
  %40 = load i32, i32* %retval, align 4, !dbg !848
  ret i32 %40, !dbg !848
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

declare i32 @lzma_lzma_encoder_create(%struct.lzma_coder_s**, %struct.lzma_allocator*, %struct.lzma_options_lzma*, %struct.lzma_lz_options*) #2

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @mf_unencoded(%struct.lzma_mf_s* %mf) #3 !dbg !278 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !849, metadata !300), !dbg !850
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !851
  %write_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %0, i32 0, i32 8, !dbg !852
  %1 = load i32, i32* %write_pos, align 4, !dbg !852
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !853
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %2, i32 0, i32 5, !dbg !854
  %3 = load i32, i32* %read_pos, align 8, !dbg !854
  %sub = sub i32 %1, %3, !dbg !855
  %4 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !856
  %read_ahead = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %4, i32 0, i32 6, !dbg !857
  %5 = load i32, i32* %read_ahead, align 4, !dbg !857
  %add = add i32 %sub, %5, !dbg !858
  ret i32 %add, !dbg !859
}

declare i32 @lzma_lzma_encoder_reset(%struct.lzma_coder_s*, %struct.lzma_options_lzma*) #2

declare i32 @lzma_lzma_encode(%struct.lzma_coder_s*, %struct.lzma_mf_s*, i8*, i64*, i64, i32) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #5

; Function Attrs: nounwind uwtable
define internal void @lzma2_header_uncompressed(%struct.lzma_coder_s* %coder) #0 !dbg !283 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !860, metadata !300), !dbg !861
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !862
  %uncompressed_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 6, !dbg !862
  %1 = load i64, i64* %uncompressed_size, align 8, !dbg !862
  %cmp = icmp ugt i64 %1, 0, !dbg !862
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !862

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !863

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([83 x i8], [83 x i8]* @.str.1, i32 0, i32 0), i32 114, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @__PRETTY_FUNCTION__.lzma2_header_uncompressed, i32 0, i32 0)) #6, !dbg !865
  unreachable, !dbg !865
                                                  ; No predecessors!
  br label %cond.end, !dbg !867

cond.end:                                         ; preds = %2, %cond.true
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !869
  %uncompressed_size1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %3, i32 0, i32 6, !dbg !869
  %4 = load i64, i64* %uncompressed_size1, align 8, !dbg !869
  %cmp2 = icmp ule i64 %4, 65536, !dbg !869
  br i1 %cmp2, label %cond.true3, label %cond.false4, !dbg !869

cond.true3:                                       ; preds = %cond.end
  br label %cond.end5, !dbg !870

cond.false4:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([83 x i8], [83 x i8]* @.str.1, i32 0, i32 0), i32 115, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @__PRETTY_FUNCTION__.lzma2_header_uncompressed, i32 0, i32 0)) #6, !dbg !871
  unreachable, !dbg !871
                                                  ; No predecessors!
  br label %cond.end5, !dbg !872

cond.end5:                                        ; preds = %5, %cond.true3
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !873
  %need_dictionary_reset = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %6, i32 0, i32 5, !dbg !875
  %7 = load i8, i8* %need_dictionary_reset, align 2, !dbg !875
  %tobool = trunc i8 %7 to i1, !dbg !875
  br i1 %tobool, label %if.then, label %if.else, !dbg !876

if.then:                                          ; preds = %cond.end5
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !877
  %buf = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %8, i32 0, i32 9, !dbg !878
  %arrayidx = getelementptr inbounds [65542 x i8], [65542 x i8]* %buf, i64 0, i64 0, !dbg !877
  store i8 1, i8* %arrayidx, align 8, !dbg !879
  br label %if.end, !dbg !877

if.else:                                          ; preds = %cond.end5
  %9 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !880
  %buf6 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %9, i32 0, i32 9, !dbg !881
  %arrayidx7 = getelementptr inbounds [65542 x i8], [65542 x i8]* %buf6, i64 0, i64 0, !dbg !880
  store i8 2, i8* %arrayidx7, align 8, !dbg !882
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %10 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !883
  %need_dictionary_reset8 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %10, i32 0, i32 5, !dbg !884
  store i8 0, i8* %need_dictionary_reset8, align 2, !dbg !885
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !886
  %uncompressed_size9 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 6, !dbg !887
  %12 = load i64, i64* %uncompressed_size9, align 8, !dbg !887
  %sub = sub i64 %12, 1, !dbg !888
  %shr = lshr i64 %sub, 8, !dbg !889
  %conv = trunc i64 %shr to i8, !dbg !890
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !891
  %buf10 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %13, i32 0, i32 9, !dbg !892
  %arrayidx11 = getelementptr inbounds [65542 x i8], [65542 x i8]* %buf10, i64 0, i64 1, !dbg !891
  store i8 %conv, i8* %arrayidx11, align 1, !dbg !893
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !894
  %uncompressed_size12 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 6, !dbg !895
  %15 = load i64, i64* %uncompressed_size12, align 8, !dbg !895
  %sub13 = sub i64 %15, 1, !dbg !896
  %and = and i64 %sub13, 255, !dbg !897
  %conv14 = trunc i64 %and to i8, !dbg !898
  %16 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !899
  %buf15 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %16, i32 0, i32 9, !dbg !900
  %arrayidx16 = getelementptr inbounds [65542 x i8], [65542 x i8]* %buf15, i64 0, i64 2, !dbg !899
  store i8 %conv14, i8* %arrayidx16, align 2, !dbg !901
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !902
  %buf_pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %17, i32 0, i32 8, !dbg !903
  store i64 0, i64* %buf_pos, align 8, !dbg !904
  ret void, !dbg !905
}

; Function Attrs: nounwind uwtable
define internal void @lzma2_header_lzma(%struct.lzma_coder_s* %coder) #0 !dbg !286 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %pos = alloca i64, align 8
  %size = alloca i64, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !906, metadata !300), !dbg !907
  call void @llvm.dbg.declare(metadata i64* %pos, metadata !908, metadata !300), !dbg !909
  call void @llvm.dbg.declare(metadata i64* %size, metadata !910, metadata !300), !dbg !911
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !912
  %uncompressed_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 6, !dbg !912
  %1 = load i64, i64* %uncompressed_size, align 8, !dbg !912
  %cmp = icmp ugt i64 %1, 0, !dbg !912
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !912

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !913

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([83 x i8], [83 x i8]* @.str.1, i32 0, i32 0), i32 60, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @__PRETTY_FUNCTION__.lzma2_header_lzma, i32 0, i32 0)) #6, !dbg !915
  unreachable, !dbg !915
                                                  ; No predecessors!
  br label %cond.end, !dbg !917

cond.end:                                         ; preds = %2, %cond.true
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !919
  %uncompressed_size1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %3, i32 0, i32 6, !dbg !919
  %4 = load i64, i64* %uncompressed_size1, align 8, !dbg !919
  %cmp2 = icmp ule i64 %4, 2097152, !dbg !919
  br i1 %cmp2, label %cond.true3, label %cond.false4, !dbg !919

cond.true3:                                       ; preds = %cond.end
  br label %cond.end5, !dbg !920

cond.false4:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([83 x i8], [83 x i8]* @.str.1, i32 0, i32 0), i32 61, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @__PRETTY_FUNCTION__.lzma2_header_lzma, i32 0, i32 0)) #6, !dbg !921
  unreachable, !dbg !921
                                                  ; No predecessors!
  br label %cond.end5, !dbg !922

cond.end5:                                        ; preds = %5, %cond.true3
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !923
  %compressed_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %6, i32 0, i32 7, !dbg !923
  %7 = load i64, i64* %compressed_size, align 8, !dbg !923
  %cmp6 = icmp ugt i64 %7, 0, !dbg !923
  br i1 %cmp6, label %cond.true7, label %cond.false8, !dbg !923

cond.true7:                                       ; preds = %cond.end5
  br label %cond.end9, !dbg !924

cond.false8:                                      ; preds = %cond.end5
  call void @__assert_fail(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([83 x i8], [83 x i8]* @.str.1, i32 0, i32 0), i32 62, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @__PRETTY_FUNCTION__.lzma2_header_lzma, i32 0, i32 0)) #6, !dbg !925
  unreachable, !dbg !925
                                                  ; No predecessors!
  br label %cond.end9, !dbg !926

cond.end9:                                        ; preds = %8, %cond.true7
  %9 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !927
  %compressed_size10 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %9, i32 0, i32 7, !dbg !927
  %10 = load i64, i64* %compressed_size10, align 8, !dbg !927
  %cmp11 = icmp ule i64 %10, 65536, !dbg !927
  br i1 %cmp11, label %cond.true12, label %cond.false13, !dbg !927

cond.true12:                                      ; preds = %cond.end9
  br label %cond.end14, !dbg !928

cond.false13:                                     ; preds = %cond.end9
  call void @__assert_fail(i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([83 x i8], [83 x i8]* @.str.1, i32 0, i32 0), i32 63, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @__PRETTY_FUNCTION__.lzma2_header_lzma, i32 0, i32 0)) #6, !dbg !929
  unreachable, !dbg !929
                                                  ; No predecessors!
  br label %cond.end14, !dbg !930

cond.end14:                                       ; preds = %11, %cond.true12
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !931
  %need_properties = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 3, !dbg !933
  %13 = load i8, i8* %need_properties, align 8, !dbg !933
  %tobool = trunc i8 %13 to i1, !dbg !933
  br i1 %tobool, label %if.then, label %if.else19, !dbg !934

if.then:                                          ; preds = %cond.end14
  store i64 0, i64* %pos, align 8, !dbg !935
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !937
  %need_dictionary_reset = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 5, !dbg !939
  %15 = load i8, i8* %need_dictionary_reset, align 2, !dbg !939
  %tobool15 = trunc i8 %15 to i1, !dbg !939
  br i1 %tobool15, label %if.then16, label %if.else, !dbg !940

if.then16:                                        ; preds = %if.then
  %16 = load i64, i64* %pos, align 8, !dbg !941
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !942
  %buf = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %17, i32 0, i32 9, !dbg !943
  %arrayidx = getelementptr inbounds [65542 x i8], [65542 x i8]* %buf, i64 0, i64 %16, !dbg !942
  store i8 -32, i8* %arrayidx, align 1, !dbg !944
  br label %if.end, !dbg !942

if.else:                                          ; preds = %if.then
  %18 = load i64, i64* %pos, align 8, !dbg !945
  %19 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !946
  %buf17 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %19, i32 0, i32 9, !dbg !947
  %arrayidx18 = getelementptr inbounds [65542 x i8], [65542 x i8]* %buf17, i64 0, i64 %18, !dbg !946
  store i8 -64, i8* %arrayidx18, align 1, !dbg !948
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then16
  br label %if.end28, !dbg !949

if.else19:                                        ; preds = %cond.end14
  store i64 1, i64* %pos, align 8, !dbg !950
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !952
  %need_state_reset = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %20, i32 0, i32 4, !dbg !954
  %21 = load i8, i8* %need_state_reset, align 1, !dbg !954
  %tobool20 = trunc i8 %21 to i1, !dbg !954
  br i1 %tobool20, label %if.then21, label %if.else24, !dbg !955

if.then21:                                        ; preds = %if.else19
  %22 = load i64, i64* %pos, align 8, !dbg !956
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !957
  %buf22 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 9, !dbg !958
  %arrayidx23 = getelementptr inbounds [65542 x i8], [65542 x i8]* %buf22, i64 0, i64 %22, !dbg !957
  store i8 -96, i8* %arrayidx23, align 1, !dbg !959
  br label %if.end27, !dbg !957

if.else24:                                        ; preds = %if.else19
  %24 = load i64, i64* %pos, align 8, !dbg !960
  %25 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !961
  %buf25 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %25, i32 0, i32 9, !dbg !962
  %arrayidx26 = getelementptr inbounds [65542 x i8], [65542 x i8]* %buf25, i64 0, i64 %24, !dbg !961
  store i8 -128, i8* %arrayidx26, align 1, !dbg !963
  br label %if.end27

if.end27:                                         ; preds = %if.else24, %if.then21
  br label %if.end28

if.end28:                                         ; preds = %if.end27, %if.end
  %26 = load i64, i64* %pos, align 8, !dbg !964
  %27 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !965
  %buf_pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %27, i32 0, i32 8, !dbg !966
  store i64 %26, i64* %buf_pos, align 8, !dbg !967
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !968
  %uncompressed_size29 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %28, i32 0, i32 6, !dbg !969
  %29 = load i64, i64* %uncompressed_size29, align 8, !dbg !969
  %sub = sub i64 %29, 1, !dbg !970
  store i64 %sub, i64* %size, align 8, !dbg !971
  %30 = load i64, i64* %size, align 8, !dbg !972
  %shr = lshr i64 %30, 16, !dbg !973
  %31 = load i64, i64* %pos, align 8, !dbg !974
  %inc = add i64 %31, 1, !dbg !974
  store i64 %inc, i64* %pos, align 8, !dbg !974
  %32 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !975
  %buf30 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %32, i32 0, i32 9, !dbg !976
  %arrayidx31 = getelementptr inbounds [65542 x i8], [65542 x i8]* %buf30, i64 0, i64 %31, !dbg !975
  %33 = load i8, i8* %arrayidx31, align 1, !dbg !977
  %conv = zext i8 %33 to i64, !dbg !977
  %add = add i64 %conv, %shr, !dbg !977
  %conv32 = trunc i64 %add to i8, !dbg !977
  store i8 %conv32, i8* %arrayidx31, align 1, !dbg !977
  %34 = load i64, i64* %size, align 8, !dbg !978
  %shr33 = lshr i64 %34, 8, !dbg !979
  %and = and i64 %shr33, 255, !dbg !980
  %conv34 = trunc i64 %and to i8, !dbg !981
  %35 = load i64, i64* %pos, align 8, !dbg !982
  %inc35 = add i64 %35, 1, !dbg !982
  store i64 %inc35, i64* %pos, align 8, !dbg !982
  %36 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !983
  %buf36 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %36, i32 0, i32 9, !dbg !984
  %arrayidx37 = getelementptr inbounds [65542 x i8], [65542 x i8]* %buf36, i64 0, i64 %35, !dbg !983
  store i8 %conv34, i8* %arrayidx37, align 1, !dbg !985
  %37 = load i64, i64* %size, align 8, !dbg !986
  %and38 = and i64 %37, 255, !dbg !987
  %conv39 = trunc i64 %and38 to i8, !dbg !986
  %38 = load i64, i64* %pos, align 8, !dbg !988
  %inc40 = add i64 %38, 1, !dbg !988
  store i64 %inc40, i64* %pos, align 8, !dbg !988
  %39 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !989
  %buf41 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %39, i32 0, i32 9, !dbg !990
  %arrayidx42 = getelementptr inbounds [65542 x i8], [65542 x i8]* %buf41, i64 0, i64 %38, !dbg !989
  store i8 %conv39, i8* %arrayidx42, align 1, !dbg !991
  %40 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !992
  %compressed_size43 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %40, i32 0, i32 7, !dbg !993
  %41 = load i64, i64* %compressed_size43, align 8, !dbg !993
  %sub44 = sub i64 %41, 1, !dbg !994
  store i64 %sub44, i64* %size, align 8, !dbg !995
  %42 = load i64, i64* %size, align 8, !dbg !996
  %shr45 = lshr i64 %42, 8, !dbg !997
  %conv46 = trunc i64 %shr45 to i8, !dbg !996
  %43 = load i64, i64* %pos, align 8, !dbg !998
  %inc47 = add i64 %43, 1, !dbg !998
  store i64 %inc47, i64* %pos, align 8, !dbg !998
  %44 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !999
  %buf48 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %44, i32 0, i32 9, !dbg !1000
  %arrayidx49 = getelementptr inbounds [65542 x i8], [65542 x i8]* %buf48, i64 0, i64 %43, !dbg !999
  store i8 %conv46, i8* %arrayidx49, align 1, !dbg !1001
  %45 = load i64, i64* %size, align 8, !dbg !1002
  %and50 = and i64 %45, 255, !dbg !1003
  %conv51 = trunc i64 %and50 to i8, !dbg !1002
  %46 = load i64, i64* %pos, align 8, !dbg !1004
  %inc52 = add i64 %46, 1, !dbg !1004
  store i64 %inc52, i64* %pos, align 8, !dbg !1004
  %47 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1005
  %buf53 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %47, i32 0, i32 9, !dbg !1006
  %arrayidx54 = getelementptr inbounds [65542 x i8], [65542 x i8]* %buf53, i64 0, i64 %46, !dbg !1005
  store i8 %conv51, i8* %arrayidx54, align 1, !dbg !1007
  %48 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1008
  %need_properties55 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %48, i32 0, i32 3, !dbg !1010
  %49 = load i8, i8* %need_properties55, align 8, !dbg !1010
  %tobool56 = trunc i8 %49 to i1, !dbg !1010
  br i1 %tobool56, label %if.then57, label %if.end59, !dbg !1011

if.then57:                                        ; preds = %if.end28
  %50 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1012
  %opt_cur = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %50, i32 0, i32 2, !dbg !1013
  %51 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1014
  %buf58 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %51, i32 0, i32 9, !dbg !1015
  %arraydecay = getelementptr inbounds [65542 x i8], [65542 x i8]* %buf58, i32 0, i32 0, !dbg !1014
  %52 = load i64, i64* %pos, align 8, !dbg !1016
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay, i64 %52, !dbg !1017
  %call = call zeroext i1 @lzma_lzma_lclppb_encode(%struct.lzma_options_lzma* %opt_cur, i8* %add.ptr), !dbg !1018
  br label %if.end59, !dbg !1018

if.end59:                                         ; preds = %if.then57, %if.end28
  %53 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1019
  %need_properties60 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %53, i32 0, i32 3, !dbg !1020
  store i8 0, i8* %need_properties60, align 8, !dbg !1021
  %54 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1022
  %need_state_reset61 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %54, i32 0, i32 4, !dbg !1023
  store i8 0, i8* %need_state_reset61, align 1, !dbg !1024
  %55 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1025
  %need_dictionary_reset62 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %55, i32 0, i32 5, !dbg !1026
  store i8 0, i8* %need_dictionary_reset62, align 2, !dbg !1027
  %56 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1028
  %compressed_size63 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %56, i32 0, i32 7, !dbg !1029
  %57 = load i64, i64* %compressed_size63, align 8, !dbg !1030
  %add64 = add i64 %57, 6, !dbg !1030
  store i64 %add64, i64* %compressed_size63, align 8, !dbg !1030
  ret void, !dbg !1031
}

declare i64 @lzma_bufcpy(i8*, i64*, i64, i8*, i64*, i64) #2

; Function Attrs: inlinehint nounwind uwtable
define internal void @mf_read(%struct.lzma_mf_s* %mf, i8* %out, i64* %out_pos, i64 %out_size, i64* %left) #3 !dbg !287 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %left.addr = alloca i64*, align 8
  %out_avail = alloca i64, align 8
  %copy_size = alloca i64, align 8
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !1032, metadata !300), !dbg !1033
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !1034, metadata !300), !dbg !1035
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !1036, metadata !300), !dbg !1037
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !1038, metadata !300), !dbg !1039
  store i64* %left, i64** %left.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %left.addr, metadata !1040, metadata !300), !dbg !1041
  call void @llvm.dbg.declare(metadata i64* %out_avail, metadata !1042, metadata !300), !dbg !1044
  %0 = load i64, i64* %out_size.addr, align 8, !dbg !1045
  %1 = load i64*, i64** %out_pos.addr, align 8, !dbg !1046
  %2 = load i64, i64* %1, align 8, !dbg !1047
  %sub = sub i64 %0, %2, !dbg !1048
  store i64 %sub, i64* %out_avail, align 8, !dbg !1044
  call void @llvm.dbg.declare(metadata i64* %copy_size, metadata !1049, metadata !300), !dbg !1050
  %3 = load i64, i64* %out_avail, align 8, !dbg !1051
  %4 = load i64*, i64** %left.addr, align 8, !dbg !1051
  %5 = load i64, i64* %4, align 8, !dbg !1051
  %cmp = icmp ult i64 %3, %5, !dbg !1051
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1051

cond.true:                                        ; preds = %entry
  %6 = load i64, i64* %out_avail, align 8, !dbg !1052
  br label %cond.end, !dbg !1052

cond.false:                                       ; preds = %entry
  %7 = load i64*, i64** %left.addr, align 8, !dbg !1054
  %8 = load i64, i64* %7, align 8, !dbg !1054
  br label %cond.end, !dbg !1054

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %6, %cond.true ], [ %8, %cond.false ], !dbg !1056
  store i64 %cond, i64* %copy_size, align 8, !dbg !1058
  %9 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1059
  %read_ahead = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %9, i32 0, i32 6, !dbg !1059
  %10 = load i32, i32* %read_ahead, align 4, !dbg !1059
  %cmp1 = icmp eq i32 %10, 0, !dbg !1059
  br i1 %cmp1, label %cond.true2, label %cond.false3, !dbg !1059

cond.true2:                                       ; preds = %cond.end
  br label %cond.end4, !dbg !1060

cond.false3:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([78 x i8], [78 x i8]* @.str.7, i32 0, i32 0), i32 286, i8* getelementptr inbounds ([63 x i8], [63 x i8]* @__PRETTY_FUNCTION__.mf_read, i32 0, i32 0)) #6, !dbg !1061
  unreachable, !dbg !1061
                                                  ; No predecessors!
  br label %cond.end4, !dbg !1062

cond.end4:                                        ; preds = %11, %cond.true2
  %12 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1063
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %12, i32 0, i32 5, !dbg !1063
  %13 = load i32, i32* %read_pos, align 8, !dbg !1063
  %conv = zext i32 %13 to i64, !dbg !1063
  %14 = load i64*, i64** %left.addr, align 8, !dbg !1063
  %15 = load i64, i64* %14, align 8, !dbg !1063
  %cmp5 = icmp uge i64 %conv, %15, !dbg !1063
  br i1 %cmp5, label %cond.true7, label %cond.false8, !dbg !1063

cond.true7:                                       ; preds = %cond.end4
  br label %cond.end9, !dbg !1064

cond.false8:                                      ; preds = %cond.end4
  call void @__assert_fail(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([78 x i8], [78 x i8]* @.str.7, i32 0, i32 0), i32 287, i8* getelementptr inbounds ([63 x i8], [63 x i8]* @__PRETTY_FUNCTION__.mf_read, i32 0, i32 0)) #6, !dbg !1065
  unreachable, !dbg !1065
                                                  ; No predecessors!
  br label %cond.end9, !dbg !1066

cond.end9:                                        ; preds = %16, %cond.true7
  %17 = load i8*, i8** %out.addr, align 8, !dbg !1067
  %18 = load i64*, i64** %out_pos.addr, align 8, !dbg !1068
  %19 = load i64, i64* %18, align 8, !dbg !1069
  %add.ptr = getelementptr inbounds i8, i8* %17, i64 %19, !dbg !1070
  %20 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1071
  %buffer = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %20, i32 0, i32 0, !dbg !1072
  %21 = load i8*, i8** %buffer, align 8, !dbg !1072
  %22 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1073
  %read_pos10 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %22, i32 0, i32 5, !dbg !1074
  %23 = load i32, i32* %read_pos10, align 8, !dbg !1074
  %idx.ext = zext i32 %23 to i64, !dbg !1075
  %add.ptr11 = getelementptr inbounds i8, i8* %21, i64 %idx.ext, !dbg !1075
  %24 = load i64*, i64** %left.addr, align 8, !dbg !1076
  %25 = load i64, i64* %24, align 8, !dbg !1077
  %idx.neg = sub i64 0, %25, !dbg !1078
  %add.ptr12 = getelementptr inbounds i8, i8* %add.ptr11, i64 %idx.neg, !dbg !1078
  %26 = load i64, i64* %copy_size, align 8, !dbg !1079
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr, i8* %add.ptr12, i64 %26, i32 1, i1 false), !dbg !1080
  %27 = load i64, i64* %copy_size, align 8, !dbg !1081
  %28 = load i64*, i64** %out_pos.addr, align 8, !dbg !1082
  %29 = load i64, i64* %28, align 8, !dbg !1083
  %add = add i64 %29, %27, !dbg !1083
  store i64 %add, i64* %28, align 8, !dbg !1083
  %30 = load i64, i64* %copy_size, align 8, !dbg !1084
  %31 = load i64*, i64** %left.addr, align 8, !dbg !1085
  %32 = load i64, i64* %31, align 8, !dbg !1086
  %sub13 = sub i64 %32, %30, !dbg !1086
  store i64 %sub13, i64* %31, align 8, !dbg !1086
  ret void, !dbg !1087
}

declare zeroext i1 @lzma_lzma_lclppb_encode(%struct.lzma_options_lzma*, i8*) #2

declare void @lzma_free(i8*, %struct.lzma_allocator*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!296, !297}
!llvm.ident = !{!298}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !113, subprograms: !116)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma2_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !46, !53, !71, !100, !106}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 57, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17}
!6 = !DIEnumerator(name: "LZMA_OK", value: 0)
!7 = !DIEnumerator(name: "LZMA_STREAM_END", value: 1)
!8 = !DIEnumerator(name: "LZMA_NO_CHECK", value: 2)
!9 = !DIEnumerator(name: "LZMA_UNSUPPORTED_CHECK", value: 3)
!10 = !DIEnumerator(name: "LZMA_GET_CHECK", value: 4)
!11 = !DIEnumerator(name: "LZMA_MEM_ERROR", value: 5)
!12 = !DIEnumerator(name: "LZMA_MEMLIMIT_ERROR", value: 6)
!13 = !DIEnumerator(name: "LZMA_FORMAT_ERROR", value: 7)
!14 = !DIEnumerator(name: "LZMA_OPTIONS_ERROR", value: 8)
!15 = !DIEnumerator(name: "LZMA_DATA_ERROR", value: 9)
!16 = !DIEnumerator(name: "LZMA_BUF_ERROR", value: 10)
!17 = !DIEnumerator(name: "LZMA_PROG_ERROR", value: 11)
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !19, file: !1, line: 21, size: 32, align: 32, elements: !94)
!19 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !1, line: 20, size: 525632, align: 64, elements: !20)
!20 = !{!21, !22, !26, !80, !82, !83, !84, !88, !89, !90}
!21 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !19, file: !1, line: 27, baseType: !18, size: 32, align: 32)
!22 = !DIDerivedType(tag: DW_TAG_member, name: "lzma", scope: !19, file: !1, line: 30, baseType: !23, size: 64, align: 64, offset: 64)
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64, align: 64)
!24 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !25, line: 73, baseType: !19)
!25 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!26 = !DIDerivedType(tag: DW_TAG_member, name: "opt_cur", scope: !19, file: !1, line: 33, baseType: !27, size: 896, align: 64, offset: 128)
!27 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_lzma", file: !28, line: 399, baseType: !29)
!28 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/lzma.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!29 = !DICompositeType(tag: DW_TAG_structure_type, file: !28, line: 185, size: 896, align: 64, elements: !30)
!30 = !{!31, !35, !40, !41, !42, !43, !44, !50, !51, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !74, !75, !76, !77, !79}
!31 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !29, file: !28, line: 217, baseType: !32, size: 32, align: 32)
!32 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !33, line: 51, baseType: !34)
!33 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!34 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!35 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict", scope: !29, file: !28, line: 240, baseType: !36, size: 64, align: 64, offset: 64)
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64, align: 64)
!37 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !38)
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !33, line: 48, baseType: !39)
!39 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict_size", scope: !29, file: !28, line: 254, baseType: !32, size: 32, align: 32, offset: 128)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "lc", scope: !29, file: !28, line: 281, baseType: !32, size: 32, align: 32, offset: 160)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "lp", scope: !29, file: !28, line: 293, baseType: !32, size: 32, align: 32, offset: 192)
!43 = !DIDerivedType(tag: DW_TAG_member, name: "pb", scope: !29, file: !28, line: 316, baseType: !32, size: 32, align: 32, offset: 224)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !29, file: !28, line: 322, baseType: !45, size: 32, align: 32, offset: 256)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_mode", file: !28, line: 155, baseType: !46)
!46 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !28, line: 138, size: 32, align: 32, elements: !47)
!47 = !{!48, !49}
!48 = !DIEnumerator(name: "LZMA_MODE_FAST", value: 1)
!49 = !DIEnumerator(name: "LZMA_MODE_NORMAL", value: 2)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !29, file: !28, line: 342, baseType: !32, size: 32, align: 32, offset: 288)
!51 = !DIDerivedType(tag: DW_TAG_member, name: "mf", scope: !29, file: !28, line: 345, baseType: !52, size: 32, align: 32, offset: 320)
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match_finder", file: !28, line: 111, baseType: !53)
!53 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !28, line: 58, size: 32, align: 32, elements: !54)
!54 = !{!55, !56, !57, !58, !59}
!55 = !DIEnumerator(name: "LZMA_MF_HC3", value: 3)
!56 = !DIEnumerator(name: "LZMA_MF_HC4", value: 4)
!57 = !DIEnumerator(name: "LZMA_MF_BT2", value: 18)
!58 = !DIEnumerator(name: "LZMA_MF_BT3", value: 19)
!59 = !DIEnumerator(name: "LZMA_MF_BT4", value: 20)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !29, file: !28, line: 375, baseType: !32, size: 32, align: 32, offset: 352)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !29, file: !28, line: 384, baseType: !32, size: 32, align: 32, offset: 384)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !29, file: !28, line: 385, baseType: !32, size: 32, align: 32, offset: 416)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !29, file: !28, line: 386, baseType: !32, size: 32, align: 32, offset: 448)
!64 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !29, file: !28, line: 387, baseType: !32, size: 32, align: 32, offset: 480)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !29, file: !28, line: 388, baseType: !32, size: 32, align: 32, offset: 512)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !29, file: !28, line: 389, baseType: !32, size: 32, align: 32, offset: 544)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !29, file: !28, line: 390, baseType: !32, size: 32, align: 32, offset: 576)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !29, file: !28, line: 391, baseType: !32, size: 32, align: 32, offset: 608)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !29, file: !28, line: 392, baseType: !70, size: 32, align: 32, offset: 640)
!70 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !71)
!71 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !72)
!72 = !{!73}
!73 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !29, file: !28, line: 393, baseType: !70, size: 32, align: 32, offset: 672)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !29, file: !28, line: 394, baseType: !70, size: 32, align: 32, offset: 704)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !29, file: !28, line: 395, baseType: !70, size: 32, align: 32, offset: 736)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !29, file: !28, line: 396, baseType: !78, size: 64, align: 64, offset: 768)
!78 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !29, file: !28, line: 397, baseType: !78, size: 64, align: 64, offset: 832)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "need_properties", scope: !19, file: !1, line: 35, baseType: !81, size: 8, align: 8, offset: 1024)
!81 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "need_state_reset", scope: !19, file: !1, line: 36, baseType: !81, size: 8, align: 8, offset: 1032)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "need_dictionary_reset", scope: !19, file: !1, line: 37, baseType: !81, size: 8, align: 8, offset: 1040)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !19, file: !1, line: 40, baseType: !85, size: 64, align: 64, offset: 1088)
!85 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !86, line: 62, baseType: !87)
!86 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!87 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_size", scope: !19, file: !1, line: 44, baseType: !85, size: 64, align: 64, offset: 1152)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "buf_pos", scope: !19, file: !1, line: 47, baseType: !85, size: 64, align: 64, offset: 1216)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "buf", scope: !19, file: !1, line: 50, baseType: !91, size: 524336, align: 8, offset: 1280)
!91 = !DICompositeType(tag: DW_TAG_array_type, baseType: !38, size: 524336, align: 8, elements: !92)
!92 = !{!93}
!93 = !DISubrange(count: 65542)
!94 = !{!95, !96, !97, !98, !99}
!95 = !DIEnumerator(name: "SEQ_INIT", value: 0)
!96 = !DIEnumerator(name: "SEQ_LZMA_ENCODE", value: 1)
!97 = !DIEnumerator(name: "SEQ_LZMA_COPY", value: 2)
!98 = !DIEnumerator(name: "SEQ_UNCOMPRESSED_HEADER", value: 3)
!99 = !DIEnumerator(name: "SEQ_UNCOMPRESSED_COPY", value: 4)
!100 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !101)
!101 = !{!102, !103, !104, !105}
!102 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!103 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!104 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!105 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!106 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !107, line: 27, size: 32, align: 32, elements: !108)
!107 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!108 = !{!109, !110, !111, !112}
!109 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!110 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!111 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!112 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!113 = !{!78, !114}
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !115, size: 64, align: 64)
!115 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !27)
!116 = !{!117, !196, !201, !204, !277, !278, !283, !286, !287, !290, !291, !292}
!117 = distinct !DISubprogram(name: "lzma_lzma2_encoder_init", scope: !1, file: !1, line: 358, type: !118, isLocal: false, isDefinition: true, scopeLine: 360, flags: DIFlagPrototyped, isOptimized: false, variables: !195)
!118 = !DISubroutineType(types: !119)
!119 = !{!120, !121, !137, !185}
!120 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!121 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !122, size: 64, align: 64)
!122 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !25, line: 75, baseType: !123)
!123 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !25, line: 119, size: 512, align: 64, elements: !124)
!124 = !{!125, !126, !130, !132, !156, !161, !168, !173}
!125 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !123, file: !25, line: 121, baseType: !23, size: 64, align: 64)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !123, file: !25, line: 125, baseType: !127, size: 64, align: 64, offset: 64)
!127 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !128, line: 63, baseType: !129)
!128 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!129 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !33, line: 55, baseType: !87)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !123, file: !25, line: 131, baseType: !131, size: 64, align: 64, offset: 128)
!131 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !33, line: 122, baseType: !87)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !123, file: !25, line: 134, baseType: !133, size: 64, align: 64, offset: 192)
!133 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !25, line: 89, baseType: !134)
!134 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !135, size: 64, align: 64)
!135 = !DISubroutineType(types: !136)
!136 = !{!120, !23, !137, !150, !151, !85, !153, !151, !85, !155}
!137 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !138, size: 64, align: 64)
!138 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !139)
!139 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !140)
!140 = !{!141, !145, !149}
!141 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !139, file: !4, line: 376, baseType: !142, size: 64, align: 64)
!142 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !143, size: 64, align: 64)
!143 = !DISubroutineType(types: !144)
!144 = !{!78, !78, !85, !85}
!145 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !139, file: !4, line: 390, baseType: !146, size: 64, align: 64, offset: 64)
!146 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !147, size: 64, align: 64)
!147 = !DISubroutineType(types: !148)
!148 = !{null, !78, !78}
!149 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !139, file: !4, line: 401, baseType: !78, size: 64, align: 64, offset: 128)
!150 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !36)
!151 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !152)
!152 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !85, size: 64, align: 64)
!153 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !154)
!154 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !38, size: 64, align: 64)
!155 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !100)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !123, file: !25, line: 139, baseType: !157, size: 64, align: 64, offset: 256)
!157 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !25, line: 97, baseType: !158)
!158 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !159, size: 64, align: 64)
!159 = !DISubroutineType(types: !160)
!160 = !{null, !23, !137}
!161 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !123, file: !25, line: 143, baseType: !162, size: 64, align: 64, offset: 320)
!162 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !163, size: 64, align: 64)
!163 = !DISubroutineType(types: !164)
!164 = !{!165, !166}
!165 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !107, line: 55, baseType: !106)
!166 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !167, size: 64, align: 64)
!167 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !24)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !123, file: !25, line: 147, baseType: !169, size: 64, align: 64, offset: 384)
!169 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !170, size: 64, align: 64)
!170 = !DISubroutineType(types: !171)
!171 = !{!120, !23, !172, !172, !129}
!172 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !129, size: 64, align: 64)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !123, file: !25, line: 152, baseType: !174, size: 64, align: 64, offset: 448)
!174 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !175, size: 64, align: 64)
!175 = !DISubroutineType(types: !176)
!176 = !{!120, !23, !137, !177, !177}
!177 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !178, size: 64, align: 64)
!178 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !179)
!179 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !180, line: 65, baseType: !181)
!180 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!181 = !DICompositeType(tag: DW_TAG_structure_type, file: !180, line: 43, size: 128, align: 64, elements: !182)
!182 = !{!183, !184}
!183 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !181, file: !180, line: 54, baseType: !127, size: 64, align: 64)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !181, file: !180, line: 63, baseType: !78, size: 64, align: 64, offset: 64)
!185 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !186, size: 64, align: 64)
!186 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !187)
!187 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_info", file: !25, line: 77, baseType: !188)
!188 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_filter_info_s", file: !25, line: 104, size: 192, align: 64, elements: !189)
!189 = !{!190, !191, !194}
!190 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !188, file: !25, line: 107, baseType: !127, size: 64, align: 64)
!191 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !188, file: !25, line: 111, baseType: !192, size: 64, align: 64, offset: 64)
!192 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_init_function", file: !25, line: 81, baseType: !193)
!193 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !118, size: 64, align: 64)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !188, file: !25, line: 114, baseType: !78, size: 64, align: 64, offset: 128)
!195 = !{}
!196 = distinct !DISubprogram(name: "lzma_lzma2_encoder_memusage", scope: !1, file: !1, line: 367, type: !197, isLocal: false, isDefinition: true, scopeLine: 368, flags: DIFlagPrototyped, isOptimized: false, variables: !195)
!197 = !DISubroutineType(types: !198)
!198 = !{!129, !199}
!199 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !200, size: 64, align: 64)
!200 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!201 = distinct !DISubprogram(name: "lzma_lzma2_props_encode", scope: !1, file: !1, line: 378, type: !202, isLocal: false, isDefinition: true, scopeLine: 379, flags: DIFlagPrototyped, isOptimized: false, variables: !195)
!202 = !DISubroutineType(types: !203)
!203 = !{!120, !199, !154}
!204 = distinct !DISubprogram(name: "lzma2_encoder_init", scope: !1, file: !1, line: 313, type: !205, isLocal: true, isDefinition: true, scopeLine: 315, flags: DIFlagPrototyped, isOptimized: false, variables: !195)
!205 = !DISubroutineType(types: !206)
!206 = !{!120, !207, !137, !199, !264}
!207 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !208, size: 64, align: 64)
!208 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_lz_encoder", file: !209, line: 208, baseType: !210)
!209 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lz/lz_encoder.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!210 = !DICompositeType(tag: DW_TAG_structure_type, file: !209, line: 192, size: 256, align: 64, elements: !211)
!211 = !{!212, !213, !259, !260}
!212 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !210, file: !209, line: 194, baseType: !23, size: 64, align: 64)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !210, file: !209, line: 197, baseType: !214, size: 64, align: 64, offset: 64)
!214 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !215, size: 64, align: 64)
!215 = !DISubroutineType(types: !216)
!216 = !{!120, !217, !218, !153, !151, !85}
!217 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !23)
!218 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !219)
!219 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !220, size: 64, align: 64)
!220 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_mf", file: !209, line: 28, baseType: !221)
!221 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_mf_s", file: !209, line: 29, size: 960, align: 64, elements: !222)
!222 = !{!223, !224, !225, !226, !227, !228, !229, !230, !231, !232, !233, !243, !247, !249, !250, !251, !252, !253, !254, !255, !256, !257, !258}
!223 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !221, file: !209, line: 35, baseType: !154, size: 64, align: 64)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !221, file: !209, line: 39, baseType: !32, size: 32, align: 32, offset: 64)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "keep_size_before", scope: !221, file: !209, line: 45, baseType: !32, size: 32, align: 32, offset: 96)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "keep_size_after", scope: !221, file: !209, line: 51, baseType: !32, size: 32, align: 32, offset: 128)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !221, file: !209, line: 58, baseType: !32, size: 32, align: 32, offset: 160)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "read_pos", scope: !221, file: !209, line: 63, baseType: !32, size: 32, align: 32, offset: 192)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "read_ahead", scope: !221, file: !209, line: 67, baseType: !32, size: 32, align: 32, offset: 224)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "read_limit", scope: !221, file: !209, line: 75, baseType: !32, size: 32, align: 32, offset: 256)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "write_pos", scope: !221, file: !209, line: 80, baseType: !32, size: 32, align: 32, offset: 288)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !221, file: !209, line: 84, baseType: !32, size: 32, align: 32, offset: 320)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "find", scope: !221, file: !209, line: 92, baseType: !234, size: 64, align: 64, offset: 384)
!234 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !235, size: 64, align: 64)
!235 = !DISubroutineType(types: !236)
!236 = !{!32, !219, !237}
!237 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !238, size: 64, align: 64)
!238 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match", file: !209, line: 25, baseType: !239)
!239 = !DICompositeType(tag: DW_TAG_structure_type, file: !209, line: 22, size: 64, align: 32, elements: !240)
!240 = !{!241, !242}
!241 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !239, file: !209, line: 23, baseType: !32, size: 32, align: 32)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "dist", scope: !239, file: !209, line: 24, baseType: !32, size: 32, align: 32, offset: 32)
!243 = !DIDerivedType(tag: DW_TAG_member, name: "skip", scope: !221, file: !209, line: 97, baseType: !244, size: 64, align: 64, offset: 448)
!244 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !245, size: 64, align: 64)
!245 = !DISubroutineType(types: !246)
!246 = !{null, !219, !32}
!247 = !DIDerivedType(tag: DW_TAG_member, name: "hash", scope: !221, file: !209, line: 99, baseType: !248, size: 64, align: 64, offset: 512)
!248 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64, align: 64)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "son", scope: !221, file: !209, line: 100, baseType: !248, size: 64, align: 64, offset: 576)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "cyclic_pos", scope: !221, file: !209, line: 101, baseType: !32, size: 32, align: 32, offset: 640)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "cyclic_size", scope: !221, file: !209, line: 102, baseType: !32, size: 32, align: 32, offset: 672)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "hash_mask", scope: !221, file: !209, line: 103, baseType: !32, size: 32, align: 32, offset: 704)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !221, file: !209, line: 106, baseType: !32, size: 32, align: 32, offset: 736)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !221, file: !209, line: 109, baseType: !32, size: 32, align: 32, offset: 768)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "match_len_max", scope: !221, file: !209, line: 114, baseType: !32, size: 32, align: 32, offset: 800)
!256 = !DIDerivedType(tag: DW_TAG_member, name: "action", scope: !221, file: !209, line: 119, baseType: !155, size: 32, align: 32, offset: 832)
!257 = !DIDerivedType(tag: DW_TAG_member, name: "hash_size_sum", scope: !221, file: !209, line: 122, baseType: !32, size: 32, align: 32, offset: 864)
!258 = !DIDerivedType(tag: DW_TAG_member, name: "sons_count", scope: !221, file: !209, line: 125, baseType: !32, size: 32, align: 32, offset: 896)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !210, file: !209, line: 202, baseType: !158, size: 64, align: 64, offset: 128)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "options_update", scope: !210, file: !209, line: 205, baseType: !261, size: 64, align: 64, offset: 192)
!261 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !262, size: 64, align: 64)
!262 = !DISubroutineType(types: !263)
!263 = !{!120, !23, !177}
!264 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !265, size: 64, align: 64)
!265 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_lz_options", file: !209, line: 161, baseType: !266)
!266 = !DICompositeType(tag: DW_TAG_structure_type, file: !209, line: 129, size: 512, align: 64, elements: !267)
!267 = !{!268, !269, !270, !271, !272, !273, !274, !275, !276}
!268 = !DIDerivedType(tag: DW_TAG_member, name: "before_size", scope: !266, file: !209, line: 132, baseType: !85, size: 64, align: 64)
!269 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !266, file: !209, line: 135, baseType: !85, size: 64, align: 64, offset: 64)
!270 = !DIDerivedType(tag: DW_TAG_member, name: "after_size", scope: !266, file: !209, line: 139, baseType: !85, size: 64, align: 64, offset: 128)
!271 = !DIDerivedType(tag: DW_TAG_member, name: "match_len_max", scope: !266, file: !209, line: 144, baseType: !85, size: 64, align: 64, offset: 192)
!272 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !266, file: !209, line: 148, baseType: !85, size: 64, align: 64, offset: 256)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "match_finder", scope: !266, file: !209, line: 151, baseType: !52, size: 32, align: 32, offset: 320)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !266, file: !209, line: 154, baseType: !32, size: 32, align: 32, offset: 352)
!275 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict", scope: !266, file: !209, line: 157, baseType: !36, size: 64, align: 64, offset: 384)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict_size", scope: !266, file: !209, line: 159, baseType: !32, size: 32, align: 32, offset: 448)
!277 = distinct !DISubprogram(name: "lzma2_encode", scope: !1, file: !1, line: 137, type: !215, isLocal: true, isDefinition: true, scopeLine: 140, flags: DIFlagPrototyped, isOptimized: false, variables: !195)
!278 = distinct !DISubprogram(name: "mf_unencoded", scope: !209, file: !209, line: 239, type: !279, isLocal: true, isDefinition: true, scopeLine: 240, flags: DIFlagPrototyped, isOptimized: false, variables: !195)
!279 = !DISubroutineType(types: !280)
!280 = !{!32, !281}
!281 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !282, size: 64, align: 64)
!282 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !220)
!283 = distinct !DISubprogram(name: "lzma2_header_uncompressed", scope: !1, file: !1, line: 112, type: !284, isLocal: true, isDefinition: true, scopeLine: 113, flags: DIFlagPrototyped, isOptimized: false, variables: !195)
!284 = !DISubroutineType(types: !285)
!285 = !{null, !23}
!286 = distinct !DISubprogram(name: "lzma2_header_lzma", scope: !1, file: !1, line: 55, type: !284, isLocal: true, isDefinition: true, scopeLine: 56, flags: DIFlagPrototyped, isOptimized: false, variables: !195)
!287 = distinct !DISubprogram(name: "mf_read", scope: !209, file: !209, line: 280, type: !288, isLocal: true, isDefinition: true, scopeLine: 282, flags: DIFlagPrototyped, isOptimized: false, variables: !195)
!288 = !DISubroutineType(types: !289)
!289 = !{null, !219, !154, !152, !85, !152}
!290 = distinct !DISubprogram(name: "lzma2_encoder_end", scope: !1, file: !1, line: 269, type: !159, isLocal: true, isDefinition: true, scopeLine: 270, flags: DIFlagPrototyped, isOptimized: false, variables: !195)
!291 = distinct !DISubprogram(name: "lzma2_encoder_options_update", scope: !1, file: !1, line: 278, type: !262, isLocal: true, isDefinition: true, scopeLine: 279, flags: DIFlagPrototyped, isOptimized: false, variables: !195)
!292 = distinct !DISubprogram(name: "get_pos_slot", scope: !293, file: !293, line: 110, type: !294, isLocal: true, isDefinition: true, scopeLine: 111, flags: DIFlagPrototyped, isOptimized: false, variables: !195)
!293 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/fastpos.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!294 = !DISubroutineType(types: !295)
!295 = !{!32, !32}
!296 = !{i32 2, !"Dwarf Version", i32 4}
!297 = !{i32 2, !"Debug Info Version", i32 3}
!298 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!299 = !DILocalVariable(name: "next", arg: 1, scope: !117, file: !1, line: 358, type: !121)
!300 = !DIExpression()
!301 = !DILocation(line: 358, column: 42, scope: !117)
!302 = !DILocalVariable(name: "allocator", arg: 2, scope: !117, file: !1, line: 358, type: !137)
!303 = !DILocation(line: 358, column: 64, scope: !117)
!304 = !DILocalVariable(name: "filters", arg: 3, scope: !117, file: !1, line: 359, type: !185)
!305 = !DILocation(line: 359, column: 27, scope: !117)
!306 = !DILocation(line: 362, column: 4, scope: !117)
!307 = !DILocation(line: 362, column: 10, scope: !117)
!308 = !DILocation(line: 362, column: 21, scope: !117)
!309 = !DILocation(line: 361, column: 9, scope: !117)
!310 = !DILocation(line: 361, column: 2, scope: !117)
!311 = !DILocalVariable(name: "lz", arg: 1, scope: !204, file: !1, line: 313, type: !207)
!312 = !DILocation(line: 313, column: 37, scope: !204)
!313 = !DILocalVariable(name: "allocator", arg: 2, scope: !204, file: !1, line: 313, type: !137)
!314 = !DILocation(line: 313, column: 57, scope: !204)
!315 = !DILocalVariable(name: "options", arg: 3, scope: !204, file: !1, line: 314, type: !199)
!316 = !DILocation(line: 314, column: 15, scope: !204)
!317 = !DILocalVariable(name: "lz_options", arg: 4, scope: !204, file: !1, line: 314, type: !264)
!318 = !DILocation(line: 314, column: 41, scope: !204)
!319 = !DILocation(line: 316, column: 6, scope: !320)
!320 = distinct !DILexicalBlock(scope: !204, file: !1, line: 316, column: 6)
!321 = !DILocation(line: 316, column: 14, scope: !320)
!322 = !DILocation(line: 316, column: 6, scope: !204)
!323 = !DILocation(line: 317, column: 3, scope: !320)
!324 = !DILocation(line: 319, column: 6, scope: !325)
!325 = distinct !DILexicalBlock(scope: !204, file: !1, line: 319, column: 6)
!326 = !DILocation(line: 319, column: 10, scope: !325)
!327 = !DILocation(line: 319, column: 16, scope: !325)
!328 = !DILocation(line: 319, column: 6, scope: !204)
!329 = !DILocation(line: 320, column: 46, scope: !330)
!330 = distinct !DILexicalBlock(scope: !325, file: !1, line: 319, column: 25)
!331 = !DILocation(line: 320, column: 15, scope: !330)
!332 = !DILocation(line: 320, column: 3, scope: !330)
!333 = !DILocation(line: 320, column: 7, scope: !330)
!334 = !DILocation(line: 320, column: 13, scope: !330)
!335 = !DILocation(line: 321, column: 7, scope: !336)
!336 = distinct !DILexicalBlock(scope: !330, file: !1, line: 321, column: 7)
!337 = !DILocation(line: 321, column: 11, scope: !336)
!338 = !DILocation(line: 321, column: 17, scope: !336)
!339 = !DILocation(line: 321, column: 7, scope: !330)
!340 = !DILocation(line: 322, column: 4, scope: !336)
!341 = !DILocation(line: 324, column: 3, scope: !330)
!342 = !DILocation(line: 324, column: 7, scope: !330)
!343 = !DILocation(line: 324, column: 12, scope: !330)
!344 = !DILocation(line: 325, column: 3, scope: !330)
!345 = !DILocation(line: 325, column: 7, scope: !330)
!346 = !DILocation(line: 325, column: 11, scope: !330)
!347 = !DILocation(line: 326, column: 3, scope: !330)
!348 = !DILocation(line: 326, column: 7, scope: !330)
!349 = !DILocation(line: 326, column: 22, scope: !330)
!350 = !DILocation(line: 328, column: 3, scope: !330)
!351 = !DILocation(line: 328, column: 7, scope: !330)
!352 = !DILocation(line: 328, column: 14, scope: !330)
!353 = !DILocation(line: 328, column: 19, scope: !330)
!354 = !DILocation(line: 329, column: 2, scope: !330)
!355 = !DILocation(line: 331, column: 2, scope: !204)
!356 = !DILocation(line: 331, column: 6, scope: !204)
!357 = !DILocation(line: 331, column: 13, scope: !204)
!358 = !DILocation(line: 331, column: 52, scope: !204)
!359 = !DILocation(line: 331, column: 24, scope: !204)
!360 = !DILocation(line: 331, column: 23, scope: !204)
!361 = !DILocation(line: 333, column: 2, scope: !204)
!362 = !DILocation(line: 333, column: 6, scope: !204)
!363 = !DILocation(line: 333, column: 13, scope: !204)
!364 = !DILocation(line: 333, column: 22, scope: !204)
!365 = !DILocation(line: 334, column: 2, scope: !204)
!366 = !DILocation(line: 334, column: 6, scope: !204)
!367 = !DILocation(line: 334, column: 13, scope: !204)
!368 = !DILocation(line: 334, column: 29, scope: !204)
!369 = !DILocation(line: 335, column: 2, scope: !204)
!370 = !DILocation(line: 335, column: 6, scope: !204)
!371 = !DILocation(line: 335, column: 13, scope: !204)
!372 = !DILocation(line: 335, column: 30, scope: !204)
!373 = !DILocation(line: 337, column: 6, scope: !204)
!374 = !DILocation(line: 337, column: 10, scope: !204)
!375 = !DILocation(line: 337, column: 17, scope: !204)
!376 = !DILocation(line: 337, column: 25, scope: !204)
!377 = !DILocation(line: 337, column: 37, scope: !204)
!378 = !DILocation(line: 338, column: 4, scope: !204)
!379 = !DILocation(line: 338, column: 7, scope: !380)
!380 = !DILexicalBlockFile(scope: !204, file: !1, discriminator: 1)
!381 = !DILocation(line: 338, column: 11, scope: !380)
!382 = !DILocation(line: 338, column: 18, scope: !380)
!383 = !DILocation(line: 338, column: 26, scope: !380)
!384 = !DILocation(line: 338, column: 43, scope: !380)
!385 = !DILocation(line: 338, column: 4, scope: !380)
!386 = !DILocation(line: 336, column: 2, scope: !204)
!387 = !DILocation(line: 336, column: 6, scope: !204)
!388 = !DILocation(line: 336, column: 13, scope: !204)
!389 = !DILocation(line: 337, column: 4, scope: !380)
!390 = !DILocation(line: 341, column: 2, scope: !204)
!391 = !DILocalVariable(name: "ret_", scope: !392, file: !1, line: 341, type: !393)
!392 = distinct !DILexicalBlock(scope: !204, file: !1, line: 341, column: 2)
!393 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !120)
!394 = !DILocation(line: 341, column: 2, scope: !392)
!395 = !DILocation(line: 341, column: 2, scope: !396)
!396 = !DILexicalBlockFile(scope: !392, file: !1, discriminator: 1)
!397 = !DILocation(line: 341, column: 2, scope: !398)
!398 = !DILexicalBlockFile(scope: !399, file: !1, discriminator: 2)
!399 = distinct !DILexicalBlock(scope: !392, file: !1, line: 341, column: 2)
!400 = !DILocation(line: 341, column: 2, scope: !401)
!401 = !DILexicalBlockFile(scope: !392, file: !1, discriminator: 3)
!402 = !DILocation(line: 349, column: 6, scope: !403)
!403 = distinct !DILexicalBlock(scope: !204, file: !1, line: 349, column: 6)
!404 = !DILocation(line: 349, column: 18, scope: !403)
!405 = !DILocation(line: 349, column: 32, scope: !403)
!406 = !DILocation(line: 349, column: 44, scope: !403)
!407 = !DILocation(line: 349, column: 30, scope: !403)
!408 = !DILocation(line: 349, column: 54, scope: !403)
!409 = !DILocation(line: 349, column: 6, scope: !204)
!410 = !DILocation(line: 351, column: 25, scope: !403)
!411 = !DILocation(line: 351, column: 37, scope: !403)
!412 = !DILocation(line: 351, column: 23, scope: !403)
!413 = !DILocation(line: 350, column: 3, scope: !403)
!414 = !DILocation(line: 350, column: 15, scope: !403)
!415 = !DILocation(line: 351, column: 5, scope: !403)
!416 = !DILocation(line: 353, column: 2, scope: !204)
!417 = !DILocation(line: 354, column: 1, scope: !204)
!418 = !DILocalVariable(name: "options", arg: 1, scope: !196, file: !1, line: 367, type: !199)
!419 = !DILocation(line: 367, column: 41, scope: !196)
!420 = !DILocalVariable(name: "lzma_mem", scope: !196, file: !1, line: 369, type: !421)
!421 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !129)
!422 = !DILocation(line: 369, column: 17, scope: !196)
!423 = !DILocation(line: 369, column: 55, scope: !196)
!424 = !DILocation(line: 369, column: 28, scope: !196)
!425 = !DILocation(line: 370, column: 6, scope: !426)
!426 = distinct !DILexicalBlock(scope: !196, file: !1, line: 370, column: 6)
!427 = !DILocation(line: 370, column: 15, scope: !426)
!428 = !DILocation(line: 370, column: 6, scope: !196)
!429 = !DILocation(line: 371, column: 3, scope: !426)
!430 = !DILocation(line: 373, column: 30, scope: !196)
!431 = !DILocation(line: 373, column: 28, scope: !196)
!432 = !DILocation(line: 373, column: 2, scope: !196)
!433 = !DILocation(line: 374, column: 1, scope: !196)
!434 = !DILocalVariable(name: "options", arg: 1, scope: !201, file: !1, line: 378, type: !199)
!435 = !DILocation(line: 378, column: 37, scope: !201)
!436 = !DILocalVariable(name: "out", arg: 2, scope: !201, file: !1, line: 378, type: !154)
!437 = !DILocation(line: 378, column: 55, scope: !201)
!438 = !DILocalVariable(name: "opt", scope: !201, file: !1, line: 380, type: !439)
!439 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !114)
!440 = !DILocation(line: 380, column: 33, scope: !201)
!441 = !DILocation(line: 380, column: 39, scope: !201)
!442 = !DILocalVariable(name: "d", scope: !201, file: !1, line: 381, type: !32)
!443 = !DILocation(line: 381, column: 11, scope: !201)
!444 = !DILocation(line: 381, column: 15, scope: !201)
!445 = !DILocation(line: 381, column: 15, scope: !446)
!446 = !DILexicalBlockFile(scope: !201, file: !1, discriminator: 1)
!447 = !DILocation(line: 381, column: 15, scope: !448)
!448 = !DILexicalBlockFile(scope: !201, file: !1, discriminator: 2)
!449 = !DILocation(line: 381, column: 15, scope: !450)
!450 = !DILexicalBlockFile(scope: !201, file: !1, discriminator: 3)
!451 = !DILocation(line: 381, column: 11, scope: !450)
!452 = !DILocation(line: 385, column: 2, scope: !201)
!453 = !DILocation(line: 386, column: 7, scope: !201)
!454 = !DILocation(line: 386, column: 9, scope: !201)
!455 = !DILocation(line: 386, column: 4, scope: !201)
!456 = !DILocation(line: 387, column: 7, scope: !201)
!457 = !DILocation(line: 387, column: 9, scope: !201)
!458 = !DILocation(line: 387, column: 4, scope: !201)
!459 = !DILocation(line: 388, column: 7, scope: !201)
!460 = !DILocation(line: 388, column: 9, scope: !201)
!461 = !DILocation(line: 388, column: 4, scope: !201)
!462 = !DILocation(line: 389, column: 7, scope: !201)
!463 = !DILocation(line: 389, column: 9, scope: !201)
!464 = !DILocation(line: 389, column: 4, scope: !201)
!465 = !DILocation(line: 390, column: 7, scope: !201)
!466 = !DILocation(line: 390, column: 9, scope: !201)
!467 = !DILocation(line: 390, column: 4, scope: !201)
!468 = !DILocation(line: 393, column: 6, scope: !469)
!469 = distinct !DILexicalBlock(scope: !201, file: !1, line: 393, column: 6)
!470 = !DILocation(line: 393, column: 8, scope: !469)
!471 = !DILocation(line: 393, column: 6, scope: !201)
!472 = !DILocation(line: 394, column: 3, scope: !469)
!473 = !DILocation(line: 394, column: 10, scope: !469)
!474 = !DILocation(line: 396, column: 25, scope: !469)
!475 = !DILocation(line: 396, column: 27, scope: !469)
!476 = !DILocation(line: 396, column: 12, scope: !469)
!477 = !DILocation(line: 396, column: 32, scope: !469)
!478 = !DILocation(line: 396, column: 3, scope: !469)
!479 = !DILocation(line: 396, column: 10, scope: !469)
!480 = !DILocation(line: 398, column: 2, scope: !201)
!481 = !DILocalVariable(name: "pos", arg: 1, scope: !292, file: !293, line: 110, type: !32)
!482 = !DILocation(line: 110, column: 23, scope: !292)
!483 = !DILocation(line: 114, column: 6, scope: !484)
!484 = distinct !DILexicalBlock(scope: !292, file: !293, line: 114, column: 6)
!485 = !DILocation(line: 114, column: 10, scope: !484)
!486 = !DILocation(line: 114, column: 6, scope: !292)
!487 = !DILocation(line: 115, column: 23, scope: !484)
!488 = !DILocation(line: 115, column: 10, scope: !484)
!489 = !DILocation(line: 115, column: 3, scope: !484)
!490 = !DILocation(line: 117, column: 6, scope: !491)
!491 = distinct !DILexicalBlock(scope: !292, file: !293, line: 117, column: 6)
!492 = !DILocation(line: 117, column: 10, scope: !491)
!493 = !DILocation(line: 117, column: 6, scope: !292)
!494 = !DILocation(line: 118, column: 10, scope: !491)
!495 = !DILocation(line: 118, column: 3, scope: !491)
!496 = !DILocation(line: 120, column: 9, scope: !292)
!497 = !DILocation(line: 120, column: 2, scope: !292)
!498 = !DILocation(line: 121, column: 1, scope: !292)
!499 = !DILocalVariable(name: "coder", arg: 1, scope: !277, file: !1, line: 137, type: !217)
!500 = !DILocation(line: 137, column: 40, scope: !277)
!501 = !DILocalVariable(name: "mf", arg: 2, scope: !277, file: !1, line: 137, type: !218)
!502 = !DILocation(line: 137, column: 70, scope: !277)
!503 = !DILocalVariable(name: "out", arg: 3, scope: !277, file: !1, line: 138, type: !153)
!504 = !DILocation(line: 138, column: 26, scope: !277)
!505 = !DILocalVariable(name: "out_pos", arg: 4, scope: !277, file: !1, line: 138, type: !151)
!506 = !DILocation(line: 138, column: 53, scope: !277)
!507 = !DILocalVariable(name: "out_size", arg: 5, scope: !277, file: !1, line: 139, type: !85)
!508 = !DILocation(line: 139, column: 10, scope: !277)
!509 = !DILocation(line: 141, column: 2, scope: !277)
!510 = !DILocation(line: 141, column: 10, scope: !511)
!511 = !DILexicalBlockFile(scope: !277, file: !1, discriminator: 1)
!512 = !DILocation(line: 141, column: 9, scope: !511)
!513 = !DILocation(line: 141, column: 20, scope: !511)
!514 = !DILocation(line: 141, column: 18, scope: !511)
!515 = !DILocation(line: 141, column: 2, scope: !511)
!516 = !DILocation(line: 142, column: 10, scope: !277)
!517 = !DILocation(line: 142, column: 17, scope: !277)
!518 = !DILocation(line: 142, column: 2, scope: !277)
!519 = !DILocation(line: 146, column: 20, scope: !520)
!520 = distinct !DILexicalBlock(scope: !521, file: !1, line: 146, column: 7)
!521 = distinct !DILexicalBlock(scope: !277, file: !1, line: 142, column: 27)
!522 = !DILocation(line: 146, column: 7, scope: !520)
!523 = !DILocation(line: 146, column: 24, scope: !520)
!524 = !DILocation(line: 146, column: 7, scope: !521)
!525 = !DILocation(line: 148, column: 8, scope: !526)
!526 = distinct !DILexicalBlock(scope: !527, file: !1, line: 148, column: 8)
!527 = distinct !DILexicalBlock(scope: !520, file: !1, line: 146, column: 30)
!528 = !DILocation(line: 148, column: 12, scope: !526)
!529 = !DILocation(line: 148, column: 19, scope: !526)
!530 = !DILocation(line: 148, column: 8, scope: !527)
!531 = !DILocation(line: 149, column: 11, scope: !526)
!532 = !DILocation(line: 149, column: 19, scope: !526)
!533 = !DILocation(line: 149, column: 5, scope: !526)
!534 = !DILocation(line: 149, column: 23, scope: !526)
!535 = !DILocation(line: 151, column: 11, scope: !527)
!536 = !DILocation(line: 151, column: 15, scope: !527)
!537 = !DILocation(line: 151, column: 22, scope: !527)
!538 = !DILocation(line: 151, column: 4, scope: !527)
!539 = !DILocation(line: 155, column: 7, scope: !540)
!540 = distinct !DILexicalBlock(scope: !521, file: !1, line: 155, column: 7)
!541 = !DILocation(line: 155, column: 14, scope: !540)
!542 = !DILocation(line: 155, column: 7, scope: !521)
!543 = !DILocation(line: 156, column: 4, scope: !540)
!544 = !DILocalVariable(name: "ret_", scope: !545, file: !1, line: 156, type: !393)
!545 = distinct !DILexicalBlock(scope: !540, file: !1, line: 156, column: 4)
!546 = !DILocation(line: 156, column: 4, scope: !545)
!547 = !DILocation(line: 156, column: 4, scope: !548)
!548 = !DILexicalBlockFile(scope: !545, file: !1, discriminator: 1)
!549 = !DILocation(line: 156, column: 4, scope: !550)
!550 = !DILexicalBlockFile(scope: !551, file: !1, discriminator: 2)
!551 = distinct !DILexicalBlock(scope: !545, file: !1, line: 156, column: 4)
!552 = !DILocation(line: 156, column: 4, scope: !553)
!553 = !DILexicalBlockFile(scope: !545, file: !1, discriminator: 3)
!554 = !DILocation(line: 156, column: 4, scope: !555)
!555 = !DILexicalBlockFile(scope: !545, file: !1, discriminator: 4)
!556 = !DILocation(line: 159, column: 3, scope: !521)
!557 = !DILocation(line: 159, column: 10, scope: !521)
!558 = !DILocation(line: 159, column: 28, scope: !521)
!559 = !DILocation(line: 160, column: 3, scope: !521)
!560 = !DILocation(line: 160, column: 10, scope: !521)
!561 = !DILocation(line: 160, column: 26, scope: !521)
!562 = !DILocation(line: 161, column: 3, scope: !521)
!563 = !DILocation(line: 161, column: 10, scope: !521)
!564 = !DILocation(line: 161, column: 19, scope: !521)
!565 = !DILocalVariable(name: "read_start", scope: !566, file: !1, line: 166, type: !32)
!566 = distinct !DILexicalBlock(scope: !521, file: !1, line: 165, column: 24)
!567 = !DILocation(line: 166, column: 12, scope: !566)
!568 = !DILocalVariable(name: "ret", scope: !566, file: !1, line: 167, type: !120)
!569 = !DILocation(line: 167, column: 12, scope: !566)
!570 = !DILocalVariable(name: "left", scope: !566, file: !1, line: 171, type: !571)
!571 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !32)
!572 = !DILocation(line: 171, column: 18, scope: !566)
!573 = !DILocation(line: 172, column: 7, scope: !566)
!574 = !DILocation(line: 172, column: 14, scope: !566)
!575 = !DILocation(line: 172, column: 5, scope: !566)
!576 = !DILocation(line: 171, column: 25, scope: !566)
!577 = !DILocalVariable(name: "limit", scope: !566, file: !1, line: 173, type: !32)
!578 = !DILocation(line: 173, column: 12, scope: !566)
!579 = !DILocation(line: 175, column: 7, scope: !580)
!580 = distinct !DILexicalBlock(scope: !566, file: !1, line: 175, column: 7)
!581 = !DILocation(line: 175, column: 14, scope: !580)
!582 = !DILocation(line: 175, column: 18, scope: !580)
!583 = !DILocation(line: 175, column: 12, scope: !580)
!584 = !DILocation(line: 175, column: 7, scope: !566)
!585 = !DILocation(line: 179, column: 10, scope: !586)
!586 = distinct !DILexicalBlock(scope: !580, file: !1, line: 175, column: 33)
!587 = !DILocation(line: 180, column: 3, scope: !586)
!588 = !DILocation(line: 183, column: 12, scope: !589)
!589 = distinct !DILexicalBlock(scope: !580, file: !1, line: 180, column: 10)
!590 = !DILocation(line: 183, column: 16, scope: !589)
!591 = !DILocation(line: 183, column: 27, scope: !589)
!592 = !DILocation(line: 183, column: 31, scope: !589)
!593 = !DILocation(line: 183, column: 25, scope: !589)
!594 = !DILocation(line: 184, column: 8, scope: !589)
!595 = !DILocation(line: 184, column: 6, scope: !589)
!596 = !DILocation(line: 184, column: 15, scope: !589)
!597 = !DILocation(line: 184, column: 19, scope: !589)
!598 = !DILocation(line: 184, column: 13, scope: !589)
!599 = !DILocation(line: 183, column: 10, scope: !589)
!600 = !DILocation(line: 189, column: 16, scope: !566)
!601 = !DILocation(line: 189, column: 20, scope: !566)
!602 = !DILocation(line: 189, column: 31, scope: !566)
!603 = !DILocation(line: 189, column: 35, scope: !566)
!604 = !DILocation(line: 189, column: 29, scope: !566)
!605 = !DILocation(line: 189, column: 14, scope: !566)
!606 = !DILocation(line: 192, column: 26, scope: !566)
!607 = !DILocation(line: 192, column: 33, scope: !566)
!608 = !DILocation(line: 192, column: 39, scope: !566)
!609 = !DILocation(line: 193, column: 5, scope: !566)
!610 = !DILocation(line: 193, column: 12, scope: !566)
!611 = !DILocation(line: 193, column: 16, scope: !566)
!612 = !DILocation(line: 194, column: 6, scope: !566)
!613 = !DILocation(line: 194, column: 13, scope: !566)
!614 = !DILocation(line: 195, column: 22, scope: !566)
!615 = !DILocation(line: 192, column: 9, scope: !566)
!616 = !DILocation(line: 192, column: 7, scope: !566)
!617 = !DILocation(line: 197, column: 31, scope: !566)
!618 = !DILocation(line: 197, column: 35, scope: !566)
!619 = !DILocation(line: 197, column: 46, scope: !566)
!620 = !DILocation(line: 197, column: 50, scope: !566)
!621 = !DILocation(line: 197, column: 44, scope: !566)
!622 = !DILocation(line: 198, column: 7, scope: !566)
!623 = !DILocation(line: 198, column: 5, scope: !566)
!624 = !DILocation(line: 197, column: 3, scope: !566)
!625 = !DILocation(line: 197, column: 10, scope: !566)
!626 = !DILocation(line: 197, column: 28, scope: !566)
!627 = !DILocation(line: 200, column: 3, scope: !566)
!628 = !DILocation(line: 200, column: 3, scope: !629)
!629 = !DILexicalBlockFile(scope: !566, file: !1, discriminator: 1)
!630 = !DILocation(line: 200, column: 3, scope: !631)
!631 = !DILexicalBlockFile(scope: !566, file: !1, discriminator: 2)
!632 = !DILocation(line: 200, column: 3, scope: !633)
!633 = !DILexicalBlockFile(scope: !566, file: !1, discriminator: 3)
!634 = !DILocation(line: 201, column: 3, scope: !566)
!635 = !DILocation(line: 201, column: 3, scope: !629)
!636 = !DILocation(line: 201, column: 3, scope: !631)
!637 = !DILocation(line: 201, column: 3, scope: !633)
!638 = !DILocation(line: 203, column: 7, scope: !639)
!639 = distinct !DILexicalBlock(scope: !566, file: !1, line: 203, column: 7)
!640 = !DILocation(line: 203, column: 11, scope: !639)
!641 = !DILocation(line: 203, column: 7, scope: !566)
!642 = !DILocation(line: 204, column: 4, scope: !639)
!643 = !DILocation(line: 209, column: 7, scope: !644)
!644 = distinct !DILexicalBlock(scope: !566, file: !1, line: 209, column: 7)
!645 = !DILocation(line: 209, column: 14, scope: !644)
!646 = !DILocation(line: 209, column: 33, scope: !644)
!647 = !DILocation(line: 209, column: 40, scope: !644)
!648 = !DILocation(line: 209, column: 30, scope: !644)
!649 = !DILocation(line: 209, column: 7, scope: !566)
!650 = !DILocation(line: 210, column: 32, scope: !651)
!651 = distinct !DILexicalBlock(scope: !644, file: !1, line: 209, column: 59)
!652 = !DILocation(line: 210, column: 36, scope: !651)
!653 = !DILocation(line: 210, column: 4, scope: !651)
!654 = !DILocation(line: 210, column: 11, scope: !651)
!655 = !DILocation(line: 210, column: 29, scope: !651)
!656 = !DILocation(line: 211, column: 4, scope: !651)
!657 = !DILocation(line: 211, column: 4, scope: !658)
!658 = !DILexicalBlockFile(scope: !651, file: !1, discriminator: 1)
!659 = !DILocation(line: 211, column: 4, scope: !660)
!660 = !DILexicalBlockFile(scope: !651, file: !1, discriminator: 2)
!661 = !DILocation(line: 211, column: 4, scope: !662)
!662 = !DILexicalBlockFile(scope: !651, file: !1, discriminator: 3)
!663 = !DILocation(line: 213, column: 4, scope: !651)
!664 = !DILocation(line: 213, column: 8, scope: !651)
!665 = !DILocation(line: 213, column: 19, scope: !651)
!666 = !DILocation(line: 214, column: 30, scope: !651)
!667 = !DILocation(line: 214, column: 4, scope: !651)
!668 = !DILocation(line: 215, column: 4, scope: !651)
!669 = !DILocation(line: 215, column: 11, scope: !651)
!670 = !DILocation(line: 215, column: 28, scope: !651)
!671 = !DILocation(line: 216, column: 4, scope: !651)
!672 = !DILocation(line: 216, column: 11, scope: !651)
!673 = !DILocation(line: 216, column: 20, scope: !651)
!674 = !DILocation(line: 217, column: 4, scope: !651)
!675 = !DILocation(line: 222, column: 21, scope: !566)
!676 = !DILocation(line: 222, column: 3, scope: !566)
!677 = !DILocation(line: 224, column: 3, scope: !566)
!678 = !DILocation(line: 224, column: 10, scope: !566)
!679 = !DILocation(line: 224, column: 19, scope: !566)
!680 = !DILocation(line: 225, column: 2, scope: !566)
!681 = !DILocation(line: 232, column: 15, scope: !521)
!682 = !DILocation(line: 232, column: 22, scope: !521)
!683 = !DILocation(line: 232, column: 28, scope: !521)
!684 = !DILocation(line: 232, column: 35, scope: !521)
!685 = !DILocation(line: 233, column: 5, scope: !521)
!686 = !DILocation(line: 233, column: 12, scope: !521)
!687 = !DILocation(line: 234, column: 5, scope: !521)
!688 = !DILocation(line: 234, column: 10, scope: !521)
!689 = !DILocation(line: 234, column: 19, scope: !521)
!690 = !DILocation(line: 232, column: 3, scope: !521)
!691 = !DILocation(line: 235, column: 7, scope: !692)
!692 = distinct !DILexicalBlock(scope: !521, file: !1, line: 235, column: 7)
!693 = !DILocation(line: 235, column: 14, scope: !692)
!694 = !DILocation(line: 235, column: 25, scope: !692)
!695 = !DILocation(line: 235, column: 32, scope: !692)
!696 = !DILocation(line: 235, column: 22, scope: !692)
!697 = !DILocation(line: 235, column: 7, scope: !521)
!698 = !DILocation(line: 236, column: 4, scope: !692)
!699 = !DILocation(line: 238, column: 3, scope: !521)
!700 = !DILocation(line: 238, column: 10, scope: !521)
!701 = !DILocation(line: 238, column: 19, scope: !521)
!702 = !DILocation(line: 239, column: 3, scope: !521)
!703 = !DILocation(line: 243, column: 15, scope: !521)
!704 = !DILocation(line: 243, column: 22, scope: !521)
!705 = !DILocation(line: 243, column: 28, scope: !521)
!706 = !DILocation(line: 243, column: 35, scope: !521)
!707 = !DILocation(line: 245, column: 5, scope: !521)
!708 = !DILocation(line: 245, column: 10, scope: !521)
!709 = !DILocation(line: 245, column: 19, scope: !521)
!710 = !DILocation(line: 243, column: 3, scope: !521)
!711 = !DILocation(line: 246, column: 7, scope: !712)
!712 = distinct !DILexicalBlock(scope: !521, file: !1, line: 246, column: 7)
!713 = !DILocation(line: 246, column: 14, scope: !712)
!714 = !DILocation(line: 246, column: 22, scope: !712)
!715 = !DILocation(line: 246, column: 7, scope: !521)
!716 = !DILocation(line: 247, column: 4, scope: !712)
!717 = !DILocation(line: 249, column: 3, scope: !521)
!718 = !DILocation(line: 249, column: 10, scope: !521)
!719 = !DILocation(line: 249, column: 19, scope: !521)
!720 = !DILocation(line: 256, column: 11, scope: !521)
!721 = !DILocation(line: 256, column: 15, scope: !521)
!722 = !DILocation(line: 256, column: 20, scope: !521)
!723 = !DILocation(line: 256, column: 29, scope: !521)
!724 = !DILocation(line: 256, column: 40, scope: !521)
!725 = !DILocation(line: 256, column: 47, scope: !521)
!726 = !DILocation(line: 256, column: 3, scope: !521)
!727 = !DILocation(line: 257, column: 7, scope: !728)
!728 = distinct !DILexicalBlock(scope: !521, file: !1, line: 257, column: 7)
!729 = !DILocation(line: 257, column: 14, scope: !728)
!730 = !DILocation(line: 257, column: 32, scope: !728)
!731 = !DILocation(line: 257, column: 7, scope: !521)
!732 = !DILocation(line: 258, column: 4, scope: !728)
!733 = !DILocation(line: 260, column: 3, scope: !521)
!734 = !DILocation(line: 260, column: 10, scope: !521)
!735 = !DILocation(line: 260, column: 19, scope: !521)
!736 = !DILocation(line: 261, column: 3, scope: !521)
!737 = !DILocation(line: 141, column: 2, scope: !738)
!738 = !DILexicalBlockFile(scope: !277, file: !1, discriminator: 2)
!739 = !DILocation(line: 264, column: 2, scope: !277)
!740 = !DILocation(line: 265, column: 1, scope: !277)
!741 = !DILocalVariable(name: "coder", arg: 1, scope: !290, file: !1, line: 269, type: !23)
!742 = !DILocation(line: 269, column: 31, scope: !290)
!743 = !DILocalVariable(name: "allocator", arg: 2, scope: !290, file: !1, line: 269, type: !137)
!744 = !DILocation(line: 269, column: 54, scope: !290)
!745 = !DILocation(line: 271, column: 12, scope: !290)
!746 = !DILocation(line: 271, column: 19, scope: !290)
!747 = !DILocation(line: 271, column: 25, scope: !290)
!748 = !DILocation(line: 271, column: 2, scope: !290)
!749 = !DILocation(line: 272, column: 12, scope: !290)
!750 = !DILocation(line: 272, column: 19, scope: !290)
!751 = !DILocation(line: 272, column: 2, scope: !290)
!752 = !DILocation(line: 273, column: 2, scope: !290)
!753 = !DILocalVariable(name: "coder", arg: 1, scope: !291, file: !1, line: 278, type: !23)
!754 = !DILocation(line: 278, column: 42, scope: !291)
!755 = !DILocalVariable(name: "filter", arg: 2, scope: !291, file: !1, line: 278, type: !177)
!756 = !DILocation(line: 278, column: 68, scope: !291)
!757 = !DILocalVariable(name: "opt", scope: !291, file: !1, line: 280, type: !758)
!758 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !27, size: 64, align: 64)
!759 = !DILocation(line: 280, column: 21, scope: !291)
!760 = !DILocation(line: 285, column: 6, scope: !761)
!761 = distinct !DILexicalBlock(scope: !291, file: !1, line: 285, column: 6)
!762 = !DILocation(line: 285, column: 14, scope: !761)
!763 = !DILocation(line: 285, column: 22, scope: !761)
!764 = !DILocation(line: 285, column: 30, scope: !761)
!765 = !DILocation(line: 285, column: 33, scope: !766)
!766 = !DILexicalBlockFile(scope: !761, file: !1, discriminator: 1)
!767 = !DILocation(line: 285, column: 40, scope: !766)
!768 = !DILocation(line: 285, column: 49, scope: !766)
!769 = !DILocation(line: 285, column: 6, scope: !766)
!770 = !DILocation(line: 286, column: 3, scope: !761)
!771 = !DILocation(line: 290, column: 8, scope: !291)
!772 = !DILocation(line: 290, column: 16, scope: !291)
!773 = !DILocation(line: 290, column: 6, scope: !291)
!774 = !DILocation(line: 291, column: 6, scope: !775)
!775 = distinct !DILexicalBlock(scope: !291, file: !1, line: 291, column: 6)
!776 = !DILocation(line: 291, column: 13, scope: !775)
!777 = !DILocation(line: 291, column: 21, scope: !775)
!778 = !DILocation(line: 291, column: 27, scope: !775)
!779 = !DILocation(line: 291, column: 32, scope: !775)
!780 = !DILocation(line: 291, column: 24, scope: !775)
!781 = !DILocation(line: 291, column: 35, scope: !775)
!782 = !DILocation(line: 291, column: 38, scope: !783)
!783 = !DILexicalBlockFile(scope: !775, file: !1, discriminator: 1)
!784 = !DILocation(line: 291, column: 45, scope: !783)
!785 = !DILocation(line: 291, column: 53, scope: !783)
!786 = !DILocation(line: 291, column: 59, scope: !783)
!787 = !DILocation(line: 291, column: 64, scope: !783)
!788 = !DILocation(line: 291, column: 56, scope: !783)
!789 = !DILocation(line: 292, column: 4, scope: !775)
!790 = !DILocation(line: 292, column: 7, scope: !783)
!791 = !DILocation(line: 292, column: 14, scope: !783)
!792 = !DILocation(line: 292, column: 22, scope: !783)
!793 = !DILocation(line: 292, column: 28, scope: !783)
!794 = !DILocation(line: 292, column: 33, scope: !783)
!795 = !DILocation(line: 292, column: 25, scope: !783)
!796 = !DILocation(line: 291, column: 6, scope: !797)
!797 = !DILexicalBlockFile(scope: !291, file: !1, discriminator: 2)
!798 = !DILocation(line: 294, column: 7, scope: !799)
!799 = distinct !DILexicalBlock(scope: !800, file: !1, line: 294, column: 7)
!800 = distinct !DILexicalBlock(scope: !775, file: !1, line: 292, column: 37)
!801 = !DILocation(line: 294, column: 12, scope: !799)
!802 = !DILocation(line: 294, column: 15, scope: !799)
!803 = !DILocation(line: 294, column: 31, scope: !799)
!804 = !DILocation(line: 294, column: 34, scope: !805)
!805 = !DILexicalBlockFile(scope: !799, file: !1, discriminator: 1)
!806 = !DILocation(line: 294, column: 39, scope: !805)
!807 = !DILocation(line: 294, column: 42, scope: !805)
!808 = !DILocation(line: 295, column: 5, scope: !799)
!809 = !DILocation(line: 295, column: 8, scope: !805)
!810 = !DILocation(line: 295, column: 13, scope: !805)
!811 = !DILocation(line: 295, column: 18, scope: !805)
!812 = !DILocation(line: 295, column: 23, scope: !805)
!813 = !DILocation(line: 295, column: 16, scope: !805)
!814 = !DILocation(line: 295, column: 26, scope: !805)
!815 = !DILocation(line: 296, column: 5, scope: !799)
!816 = !DILocation(line: 296, column: 8, scope: !805)
!817 = !DILocation(line: 296, column: 13, scope: !805)
!818 = !DILocation(line: 296, column: 16, scope: !805)
!819 = !DILocation(line: 294, column: 7, scope: !820)
!820 = !DILexicalBlockFile(scope: !800, file: !1, discriminator: 2)
!821 = !DILocation(line: 297, column: 4, scope: !799)
!822 = !DILocation(line: 301, column: 23, scope: !800)
!823 = !DILocation(line: 301, column: 28, scope: !800)
!824 = !DILocation(line: 301, column: 3, scope: !800)
!825 = !DILocation(line: 301, column: 10, scope: !800)
!826 = !DILocation(line: 301, column: 18, scope: !800)
!827 = !DILocation(line: 301, column: 21, scope: !800)
!828 = !DILocation(line: 302, column: 23, scope: !800)
!829 = !DILocation(line: 302, column: 28, scope: !800)
!830 = !DILocation(line: 302, column: 3, scope: !800)
!831 = !DILocation(line: 302, column: 10, scope: !800)
!832 = !DILocation(line: 302, column: 18, scope: !800)
!833 = !DILocation(line: 302, column: 21, scope: !800)
!834 = !DILocation(line: 303, column: 23, scope: !800)
!835 = !DILocation(line: 303, column: 28, scope: !800)
!836 = !DILocation(line: 303, column: 3, scope: !800)
!837 = !DILocation(line: 303, column: 10, scope: !800)
!838 = !DILocation(line: 303, column: 18, scope: !800)
!839 = !DILocation(line: 303, column: 21, scope: !800)
!840 = !DILocation(line: 304, column: 3, scope: !800)
!841 = !DILocation(line: 304, column: 10, scope: !800)
!842 = !DILocation(line: 304, column: 26, scope: !800)
!843 = !DILocation(line: 305, column: 3, scope: !800)
!844 = !DILocation(line: 305, column: 10, scope: !800)
!845 = !DILocation(line: 305, column: 27, scope: !800)
!846 = !DILocation(line: 306, column: 2, scope: !800)
!847 = !DILocation(line: 308, column: 2, scope: !291)
!848 = !DILocation(line: 309, column: 1, scope: !291)
!849 = !DILocalVariable(name: "mf", arg: 1, scope: !278, file: !209, line: 239, type: !281)
!850 = !DILocation(line: 239, column: 29, scope: !278)
!851 = !DILocation(line: 241, column: 9, scope: !278)
!852 = !DILocation(line: 241, column: 13, scope: !278)
!853 = !DILocation(line: 241, column: 25, scope: !278)
!854 = !DILocation(line: 241, column: 29, scope: !278)
!855 = !DILocation(line: 241, column: 23, scope: !278)
!856 = !DILocation(line: 241, column: 40, scope: !278)
!857 = !DILocation(line: 241, column: 44, scope: !278)
!858 = !DILocation(line: 241, column: 38, scope: !278)
!859 = !DILocation(line: 241, column: 2, scope: !278)
!860 = !DILocalVariable(name: "coder", arg: 1, scope: !283, file: !1, line: 112, type: !23)
!861 = !DILocation(line: 112, column: 39, scope: !283)
!862 = !DILocation(line: 114, column: 2, scope: !283)
!863 = !DILocation(line: 114, column: 2, scope: !864)
!864 = !DILexicalBlockFile(scope: !283, file: !1, discriminator: 1)
!865 = !DILocation(line: 114, column: 2, scope: !866)
!866 = !DILexicalBlockFile(scope: !283, file: !1, discriminator: 2)
!867 = !DILocation(line: 114, column: 2, scope: !868)
!868 = !DILexicalBlockFile(scope: !283, file: !1, discriminator: 3)
!869 = !DILocation(line: 115, column: 2, scope: !283)
!870 = !DILocation(line: 115, column: 2, scope: !864)
!871 = !DILocation(line: 115, column: 2, scope: !866)
!872 = !DILocation(line: 115, column: 2, scope: !868)
!873 = !DILocation(line: 119, column: 6, scope: !874)
!874 = distinct !DILexicalBlock(scope: !283, file: !1, line: 119, column: 6)
!875 = !DILocation(line: 119, column: 13, scope: !874)
!876 = !DILocation(line: 119, column: 6, scope: !283)
!877 = !DILocation(line: 120, column: 3, scope: !874)
!878 = !DILocation(line: 120, column: 10, scope: !874)
!879 = !DILocation(line: 120, column: 17, scope: !874)
!880 = !DILocation(line: 122, column: 3, scope: !874)
!881 = !DILocation(line: 122, column: 10, scope: !874)
!882 = !DILocation(line: 122, column: 17, scope: !874)
!883 = !DILocation(line: 124, column: 2, scope: !283)
!884 = !DILocation(line: 124, column: 9, scope: !283)
!885 = !DILocation(line: 124, column: 31, scope: !283)
!886 = !DILocation(line: 127, column: 19, scope: !283)
!887 = !DILocation(line: 127, column: 26, scope: !283)
!888 = !DILocation(line: 127, column: 44, scope: !283)
!889 = !DILocation(line: 127, column: 49, scope: !283)
!890 = !DILocation(line: 127, column: 18, scope: !283)
!891 = !DILocation(line: 127, column: 2, scope: !283)
!892 = !DILocation(line: 127, column: 9, scope: !283)
!893 = !DILocation(line: 127, column: 16, scope: !283)
!894 = !DILocation(line: 128, column: 19, scope: !283)
!895 = !DILocation(line: 128, column: 26, scope: !283)
!896 = !DILocation(line: 128, column: 44, scope: !283)
!897 = !DILocation(line: 128, column: 49, scope: !283)
!898 = !DILocation(line: 128, column: 18, scope: !283)
!899 = !DILocation(line: 128, column: 2, scope: !283)
!900 = !DILocation(line: 128, column: 9, scope: !283)
!901 = !DILocation(line: 128, column: 16, scope: !283)
!902 = !DILocation(line: 131, column: 2, scope: !283)
!903 = !DILocation(line: 131, column: 9, scope: !283)
!904 = !DILocation(line: 131, column: 17, scope: !283)
!905 = !DILocation(line: 132, column: 2, scope: !283)
!906 = !DILocalVariable(name: "coder", arg: 1, scope: !286, file: !1, line: 55, type: !23)
!907 = !DILocation(line: 55, column: 31, scope: !286)
!908 = !DILocalVariable(name: "pos", scope: !286, file: !1, line: 57, type: !85)
!909 = !DILocation(line: 57, column: 9, scope: !286)
!910 = !DILocalVariable(name: "size", scope: !286, file: !1, line: 58, type: !85)
!911 = !DILocation(line: 58, column: 9, scope: !286)
!912 = !DILocation(line: 60, column: 2, scope: !286)
!913 = !DILocation(line: 60, column: 2, scope: !914)
!914 = !DILexicalBlockFile(scope: !286, file: !1, discriminator: 1)
!915 = !DILocation(line: 60, column: 2, scope: !916)
!916 = !DILexicalBlockFile(scope: !286, file: !1, discriminator: 2)
!917 = !DILocation(line: 60, column: 2, scope: !918)
!918 = !DILexicalBlockFile(scope: !286, file: !1, discriminator: 3)
!919 = !DILocation(line: 61, column: 2, scope: !286)
!920 = !DILocation(line: 61, column: 2, scope: !914)
!921 = !DILocation(line: 61, column: 2, scope: !916)
!922 = !DILocation(line: 61, column: 2, scope: !918)
!923 = !DILocation(line: 62, column: 2, scope: !286)
!924 = !DILocation(line: 62, column: 2, scope: !914)
!925 = !DILocation(line: 62, column: 2, scope: !916)
!926 = !DILocation(line: 62, column: 2, scope: !918)
!927 = !DILocation(line: 63, column: 2, scope: !286)
!928 = !DILocation(line: 63, column: 2, scope: !914)
!929 = !DILocation(line: 63, column: 2, scope: !916)
!930 = !DILocation(line: 63, column: 2, scope: !918)
!931 = !DILocation(line: 65, column: 6, scope: !932)
!932 = distinct !DILexicalBlock(scope: !286, file: !1, line: 65, column: 6)
!933 = !DILocation(line: 65, column: 13, scope: !932)
!934 = !DILocation(line: 65, column: 6, scope: !286)
!935 = !DILocation(line: 66, column: 7, scope: !936)
!936 = distinct !DILexicalBlock(scope: !932, file: !1, line: 65, column: 30)
!937 = !DILocation(line: 68, column: 7, scope: !938)
!938 = distinct !DILexicalBlock(scope: !936, file: !1, line: 68, column: 7)
!939 = !DILocation(line: 68, column: 14, scope: !938)
!940 = !DILocation(line: 68, column: 7, scope: !936)
!941 = !DILocation(line: 69, column: 15, scope: !938)
!942 = !DILocation(line: 69, column: 4, scope: !938)
!943 = !DILocation(line: 69, column: 11, scope: !938)
!944 = !DILocation(line: 69, column: 20, scope: !938)
!945 = !DILocation(line: 71, column: 15, scope: !938)
!946 = !DILocation(line: 71, column: 4, scope: !938)
!947 = !DILocation(line: 71, column: 11, scope: !938)
!948 = !DILocation(line: 71, column: 20, scope: !938)
!949 = !DILocation(line: 72, column: 2, scope: !936)
!950 = !DILocation(line: 73, column: 7, scope: !951)
!951 = distinct !DILexicalBlock(scope: !932, file: !1, line: 72, column: 9)
!952 = !DILocation(line: 75, column: 7, scope: !953)
!953 = distinct !DILexicalBlock(scope: !951, file: !1, line: 75, column: 7)
!954 = !DILocation(line: 75, column: 14, scope: !953)
!955 = !DILocation(line: 75, column: 7, scope: !951)
!956 = !DILocation(line: 76, column: 15, scope: !953)
!957 = !DILocation(line: 76, column: 4, scope: !953)
!958 = !DILocation(line: 76, column: 11, scope: !953)
!959 = !DILocation(line: 76, column: 20, scope: !953)
!960 = !DILocation(line: 78, column: 15, scope: !953)
!961 = !DILocation(line: 78, column: 4, scope: !953)
!962 = !DILocation(line: 78, column: 11, scope: !953)
!963 = !DILocation(line: 78, column: 20, scope: !953)
!964 = !DILocation(line: 82, column: 19, scope: !286)
!965 = !DILocation(line: 82, column: 2, scope: !286)
!966 = !DILocation(line: 82, column: 9, scope: !286)
!967 = !DILocation(line: 82, column: 17, scope: !286)
!968 = !DILocation(line: 85, column: 9, scope: !286)
!969 = !DILocation(line: 85, column: 16, scope: !286)
!970 = !DILocation(line: 85, column: 34, scope: !286)
!971 = !DILocation(line: 85, column: 7, scope: !286)
!972 = !DILocation(line: 86, column: 23, scope: !286)
!973 = !DILocation(line: 86, column: 28, scope: !286)
!974 = !DILocation(line: 86, column: 16, scope: !286)
!975 = !DILocation(line: 86, column: 2, scope: !286)
!976 = !DILocation(line: 86, column: 9, scope: !286)
!977 = !DILocation(line: 86, column: 20, scope: !286)
!978 = !DILocation(line: 87, column: 23, scope: !286)
!979 = !DILocation(line: 87, column: 28, scope: !286)
!980 = !DILocation(line: 87, column: 34, scope: !286)
!981 = !DILocation(line: 87, column: 22, scope: !286)
!982 = !DILocation(line: 87, column: 16, scope: !286)
!983 = !DILocation(line: 87, column: 2, scope: !286)
!984 = !DILocation(line: 87, column: 9, scope: !286)
!985 = !DILocation(line: 87, column: 20, scope: !286)
!986 = !DILocation(line: 88, column: 22, scope: !286)
!987 = !DILocation(line: 88, column: 27, scope: !286)
!988 = !DILocation(line: 88, column: 16, scope: !286)
!989 = !DILocation(line: 88, column: 2, scope: !286)
!990 = !DILocation(line: 88, column: 9, scope: !286)
!991 = !DILocation(line: 88, column: 20, scope: !286)
!992 = !DILocation(line: 91, column: 9, scope: !286)
!993 = !DILocation(line: 91, column: 16, scope: !286)
!994 = !DILocation(line: 91, column: 32, scope: !286)
!995 = !DILocation(line: 91, column: 7, scope: !286)
!996 = !DILocation(line: 92, column: 22, scope: !286)
!997 = !DILocation(line: 92, column: 27, scope: !286)
!998 = !DILocation(line: 92, column: 16, scope: !286)
!999 = !DILocation(line: 92, column: 2, scope: !286)
!1000 = !DILocation(line: 92, column: 9, scope: !286)
!1001 = !DILocation(line: 92, column: 20, scope: !286)
!1002 = !DILocation(line: 93, column: 22, scope: !286)
!1003 = !DILocation(line: 93, column: 27, scope: !286)
!1004 = !DILocation(line: 93, column: 16, scope: !286)
!1005 = !DILocation(line: 93, column: 2, scope: !286)
!1006 = !DILocation(line: 93, column: 9, scope: !286)
!1007 = !DILocation(line: 93, column: 20, scope: !286)
!1008 = !DILocation(line: 96, column: 6, scope: !1009)
!1009 = distinct !DILexicalBlock(scope: !286, file: !1, line: 96, column: 6)
!1010 = !DILocation(line: 96, column: 13, scope: !1009)
!1011 = !DILocation(line: 96, column: 6, scope: !286)
!1012 = !DILocation(line: 97, column: 28, scope: !1009)
!1013 = !DILocation(line: 97, column: 35, scope: !1009)
!1014 = !DILocation(line: 97, column: 44, scope: !1009)
!1015 = !DILocation(line: 97, column: 51, scope: !1009)
!1016 = !DILocation(line: 97, column: 57, scope: !1009)
!1017 = !DILocation(line: 97, column: 55, scope: !1009)
!1018 = !DILocation(line: 97, column: 3, scope: !1009)
!1019 = !DILocation(line: 99, column: 2, scope: !286)
!1020 = !DILocation(line: 99, column: 9, scope: !286)
!1021 = !DILocation(line: 99, column: 25, scope: !286)
!1022 = !DILocation(line: 100, column: 2, scope: !286)
!1023 = !DILocation(line: 100, column: 9, scope: !286)
!1024 = !DILocation(line: 100, column: 26, scope: !286)
!1025 = !DILocation(line: 101, column: 2, scope: !286)
!1026 = !DILocation(line: 101, column: 9, scope: !286)
!1027 = !DILocation(line: 101, column: 31, scope: !286)
!1028 = !DILocation(line: 105, column: 2, scope: !286)
!1029 = !DILocation(line: 105, column: 9, scope: !286)
!1030 = !DILocation(line: 105, column: 25, scope: !286)
!1031 = !DILocation(line: 107, column: 2, scope: !286)
!1032 = !DILocalVariable(name: "mf", arg: 1, scope: !287, file: !209, line: 280, type: !219)
!1033 = !DILocation(line: 280, column: 18, scope: !287)
!1034 = !DILocalVariable(name: "out", arg: 2, scope: !287, file: !209, line: 280, type: !154)
!1035 = !DILocation(line: 280, column: 31, scope: !287)
!1036 = !DILocalVariable(name: "out_pos", arg: 3, scope: !287, file: !209, line: 280, type: !152)
!1037 = !DILocation(line: 280, column: 44, scope: !287)
!1038 = !DILocalVariable(name: "out_size", arg: 4, scope: !287, file: !209, line: 280, type: !85)
!1039 = !DILocation(line: 280, column: 60, scope: !287)
!1040 = !DILocalVariable(name: "left", arg: 5, scope: !287, file: !209, line: 281, type: !152)
!1041 = !DILocation(line: 281, column: 11, scope: !287)
!1042 = !DILocalVariable(name: "out_avail", scope: !287, file: !209, line: 283, type: !1043)
!1043 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !85)
!1044 = !DILocation(line: 283, column: 15, scope: !287)
!1045 = !DILocation(line: 283, column: 27, scope: !287)
!1046 = !DILocation(line: 283, column: 39, scope: !287)
!1047 = !DILocation(line: 283, column: 38, scope: !287)
!1048 = !DILocation(line: 283, column: 36, scope: !287)
!1049 = !DILocalVariable(name: "copy_size", scope: !287, file: !209, line: 284, type: !1043)
!1050 = !DILocation(line: 284, column: 15, scope: !287)
!1051 = !DILocation(line: 284, column: 27, scope: !287)
!1052 = !DILocation(line: 284, column: 27, scope: !1053)
!1053 = !DILexicalBlockFile(scope: !287, file: !209, discriminator: 1)
!1054 = !DILocation(line: 284, column: 27, scope: !1055)
!1055 = !DILexicalBlockFile(scope: !287, file: !209, discriminator: 2)
!1056 = !DILocation(line: 284, column: 27, scope: !1057)
!1057 = !DILexicalBlockFile(scope: !287, file: !209, discriminator: 3)
!1058 = !DILocation(line: 284, column: 15, scope: !1057)
!1059 = !DILocation(line: 286, column: 2, scope: !287)
!1060 = !DILocation(line: 286, column: 2, scope: !1053)
!1061 = !DILocation(line: 286, column: 2, scope: !1055)
!1062 = !DILocation(line: 286, column: 2, scope: !1057)
!1063 = !DILocation(line: 287, column: 2, scope: !287)
!1064 = !DILocation(line: 287, column: 2, scope: !1053)
!1065 = !DILocation(line: 287, column: 2, scope: !1055)
!1066 = !DILocation(line: 287, column: 2, scope: !1057)
!1067 = !DILocation(line: 289, column: 9, scope: !287)
!1068 = !DILocation(line: 289, column: 16, scope: !287)
!1069 = !DILocation(line: 289, column: 15, scope: !287)
!1070 = !DILocation(line: 289, column: 13, scope: !287)
!1071 = !DILocation(line: 289, column: 25, scope: !287)
!1072 = !DILocation(line: 289, column: 29, scope: !287)
!1073 = !DILocation(line: 289, column: 38, scope: !287)
!1074 = !DILocation(line: 289, column: 42, scope: !287)
!1075 = !DILocation(line: 289, column: 36, scope: !287)
!1076 = !DILocation(line: 289, column: 54, scope: !287)
!1077 = !DILocation(line: 289, column: 53, scope: !287)
!1078 = !DILocation(line: 289, column: 51, scope: !287)
!1079 = !DILocation(line: 290, column: 4, scope: !287)
!1080 = !DILocation(line: 289, column: 2, scope: !287)
!1081 = !DILocation(line: 292, column: 14, scope: !287)
!1082 = !DILocation(line: 292, column: 3, scope: !287)
!1083 = !DILocation(line: 292, column: 11, scope: !287)
!1084 = !DILocation(line: 293, column: 11, scope: !287)
!1085 = !DILocation(line: 293, column: 3, scope: !287)
!1086 = !DILocation(line: 293, column: 8, scope: !287)
!1087 = !DILocation(line: 294, column: 2, scope: !287)
