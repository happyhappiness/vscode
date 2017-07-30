; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_decoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type { i32, %struct.lzma_next_coder_s, %struct.lzma_block, %struct.lzma_stream_flags, %struct.lzma_index_hash_s*, i64, i64, i8, i8, i8, i8, i8, i64, [1024 x i8] }
%struct.lzma_block = type { i32, i32, i32, i64, i64, %struct.lzma_filter*, [64 x i8], i8*, i8*, i8*, i32, i32, i64, i64, i64, i64, i64, i64, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8, i8, i8 }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_stream_flags = type { i32, i64, i32, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8, i8, i8, i32, i32 }
%struct.lzma_index_hash_s = type opaque
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_stream = type { i8*, i64, i64, i8*, i64, i64, %struct.lzma_allocator*, %struct.lzma_internal_s*, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i32, i32 }
%struct.lzma_internal_s = type { %struct.lzma_next_coder_s, i32, i64, [4 x i8], i8 }

@LZMA_NEXT_CODER_INIT = internal constant %struct.lzma_next_coder_s { %struct.lzma_coder_s* null, i64 -1, i64 0, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* null, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* null, i32 (%struct.lzma_coder_s*)* null, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* null, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* null }, align 8
@.str = private unnamed_addr constant [20 x i8] c"coder->concatenated\00", align 1
@.str.1 = private unnamed_addr constant [86 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_decoder.c\00", align 1
@__PRETTY_FUNCTION__.stream_decode = private unnamed_addr constant [164 x i8] c"lzma_ret stream_decode(lzma_coder *, lzma_allocator *, const uint8_t *restrict, size_t *restrict, size_t, uint8_t *restrict, size_t *restrict, size_t, lzma_action)\00", align 1
@.str.2 = private unnamed_addr constant [2 x i8] c"0\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_stream_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, i64 %memlimit, i32 %flags) #0 !dbg !225 {
entry:
  %retval = alloca i32, align 4
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %memlimit.addr = alloca i64, align 8
  %flags.addr = alloca i32, align 4
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !270, metadata !271), !dbg !272
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !273, metadata !271), !dbg !274
  store i64 %memlimit, i64* %memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %memlimit.addr, metadata !275, metadata !271), !dbg !276
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !277, metadata !271), !dbg !278
  br label %do.body, !dbg !279

do.body:                                          ; preds = %entry
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !280
  %init = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %0, i32 0, i32 2, !dbg !280
  %1 = load i64, i64* %init, align 8, !dbg !280
  %cmp = icmp ne i64 ptrtoint (i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, i64, i32)* @lzma_stream_decoder_init to i64), %1, !dbg !280
  br i1 %cmp, label %if.then, label %if.end, !dbg !280

if.then:                                          ; preds = %do.body
  %2 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !284
  %3 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !284
  call void @lzma_next_end(%struct.lzma_next_coder_s* %2, %struct.lzma_allocator* %3), !dbg !284
  br label %if.end, !dbg !284

if.end:                                           ; preds = %if.then, %do.body
  %4 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !286
  %init1 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %4, i32 0, i32 2, !dbg !286
  store i64 ptrtoint (i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, i64, i32)* @lzma_stream_decoder_init to i64), i64* %init1, align 8, !dbg !286
  br label %do.end, !dbg !286

do.end:                                           ; preds = %if.end
  %5 = load i64, i64* %memlimit.addr, align 8, !dbg !288
  %cmp2 = icmp eq i64 %5, 0, !dbg !290
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !291

if.then3:                                         ; preds = %do.end
  store i32 11, i32* %retval, align 4, !dbg !292
  br label %return, !dbg !292

if.end4:                                          ; preds = %do.end
  %6 = load i32, i32* %flags.addr, align 4, !dbg !293
  %and = and i32 %6, -16, !dbg !295
  %tobool = icmp ne i32 %and, 0, !dbg !295
  br i1 %tobool, label %if.then5, label %if.end6, !dbg !296

if.then5:                                         ; preds = %if.end4
  store i32 8, i32* %retval, align 4, !dbg !297
  br label %return, !dbg !297

if.end6:                                          ; preds = %if.end4
  %7 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !298
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %7, i32 0, i32 0, !dbg !300
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !300
  %cmp7 = icmp eq %struct.lzma_coder_s* %8, null, !dbg !301
  br i1 %cmp7, label %if.then8, label %if.end16, !dbg !302

if.then8:                                         ; preds = %if.end6
  %9 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !303
  %call = call noalias i8* @lzma_alloc(i64 1400, %struct.lzma_allocator* %9), !dbg !305
  %10 = bitcast i8* %call to %struct.lzma_coder_s*, !dbg !305
  %11 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !306
  %coder9 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %11, i32 0, i32 0, !dbg !307
  store %struct.lzma_coder_s* %10, %struct.lzma_coder_s** %coder9, align 8, !dbg !308
  %12 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !309
  %coder10 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %12, i32 0, i32 0, !dbg !311
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder10, align 8, !dbg !311
  %cmp11 = icmp eq %struct.lzma_coder_s* %13, null, !dbg !312
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !313

if.then12:                                        ; preds = %if.then8
  store i32 5, i32* %retval, align 4, !dbg !314
  br label %return, !dbg !314

if.end13:                                         ; preds = %if.then8
  %14 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !315
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %14, i32 0, i32 3, !dbg !316
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* @stream_decode, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !317
  %15 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !318
  %end = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %15, i32 0, i32 4, !dbg !319
  store void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* @stream_decoder_end, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !320
  %16 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !321
  %get_check = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %16, i32 0, i32 5, !dbg !322
  store i32 (%struct.lzma_coder_s*)* @stream_decoder_get_check, i32 (%struct.lzma_coder_s*)** %get_check, align 8, !dbg !323
  %17 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !324
  %memconfig = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %17, i32 0, i32 6, !dbg !325
  store i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* @stream_decoder_memconfig, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)** %memconfig, align 8, !dbg !326
  %18 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !327
  %coder14 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %18, i32 0, i32 0, !dbg !328
  %19 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder14, align 8, !dbg !328
  %block_decoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %19, i32 0, i32 1, !dbg !329
  %20 = bitcast %struct.lzma_next_coder_s* %block_decoder to i8*, !dbg !330
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %20, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !330
  %21 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !331
  %coder15 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %21, i32 0, i32 0, !dbg !332
  %22 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder15, align 8, !dbg !332
  %index_hash = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %22, i32 0, i32 4, !dbg !333
  store %struct.lzma_index_hash_s* null, %struct.lzma_index_hash_s** %index_hash, align 8, !dbg !334
  br label %if.end16, !dbg !335

if.end16:                                         ; preds = %if.end13, %if.end6
  %23 = load i64, i64* %memlimit.addr, align 8, !dbg !336
  %24 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !337
  %coder17 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %24, i32 0, i32 0, !dbg !338
  %25 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder17, align 8, !dbg !338
  %memlimit18 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %25, i32 0, i32 5, !dbg !339
  store i64 %23, i64* %memlimit18, align 8, !dbg !340
  %26 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !341
  %coder19 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %26, i32 0, i32 0, !dbg !342
  %27 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder19, align 8, !dbg !342
  %memusage = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %27, i32 0, i32 6, !dbg !343
  store i64 32768, i64* %memusage, align 8, !dbg !344
  %28 = load i32, i32* %flags.addr, align 4, !dbg !345
  %and20 = and i32 %28, 1, !dbg !346
  %cmp21 = icmp ne i32 %and20, 0, !dbg !347
  %29 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !348
  %coder22 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %29, i32 0, i32 0, !dbg !349
  %30 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder22, align 8, !dbg !349
  %tell_no_check = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %30, i32 0, i32 7, !dbg !350
  %frombool = zext i1 %cmp21 to i8, !dbg !351
  store i8 %frombool, i8* %tell_no_check, align 8, !dbg !351
  %31 = load i32, i32* %flags.addr, align 4, !dbg !352
  %and23 = and i32 %31, 2, !dbg !353
  %cmp24 = icmp ne i32 %and23, 0, !dbg !354
  %32 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !355
  %coder25 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %32, i32 0, i32 0, !dbg !356
  %33 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder25, align 8, !dbg !356
  %tell_unsupported_check = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %33, i32 0, i32 8, !dbg !357
  %frombool26 = zext i1 %cmp24 to i8, !dbg !358
  store i8 %frombool26, i8* %tell_unsupported_check, align 1, !dbg !358
  %34 = load i32, i32* %flags.addr, align 4, !dbg !359
  %and27 = and i32 %34, 4, !dbg !360
  %cmp28 = icmp ne i32 %and27, 0, !dbg !361
  %35 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !362
  %coder29 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %35, i32 0, i32 0, !dbg !363
  %36 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder29, align 8, !dbg !363
  %tell_any_check = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %36, i32 0, i32 9, !dbg !364
  %frombool30 = zext i1 %cmp28 to i8, !dbg !365
  store i8 %frombool30, i8* %tell_any_check, align 2, !dbg !365
  %37 = load i32, i32* %flags.addr, align 4, !dbg !366
  %and31 = and i32 %37, 8, !dbg !367
  %cmp32 = icmp ne i32 %and31, 0, !dbg !368
  %38 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !369
  %coder33 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %38, i32 0, i32 0, !dbg !370
  %39 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder33, align 8, !dbg !370
  %concatenated = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %39, i32 0, i32 10, !dbg !371
  %frombool34 = zext i1 %cmp32 to i8, !dbg !372
  store i8 %frombool34, i8* %concatenated, align 1, !dbg !372
  %40 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !373
  %coder35 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %40, i32 0, i32 0, !dbg !374
  %41 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder35, align 8, !dbg !374
  %first_stream = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %41, i32 0, i32 11, !dbg !375
  store i8 1, i8* %first_stream, align 4, !dbg !376
  %42 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !377
  %coder36 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %42, i32 0, i32 0, !dbg !378
  %43 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder36, align 8, !dbg !378
  %44 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !379
  %call37 = call i32 @stream_decoder_reset(%struct.lzma_coder_s* %43, %struct.lzma_allocator* %44), !dbg !380
  store i32 %call37, i32* %retval, align 4, !dbg !381
  br label %return, !dbg !381

return:                                           ; preds = %if.end16, %if.then12, %if.then5, %if.then3
  %45 = load i32, i32* %retval, align 4, !dbg !382
  ret i32 %45, !dbg !382
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @lzma_next_end(%struct.lzma_next_coder_s*, %struct.lzma_allocator*) #2

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #2

; Function Attrs: nounwind uwtable
define internal i32 @stream_decode(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, i8* noalias %in, i64* noalias %in_pos, i64 %in_size, i8* noalias %out, i64* noalias %out_pos, i64 %out_size, i32 %action) #0 !dbg !257 {
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
  %ret = alloca i32, align 4
  %filters = alloca [5 x %struct.lzma_filter], align 16
  %memusage = alloca i64, align 8
  %ret33 = alloca i32, align 4
  %i = alloca i64, align 8
  %ret_ = alloca i32, align 4
  %ret102 = alloca i32, align 4
  %ret_112 = alloca i32, align 4
  %ret124 = alloca i32, align 4
  %footer_flags = alloca %struct.lzma_stream_flags, align 8
  %ret137 = alloca i32, align 4
  %ret_168 = alloca i32, align 4
  %ret_218 = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !383, metadata !271), !dbg !384
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !385, metadata !271), !dbg !386
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !387, metadata !271), !dbg !388
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !389, metadata !271), !dbg !390
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !391, metadata !271), !dbg !392
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !393, metadata !271), !dbg !394
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !395, metadata !271), !dbg !396
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !397, metadata !271), !dbg !398
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !399, metadata !271), !dbg !400
  br label %while.body, !dbg !401

while.body:                                       ; preds = %entry, %sw.epilog
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !402
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 0, !dbg !403
  %1 = load i32, i32* %sequence, align 8, !dbg !403
  switch i32 %1, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb32
    i32 2, label %sw.bb101
    i32 3, label %sw.bb123
    i32 4, label %sw.bb136
    i32 5, label %sw.bb180
  ], !dbg !404

sw.bb:                                            ; preds = %while.body
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !405, metadata !271), !dbg !408
  %2 = load i8*, i8** %in.addr, align 8, !dbg !409
  %3 = load i64*, i64** %in_pos.addr, align 8, !dbg !410
  %4 = load i64, i64* %in_size.addr, align 8, !dbg !411
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !412
  %buffer = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 13, !dbg !413
  %arraydecay = getelementptr inbounds [1024 x i8], [1024 x i8]* %buffer, i32 0, i32 0, !dbg !412
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !414
  %pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %6, i32 0, i32 12, !dbg !415
  %call = call i64 @lzma_bufcpy(i8* %2, i64* %3, i64 %4, i8* %arraydecay, i64* %pos, i64 12), !dbg !416
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !417
  %pos1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 12, !dbg !419
  %8 = load i64, i64* %pos1, align 8, !dbg !419
  %cmp = icmp ult i64 %8, 12, !dbg !420
  br i1 %cmp, label %if.then, label %if.end, !dbg !421

if.then:                                          ; preds = %sw.bb
  store i32 0, i32* %retval, align 4, !dbg !422
  br label %return, !dbg !422

if.end:                                           ; preds = %sw.bb
  %9 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !423
  %pos2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %9, i32 0, i32 12, !dbg !424
  store i64 0, i64* %pos2, align 8, !dbg !425
  %10 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !426
  %stream_flags = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %10, i32 0, i32 3, !dbg !427
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !428
  %buffer3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 13, !dbg !429
  %arraydecay4 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buffer3, i32 0, i32 0, !dbg !428
  %call5 = call i32 @lzma_stream_header_decode(%struct.lzma_stream_flags* %stream_flags, i8* %arraydecay4) #8, !dbg !430
  store i32 %call5, i32* %ret, align 4, !dbg !431
  %12 = load i32, i32* %ret, align 4, !dbg !432
  %cmp6 = icmp ne i32 %12, 0, !dbg !434
  br i1 %cmp6, label %if.then7, label %if.end9, !dbg !435

if.then7:                                         ; preds = %if.end
  %13 = load i32, i32* %ret, align 4, !dbg !436
  %cmp8 = icmp eq i32 %13, 7, !dbg !437
  br i1 %cmp8, label %land.lhs.true, label %cond.false, !dbg !438

land.lhs.true:                                    ; preds = %if.then7
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !439
  %first_stream = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 11, !dbg !441
  %15 = load i8, i8* %first_stream, align 4, !dbg !441
  %tobool = trunc i8 %15 to i1, !dbg !441
  br i1 %tobool, label %cond.false, label %cond.true, !dbg !442

cond.true:                                        ; preds = %land.lhs.true
  br label %cond.end, !dbg !443

cond.false:                                       ; preds = %land.lhs.true, %if.then7
  %16 = load i32, i32* %ret, align 4, !dbg !445
  br label %cond.end, !dbg !446

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ 9, %cond.true ], [ %16, %cond.false ], !dbg !448
  store i32 %cond, i32* %retval, align 4, !dbg !450
  br label %return, !dbg !450

if.end9:                                          ; preds = %if.end
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !451
  %first_stream10 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %17, i32 0, i32 11, !dbg !452
  store i8 0, i8* %first_stream10, align 4, !dbg !453
  %18 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !454
  %stream_flags11 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %18, i32 0, i32 3, !dbg !455
  %check = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags11, i32 0, i32 2, !dbg !456
  %19 = load i32, i32* %check, align 8, !dbg !456
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !457
  %block_options = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %20, i32 0, i32 2, !dbg !458
  %check12 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block_options, i32 0, i32 2, !dbg !459
  store i32 %19, i32* %check12, align 8, !dbg !460
  %21 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !461
  %sequence13 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %21, i32 0, i32 0, !dbg !462
  store i32 1, i32* %sequence13, align 8, !dbg !463
  %22 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !464
  %tell_no_check = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %22, i32 0, i32 7, !dbg !466
  %23 = load i8, i8* %tell_no_check, align 8, !dbg !466
  %tobool14 = trunc i8 %23 to i1, !dbg !466
  br i1 %tobool14, label %land.lhs.true15, label %if.end20, !dbg !467

land.lhs.true15:                                  ; preds = %if.end9
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !468
  %stream_flags16 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %24, i32 0, i32 3, !dbg !470
  %check17 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags16, i32 0, i32 2, !dbg !471
  %25 = load i32, i32* %check17, align 8, !dbg !471
  %cmp18 = icmp eq i32 %25, 0, !dbg !472
  br i1 %cmp18, label %if.then19, label %if.end20, !dbg !473

if.then19:                                        ; preds = %land.lhs.true15
  store i32 2, i32* %retval, align 4, !dbg !474
  br label %return, !dbg !474

if.end20:                                         ; preds = %land.lhs.true15, %if.end9
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !475
  %tell_unsupported_check = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %26, i32 0, i32 8, !dbg !477
  %27 = load i8, i8* %tell_unsupported_check, align 1, !dbg !477
  %tobool21 = trunc i8 %27 to i1, !dbg !477
  br i1 %tobool21, label %land.lhs.true22, label %if.end28, !dbg !478

land.lhs.true22:                                  ; preds = %if.end20
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !479
  %stream_flags23 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %28, i32 0, i32 3, !dbg !480
  %check24 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags23, i32 0, i32 2, !dbg !481
  %29 = load i32, i32* %check24, align 8, !dbg !481
  %call25 = call zeroext i8 @lzma_check_is_supported(i32 %29) #1, !dbg !482
  %tobool26 = icmp ne i8 %call25, 0, !dbg !482
  br i1 %tobool26, label %if.end28, label %if.then27, !dbg !484

if.then27:                                        ; preds = %land.lhs.true22
  store i32 3, i32* %retval, align 4, !dbg !486
  br label %return, !dbg !486

if.end28:                                         ; preds = %land.lhs.true22, %if.end20
  %30 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !487
  %tell_any_check = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %30, i32 0, i32 9, !dbg !489
  %31 = load i8, i8* %tell_any_check, align 2, !dbg !489
  %tobool29 = trunc i8 %31 to i1, !dbg !489
  br i1 %tobool29, label %if.then30, label %if.end31, !dbg !490

if.then30:                                        ; preds = %if.end28
  store i32 4, i32* %retval, align 4, !dbg !491
  br label %return, !dbg !491

if.end31:                                         ; preds = %if.end28
  br label %sw.bb32, !dbg !492

sw.bb32:                                          ; preds = %while.body, %if.end31
  call void @llvm.dbg.declare(metadata [5 x %struct.lzma_filter]* %filters, metadata !493, metadata !271), !dbg !498
  call void @llvm.dbg.declare(metadata i64* %memusage, metadata !499, metadata !271), !dbg !500
  call void @llvm.dbg.declare(metadata i32* %ret33, metadata !501, metadata !271), !dbg !502
  call void @llvm.dbg.declare(metadata i64* %i, metadata !503, metadata !271), !dbg !504
  %32 = load i64*, i64** %in_pos.addr, align 8, !dbg !505
  %33 = load i64, i64* %32, align 8, !dbg !507
  %34 = load i64, i64* %in_size.addr, align 8, !dbg !508
  %cmp34 = icmp uge i64 %33, %34, !dbg !509
  br i1 %cmp34, label %if.then35, label %if.end36, !dbg !510

if.then35:                                        ; preds = %sw.bb32
  store i32 0, i32* %retval, align 4, !dbg !511
  br label %return, !dbg !511

if.end36:                                         ; preds = %sw.bb32
  %35 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !512
  %pos37 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %35, i32 0, i32 12, !dbg !514
  %36 = load i64, i64* %pos37, align 8, !dbg !514
  %cmp38 = icmp eq i64 %36, 0, !dbg !515
  br i1 %cmp38, label %if.then39, label %if.end48, !dbg !516

if.then39:                                        ; preds = %if.end36
  %37 = load i64*, i64** %in_pos.addr, align 8, !dbg !517
  %38 = load i64, i64* %37, align 8, !dbg !520
  %39 = load i8*, i8** %in.addr, align 8, !dbg !521
  %arrayidx = getelementptr inbounds i8, i8* %39, i64 %38, !dbg !521
  %40 = load i8, i8* %arrayidx, align 1, !dbg !521
  %conv = zext i8 %40 to i32, !dbg !521
  %cmp40 = icmp eq i32 %conv, 0, !dbg !522
  br i1 %cmp40, label %if.then42, label %if.end44, !dbg !523

if.then42:                                        ; preds = %if.then39
  %41 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !524
  %sequence43 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %41, i32 0, i32 0, !dbg !526
  store i32 3, i32* %sequence43, align 8, !dbg !527
  br label %sw.epilog, !dbg !528

if.end44:                                         ; preds = %if.then39
  %42 = load i64*, i64** %in_pos.addr, align 8, !dbg !529
  %43 = load i64, i64* %42, align 8, !dbg !529
  %44 = load i8*, i8** %in.addr, align 8, !dbg !529
  %arrayidx45 = getelementptr inbounds i8, i8* %44, i64 %43, !dbg !529
  %45 = load i8, i8* %arrayidx45, align 1, !dbg !529
  %conv46 = zext i8 %45 to i32, !dbg !529
  %add = add i32 %conv46, 1, !dbg !529
  %mul = mul i32 %add, 4, !dbg !529
  %46 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !530
  %block_options47 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %46, i32 0, i32 2, !dbg !531
  %header_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block_options47, i32 0, i32 1, !dbg !532
  store i32 %mul, i32* %header_size, align 4, !dbg !533
  br label %if.end48, !dbg !534

if.end48:                                         ; preds = %if.end44, %if.end36
  %47 = load i8*, i8** %in.addr, align 8, !dbg !535
  %48 = load i64*, i64** %in_pos.addr, align 8, !dbg !536
  %49 = load i64, i64* %in_size.addr, align 8, !dbg !537
  %50 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !538
  %buffer49 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %50, i32 0, i32 13, !dbg !539
  %arraydecay50 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buffer49, i32 0, i32 0, !dbg !538
  %51 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !540
  %pos51 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %51, i32 0, i32 12, !dbg !541
  %52 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !542
  %block_options52 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %52, i32 0, i32 2, !dbg !543
  %header_size53 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block_options52, i32 0, i32 1, !dbg !544
  %53 = load i32, i32* %header_size53, align 4, !dbg !544
  %conv54 = zext i32 %53 to i64, !dbg !542
  %call55 = call i64 @lzma_bufcpy(i8* %47, i64* %48, i64 %49, i8* %arraydecay50, i64* %pos51, i64 %conv54), !dbg !545
  %54 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !546
  %pos56 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %54, i32 0, i32 12, !dbg !548
  %55 = load i64, i64* %pos56, align 8, !dbg !548
  %56 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !549
  %block_options57 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %56, i32 0, i32 2, !dbg !550
  %header_size58 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block_options57, i32 0, i32 1, !dbg !551
  %57 = load i32, i32* %header_size58, align 4, !dbg !551
  %conv59 = zext i32 %57 to i64, !dbg !549
  %cmp60 = icmp ult i64 %55, %conv59, !dbg !552
  br i1 %cmp60, label %if.then62, label %if.end63, !dbg !553

if.then62:                                        ; preds = %if.end48
  store i32 0, i32* %retval, align 4, !dbg !554
  br label %return, !dbg !554

if.end63:                                         ; preds = %if.end48
  %58 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !555
  %pos64 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %58, i32 0, i32 12, !dbg !556
  store i64 0, i64* %pos64, align 8, !dbg !557
  %59 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !558
  %block_options65 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %59, i32 0, i32 2, !dbg !559
  %version = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block_options65, i32 0, i32 0, !dbg !560
  store i32 0, i32* %version, align 8, !dbg !561
  %arraydecay66 = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %filters, i32 0, i32 0, !dbg !562
  %60 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !563
  %block_options67 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %60, i32 0, i32 2, !dbg !564
  %filters68 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block_options67, i32 0, i32 5, !dbg !565
  store %struct.lzma_filter* %arraydecay66, %struct.lzma_filter** %filters68, align 8, !dbg !566
  br label %do.body, !dbg !567

do.body:                                          ; preds = %if.end63
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !568, metadata !271), !dbg !571
  %61 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !572
  %block_options69 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %61, i32 0, i32 2, !dbg !572
  %62 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !572
  %63 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !572
  %buffer70 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %63, i32 0, i32 13, !dbg !572
  %arraydecay71 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buffer70, i32 0, i32 0, !dbg !572
  %call72 = call i32 @lzma_block_header_decode(%struct.lzma_block* %block_options69, %struct.lzma_allocator* %62, i8* %arraydecay71) #8, !dbg !572
  store i32 %call72, i32* %ret_, align 4, !dbg !572
  %64 = load i32, i32* %ret_, align 4, !dbg !572
  %cmp73 = icmp ne i32 %64, 0, !dbg !572
  br i1 %cmp73, label %if.then75, label %if.end76, !dbg !572

if.then75:                                        ; preds = %do.body
  %65 = load i32, i32* %ret_, align 4, !dbg !574
  store i32 %65, i32* %retval, align 4, !dbg !574
  br label %return, !dbg !574

if.end76:                                         ; preds = %do.body
  br label %do.end, !dbg !577

do.end:                                           ; preds = %if.end76
  %arraydecay77 = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %filters, i32 0, i32 0, !dbg !579
  %call78 = call i64 @lzma_raw_decoder_memusage(%struct.lzma_filter* %arraydecay77) #9, !dbg !580
  store i64 %call78, i64* %memusage, align 8, !dbg !581
  %66 = load i64, i64* %memusage, align 8, !dbg !582
  %cmp79 = icmp eq i64 %66, -1, !dbg !584
  br i1 %cmp79, label %if.then81, label %if.else, !dbg !585

if.then81:                                        ; preds = %do.end
  store i32 8, i32* %ret33, align 4, !dbg !586
  br label %if.end90, !dbg !588

if.else:                                          ; preds = %do.end
  %67 = load i64, i64* %memusage, align 8, !dbg !589
  %68 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !591
  %memusage82 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %68, i32 0, i32 6, !dbg !592
  store i64 %67, i64* %memusage82, align 8, !dbg !593
  %69 = load i64, i64* %memusage, align 8, !dbg !594
  %70 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !596
  %memlimit = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %70, i32 0, i32 5, !dbg !597
  %71 = load i64, i64* %memlimit, align 8, !dbg !597
  %cmp83 = icmp ugt i64 %69, %71, !dbg !598
  br i1 %cmp83, label %if.then85, label %if.else86, !dbg !599

if.then85:                                        ; preds = %if.else
  store i32 6, i32* %ret33, align 4, !dbg !600
  br label %if.end89, !dbg !602

if.else86:                                        ; preds = %if.else
  %72 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !603
  %block_decoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %72, i32 0, i32 1, !dbg !605
  %73 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !606
  %74 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !607
  %block_options87 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %74, i32 0, i32 2, !dbg !608
  %call88 = call i32 @lzma_block_decoder_init(%struct.lzma_next_coder_s* %block_decoder, %struct.lzma_allocator* %73, %struct.lzma_block* %block_options87), !dbg !609
  store i32 %call88, i32* %ret33, align 4, !dbg !610
  br label %if.end89

if.end89:                                         ; preds = %if.else86, %if.then85
  br label %if.end90

if.end90:                                         ; preds = %if.end89, %if.then81
  store i64 0, i64* %i, align 8, !dbg !611
  br label %for.cond, !dbg !613

for.cond:                                         ; preds = %for.inc, %if.end90
  %75 = load i64, i64* %i, align 8, !dbg !614
  %cmp91 = icmp ult i64 %75, 4, !dbg !617
  br i1 %cmp91, label %for.body, label %for.end, !dbg !618

for.body:                                         ; preds = %for.cond
  %76 = load i64, i64* %i, align 8, !dbg !619
  %arrayidx93 = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %filters, i64 0, i64 %76, !dbg !620
  %options = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx93, i32 0, i32 1, !dbg !621
  %77 = load i8*, i8** %options, align 8, !dbg !621
  %78 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !622
  call void @lzma_free(i8* %77, %struct.lzma_allocator* %78), !dbg !623
  br label %for.inc, !dbg !623

for.inc:                                          ; preds = %for.body
  %79 = load i64, i64* %i, align 8, !dbg !624
  %inc = add i64 %79, 1, !dbg !624
  store i64 %inc, i64* %i, align 8, !dbg !624
  br label %for.cond, !dbg !626

for.end:                                          ; preds = %for.cond
  %80 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !627
  %block_options94 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %80, i32 0, i32 2, !dbg !628
  %filters95 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block_options94, i32 0, i32 5, !dbg !629
  store %struct.lzma_filter* null, %struct.lzma_filter** %filters95, align 8, !dbg !630
  %81 = load i32, i32* %ret33, align 4, !dbg !631
  %cmp96 = icmp ne i32 %81, 0, !dbg !633
  br i1 %cmp96, label %if.then98, label %if.end99, !dbg !634

if.then98:                                        ; preds = %for.end
  %82 = load i32, i32* %ret33, align 4, !dbg !635
  store i32 %82, i32* %retval, align 4, !dbg !636
  br label %return, !dbg !636

if.end99:                                         ; preds = %for.end
  %83 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !637
  %sequence100 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %83, i32 0, i32 0, !dbg !638
  store i32 2, i32* %sequence100, align 8, !dbg !639
  br label %sw.bb101, !dbg !640

sw.bb101:                                         ; preds = %while.body, %if.end99
  call void @llvm.dbg.declare(metadata i32* %ret102, metadata !641, metadata !271), !dbg !643
  %84 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !644
  %block_decoder103 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %84, i32 0, i32 1, !dbg !645
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %block_decoder103, i32 0, i32 3, !dbg !646
  %85 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !646
  %86 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !647
  %block_decoder104 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %86, i32 0, i32 1, !dbg !648
  %coder105 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %block_decoder104, i32 0, i32 0, !dbg !649
  %87 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder105, align 8, !dbg !649
  %88 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !650
  %89 = load i8*, i8** %in.addr, align 8, !dbg !651
  %90 = load i64*, i64** %in_pos.addr, align 8, !dbg !652
  %91 = load i64, i64* %in_size.addr, align 8, !dbg !653
  %92 = load i8*, i8** %out.addr, align 8, !dbg !654
  %93 = load i64*, i64** %out_pos.addr, align 8, !dbg !655
  %94 = load i64, i64* %out_size.addr, align 8, !dbg !656
  %95 = load i32, i32* %action.addr, align 4, !dbg !657
  %call106 = call i32 %85(%struct.lzma_coder_s* %87, %struct.lzma_allocator* %88, i8* %89, i64* %90, i64 %91, i8* %92, i64* %93, i64 %94, i32 %95), !dbg !644
  store i32 %call106, i32* %ret102, align 4, !dbg !643
  %96 = load i32, i32* %ret102, align 4, !dbg !658
  %cmp107 = icmp ne i32 %96, 1, !dbg !660
  br i1 %cmp107, label %if.then109, label %if.end110, !dbg !661

if.then109:                                       ; preds = %sw.bb101
  %97 = load i32, i32* %ret102, align 4, !dbg !662
  store i32 %97, i32* %retval, align 4, !dbg !663
  br label %return, !dbg !663

if.end110:                                        ; preds = %sw.bb101
  br label %do.body111, !dbg !664

do.body111:                                       ; preds = %if.end110
  call void @llvm.dbg.declare(metadata i32* %ret_112, metadata !665, metadata !271), !dbg !667
  %98 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !668
  %index_hash = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %98, i32 0, i32 4, !dbg !668
  %99 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash, align 8, !dbg !668
  %100 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !668
  %block_options113 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %100, i32 0, i32 2, !dbg !668
  %call114 = call i64 @lzma_block_unpadded_size(%struct.lzma_block* %block_options113) #9, !dbg !668
  %101 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !668
  %block_options115 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %101, i32 0, i32 2, !dbg !668
  %uncompressed_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block_options115, i32 0, i32 4, !dbg !668
  %102 = load i64, i64* %uncompressed_size, align 8, !dbg !668
  %call116 = call i32 @lzma_index_hash_append(%struct.lzma_index_hash_s* %99, i64 %call114, i64 %102) #8, !dbg !670
  store i32 %call116, i32* %ret_112, align 4, !dbg !668
  %103 = load i32, i32* %ret_112, align 4, !dbg !668
  %cmp117 = icmp ne i32 %103, 0, !dbg !668
  br i1 %cmp117, label %if.then119, label %if.end120, !dbg !668

if.then119:                                       ; preds = %do.body111
  %104 = load i32, i32* %ret_112, align 4, !dbg !672
  store i32 %104, i32* %retval, align 4, !dbg !672
  br label %return, !dbg !672

if.end120:                                        ; preds = %do.body111
  br label %do.end121, !dbg !675

do.end121:                                        ; preds = %if.end120
  %105 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !677
  %sequence122 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %105, i32 0, i32 0, !dbg !678
  store i32 1, i32* %sequence122, align 8, !dbg !679
  br label %sw.epilog, !dbg !680

sw.bb123:                                         ; preds = %while.body
  call void @llvm.dbg.declare(metadata i32* %ret124, metadata !681, metadata !271), !dbg !683
  %106 = load i64*, i64** %in_pos.addr, align 8, !dbg !684
  %107 = load i64, i64* %106, align 8, !dbg !686
  %108 = load i64, i64* %in_size.addr, align 8, !dbg !687
  %cmp125 = icmp uge i64 %107, %108, !dbg !688
  br i1 %cmp125, label %if.then127, label %if.end128, !dbg !689

if.then127:                                       ; preds = %sw.bb123
  store i32 0, i32* %retval, align 4, !dbg !690
  br label %return, !dbg !690

if.end128:                                        ; preds = %sw.bb123
  %109 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !691
  %index_hash129 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %109, i32 0, i32 4, !dbg !692
  %110 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash129, align 8, !dbg !692
  %111 = load i8*, i8** %in.addr, align 8, !dbg !693
  %112 = load i64*, i64** %in_pos.addr, align 8, !dbg !694
  %113 = load i64, i64* %in_size.addr, align 8, !dbg !695
  %call130 = call i32 @lzma_index_hash_decode(%struct.lzma_index_hash_s* %110, i8* %111, i64* %112, i64 %113) #8, !dbg !696
  store i32 %call130, i32* %ret124, align 4, !dbg !697
  %114 = load i32, i32* %ret124, align 4, !dbg !698
  %cmp131 = icmp ne i32 %114, 1, !dbg !700
  br i1 %cmp131, label %if.then133, label %if.end134, !dbg !701

if.then133:                                       ; preds = %if.end128
  %115 = load i32, i32* %ret124, align 4, !dbg !702
  store i32 %115, i32* %retval, align 4, !dbg !703
  br label %return, !dbg !703

if.end134:                                        ; preds = %if.end128
  %116 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !704
  %sequence135 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %116, i32 0, i32 0, !dbg !705
  store i32 4, i32* %sequence135, align 8, !dbg !706
  br label %sw.bb136, !dbg !707

sw.bb136:                                         ; preds = %while.body, %if.end134
  call void @llvm.dbg.declare(metadata %struct.lzma_stream_flags* %footer_flags, metadata !708, metadata !271), !dbg !710
  call void @llvm.dbg.declare(metadata i32* %ret137, metadata !711, metadata !271), !dbg !712
  %117 = load i8*, i8** %in.addr, align 8, !dbg !713
  %118 = load i64*, i64** %in_pos.addr, align 8, !dbg !714
  %119 = load i64, i64* %in_size.addr, align 8, !dbg !715
  %120 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !716
  %buffer138 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %120, i32 0, i32 13, !dbg !717
  %arraydecay139 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buffer138, i32 0, i32 0, !dbg !716
  %121 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !718
  %pos140 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %121, i32 0, i32 12, !dbg !719
  %call141 = call i64 @lzma_bufcpy(i8* %117, i64* %118, i64 %119, i8* %arraydecay139, i64* %pos140, i64 12), !dbg !720
  %122 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !721
  %pos142 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %122, i32 0, i32 12, !dbg !723
  %123 = load i64, i64* %pos142, align 8, !dbg !723
  %cmp143 = icmp ult i64 %123, 12, !dbg !724
  br i1 %cmp143, label %if.then145, label %if.end146, !dbg !725

if.then145:                                       ; preds = %sw.bb136
  store i32 0, i32* %retval, align 4, !dbg !726
  br label %return, !dbg !726

if.end146:                                        ; preds = %sw.bb136
  %124 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !727
  %pos147 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %124, i32 0, i32 12, !dbg !728
  store i64 0, i64* %pos147, align 8, !dbg !729
  %125 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !730
  %buffer148 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %125, i32 0, i32 13, !dbg !731
  %arraydecay149 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buffer148, i32 0, i32 0, !dbg !730
  %call150 = call i32 @lzma_stream_footer_decode(%struct.lzma_stream_flags* %footer_flags, i8* %arraydecay149) #8, !dbg !732
  store i32 %call150, i32* %ret137, align 4, !dbg !733
  %126 = load i32, i32* %ret137, align 4, !dbg !734
  %cmp151 = icmp ne i32 %126, 0, !dbg !736
  br i1 %cmp151, label %if.then153, label %if.end160, !dbg !737

if.then153:                                       ; preds = %if.end146
  %127 = load i32, i32* %ret137, align 4, !dbg !738
  %cmp154 = icmp eq i32 %127, 7, !dbg !739
  br i1 %cmp154, label %cond.true156, label %cond.false157, !dbg !738

cond.true156:                                     ; preds = %if.then153
  br label %cond.end158, !dbg !740

cond.false157:                                    ; preds = %if.then153
  %128 = load i32, i32* %ret137, align 4, !dbg !742
  br label %cond.end158, !dbg !743

cond.end158:                                      ; preds = %cond.false157, %cond.true156
  %cond159 = phi i32 [ 9, %cond.true156 ], [ %128, %cond.false157 ], !dbg !745
  store i32 %cond159, i32* %retval, align 4, !dbg !747
  br label %return, !dbg !747

if.end160:                                        ; preds = %if.end146
  %129 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !748
  %index_hash161 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %129, i32 0, i32 4, !dbg !750
  %130 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash161, align 8, !dbg !750
  %call162 = call i64 @lzma_index_hash_size(%struct.lzma_index_hash_s* %130) #9, !dbg !751
  %backward_size = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %footer_flags, i32 0, i32 1, !dbg !752
  %131 = load i64, i64* %backward_size, align 8, !dbg !752
  %cmp163 = icmp ne i64 %call162, %131, !dbg !753
  br i1 %cmp163, label %if.then165, label %if.end166, !dbg !754

if.then165:                                       ; preds = %if.end160
  store i32 9, i32* %retval, align 4, !dbg !755
  br label %return, !dbg !755

if.end166:                                        ; preds = %if.end160
  br label %do.body167, !dbg !756

do.body167:                                       ; preds = %if.end166
  call void @llvm.dbg.declare(metadata i32* %ret_168, metadata !757, metadata !271), !dbg !759
  %132 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !760
  %stream_flags169 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %132, i32 0, i32 3, !dbg !760
  %call170 = call i32 @lzma_stream_flags_compare(%struct.lzma_stream_flags* %stream_flags169, %struct.lzma_stream_flags* %footer_flags) #9, !dbg !760
  store i32 %call170, i32* %ret_168, align 4, !dbg !760
  %133 = load i32, i32* %ret_168, align 4, !dbg !760
  %cmp171 = icmp ne i32 %133, 0, !dbg !760
  br i1 %cmp171, label %if.then173, label %if.end174, !dbg !760

if.then173:                                       ; preds = %do.body167
  %134 = load i32, i32* %ret_168, align 4, !dbg !762
  store i32 %134, i32* %retval, align 4, !dbg !762
  br label %return, !dbg !762

if.end174:                                        ; preds = %do.body167
  br label %do.end175, !dbg !765

do.end175:                                        ; preds = %if.end174
  %135 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !767
  %concatenated = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %135, i32 0, i32 10, !dbg !769
  %136 = load i8, i8* %concatenated, align 1, !dbg !769
  %tobool176 = trunc i8 %136 to i1, !dbg !769
  br i1 %tobool176, label %if.end178, label %if.then177, !dbg !770

if.then177:                                       ; preds = %do.end175
  store i32 1, i32* %retval, align 4, !dbg !771
  br label %return, !dbg !771

if.end178:                                        ; preds = %do.end175
  %137 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !772
  %sequence179 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %137, i32 0, i32 0, !dbg !773
  store i32 5, i32* %sequence179, align 8, !dbg !774
  br label %sw.bb180, !dbg !775

sw.bb180:                                         ; preds = %while.body, %if.end178
  %138 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !776
  %concatenated181 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %138, i32 0, i32 10, !dbg !776
  %139 = load i8, i8* %concatenated181, align 1, !dbg !776
  %tobool182 = trunc i8 %139 to i1, !dbg !776
  br i1 %tobool182, label %cond.true184, label %cond.false185, !dbg !776

cond.true184:                                     ; preds = %sw.bb180
  br label %cond.end186, !dbg !777

cond.false185:                                    ; preds = %sw.bb180
  call void @__assert_fail(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([86 x i8], [86 x i8]* @.str.1, i32 0, i32 0), i32 330, i8* getelementptr inbounds ([164 x i8], [164 x i8]* @__PRETTY_FUNCTION__.stream_decode, i32 0, i32 0)) #10, !dbg !779
  unreachable, !dbg !779
                                                  ; No predecessors!
  br label %cond.end186, !dbg !781

cond.end186:                                      ; preds = %140, %cond.true184
  br label %while.body188, !dbg !783

while.body188:                                    ; preds = %cond.end186, %if.end206
  %141 = load i64*, i64** %in_pos.addr, align 8, !dbg !784
  %142 = load i64, i64* %141, align 8, !dbg !787
  %143 = load i64, i64* %in_size.addr, align 8, !dbg !788
  %cmp189 = icmp uge i64 %142, %143, !dbg !789
  br i1 %cmp189, label %if.then191, label %if.end200, !dbg !790

if.then191:                                       ; preds = %while.body188
  %144 = load i32, i32* %action.addr, align 4, !dbg !791
  %cmp192 = icmp ne i32 %144, 3, !dbg !794
  br i1 %cmp192, label %if.then194, label %if.end195, !dbg !795

if.then194:                                       ; preds = %if.then191
  store i32 0, i32* %retval, align 4, !dbg !796
  br label %return, !dbg !796

if.end195:                                        ; preds = %if.then191
  %145 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !797
  %pos196 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %145, i32 0, i32 12, !dbg !798
  %146 = load i64, i64* %pos196, align 8, !dbg !798
  %cmp197 = icmp eq i64 %146, 0, !dbg !799
  %cond199 = select i1 %cmp197, i32 1, i32 9, !dbg !797
  store i32 %cond199, i32* %retval, align 4, !dbg !800
  br label %return, !dbg !800

if.end200:                                        ; preds = %while.body188
  %147 = load i64*, i64** %in_pos.addr, align 8, !dbg !801
  %148 = load i64, i64* %147, align 8, !dbg !803
  %149 = load i8*, i8** %in.addr, align 8, !dbg !804
  %arrayidx201 = getelementptr inbounds i8, i8* %149, i64 %148, !dbg !804
  %150 = load i8, i8* %arrayidx201, align 1, !dbg !804
  %conv202 = zext i8 %150 to i32, !dbg !804
  %cmp203 = icmp ne i32 %conv202, 0, !dbg !805
  br i1 %cmp203, label %if.then205, label %if.end206, !dbg !806

if.then205:                                       ; preds = %if.end200
  br label %while.end, !dbg !807

if.end206:                                        ; preds = %if.end200
  %151 = load i64*, i64** %in_pos.addr, align 8, !dbg !808
  %152 = load i64, i64* %151, align 8, !dbg !809
  %inc207 = add i64 %152, 1, !dbg !809
  store i64 %inc207, i64* %151, align 8, !dbg !809
  %153 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !810
  %pos208 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %153, i32 0, i32 12, !dbg !811
  %154 = load i64, i64* %pos208, align 8, !dbg !811
  %add209 = add i64 %154, 1, !dbg !812
  %and = and i64 %add209, 3, !dbg !813
  %155 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !814
  %pos210 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %155, i32 0, i32 12, !dbg !815
  store i64 %and, i64* %pos210, align 8, !dbg !816
  br label %while.body188, !dbg !817

while.end:                                        ; preds = %if.then205
  %156 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !818
  %pos211 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %156, i32 0, i32 12, !dbg !820
  %157 = load i64, i64* %pos211, align 8, !dbg !820
  %cmp212 = icmp ne i64 %157, 0, !dbg !821
  br i1 %cmp212, label %if.then214, label %if.end216, !dbg !822

if.then214:                                       ; preds = %while.end
  %158 = load i64*, i64** %in_pos.addr, align 8, !dbg !823
  %159 = load i64, i64* %158, align 8, !dbg !825
  %inc215 = add i64 %159, 1, !dbg !825
  store i64 %inc215, i64* %158, align 8, !dbg !825
  store i32 9, i32* %retval, align 4, !dbg !826
  br label %return, !dbg !826

if.end216:                                        ; preds = %while.end
  br label %do.body217, !dbg !827

do.body217:                                       ; preds = %if.end216
  call void @llvm.dbg.declare(metadata i32* %ret_218, metadata !828, metadata !271), !dbg !830
  %160 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !831
  %161 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !831
  %call219 = call i32 @stream_decoder_reset(%struct.lzma_coder_s* %160, %struct.lzma_allocator* %161), !dbg !831
  store i32 %call219, i32* %ret_218, align 4, !dbg !831
  %162 = load i32, i32* %ret_218, align 4, !dbg !831
  %cmp220 = icmp ne i32 %162, 0, !dbg !831
  br i1 %cmp220, label %if.then222, label %if.end223, !dbg !831

if.then222:                                       ; preds = %do.body217
  %163 = load i32, i32* %ret_218, align 4, !dbg !833
  store i32 %163, i32* %retval, align 4, !dbg !833
  br label %return, !dbg !833

if.end223:                                        ; preds = %do.body217
  br label %do.end224, !dbg !836

do.end224:                                        ; preds = %if.end223
  br label %sw.epilog, !dbg !838

sw.default:                                       ; preds = %while.body
  call void @__assert_fail(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([86 x i8], [86 x i8]* @.str.1, i32 0, i32 0), i32 368, i8* getelementptr inbounds ([164 x i8], [164 x i8]* @__PRETTY_FUNCTION__.stream_decode, i32 0, i32 0)) #10, !dbg !839
  unreachable, !dbg !839

sw.epilog:                                        ; preds = %do.end224, %do.end121, %if.then42
  br label %while.body, !dbg !840

return:                                           ; preds = %if.then222, %if.then214, %if.end195, %if.then194, %if.then177, %if.then173, %if.then165, %cond.end158, %if.then145, %if.then133, %if.then127, %if.then119, %if.then109, %if.then98, %if.then75, %if.then62, %if.then35, %if.then30, %if.then27, %if.then19, %cond.end, %if.then
  %164 = load i32, i32* %retval, align 4, !dbg !842
  ret i32 %164, !dbg !842
}

; Function Attrs: nounwind uwtable
define internal void @stream_decoder_end(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator) #0 !dbg !258 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !843, metadata !271), !dbg !844
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !845, metadata !271), !dbg !846
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !847
  %block_decoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 1, !dbg !848
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !849
  call void @lzma_next_end(%struct.lzma_next_coder_s* %block_decoder, %struct.lzma_allocator* %1), !dbg !850
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !851
  %index_hash = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 4, !dbg !852
  %3 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash, align 8, !dbg !852
  %4 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !853
  call void @lzma_index_hash_end(%struct.lzma_index_hash_s* %3, %struct.lzma_allocator* %4) #8, !dbg !854
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !855
  %6 = bitcast %struct.lzma_coder_s* %5 to i8*, !dbg !855
  %7 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !856
  call void @lzma_free(i8* %6, %struct.lzma_allocator* %7), !dbg !857
  ret void, !dbg !858
}

; Function Attrs: nounwind uwtable
define internal i32 @stream_decoder_get_check(%struct.lzma_coder_s* %coder) #0 !dbg !259 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !859, metadata !271), !dbg !860
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !861
  %stream_flags = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 3, !dbg !862
  %check = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 2, !dbg !863
  %1 = load i32, i32* %check, align 8, !dbg !863
  ret i32 %1, !dbg !864
}

; Function Attrs: nounwind uwtable
define internal i32 @stream_decoder_memconfig(%struct.lzma_coder_s* %coder, i64* %memusage, i64* %old_memlimit, i64 %new_memlimit) #0 !dbg !260 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %memusage.addr = alloca i64*, align 8
  %old_memlimit.addr = alloca i64*, align 8
  %new_memlimit.addr = alloca i64, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !865, metadata !271), !dbg !866
  store i64* %memusage, i64** %memusage.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %memusage.addr, metadata !867, metadata !271), !dbg !868
  store i64* %old_memlimit, i64** %old_memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %old_memlimit.addr, metadata !869, metadata !271), !dbg !870
  store i64 %new_memlimit, i64* %new_memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %new_memlimit.addr, metadata !871, metadata !271), !dbg !872
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !873
  %memusage1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 6, !dbg !874
  %1 = load i64, i64* %memusage1, align 8, !dbg !874
  %2 = load i64*, i64** %memusage.addr, align 8, !dbg !875
  store i64 %1, i64* %2, align 8, !dbg !876
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !877
  %memlimit = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %3, i32 0, i32 5, !dbg !878
  %4 = load i64, i64* %memlimit, align 8, !dbg !878
  %5 = load i64*, i64** %old_memlimit.addr, align 8, !dbg !879
  store i64 %4, i64* %5, align 8, !dbg !880
  %6 = load i64, i64* %new_memlimit.addr, align 8, !dbg !881
  %cmp = icmp ne i64 %6, 0, !dbg !883
  br i1 %cmp, label %if.then, label %if.end6, !dbg !884

if.then:                                          ; preds = %entry
  %7 = load i64, i64* %new_memlimit.addr, align 8, !dbg !885
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !888
  %memusage2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %8, i32 0, i32 6, !dbg !889
  %9 = load i64, i64* %memusage2, align 8, !dbg !889
  %cmp3 = icmp ult i64 %7, %9, !dbg !890
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !891

if.then4:                                         ; preds = %if.then
  store i32 6, i32* %retval, align 4, !dbg !892
  br label %return, !dbg !892

if.end:                                           ; preds = %if.then
  %10 = load i64, i64* %new_memlimit.addr, align 8, !dbg !893
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !894
  %memlimit5 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 5, !dbg !895
  store i64 %10, i64* %memlimit5, align 8, !dbg !896
  br label %if.end6, !dbg !897

if.end6:                                          ; preds = %if.end, %entry
  store i32 0, i32* %retval, align 4, !dbg !898
  br label %return, !dbg !898

return:                                           ; preds = %if.end6, %if.then4
  %12 = load i32, i32* %retval, align 4, !dbg !899
  ret i32 %12, !dbg !899
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

; Function Attrs: nounwind uwtable
define internal i32 @stream_decoder_reset(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator) #0 !dbg !261 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !900, metadata !271), !dbg !901
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !902, metadata !271), !dbg !903
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !904
  %index_hash = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 4, !dbg !905
  %1 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash, align 8, !dbg !905
  %2 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !906
  %call = call %struct.lzma_index_hash_s* @lzma_index_hash_init(%struct.lzma_index_hash_s* %1, %struct.lzma_allocator* %2) #8, !dbg !907
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !908
  %index_hash1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %3, i32 0, i32 4, !dbg !909
  store %struct.lzma_index_hash_s* %call, %struct.lzma_index_hash_s** %index_hash1, align 8, !dbg !910
  %4 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !911
  %index_hash2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %4, i32 0, i32 4, !dbg !913
  %5 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash2, align 8, !dbg !913
  %cmp = icmp eq %struct.lzma_index_hash_s* %5, null, !dbg !914
  br i1 %cmp, label %if.then, label %if.end, !dbg !915

if.then:                                          ; preds = %entry
  store i32 5, i32* %retval, align 4, !dbg !916
  br label %return, !dbg !916

if.end:                                           ; preds = %entry
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !917
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %6, i32 0, i32 0, !dbg !918
  store i32 0, i32* %sequence, align 8, !dbg !919
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !920
  %pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 12, !dbg !921
  store i64 0, i64* %pos, align 8, !dbg !922
  store i32 0, i32* %retval, align 4, !dbg !923
  br label %return, !dbg !923

return:                                           ; preds = %if.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !924
  ret i32 %8, !dbg !924
}

; Function Attrs: nounwind uwtable
define i32 @lzma_stream_decoder(%struct.lzma_stream* %strm, i64 %memlimit, i32 %flags) #0 !dbg !230 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzma_stream*, align 8
  %memlimit.addr = alloca i64, align 8
  %flags.addr = alloca i32, align 4
  %ret_ = alloca i32, align 4
  %ret_2 = alloca i32, align 4
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !925, metadata !271), !dbg !926
  store i64 %memlimit, i64* %memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %memlimit.addr, metadata !927, metadata !271), !dbg !928
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !929, metadata !271), !dbg !930
  br label %do.body, !dbg !931

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !932, metadata !271), !dbg !934
  br label %do.body1, !dbg !935

do.body1:                                         ; preds = %do.body
  call void @llvm.dbg.declare(metadata i32* %ret_2, metadata !937, metadata !271), !dbg !939
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !940
  %call = call i32 @lzma_strm_init(%struct.lzma_stream* %0), !dbg !940
  store i32 %call, i32* %ret_2, align 4, !dbg !940
  %1 = load i32, i32* %ret_2, align 4, !dbg !940
  %cmp = icmp ne i32 %1, 0, !dbg !940
  br i1 %cmp, label %if.then, label %if.end, !dbg !940

if.then:                                          ; preds = %do.body1
  %2 = load i32, i32* %ret_2, align 4, !dbg !942
  store i32 %2, i32* %retval, align 4, !dbg !942
  br label %return, !dbg !942

if.end:                                           ; preds = %do.body1
  br label %do.end, !dbg !945

do.end:                                           ; preds = %if.end
  %3 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !947
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %3, i32 0, i32 7, !dbg !947
  %4 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !947
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %4, i32 0, i32 0, !dbg !947
  %5 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !947
  %allocator = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %5, i32 0, i32 6, !dbg !947
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator, align 8, !dbg !947
  %7 = load i64, i64* %memlimit.addr, align 8, !dbg !947
  %8 = load i32, i32* %flags.addr, align 4, !dbg !947
  %call3 = call i32 @lzma_stream_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %6, i64 %7, i32 %8), !dbg !947
  store i32 %call3, i32* %ret_, align 4, !dbg !947
  %9 = load i32, i32* %ret_, align 4, !dbg !947
  %cmp4 = icmp ne i32 %9, 0, !dbg !947
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !947

if.then5:                                         ; preds = %do.end
  %10 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !949
  call void @lzma_end(%struct.lzma_stream* %10) #8, !dbg !949
  %11 = load i32, i32* %ret_, align 4, !dbg !949
  store i32 %11, i32* %retval, align 4, !dbg !949
  br label %return, !dbg !949

if.end6:                                          ; preds = %do.end
  br label %do.end7, !dbg !953

do.end7:                                          ; preds = %if.end6
  %12 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !955
  %internal8 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %12, i32 0, i32 7, !dbg !956
  %13 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal8, align 8, !dbg !956
  %supported_actions = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %13, i32 0, i32 3, !dbg !957
  %arrayidx = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions, i64 0, i64 0, !dbg !955
  store i8 1, i8* %arrayidx, align 8, !dbg !958
  %14 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !959
  %internal9 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %14, i32 0, i32 7, !dbg !960
  %15 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal9, align 8, !dbg !960
  %supported_actions10 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %15, i32 0, i32 3, !dbg !961
  %arrayidx11 = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions10, i64 0, i64 3, !dbg !959
  store i8 1, i8* %arrayidx11, align 1, !dbg !962
  store i32 0, i32* %retval, align 4, !dbg !963
  br label %return, !dbg !963

return:                                           ; preds = %do.end7, %if.then5, %if.then
  %16 = load i32, i32* %retval, align 4, !dbg !964
  ret i32 %16, !dbg !964
}

declare i32 @lzma_strm_init(%struct.lzma_stream*) #2

; Function Attrs: nounwind
declare void @lzma_end(%struct.lzma_stream*) #4

declare i64 @lzma_bufcpy(i8*, i64*, i64, i8*, i64*, i64) #2

; Function Attrs: nounwind
declare i32 @lzma_stream_header_decode(%struct.lzma_stream_flags*, i8*) #4

; Function Attrs: nounwind readnone
declare zeroext i8 @lzma_check_is_supported(i32) #5

; Function Attrs: nounwind
declare i32 @lzma_block_header_decode(%struct.lzma_block*, %struct.lzma_allocator*, i8*) #4

; Function Attrs: nounwind readonly
declare i64 @lzma_raw_decoder_memusage(%struct.lzma_filter*) #6

declare i32 @lzma_block_decoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_block*) #2

declare void @lzma_free(i8*, %struct.lzma_allocator*) #2

; Function Attrs: nounwind
declare i32 @lzma_index_hash_append(%struct.lzma_index_hash_s*, i64, i64) #4

; Function Attrs: nounwind readonly
declare i64 @lzma_block_unpadded_size(%struct.lzma_block*) #6

; Function Attrs: nounwind
declare i32 @lzma_index_hash_decode(%struct.lzma_index_hash_s*, i8*, i64*, i64) #4

; Function Attrs: nounwind
declare i32 @lzma_stream_footer_decode(%struct.lzma_stream_flags*, i8*) #4

; Function Attrs: nounwind readonly
declare i64 @lzma_index_hash_size(%struct.lzma_index_hash_s*) #6

; Function Attrs: nounwind readonly
declare i32 @lzma_stream_flags_compare(%struct.lzma_stream_flags*, %struct.lzma_stream_flags*) #6

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #7

; Function Attrs: nounwind
declare void @lzma_index_hash_end(%struct.lzma_index_hash_s*, %struct.lzma_allocator*) #4

; Function Attrs: nounwind
declare %struct.lzma_index_hash_s* @lzma_index_hash_init(%struct.lzma_index_hash_s*, %struct.lzma_allocator*) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { nounwind }
attributes #9 = { nounwind readonly }
attributes #10 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!267, !268}
!llvm.ident = !{!269}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !223, subprograms: !224, globals: !264)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_decoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !87, !143, !70, !205}
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
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !19, file: !1, line: 18, size: 32, align: 32, elements: !198)
!19 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !1, line: 17, size: 11200, align: 64, elements: !20)
!20 = !{!21, !22, !112, !158, !180, !185, !186, !187, !189, !190, !191, !192, !193, !194}
!21 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !19, file: !1, line: 25, baseType: !18, size: 32, align: 32)
!22 = !DIDerivedType(tag: DW_TAG_member, name: "block_decoder", scope: !19, file: !1, line: 30, baseType: !23, size: 512, align: 64, offset: 64)
!23 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !24, line: 75, baseType: !25)
!24 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!25 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !24, line: 119, size: 512, align: 64, elements: !26)
!26 = !{!27, !30, !36, !38, !76, !81, !95, !100}
!27 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !25, file: !24, line: 121, baseType: !28, size: 64, align: 64)
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64, align: 64)
!29 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !24, line: 73, baseType: !19)
!30 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !25, file: !24, line: 125, baseType: !31, size: 64, align: 64, offset: 64)
!31 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !32, line: 63, baseType: !33)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!33 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !34, line: 55, baseType: !35)
!34 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!35 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!36 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !25, file: !24, line: 131, baseType: !37, size: 64, align: 64, offset: 128)
!37 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !34, line: 122, baseType: !35)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !25, file: !24, line: 134, baseType: !39, size: 64, align: 64, offset: 192)
!39 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !24, line: 89, baseType: !40)
!40 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64, align: 64)
!41 = !DISubroutineType(types: !42)
!42 = !{!43, !28, !44, !60, !65, !53, !67, !65, !53, !69}
!43 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!44 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !46)
!46 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !47)
!47 = !{!48, !55, !59}
!48 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !46, file: !4, line: 376, baseType: !49, size: 64, align: 64)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DISubroutineType(types: !51)
!51 = !{!52, !52, !53, !53}
!52 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!53 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !54, line: 62, baseType: !35)
!54 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!55 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !46, file: !4, line: 390, baseType: !56, size: 64, align: 64, offset: 64)
!56 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64, align: 64)
!57 = !DISubroutineType(types: !58)
!58 = !{null, !52, !52}
!59 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !46, file: !4, line: 401, baseType: !52, size: 64, align: 64, offset: 128)
!60 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !61)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !63)
!63 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !34, line: 48, baseType: !64)
!64 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!65 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !66)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !53, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !68)
!68 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!69 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !70)
!70 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !71)
!71 = !{!72, !73, !74, !75}
!72 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!73 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!74 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!75 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !25, file: !24, line: 139, baseType: !77, size: 64, align: 64, offset: 256)
!77 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !24, line: 97, baseType: !78)
!78 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !79, size: 64, align: 64)
!79 = !DISubroutineType(types: !80)
!80 = !{null, !28, !44}
!81 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !25, file: !24, line: 143, baseType: !82, size: 64, align: 64, offset: 320)
!82 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !83, size: 64, align: 64)
!83 = !DISubroutineType(types: !84)
!84 = !{!85, !93}
!85 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !86, line: 55, baseType: !87)
!86 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!87 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !86, line: 27, size: 32, align: 32, elements: !88)
!88 = !{!89, !90, !91, !92}
!89 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!90 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!91 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!92 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!93 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !94, size: 64, align: 64)
!94 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !29)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !25, file: !24, line: 147, baseType: !96, size: 64, align: 64, offset: 384)
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !97, size: 64, align: 64)
!97 = !DISubroutineType(types: !98)
!98 = !{!43, !28, !99, !99, !33}
!99 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !33, size: 64, align: 64)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !25, file: !24, line: 152, baseType: !101, size: 64, align: 64, offset: 448)
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !102, size: 64, align: 64)
!102 = !DISubroutineType(types: !103)
!103 = !{!43, !28, !44, !104, !104}
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !105, size: 64, align: 64)
!105 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !106)
!106 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !107, line: 65, baseType: !108)
!107 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!108 = !DICompositeType(tag: DW_TAG_structure_type, file: !107, line: 43, size: 128, align: 64, elements: !109)
!109 = !{!110, !111}
!110 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !108, file: !107, line: 54, baseType: !31, size: 64, align: 64)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !108, file: !107, line: 63, baseType: !52, size: 64, align: 64, offset: 64)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "block_options", scope: !19, file: !1, line: 34, baseType: !113, size: 1664, align: 64, offset: 576)
!113 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_block", file: !114, line: 245, baseType: !115)
!114 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/block.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!115 = !DICompositeType(tag: DW_TAG_structure_type, file: !114, line: 30, size: 1664, align: 64, elements: !116)
!116 = !{!117, !120, !121, !122, !123, !124, !126, !130, !131, !132, !133, !134, !135, !136, !137, !138, !139, !140, !141, !146, !147, !148, !149, !151, !152, !153, !154, !155, !156, !157}
!117 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !115, file: !114, line: 47, baseType: !118, size: 32, align: 32)
!118 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !34, line: 51, baseType: !119)
!119 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "header_size", scope: !115, file: !114, line: 67, baseType: !118, size: 32, align: 32, offset: 32)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !115, file: !114, line: 88, baseType: !85, size: 32, align: 32, offset: 64)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_size", scope: !115, file: !114, line: 143, baseType: !31, size: 64, align: 64, offset: 128)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !115, file: !114, line: 167, baseType: !31, size: 64, align: 64, offset: 192)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "filters", scope: !115, file: !114, line: 195, baseType: !125, size: 64, align: 64, offset: 256)
!125 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !106, size: 64, align: 64)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "raw_check", scope: !115, file: !114, line: 212, baseType: !127, size: 512, align: 8, offset: 320)
!127 = !DICompositeType(tag: DW_TAG_array_type, baseType: !63, size: 512, align: 8, elements: !128)
!128 = !{!129}
!129 = !DISubrange(count: 64)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !115, file: !114, line: 221, baseType: !52, size: 64, align: 64, offset: 832)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !115, file: !114, line: 222, baseType: !52, size: 64, align: 64, offset: 896)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !115, file: !114, line: 223, baseType: !52, size: 64, align: 64, offset: 960)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !115, file: !114, line: 224, baseType: !118, size: 32, align: 32, offset: 1024)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !115, file: !114, line: 225, baseType: !118, size: 32, align: 32, offset: 1056)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !115, file: !114, line: 226, baseType: !31, size: 64, align: 64, offset: 1088)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !115, file: !114, line: 227, baseType: !31, size: 64, align: 64, offset: 1152)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !115, file: !114, line: 228, baseType: !31, size: 64, align: 64, offset: 1216)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !115, file: !114, line: 229, baseType: !31, size: 64, align: 64, offset: 1280)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !115, file: !114, line: 230, baseType: !31, size: 64, align: 64, offset: 1344)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !115, file: !114, line: 231, baseType: !31, size: 64, align: 64, offset: 1408)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !115, file: !114, line: 232, baseType: !142, size: 32, align: 32, offset: 1472)
!142 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !143)
!143 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !144)
!144 = !{!145}
!145 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !115, file: !114, line: 233, baseType: !142, size: 32, align: 32, offset: 1504)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !115, file: !114, line: 234, baseType: !142, size: 32, align: 32, offset: 1536)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !115, file: !114, line: 235, baseType: !142, size: 32, align: 32, offset: 1568)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool1", scope: !115, file: !114, line: 236, baseType: !150, size: 8, align: 8, offset: 1600)
!150 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !4, line: 29, baseType: !64)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool2", scope: !115, file: !114, line: 237, baseType: !150, size: 8, align: 8, offset: 1608)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool3", scope: !115, file: !114, line: 238, baseType: !150, size: 8, align: 8, offset: 1616)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool4", scope: !115, file: !114, line: 239, baseType: !150, size: 8, align: 8, offset: 1624)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool5", scope: !115, file: !114, line: 240, baseType: !150, size: 8, align: 8, offset: 1632)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool6", scope: !115, file: !114, line: 241, baseType: !150, size: 8, align: 8, offset: 1640)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool7", scope: !115, file: !114, line: 242, baseType: !150, size: 8, align: 8, offset: 1648)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool8", scope: !115, file: !114, line: 243, baseType: !150, size: 8, align: 8, offset: 1656)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "stream_flags", scope: !19, file: !1, line: 37, baseType: !159, size: 448, align: 64, offset: 2240)
!159 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream_flags", file: !160, line: 105, baseType: !161)
!160 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/stream_flags.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!161 = !DICompositeType(tag: DW_TAG_structure_type, file: !160, line: 33, size: 448, align: 64, elements: !162)
!162 = !{!163, !164, !165, !166, !167, !168, !169, !170, !171, !172, !173, !174, !175, !176, !177, !178, !179}
!163 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !161, file: !160, line: 51, baseType: !118, size: 32, align: 32)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "backward_size", scope: !161, file: !160, line: 69, baseType: !31, size: 64, align: 64, offset: 64)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !161, file: !160, line: 79, baseType: !85, size: 32, align: 32, offset: 128)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !161, file: !160, line: 90, baseType: !142, size: 32, align: 32, offset: 160)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !161, file: !160, line: 91, baseType: !142, size: 32, align: 32, offset: 192)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !161, file: !160, line: 92, baseType: !142, size: 32, align: 32, offset: 224)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !161, file: !160, line: 93, baseType: !142, size: 32, align: 32, offset: 256)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool1", scope: !161, file: !160, line: 94, baseType: !150, size: 8, align: 8, offset: 288)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool2", scope: !161, file: !160, line: 95, baseType: !150, size: 8, align: 8, offset: 296)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool3", scope: !161, file: !160, line: 96, baseType: !150, size: 8, align: 8, offset: 304)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool4", scope: !161, file: !160, line: 97, baseType: !150, size: 8, align: 8, offset: 312)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool5", scope: !161, file: !160, line: 98, baseType: !150, size: 8, align: 8, offset: 320)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool6", scope: !161, file: !160, line: 99, baseType: !150, size: 8, align: 8, offset: 328)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool7", scope: !161, file: !160, line: 100, baseType: !150, size: 8, align: 8, offset: 336)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool8", scope: !161, file: !160, line: 101, baseType: !150, size: 8, align: 8, offset: 344)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !161, file: !160, line: 102, baseType: !118, size: 32, align: 32, offset: 352)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !161, file: !160, line: 103, baseType: !118, size: 32, align: 32, offset: 384)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "index_hash", scope: !19, file: !1, line: 41, baseType: !181, size: 64, align: 64, offset: 2688)
!181 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !182, size: 64, align: 64)
!182 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_index_hash", file: !183, line: 25, baseType: !184)
!183 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/index_hash.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!184 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_index_hash_s", file: !183, line: 25, flags: DIFlagFwdDecl)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "memlimit", scope: !19, file: !1, line: 44, baseType: !33, size: 64, align: 64, offset: 2752)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "memusage", scope: !19, file: !1, line: 47, baseType: !33, size: 64, align: 64, offset: 2816)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "tell_no_check", scope: !19, file: !1, line: 51, baseType: !188, size: 8, align: 8, offset: 2880)
!188 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!189 = !DIDerivedType(tag: DW_TAG_member, name: "tell_unsupported_check", scope: !19, file: !1, line: 55, baseType: !188, size: 8, align: 8, offset: 2888)
!190 = !DIDerivedType(tag: DW_TAG_member, name: "tell_any_check", scope: !19, file: !1, line: 58, baseType: !188, size: 8, align: 8, offset: 2896)
!191 = !DIDerivedType(tag: DW_TAG_member, name: "concatenated", scope: !19, file: !1, line: 65, baseType: !188, size: 8, align: 8, offset: 2904)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "first_stream", scope: !19, file: !1, line: 71, baseType: !188, size: 8, align: 8, offset: 2912)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "pos", scope: !19, file: !1, line: 74, baseType: !53, size: 64, align: 64, offset: 2944)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !19, file: !1, line: 78, baseType: !195, size: 8192, align: 8, offset: 3008)
!195 = !DICompositeType(tag: DW_TAG_array_type, baseType: !63, size: 8192, align: 8, elements: !196)
!196 = !{!197}
!197 = !DISubrange(count: 1024)
!198 = !{!199, !200, !201, !202, !203, !204}
!199 = !DIEnumerator(name: "SEQ_STREAM_HEADER", value: 0)
!200 = !DIEnumerator(name: "SEQ_BLOCK_HEADER", value: 1)
!201 = !DIEnumerator(name: "SEQ_BLOCK", value: 2)
!202 = !DIEnumerator(name: "SEQ_INDEX", value: 3)
!203 = !DIEnumerator(name: "SEQ_STREAM_FOOTER", value: 4)
!204 = !DIEnumerator(name: "SEQ_STREAM_PADDING", value: 5)
!205 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !206, file: !24, line: 182, size: 32, align: 32, elements: !216)
!206 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_internal_s", file: !24, line: 174, size: 704, align: 64, elements: !207)
!207 = !{!208, !209, !210, !211, !215}
!208 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !206, file: !24, line: 176, baseType: !23, size: 512, align: 64)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !206, file: !24, line: 189, baseType: !205, size: 32, align: 32, offset: 512)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !206, file: !24, line: 194, baseType: !53, size: 64, align: 64, offset: 576)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "supported_actions", scope: !206, file: !24, line: 197, baseType: !212, size: 32, align: 8, offset: 640)
!212 = !DICompositeType(tag: DW_TAG_array_type, baseType: !188, size: 32, align: 8, elements: !213)
!213 = !{!214}
!214 = !DISubrange(count: 4)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "allow_buf_error", scope: !206, file: !24, line: 201, baseType: !188, size: 8, align: 8, offset: 672)
!216 = !{!217, !218, !219, !220, !221, !222}
!217 = !DIEnumerator(name: "ISEQ_RUN", value: 0)
!218 = !DIEnumerator(name: "ISEQ_SYNC_FLUSH", value: 1)
!219 = !DIEnumerator(name: "ISEQ_FULL_FLUSH", value: 2)
!220 = !DIEnumerator(name: "ISEQ_FINISH", value: 3)
!221 = !DIEnumerator(name: "ISEQ_END", value: 4)
!222 = !DIEnumerator(name: "ISEQ_ERROR", value: 5)
!223 = !{!37, !52, !118}
!224 = !{!225, !230, !257, !258, !259, !260, !261}
!225 = distinct !DISubprogram(name: "lzma_stream_decoder_init", scope: !1, file: !1, line: 412, type: !226, isLocal: false, isDefinition: true, scopeLine: 414, flags: DIFlagPrototyped, isOptimized: false, variables: !229)
!226 = !DISubroutineType(types: !227)
!227 = !{!43, !228, !44, !33, !118}
!228 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!229 = !{}
!230 = distinct !DISubprogram(name: "lzma_stream_decoder", scope: !1, file: !1, line: 451, type: !231, isLocal: false, isDefinition: true, scopeLine: 452, flags: DIFlagPrototyped, isOptimized: false, variables: !229)
!231 = !DISubroutineType(types: !232)
!232 = !{!43, !233, !33, !118}
!233 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !234, size: 64, align: 64)
!234 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream", file: !4, line: 490, baseType: !235)
!235 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 453, size: 1088, align: 64, elements: !236)
!236 = !{!237, !238, !239, !240, !241, !242, !243, !244, !247, !248, !249, !250, !251, !252, !253, !254, !255, !256}
!237 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !235, file: !4, line: 454, baseType: !61, size: 64, align: 64)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !235, file: !4, line: 455, baseType: !53, size: 64, align: 64, offset: 64)
!239 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !235, file: !4, line: 456, baseType: !33, size: 64, align: 64, offset: 128)
!240 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !235, file: !4, line: 458, baseType: !68, size: 64, align: 64, offset: 192)
!241 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !235, file: !4, line: 459, baseType: !53, size: 64, align: 64, offset: 256)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !235, file: !4, line: 460, baseType: !33, size: 64, align: 64, offset: 320)
!243 = !DIDerivedType(tag: DW_TAG_member, name: "allocator", scope: !235, file: !4, line: 468, baseType: !44, size: 64, align: 64, offset: 384)
!244 = !DIDerivedType(tag: DW_TAG_member, name: "internal", scope: !235, file: !4, line: 471, baseType: !245, size: 64, align: 64, offset: 448)
!245 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !246, size: 64, align: 64)
!246 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_internal", file: !4, line: 411, baseType: !206)
!247 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !235, file: !4, line: 479, baseType: !52, size: 64, align: 64, offset: 512)
!248 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !235, file: !4, line: 480, baseType: !52, size: 64, align: 64, offset: 576)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !235, file: !4, line: 481, baseType: !52, size: 64, align: 64, offset: 640)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr4", scope: !235, file: !4, line: 482, baseType: !52, size: 64, align: 64, offset: 704)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !235, file: !4, line: 483, baseType: !33, size: 64, align: 64, offset: 768)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !235, file: !4, line: 484, baseType: !33, size: 64, align: 64, offset: 832)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !235, file: !4, line: 485, baseType: !53, size: 64, align: 64, offset: 896)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !235, file: !4, line: 486, baseType: !53, size: 64, align: 64, offset: 960)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !235, file: !4, line: 487, baseType: !142, size: 32, align: 32, offset: 1024)
!256 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !235, file: !4, line: 488, baseType: !142, size: 32, align: 32, offset: 1056)
!257 = distinct !DISubprogram(name: "stream_decode", scope: !1, file: !1, line: 99, type: !41, isLocal: true, isDefinition: true, scopeLine: 103, flags: DIFlagPrototyped, isOptimized: false, variables: !229)
!258 = distinct !DISubprogram(name: "stream_decoder_end", scope: !1, file: !1, line: 377, type: !79, isLocal: true, isDefinition: true, scopeLine: 378, flags: DIFlagPrototyped, isOptimized: false, variables: !229)
!259 = distinct !DISubprogram(name: "stream_decoder_get_check", scope: !1, file: !1, line: 387, type: !83, isLocal: true, isDefinition: true, scopeLine: 388, flags: DIFlagPrototyped, isOptimized: false, variables: !229)
!260 = distinct !DISubprogram(name: "stream_decoder_memconfig", scope: !1, file: !1, line: 394, type: !97, isLocal: true, isDefinition: true, scopeLine: 396, flags: DIFlagPrototyped, isOptimized: false, variables: !229)
!261 = distinct !DISubprogram(name: "stream_decoder_reset", scope: !1, file: !1, line: 83, type: !262, isLocal: true, isDefinition: true, scopeLine: 84, flags: DIFlagPrototyped, isOptimized: false, variables: !229)
!262 = !DISubroutineType(types: !263)
!263 = !{!43, !28, !44}
!264 = !{!265}
!265 = !DIGlobalVariable(name: "LZMA_NEXT_CODER_INIT", scope: !0, file: !24, line: 159, type: !266, isLocal: true, isDefinition: true, variable: %struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT)
!266 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !23)
!267 = !{i32 2, !"Dwarf Version", i32 4}
!268 = !{i32 2, !"Debug Info Version", i32 3}
!269 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!270 = !DILocalVariable(name: "next", arg: 1, scope: !225, file: !1, line: 412, type: !228)
!271 = !DIExpression()
!272 = !DILocation(line: 412, column: 43, scope: !225)
!273 = !DILocalVariable(name: "allocator", arg: 2, scope: !225, file: !1, line: 412, type: !44)
!274 = !DILocation(line: 412, column: 65, scope: !225)
!275 = !DILocalVariable(name: "memlimit", arg: 3, scope: !225, file: !1, line: 413, type: !33)
!276 = !DILocation(line: 413, column: 12, scope: !225)
!277 = !DILocalVariable(name: "flags", arg: 4, scope: !225, file: !1, line: 413, type: !118)
!278 = !DILocation(line: 413, column: 31, scope: !225)
!279 = !DILocation(line: 415, column: 2, scope: !225)
!280 = !DILocation(line: 415, column: 2, scope: !281)
!281 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 1)
!282 = distinct !DILexicalBlock(scope: !283, file: !1, line: 415, column: 2)
!283 = distinct !DILexicalBlock(scope: !225, file: !1, line: 415, column: 2)
!284 = !DILocation(line: 415, column: 2, scope: !285)
!285 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 2)
!286 = !DILocation(line: 415, column: 2, scope: !287)
!287 = !DILexicalBlockFile(scope: !283, file: !1, discriminator: 3)
!288 = !DILocation(line: 417, column: 6, scope: !289)
!289 = distinct !DILexicalBlock(scope: !225, file: !1, line: 417, column: 6)
!290 = !DILocation(line: 417, column: 15, scope: !289)
!291 = !DILocation(line: 417, column: 6, scope: !225)
!292 = !DILocation(line: 418, column: 3, scope: !289)
!293 = !DILocation(line: 420, column: 6, scope: !294)
!294 = distinct !DILexicalBlock(scope: !225, file: !1, line: 420, column: 6)
!295 = !DILocation(line: 420, column: 12, scope: !294)
!296 = !DILocation(line: 420, column: 6, scope: !225)
!297 = !DILocation(line: 421, column: 3, scope: !294)
!298 = !DILocation(line: 423, column: 6, scope: !299)
!299 = distinct !DILexicalBlock(scope: !225, file: !1, line: 423, column: 6)
!300 = !DILocation(line: 423, column: 12, scope: !299)
!301 = !DILocation(line: 423, column: 18, scope: !299)
!302 = !DILocation(line: 423, column: 6, scope: !225)
!303 = !DILocation(line: 424, column: 48, scope: !304)
!304 = distinct !DILexicalBlock(scope: !299, file: !1, line: 423, column: 27)
!305 = !DILocation(line: 424, column: 17, scope: !304)
!306 = !DILocation(line: 424, column: 3, scope: !304)
!307 = !DILocation(line: 424, column: 9, scope: !304)
!308 = !DILocation(line: 424, column: 15, scope: !304)
!309 = !DILocation(line: 425, column: 7, scope: !310)
!310 = distinct !DILexicalBlock(scope: !304, file: !1, line: 425, column: 7)
!311 = !DILocation(line: 425, column: 13, scope: !310)
!312 = !DILocation(line: 425, column: 19, scope: !310)
!313 = !DILocation(line: 425, column: 7, scope: !304)
!314 = !DILocation(line: 426, column: 4, scope: !310)
!315 = !DILocation(line: 428, column: 3, scope: !304)
!316 = !DILocation(line: 428, column: 9, scope: !304)
!317 = !DILocation(line: 428, column: 14, scope: !304)
!318 = !DILocation(line: 429, column: 3, scope: !304)
!319 = !DILocation(line: 429, column: 9, scope: !304)
!320 = !DILocation(line: 429, column: 13, scope: !304)
!321 = !DILocation(line: 430, column: 3, scope: !304)
!322 = !DILocation(line: 430, column: 9, scope: !304)
!323 = !DILocation(line: 430, column: 19, scope: !304)
!324 = !DILocation(line: 431, column: 3, scope: !304)
!325 = !DILocation(line: 431, column: 9, scope: !304)
!326 = !DILocation(line: 431, column: 19, scope: !304)
!327 = !DILocation(line: 433, column: 3, scope: !304)
!328 = !DILocation(line: 433, column: 9, scope: !304)
!329 = !DILocation(line: 433, column: 16, scope: !304)
!330 = !DILocation(line: 433, column: 32, scope: !304)
!331 = !DILocation(line: 434, column: 3, scope: !304)
!332 = !DILocation(line: 434, column: 9, scope: !304)
!333 = !DILocation(line: 434, column: 16, scope: !304)
!334 = !DILocation(line: 434, column: 27, scope: !304)
!335 = !DILocation(line: 435, column: 2, scope: !304)
!336 = !DILocation(line: 437, column: 26, scope: !225)
!337 = !DILocation(line: 437, column: 2, scope: !225)
!338 = !DILocation(line: 437, column: 8, scope: !225)
!339 = !DILocation(line: 437, column: 15, scope: !225)
!340 = !DILocation(line: 437, column: 24, scope: !225)
!341 = !DILocation(line: 438, column: 2, scope: !225)
!342 = !DILocation(line: 438, column: 8, scope: !225)
!343 = !DILocation(line: 438, column: 15, scope: !225)
!344 = !DILocation(line: 438, column: 24, scope: !225)
!345 = !DILocation(line: 439, column: 32, scope: !225)
!346 = !DILocation(line: 439, column: 38, scope: !225)
!347 = !DILocation(line: 439, column: 60, scope: !225)
!348 = !DILocation(line: 439, column: 2, scope: !225)
!349 = !DILocation(line: 439, column: 8, scope: !225)
!350 = !DILocation(line: 439, column: 15, scope: !225)
!351 = !DILocation(line: 439, column: 29, scope: !225)
!352 = !DILocation(line: 441, column: 7, scope: !225)
!353 = !DILocation(line: 441, column: 13, scope: !225)
!354 = !DILocation(line: 441, column: 44, scope: !225)
!355 = !DILocation(line: 440, column: 2, scope: !225)
!356 = !DILocation(line: 440, column: 8, scope: !225)
!357 = !DILocation(line: 440, column: 15, scope: !225)
!358 = !DILocation(line: 441, column: 4, scope: !225)
!359 = !DILocation(line: 442, column: 33, scope: !225)
!360 = !DILocation(line: 442, column: 39, scope: !225)
!361 = !DILocation(line: 442, column: 62, scope: !225)
!362 = !DILocation(line: 442, column: 2, scope: !225)
!363 = !DILocation(line: 442, column: 8, scope: !225)
!364 = !DILocation(line: 442, column: 15, scope: !225)
!365 = !DILocation(line: 442, column: 30, scope: !225)
!366 = !DILocation(line: 443, column: 31, scope: !225)
!367 = !DILocation(line: 443, column: 37, scope: !225)
!368 = !DILocation(line: 443, column: 58, scope: !225)
!369 = !DILocation(line: 443, column: 2, scope: !225)
!370 = !DILocation(line: 443, column: 8, scope: !225)
!371 = !DILocation(line: 443, column: 15, scope: !225)
!372 = !DILocation(line: 443, column: 28, scope: !225)
!373 = !DILocation(line: 444, column: 2, scope: !225)
!374 = !DILocation(line: 444, column: 8, scope: !225)
!375 = !DILocation(line: 444, column: 15, scope: !225)
!376 = !DILocation(line: 444, column: 28, scope: !225)
!377 = !DILocation(line: 446, column: 30, scope: !225)
!378 = !DILocation(line: 446, column: 36, scope: !225)
!379 = !DILocation(line: 446, column: 43, scope: !225)
!380 = !DILocation(line: 446, column: 9, scope: !225)
!381 = !DILocation(line: 446, column: 2, scope: !225)
!382 = !DILocation(line: 447, column: 1, scope: !225)
!383 = !DILocalVariable(name: "coder", arg: 1, scope: !257, file: !1, line: 99, type: !28)
!384 = !DILocation(line: 99, column: 27, scope: !257)
!385 = !DILocalVariable(name: "allocator", arg: 2, scope: !257, file: !1, line: 99, type: !44)
!386 = !DILocation(line: 99, column: 50, scope: !257)
!387 = !DILocalVariable(name: "in", arg: 3, scope: !257, file: !1, line: 100, type: !60)
!388 = !DILocation(line: 100, column: 32, scope: !257)
!389 = !DILocalVariable(name: "in_pos", arg: 4, scope: !257, file: !1, line: 100, type: !65)
!390 = !DILocation(line: 100, column: 58, scope: !257)
!391 = !DILocalVariable(name: "in_size", arg: 5, scope: !257, file: !1, line: 101, type: !53)
!392 = !DILocation(line: 101, column: 10, scope: !257)
!393 = !DILocalVariable(name: "out", arg: 6, scope: !257, file: !1, line: 101, type: !67)
!394 = !DILocation(line: 101, column: 42, scope: !257)
!395 = !DILocalVariable(name: "out_pos", arg: 7, scope: !257, file: !1, line: 102, type: !65)
!396 = !DILocation(line: 102, column: 25, scope: !257)
!397 = !DILocalVariable(name: "out_size", arg: 8, scope: !257, file: !1, line: 102, type: !53)
!398 = !DILocation(line: 102, column: 41, scope: !257)
!399 = !DILocalVariable(name: "action", arg: 9, scope: !257, file: !1, line: 102, type: !69)
!400 = !DILocation(line: 102, column: 63, scope: !257)
!401 = !DILocation(line: 106, column: 2, scope: !257)
!402 = !DILocation(line: 107, column: 10, scope: !257)
!403 = !DILocation(line: 107, column: 17, scope: !257)
!404 = !DILocation(line: 107, column: 2, scope: !257)
!405 = !DILocalVariable(name: "ret", scope: !406, file: !1, line: 109, type: !43)
!406 = distinct !DILexicalBlock(scope: !407, file: !1, line: 108, column: 26)
!407 = distinct !DILexicalBlock(scope: !257, file: !1, line: 107, column: 27)
!408 = !DILocation(line: 109, column: 12, scope: !406)
!409 = !DILocation(line: 112, column: 15, scope: !406)
!410 = !DILocation(line: 112, column: 19, scope: !406)
!411 = !DILocation(line: 112, column: 27, scope: !406)
!412 = !DILocation(line: 112, column: 36, scope: !406)
!413 = !DILocation(line: 112, column: 43, scope: !406)
!414 = !DILocation(line: 112, column: 52, scope: !406)
!415 = !DILocation(line: 112, column: 59, scope: !406)
!416 = !DILocation(line: 112, column: 3, scope: !406)
!417 = !DILocation(line: 116, column: 7, scope: !418)
!418 = distinct !DILexicalBlock(scope: !406, file: !1, line: 116, column: 7)
!419 = !DILocation(line: 116, column: 14, scope: !418)
!420 = !DILocation(line: 116, column: 18, scope: !418)
!421 = !DILocation(line: 116, column: 7, scope: !406)
!422 = !DILocation(line: 117, column: 4, scope: !418)
!423 = !DILocation(line: 119, column: 3, scope: !406)
!424 = !DILocation(line: 119, column: 10, scope: !406)
!425 = !DILocation(line: 119, column: 14, scope: !406)
!426 = !DILocation(line: 123, column: 6, scope: !406)
!427 = !DILocation(line: 123, column: 13, scope: !406)
!428 = !DILocation(line: 123, column: 27, scope: !406)
!429 = !DILocation(line: 123, column: 34, scope: !406)
!430 = !DILocation(line: 122, column: 9, scope: !406)
!431 = !DILocation(line: 122, column: 7, scope: !406)
!432 = !DILocation(line: 124, column: 7, scope: !433)
!433 = distinct !DILexicalBlock(scope: !406, file: !1, line: 124, column: 7)
!434 = !DILocation(line: 124, column: 11, scope: !433)
!435 = !DILocation(line: 124, column: 7, scope: !406)
!436 = !DILocation(line: 125, column: 11, scope: !433)
!437 = !DILocation(line: 125, column: 15, scope: !433)
!438 = !DILocation(line: 125, column: 36, scope: !433)
!439 = !DILocation(line: 125, column: 40, scope: !440)
!440 = !DILexicalBlockFile(scope: !433, file: !1, discriminator: 1)
!441 = !DILocation(line: 125, column: 47, scope: !440)
!442 = !DILocation(line: 125, column: 11, scope: !440)
!443 = !DILocation(line: 125, column: 11, scope: !444)
!444 = !DILexicalBlockFile(scope: !433, file: !1, discriminator: 2)
!445 = !DILocation(line: 126, column: 26, scope: !433)
!446 = !DILocation(line: 125, column: 11, scope: !447)
!447 = !DILexicalBlockFile(scope: !433, file: !1, discriminator: 3)
!448 = !DILocation(line: 125, column: 11, scope: !449)
!449 = !DILexicalBlockFile(scope: !433, file: !1, discriminator: 4)
!450 = !DILocation(line: 125, column: 4, scope: !449)
!451 = !DILocation(line: 131, column: 3, scope: !406)
!452 = !DILocation(line: 131, column: 10, scope: !406)
!453 = !DILocation(line: 131, column: 23, scope: !406)
!454 = !DILocation(line: 135, column: 32, scope: !406)
!455 = !DILocation(line: 135, column: 39, scope: !406)
!456 = !DILocation(line: 135, column: 52, scope: !406)
!457 = !DILocation(line: 135, column: 3, scope: !406)
!458 = !DILocation(line: 135, column: 10, scope: !406)
!459 = !DILocation(line: 135, column: 24, scope: !406)
!460 = !DILocation(line: 135, column: 30, scope: !406)
!461 = !DILocation(line: 139, column: 3, scope: !406)
!462 = !DILocation(line: 139, column: 10, scope: !406)
!463 = !DILocation(line: 139, column: 19, scope: !406)
!464 = !DILocation(line: 143, column: 7, scope: !465)
!465 = distinct !DILexicalBlock(scope: !406, file: !1, line: 143, column: 7)
!466 = !DILocation(line: 143, column: 14, scope: !465)
!467 = !DILocation(line: 143, column: 28, scope: !465)
!468 = !DILocation(line: 143, column: 31, scope: !469)
!469 = !DILexicalBlockFile(scope: !465, file: !1, discriminator: 1)
!470 = !DILocation(line: 143, column: 38, scope: !469)
!471 = !DILocation(line: 143, column: 51, scope: !469)
!472 = !DILocation(line: 144, column: 5, scope: !465)
!473 = !DILocation(line: 143, column: 7, scope: !469)
!474 = !DILocation(line: 145, column: 4, scope: !465)
!475 = !DILocation(line: 147, column: 7, scope: !476)
!476 = distinct !DILexicalBlock(scope: !406, file: !1, line: 147, column: 7)
!477 = !DILocation(line: 147, column: 14, scope: !476)
!478 = !DILocation(line: 148, column: 5, scope: !476)
!479 = !DILocation(line: 149, column: 6, scope: !476)
!480 = !DILocation(line: 149, column: 13, scope: !476)
!481 = !DILocation(line: 149, column: 26, scope: !476)
!482 = !DILocation(line: 148, column: 9, scope: !483)
!483 = !DILexicalBlockFile(scope: !476, file: !1, discriminator: 1)
!484 = !DILocation(line: 147, column: 7, scope: !485)
!485 = !DILexicalBlockFile(scope: !406, file: !1, discriminator: 1)
!486 = !DILocation(line: 150, column: 4, scope: !476)
!487 = !DILocation(line: 152, column: 7, scope: !488)
!488 = distinct !DILexicalBlock(scope: !406, file: !1, line: 152, column: 7)
!489 = !DILocation(line: 152, column: 14, scope: !488)
!490 = !DILocation(line: 152, column: 7, scope: !406)
!491 = !DILocation(line: 153, column: 4, scope: !488)
!492 = !DILocation(line: 154, column: 2, scope: !406)
!493 = !DILocalVariable(name: "filters", scope: !494, file: !1, line: 159, type: !495)
!494 = distinct !DILexicalBlock(scope: !407, file: !1, line: 158, column: 25)
!495 = !DICompositeType(tag: DW_TAG_array_type, baseType: !106, size: 640, align: 64, elements: !496)
!496 = !{!497}
!497 = !DISubrange(count: 5)
!498 = !DILocation(line: 159, column: 15, scope: !494)
!499 = !DILocalVariable(name: "memusage", scope: !494, file: !1, line: 160, type: !33)
!500 = !DILocation(line: 160, column: 12, scope: !494)
!501 = !DILocalVariable(name: "ret", scope: !494, file: !1, line: 161, type: !43)
!502 = !DILocation(line: 161, column: 12, scope: !494)
!503 = !DILocalVariable(name: "i", scope: !494, file: !1, line: 162, type: !53)
!504 = !DILocation(line: 162, column: 10, scope: !494)
!505 = !DILocation(line: 164, column: 8, scope: !506)
!506 = distinct !DILexicalBlock(scope: !494, file: !1, line: 164, column: 7)
!507 = !DILocation(line: 164, column: 7, scope: !506)
!508 = !DILocation(line: 164, column: 18, scope: !506)
!509 = !DILocation(line: 164, column: 15, scope: !506)
!510 = !DILocation(line: 164, column: 7, scope: !494)
!511 = !DILocation(line: 165, column: 4, scope: !506)
!512 = !DILocation(line: 167, column: 7, scope: !513)
!513 = distinct !DILexicalBlock(scope: !494, file: !1, line: 167, column: 7)
!514 = !DILocation(line: 167, column: 14, scope: !513)
!515 = !DILocation(line: 167, column: 18, scope: !513)
!516 = !DILocation(line: 167, column: 7, scope: !494)
!517 = !DILocation(line: 169, column: 12, scope: !518)
!518 = distinct !DILexicalBlock(scope: !519, file: !1, line: 169, column: 8)
!519 = distinct !DILexicalBlock(scope: !513, file: !1, line: 167, column: 24)
!520 = !DILocation(line: 169, column: 11, scope: !518)
!521 = !DILocation(line: 169, column: 8, scope: !518)
!522 = !DILocation(line: 169, column: 20, scope: !518)
!523 = !DILocation(line: 169, column: 8, scope: !519)
!524 = !DILocation(line: 170, column: 5, scope: !525)
!525 = distinct !DILexicalBlock(scope: !518, file: !1, line: 169, column: 29)
!526 = !DILocation(line: 170, column: 12, scope: !525)
!527 = !DILocation(line: 170, column: 21, scope: !525)
!528 = !DILocation(line: 171, column: 5, scope: !525)
!529 = !DILocation(line: 178, column: 8, scope: !519)
!530 = !DILocation(line: 177, column: 4, scope: !519)
!531 = !DILocation(line: 177, column: 11, scope: !519)
!532 = !DILocation(line: 177, column: 25, scope: !519)
!533 = !DILocation(line: 178, column: 6, scope: !519)
!534 = !DILocation(line: 180, column: 3, scope: !519)
!535 = !DILocation(line: 183, column: 15, scope: !494)
!536 = !DILocation(line: 183, column: 19, scope: !494)
!537 = !DILocation(line: 183, column: 27, scope: !494)
!538 = !DILocation(line: 183, column: 36, scope: !494)
!539 = !DILocation(line: 183, column: 43, scope: !494)
!540 = !DILocation(line: 183, column: 52, scope: !494)
!541 = !DILocation(line: 183, column: 59, scope: !494)
!542 = !DILocation(line: 184, column: 5, scope: !494)
!543 = !DILocation(line: 184, column: 12, scope: !494)
!544 = !DILocation(line: 184, column: 26, scope: !494)
!545 = !DILocation(line: 183, column: 3, scope: !494)
!546 = !DILocation(line: 187, column: 7, scope: !547)
!547 = distinct !DILexicalBlock(scope: !494, file: !1, line: 187, column: 7)
!548 = !DILocation(line: 187, column: 14, scope: !547)
!549 = !DILocation(line: 187, column: 20, scope: !547)
!550 = !DILocation(line: 187, column: 27, scope: !547)
!551 = !DILocation(line: 187, column: 41, scope: !547)
!552 = !DILocation(line: 187, column: 18, scope: !547)
!553 = !DILocation(line: 187, column: 7, scope: !494)
!554 = !DILocation(line: 188, column: 4, scope: !547)
!555 = !DILocation(line: 190, column: 3, scope: !494)
!556 = !DILocation(line: 190, column: 10, scope: !494)
!557 = !DILocation(line: 190, column: 14, scope: !494)
!558 = !DILocation(line: 193, column: 3, scope: !494)
!559 = !DILocation(line: 193, column: 10, scope: !494)
!560 = !DILocation(line: 193, column: 24, scope: !494)
!561 = !DILocation(line: 193, column: 32, scope: !494)
!562 = !DILocation(line: 198, column: 34, scope: !494)
!563 = !DILocation(line: 198, column: 3, scope: !494)
!564 = !DILocation(line: 198, column: 10, scope: !494)
!565 = !DILocation(line: 198, column: 24, scope: !494)
!566 = !DILocation(line: 198, column: 32, scope: !494)
!567 = !DILocation(line: 201, column: 3, scope: !494)
!568 = !DILocalVariable(name: "ret_", scope: !569, file: !1, line: 201, type: !570)
!569 = distinct !DILexicalBlock(scope: !494, file: !1, line: 201, column: 3)
!570 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !43)
!571 = !DILocation(line: 201, column: 3, scope: !569)
!572 = !DILocation(line: 201, column: 3, scope: !573)
!573 = !DILexicalBlockFile(scope: !569, file: !1, discriminator: 1)
!574 = !DILocation(line: 201, column: 3, scope: !575)
!575 = !DILexicalBlockFile(scope: !576, file: !1, discriminator: 2)
!576 = distinct !DILexicalBlock(scope: !569, file: !1, line: 201, column: 3)
!577 = !DILocation(line: 201, column: 3, scope: !578)
!578 = !DILexicalBlockFile(scope: !569, file: !1, discriminator: 3)
!579 = !DILocation(line: 205, column: 40, scope: !494)
!580 = !DILocation(line: 205, column: 14, scope: !494)
!581 = !DILocation(line: 205, column: 12, scope: !494)
!582 = !DILocation(line: 206, column: 7, scope: !583)
!583 = distinct !DILexicalBlock(scope: !494, file: !1, line: 206, column: 7)
!584 = !DILocation(line: 206, column: 16, scope: !583)
!585 = !DILocation(line: 206, column: 7, scope: !494)
!586 = !DILocation(line: 208, column: 8, scope: !587)
!587 = distinct !DILexicalBlock(scope: !583, file: !1, line: 206, column: 31)
!588 = !DILocation(line: 209, column: 3, scope: !587)
!589 = !DILocation(line: 214, column: 22, scope: !590)
!590 = distinct !DILexicalBlock(scope: !583, file: !1, line: 209, column: 10)
!591 = !DILocation(line: 214, column: 4, scope: !590)
!592 = !DILocation(line: 214, column: 11, scope: !590)
!593 = !DILocation(line: 214, column: 20, scope: !590)
!594 = !DILocation(line: 216, column: 8, scope: !595)
!595 = distinct !DILexicalBlock(scope: !590, file: !1, line: 216, column: 8)
!596 = !DILocation(line: 216, column: 19, scope: !595)
!597 = !DILocation(line: 216, column: 26, scope: !595)
!598 = !DILocation(line: 216, column: 17, scope: !595)
!599 = !DILocation(line: 216, column: 8, scope: !590)
!600 = !DILocation(line: 218, column: 9, scope: !601)
!601 = distinct !DILexicalBlock(scope: !595, file: !1, line: 216, column: 36)
!602 = !DILocation(line: 219, column: 4, scope: !601)
!603 = !DILocation(line: 223, column: 8, scope: !604)
!604 = distinct !DILexicalBlock(scope: !595, file: !1, line: 219, column: 11)
!605 = !DILocation(line: 223, column: 15, scope: !604)
!606 = !DILocation(line: 224, column: 7, scope: !604)
!607 = !DILocation(line: 225, column: 8, scope: !604)
!608 = !DILocation(line: 225, column: 15, scope: !604)
!609 = !DILocation(line: 222, column: 11, scope: !604)
!610 = !DILocation(line: 222, column: 9, scope: !604)
!611 = !DILocation(line: 231, column: 10, scope: !612)
!612 = distinct !DILexicalBlock(scope: !494, file: !1, line: 231, column: 3)
!613 = !DILocation(line: 231, column: 8, scope: !612)
!614 = !DILocation(line: 231, column: 15, scope: !615)
!615 = !DILexicalBlockFile(scope: !616, file: !1, discriminator: 1)
!616 = distinct !DILexicalBlock(scope: !612, file: !1, line: 231, column: 3)
!617 = !DILocation(line: 231, column: 17, scope: !615)
!618 = !DILocation(line: 231, column: 3, scope: !615)
!619 = !DILocation(line: 232, column: 22, scope: !616)
!620 = !DILocation(line: 232, column: 14, scope: !616)
!621 = !DILocation(line: 232, column: 25, scope: !616)
!622 = !DILocation(line: 232, column: 34, scope: !616)
!623 = !DILocation(line: 232, column: 4, scope: !616)
!624 = !DILocation(line: 231, column: 37, scope: !625)
!625 = !DILexicalBlockFile(scope: !616, file: !1, discriminator: 2)
!626 = !DILocation(line: 231, column: 3, scope: !625)
!627 = !DILocation(line: 234, column: 3, scope: !494)
!628 = !DILocation(line: 234, column: 10, scope: !494)
!629 = !DILocation(line: 234, column: 24, scope: !494)
!630 = !DILocation(line: 234, column: 32, scope: !494)
!631 = !DILocation(line: 238, column: 7, scope: !632)
!632 = distinct !DILexicalBlock(scope: !494, file: !1, line: 238, column: 7)
!633 = !DILocation(line: 238, column: 11, scope: !632)
!634 = !DILocation(line: 238, column: 7, scope: !494)
!635 = !DILocation(line: 239, column: 11, scope: !632)
!636 = !DILocation(line: 239, column: 4, scope: !632)
!637 = !DILocation(line: 241, column: 3, scope: !494)
!638 = !DILocation(line: 241, column: 10, scope: !494)
!639 = !DILocation(line: 241, column: 19, scope: !494)
!640 = !DILocation(line: 242, column: 2, scope: !494)
!641 = !DILocalVariable(name: "ret", scope: !642, file: !1, line: 247, type: !570)
!642 = distinct !DILexicalBlock(scope: !407, file: !1, line: 246, column: 18)
!643 = !DILocation(line: 247, column: 18, scope: !642)
!644 = !DILocation(line: 247, column: 24, scope: !642)
!645 = !DILocation(line: 247, column: 31, scope: !642)
!646 = !DILocation(line: 247, column: 45, scope: !642)
!647 = !DILocation(line: 248, column: 5, scope: !642)
!648 = !DILocation(line: 248, column: 12, scope: !642)
!649 = !DILocation(line: 248, column: 26, scope: !642)
!650 = !DILocation(line: 248, column: 33, scope: !642)
!651 = !DILocation(line: 249, column: 5, scope: !642)
!652 = !DILocation(line: 249, column: 9, scope: !642)
!653 = !DILocation(line: 249, column: 17, scope: !642)
!654 = !DILocation(line: 249, column: 26, scope: !642)
!655 = !DILocation(line: 249, column: 31, scope: !642)
!656 = !DILocation(line: 249, column: 40, scope: !642)
!657 = !DILocation(line: 250, column: 5, scope: !642)
!658 = !DILocation(line: 252, column: 7, scope: !659)
!659 = distinct !DILexicalBlock(scope: !642, file: !1, line: 252, column: 7)
!660 = !DILocation(line: 252, column: 11, scope: !659)
!661 = !DILocation(line: 252, column: 7, scope: !642)
!662 = !DILocation(line: 253, column: 11, scope: !659)
!663 = !DILocation(line: 253, column: 4, scope: !659)
!664 = !DILocation(line: 257, column: 3, scope: !642)
!665 = !DILocalVariable(name: "ret_", scope: !666, file: !1, line: 257, type: !570)
!666 = distinct !DILexicalBlock(scope: !642, file: !1, line: 257, column: 3)
!667 = !DILocation(line: 257, column: 3, scope: !666)
!668 = !DILocation(line: 257, column: 3, scope: !669)
!669 = !DILexicalBlockFile(scope: !666, file: !1, discriminator: 1)
!670 = !DILocation(line: 257, column: 3, scope: !671)
!671 = !DILexicalBlockFile(scope: !669, file: !1, discriminator: 4)
!672 = !DILocation(line: 257, column: 3, scope: !673)
!673 = !DILexicalBlockFile(scope: !674, file: !1, discriminator: 2)
!674 = distinct !DILexicalBlock(scope: !666, file: !1, line: 257, column: 3)
!675 = !DILocation(line: 257, column: 3, scope: !676)
!676 = !DILexicalBlockFile(scope: !666, file: !1, discriminator: 3)
!677 = !DILocation(line: 262, column: 3, scope: !642)
!678 = !DILocation(line: 262, column: 10, scope: !642)
!679 = !DILocation(line: 262, column: 19, scope: !642)
!680 = !DILocation(line: 263, column: 3, scope: !642)
!681 = !DILocalVariable(name: "ret", scope: !682, file: !1, line: 267, type: !43)
!682 = distinct !DILexicalBlock(scope: !407, file: !1, line: 266, column: 18)
!683 = !DILocation(line: 267, column: 12, scope: !682)
!684 = !DILocation(line: 272, column: 8, scope: !685)
!685 = distinct !DILexicalBlock(scope: !682, file: !1, line: 272, column: 7)
!686 = !DILocation(line: 272, column: 7, scope: !685)
!687 = !DILocation(line: 272, column: 18, scope: !685)
!688 = !DILocation(line: 272, column: 15, scope: !685)
!689 = !DILocation(line: 272, column: 7, scope: !682)
!690 = !DILocation(line: 273, column: 4, scope: !685)
!691 = !DILocation(line: 277, column: 32, scope: !682)
!692 = !DILocation(line: 277, column: 39, scope: !682)
!693 = !DILocation(line: 278, column: 5, scope: !682)
!694 = !DILocation(line: 278, column: 9, scope: !682)
!695 = !DILocation(line: 278, column: 17, scope: !682)
!696 = !DILocation(line: 277, column: 9, scope: !682)
!697 = !DILocation(line: 277, column: 7, scope: !682)
!698 = !DILocation(line: 279, column: 7, scope: !699)
!699 = distinct !DILexicalBlock(scope: !682, file: !1, line: 279, column: 7)
!700 = !DILocation(line: 279, column: 11, scope: !699)
!701 = !DILocation(line: 279, column: 7, scope: !682)
!702 = !DILocation(line: 280, column: 11, scope: !699)
!703 = !DILocation(line: 280, column: 4, scope: !699)
!704 = !DILocation(line: 282, column: 3, scope: !682)
!705 = !DILocation(line: 282, column: 10, scope: !682)
!706 = !DILocation(line: 282, column: 19, scope: !682)
!707 = !DILocation(line: 283, column: 2, scope: !682)
!708 = !DILocalVariable(name: "footer_flags", scope: !709, file: !1, line: 288, type: !159)
!709 = distinct !DILexicalBlock(scope: !407, file: !1, line: 287, column: 26)
!710 = !DILocation(line: 288, column: 21, scope: !709)
!711 = !DILocalVariable(name: "ret", scope: !709, file: !1, line: 289, type: !43)
!712 = !DILocation(line: 289, column: 12, scope: !709)
!713 = !DILocation(line: 292, column: 15, scope: !709)
!714 = !DILocation(line: 292, column: 19, scope: !709)
!715 = !DILocation(line: 292, column: 27, scope: !709)
!716 = !DILocation(line: 292, column: 36, scope: !709)
!717 = !DILocation(line: 292, column: 43, scope: !709)
!718 = !DILocation(line: 292, column: 52, scope: !709)
!719 = !DILocation(line: 292, column: 59, scope: !709)
!720 = !DILocation(line: 292, column: 3, scope: !709)
!721 = !DILocation(line: 296, column: 7, scope: !722)
!722 = distinct !DILexicalBlock(scope: !709, file: !1, line: 296, column: 7)
!723 = !DILocation(line: 296, column: 14, scope: !722)
!724 = !DILocation(line: 296, column: 18, scope: !722)
!725 = !DILocation(line: 296, column: 7, scope: !709)
!726 = !DILocation(line: 297, column: 4, scope: !722)
!727 = !DILocation(line: 299, column: 3, scope: !709)
!728 = !DILocation(line: 299, column: 10, scope: !709)
!729 = !DILocation(line: 299, column: 14, scope: !709)
!730 = !DILocation(line: 305, column: 20, scope: !709)
!731 = !DILocation(line: 305, column: 27, scope: !709)
!732 = !DILocation(line: 304, column: 9, scope: !709)
!733 = !DILocation(line: 304, column: 7, scope: !709)
!734 = !DILocation(line: 306, column: 7, scope: !735)
!735 = distinct !DILexicalBlock(scope: !709, file: !1, line: 306, column: 7)
!736 = !DILocation(line: 306, column: 11, scope: !735)
!737 = !DILocation(line: 306, column: 7, scope: !709)
!738 = !DILocation(line: 307, column: 11, scope: !735)
!739 = !DILocation(line: 307, column: 15, scope: !735)
!740 = !DILocation(line: 307, column: 11, scope: !741)
!741 = !DILexicalBlockFile(scope: !735, file: !1, discriminator: 1)
!742 = !DILocation(line: 308, column: 26, scope: !735)
!743 = !DILocation(line: 307, column: 11, scope: !744)
!744 = !DILexicalBlockFile(scope: !735, file: !1, discriminator: 2)
!745 = !DILocation(line: 307, column: 11, scope: !746)
!746 = !DILexicalBlockFile(scope: !735, file: !1, discriminator: 3)
!747 = !DILocation(line: 307, column: 4, scope: !746)
!748 = !DILocation(line: 312, column: 28, scope: !749)
!749 = distinct !DILexicalBlock(scope: !709, file: !1, line: 312, column: 7)
!750 = !DILocation(line: 312, column: 35, scope: !749)
!751 = !DILocation(line: 312, column: 7, scope: !749)
!752 = !DILocation(line: 313, column: 21, scope: !749)
!753 = !DILocation(line: 313, column: 5, scope: !749)
!754 = !DILocation(line: 312, column: 7, scope: !709)
!755 = !DILocation(line: 314, column: 4, scope: !749)
!756 = !DILocation(line: 318, column: 3, scope: !709)
!757 = !DILocalVariable(name: "ret_", scope: !758, file: !1, line: 318, type: !570)
!758 = distinct !DILexicalBlock(scope: !709, file: !1, line: 318, column: 3)
!759 = !DILocation(line: 318, column: 3, scope: !758)
!760 = !DILocation(line: 318, column: 3, scope: !761)
!761 = !DILexicalBlockFile(scope: !758, file: !1, discriminator: 1)
!762 = !DILocation(line: 318, column: 3, scope: !763)
!763 = !DILexicalBlockFile(scope: !764, file: !1, discriminator: 2)
!764 = distinct !DILexicalBlock(scope: !758, file: !1, line: 318, column: 3)
!765 = !DILocation(line: 318, column: 3, scope: !766)
!766 = !DILexicalBlockFile(scope: !758, file: !1, discriminator: 3)
!767 = !DILocation(line: 321, column: 8, scope: !768)
!768 = distinct !DILexicalBlock(scope: !709, file: !1, line: 321, column: 7)
!769 = !DILocation(line: 321, column: 15, scope: !768)
!770 = !DILocation(line: 321, column: 7, scope: !709)
!771 = !DILocation(line: 322, column: 4, scope: !768)
!772 = !DILocation(line: 324, column: 3, scope: !709)
!773 = !DILocation(line: 324, column: 10, scope: !709)
!774 = !DILocation(line: 324, column: 19, scope: !709)
!775 = !DILocation(line: 325, column: 2, scope: !709)
!776 = !DILocation(line: 330, column: 3, scope: !407)
!777 = !DILocation(line: 330, column: 3, scope: !778)
!778 = !DILexicalBlockFile(scope: !407, file: !1, discriminator: 1)
!779 = !DILocation(line: 330, column: 3, scope: !780)
!780 = !DILexicalBlockFile(scope: !407, file: !1, discriminator: 2)
!781 = !DILocation(line: 330, column: 3, scope: !782)
!782 = !DILexicalBlockFile(scope: !407, file: !1, discriminator: 3)
!783 = !DILocation(line: 333, column: 3, scope: !407)
!784 = !DILocation(line: 334, column: 9, scope: !785)
!785 = distinct !DILexicalBlock(scope: !786, file: !1, line: 334, column: 8)
!786 = distinct !DILexicalBlock(scope: !407, file: !1, line: 333, column: 16)
!787 = !DILocation(line: 334, column: 8, scope: !785)
!788 = !DILocation(line: 334, column: 19, scope: !785)
!789 = !DILocation(line: 334, column: 16, scope: !785)
!790 = !DILocation(line: 334, column: 8, scope: !786)
!791 = !DILocation(line: 337, column: 9, scope: !792)
!792 = distinct !DILexicalBlock(scope: !793, file: !1, line: 337, column: 9)
!793 = distinct !DILexicalBlock(scope: !785, file: !1, line: 334, column: 28)
!794 = !DILocation(line: 337, column: 16, scope: !792)
!795 = !DILocation(line: 337, column: 9, scope: !793)
!796 = !DILocation(line: 338, column: 6, scope: !792)
!797 = !DILocation(line: 342, column: 12, scope: !793)
!798 = !DILocation(line: 342, column: 19, scope: !793)
!799 = !DILocation(line: 342, column: 23, scope: !793)
!800 = !DILocation(line: 342, column: 5, scope: !793)
!801 = !DILocation(line: 349, column: 12, scope: !802)
!802 = distinct !DILexicalBlock(scope: !786, file: !1, line: 349, column: 8)
!803 = !DILocation(line: 349, column: 11, scope: !802)
!804 = !DILocation(line: 349, column: 8, scope: !802)
!805 = !DILocation(line: 349, column: 20, scope: !802)
!806 = !DILocation(line: 349, column: 8, scope: !786)
!807 = !DILocation(line: 350, column: 5, scope: !802)
!808 = !DILocation(line: 352, column: 7, scope: !786)
!809 = !DILocation(line: 352, column: 4, scope: !786)
!810 = !DILocation(line: 353, column: 18, scope: !786)
!811 = !DILocation(line: 353, column: 25, scope: !786)
!812 = !DILocation(line: 353, column: 29, scope: !786)
!813 = !DILocation(line: 353, column: 34, scope: !786)
!814 = !DILocation(line: 353, column: 4, scope: !786)
!815 = !DILocation(line: 353, column: 11, scope: !786)
!816 = !DILocation(line: 353, column: 15, scope: !786)
!817 = !DILocation(line: 333, column: 3, scope: !778)
!818 = !DILocation(line: 358, column: 7, scope: !819)
!819 = distinct !DILexicalBlock(scope: !407, file: !1, line: 358, column: 7)
!820 = !DILocation(line: 358, column: 14, scope: !819)
!821 = !DILocation(line: 358, column: 18, scope: !819)
!822 = !DILocation(line: 358, column: 7, scope: !407)
!823 = !DILocation(line: 359, column: 7, scope: !824)
!824 = distinct !DILexicalBlock(scope: !819, file: !1, line: 358, column: 24)
!825 = !DILocation(line: 359, column: 4, scope: !824)
!826 = !DILocation(line: 360, column: 4, scope: !824)
!827 = !DILocation(line: 364, column: 3, scope: !407)
!828 = !DILocalVariable(name: "ret_", scope: !829, file: !1, line: 364, type: !570)
!829 = distinct !DILexicalBlock(scope: !407, file: !1, line: 364, column: 3)
!830 = !DILocation(line: 364, column: 3, scope: !829)
!831 = !DILocation(line: 364, column: 3, scope: !832)
!832 = !DILexicalBlockFile(scope: !829, file: !1, discriminator: 1)
!833 = !DILocation(line: 364, column: 3, scope: !834)
!834 = !DILexicalBlockFile(scope: !835, file: !1, discriminator: 2)
!835 = distinct !DILexicalBlock(scope: !829, file: !1, line: 364, column: 3)
!836 = !DILocation(line: 364, column: 3, scope: !837)
!837 = !DILexicalBlockFile(scope: !829, file: !1, discriminator: 3)
!838 = !DILocation(line: 365, column: 3, scope: !407)
!839 = !DILocation(line: 368, column: 3, scope: !407)
!840 = !DILocation(line: 106, column: 2, scope: !841)
!841 = !DILexicalBlockFile(scope: !257, file: !1, discriminator: 1)
!842 = !DILocation(line: 373, column: 1, scope: !257)
!843 = !DILocalVariable(name: "coder", arg: 1, scope: !258, file: !1, line: 377, type: !28)
!844 = !DILocation(line: 377, column: 32, scope: !258)
!845 = !DILocalVariable(name: "allocator", arg: 2, scope: !258, file: !1, line: 377, type: !44)
!846 = !DILocation(line: 377, column: 55, scope: !258)
!847 = !DILocation(line: 379, column: 17, scope: !258)
!848 = !DILocation(line: 379, column: 24, scope: !258)
!849 = !DILocation(line: 379, column: 39, scope: !258)
!850 = !DILocation(line: 379, column: 2, scope: !258)
!851 = !DILocation(line: 380, column: 22, scope: !258)
!852 = !DILocation(line: 380, column: 29, scope: !258)
!853 = !DILocation(line: 380, column: 41, scope: !258)
!854 = !DILocation(line: 380, column: 2, scope: !258)
!855 = !DILocation(line: 381, column: 12, scope: !258)
!856 = !DILocation(line: 381, column: 19, scope: !258)
!857 = !DILocation(line: 381, column: 2, scope: !258)
!858 = !DILocation(line: 382, column: 2, scope: !258)
!859 = !DILocalVariable(name: "coder", arg: 1, scope: !259, file: !1, line: 387, type: !93)
!860 = !DILocation(line: 387, column: 44, scope: !259)
!861 = !DILocation(line: 389, column: 9, scope: !259)
!862 = !DILocation(line: 389, column: 16, scope: !259)
!863 = !DILocation(line: 389, column: 29, scope: !259)
!864 = !DILocation(line: 389, column: 2, scope: !259)
!865 = !DILocalVariable(name: "coder", arg: 1, scope: !260, file: !1, line: 394, type: !28)
!866 = !DILocation(line: 394, column: 38, scope: !260)
!867 = !DILocalVariable(name: "memusage", arg: 2, scope: !260, file: !1, line: 394, type: !99)
!868 = !DILocation(line: 394, column: 55, scope: !260)
!869 = !DILocalVariable(name: "old_memlimit", arg: 3, scope: !260, file: !1, line: 395, type: !99)
!870 = !DILocation(line: 395, column: 13, scope: !260)
!871 = !DILocalVariable(name: "new_memlimit", arg: 4, scope: !260, file: !1, line: 395, type: !33)
!872 = !DILocation(line: 395, column: 36, scope: !260)
!873 = !DILocation(line: 397, column: 14, scope: !260)
!874 = !DILocation(line: 397, column: 21, scope: !260)
!875 = !DILocation(line: 397, column: 3, scope: !260)
!876 = !DILocation(line: 397, column: 12, scope: !260)
!877 = !DILocation(line: 398, column: 18, scope: !260)
!878 = !DILocation(line: 398, column: 25, scope: !260)
!879 = !DILocation(line: 398, column: 3, scope: !260)
!880 = !DILocation(line: 398, column: 16, scope: !260)
!881 = !DILocation(line: 400, column: 6, scope: !882)
!882 = distinct !DILexicalBlock(scope: !260, file: !1, line: 400, column: 6)
!883 = !DILocation(line: 400, column: 19, scope: !882)
!884 = !DILocation(line: 400, column: 6, scope: !260)
!885 = !DILocation(line: 401, column: 7, scope: !886)
!886 = distinct !DILexicalBlock(scope: !887, file: !1, line: 401, column: 7)
!887 = distinct !DILexicalBlock(scope: !882, file: !1, line: 400, column: 25)
!888 = !DILocation(line: 401, column: 22, scope: !886)
!889 = !DILocation(line: 401, column: 29, scope: !886)
!890 = !DILocation(line: 401, column: 20, scope: !886)
!891 = !DILocation(line: 401, column: 7, scope: !887)
!892 = !DILocation(line: 402, column: 4, scope: !886)
!893 = !DILocation(line: 404, column: 21, scope: !887)
!894 = !DILocation(line: 404, column: 3, scope: !887)
!895 = !DILocation(line: 404, column: 10, scope: !887)
!896 = !DILocation(line: 404, column: 19, scope: !887)
!897 = !DILocation(line: 405, column: 2, scope: !887)
!898 = !DILocation(line: 407, column: 2, scope: !260)
!899 = !DILocation(line: 408, column: 1, scope: !260)
!900 = !DILocalVariable(name: "coder", arg: 1, scope: !261, file: !1, line: 83, type: !28)
!901 = !DILocation(line: 83, column: 34, scope: !261)
!902 = !DILocalVariable(name: "allocator", arg: 2, scope: !261, file: !1, line: 83, type: !44)
!903 = !DILocation(line: 83, column: 57, scope: !261)
!904 = !DILocation(line: 86, column: 43, scope: !261)
!905 = !DILocation(line: 86, column: 50, scope: !261)
!906 = !DILocation(line: 86, column: 62, scope: !261)
!907 = !DILocation(line: 86, column: 22, scope: !261)
!908 = !DILocation(line: 86, column: 2, scope: !261)
!909 = !DILocation(line: 86, column: 9, scope: !261)
!910 = !DILocation(line: 86, column: 20, scope: !261)
!911 = !DILocation(line: 87, column: 6, scope: !912)
!912 = distinct !DILexicalBlock(scope: !261, file: !1, line: 87, column: 6)
!913 = !DILocation(line: 87, column: 13, scope: !912)
!914 = !DILocation(line: 87, column: 24, scope: !912)
!915 = !DILocation(line: 87, column: 6, scope: !261)
!916 = !DILocation(line: 88, column: 3, scope: !912)
!917 = !DILocation(line: 91, column: 2, scope: !261)
!918 = !DILocation(line: 91, column: 9, scope: !261)
!919 = !DILocation(line: 91, column: 18, scope: !261)
!920 = !DILocation(line: 92, column: 2, scope: !261)
!921 = !DILocation(line: 92, column: 9, scope: !261)
!922 = !DILocation(line: 92, column: 13, scope: !261)
!923 = !DILocation(line: 94, column: 2, scope: !261)
!924 = !DILocation(line: 95, column: 1, scope: !261)
!925 = !DILocalVariable(name: "strm", arg: 1, scope: !230, file: !1, line: 451, type: !233)
!926 = !DILocation(line: 451, column: 34, scope: !230)
!927 = !DILocalVariable(name: "memlimit", arg: 2, scope: !230, file: !1, line: 451, type: !33)
!928 = !DILocation(line: 451, column: 49, scope: !230)
!929 = !DILocalVariable(name: "flags", arg: 3, scope: !230, file: !1, line: 451, type: !118)
!930 = !DILocation(line: 451, column: 68, scope: !230)
!931 = !DILocation(line: 453, column: 2, scope: !230)
!932 = !DILocalVariable(name: "ret_", scope: !933, file: !1, line: 453, type: !43)
!933 = distinct !DILexicalBlock(scope: !230, file: !1, line: 453, column: 2)
!934 = !DILocation(line: 453, column: 2, scope: !933)
!935 = !DILocation(line: 453, column: 2, scope: !936)
!936 = !DILexicalBlockFile(scope: !933, file: !1, discriminator: 1)
!937 = !DILocalVariable(name: "ret_", scope: !938, file: !1, line: 453, type: !570)
!938 = distinct !DILexicalBlock(scope: !933, file: !1, line: 453, column: 2)
!939 = !DILocation(line: 453, column: 2, scope: !938)
!940 = !DILocation(line: 453, column: 2, scope: !941)
!941 = !DILexicalBlockFile(scope: !938, file: !1, discriminator: 2)
!942 = !DILocation(line: 453, column: 2, scope: !943)
!943 = !DILexicalBlockFile(scope: !944, file: !1, discriminator: 3)
!944 = distinct !DILexicalBlock(scope: !938, file: !1, line: 453, column: 2)
!945 = !DILocation(line: 453, column: 2, scope: !946)
!946 = !DILexicalBlockFile(scope: !938, file: !1, discriminator: 4)
!947 = !DILocation(line: 453, column: 2, scope: !948)
!948 = !DILexicalBlockFile(scope: !933, file: !1, discriminator: 5)
!949 = !DILocation(line: 453, column: 2, scope: !950)
!950 = !DILexicalBlockFile(scope: !951, file: !1, discriminator: 6)
!951 = distinct !DILexicalBlock(scope: !952, file: !1, line: 453, column: 2)
!952 = distinct !DILexicalBlock(scope: !933, file: !1, line: 453, column: 2)
!953 = !DILocation(line: 453, column: 2, scope: !954)
!954 = !DILexicalBlockFile(scope: !933, file: !1, discriminator: 7)
!955 = !DILocation(line: 455, column: 2, scope: !230)
!956 = !DILocation(line: 455, column: 8, scope: !230)
!957 = !DILocation(line: 455, column: 18, scope: !230)
!958 = !DILocation(line: 455, column: 46, scope: !230)
!959 = !DILocation(line: 456, column: 2, scope: !230)
!960 = !DILocation(line: 456, column: 8, scope: !230)
!961 = !DILocation(line: 456, column: 18, scope: !230)
!962 = !DILocation(line: 456, column: 49, scope: !230)
!963 = !DILocation(line: 458, column: 2, scope: !230)
!964 = !DILocation(line: 459, column: 1, scope: !230)
