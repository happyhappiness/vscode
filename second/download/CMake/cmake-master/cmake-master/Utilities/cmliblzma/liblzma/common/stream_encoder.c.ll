; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type { i32, i8, %struct.lzma_next_coder_s, %struct.lzma_block, [5 x %struct.lzma_filter], %struct.lzma_next_coder_s, %struct.lzma_index_s*, i64, i64, [1024 x i8] }
%struct.lzma_block = type { i32, i32, i32, i64, i64, %struct.lzma_filter*, [64 x i8], i8*, i8*, i8*, i32, i32, i64, i64, i64, i64, i64, i64, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8, i8, i8 }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_index_s = type opaque
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_stream_flags = type { i32, i64, i32, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8, i8, i8, i32, i32 }
%struct.lzma_stream = type { i8*, i64, i64, i8*, i64, i64, %struct.lzma_allocator*, %struct.lzma_internal_s*, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i32, i32 }
%struct.lzma_internal_s = type { %struct.lzma_next_coder_s, i32, i64, [4 x i8], i8 }

@LZMA_NEXT_CODER_INIT = internal constant %struct.lzma_next_coder_s { %struct.lzma_coder_s* null, i64 -1, i64 0, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* null, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* null, i32 (%struct.lzma_coder_s*)* null, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* null, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* null }, align 8
@stream_encode.convert = internal constant [4 x i32] [i32 0, i32 1, i32 3, i32 3], align 16
@.str = private unnamed_addr constant [19 x i8] c"unpadded_size != 0\00", align 1
@.str.1 = private unnamed_addr constant [86 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_encoder.c\00", align 1
@__PRETTY_FUNCTION__.stream_encode = private unnamed_addr constant [164 x i8] c"lzma_ret stream_encode(lzma_coder *, lzma_allocator *, const uint8_t *restrict, size_t *restrict, size_t, uint8_t *restrict, size_t *restrict, size_t, lzma_action)\00", align 1
@.str.2 = private unnamed_addr constant [2 x i8] c"0\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_stream_encoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter* %filters, i32 %check) #0 !dbg !203 {
entry:
  %retval = alloca i32, align 4
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter*, align 8
  %check.addr = alloca i32, align 4
  %stream_flags = alloca %struct.lzma_stream_flags, align 8
  %ret_ = alloca i32, align 4
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !250, metadata !251), !dbg !252
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !253, metadata !251), !dbg !254
  store %struct.lzma_filter* %filters, %struct.lzma_filter** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filters.addr, metadata !255, metadata !251), !dbg !256
  store i32 %check, i32* %check.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %check.addr, metadata !257, metadata !251), !dbg !258
  call void @llvm.dbg.declare(metadata %struct.lzma_stream_flags* %stream_flags, metadata !259, metadata !251), !dbg !281
  %version = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 0, !dbg !282
  store i32 0, i32* %version, align 8, !dbg !282
  %backward_size = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 1, !dbg !282
  store i64 0, i64* %backward_size, align 8, !dbg !282
  %check1 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 2, !dbg !282
  %0 = load i32, i32* %check.addr, align 4, !dbg !283
  store i32 %0, i32* %check1, align 8, !dbg !282
  %reserved_enum1 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 3, !dbg !282
  store i32 0, i32* %reserved_enum1, align 4, !dbg !282
  %reserved_enum2 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 4, !dbg !282
  store i32 0, i32* %reserved_enum2, align 8, !dbg !282
  %reserved_enum3 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 5, !dbg !282
  store i32 0, i32* %reserved_enum3, align 4, !dbg !282
  %reserved_enum4 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 6, !dbg !282
  store i32 0, i32* %reserved_enum4, align 8, !dbg !282
  %reserved_bool1 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 7, !dbg !282
  store i8 0, i8* %reserved_bool1, align 4, !dbg !282
  %reserved_bool2 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 8, !dbg !282
  store i8 0, i8* %reserved_bool2, align 1, !dbg !282
  %reserved_bool3 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 9, !dbg !282
  store i8 0, i8* %reserved_bool3, align 2, !dbg !282
  %reserved_bool4 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 10, !dbg !282
  store i8 0, i8* %reserved_bool4, align 1, !dbg !282
  %reserved_bool5 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 11, !dbg !282
  store i8 0, i8* %reserved_bool5, align 8, !dbg !282
  %reserved_bool6 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 12, !dbg !282
  store i8 0, i8* %reserved_bool6, align 1, !dbg !282
  %reserved_bool7 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 13, !dbg !282
  store i8 0, i8* %reserved_bool7, align 2, !dbg !282
  %reserved_bool8 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 14, !dbg !282
  store i8 0, i8* %reserved_bool8, align 1, !dbg !282
  %reserved_int1 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 15, !dbg !282
  store i32 0, i32* %reserved_int1, align 4, !dbg !282
  %reserved_int2 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 16, !dbg !282
  store i32 0, i32* %reserved_int2, align 8, !dbg !282
  br label %do.body, !dbg !284

do.body:                                          ; preds = %entry
  %1 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !285
  %init = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %1, i32 0, i32 2, !dbg !285
  %2 = load i64, i64* %init, align 8, !dbg !285
  %cmp = icmp ne i64 ptrtoint (i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, i32)* @lzma_stream_encoder_init to i64), %2, !dbg !285
  br i1 %cmp, label %if.then, label %if.end, !dbg !285

if.then:                                          ; preds = %do.body
  %3 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !289
  %4 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !289
  call void @lzma_next_end(%struct.lzma_next_coder_s* %3, %struct.lzma_allocator* %4), !dbg !289
  br label %if.end, !dbg !289

if.end:                                           ; preds = %if.then, %do.body
  %5 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !291
  %init2 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %5, i32 0, i32 2, !dbg !291
  store i64 ptrtoint (i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, i32)* @lzma_stream_encoder_init to i64), i64* %init2, align 8, !dbg !291
  br label %do.end, !dbg !291

do.end:                                           ; preds = %if.end
  %6 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !293
  %cmp3 = icmp eq %struct.lzma_filter* %6, null, !dbg !295
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !296

if.then4:                                         ; preds = %do.end
  store i32 11, i32* %retval, align 4, !dbg !297
  br label %return, !dbg !297

if.end5:                                          ; preds = %do.end
  %7 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !298
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %7, i32 0, i32 0, !dbg !300
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !300
  %cmp6 = icmp eq %struct.lzma_coder_s* %8, null, !dbg !301
  br i1 %cmp6, label %if.then7, label %if.end18, !dbg !302

if.then7:                                         ; preds = %if.end5
  %9 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !303
  %call = call noalias i8* @lzma_alloc(i64 1472, %struct.lzma_allocator* %9), !dbg !305
  %10 = bitcast i8* %call to %struct.lzma_coder_s*, !dbg !305
  %11 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !306
  %coder8 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %11, i32 0, i32 0, !dbg !307
  store %struct.lzma_coder_s* %10, %struct.lzma_coder_s** %coder8, align 8, !dbg !308
  %12 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !309
  %coder9 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %12, i32 0, i32 0, !dbg !311
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder9, align 8, !dbg !311
  %cmp10 = icmp eq %struct.lzma_coder_s* %13, null, !dbg !312
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !313

if.then11:                                        ; preds = %if.then7
  store i32 5, i32* %retval, align 4, !dbg !314
  br label %return, !dbg !314

if.end12:                                         ; preds = %if.then7
  %14 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !315
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %14, i32 0, i32 3, !dbg !316
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* @stream_encode, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !317
  %15 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !318
  %end = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %15, i32 0, i32 4, !dbg !319
  store void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* @stream_encoder_end, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !320
  %16 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !321
  %update = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %16, i32 0, i32 7, !dbg !322
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* @stream_encoder_update, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)** %update, align 8, !dbg !323
  %17 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !324
  %coder13 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %17, i32 0, i32 0, !dbg !325
  %18 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder13, align 8, !dbg !325
  %filters14 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %18, i32 0, i32 4, !dbg !326
  %arrayidx = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %filters14, i64 0, i64 0, !dbg !324
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx, i32 0, i32 0, !dbg !327
  store i64 -1, i64* %id, align 8, !dbg !328
  %19 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !329
  %coder15 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %19, i32 0, i32 0, !dbg !330
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder15, align 8, !dbg !330
  %block_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %20, i32 0, i32 2, !dbg !331
  %21 = bitcast %struct.lzma_next_coder_s* %block_encoder to i8*, !dbg !332
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %21, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !332
  %22 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !333
  %coder16 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %22, i32 0, i32 0, !dbg !334
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder16, align 8, !dbg !334
  %index_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 5, !dbg !335
  %24 = bitcast %struct.lzma_next_coder_s* %index_encoder to i8*, !dbg !336
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %24, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !336
  %25 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !337
  %coder17 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %25, i32 0, i32 0, !dbg !338
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder17, align 8, !dbg !338
  %index = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %26, i32 0, i32 6, !dbg !339
  store %struct.lzma_index_s* null, %struct.lzma_index_s** %index, align 8, !dbg !340
  br label %if.end18, !dbg !341

if.end18:                                         ; preds = %if.end12, %if.end5
  %27 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !342
  %coder19 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %27, i32 0, i32 0, !dbg !343
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder19, align 8, !dbg !343
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %28, i32 0, i32 0, !dbg !344
  store i32 0, i32* %sequence, align 8, !dbg !345
  %29 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !346
  %coder20 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %29, i32 0, i32 0, !dbg !347
  %30 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder20, align 8, !dbg !347
  %block_options = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %30, i32 0, i32 3, !dbg !348
  %version21 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block_options, i32 0, i32 0, !dbg !349
  store i32 0, i32* %version21, align 8, !dbg !350
  %31 = load i32, i32* %check.addr, align 4, !dbg !351
  %32 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !352
  %coder22 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %32, i32 0, i32 0, !dbg !353
  %33 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder22, align 8, !dbg !353
  %block_options23 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %33, i32 0, i32 3, !dbg !354
  %check24 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block_options23, i32 0, i32 2, !dbg !355
  store i32 %31, i32* %check24, align 8, !dbg !356
  %34 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !357
  %coder25 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %34, i32 0, i32 0, !dbg !358
  %35 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder25, align 8, !dbg !358
  %index26 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %35, i32 0, i32 6, !dbg !359
  %36 = load %struct.lzma_index_s*, %struct.lzma_index_s** %index26, align 8, !dbg !359
  %37 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !360
  call void @lzma_index_end(%struct.lzma_index_s* %36, %struct.lzma_allocator* %37) #7, !dbg !361
  %38 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !362
  %call27 = call %struct.lzma_index_s* @lzma_index_init(%struct.lzma_allocator* %38) #7, !dbg !363
  %39 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !364
  %coder28 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %39, i32 0, i32 0, !dbg !365
  %40 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder28, align 8, !dbg !365
  %index29 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %40, i32 0, i32 6, !dbg !366
  store %struct.lzma_index_s* %call27, %struct.lzma_index_s** %index29, align 8, !dbg !367
  %41 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !368
  %coder30 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %41, i32 0, i32 0, !dbg !370
  %42 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder30, align 8, !dbg !370
  %index31 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %42, i32 0, i32 6, !dbg !371
  %43 = load %struct.lzma_index_s*, %struct.lzma_index_s** %index31, align 8, !dbg !371
  %cmp32 = icmp eq %struct.lzma_index_s* %43, null, !dbg !372
  br i1 %cmp32, label %if.then33, label %if.end34, !dbg !373

if.then33:                                        ; preds = %if.end18
  store i32 5, i32* %retval, align 4, !dbg !374
  br label %return, !dbg !374

if.end34:                                         ; preds = %if.end18
  br label %do.body35, !dbg !375

do.body35:                                        ; preds = %if.end34
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !376, metadata !251), !dbg !379
  %44 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !380
  %coder36 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %44, i32 0, i32 0, !dbg !380
  %45 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder36, align 8, !dbg !380
  %buffer = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %45, i32 0, i32 9, !dbg !380
  %arraydecay = getelementptr inbounds [1024 x i8], [1024 x i8]* %buffer, i32 0, i32 0, !dbg !380
  %call37 = call i32 @lzma_stream_header_encode(%struct.lzma_stream_flags* %stream_flags, i8* %arraydecay) #7, !dbg !380
  store i32 %call37, i32* %ret_, align 4, !dbg !380
  %46 = load i32, i32* %ret_, align 4, !dbg !380
  %cmp38 = icmp ne i32 %46, 0, !dbg !380
  br i1 %cmp38, label %if.then39, label %if.end40, !dbg !380

if.then39:                                        ; preds = %do.body35
  %47 = load i32, i32* %ret_, align 4, !dbg !382
  store i32 %47, i32* %retval, align 4, !dbg !382
  br label %return, !dbg !382

if.end40:                                         ; preds = %do.body35
  br label %do.end41, !dbg !385

do.end41:                                         ; preds = %if.end40
  %48 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !387
  %coder42 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %48, i32 0, i32 0, !dbg !388
  %49 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder42, align 8, !dbg !388
  %buffer_pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %49, i32 0, i32 7, !dbg !389
  store i64 0, i64* %buffer_pos, align 8, !dbg !390
  %50 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !391
  %coder43 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %50, i32 0, i32 0, !dbg !392
  %51 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder43, align 8, !dbg !392
  %buffer_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %51, i32 0, i32 8, !dbg !393
  store i64 12, i64* %buffer_size, align 8, !dbg !394
  %52 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !395
  %coder44 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %52, i32 0, i32 0, !dbg !396
  %53 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder44, align 8, !dbg !396
  %54 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !397
  %55 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !398
  %call45 = call i32 @stream_encoder_update(%struct.lzma_coder_s* %53, %struct.lzma_allocator* %54, %struct.lzma_filter* %55, %struct.lzma_filter* null), !dbg !399
  store i32 %call45, i32* %retval, align 4, !dbg !400
  br label %return, !dbg !400

return:                                           ; preds = %do.end41, %if.then39, %if.then33, %if.then11, %if.then4
  %56 = load i32, i32* %retval, align 4, !dbg !401
  ret i32 %56, !dbg !401
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @lzma_next_end(%struct.lzma_next_coder_s*, %struct.lzma_allocator*) #2

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #2

; Function Attrs: nounwind uwtable
define internal i32 @stream_encode(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, i8* noalias %in, i64* noalias %in_pos, i64 %in_size, i8* noalias %out, i64* noalias %out_pos, i64 %out_size, i32 %action) #0 !dbg !235 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %in.addr = alloca i8*, align 8
  %in_pos.addr = alloca i64*, align 8
  %in_size.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %action.addr = alloca i32, align 4
  %ret_ = alloca i32, align 4
  %ret_25 = alloca i32, align 4
  %unpadded_size = alloca i64, align 8
  %ret = alloca i32, align 4
  %ret_57 = alloca i32, align 4
  %stream_flags = alloca %struct.lzma_stream_flags, align 8
  %ret72 = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !402, metadata !251), !dbg !403
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !404, metadata !251), !dbg !405
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !406, metadata !251), !dbg !407
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !408, metadata !251), !dbg !409
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !410, metadata !251), !dbg !411
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !412, metadata !251), !dbg !413
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !414, metadata !251), !dbg !415
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !416, metadata !251), !dbg !417
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !418, metadata !251), !dbg !419
  br label %while.cond, !dbg !420

while.cond:                                       ; preds = %sw.epilog, %entry
  %0 = load i64*, i64** %out_pos.addr, align 8, !dbg !421
  %1 = load i64, i64* %0, align 8, !dbg !423
  %2 = load i64, i64* %out_size.addr, align 8, !dbg !424
  %cmp = icmp ult i64 %1, %2, !dbg !425
  br i1 %cmp, label %while.body, label %while.end, !dbg !426

while.body:                                       ; preds = %while.cond
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !427
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %3, i32 0, i32 0, !dbg !428
  %4 = load i32, i32* %sequence, align 8, !dbg !428
  switch i32 %4, label %sw.default [
    i32 0, label %sw.bb
    i32 2, label %sw.bb
    i32 5, label %sw.bb
    i32 1, label %sw.bb10
    i32 3, label %sw.bb42
    i32 4, label %sw.bb67
  ], !dbg !429

sw.bb:                                            ; preds = %while.body, %while.body, %while.body
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !430
  %buffer = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 9, !dbg !432
  %arraydecay = getelementptr inbounds [1024 x i8], [1024 x i8]* %buffer, i32 0, i32 0, !dbg !430
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !433
  %buffer_pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %6, i32 0, i32 7, !dbg !434
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !435
  %buffer_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 8, !dbg !436
  %8 = load i64, i64* %buffer_size, align 8, !dbg !436
  %9 = load i8*, i8** %out.addr, align 8, !dbg !437
  %10 = load i64*, i64** %out_pos.addr, align 8, !dbg !438
  %11 = load i64, i64* %out_size.addr, align 8, !dbg !439
  %call = call i64 @lzma_bufcpy(i8* %arraydecay, i64* %buffer_pos, i64 %8, i8* %9, i64* %10, i64 %11), !dbg !440
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !441
  %buffer_pos1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 7, !dbg !443
  %13 = load i64, i64* %buffer_pos1, align 8, !dbg !443
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !444
  %buffer_size2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 8, !dbg !445
  %15 = load i64, i64* %buffer_size2, align 8, !dbg !445
  %cmp3 = icmp ult i64 %13, %15, !dbg !446
  br i1 %cmp3, label %if.then, label %if.end, !dbg !447

if.then:                                          ; preds = %sw.bb
  store i32 0, i32* %retval, align 4, !dbg !448
  br label %return, !dbg !448

if.end:                                           ; preds = %sw.bb
  %16 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !449
  %sequence4 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %16, i32 0, i32 0, !dbg !451
  %17 = load i32, i32* %sequence4, align 8, !dbg !451
  %cmp5 = icmp eq i32 %17, 5, !dbg !452
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !453

if.then6:                                         ; preds = %if.end
  store i32 1, i32* %retval, align 4, !dbg !454
  br label %return, !dbg !454

if.end7:                                          ; preds = %if.end
  %18 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !455
  %buffer_pos8 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %18, i32 0, i32 7, !dbg !456
  store i64 0, i64* %buffer_pos8, align 8, !dbg !457
  %19 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !458
  %sequence9 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %19, i32 0, i32 0, !dbg !459
  %20 = load i32, i32* %sequence9, align 8, !dbg !460
  %inc = add i32 %20, 1, !dbg !460
  store i32 %inc, i32* %sequence9, align 8, !dbg !460
  br label %sw.epilog, !dbg !461

sw.bb10:                                          ; preds = %while.body
  %21 = load i64*, i64** %in_pos.addr, align 8, !dbg !462
  %22 = load i64, i64* %21, align 8, !dbg !465
  %23 = load i64, i64* %in_size.addr, align 8, !dbg !466
  %cmp11 = icmp eq i64 %22, %23, !dbg !467
  br i1 %cmp11, label %if.then12, label %if.end22, !dbg !468

if.then12:                                        ; preds = %sw.bb10
  %24 = load i32, i32* %action.addr, align 4, !dbg !469
  %cmp13 = icmp ne i32 %24, 3, !dbg !472
  br i1 %cmp13, label %if.then14, label %if.end16, !dbg !473

if.then14:                                        ; preds = %if.then12
  %25 = load i32, i32* %action.addr, align 4, !dbg !474
  %cmp15 = icmp eq i32 %25, 0, !dbg !475
  %cond = select i1 %cmp15, i32 0, i32 1, !dbg !474
  store i32 %cond, i32* %retval, align 4, !dbg !476
  br label %return, !dbg !476

if.end16:                                         ; preds = %if.then12
  br label %do.body, !dbg !477

do.body:                                          ; preds = %if.end16
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !478, metadata !251), !dbg !480
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !481
  %index_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %26, i32 0, i32 5, !dbg !481
  %27 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !481
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !481
  %index = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %28, i32 0, i32 6, !dbg !481
  %29 = load %struct.lzma_index_s*, %struct.lzma_index_s** %index, align 8, !dbg !481
  %call17 = call i32 @lzma_index_encoder_init(%struct.lzma_next_coder_s* %index_encoder, %struct.lzma_allocator* %27, %struct.lzma_index_s* %29), !dbg !481
  store i32 %call17, i32* %ret_, align 4, !dbg !481
  %30 = load i32, i32* %ret_, align 4, !dbg !481
  %cmp18 = icmp ne i32 %30, 0, !dbg !481
  br i1 %cmp18, label %if.then19, label %if.end20, !dbg !481

if.then19:                                        ; preds = %do.body
  %31 = load i32, i32* %ret_, align 4, !dbg !483
  store i32 %31, i32* %retval, align 4, !dbg !483
  br label %return, !dbg !483

if.end20:                                         ; preds = %do.body
  br label %do.end, !dbg !486

do.end:                                           ; preds = %if.end20
  %32 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !488
  %sequence21 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %32, i32 0, i32 0, !dbg !489
  store i32 4, i32* %sequence21, align 8, !dbg !490
  br label %sw.epilog, !dbg !491

if.end22:                                         ; preds = %sw.bb10
  %33 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !492
  %block_encoder_is_initialized = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %33, i32 0, i32 1, !dbg !494
  %34 = load i8, i8* %block_encoder_is_initialized, align 4, !dbg !494
  %tobool = trunc i8 %34 to i1, !dbg !494
  br i1 %tobool, label %if.end31, label %if.then23, !dbg !495

if.then23:                                        ; preds = %if.end22
  br label %do.body24, !dbg !496

do.body24:                                        ; preds = %if.then23
  call void @llvm.dbg.declare(metadata i32* %ret_25, metadata !497, metadata !251), !dbg !499
  %35 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !500
  %36 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !500
  %call26 = call i32 @block_encoder_init(%struct.lzma_coder_s* %35, %struct.lzma_allocator* %36), !dbg !500
  store i32 %call26, i32* %ret_25, align 4, !dbg !500
  %37 = load i32, i32* %ret_25, align 4, !dbg !500
  %cmp27 = icmp ne i32 %37, 0, !dbg !500
  br i1 %cmp27, label %if.then28, label %if.end29, !dbg !500

if.then28:                                        ; preds = %do.body24
  %38 = load i32, i32* %ret_25, align 4, !dbg !502
  store i32 %38, i32* %retval, align 4, !dbg !502
  br label %return, !dbg !502

if.end29:                                         ; preds = %do.body24
  br label %do.end30, !dbg !505

do.end30:                                         ; preds = %if.end29
  br label %if.end31, !dbg !507

if.end31:                                         ; preds = %do.end30, %if.end22
  %39 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !509
  %block_encoder_is_initialized32 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %39, i32 0, i32 1, !dbg !510
  store i8 0, i8* %block_encoder_is_initialized32, align 4, !dbg !511
  %40 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !512
  %block_options = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %40, i32 0, i32 3, !dbg !514
  %41 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !515
  %buffer33 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %41, i32 0, i32 9, !dbg !516
  %arraydecay34 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buffer33, i32 0, i32 0, !dbg !515
  %call35 = call i32 @lzma_block_header_encode(%struct.lzma_block* %block_options, i8* %arraydecay34) #7, !dbg !517
  %cmp36 = icmp ne i32 %call35, 0, !dbg !518
  br i1 %cmp36, label %if.then37, label %if.end38, !dbg !519

if.then37:                                        ; preds = %if.end31
  store i32 11, i32* %retval, align 4, !dbg !520
  br label %return, !dbg !520

if.end38:                                         ; preds = %if.end31
  %42 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !521
  %block_options39 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %42, i32 0, i32 3, !dbg !522
  %header_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block_options39, i32 0, i32 1, !dbg !523
  %43 = load i32, i32* %header_size, align 4, !dbg !523
  %conv = zext i32 %43 to i64, !dbg !521
  %44 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !524
  %buffer_size40 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %44, i32 0, i32 8, !dbg !525
  store i64 %conv, i64* %buffer_size40, align 8, !dbg !526
  %45 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !527
  %sequence41 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %45, i32 0, i32 0, !dbg !528
  store i32 2, i32* %sequence41, align 8, !dbg !529
  br label %sw.epilog, !dbg !530

sw.bb42:                                          ; preds = %while.body
  call void @llvm.dbg.declare(metadata i64* %unpadded_size, metadata !531, metadata !251), !dbg !533
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !534, metadata !251), !dbg !535
  %46 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !536
  %block_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %46, i32 0, i32 2, !dbg !537
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %block_encoder, i32 0, i32 3, !dbg !538
  %47 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !538
  %48 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !539
  %block_encoder43 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %48, i32 0, i32 2, !dbg !540
  %coder44 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %block_encoder43, i32 0, i32 0, !dbg !541
  %49 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder44, align 8, !dbg !541
  %50 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !542
  %51 = load i8*, i8** %in.addr, align 8, !dbg !543
  %52 = load i64*, i64** %in_pos.addr, align 8, !dbg !544
  %53 = load i64, i64* %in_size.addr, align 8, !dbg !545
  %54 = load i8*, i8** %out.addr, align 8, !dbg !546
  %55 = load i64*, i64** %out_pos.addr, align 8, !dbg !547
  %56 = load i64, i64* %out_size.addr, align 8, !dbg !548
  %57 = load i32, i32* %action.addr, align 4, !dbg !549
  %idxprom = zext i32 %57 to i64, !dbg !550
  %arrayidx = getelementptr inbounds [4 x i32], [4 x i32]* @stream_encode.convert, i64 0, i64 %idxprom, !dbg !550
  %58 = load i32, i32* %arrayidx, align 4, !dbg !550
  %call45 = call i32 %47(%struct.lzma_coder_s* %49, %struct.lzma_allocator* %50, i8* %51, i64* %52, i64 %53, i8* %54, i64* %55, i64 %56, i32 %58), !dbg !536
  store i32 %call45, i32* %ret, align 4, !dbg !535
  %59 = load i32, i32* %ret, align 4, !dbg !551
  %cmp46 = icmp ne i32 %59, 1, !dbg !553
  br i1 %cmp46, label %if.then50, label %lor.lhs.false, !dbg !554

lor.lhs.false:                                    ; preds = %sw.bb42
  %60 = load i32, i32* %action.addr, align 4, !dbg !555
  %cmp48 = icmp eq i32 %60, 1, !dbg !557
  br i1 %cmp48, label %if.then50, label %if.end51, !dbg !558

if.then50:                                        ; preds = %lor.lhs.false, %sw.bb42
  %61 = load i32, i32* %ret, align 4, !dbg !559
  store i32 %61, i32* %retval, align 4, !dbg !560
  br label %return, !dbg !560

if.end51:                                         ; preds = %lor.lhs.false
  %62 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !561
  %block_options52 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %62, i32 0, i32 3, !dbg !562
  %call53 = call i64 @lzma_block_unpadded_size(%struct.lzma_block* %block_options52) #8, !dbg !563
  store i64 %call53, i64* %unpadded_size, align 8, !dbg !564
  %63 = load i64, i64* %unpadded_size, align 8, !dbg !565
  %cmp54 = icmp ne i64 %63, 0, !dbg !565
  br i1 %cmp54, label %cond.true, label %cond.false, !dbg !565

cond.true:                                        ; preds = %if.end51
  br label %cond.end, !dbg !566

cond.false:                                       ; preds = %if.end51
  call void @__assert_fail(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([86 x i8], [86 x i8]* @.str.1, i32 0, i32 0), i32 169, i8* getelementptr inbounds ([164 x i8], [164 x i8]* @__PRETTY_FUNCTION__.stream_encode, i32 0, i32 0)) #9, !dbg !568
  unreachable, !dbg !568
                                                  ; No predecessors!
  br label %cond.end, !dbg !570

cond.end:                                         ; preds = %64, %cond.true
  br label %do.body56, !dbg !572

do.body56:                                        ; preds = %cond.end
  call void @llvm.dbg.declare(metadata i32* %ret_57, metadata !573, metadata !251), !dbg !575
  %65 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !576
  %index58 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %65, i32 0, i32 6, !dbg !576
  %66 = load %struct.lzma_index_s*, %struct.lzma_index_s** %index58, align 8, !dbg !576
  %67 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !576
  %68 = load i64, i64* %unpadded_size, align 8, !dbg !576
  %69 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !576
  %block_options59 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %69, i32 0, i32 3, !dbg !576
  %uncompressed_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block_options59, i32 0, i32 4, !dbg !576
  %70 = load i64, i64* %uncompressed_size, align 8, !dbg !576
  %call60 = call i32 @lzma_index_append(%struct.lzma_index_s* %66, %struct.lzma_allocator* %67, i64 %68, i64 %70) #7, !dbg !576
  store i32 %call60, i32* %ret_57, align 4, !dbg !576
  %71 = load i32, i32* %ret_57, align 4, !dbg !576
  %cmp61 = icmp ne i32 %71, 0, !dbg !576
  br i1 %cmp61, label %if.then63, label %if.end64, !dbg !576

if.then63:                                        ; preds = %do.body56
  %72 = load i32, i32* %ret_57, align 4, !dbg !578
  store i32 %72, i32* %retval, align 4, !dbg !578
  br label %return, !dbg !578

if.end64:                                         ; preds = %do.body56
  br label %do.end65, !dbg !581

do.end65:                                         ; preds = %if.end64
  %73 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !583
  %sequence66 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %73, i32 0, i32 0, !dbg !584
  store i32 1, i32* %sequence66, align 8, !dbg !585
  br label %sw.epilog, !dbg !586

sw.bb67:                                          ; preds = %while.body
  call void @llvm.dbg.declare(metadata %struct.lzma_stream_flags* %stream_flags, metadata !587, metadata !251), !dbg !590
  %version = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 0, !dbg !591
  store i32 0, i32* %version, align 8, !dbg !591
  %backward_size = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 1, !dbg !591
  %74 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !592
  %index68 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %74, i32 0, i32 6, !dbg !593
  %75 = load %struct.lzma_index_s*, %struct.lzma_index_s** %index68, align 8, !dbg !593
  %call69 = call i64 @lzma_index_size(%struct.lzma_index_s* %75) #8, !dbg !594
  store i64 %call69, i64* %backward_size, align 8, !dbg !591
  %check = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 2, !dbg !591
  %76 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !595
  %block_options70 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %76, i32 0, i32 3, !dbg !596
  %check71 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block_options70, i32 0, i32 2, !dbg !597
  %77 = load i32, i32* %check71, align 8, !dbg !597
  store i32 %77, i32* %check, align 8, !dbg !591
  %reserved_enum1 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 3, !dbg !591
  store i32 0, i32* %reserved_enum1, align 4, !dbg !591
  %reserved_enum2 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 4, !dbg !591
  store i32 0, i32* %reserved_enum2, align 8, !dbg !591
  %reserved_enum3 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 5, !dbg !591
  store i32 0, i32* %reserved_enum3, align 4, !dbg !591
  %reserved_enum4 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 6, !dbg !591
  store i32 0, i32* %reserved_enum4, align 8, !dbg !591
  %reserved_bool1 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 7, !dbg !591
  store i8 0, i8* %reserved_bool1, align 4, !dbg !591
  %reserved_bool2 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 8, !dbg !591
  store i8 0, i8* %reserved_bool2, align 1, !dbg !591
  %reserved_bool3 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 9, !dbg !591
  store i8 0, i8* %reserved_bool3, align 2, !dbg !591
  %reserved_bool4 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 10, !dbg !591
  store i8 0, i8* %reserved_bool4, align 1, !dbg !591
  %reserved_bool5 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 11, !dbg !591
  store i8 0, i8* %reserved_bool5, align 8, !dbg !591
  %reserved_bool6 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 12, !dbg !591
  store i8 0, i8* %reserved_bool6, align 1, !dbg !591
  %reserved_bool7 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 13, !dbg !591
  store i8 0, i8* %reserved_bool7, align 2, !dbg !591
  %reserved_bool8 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 14, !dbg !591
  store i8 0, i8* %reserved_bool8, align 1, !dbg !591
  %reserved_int1 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 15, !dbg !591
  store i32 0, i32* %reserved_int1, align 4, !dbg !591
  %reserved_int2 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 16, !dbg !591
  store i32 0, i32* %reserved_int2, align 8, !dbg !591
  call void @llvm.dbg.declare(metadata i32* %ret72, metadata !598, metadata !251), !dbg !599
  %78 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !600
  %index_encoder73 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %78, i32 0, i32 5, !dbg !601
  %code74 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %index_encoder73, i32 0, i32 3, !dbg !602
  %79 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code74, align 8, !dbg !602
  %80 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !603
  %index_encoder75 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %80, i32 0, i32 5, !dbg !604
  %coder76 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %index_encoder75, i32 0, i32 0, !dbg !605
  %81 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder76, align 8, !dbg !605
  %82 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !606
  %83 = load i8*, i8** %out.addr, align 8, !dbg !607
  %84 = load i64*, i64** %out_pos.addr, align 8, !dbg !608
  %85 = load i64, i64* %out_size.addr, align 8, !dbg !609
  %call77 = call i32 %79(%struct.lzma_coder_s* %81, %struct.lzma_allocator* %82, i8* null, i64* null, i64 0, i8* %83, i64* %84, i64 %85, i32 0), !dbg !600
  store i32 %call77, i32* %ret72, align 4, !dbg !599
  %86 = load i32, i32* %ret72, align 4, !dbg !610
  %cmp78 = icmp ne i32 %86, 1, !dbg !612
  br i1 %cmp78, label %if.then80, label %if.end81, !dbg !613

if.then80:                                        ; preds = %sw.bb67
  %87 = load i32, i32* %ret72, align 4, !dbg !614
  store i32 %87, i32* %retval, align 4, !dbg !615
  br label %return, !dbg !615

if.end81:                                         ; preds = %sw.bb67
  %88 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !616
  %buffer82 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %88, i32 0, i32 9, !dbg !618
  %arraydecay83 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buffer82, i32 0, i32 0, !dbg !616
  %call84 = call i32 @lzma_stream_footer_encode(%struct.lzma_stream_flags* %stream_flags, i8* %arraydecay83) #7, !dbg !619
  %cmp85 = icmp ne i32 %call84, 0, !dbg !620
  br i1 %cmp85, label %if.then87, label %if.end88, !dbg !621

if.then87:                                        ; preds = %if.end81
  store i32 11, i32* %retval, align 4, !dbg !622
  br label %return, !dbg !622

if.end88:                                         ; preds = %if.end81
  %89 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !623
  %buffer_size89 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %89, i32 0, i32 8, !dbg !624
  store i64 12, i64* %buffer_size89, align 8, !dbg !625
  %90 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !626
  %sequence90 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %90, i32 0, i32 0, !dbg !627
  store i32 5, i32* %sequence90, align 8, !dbg !628
  br label %sw.epilog, !dbg !629

sw.default:                                       ; preds = %while.body
  call void @__assert_fail(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([86 x i8], [86 x i8]* @.str.1, i32 0, i32 0), i32 206, i8* getelementptr inbounds ([164 x i8], [164 x i8]* @__PRETTY_FUNCTION__.stream_encode, i32 0, i32 0)) #9, !dbg !630
  unreachable, !dbg !630

sw.epilog:                                        ; preds = %if.end88, %do.end65, %if.end38, %do.end, %if.end7
  br label %while.cond, !dbg !631

while.end:                                        ; preds = %while.cond
  store i32 0, i32* %retval, align 4, !dbg !633
  br label %return, !dbg !633

return:                                           ; preds = %while.end, %if.then87, %if.then80, %if.then63, %if.then50, %if.then37, %if.then28, %if.then19, %if.then14, %if.then6, %if.then
  %91 = load i32, i32* %retval, align 4, !dbg !634
  ret i32 %91, !dbg !634
}

; Function Attrs: nounwind uwtable
define internal void @stream_encoder_end(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator) #0 !dbg !239 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %i = alloca i64, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !635, metadata !251), !dbg !636
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !637, metadata !251), !dbg !638
  call void @llvm.dbg.declare(metadata i64* %i, metadata !639, metadata !251), !dbg !640
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !641
  %block_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 2, !dbg !642
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !643
  call void @lzma_next_end(%struct.lzma_next_coder_s* %block_encoder, %struct.lzma_allocator* %1), !dbg !644
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !645
  %index_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 5, !dbg !646
  %3 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !647
  call void @lzma_next_end(%struct.lzma_next_coder_s* %index_encoder, %struct.lzma_allocator* %3), !dbg !648
  %4 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !649
  %index = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %4, i32 0, i32 6, !dbg !650
  %5 = load %struct.lzma_index_s*, %struct.lzma_index_s** %index, align 8, !dbg !650
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !651
  call void @lzma_index_end(%struct.lzma_index_s* %5, %struct.lzma_allocator* %6) #7, !dbg !652
  store i64 0, i64* %i, align 8, !dbg !653
  br label %for.cond, !dbg !655

for.cond:                                         ; preds = %for.inc, %entry
  %7 = load i64, i64* %i, align 8, !dbg !656
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !659
  %filters = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %8, i32 0, i32 4, !dbg !660
  %arrayidx = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %filters, i64 0, i64 %7, !dbg !659
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx, i32 0, i32 0, !dbg !661
  %9 = load i64, i64* %id, align 8, !dbg !661
  %cmp = icmp ne i64 %9, -1, !dbg !662
  br i1 %cmp, label %for.body, label %for.end, !dbg !663

for.body:                                         ; preds = %for.cond
  %10 = load i64, i64* %i, align 8, !dbg !664
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !665
  %filters1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 4, !dbg !666
  %arrayidx2 = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %filters1, i64 0, i64 %10, !dbg !665
  %options = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx2, i32 0, i32 1, !dbg !667
  %12 = load i8*, i8** %options, align 8, !dbg !667
  %13 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !668
  call void @lzma_free(i8* %12, %struct.lzma_allocator* %13), !dbg !669
  br label %for.inc, !dbg !669

for.inc:                                          ; preds = %for.body
  %14 = load i64, i64* %i, align 8, !dbg !670
  %inc = add i64 %14, 1, !dbg !670
  store i64 %inc, i64* %i, align 8, !dbg !670
  br label %for.cond, !dbg !672

for.end:                                          ; preds = %for.cond
  %15 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !673
  %16 = bitcast %struct.lzma_coder_s* %15 to i8*, !dbg !673
  %17 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !674
  call void @lzma_free(i8* %16, %struct.lzma_allocator* %17), !dbg !675
  ret void, !dbg !676
}

; Function Attrs: nounwind uwtable
define internal i32 @stream_encoder_update(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, %struct.lzma_filter* %filters, %struct.lzma_filter* %reversed_filters) #0 !dbg !240 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter*, align 8
  %reversed_filters.addr = alloca %struct.lzma_filter*, align 8
  %i = alloca i64, align 8
  %ret = alloca i32, align 4
  %ret_ = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !677, metadata !251), !dbg !678
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !679, metadata !251), !dbg !680
  store %struct.lzma_filter* %filters, %struct.lzma_filter** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filters.addr, metadata !681, metadata !251), !dbg !682
  store %struct.lzma_filter* %reversed_filters, %struct.lzma_filter** %reversed_filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %reversed_filters.addr, metadata !683, metadata !251), !dbg !684
  call void @llvm.dbg.declare(metadata i64* %i, metadata !685, metadata !251), !dbg !686
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !687
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 0, !dbg !689
  %1 = load i32, i32* %sequence, align 8, !dbg !689
  %cmp = icmp ule i32 %1, 1, !dbg !690
  br i1 %cmp, label %if.then, label %if.else, !dbg !691

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !692, metadata !251), !dbg !694
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !695
  %block_encoder_is_initialized = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 1, !dbg !696
  store i8 0, i8* %block_encoder_is_initialized, align 4, !dbg !697
  %3 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !698
  %4 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !699
  %block_options = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %4, i32 0, i32 3, !dbg !700
  %filters1 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block_options, i32 0, i32 5, !dbg !701
  store %struct.lzma_filter* %3, %struct.lzma_filter** %filters1, align 8, !dbg !702
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !703
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !704
  %call = call i32 @block_encoder_init(%struct.lzma_coder_s* %5, %struct.lzma_allocator* %6), !dbg !705
  store i32 %call, i32* %ret, align 4, !dbg !706
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !707
  %filters2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 4, !dbg !708
  %arraydecay = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %filters2, i32 0, i32 0, !dbg !707
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !709
  %block_options3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %8, i32 0, i32 3, !dbg !710
  %filters4 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block_options3, i32 0, i32 5, !dbg !711
  store %struct.lzma_filter* %arraydecay, %struct.lzma_filter** %filters4, align 8, !dbg !712
  %9 = load i32, i32* %ret, align 4, !dbg !713
  %cmp5 = icmp ne i32 %9, 0, !dbg !715
  br i1 %cmp5, label %if.then6, label %if.end, !dbg !716

if.then6:                                         ; preds = %if.then
  %10 = load i32, i32* %ret, align 4, !dbg !717
  store i32 %10, i32* %retval, align 4, !dbg !718
  br label %return, !dbg !718

if.end:                                           ; preds = %if.then
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !719
  %block_encoder_is_initialized7 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 1, !dbg !720
  store i8 1, i8* %block_encoder_is_initialized7, align 4, !dbg !721
  br label %if.end19, !dbg !722

if.else:                                          ; preds = %entry
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !723
  %sequence8 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 0, !dbg !726
  %13 = load i32, i32* %sequence8, align 8, !dbg !726
  %cmp9 = icmp ule i32 %13, 3, !dbg !727
  br i1 %cmp9, label %if.then10, label %if.else17, !dbg !723

if.then10:                                        ; preds = %if.else
  br label %do.body, !dbg !728

do.body:                                          ; preds = %if.then10
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !730, metadata !251), !dbg !732
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !733
  %block_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 2, !dbg !733
  %update = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %block_encoder, i32 0, i32 7, !dbg !733
  %15 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)** %update, align 8, !dbg !733
  %16 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !733
  %block_encoder11 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %16, i32 0, i32 2, !dbg !733
  %coder12 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %block_encoder11, i32 0, i32 0, !dbg !733
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder12, align 8, !dbg !733
  %18 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !733
  %19 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !733
  %20 = load %struct.lzma_filter*, %struct.lzma_filter** %reversed_filters.addr, align 8, !dbg !733
  %call13 = call i32 %15(%struct.lzma_coder_s* %17, %struct.lzma_allocator* %18, %struct.lzma_filter* %19, %struct.lzma_filter* %20), !dbg !733
  store i32 %call13, i32* %ret_, align 4, !dbg !733
  %21 = load i32, i32* %ret_, align 4, !dbg !733
  %cmp14 = icmp ne i32 %21, 0, !dbg !733
  br i1 %cmp14, label %if.then15, label %if.end16, !dbg !733

if.then15:                                        ; preds = %do.body
  %22 = load i32, i32* %ret_, align 4, !dbg !735
  store i32 %22, i32* %retval, align 4, !dbg !735
  br label %return, !dbg !735

if.end16:                                         ; preds = %do.body
  br label %do.end, !dbg !738

do.end:                                           ; preds = %if.end16
  br label %if.end18, !dbg !740

if.else17:                                        ; preds = %if.else
  store i32 11, i32* %retval, align 4, !dbg !741
  br label %return, !dbg !741

if.end18:                                         ; preds = %do.end
  br label %if.end19

if.end19:                                         ; preds = %if.end18, %if.end
  store i64 0, i64* %i, align 8, !dbg !743
  br label %for.cond, !dbg !745

for.cond:                                         ; preds = %for.inc, %if.end19
  %23 = load i64, i64* %i, align 8, !dbg !746
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !749
  %filters20 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %24, i32 0, i32 4, !dbg !750
  %arrayidx = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %filters20, i64 0, i64 %23, !dbg !749
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx, i32 0, i32 0, !dbg !751
  %25 = load i64, i64* %id, align 8, !dbg !751
  %cmp21 = icmp ne i64 %25, -1, !dbg !752
  br i1 %cmp21, label %for.body, label %for.end, !dbg !753

for.body:                                         ; preds = %for.cond
  %26 = load i64, i64* %i, align 8, !dbg !754
  %27 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !755
  %filters22 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %27, i32 0, i32 4, !dbg !756
  %arrayidx23 = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %filters22, i64 0, i64 %26, !dbg !755
  %options = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx23, i32 0, i32 1, !dbg !757
  %28 = load i8*, i8** %options, align 8, !dbg !757
  %29 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !758
  call void @lzma_free(i8* %28, %struct.lzma_allocator* %29), !dbg !759
  br label %for.inc, !dbg !759

for.inc:                                          ; preds = %for.body
  %30 = load i64, i64* %i, align 8, !dbg !760
  %inc = add i64 %30, 1, !dbg !760
  store i64 %inc, i64* %i, align 8, !dbg !760
  br label %for.cond, !dbg !762

for.end:                                          ; preds = %for.cond
  %31 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !763
  %32 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !764
  %filters24 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %32, i32 0, i32 4, !dbg !765
  %arraydecay25 = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %filters24, i32 0, i32 0, !dbg !764
  %33 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !766
  %call26 = call i32 @lzma_filters_copy(%struct.lzma_filter* %31, %struct.lzma_filter* %arraydecay25, %struct.lzma_allocator* %33) #7, !dbg !767
  store i32 %call26, i32* %retval, align 4, !dbg !768
  br label %return, !dbg !768

return:                                           ; preds = %for.end, %if.else17, %if.then15, %if.then6
  %34 = load i32, i32* %retval, align 4, !dbg !769
  ret i32 %34, !dbg !769
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

; Function Attrs: nounwind
declare void @lzma_index_end(%struct.lzma_index_s*, %struct.lzma_allocator*) #4

; Function Attrs: nounwind
declare %struct.lzma_index_s* @lzma_index_init(%struct.lzma_allocator*) #4

; Function Attrs: nounwind
declare i32 @lzma_stream_header_encode(%struct.lzma_stream_flags*, i8*) #4

; Function Attrs: nounwind uwtable
define i32 @lzma_stream_encoder(%struct.lzma_stream* %strm, %struct.lzma_filter* %filters, i32 %check) #0 !dbg !208 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzma_stream*, align 8
  %filters.addr = alloca %struct.lzma_filter*, align 8
  %check.addr = alloca i32, align 4
  %ret_ = alloca i32, align 4
  %ret_2 = alloca i32, align 4
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !770, metadata !251), !dbg !771
  store %struct.lzma_filter* %filters, %struct.lzma_filter** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filters.addr, metadata !772, metadata !251), !dbg !773
  store i32 %check, i32* %check.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %check.addr, metadata !774, metadata !251), !dbg !775
  br label %do.body, !dbg !776

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !777, metadata !251), !dbg !779
  br label %do.body1, !dbg !780

do.body1:                                         ; preds = %do.body
  call void @llvm.dbg.declare(metadata i32* %ret_2, metadata !782, metadata !251), !dbg !784
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !785
  %call = call i32 @lzma_strm_init(%struct.lzma_stream* %0), !dbg !785
  store i32 %call, i32* %ret_2, align 4, !dbg !785
  %1 = load i32, i32* %ret_2, align 4, !dbg !785
  %cmp = icmp ne i32 %1, 0, !dbg !785
  br i1 %cmp, label %if.then, label %if.end, !dbg !785

if.then:                                          ; preds = %do.body1
  %2 = load i32, i32* %ret_2, align 4, !dbg !787
  store i32 %2, i32* %retval, align 4, !dbg !787
  br label %return, !dbg !787

if.end:                                           ; preds = %do.body1
  br label %do.end, !dbg !790

do.end:                                           ; preds = %if.end
  %3 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !792
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %3, i32 0, i32 7, !dbg !792
  %4 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !792
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %4, i32 0, i32 0, !dbg !792
  %5 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !792
  %allocator = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %5, i32 0, i32 6, !dbg !792
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator, align 8, !dbg !792
  %7 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !792
  %8 = load i32, i32* %check.addr, align 4, !dbg !792
  %call3 = call i32 @lzma_stream_encoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %6, %struct.lzma_filter* %7, i32 %8), !dbg !792
  store i32 %call3, i32* %ret_, align 4, !dbg !792
  %9 = load i32, i32* %ret_, align 4, !dbg !792
  %cmp4 = icmp ne i32 %9, 0, !dbg !792
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !792

if.then5:                                         ; preds = %do.end
  %10 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !794
  call void @lzma_end(%struct.lzma_stream* %10) #7, !dbg !794
  %11 = load i32, i32* %ret_, align 4, !dbg !794
  store i32 %11, i32* %retval, align 4, !dbg !794
  br label %return, !dbg !794

if.end6:                                          ; preds = %do.end
  br label %do.end7, !dbg !798

do.end7:                                          ; preds = %if.end6
  %12 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !800
  %internal8 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %12, i32 0, i32 7, !dbg !801
  %13 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal8, align 8, !dbg !801
  %supported_actions = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %13, i32 0, i32 3, !dbg !802
  %arrayidx = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions, i64 0, i64 0, !dbg !800
  store i8 1, i8* %arrayidx, align 8, !dbg !803
  %14 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !804
  %internal9 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %14, i32 0, i32 7, !dbg !805
  %15 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal9, align 8, !dbg !805
  %supported_actions10 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %15, i32 0, i32 3, !dbg !806
  %arrayidx11 = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions10, i64 0, i64 1, !dbg !804
  store i8 1, i8* %arrayidx11, align 1, !dbg !807
  %16 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !808
  %internal12 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %16, i32 0, i32 7, !dbg !809
  %17 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal12, align 8, !dbg !809
  %supported_actions13 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %17, i32 0, i32 3, !dbg !810
  %arrayidx14 = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions13, i64 0, i64 2, !dbg !808
  store i8 1, i8* %arrayidx14, align 2, !dbg !811
  %18 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !812
  %internal15 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %18, i32 0, i32 7, !dbg !813
  %19 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal15, align 8, !dbg !813
  %supported_actions16 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %19, i32 0, i32 3, !dbg !814
  %arrayidx17 = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions16, i64 0, i64 3, !dbg !812
  store i8 1, i8* %arrayidx17, align 1, !dbg !815
  store i32 0, i32* %retval, align 4, !dbg !816
  br label %return, !dbg !816

return:                                           ; preds = %do.end7, %if.then5, %if.then
  %20 = load i32, i32* %retval, align 4, !dbg !817
  ret i32 %20, !dbg !817
}

declare i32 @lzma_strm_init(%struct.lzma_stream*) #2

; Function Attrs: nounwind
declare void @lzma_end(%struct.lzma_stream*) #4

declare i64 @lzma_bufcpy(i8*, i64*, i64, i8*, i64*, i64) #2

declare i32 @lzma_index_encoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_index_s*) #2

; Function Attrs: nounwind uwtable
define internal i32 @block_encoder_init(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator) #0 !dbg !236 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %ret_ = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !818, metadata !251), !dbg !819
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !820, metadata !251), !dbg !821
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !822
  %block_options = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 3, !dbg !823
  %compressed_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block_options, i32 0, i32 3, !dbg !824
  store i64 -1, i64* %compressed_size, align 8, !dbg !825
  %1 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !826
  %block_options1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %1, i32 0, i32 3, !dbg !827
  %uncompressed_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block_options1, i32 0, i32 4, !dbg !828
  store i64 -1, i64* %uncompressed_size, align 8, !dbg !829
  br label %do.body, !dbg !830

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !831, metadata !251), !dbg !833
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !834
  %block_options2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 3, !dbg !834
  %call = call i32 @lzma_block_header_size(%struct.lzma_block* %block_options2) #7, !dbg !834
  store i32 %call, i32* %ret_, align 4, !dbg !834
  %3 = load i32, i32* %ret_, align 4, !dbg !834
  %cmp = icmp ne i32 %3, 0, !dbg !834
  br i1 %cmp, label %if.then, label %if.end, !dbg !834

if.then:                                          ; preds = %do.body
  %4 = load i32, i32* %ret_, align 4, !dbg !836
  store i32 %4, i32* %retval, align 4, !dbg !836
  br label %return, !dbg !836

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !839

do.end:                                           ; preds = %if.end
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !841
  %block_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 2, !dbg !842
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !843
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !844
  %block_options3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 3, !dbg !845
  %call4 = call i32 @lzma_block_encoder_init(%struct.lzma_next_coder_s* %block_encoder, %struct.lzma_allocator* %6, %struct.lzma_block* %block_options3), !dbg !846
  store i32 %call4, i32* %retval, align 4, !dbg !847
  br label %return, !dbg !847

return:                                           ; preds = %do.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !848
  ret i32 %8, !dbg !848
}

; Function Attrs: nounwind
declare i32 @lzma_block_header_encode(%struct.lzma_block*, i8*) #4

; Function Attrs: nounwind readonly
declare i64 @lzma_block_unpadded_size(%struct.lzma_block*) #5

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #6

; Function Attrs: nounwind
declare i32 @lzma_index_append(%struct.lzma_index_s*, %struct.lzma_allocator*, i64, i64) #4

; Function Attrs: nounwind readonly
declare i64 @lzma_index_size(%struct.lzma_index_s*) #5

; Function Attrs: nounwind
declare i32 @lzma_stream_footer_encode(%struct.lzma_stream_flags*, i8*) #4

; Function Attrs: nounwind
declare i32 @lzma_block_header_size(%struct.lzma_block*) #4

declare i32 @lzma_block_encoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_block*) #2

declare void @lzma_free(i8*, %struct.lzma_allocator*) #2

; Function Attrs: nounwind
declare i32 @lzma_filters_copy(%struct.lzma_filter*, %struct.lzma_filter*, %struct.lzma_allocator*) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind }
attributes #8 = { nounwind readonly }
attributes #9 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!247, !248}
!llvm.ident = !{!249}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !201, subprograms: !202, globals: !241)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !89, !145, !72, !183}
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
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !19, file: !1, line: 19, size: 32, align: 32, elements: !176)
!19 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !1, line: 18, size: 11776, align: 64, elements: !20)
!20 = !{!21, !22, !24, !114, !160, !164, !165, !170, !171, !172}
!21 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !19, file: !1, line: 26, baseType: !18, size: 32, align: 32)
!22 = !DIDerivedType(tag: DW_TAG_member, name: "block_encoder_is_initialized", scope: !19, file: !1, line: 31, baseType: !23, size: 8, align: 8, offset: 32)
!23 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!24 = !DIDerivedType(tag: DW_TAG_member, name: "block_encoder", scope: !19, file: !1, line: 34, baseType: !25, size: 512, align: 64, offset: 64)
!25 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !26, line: 75, baseType: !27)
!26 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!27 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !26, line: 119, size: 512, align: 64, elements: !28)
!28 = !{!29, !32, !38, !40, !78, !83, !97, !102}
!29 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !27, file: !26, line: 121, baseType: !30, size: 64, align: 64)
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!31 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !26, line: 73, baseType: !19)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !27, file: !26, line: 125, baseType: !33, size: 64, align: 64, offset: 64)
!33 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !34, line: 63, baseType: !35)
!34 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!35 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !36, line: 55, baseType: !37)
!36 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!37 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !27, file: !26, line: 131, baseType: !39, size: 64, align: 64, offset: 128)
!39 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !36, line: 122, baseType: !37)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !27, file: !26, line: 134, baseType: !41, size: 64, align: 64, offset: 192)
!41 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !26, line: 89, baseType: !42)
!42 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!43 = !DISubroutineType(types: !44)
!44 = !{!45, !30, !46, !62, !67, !55, !69, !67, !55, !71}
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!46 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !47, size: 64, align: 64)
!47 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !48)
!48 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !49)
!49 = !{!50, !57, !61}
!50 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !48, file: !4, line: 376, baseType: !51, size: 64, align: 64)
!51 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!52 = !DISubroutineType(types: !53)
!53 = !{!54, !54, !55, !55}
!54 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!55 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !56, line: 62, baseType: !37)
!56 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!57 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !48, file: !4, line: 390, baseType: !58, size: 64, align: 64, offset: 64)
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !59, size: 64, align: 64)
!59 = !DISubroutineType(types: !60)
!60 = !{null, !54, !54}
!61 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !48, file: !4, line: 401, baseType: !54, size: 64, align: 64, offset: 128)
!62 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !63)
!63 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !64, size: 64, align: 64)
!64 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !65)
!65 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !36, line: 48, baseType: !66)
!66 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!67 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !68)
!68 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!69 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !70)
!70 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !65, size: 64, align: 64)
!71 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !72)
!72 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !73)
!73 = !{!74, !75, !76, !77}
!74 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!75 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!76 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!77 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !27, file: !26, line: 139, baseType: !79, size: 64, align: 64, offset: 256)
!79 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !26, line: 97, baseType: !80)
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!81 = !DISubroutineType(types: !82)
!82 = !{null, !30, !46}
!83 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !27, file: !26, line: 143, baseType: !84, size: 64, align: 64, offset: 320)
!84 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !85, size: 64, align: 64)
!85 = !DISubroutineType(types: !86)
!86 = !{!87, !95}
!87 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !88, line: 55, baseType: !89)
!88 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!89 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !88, line: 27, size: 32, align: 32, elements: !90)
!90 = !{!91, !92, !93, !94}
!91 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!92 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!93 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!94 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !96, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !31)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !27, file: !26, line: 147, baseType: !98, size: 64, align: 64, offset: 384)
!98 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !99, size: 64, align: 64)
!99 = !DISubroutineType(types: !100)
!100 = !{!45, !30, !101, !101, !35}
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !35, size: 64, align: 64)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !27, file: !26, line: 152, baseType: !103, size: 64, align: 64, offset: 448)
!103 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !104, size: 64, align: 64)
!104 = !DISubroutineType(types: !105)
!105 = !{!45, !30, !46, !106, !106}
!106 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !107, size: 64, align: 64)
!107 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !108)
!108 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !109, line: 65, baseType: !110)
!109 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!110 = !DICompositeType(tag: DW_TAG_structure_type, file: !109, line: 43, size: 128, align: 64, elements: !111)
!111 = !{!112, !113}
!112 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !110, file: !109, line: 54, baseType: !33, size: 64, align: 64)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !110, file: !109, line: 63, baseType: !54, size: 64, align: 64, offset: 64)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "block_options", scope: !19, file: !1, line: 37, baseType: !115, size: 1664, align: 64, offset: 576)
!115 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_block", file: !116, line: 245, baseType: !117)
!116 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/block.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!117 = !DICompositeType(tag: DW_TAG_structure_type, file: !116, line: 30, size: 1664, align: 64, elements: !118)
!118 = !{!119, !122, !123, !124, !125, !126, !128, !132, !133, !134, !135, !136, !137, !138, !139, !140, !141, !142, !143, !148, !149, !150, !151, !153, !154, !155, !156, !157, !158, !159}
!119 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !117, file: !116, line: 47, baseType: !120, size: 32, align: 32)
!120 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !36, line: 51, baseType: !121)
!121 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "header_size", scope: !117, file: !116, line: 67, baseType: !120, size: 32, align: 32, offset: 32)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !117, file: !116, line: 88, baseType: !87, size: 32, align: 32, offset: 64)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_size", scope: !117, file: !116, line: 143, baseType: !33, size: 64, align: 64, offset: 128)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !117, file: !116, line: 167, baseType: !33, size: 64, align: 64, offset: 192)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "filters", scope: !117, file: !116, line: 195, baseType: !127, size: 64, align: 64, offset: 256)
!127 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !108, size: 64, align: 64)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "raw_check", scope: !117, file: !116, line: 212, baseType: !129, size: 512, align: 8, offset: 320)
!129 = !DICompositeType(tag: DW_TAG_array_type, baseType: !65, size: 512, align: 8, elements: !130)
!130 = !{!131}
!131 = !DISubrange(count: 64)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !117, file: !116, line: 221, baseType: !54, size: 64, align: 64, offset: 832)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !117, file: !116, line: 222, baseType: !54, size: 64, align: 64, offset: 896)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !117, file: !116, line: 223, baseType: !54, size: 64, align: 64, offset: 960)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !117, file: !116, line: 224, baseType: !120, size: 32, align: 32, offset: 1024)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !117, file: !116, line: 225, baseType: !120, size: 32, align: 32, offset: 1056)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !117, file: !116, line: 226, baseType: !33, size: 64, align: 64, offset: 1088)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !117, file: !116, line: 227, baseType: !33, size: 64, align: 64, offset: 1152)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !117, file: !116, line: 228, baseType: !33, size: 64, align: 64, offset: 1216)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !117, file: !116, line: 229, baseType: !33, size: 64, align: 64, offset: 1280)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !117, file: !116, line: 230, baseType: !33, size: 64, align: 64, offset: 1344)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !117, file: !116, line: 231, baseType: !33, size: 64, align: 64, offset: 1408)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !117, file: !116, line: 232, baseType: !144, size: 32, align: 32, offset: 1472)
!144 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !145)
!145 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !146)
!146 = !{!147}
!147 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !117, file: !116, line: 233, baseType: !144, size: 32, align: 32, offset: 1504)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !117, file: !116, line: 234, baseType: !144, size: 32, align: 32, offset: 1536)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !117, file: !116, line: 235, baseType: !144, size: 32, align: 32, offset: 1568)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool1", scope: !117, file: !116, line: 236, baseType: !152, size: 8, align: 8, offset: 1600)
!152 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !4, line: 29, baseType: !66)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool2", scope: !117, file: !116, line: 237, baseType: !152, size: 8, align: 8, offset: 1608)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool3", scope: !117, file: !116, line: 238, baseType: !152, size: 8, align: 8, offset: 1616)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool4", scope: !117, file: !116, line: 239, baseType: !152, size: 8, align: 8, offset: 1624)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool5", scope: !117, file: !116, line: 240, baseType: !152, size: 8, align: 8, offset: 1632)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool6", scope: !117, file: !116, line: 241, baseType: !152, size: 8, align: 8, offset: 1640)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool7", scope: !117, file: !116, line: 242, baseType: !152, size: 8, align: 8, offset: 1648)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool8", scope: !117, file: !116, line: 243, baseType: !152, size: 8, align: 8, offset: 1656)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "filters", scope: !19, file: !1, line: 40, baseType: !161, size: 640, align: 64, offset: 2240)
!161 = !DICompositeType(tag: DW_TAG_array_type, baseType: !108, size: 640, align: 64, elements: !162)
!162 = !{!163}
!163 = !DISubrange(count: 5)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "index_encoder", scope: !19, file: !1, line: 45, baseType: !25, size: 512, align: 64, offset: 2880)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "index", scope: !19, file: !1, line: 48, baseType: !166, size: 64, align: 64, offset: 3392)
!166 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !167, size: 64, align: 64)
!167 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_index", file: !168, line: 37, baseType: !169)
!168 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/index.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!169 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_index_s", file: !168, line: 37, flags: DIFlagFwdDecl)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_pos", scope: !19, file: !1, line: 51, baseType: !55, size: 64, align: 64, offset: 3456)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_size", scope: !19, file: !1, line: 54, baseType: !55, size: 64, align: 64, offset: 3520)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !19, file: !1, line: 58, baseType: !173, size: 8192, align: 8, offset: 3584)
!173 = !DICompositeType(tag: DW_TAG_array_type, baseType: !65, size: 8192, align: 8, elements: !174)
!174 = !{!175}
!175 = !DISubrange(count: 1024)
!176 = !{!177, !178, !179, !180, !181, !182}
!177 = !DIEnumerator(name: "SEQ_STREAM_HEADER", value: 0)
!178 = !DIEnumerator(name: "SEQ_BLOCK_INIT", value: 1)
!179 = !DIEnumerator(name: "SEQ_BLOCK_HEADER", value: 2)
!180 = !DIEnumerator(name: "SEQ_BLOCK_ENCODE", value: 3)
!181 = !DIEnumerator(name: "SEQ_INDEX_ENCODE", value: 4)
!182 = !DIEnumerator(name: "SEQ_STREAM_FOOTER", value: 5)
!183 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !184, file: !26, line: 182, size: 32, align: 32, elements: !194)
!184 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_internal_s", file: !26, line: 174, size: 704, align: 64, elements: !185)
!185 = !{!186, !187, !188, !189, !193}
!186 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !184, file: !26, line: 176, baseType: !25, size: 512, align: 64)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !184, file: !26, line: 189, baseType: !183, size: 32, align: 32, offset: 512)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !184, file: !26, line: 194, baseType: !55, size: 64, align: 64, offset: 576)
!189 = !DIDerivedType(tag: DW_TAG_member, name: "supported_actions", scope: !184, file: !26, line: 197, baseType: !190, size: 32, align: 8, offset: 640)
!190 = !DICompositeType(tag: DW_TAG_array_type, baseType: !23, size: 32, align: 8, elements: !191)
!191 = !{!192}
!192 = !DISubrange(count: 4)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "allow_buf_error", scope: !184, file: !26, line: 201, baseType: !23, size: 8, align: 8, offset: 672)
!194 = !{!195, !196, !197, !198, !199, !200}
!195 = !DIEnumerator(name: "ISEQ_RUN", value: 0)
!196 = !DIEnumerator(name: "ISEQ_SYNC_FLUSH", value: 1)
!197 = !DIEnumerator(name: "ISEQ_FULL_FLUSH", value: 2)
!198 = !DIEnumerator(name: "ISEQ_FINISH", value: 3)
!199 = !DIEnumerator(name: "ISEQ_END", value: 4)
!200 = !DIEnumerator(name: "ISEQ_ERROR", value: 5)
!201 = !{!39, !54, !127}
!202 = !{!203, !208, !235, !236, !239, !240}
!203 = distinct !DISubprogram(name: "lzma_stream_encoder_init", scope: !1, file: !1, line: 275, type: !204, isLocal: false, isDefinition: true, scopeLine: 277, flags: DIFlagPrototyped, isOptimized: false, variables: !207)
!204 = !DISubroutineType(types: !205)
!205 = !{!45, !206, !46, !106, !87}
!206 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !25, size: 64, align: 64)
!207 = !{}
!208 = distinct !DISubprogram(name: "lzma_stream_encoder", scope: !1, file: !1, line: 327, type: !209, isLocal: false, isDefinition: true, scopeLine: 329, flags: DIFlagPrototyped, isOptimized: false, variables: !207)
!209 = !DISubroutineType(types: !210)
!210 = !{!45, !211, !106, !87}
!211 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !212, size: 64, align: 64)
!212 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream", file: !4, line: 490, baseType: !213)
!213 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 453, size: 1088, align: 64, elements: !214)
!214 = !{!215, !216, !217, !218, !219, !220, !221, !222, !225, !226, !227, !228, !229, !230, !231, !232, !233, !234}
!215 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !213, file: !4, line: 454, baseType: !63, size: 64, align: 64)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !213, file: !4, line: 455, baseType: !55, size: 64, align: 64, offset: 64)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !213, file: !4, line: 456, baseType: !35, size: 64, align: 64, offset: 128)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !213, file: !4, line: 458, baseType: !70, size: 64, align: 64, offset: 192)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !213, file: !4, line: 459, baseType: !55, size: 64, align: 64, offset: 256)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !213, file: !4, line: 460, baseType: !35, size: 64, align: 64, offset: 320)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "allocator", scope: !213, file: !4, line: 468, baseType: !46, size: 64, align: 64, offset: 384)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "internal", scope: !213, file: !4, line: 471, baseType: !223, size: 64, align: 64, offset: 448)
!223 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !224, size: 64, align: 64)
!224 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_internal", file: !4, line: 411, baseType: !184)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !213, file: !4, line: 479, baseType: !54, size: 64, align: 64, offset: 512)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !213, file: !4, line: 480, baseType: !54, size: 64, align: 64, offset: 576)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !213, file: !4, line: 481, baseType: !54, size: 64, align: 64, offset: 640)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr4", scope: !213, file: !4, line: 482, baseType: !54, size: 64, align: 64, offset: 704)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !213, file: !4, line: 483, baseType: !35, size: 64, align: 64, offset: 768)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !213, file: !4, line: 484, baseType: !35, size: 64, align: 64, offset: 832)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !213, file: !4, line: 485, baseType: !55, size: 64, align: 64, offset: 896)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !213, file: !4, line: 486, baseType: !55, size: 64, align: 64, offset: 960)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !213, file: !4, line: 487, baseType: !144, size: 32, align: 32, offset: 1024)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !213, file: !4, line: 488, baseType: !144, size: 32, align: 32, offset: 1056)
!235 = distinct !DISubprogram(name: "stream_encode", scope: !1, file: !1, line: 82, type: !43, isLocal: true, isDefinition: true, scopeLine: 86, flags: DIFlagPrototyped, isOptimized: false, variables: !207)
!236 = distinct !DISubprogram(name: "block_encoder_init", scope: !1, file: !1, line: 63, type: !237, isLocal: true, isDefinition: true, scopeLine: 64, flags: DIFlagPrototyped, isOptimized: false, variables: !207)
!237 = !DISubroutineType(types: !238)
!238 = !{!45, !30, !46}
!239 = distinct !DISubprogram(name: "stream_encoder_end", scope: !1, file: !1, line: 215, type: !81, isLocal: true, isDefinition: true, scopeLine: 216, flags: DIFlagPrototyped, isOptimized: false, variables: !207)
!240 = distinct !DISubprogram(name: "stream_encoder_update", scope: !1, file: !1, line: 232, type: !104, isLocal: true, isDefinition: true, scopeLine: 235, flags: DIFlagPrototyped, isOptimized: false, variables: !207)
!241 = !{!242, !245}
!242 = !DIGlobalVariable(name: "convert", scope: !235, file: !1, line: 152, type: !243, isLocal: true, isDefinition: true, variable: [4 x i32]* @stream_encode.convert)
!243 = !DICompositeType(tag: DW_TAG_array_type, baseType: !244, size: 128, align: 32, elements: !191)
!244 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !71)
!245 = !DIGlobalVariable(name: "LZMA_NEXT_CODER_INIT", scope: !0, file: !26, line: 159, type: !246, isLocal: true, isDefinition: true, variable: %struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT)
!246 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !25)
!247 = !{i32 2, !"Dwarf Version", i32 4}
!248 = !{i32 2, !"Debug Info Version", i32 3}
!249 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!250 = !DILocalVariable(name: "next", arg: 1, scope: !203, file: !1, line: 275, type: !206)
!251 = !DIExpression()
!252 = !DILocation(line: 275, column: 43, scope: !203)
!253 = !DILocalVariable(name: "allocator", arg: 2, scope: !203, file: !1, line: 275, type: !46)
!254 = !DILocation(line: 275, column: 65, scope: !203)
!255 = !DILocalVariable(name: "filters", arg: 3, scope: !203, file: !1, line: 276, type: !106)
!256 = !DILocation(line: 276, column: 22, scope: !203)
!257 = !DILocalVariable(name: "check", arg: 4, scope: !203, file: !1, line: 276, type: !87)
!258 = !DILocation(line: 276, column: 42, scope: !203)
!259 = !DILocalVariable(name: "stream_flags", scope: !203, file: !1, line: 278, type: !260)
!260 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream_flags", file: !261, line: 105, baseType: !262)
!261 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/stream_flags.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!262 = !DICompositeType(tag: DW_TAG_structure_type, file: !261, line: 33, size: 448, align: 64, elements: !263)
!263 = !{!264, !265, !266, !267, !268, !269, !270, !271, !272, !273, !274, !275, !276, !277, !278, !279, !280}
!264 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !262, file: !261, line: 51, baseType: !120, size: 32, align: 32)
!265 = !DIDerivedType(tag: DW_TAG_member, name: "backward_size", scope: !262, file: !261, line: 69, baseType: !33, size: 64, align: 64, offset: 64)
!266 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !262, file: !261, line: 79, baseType: !87, size: 32, align: 32, offset: 128)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !262, file: !261, line: 90, baseType: !144, size: 32, align: 32, offset: 160)
!268 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !262, file: !261, line: 91, baseType: !144, size: 32, align: 32, offset: 192)
!269 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !262, file: !261, line: 92, baseType: !144, size: 32, align: 32, offset: 224)
!270 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !262, file: !261, line: 93, baseType: !144, size: 32, align: 32, offset: 256)
!271 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool1", scope: !262, file: !261, line: 94, baseType: !152, size: 8, align: 8, offset: 288)
!272 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool2", scope: !262, file: !261, line: 95, baseType: !152, size: 8, align: 8, offset: 296)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool3", scope: !262, file: !261, line: 96, baseType: !152, size: 8, align: 8, offset: 304)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool4", scope: !262, file: !261, line: 97, baseType: !152, size: 8, align: 8, offset: 312)
!275 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool5", scope: !262, file: !261, line: 98, baseType: !152, size: 8, align: 8, offset: 320)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool6", scope: !262, file: !261, line: 99, baseType: !152, size: 8, align: 8, offset: 328)
!277 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool7", scope: !262, file: !261, line: 100, baseType: !152, size: 8, align: 8, offset: 336)
!278 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool8", scope: !262, file: !261, line: 101, baseType: !152, size: 8, align: 8, offset: 344)
!279 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !262, file: !261, line: 102, baseType: !120, size: 32, align: 32, offset: 352)
!280 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !262, file: !261, line: 103, baseType: !120, size: 32, align: 32, offset: 384)
!281 = !DILocation(line: 278, column: 20, scope: !203)
!282 = !DILocation(line: 278, column: 35, scope: !203)
!283 = !DILocation(line: 278, column: 43, scope: !203)
!284 = !DILocation(line: 280, column: 2, scope: !203)
!285 = !DILocation(line: 280, column: 2, scope: !286)
!286 = !DILexicalBlockFile(scope: !287, file: !1, discriminator: 1)
!287 = distinct !DILexicalBlock(scope: !288, file: !1, line: 280, column: 2)
!288 = distinct !DILexicalBlock(scope: !203, file: !1, line: 280, column: 2)
!289 = !DILocation(line: 280, column: 2, scope: !290)
!290 = !DILexicalBlockFile(scope: !287, file: !1, discriminator: 2)
!291 = !DILocation(line: 280, column: 2, scope: !292)
!292 = !DILexicalBlockFile(scope: !288, file: !1, discriminator: 3)
!293 = !DILocation(line: 282, column: 6, scope: !294)
!294 = distinct !DILexicalBlock(scope: !203, file: !1, line: 282, column: 6)
!295 = !DILocation(line: 282, column: 14, scope: !294)
!296 = !DILocation(line: 282, column: 6, scope: !203)
!297 = !DILocation(line: 283, column: 3, scope: !294)
!298 = !DILocation(line: 285, column: 6, scope: !299)
!299 = distinct !DILexicalBlock(scope: !203, file: !1, line: 285, column: 6)
!300 = !DILocation(line: 285, column: 12, scope: !299)
!301 = !DILocation(line: 285, column: 18, scope: !299)
!302 = !DILocation(line: 285, column: 6, scope: !203)
!303 = !DILocation(line: 286, column: 48, scope: !304)
!304 = distinct !DILexicalBlock(scope: !299, file: !1, line: 285, column: 27)
!305 = !DILocation(line: 286, column: 17, scope: !304)
!306 = !DILocation(line: 286, column: 3, scope: !304)
!307 = !DILocation(line: 286, column: 9, scope: !304)
!308 = !DILocation(line: 286, column: 15, scope: !304)
!309 = !DILocation(line: 287, column: 7, scope: !310)
!310 = distinct !DILexicalBlock(scope: !304, file: !1, line: 287, column: 7)
!311 = !DILocation(line: 287, column: 13, scope: !310)
!312 = !DILocation(line: 287, column: 19, scope: !310)
!313 = !DILocation(line: 287, column: 7, scope: !304)
!314 = !DILocation(line: 288, column: 4, scope: !310)
!315 = !DILocation(line: 290, column: 3, scope: !304)
!316 = !DILocation(line: 290, column: 9, scope: !304)
!317 = !DILocation(line: 290, column: 14, scope: !304)
!318 = !DILocation(line: 291, column: 3, scope: !304)
!319 = !DILocation(line: 291, column: 9, scope: !304)
!320 = !DILocation(line: 291, column: 13, scope: !304)
!321 = !DILocation(line: 292, column: 3, scope: !304)
!322 = !DILocation(line: 292, column: 9, scope: !304)
!323 = !DILocation(line: 292, column: 16, scope: !304)
!324 = !DILocation(line: 294, column: 3, scope: !304)
!325 = !DILocation(line: 294, column: 9, scope: !304)
!326 = !DILocation(line: 294, column: 16, scope: !304)
!327 = !DILocation(line: 294, column: 27, scope: !304)
!328 = !DILocation(line: 294, column: 30, scope: !304)
!329 = !DILocation(line: 295, column: 3, scope: !304)
!330 = !DILocation(line: 295, column: 9, scope: !304)
!331 = !DILocation(line: 295, column: 16, scope: !304)
!332 = !DILocation(line: 295, column: 32, scope: !304)
!333 = !DILocation(line: 296, column: 3, scope: !304)
!334 = !DILocation(line: 296, column: 9, scope: !304)
!335 = !DILocation(line: 296, column: 16, scope: !304)
!336 = !DILocation(line: 296, column: 32, scope: !304)
!337 = !DILocation(line: 297, column: 3, scope: !304)
!338 = !DILocation(line: 297, column: 9, scope: !304)
!339 = !DILocation(line: 297, column: 16, scope: !304)
!340 = !DILocation(line: 297, column: 22, scope: !304)
!341 = !DILocation(line: 298, column: 2, scope: !304)
!342 = !DILocation(line: 301, column: 2, scope: !203)
!343 = !DILocation(line: 301, column: 8, scope: !203)
!344 = !DILocation(line: 301, column: 15, scope: !203)
!345 = !DILocation(line: 301, column: 24, scope: !203)
!346 = !DILocation(line: 302, column: 2, scope: !203)
!347 = !DILocation(line: 302, column: 8, scope: !203)
!348 = !DILocation(line: 302, column: 15, scope: !203)
!349 = !DILocation(line: 302, column: 29, scope: !203)
!350 = !DILocation(line: 302, column: 37, scope: !203)
!351 = !DILocation(line: 303, column: 37, scope: !203)
!352 = !DILocation(line: 303, column: 2, scope: !203)
!353 = !DILocation(line: 303, column: 8, scope: !203)
!354 = !DILocation(line: 303, column: 15, scope: !203)
!355 = !DILocation(line: 303, column: 29, scope: !203)
!356 = !DILocation(line: 303, column: 35, scope: !203)
!357 = !DILocation(line: 306, column: 17, scope: !203)
!358 = !DILocation(line: 306, column: 23, scope: !203)
!359 = !DILocation(line: 306, column: 30, scope: !203)
!360 = !DILocation(line: 306, column: 37, scope: !203)
!361 = !DILocation(line: 306, column: 2, scope: !203)
!362 = !DILocation(line: 307, column: 39, scope: !203)
!363 = !DILocation(line: 307, column: 23, scope: !203)
!364 = !DILocation(line: 307, column: 2, scope: !203)
!365 = !DILocation(line: 307, column: 8, scope: !203)
!366 = !DILocation(line: 307, column: 15, scope: !203)
!367 = !DILocation(line: 307, column: 21, scope: !203)
!368 = !DILocation(line: 308, column: 6, scope: !369)
!369 = distinct !DILexicalBlock(scope: !203, file: !1, line: 308, column: 6)
!370 = !DILocation(line: 308, column: 12, scope: !369)
!371 = !DILocation(line: 308, column: 19, scope: !369)
!372 = !DILocation(line: 308, column: 25, scope: !369)
!373 = !DILocation(line: 308, column: 6, scope: !203)
!374 = !DILocation(line: 309, column: 3, scope: !369)
!375 = !DILocation(line: 312, column: 2, scope: !203)
!376 = !DILocalVariable(name: "ret_", scope: !377, file: !1, line: 312, type: !378)
!377 = distinct !DILexicalBlock(scope: !203, file: !1, line: 312, column: 2)
!378 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !45)
!379 = !DILocation(line: 312, column: 2, scope: !377)
!380 = !DILocation(line: 312, column: 2, scope: !381)
!381 = !DILexicalBlockFile(scope: !377, file: !1, discriminator: 1)
!382 = !DILocation(line: 312, column: 2, scope: !383)
!383 = !DILexicalBlockFile(scope: !384, file: !1, discriminator: 2)
!384 = distinct !DILexicalBlock(scope: !377, file: !1, line: 312, column: 2)
!385 = !DILocation(line: 312, column: 2, scope: !386)
!386 = !DILexicalBlockFile(scope: !377, file: !1, discriminator: 3)
!387 = !DILocation(line: 315, column: 2, scope: !203)
!388 = !DILocation(line: 315, column: 8, scope: !203)
!389 = !DILocation(line: 315, column: 15, scope: !203)
!390 = !DILocation(line: 315, column: 26, scope: !203)
!391 = !DILocation(line: 316, column: 2, scope: !203)
!392 = !DILocation(line: 316, column: 8, scope: !203)
!393 = !DILocation(line: 316, column: 15, scope: !203)
!394 = !DILocation(line: 316, column: 27, scope: !203)
!395 = !DILocation(line: 322, column: 4, scope: !203)
!396 = !DILocation(line: 322, column: 10, scope: !203)
!397 = !DILocation(line: 322, column: 17, scope: !203)
!398 = !DILocation(line: 322, column: 28, scope: !203)
!399 = !DILocation(line: 321, column: 9, scope: !203)
!400 = !DILocation(line: 321, column: 2, scope: !203)
!401 = !DILocation(line: 323, column: 1, scope: !203)
!402 = !DILocalVariable(name: "coder", arg: 1, scope: !235, file: !1, line: 82, type: !30)
!403 = !DILocation(line: 82, column: 27, scope: !235)
!404 = !DILocalVariable(name: "allocator", arg: 2, scope: !235, file: !1, line: 82, type: !46)
!405 = !DILocation(line: 82, column: 50, scope: !235)
!406 = !DILocalVariable(name: "in", arg: 3, scope: !235, file: !1, line: 83, type: !62)
!407 = !DILocation(line: 83, column: 32, scope: !235)
!408 = !DILocalVariable(name: "in_pos", arg: 4, scope: !235, file: !1, line: 83, type: !67)
!409 = !DILocation(line: 83, column: 58, scope: !235)
!410 = !DILocalVariable(name: "in_size", arg: 5, scope: !235, file: !1, line: 84, type: !55)
!411 = !DILocation(line: 84, column: 10, scope: !235)
!412 = !DILocalVariable(name: "out", arg: 6, scope: !235, file: !1, line: 84, type: !69)
!413 = !DILocation(line: 84, column: 42, scope: !235)
!414 = !DILocalVariable(name: "out_pos", arg: 7, scope: !235, file: !1, line: 85, type: !67)
!415 = !DILocation(line: 85, column: 25, scope: !235)
!416 = !DILocalVariable(name: "out_size", arg: 8, scope: !235, file: !1, line: 85, type: !55)
!417 = !DILocation(line: 85, column: 41, scope: !235)
!418 = !DILocalVariable(name: "action", arg: 9, scope: !235, file: !1, line: 85, type: !71)
!419 = !DILocation(line: 85, column: 63, scope: !235)
!420 = !DILocation(line: 88, column: 2, scope: !235)
!421 = !DILocation(line: 88, column: 10, scope: !422)
!422 = !DILexicalBlockFile(scope: !235, file: !1, discriminator: 1)
!423 = !DILocation(line: 88, column: 9, scope: !422)
!424 = !DILocation(line: 88, column: 20, scope: !422)
!425 = !DILocation(line: 88, column: 18, scope: !422)
!426 = !DILocation(line: 88, column: 2, scope: !422)
!427 = !DILocation(line: 89, column: 10, scope: !235)
!428 = !DILocation(line: 89, column: 17, scope: !235)
!429 = !DILocation(line: 89, column: 2, scope: !235)
!430 = !DILocation(line: 93, column: 15, scope: !431)
!431 = distinct !DILexicalBlock(scope: !235, file: !1, line: 89, column: 27)
!432 = !DILocation(line: 93, column: 22, scope: !431)
!433 = !DILocation(line: 93, column: 31, scope: !431)
!434 = !DILocation(line: 93, column: 38, scope: !431)
!435 = !DILocation(line: 94, column: 5, scope: !431)
!436 = !DILocation(line: 94, column: 12, scope: !431)
!437 = !DILocation(line: 94, column: 25, scope: !431)
!438 = !DILocation(line: 94, column: 30, scope: !431)
!439 = !DILocation(line: 94, column: 39, scope: !431)
!440 = !DILocation(line: 93, column: 3, scope: !431)
!441 = !DILocation(line: 95, column: 7, scope: !442)
!442 = distinct !DILexicalBlock(scope: !431, file: !1, line: 95, column: 7)
!443 = !DILocation(line: 95, column: 14, scope: !442)
!444 = !DILocation(line: 95, column: 27, scope: !442)
!445 = !DILocation(line: 95, column: 34, scope: !442)
!446 = !DILocation(line: 95, column: 25, scope: !442)
!447 = !DILocation(line: 95, column: 7, scope: !431)
!448 = !DILocation(line: 96, column: 4, scope: !442)
!449 = !DILocation(line: 98, column: 7, scope: !450)
!450 = distinct !DILexicalBlock(scope: !431, file: !1, line: 98, column: 7)
!451 = !DILocation(line: 98, column: 14, scope: !450)
!452 = !DILocation(line: 98, column: 23, scope: !450)
!453 = !DILocation(line: 98, column: 7, scope: !431)
!454 = !DILocation(line: 99, column: 4, scope: !450)
!455 = !DILocation(line: 101, column: 3, scope: !431)
!456 = !DILocation(line: 101, column: 10, scope: !431)
!457 = !DILocation(line: 101, column: 21, scope: !431)
!458 = !DILocation(line: 102, column: 5, scope: !431)
!459 = !DILocation(line: 102, column: 12, scope: !431)
!460 = !DILocation(line: 102, column: 3, scope: !431)
!461 = !DILocation(line: 103, column: 3, scope: !431)
!462 = !DILocation(line: 106, column: 8, scope: !463)
!463 = distinct !DILexicalBlock(scope: !464, file: !1, line: 106, column: 7)
!464 = distinct !DILexicalBlock(scope: !431, file: !1, line: 105, column: 23)
!465 = !DILocation(line: 106, column: 7, scope: !463)
!466 = !DILocation(line: 106, column: 18, scope: !463)
!467 = !DILocation(line: 106, column: 15, scope: !463)
!468 = !DILocation(line: 106, column: 7, scope: !464)
!469 = !DILocation(line: 110, column: 8, scope: !470)
!470 = distinct !DILexicalBlock(scope: !471, file: !1, line: 110, column: 8)
!471 = distinct !DILexicalBlock(scope: !463, file: !1, line: 106, column: 27)
!472 = !DILocation(line: 110, column: 15, scope: !470)
!473 = !DILocation(line: 110, column: 8, scope: !471)
!474 = !DILocation(line: 111, column: 12, scope: !470)
!475 = !DILocation(line: 111, column: 19, scope: !470)
!476 = !DILocation(line: 111, column: 5, scope: !470)
!477 = !DILocation(line: 121, column: 4, scope: !471)
!478 = !DILocalVariable(name: "ret_", scope: !479, file: !1, line: 121, type: !378)
!479 = distinct !DILexicalBlock(scope: !471, file: !1, line: 121, column: 4)
!480 = !DILocation(line: 121, column: 4, scope: !479)
!481 = !DILocation(line: 121, column: 4, scope: !482)
!482 = !DILexicalBlockFile(scope: !479, file: !1, discriminator: 1)
!483 = !DILocation(line: 121, column: 4, scope: !484)
!484 = !DILexicalBlockFile(scope: !485, file: !1, discriminator: 2)
!485 = distinct !DILexicalBlock(scope: !479, file: !1, line: 121, column: 4)
!486 = !DILocation(line: 121, column: 4, scope: !487)
!487 = !DILexicalBlockFile(scope: !479, file: !1, discriminator: 3)
!488 = !DILocation(line: 124, column: 4, scope: !471)
!489 = !DILocation(line: 124, column: 11, scope: !471)
!490 = !DILocation(line: 124, column: 20, scope: !471)
!491 = !DILocation(line: 125, column: 4, scope: !471)
!492 = !DILocation(line: 131, column: 8, scope: !493)
!493 = distinct !DILexicalBlock(scope: !464, file: !1, line: 131, column: 7)
!494 = !DILocation(line: 131, column: 15, scope: !493)
!495 = !DILocation(line: 131, column: 7, scope: !464)
!496 = !DILocation(line: 132, column: 4, scope: !493)
!497 = !DILocalVariable(name: "ret_", scope: !498, file: !1, line: 132, type: !378)
!498 = distinct !DILexicalBlock(scope: !493, file: !1, line: 132, column: 4)
!499 = !DILocation(line: 132, column: 4, scope: !498)
!500 = !DILocation(line: 132, column: 4, scope: !501)
!501 = !DILexicalBlockFile(scope: !498, file: !1, discriminator: 1)
!502 = !DILocation(line: 132, column: 4, scope: !503)
!503 = !DILexicalBlockFile(scope: !504, file: !1, discriminator: 2)
!504 = distinct !DILexicalBlock(scope: !498, file: !1, line: 132, column: 4)
!505 = !DILocation(line: 132, column: 4, scope: !506)
!506 = !DILexicalBlockFile(scope: !498, file: !1, discriminator: 3)
!507 = !DILocation(line: 132, column: 4, scope: !508)
!508 = !DILexicalBlockFile(scope: !498, file: !1, discriminator: 4)
!509 = !DILocation(line: 136, column: 3, scope: !464)
!510 = !DILocation(line: 136, column: 10, scope: !464)
!511 = !DILocation(line: 136, column: 39, scope: !464)
!512 = !DILocation(line: 140, column: 33, scope: !513)
!513 = distinct !DILexicalBlock(scope: !464, file: !1, line: 140, column: 7)
!514 = !DILocation(line: 140, column: 40, scope: !513)
!515 = !DILocation(line: 141, column: 5, scope: !513)
!516 = !DILocation(line: 141, column: 12, scope: !513)
!517 = !DILocation(line: 140, column: 7, scope: !513)
!518 = !DILocation(line: 141, column: 20, scope: !513)
!519 = !DILocation(line: 140, column: 7, scope: !464)
!520 = !DILocation(line: 142, column: 4, scope: !513)
!521 = !DILocation(line: 144, column: 24, scope: !464)
!522 = !DILocation(line: 144, column: 31, scope: !464)
!523 = !DILocation(line: 144, column: 45, scope: !464)
!524 = !DILocation(line: 144, column: 3, scope: !464)
!525 = !DILocation(line: 144, column: 10, scope: !464)
!526 = !DILocation(line: 144, column: 22, scope: !464)
!527 = !DILocation(line: 145, column: 3, scope: !464)
!528 = !DILocation(line: 145, column: 10, scope: !464)
!529 = !DILocation(line: 145, column: 19, scope: !464)
!530 = !DILocation(line: 146, column: 3, scope: !464)
!531 = !DILocalVariable(name: "unpadded_size", scope: !532, file: !1, line: 150, type: !33)
!532 = distinct !DILexicalBlock(scope: !431, file: !1, line: 149, column: 25)
!533 = !DILocation(line: 150, column: 12, scope: !532)
!534 = !DILocalVariable(name: "ret", scope: !532, file: !1, line: 159, type: !378)
!535 = !DILocation(line: 159, column: 18, scope: !532)
!536 = !DILocation(line: 159, column: 24, scope: !532)
!537 = !DILocation(line: 159, column: 31, scope: !532)
!538 = !DILocation(line: 159, column: 45, scope: !532)
!539 = !DILocation(line: 160, column: 5, scope: !532)
!540 = !DILocation(line: 160, column: 12, scope: !532)
!541 = !DILocation(line: 160, column: 26, scope: !532)
!542 = !DILocation(line: 160, column: 33, scope: !532)
!543 = !DILocation(line: 161, column: 5, scope: !532)
!544 = !DILocation(line: 161, column: 9, scope: !532)
!545 = !DILocation(line: 161, column: 17, scope: !532)
!546 = !DILocation(line: 162, column: 5, scope: !532)
!547 = !DILocation(line: 162, column: 10, scope: !532)
!548 = !DILocation(line: 162, column: 19, scope: !532)
!549 = !DILocation(line: 162, column: 37, scope: !532)
!550 = !DILocation(line: 162, column: 29, scope: !532)
!551 = !DILocation(line: 163, column: 7, scope: !552)
!552 = distinct !DILexicalBlock(scope: !532, file: !1, line: 163, column: 7)
!553 = !DILocation(line: 163, column: 11, scope: !552)
!554 = !DILocation(line: 163, column: 30, scope: !552)
!555 = !DILocation(line: 163, column: 33, scope: !556)
!556 = !DILexicalBlockFile(scope: !552, file: !1, discriminator: 1)
!557 = !DILocation(line: 163, column: 40, scope: !556)
!558 = !DILocation(line: 163, column: 7, scope: !556)
!559 = !DILocation(line: 164, column: 11, scope: !552)
!560 = !DILocation(line: 164, column: 4, scope: !552)
!561 = !DILocation(line: 168, column: 6, scope: !532)
!562 = !DILocation(line: 168, column: 13, scope: !532)
!563 = !DILocation(line: 167, column: 19, scope: !532)
!564 = !DILocation(line: 167, column: 17, scope: !532)
!565 = !DILocation(line: 169, column: 3, scope: !532)
!566 = !DILocation(line: 169, column: 3, scope: !567)
!567 = !DILexicalBlockFile(scope: !532, file: !1, discriminator: 1)
!568 = !DILocation(line: 169, column: 3, scope: !569)
!569 = !DILexicalBlockFile(scope: !532, file: !1, discriminator: 2)
!570 = !DILocation(line: 169, column: 3, scope: !571)
!571 = !DILexicalBlockFile(scope: !532, file: !1, discriminator: 3)
!572 = !DILocation(line: 170, column: 3, scope: !532)
!573 = !DILocalVariable(name: "ret_", scope: !574, file: !1, line: 170, type: !378)
!574 = distinct !DILexicalBlock(scope: !532, file: !1, line: 170, column: 3)
!575 = !DILocation(line: 170, column: 3, scope: !574)
!576 = !DILocation(line: 170, column: 3, scope: !577)
!577 = !DILexicalBlockFile(scope: !574, file: !1, discriminator: 1)
!578 = !DILocation(line: 170, column: 3, scope: !579)
!579 = !DILexicalBlockFile(scope: !580, file: !1, discriminator: 2)
!580 = distinct !DILexicalBlock(scope: !574, file: !1, line: 170, column: 3)
!581 = !DILocation(line: 170, column: 3, scope: !582)
!582 = !DILexicalBlockFile(scope: !574, file: !1, discriminator: 3)
!583 = !DILocation(line: 174, column: 3, scope: !532)
!584 = !DILocation(line: 174, column: 10, scope: !532)
!585 = !DILocation(line: 174, column: 19, scope: !532)
!586 = !DILocation(line: 175, column: 3, scope: !532)
!587 = !DILocalVariable(name: "stream_flags", scope: !588, file: !1, line: 179, type: !589)
!588 = distinct !DILexicalBlock(scope: !431, file: !1, line: 178, column: 25)
!589 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !260)
!590 = !DILocation(line: 179, column: 27, scope: !588)
!591 = !DILocation(line: 179, column: 42, scope: !588)
!592 = !DILocation(line: 181, column: 20, scope: !588)
!593 = !DILocation(line: 181, column: 27, scope: !588)
!594 = !DILocation(line: 181, column: 4, scope: !588)
!595 = !DILocation(line: 182, column: 4, scope: !588)
!596 = !DILocation(line: 182, column: 11, scope: !588)
!597 = !DILocation(line: 182, column: 25, scope: !588)
!598 = !DILocalVariable(name: "ret", scope: !588, file: !1, line: 187, type: !378)
!599 = !DILocation(line: 187, column: 18, scope: !588)
!600 = !DILocation(line: 187, column: 24, scope: !588)
!601 = !DILocation(line: 187, column: 31, scope: !588)
!602 = !DILocation(line: 187, column: 45, scope: !588)
!603 = !DILocation(line: 188, column: 5, scope: !588)
!604 = !DILocation(line: 188, column: 12, scope: !588)
!605 = !DILocation(line: 188, column: 26, scope: !588)
!606 = !DILocation(line: 188, column: 33, scope: !588)
!607 = !DILocation(line: 190, column: 5, scope: !588)
!608 = !DILocation(line: 190, column: 10, scope: !588)
!609 = !DILocation(line: 190, column: 19, scope: !588)
!610 = !DILocation(line: 191, column: 7, scope: !611)
!611 = distinct !DILexicalBlock(scope: !588, file: !1, line: 191, column: 7)
!612 = !DILocation(line: 191, column: 11, scope: !611)
!613 = !DILocation(line: 191, column: 7, scope: !588)
!614 = !DILocation(line: 192, column: 11, scope: !611)
!615 = !DILocation(line: 192, column: 4, scope: !611)
!616 = !DILocation(line: 196, column: 48, scope: !617)
!617 = distinct !DILexicalBlock(scope: !588, file: !1, line: 196, column: 7)
!618 = !DILocation(line: 196, column: 55, scope: !617)
!619 = !DILocation(line: 196, column: 7, scope: !617)
!620 = !DILocation(line: 197, column: 5, scope: !617)
!621 = !DILocation(line: 196, column: 7, scope: !588)
!622 = !DILocation(line: 198, column: 4, scope: !617)
!623 = !DILocation(line: 200, column: 3, scope: !588)
!624 = !DILocation(line: 200, column: 10, scope: !588)
!625 = !DILocation(line: 200, column: 22, scope: !588)
!626 = !DILocation(line: 201, column: 3, scope: !588)
!627 = !DILocation(line: 201, column: 10, scope: !588)
!628 = !DILocation(line: 201, column: 19, scope: !588)
!629 = !DILocation(line: 202, column: 3, scope: !588)
!630 = !DILocation(line: 206, column: 3, scope: !431)
!631 = !DILocation(line: 88, column: 2, scope: !632)
!632 = !DILexicalBlockFile(scope: !235, file: !1, discriminator: 2)
!633 = !DILocation(line: 210, column: 2, scope: !235)
!634 = !DILocation(line: 211, column: 1, scope: !235)
!635 = !DILocalVariable(name: "coder", arg: 1, scope: !239, file: !1, line: 215, type: !30)
!636 = !DILocation(line: 215, column: 32, scope: !239)
!637 = !DILocalVariable(name: "allocator", arg: 2, scope: !239, file: !1, line: 215, type: !46)
!638 = !DILocation(line: 215, column: 55, scope: !239)
!639 = !DILocalVariable(name: "i", scope: !239, file: !1, line: 217, type: !55)
!640 = !DILocation(line: 217, column: 9, scope: !239)
!641 = !DILocation(line: 219, column: 17, scope: !239)
!642 = !DILocation(line: 219, column: 24, scope: !239)
!643 = !DILocation(line: 219, column: 39, scope: !239)
!644 = !DILocation(line: 219, column: 2, scope: !239)
!645 = !DILocation(line: 220, column: 17, scope: !239)
!646 = !DILocation(line: 220, column: 24, scope: !239)
!647 = !DILocation(line: 220, column: 39, scope: !239)
!648 = !DILocation(line: 220, column: 2, scope: !239)
!649 = !DILocation(line: 221, column: 17, scope: !239)
!650 = !DILocation(line: 221, column: 24, scope: !239)
!651 = !DILocation(line: 221, column: 31, scope: !239)
!652 = !DILocation(line: 221, column: 2, scope: !239)
!653 = !DILocation(line: 223, column: 9, scope: !654)
!654 = distinct !DILexicalBlock(scope: !239, file: !1, line: 223, column: 2)
!655 = !DILocation(line: 223, column: 7, scope: !654)
!656 = !DILocation(line: 223, column: 29, scope: !657)
!657 = !DILexicalBlockFile(scope: !658, file: !1, discriminator: 1)
!658 = distinct !DILexicalBlock(scope: !654, file: !1, line: 223, column: 2)
!659 = !DILocation(line: 223, column: 14, scope: !657)
!660 = !DILocation(line: 223, column: 21, scope: !657)
!661 = !DILocation(line: 223, column: 32, scope: !657)
!662 = !DILocation(line: 223, column: 35, scope: !657)
!663 = !DILocation(line: 223, column: 2, scope: !657)
!664 = !DILocation(line: 224, column: 28, scope: !658)
!665 = !DILocation(line: 224, column: 13, scope: !658)
!666 = !DILocation(line: 224, column: 20, scope: !658)
!667 = !DILocation(line: 224, column: 31, scope: !658)
!668 = !DILocation(line: 224, column: 40, scope: !658)
!669 = !DILocation(line: 224, column: 3, scope: !658)
!670 = !DILocation(line: 223, column: 56, scope: !671)
!671 = !DILexicalBlockFile(scope: !658, file: !1, discriminator: 2)
!672 = !DILocation(line: 223, column: 2, scope: !671)
!673 = !DILocation(line: 226, column: 12, scope: !239)
!674 = !DILocation(line: 226, column: 19, scope: !239)
!675 = !DILocation(line: 226, column: 2, scope: !239)
!676 = !DILocation(line: 227, column: 2, scope: !239)
!677 = !DILocalVariable(name: "coder", arg: 1, scope: !240, file: !1, line: 232, type: !30)
!678 = !DILocation(line: 232, column: 35, scope: !240)
!679 = !DILocalVariable(name: "allocator", arg: 2, scope: !240, file: !1, line: 232, type: !46)
!680 = !DILocation(line: 232, column: 58, scope: !240)
!681 = !DILocalVariable(name: "filters", arg: 3, scope: !240, file: !1, line: 233, type: !106)
!682 = !DILocation(line: 233, column: 22, scope: !240)
!683 = !DILocalVariable(name: "reversed_filters", arg: 4, scope: !240, file: !1, line: 234, type: !106)
!684 = !DILocation(line: 234, column: 22, scope: !240)
!685 = !DILocalVariable(name: "i", scope: !240, file: !1, line: 236, type: !55)
!686 = !DILocation(line: 236, column: 9, scope: !240)
!687 = !DILocation(line: 238, column: 6, scope: !688)
!688 = distinct !DILexicalBlock(scope: !240, file: !1, line: 238, column: 6)
!689 = !DILocation(line: 238, column: 13, scope: !688)
!690 = !DILocation(line: 238, column: 22, scope: !688)
!691 = !DILocation(line: 238, column: 6, scope: !240)
!692 = !DILocalVariable(name: "ret", scope: !693, file: !1, line: 239, type: !45)
!693 = distinct !DILexicalBlock(scope: !688, file: !1, line: 238, column: 41)
!694 = !DILocation(line: 239, column: 12, scope: !693)
!695 = !DILocation(line: 245, column: 3, scope: !693)
!696 = !DILocation(line: 245, column: 10, scope: !693)
!697 = !DILocation(line: 245, column: 39, scope: !693)
!698 = !DILocation(line: 246, column: 50, scope: !693)
!699 = !DILocation(line: 246, column: 3, scope: !693)
!700 = !DILocation(line: 246, column: 10, scope: !693)
!701 = !DILocation(line: 246, column: 24, scope: !693)
!702 = !DILocation(line: 246, column: 32, scope: !693)
!703 = !DILocation(line: 247, column: 28, scope: !693)
!704 = !DILocation(line: 247, column: 35, scope: !693)
!705 = !DILocation(line: 247, column: 9, scope: !693)
!706 = !DILocation(line: 247, column: 7, scope: !693)
!707 = !DILocation(line: 248, column: 34, scope: !693)
!708 = !DILocation(line: 248, column: 41, scope: !693)
!709 = !DILocation(line: 248, column: 3, scope: !693)
!710 = !DILocation(line: 248, column: 10, scope: !693)
!711 = !DILocation(line: 248, column: 24, scope: !693)
!712 = !DILocation(line: 248, column: 32, scope: !693)
!713 = !DILocation(line: 249, column: 7, scope: !714)
!714 = distinct !DILexicalBlock(scope: !693, file: !1, line: 249, column: 7)
!715 = !DILocation(line: 249, column: 11, scope: !714)
!716 = !DILocation(line: 249, column: 7, scope: !693)
!717 = !DILocation(line: 250, column: 11, scope: !714)
!718 = !DILocation(line: 250, column: 4, scope: !714)
!719 = !DILocation(line: 252, column: 3, scope: !693)
!720 = !DILocation(line: 252, column: 10, scope: !693)
!721 = !DILocation(line: 252, column: 39, scope: !693)
!722 = !DILocation(line: 254, column: 2, scope: !693)
!723 = !DILocation(line: 254, column: 13, scope: !724)
!724 = !DILexicalBlockFile(scope: !725, file: !1, discriminator: 1)
!725 = distinct !DILexicalBlock(scope: !688, file: !1, line: 254, column: 13)
!726 = !DILocation(line: 254, column: 20, scope: !724)
!727 = !DILocation(line: 254, column: 29, scope: !724)
!728 = !DILocation(line: 257, column: 3, scope: !729)
!729 = distinct !DILexicalBlock(scope: !725, file: !1, line: 254, column: 50)
!730 = !DILocalVariable(name: "ret_", scope: !731, file: !1, line: 257, type: !378)
!731 = distinct !DILexicalBlock(scope: !729, file: !1, line: 257, column: 3)
!732 = !DILocation(line: 257, column: 3, scope: !731)
!733 = !DILocation(line: 257, column: 3, scope: !734)
!734 = !DILexicalBlockFile(scope: !731, file: !1, discriminator: 1)
!735 = !DILocation(line: 257, column: 3, scope: !736)
!736 = !DILexicalBlockFile(scope: !737, file: !1, discriminator: 2)
!737 = distinct !DILexicalBlock(scope: !731, file: !1, line: 257, column: 3)
!738 = !DILocation(line: 257, column: 3, scope: !739)
!739 = !DILexicalBlockFile(scope: !731, file: !1, discriminator: 3)
!740 = !DILocation(line: 260, column: 2, scope: !729)
!741 = !DILocation(line: 263, column: 3, scope: !742)
!742 = distinct !DILexicalBlock(scope: !725, file: !1, line: 260, column: 9)
!743 = !DILocation(line: 267, column: 9, scope: !744)
!744 = distinct !DILexicalBlock(scope: !240, file: !1, line: 267, column: 2)
!745 = !DILocation(line: 267, column: 7, scope: !744)
!746 = !DILocation(line: 267, column: 29, scope: !747)
!747 = !DILexicalBlockFile(scope: !748, file: !1, discriminator: 1)
!748 = distinct !DILexicalBlock(scope: !744, file: !1, line: 267, column: 2)
!749 = !DILocation(line: 267, column: 14, scope: !747)
!750 = !DILocation(line: 267, column: 21, scope: !747)
!751 = !DILocation(line: 267, column: 32, scope: !747)
!752 = !DILocation(line: 267, column: 35, scope: !747)
!753 = !DILocation(line: 267, column: 2, scope: !747)
!754 = !DILocation(line: 268, column: 28, scope: !748)
!755 = !DILocation(line: 268, column: 13, scope: !748)
!756 = !DILocation(line: 268, column: 20, scope: !748)
!757 = !DILocation(line: 268, column: 31, scope: !748)
!758 = !DILocation(line: 268, column: 40, scope: !748)
!759 = !DILocation(line: 268, column: 3, scope: !748)
!760 = !DILocation(line: 267, column: 56, scope: !761)
!761 = !DILexicalBlockFile(scope: !748, file: !1, discriminator: 2)
!762 = !DILocation(line: 267, column: 2, scope: !761)
!763 = !DILocation(line: 270, column: 27, scope: !240)
!764 = !DILocation(line: 270, column: 36, scope: !240)
!765 = !DILocation(line: 270, column: 43, scope: !240)
!766 = !DILocation(line: 270, column: 52, scope: !240)
!767 = !DILocation(line: 270, column: 9, scope: !240)
!768 = !DILocation(line: 270, column: 2, scope: !240)
!769 = !DILocation(line: 271, column: 1, scope: !240)
!770 = !DILocalVariable(name: "strm", arg: 1, scope: !208, file: !1, line: 327, type: !211)
!771 = !DILocation(line: 327, column: 34, scope: !208)
!772 = !DILocalVariable(name: "filters", arg: 2, scope: !208, file: !1, line: 328, type: !106)
!773 = !DILocation(line: 328, column: 22, scope: !208)
!774 = !DILocalVariable(name: "check", arg: 3, scope: !208, file: !1, line: 328, type: !87)
!775 = !DILocation(line: 328, column: 42, scope: !208)
!776 = !DILocation(line: 330, column: 2, scope: !208)
!777 = !DILocalVariable(name: "ret_", scope: !778, file: !1, line: 330, type: !45)
!778 = distinct !DILexicalBlock(scope: !208, file: !1, line: 330, column: 2)
!779 = !DILocation(line: 330, column: 2, scope: !778)
!780 = !DILocation(line: 330, column: 2, scope: !781)
!781 = !DILexicalBlockFile(scope: !778, file: !1, discriminator: 1)
!782 = !DILocalVariable(name: "ret_", scope: !783, file: !1, line: 330, type: !378)
!783 = distinct !DILexicalBlock(scope: !778, file: !1, line: 330, column: 2)
!784 = !DILocation(line: 330, column: 2, scope: !783)
!785 = !DILocation(line: 330, column: 2, scope: !786)
!786 = !DILexicalBlockFile(scope: !783, file: !1, discriminator: 2)
!787 = !DILocation(line: 330, column: 2, scope: !788)
!788 = !DILexicalBlockFile(scope: !789, file: !1, discriminator: 3)
!789 = distinct !DILexicalBlock(scope: !783, file: !1, line: 330, column: 2)
!790 = !DILocation(line: 330, column: 2, scope: !791)
!791 = !DILexicalBlockFile(scope: !783, file: !1, discriminator: 4)
!792 = !DILocation(line: 330, column: 2, scope: !793)
!793 = !DILexicalBlockFile(scope: !778, file: !1, discriminator: 5)
!794 = !DILocation(line: 330, column: 2, scope: !795)
!795 = !DILexicalBlockFile(scope: !796, file: !1, discriminator: 6)
!796 = distinct !DILexicalBlock(scope: !797, file: !1, line: 330, column: 2)
!797 = distinct !DILexicalBlock(scope: !778, file: !1, line: 330, column: 2)
!798 = !DILocation(line: 330, column: 2, scope: !799)
!799 = !DILexicalBlockFile(scope: !778, file: !1, discriminator: 7)
!800 = !DILocation(line: 332, column: 2, scope: !208)
!801 = !DILocation(line: 332, column: 8, scope: !208)
!802 = !DILocation(line: 332, column: 18, scope: !208)
!803 = !DILocation(line: 332, column: 46, scope: !208)
!804 = !DILocation(line: 333, column: 2, scope: !208)
!805 = !DILocation(line: 333, column: 8, scope: !208)
!806 = !DILocation(line: 333, column: 18, scope: !208)
!807 = !DILocation(line: 333, column: 53, scope: !208)
!808 = !DILocation(line: 334, column: 2, scope: !208)
!809 = !DILocation(line: 334, column: 8, scope: !208)
!810 = !DILocation(line: 334, column: 18, scope: !208)
!811 = !DILocation(line: 334, column: 53, scope: !208)
!812 = !DILocation(line: 335, column: 2, scope: !208)
!813 = !DILocation(line: 335, column: 8, scope: !208)
!814 = !DILocation(line: 335, column: 18, scope: !208)
!815 = !DILocation(line: 335, column: 49, scope: !208)
!816 = !DILocation(line: 337, column: 2, scope: !208)
!817 = !DILocation(line: 338, column: 1, scope: !208)
!818 = !DILocalVariable(name: "coder", arg: 1, scope: !236, file: !1, line: 63, type: !30)
!819 = !DILocation(line: 63, column: 32, scope: !236)
!820 = !DILocalVariable(name: "allocator", arg: 2, scope: !236, file: !1, line: 63, type: !46)
!821 = !DILocation(line: 63, column: 55, scope: !236)
!822 = !DILocation(line: 70, column: 2, scope: !236)
!823 = !DILocation(line: 70, column: 9, scope: !236)
!824 = !DILocation(line: 70, column: 23, scope: !236)
!825 = !DILocation(line: 70, column: 39, scope: !236)
!826 = !DILocation(line: 71, column: 2, scope: !236)
!827 = !DILocation(line: 71, column: 9, scope: !236)
!828 = !DILocation(line: 71, column: 23, scope: !236)
!829 = !DILocation(line: 71, column: 41, scope: !236)
!830 = !DILocation(line: 73, column: 2, scope: !236)
!831 = !DILocalVariable(name: "ret_", scope: !832, file: !1, line: 73, type: !378)
!832 = distinct !DILexicalBlock(scope: !236, file: !1, line: 73, column: 2)
!833 = !DILocation(line: 73, column: 2, scope: !832)
!834 = !DILocation(line: 73, column: 2, scope: !835)
!835 = !DILexicalBlockFile(scope: !832, file: !1, discriminator: 1)
!836 = !DILocation(line: 73, column: 2, scope: !837)
!837 = !DILexicalBlockFile(scope: !838, file: !1, discriminator: 2)
!838 = distinct !DILexicalBlock(scope: !832, file: !1, line: 73, column: 2)
!839 = !DILocation(line: 73, column: 2, scope: !840)
!840 = !DILexicalBlockFile(scope: !832, file: !1, discriminator: 3)
!841 = !DILocation(line: 76, column: 34, scope: !236)
!842 = !DILocation(line: 76, column: 41, scope: !236)
!843 = !DILocation(line: 76, column: 56, scope: !236)
!844 = !DILocation(line: 77, column: 5, scope: !236)
!845 = !DILocation(line: 77, column: 12, scope: !236)
!846 = !DILocation(line: 76, column: 9, scope: !236)
!847 = !DILocation(line: 76, column: 2, scope: !236)
!848 = !DILocation(line: 78, column: 1, scope: !236)
