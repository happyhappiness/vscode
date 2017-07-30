; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/block_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type { %struct.lzma_next_coder_s, %struct.lzma_block*, i32, i64, i64, i64, %struct.lzma_check_state }
%struct.lzma_block = type { i32, i32, i32, i64, i64, %struct.lzma_filter*, [64 x i8], i8*, i8*, i8*, i32, i32, i64, i64, i64, i64, i64, i64, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8, i8, i8 }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_check_state = type { %union.anon, %union.anon.0 }
%union.anon = type { [8 x i64] }
%union.anon.0 = type { %struct.anon }
%struct.anon = type { [8 x i32], i64 }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_stream = type { i8*, i64, i64, i8*, i64, i64, %struct.lzma_allocator*, %struct.lzma_internal_s*, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i32, i32 }
%struct.lzma_internal_s = type { %struct.lzma_next_coder_s, i32, i64, [4 x i8], i8 }

@LZMA_NEXT_CODER_INIT = internal constant %struct.lzma_next_coder_s { %struct.lzma_coder_s* null, i64 -1, i64 0, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* null, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* null, i32 (%struct.lzma_coder_s*)* null, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* null, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* null }, align 8
@.str = private unnamed_addr constant [19 x i8] c"*in_pos == in_size\00", align 1
@.str.1 = private unnamed_addr constant [85 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/block_encoder.c\00", align 1
@__PRETTY_FUNCTION__.block_encode = private unnamed_addr constant [163 x i8] c"lzma_ret block_encode(lzma_coder *, lzma_allocator *, const uint8_t *restrict, size_t *restrict, size_t, uint8_t *restrict, size_t *restrict, size_t, lzma_action)\00", align 1
@.str.2 = private unnamed_addr constant [22 x i8] c"action == LZMA_FINISH\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_block_encoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_block* %block) #0 !dbg !215 {
entry:
  %retval = alloca i32, align 4
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %block.addr = alloca %struct.lzma_block*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !256, metadata !257), !dbg !258
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !259, metadata !257), !dbg !260
  store %struct.lzma_block* %block, %struct.lzma_block** %block.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_block** %block.addr, metadata !261, metadata !257), !dbg !262
  br label %do.body, !dbg !263

do.body:                                          ; preds = %entry
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !264
  %init = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %0, i32 0, i32 2, !dbg !264
  %1 = load i64, i64* %init, align 8, !dbg !264
  %cmp = icmp ne i64 ptrtoint (i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_block*)* @lzma_block_encoder_init to i64), %1, !dbg !264
  br i1 %cmp, label %if.then, label %if.end, !dbg !264

if.then:                                          ; preds = %do.body
  %2 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !268
  %3 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !268
  call void @lzma_next_end(%struct.lzma_next_coder_s* %2, %struct.lzma_allocator* %3), !dbg !268
  br label %if.end, !dbg !268

if.end:                                           ; preds = %if.then, %do.body
  %4 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !270
  %init1 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %4, i32 0, i32 2, !dbg !270
  store i64 ptrtoint (i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_block*)* @lzma_block_encoder_init to i64), i64* %init1, align 8, !dbg !270
  br label %do.end, !dbg !270

do.end:                                           ; preds = %if.end
  %5 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !272
  %cmp2 = icmp eq %struct.lzma_block* %5, null, !dbg !274
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !275

if.then3:                                         ; preds = %do.end
  store i32 11, i32* %retval, align 4, !dbg !276
  br label %return, !dbg !276

if.end4:                                          ; preds = %do.end
  %6 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !277
  %version = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %6, i32 0, i32 0, !dbg !279
  %7 = load i32, i32* %version, align 8, !dbg !279
  %cmp5 = icmp ne i32 %7, 0, !dbg !280
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !281

if.then6:                                         ; preds = %if.end4
  store i32 8, i32* %retval, align 4, !dbg !282
  br label %return, !dbg !282

if.end7:                                          ; preds = %if.end4
  %8 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !283
  %check = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %8, i32 0, i32 2, !dbg !285
  %9 = load i32, i32* %check, align 8, !dbg !285
  %cmp8 = icmp ugt i32 %9, 15, !dbg !286
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !287

if.then9:                                         ; preds = %if.end7
  store i32 11, i32* %retval, align 4, !dbg !288
  br label %return, !dbg !288

if.end10:                                         ; preds = %if.end7
  %10 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !289
  %check11 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %10, i32 0, i32 2, !dbg !291
  %11 = load i32, i32* %check11, align 8, !dbg !291
  %call = call zeroext i8 @lzma_check_is_supported(i32 %11) #1, !dbg !292
  %tobool = icmp ne i8 %call, 0, !dbg !292
  br i1 %tobool, label %if.end13, label %if.then12, !dbg !293

if.then12:                                        ; preds = %if.end10
  store i32 3, i32* %retval, align 4, !dbg !294
  br label %return, !dbg !294

if.end13:                                         ; preds = %if.end10
  %12 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !295
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %12, i32 0, i32 0, !dbg !297
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !297
  %cmp14 = icmp eq %struct.lzma_coder_s* %13, null, !dbg !298
  br i1 %cmp14, label %if.then15, label %if.end24, !dbg !299

if.then15:                                        ; preds = %if.end13
  %14 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !300
  %call16 = call noalias i8* @lzma_alloc(i64 208, %struct.lzma_allocator* %14), !dbg !302
  %15 = bitcast i8* %call16 to %struct.lzma_coder_s*, !dbg !302
  %16 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !303
  %coder17 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %16, i32 0, i32 0, !dbg !304
  store %struct.lzma_coder_s* %15, %struct.lzma_coder_s** %coder17, align 8, !dbg !305
  %17 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !306
  %coder18 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %17, i32 0, i32 0, !dbg !308
  %18 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder18, align 8, !dbg !308
  %cmp19 = icmp eq %struct.lzma_coder_s* %18, null, !dbg !309
  br i1 %cmp19, label %if.then20, label %if.end21, !dbg !310

if.then20:                                        ; preds = %if.then15
  store i32 5, i32* %retval, align 4, !dbg !311
  br label %return, !dbg !311

if.end21:                                         ; preds = %if.then15
  %19 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !312
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %19, i32 0, i32 3, !dbg !313
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* @block_encode, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !314
  %20 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !315
  %end = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %20, i32 0, i32 4, !dbg !316
  store void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* @block_encoder_end, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !317
  %21 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !318
  %update = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %21, i32 0, i32 7, !dbg !319
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* @block_encoder_update, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)** %update, align 8, !dbg !320
  %22 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !321
  %coder22 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %22, i32 0, i32 0, !dbg !322
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder22, align 8, !dbg !322
  %next23 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 0, !dbg !323
  %24 = bitcast %struct.lzma_next_coder_s* %next23 to i8*, !dbg !324
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %24, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !324
  br label %if.end24, !dbg !325

if.end24:                                         ; preds = %if.end21, %if.end13
  %25 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !326
  %coder25 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %25, i32 0, i32 0, !dbg !327
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder25, align 8, !dbg !327
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %26, i32 0, i32 2, !dbg !328
  store i32 0, i32* %sequence, align 8, !dbg !329
  %27 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !330
  %28 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !331
  %coder26 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %28, i32 0, i32 0, !dbg !332
  %29 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder26, align 8, !dbg !332
  %block27 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %29, i32 0, i32 1, !dbg !333
  store %struct.lzma_block* %27, %struct.lzma_block** %block27, align 8, !dbg !334
  %30 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !335
  %coder28 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %30, i32 0, i32 0, !dbg !336
  %31 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder28, align 8, !dbg !336
  %compressed_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %31, i32 0, i32 3, !dbg !337
  store i64 0, i64* %compressed_size, align 8, !dbg !338
  %32 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !339
  %coder29 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %32, i32 0, i32 0, !dbg !340
  %33 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder29, align 8, !dbg !340
  %uncompressed_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %33, i32 0, i32 4, !dbg !341
  store i64 0, i64* %uncompressed_size, align 8, !dbg !342
  %34 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !343
  %coder30 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %34, i32 0, i32 0, !dbg !344
  %35 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder30, align 8, !dbg !344
  %pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %35, i32 0, i32 5, !dbg !345
  store i64 0, i64* %pos, align 8, !dbg !346
  %36 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !347
  %coder31 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %36, i32 0, i32 0, !dbg !348
  %37 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder31, align 8, !dbg !348
  %check32 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %37, i32 0, i32 6, !dbg !349
  %38 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !350
  %check33 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %38, i32 0, i32 2, !dbg !351
  %39 = load i32, i32* %check33, align 8, !dbg !351
  call void @lzma_check_init(%struct.lzma_check_state* %check32, i32 %39), !dbg !352
  %40 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !353
  %coder34 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %40, i32 0, i32 0, !dbg !354
  %41 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder34, align 8, !dbg !354
  %next35 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %41, i32 0, i32 0, !dbg !355
  %42 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !356
  %43 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !357
  %filters = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %43, i32 0, i32 5, !dbg !358
  %44 = load %struct.lzma_filter*, %struct.lzma_filter** %filters, align 8, !dbg !358
  %call36 = call i32 @lzma_raw_encoder_init(%struct.lzma_next_coder_s* %next35, %struct.lzma_allocator* %42, %struct.lzma_filter* %44), !dbg !359
  store i32 %call36, i32* %retval, align 4, !dbg !360
  br label %return, !dbg !360

return:                                           ; preds = %if.end24, %if.then20, %if.then12, %if.then9, %if.then6, %if.then3
  %45 = load i32, i32* %retval, align 4, !dbg !361
  ret i32 %45, !dbg !361
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @lzma_next_end(%struct.lzma_next_coder_s*, %struct.lzma_allocator*) #2

; Function Attrs: nounwind readnone
declare zeroext i8 @lzma_check_is_supported(i32) #3

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #2

; Function Attrs: nounwind uwtable
define internal i32 @block_encode(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, i8* noalias %in, i64* noalias %in_pos, i64 %in_size, i8* noalias %out, i64* noalias %out_pos, i64 %out_size, i32 %action) #0 !dbg !247 {
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
  %in_start = alloca i64, align 8
  %out_start = alloca i64, align 8
  %ret = alloca i32, align 4
  %in_used = alloca i64, align 8
  %out_used = alloca i64, align 8
  %check_size = alloca i64, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !362, metadata !257), !dbg !363
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !364, metadata !257), !dbg !365
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !366, metadata !257), !dbg !367
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !368, metadata !257), !dbg !369
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !370, metadata !257), !dbg !371
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !372, metadata !257), !dbg !373
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !374, metadata !257), !dbg !375
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !376, metadata !257), !dbg !377
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !378, metadata !257), !dbg !379
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !380
  %uncompressed_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 4, !dbg !382
  %1 = load i64, i64* %uncompressed_size, align 8, !dbg !382
  %sub = sub i64 9223372036854775807, %1, !dbg !383
  %2 = load i64, i64* %in_size.addr, align 8, !dbg !384
  %3 = load i64*, i64** %in_pos.addr, align 8, !dbg !385
  %4 = load i64, i64* %3, align 8, !dbg !386
  %sub1 = sub i64 %2, %4, !dbg !387
  %cmp = icmp ult i64 %sub, %sub1, !dbg !388
  br i1 %cmp, label %if.then, label %if.end, !dbg !389

if.then:                                          ; preds = %entry
  store i32 9, i32* %retval, align 4, !dbg !390
  br label %return, !dbg !390

if.end:                                           ; preds = %entry
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !391
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 2, !dbg !392
  %6 = load i32, i32* %sequence, align 8, !dbg !392
  switch i32 %6, label %sw.epilog [
    i32 0, label %sw.bb
    i32 1, label %sw.bb30
    i32 2, label %sw.bb46
  ], !dbg !393

sw.bb:                                            ; preds = %if.end
  call void @llvm.dbg.declare(metadata i64* %in_start, metadata !394, metadata !257), !dbg !398
  %7 = load i64*, i64** %in_pos.addr, align 8, !dbg !399
  %8 = load i64, i64* %7, align 8, !dbg !400
  store i64 %8, i64* %in_start, align 8, !dbg !398
  call void @llvm.dbg.declare(metadata i64* %out_start, metadata !401, metadata !257), !dbg !402
  %9 = load i64*, i64** %out_pos.addr, align 8, !dbg !403
  %10 = load i64, i64* %9, align 8, !dbg !404
  store i64 %10, i64* %out_start, align 8, !dbg !402
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !405, metadata !257), !dbg !407
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !408
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 0, !dbg !409
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 3, !dbg !410
  %12 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !410
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !411
  %next2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %13, i32 0, i32 0, !dbg !412
  %coder3 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next2, i32 0, i32 0, !dbg !413
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder3, align 8, !dbg !413
  %15 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !414
  %16 = load i8*, i8** %in.addr, align 8, !dbg !415
  %17 = load i64*, i64** %in_pos.addr, align 8, !dbg !416
  %18 = load i64, i64* %in_size.addr, align 8, !dbg !417
  %19 = load i8*, i8** %out.addr, align 8, !dbg !418
  %20 = load i64*, i64** %out_pos.addr, align 8, !dbg !419
  %21 = load i64, i64* %out_size.addr, align 8, !dbg !420
  %22 = load i32, i32* %action.addr, align 4, !dbg !421
  %call = call i32 %12(%struct.lzma_coder_s* %14, %struct.lzma_allocator* %15, i8* %16, i64* %17, i64 %18, i8* %19, i64* %20, i64 %21, i32 %22), !dbg !408
  store i32 %call, i32* %ret, align 4, !dbg !407
  call void @llvm.dbg.declare(metadata i64* %in_used, metadata !422, metadata !257), !dbg !423
  %23 = load i64*, i64** %in_pos.addr, align 8, !dbg !424
  %24 = load i64, i64* %23, align 8, !dbg !425
  %25 = load i64, i64* %in_start, align 8, !dbg !426
  %sub4 = sub i64 %24, %25, !dbg !427
  store i64 %sub4, i64* %in_used, align 8, !dbg !423
  call void @llvm.dbg.declare(metadata i64* %out_used, metadata !428, metadata !257), !dbg !429
  %26 = load i64*, i64** %out_pos.addr, align 8, !dbg !430
  %27 = load i64, i64* %26, align 8, !dbg !431
  %28 = load i64, i64* %out_start, align 8, !dbg !432
  %sub5 = sub i64 %27, %28, !dbg !433
  store i64 %sub5, i64* %out_used, align 8, !dbg !429
  %29 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !434
  %compressed_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %29, i32 0, i32 3, !dbg !436
  %30 = load i64, i64* %compressed_size, align 8, !dbg !436
  %sub6 = sub i64 9223372036854774716, %30, !dbg !437
  %31 = load i64, i64* %out_used, align 8, !dbg !438
  %cmp7 = icmp ult i64 %sub6, %31, !dbg !439
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !440

if.then8:                                         ; preds = %sw.bb
  store i32 9, i32* %retval, align 4, !dbg !441
  br label %return, !dbg !441

if.end9:                                          ; preds = %sw.bb
  %32 = load i64, i64* %out_used, align 8, !dbg !442
  %33 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !443
  %compressed_size10 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %33, i32 0, i32 3, !dbg !444
  %34 = load i64, i64* %compressed_size10, align 8, !dbg !445
  %add = add i64 %34, %32, !dbg !445
  store i64 %add, i64* %compressed_size10, align 8, !dbg !445
  %35 = load i64, i64* %in_used, align 8, !dbg !446
  %36 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !447
  %uncompressed_size11 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %36, i32 0, i32 4, !dbg !448
  %37 = load i64, i64* %uncompressed_size11, align 8, !dbg !449
  %add12 = add i64 %37, %35, !dbg !449
  store i64 %add12, i64* %uncompressed_size11, align 8, !dbg !449
  %38 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !450
  %check = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %38, i32 0, i32 6, !dbg !451
  %39 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !452
  %block = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %39, i32 0, i32 1, !dbg !453
  %40 = load %struct.lzma_block*, %struct.lzma_block** %block, align 8, !dbg !453
  %check13 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %40, i32 0, i32 2, !dbg !454
  %41 = load i32, i32* %check13, align 8, !dbg !454
  %42 = load i8*, i8** %in.addr, align 8, !dbg !455
  %43 = load i64, i64* %in_start, align 8, !dbg !456
  %add.ptr = getelementptr inbounds i8, i8* %42, i64 %43, !dbg !457
  %44 = load i64, i64* %in_used, align 8, !dbg !458
  call void @lzma_check_update(%struct.lzma_check_state* %check, i32 %41, i8* %add.ptr, i64 %44), !dbg !459
  %45 = load i32, i32* %ret, align 4, !dbg !460
  %cmp14 = icmp ne i32 %45, 1, !dbg !462
  br i1 %cmp14, label %if.then16, label %lor.lhs.false, !dbg !463

lor.lhs.false:                                    ; preds = %if.end9
  %46 = load i32, i32* %action.addr, align 4, !dbg !464
  %cmp15 = icmp eq i32 %46, 1, !dbg !466
  br i1 %cmp15, label %if.then16, label %if.end17, !dbg !467

if.then16:                                        ; preds = %lor.lhs.false, %if.end9
  %47 = load i32, i32* %ret, align 4, !dbg !468
  store i32 %47, i32* %retval, align 4, !dbg !469
  br label %return, !dbg !469

if.end17:                                         ; preds = %lor.lhs.false
  %48 = load i64*, i64** %in_pos.addr, align 8, !dbg !470
  %49 = load i64, i64* %48, align 8, !dbg !470
  %50 = load i64, i64* %in_size.addr, align 8, !dbg !470
  %cmp18 = icmp eq i64 %49, %50, !dbg !470
  br i1 %cmp18, label %cond.true, label %cond.false, !dbg !470

cond.true:                                        ; preds = %if.end17
  br label %cond.end, !dbg !471

cond.false:                                       ; preds = %if.end17
  call void @__assert_fail(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([85 x i8], [85 x i8]* @.str.1, i32 0, i32 0), i32 84, i8* getelementptr inbounds ([163 x i8], [163 x i8]* @__PRETTY_FUNCTION__.block_encode, i32 0, i32 0)) #7, !dbg !473
  unreachable, !dbg !473
                                                  ; No predecessors!
  br label %cond.end, !dbg !475

cond.end:                                         ; preds = %51, %cond.true
  %52 = load i32, i32* %action.addr, align 4, !dbg !477
  %cmp19 = icmp eq i32 %52, 3, !dbg !477
  br i1 %cmp19, label %cond.true20, label %cond.false21, !dbg !477

cond.true20:                                      ; preds = %cond.end
  br label %cond.end22, !dbg !478

cond.false21:                                     ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([85 x i8], [85 x i8]* @.str.1, i32 0, i32 0), i32 85, i8* getelementptr inbounds ([163 x i8], [163 x i8]* @__PRETTY_FUNCTION__.block_encode, i32 0, i32 0)) #7, !dbg !479
  unreachable, !dbg !479
                                                  ; No predecessors!
  br label %cond.end22, !dbg !480

cond.end22:                                       ; preds = %53, %cond.true20
  %54 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !481
  %compressed_size23 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %54, i32 0, i32 3, !dbg !482
  %55 = load i64, i64* %compressed_size23, align 8, !dbg !482
  %56 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !483
  %block24 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %56, i32 0, i32 1, !dbg !484
  %57 = load %struct.lzma_block*, %struct.lzma_block** %block24, align 8, !dbg !484
  %compressed_size25 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %57, i32 0, i32 3, !dbg !485
  store i64 %55, i64* %compressed_size25, align 8, !dbg !486
  %58 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !487
  %uncompressed_size26 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %58, i32 0, i32 4, !dbg !488
  %59 = load i64, i64* %uncompressed_size26, align 8, !dbg !488
  %60 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !489
  %block27 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %60, i32 0, i32 1, !dbg !490
  %61 = load %struct.lzma_block*, %struct.lzma_block** %block27, align 8, !dbg !490
  %uncompressed_size28 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %61, i32 0, i32 4, !dbg !491
  store i64 %59, i64* %uncompressed_size28, align 8, !dbg !492
  %62 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !493
  %sequence29 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %62, i32 0, i32 2, !dbg !494
  store i32 1, i32* %sequence29, align 8, !dbg !495
  br label %sw.bb30, !dbg !496

sw.bb30:                                          ; preds = %if.end, %cond.end22
  br label %while.cond, !dbg !497

while.cond:                                       ; preds = %if.end34, %sw.bb30
  %63 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !498
  %compressed_size31 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %63, i32 0, i32 3, !dbg !500
  %64 = load i64, i64* %compressed_size31, align 8, !dbg !500
  %and = and i64 %64, 3, !dbg !501
  %tobool = icmp ne i64 %and, 0, !dbg !502
  br i1 %tobool, label %while.body, label %while.end, !dbg !502

while.body:                                       ; preds = %while.cond
  %65 = load i64*, i64** %out_pos.addr, align 8, !dbg !503
  %66 = load i64, i64* %65, align 8, !dbg !506
  %67 = load i64, i64* %out_size.addr, align 8, !dbg !507
  %cmp32 = icmp uge i64 %66, %67, !dbg !508
  br i1 %cmp32, label %if.then33, label %if.end34, !dbg !509

if.then33:                                        ; preds = %while.body
  store i32 0, i32* %retval, align 4, !dbg !510
  br label %return, !dbg !510

if.end34:                                         ; preds = %while.body
  %68 = load i64*, i64** %out_pos.addr, align 8, !dbg !511
  %69 = load i64, i64* %68, align 8, !dbg !512
  %70 = load i8*, i8** %out.addr, align 8, !dbg !513
  %arrayidx = getelementptr inbounds i8, i8* %70, i64 %69, !dbg !513
  store i8 0, i8* %arrayidx, align 1, !dbg !514
  %71 = load i64*, i64** %out_pos.addr, align 8, !dbg !515
  %72 = load i64, i64* %71, align 8, !dbg !516
  %inc = add i64 %72, 1, !dbg !516
  store i64 %inc, i64* %71, align 8, !dbg !516
  %73 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !517
  %compressed_size35 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %73, i32 0, i32 3, !dbg !518
  %74 = load i64, i64* %compressed_size35, align 8, !dbg !519
  %inc36 = add i64 %74, 1, !dbg !519
  store i64 %inc36, i64* %compressed_size35, align 8, !dbg !519
  br label %while.cond, !dbg !520

while.end:                                        ; preds = %while.cond
  %75 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !522
  %block37 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %75, i32 0, i32 1, !dbg !524
  %76 = load %struct.lzma_block*, %struct.lzma_block** %block37, align 8, !dbg !524
  %check38 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %76, i32 0, i32 2, !dbg !525
  %77 = load i32, i32* %check38, align 8, !dbg !525
  %cmp39 = icmp eq i32 %77, 0, !dbg !526
  br i1 %cmp39, label %if.then40, label %if.end41, !dbg !527

if.then40:                                        ; preds = %while.end
  store i32 1, i32* %retval, align 4, !dbg !528
  br label %return, !dbg !528

if.end41:                                         ; preds = %while.end
  %78 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !529
  %check42 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %78, i32 0, i32 6, !dbg !530
  %79 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !531
  %block43 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %79, i32 0, i32 1, !dbg !532
  %80 = load %struct.lzma_block*, %struct.lzma_block** %block43, align 8, !dbg !532
  %check44 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %80, i32 0, i32 2, !dbg !533
  %81 = load i32, i32* %check44, align 8, !dbg !533
  call void @lzma_check_finish(%struct.lzma_check_state* %check42, i32 %81), !dbg !534
  %82 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !535
  %sequence45 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %82, i32 0, i32 2, !dbg !536
  store i32 2, i32* %sequence45, align 8, !dbg !537
  br label %sw.bb46, !dbg !535

sw.bb46:                                          ; preds = %if.end, %if.end41
  call void @llvm.dbg.declare(metadata i64* %check_size, metadata !538, metadata !257), !dbg !540
  %83 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !541
  %block47 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %83, i32 0, i32 1, !dbg !542
  %84 = load %struct.lzma_block*, %struct.lzma_block** %block47, align 8, !dbg !542
  %check48 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %84, i32 0, i32 2, !dbg !543
  %85 = load i32, i32* %check48, align 8, !dbg !543
  %call49 = call i32 @lzma_check_size(i32 %85) #1, !dbg !544
  %conv = zext i32 %call49 to i64, !dbg !544
  store i64 %conv, i64* %check_size, align 8, !dbg !540
  %86 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !545
  %check50 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %86, i32 0, i32 6, !dbg !546
  %buffer = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %check50, i32 0, i32 0, !dbg !547
  %u8 = bitcast %union.anon* %buffer to [64 x i8]*, !dbg !548
  %arraydecay = getelementptr inbounds [64 x i8], [64 x i8]* %u8, i32 0, i32 0, !dbg !545
  %87 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !549
  %pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %87, i32 0, i32 5, !dbg !550
  %88 = load i64, i64* %check_size, align 8, !dbg !551
  %89 = load i8*, i8** %out.addr, align 8, !dbg !552
  %90 = load i64*, i64** %out_pos.addr, align 8, !dbg !553
  %91 = load i64, i64* %out_size.addr, align 8, !dbg !554
  %call51 = call i64 @lzma_bufcpy(i8* %arraydecay, i64* %pos, i64 %88, i8* %89, i64* %90, i64 %91), !dbg !555
  %92 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !556
  %pos52 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %92, i32 0, i32 5, !dbg !558
  %93 = load i64, i64* %pos52, align 8, !dbg !558
  %94 = load i64, i64* %check_size, align 8, !dbg !559
  %cmp53 = icmp ult i64 %93, %94, !dbg !560
  br i1 %cmp53, label %if.then55, label %if.end56, !dbg !561

if.then55:                                        ; preds = %sw.bb46
  store i32 0, i32* %retval, align 4, !dbg !562
  br label %return, !dbg !562

if.end56:                                         ; preds = %sw.bb46
  %95 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !563
  %block57 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %95, i32 0, i32 1, !dbg !564
  %96 = load %struct.lzma_block*, %struct.lzma_block** %block57, align 8, !dbg !564
  %raw_check = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %96, i32 0, i32 6, !dbg !565
  %arraydecay58 = getelementptr inbounds [64 x i8], [64 x i8]* %raw_check, i32 0, i32 0, !dbg !566
  %97 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !567
  %check59 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %97, i32 0, i32 6, !dbg !568
  %buffer60 = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %check59, i32 0, i32 0, !dbg !569
  %u861 = bitcast %union.anon* %buffer60 to [64 x i8]*, !dbg !570
  %arraydecay62 = getelementptr inbounds [64 x i8], [64 x i8]* %u861, i32 0, i32 0, !dbg !566
  %98 = load i64, i64* %check_size, align 8, !dbg !571
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay58, i8* %arraydecay62, i64 %98, i32 8, i1 false), !dbg !566
  store i32 1, i32* %retval, align 4, !dbg !572
  br label %return, !dbg !572

sw.epilog:                                        ; preds = %if.end
  store i32 11, i32* %retval, align 4, !dbg !573
  br label %return, !dbg !573

return:                                           ; preds = %sw.epilog, %if.end56, %if.then55, %if.then40, %if.then33, %if.then16, %if.then8, %if.then
  %99 = load i32, i32* %retval, align 4, !dbg !574
  ret i32 %99, !dbg !574
}

; Function Attrs: nounwind uwtable
define internal void @block_encoder_end(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator) #0 !dbg !248 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !575, metadata !257), !dbg !576
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !577, metadata !257), !dbg !578
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !579
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 0, !dbg !580
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !581
  call void @lzma_next_end(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %1), !dbg !582
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !583
  %3 = bitcast %struct.lzma_coder_s* %2 to i8*, !dbg !583
  %4 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !584
  call void @lzma_free(i8* %3, %struct.lzma_allocator* %4), !dbg !585
  ret void, !dbg !586
}

; Function Attrs: nounwind uwtable
define internal i32 @block_encoder_update(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, %struct.lzma_filter* %filters, %struct.lzma_filter* %reversed_filters) #0 !dbg !249 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter*, align 8
  %reversed_filters.addr = alloca %struct.lzma_filter*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !587, metadata !257), !dbg !588
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !589, metadata !257), !dbg !590
  store %struct.lzma_filter* %filters, %struct.lzma_filter** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filters.addr, metadata !591, metadata !257), !dbg !592
  store %struct.lzma_filter* %reversed_filters, %struct.lzma_filter** %reversed_filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %reversed_filters.addr, metadata !593, metadata !257), !dbg !594
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !595
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 2, !dbg !597
  %1 = load i32, i32* %sequence, align 8, !dbg !597
  %cmp = icmp ne i32 %1, 0, !dbg !598
  br i1 %cmp, label %if.then, label %if.end, !dbg !599

if.then:                                          ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !600
  br label %return, !dbg !600

if.end:                                           ; preds = %entry
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !601
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 0, !dbg !602
  %3 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !603
  %4 = load %struct.lzma_filter*, %struct.lzma_filter** %reversed_filters.addr, align 8, !dbg !604
  %call = call i32 @lzma_next_filter_update(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %3, %struct.lzma_filter* %4), !dbg !605
  store i32 %call, i32* %retval, align 4, !dbg !606
  br label %return, !dbg !606

return:                                           ; preds = %if.end, %if.then
  %5 = load i32, i32* %retval, align 4, !dbg !607
  ret i32 %5, !dbg !607
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

declare void @lzma_check_init(%struct.lzma_check_state*, i32) #2

declare i32 @lzma_raw_encoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*) #2

; Function Attrs: nounwind uwtable
define i32 @lzma_block_encoder(%struct.lzma_stream* %strm, %struct.lzma_block* %block) #0 !dbg !220 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzma_stream*, align 8
  %block.addr = alloca %struct.lzma_block*, align 8
  %ret_ = alloca i32, align 4
  %ret_2 = alloca i32, align 4
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !608, metadata !257), !dbg !609
  store %struct.lzma_block* %block, %struct.lzma_block** %block.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_block** %block.addr, metadata !610, metadata !257), !dbg !611
  br label %do.body, !dbg !612

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !613, metadata !257), !dbg !615
  br label %do.body1, !dbg !616

do.body1:                                         ; preds = %do.body
  call void @llvm.dbg.declare(metadata i32* %ret_2, metadata !618, metadata !257), !dbg !620
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !621
  %call = call i32 @lzma_strm_init(%struct.lzma_stream* %0), !dbg !621
  store i32 %call, i32* %ret_2, align 4, !dbg !621
  %1 = load i32, i32* %ret_2, align 4, !dbg !621
  %cmp = icmp ne i32 %1, 0, !dbg !621
  br i1 %cmp, label %if.then, label %if.end, !dbg !621

if.then:                                          ; preds = %do.body1
  %2 = load i32, i32* %ret_2, align 4, !dbg !623
  store i32 %2, i32* %retval, align 4, !dbg !623
  br label %return, !dbg !623

if.end:                                           ; preds = %do.body1
  br label %do.end, !dbg !626

do.end:                                           ; preds = %if.end
  %3 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !628
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %3, i32 0, i32 7, !dbg !628
  %4 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !628
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %4, i32 0, i32 0, !dbg !628
  %5 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !628
  %allocator = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %5, i32 0, i32 6, !dbg !628
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator, align 8, !dbg !628
  %7 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !628
  %call3 = call i32 @lzma_block_encoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %6, %struct.lzma_block* %7), !dbg !628
  store i32 %call3, i32* %ret_, align 4, !dbg !628
  %8 = load i32, i32* %ret_, align 4, !dbg !628
  %cmp4 = icmp ne i32 %8, 0, !dbg !628
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !628

if.then5:                                         ; preds = %do.end
  %9 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !630
  call void @lzma_end(%struct.lzma_stream* %9) #8, !dbg !630
  %10 = load i32, i32* %ret_, align 4, !dbg !630
  store i32 %10, i32* %retval, align 4, !dbg !630
  br label %return, !dbg !630

if.end6:                                          ; preds = %do.end
  br label %do.end7, !dbg !634

do.end7:                                          ; preds = %if.end6
  %11 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !636
  %internal8 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %11, i32 0, i32 7, !dbg !637
  %12 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal8, align 8, !dbg !637
  %supported_actions = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %12, i32 0, i32 3, !dbg !638
  %arrayidx = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions, i64 0, i64 0, !dbg !636
  store i8 1, i8* %arrayidx, align 8, !dbg !639
  %13 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !640
  %internal9 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %13, i32 0, i32 7, !dbg !641
  %14 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal9, align 8, !dbg !641
  %supported_actions10 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %14, i32 0, i32 3, !dbg !642
  %arrayidx11 = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions10, i64 0, i64 3, !dbg !640
  store i8 1, i8* %arrayidx11, align 1, !dbg !643
  store i32 0, i32* %retval, align 4, !dbg !644
  br label %return, !dbg !644

return:                                           ; preds = %do.end7, %if.then5, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !645
  ret i32 %15, !dbg !645
}

declare i32 @lzma_strm_init(%struct.lzma_stream*) #2

; Function Attrs: nounwind
declare void @lzma_end(%struct.lzma_stream*) #5

declare void @lzma_check_update(%struct.lzma_check_state*, i32, i8*, i64) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #6

declare void @lzma_check_finish(%struct.lzma_check_state*, i32) #2

; Function Attrs: nounwind readnone
declare i32 @lzma_check_size(i32) #3

declare i64 @lzma_bufcpy(i8*, i64*, i64, i8*, i64*, i64) #2

declare void @lzma_free(i8*, %struct.lzma_allocator*) #2

declare i32 @lzma_next_filter_update(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { noreturn nounwind }
attributes #8 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!253, !254}
!llvm.ident = !{!255}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !213, subprograms: !214, globals: !250)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/block_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !25, !28, !79, !194}
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
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !19, line: 27, size: 32, align: 32, elements: !20)
!19 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!20 = !{!21, !22, !23, !24}
!21 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!22 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!23 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!24 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!25 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !26)
!26 = !{!27}
!27 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!28 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !29, file: !1, line: 27, size: 32, align: 32, elements: !190)
!29 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !1, line: 18, size: 1664, align: 64, elements: !30)
!30 = !{!31, !114, !158, !159, !160, !161, !162}
!31 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !29, file: !1, line: 20, baseType: !32, size: 512, align: 64)
!32 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !33, line: 75, baseType: !34)
!33 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!34 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !33, line: 119, size: 512, align: 64, elements: !35)
!35 = !{!36, !39, !45, !47, !85, !90, !97, !102}
!36 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !34, file: !33, line: 121, baseType: !37, size: 64, align: 64)
!37 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !38, size: 64, align: 64)
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !33, line: 73, baseType: !29)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !34, file: !33, line: 125, baseType: !40, size: 64, align: 64, offset: 64)
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !41, line: 63, baseType: !42)
!41 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !43, line: 55, baseType: !44)
!43 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!44 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !34, file: !33, line: 131, baseType: !46, size: 64, align: 64, offset: 128)
!46 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !43, line: 122, baseType: !44)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !34, file: !33, line: 134, baseType: !48, size: 64, align: 64, offset: 192)
!48 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !33, line: 89, baseType: !49)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DISubroutineType(types: !51)
!51 = !{!52, !37, !53, !69, !74, !62, !76, !74, !62, !78}
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!53 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64, align: 64)
!54 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !55)
!55 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !56)
!56 = !{!57, !64, !68}
!57 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !55, file: !4, line: 376, baseType: !58, size: 64, align: 64)
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !59, size: 64, align: 64)
!59 = !DISubroutineType(types: !60)
!60 = !{!61, !61, !62, !62}
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!62 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !63, line: 62, baseType: !44)
!63 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!64 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !55, file: !4, line: 390, baseType: !65, size: 64, align: 64, offset: 64)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !66, size: 64, align: 64)
!66 = !DISubroutineType(types: !67)
!67 = !{null, !61, !61}
!68 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !55, file: !4, line: 401, baseType: !61, size: 64, align: 64, offset: 128)
!69 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !70)
!70 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !71, size: 64, align: 64)
!71 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !72)
!72 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !43, line: 48, baseType: !73)
!73 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!74 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !75)
!75 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!76 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !77)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !72, size: 64, align: 64)
!78 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !79)
!79 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !80)
!80 = !{!81, !82, !83, !84}
!81 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!82 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!83 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!84 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !34, file: !33, line: 139, baseType: !86, size: 64, align: 64, offset: 256)
!86 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !33, line: 97, baseType: !87)
!87 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !88, size: 64, align: 64)
!88 = !DISubroutineType(types: !89)
!89 = !{null, !37, !53}
!90 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !34, file: !33, line: 143, baseType: !91, size: 64, align: 64, offset: 320)
!91 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !92, size: 64, align: 64)
!92 = !DISubroutineType(types: !93)
!93 = !{!94, !95}
!94 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !19, line: 55, baseType: !18)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !96, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !38)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !34, file: !33, line: 147, baseType: !98, size: 64, align: 64, offset: 384)
!98 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !99, size: 64, align: 64)
!99 = !DISubroutineType(types: !100)
!100 = !{!52, !37, !101, !101, !42}
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !42, size: 64, align: 64)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !34, file: !33, line: 152, baseType: !103, size: 64, align: 64, offset: 448)
!103 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !104, size: 64, align: 64)
!104 = !DISubroutineType(types: !105)
!105 = !{!52, !37, !53, !106, !106}
!106 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !107, size: 64, align: 64)
!107 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !108)
!108 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !109, line: 65, baseType: !110)
!109 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!110 = !DICompositeType(tag: DW_TAG_structure_type, file: !109, line: 43, size: 128, align: 64, elements: !111)
!111 = !{!112, !113}
!112 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !110, file: !109, line: 54, baseType: !40, size: 64, align: 64)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !110, file: !109, line: 63, baseType: !61, size: 64, align: 64, offset: 64)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "block", scope: !29, file: !1, line: 25, baseType: !115, size: 64, align: 64, offset: 512)
!115 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !116, size: 64, align: 64)
!116 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_block", file: !117, line: 245, baseType: !118)
!117 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/block.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!118 = !DICompositeType(tag: DW_TAG_structure_type, file: !117, line: 30, size: 1664, align: 64, elements: !119)
!119 = !{!120, !123, !124, !125, !126, !127, !129, !133, !134, !135, !136, !137, !138, !139, !140, !141, !142, !143, !144, !146, !147, !148, !149, !151, !152, !153, !154, !155, !156, !157}
!120 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !118, file: !117, line: 47, baseType: !121, size: 32, align: 32)
!121 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !43, line: 51, baseType: !122)
!122 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "header_size", scope: !118, file: !117, line: 67, baseType: !121, size: 32, align: 32, offset: 32)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !118, file: !117, line: 88, baseType: !94, size: 32, align: 32, offset: 64)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_size", scope: !118, file: !117, line: 143, baseType: !40, size: 64, align: 64, offset: 128)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !118, file: !117, line: 167, baseType: !40, size: 64, align: 64, offset: 192)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "filters", scope: !118, file: !117, line: 195, baseType: !128, size: 64, align: 64, offset: 256)
!128 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !108, size: 64, align: 64)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "raw_check", scope: !118, file: !117, line: 212, baseType: !130, size: 512, align: 8, offset: 320)
!130 = !DICompositeType(tag: DW_TAG_array_type, baseType: !72, size: 512, align: 8, elements: !131)
!131 = !{!132}
!132 = !DISubrange(count: 64)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !118, file: !117, line: 221, baseType: !61, size: 64, align: 64, offset: 832)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !118, file: !117, line: 222, baseType: !61, size: 64, align: 64, offset: 896)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !118, file: !117, line: 223, baseType: !61, size: 64, align: 64, offset: 960)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !118, file: !117, line: 224, baseType: !121, size: 32, align: 32, offset: 1024)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !118, file: !117, line: 225, baseType: !121, size: 32, align: 32, offset: 1056)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !118, file: !117, line: 226, baseType: !40, size: 64, align: 64, offset: 1088)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !118, file: !117, line: 227, baseType: !40, size: 64, align: 64, offset: 1152)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !118, file: !117, line: 228, baseType: !40, size: 64, align: 64, offset: 1216)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !118, file: !117, line: 229, baseType: !40, size: 64, align: 64, offset: 1280)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !118, file: !117, line: 230, baseType: !40, size: 64, align: 64, offset: 1344)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !118, file: !117, line: 231, baseType: !40, size: 64, align: 64, offset: 1408)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !118, file: !117, line: 232, baseType: !145, size: 32, align: 32, offset: 1472)
!145 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !25)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !118, file: !117, line: 233, baseType: !145, size: 32, align: 32, offset: 1504)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !118, file: !117, line: 234, baseType: !145, size: 32, align: 32, offset: 1536)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !118, file: !117, line: 235, baseType: !145, size: 32, align: 32, offset: 1568)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool1", scope: !118, file: !117, line: 236, baseType: !150, size: 8, align: 8, offset: 1600)
!150 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !4, line: 29, baseType: !73)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool2", scope: !118, file: !117, line: 237, baseType: !150, size: 8, align: 8, offset: 1608)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool3", scope: !118, file: !117, line: 238, baseType: !150, size: 8, align: 8, offset: 1616)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool4", scope: !118, file: !117, line: 239, baseType: !150, size: 8, align: 8, offset: 1624)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool5", scope: !118, file: !117, line: 240, baseType: !150, size: 8, align: 8, offset: 1632)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool6", scope: !118, file: !117, line: 241, baseType: !150, size: 8, align: 8, offset: 1640)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool7", scope: !118, file: !117, line: 242, baseType: !150, size: 8, align: 8, offset: 1648)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool8", scope: !118, file: !117, line: 243, baseType: !150, size: 8, align: 8, offset: 1656)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !29, file: !1, line: 31, baseType: !28, size: 32, align: 32, offset: 576)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_size", scope: !29, file: !1, line: 34, baseType: !40, size: 64, align: 64, offset: 640)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !29, file: !1, line: 37, baseType: !40, size: 64, align: 64, offset: 704)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "pos", scope: !29, file: !1, line: 40, baseType: !62, size: 64, align: 64, offset: 768)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !29, file: !1, line: 43, baseType: !163, size: 832, align: 64, offset: 832)
!163 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check_state", file: !164, line: 56, baseType: !165)
!164 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/check/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!165 = !DICompositeType(tag: DW_TAG_structure_type, file: !164, line: 34, size: 832, align: 64, elements: !166)
!166 = !{!167, !179}
!167 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !165, file: !164, line: 40, baseType: !168, size: 512, align: 64)
!168 = !DICompositeType(tag: DW_TAG_union_type, scope: !165, file: !164, line: 36, size: 512, align: 64, elements: !169)
!169 = !{!170, !171, !175}
!170 = !DIDerivedType(tag: DW_TAG_member, name: "u8", scope: !168, file: !164, line: 37, baseType: !130, size: 512, align: 8)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "u32", scope: !168, file: !164, line: 38, baseType: !172, size: 512, align: 32)
!172 = !DICompositeType(tag: DW_TAG_array_type, baseType: !121, size: 512, align: 32, elements: !173)
!173 = !{!174}
!174 = !DISubrange(count: 16)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "u64", scope: !168, file: !164, line: 39, baseType: !176, size: 512, align: 64)
!176 = !DICompositeType(tag: DW_TAG_array_type, baseType: !42, size: 512, align: 64, elements: !177)
!177 = !{!178}
!178 = !DISubrange(count: 8)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !165, file: !164, line: 54, baseType: !180, size: 320, align: 64, offset: 512)
!180 = !DICompositeType(tag: DW_TAG_union_type, scope: !165, file: !164, line: 43, size: 320, align: 64, elements: !181)
!181 = !{!182, !183, !184}
!182 = !DIDerivedType(tag: DW_TAG_member, name: "crc32", scope: !180, file: !164, line: 44, baseType: !121, size: 32, align: 32)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "crc64", scope: !180, file: !164, line: 45, baseType: !42, size: 64, align: 64)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "sha256", scope: !180, file: !164, line: 53, baseType: !185, size: 320, align: 64)
!185 = !DICompositeType(tag: DW_TAG_structure_type, scope: !180, file: !164, line: 47, size: 320, align: 64, elements: !186)
!186 = !{!187, !189}
!187 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !185, file: !164, line: 49, baseType: !188, size: 256, align: 32)
!188 = !DICompositeType(tag: DW_TAG_array_type, baseType: !121, size: 256, align: 32, elements: !177)
!189 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !185, file: !164, line: 52, baseType: !42, size: 64, align: 64, offset: 256)
!190 = !{!191, !192, !193}
!191 = !DIEnumerator(name: "SEQ_CODE", value: 0)
!192 = !DIEnumerator(name: "SEQ_PADDING", value: 1)
!193 = !DIEnumerator(name: "SEQ_CHECK", value: 2)
!194 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !195, file: !33, line: 182, size: 32, align: 32, elements: !206)
!195 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_internal_s", file: !33, line: 174, size: 704, align: 64, elements: !196)
!196 = !{!197, !198, !199, !200, !205}
!197 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !195, file: !33, line: 176, baseType: !32, size: 512, align: 64)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !195, file: !33, line: 189, baseType: !194, size: 32, align: 32, offset: 512)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !195, file: !33, line: 194, baseType: !62, size: 64, align: 64, offset: 576)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "supported_actions", scope: !195, file: !33, line: 197, baseType: !201, size: 32, align: 8, offset: 640)
!201 = !DICompositeType(tag: DW_TAG_array_type, baseType: !202, size: 32, align: 8, elements: !203)
!202 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!203 = !{!204}
!204 = !DISubrange(count: 4)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "allow_buf_error", scope: !195, file: !33, line: 201, baseType: !202, size: 8, align: 8, offset: 672)
!206 = !{!207, !208, !209, !210, !211, !212}
!207 = !DIEnumerator(name: "ISEQ_RUN", value: 0)
!208 = !DIEnumerator(name: "ISEQ_SYNC_FLUSH", value: 1)
!209 = !DIEnumerator(name: "ISEQ_FULL_FLUSH", value: 2)
!210 = !DIEnumerator(name: "ISEQ_FINISH", value: 3)
!211 = !DIEnumerator(name: "ISEQ_END", value: 4)
!212 = !DIEnumerator(name: "ISEQ_ERROR", value: 5)
!213 = !{!46, !61, !122}
!214 = !{!215, !220, !247, !248, !249}
!215 = distinct !DISubprogram(name: "lzma_block_encoder_init", scope: !1, file: !1, line: 159, type: !216, isLocal: false, isDefinition: true, scopeLine: 161, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!216 = !DISubroutineType(types: !217)
!217 = !{!52, !218, !53, !115}
!218 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64, align: 64)
!219 = !{}
!220 = distinct !DISubprogram(name: "lzma_block_encoder", scope: !1, file: !1, line: 209, type: !221, isLocal: false, isDefinition: true, scopeLine: 210, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!221 = !DISubroutineType(types: !222)
!222 = !{!52, !223, !115}
!223 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !224, size: 64, align: 64)
!224 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream", file: !4, line: 490, baseType: !225)
!225 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 453, size: 1088, align: 64, elements: !226)
!226 = !{!227, !228, !229, !230, !231, !232, !233, !234, !237, !238, !239, !240, !241, !242, !243, !244, !245, !246}
!227 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !225, file: !4, line: 454, baseType: !70, size: 64, align: 64)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !225, file: !4, line: 455, baseType: !62, size: 64, align: 64, offset: 64)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !225, file: !4, line: 456, baseType: !42, size: 64, align: 64, offset: 128)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !225, file: !4, line: 458, baseType: !77, size: 64, align: 64, offset: 192)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !225, file: !4, line: 459, baseType: !62, size: 64, align: 64, offset: 256)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !225, file: !4, line: 460, baseType: !42, size: 64, align: 64, offset: 320)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "allocator", scope: !225, file: !4, line: 468, baseType: !53, size: 64, align: 64, offset: 384)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "internal", scope: !225, file: !4, line: 471, baseType: !235, size: 64, align: 64, offset: 448)
!235 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !236, size: 64, align: 64)
!236 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_internal", file: !4, line: 411, baseType: !195)
!237 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !225, file: !4, line: 479, baseType: !61, size: 64, align: 64, offset: 512)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !225, file: !4, line: 480, baseType: !61, size: 64, align: 64, offset: 576)
!239 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !225, file: !4, line: 481, baseType: !61, size: 64, align: 64, offset: 640)
!240 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr4", scope: !225, file: !4, line: 482, baseType: !61, size: 64, align: 64, offset: 704)
!241 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !225, file: !4, line: 483, baseType: !42, size: 64, align: 64, offset: 768)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !225, file: !4, line: 484, baseType: !42, size: 64, align: 64, offset: 832)
!243 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !225, file: !4, line: 485, baseType: !62, size: 64, align: 64, offset: 896)
!244 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !225, file: !4, line: 486, baseType: !62, size: 64, align: 64, offset: 960)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !225, file: !4, line: 487, baseType: !145, size: 32, align: 32, offset: 1024)
!246 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !225, file: !4, line: 488, baseType: !145, size: 32, align: 32, offset: 1056)
!247 = distinct !DISubprogram(name: "block_encode", scope: !1, file: !1, line: 48, type: !50, isLocal: true, isDefinition: true, scopeLine: 52, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!248 = distinct !DISubprogram(name: "block_encoder_end", scope: !1, file: !1, line: 137, type: !88, isLocal: true, isDefinition: true, scopeLine: 138, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!249 = distinct !DISubprogram(name: "block_encoder_update", scope: !1, file: !1, line: 146, type: !104, isLocal: true, isDefinition: true, scopeLine: 149, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!250 = !{!251}
!251 = !DIGlobalVariable(name: "LZMA_NEXT_CODER_INIT", scope: !0, file: !33, line: 159, type: !252, isLocal: true, isDefinition: true, variable: %struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT)
!252 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !32)
!253 = !{i32 2, !"Dwarf Version", i32 4}
!254 = !{i32 2, !"Debug Info Version", i32 3}
!255 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!256 = !DILocalVariable(name: "next", arg: 1, scope: !215, file: !1, line: 159, type: !218)
!257 = !DIExpression()
!258 = !DILocation(line: 159, column: 42, scope: !215)
!259 = !DILocalVariable(name: "allocator", arg: 2, scope: !215, file: !1, line: 159, type: !53)
!260 = !DILocation(line: 159, column: 64, scope: !215)
!261 = !DILocalVariable(name: "block", arg: 3, scope: !215, file: !1, line: 160, type: !115)
!262 = !DILocation(line: 160, column: 15, scope: !215)
!263 = !DILocation(line: 162, column: 2, scope: !215)
!264 = !DILocation(line: 162, column: 2, scope: !265)
!265 = !DILexicalBlockFile(scope: !266, file: !1, discriminator: 1)
!266 = distinct !DILexicalBlock(scope: !267, file: !1, line: 162, column: 2)
!267 = distinct !DILexicalBlock(scope: !215, file: !1, line: 162, column: 2)
!268 = !DILocation(line: 162, column: 2, scope: !269)
!269 = !DILexicalBlockFile(scope: !266, file: !1, discriminator: 2)
!270 = !DILocation(line: 162, column: 2, scope: !271)
!271 = !DILexicalBlockFile(scope: !267, file: !1, discriminator: 3)
!272 = !DILocation(line: 164, column: 6, scope: !273)
!273 = distinct !DILexicalBlock(scope: !215, file: !1, line: 164, column: 6)
!274 = !DILocation(line: 164, column: 12, scope: !273)
!275 = !DILocation(line: 164, column: 6, scope: !215)
!276 = !DILocation(line: 165, column: 3, scope: !273)
!277 = !DILocation(line: 169, column: 6, scope: !278)
!278 = distinct !DILexicalBlock(scope: !215, file: !1, line: 169, column: 6)
!279 = !DILocation(line: 169, column: 13, scope: !278)
!280 = !DILocation(line: 169, column: 21, scope: !278)
!281 = !DILocation(line: 169, column: 6, scope: !215)
!282 = !DILocation(line: 170, column: 3, scope: !278)
!283 = !DILocation(line: 174, column: 21, scope: !284)
!284 = distinct !DILexicalBlock(scope: !215, file: !1, line: 174, column: 6)
!285 = !DILocation(line: 174, column: 28, scope: !284)
!286 = !DILocation(line: 174, column: 35, scope: !284)
!287 = !DILocation(line: 174, column: 6, scope: !215)
!288 = !DILocation(line: 175, column: 3, scope: !284)
!289 = !DILocation(line: 177, column: 31, scope: !290)
!290 = distinct !DILexicalBlock(scope: !215, file: !1, line: 177, column: 6)
!291 = !DILocation(line: 177, column: 38, scope: !290)
!292 = !DILocation(line: 177, column: 7, scope: !290)
!293 = !DILocation(line: 177, column: 6, scope: !215)
!294 = !DILocation(line: 178, column: 3, scope: !290)
!295 = !DILocation(line: 181, column: 6, scope: !296)
!296 = distinct !DILexicalBlock(scope: !215, file: !1, line: 181, column: 6)
!297 = !DILocation(line: 181, column: 12, scope: !296)
!298 = !DILocation(line: 181, column: 18, scope: !296)
!299 = !DILocation(line: 181, column: 6, scope: !215)
!300 = !DILocation(line: 182, column: 48, scope: !301)
!301 = distinct !DILexicalBlock(scope: !296, file: !1, line: 181, column: 27)
!302 = !DILocation(line: 182, column: 17, scope: !301)
!303 = !DILocation(line: 182, column: 3, scope: !301)
!304 = !DILocation(line: 182, column: 9, scope: !301)
!305 = !DILocation(line: 182, column: 15, scope: !301)
!306 = !DILocation(line: 183, column: 7, scope: !307)
!307 = distinct !DILexicalBlock(scope: !301, file: !1, line: 183, column: 7)
!308 = !DILocation(line: 183, column: 13, scope: !307)
!309 = !DILocation(line: 183, column: 19, scope: !307)
!310 = !DILocation(line: 183, column: 7, scope: !301)
!311 = !DILocation(line: 184, column: 4, scope: !307)
!312 = !DILocation(line: 186, column: 3, scope: !301)
!313 = !DILocation(line: 186, column: 9, scope: !301)
!314 = !DILocation(line: 186, column: 14, scope: !301)
!315 = !DILocation(line: 187, column: 3, scope: !301)
!316 = !DILocation(line: 187, column: 9, scope: !301)
!317 = !DILocation(line: 187, column: 13, scope: !301)
!318 = !DILocation(line: 188, column: 3, scope: !301)
!319 = !DILocation(line: 188, column: 9, scope: !301)
!320 = !DILocation(line: 188, column: 16, scope: !301)
!321 = !DILocation(line: 189, column: 3, scope: !301)
!322 = !DILocation(line: 189, column: 9, scope: !301)
!323 = !DILocation(line: 189, column: 16, scope: !301)
!324 = !DILocation(line: 189, column: 23, scope: !301)
!325 = !DILocation(line: 190, column: 2, scope: !301)
!326 = !DILocation(line: 193, column: 2, scope: !215)
!327 = !DILocation(line: 193, column: 8, scope: !215)
!328 = !DILocation(line: 193, column: 15, scope: !215)
!329 = !DILocation(line: 193, column: 24, scope: !215)
!330 = !DILocation(line: 194, column: 23, scope: !215)
!331 = !DILocation(line: 194, column: 2, scope: !215)
!332 = !DILocation(line: 194, column: 8, scope: !215)
!333 = !DILocation(line: 194, column: 15, scope: !215)
!334 = !DILocation(line: 194, column: 21, scope: !215)
!335 = !DILocation(line: 195, column: 2, scope: !215)
!336 = !DILocation(line: 195, column: 8, scope: !215)
!337 = !DILocation(line: 195, column: 15, scope: !215)
!338 = !DILocation(line: 195, column: 31, scope: !215)
!339 = !DILocation(line: 196, column: 2, scope: !215)
!340 = !DILocation(line: 196, column: 8, scope: !215)
!341 = !DILocation(line: 196, column: 15, scope: !215)
!342 = !DILocation(line: 196, column: 33, scope: !215)
!343 = !DILocation(line: 197, column: 2, scope: !215)
!344 = !DILocation(line: 197, column: 8, scope: !215)
!345 = !DILocation(line: 197, column: 15, scope: !215)
!346 = !DILocation(line: 197, column: 19, scope: !215)
!347 = !DILocation(line: 200, column: 19, scope: !215)
!348 = !DILocation(line: 200, column: 25, scope: !215)
!349 = !DILocation(line: 200, column: 32, scope: !215)
!350 = !DILocation(line: 200, column: 39, scope: !215)
!351 = !DILocation(line: 200, column: 46, scope: !215)
!352 = !DILocation(line: 200, column: 2, scope: !215)
!353 = !DILocation(line: 203, column: 32, scope: !215)
!354 = !DILocation(line: 203, column: 38, scope: !215)
!355 = !DILocation(line: 203, column: 45, scope: !215)
!356 = !DILocation(line: 203, column: 51, scope: !215)
!357 = !DILocation(line: 204, column: 4, scope: !215)
!358 = !DILocation(line: 204, column: 11, scope: !215)
!359 = !DILocation(line: 203, column: 9, scope: !215)
!360 = !DILocation(line: 203, column: 2, scope: !215)
!361 = !DILocation(line: 205, column: 1, scope: !215)
!362 = !DILocalVariable(name: "coder", arg: 1, scope: !247, file: !1, line: 48, type: !37)
!363 = !DILocation(line: 48, column: 26, scope: !247)
!364 = !DILocalVariable(name: "allocator", arg: 2, scope: !247, file: !1, line: 48, type: !53)
!365 = !DILocation(line: 48, column: 49, scope: !247)
!366 = !DILocalVariable(name: "in", arg: 3, scope: !247, file: !1, line: 49, type: !69)
!367 = !DILocation(line: 49, column: 32, scope: !247)
!368 = !DILocalVariable(name: "in_pos", arg: 4, scope: !247, file: !1, line: 49, type: !74)
!369 = !DILocation(line: 49, column: 58, scope: !247)
!370 = !DILocalVariable(name: "in_size", arg: 5, scope: !247, file: !1, line: 50, type: !62)
!371 = !DILocation(line: 50, column: 10, scope: !247)
!372 = !DILocalVariable(name: "out", arg: 6, scope: !247, file: !1, line: 50, type: !76)
!373 = !DILocation(line: 50, column: 42, scope: !247)
!374 = !DILocalVariable(name: "out_pos", arg: 7, scope: !247, file: !1, line: 51, type: !74)
!375 = !DILocation(line: 51, column: 25, scope: !247)
!376 = !DILocalVariable(name: "out_size", arg: 8, scope: !247, file: !1, line: 51, type: !62)
!377 = !DILocation(line: 51, column: 41, scope: !247)
!378 = !DILocalVariable(name: "action", arg: 9, scope: !247, file: !1, line: 51, type: !78)
!379 = !DILocation(line: 51, column: 63, scope: !247)
!380 = !DILocation(line: 54, column: 21, scope: !381)
!381 = distinct !DILexicalBlock(scope: !247, file: !1, line: 54, column: 6)
!382 = !DILocation(line: 54, column: 28, scope: !381)
!383 = !DILocation(line: 54, column: 19, scope: !381)
!384 = !DILocation(line: 54, column: 48, scope: !381)
!385 = !DILocation(line: 54, column: 59, scope: !381)
!386 = !DILocation(line: 54, column: 58, scope: !381)
!387 = !DILocation(line: 54, column: 56, scope: !381)
!388 = !DILocation(line: 54, column: 46, scope: !381)
!389 = !DILocation(line: 54, column: 6, scope: !247)
!390 = !DILocation(line: 55, column: 3, scope: !381)
!391 = !DILocation(line: 57, column: 10, scope: !247)
!392 = !DILocation(line: 57, column: 17, scope: !247)
!393 = !DILocation(line: 57, column: 2, scope: !247)
!394 = !DILocalVariable(name: "in_start", scope: !395, file: !1, line: 59, type: !397)
!395 = distinct !DILexicalBlock(scope: !396, file: !1, line: 58, column: 17)
!396 = distinct !DILexicalBlock(scope: !247, file: !1, line: 57, column: 27)
!397 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !62)
!398 = !DILocation(line: 59, column: 16, scope: !395)
!399 = !DILocation(line: 59, column: 28, scope: !395)
!400 = !DILocation(line: 59, column: 27, scope: !395)
!401 = !DILocalVariable(name: "out_start", scope: !395, file: !1, line: 60, type: !397)
!402 = !DILocation(line: 60, column: 16, scope: !395)
!403 = !DILocation(line: 60, column: 29, scope: !395)
!404 = !DILocation(line: 60, column: 28, scope: !395)
!405 = !DILocalVariable(name: "ret", scope: !395, file: !1, line: 62, type: !406)
!406 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !52)
!407 = !DILocation(line: 62, column: 18, scope: !395)
!408 = !DILocation(line: 62, column: 24, scope: !395)
!409 = !DILocation(line: 62, column: 31, scope: !395)
!410 = !DILocation(line: 62, column: 36, scope: !395)
!411 = !DILocation(line: 62, column: 41, scope: !395)
!412 = !DILocation(line: 62, column: 48, scope: !395)
!413 = !DILocation(line: 62, column: 53, scope: !395)
!414 = !DILocation(line: 63, column: 5, scope: !395)
!415 = !DILocation(line: 63, column: 16, scope: !395)
!416 = !DILocation(line: 63, column: 20, scope: !395)
!417 = !DILocation(line: 63, column: 28, scope: !395)
!418 = !DILocation(line: 64, column: 5, scope: !395)
!419 = !DILocation(line: 64, column: 10, scope: !395)
!420 = !DILocation(line: 64, column: 19, scope: !395)
!421 = !DILocation(line: 64, column: 29, scope: !395)
!422 = !DILocalVariable(name: "in_used", scope: !395, file: !1, line: 66, type: !397)
!423 = !DILocation(line: 66, column: 16, scope: !395)
!424 = !DILocation(line: 66, column: 27, scope: !395)
!425 = !DILocation(line: 66, column: 26, scope: !395)
!426 = !DILocation(line: 66, column: 36, scope: !395)
!427 = !DILocation(line: 66, column: 34, scope: !395)
!428 = !DILocalVariable(name: "out_used", scope: !395, file: !1, line: 67, type: !397)
!429 = !DILocation(line: 67, column: 16, scope: !395)
!430 = !DILocation(line: 67, column: 28, scope: !395)
!431 = !DILocation(line: 67, column: 27, scope: !395)
!432 = !DILocation(line: 67, column: 38, scope: !395)
!433 = !DILocation(line: 67, column: 36, scope: !395)
!434 = !DILocation(line: 69, column: 29, scope: !435)
!435 = distinct !DILexicalBlock(scope: !395, file: !1, line: 69, column: 7)
!436 = !DILocation(line: 69, column: 36, scope: !435)
!437 = !DILocation(line: 69, column: 27, scope: !435)
!438 = !DILocation(line: 69, column: 54, scope: !435)
!439 = !DILocation(line: 69, column: 52, scope: !435)
!440 = !DILocation(line: 69, column: 7, scope: !395)
!441 = !DILocation(line: 70, column: 4, scope: !435)
!442 = !DILocation(line: 72, column: 29, scope: !395)
!443 = !DILocation(line: 72, column: 3, scope: !395)
!444 = !DILocation(line: 72, column: 10, scope: !395)
!445 = !DILocation(line: 72, column: 26, scope: !395)
!446 = !DILocation(line: 76, column: 31, scope: !395)
!447 = !DILocation(line: 76, column: 3, scope: !395)
!448 = !DILocation(line: 76, column: 10, scope: !395)
!449 = !DILocation(line: 76, column: 28, scope: !395)
!450 = !DILocation(line: 78, column: 22, scope: !395)
!451 = !DILocation(line: 78, column: 29, scope: !395)
!452 = !DILocation(line: 78, column: 36, scope: !395)
!453 = !DILocation(line: 78, column: 43, scope: !395)
!454 = !DILocation(line: 78, column: 50, scope: !395)
!455 = !DILocation(line: 79, column: 5, scope: !395)
!456 = !DILocation(line: 79, column: 10, scope: !395)
!457 = !DILocation(line: 79, column: 8, scope: !395)
!458 = !DILocation(line: 79, column: 20, scope: !395)
!459 = !DILocation(line: 78, column: 3, scope: !395)
!460 = !DILocation(line: 81, column: 7, scope: !461)
!461 = distinct !DILexicalBlock(scope: !395, file: !1, line: 81, column: 7)
!462 = !DILocation(line: 81, column: 11, scope: !461)
!463 = !DILocation(line: 81, column: 30, scope: !461)
!464 = !DILocation(line: 81, column: 33, scope: !465)
!465 = !DILexicalBlockFile(scope: !461, file: !1, discriminator: 1)
!466 = !DILocation(line: 81, column: 40, scope: !465)
!467 = !DILocation(line: 81, column: 7, scope: !465)
!468 = !DILocation(line: 82, column: 11, scope: !461)
!469 = !DILocation(line: 82, column: 4, scope: !461)
!470 = !DILocation(line: 84, column: 3, scope: !395)
!471 = !DILocation(line: 84, column: 3, scope: !472)
!472 = !DILexicalBlockFile(scope: !395, file: !1, discriminator: 1)
!473 = !DILocation(line: 84, column: 3, scope: !474)
!474 = !DILexicalBlockFile(scope: !395, file: !1, discriminator: 2)
!475 = !DILocation(line: 84, column: 3, scope: !476)
!476 = !DILexicalBlockFile(scope: !395, file: !1, discriminator: 3)
!477 = !DILocation(line: 85, column: 3, scope: !395)
!478 = !DILocation(line: 85, column: 3, scope: !472)
!479 = !DILocation(line: 85, column: 3, scope: !474)
!480 = !DILocation(line: 85, column: 3, scope: !476)
!481 = !DILocation(line: 89, column: 35, scope: !395)
!482 = !DILocation(line: 89, column: 42, scope: !395)
!483 = !DILocation(line: 89, column: 3, scope: !395)
!484 = !DILocation(line: 89, column: 10, scope: !395)
!485 = !DILocation(line: 89, column: 17, scope: !395)
!486 = !DILocation(line: 89, column: 33, scope: !395)
!487 = !DILocation(line: 90, column: 37, scope: !395)
!488 = !DILocation(line: 90, column: 44, scope: !395)
!489 = !DILocation(line: 90, column: 3, scope: !395)
!490 = !DILocation(line: 90, column: 10, scope: !395)
!491 = !DILocation(line: 90, column: 17, scope: !395)
!492 = !DILocation(line: 90, column: 35, scope: !395)
!493 = !DILocation(line: 92, column: 3, scope: !395)
!494 = !DILocation(line: 92, column: 10, scope: !395)
!495 = !DILocation(line: 92, column: 19, scope: !395)
!496 = !DILocation(line: 93, column: 2, scope: !395)
!497 = !DILocation(line: 101, column: 3, scope: !396)
!498 = !DILocation(line: 101, column: 10, scope: !499)
!499 = !DILexicalBlockFile(scope: !396, file: !1, discriminator: 1)
!500 = !DILocation(line: 101, column: 17, scope: !499)
!501 = !DILocation(line: 101, column: 33, scope: !499)
!502 = !DILocation(line: 101, column: 3, scope: !499)
!503 = !DILocation(line: 102, column: 9, scope: !504)
!504 = distinct !DILexicalBlock(scope: !505, file: !1, line: 102, column: 8)
!505 = distinct !DILexicalBlock(scope: !396, file: !1, line: 101, column: 38)
!506 = !DILocation(line: 102, column: 8, scope: !504)
!507 = !DILocation(line: 102, column: 20, scope: !504)
!508 = !DILocation(line: 102, column: 17, scope: !504)
!509 = !DILocation(line: 102, column: 8, scope: !505)
!510 = !DILocation(line: 103, column: 5, scope: !504)
!511 = !DILocation(line: 105, column: 9, scope: !505)
!512 = !DILocation(line: 105, column: 8, scope: !505)
!513 = !DILocation(line: 105, column: 4, scope: !505)
!514 = !DILocation(line: 105, column: 18, scope: !505)
!515 = !DILocation(line: 106, column: 7, scope: !505)
!516 = !DILocation(line: 106, column: 4, scope: !505)
!517 = !DILocation(line: 107, column: 6, scope: !505)
!518 = !DILocation(line: 107, column: 13, scope: !505)
!519 = !DILocation(line: 107, column: 4, scope: !505)
!520 = !DILocation(line: 101, column: 3, scope: !521)
!521 = !DILexicalBlockFile(scope: !396, file: !1, discriminator: 2)
!522 = !DILocation(line: 110, column: 7, scope: !523)
!523 = distinct !DILexicalBlock(scope: !396, file: !1, line: 110, column: 7)
!524 = !DILocation(line: 110, column: 14, scope: !523)
!525 = !DILocation(line: 110, column: 21, scope: !523)
!526 = !DILocation(line: 110, column: 27, scope: !523)
!527 = !DILocation(line: 110, column: 7, scope: !396)
!528 = !DILocation(line: 111, column: 4, scope: !523)
!529 = !DILocation(line: 113, column: 22, scope: !396)
!530 = !DILocation(line: 113, column: 29, scope: !396)
!531 = !DILocation(line: 113, column: 36, scope: !396)
!532 = !DILocation(line: 113, column: 43, scope: !396)
!533 = !DILocation(line: 113, column: 50, scope: !396)
!534 = !DILocation(line: 113, column: 3, scope: !396)
!535 = !DILocation(line: 115, column: 3, scope: !396)
!536 = !DILocation(line: 115, column: 10, scope: !396)
!537 = !DILocation(line: 115, column: 19, scope: !396)
!538 = !DILocalVariable(name: "check_size", scope: !539, file: !1, line: 120, type: !397)
!539 = distinct !DILexicalBlock(scope: !396, file: !1, line: 119, column: 18)
!540 = !DILocation(line: 120, column: 16, scope: !539)
!541 = !DILocation(line: 120, column: 45, scope: !539)
!542 = !DILocation(line: 120, column: 52, scope: !539)
!543 = !DILocation(line: 120, column: 59, scope: !539)
!544 = !DILocation(line: 120, column: 29, scope: !539)
!545 = !DILocation(line: 121, column: 15, scope: !539)
!546 = !DILocation(line: 121, column: 22, scope: !539)
!547 = !DILocation(line: 121, column: 28, scope: !539)
!548 = !DILocation(line: 121, column: 35, scope: !539)
!549 = !DILocation(line: 121, column: 40, scope: !539)
!550 = !DILocation(line: 121, column: 47, scope: !539)
!551 = !DILocation(line: 121, column: 52, scope: !539)
!552 = !DILocation(line: 122, column: 5, scope: !539)
!553 = !DILocation(line: 122, column: 10, scope: !539)
!554 = !DILocation(line: 122, column: 19, scope: !539)
!555 = !DILocation(line: 121, column: 3, scope: !539)
!556 = !DILocation(line: 123, column: 7, scope: !557)
!557 = distinct !DILexicalBlock(scope: !539, file: !1, line: 123, column: 7)
!558 = !DILocation(line: 123, column: 14, scope: !557)
!559 = !DILocation(line: 123, column: 20, scope: !557)
!560 = !DILocation(line: 123, column: 18, scope: !557)
!561 = !DILocation(line: 123, column: 7, scope: !539)
!562 = !DILocation(line: 124, column: 4, scope: !557)
!563 = !DILocation(line: 126, column: 10, scope: !539)
!564 = !DILocation(line: 126, column: 17, scope: !539)
!565 = !DILocation(line: 126, column: 24, scope: !539)
!566 = !DILocation(line: 126, column: 3, scope: !539)
!567 = !DILocation(line: 126, column: 35, scope: !539)
!568 = !DILocation(line: 126, column: 42, scope: !539)
!569 = !DILocation(line: 126, column: 48, scope: !539)
!570 = !DILocation(line: 126, column: 55, scope: !539)
!571 = !DILocation(line: 127, column: 5, scope: !539)
!572 = !DILocation(line: 128, column: 3, scope: !539)
!573 = !DILocation(line: 132, column: 2, scope: !247)
!574 = !DILocation(line: 133, column: 1, scope: !247)
!575 = !DILocalVariable(name: "coder", arg: 1, scope: !248, file: !1, line: 137, type: !37)
!576 = !DILocation(line: 137, column: 31, scope: !248)
!577 = !DILocalVariable(name: "allocator", arg: 2, scope: !248, file: !1, line: 137, type: !53)
!578 = !DILocation(line: 137, column: 54, scope: !248)
!579 = !DILocation(line: 139, column: 17, scope: !248)
!580 = !DILocation(line: 139, column: 24, scope: !248)
!581 = !DILocation(line: 139, column: 30, scope: !248)
!582 = !DILocation(line: 139, column: 2, scope: !248)
!583 = !DILocation(line: 140, column: 12, scope: !248)
!584 = !DILocation(line: 140, column: 19, scope: !248)
!585 = !DILocation(line: 140, column: 2, scope: !248)
!586 = !DILocation(line: 141, column: 2, scope: !248)
!587 = !DILocalVariable(name: "coder", arg: 1, scope: !249, file: !1, line: 146, type: !37)
!588 = !DILocation(line: 146, column: 34, scope: !249)
!589 = !DILocalVariable(name: "allocator", arg: 2, scope: !249, file: !1, line: 146, type: !53)
!590 = !DILocation(line: 146, column: 57, scope: !249)
!591 = !DILocalVariable(name: "filters", arg: 3, scope: !249, file: !1, line: 147, type: !106)
!592 = !DILocation(line: 147, column: 22, scope: !249)
!593 = !DILocalVariable(name: "reversed_filters", arg: 4, scope: !249, file: !1, line: 148, type: !106)
!594 = !DILocation(line: 148, column: 22, scope: !249)
!595 = !DILocation(line: 150, column: 6, scope: !596)
!596 = distinct !DILexicalBlock(scope: !249, file: !1, line: 150, column: 6)
!597 = !DILocation(line: 150, column: 13, scope: !596)
!598 = !DILocation(line: 150, column: 22, scope: !596)
!599 = !DILocation(line: 150, column: 6, scope: !249)
!600 = !DILocation(line: 151, column: 3, scope: !596)
!601 = !DILocation(line: 154, column: 5, scope: !249)
!602 = !DILocation(line: 154, column: 12, scope: !249)
!603 = !DILocation(line: 154, column: 18, scope: !249)
!604 = !DILocation(line: 154, column: 29, scope: !249)
!605 = !DILocation(line: 153, column: 9, scope: !249)
!606 = !DILocation(line: 153, column: 2, scope: !249)
!607 = !DILocation(line: 155, column: 1, scope: !249)
!608 = !DILocalVariable(name: "strm", arg: 1, scope: !220, file: !1, line: 209, type: !223)
!609 = !DILocation(line: 209, column: 33, scope: !220)
!610 = !DILocalVariable(name: "block", arg: 2, scope: !220, file: !1, line: 209, type: !115)
!611 = !DILocation(line: 209, column: 51, scope: !220)
!612 = !DILocation(line: 211, column: 2, scope: !220)
!613 = !DILocalVariable(name: "ret_", scope: !614, file: !1, line: 211, type: !52)
!614 = distinct !DILexicalBlock(scope: !220, file: !1, line: 211, column: 2)
!615 = !DILocation(line: 211, column: 2, scope: !614)
!616 = !DILocation(line: 211, column: 2, scope: !617)
!617 = !DILexicalBlockFile(scope: !614, file: !1, discriminator: 1)
!618 = !DILocalVariable(name: "ret_", scope: !619, file: !1, line: 211, type: !406)
!619 = distinct !DILexicalBlock(scope: !614, file: !1, line: 211, column: 2)
!620 = !DILocation(line: 211, column: 2, scope: !619)
!621 = !DILocation(line: 211, column: 2, scope: !622)
!622 = !DILexicalBlockFile(scope: !619, file: !1, discriminator: 2)
!623 = !DILocation(line: 211, column: 2, scope: !624)
!624 = !DILexicalBlockFile(scope: !625, file: !1, discriminator: 3)
!625 = distinct !DILexicalBlock(scope: !619, file: !1, line: 211, column: 2)
!626 = !DILocation(line: 211, column: 2, scope: !627)
!627 = !DILexicalBlockFile(scope: !619, file: !1, discriminator: 4)
!628 = !DILocation(line: 211, column: 2, scope: !629)
!629 = !DILexicalBlockFile(scope: !614, file: !1, discriminator: 5)
!630 = !DILocation(line: 211, column: 2, scope: !631)
!631 = !DILexicalBlockFile(scope: !632, file: !1, discriminator: 6)
!632 = distinct !DILexicalBlock(scope: !633, file: !1, line: 211, column: 2)
!633 = distinct !DILexicalBlock(scope: !614, file: !1, line: 211, column: 2)
!634 = !DILocation(line: 211, column: 2, scope: !635)
!635 = !DILexicalBlockFile(scope: !614, file: !1, discriminator: 7)
!636 = !DILocation(line: 213, column: 2, scope: !220)
!637 = !DILocation(line: 213, column: 8, scope: !220)
!638 = !DILocation(line: 213, column: 18, scope: !220)
!639 = !DILocation(line: 213, column: 46, scope: !220)
!640 = !DILocation(line: 214, column: 2, scope: !220)
!641 = !DILocation(line: 214, column: 8, scope: !220)
!642 = !DILocation(line: 214, column: 18, scope: !220)
!643 = !DILocation(line: 214, column: 49, scope: !220)
!644 = !DILocation(line: 216, column: 2, scope: !220)
!645 = !DILocation(line: 217, column: 1, scope: !220)
