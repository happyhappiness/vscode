; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/index_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type { i32, %struct.lzma_index_s*, %struct.lzma_index_iter, i64, i32 }
%struct.lzma_index_iter = type { %struct.anon, %struct.anon.0, [6 x %union.anon] }
%struct.anon = type { %struct.lzma_stream_flags*, i8*, i8*, i8*, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64 }
%struct.lzma_stream_flags = type { i32, i64, i32, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8, i8, i8, i32, i32 }
%struct.anon.0 = type { i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i8*, i8*, i8*, i8* }
%union.anon = type { i8* }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_index_s = type opaque
%struct.lzma_stream = type { i8*, i64, i64, i8*, i64, i64, %struct.lzma_allocator*, %struct.lzma_internal_s*, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i32, i32 }
%struct.lzma_internal_s = type { %struct.lzma_next_coder_s, i32, i64, [4 x i8], i8 }

@.str = private unnamed_addr constant [2 x i8] c"0\00", align 1
@.str.1 = private unnamed_addr constant [85 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/index_encoder.c\00", align 1
@__PRETTY_FUNCTION__.lzma_index_buffer_encode = private unnamed_addr constant [83 x i8] c"lzma_ret lzma_index_buffer_encode(const lzma_index *, uint8_t *, size_t *, size_t)\00", align 1
@.str.2 = private unnamed_addr constant [16 x i8] c"coder->pos <= 3\00", align 1
@__PRETTY_FUNCTION__.index_encode = private unnamed_addr constant [163 x i8] c"lzma_ret index_encode(lzma_coder *, lzma_allocator *, const uint8_t *restrict, size_t *restrict, size_t, uint8_t *restrict, size_t *restrict, size_t, lzma_action)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_index_encoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_index_s* %i) #0 !dbg !237 {
entry:
  %retval = alloca i32, align 4
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %i.addr = alloca %struct.lzma_index_s*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !280, metadata !281), !dbg !282
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !283, metadata !281), !dbg !284
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !285, metadata !281), !dbg !286
  br label %do.body, !dbg !287

do.body:                                          ; preds = %entry
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !288
  %init = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %0, i32 0, i32 2, !dbg !288
  %1 = load i64, i64* %init, align 8, !dbg !288
  %cmp = icmp ne i64 ptrtoint (i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_index_s*)* @lzma_index_encoder_init to i64), %1, !dbg !288
  br i1 %cmp, label %if.then, label %if.end, !dbg !288

if.then:                                          ; preds = %do.body
  %2 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !292
  %3 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !292
  call void @lzma_next_end(%struct.lzma_next_coder_s* %2, %struct.lzma_allocator* %3), !dbg !292
  br label %if.end, !dbg !292

if.end:                                           ; preds = %if.then, %do.body
  %4 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !294
  %init1 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %4, i32 0, i32 2, !dbg !294
  store i64 ptrtoint (i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_index_s*)* @lzma_index_encoder_init to i64), i64* %init1, align 8, !dbg !294
  br label %do.end, !dbg !294

do.end:                                           ; preds = %if.end
  %5 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !296
  %cmp2 = icmp eq %struct.lzma_index_s* %5, null, !dbg !298
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !299

if.then3:                                         ; preds = %do.end
  store i32 11, i32* %retval, align 4, !dbg !300
  br label %return, !dbg !300

if.end4:                                          ; preds = %do.end
  %6 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !301
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %6, i32 0, i32 0, !dbg !303
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !303
  %cmp5 = icmp eq %struct.lzma_coder_s* %7, null, !dbg !304
  br i1 %cmp5, label %if.then6, label %if.end12, !dbg !305

if.then6:                                         ; preds = %if.end4
  %8 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !306
  %call = call noalias i8* @lzma_alloc(i64 336, %struct.lzma_allocator* %8), !dbg !308
  %9 = bitcast i8* %call to %struct.lzma_coder_s*, !dbg !308
  %10 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !309
  %coder7 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %10, i32 0, i32 0, !dbg !310
  store %struct.lzma_coder_s* %9, %struct.lzma_coder_s** %coder7, align 8, !dbg !311
  %11 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !312
  %coder8 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %11, i32 0, i32 0, !dbg !314
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder8, align 8, !dbg !314
  %cmp9 = icmp eq %struct.lzma_coder_s* %12, null, !dbg !315
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !316

if.then10:                                        ; preds = %if.then6
  store i32 5, i32* %retval, align 4, !dbg !317
  br label %return, !dbg !317

if.end11:                                         ; preds = %if.then6
  %13 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !318
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %13, i32 0, i32 3, !dbg !319
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* @index_encode, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !320
  %14 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !321
  %end = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %14, i32 0, i32 4, !dbg !322
  store void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* @index_encoder_end, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !323
  br label %if.end12, !dbg !324

if.end12:                                         ; preds = %if.end11, %if.end4
  %15 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !325
  %coder13 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %15, i32 0, i32 0, !dbg !326
  %16 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder13, align 8, !dbg !326
  %17 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !327
  call void @index_encoder_reset(%struct.lzma_coder_s* %16, %struct.lzma_index_s* %17), !dbg !328
  store i32 0, i32* %retval, align 4, !dbg !329
  br label %return, !dbg !329

return:                                           ; preds = %if.end12, %if.then10, %if.then3
  %18 = load i32, i32* %retval, align 4, !dbg !330
  ret i32 %18, !dbg !330
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @lzma_next_end(%struct.lzma_next_coder_s*, %struct.lzma_allocator*) #2

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #2

; Function Attrs: nounwind uwtable
define internal i32 @index_encode(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, i8* noalias %in, i64* noalias %in_pos, i64 %in_size, i8* noalias %out, i64* noalias %out_pos, i64 %out_size, i32 %action) #0 !dbg !272 {
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
  %out_start = alloca i64, align 8
  %ret = alloca i32, align 4
  %count = alloca i64, align 8
  %size = alloca i64, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !331, metadata !281), !dbg !332
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !333, metadata !281), !dbg !334
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !335, metadata !281), !dbg !336
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !337, metadata !281), !dbg !338
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !339, metadata !281), !dbg !340
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !341, metadata !281), !dbg !342
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !343, metadata !281), !dbg !344
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !345, metadata !281), !dbg !346
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !347, metadata !281), !dbg !348
  call void @llvm.dbg.declare(metadata i64* %out_start, metadata !349, metadata !281), !dbg !351
  %0 = load i64*, i64** %out_pos.addr, align 8, !dbg !352
  %1 = load i64, i64* %0, align 8, !dbg !353
  store i64 %1, i64* %out_start, align 8, !dbg !351
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !354, metadata !281), !dbg !355
  store i32 0, i32* %ret, align 4, !dbg !355
  br label %while.cond, !dbg !356

while.cond:                                       ; preds = %sw.epilog, %entry
  %2 = load i64*, i64** %out_pos.addr, align 8, !dbg !357
  %3 = load i64, i64* %2, align 8, !dbg !359
  %4 = load i64, i64* %out_size.addr, align 8, !dbg !360
  %cmp = icmp ult i64 %3, %4, !dbg !361
  br i1 %cmp, label %while.body, label %while.end, !dbg !362

while.body:                                       ; preds = %while.cond
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !363
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 0, !dbg !364
  %6 = load i32, i32* %sequence, align 8, !dbg !364
  switch i32 %6, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb2
    i32 4, label %sw.bb7
    i32 2, label %sw.bb19
    i32 3, label %sw.bb19
    i32 5, label %sw.bb38
    i32 6, label %sw.bb50
  ], !dbg !365

sw.bb:                                            ; preds = %while.body
  %7 = load i64*, i64** %out_pos.addr, align 8, !dbg !366
  %8 = load i64, i64* %7, align 8, !dbg !368
  %9 = load i8*, i8** %out.addr, align 8, !dbg !369
  %arrayidx = getelementptr inbounds i8, i8* %9, i64 %8, !dbg !369
  store i8 0, i8* %arrayidx, align 1, !dbg !370
  %10 = load i64*, i64** %out_pos.addr, align 8, !dbg !371
  %11 = load i64, i64* %10, align 8, !dbg !372
  %inc = add i64 %11, 1, !dbg !372
  store i64 %inc, i64* %10, align 8, !dbg !372
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !373
  %sequence1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 0, !dbg !374
  store i32 1, i32* %sequence1, align 8, !dbg !375
  br label %sw.epilog, !dbg !376

sw.bb2:                                           ; preds = %while.body
  call void @llvm.dbg.declare(metadata i64* %count, metadata !377, metadata !281), !dbg !380
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !381
  %index = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %13, i32 0, i32 1, !dbg !382
  %14 = load %struct.lzma_index_s*, %struct.lzma_index_s** %index, align 8, !dbg !382
  %call = call i64 @lzma_index_block_count(%struct.lzma_index_s* %14) #6, !dbg !383
  store i64 %call, i64* %count, align 8, !dbg !380
  %15 = load i64, i64* %count, align 8, !dbg !384
  %16 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !385
  %pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %16, i32 0, i32 3, !dbg !386
  %17 = load i8*, i8** %out.addr, align 8, !dbg !387
  %18 = load i64*, i64** %out_pos.addr, align 8, !dbg !388
  %19 = load i64, i64* %out_size.addr, align 8, !dbg !389
  %call3 = call i32 @lzma_vli_encode(i64 %15, i64* %pos, i8* %17, i64* %18, i64 %19) #7, !dbg !390
  store i32 %call3, i32* %ret, align 4, !dbg !391
  %20 = load i32, i32* %ret, align 4, !dbg !392
  %cmp4 = icmp ne i32 %20, 1, !dbg !394
  br i1 %cmp4, label %if.then, label %if.end, !dbg !395

if.then:                                          ; preds = %sw.bb2
  br label %out64, !dbg !396

if.end:                                           ; preds = %sw.bb2
  store i32 0, i32* %ret, align 4, !dbg !397
  %21 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !398
  %pos5 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %21, i32 0, i32 3, !dbg !399
  store i64 0, i64* %pos5, align 8, !dbg !400
  %22 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !401
  %sequence6 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %22, i32 0, i32 0, !dbg !402
  store i32 4, i32* %sequence6, align 8, !dbg !403
  br label %sw.epilog, !dbg !404

sw.bb7:                                           ; preds = %while.body
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !405
  %iter = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 2, !dbg !407
  %call8 = call zeroext i8 @lzma_index_iter_next(%struct.lzma_index_iter* %iter, i32 2) #7, !dbg !408
  %tobool = icmp ne i8 %call8, 0, !dbg !408
  br i1 %tobool, label %if.then9, label %if.end17, !dbg !409

if.then9:                                         ; preds = %sw.bb7
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !410
  %index10 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %24, i32 0, i32 1, !dbg !412
  %25 = load %struct.lzma_index_s*, %struct.lzma_index_s** %index10, align 8, !dbg !412
  %call11 = call i32 @lzma_index_padding_size(%struct.lzma_index_s* %25), !dbg !413
  %conv = zext i32 %call11 to i64, !dbg !413
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !414
  %pos12 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %26, i32 0, i32 3, !dbg !415
  store i64 %conv, i64* %pos12, align 8, !dbg !416
  %27 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !417
  %pos13 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %27, i32 0, i32 3, !dbg !417
  %28 = load i64, i64* %pos13, align 8, !dbg !417
  %cmp14 = icmp ule i64 %28, 3, !dbg !417
  br i1 %cmp14, label %cond.true, label %cond.false, !dbg !417

cond.true:                                        ; preds = %if.then9
  br label %cond.end, !dbg !418

cond.false:                                       ; preds = %if.then9
  call void @__assert_fail(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([85 x i8], [85 x i8]* @.str.1, i32 0, i32 0), i32 89, i8* getelementptr inbounds ([163 x i8], [163 x i8]* @__PRETTY_FUNCTION__.index_encode, i32 0, i32 0)) #8, !dbg !420
  unreachable, !dbg !420
                                                  ; No predecessors!
  br label %cond.end, !dbg !422

cond.end:                                         ; preds = %29, %cond.true
  %30 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !424
  %sequence16 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %30, i32 0, i32 0, !dbg !425
  store i32 5, i32* %sequence16, align 8, !dbg !426
  br label %sw.epilog, !dbg !427

if.end17:                                         ; preds = %sw.bb7
  %31 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !428
  %sequence18 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %31, i32 0, i32 0, !dbg !429
  store i32 2, i32* %sequence18, align 8, !dbg !430
  br label %sw.bb19, !dbg !428

sw.bb19:                                          ; preds = %while.body, %while.body, %if.end17
  call void @llvm.dbg.declare(metadata i64* %size, metadata !431, metadata !281), !dbg !433
  %32 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !434
  %sequence20 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %32, i32 0, i32 0, !dbg !435
  %33 = load i32, i32* %sequence20, align 8, !dbg !435
  %cmp21 = icmp eq i32 %33, 2, !dbg !436
  br i1 %cmp21, label %cond.true23, label %cond.false25, !dbg !434

cond.true23:                                      ; preds = %sw.bb19
  %34 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !437
  %iter24 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %34, i32 0, i32 2, !dbg !438
  %block = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %iter24, i32 0, i32 1, !dbg !439
  %unpadded_size = getelementptr inbounds %struct.anon.0, %struct.anon.0* %block, i32 0, i32 7, !dbg !440
  %35 = load i64, i64* %unpadded_size, align 8, !dbg !440
  br label %cond.end28, !dbg !441

cond.false25:                                     ; preds = %sw.bb19
  %36 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !443
  %iter26 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %36, i32 0, i32 2, !dbg !444
  %block27 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %iter26, i32 0, i32 1, !dbg !445
  %uncompressed_size = getelementptr inbounds %struct.anon.0, %struct.anon.0* %block27, i32 0, i32 6, !dbg !446
  %37 = load i64, i64* %uncompressed_size, align 8, !dbg !446
  br label %cond.end28, !dbg !447

cond.end28:                                       ; preds = %cond.false25, %cond.true23
  %cond = phi i64 [ %35, %cond.true23 ], [ %37, %cond.false25 ], !dbg !449
  store i64 %cond, i64* %size, align 8, !dbg !451
  %38 = load i64, i64* %size, align 8, !dbg !452
  %39 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !453
  %pos29 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %39, i32 0, i32 3, !dbg !454
  %40 = load i8*, i8** %out.addr, align 8, !dbg !455
  %41 = load i64*, i64** %out_pos.addr, align 8, !dbg !456
  %42 = load i64, i64* %out_size.addr, align 8, !dbg !457
  %call30 = call i32 @lzma_vli_encode(i64 %38, i64* %pos29, i8* %40, i64* %41, i64 %42) #7, !dbg !458
  store i32 %call30, i32* %ret, align 4, !dbg !459
  %43 = load i32, i32* %ret, align 4, !dbg !460
  %cmp31 = icmp ne i32 %43, 1, !dbg !462
  br i1 %cmp31, label %if.then33, label %if.end34, !dbg !463

if.then33:                                        ; preds = %cond.end28
  br label %out64, !dbg !464

if.end34:                                         ; preds = %cond.end28
  store i32 0, i32* %ret, align 4, !dbg !465
  %44 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !466
  %pos35 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %44, i32 0, i32 3, !dbg !467
  store i64 0, i64* %pos35, align 8, !dbg !468
  %45 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !469
  %sequence36 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %45, i32 0, i32 0, !dbg !470
  %46 = load i32, i32* %sequence36, align 8, !dbg !471
  %inc37 = add i32 %46, 1, !dbg !471
  store i32 %inc37, i32* %sequence36, align 8, !dbg !471
  br label %sw.epilog, !dbg !472

sw.bb38:                                          ; preds = %while.body
  %47 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !473
  %pos39 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %47, i32 0, i32 3, !dbg !475
  %48 = load i64, i64* %pos39, align 8, !dbg !475
  %cmp40 = icmp ugt i64 %48, 0, !dbg !476
  br i1 %cmp40, label %if.then42, label %if.end46, !dbg !477

if.then42:                                        ; preds = %sw.bb38
  %49 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !478
  %pos43 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %49, i32 0, i32 3, !dbg !480
  %50 = load i64, i64* %pos43, align 8, !dbg !481
  %dec = add i64 %50, -1, !dbg !481
  store i64 %dec, i64* %pos43, align 8, !dbg !481
  %51 = load i64*, i64** %out_pos.addr, align 8, !dbg !482
  %52 = load i64, i64* %51, align 8, !dbg !483
  %inc44 = add i64 %52, 1, !dbg !483
  store i64 %inc44, i64* %51, align 8, !dbg !483
  %53 = load i8*, i8** %out.addr, align 8, !dbg !484
  %arrayidx45 = getelementptr inbounds i8, i8* %53, i64 %52, !dbg !484
  store i8 0, i8* %arrayidx45, align 1, !dbg !485
  br label %sw.epilog, !dbg !486

if.end46:                                         ; preds = %sw.bb38
  %54 = load i8*, i8** %out.addr, align 8, !dbg !487
  %55 = load i64, i64* %out_start, align 8, !dbg !488
  %add.ptr = getelementptr inbounds i8, i8* %54, i64 %55, !dbg !489
  %56 = load i64*, i64** %out_pos.addr, align 8, !dbg !490
  %57 = load i64, i64* %56, align 8, !dbg !491
  %58 = load i64, i64* %out_start, align 8, !dbg !492
  %sub = sub i64 %57, %58, !dbg !493
  %59 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !494
  %crc32 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %59, i32 0, i32 4, !dbg !495
  %60 = load i32, i32* %crc32, align 8, !dbg !495
  %call47 = call i32 @lzma_crc32(i8* %add.ptr, i64 %sub, i32 %60) #6, !dbg !496
  %61 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !497
  %crc3248 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %61, i32 0, i32 4, !dbg !498
  store i32 %call47, i32* %crc3248, align 8, !dbg !499
  %62 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !500
  %sequence49 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %62, i32 0, i32 0, !dbg !501
  store i32 6, i32* %sequence49, align 8, !dbg !502
  br label %sw.bb50, !dbg !500

sw.bb50:                                          ; preds = %while.body, %if.end46
  br label %do.body, !dbg !503

do.body:                                          ; preds = %do.cond, %sw.bb50
  %63 = load i64*, i64** %out_pos.addr, align 8, !dbg !504
  %64 = load i64, i64* %63, align 8, !dbg !507
  %65 = load i64, i64* %out_size.addr, align 8, !dbg !508
  %cmp51 = icmp eq i64 %64, %65, !dbg !509
  br i1 %cmp51, label %if.then53, label %if.end54, !dbg !510

if.then53:                                        ; preds = %do.body
  store i32 0, i32* %retval, align 4, !dbg !511
  br label %return, !dbg !511

if.end54:                                         ; preds = %do.body
  %66 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !512
  %crc3255 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %66, i32 0, i32 4, !dbg !513
  %67 = load i32, i32* %crc3255, align 8, !dbg !513
  %68 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !514
  %pos56 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %68, i32 0, i32 3, !dbg !515
  %69 = load i64, i64* %pos56, align 8, !dbg !515
  %mul = mul i64 %69, 8, !dbg !516
  %sh_prom = trunc i64 %mul to i32, !dbg !517
  %shr = lshr i32 %67, %sh_prom, !dbg !517
  %and = and i32 %shr, 255, !dbg !518
  %conv57 = trunc i32 %and to i8, !dbg !519
  %70 = load i64*, i64** %out_pos.addr, align 8, !dbg !520
  %71 = load i64, i64* %70, align 8, !dbg !521
  %72 = load i8*, i8** %out.addr, align 8, !dbg !522
  %arrayidx58 = getelementptr inbounds i8, i8* %72, i64 %71, !dbg !522
  store i8 %conv57, i8* %arrayidx58, align 1, !dbg !523
  %73 = load i64*, i64** %out_pos.addr, align 8, !dbg !524
  %74 = load i64, i64* %73, align 8, !dbg !525
  %inc59 = add i64 %74, 1, !dbg !525
  store i64 %inc59, i64* %73, align 8, !dbg !525
  br label %do.cond, !dbg !526

do.cond:                                          ; preds = %if.end54
  %75 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !527
  %pos60 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %75, i32 0, i32 3, !dbg !529
  %76 = load i64, i64* %pos60, align 8, !dbg !530
  %inc61 = add i64 %76, 1, !dbg !530
  store i64 %inc61, i64* %pos60, align 8, !dbg !530
  %cmp62 = icmp ult i64 %inc61, 4, !dbg !531
  br i1 %cmp62, label %do.body, label %do.end, !dbg !532

do.end:                                           ; preds = %do.cond
  store i32 1, i32* %retval, align 4, !dbg !533
  br label %return, !dbg !533

sw.default:                                       ; preds = %while.body
  call void @__assert_fail(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([85 x i8], [85 x i8]* @.str.1, i32 0, i32 0), i32 148, i8* getelementptr inbounds ([163 x i8], [163 x i8]* @__PRETTY_FUNCTION__.index_encode, i32 0, i32 0)) #8, !dbg !534
  unreachable, !dbg !534

sw.epilog:                                        ; preds = %if.then42, %if.end34, %cond.end, %if.end, %sw.bb
  br label %while.cond, !dbg !535

while.end:                                        ; preds = %while.cond
  br label %out64, !dbg !537

out64:                                            ; preds = %while.end, %if.then33, %if.then
  %77 = load i8*, i8** %out.addr, align 8, !dbg !539
  %78 = load i64, i64* %out_start, align 8, !dbg !540
  %add.ptr65 = getelementptr inbounds i8, i8* %77, i64 %78, !dbg !541
  %79 = load i64*, i64** %out_pos.addr, align 8, !dbg !542
  %80 = load i64, i64* %79, align 8, !dbg !543
  %81 = load i64, i64* %out_start, align 8, !dbg !544
  %sub66 = sub i64 %80, %81, !dbg !545
  %82 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !546
  %crc3267 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %82, i32 0, i32 4, !dbg !547
  %83 = load i32, i32* %crc3267, align 8, !dbg !547
  %call68 = call i32 @lzma_crc32(i8* %add.ptr65, i64 %sub66, i32 %83) #6, !dbg !548
  %84 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !549
  %crc3269 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %84, i32 0, i32 4, !dbg !550
  store i32 %call68, i32* %crc3269, align 8, !dbg !551
  %85 = load i32, i32* %ret, align 4, !dbg !552
  store i32 %85, i32* %retval, align 4, !dbg !553
  br label %return, !dbg !553

return:                                           ; preds = %out64, %do.end, %if.then53
  %86 = load i32, i32* %retval, align 4, !dbg !554
  ret i32 %86, !dbg !554
}

; Function Attrs: nounwind uwtable
define internal void @index_encoder_end(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator) #0 !dbg !273 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !555, metadata !281), !dbg !556
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !557, metadata !281), !dbg !558
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !559
  %1 = bitcast %struct.lzma_coder_s* %0 to i8*, !dbg !559
  %2 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !560
  call void @lzma_free(i8* %1, %struct.lzma_allocator* %2), !dbg !561
  ret void, !dbg !562
}

; Function Attrs: nounwind uwtable
define internal void @index_encoder_reset(%struct.lzma_coder_s* %coder, %struct.lzma_index_s* %i) #0 !dbg !274 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %i.addr = alloca %struct.lzma_index_s*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !563, metadata !281), !dbg !564
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !565, metadata !281), !dbg !566
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !567
  %iter = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 2, !dbg !568
  %1 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !569
  call void @lzma_index_iter_init(%struct.lzma_index_iter* %iter, %struct.lzma_index_s* %1) #7, !dbg !570
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !571
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 0, !dbg !572
  store i32 0, i32* %sequence, align 8, !dbg !573
  %3 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !574
  %4 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !575
  %index = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %4, i32 0, i32 1, !dbg !576
  store %struct.lzma_index_s* %3, %struct.lzma_index_s** %index, align 8, !dbg !577
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !578
  %pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 3, !dbg !579
  store i64 0, i64* %pos, align 8, !dbg !580
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !581
  %crc32 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %6, i32 0, i32 4, !dbg !582
  store i32 0, i32* %crc32, align 8, !dbg !583
  ret void, !dbg !584
}

; Function Attrs: nounwind uwtable
define i32 @lzma_index_encoder(%struct.lzma_stream* %strm, %struct.lzma_index_s* %i) #0 !dbg !242 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzma_stream*, align 8
  %i.addr = alloca %struct.lzma_index_s*, align 8
  %ret_ = alloca i32, align 4
  %ret_2 = alloca i32, align 4
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !585, metadata !281), !dbg !586
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !587, metadata !281), !dbg !588
  br label %do.body, !dbg !589

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !590, metadata !281), !dbg !592
  br label %do.body1, !dbg !593

do.body1:                                         ; preds = %do.body
  call void @llvm.dbg.declare(metadata i32* %ret_2, metadata !595, metadata !281), !dbg !598
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !599
  %call = call i32 @lzma_strm_init(%struct.lzma_stream* %0), !dbg !599
  store i32 %call, i32* %ret_2, align 4, !dbg !599
  %1 = load i32, i32* %ret_2, align 4, !dbg !599
  %cmp = icmp ne i32 %1, 0, !dbg !599
  br i1 %cmp, label %if.then, label %if.end, !dbg !599

if.then:                                          ; preds = %do.body1
  %2 = load i32, i32* %ret_2, align 4, !dbg !601
  store i32 %2, i32* %retval, align 4, !dbg !601
  br label %return, !dbg !601

if.end:                                           ; preds = %do.body1
  br label %do.end, !dbg !604

do.end:                                           ; preds = %if.end
  %3 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !606
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %3, i32 0, i32 7, !dbg !606
  %4 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !606
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %4, i32 0, i32 0, !dbg !606
  %5 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !606
  %allocator = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %5, i32 0, i32 6, !dbg !606
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator, align 8, !dbg !606
  %7 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !606
  %call3 = call i32 @lzma_index_encoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %6, %struct.lzma_index_s* %7), !dbg !606
  store i32 %call3, i32* %ret_, align 4, !dbg !606
  %8 = load i32, i32* %ret_, align 4, !dbg !606
  %cmp4 = icmp ne i32 %8, 0, !dbg !606
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !606

if.then5:                                         ; preds = %do.end
  %9 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !608
  call void @lzma_end(%struct.lzma_stream* %9) #7, !dbg !608
  %10 = load i32, i32* %ret_, align 4, !dbg !608
  store i32 %10, i32* %retval, align 4, !dbg !608
  br label %return, !dbg !608

if.end6:                                          ; preds = %do.end
  br label %do.end7, !dbg !612

do.end7:                                          ; preds = %if.end6
  %11 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !614
  %internal8 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %11, i32 0, i32 7, !dbg !615
  %12 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal8, align 8, !dbg !615
  %supported_actions = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %12, i32 0, i32 3, !dbg !616
  %arrayidx = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions, i64 0, i64 0, !dbg !614
  store i8 1, i8* %arrayidx, align 8, !dbg !617
  %13 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !618
  %internal9 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %13, i32 0, i32 7, !dbg !619
  %14 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal9, align 8, !dbg !619
  %supported_actions10 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %14, i32 0, i32 3, !dbg !620
  %arrayidx11 = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions10, i64 0, i64 3, !dbg !618
  store i8 1, i8* %arrayidx11, align 1, !dbg !621
  store i32 0, i32* %retval, align 4, !dbg !622
  br label %return, !dbg !622

return:                                           ; preds = %do.end7, %if.then5, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !623
  ret i32 %15, !dbg !623
}

declare i32 @lzma_strm_init(%struct.lzma_stream*) #2

; Function Attrs: nounwind
declare void @lzma_end(%struct.lzma_stream*) #3

; Function Attrs: nounwind uwtable
define i32 @lzma_index_buffer_encode(%struct.lzma_index_s* %i, i8* %out, i64* %out_pos, i64 %out_size) #0 !dbg !269 {
entry:
  %retval = alloca i32, align 4
  %i.addr = alloca %struct.lzma_index_s*, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %coder = alloca %struct.lzma_coder_s, align 8
  %out_start = alloca i64, align 8
  %ret = alloca i32, align 4
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !624, metadata !281), !dbg !625
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !626, metadata !281), !dbg !627
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !628, metadata !281), !dbg !629
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !630, metadata !281), !dbg !631
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s* %coder, metadata !632, metadata !281), !dbg !633
  call void @llvm.dbg.declare(metadata i64* %out_start, metadata !634, metadata !281), !dbg !635
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !636, metadata !281), !dbg !637
  %0 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !638
  %cmp = icmp eq %struct.lzma_index_s* %0, null, !dbg !640
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !641

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8*, i8** %out.addr, align 8, !dbg !642
  %cmp1 = icmp eq i8* %1, null, !dbg !644
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !645

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %2 = load i64*, i64** %out_pos.addr, align 8, !dbg !646
  %cmp3 = icmp eq i64* %2, null, !dbg !648
  br i1 %cmp3, label %if.then, label %lor.lhs.false4, !dbg !649

lor.lhs.false4:                                   ; preds = %lor.lhs.false2
  %3 = load i64*, i64** %out_pos.addr, align 8, !dbg !650
  %4 = load i64, i64* %3, align 8, !dbg !652
  %5 = load i64, i64* %out_size.addr, align 8, !dbg !653
  %cmp5 = icmp ugt i64 %4, %5, !dbg !654
  br i1 %cmp5, label %if.then, label %if.end, !dbg !655

if.then:                                          ; preds = %lor.lhs.false4, %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 11, i32* %retval, align 4, !dbg !656
  br label %return, !dbg !656

if.end:                                           ; preds = %lor.lhs.false4
  %6 = load i64, i64* %out_size.addr, align 8, !dbg !657
  %7 = load i64*, i64** %out_pos.addr, align 8, !dbg !659
  %8 = load i64, i64* %7, align 8, !dbg !660
  %sub = sub i64 %6, %8, !dbg !661
  %9 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !662
  %call = call i64 @lzma_index_size(%struct.lzma_index_s* %9) #6, !dbg !663
  %cmp6 = icmp ult i64 %sub, %call, !dbg !664
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !665

if.then7:                                         ; preds = %if.end
  store i32 10, i32* %retval, align 4, !dbg !666
  br label %return, !dbg !666

if.end8:                                          ; preds = %if.end
  %10 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !667
  call void @index_encoder_reset(%struct.lzma_coder_s* %coder, %struct.lzma_index_s* %10), !dbg !668
  %11 = load i64*, i64** %out_pos.addr, align 8, !dbg !669
  %12 = load i64, i64* %11, align 8, !dbg !670
  store i64 %12, i64* %out_start, align 8, !dbg !671
  %13 = load i8*, i8** %out.addr, align 8, !dbg !672
  %14 = load i64*, i64** %out_pos.addr, align 8, !dbg !673
  %15 = load i64, i64* %out_size.addr, align 8, !dbg !674
  %call9 = call i32 @index_encode(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* null, i8* null, i64* null, i64 0, i8* %13, i64* %14, i64 %15, i32 0), !dbg !675
  store i32 %call9, i32* %ret, align 4, !dbg !676
  %16 = load i32, i32* %ret, align 4, !dbg !677
  %cmp10 = icmp eq i32 %16, 1, !dbg !679
  br i1 %cmp10, label %if.then11, label %if.else, !dbg !680

if.then11:                                        ; preds = %if.end8
  store i32 0, i32* %ret, align 4, !dbg !681
  br label %if.end12, !dbg !683

if.else:                                          ; preds = %if.end8
  call void @__assert_fail(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([85 x i8], [85 x i8]* @.str.1, i32 0, i32 0), i32 251, i8* getelementptr inbounds ([83 x i8], [83 x i8]* @__PRETTY_FUNCTION__.lzma_index_buffer_encode, i32 0, i32 0)) #8, !dbg !684
  unreachable, !dbg !684

if.end12:                                         ; preds = %if.then11
  %17 = load i32, i32* %ret, align 4, !dbg !686
  store i32 %17, i32* %retval, align 4, !dbg !687
  br label %return, !dbg !687

return:                                           ; preds = %if.end12, %if.then7, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !688
  ret i32 %18, !dbg !688
}

; Function Attrs: nounwind readonly
declare i64 @lzma_index_size(%struct.lzma_index_s*) #4

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #5

; Function Attrs: nounwind readonly
declare i64 @lzma_index_block_count(%struct.lzma_index_s*) #4

; Function Attrs: nounwind
declare i32 @lzma_vli_encode(i64, i64*, i8*, i64*, i64) #3

; Function Attrs: nounwind
declare zeroext i8 @lzma_index_iter_next(%struct.lzma_index_iter*, i32) #3

declare i32 @lzma_index_padding_size(%struct.lzma_index_s*) #2

; Function Attrs: nounwind readonly
declare i32 @lzma_crc32(i8*, i64, i32) #4

declare void @lzma_free(i8*, %struct.lzma_allocator*) #2

; Function Attrs: nounwind
declare void @lzma_index_iter_init(%struct.lzma_index_iter*, %struct.lzma_index_s*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly }
attributes #7 = { nounwind }
attributes #8 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!277, !278}
!llvm.ident = !{!279}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !235, subprograms: !236)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/index_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !54, !62, !137, !143, !229}
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
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !19, file: !1, line: 19, size: 32, align: 32, elements: !129)
!19 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !1, line: 18, size: 2688, align: 64, elements: !20)
!20 = !{!21, !22, !28, !127, !128}
!21 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !19, file: !1, line: 27, baseType: !18, size: 32, align: 32)
!22 = !DIDerivedType(tag: DW_TAG_member, name: "index", scope: !19, file: !1, line: 30, baseType: !23, size: 64, align: 64, offset: 64)
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64, align: 64)
!24 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !25)
!25 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_index", file: !26, line: 37, baseType: !27)
!26 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/index.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!27 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_index_s", file: !26, line: 37, flags: DIFlagFwdDecl)
!28 = !DIDerivedType(tag: DW_TAG_member, name: "iter", scope: !19, file: !1, line: 33, baseType: !29, size: 2432, align: 64, offset: 128)
!29 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_index_iter", file: !26, line: 220, baseType: !30)
!30 = !DICompositeType(tag: DW_TAG_structure_type, file: !26, line: 43, size: 2432, align: 64, elements: !31)
!31 = !{!32, !96, !116}
!32 = !DIDerivedType(tag: DW_TAG_member, name: "stream", scope: !30, file: !26, line: 114, baseType: !33, size: 960, align: 64)
!33 = !DICompositeType(tag: DW_TAG_structure_type, scope: !30, file: !26, line: 44, size: 960, align: 64, elements: !34)
!34 = !{!35, !80, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95}
!35 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !33, file: !26, line: 51, baseType: !36, size: 64, align: 64)
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64, align: 64)
!37 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !38)
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream_flags", file: !39, line: 105, baseType: !40)
!39 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/stream_flags.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!40 = !DICompositeType(tag: DW_TAG_structure_type, file: !39, line: 33, size: 448, align: 64, elements: !41)
!41 = !{!42, !46, !51, !60, !65, !66, !67, !68, !71, !72, !73, !74, !75, !76, !77, !78, !79}
!42 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !40, file: !39, line: 51, baseType: !43, size: 32, align: 32)
!43 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !44, line: 51, baseType: !45)
!44 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!45 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "backward_size", scope: !40, file: !39, line: 69, baseType: !47, size: 64, align: 64, offset: 64)
!47 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !48, line: 63, baseType: !49)
!48 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!49 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !44, line: 55, baseType: !50)
!50 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!51 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !40, file: !39, line: 79, baseType: !52, size: 32, align: 32, offset: 128)
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !53, line: 55, baseType: !54)
!53 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!54 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !53, line: 27, size: 32, align: 32, elements: !55)
!55 = !{!56, !57, !58, !59}
!56 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!57 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!58 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!59 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !40, file: !39, line: 90, baseType: !61, size: 32, align: 32, offset: 160)
!61 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !62)
!62 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !63)
!63 = !{!64}
!64 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !40, file: !39, line: 91, baseType: !61, size: 32, align: 32, offset: 192)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !40, file: !39, line: 92, baseType: !61, size: 32, align: 32, offset: 224)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !40, file: !39, line: 93, baseType: !61, size: 32, align: 32, offset: 256)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool1", scope: !40, file: !39, line: 94, baseType: !69, size: 8, align: 8, offset: 288)
!69 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !4, line: 29, baseType: !70)
!70 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool2", scope: !40, file: !39, line: 95, baseType: !69, size: 8, align: 8, offset: 296)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool3", scope: !40, file: !39, line: 96, baseType: !69, size: 8, align: 8, offset: 304)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool4", scope: !40, file: !39, line: 97, baseType: !69, size: 8, align: 8, offset: 312)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool5", scope: !40, file: !39, line: 98, baseType: !69, size: 8, align: 8, offset: 320)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool6", scope: !40, file: !39, line: 99, baseType: !69, size: 8, align: 8, offset: 328)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool7", scope: !40, file: !39, line: 100, baseType: !69, size: 8, align: 8, offset: 336)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool8", scope: !40, file: !39, line: 101, baseType: !69, size: 8, align: 8, offset: 344)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !40, file: !39, line: 102, baseType: !43, size: 32, align: 32, offset: 352)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !40, file: !39, line: 103, baseType: !43, size: 32, align: 32, offset: 384)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !33, file: !26, line: 53, baseType: !81, size: 64, align: 64, offset: 64)
!81 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!82 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !33, file: !26, line: 54, baseType: !81, size: 64, align: 64, offset: 128)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !33, file: !26, line: 55, baseType: !81, size: 64, align: 64, offset: 192)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "number", scope: !33, file: !26, line: 62, baseType: !47, size: 64, align: 64, offset: 256)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "block_count", scope: !33, file: !26, line: 70, baseType: !47, size: 64, align: 64, offset: 320)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_offset", scope: !33, file: !26, line: 78, baseType: !47, size: 64, align: 64, offset: 384)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_offset", scope: !33, file: !26, line: 86, baseType: !47, size: 64, align: 64, offset: 448)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_size", scope: !33, file: !26, line: 94, baseType: !47, size: 64, align: 64, offset: 512)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !33, file: !26, line: 99, baseType: !47, size: 64, align: 64, offset: 576)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "padding", scope: !33, file: !26, line: 108, baseType: !47, size: 64, align: 64, offset: 640)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_vli1", scope: !33, file: !26, line: 110, baseType: !47, size: 64, align: 64, offset: 704)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_vli2", scope: !33, file: !26, line: 111, baseType: !47, size: 64, align: 64, offset: 768)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_vli3", scope: !33, file: !26, line: 112, baseType: !47, size: 64, align: 64, offset: 832)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_vli4", scope: !33, file: !26, line: 113, baseType: !47, size: 64, align: 64, offset: 896)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "block", scope: !30, file: !26, line: 208, baseType: !97, size: 1088, align: 64, offset: 960)
!97 = !DICompositeType(tag: DW_TAG_structure_type, scope: !30, file: !26, line: 116, size: 1088, align: 64, elements: !98)
!98 = !{!99, !100, !101, !102, !103, !104, !105, !106, !107, !108, !109, !110, !111, !112, !113, !114, !115}
!99 = !DIDerivedType(tag: DW_TAG_member, name: "number_in_file", scope: !97, file: !26, line: 122, baseType: !47, size: 64, align: 64)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_file_offset", scope: !97, file: !26, line: 132, baseType: !47, size: 64, align: 64, offset: 64)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_file_offset", scope: !97, file: !26, line: 147, baseType: !47, size: 64, align: 64, offset: 128)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "number_in_stream", scope: !97, file: !26, line: 154, baseType: !47, size: 64, align: 64, offset: 192)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_stream_offset", scope: !97, file: !26, line: 162, baseType: !47, size: 64, align: 64, offset: 256)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_stream_offset", scope: !97, file: !26, line: 170, baseType: !47, size: 64, align: 64, offset: 320)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !97, file: !26, line: 179, baseType: !47, size: 64, align: 64, offset: 384)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "unpadded_size", scope: !97, file: !26, line: 188, baseType: !47, size: 64, align: 64, offset: 448)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "total_size", scope: !97, file: !26, line: 197, baseType: !47, size: 64, align: 64, offset: 512)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_vli1", scope: !97, file: !26, line: 199, baseType: !47, size: 64, align: 64, offset: 576)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_vli2", scope: !97, file: !26, line: 200, baseType: !47, size: 64, align: 64, offset: 640)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_vli3", scope: !97, file: !26, line: 201, baseType: !47, size: 64, align: 64, offset: 704)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_vli4", scope: !97, file: !26, line: 202, baseType: !47, size: 64, align: 64, offset: 768)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !97, file: !26, line: 204, baseType: !81, size: 64, align: 64, offset: 832)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !97, file: !26, line: 205, baseType: !81, size: 64, align: 64, offset: 896)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !97, file: !26, line: 206, baseType: !81, size: 64, align: 64, offset: 960)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr4", scope: !97, file: !26, line: 207, baseType: !81, size: 64, align: 64, offset: 1024)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "internal", scope: !30, file: !26, line: 219, baseType: !117, size: 384, align: 64, offset: 2048)
!117 = !DICompositeType(tag: DW_TAG_array_type, baseType: !118, size: 384, align: 64, elements: !125)
!118 = !DICompositeType(tag: DW_TAG_union_type, scope: !30, file: !26, line: 215, size: 64, align: 64, elements: !119)
!119 = !{!120, !121, !124}
!120 = !DIDerivedType(tag: DW_TAG_member, name: "p", scope: !118, file: !26, line: 216, baseType: !81, size: 64, align: 64)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !118, file: !26, line: 217, baseType: !122, size: 64, align: 64)
!122 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !123, line: 62, baseType: !50)
!123 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!124 = !DIDerivedType(tag: DW_TAG_member, name: "v", scope: !118, file: !26, line: 218, baseType: !47, size: 64, align: 64)
!125 = !{!126}
!126 = !DISubrange(count: 6)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "pos", scope: !19, file: !1, line: 36, baseType: !122, size: 64, align: 64, offset: 2560)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "crc32", scope: !19, file: !1, line: 39, baseType: !43, size: 32, align: 32, offset: 2624)
!129 = !{!130, !131, !132, !133, !134, !135, !136}
!130 = !DIEnumerator(name: "SEQ_INDICATOR", value: 0)
!131 = !DIEnumerator(name: "SEQ_COUNT", value: 1)
!132 = !DIEnumerator(name: "SEQ_UNPADDED", value: 2)
!133 = !DIEnumerator(name: "SEQ_UNCOMPRESSED", value: 3)
!134 = !DIEnumerator(name: "SEQ_NEXT", value: 4)
!135 = !DIEnumerator(name: "SEQ_PADDING", value: 5)
!136 = !DIEnumerator(name: "SEQ_CRC32", value: 6)
!137 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !138)
!138 = !{!139, !140, !141, !142}
!139 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!140 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!141 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!142 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!143 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !145, file: !144, line: 182, size: 32, align: 32, elements: !222)
!144 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!145 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_internal_s", file: !144, line: 174, size: 704, align: 64, elements: !146)
!146 = !{!147, !214, !215, !216, !221}
!147 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !145, file: !144, line: 176, baseType: !148, size: 512, align: 64)
!148 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !144, line: 75, baseType: !149)
!149 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !144, line: 119, size: 512, align: 64, elements: !150)
!150 = !{!151, !154, !155, !157, !186, !191, !197, !202}
!151 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !149, file: !144, line: 121, baseType: !152, size: 64, align: 64)
!152 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !153, size: 64, align: 64)
!153 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !144, line: 73, baseType: !19)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !149, file: !144, line: 125, baseType: !47, size: 64, align: 64, offset: 64)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !149, file: !144, line: 131, baseType: !156, size: 64, align: 64, offset: 128)
!156 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !44, line: 122, baseType: !50)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !149, file: !144, line: 134, baseType: !158, size: 64, align: 64, offset: 192)
!158 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !144, line: 89, baseType: !159)
!159 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !160, size: 64, align: 64)
!160 = !DISubroutineType(types: !161)
!161 = !{!162, !152, !163, !177, !181, !122, !183, !181, !122, !185}
!162 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!163 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !164, size: 64, align: 64)
!164 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !165)
!165 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !166)
!166 = !{!167, !172, !176}
!167 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !165, file: !4, line: 376, baseType: !168, size: 64, align: 64)
!168 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !169, size: 64, align: 64)
!169 = !DISubroutineType(types: !170)
!170 = !{!171, !171, !122, !122}
!171 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !165, file: !4, line: 390, baseType: !173, size: 64, align: 64, offset: 64)
!173 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !174, size: 64, align: 64)
!174 = !DISubroutineType(types: !175)
!175 = !{null, !171, !171}
!176 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !165, file: !4, line: 401, baseType: !171, size: 64, align: 64, offset: 128)
!177 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !178)
!178 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !179, size: 64, align: 64)
!179 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !180)
!180 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !44, line: 48, baseType: !70)
!181 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !182)
!182 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !122, size: 64, align: 64)
!183 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !184)
!184 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !180, size: 64, align: 64)
!185 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !137)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !149, file: !144, line: 139, baseType: !187, size: 64, align: 64, offset: 256)
!187 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !144, line: 97, baseType: !188)
!188 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !189, size: 64, align: 64)
!189 = !DISubroutineType(types: !190)
!190 = !{null, !152, !163}
!191 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !149, file: !144, line: 143, baseType: !192, size: 64, align: 64, offset: 320)
!192 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !193, size: 64, align: 64)
!193 = !DISubroutineType(types: !194)
!194 = !{!52, !195}
!195 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !196, size: 64, align: 64)
!196 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !153)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !149, file: !144, line: 147, baseType: !198, size: 64, align: 64, offset: 384)
!198 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !199, size: 64, align: 64)
!199 = !DISubroutineType(types: !200)
!200 = !{!162, !152, !201, !201, !49}
!201 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64, align: 64)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !149, file: !144, line: 152, baseType: !203, size: 64, align: 64, offset: 448)
!203 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !204, size: 64, align: 64)
!204 = !DISubroutineType(types: !205)
!205 = !{!162, !152, !163, !206, !206}
!206 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !207, size: 64, align: 64)
!207 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !208)
!208 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !209, line: 65, baseType: !210)
!209 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!210 = !DICompositeType(tag: DW_TAG_structure_type, file: !209, line: 43, size: 128, align: 64, elements: !211)
!211 = !{!212, !213}
!212 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !210, file: !209, line: 54, baseType: !47, size: 64, align: 64)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !210, file: !209, line: 63, baseType: !171, size: 64, align: 64, offset: 64)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !145, file: !144, line: 189, baseType: !143, size: 32, align: 32, offset: 512)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !145, file: !144, line: 194, baseType: !122, size: 64, align: 64, offset: 576)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "supported_actions", scope: !145, file: !144, line: 197, baseType: !217, size: 32, align: 8, offset: 640)
!217 = !DICompositeType(tag: DW_TAG_array_type, baseType: !218, size: 32, align: 8, elements: !219)
!218 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!219 = !{!220}
!220 = !DISubrange(count: 4)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "allow_buf_error", scope: !145, file: !144, line: 201, baseType: !218, size: 8, align: 8, offset: 672)
!222 = !{!223, !224, !225, !226, !227, !228}
!223 = !DIEnumerator(name: "ISEQ_RUN", value: 0)
!224 = !DIEnumerator(name: "ISEQ_SYNC_FLUSH", value: 1)
!225 = !DIEnumerator(name: "ISEQ_FULL_FLUSH", value: 2)
!226 = !DIEnumerator(name: "ISEQ_FINISH", value: 3)
!227 = !DIEnumerator(name: "ISEQ_END", value: 4)
!228 = !DIEnumerator(name: "ISEQ_ERROR", value: 5)
!229 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !26, line: 226, size: 32, align: 32, elements: !230)
!230 = !{!231, !232, !233, !234}
!231 = !DIEnumerator(name: "LZMA_INDEX_ITER_ANY", value: 0)
!232 = !DIEnumerator(name: "LZMA_INDEX_ITER_STREAM", value: 1)
!233 = !DIEnumerator(name: "LZMA_INDEX_ITER_BLOCK", value: 2)
!234 = !DIEnumerator(name: "LZMA_INDEX_ITER_NONEMPTY_BLOCK", value: 3)
!235 = !{!156, !171}
!236 = !{!237, !242, !269, !272, !273, !274}
!237 = distinct !DISubprogram(name: "lzma_index_encoder_init", scope: !1, file: !1, line: 184, type: !238, isLocal: false, isDefinition: true, scopeLine: 186, flags: DIFlagPrototyped, isOptimized: false, variables: !241)
!238 = !DISubroutineType(types: !239)
!239 = !{!162, !240, !163, !23}
!240 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !148, size: 64, align: 64)
!241 = !{}
!242 = distinct !DISubprogram(name: "lzma_index_encoder", scope: !1, file: !1, line: 208, type: !243, isLocal: false, isDefinition: true, scopeLine: 209, flags: DIFlagPrototyped, isOptimized: false, variables: !241)
!243 = !DISubroutineType(types: !244)
!244 = !{!162, !245, !23}
!245 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !246, size: 64, align: 64)
!246 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream", file: !4, line: 490, baseType: !247)
!247 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 453, size: 1088, align: 64, elements: !248)
!248 = !{!249, !250, !251, !252, !253, !254, !255, !256, !259, !260, !261, !262, !263, !264, !265, !266, !267, !268}
!249 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !247, file: !4, line: 454, baseType: !178, size: 64, align: 64)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !247, file: !4, line: 455, baseType: !122, size: 64, align: 64, offset: 64)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !247, file: !4, line: 456, baseType: !49, size: 64, align: 64, offset: 128)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !247, file: !4, line: 458, baseType: !184, size: 64, align: 64, offset: 192)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !247, file: !4, line: 459, baseType: !122, size: 64, align: 64, offset: 256)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !247, file: !4, line: 460, baseType: !49, size: 64, align: 64, offset: 320)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "allocator", scope: !247, file: !4, line: 468, baseType: !163, size: 64, align: 64, offset: 384)
!256 = !DIDerivedType(tag: DW_TAG_member, name: "internal", scope: !247, file: !4, line: 471, baseType: !257, size: 64, align: 64, offset: 448)
!257 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !258, size: 64, align: 64)
!258 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_internal", file: !4, line: 411, baseType: !145)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !247, file: !4, line: 479, baseType: !171, size: 64, align: 64, offset: 512)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !247, file: !4, line: 480, baseType: !171, size: 64, align: 64, offset: 576)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !247, file: !4, line: 481, baseType: !171, size: 64, align: 64, offset: 640)
!262 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr4", scope: !247, file: !4, line: 482, baseType: !171, size: 64, align: 64, offset: 704)
!263 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !247, file: !4, line: 483, baseType: !49, size: 64, align: 64, offset: 768)
!264 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !247, file: !4, line: 484, baseType: !49, size: 64, align: 64, offset: 832)
!265 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !247, file: !4, line: 485, baseType: !122, size: 64, align: 64, offset: 896)
!266 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !247, file: !4, line: 486, baseType: !122, size: 64, align: 64, offset: 960)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !247, file: !4, line: 487, baseType: !61, size: 32, align: 32, offset: 1024)
!268 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !247, file: !4, line: 488, baseType: !61, size: 32, align: 32, offset: 1056)
!269 = distinct !DISubprogram(name: "lzma_index_buffer_encode", scope: !1, file: !1, line: 220, type: !270, isLocal: false, isDefinition: true, scopeLine: 222, flags: DIFlagPrototyped, isOptimized: false, variables: !241)
!270 = !DISubroutineType(types: !271)
!271 = !{!162, !23, !184, !182, !122}
!272 = distinct !DISubprogram(name: "index_encode", scope: !1, file: !1, line: 44, type: !160, isLocal: true, isDefinition: true, scopeLine: 52, flags: DIFlagPrototyped, isOptimized: false, variables: !241)
!273 = distinct !DISubprogram(name: "index_encoder_end", scope: !1, file: !1, line: 162, type: !189, isLocal: true, isDefinition: true, scopeLine: 163, flags: DIFlagPrototyped, isOptimized: false, variables: !241)
!274 = distinct !DISubprogram(name: "index_encoder_reset", scope: !1, file: !1, line: 170, type: !275, isLocal: true, isDefinition: true, scopeLine: 171, flags: DIFlagPrototyped, isOptimized: false, variables: !241)
!275 = !DISubroutineType(types: !276)
!276 = !{null, !152, !23}
!277 = !{i32 2, !"Dwarf Version", i32 4}
!278 = !{i32 2, !"Debug Info Version", i32 3}
!279 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!280 = !DILocalVariable(name: "next", arg: 1, scope: !237, file: !1, line: 184, type: !240)
!281 = !DIExpression()
!282 = !DILocation(line: 184, column: 42, scope: !237)
!283 = !DILocalVariable(name: "allocator", arg: 2, scope: !237, file: !1, line: 184, type: !163)
!284 = !DILocation(line: 184, column: 64, scope: !237)
!285 = !DILocalVariable(name: "i", arg: 3, scope: !237, file: !1, line: 185, type: !23)
!286 = !DILocation(line: 185, column: 21, scope: !237)
!287 = !DILocation(line: 187, column: 2, scope: !237)
!288 = !DILocation(line: 187, column: 2, scope: !289)
!289 = !DILexicalBlockFile(scope: !290, file: !1, discriminator: 1)
!290 = distinct !DILexicalBlock(scope: !291, file: !1, line: 187, column: 2)
!291 = distinct !DILexicalBlock(scope: !237, file: !1, line: 187, column: 2)
!292 = !DILocation(line: 187, column: 2, scope: !293)
!293 = !DILexicalBlockFile(scope: !290, file: !1, discriminator: 2)
!294 = !DILocation(line: 187, column: 2, scope: !295)
!295 = !DILexicalBlockFile(scope: !291, file: !1, discriminator: 3)
!296 = !DILocation(line: 189, column: 6, scope: !297)
!297 = distinct !DILexicalBlock(scope: !237, file: !1, line: 189, column: 6)
!298 = !DILocation(line: 189, column: 8, scope: !297)
!299 = !DILocation(line: 189, column: 6, scope: !237)
!300 = !DILocation(line: 190, column: 3, scope: !297)
!301 = !DILocation(line: 192, column: 6, scope: !302)
!302 = distinct !DILexicalBlock(scope: !237, file: !1, line: 192, column: 6)
!303 = !DILocation(line: 192, column: 12, scope: !302)
!304 = !DILocation(line: 192, column: 18, scope: !302)
!305 = !DILocation(line: 192, column: 6, scope: !237)
!306 = !DILocation(line: 193, column: 48, scope: !307)
!307 = distinct !DILexicalBlock(scope: !302, file: !1, line: 192, column: 27)
!308 = !DILocation(line: 193, column: 17, scope: !307)
!309 = !DILocation(line: 193, column: 3, scope: !307)
!310 = !DILocation(line: 193, column: 9, scope: !307)
!311 = !DILocation(line: 193, column: 15, scope: !307)
!312 = !DILocation(line: 194, column: 7, scope: !313)
!313 = distinct !DILexicalBlock(scope: !307, file: !1, line: 194, column: 7)
!314 = !DILocation(line: 194, column: 13, scope: !313)
!315 = !DILocation(line: 194, column: 19, scope: !313)
!316 = !DILocation(line: 194, column: 7, scope: !307)
!317 = !DILocation(line: 195, column: 4, scope: !313)
!318 = !DILocation(line: 197, column: 3, scope: !307)
!319 = !DILocation(line: 197, column: 9, scope: !307)
!320 = !DILocation(line: 197, column: 14, scope: !307)
!321 = !DILocation(line: 198, column: 3, scope: !307)
!322 = !DILocation(line: 198, column: 9, scope: !307)
!323 = !DILocation(line: 198, column: 13, scope: !307)
!324 = !DILocation(line: 199, column: 2, scope: !307)
!325 = !DILocation(line: 201, column: 22, scope: !237)
!326 = !DILocation(line: 201, column: 28, scope: !237)
!327 = !DILocation(line: 201, column: 35, scope: !237)
!328 = !DILocation(line: 201, column: 2, scope: !237)
!329 = !DILocation(line: 203, column: 2, scope: !237)
!330 = !DILocation(line: 204, column: 1, scope: !237)
!331 = !DILocalVariable(name: "coder", arg: 1, scope: !272, file: !1, line: 44, type: !152)
!332 = !DILocation(line: 44, column: 26, scope: !272)
!333 = !DILocalVariable(name: "allocator", arg: 2, scope: !272, file: !1, line: 45, type: !163)
!334 = !DILocation(line: 45, column: 19, scope: !272)
!335 = !DILocalVariable(name: "in", arg: 3, scope: !272, file: !1, line: 46, type: !177)
!336 = !DILocation(line: 46, column: 32, scope: !272)
!337 = !DILocalVariable(name: "in_pos", arg: 4, scope: !272, file: !1, line: 47, type: !181)
!338 = !DILocation(line: 47, column: 25, scope: !272)
!339 = !DILocalVariable(name: "in_size", arg: 5, scope: !272, file: !1, line: 48, type: !122)
!340 = !DILocation(line: 48, column: 10, scope: !272)
!341 = !DILocalVariable(name: "out", arg: 6, scope: !272, file: !1, line: 49, type: !183)
!342 = !DILocation(line: 49, column: 26, scope: !272)
!343 = !DILocalVariable(name: "out_pos", arg: 7, scope: !272, file: !1, line: 49, type: !181)
!344 = !DILocation(line: 49, column: 53, scope: !272)
!345 = !DILocalVariable(name: "out_size", arg: 8, scope: !272, file: !1, line: 50, type: !122)
!346 = !DILocation(line: 50, column: 10, scope: !272)
!347 = !DILocalVariable(name: "action", arg: 9, scope: !272, file: !1, line: 51, type: !185)
!348 = !DILocation(line: 51, column: 15, scope: !272)
!349 = !DILocalVariable(name: "out_start", scope: !272, file: !1, line: 55, type: !350)
!350 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !122)
!351 = !DILocation(line: 55, column: 15, scope: !272)
!352 = !DILocation(line: 55, column: 28, scope: !272)
!353 = !DILocation(line: 55, column: 27, scope: !272)
!354 = !DILocalVariable(name: "ret", scope: !272, file: !1, line: 61, type: !162)
!355 = !DILocation(line: 61, column: 11, scope: !272)
!356 = !DILocation(line: 63, column: 2, scope: !272)
!357 = !DILocation(line: 63, column: 10, scope: !358)
!358 = !DILexicalBlockFile(scope: !272, file: !1, discriminator: 1)
!359 = !DILocation(line: 63, column: 9, scope: !358)
!360 = !DILocation(line: 63, column: 20, scope: !358)
!361 = !DILocation(line: 63, column: 18, scope: !358)
!362 = !DILocation(line: 63, column: 2, scope: !358)
!363 = !DILocation(line: 64, column: 10, scope: !272)
!364 = !DILocation(line: 64, column: 17, scope: !272)
!365 = !DILocation(line: 64, column: 2, scope: !272)
!366 = !DILocation(line: 66, column: 8, scope: !367)
!367 = distinct !DILexicalBlock(scope: !272, file: !1, line: 64, column: 27)
!368 = !DILocation(line: 66, column: 7, scope: !367)
!369 = !DILocation(line: 66, column: 3, scope: !367)
!370 = !DILocation(line: 66, column: 17, scope: !367)
!371 = !DILocation(line: 67, column: 6, scope: !367)
!372 = !DILocation(line: 67, column: 3, scope: !367)
!373 = !DILocation(line: 68, column: 3, scope: !367)
!374 = !DILocation(line: 68, column: 10, scope: !367)
!375 = !DILocation(line: 68, column: 19, scope: !367)
!376 = !DILocation(line: 69, column: 3, scope: !367)
!377 = !DILocalVariable(name: "count", scope: !378, file: !1, line: 72, type: !379)
!378 = distinct !DILexicalBlock(scope: !367, file: !1, line: 71, column: 18)
!379 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !47)
!380 = !DILocation(line: 72, column: 18, scope: !378)
!381 = !DILocation(line: 72, column: 49, scope: !378)
!382 = !DILocation(line: 72, column: 56, scope: !378)
!383 = !DILocation(line: 72, column: 26, scope: !378)
!384 = !DILocation(line: 73, column: 25, scope: !378)
!385 = !DILocation(line: 73, column: 33, scope: !378)
!386 = !DILocation(line: 73, column: 40, scope: !378)
!387 = !DILocation(line: 74, column: 5, scope: !378)
!388 = !DILocation(line: 74, column: 10, scope: !378)
!389 = !DILocation(line: 74, column: 19, scope: !378)
!390 = !DILocation(line: 73, column: 9, scope: !378)
!391 = !DILocation(line: 73, column: 7, scope: !378)
!392 = !DILocation(line: 75, column: 7, scope: !393)
!393 = distinct !DILexicalBlock(scope: !378, file: !1, line: 75, column: 7)
!394 = !DILocation(line: 75, column: 11, scope: !393)
!395 = !DILocation(line: 75, column: 7, scope: !378)
!396 = !DILocation(line: 76, column: 4, scope: !393)
!397 = !DILocation(line: 78, column: 7, scope: !378)
!398 = !DILocation(line: 79, column: 3, scope: !378)
!399 = !DILocation(line: 79, column: 10, scope: !378)
!400 = !DILocation(line: 79, column: 14, scope: !378)
!401 = !DILocation(line: 80, column: 3, scope: !378)
!402 = !DILocation(line: 80, column: 10, scope: !378)
!403 = !DILocation(line: 80, column: 19, scope: !378)
!404 = !DILocation(line: 81, column: 3, scope: !378)
!405 = !DILocation(line: 86, column: 6, scope: !406)
!406 = distinct !DILexicalBlock(scope: !367, file: !1, line: 85, column: 7)
!407 = !DILocation(line: 86, column: 13, scope: !406)
!408 = !DILocation(line: 85, column: 7, scope: !406)
!409 = !DILocation(line: 85, column: 7, scope: !367)
!410 = !DILocation(line: 88, column: 41, scope: !411)
!411 = distinct !DILexicalBlock(scope: !406, file: !1, line: 86, column: 43)
!412 = !DILocation(line: 88, column: 48, scope: !411)
!413 = !DILocation(line: 88, column: 17, scope: !411)
!414 = !DILocation(line: 88, column: 4, scope: !411)
!415 = !DILocation(line: 88, column: 11, scope: !411)
!416 = !DILocation(line: 88, column: 15, scope: !411)
!417 = !DILocation(line: 89, column: 4, scope: !411)
!418 = !DILocation(line: 89, column: 4, scope: !419)
!419 = !DILexicalBlockFile(scope: !411, file: !1, discriminator: 1)
!420 = !DILocation(line: 89, column: 4, scope: !421)
!421 = !DILexicalBlockFile(scope: !411, file: !1, discriminator: 2)
!422 = !DILocation(line: 89, column: 4, scope: !423)
!423 = !DILexicalBlockFile(scope: !411, file: !1, discriminator: 3)
!424 = !DILocation(line: 90, column: 4, scope: !411)
!425 = !DILocation(line: 90, column: 11, scope: !411)
!426 = !DILocation(line: 90, column: 20, scope: !411)
!427 = !DILocation(line: 91, column: 4, scope: !411)
!428 = !DILocation(line: 94, column: 3, scope: !367)
!429 = !DILocation(line: 94, column: 10, scope: !367)
!430 = !DILocation(line: 94, column: 19, scope: !367)
!431 = !DILocalVariable(name: "size", scope: !432, file: !1, line: 100, type: !379)
!432 = distinct !DILexicalBlock(scope: !367, file: !1, line: 99, column: 25)
!433 = !DILocation(line: 100, column: 18, scope: !432)
!434 = !DILocation(line: 100, column: 25, scope: !432)
!435 = !DILocation(line: 100, column: 32, scope: !432)
!436 = !DILocation(line: 100, column: 41, scope: !432)
!437 = !DILocation(line: 101, column: 7, scope: !432)
!438 = !DILocation(line: 101, column: 14, scope: !432)
!439 = !DILocation(line: 101, column: 19, scope: !432)
!440 = !DILocation(line: 101, column: 25, scope: !432)
!441 = !DILocation(line: 100, column: 25, scope: !442)
!442 = !DILexicalBlockFile(scope: !432, file: !1, discriminator: 1)
!443 = !DILocation(line: 102, column: 7, scope: !432)
!444 = !DILocation(line: 102, column: 14, scope: !432)
!445 = !DILocation(line: 102, column: 19, scope: !432)
!446 = !DILocation(line: 102, column: 25, scope: !432)
!447 = !DILocation(line: 100, column: 25, scope: !448)
!448 = !DILexicalBlockFile(scope: !432, file: !1, discriminator: 2)
!449 = !DILocation(line: 100, column: 25, scope: !450)
!450 = !DILexicalBlockFile(scope: !432, file: !1, discriminator: 3)
!451 = !DILocation(line: 100, column: 18, scope: !450)
!452 = !DILocation(line: 104, column: 25, scope: !432)
!453 = !DILocation(line: 104, column: 32, scope: !432)
!454 = !DILocation(line: 104, column: 39, scope: !432)
!455 = !DILocation(line: 105, column: 5, scope: !432)
!456 = !DILocation(line: 105, column: 10, scope: !432)
!457 = !DILocation(line: 105, column: 19, scope: !432)
!458 = !DILocation(line: 104, column: 9, scope: !432)
!459 = !DILocation(line: 104, column: 7, scope: !432)
!460 = !DILocation(line: 106, column: 7, scope: !461)
!461 = distinct !DILexicalBlock(scope: !432, file: !1, line: 106, column: 7)
!462 = !DILocation(line: 106, column: 11, scope: !461)
!463 = !DILocation(line: 106, column: 7, scope: !432)
!464 = !DILocation(line: 107, column: 4, scope: !461)
!465 = !DILocation(line: 109, column: 7, scope: !432)
!466 = !DILocation(line: 110, column: 3, scope: !432)
!467 = !DILocation(line: 110, column: 10, scope: !432)
!468 = !DILocation(line: 110, column: 14, scope: !432)
!469 = !DILocation(line: 113, column: 5, scope: !432)
!470 = !DILocation(line: 113, column: 12, scope: !432)
!471 = !DILocation(line: 113, column: 3, scope: !432)
!472 = !DILocation(line: 114, column: 3, scope: !432)
!473 = !DILocation(line: 118, column: 7, scope: !474)
!474 = distinct !DILexicalBlock(scope: !367, file: !1, line: 118, column: 7)
!475 = !DILocation(line: 118, column: 14, scope: !474)
!476 = !DILocation(line: 118, column: 18, scope: !474)
!477 = !DILocation(line: 118, column: 7, scope: !367)
!478 = !DILocation(line: 119, column: 6, scope: !479)
!479 = distinct !DILexicalBlock(scope: !474, file: !1, line: 118, column: 23)
!480 = !DILocation(line: 119, column: 13, scope: !479)
!481 = !DILocation(line: 119, column: 4, scope: !479)
!482 = !DILocation(line: 120, column: 10, scope: !479)
!483 = !DILocation(line: 120, column: 18, scope: !479)
!484 = !DILocation(line: 120, column: 4, scope: !479)
!485 = !DILocation(line: 120, column: 22, scope: !479)
!486 = !DILocation(line: 121, column: 4, scope: !479)
!487 = !DILocation(line: 125, column: 29, scope: !367)
!488 = !DILocation(line: 125, column: 35, scope: !367)
!489 = !DILocation(line: 125, column: 33, scope: !367)
!490 = !DILocation(line: 126, column: 6, scope: !367)
!491 = !DILocation(line: 126, column: 5, scope: !367)
!492 = !DILocation(line: 126, column: 16, scope: !367)
!493 = !DILocation(line: 126, column: 14, scope: !367)
!494 = !DILocation(line: 126, column: 27, scope: !367)
!495 = !DILocation(line: 126, column: 34, scope: !367)
!496 = !DILocation(line: 125, column: 18, scope: !367)
!497 = !DILocation(line: 125, column: 3, scope: !367)
!498 = !DILocation(line: 125, column: 10, scope: !367)
!499 = !DILocation(line: 125, column: 16, scope: !367)
!500 = !DILocation(line: 128, column: 3, scope: !367)
!501 = !DILocation(line: 128, column: 10, scope: !367)
!502 = !DILocation(line: 128, column: 19, scope: !367)
!503 = !DILocation(line: 135, column: 3, scope: !367)
!504 = !DILocation(line: 136, column: 9, scope: !505)
!505 = distinct !DILexicalBlock(scope: !506, file: !1, line: 136, column: 8)
!506 = distinct !DILexicalBlock(scope: !367, file: !1, line: 135, column: 6)
!507 = !DILocation(line: 136, column: 8, scope: !505)
!508 = !DILocation(line: 136, column: 20, scope: !505)
!509 = !DILocation(line: 136, column: 17, scope: !505)
!510 = !DILocation(line: 136, column: 8, scope: !506)
!511 = !DILocation(line: 137, column: 5, scope: !505)
!512 = !DILocation(line: 139, column: 21, scope: !506)
!513 = !DILocation(line: 139, column: 28, scope: !506)
!514 = !DILocation(line: 139, column: 38, scope: !506)
!515 = !DILocation(line: 139, column: 45, scope: !506)
!516 = !DILocation(line: 139, column: 49, scope: !506)
!517 = !DILocation(line: 139, column: 34, scope: !506)
!518 = !DILocation(line: 140, column: 6, scope: !506)
!519 = !DILocation(line: 139, column: 20, scope: !506)
!520 = !DILocation(line: 139, column: 9, scope: !506)
!521 = !DILocation(line: 139, column: 8, scope: !506)
!522 = !DILocation(line: 139, column: 4, scope: !506)
!523 = !DILocation(line: 139, column: 18, scope: !506)
!524 = !DILocation(line: 141, column: 7, scope: !506)
!525 = !DILocation(line: 141, column: 4, scope: !506)
!526 = !DILocation(line: 143, column: 3, scope: !506)
!527 = !DILocation(line: 143, column: 14, scope: !528)
!528 = !DILexicalBlockFile(scope: !367, file: !1, discriminator: 1)
!529 = !DILocation(line: 143, column: 21, scope: !528)
!530 = !DILocation(line: 143, column: 12, scope: !528)
!531 = !DILocation(line: 143, column: 25, scope: !528)
!532 = !DILocation(line: 143, column: 3, scope: !528)
!533 = !DILocation(line: 145, column: 3, scope: !367)
!534 = !DILocation(line: 148, column: 3, scope: !367)
!535 = !DILocation(line: 63, column: 2, scope: !536)
!536 = !DILexicalBlockFile(scope: !272, file: !1, discriminator: 2)
!537 = !DILocation(line: 63, column: 2, scope: !538)
!538 = !DILexicalBlockFile(scope: !272, file: !1, discriminator: 3)
!539 = !DILocation(line: 154, column: 28, scope: !272)
!540 = !DILocation(line: 154, column: 34, scope: !272)
!541 = !DILocation(line: 154, column: 32, scope: !272)
!542 = !DILocation(line: 155, column: 5, scope: !272)
!543 = !DILocation(line: 155, column: 4, scope: !272)
!544 = !DILocation(line: 155, column: 15, scope: !272)
!545 = !DILocation(line: 155, column: 13, scope: !272)
!546 = !DILocation(line: 155, column: 26, scope: !272)
!547 = !DILocation(line: 155, column: 33, scope: !272)
!548 = !DILocation(line: 154, column: 17, scope: !272)
!549 = !DILocation(line: 154, column: 2, scope: !272)
!550 = !DILocation(line: 154, column: 9, scope: !272)
!551 = !DILocation(line: 154, column: 15, scope: !272)
!552 = !DILocation(line: 157, column: 9, scope: !272)
!553 = !DILocation(line: 157, column: 2, scope: !272)
!554 = !DILocation(line: 158, column: 1, scope: !272)
!555 = !DILocalVariable(name: "coder", arg: 1, scope: !273, file: !1, line: 162, type: !152)
!556 = !DILocation(line: 162, column: 31, scope: !273)
!557 = !DILocalVariable(name: "allocator", arg: 2, scope: !273, file: !1, line: 162, type: !163)
!558 = !DILocation(line: 162, column: 54, scope: !273)
!559 = !DILocation(line: 164, column: 12, scope: !273)
!560 = !DILocation(line: 164, column: 19, scope: !273)
!561 = !DILocation(line: 164, column: 2, scope: !273)
!562 = !DILocation(line: 165, column: 2, scope: !273)
!563 = !DILocalVariable(name: "coder", arg: 1, scope: !274, file: !1, line: 170, type: !152)
!564 = !DILocation(line: 170, column: 33, scope: !274)
!565 = !DILocalVariable(name: "i", arg: 2, scope: !274, file: !1, line: 170, type: !23)
!566 = !DILocation(line: 170, column: 58, scope: !274)
!567 = !DILocation(line: 172, column: 24, scope: !274)
!568 = !DILocation(line: 172, column: 31, scope: !274)
!569 = !DILocation(line: 172, column: 37, scope: !274)
!570 = !DILocation(line: 172, column: 2, scope: !274)
!571 = !DILocation(line: 174, column: 2, scope: !274)
!572 = !DILocation(line: 174, column: 9, scope: !274)
!573 = !DILocation(line: 174, column: 18, scope: !274)
!574 = !DILocation(line: 175, column: 17, scope: !274)
!575 = !DILocation(line: 175, column: 2, scope: !274)
!576 = !DILocation(line: 175, column: 9, scope: !274)
!577 = !DILocation(line: 175, column: 15, scope: !274)
!578 = !DILocation(line: 176, column: 2, scope: !274)
!579 = !DILocation(line: 176, column: 9, scope: !274)
!580 = !DILocation(line: 176, column: 13, scope: !274)
!581 = !DILocation(line: 177, column: 2, scope: !274)
!582 = !DILocation(line: 177, column: 9, scope: !274)
!583 = !DILocation(line: 177, column: 15, scope: !274)
!584 = !DILocation(line: 179, column: 2, scope: !274)
!585 = !DILocalVariable(name: "strm", arg: 1, scope: !242, file: !1, line: 208, type: !245)
!586 = !DILocation(line: 208, column: 33, scope: !242)
!587 = !DILocalVariable(name: "i", arg: 2, scope: !242, file: !1, line: 208, type: !23)
!588 = !DILocation(line: 208, column: 57, scope: !242)
!589 = !DILocation(line: 210, column: 2, scope: !242)
!590 = !DILocalVariable(name: "ret_", scope: !591, file: !1, line: 210, type: !162)
!591 = distinct !DILexicalBlock(scope: !242, file: !1, line: 210, column: 2)
!592 = !DILocation(line: 210, column: 2, scope: !591)
!593 = !DILocation(line: 210, column: 2, scope: !594)
!594 = !DILexicalBlockFile(scope: !591, file: !1, discriminator: 1)
!595 = !DILocalVariable(name: "ret_", scope: !596, file: !1, line: 210, type: !597)
!596 = distinct !DILexicalBlock(scope: !591, file: !1, line: 210, column: 2)
!597 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !162)
!598 = !DILocation(line: 210, column: 2, scope: !596)
!599 = !DILocation(line: 210, column: 2, scope: !600)
!600 = !DILexicalBlockFile(scope: !596, file: !1, discriminator: 2)
!601 = !DILocation(line: 210, column: 2, scope: !602)
!602 = !DILexicalBlockFile(scope: !603, file: !1, discriminator: 3)
!603 = distinct !DILexicalBlock(scope: !596, file: !1, line: 210, column: 2)
!604 = !DILocation(line: 210, column: 2, scope: !605)
!605 = !DILexicalBlockFile(scope: !596, file: !1, discriminator: 4)
!606 = !DILocation(line: 210, column: 2, scope: !607)
!607 = !DILexicalBlockFile(scope: !591, file: !1, discriminator: 5)
!608 = !DILocation(line: 210, column: 2, scope: !609)
!609 = !DILexicalBlockFile(scope: !610, file: !1, discriminator: 6)
!610 = distinct !DILexicalBlock(scope: !611, file: !1, line: 210, column: 2)
!611 = distinct !DILexicalBlock(scope: !591, file: !1, line: 210, column: 2)
!612 = !DILocation(line: 210, column: 2, scope: !613)
!613 = !DILexicalBlockFile(scope: !591, file: !1, discriminator: 7)
!614 = !DILocation(line: 212, column: 2, scope: !242)
!615 = !DILocation(line: 212, column: 8, scope: !242)
!616 = !DILocation(line: 212, column: 18, scope: !242)
!617 = !DILocation(line: 212, column: 46, scope: !242)
!618 = !DILocation(line: 213, column: 2, scope: !242)
!619 = !DILocation(line: 213, column: 8, scope: !242)
!620 = !DILocation(line: 213, column: 18, scope: !242)
!621 = !DILocation(line: 213, column: 49, scope: !242)
!622 = !DILocation(line: 215, column: 2, scope: !242)
!623 = !DILocation(line: 216, column: 1, scope: !242)
!624 = !DILocalVariable(name: "i", arg: 1, scope: !269, file: !1, line: 220, type: !23)
!625 = !DILocation(line: 220, column: 44, scope: !269)
!626 = !DILocalVariable(name: "out", arg: 2, scope: !269, file: !1, line: 221, type: !184)
!627 = !DILocation(line: 221, column: 12, scope: !269)
!628 = !DILocalVariable(name: "out_pos", arg: 3, scope: !269, file: !1, line: 221, type: !182)
!629 = !DILocation(line: 221, column: 25, scope: !269)
!630 = !DILocalVariable(name: "out_size", arg: 4, scope: !269, file: !1, line: 221, type: !122)
!631 = !DILocation(line: 221, column: 41, scope: !269)
!632 = !DILocalVariable(name: "coder", scope: !269, file: !1, line: 223, type: !153)
!633 = !DILocation(line: 223, column: 13, scope: !269)
!634 = !DILocalVariable(name: "out_start", scope: !269, file: !1, line: 224, type: !122)
!635 = !DILocation(line: 224, column: 9, scope: !269)
!636 = !DILocalVariable(name: "ret", scope: !269, file: !1, line: 225, type: !162)
!637 = !DILocation(line: 225, column: 11, scope: !269)
!638 = !DILocation(line: 228, column: 6, scope: !639)
!639 = distinct !DILexicalBlock(scope: !269, file: !1, line: 228, column: 6)
!640 = !DILocation(line: 228, column: 8, scope: !639)
!641 = !DILocation(line: 228, column: 16, scope: !639)
!642 = !DILocation(line: 228, column: 19, scope: !643)
!643 = !DILexicalBlockFile(scope: !639, file: !1, discriminator: 1)
!644 = !DILocation(line: 228, column: 23, scope: !643)
!645 = !DILocation(line: 228, column: 31, scope: !643)
!646 = !DILocation(line: 228, column: 34, scope: !647)
!647 = !DILexicalBlockFile(scope: !639, file: !1, discriminator: 2)
!648 = !DILocation(line: 228, column: 42, scope: !647)
!649 = !DILocation(line: 228, column: 50, scope: !647)
!650 = !DILocation(line: 228, column: 54, scope: !651)
!651 = !DILexicalBlockFile(scope: !639, file: !1, discriminator: 3)
!652 = !DILocation(line: 228, column: 53, scope: !651)
!653 = !DILocation(line: 228, column: 64, scope: !651)
!654 = !DILocation(line: 228, column: 62, scope: !651)
!655 = !DILocation(line: 228, column: 6, scope: !651)
!656 = !DILocation(line: 229, column: 3, scope: !639)
!657 = !DILocation(line: 232, column: 6, scope: !658)
!658 = distinct !DILexicalBlock(scope: !269, file: !1, line: 232, column: 6)
!659 = !DILocation(line: 232, column: 18, scope: !658)
!660 = !DILocation(line: 232, column: 17, scope: !658)
!661 = !DILocation(line: 232, column: 15, scope: !658)
!662 = !DILocation(line: 232, column: 44, scope: !658)
!663 = !DILocation(line: 232, column: 28, scope: !658)
!664 = !DILocation(line: 232, column: 26, scope: !658)
!665 = !DILocation(line: 232, column: 6, scope: !269)
!666 = !DILocation(line: 233, column: 3, scope: !658)
!667 = !DILocation(line: 237, column: 30, scope: !269)
!668 = !DILocation(line: 237, column: 2, scope: !269)
!669 = !DILocation(line: 241, column: 15, scope: !269)
!670 = !DILocation(line: 241, column: 14, scope: !269)
!671 = !DILocation(line: 241, column: 12, scope: !269)
!672 = !DILocation(line: 243, column: 4, scope: !269)
!673 = !DILocation(line: 243, column: 9, scope: !269)
!674 = !DILocation(line: 243, column: 18, scope: !269)
!675 = !DILocation(line: 242, column: 8, scope: !269)
!676 = !DILocation(line: 242, column: 6, scope: !269)
!677 = !DILocation(line: 245, column: 6, scope: !678)
!678 = distinct !DILexicalBlock(scope: !269, file: !1, line: 245, column: 6)
!679 = !DILocation(line: 245, column: 10, scope: !678)
!680 = !DILocation(line: 245, column: 6, scope: !269)
!681 = !DILocation(line: 246, column: 7, scope: !682)
!682 = distinct !DILexicalBlock(scope: !678, file: !1, line: 245, column: 30)
!683 = !DILocation(line: 247, column: 2, scope: !682)
!684 = !DILocation(line: 251, column: 3, scope: !685)
!685 = distinct !DILexicalBlock(scope: !678, file: !1, line: 247, column: 9)
!686 = !DILocation(line: 256, column: 9, scope: !269)
!687 = !DILocation(line: 256, column: 2, scope: !269)
!688 = !DILocation(line: 257, column: 1, scope: !269)
