; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/block_decoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type { i32, %struct.lzma_next_coder_s, %struct.lzma_block*, i64, i64, i64, i64, %struct.lzma_check_state }
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

; Function Attrs: nounwind uwtable
define i32 @lzma_block_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_block* %block) #0 !dbg !216 {
entry:
  %retval = alloca i32, align 4
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %block.addr = alloca %struct.lzma_block*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !263, metadata !264), !dbg !265
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !266, metadata !264), !dbg !267
  store %struct.lzma_block* %block, %struct.lzma_block** %block.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_block** %block.addr, metadata !268, metadata !264), !dbg !269
  br label %do.body, !dbg !270

do.body:                                          ; preds = %entry
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !271
  %init = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %0, i32 0, i32 2, !dbg !271
  %1 = load i64, i64* %init, align 8, !dbg !271
  %cmp = icmp ne i64 ptrtoint (i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_block*)* @lzma_block_decoder_init to i64), %1, !dbg !271
  br i1 %cmp, label %if.then, label %if.end, !dbg !271

if.then:                                          ; preds = %do.body
  %2 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !275
  %3 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !275
  call void @lzma_next_end(%struct.lzma_next_coder_s* %2, %struct.lzma_allocator* %3), !dbg !275
  br label %if.end, !dbg !275

if.end:                                           ; preds = %if.then, %do.body
  %4 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !277
  %init1 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %4, i32 0, i32 2, !dbg !277
  store i64 ptrtoint (i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_block*)* @lzma_block_decoder_init to i64), i64* %init1, align 8, !dbg !277
  br label %do.end, !dbg !277

do.end:                                           ; preds = %if.end
  %5 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !279
  %call = call i64 @lzma_block_unpadded_size(%struct.lzma_block* %5) #8, !dbg !281
  %cmp2 = icmp eq i64 %call, 0, !dbg !282
  br i1 %cmp2, label %if.then7, label %lor.lhs.false, !dbg !283

lor.lhs.false:                                    ; preds = %do.end
  %6 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !284
  %uncompressed_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %6, i32 0, i32 4, !dbg !284
  %7 = load i64, i64* %uncompressed_size, align 8, !dbg !284
  %cmp3 = icmp ule i64 %7, 9223372036854775807, !dbg !284
  br i1 %cmp3, label %if.end8, label %lor.lhs.false4, !dbg !284

lor.lhs.false4:                                   ; preds = %lor.lhs.false
  %8 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !286
  %uncompressed_size5 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %8, i32 0, i32 4, !dbg !286
  %9 = load i64, i64* %uncompressed_size5, align 8, !dbg !286
  %cmp6 = icmp eq i64 %9, -1, !dbg !286
  br i1 %cmp6, label %if.end8, label %if.then7, !dbg !288

if.then7:                                         ; preds = %lor.lhs.false4, %do.end
  store i32 11, i32* %retval, align 4, !dbg !290
  br label %return, !dbg !290

if.end8:                                          ; preds = %lor.lhs.false4, %lor.lhs.false
  %10 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !291
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %10, i32 0, i32 0, !dbg !293
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !293
  %cmp9 = icmp eq %struct.lzma_coder_s* %11, null, !dbg !294
  br i1 %cmp9, label %if.then10, label %if.end19, !dbg !295

if.then10:                                        ; preds = %if.end8
  %12 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !296
  %call11 = call noalias i8* @lzma_alloc(i64 216, %struct.lzma_allocator* %12), !dbg !298
  %13 = bitcast i8* %call11 to %struct.lzma_coder_s*, !dbg !298
  %14 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !299
  %coder12 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %14, i32 0, i32 0, !dbg !300
  store %struct.lzma_coder_s* %13, %struct.lzma_coder_s** %coder12, align 8, !dbg !301
  %15 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !302
  %coder13 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %15, i32 0, i32 0, !dbg !304
  %16 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder13, align 8, !dbg !304
  %cmp14 = icmp eq %struct.lzma_coder_s* %16, null, !dbg !305
  br i1 %cmp14, label %if.then15, label %if.end16, !dbg !306

if.then15:                                        ; preds = %if.then10
  store i32 5, i32* %retval, align 4, !dbg !307
  br label %return, !dbg !307

if.end16:                                         ; preds = %if.then10
  %17 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !308
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %17, i32 0, i32 3, !dbg !309
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* @block_decode, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !310
  %18 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !311
  %end = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %18, i32 0, i32 4, !dbg !312
  store void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* @block_decoder_end, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !313
  %19 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !314
  %coder17 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %19, i32 0, i32 0, !dbg !315
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder17, align 8, !dbg !315
  %next18 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %20, i32 0, i32 1, !dbg !316
  %21 = bitcast %struct.lzma_next_coder_s* %next18 to i8*, !dbg !317
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %21, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !317
  br label %if.end19, !dbg !318

if.end19:                                         ; preds = %if.end16, %if.end8
  %22 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !319
  %coder20 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %22, i32 0, i32 0, !dbg !320
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder20, align 8, !dbg !320
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 0, !dbg !321
  store i32 0, i32* %sequence, align 8, !dbg !322
  %24 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !323
  %25 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !324
  %coder21 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %25, i32 0, i32 0, !dbg !325
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder21, align 8, !dbg !325
  %block22 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %26, i32 0, i32 2, !dbg !326
  store %struct.lzma_block* %24, %struct.lzma_block** %block22, align 8, !dbg !327
  %27 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !328
  %coder23 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %27, i32 0, i32 0, !dbg !329
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder23, align 8, !dbg !329
  %compressed_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %28, i32 0, i32 3, !dbg !330
  store i64 0, i64* %compressed_size, align 8, !dbg !331
  %29 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !332
  %coder24 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %29, i32 0, i32 0, !dbg !333
  %30 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder24, align 8, !dbg !333
  %uncompressed_size25 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %30, i32 0, i32 4, !dbg !334
  store i64 0, i64* %uncompressed_size25, align 8, !dbg !335
  %31 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !336
  %compressed_size26 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %31, i32 0, i32 3, !dbg !337
  %32 = load i64, i64* %compressed_size26, align 8, !dbg !337
  %cmp27 = icmp eq i64 %32, -1, !dbg !338
  br i1 %cmp27, label %cond.true, label %cond.false, !dbg !336

cond.true:                                        ; preds = %if.end19
  %33 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !339
  %header_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %33, i32 0, i32 1, !dbg !340
  %34 = load i32, i32* %header_size, align 4, !dbg !340
  %conv = zext i32 %34 to i64, !dbg !339
  %sub = sub i64 9223372036854775804, %conv, !dbg !341
  %35 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !342
  %check = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %35, i32 0, i32 2, !dbg !343
  %36 = load i32, i32* %check, align 8, !dbg !343
  %call28 = call i32 @lzma_check_size(i32 %36) #1, !dbg !344
  %conv29 = zext i32 %call28 to i64, !dbg !344
  %sub30 = sub i64 %sub, %conv29, !dbg !345
  br label %cond.end, !dbg !346

cond.false:                                       ; preds = %if.end19
  %37 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !347
  %compressed_size31 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %37, i32 0, i32 3, !dbg !348
  %38 = load i64, i64* %compressed_size31, align 8, !dbg !348
  br label %cond.end, !dbg !349

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %sub30, %cond.true ], [ %38, %cond.false ], !dbg !351
  %39 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !353
  %coder32 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %39, i32 0, i32 0, !dbg !354
  %40 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder32, align 8, !dbg !354
  %compressed_limit = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %40, i32 0, i32 5, !dbg !355
  store i64 %cond, i64* %compressed_limit, align 8, !dbg !356
  %41 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !357
  %coder33 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %41, i32 0, i32 0, !dbg !358
  %42 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder33, align 8, !dbg !358
  %check_pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %42, i32 0, i32 6, !dbg !359
  store i64 0, i64* %check_pos, align 8, !dbg !360
  %43 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !361
  %coder34 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %43, i32 0, i32 0, !dbg !362
  %44 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder34, align 8, !dbg !362
  %check35 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %44, i32 0, i32 7, !dbg !363
  %45 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !364
  %check36 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %45, i32 0, i32 2, !dbg !365
  %46 = load i32, i32* %check36, align 8, !dbg !365
  call void @lzma_check_init(%struct.lzma_check_state* %check35, i32 %46), !dbg !366
  %47 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !367
  %coder37 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %47, i32 0, i32 0, !dbg !368
  %48 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder37, align 8, !dbg !368
  %next38 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %48, i32 0, i32 1, !dbg !369
  %49 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !370
  %50 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !371
  %filters = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %50, i32 0, i32 5, !dbg !372
  %51 = load %struct.lzma_filter*, %struct.lzma_filter** %filters, align 8, !dbg !372
  %call39 = call i32 @lzma_raw_decoder_init(%struct.lzma_next_coder_s* %next38, %struct.lzma_allocator* %49, %struct.lzma_filter* %51), !dbg !373
  store i32 %call39, i32* %retval, align 4, !dbg !374
  br label %return, !dbg !374

return:                                           ; preds = %cond.end, %if.then15, %if.then7
  %52 = load i32, i32* %retval, align 4, !dbg !375
  ret i32 %52, !dbg !375
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @lzma_next_end(%struct.lzma_next_coder_s*, %struct.lzma_allocator*) #2

; Function Attrs: nounwind readonly
declare i64 @lzma_block_unpadded_size(%struct.lzma_block*) #3

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #2

; Function Attrs: nounwind uwtable
define internal i32 @block_decode(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, i8* noalias %in, i64* noalias %in_pos, i64 %in_size, i8* noalias %out, i64* noalias %out_pos, i64 %out_size, i32 %action) #0 !dbg !248 {
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
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !376, metadata !264), !dbg !377
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !378, metadata !264), !dbg !379
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !380, metadata !264), !dbg !381
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !382, metadata !264), !dbg !383
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !384, metadata !264), !dbg !385
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !386, metadata !264), !dbg !387
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !388, metadata !264), !dbg !389
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !390, metadata !264), !dbg !391
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !392, metadata !264), !dbg !393
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !394
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 0, !dbg !395
  %1 = load i32, i32* %sequence, align 8, !dbg !395
  switch i32 %1, label %sw.epilog [
    i32 0, label %sw.bb
    i32 1, label %sw.bb29
    i32 2, label %sw.bb50
  ], !dbg !396

sw.bb:                                            ; preds = %entry
  call void @llvm.dbg.declare(metadata i64* %in_start, metadata !397, metadata !264), !dbg !401
  %2 = load i64*, i64** %in_pos.addr, align 8, !dbg !402
  %3 = load i64, i64* %2, align 8, !dbg !403
  store i64 %3, i64* %in_start, align 8, !dbg !401
  call void @llvm.dbg.declare(metadata i64* %out_start, metadata !404, metadata !264), !dbg !405
  %4 = load i64*, i64** %out_pos.addr, align 8, !dbg !406
  %5 = load i64, i64* %4, align 8, !dbg !407
  store i64 %5, i64* %out_start, align 8, !dbg !405
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !408, metadata !264), !dbg !410
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !411
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %6, i32 0, i32 1, !dbg !412
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 3, !dbg !413
  %7 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !413
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !414
  %next1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %8, i32 0, i32 1, !dbg !415
  %coder2 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next1, i32 0, i32 0, !dbg !416
  %9 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder2, align 8, !dbg !416
  %10 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !417
  %11 = load i8*, i8** %in.addr, align 8, !dbg !418
  %12 = load i64*, i64** %in_pos.addr, align 8, !dbg !419
  %13 = load i64, i64* %in_size.addr, align 8, !dbg !420
  %14 = load i8*, i8** %out.addr, align 8, !dbg !421
  %15 = load i64*, i64** %out_pos.addr, align 8, !dbg !422
  %16 = load i64, i64* %out_size.addr, align 8, !dbg !423
  %17 = load i32, i32* %action.addr, align 4, !dbg !424
  %call = call i32 %7(%struct.lzma_coder_s* %9, %struct.lzma_allocator* %10, i8* %11, i64* %12, i64 %13, i8* %14, i64* %15, i64 %16, i32 %17), !dbg !411
  store i32 %call, i32* %ret, align 4, !dbg !410
  call void @llvm.dbg.declare(metadata i64* %in_used, metadata !425, metadata !264), !dbg !426
  %18 = load i64*, i64** %in_pos.addr, align 8, !dbg !427
  %19 = load i64, i64* %18, align 8, !dbg !428
  %20 = load i64, i64* %in_start, align 8, !dbg !429
  %sub = sub i64 %19, %20, !dbg !430
  store i64 %sub, i64* %in_used, align 8, !dbg !426
  call void @llvm.dbg.declare(metadata i64* %out_used, metadata !431, metadata !264), !dbg !432
  %21 = load i64*, i64** %out_pos.addr, align 8, !dbg !433
  %22 = load i64, i64* %21, align 8, !dbg !434
  %23 = load i64, i64* %out_start, align 8, !dbg !435
  %sub3 = sub i64 %22, %23, !dbg !436
  store i64 %sub3, i64* %out_used, align 8, !dbg !432
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !437
  %compressed_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %24, i32 0, i32 3, !dbg !439
  %25 = load i64, i64* %in_used, align 8, !dbg !440
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !441
  %compressed_limit = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %26, i32 0, i32 5, !dbg !442
  %27 = load i64, i64* %compressed_limit, align 8, !dbg !442
  %call4 = call zeroext i1 @update_size(i64* %compressed_size, i64 %25, i64 %27), !dbg !443
  br i1 %call4, label %if.then, label %lor.lhs.false, !dbg !444

lor.lhs.false:                                    ; preds = %sw.bb
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !445
  %uncompressed_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %28, i32 0, i32 4, !dbg !447
  %29 = load i64, i64* %out_used, align 8, !dbg !448
  %30 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !449
  %block = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %30, i32 0, i32 2, !dbg !450
  %31 = load %struct.lzma_block*, %struct.lzma_block** %block, align 8, !dbg !450
  %uncompressed_size5 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %31, i32 0, i32 4, !dbg !451
  %32 = load i64, i64* %uncompressed_size5, align 8, !dbg !451
  %call6 = call zeroext i1 @update_size(i64* %uncompressed_size, i64 %29, i64 %32), !dbg !452
  br i1 %call6, label %if.then, label %if.end, !dbg !453

if.then:                                          ; preds = %lor.lhs.false, %sw.bb
  store i32 9, i32* %retval, align 4, !dbg !455
  br label %return, !dbg !455

if.end:                                           ; preds = %lor.lhs.false
  %33 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !456
  %check = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %33, i32 0, i32 7, !dbg !457
  %34 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !458
  %block7 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %34, i32 0, i32 2, !dbg !459
  %35 = load %struct.lzma_block*, %struct.lzma_block** %block7, align 8, !dbg !459
  %check8 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %35, i32 0, i32 2, !dbg !460
  %36 = load i32, i32* %check8, align 8, !dbg !460
  %37 = load i8*, i8** %out.addr, align 8, !dbg !461
  %38 = load i64, i64* %out_start, align 8, !dbg !462
  %add.ptr = getelementptr inbounds i8, i8* %37, i64 %38, !dbg !463
  %39 = load i64, i64* %out_used, align 8, !dbg !464
  call void @lzma_check_update(%struct.lzma_check_state* %check, i32 %36, i8* %add.ptr, i64 %39), !dbg !465
  %40 = load i32, i32* %ret, align 4, !dbg !466
  %cmp = icmp ne i32 %40, 1, !dbg !468
  br i1 %cmp, label %if.then9, label %if.end10, !dbg !469

if.then9:                                         ; preds = %if.end
  %41 = load i32, i32* %ret, align 4, !dbg !470
  store i32 %41, i32* %retval, align 4, !dbg !471
  br label %return, !dbg !471

if.end10:                                         ; preds = %if.end
  %42 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !472
  %compressed_size11 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %42, i32 0, i32 3, !dbg !474
  %43 = load i64, i64* %compressed_size11, align 8, !dbg !474
  %44 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !475
  %block12 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %44, i32 0, i32 2, !dbg !476
  %45 = load %struct.lzma_block*, %struct.lzma_block** %block12, align 8, !dbg !476
  %compressed_size13 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %45, i32 0, i32 3, !dbg !477
  %46 = load i64, i64* %compressed_size13, align 8, !dbg !477
  %call14 = call zeroext i1 @is_size_valid(i64 %43, i64 %46), !dbg !478
  br i1 %call14, label %lor.lhs.false15, label %if.then20, !dbg !479

lor.lhs.false15:                                  ; preds = %if.end10
  %47 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !480
  %uncompressed_size16 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %47, i32 0, i32 4, !dbg !482
  %48 = load i64, i64* %uncompressed_size16, align 8, !dbg !482
  %49 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !483
  %block17 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %49, i32 0, i32 2, !dbg !484
  %50 = load %struct.lzma_block*, %struct.lzma_block** %block17, align 8, !dbg !484
  %uncompressed_size18 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %50, i32 0, i32 4, !dbg !485
  %51 = load i64, i64* %uncompressed_size18, align 8, !dbg !485
  %call19 = call zeroext i1 @is_size_valid(i64 %48, i64 %51), !dbg !486
  br i1 %call19, label %if.end21, label %if.then20, !dbg !487

if.then20:                                        ; preds = %lor.lhs.false15, %if.end10
  store i32 9, i32* %retval, align 4, !dbg !488
  br label %return, !dbg !488

if.end21:                                         ; preds = %lor.lhs.false15
  %52 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !489
  %compressed_size22 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %52, i32 0, i32 3, !dbg !490
  %53 = load i64, i64* %compressed_size22, align 8, !dbg !490
  %54 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !491
  %block23 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %54, i32 0, i32 2, !dbg !492
  %55 = load %struct.lzma_block*, %struct.lzma_block** %block23, align 8, !dbg !492
  %compressed_size24 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %55, i32 0, i32 3, !dbg !493
  store i64 %53, i64* %compressed_size24, align 8, !dbg !494
  %56 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !495
  %uncompressed_size25 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %56, i32 0, i32 4, !dbg !496
  %57 = load i64, i64* %uncompressed_size25, align 8, !dbg !496
  %58 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !497
  %block26 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %58, i32 0, i32 2, !dbg !498
  %59 = load %struct.lzma_block*, %struct.lzma_block** %block26, align 8, !dbg !498
  %uncompressed_size27 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %59, i32 0, i32 4, !dbg !499
  store i64 %57, i64* %uncompressed_size27, align 8, !dbg !500
  %60 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !501
  %sequence28 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %60, i32 0, i32 0, !dbg !502
  store i32 1, i32* %sequence28, align 8, !dbg !503
  br label %sw.bb29, !dbg !504

sw.bb29:                                          ; preds = %entry, %if.end21
  br label %while.cond, !dbg !505

while.cond:                                       ; preds = %if.end39, %sw.bb29
  %61 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !506
  %compressed_size30 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %61, i32 0, i32 3, !dbg !508
  %62 = load i64, i64* %compressed_size30, align 8, !dbg !508
  %and = and i64 %62, 3, !dbg !509
  %tobool = icmp ne i64 %and, 0, !dbg !510
  br i1 %tobool, label %while.body, label %while.end, !dbg !510

while.body:                                       ; preds = %while.cond
  %63 = load i64*, i64** %in_pos.addr, align 8, !dbg !511
  %64 = load i64, i64* %63, align 8, !dbg !514
  %65 = load i64, i64* %in_size.addr, align 8, !dbg !515
  %cmp31 = icmp uge i64 %64, %65, !dbg !516
  br i1 %cmp31, label %if.then32, label %if.end33, !dbg !517

if.then32:                                        ; preds = %while.body
  store i32 0, i32* %retval, align 4, !dbg !518
  br label %return, !dbg !518

if.end33:                                         ; preds = %while.body
  %66 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !519
  %compressed_size34 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %66, i32 0, i32 3, !dbg !520
  %67 = load i64, i64* %compressed_size34, align 8, !dbg !521
  %inc = add i64 %67, 1, !dbg !521
  store i64 %inc, i64* %compressed_size34, align 8, !dbg !521
  %68 = load i64*, i64** %in_pos.addr, align 8, !dbg !522
  %69 = load i64, i64* %68, align 8, !dbg !524
  %inc35 = add i64 %69, 1, !dbg !524
  store i64 %inc35, i64* %68, align 8, !dbg !524
  %70 = load i8*, i8** %in.addr, align 8, !dbg !525
  %arrayidx = getelementptr inbounds i8, i8* %70, i64 %69, !dbg !525
  %71 = load i8, i8* %arrayidx, align 1, !dbg !525
  %conv = zext i8 %71 to i32, !dbg !525
  %cmp36 = icmp ne i32 %conv, 0, !dbg !526
  br i1 %cmp36, label %if.then38, label %if.end39, !dbg !527

if.then38:                                        ; preds = %if.end33
  store i32 9, i32* %retval, align 4, !dbg !528
  br label %return, !dbg !528

if.end39:                                         ; preds = %if.end33
  br label %while.cond, !dbg !529

while.end:                                        ; preds = %while.cond
  %72 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !531
  %block40 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %72, i32 0, i32 2, !dbg !533
  %73 = load %struct.lzma_block*, %struct.lzma_block** %block40, align 8, !dbg !533
  %check41 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %73, i32 0, i32 2, !dbg !534
  %74 = load i32, i32* %check41, align 8, !dbg !534
  %cmp42 = icmp eq i32 %74, 0, !dbg !535
  br i1 %cmp42, label %if.then44, label %if.end45, !dbg !536

if.then44:                                        ; preds = %while.end
  store i32 1, i32* %retval, align 4, !dbg !537
  br label %return, !dbg !537

if.end45:                                         ; preds = %while.end
  %75 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !538
  %check46 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %75, i32 0, i32 7, !dbg !539
  %76 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !540
  %block47 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %76, i32 0, i32 2, !dbg !541
  %77 = load %struct.lzma_block*, %struct.lzma_block** %block47, align 8, !dbg !541
  %check48 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %77, i32 0, i32 2, !dbg !542
  %78 = load i32, i32* %check48, align 8, !dbg !542
  call void @lzma_check_finish(%struct.lzma_check_state* %check46, i32 %78), !dbg !543
  %79 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !544
  %sequence49 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %79, i32 0, i32 0, !dbg !545
  store i32 2, i32* %sequence49, align 8, !dbg !546
  br label %sw.bb50, !dbg !544

sw.bb50:                                          ; preds = %entry, %if.end45
  call void @llvm.dbg.declare(metadata i64* %check_size, metadata !547, metadata !264), !dbg !549
  %80 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !550
  %block51 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %80, i32 0, i32 2, !dbg !551
  %81 = load %struct.lzma_block*, %struct.lzma_block** %block51, align 8, !dbg !551
  %check52 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %81, i32 0, i32 2, !dbg !552
  %82 = load i32, i32* %check52, align 8, !dbg !552
  %call53 = call i32 @lzma_check_size(i32 %82) #1, !dbg !553
  %conv54 = zext i32 %call53 to i64, !dbg !553
  store i64 %conv54, i64* %check_size, align 8, !dbg !549
  %83 = load i8*, i8** %in.addr, align 8, !dbg !554
  %84 = load i64*, i64** %in_pos.addr, align 8, !dbg !555
  %85 = load i64, i64* %in_size.addr, align 8, !dbg !556
  %86 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !557
  %block55 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %86, i32 0, i32 2, !dbg !558
  %87 = load %struct.lzma_block*, %struct.lzma_block** %block55, align 8, !dbg !558
  %raw_check = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %87, i32 0, i32 6, !dbg !559
  %arraydecay = getelementptr inbounds [64 x i8], [64 x i8]* %raw_check, i32 0, i32 0, !dbg !557
  %88 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !560
  %check_pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %88, i32 0, i32 6, !dbg !561
  %89 = load i64, i64* %check_size, align 8, !dbg !562
  %call56 = call i64 @lzma_bufcpy(i8* %83, i64* %84, i64 %85, i8* %arraydecay, i64* %check_pos, i64 %89), !dbg !563
  %90 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !564
  %check_pos57 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %90, i32 0, i32 6, !dbg !566
  %91 = load i64, i64* %check_pos57, align 8, !dbg !566
  %92 = load i64, i64* %check_size, align 8, !dbg !567
  %cmp58 = icmp ult i64 %91, %92, !dbg !568
  br i1 %cmp58, label %if.then60, label %if.end61, !dbg !569

if.then60:                                        ; preds = %sw.bb50
  store i32 0, i32* %retval, align 4, !dbg !570
  br label %return, !dbg !570

if.end61:                                         ; preds = %sw.bb50
  %93 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !571
  %block62 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %93, i32 0, i32 2, !dbg !573
  %94 = load %struct.lzma_block*, %struct.lzma_block** %block62, align 8, !dbg !573
  %check63 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %94, i32 0, i32 2, !dbg !574
  %95 = load i32, i32* %check63, align 8, !dbg !574
  %call64 = call zeroext i8 @lzma_check_is_supported(i32 %95) #1, !dbg !575
  %conv65 = zext i8 %call64 to i32, !dbg !575
  %tobool66 = icmp ne i32 %conv65, 0, !dbg !575
  br i1 %tobool66, label %land.lhs.true, label %if.end76, !dbg !576

land.lhs.true:                                    ; preds = %if.end61
  %96 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !577
  %block67 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %96, i32 0, i32 2, !dbg !579
  %97 = load %struct.lzma_block*, %struct.lzma_block** %block67, align 8, !dbg !579
  %raw_check68 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %97, i32 0, i32 6, !dbg !580
  %arraydecay69 = getelementptr inbounds [64 x i8], [64 x i8]* %raw_check68, i32 0, i32 0, !dbg !577
  %98 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !581
  %check70 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %98, i32 0, i32 7, !dbg !582
  %buffer = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %check70, i32 0, i32 0, !dbg !583
  %u8 = bitcast %union.anon* %buffer to [64 x i8]*, !dbg !584
  %arraydecay71 = getelementptr inbounds [64 x i8], [64 x i8]* %u8, i32 0, i32 0, !dbg !581
  %99 = load i64, i64* %check_size, align 8, !dbg !585
  %call72 = call i32 @memcmp(i8* %arraydecay69, i8* %arraydecay71, i64 %99) #8, !dbg !586
  %cmp73 = icmp ne i32 %call72, 0, !dbg !587
  br i1 %cmp73, label %if.then75, label %if.end76, !dbg !588

if.then75:                                        ; preds = %land.lhs.true
  store i32 9, i32* %retval, align 4, !dbg !590
  br label %return, !dbg !590

if.end76:                                         ; preds = %land.lhs.true, %if.end61
  store i32 1, i32* %retval, align 4, !dbg !591
  br label %return, !dbg !591

sw.epilog:                                        ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !592
  br label %return, !dbg !592

return:                                           ; preds = %sw.epilog, %if.end76, %if.then75, %if.then60, %if.then44, %if.then38, %if.then32, %if.then20, %if.then9, %if.then
  %100 = load i32, i32* %retval, align 4, !dbg !593
  ret i32 %100, !dbg !593
}

; Function Attrs: nounwind uwtable
define internal void @block_decoder_end(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator) #0 !dbg !256 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !594, metadata !264), !dbg !595
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !596, metadata !264), !dbg !597
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !598
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 1, !dbg !599
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !600
  call void @lzma_next_end(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %1), !dbg !601
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !602
  %3 = bitcast %struct.lzma_coder_s* %2 to i8*, !dbg !602
  %4 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !603
  call void @lzma_free(i8* %3, %struct.lzma_allocator* %4), !dbg !604
  ret void, !dbg !605
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

; Function Attrs: nounwind readnone
declare i32 @lzma_check_size(i32) #5

declare void @lzma_check_init(%struct.lzma_check_state*, i32) #2

declare i32 @lzma_raw_decoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*) #2

; Function Attrs: nounwind uwtable
define i32 @lzma_block_decoder(%struct.lzma_stream* %strm, %struct.lzma_block* %block) #0 !dbg !221 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzma_stream*, align 8
  %block.addr = alloca %struct.lzma_block*, align 8
  %ret_ = alloca i32, align 4
  %ret_2 = alloca i32, align 4
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !606, metadata !264), !dbg !607
  store %struct.lzma_block* %block, %struct.lzma_block** %block.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_block** %block.addr, metadata !608, metadata !264), !dbg !609
  br label %do.body, !dbg !610

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !611, metadata !264), !dbg !613
  br label %do.body1, !dbg !614

do.body1:                                         ; preds = %do.body
  call void @llvm.dbg.declare(metadata i32* %ret_2, metadata !616, metadata !264), !dbg !618
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !619
  %call = call i32 @lzma_strm_init(%struct.lzma_stream* %0), !dbg !619
  store i32 %call, i32* %ret_2, align 4, !dbg !619
  %1 = load i32, i32* %ret_2, align 4, !dbg !619
  %cmp = icmp ne i32 %1, 0, !dbg !619
  br i1 %cmp, label %if.then, label %if.end, !dbg !619

if.then:                                          ; preds = %do.body1
  %2 = load i32, i32* %ret_2, align 4, !dbg !621
  store i32 %2, i32* %retval, align 4, !dbg !621
  br label %return, !dbg !621

if.end:                                           ; preds = %do.body1
  br label %do.end, !dbg !624

do.end:                                           ; preds = %if.end
  %3 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !626
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %3, i32 0, i32 7, !dbg !626
  %4 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !626
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %4, i32 0, i32 0, !dbg !626
  %5 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !626
  %allocator = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %5, i32 0, i32 6, !dbg !626
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator, align 8, !dbg !626
  %7 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !626
  %call3 = call i32 @lzma_block_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %6, %struct.lzma_block* %7), !dbg !626
  store i32 %call3, i32* %ret_, align 4, !dbg !626
  %8 = load i32, i32* %ret_, align 4, !dbg !626
  %cmp4 = icmp ne i32 %8, 0, !dbg !626
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !626

if.then5:                                         ; preds = %do.end
  %9 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !628
  call void @lzma_end(%struct.lzma_stream* %9) #9, !dbg !628
  %10 = load i32, i32* %ret_, align 4, !dbg !628
  store i32 %10, i32* %retval, align 4, !dbg !628
  br label %return, !dbg !628

if.end6:                                          ; preds = %do.end
  br label %do.end7, !dbg !632

do.end7:                                          ; preds = %if.end6
  %11 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !634
  %internal8 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %11, i32 0, i32 7, !dbg !635
  %12 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal8, align 8, !dbg !635
  %supported_actions = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %12, i32 0, i32 3, !dbg !636
  %arrayidx = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions, i64 0, i64 0, !dbg !634
  store i8 1, i8* %arrayidx, align 8, !dbg !637
  %13 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !638
  %internal9 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %13, i32 0, i32 7, !dbg !639
  %14 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal9, align 8, !dbg !639
  %supported_actions10 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %14, i32 0, i32 3, !dbg !640
  %arrayidx11 = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions10, i64 0, i64 3, !dbg !638
  store i8 1, i8* %arrayidx11, align 1, !dbg !641
  store i32 0, i32* %retval, align 4, !dbg !642
  br label %return, !dbg !642

return:                                           ; preds = %do.end7, %if.then5, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !643
  ret i32 %15, !dbg !643
}

declare i32 @lzma_strm_init(%struct.lzma_stream*) #2

; Function Attrs: nounwind
declare void @lzma_end(%struct.lzma_stream*) #6

; Function Attrs: inlinehint nounwind uwtable
define internal zeroext i1 @update_size(i64* %size, i64 %add, i64 %limit) #7 !dbg !249 {
entry:
  %retval = alloca i1, align 1
  %size.addr = alloca i64*, align 8
  %add.addr = alloca i64, align 8
  %limit.addr = alloca i64, align 8
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !644, metadata !264), !dbg !645
  store i64 %add, i64* %add.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %add.addr, metadata !646, metadata !264), !dbg !647
  store i64 %limit, i64* %limit.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %limit.addr, metadata !648, metadata !264), !dbg !649
  %0 = load i64, i64* %limit.addr, align 8, !dbg !650
  %cmp = icmp ugt i64 %0, 9223372036854775807, !dbg !652
  br i1 %cmp, label %if.then, label %if.end, !dbg !653

if.then:                                          ; preds = %entry
  store i64 9223372036854775807, i64* %limit.addr, align 8, !dbg !654
  br label %if.end, !dbg !655

if.end:                                           ; preds = %if.then, %entry
  %1 = load i64, i64* %limit.addr, align 8, !dbg !656
  %2 = load i64*, i64** %size.addr, align 8, !dbg !658
  %3 = load i64, i64* %2, align 8, !dbg !659
  %cmp1 = icmp ult i64 %1, %3, !dbg !660
  br i1 %cmp1, label %if.then3, label %lor.lhs.false, !dbg !661

lor.lhs.false:                                    ; preds = %if.end
  %4 = load i64, i64* %limit.addr, align 8, !dbg !662
  %5 = load i64*, i64** %size.addr, align 8, !dbg !664
  %6 = load i64, i64* %5, align 8, !dbg !665
  %sub = sub i64 %4, %6, !dbg !666
  %7 = load i64, i64* %add.addr, align 8, !dbg !667
  %cmp2 = icmp ult i64 %sub, %7, !dbg !668
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !669

if.then3:                                         ; preds = %lor.lhs.false, %if.end
  store i1 true, i1* %retval, align 1, !dbg !670
  br label %return, !dbg !670

if.end4:                                          ; preds = %lor.lhs.false
  %8 = load i64, i64* %add.addr, align 8, !dbg !671
  %9 = load i64*, i64** %size.addr, align 8, !dbg !672
  %10 = load i64, i64* %9, align 8, !dbg !673
  %add5 = add i64 %10, %8, !dbg !673
  store i64 %add5, i64* %9, align 8, !dbg !673
  store i1 false, i1* %retval, align 1, !dbg !674
  br label %return, !dbg !674

return:                                           ; preds = %if.end4, %if.then3
  %11 = load i1, i1* %retval, align 1, !dbg !675
  ret i1 %11, !dbg !675
}

declare void @lzma_check_update(%struct.lzma_check_state*, i32, i8*, i64) #2

; Function Attrs: inlinehint nounwind uwtable
define internal zeroext i1 @is_size_valid(i64 %size, i64 %reference) #7 !dbg !253 {
entry:
  %size.addr = alloca i64, align 8
  %reference.addr = alloca i64, align 8
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !676, metadata !264), !dbg !677
  store i64 %reference, i64* %reference.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %reference.addr, metadata !678, metadata !264), !dbg !679
  %0 = load i64, i64* %reference.addr, align 8, !dbg !680
  %cmp = icmp eq i64 %0, -1, !dbg !681
  br i1 %cmp, label %lor.end, label %lor.rhs, !dbg !682

lor.rhs:                                          ; preds = %entry
  %1 = load i64, i64* %reference.addr, align 8, !dbg !683
  %2 = load i64, i64* %size.addr, align 8, !dbg !685
  %cmp1 = icmp eq i64 %1, %2, !dbg !686
  br label %lor.end, !dbg !687

lor.end:                                          ; preds = %lor.rhs, %entry
  %3 = phi i1 [ true, %entry ], [ %cmp1, %lor.rhs ]
  ret i1 %3, !dbg !688
}

declare void @lzma_check_finish(%struct.lzma_check_state*, i32) #2

declare i64 @lzma_bufcpy(i8*, i64*, i64, i8*, i64*, i64) #2

; Function Attrs: nounwind readnone
declare zeroext i8 @lzma_check_is_supported(i32) #5

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #3

declare void @lzma_free(i8*, %struct.lzma_allocator*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { nounwind readonly }
attributes #9 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!260, !261}
!llvm.ident = !{!262}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !214, subprograms: !215, globals: !257)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/block_decoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !87, !144, !70, !195}
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
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !19, file: !1, line: 19, size: 32, align: 32, elements: !191)
!19 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !1, line: 18, size: 1728, align: 64, elements: !20)
!20 = !{!21, !22, !112, !159, !160, !161, !162, !163}
!21 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !19, file: !1, line: 23, baseType: !18, size: 32, align: 32)
!22 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !19, file: !1, line: 26, baseType: !23, size: 512, align: 64, offset: 64)
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
!112 = !DIDerivedType(tag: DW_TAG_member, name: "block", scope: !19, file: !1, line: 30, baseType: !113, size: 64, align: 64, offset: 576)
!113 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !114, size: 64, align: 64)
!114 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_block", file: !115, line: 245, baseType: !116)
!115 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/block.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!116 = !DICompositeType(tag: DW_TAG_structure_type, file: !115, line: 30, size: 1664, align: 64, elements: !117)
!117 = !{!118, !121, !122, !123, !124, !125, !127, !131, !132, !133, !134, !135, !136, !137, !138, !139, !140, !141, !142, !147, !148, !149, !150, !152, !153, !154, !155, !156, !157, !158}
!118 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !116, file: !115, line: 47, baseType: !119, size: 32, align: 32)
!119 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !34, line: 51, baseType: !120)
!120 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "header_size", scope: !116, file: !115, line: 67, baseType: !119, size: 32, align: 32, offset: 32)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !116, file: !115, line: 88, baseType: !85, size: 32, align: 32, offset: 64)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_size", scope: !116, file: !115, line: 143, baseType: !31, size: 64, align: 64, offset: 128)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !116, file: !115, line: 167, baseType: !31, size: 64, align: 64, offset: 192)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "filters", scope: !116, file: !115, line: 195, baseType: !126, size: 64, align: 64, offset: 256)
!126 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !106, size: 64, align: 64)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "raw_check", scope: !116, file: !115, line: 212, baseType: !128, size: 512, align: 8, offset: 320)
!128 = !DICompositeType(tag: DW_TAG_array_type, baseType: !63, size: 512, align: 8, elements: !129)
!129 = !{!130}
!130 = !DISubrange(count: 64)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !116, file: !115, line: 221, baseType: !52, size: 64, align: 64, offset: 832)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !116, file: !115, line: 222, baseType: !52, size: 64, align: 64, offset: 896)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !116, file: !115, line: 223, baseType: !52, size: 64, align: 64, offset: 960)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !116, file: !115, line: 224, baseType: !119, size: 32, align: 32, offset: 1024)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !116, file: !115, line: 225, baseType: !119, size: 32, align: 32, offset: 1056)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !116, file: !115, line: 226, baseType: !31, size: 64, align: 64, offset: 1088)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !116, file: !115, line: 227, baseType: !31, size: 64, align: 64, offset: 1152)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !116, file: !115, line: 228, baseType: !31, size: 64, align: 64, offset: 1216)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !116, file: !115, line: 229, baseType: !31, size: 64, align: 64, offset: 1280)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !116, file: !115, line: 230, baseType: !31, size: 64, align: 64, offset: 1344)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !116, file: !115, line: 231, baseType: !31, size: 64, align: 64, offset: 1408)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !116, file: !115, line: 232, baseType: !143, size: 32, align: 32, offset: 1472)
!143 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !144)
!144 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !145)
!145 = !{!146}
!146 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !116, file: !115, line: 233, baseType: !143, size: 32, align: 32, offset: 1504)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !116, file: !115, line: 234, baseType: !143, size: 32, align: 32, offset: 1536)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !116, file: !115, line: 235, baseType: !143, size: 32, align: 32, offset: 1568)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool1", scope: !116, file: !115, line: 236, baseType: !151, size: 8, align: 8, offset: 1600)
!151 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !4, line: 29, baseType: !64)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool2", scope: !116, file: !115, line: 237, baseType: !151, size: 8, align: 8, offset: 1608)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool3", scope: !116, file: !115, line: 238, baseType: !151, size: 8, align: 8, offset: 1616)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool4", scope: !116, file: !115, line: 239, baseType: !151, size: 8, align: 8, offset: 1624)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool5", scope: !116, file: !115, line: 240, baseType: !151, size: 8, align: 8, offset: 1632)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool6", scope: !116, file: !115, line: 241, baseType: !151, size: 8, align: 8, offset: 1640)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool7", scope: !116, file: !115, line: 242, baseType: !151, size: 8, align: 8, offset: 1648)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool8", scope: !116, file: !115, line: 243, baseType: !151, size: 8, align: 8, offset: 1656)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_size", scope: !19, file: !1, line: 33, baseType: !31, size: 64, align: 64, offset: 640)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !19, file: !1, line: 36, baseType: !31, size: 64, align: 64, offset: 704)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_limit", scope: !19, file: !1, line: 41, baseType: !31, size: 64, align: 64, offset: 768)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "check_pos", scope: !19, file: !1, line: 44, baseType: !53, size: 64, align: 64, offset: 832)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !19, file: !1, line: 47, baseType: !164, size: 832, align: 64, offset: 896)
!164 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check_state", file: !165, line: 56, baseType: !166)
!165 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/check/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!166 = !DICompositeType(tag: DW_TAG_structure_type, file: !165, line: 34, size: 832, align: 64, elements: !167)
!167 = !{!168, !180}
!168 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !166, file: !165, line: 40, baseType: !169, size: 512, align: 64)
!169 = !DICompositeType(tag: DW_TAG_union_type, scope: !166, file: !165, line: 36, size: 512, align: 64, elements: !170)
!170 = !{!171, !172, !176}
!171 = !DIDerivedType(tag: DW_TAG_member, name: "u8", scope: !169, file: !165, line: 37, baseType: !128, size: 512, align: 8)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "u32", scope: !169, file: !165, line: 38, baseType: !173, size: 512, align: 32)
!173 = !DICompositeType(tag: DW_TAG_array_type, baseType: !119, size: 512, align: 32, elements: !174)
!174 = !{!175}
!175 = !DISubrange(count: 16)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "u64", scope: !169, file: !165, line: 39, baseType: !177, size: 512, align: 64)
!177 = !DICompositeType(tag: DW_TAG_array_type, baseType: !33, size: 512, align: 64, elements: !178)
!178 = !{!179}
!179 = !DISubrange(count: 8)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !166, file: !165, line: 54, baseType: !181, size: 320, align: 64, offset: 512)
!181 = !DICompositeType(tag: DW_TAG_union_type, scope: !166, file: !165, line: 43, size: 320, align: 64, elements: !182)
!182 = !{!183, !184, !185}
!183 = !DIDerivedType(tag: DW_TAG_member, name: "crc32", scope: !181, file: !165, line: 44, baseType: !119, size: 32, align: 32)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "crc64", scope: !181, file: !165, line: 45, baseType: !33, size: 64, align: 64)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "sha256", scope: !181, file: !165, line: 53, baseType: !186, size: 320, align: 64)
!186 = !DICompositeType(tag: DW_TAG_structure_type, scope: !181, file: !165, line: 47, size: 320, align: 64, elements: !187)
!187 = !{!188, !190}
!188 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !186, file: !165, line: 49, baseType: !189, size: 256, align: 32)
!189 = !DICompositeType(tag: DW_TAG_array_type, baseType: !119, size: 256, align: 32, elements: !178)
!190 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !186, file: !165, line: 52, baseType: !33, size: 64, align: 64, offset: 256)
!191 = !{!192, !193, !194}
!192 = !DIEnumerator(name: "SEQ_CODE", value: 0)
!193 = !DIEnumerator(name: "SEQ_PADDING", value: 1)
!194 = !DIEnumerator(name: "SEQ_CHECK", value: 2)
!195 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !196, file: !24, line: 182, size: 32, align: 32, elements: !207)
!196 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_internal_s", file: !24, line: 174, size: 704, align: 64, elements: !197)
!197 = !{!198, !199, !200, !201, !206}
!198 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !196, file: !24, line: 176, baseType: !23, size: 512, align: 64)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !196, file: !24, line: 189, baseType: !195, size: 32, align: 32, offset: 512)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !196, file: !24, line: 194, baseType: !53, size: 64, align: 64, offset: 576)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "supported_actions", scope: !196, file: !24, line: 197, baseType: !202, size: 32, align: 8, offset: 640)
!202 = !DICompositeType(tag: DW_TAG_array_type, baseType: !203, size: 32, align: 8, elements: !204)
!203 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!204 = !{!205}
!205 = !DISubrange(count: 4)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "allow_buf_error", scope: !196, file: !24, line: 201, baseType: !203, size: 8, align: 8, offset: 672)
!207 = !{!208, !209, !210, !211, !212, !213}
!208 = !DIEnumerator(name: "ISEQ_RUN", value: 0)
!209 = !DIEnumerator(name: "ISEQ_SYNC_FLUSH", value: 1)
!210 = !DIEnumerator(name: "ISEQ_FULL_FLUSH", value: 2)
!211 = !DIEnumerator(name: "ISEQ_FINISH", value: 3)
!212 = !DIEnumerator(name: "ISEQ_END", value: 4)
!213 = !DIEnumerator(name: "ISEQ_ERROR", value: 5)
!214 = !{!37, !52}
!215 = !{!216, !221, !248, !249, !253, !256}
!216 = distinct !DISubprogram(name: "lzma_block_decoder_init", scope: !1, file: !1, line: 182, type: !217, isLocal: false, isDefinition: true, scopeLine: 184, flags: DIFlagPrototyped, isOptimized: false, variables: !220)
!217 = !DISubroutineType(types: !218)
!218 = !{!43, !219, !44, !113}
!219 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!220 = !{}
!221 = distinct !DISubprogram(name: "lzma_block_decoder", scope: !1, file: !1, line: 234, type: !222, isLocal: false, isDefinition: true, scopeLine: 235, flags: DIFlagPrototyped, isOptimized: false, variables: !220)
!222 = !DISubroutineType(types: !223)
!223 = !{!43, !224, !113}
!224 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !225, size: 64, align: 64)
!225 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream", file: !4, line: 490, baseType: !226)
!226 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 453, size: 1088, align: 64, elements: !227)
!227 = !{!228, !229, !230, !231, !232, !233, !234, !235, !238, !239, !240, !241, !242, !243, !244, !245, !246, !247}
!228 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !226, file: !4, line: 454, baseType: !61, size: 64, align: 64)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !226, file: !4, line: 455, baseType: !53, size: 64, align: 64, offset: 64)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !226, file: !4, line: 456, baseType: !33, size: 64, align: 64, offset: 128)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !226, file: !4, line: 458, baseType: !68, size: 64, align: 64, offset: 192)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !226, file: !4, line: 459, baseType: !53, size: 64, align: 64, offset: 256)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !226, file: !4, line: 460, baseType: !33, size: 64, align: 64, offset: 320)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "allocator", scope: !226, file: !4, line: 468, baseType: !44, size: 64, align: 64, offset: 384)
!235 = !DIDerivedType(tag: DW_TAG_member, name: "internal", scope: !226, file: !4, line: 471, baseType: !236, size: 64, align: 64, offset: 448)
!236 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !237, size: 64, align: 64)
!237 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_internal", file: !4, line: 411, baseType: !196)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !226, file: !4, line: 479, baseType: !52, size: 64, align: 64, offset: 512)
!239 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !226, file: !4, line: 480, baseType: !52, size: 64, align: 64, offset: 576)
!240 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !226, file: !4, line: 481, baseType: !52, size: 64, align: 64, offset: 640)
!241 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr4", scope: !226, file: !4, line: 482, baseType: !52, size: 64, align: 64, offset: 704)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !226, file: !4, line: 483, baseType: !33, size: 64, align: 64, offset: 768)
!243 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !226, file: !4, line: 484, baseType: !33, size: 64, align: 64, offset: 832)
!244 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !226, file: !4, line: 485, baseType: !53, size: 64, align: 64, offset: 896)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !226, file: !4, line: 486, baseType: !53, size: 64, align: 64, offset: 960)
!246 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !226, file: !4, line: 487, baseType: !143, size: 32, align: 32, offset: 1024)
!247 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !226, file: !4, line: 488, baseType: !143, size: 32, align: 32, offset: 1056)
!248 = distinct !DISubprogram(name: "block_decode", scope: !1, file: !1, line: 74, type: !41, isLocal: true, isDefinition: true, scopeLine: 78, flags: DIFlagPrototyped, isOptimized: false, variables: !220)
!249 = distinct !DISubprogram(name: "update_size", scope: !1, file: !1, line: 52, type: !250, isLocal: true, isDefinition: true, scopeLine: 53, flags: DIFlagPrototyped, isOptimized: false, variables: !220)
!250 = !DISubroutineType(types: !251)
!251 = !{!203, !252, !31, !31}
!252 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!253 = distinct !DISubprogram(name: "is_size_valid", scope: !1, file: !1, line: 67, type: !254, isLocal: true, isDefinition: true, scopeLine: 68, flags: DIFlagPrototyped, isOptimized: false, variables: !220)
!254 = !DISubroutineType(types: !255)
!255 = !{!203, !31, !31}
!256 = distinct !DISubprogram(name: "block_decoder_end", scope: !1, file: !1, line: 173, type: !79, isLocal: true, isDefinition: true, scopeLine: 174, flags: DIFlagPrototyped, isOptimized: false, variables: !220)
!257 = !{!258}
!258 = !DIGlobalVariable(name: "LZMA_NEXT_CODER_INIT", scope: !0, file: !24, line: 159, type: !259, isLocal: true, isDefinition: true, variable: %struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT)
!259 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !23)
!260 = !{i32 2, !"Dwarf Version", i32 4}
!261 = !{i32 2, !"Debug Info Version", i32 3}
!262 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!263 = !DILocalVariable(name: "next", arg: 1, scope: !216, file: !1, line: 182, type: !219)
!264 = !DIExpression()
!265 = !DILocation(line: 182, column: 42, scope: !216)
!266 = !DILocalVariable(name: "allocator", arg: 2, scope: !216, file: !1, line: 182, type: !44)
!267 = !DILocation(line: 182, column: 64, scope: !216)
!268 = !DILocalVariable(name: "block", arg: 3, scope: !216, file: !1, line: 183, type: !113)
!269 = !DILocation(line: 183, column: 15, scope: !216)
!270 = !DILocation(line: 185, column: 2, scope: !216)
!271 = !DILocation(line: 185, column: 2, scope: !272)
!272 = !DILexicalBlockFile(scope: !273, file: !1, discriminator: 1)
!273 = distinct !DILexicalBlock(scope: !274, file: !1, line: 185, column: 2)
!274 = distinct !DILexicalBlock(scope: !216, file: !1, line: 185, column: 2)
!275 = !DILocation(line: 185, column: 2, scope: !276)
!276 = !DILexicalBlockFile(scope: !273, file: !1, discriminator: 2)
!277 = !DILocation(line: 185, column: 2, scope: !278)
!278 = !DILexicalBlockFile(scope: !274, file: !1, discriminator: 3)
!279 = !DILocation(line: 190, column: 31, scope: !280)
!280 = distinct !DILexicalBlock(scope: !216, file: !1, line: 190, column: 6)
!281 = !DILocation(line: 190, column: 6, scope: !280)
!282 = !DILocation(line: 190, column: 38, scope: !280)
!283 = !DILocation(line: 191, column: 4, scope: !280)
!284 = !DILocation(line: 191, column: 8, scope: !285)
!285 = !DILexicalBlockFile(scope: !280, file: !1, discriminator: 1)
!286 = !DILocation(line: 191, column: 8, scope: !287)
!287 = !DILexicalBlockFile(scope: !280, file: !1, discriminator: 2)
!288 = !DILocation(line: 190, column: 6, scope: !289)
!289 = !DILexicalBlockFile(scope: !216, file: !1, discriminator: 1)
!290 = !DILocation(line: 192, column: 3, scope: !280)
!291 = !DILocation(line: 195, column: 6, scope: !292)
!292 = distinct !DILexicalBlock(scope: !216, file: !1, line: 195, column: 6)
!293 = !DILocation(line: 195, column: 12, scope: !292)
!294 = !DILocation(line: 195, column: 18, scope: !292)
!295 = !DILocation(line: 195, column: 6, scope: !216)
!296 = !DILocation(line: 196, column: 48, scope: !297)
!297 = distinct !DILexicalBlock(scope: !292, file: !1, line: 195, column: 27)
!298 = !DILocation(line: 196, column: 17, scope: !297)
!299 = !DILocation(line: 196, column: 3, scope: !297)
!300 = !DILocation(line: 196, column: 9, scope: !297)
!301 = !DILocation(line: 196, column: 15, scope: !297)
!302 = !DILocation(line: 197, column: 7, scope: !303)
!303 = distinct !DILexicalBlock(scope: !297, file: !1, line: 197, column: 7)
!304 = !DILocation(line: 197, column: 13, scope: !303)
!305 = !DILocation(line: 197, column: 19, scope: !303)
!306 = !DILocation(line: 197, column: 7, scope: !297)
!307 = !DILocation(line: 198, column: 4, scope: !303)
!308 = !DILocation(line: 200, column: 3, scope: !297)
!309 = !DILocation(line: 200, column: 9, scope: !297)
!310 = !DILocation(line: 200, column: 14, scope: !297)
!311 = !DILocation(line: 201, column: 3, scope: !297)
!312 = !DILocation(line: 201, column: 9, scope: !297)
!313 = !DILocation(line: 201, column: 13, scope: !297)
!314 = !DILocation(line: 202, column: 3, scope: !297)
!315 = !DILocation(line: 202, column: 9, scope: !297)
!316 = !DILocation(line: 202, column: 16, scope: !297)
!317 = !DILocation(line: 202, column: 23, scope: !297)
!318 = !DILocation(line: 203, column: 2, scope: !297)
!319 = !DILocation(line: 206, column: 2, scope: !216)
!320 = !DILocation(line: 206, column: 8, scope: !216)
!321 = !DILocation(line: 206, column: 15, scope: !216)
!322 = !DILocation(line: 206, column: 24, scope: !216)
!323 = !DILocation(line: 207, column: 23, scope: !216)
!324 = !DILocation(line: 207, column: 2, scope: !216)
!325 = !DILocation(line: 207, column: 8, scope: !216)
!326 = !DILocation(line: 207, column: 15, scope: !216)
!327 = !DILocation(line: 207, column: 21, scope: !216)
!328 = !DILocation(line: 208, column: 2, scope: !216)
!329 = !DILocation(line: 208, column: 8, scope: !216)
!330 = !DILocation(line: 208, column: 15, scope: !216)
!331 = !DILocation(line: 208, column: 31, scope: !216)
!332 = !DILocation(line: 209, column: 2, scope: !216)
!333 = !DILocation(line: 209, column: 8, scope: !216)
!334 = !DILocation(line: 209, column: 15, scope: !216)
!335 = !DILocation(line: 209, column: 33, scope: !216)
!336 = !DILocation(line: 215, column: 6, scope: !216)
!337 = !DILocation(line: 215, column: 13, scope: !216)
!338 = !DILocation(line: 215, column: 29, scope: !216)
!339 = !DILocation(line: 217, column: 8, scope: !216)
!340 = !DILocation(line: 217, column: 15, scope: !216)
!341 = !DILocation(line: 217, column: 6, scope: !216)
!342 = !DILocation(line: 218, column: 24, scope: !216)
!343 = !DILocation(line: 218, column: 31, scope: !216)
!344 = !DILocation(line: 218, column: 8, scope: !216)
!345 = !DILocation(line: 218, column: 6, scope: !216)
!346 = !DILocation(line: 215, column: 6, scope: !289)
!347 = !DILocation(line: 219, column: 7, scope: !216)
!348 = !DILocation(line: 219, column: 14, scope: !216)
!349 = !DILocation(line: 215, column: 6, scope: !350)
!350 = !DILexicalBlockFile(scope: !216, file: !1, discriminator: 2)
!351 = !DILocation(line: 215, column: 6, scope: !352)
!352 = !DILexicalBlockFile(scope: !216, file: !1, discriminator: 3)
!353 = !DILocation(line: 214, column: 2, scope: !216)
!354 = !DILocation(line: 214, column: 8, scope: !216)
!355 = !DILocation(line: 214, column: 15, scope: !216)
!356 = !DILocation(line: 215, column: 4, scope: !352)
!357 = !DILocation(line: 224, column: 2, scope: !216)
!358 = !DILocation(line: 224, column: 8, scope: !216)
!359 = !DILocation(line: 224, column: 15, scope: !216)
!360 = !DILocation(line: 224, column: 25, scope: !216)
!361 = !DILocation(line: 225, column: 19, scope: !216)
!362 = !DILocation(line: 225, column: 25, scope: !216)
!363 = !DILocation(line: 225, column: 32, scope: !216)
!364 = !DILocation(line: 225, column: 39, scope: !216)
!365 = !DILocation(line: 225, column: 46, scope: !216)
!366 = !DILocation(line: 225, column: 2, scope: !216)
!367 = !DILocation(line: 228, column: 32, scope: !216)
!368 = !DILocation(line: 228, column: 38, scope: !216)
!369 = !DILocation(line: 228, column: 45, scope: !216)
!370 = !DILocation(line: 228, column: 51, scope: !216)
!371 = !DILocation(line: 229, column: 4, scope: !216)
!372 = !DILocation(line: 229, column: 11, scope: !216)
!373 = !DILocation(line: 228, column: 9, scope: !216)
!374 = !DILocation(line: 228, column: 2, scope: !216)
!375 = !DILocation(line: 230, column: 1, scope: !216)
!376 = !DILocalVariable(name: "coder", arg: 1, scope: !248, file: !1, line: 74, type: !28)
!377 = !DILocation(line: 74, column: 26, scope: !248)
!378 = !DILocalVariable(name: "allocator", arg: 2, scope: !248, file: !1, line: 74, type: !44)
!379 = !DILocation(line: 74, column: 49, scope: !248)
!380 = !DILocalVariable(name: "in", arg: 3, scope: !248, file: !1, line: 75, type: !60)
!381 = !DILocation(line: 75, column: 32, scope: !248)
!382 = !DILocalVariable(name: "in_pos", arg: 4, scope: !248, file: !1, line: 75, type: !65)
!383 = !DILocation(line: 75, column: 58, scope: !248)
!384 = !DILocalVariable(name: "in_size", arg: 5, scope: !248, file: !1, line: 76, type: !53)
!385 = !DILocation(line: 76, column: 10, scope: !248)
!386 = !DILocalVariable(name: "out", arg: 6, scope: !248, file: !1, line: 76, type: !67)
!387 = !DILocation(line: 76, column: 42, scope: !248)
!388 = !DILocalVariable(name: "out_pos", arg: 7, scope: !248, file: !1, line: 77, type: !65)
!389 = !DILocation(line: 77, column: 25, scope: !248)
!390 = !DILocalVariable(name: "out_size", arg: 8, scope: !248, file: !1, line: 77, type: !53)
!391 = !DILocation(line: 77, column: 41, scope: !248)
!392 = !DILocalVariable(name: "action", arg: 9, scope: !248, file: !1, line: 77, type: !69)
!393 = !DILocation(line: 77, column: 63, scope: !248)
!394 = !DILocation(line: 79, column: 10, scope: !248)
!395 = !DILocation(line: 79, column: 17, scope: !248)
!396 = !DILocation(line: 79, column: 2, scope: !248)
!397 = !DILocalVariable(name: "in_start", scope: !398, file: !1, line: 81, type: !400)
!398 = distinct !DILexicalBlock(scope: !399, file: !1, line: 80, column: 17)
!399 = distinct !DILexicalBlock(scope: !248, file: !1, line: 79, column: 27)
!400 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !53)
!401 = !DILocation(line: 81, column: 16, scope: !398)
!402 = !DILocation(line: 81, column: 28, scope: !398)
!403 = !DILocation(line: 81, column: 27, scope: !398)
!404 = !DILocalVariable(name: "out_start", scope: !398, file: !1, line: 82, type: !400)
!405 = !DILocation(line: 82, column: 16, scope: !398)
!406 = !DILocation(line: 82, column: 29, scope: !398)
!407 = !DILocation(line: 82, column: 28, scope: !398)
!408 = !DILocalVariable(name: "ret", scope: !398, file: !1, line: 84, type: !409)
!409 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !43)
!410 = !DILocation(line: 84, column: 18, scope: !398)
!411 = !DILocation(line: 84, column: 24, scope: !398)
!412 = !DILocation(line: 84, column: 31, scope: !398)
!413 = !DILocation(line: 84, column: 36, scope: !398)
!414 = !DILocation(line: 84, column: 41, scope: !398)
!415 = !DILocation(line: 84, column: 48, scope: !398)
!416 = !DILocation(line: 84, column: 53, scope: !398)
!417 = !DILocation(line: 85, column: 5, scope: !398)
!418 = !DILocation(line: 85, column: 16, scope: !398)
!419 = !DILocation(line: 85, column: 20, scope: !398)
!420 = !DILocation(line: 85, column: 28, scope: !398)
!421 = !DILocation(line: 86, column: 5, scope: !398)
!422 = !DILocation(line: 86, column: 10, scope: !398)
!423 = !DILocation(line: 86, column: 19, scope: !398)
!424 = !DILocation(line: 86, column: 29, scope: !398)
!425 = !DILocalVariable(name: "in_used", scope: !398, file: !1, line: 88, type: !400)
!426 = !DILocation(line: 88, column: 16, scope: !398)
!427 = !DILocation(line: 88, column: 27, scope: !398)
!428 = !DILocation(line: 88, column: 26, scope: !398)
!429 = !DILocation(line: 88, column: 36, scope: !398)
!430 = !DILocation(line: 88, column: 34, scope: !398)
!431 = !DILocalVariable(name: "out_used", scope: !398, file: !1, line: 89, type: !400)
!432 = !DILocation(line: 89, column: 16, scope: !398)
!433 = !DILocation(line: 89, column: 28, scope: !398)
!434 = !DILocation(line: 89, column: 27, scope: !398)
!435 = !DILocation(line: 89, column: 38, scope: !398)
!436 = !DILocation(line: 89, column: 36, scope: !398)
!437 = !DILocation(line: 93, column: 20, scope: !438)
!438 = distinct !DILexicalBlock(scope: !398, file: !1, line: 93, column: 7)
!439 = !DILocation(line: 93, column: 27, scope: !438)
!440 = !DILocation(line: 93, column: 44, scope: !438)
!441 = !DILocation(line: 94, column: 6, scope: !438)
!442 = !DILocation(line: 94, column: 13, scope: !438)
!443 = !DILocation(line: 93, column: 7, scope: !438)
!444 = !DILocation(line: 95, column: 5, scope: !438)
!445 = !DILocation(line: 95, column: 21, scope: !446)
!446 = !DILexicalBlockFile(scope: !438, file: !1, discriminator: 1)
!447 = !DILocation(line: 95, column: 28, scope: !446)
!448 = !DILocation(line: 96, column: 6, scope: !438)
!449 = !DILocation(line: 97, column: 6, scope: !438)
!450 = !DILocation(line: 97, column: 13, scope: !438)
!451 = !DILocation(line: 97, column: 20, scope: !438)
!452 = !DILocation(line: 95, column: 8, scope: !446)
!453 = !DILocation(line: 93, column: 7, scope: !454)
!454 = !DILexicalBlockFile(scope: !398, file: !1, discriminator: 1)
!455 = !DILocation(line: 98, column: 4, scope: !438)
!456 = !DILocation(line: 100, column: 22, scope: !398)
!457 = !DILocation(line: 100, column: 29, scope: !398)
!458 = !DILocation(line: 100, column: 36, scope: !398)
!459 = !DILocation(line: 100, column: 43, scope: !398)
!460 = !DILocation(line: 100, column: 50, scope: !398)
!461 = !DILocation(line: 101, column: 5, scope: !398)
!462 = !DILocation(line: 101, column: 11, scope: !398)
!463 = !DILocation(line: 101, column: 9, scope: !398)
!464 = !DILocation(line: 101, column: 22, scope: !398)
!465 = !DILocation(line: 100, column: 3, scope: !398)
!466 = !DILocation(line: 103, column: 7, scope: !467)
!467 = distinct !DILexicalBlock(scope: !398, file: !1, line: 103, column: 7)
!468 = !DILocation(line: 103, column: 11, scope: !467)
!469 = !DILocation(line: 103, column: 7, scope: !398)
!470 = !DILocation(line: 104, column: 11, scope: !467)
!471 = !DILocation(line: 104, column: 4, scope: !467)
!472 = !DILocation(line: 108, column: 22, scope: !473)
!473 = distinct !DILexicalBlock(scope: !398, file: !1, line: 108, column: 7)
!474 = !DILocation(line: 108, column: 29, scope: !473)
!475 = !DILocation(line: 109, column: 6, scope: !473)
!476 = !DILocation(line: 109, column: 13, scope: !473)
!477 = !DILocation(line: 109, column: 20, scope: !473)
!478 = !DILocation(line: 108, column: 8, scope: !473)
!479 = !DILocation(line: 110, column: 5, scope: !473)
!480 = !DILocation(line: 110, column: 23, scope: !481)
!481 = !DILexicalBlockFile(scope: !473, file: !1, discriminator: 1)
!482 = !DILocation(line: 110, column: 30, scope: !481)
!483 = !DILocation(line: 111, column: 6, scope: !473)
!484 = !DILocation(line: 111, column: 13, scope: !473)
!485 = !DILocation(line: 111, column: 20, scope: !473)
!486 = !DILocation(line: 110, column: 9, scope: !481)
!487 = !DILocation(line: 108, column: 7, scope: !454)
!488 = !DILocation(line: 112, column: 4, scope: !473)
!489 = !DILocation(line: 116, column: 35, scope: !398)
!490 = !DILocation(line: 116, column: 42, scope: !398)
!491 = !DILocation(line: 116, column: 3, scope: !398)
!492 = !DILocation(line: 116, column: 10, scope: !398)
!493 = !DILocation(line: 116, column: 17, scope: !398)
!494 = !DILocation(line: 116, column: 33, scope: !398)
!495 = !DILocation(line: 117, column: 37, scope: !398)
!496 = !DILocation(line: 117, column: 44, scope: !398)
!497 = !DILocation(line: 117, column: 3, scope: !398)
!498 = !DILocation(line: 117, column: 10, scope: !398)
!499 = !DILocation(line: 117, column: 17, scope: !398)
!500 = !DILocation(line: 117, column: 35, scope: !398)
!501 = !DILocation(line: 119, column: 3, scope: !398)
!502 = !DILocation(line: 119, column: 10, scope: !398)
!503 = !DILocation(line: 119, column: 19, scope: !398)
!504 = !DILocation(line: 120, column: 2, scope: !398)
!505 = !DILocation(line: 126, column: 3, scope: !399)
!506 = !DILocation(line: 126, column: 10, scope: !507)
!507 = !DILexicalBlockFile(scope: !399, file: !1, discriminator: 1)
!508 = !DILocation(line: 126, column: 17, scope: !507)
!509 = !DILocation(line: 126, column: 33, scope: !507)
!510 = !DILocation(line: 126, column: 3, scope: !507)
!511 = !DILocation(line: 127, column: 9, scope: !512)
!512 = distinct !DILexicalBlock(scope: !513, file: !1, line: 127, column: 8)
!513 = distinct !DILexicalBlock(scope: !399, file: !1, line: 126, column: 38)
!514 = !DILocation(line: 127, column: 8, scope: !512)
!515 = !DILocation(line: 127, column: 19, scope: !512)
!516 = !DILocation(line: 127, column: 16, scope: !512)
!517 = !DILocation(line: 127, column: 8, scope: !513)
!518 = !DILocation(line: 128, column: 5, scope: !512)
!519 = !DILocation(line: 134, column: 6, scope: !513)
!520 = !DILocation(line: 134, column: 13, scope: !513)
!521 = !DILocation(line: 134, column: 4, scope: !513)
!522 = !DILocation(line: 136, column: 13, scope: !523)
!523 = distinct !DILexicalBlock(scope: !513, file: !1, line: 136, column: 8)
!524 = !DILocation(line: 136, column: 20, scope: !523)
!525 = !DILocation(line: 136, column: 8, scope: !523)
!526 = !DILocation(line: 136, column: 24, scope: !523)
!527 = !DILocation(line: 136, column: 8, scope: !513)
!528 = !DILocation(line: 137, column: 5, scope: !523)
!529 = !DILocation(line: 126, column: 3, scope: !530)
!530 = !DILexicalBlockFile(scope: !399, file: !1, discriminator: 2)
!531 = !DILocation(line: 140, column: 7, scope: !532)
!532 = distinct !DILexicalBlock(scope: !399, file: !1, line: 140, column: 7)
!533 = !DILocation(line: 140, column: 14, scope: !532)
!534 = !DILocation(line: 140, column: 21, scope: !532)
!535 = !DILocation(line: 140, column: 27, scope: !532)
!536 = !DILocation(line: 140, column: 7, scope: !399)
!537 = !DILocation(line: 141, column: 4, scope: !532)
!538 = !DILocation(line: 143, column: 22, scope: !399)
!539 = !DILocation(line: 143, column: 29, scope: !399)
!540 = !DILocation(line: 143, column: 36, scope: !399)
!541 = !DILocation(line: 143, column: 43, scope: !399)
!542 = !DILocation(line: 143, column: 50, scope: !399)
!543 = !DILocation(line: 143, column: 3, scope: !399)
!544 = !DILocation(line: 144, column: 3, scope: !399)
!545 = !DILocation(line: 144, column: 10, scope: !399)
!546 = !DILocation(line: 144, column: 19, scope: !399)
!547 = !DILocalVariable(name: "check_size", scope: !548, file: !1, line: 149, type: !400)
!548 = distinct !DILexicalBlock(scope: !399, file: !1, line: 148, column: 18)
!549 = !DILocation(line: 149, column: 16, scope: !548)
!550 = !DILocation(line: 149, column: 45, scope: !548)
!551 = !DILocation(line: 149, column: 52, scope: !548)
!552 = !DILocation(line: 149, column: 59, scope: !548)
!553 = !DILocation(line: 149, column: 29, scope: !548)
!554 = !DILocation(line: 150, column: 15, scope: !548)
!555 = !DILocation(line: 150, column: 19, scope: !548)
!556 = !DILocation(line: 150, column: 27, scope: !548)
!557 = !DILocation(line: 150, column: 36, scope: !548)
!558 = !DILocation(line: 150, column: 43, scope: !548)
!559 = !DILocation(line: 150, column: 50, scope: !548)
!560 = !DILocation(line: 151, column: 6, scope: !548)
!561 = !DILocation(line: 151, column: 13, scope: !548)
!562 = !DILocation(line: 151, column: 24, scope: !548)
!563 = !DILocation(line: 150, column: 3, scope: !548)
!564 = !DILocation(line: 152, column: 7, scope: !565)
!565 = distinct !DILexicalBlock(scope: !548, file: !1, line: 152, column: 7)
!566 = !DILocation(line: 152, column: 14, scope: !565)
!567 = !DILocation(line: 152, column: 26, scope: !565)
!568 = !DILocation(line: 152, column: 24, scope: !565)
!569 = !DILocation(line: 152, column: 7, scope: !548)
!570 = !DILocation(line: 153, column: 4, scope: !565)
!571 = !DILocation(line: 158, column: 31, scope: !572)
!572 = distinct !DILexicalBlock(scope: !548, file: !1, line: 158, column: 7)
!573 = !DILocation(line: 158, column: 38, scope: !572)
!574 = !DILocation(line: 158, column: 45, scope: !572)
!575 = !DILocation(line: 158, column: 7, scope: !572)
!576 = !DILocation(line: 159, column: 5, scope: !572)
!577 = !DILocation(line: 159, column: 15, scope: !578)
!578 = !DILexicalBlockFile(scope: !572, file: !1, discriminator: 1)
!579 = !DILocation(line: 159, column: 22, scope: !578)
!580 = !DILocation(line: 159, column: 29, scope: !578)
!581 = !DILocation(line: 160, column: 6, scope: !572)
!582 = !DILocation(line: 160, column: 13, scope: !572)
!583 = !DILocation(line: 160, column: 19, scope: !572)
!584 = !DILocation(line: 160, column: 26, scope: !572)
!585 = !DILocation(line: 161, column: 6, scope: !572)
!586 = !DILocation(line: 159, column: 8, scope: !578)
!587 = !DILocation(line: 161, column: 18, scope: !572)
!588 = !DILocation(line: 158, column: 7, scope: !589)
!589 = !DILexicalBlockFile(scope: !548, file: !1, discriminator: 1)
!590 = !DILocation(line: 162, column: 4, scope: !572)
!591 = !DILocation(line: 164, column: 3, scope: !548)
!592 = !DILocation(line: 168, column: 2, scope: !248)
!593 = !DILocation(line: 169, column: 1, scope: !248)
!594 = !DILocalVariable(name: "coder", arg: 1, scope: !256, file: !1, line: 173, type: !28)
!595 = !DILocation(line: 173, column: 31, scope: !256)
!596 = !DILocalVariable(name: "allocator", arg: 2, scope: !256, file: !1, line: 173, type: !44)
!597 = !DILocation(line: 173, column: 54, scope: !256)
!598 = !DILocation(line: 175, column: 17, scope: !256)
!599 = !DILocation(line: 175, column: 24, scope: !256)
!600 = !DILocation(line: 175, column: 30, scope: !256)
!601 = !DILocation(line: 175, column: 2, scope: !256)
!602 = !DILocation(line: 176, column: 12, scope: !256)
!603 = !DILocation(line: 176, column: 19, scope: !256)
!604 = !DILocation(line: 176, column: 2, scope: !256)
!605 = !DILocation(line: 177, column: 2, scope: !256)
!606 = !DILocalVariable(name: "strm", arg: 1, scope: !221, file: !1, line: 234, type: !224)
!607 = !DILocation(line: 234, column: 33, scope: !221)
!608 = !DILocalVariable(name: "block", arg: 2, scope: !221, file: !1, line: 234, type: !113)
!609 = !DILocation(line: 234, column: 51, scope: !221)
!610 = !DILocation(line: 236, column: 2, scope: !221)
!611 = !DILocalVariable(name: "ret_", scope: !612, file: !1, line: 236, type: !43)
!612 = distinct !DILexicalBlock(scope: !221, file: !1, line: 236, column: 2)
!613 = !DILocation(line: 236, column: 2, scope: !612)
!614 = !DILocation(line: 236, column: 2, scope: !615)
!615 = !DILexicalBlockFile(scope: !612, file: !1, discriminator: 1)
!616 = !DILocalVariable(name: "ret_", scope: !617, file: !1, line: 236, type: !409)
!617 = distinct !DILexicalBlock(scope: !612, file: !1, line: 236, column: 2)
!618 = !DILocation(line: 236, column: 2, scope: !617)
!619 = !DILocation(line: 236, column: 2, scope: !620)
!620 = !DILexicalBlockFile(scope: !617, file: !1, discriminator: 2)
!621 = !DILocation(line: 236, column: 2, scope: !622)
!622 = !DILexicalBlockFile(scope: !623, file: !1, discriminator: 3)
!623 = distinct !DILexicalBlock(scope: !617, file: !1, line: 236, column: 2)
!624 = !DILocation(line: 236, column: 2, scope: !625)
!625 = !DILexicalBlockFile(scope: !617, file: !1, discriminator: 4)
!626 = !DILocation(line: 236, column: 2, scope: !627)
!627 = !DILexicalBlockFile(scope: !612, file: !1, discriminator: 5)
!628 = !DILocation(line: 236, column: 2, scope: !629)
!629 = !DILexicalBlockFile(scope: !630, file: !1, discriminator: 6)
!630 = distinct !DILexicalBlock(scope: !631, file: !1, line: 236, column: 2)
!631 = distinct !DILexicalBlock(scope: !612, file: !1, line: 236, column: 2)
!632 = !DILocation(line: 236, column: 2, scope: !633)
!633 = !DILexicalBlockFile(scope: !612, file: !1, discriminator: 7)
!634 = !DILocation(line: 238, column: 2, scope: !221)
!635 = !DILocation(line: 238, column: 8, scope: !221)
!636 = !DILocation(line: 238, column: 18, scope: !221)
!637 = !DILocation(line: 238, column: 46, scope: !221)
!638 = !DILocation(line: 239, column: 2, scope: !221)
!639 = !DILocation(line: 239, column: 8, scope: !221)
!640 = !DILocation(line: 239, column: 18, scope: !221)
!641 = !DILocation(line: 239, column: 49, scope: !221)
!642 = !DILocation(line: 241, column: 2, scope: !221)
!643 = !DILocation(line: 242, column: 1, scope: !221)
!644 = !DILocalVariable(name: "size", arg: 1, scope: !249, file: !1, line: 52, type: !252)
!645 = !DILocation(line: 52, column: 23, scope: !249)
!646 = !DILocalVariable(name: "add", arg: 2, scope: !249, file: !1, line: 52, type: !31)
!647 = !DILocation(line: 52, column: 38, scope: !249)
!648 = !DILocalVariable(name: "limit", arg: 3, scope: !249, file: !1, line: 52, type: !31)
!649 = !DILocation(line: 52, column: 52, scope: !249)
!650 = !DILocation(line: 54, column: 6, scope: !651)
!651 = distinct !DILexicalBlock(scope: !249, file: !1, line: 54, column: 6)
!652 = !DILocation(line: 54, column: 12, scope: !651)
!653 = !DILocation(line: 54, column: 6, scope: !249)
!654 = !DILocation(line: 55, column: 9, scope: !651)
!655 = !DILocation(line: 55, column: 3, scope: !651)
!656 = !DILocation(line: 57, column: 6, scope: !657)
!657 = distinct !DILexicalBlock(scope: !249, file: !1, line: 57, column: 6)
!658 = !DILocation(line: 57, column: 15, scope: !657)
!659 = !DILocation(line: 57, column: 14, scope: !657)
!660 = !DILocation(line: 57, column: 12, scope: !657)
!661 = !DILocation(line: 57, column: 20, scope: !657)
!662 = !DILocation(line: 57, column: 23, scope: !663)
!663 = !DILexicalBlockFile(scope: !657, file: !1, discriminator: 1)
!664 = !DILocation(line: 57, column: 32, scope: !663)
!665 = !DILocation(line: 57, column: 31, scope: !663)
!666 = !DILocation(line: 57, column: 29, scope: !663)
!667 = !DILocation(line: 57, column: 39, scope: !663)
!668 = !DILocation(line: 57, column: 37, scope: !663)
!669 = !DILocation(line: 57, column: 6, scope: !663)
!670 = !DILocation(line: 58, column: 3, scope: !657)
!671 = !DILocation(line: 60, column: 11, scope: !249)
!672 = !DILocation(line: 60, column: 3, scope: !249)
!673 = !DILocation(line: 60, column: 8, scope: !249)
!674 = !DILocation(line: 62, column: 2, scope: !249)
!675 = !DILocation(line: 63, column: 1, scope: !249)
!676 = !DILocalVariable(name: "size", arg: 1, scope: !253, file: !1, line: 67, type: !31)
!677 = !DILocation(line: 67, column: 24, scope: !253)
!678 = !DILocalVariable(name: "reference", arg: 2, scope: !253, file: !1, line: 67, type: !31)
!679 = !DILocation(line: 67, column: 39, scope: !253)
!680 = !DILocation(line: 69, column: 9, scope: !253)
!681 = !DILocation(line: 69, column: 19, scope: !253)
!682 = !DILocation(line: 69, column: 39, scope: !253)
!683 = !DILocation(line: 69, column: 42, scope: !684)
!684 = !DILexicalBlockFile(scope: !253, file: !1, discriminator: 1)
!685 = !DILocation(line: 69, column: 55, scope: !684)
!686 = !DILocation(line: 69, column: 52, scope: !684)
!687 = !DILocation(line: 69, column: 39, scope: !684)
!688 = !DILocation(line: 69, column: 2, scope: !689)
!689 = !DILexicalBlockFile(scope: !253, file: !1, discriminator: 2)
